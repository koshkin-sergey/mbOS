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

#define osThreadFlagsLimit    31U    ///< number of Thread Flags available per object
#define osThreadFlagsMask     ((1UL << osThreadFlagsLimit) - 1UL)

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

static uint32_t ThreadFlagsSet(osThread_t *thread, uint32_t flags)
{
  uint32_t thread_flags;

  BEGIN_CRITICAL_SECTION

  thread->thread_flags |= flags;
  thread_flags = thread->thread_flags;

  END_CRITICAL_SECTION

  return (thread_flags);
}

static uint32_t ThreadFlagsCheck(osThread_t *thread, uint32_t flags, uint32_t options)
{
  uint32_t pattern;

  if ((options & osFlagsNoClear) == 0U) {
    BEGIN_CRITICAL_SECTION

    pattern = thread->thread_flags;
    if ((((options & osFlagsWaitAll) != 0U) && ((pattern & flags) != flags)) ||
        (((options & osFlagsWaitAll) == 0U) && ((pattern & flags) == 0U)))
    {
      pattern = 0U;
    }
    else {
      thread->thread_flags &= ~flags;
    }

    END_CRITICAL_SECTION
  }
  else {
    pattern = thread->thread_flags;

    if ((((options & osFlagsWaitAll) != 0U) && ((pattern & flags) != flags)) ||
        (((options & osFlagsWaitAll) == 0U) && ((pattern & flags) == 0U)))
    {
      pattern = 0U;
    }
  }

  return (pattern);
}

/**
 * @brief       Adds thread to the end of ready queue for current priority
 * @param[in]   thread
 */
static void ThreadReadyAdd(osThread_t *thread)
{
  int8_t priority = thread->priority - 1;

  /* Remove the thread from any queue */
  QueueRemoveEntry(&thread->thread_que);

  thread->state = ThreadStateReady;
  /* Add the thread to the end of ready queue */
  QueueAppend(&osInfo.ready_list[priority], &thread->thread_que);
  osInfo.ready_to_run_bmp |= (1UL << priority);
}

/**
 * @brief       Deletes thread from the ready queue for current priority
 * @param[in]   thread
 */
static void ThreadReadyDel(osThread_t *thread)
{
  int8_t priority = thread->priority - 1;

  /* Remove the thread from ready queue */
  QueueRemoveEntry(&thread->thread_que);

  if (isQueueEmpty(&osInfo.ready_list[priority])) {
    /* No ready threads for the current priority */
    osInfo.ready_to_run_bmp &= ~(1UL << priority);
  }
}

/**
 * @brief       OS Idle Thread.
 * @param[in]   argument
 */
__WEAK __NO_RETURN
void osIdleThread(void *argument)
{
  (void) argument;

  for (;;) {

  }
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osThreadId_t svcThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
{
  osThread_t   *thread;
  void         *stack_mem;
  uint32_t      stack_size;
  osPriority_t  priority;

  if ((func == NULL) || (attr == NULL)) {
    return (NULL);
  }

  thread = attr->cb_mem;
  stack_mem = attr->stack_mem;
  stack_size = attr->stack_size;
  priority = attr->priority;

  if ((thread == NULL) || (attr->cb_size < sizeof(osThread_t))) {
    return (NULL);
  }

  if ((stack_mem == NULL) || (((uint32_t)stack_mem & 7U) != 0U) ||
      (stack_size < MIN_THREAD_STK_SIZE)  || ((stack_size & 7U) != 0U)            ) {
    return (NULL);
  }

  if (priority == osPriorityNone) {
    priority = osPriorityNormal;
  }
  else if ((priority < osPriorityIdle) || priority > osPriorityISR) {
    return (NULL);
  }

  /* Init thread control block */
  thread->exc_return    = INIT_EXC_RETURN;
  thread->stk_mem       = stack_mem;
  thread->stk_size      = stack_size;
  thread->base_priority = (int8_t)priority;
  thread->priority      = (int8_t)priority;
  thread->id            = ID_THREAD;
  thread->flags         = 0U;
  thread->attr          = attr->attr_bits;
  thread->delay         = 0U;
  thread->thread_flags  = 0U;
  thread->name          = attr->name;

  QueueReset(&thread->thread_que);
  QueueReset(&thread->delay_que);
  QueueReset(&thread->mutex_que);
  QueueReset(&thread->post_queue);

  /* Fill all thread stack space by FILL_STACK_VAL */
  uint32_t *ptr = stack_mem;
  for (uint32_t i = stack_size/sizeof(uint32_t); i != 0U; --i) {
    *ptr++ = FILL_STACK_VALUE;
  }

  /* Init thread stack */
  StackAttr_t stack_attr = {
      .func_addr  = (uint32_t)func,
      .func_param = (uint32_t)argument,
      .func_exit  = (uint32_t)osThreadExit,
      .stk_mem    = (uint32_t)stack_mem,
      .stk_size   = stack_size,
  };
  thread->stk = StackInit(
      &stack_attr,
      (osConfig.flags & osConfigPrivilegedMode) != 0U
  );

  ThreadReadyAdd(thread);
  krnThreadDispatch(thread);

  return (thread);
}

static
const char *svcThreadGetName(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (NULL);
  }

  return (thread->name);
}

