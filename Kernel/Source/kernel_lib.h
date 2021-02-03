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
 */

#ifndef _KERNEL_LIB_H_
#define _KERNEL_LIB_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "arch.h"
#include "Kernel/kernel.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* Kernel Information */
#define osVersionAPI         20010003         ///< API version (2.1.3)
#define osVersionKernel      10000000         ///< Kernel version (1.0.0)
#define osKernelId           "Kernel V1.0.0"  ///< Kernel identification string

/* Object Identifier definitions */
#define ID_INVALID                  0x00
#define ID_THREAD                   0x47
#define ID_SEMAPHORE                0x6F
#define ID_EVENT_FLAGS              0x5E
#define ID_MEMORYPOOL               0x26
#define ID_MUTEX                    0x17
#define ID_TIMER                    0x7A
#define ID_MESSAGE_QUEUE            0x1C
#define ID_MESSAGE                  0x1D
#define ID_DATA_QUEUE               0x1E

/* Thread State definitions */
#define ThreadStateInactive         ((uint8_t)osThreadInactive)
#define ThreadStateReady            ((uint8_t)osThreadReady)
#define ThreadStateRunning          ((uint8_t)osThreadRunning)
#define ThreadStateBlocked          ((uint8_t)osThreadBlocked)
#define ThreadStateTerminated       ((uint8_t)osThreadTerminated)

#define container_of(ptr, type, member) ((type *)(void *)((uint8_t *)(ptr) - offsetof(type, member)))

#define GetThreadByQueue(que)       container_of(que, osThread_t, thread_que)
#define GetThreadByDelayQueue(que)  container_of(que, osThread_t, delay_que)
#define GetMutexByQueque(que)       container_of(que, osMutex_t, mutex_que)
#define GetTimerByQueue(que)        container_of(que, osTimer_t, timer_que)
#define GetMessageByQueue(que)      container_of(que, osMessage_t, msg_que)

#define osThreadWait                (-16)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* Kernel Runtime Information structure */
typedef struct KernelInfo_s {
  struct {
    struct {
      osThread_t                         *curr;   /// Task that is running now
      osThread_t                         *next;   /// Task to be run after switch context
    } run;
    osThreadId_t                          idle;
    osThreadId_t                         timer;
  } thread;
  struct {
    osKernelState_t                      state;   ///< State
    uint32_t                              tick;
  } kernel;
  uint32_t                       base_priority;
  uint32_t                    ready_to_run_bmp;
  queue_t             ready_list[NUM_PRIORITY];   ///< all ready to run(RUNNABLE) tasks
  queue_t                          timer_queue;
  queue_t                          delay_queue;
  queue_t                           post_queue;
  osSemaphoreId_t              timer_semaphore;
} KernelInfo_t;

typedef enum {
  DISPATCH_NO  = 0,
  DISPATCH_YES = 1,
} dispatch_t;

/* Generic Object Control Block */
typedef struct osObject_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t                       state;  ///< Object State
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    reserved;
  const char                    *name;  ///< Object Name
  queue_t                  post_queue;  ///< Post Processing queue
  queue_t                  wait_queue;  ///< Waiting Threads queue
} osObject_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

extern KernelInfo_t osInfo;               ///< Kernel Runtime Information
extern const osConfig_t osConfig;         ///< Kernel Configuration

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/* Thread */

/**
 * @brief       Thread startup (Idle and Timer Thread).
 * @return      true - success, false - failure.
 */
bool libThreadStartup(void);

/**
 * @brief       Exit Thread wait state.
 * @param[out]  thread    thread object.
 * @param[in]   ret_val   return value.
 */
void libThreadWaitExit(osThread_t *thread, uint32_t ret_val, dispatch_t dispatch);

/**
 * @brief       Enter Thread wait state.
 * @param[out]  thread    thread object.
 * @param[out]  wait_que  Pointer to wait queue.
 * @param[in]   timeout   Timeout
 */
bool libThreadWaitEnter(osThread_t *thread, queue_t *wait_que, uint32_t timeout);

/**
 * @brief
 * @param wait_que
 */
void libThreadWaitDelete(queue_t *que);

/**
 * @brief       Process Thread Delay Tick (executed each System Tick).
 */
