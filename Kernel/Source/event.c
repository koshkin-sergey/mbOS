/*
 * Copyright (C) 2017-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Project: mbOS real-time kernel
 */

/**
 * @file
 *
 * Kernel system routines.
 *
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "kernel_lib.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define osEventFlagsLimit     31U    ///< number of Event Flags available per object
#define osEventFlagsMask      ((1UL << osEventFlagsLimit) - 1UL)

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

static
uint32_t EventFlagsSet(osEventFlags_t *evf, uint32_t flags)
{
  uint32_t event_flags;

  BEGIN_CRITICAL_SECTION

  evf->event_flags |= flags;
  event_flags = evf->event_flags;

  END_CRITICAL_SECTION

  return (event_flags);
}

static
uint32_t EventFlagsCheck(osEventFlags_t *evf, uint32_t flags, uint32_t options)
{
  uint32_t pattern;

  if ((options & osFlagsNoClear) == 0U) {
    BEGIN_CRITICAL_SECTION

    pattern = evf->event_flags;
    if ((((options & osFlagsWaitAll) != 0U) && ((pattern & flags) != flags)) ||
        (((options & osFlagsWaitAll) == 0U) && ((pattern & flags) == 0U)))
    {
      pattern = 0U;
    }
    else {
      evf->event_flags &= ~flags;
    }

    END_CRITICAL_SECTION
  }
  else {
    pattern = evf->event_flags;

    if ((((options & osFlagsWaitAll) != 0U) && ((pattern & flags) != flags)) ||
        (((options & osFlagsWaitAll) == 0U) && ((pattern & flags) == 0U)))
    {
      pattern = 0U;
    }
  }

  return (pattern);
}

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static osEventFlagsId_t svcEventFlagsNew(const osEventFlagsAttr_t *attr)
{
  osEventFlags_t *evf;

  /* Check parameters */
  if ((attr == NULL)                        ||
      (attr->cb_mem == NULL)                ||
      (((uint32_t)attr->cb_mem & 3U) != 0U) ||
      (attr->cb_size < sizeof(osEventFlags_t)))
  {
    return (NULL);
  }

  evf = attr->cb_mem;

  /* Initialize control block */
  evf->id = ID_EVENT_FLAGS;
  evf->flags = 0U;
  evf->name = attr->name;
  evf->event_flags = 0U;

  QueueReset(&evf->wait_queue);
  QueueReset(&evf->post_queue);

  return (evf);
}

static const char *svcEventFlagsGetName(osEventFlagsId_t ef_id)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS)) {
    return (NULL);
  }

  return (evf->name);
}

static uint32_t svcEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  uint32_t        event_flags;
  uint32_t        pattern;
  queue_t        *que;
  osThread_t     *thread;

  /* Check parameters */
  if (evf == NULL || evf->id != ID_EVENT_FLAGS) {
    return (osFlagsErrorParameter);
  }

  /* Set Event Flags */
  event_flags = EventFlagsSet(evf, flags);

  /* Check if Threads are waiting for Event Flags */
  que = evf->wait_queue.next;
  while (que != &evf->wait_queue) {
    thread = GetThreadByQueue(que);
    que = que->next;

    pattern = EventFlagsCheck(evf, thread->winfo.event.flags, thread->winfo.event.options);
    if (pattern) {
      if (!(thread->winfo.event.options & osFlagsNoClear)) {
        event_flags = pattern & ~thread->winfo.event.flags;
      }
      else {
        event_flags = pattern;
      }
      krnThreadWaitExit(thread, pattern, DISPATCH_NO);
    }
  }

  krnThreadDispatch(NULL);

  return (event_flags);
}

static uint32_t svcEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  uint32_t event_flags;

  /* Check parameters */
  if (evf == NULL || evf->id != ID_EVENT_FLAGS) {
    return (osFlagsErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  event_flags = evf->event_flags;
  evf->event_flags &= ~flags;

  END_CRITICAL_SECTION

  return (event_flags);
}

static uint32_t svcEventFlagsGet(osEventFlagsId_t ef_id)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS)) {
    return (0U);
  }

  return (evf->event_flags);
}

static uint32_t svcEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  winfo_flags_t  *winfo;
  uint32_t        event_flags;

  /* Check parameters */
  if (evf == NULL || evf->id != ID_EVENT_FLAGS) {
    return (osFlagsErrorParameter);
  }

  event_flags = EventFlagsCheck(evf, flags, options);

  if (event_flags == 0U) {
    if (timeout != 0U) {
      event_flags = (uint32_t)krnThreadWaitEnter(ThreadWaitingEventFlags, &evf->wait_queue, timeout);
      if (event_flags != (uint32_t)osErrorTimeout) {
        winfo          = &ThreadGetRunning()->winfo.event;
        winfo->options = options;
        winfo->flags   = flags;
      }
    }
    else {
      event_flags = osFlagsErrorResource;
    }
  }

  return (event_flags);
}

static osStatus_t svcEventFlagsDelete(osEventFlagsId_t ef_id)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  krnThreadWaitDelete(&evf->wait_queue);

  /* Mark object as invalid */
  evf->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  ISR Calls
 ******************************************************************************/

__STATIC_INLINE
uint32_t isrEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  uint32_t        event_flags;

  /* Check parameters */
  if (evf == NULL || evf->id != ID_EVENT_FLAGS) {
    return (osFlagsErrorParameter);
  }

  /* Set Event Flags */
  event_flags = EventFlagsSet(evf, flags);

  /* Register post ISR processing */
  krnPostProcess((osObject_t *)evf);

  return (event_flags);
}