static
osThreadId_t svcThreadGetId(void)
{
  osThread_t *thread;

  thread = ThreadGetRunning();

  return (thread);
}

static
osThreadState_t svcThreadGetState(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (osThreadError);
  }

  return ((osThreadState_t)thread->state);
}

static
uint32_t svcThreadGetStackSize(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (0U);
  }

  return (thread->stk_size);
}

static
uint32_t svcThreadGetStackSpace(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;
  const uint32_t *stack;
  uint32_t space = 0U;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (0U);
  }

  stack = thread->stk_mem;
  for (; space < thread->stk_size; space += sizeof(uint32_t)) {
    if (*stack++ != FILL_STACK_VALUE) {
      break;
    }
  }

  return (space);
}

static osStatus_t svcThreadSetPriority(osThreadId_t thread_id, osPriority_t priority)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD) ||
      (priority < osPriorityIdle) || (priority > osPriorityISR)) {
    return (osErrorParameter);
  }

  /* Check object state */
  if (thread->state == ThreadStateTerminated) {
    return (osErrorResource);
  }

  if (thread->base_priority != (int8_t)priority) {
    thread->base_priority = (int8_t)priority;
    krnThreadSetPriority(thread, (int8_t)priority);
  }

  return (osOK);
}

static osPriority_t svcThreadGetPriority(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;
  osPriority_t priority;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (osPriorityError);
  }

  /* Check object state */
  if (thread->state == ThreadStateTerminated) {
    return (osPriorityError);
  }

  priority = (osPriority_t)thread->priority;

  return (priority);
}

static osStatus_t svcThreadYield(void)
{
  queue_t    *que;
  osThread_t *thread_running;

  if (osInfo.kernel.state == osKernelRunning) {
    thread_running = ThreadGetRunning();
    que = &osInfo.ready_list[thread_running->priority - 1];

    /* Remove the running thread from ready queue */
    QueueRemoveEntry(&thread_running->thread_que);

    if (!isQueueEmpty(que)) {
      thread_running->state = ThreadStateReady;
      krnThreadSwitch(GetThreadByQueue(que->next));
    }

    /* Add the running thread to the end of ready queue */
    QueueAppend(que, &thread_running->thread_que);
  }

  return (osOK);
}

static
osStatus_t svcThreadSuspend(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;
  osStatus_t status = osOK;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (osErrorParameter);
  }

  switch (thread->state) {
    case ThreadStateRunning:
      if (osInfo.kernel.state != osKernelRunning ||
          osInfo.ready_to_run_bmp == 0U) {
        status = osErrorResource;
      }
      else {
        ThreadReadyDel(thread);
        thread->state = ThreadStateBlocked;
        thread = krnThreadHighestPrioGet();
        krnThreadSwitch(thread);
      }
      break;

    case ThreadStateReady:
      ThreadReadyDel(thread);
      thread->state = ThreadStateBlocked;
      break;

    case ThreadStateBlocked:
      /* Remove the thread from delay queue */
      QueueRemoveEntry(&thread->delay_que);
      /* Remove the thread from wait queue */
      QueueRemoveEntry(&thread->thread_que);
      break;

    case ThreadStateTerminated:
    case ThreadStateInactive:
    default:
      status = osErrorResource;
      break;
  }

  return (status);
}