bool libThreadDelayTick(void);

/**
 * @brief       Change priority of a thread.
 * @param[in]   thread    thread object.
 * @param[in]   priority  new priority value for the thread.
 */
void libThreadSetPriority(osThread_t *thread, int8_t priority);

osThread_t *libThreadHighestPrioGet(void);

void libThreadSwitch(osThread_t *thread);

/**
 * @brief       Dispatch specified Thread or Ready Thread with Highest Priority.
 * @param[in]   thread  thread object or NULL.
 */
void libThreadDispatch(osThread_t *thread);

__STATIC_FORCEINLINE
osThread_t *ThreadGetRunning(void)
{
  return (osInfo.thread.run.curr);
}


/* Queue */

__STATIC_FORCEINLINE
void QueueReset(queue_t *que)
{
  que->prev = que->next = que;
}

__STATIC_FORCEINLINE
bool isQueueEmpty(queue_t *que)
{
  return ((que->next == que) ? true : false);
}

/**
 * @fn          void QueueAppend(queue_t *que, queue_t *entry)
 * @brief       Appends an entry at the tail of the queue.
 * @param[out]  que     Pointer to the queue
 * @param[out]  entry   Pointer to an entry
 */
__STATIC_FORCEINLINE
void QueueAppend(queue_t *que, queue_t *entry)
{
  entry->next = que;
  entry->prev = que->prev;
  entry->prev->next = entry;
  que->prev = entry;
}

/**
 * @fn          queue_t* QueueExtract(queue_t *que)
 * @brief       Removes and return an entry at the head of the queue.
 * @param[out]  que   Pointer to the queue
 * @return      Returns a pointer to an entry at the head of the queue
 */
__STATIC_FORCEINLINE
queue_t* QueueExtract(queue_t *que)
{
  queue_t *entry = que->next;

  entry->next->prev = que;
  que->next = entry->next;
  QueueReset(entry);

  return (entry);
}

/**
 * @fn          void QueueRemoveEntry(queue_t *entry)
 * @brief       Removes an entry from the queue.
 * @param[out]  entry   Pointer to an entry of the queue
 */
__STATIC_FORCEINLINE
void QueueRemoveEntry(queue_t *entry)
{
  if (!isQueueEmpty(entry)) {
    entry->prev->next = entry->next;
    entry->next->prev = entry->prev;
    QueueReset(entry);
  }
}


/* Timer */

void libTimerInsert(osTimer_t *timer, uint32_t time);
void libTimerRemove(osTimer_t *timer);
void libTimerThread(void *argument);

/**
 * @brief       Release Mutexes when owner Task terminates.
 * @param[in]   que   Queue of mutexes
 */
void libMutexOwnerRelease(queue_t *que);

/**
 * @brief       Initialize Memory Pool.
 * @param[in]   block_count   maximum number of memory blocks in memory pool.
 * @param[in]   block_size    size of a memory block in bytes.
 * @param[in]   block_mem     pointer to memory for block storage.
 * @param[in]   mp_info       memory pool info.
 */
void libMemoryPoolInit(uint32_t block_count, uint32_t block_size, void *block_mem, osMemoryPoolInfo_t *mp_info);

/**
 * @brief       Reset Memory Pool.
 * @param[in]   mp_info       memory pool info.
 */
void libMemoryPoolReset(osMemoryPoolInfo_t *mp_info);

/**
 * @brief       Allocate a memory block from a Memory Pool.
 * @param[in]   mp_info   memory pool info.
 * @return      address of the allocated memory block or NULL in case of no memory is available.
 */
void *libMemoryPoolAlloc(osMemoryPoolInfo_t *mp_info);

/**
 * @brief       Return an allocated memory block back to a Memory Pool.
 * @param[in]   mp_info   memory pool info.
 * @param[in]   block     address of the allocated memory block to be returned to the memory pool.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t libMemoryPoolFree(osMemoryPoolInfo_t *mp_info, void *block);

/*******************************************************************************
 *  System Library functions
 ******************************************************************************/

extern void osTick_Handler(void);
extern void osPendSV_Handler(void);
extern void osPostProcess(osObject_t *object);

#endif /* _KERNEL_LIB_H_ */
