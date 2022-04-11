/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "Kernel/tick.h"
#include "kernel_lib.h"

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

/**
 * @fn          void post_queue_put(osObject_t*)
 * @brief       Put Object into ISR Queue.
 * @param[in]   object  object.
 */
static void post_queue_put(osObject_t *object)
{
  BEGIN_CRITICAL_SECTION

  if ((object->flags & FLAGS_POST_PROC) == 0U) {
    object->flags |= FLAGS_POST_PROC;
    /* Add the object to the end of post ISR queue */
    QueueAppend(&osInfo.post_process.queue, &object->post_queue);
  }

  END_CRITICAL_SECTION
}

/**
 * @fn          osObject_t post_queue_get*(void)
 * @brief       Get Object from ISR Queue.
 * @return      object or NULL.
 */
static osObject_t* post_queue_get(void)
{
  queue_t    *que;
  osObject_t *obj;

  BEGIN_CRITICAL_SECTION

  que = &osInfo.post_process.queue;

  if (!isQueueEmpty(que)) {
    obj = GetObjectByQueue(QueueExtract(que));
    obj->flags &= ~FLAGS_POST_PROC;
  }
  else {
    obj = NULL;
  }

  END_CRITICAL_SECTION

  return (obj);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void osTick_Handler(void)
 * @brief       Tick Handler.
 */
void osTick_Handler(void)
{
  osTimer_t  *timer;
  osThread_t *thread;
  queue_t    *que;

  osTickAcknowledgeIRQ();
  ++osInfo.kernel.tick;

  /* Process Timers */
  que = &osInfo.timer_queue;
  if (!isQueueEmpty(que)) {
    timer = GetTimerByQueue(que->next);
    if (time_before_eq(timer->time, osInfo.kernel.tick)) {
      osThreadFlagsSet(osInfo.thread.timer, FLAGS_TIMER_PROC);
    }
  }

  /* Process Thread Delays */
  que = &osInfo.delay_queue;
  while (!isQueueEmpty(que)) {
    thread = GetThreadByDelayQueue(que->next);
    if (time_after(thread->delay, osInfo.kernel.tick)) {
      break;
    }
    else {
      krnThreadWaitExit(thread, (uint32_t)osErrorTimeout, DISPATCH_NO);
    }
  }

  /* Check Round Robin timeout */
  if (osConfig.robin_timeout != 0U) {
    thread = ThreadGetRunning();
    thread->time_slice++;
    if (thread->time_slice > osConfig.robin_timeout) {
      thread->time_slice = 0U;
      SchedYield(thread);
    }
  }

  SchedDispatch(NULL);
}

/**
 * @fn          void osPendSV_Handler(void)
 * @brief       Pending Service Call Handler.
 */
void osPendSV_Handler(void)
{
  osObject_t *object;

  for (;;) {
    object = post_queue_get();
    if (object == NULL) {
      break;
    }

    switch (object->id) {
      case ID_THREAD:
        krnThreadFlagsPostProcess(object);
        break;

      case ID_SEMAPHORE:
        krnSemaphorePostProcess((osSemaphore_t *)object);
        break;

      case ID_EVENT_FLAGS:
        krnEventFlagsPostProcess((osEventFlags_t *)object);
        break;

      case ID_MEMORYPOOL:
        krnMemoryPoolPostProcess((osMemoryPool_t *)object);
        break;

      case ID_MESSAGE_QUEUE:
        krnMessageQueuePostProcess((osMessageQueue_t *)object);
        break;

      case ID_DATA_QUEUE:
        krnDataQueuePostProcess((osDataQueue_t *)object);
        break;

      default:
        break;
    }
  }

  SchedDispatch(NULL);
}

/**
 * @brief       Register post ISR processing.
 * @param[in]   object  generic object.
 */
void krnPostProcess(osObject_t *object)
{
  post_queue_put(object);
  PendServCallReq();
}