static osStatus_t svcThreadResume(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (osErrorParameter);
  }

  /* Check object state */
  if (thread->state != ThreadStateBlocked) {
    return (osErrorResource);
  }

  /* Wakeup Thread */
  krnThreadWaitExit(thread, (uint32_t)osErrorTimeout, DISPATCH_YES);

  return (osOK);
}

static void svcThreadExit(void)
{
  osThread_t *thread;

  if (osInfo.kernel.state != osKernelRunning ||
      osInfo.ready_to_run_bmp == 0U) {
    return;
  }

  thread = ThreadGetRunning();

  /* Release owned Mutexes */
  krnMutexOwnerRelease(&thread->mutex_que);

  ThreadReadyDel(thread);
  krnThreadSwitch(krnThreadHighestPrioGet());
  thread->state = ThreadStateInactive;
  thread->id = ID_INVALID;
}

static osStatus_t svcThreadTerminate(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;
  osStatus_t status = osOK;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (osErrorParameter);
  }

  /* Check object state */
  switch (thread->state) {
    case ThreadStateRunning:
      if (osInfo.kernel.state != osKernelRunning ||
          osInfo.ready_to_run_bmp == 0U) {
        status = osErrorResource;
      }
      else {
        ThreadReadyDel(thread);
      }
      break;

    case ThreadStateReady:
      ThreadReadyDel(thread);
      break;

    case ThreadStateBlocked:
      /* Remove the thread from delay queue */
      QueueRemoveEntry(&thread->delay_que);
      /* Remove the thread from wait queue */
      QueueRemoveEntry(&thread->thread_que);
      break;

    case ThreadStateInactive:
    case ThreadStateTerminated:
    default:
      status = osErrorResource;
      break;
  }

  if (status == osOK) {
    /* Release owned Mutexes */
    krnMutexOwnerRelease(&thread->mutex_que);

    if (thread->state == ThreadStateRunning) {
      krnThreadSwitch(krnThreadHighestPrioGet());
    }
    else {
      krnThreadDispatch(NULL);
    }

    thread->state = ThreadStateInactive;
    thread->id = ID_INVALID;
  }

  return (status);
}

static uint32_t svcThreadGetCount(void)
{
  return (0U);
}

static uint32_t svcThreadEnumerate(osThreadId_t *thread_array, uint32_t array_items)
{
  (void)thread_array;
  (void)array_items;

  return (0U);
}

static uint32_t svcThreadFlagsSet(osThreadId_t thread_id, uint32_t flags)
{
  osThread_t *thread = thread_id;
  uint32_t    thread_flags;
  uint32_t    pattern;

  /* Check parameters */
  if (thread->id != ID_THREAD) {
    return (osFlagsErrorParameter);
  }

  /* Set Thread Flags */
  thread_flags = ThreadFlagsSet(thread, flags);

  /* Check Thread Flags */
  pattern = ThreadFlagsCheck(thread, thread->winfo.thread.flags, thread->winfo.thread.options);
  if (pattern != 0U) {
    if ((thread->winfo.thread.options & osFlagsNoClear) == 0U) {
      thread_flags = pattern & ~thread->winfo.thread.flags;
    }
    else {
      thread_flags = pattern;
    }
    krnThreadWaitExit(thread, pattern, DISPATCH_YES);
  }

  return (thread_flags);
}

static uint32_t svcThreadFlagsClear(uint32_t flags)
{
  uint32_t    thread_flags;
  osThread_t *thread;

  thread = ThreadGetRunning();

  BEGIN_CRITICAL_SECTION

  thread_flags = thread->thread_flags;
  thread->thread_flags &= ~flags;

  END_CRITICAL_SECTION

  return (thread_flags);
}

static uint32_t svcThreadFlagsGet(void)
{
  return (ThreadGetRunning()->thread_flags);
}