__STATIC_INLINE
uint32_t isrEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  uint32_t        event_flags;

  /* Check parameters */
  if (evf == NULL || evf->id != ID_EVENT_FLAGS || timeout != 0U) {
    return (osFlagsErrorParameter);
  }

  /* Check Event Flags */
  event_flags = EventFlagsCheck(evf, flags, options);
  if (event_flags == 0U) {
    event_flags = osFlagsErrorResource;
  }

  return (event_flags);
}

/*******************************************************************************
 *  Post ISR processing
 ******************************************************************************/

/**
 * @brief       Event Flags post ISR processing.
 * @param[in]   evf  event flags object.
 */
void krnEventFlagsPostProcess(osEventFlags_t *evf)
{
  uint32_t    pattern;
  queue_t    *que;
  osThread_t *thread;

  /* Check if Threads are waiting for Event Flags */
  que = evf->wait_queue.next;
  while (que != &evf->wait_queue) {
    thread = GetThreadByQueue(que);
    que = que->next;

    pattern = EventFlagsCheck(evf, thread->winfo.event.flags, thread->winfo.event.options);
    if (pattern) {
      krnThreadWaitExit(thread, pattern, DISPATCH_NO);
    }
  }
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osEventFlagsId_t osEventFlagsNew(const osEventFlagsAttr_t *attr)
 * @brief       Create and Initialize an Event Flags object.
 * @param[in]   attr  event flags attributes.
 * @return      event flags ID for reference by other functions or NULL in case of error.
 */
osEventFlagsId_t osEventFlagsNew(const osEventFlagsAttr_t *attr)
{
  osEventFlagsId_t ef_id;

  if (IsIrqMode() || IsIrqMasked()) {
    ef_id = NULL;
  }
  else {
    ef_id = (osEventFlagsId_t)SVC_1(attr, svcEventFlagsNew);
  }

  return (ef_id);
}

/**
 * @fn          const char *osEventFlagsGetName(osEventFlagsId_t ef_id)
 * @brief       Get name of an Event Flags object.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osEventFlagsGetName(osEventFlagsId_t ef_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(ef_id, svcEventFlagsGetName);
  }

  return (name);
}

/**
 * @fn          uint32_t osEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
 * @brief       Set the specified Event Flags.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]   flags   specifies the flags that shall be set.
 * @return      event flags after setting or error code if highest bit set.
 */
uint32_t osEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
{
  uint32_t event_flags;

  /* Check parameters */
  if (flags == 0U || (flags & ~osEventFlagsMask) != 0U) {
    return (osFlagsErrorParameter);
  }

  if (IsIrqMode() || IsIrqMasked()) {
    event_flags = isrEventFlagsSet(ef_id, flags);
  }
  else {
    event_flags = SVC_2(ef_id, flags, svcEventFlagsSet);
  }

  return (event_flags);
}

/**
 * @fn          uint32_t osEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags)
 * @brief       Clear the specified Event Flags.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]   flags   specifies the flags that shall be cleared.
 * @return      event flags before clearing or error code if highest bit set.
 */
uint32_t osEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags)
{
  uint32_t event_flags;

  /* Check parameters */
  if (flags == 0U || (flags & ~osEventFlagsMask) != 0U) {
    return (osFlagsErrorParameter);
  }

  if (IsIrqMode() || IsIrqMasked()) {
    event_flags = svcEventFlagsClear(ef_id, flags);
  }
  else {
    event_flags = SVC_2(ef_id, flags, svcEventFlagsClear);
  }

  return (event_flags);
}

/**
 * @fn          uint32_t osEventFlagsGet(osEventFlagsId_t ef_id)
 * @brief       Get the current Event Flags.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @return      current event flags or 0 in case of an error.
 */
uint32_t osEventFlagsGet(osEventFlagsId_t ef_id)
{
  uint32_t event_flags;

  if (IsIrqMode() || IsIrqMasked()) {
    event_flags = svcEventFlagsGet(ef_id);
  }
  else {
    event_flags = SVC_1(ef_id, svcEventFlagsGet);
  }

  return (event_flags);
}

/**
 * @fn          uint32_t osEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
 * @brief       Wait for one or more Event Flags to become signaled.
 * @param[in]   ef_id     event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]   flags     specifies the flags to wait for.
 * @param[in]   options   specifies flags options (osFlagsXxxx).
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      event flags before clearing or error code if highest bit set.
 */
uint32_t osEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
{
  uint32_t event_flags;

  /* Check parameters */
  if (flags == 0U || (flags & ~osEventFlagsMask) != 0U) {
    return (osFlagsErrorParameter);
  }

  if (IsIrqMode() || IsIrqMasked()) {
    event_flags = isrEventFlagsWait(ef_id, flags, options, timeout);
  }
  else {
    event_flags = SVC_4(ef_id, flags, options, timeout, svcEventFlagsWait);
    if ((int32_t)event_flags == osThreadWait) {
      event_flags = ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (event_flags);
}

/**
 * @fn          osStatus_t osEventFlagsDelete(osEventFlagsId_t ef_id)
 * @brief       Delete an Event Flags object.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osEventFlagsDelete(osEventFlagsId_t ef_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(ef_id, svcEventFlagsDelete);
  }

  return (status);
}

/* ----------------------------- End of file ---------------------------------*/
