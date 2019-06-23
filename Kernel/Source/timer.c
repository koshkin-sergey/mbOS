/*
 * Copyright (C) 2011-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: uKernel real-time kernel
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

#include "os_lib.h"

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
    if (time_after(timer->time, osInfo.kernel.tick)) {
      timer_finfo = NULL;
    }
    else {
      libTimerRemove(timer);
      timer_finfo = &timer->finfo;
      if (timer->type == osTimerPeriodic) {
        libTimerInsert(timer, timer->load);
      }
      else {
        timer->state = osTimerStopped;
      }
    }
  }

  return (timer_finfo);
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osTimerId_t TimerNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr)
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

static const char *TimerGetName(osTimerId_t timer_id)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER)) {
    return (NULL);
  }

  return (timer->name);
}

static osStatus_t TimerStart(osTimerId_t timer_id, uint32_t ticks)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER) || (ticks == 0U)) {
    return (osErrorParameter);
  }

  if (timer->state == osTimerRunning) {
    libTimerRemove(timer);
  }
  else {
    if (osInfo.timer_semaphore == NULL) {
      return (osErrorResource);
    }
    else {
      timer->state = osTimerRunning;
      timer->load  = ticks;
    }
  }

  libTimerInsert(timer, ticks);

  return (osOK);
}

static osStatus_t TimerStop(osTimerId_t timer_id)
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

  libTimerRemove(timer);

  return (osOK);
}

static uint32_t TimerIsRunning(osTimerId_t timer_id)
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

static osStatus_t TimerDelete(osTimerId_t timer_id)
{
  osTimer_t *timer = timer_id;

  /* Check parameters */
  if ((timer == NULL) || (timer->id != ID_TIMER)) {
    return (osErrorParameter);
  }

  /* Check object state */
  if (timer->state == osTimerRunning) {
    libTimerRemove(timer);
  }

  /* Mark object as inactive and invalid */
  timer->state = osTimerInactive;
  timer->id    = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  Library functions
 ******************************************************************************/

void libTimerInsert(osTimer_t *timer, uint32_t time)
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

void libTimerRemove(osTimer_t *timer)
{
  QueueRemoveEntry(&timer->timer_que);
}

void libTimerThread(void *argument)
{
  (void)          argument;
  osTimerFinfo_t *timer_finfo;

  osInfo.timer_semaphore = osSemaphoreNew(1U, 0U, osConfig.timer_semaphore_attr);
  if (osInfo.timer_semaphore == NULL) {
    return;
  }

  for (;;) {
    osSemaphoreAcquire(osInfo.timer_semaphore, osWaitForever);

    while ((timer_finfo = (osTimerFinfo_t *)svc_0((uint32_t)TimerGetFinfo)) != NULL) {
      (timer_finfo->func)(timer_finfo->arg);
    }
  }
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
    timer_id = (osTimerId_t)svc_4((uint32_t)func, (uint32_t)type, (uint32_t)argument, (uint32_t)attr, (uint32_t)TimerNew);
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
    name = (const char *)svc_1((uint32_t)timer_id, (uint32_t)TimerGetName);
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
    status = (osStatus_t)svc_2((uint32_t)timer_id, ticks, (uint32_t)TimerStart);
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
    status = (osStatus_t)svc_1((uint32_t)timer_id, (uint32_t)TimerStop);
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
    is_running = svc_1((uint32_t)timer_id, (uint32_t)TimerIsRunning);
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
    status = (osStatus_t)svc_1((uint32_t)timer_id, (uint32_t)TimerDelete);
  }

  return (status);
}

/*------------------------------ End of file ---------------------------------*/