static uint32_t svcThreadFlagsWait(uint32_t flags, uint32_t options, uint32_t timeout)
{
  uint32_t       thread_flags;
  osThread_t    *thread;
  winfo_flags_t *winfo;

  thread = ThreadGetRunning();

  /* Check Thread Flags */
  thread_flags = ThreadFlagsCheck(thread, flags, options);
  if (thread_flags == 0U) {
    if (timeout != 0U) {
      thread_flags = (uint32_t)krnThreadWaitEnter(thread, NULL, timeout);
      if (thread_flags != (uint32_t)osErrorTimeout) {
        winfo = &thread->winfo.thread;
        winfo->options = options;
        winfo->flags = flags;
      }
    }
    else {
      thread_flags = osFlagsErrorResource;
    }
  }

  return (thread_flags);
}

/*******************************************************************************
 *  ISR Calls
 ******************************************************************************/

__STATIC_INLINE
uint32_t isrThreadFlagsSet(osThreadId_t thread_id, uint32_t flags)
{
  osThread_t *thread = thread_id;
  uint32_t    thread_flags;

  /* Check parameters */
  if (thread->id != ID_THREAD) {
    return (osFlagsErrorParameter);
  }

  /* Set Thread Flags */
  thread_flags = ThreadFlagsSet(thread, flags);

  /* Register post ISR processing */
  krnPostProcess((osObject_t *)&thread->id);

  return (thread_flags);
}

/*******************************************************************************
 *  Post ISR processing
 ******************************************************************************/

/**
 * @fn          void krnThreadFlagsPostProcess(osObject_t *obj)
 * @brief       Thread Flags post ISR processing.
 * @param[in]   obj  object.
 */
void krnThreadFlagsPostProcess(osObject_t *obj)
{
  osThread_t *thread;
  uint32_t    pattern;

  /* Get Thread */
  thread = GetThreadByObject(obj);

  /* Check Thread Flags */
  pattern = ThreadFlagsCheck(thread, thread->winfo.thread.flags, thread->winfo.thread.options);
  if (pattern != 0U) {
    krnThreadWaitExit(thread, pattern, DISPATCH_NO);
  }
}


/*******************************************************************************
 *  Library functions
 ******************************************************************************/

/**
 * @brief       Thread startup (Idle and Timer Thread).
 * @return      true - success, false - failure.
 */
bool krnThreadStartup(void)
{
  bool ret = true;

  /* Create Idle Thread */
  if (osInfo.thread.idle == NULL) {
    osInfo.thread.idle = svcThreadNew(osIdleThread, NULL, osConfig.idle_thread_attr);
    if (osInfo.thread.idle == NULL) {
      ret = false;
    }
  }

  /* Create Timer Thread */
  if (osInfo.thread.timer == NULL) {
    osInfo.thread.timer = svcThreadNew(krnTimerThread, NULL, osConfig.timer_thread_attr);
    if (osInfo.thread.timer == NULL) {
      ret = false;
    }
  }

  return (ret);
}

/**
 * @brief       Exit Thread wait state.
 * @param[out]  thread    thread object.
 * @param[in]   ret_val   return value.
 */
void krnThreadWaitExit(osThread_t *thread, uint32_t ret_val, dispatch_t dispatch)
{
  thread->winfo.ret_val = ret_val;

  /* Remove the thread from delay queue */
  QueueRemoveEntry(&thread->delay_que);
  ThreadReadyAdd(thread);
  if (dispatch != DISPATCH_NO) {
    krnThreadDispatch(thread);
  }
}

/**
 * @brief       Enter Thread wait state.
 * @param[out]  thread    thread object.
 * @param[out]  wait_que  Pointer to wait queue.
 * @param[in]   timeout   Timeout
 */
