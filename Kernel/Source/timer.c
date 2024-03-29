/*
 * Copyright (C) 2011-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/* Timer State definitions */
#define osTimerInactive      0x00U   ///< Timer Inactive
#define osTimerStopped       0x01U   ///< Timer Stopped
#define osTimerRunning       0x02U   ///< Timer Running

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

static osTimerFinfo_t *TimerGetFinfo(void)
{
  osTimer_t      *timer;
  osTimerFinfo_t *timer_finfo = NULL;
  queue_t        *timer_queue = &osInfo.timer_queue;

  if (!isQueueEmpty(timer_queue)) {
    timer = GetTimerByQueue(timer_queue->next);
    if (time_before_eq(timer->time, osInfo.kernel.tick)) {
      krnTimerRemove(timer);
      if (timer->type == osTimerPeriodic) {
        krnTimerInsert(timer, timer->load);
      }
      else {
        timer->state = osTimerStopped;
      }
      timer_finfo = &timer->finfo;
    }
  }

  return (timer_finfo);
}

/*******************************************************************************
 *  Library functions
 ******************************************************************************/

void krnTimerInsert(osTimer_t *timer, uint32_t time)
{
  queue_t *que;
  queue_t *timer_queue;

  timer_queue = &osInfo.timer_queue;
  timer->time = time + osInfo.kernel.tick;

  for (que = timer_queue->next; que != timer_queue; que = que->next) {
    if (time_before(timer->time, GetTimerByQueue(que)->time)) {
      break;
    }
  }

  QueueAppend(que, &timer->timer_que);
}

void krnTimerRemove(osTimer_t *timer)
{
  QueueRemoveEntry(&timer->timer_que);
}

void krnTimerThread(void *argument)
{
  (void)          argument;
  osTimerFinfo_t *timer_finfo;

  for (;;) {
    osThreadFlagsWait(FLAGS_TIMER_PROC, osFlagsWaitAny, osWaitForever);

    while ((timer_finfo = (osTimerFinfo_t *)SVC_0(TimerGetFinfo)) != NULL) {
      (timer_finfo->func)(timer_finfo->arg);
    }
  }
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osTimerId_t svcTimerNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr)
{
  osTimer_t *timer;

  /* Check parameters */
  if ((func == NULL) || (attr == NULL) || ((type != osTimerOnce) && (type != osTimerPeriodic))) {
    return NULL;
  }

  timer = attr->cb_mem;

  /* Check parameters */
  if ((timer == NULL) || (((uint32_t)timer & 3U) != 0U) || (attr->cb_size < sizeof(osTimer_t))) {
    return (NULL);
  }

  /* Initialize control block */
  timer->id         = ID_TIMER;
  timer->state      = osTimerStopped;
  timer->flags      = 0U;
  timer->type       = (uint8_t)type;
  timer->name       = attr->name;
  timer->load       = 0U;
  timer->time       = 0U;
  timer->finfo.func = func;
  timer->finfo.arg  = argument;
  QueueReset(&timer->timer_que);

  return (timer);
}

static const char *svcTimerGetName(osTimerId_t timer_id)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER)) {
    return (NULL);
  }

  return (timer->name);
}

static osStatus_t svcTimerStart(osTimerId_t timer_id, uint32_t ticks)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER) || (ticks == 0U)) {
    return (osErrorParameter);
  }

  if (timer->state == osTimerRunning) {
    krnTimerRemove(timer);
  }
  else {
    timer->state = osTimerRunning;
    timer->load  = ticks;
  }

  krnTimerInsert(timer, ticks);

  return (osOK);
}

static osStatus_t svcTimerStop(osTimerId_t timer_id)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER)) {
    return (osErrorParameter);
  }

  /* Check object state */
  if (timer->state != osTimerRunning) {
    return (osErrorResource);
  }

  timer->state = osTimerStopped;

  krnTimerRemove(timer);

  return (osOK);
}

static uint32_t svcTimerIsRunning(osTimerId_t timer_id)
{
  osTimer_t *timer = timer_id;
  uint32_t   is_running;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER)) {
    return (0U);
  }

  if (timer->state == osTimerRunning) {
    is_running = 1U;
  }
  else {
    is_running = 0U;
  }

  return (is_running);
}

static osStatus_t svcTimerDelete(osTimerId_t timer_id)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER)) {
    return (osErrorParameter);
  }

  /* Check object state */
  if (timer->state == osTimerRunning) {
    krnTimerRemove(timer);
  }

  /* Mark object as inactive and invalid */
  timer->state = osTimerInactive;
  timer->id    = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osTimerId_t osTimerNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr)
 * @brief       Create and Initialize a timer.
 * @param[in]   func      function pointer to callback function.
 * @param[in]   type      \ref osTimerOnce for one-shot or \ref osTimerPeriodic for periodic behavior.
 * @param[in]   argument  argument to the timer callback function.
 * @param[in]   attr      timer attributes; NULL: default values.
 * @return      timer ID for reference by other functions or NULL in case of error.
 */
osTimerId_t osTimerNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr)
{
  osTimerId_t timer_id;

  if (IsIrqMode() || IsIrqMasked()) {
    timer_id = NULL;
  }
  else {
    timer_id = (osTimerId_t)SVC_4(func, type, argument, attr, svcTimerNew);
  }

  return (timer_id);
}

/**
 * @fn          const char *osTimerGetName(osTimerId_t timer_id)
 * @brief       Get name of a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osTimerGetName(osTimerId_t timer_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(timer_id, svcTimerGetName);
  }

  return (name);
}

/**
 * @fn          osStatus_t osTimerStart(osTimerId_t timer_id, uint32_t ticks)
 * @brief       Start or restart a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @param[in]   ticks     \ref CMSIS_RTOS_TimeOutValue "time ticks" value of the timer.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osTimerStart(osTimerId_t timer_id, uint32_t ticks)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_2(timer_id, ticks, svcTimerStart);
  }

  return (status);
}

/**
 * @fn          osStatus_t osTimerStop(osTimerId_t timer_id)
 * @brief       Stop a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osTimerStop(osTimerId_t timer_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(timer_id, svcTimerStop);
  }

  return (status);
}

/**
 * @fn          uint32_t osTimerIsRunning(osTimerId_t timer_id)
 * @brief       Check if a timer is running.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      0 not running or an error occurred, 1 running.
 */
uint32_t osTimerIsRunning(osTimerId_t timer_id)
{
  uint32_t is_running;

  if (IsIrqMode() || IsIrqMasked()) {
    is_running = 0U;
  }
  else {
    is_running = SVC_1(timer_id, svcTimerIsRunning);
  }

  return (is_running);
}

/**
 * @fn          osStatus_t osTimerDelete(osTimerId_t timer_id)
 * @brief       Delete a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osTimerDelete(osTimerId_t timer_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(timer_id, svcTimerDelete);
  }

  return (status);
}

/*------------------------------ End of file ---------------------------------*/
