/*
 * Copyright (C) 2017-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *  Helper functions
 ******************************************************************************/

static void ThreadStackInit(uint32_t func_addr, void *func_param, osThread_t *thread)
{
  uint32_t *stk = (uint32_t *)((uint32_t)thread->stk_mem + thread->stk_size);

  *(--stk) = 0x01000000L;                       //-- xPSR
  *(--stk) = func_addr;                         //-- Entry Point
  *(--stk) = (uint32_t)osThreadExit;            //-- R14 (LR)
  *(--stk) = 0x12121212L;                       //-- R12
  *(--stk) = 0x03030303L;                       //-- R3
  *(--stk) = 0x02020202L;                       //-- R2
  *(--stk) = 0x01010101L;                       //-- R1
  *(--stk) = (uint32_t)func_param;              //-- R0 - thread's function argument
  *(--stk) = 0x11111111L;                       //-- R11
  *(--stk) = 0x10101010L;                       //-- R10
  *(--stk) = 0x09090909L;                       //-- R9
  *(--stk) = 0x08080808L;                       //-- R8
  *(--stk) = 0x07070707L;                       //-- R7
  *(--stk) = 0x06060606L;                       //-- R6
  *(--stk) = 0x05050505L;                       //-- R5
  *(--stk) = 0x04040404L;                       //-- R4

  thread->stk = (uint32_t)stk;
}

/**
 * @brief       Adds thread to the end of ready queue for current priority
 * @param[in]   thread
 */
static void ThreadReadyAdd(osThread_t *thread)
{
  int8_t priority = thread->priority - 1U;

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
  int8_t priority = thread->priority - 1U;

  /* Remove the thread from ready queue */
  QueueRemoveEntry(&thread->thread_que);

  if (isQueueEmpty(&osInfo.ready_list[priority])) {
    /* No ready threads for the current priority */
    osInfo.ready_to_run_bmp &= ~(1UL << priority);
  }
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osThreadId_t ThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
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
      (stack_size < 64U)  || ((stack_size & 7U) != 0U)            ) {
    return (NULL);
  }

  if (priority == osPriorityNone) {
    priority = osPriorityNormal;
  }
  else if ((priority < osPriorityIdle) || priority > osPriorityISR) {
    return (NULL);
  }

  /* Init thread control block */
  thread->stk_mem       = stack_mem;
  thread->stk_size      = stack_size;
  thread->base_priority = (int8_t)priority;
  thread->priority      = (int8_t)priority;
  thread->id            = ID_THREAD;
  thread->name          = attr->name;
  thread->delay         = 0U;

  QueueReset(&thread->thread_que);
  QueueReset(&thread->delay_que);
  QueueReset(&thread->mutex_que);

  /* Fill all thread stack space by FILL_STACK_VAL */
  uint32_t *ptr = stack_mem;
  for (uint32_t i = stack_size/sizeof(uint32_t); i != 0U; --i) {
    *ptr++ = FILL_STACK_VALUE;
  }

  ThreadStackInit((uint32_t)func, argument, thread);

  ThreadReadyAdd(thread);
  libThreadDispatch(thread);

  return (thread);
}

static
const char *ThreadGetName(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (NULL);
  }

  return (thread->name);
}

static
osThreadId_t ThreadGetId(void)
{
  osThread_t *thread;

  thread = ThreadGetRunning();

  return (thread);
}

static
osThreadState_t ThreadGetState(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (osThreadError);
  }

  return ((osThreadState_t)thread->state);
}

static
uint32_t ThreadGetStackSize(osThreadId_t thread_id)
{
  osThread_t *thread = (osThread_t *)thread_id;

  /* Check parameters */
  if ((thread == NULL) || (thread->id != ID_THREAD)) {
    return (0U);
  }

  return (thread->stk_size);
}

static
uint32_t ThreadGetStackSpace(osThreadId_t thread_id)
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

static osStatus_t ThreadSetPriority(osThreadId_t thread_id, osPriority_t priority)
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
    libThreadSetPriority(thread, (int8_t)priority);
  }

  return (osOK);
}

static osPriority_t ThreadGetPriority(osThreadId_t thread_id)
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

static osStatus_t ThreadYield(void)
{
  queue_t    *que;
  osThread_t *thread_running;

  if (osInfo.kernel.state == osKernelRunning) {
    thread_running = ThreadGetRunning();
    que = &osInfo.ready_list[thread_running->priority - 1U];

    /* Remove the running thread from ready queue */
    QueueRemoveEntry(&thread_running->thread_que);

    if (!isQueueEmpty(que)) {
      thread_running->state = ThreadStateReady;
      libThreadSwitch(GetThreadByQueue(que->next));
    }

    /* Add the running thread to the end of ready queue */
    QueueAppend(que, &thread_running->thread_que);
  }

  return (osOK);
}

static
osStatus_t ThreadSuspend(osThreadId_t thread_id)
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
        thread = libThreadHighestPrioGet();
        libThreadSwitch(thread);
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

static osStatus_t ThreadResume(osThreadId_t thread_id)
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
  libThreadWaitExit(thread, (uint32_t)osErrorTimeout, DISPATCH_YES);

  return (osOK);
}

static void ThreadExit(void)
{
  osThread_t *thread;

  if (osInfo.kernel.state != osKernelRunning ||
      osInfo.ready_to_run_bmp == 0U) {
    return;
  }

  thread = ThreadGetRunning();

  /* Release owned Mutexes */
  libMutexOwnerRelease(&thread->mutex_que);

  ThreadReadyDel(thread);
  libThreadSwitch(libThreadHighestPrioGet());
  thread->state = ThreadStateInactive;
  thread->id = ID_INVALID;
}