osStatus_t krnThreadWaitEnter(osThread_t *thread, queue_t *wait_que, uint32_t timeout)
{
  queue_t *que;
  queue_t *delay_queue;

  if (osInfo.kernel.state != osKernelRunning) {
    return (osErrorTimeout);
  }

  ThreadReadyDel(thread);

  thread->state = ThreadStateBlocked;

  /* Add to the wait queue */
  if (wait_que != NULL) {
    for (que = wait_que->next; que != wait_que; que = que->next) {
      if (thread->priority > GetThreadByQueue(que)->priority) {
        break;
      }
    }
    QueueAppend(que, &thread->thread_que);
  }

  /* Add to the delay queue */
  if (timeout != osWaitForever) {
    thread->delay = osInfo.kernel.tick + timeout;
    delay_queue = &osInfo.delay_queue;
    for (que = delay_queue->next; que != delay_queue; que = que->next) {
      if (time_before(thread->delay, GetThreadByDelayQueue(que)->delay)) {
        break;
      }
    }

    QueueAppend(que, &thread->delay_que);
  }

  thread = krnThreadHighestPrioGet();
  krnThreadSwitch(thread);

  return ((osStatus_t)osThreadWait);
}

/**
 * @brief
 * @param wait_que
 */
void krnThreadWaitDelete(queue_t *wait_que)
{
  while (!isQueueEmpty(wait_que)) {
    krnThreadWaitExit(GetThreadByQueue(wait_que->next), (uint32_t)osErrorResource, DISPATCH_NO);
  }
  krnThreadDispatch(NULL);
}

/**
 * @brief       Process Thread Delay Tick (executed each System Tick).
 */
bool krnThreadDelayTick(void)
{
  osThread_t *thread;
  bool        result = false;
  queue_t    *delay_queue = &osInfo.delay_queue;

  while (!isQueueEmpty(delay_queue)) {
    thread = GetThreadByDelayQueue(delay_queue->next);
    if (time_after(thread->delay, osInfo.kernel.tick)) {
      break;
    }
    else {
      krnThreadWaitExit(thread, (uint32_t)osErrorTimeout, DISPATCH_NO);
      result = true;
    }
  }

  return (result);
}

/**
 * @brief       Change priority of a thread.
 * @param[in]   thread    thread object.
 * @param[in]   priority  new priority value for the thread.
 */
void krnThreadSetPriority(osThread_t *thread, int8_t priority)
{
  if (thread->priority != priority) {
    if (thread->state == ThreadStateBlocked) {
      thread->priority = priority;
    }
    else {
      ThreadReadyDel(thread);
      thread->priority = priority;
      ThreadReadyAdd(thread);
    }
  }
}

osThread_t *krnThreadHighestPrioGet(void)
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

void krnThreadSwitch(osThread_t *thread)
{
  thread->state = ThreadStateRunning;
  osInfo.thread.run.next = thread;
}

/**
 * @brief       Dispatch specified Thread or Ready Thread with Highest Priority.
 * @param[in]   thread  thread object or NULL.
 */
void krnThreadDispatch(osThread_t *thread)
{
  osThread_t *thread_running;

  if (thread == NULL) {
    thread = krnThreadHighestPrioGet();
  }

  thread_running = ThreadGetRunning();

  if ((osInfo.kernel.state == osKernelRunning) &&
      (thread != NULL) &&
      (thread_running != NULL) &&
      (thread->priority > thread_running->priority)) {
    /* Preempt running Thread */
    thread_running->state = ThreadStateReady;
    krnThreadSwitch(thread);
  }
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
 * @brief       Create a thread and add it to Active Threads.
 * @param[in]   func      thread function.
 * @param[in]   argument  pointer that is passed to the thread function as start argument.
 * @param[in]   attr      thread attributes.
 * @return      thread ID for reference by other functions or NULL in case of error.
 */
osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
{
  osThreadId_t thread_id;

  if (IsIrqMode() || IsIrqMasked()) {
    thread_id = NULL;
  }
  else {
    thread_id = (osThreadId_t)SVC_3(func, argument, attr, svcThreadNew);
  }

  return (thread_id);
}

/**
 * @fn          const char *osThreadGetName(osThreadId_t thread_id)
 * @brief       Get name of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      name as null-terminated string.
 */
const char *osThreadGetName(osThreadId_t thread_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(thread_id, svcThreadGetName);
  }

  return (name);
}

