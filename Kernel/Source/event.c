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
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define osEventFlagsLimit     31U    ///< number of Event Flags available per object

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
uint32_t FlagsSet(osEventFlags_t *evf, uint32_t flags)
{
  uint32_t event_flags;

  evf->event_flags |= flags;
  event_flags = evf->event_flags;

  return (event_flags);
}

static
uint32_t FlagsCheck (osEventFlags_t *evf, uint32_t flags, uint32_t options)
{
  uint32_t pattern;

  if ((options & osFlagsNoClear) == 0U) {
    pattern = evf->event_flags;

    if ((((options & osFlagsWaitAll) != 0U) && ((pattern & flags) != flags)) ||
        (((options & osFlagsWaitAll) == 0U) && ((pattern & flags) == 0U)))
    {
      pattern = 0U;
    }
    else {
      evf->event_flags &= ~flags;
    }
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

static osEventFlagsId_t EventFlagsNew(const osEventFlagsAttr_t *attr)
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

  return (evf);
}

static const char *EventFlagsGetName(osEventFlagsId_t ef_id)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS)) {
    return (NULL);
  }

  return (evf->name);
}

static uint32_t EventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  uint32_t        event_flags;
  uint32_t        pattern;
  queue_t        *que;
  osThread_t     *thread;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS) ||
      (flags == 0U) || ((flags & (1UL << osEventFlagsLimit)) != 0U))
  {
    return ((uint32_t)osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  /* Set Event Flags */
  event_flags = FlagsSet(evf, flags);

  que = evf->wait_queue.next;
  while (que != &evf->wait_queue) {
    thread = GetThreadByQueue(que);
    que = que->next;

    pattern = FlagsCheck(evf, thread->winfo.event.flags, thread->winfo.event.options);

    if (pattern) {
      if (!(thread->winfo.event.options & osFlagsNoClear)) {
        event_flags = pattern & ~thread->winfo.event.flags;
      }
      else {
        event_flags = pattern;
      }
      libThreadWaitExit(thread, pattern, DISPATCH_NO);
    }
  }
  libThreadDispatch(NULL);

  END_CRITICAL_SECTION

  return (event_flags);
}

static uint32_t EventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  uint32_t event_flags;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS) ||
      (flags == 0U) || ((flags & (1UL << osEventFlagsLimit)) != 0U))
  {
    return ((uint32_t)osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  event_flags = evf->event_flags;
  evf->event_flags &= ~flags;

  END_CRITICAL_SECTION

  return (event_flags);
}

static uint32_t EventFlagsGet(osEventFlagsId_t ef_id)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS)) {
    return (0U);
  }

  return (evf->event_flags);
}

static uint32_t EventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;
  osThread_t *thread;
  winfo_event_t *winfo;
  uint32_t event_flags;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS) ||
      (flags == 0U) || ((flags & (1UL << osEventFlagsLimit)) != 0U))
  {
    return ((uint32_t)osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  event_flags = FlagsCheck(evf, flags, options);

  if (event_flags == 0U) {
    if (timeout != 0U) {
      thread = ThreadGetRunning();
      if (libThreadWaitEnter(thread, &evf->wait_queue, timeout)) {
        winfo = &thread->winfo.event;
        winfo->options = options;
        winfo->flags = flags;
        event_flags = (uint32_t)osThreadWait;
      }
      else {
        event_flags = (uint32_t)osErrorTimeout;
      }
    }
    else {
      event_flags = (uint32_t)osErrorResource;
    }
  }

  END_CRITICAL_SECTION

  return (event_flags);
}

static osStatus_t EventFlagsDelete(osEventFlagsId_t ef_id)
{
  osEventFlags_t *evf = (osEventFlags_t *)ef_id;

  /* Check parameters */
  if ((evf == NULL) || (evf->id != ID_EVENT_FLAGS)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  libThreadWaitDelete(&evf->wait_queue);

  /* Mark object as invalid */
  evf->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  Post ISR processing
 ******************************************************************************/

/**
 * @fn          void osKrnEventFlagsPostProcess(osEventFlags_t*)
 * @brief       Event Flags post ISR processing.
 * @param[in]   evf  event flags object.
 */
void krnEventFlagsPostProcess(osEventFlags_t *evf)
{

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
    ef_id = (osEventFlagsId_t)SVC_1(attr, EventFlagsNew);
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
    name = (const char *)SVC_1(ef_id, EventFlagsGetName);
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

  if (IsIrqMode() || IsIrqMasked()) {
    event_flags = EventFlagsSet(ef_id, flags);
  }
  else {
    event_flags = SVC_2(ef_id, flags, EventFlagsSet);
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

  if (IsIrqMode() || IsIrqMasked()) {
    event_flags = EventFlagsClear(ef_id, flags);
  }
  else {
    event_flags = SVC_2(ef_id, flags, EventFlagsClear);
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
    event_flags = EventFlagsGet(ef_id);
  }
  else {
    event_flags = SVC_1(ef_id, EventFlagsGet);
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

  if (IsIrqMode() || IsIrqMasked()) {
    if (timeout != 0U) {
      event_flags = (uint32_t)osErrorParameter;
    }
    else {
      event_flags = EventFlagsWait(ef_id, flags, options, timeout);
    }
  }
  else {
    event_flags = SVC_4(ef_id, flags, options, timeout, EventFlagsWait);
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
    status = (osStatus_t)SVC_1(ef_id, EventFlagsDelete);
  }

  return (status);
}

/* ----------------------------- End of file ---------------------------------*/