static osStatus_t ThreadTerminate(osThreadId_t thread_id)
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
    libMutexOwnerRelease(&thread->mutex_que);

    if (thread->state == ThreadStateRunning) {
      libThreadSwitch(libThreadHighestPrioGet());
    }
    else {
      libThreadDispatch(NULL);
    }

    thread->state = ThreadStateInactive;
    thread->id = ID_INVALID;
  }

  return (status);
}

static uint32_t ThreadGetCount(void)
{
  return (0U);
}

static uint32_t ThreadEnumerate(osThreadId_t *thread_array, uint32_t array_items)
{
  (void)thread_array;
  (void)array_items;

  return (0U);
}

/*******************************************************************************
 *  Library functions
 ******************************************************************************/

/**
 * @brief       Thread startup (Idle and Timer Thread).
 * @return      true - success, false - failure.
 */
bool libThreadStartup(void)
{
  bool ret = true;

  /* Create Idle Thread */
  if (osInfo.thread.idle == NULL) {
    osInfo.thread.idle = ThreadNew(osIdleThread, NULL, osConfig.idle_thread_attr);
    if (osInfo.thread.idle == NULL) {
      ret = false;
    }
  }

  /* Create Timer Thread */
  if (osInfo.thread.timer == NULL) {
    osInfo.thread.timer = ThreadNew(libTimerThread, NULL, osConfig.timer_thread_attr);
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
void libThreadWaitExit(osThread_t *thread, uint32_t ret_val, dispatch_t dispatch)
{
  BEGIN_CRITICAL_SECTION

  thread->winfo.ret_val = ret_val;

  /* Remove the thread from delay queue */
  QueueRemoveEntry(&thread->delay_que);
  ThreadReadyAdd(thread);
  if (dispatch != DISPATCH_NO) {
    libThreadDispatch(thread);
  }

  END_CRITICAL_SECTION
}

/**
 * @brief       Enter Thread wait state.
 * @param[out]  thread    thread object.
 * @param[out]  wait_que  Pointer to wait queue.
 * @param[in]   timeout   Timeout
 */
bool libThreadWaitEnter(osThread_t *thread, queue_t *wait_que, uint32_t timeout)
{
  queue_t *que;
  queue_t *delay_queue;

  if (osInfo.kernel.state != osKernelRunning) {
    return (false);
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

  thread = libThreadHighestPrioGet();
  libThreadSwitch(thread);

  return (true);
}

/**
 * @brief
 * @param wait_que
 */
void libThreadWaitDelete(queue_t *wait_que)
{
  while (!isQueueEmpty(wait_que)) {
    libThreadWaitExit(GetThreadByQueue(wait_que->next), (uint32_t)osErrorResource, DISPATCH_NO);
  }
  libThreadDispatch(NULL);
}

/**
 * @brief       Process Thread Delay Tick (executed each System Tick).
 */
bool libThreadDelayTick(void)
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
      libThreadWaitExit(thread, (uint32_t)osErrorTimeout, DISPATCH_NO);
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
void libThreadSetPriority(osThread_t *thread, int8_t priority)
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

osThread_t *libThreadHighestPrioGet(void)
{
  int8_t priority;
  osThread_t *thread;

  if (osInfo.ready_to_run_bmp == 0U) {
    return (NULL);
  }

  priority = (NUM_PRIORITY - 1U) - __CLZ(osInfo.ready_to_run_bmp);
  thread = GetThreadByQueue(osInfo.ready_list[priority].next);

  return (thread);
}

void libThreadSwitch(osThread_t *thread)
{
  thread->state = ThreadStateRunning;
  osInfo.thread.run.next = thread;
  archSwitchContextRequest();
}

/**
 * @brief       Dispatch specified Thread or Ready Thread with Highest Priority.
 * @param[in]   thread  thread object or NULL.
 */
void libThreadDispatch(osThread_t *thread)
{
  osThread_t *thread_running;

  if (thread == NULL) {
    thread = libThreadHighestPrioGet();
  }

  thread_running = ThreadGetRunning();

  if ((osInfo.kernel.state == osKernelRunning) &&
      (thread != NULL) &&
      (thread_running != NULL) &&
      (thread->priority > thread_running->priority)) {
    /* Preempt running Thread */
    thread_running->state = ThreadStateReady;
    libThreadSwitch(thread);
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
    thread_id = (osThreadId_t)SVC_3(func, argument, attr, ThreadNew);
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
    name = (const char *)SVC_1(thread_id, ThreadGetName);
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
    thread_id = ThreadGetId();
  }
  else {
    thread_id = (osThreadId_t)SVC_0(ThreadGetId);
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
    state = (osThreadState_t)SVC_1(thread_id, ThreadGetState);
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
    stack_size = SVC_1(thread_id, ThreadGetStackSize);
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
    stack_space = SVC_1(thread_id, ThreadGetStackSpace);
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
    status = (osStatus_t)SVC_2(thread_id, priority, ThreadSetPriority);
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
    priority = (osPriority_t)SVC_1(thread_id, ThreadGetPriority);
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
    status = (osStatus_t)SVC_0(ThreadYield);
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
    status = (osStatus_t)SVC_1(thread_id, ThreadSuspend);
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
    status = (osStatus_t)SVC_1(thread_id, ThreadResume);
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
  SVC_0(ThreadExit);
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
    status = (osStatus_t)SVC_1(thread_id, ThreadTerminate);
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
    count = SVC_0(ThreadGetCount);
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
    count = SVC_2(thread_array, array_items, ThreadEnumerate);
  }

  return (count);
}

/* ----------------------------- End of file ---------------------------------*/