/**
 * @fn          osThreadId_t osThreadGetId(void)
 * @brief       Return the thread ID of the current running thread.
 * @return      thread ID for reference by other functions or NULL in case of error.
 */
osThreadId_t osThreadGetId(void)
{
  osThreadId_t thread_id;

  if (IsIrqMode() || IsIrqMasked()) {
    thread_id = svcThreadGetId();
  }
  else {
    thread_id = (osThreadId_t)SVC_0(svcThreadGetId);
  }

  return (thread_id);
}

/**
 * @fn          osThreadState_t osThreadGetState(osThreadId_t thread_id)
 * @brief       Get current thread state of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      current thread state of the specified thread.
 */
osThreadState_t osThreadGetState(osThreadId_t thread_id)
{
  osThreadState_t state;

  if (IsIrqMode() || IsIrqMasked()) {
    state = osThreadError;
  }
  else {
    state = (osThreadState_t)SVC_1(thread_id, svcThreadGetState);
  }

  return (state);
}

/**
 * @fn          uint32_t osThreadGetStackSize(osThreadId_t thread_id)
 * @brief       Get stack size of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      stack size in bytes.
 */
uint32_t osThreadGetStackSize(osThreadId_t thread_id)
{
  uint32_t stack_size;

  if (IsIrqMode() || IsIrqMasked()) {
    stack_size = 0U;
  }
  else {
    stack_size = SVC_1(thread_id, svcThreadGetStackSize);
  }

  return (stack_size);
}

/**
 * @fn          uint32_t osThreadGetStackSpace(osThreadId_t thread_id)
 * @brief       Get available stack space of a thread based on stack watermark recording during execution.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      remaining stack space in bytes.
 */
uint32_t osThreadGetStackSpace(osThreadId_t thread_id)
{
  uint32_t stack_space;

  if (IsIrqMode() || IsIrqMasked()) {
    stack_space = 0U;
  }
  else {
    stack_space = SVC_1(thread_id, svcThreadGetStackSpace);
  }

  return (stack_space);
}

/**
 * @fn          osStatus_t osThreadSetPriority(osThreadId_t thread_id, osPriority_t priority)
 * @brief       Change priority of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @param[in]   priority    new priority value for the thread function.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadSetPriority(osThreadId_t thread_id, osPriority_t priority)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_2(thread_id, priority, svcThreadSetPriority);
  }

  return (status);
}

/**
 * @fn          osPriority_t osThreadGetPriority(osThreadId_t thread_id)
 * @brief       Get current priority of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      current priority value of the specified thread.
 */
osPriority_t osThreadGetPriority(osThreadId_t thread_id)
{
  osPriority_t priority;

  if (IsIrqMode() || IsIrqMasked()) {
    priority = osPriorityError;
  }
  else {
    priority = (osPriority_t)SVC_1(thread_id, svcThreadGetPriority);
  }

  return (priority);
}

/**
 * @fn          osStatus_t osThreadYield(void)
 * @brief       Pass control to next thread that is in state READY.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadYield(void)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_0(svcThreadYield);
  }

  return (status);
}

/**
 * @fn          osStatus_t osThreadSuspend(osThreadId_t thread_id)
 * @brief       Suspend execution of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadSuspend(osThreadId_t thread_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(thread_id, svcThreadSuspend);
  }

  return (status);
}

/**
 * @fn          osStatus_t osThreadResume(osThreadId_t thread_id)
 * @brief       Resume execution of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadResume(osThreadId_t thread_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(thread_id, svcThreadResume);
  }

  return (status);
}

/**
 * @fn          void osThreadExit(void)
 * @brief       Terminate execution of current running thread.
 */
__NO_RETURN
void osThreadExit(void)
{
  SVC_0(svcThreadExit);
  for (;;);
}

/**
 * @fn          osStatus_t osThreadTerminate(osThreadId_t thread_id)
 * @brief       Terminate execution of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadTerminate(osThreadId_t thread_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(thread_id, svcThreadTerminate);
  }

  return (status);
}

/**
 * @fn          uint32_t osThreadGetCount(void)
 * @brief       Get number of active threads.
 * @return      number of active threads or 0 in case of an error.
 */
