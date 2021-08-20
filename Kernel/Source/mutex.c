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

#define osMutexLockLimit              (255U)

/*******************************************************************************
 *  Library functions
 ******************************************************************************/

/**
 * @brief       Release Mutexes when owner Task terminates.
 * @param[in]   que   Queue of mutexes
 */
void krnMutexOwnerRelease(queue_t *que)
{
  osMutex_t  *mutex;
  osThread_t *thread;

  while (!isQueueEmpty(que)) {
    mutex = GetMutexByQueque(QueueExtract(que));
    if ((mutex->attr & osMutexRobust) != 0U) {
      mutex->holder = NULL;
      mutex->cnt = 0U;
      /* Check if Thread is waiting for a Mutex */
      if (!isQueueEmpty(&mutex->wait_que)) {
        /* Wakeup waiting Thread with highest Priority */
        thread = GetThreadByQueue(mutex->wait_que.next);
        krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
        mutex->holder = thread;
        mutex->cnt = 1U;
        QueueAppend(&thread->mutex_que, &mutex->mutex_que);
      }
    }
  }
}

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

static void RestoreThreadPriority(osThread_t *thread)
{
  osMutex_t  *mutex;
  queue_t    *que;
  int8_t      priority;
  osThread_t *wthread;

  priority = thread->base_priority;

  if (!isQueueEmpty(&thread->mutex_que)) {
    que = thread->mutex_que.next;
    while (que != &thread->mutex_que) {
      mutex = GetMutexByQueque(que);
      if (!isQueueEmpty(&mutex->wait_que)) {
        wthread = GetThreadByQueue(mutex->wait_que.next);
        if (wthread->priority > priority) {
          priority = wthread->priority;
        }
      }
      que = que->next;
    }
  }

  krnThreadSetPriority(thread, priority);
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osMutexId_t svcMutexNew(const osMutexAttr_t *attr)
{
  osMutex_t *mutex;

  /* Check parameters */
  if (attr == NULL) {
    return (NULL);
  }

  mutex = attr->cb_mem;

  /* Check parameters */
  if ((mutex == NULL) || (((uint32_t)mutex & 3U) != 0U) || (attr->cb_size < sizeof(osMutex_t))) {
    return (NULL);
  }

  /* Initialize control block */
  mutex->id     = ID_MUTEX;
  mutex->flags  = 0U;
  mutex->attr   = (uint8_t)attr->attr_bits;
  mutex->name   = attr->name;
  mutex->holder = NULL;
  mutex->cnt    = 0U;
  QueueReset(&mutex->wait_que);
  QueueReset(&mutex->mutex_que);
  QueueReset(&mutex->post_queue);

  return (mutex);
}

static const char *svcMutexGetName(osMutexId_t mutex_id)
{
  osMutex_t *mutex = mutex_id;

  /* Check parameters */
  if ((mutex == NULL) || (mutex->id != ID_MUTEX)) {
    return (NULL);
  }

  return (mutex->name);
}

static osStatus_t svcMutexAcquire(osMutexId_t mutex_id, uint32_t timeout)
{
  osMutex_t  *mutex = mutex_id;
  osThread_t *running_thread;
  osStatus_t  status;

  /* Check parameters */
  if ((mutex == NULL) || (mutex->id != ID_MUTEX)) {
    return (osErrorParameter);
  }

  running_thread = ThreadGetRunning();
  if (running_thread == NULL) {
    return (osError);
  }

  /* Check if Mutex is not locked */
  if (mutex->cnt == 0U) {
    /* Acquire Mutex */
    mutex->holder = running_thread;
    mutex->cnt = 1U;
    QueueAppend(&running_thread->mutex_que, &mutex->mutex_que);
    status = osOK;
  }
  else {
    /* Check if Mutex is recursive and running Thread is the owner */
    if (((mutex->attr & osMutexRecursive) != 0U) && (mutex->holder == running_thread)) {
      /* Try to increment lock counter */
      if (mutex->cnt == osMutexLockLimit) {
        status = osErrorResource;
      }
      else {
        mutex->cnt++;
        status = osOK;
      }
    }
    else {
      /* Check if timeout is specified */
      if (timeout != 0U) {
        /* Check if Priority inheritance protocol is enabled */
        if ((mutex->attr & osMutexPrioInherit) != 0U) {
          /* Raise priority of owner Task if lower than priority of running Task */
          if (mutex->holder->priority < running_thread->priority) {
            krnThreadSetPriority(mutex->holder, running_thread->priority);
          }
        }
        /* Suspend current Thread */
        status = krnThreadWaitEnter(running_thread, &mutex->wait_que, timeout);
      }
      else {
        status = osErrorResource;
      }
    }
  }

  return (status);
}

static osStatus_t svcMutexRelease(osMutexId_t mutex_id)
{
  osMutex_t  *mutex = mutex_id;
  osThread_t *thread;
  osThread_t *running_thread;

  /* Check parameters */
  if ((mutex == NULL) || (mutex->id != ID_MUTEX)) {
    return (osErrorParameter);
  }

  running_thread = ThreadGetRunning();
  if (running_thread == NULL) {
    return (osError);
  }

  /* Check if Mutex is not locked */
  if (mutex->cnt == 0U) {
    return (osErrorResource);
  }

  /* Check if running Thread is not the owner */
  if (mutex->holder != running_thread) {
    return (osErrorResource);
  }

  /* Decrement Lock counter */
  mutex->cnt--;

  /* Check Lock counter */
  if (mutex->cnt == 0) {
    /* Remove Mutex from Thread owner list */
    QueueRemoveEntry(&mutex->mutex_que);

    /* Restore owner Thread priority */
    if ((mutex->attr & osMutexPrioInherit) != 0U) {
      RestoreThreadPriority(running_thread);
    }

    /* Check if Thread is waiting for a Mutex */
    if (!isQueueEmpty(&mutex->wait_que)) {
      /* Wakeup waiting Thread with highest Priority */
      thread = GetThreadByQueue(mutex->wait_que.next);
      krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
      mutex->holder = thread;
      mutex->cnt = 1U;
      QueueAppend(&thread->mutex_que, &mutex->mutex_que);
    }

    krnThreadDispatch(NULL);
  }

  return (osOK);
}

static osThreadId_t svcMutexGetOwner(osMutexId_t mutex_id)
{
  osMutex_t *mutex = mutex_id;

  /* Check parameters */
  if ((mutex == NULL) || (mutex->id != ID_MUTEX)) {
    return (NULL);
  }

  if (mutex->cnt == 0U) {
    return (NULL);
  }

  return (mutex->holder);
}

static osStatus_t svcMutexDelete(osMutexId_t mutex_id)
{
  osMutex_t *mutex = mutex_id;

  /* Check parameters */
  if ((mutex == NULL) || (mutex->id != ID_MUTEX)) {
    return (osErrorParameter);
  }

  /* Check if Mutex is locked */
  if (mutex->cnt != 0U) {
    /* Remove Mutex from Thread owner list */
    QueueRemoveEntry(&mutex->mutex_que);

    /* Restore owner Thread priority */
    if ((mutex->attr & osMutexPrioInherit) != 0U) {
      RestoreThreadPriority(mutex->holder);
    }

    /* Unblock waiting threads */
    krnThreadWaitDelete(&mutex->wait_que);

    krnThreadDispatch(NULL);
  }

  /* Mutex not exists now */
  mutex->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osMutexId_t osMutexNew(const osMutexAttr_t *attr)
 * @brief       Create and Initialize a Mutex object.
 * @param[in]   attr  mutex attributes.
 * @return      mutex ID for reference by other functions or NULL in case of error.
 */
osMutexId_t osMutexNew(const osMutexAttr_t *attr)
{
  osMutexId_t mutex_id;

  if (IsIrqMode() || IsIrqMasked()) {
    mutex_id = NULL;
  }
  else {
    mutex_id = (osMutexId_t)SVC_1(attr, svcMutexNew);
  }

  return (mutex_id);
}

/**
 * @fn          const char *osMutexGetName(osMutexId_t mutex_id)
 * @brief       Get name of a Mutex object.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osMutexGetName(osMutexId_t mutex_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(mutex_id, svcMutexGetName);
  }

  return (name);
}

/**
 * @fn          osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t timeout)
 * @brief       Acquire a Mutex or timeout if it is locked.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t timeout)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_2(mutex_id, timeout, svcMutexAcquire);
    if (status == osThreadWait) {
      status = (osStatus_t)ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (status);
}

/**
 * @fn          osStatus_t osMutexRelease(osMutexId_t mutex_id)
 * @brief       Release a Mutex that was acquired by \ref osMutexAcquire.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMutexRelease(osMutexId_t mutex_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(mutex_id, svcMutexRelease);
  }

  return (status);
}

/**
 * @fn          osThreadId_t osMutexGetOwner(osMutexId_t mutex_id)
 * @brief       Get Thread which owns a Mutex object.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      thread ID of owner thread or NULL when mutex was not acquired.
 */
osThreadId_t osMutexGetOwner(osMutexId_t mutex_id)
{
  osThreadId_t thread;

  if (IsIrqMode() || IsIrqMasked()) {
    thread = NULL;
  }
  else {
    thread = (osThreadId_t)SVC_1(mutex_id, svcMutexGetOwner);
  }

  return (thread);
}

/**
 * @fn          osStatus_t osMutexDelete(osMutexId_t mutex_id)
 * @brief       Delete a Mutex object.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMutexDelete(osMutexId_t mutex_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(mutex_id, svcMutexDelete);
  }

  return (status);
}

/*------------------------------ End of file ---------------------------------*/
