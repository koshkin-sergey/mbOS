/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
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
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "kernel_lib.h"

/*******************************************************************************
 *  Scheduler functions
 ******************************************************************************/

static osThread_t* ThreadHighestPrioGet(void)
{
  int8_t priority;
  osThread_t *thread;

  if (osInfo.ready_to_run_bmp == 0U) {
    return (NULL);
  }

  priority = (int8_t)((NUM_PRIORITY - 1U) - __CLZ(osInfo.ready_to_run_bmp));
  thread = GetThreadByQueue(osInfo.ready_list[priority].next);

  return (thread);
}

__STATIC_FORCEINLINE
void ThreadSwitch(osThread_t *thread)
{
  thread->state = ThreadRunning;
  osInfo.thread.run.next = thread;
}

/**
 * @brief       Dispatch specified Thread or Ready Thread with Highest Priority.
 * @param[in]   thread  thread object or NULL.
 */
void SchedDispatch(osThread_t *thread)
{
  osThread_t *thread_next;

  if (osInfo.kernel.state == osKernelRunning) {
    if (thread == NULL) {
      thread = ThreadHighestPrioGet();
      if (thread == NULL) {
        return;
      }
    }

    thread_next = osInfo.thread.run.next;
    if (thread_next == NULL || thread_next->state != ThreadRunning) {
      ThreadSwitch(thread);
      return;
    }

    if (thread->priority > thread_next->priority) {
      /* Preempt running Thread */
      thread_next->state = ThreadReady;
      ThreadSwitch(thread);
    }
  }
}

/**
 * @brief       The function passes control to the next thread with the same
 *              priority that is in the READY state.
 * @param[in]   thread  Thread object
 */
void SchedYield(osThread_t *thread)
{
  queue_t *que;
  int8_t  priority;

  priority = thread->priority - 1;
  que = &osInfo.ready_list[priority];

  if (!isQueueEmpty(que) && que->next->next != que) {
    /* Remove the thread from ready queue */
    QueueRemoveEntry(&thread->thread_que);
    thread->state = ThreadReady;
    /* Add the thread to the end of ready queue */
    QueueAppend(que, &thread->thread_que);
  }
}

/**
 * @brief       Adds thread to the end of ready queue for current priority
 * @param[in]   thread  Thread object
 */
void SchedThreadReadyAdd(osThread_t *thread)
{
  int8_t priority = thread->priority - 1;

  /* Remove the thread from any queue */
  QueueRemoveEntry(&thread->thread_que);

  thread->state = ThreadReady;
  /* Add the thread to the end of ready queue */
  QueueAppend(&osInfo.ready_list[priority], &thread->thread_que);
  osInfo.ready_to_run_bmp |= (1UL << priority);
}

/**
 * @brief       Deletes thread from the ready queue for current priority
 * @param[in]   thread        Thread object
 * @param[in]   thread_state  New thread state
 */
void SchedThreadReadyDel(osThread_t *thread, uint8_t thread_state)
{
  int8_t priority = thread->priority - 1;

  /* Remove the thread from ready queue */
  QueueRemoveEntry(&thread->thread_que);

  thread->state = thread_state;
  if (isQueueEmpty(&osInfo.ready_list[priority])) {
    /* No ready threads for the current priority */
    osInfo.ready_to_run_bmp &= ~(1UL << priority);
  }
}