uint32_t osThreadGetCount(void)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = 0U;
  }
  else {
    count = SVC_0(svcThreadGetCount);
  }

  return (count);
}

/**
 * @fn          uint32_t osThreadEnumerate(osThreadId_t *thread_array, uint32_t array_items)
 * @brief       Enumerate active threads.
 * @param[out]  thread_array  pointer to array for retrieving thread IDs.
 * @param[in]   array_items   maximum number of items in array for retrieving thread IDs.
 * @return      number of enumerated threads or 0 in case of an error.
 */
uint32_t osThreadEnumerate(osThreadId_t *thread_array, uint32_t array_items)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = 0U;
  }
  else {
    count = SVC_2(thread_array, array_items, svcThreadEnumerate);
  }

  return (count);
}

/**
 * @fn          uint32_t osThreadFlagsSet(osThreadId_t thread_id, uint32_t flags)
 * @brief       Set the specified Thread Flags of a thread.
 * @param[in]   thread_id  thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @param[in]   flags      specifies the flags of the thread that shall be set.
 * @return      thread flags after setting or error code if highest bit set.
 */
uint32_t osThreadFlagsSet(osThreadId_t thread_id, uint32_t flags)
{
  uint32_t thread_flags;

  if ((thread_id == NULL) || (flags == 0U) || ((flags & ~osThreadFlagsMask) != 0U)) {
    return (osFlagsErrorParameter);
  }

  if (IsIrqMode() || IsIrqMasked()) {
    thread_flags = isrThreadFlagsSet(thread_id, flags);return (osFlagsErrorParameter);
  }
  else {
    thread_flags = SVC_2(thread_id, flags, svcThreadFlagsSet);
  }

  return (thread_flags);
}

/**
 * @fn          uint32_t osThreadFlagsClear(uint32_t flags)
 * @brief       Clear the specified Thread Flags of current running thread.
 * @param[in]   flags  specifies the flags of the thread that shall be cleared.
 * @return      thread flags before clearing or error code if highest bit set.
 */
uint32_t osThreadFlagsClear(uint32_t flags)
{
  /* Check parameters */
  if ((flags == 0U) || ((flags & ~osThreadFlagsMask) != 0U)) {
    return (osFlagsErrorParameter);
  }

  if (IsIrqMode() || IsIrqMasked()) {
    return (osFlagsErrorISR);
  }

  return (SVC_1(flags, svcThreadFlagsClear));
}

/**
 * @fn          uint32_t osThreadFlagsGet(void)
 * @brief       Get the current Thread Flags of current running thread.
 * @return      current thread flags.
 */
uint32_t osThreadFlagsGet(void)
{
  uint32_t thread_flags;

  if (IsIrqMode() || IsIrqMasked()) {
    thread_flags = 0U;
  }
  else {
    thread_flags = SVC_0(svcThreadFlagsGet);
  }

  return (thread_flags);
}

/**
 * @fn          uint32_t osThreadFlagsWait(uint32_t flags, uint32_t options, uint32_t timeout)
 * @brief       Wait for one or more Thread Flags of the current running thread to become signaled.
 * @param[in]   flags    specifies the flags to wait for.
 * @param[in]   options  specifies flags options (osFlagsXxxx).
 * @param[in]   timeout  \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      thread flags before clearing or error code if highest bit set.
 */
uint32_t osThreadFlagsWait(uint32_t flags, uint32_t options, uint32_t timeout)
{
  uint32_t thread_flags;

  /* Check parameters */
  if ((flags == 0U) || ((flags & ~osThreadFlagsMask) != 0U)) {
    return (osFlagsErrorParameter);
  }

  if (IsIrqMode() || IsIrqMasked()) {
    return (osFlagsErrorISR);
  }

  thread_flags = SVC_3(flags, options, timeout, svcThreadFlagsWait);
  if ((int32_t)thread_flags == osThreadWait) {
    thread_flags = ThreadGetRunning()->winfo.ret_val;
  }

  return (thread_flags);
}

/* ----------------------------- End of file ---------------------------------*/
