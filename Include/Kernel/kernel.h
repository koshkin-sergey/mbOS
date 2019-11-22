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

#ifndef _KERNEL_H_
#define _KERNEL_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>

#ifdef  __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* Flags options (\ref osEventFlagsWait) */
#define osFlagsWaitAny                0x00000000U ///< Wait for any flag (default).
#define osFlagsWaitAll                0x00000001U ///< Wait for all flags.
#define osFlagsNoClear                0x00000002U ///< Do not clear flags which have been specified to wait for.

/* Thread attributes (attr_bits in \ref osThreadAttr_t) */
#define osThreadDetached              0x00000000U ///< Thread created in detached mode (default)
#define osThreadJoinable              0x00000001U ///< Thread created in joinable mode

/* Mutex attributes */
#define osMutexPrioInherit            (1UL<<0)    ///< Priority inherit protocol.
#define osMutexRecursive              (1UL<<1)    ///< Recursive mutex.
#define osMutexRobust                 (1UL<<2)    ///< Robust mutex.

/* OS Configuration flags */
#define osConfigPrivilegedMode        (1UL<<0)    ///< Threads in Privileged mode
#define osConfigStackCheck            (1UL<<1)    ///< Stack overrun checking
#define osConfigStackWatermark        (1UL<<2)    ///< Stack usage Watermark

/* Timeout value */
#define osWaitForever                 (0xFFFFFFFF)

#define time_after(a,b)               ((int32_t)(b) - (int32_t)(a) < 0)
#define time_before(a,b)              time_after(b,a)

#define time_after_eq(a,b)            ((int32_t)(a) - (int32_t)(b) >= 0)
#define time_before_eq(a,b)           time_after_eq(b,a)

/* Control Block sizes */
#define osThreadCbSize                sizeof(osThread_t)
#define osTimerCbSize                 sizeof(osTimer_t)
#define osEventFlagsCbSize            sizeof(osEventFlags_t)
#define osMutexCbSize                 sizeof(osMutex_t)
#define osSemaphoreCbSize             sizeof(osSemaphore_t)
#define osMemoryPoolCbSize            sizeof(osMemoryPool_t)
#define osMessageQueueCbSize          sizeof(osMessageQueue_t)

/// Memory size in bytes for Memory Pool storage.
/// \param         block_count   maximum number of memory blocks in memory pool.
/// \param         block_size    memory block size in bytes.
#define osMemoryPoolMemSize(block_count, block_size) \
  (4*(block_count)*(((block_size)+3)/4))

/// Memory size in bytes for Message Queue storage.
/// \param         msg_count     maximum number of messages in queue.
/// \param         msg_size      maximum message size in bytes.
#define osMessageQueueMemSize(msg_count, msg_size) \
  (4*(msg_count)*(3+(((msg_size)+3)/4)))

/* Number priority levels */
#define NUM_PRIORITY                  (32U)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/// Version information.
typedef struct {
  uint32_t                       api;   ///< API version (major.minor.rev: mmnnnrrrr dec).
  uint32_t                    kernel;   ///< Kernel version (major.minor.rev: mmnnnrrrr dec).
} osVersion_t;

/// Kernel state.
typedef enum {
  osKernelInactive        =  0,         ///< Inactive.
  osKernelReady           =  1,         ///< Ready.
  osKernelRunning         =  2,         ///< Running.
  osKernelLocked          =  3,         ///< Locked.
  osKernelSuspended       =  4,         ///< Suspended.
  osKernelError           = -1,         ///< Error.
  osKernelReserved        = 0x7FFFFFFFU ///< Prevents enum down-size compiler optimization.
} osKernelState_t;

/// Status code values returned by CMSIS-RTOS functions.
typedef enum {
  osOK                    =  0,         ///< Operation completed successfully.
  osError                 = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
  osErrorTimeout          = -2,         ///< Operation not completed within the timeout period.
  osErrorResource         = -3,         ///< Resource not available.
  osErrorParameter        = -4,         ///< Parameter error.
  osErrorNoMemory         = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
  osErrorISR              = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
  osStatusReserved        = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osStatus_t;

/// Priority values.
typedef enum {
  osPriorityNone          =  0,         ///< No priority (not initialized).
  osPriorityIdle          =  1,         ///< Reserved for Idle thread.
  osPriorityLow           =  2,         ///< Priority: low
  osPriorityLow1          =  2+1,       ///< Priority: low + 1
  osPriorityLow2          =  2+2,       ///< Priority: low + 2
  osPriorityLow3          =  2+3,       ///< Priority: low + 3
  osPriorityLow4          =  2+4,       ///< Priority: low + 4
  osPriorityBelowNormal   =  7,         ///< Priority: below normal
  osPriorityBelowNormal1  =  7+1,       ///< Priority: below normal + 1
  osPriorityBelowNormal2  =  7+2,       ///< Priority: below normal + 2
  osPriorityBelowNormal3  =  7+3,       ///< Priority: below normal + 3
  osPriorityBelowNormal4  =  7+4,       ///< Priority: below normal + 4
  osPriorityNormal        = 12,         ///< Priority: normal
  osPriorityNormal1       = 12+1,       ///< Priority: normal + 1
  osPriorityNormal2       = 12+2,       ///< Priority: normal + 2
  osPriorityNormal3       = 12+3,       ///< Priority: normal + 3
  osPriorityNormal4       = 12+4,       ///< Priority: normal + 4
  osPriorityAboveNormal   = 17,         ///< Priority: above normal
  osPriorityAboveNormal1  = 17+1,       ///< Priority: above normal + 1
  osPriorityAboveNormal2  = 17+2,       ///< Priority: above normal + 2
  osPriorityAboveNormal3  = 17+3,       ///< Priority: above normal + 3
  osPriorityAboveNormal4  = 17+4,       ///< Priority: above normal + 4
  osPriorityHigh          = 22,         ///< Priority: high
  osPriorityHigh1         = 22+1,       ///< Priority: high + 1
  osPriorityHigh2         = 22+2,       ///< Priority: high + 2
  osPriorityHigh3         = 22+3,       ///< Priority: high + 3
  osPriorityHigh4         = 22+4,       ///< Priority: high + 4
  osPriorityRealtime      = 27,         ///< Priority: realtime
  osPriorityRealtime1     = 27+1,       ///< Priority: realtime + 1
  osPriorityRealtime2     = 27+2,       ///< Priority: realtime + 2
  osPriorityRealtime3     = 27+3,       ///< Priority: realtime + 3
  osPriorityRealtime4     = 27+4,       ///< Priority: realtime + 4
  osPriorityISR           = 32,         ///< Reserved for ISR deferred thread.
  osPriorityError         = -1,         ///< System cannot determine priority or illegal priority.
  osPriorityReserved      = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osPriority_t;

/// Thread state.
typedef enum {
  osThreadInactive        =  0,         ///< Inactive.
  osThreadReady           =  1,         ///< Ready.
  osThreadRunning         =  2,         ///< Running.
  osThreadBlocked         =  3,         ///< Blocked.
  osThreadTerminated      =  4,         ///< Terminated.
  osThreadError           = -1,         ///< Error.
  osThreadReserved        = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osThreadState_t;

/// Timer type.
typedef enum {
  osTimerOnce               = 0,          ///< One-shot timer.
  osTimerPeriodic           = 1           ///< Repeating timer.
} osTimerType_t;

/// Entry point of a thread.
typedef void (*osThreadFunc_t)(void *argument);

/// Timer callback function.
typedef void (*osTimerFunc_t)(void *argument);

/* Circular double-linked list queue */
typedef struct queue_s {
  struct queue_s *next;
  struct queue_s *prev;
} queue_t;

/* Timer Function Information */
typedef struct osTimerFinfo_s {
  osTimerFunc_t                  func;  ///< Function Pointer
  void                           *arg;  ///< Function Argument
} osTimerFinfo_t;

typedef struct winfo_msgque_s {
  uint32_t  msg;
  uint32_t  msg_prio;
} winfo_msgque_t;

typedef struct winfo_dataque_s {
  uint32_t  data_ptr;
} winfo_dataque_t;

typedef struct winfo_event_s {
  uint32_t flags;
  uint32_t options;
} winfo_event_t;

/*
 * Definition of wait information in thread control block
 */
typedef struct winfo_s {
  union {
    winfo_msgque_t  msgque;
    winfo_dataque_t dataque;
    winfo_event_t   event;
  };
  uint32_t ret_val;
} winfo_t;

/// @details Thread ID identifies the thread.
typedef void *osThreadId_t;

/// \details Timer ID identifies the timer.
typedef void *osTimerId_t;

/// @details Event Flags ID identifies the event flags.
typedef void *osEventFlagsId_t;

/// \details Semaphore ID identifies the semaphore.
typedef void *osSemaphoreId_t;

/// \details Mutex ID identifies the mutex.
typedef void *osMutexId_t;

/// \details Message Queue ID identifies the message queue.
typedef void *osMessageQueueId_t;

/// \details Data Queue ID identifies the data queue.
typedef void *osDataQueueId_t;

/// \details Memory Pool ID identifies the memory pool.
typedef void *osMemoryPoolId_t;

/* Thread Control Block */
typedef struct osThread_s {
  uint32_t                        stk;  ///< Address of thread's top of stack
  queue_t                  thread_que;  ///< Queue is used to include thread in ready/wait lists
  queue_t                   mutex_que;  ///< List of all mutexes that tack locked
  void                       *stk_mem;  ///< Base address of thread's stack space
  uint32_t                   stk_size;  ///< Task's stack size (in bytes)
  int8_t                base_priority;  ///< Task base priority
  int8_t                     priority;  ///< Task current priority
  uint8_t                          id;  ///< ID for verification(is it a thread or another object?)
  uint8_t                       state;  ///< Task state
  const char                    *name;  ///< Object Name
  winfo_t                       winfo;  ///< Wait information
  queue_t                   delay_que;  ///< Queue is used to include thread id delay list
  uint32_t                      delay;  ///< Delay Time
} osThread_t;

/* Semaphore Control Block */
typedef struct osSemaphore_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    reserved;
  const char                    *name;  ///< Object Name
  queue_t                  wait_queue;  ///< Waiting Threads queue
  uint16_t                      count;  ///< Current number of tokens
  uint16_t                  max_count;  ///< Maximum number of tokens
} osSemaphore_t;

/* Event Flags Control Block */
typedef struct osEventFlags_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    reserved;
  const char                    *name;  ///< Object Name
  queue_t                  wait_queue;  ///< Waiting Threads queue
  uint32_t                event_flags;  ///< Initial value of the eventflag bit pattern
} osEventFlags_t;

/* - Memory Pool definitions   -----------------------------------------------*/

/* Memory Pool Information */
typedef struct osMemoryPoolInfo_s {
  uint32_t                 max_blocks;  ///< Maximum number of Blocks
  uint32_t                used_blocks;  ///< Number of used Blocks
  uint32_t                 block_size;  ///< Block Size
  void                    *block_base;  ///< Block Memory Base Address
  void                     *block_lim;  ///< Block Memory Limit Address
  void                    *block_free;  ///< First free Block Address
} osMemoryPoolInfo_t;

/* Memory Pool Control Block */
typedef struct osMemoryPool_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    reserved;
  const char                    *name;  ///< Object Name
  queue_t                  wait_queue;  ///< Waiting Threads queue
  osMemoryPoolInfo_t             info;  ///< Memory Pool Info
} osMemoryPool_t;

/* - Message Queue definitions   -----------------------------------------------*/

/* Message Control Block */
typedef struct osMessage_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    priority;  ///< Message Priority
  queue_t                     msg_que;  ///< Entry is used to include message in the list
} osMessage_t;

/* Message Queue Control Block */
typedef struct osMessageQueue_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    reserved;
  const char                    *name;  ///< Object Name
  queue_t              wait_put_queue;  ///< Queue of threads waiting to send a message
  queue_t              wait_get_queue;  ///< Queue of threads waiting to receive a message
  osMemoryPoolInfo_t          mp_info;  ///< Memory Pool Info
  uint32_t                   msg_size;  ///< Message size in bytes
  uint32_t                  msg_count;  ///< Number of queued Messages
  queue_t                   msg_queue;  ///< List of all queued Messages
} osMessageQueue_t;

/* Data Queue Control Block */
typedef struct osDataQueue_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                    reserved;
  const char                    *name;  ///< Object Name
  queue_t              wait_put_queue;  ///< Queue of threads waiting to send a data
  queue_t              wait_get_queue;  ///< Queue of threads waiting to receive a data
  uint32_t             max_data_count;  ///< Maximum number of Data
  uint32_t                  data_size;  ///< Data size in bytes
  uint32_t                 data_count;  ///< Number of queued Data
  uint32_t                 data_limit;  ///< Data Limit
  uint32_t                       head;
  uint32_t                       tail;
  uint8_t                     *dq_mem;  ///< Data Memory Address
} osDataQueue_t;

/* Mutex Control Block */
typedef struct osMutex_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t              reserved_state;  ///< Object State (not used)
  uint8_t                       flags;  ///< Object Flags
  uint8_t                        attr;  ///< Object Attributes
  const char                    *name;  ///< Object Name
  queue_t                    wait_que;  ///< List of tasks that wait a mutex
  queue_t                   mutex_que;  ///< To include in thread's locked mutexes list (if any)
  osThread_t                  *holder;  ///< Current mutex owner(thread that locked mutex)
  uint32_t                        cnt;  ///< Lock counter
} osMutex_t;

/* Timer Control Block */
typedef struct osTimer_s {
  uint8_t                          id;  ///< Object Identifier
  uint8_t                       state;  ///< Object State
  uint8_t                       flags;  ///< Object Flags
  uint8_t                        type;  ///< Timer Type (Periodic/One-shot)
  const char                    *name;  ///< Object Name
  uint32_t                       load;  ///< Timer Load value
  uint32_t                       time;  ///< Event time
  queue_t                   timer_que;  ///< Timer event queue
  osTimerFinfo_t                finfo;  ///< Timer Function Info
} osTimer_t;

#ifndef TZ_MODULEID_T
#define TZ_MODULEID_T
/// \details Data type that identifies secure software modules called by a process.
typedef uint32_t TZ_ModuleId_t;
#endif

/// Attributes structure for thread.
typedef struct {
  const char                   *name;   ///< name of the thread
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                    *stack_mem;   ///< memory for stack
  uint32_t                stack_size;   ///< size of stack
  osPriority_t              priority;   ///< initial thread priority (default: osPriorityNormal)
  TZ_ModuleId_t            tz_module;   ///< TrustZone module identifier
  uint32_t                  reserved;   ///< reserved (must be 0)
} osThreadAttr_t;

/// Attributes structure for timer.
typedef struct {
  const char                   *name;   ///< name of the timer
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osTimerAttr_t;

/// Attributes structure for event flags.
typedef struct {
  const char                   *name;   ///< name of the event flags
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osEventFlagsAttr_t;

/// Attributes structure for semaphore.
typedef struct {
  const char                   *name;   ///< name of the semaphore
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osSemaphoreAttr_t;

/// Attributes structure for mutex.
typedef struct {
  const char                   *name;   ///< name of the mutex
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osMutexAttr_t;

/// Attributes structure for message queue.
typedef struct {
  const char                   *name;   ///< name of the message queue
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                       *mq_mem;   ///< memory for data storage
  uint32_t                   mq_size;   ///< size of provided memory for data storage
} osMessageQueueAttr_t;

/// Attributes structure for data queue.
typedef struct osDataQueueAttr_s {
  const char                   *name;   ///< name of the data queue
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                       *dq_mem;   ///< memory for data storage
  uint32_t                   dq_size;   ///< size of provided memory for data storage
} osDataQueueAttr_t;

/// Attributes structure for memory pool.
typedef struct {
  const char                   *name;   ///< name of the memory pool
  uint32_t                 attr_bits;   ///< attribute bits
  void                       *cb_mem;   ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                       *mp_mem;   ///< memory for data storage
  uint32_t                   mp_size;   ///< size of provided memory for data storage
} osMemoryPoolAttr_t;

/* OS Configuration structure */
typedef struct osConfig_s {
  uint32_t                             flags;   ///< OS Configuration Flags
  uint32_t                         tick_freq;   ///< Kernel Tick Frequency
  uint32_t                     robin_timeout;   ///< Round Robin Timeout Tick
  uint32_t        max_api_interrupt_priority;
  const
  osThreadAttr_t           *idle_thread_attr;   ///< Idle Thread Attributes
  const
  osThreadAttr_t          *timer_thread_attr;   ///< Timer Thread Attributes
  const
  osSemaphoreAttr_t    *timer_semaphore_attr;   ///< Timer Semaphore Attributes
} osConfig_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  OS External Functions
 ******************************************************************************/

/* OS Idle Thread */
extern void osIdleThread(void *argument);
/* SysTick timer initialization */
extern void osSysTickInit(uint32_t hz);

/*******************************************************************************
 *  Kernel Information and Control
 ******************************************************************************/

/**
 * @fn          osStatus_t osKernelInitialize(void)
 * @brief       Initialize the RTOS Kernel.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osKernelInitialize(void);

/**
 * @fn          osStatus_t osKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size)
 * @brief       Get RTOS Kernel Information.
 * @param[out]  version   pointer to buffer for retrieving version information.
 * @param[out]  id_buf    pointer to buffer for retrieving kernel identification string.
 * @param[in]   id_size   size of buffer for kernel identification string.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size);

/**
 * @fn          osKernelState_t osKernelGetState(void)
 * @brief       Get the current RTOS Kernel state.
 * @return      current RTOS Kernel state.
 */
osKernelState_t osKernelGetState(void);

/**
 * @fn          osStatus_t osKernelStart(void)
 * @brief       Start the RTOS Kernel scheduler.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osKernelStart(void);

/**
 * @fn          int32_t osKernelLock(void)
 * @brief       Lock the RTOS Kernel scheduler.
 * @return      previous lock state (1 - locked, 0 - not locked, error code if negative).
 */
int32_t osKernelLock(void);

/**
 * @fn          int32_t osKernelUnlock(void)
 * @brief       Unlock the RTOS Kernel scheduler.
 * @return      previous lock state (1 - locked, 0 - not locked, error code if negative).
 */
int32_t osKernelUnlock(void);

/**
 * @fn          int32_t osKernelRestoreLock(int32_t lock)
 * @brief       Restore the RTOS Kernel scheduler lock state.
 * @param[in]   lock  lock state obtained by \ref osKernelLock or \ref osKernelUnlock.
 * @return      new lock state (1 - locked, 0 - not locked, error code if negative).
 */
int32_t osKernelRestoreLock(int32_t lock);

/**
 * @fn          uint32_t osKernelGetTickCount(void)
 * @brief       Get the RTOS kernel tick count.
 * @return      RTOS kernel current tick count.
 */
uint32_t osKernelGetTickCount(void);

/**
 * @fn          uint32_t osKernelGetTickFreq(void)
 * @brief       Get the RTOS kernel tick frequency.
 * @return      frequency of the kernel tick in hertz, i.e. kernel ticks per second.
 */
uint32_t osKernelGetTickFreq(void);

/*******************************************************************************
 *  Timer Management
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
osTimerId_t osTimerNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);

/**
 * @fn          const char *osTimerGetName(osTimerId_t timer_id)
 * @brief       Get name of a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osTimerGetName(osTimerId_t timer_id);

/**
 * @fn          osStatus_t osTimerStart(osTimerId_t timer_id, uint32_t ticks)
 * @brief       Start or restart a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @param[in]   ticks     \ref CMSIS_RTOS_TimeOutValue "time ticks" value of the timer.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osTimerStart(osTimerId_t timer_id, uint32_t ticks);

/**
 * @fn          osStatus_t osTimerStop(osTimerId_t timer_id)
 * @brief       Stop a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osTimerStop(osTimerId_t timer_id);

/**
 * @fn          uint32_t osTimerIsRunning(osTimerId_t timer_id)
 * @brief       Check if a timer is running.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      0 not running or an error occurred, 1 running.
 */
uint32_t osTimerIsRunning(osTimerId_t timer_id);

/**
 * @fn          osStatus_t osTimerDelete(osTimerId_t timer_id)
 * @brief       Delete a timer.
 * @param[in]   timer_id  timer ID obtained by \ref osTimerNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osTimerDelete(osTimerId_t timer_id);

/*******************************************************************************
 *  Thread Management
 ******************************************************************************/

/**
 * @fn          osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
 * @brief       Create a thread and add it to Active Threads.
 * @param[in]   func      thread function.
 * @param[in]   argument  pointer that is passed to the thread function as start argument.
 * @param[in]   attr      thread attributes.
 * @return      thread ID for reference by other functions or NULL in case of error.
 */
osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);

/**
 * @fn          const char *osThreadGetName(osThreadId_t thread_id)
 * @brief       Get name of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      name as null-terminated string.
 */
const char *osThreadGetName(osThreadId_t thread_id);

/**
 * @fn          osThreadId_t osThreadGetId(void)
 * @brief       Return the thread ID of the current running thread.
 * @return      thread ID for reference by other functions or NULL in case of error.
 */
osThreadId_t osThreadGetId(void);

/**
 * @fn          osThreadState_t osThreadGetState(osThreadId_t thread_id)
 * @brief       Get current thread state of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      current thread state of the specified thread.
 */
osThreadState_t osThreadGetState(osThreadId_t thread_id);

/**
 * @fn          uint32_t osThreadGetStackSize(osThreadId_t thread_id)
 * @brief       Get stack size of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      stack size in bytes.
 */
uint32_t osThreadGetStackSize(osThreadId_t thread_id);

/**
 * @fn          uint32_t osThreadGetStackSpace(osThreadId_t thread_id)
 * @brief       Get available stack space of a thread based on stack watermark recording during execution.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      remaining stack space in bytes.
 */
uint32_t osThreadGetStackSpace(osThreadId_t thread_id);

/**
 * @fn          osStatus_t osThreadSetPriority(osThreadId_t thread_id, osPriority_t priority)
 * @brief       Change priority of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @param[in]   priority    new priority value for the thread function.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadSetPriority(osThreadId_t thread_id, osPriority_t priority);

/**
 * @fn          osPriority_t osThreadGetPriority(osThreadId_t thread_id)
 * @brief       Get current priority of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      current priority value of the specified thread.
 */
osPriority_t osThreadGetPriority(osThreadId_t thread_id);

/**
 * @fn          osStatus_t osThreadYield(void)
 * @brief       Pass control to next thread that is in state READY.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadYield(void);

/**
 * @fn          osStatus_t osThreadSuspend(osThreadId_t thread_id)
 * @brief       Suspend execution of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadSuspend(osThreadId_t thread_id);

/**
 * @fn          osStatus_t osThreadResume(osThreadId_t thread_id)
 * @brief       Resume execution of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadResume(osThreadId_t thread_id);

/**
 * @fn          void osThreadExit(void)
 * @brief       Terminate execution of current running thread.
 */
__NO_RETURN void osThreadExit(void);

/**
 * @fn          osStatus_t osThreadTerminate(osThreadId_t thread_id)
 * @brief       Terminate execution of a thread.
 * @param[in]   thread_id   thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osThreadTerminate(osThreadId_t thread_id);

/**
 * @fn          uint32_t osThreadGetCount(void)
 * @brief       Get number of active threads.
 * @return      number of active threads or 0 in case of an error.
 */
uint32_t osThreadGetCount(void);

/**
 * @fn          uint32_t osThreadEnumerate(osThreadId_t *thread_array, uint32_t array_items)
 * @brief       Enumerate active threads.
 * @param[out]  thread_array  pointer to array for retrieving thread IDs.
 * @param[in]   array_items   maximum number of items in array for retrieving thread IDs.
 * @return      number of enumerated threads or 0 in case of an error.
 */
uint32_t osThreadEnumerate(osThreadId_t *thread_array, uint32_t array_items);

/*******************************************************************************
 *  Generic Wait Functions
 ******************************************************************************/

/**
 * @fn          osStatus_t osDelay(uint32_t ticks)
 * @brief       Wait for Timeout (Time Delay).
 * @param[in]   ticks   \ref CMSIS_RTOS_TimeOutValue "time ticks" value
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDelay(uint32_t ticks);

/**
 * @fn          osStatus_t osDelayUntil(uint32_t ticks)
 * @brief       Wait until specified time.
 * @param[in]   ticks   absolute time in ticks
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDelayUntil(uint32_t ticks);

/*******************************************************************************
 *  Semaphores
 ******************************************************************************/

/**
 * @fn          osSemaphoreId_t osSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr)
 * @brief       Create and Initialize a Semaphore object.
 * @param[in]   max_count       maximum number of available tokens.
 * @param[in]   initial_count   initial number of available tokens.
 * @param[in]   attr            semaphore attributes.
 * @return      semaphore ID for reference by other functions or NULL in case of error.
 */
osSemaphoreId_t osSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);

/**
 * @fn          const char *osSemaphoreGetName(osSemaphoreId_t semaphore_id)
 * @brief       Get name of a Semaphore object.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osSemaphoreGetName(osSemaphoreId_t semaphore_id);

/**
 * @fn          osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout)
 * @brief       Acquire a Semaphore token or timeout if no tokens are available.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @param[in]   timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout);

/**
 * @fn          osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id)
 * @brief       Release a Semaphore token that was acquired by osSemaphoreAcquire.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id);

/**
 * @fn          uint32_t osSemaphoreGetCount(osSemaphoreId_t semaphore_id)
 * @brief       Get current Semaphore token count.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      number of tokens available or 0 in case of an error.
 */
uint32_t osSemaphoreGetCount(osSemaphoreId_t semaphore_id);

/**
 * @fn          osStatus_t osSemaphoreDelete(osSemaphoreId_t semaphore_id)
 * @brief       Delete a Semaphore object.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreDelete(osSemaphoreId_t semaphore_id);


/*******************************************************************************
 *  Message Queue
 ******************************************************************************/

/**
 * @fn          osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr)
 * @brief       Create and Initialize a Message Queue object.
 * @param[in]   msg_count   maximum number of messages in queue.
 * @param[in]   msg_size    maximum message size in bytes.
 * @param[in]   attr        message queue attributes.
 * @return      message queue ID for reference by other functions or NULL in case of error.
 */
osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);

/**
 * @fn          const char *osMessageQueueGetName(osMessageQueueId_t mq_id)
 * @brief       Get name of a Message Queue object.
 * @param[in]   mq_id   message queue ID obtained by \ref osMessageQueueNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osMessageQueueGetName(osMessageQueueId_t mq_id);

/**
 * @fn          osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
 * @brief       Put a Message into a Queue or timeout if Queue is full.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @param[in]   msg_ptr   pointer to buffer with message to put into a queue.
 * @param[in]   msg_prio  message priority.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);

/**
 * @fn          osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
 * @brief       Get a Message from a Queue or timeout if Queue is empty.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @param[out]  msg_ptr   pointer to buffer for message to get from a queue.
 * @param[out]  msg_prio  pointer to buffer for message priority or NULL.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);

/**
 * @fn          uint32_t osMessageQueueGetCapacity(osMessageQueueId_t mq_id)
 * @brief       Get maximum number of messages in a Message Queue.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      maximum number of messages or 0 in case of an error.
 */
uint32_t osMessageQueueGetCapacity(osMessageQueueId_t mq_id);

/**
 * @fn          uint32_t osMessageQueueGetMsgSize(osMessageQueueId_t mq_id)
 * @brief       Get maximum message size in bytes.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      maximum message size in bytes or 0 in case of an error.
 */
uint32_t osMessageQueueGetMsgSize(osMessageQueueId_t mq_id);

/**
 * @fn          uint32_t osMessageQueueGetCount(osMessageQueueId_t mq_id)
 * @brief       Get number of queued messages in a Message Queue.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      number of queued messages or 0 in case of an error.
 */
uint32_t osMessageQueueGetCount(osMessageQueueId_t mq_id);

/**
 * @fn          uint32_t osMessageQueueGetSpace(osMessageQueueId_t mq_id)
 * @brief       Get number of available slots for messages in a Message Queue.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      number of available slots for messages or 0 in case of an error.
 */
uint32_t osMessageQueueGetSpace(osMessageQueueId_t mq_id);

/**
 * @fn          osStatus_t osMessageQueueReset(osMessageQueueId_t mq_id)
 * @brief       Reset a Message Queue to initial empty state.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueReset(osMessageQueueId_t mq_id);

/**
 * @fn          osStatus_t osMessageQueueDelete(osMessageQueueId_t mq_id)
 * @brief       Delete a Message Queue object.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueDelete(osMessageQueueId_t mq_id);

/*******************************************************************************
 *  Data Queue
 ******************************************************************************/

/**
 * @fn          osDataQueueId_t osDataQueueNew(uint32_t data_count, uint32_t data_size, const osDataQueueAttr_t *attr)
 * @brief       Create and Initialize a Data Queue object.
 * @param[in]   data_count  maximum number of data in queue.
 * @param[in]   data_size   maximum data size in bytes.
 * @param[in]   attr        data queue attributes.
 * @return      data queue ID for reference by other functions or NULL in case of error.
 */
osDataQueueId_t osDataQueueNew(uint32_t data_count, uint32_t data_size, const osDataQueueAttr_t *attr);

/**
 * @fn          const char *osDataQueueGetName(osDataQueueId_t dq_id)
 * @brief       Get name of a Data Queue object.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osDataQueueGetName(osDataQueueId_t dq_id);

/**
 * @fn          osStatus_t osDataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout)
 * @brief       Put a Data into a Queue or timeout if Queue is full.
 * @param[in]   dq_id     data queue ID obtained by \ref osDataQueueNew.
 * @param[in]   data_ptr  pointer to buffer with data to put into a queue.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout);

/**
 * @fn          osStatus_t osDataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout)
 * @brief       Get a Data from a Queue or timeout if Queue is empty.
 * @param[in]   dq_id     data queue ID obtained by \ref osDataQueueNew.
 * @param[out]  data_ptr  pointer to buffer for data to get from a queue.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout);

/**
 * @fn          uint32_t osDataQueueGetCapacity(osDataQueueId_t dq_id)
 * @brief       Get maximum number of data in a Data Queue.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      maximum number of data or 0 in case of an error.
 */
uint32_t osDataQueueGetCapacity(osDataQueueId_t dq_id);

/**
 * @fn          uint32_t osDataQueueGetDataSize(osDataQueueId_t dq_id)
 * @brief       Get maximum data size in bytes.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      maximum data size in bytes or 0 in case of an error.
 */
uint32_t osDataQueueGetDataSize(osDataQueueId_t dq_id);

/**
 * @fn          uint32_t osDataQueueGetCount(osDataQueueId_t dq_id)
 * @brief       Get number of queued data in a Data Queue.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      number of queued data or 0 in case of an error.
 */
uint32_t osDataQueueGetCount(osDataQueueId_t dq_id);

/**
 * @fn          uint32_t osDataQueueGetSpace(osDataQueueId_t dq_id)
 * @brief       Get number of available slots for data in a Data Queue.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      number of available slots for data or 0 in case of an error.
 */
uint32_t osDataQueueGetSpace(osDataQueueId_t dq_id);

/**
 * @fn          osStatus_t osDataQueueReset(osDataQueueId_t dq_id)
 * @brief       Reset a Data Queue to initial empty state.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueueReset(osDataQueueId_t dq_id);

/**
 * @fn          osStatus_t osDataQueueDelete(osDataQueueId_t dq_id)
 * @brief       Delete a Data Queue object.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueueDelete(osDataQueueId_t dq_id);

/*******************************************************************************
 *  Event Flags
 ******************************************************************************/

/**
 * @fn          osEventFlagsId_t osEventFlagsNew(const osEventFlagsAttr_t *attr)
 * @brief       Create and Initialize an Event Flags object.
 * @param[in]   attr  event flags attributes.
 * @return      event flags ID for reference by other functions or NULL in case of error.
 */
osEventFlagsId_t osEventFlagsNew(const osEventFlagsAttr_t *attr);

/**
 * @fn          const char *osEventFlagsGetName(osEventFlagsId_t ef_id)
 * @brief       Get name of an Event Flags object.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osEventFlagsGetName(osEventFlagsId_t ef_id);

/**
 * @fn          uint32_t osEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
 * @brief       Set the specified Event Flags.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]   flags   specifies the flags that shall be set.
 * @return      event flags after setting or error code if highest bit set.
 */
uint32_t osEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags);

/**
 * @fn          uint32_t osEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags)
 * @brief       Clear the specified Event Flags.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]   flags   specifies the flags that shall be cleared.
 * @return      event flags before clearing or error code if highest bit set.
 */
uint32_t osEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags);

/**
 * @fn          uint32_t osEventFlagsGet(osEventFlagsId_t ef_id)
 * @brief       Get the current Event Flags.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @return      current event flags or 0 in case of an error.
 */
uint32_t osEventFlagsGet(osEventFlagsId_t ef_id);

/**
 * @fn          uint32_t osEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
 * @brief       Wait for one or more Event Flags to become signaled.
 * @param[in]   ef_id     event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]   flags     specifies the flags to wait for.
 * @param[in]   options   specifies flags options (osFlagsXxxx).
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      event flags before clearing or error code if highest bit set.
 */
uint32_t osEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);

/**
 * @fn          osStatus_t osEventFlagsDelete(osEventFlagsId_t ef_id)
 * @brief       Delete an Event Flags object.
 * @param[in]   ef_id   event flags ID obtained by \ref osEventFlagsNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osEventFlagsDelete(osEventFlagsId_t ef_id);


/*******************************************************************************
 *  Memory Pool
 ******************************************************************************/

/**
 * @fn          osMemoryPoolId_t osMemoryPoolNew(uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr)
 * @brief       Create and Initialize a Memory Pool object.
 * @param[in]   block_count   maximum number of memory blocks in memory pool.
 * @param[in]   block_size    memory block size in bytes.
 * @param[in]   attr          memory pool attributes.
 * @return      memory pool ID for reference by other functions or NULL in case of error.
 */
osMemoryPoolId_t osMemoryPoolNew(uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr);

/**
 * @fn          const char *osMemoryPoolGetName(osMemoryPoolId_t mp_id)
 * @brief       Get name of a Memory Pool object.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osMemoryPoolGetName(osMemoryPoolId_t mp_id);

/**
 * @fn          void *osMemoryPoolAlloc(osMemoryPoolId_t mp_id, uint32_t timeout)
 * @brief       Allocate a memory block from a Memory Pool.
 * @param[in]   mp_id     memory pool ID obtained by \ref osMemoryPoolNew.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      address of the allocated memory block or NULL in case of no memory is available.
 */
void *osMemoryPoolAlloc(osMemoryPoolId_t mp_id, uint32_t timeout);

/**
 * @fn          osStatus_t osMemoryPoolFree(osMemoryPoolId_t mp_id, void *block)
 * @brief       Return an allocated memory block back to a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @param[in]   block   address of the allocated memory block to be returned to the memory pool.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMemoryPoolFree(osMemoryPoolId_t mp_id, void *block);

/**
 * @fn          uint32_t osMemoryPoolGetCapacity(osMemoryPoolId_t mp_id)
 * @brief       Get maximum number of memory blocks in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      maximum number of memory blocks or 0 in case of an error.
 */
uint32_t osMemoryPoolGetCapacity(osMemoryPoolId_t mp_id);

/**
 * @fn          uint32_t osMemoryPoolGetBlockSize(osMemoryPoolId_t mp_id)
 * @brief       Get memory block size in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      memory block size in bytes or 0 in case of an error.
 */
uint32_t osMemoryPoolGetBlockSize(osMemoryPoolId_t mp_id);

/**
 * @fn          uint32_t osMemoryPoolGetCount(osMemoryPoolId_t mp_id)
 * @brief       Get number of memory blocks used in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      number of memory blocks used or 0 in case of an error.
 */
uint32_t osMemoryPoolGetCount(osMemoryPoolId_t mp_id);

/**
 * @fn          uint32_t osMemoryPoolGetSpace(osMemoryPoolId_t mp_id)
 * @brief       Get number of memory blocks available in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      number of memory blocks available or 0 in case of an error.
 */
uint32_t osMemoryPoolGetSpace(osMemoryPoolId_t mp_id);

/**
 * @fn          osStatus_t osMemoryPoolDelete(osMemoryPoolId_t mp_id)
 * @brief       Delete a Memory Pool object.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMemoryPoolDelete(osMemoryPoolId_t mp_id);


/*******************************************************************************
 *  Mutex Management
 ******************************************************************************/

/**
 * @fn          osMutexId_t osMutexNew(const osMutexAttr_t *attr)
 * @brief       Create and Initialize a Mutex object.
 * @param[in]   attr  mutex attributes.
 * @return      mutex ID for reference by other functions or NULL in case of error.
 */
osMutexId_t osMutexNew(const osMutexAttr_t *attr);

/**
 * @fn          const char *osMutexGetName(osMutexId_t mutex_id)
 * @brief       Get name of a Mutex object.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osMutexGetName(osMutexId_t mutex_id);

/**
 * @fn          osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t timeout)
 * @brief       Acquire a Mutex or timeout if it is locked.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t timeout);

/**
 * @fn          osStatus_t osMutexRelease(osMutexId_t mutex_id)
 * @brief       Release a Mutex that was acquired by \ref osMutexAcquire.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMutexRelease(osMutexId_t mutex_id);

/**
 * @fn          osThreadId_t osMutexGetOwner(osMutexId_t mutex_id)
 * @brief       Get Thread which owns a Mutex object.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      thread ID of owner thread or NULL when mutex was not acquired.
 */
osThreadId_t osMutexGetOwner(osMutexId_t mutex_id);

/**
 * @fn          osStatus_t osMutexDelete(osMutexId_t mutex_id)
 * @brief       Delete a Mutex object.
 * @param[in]   mutex_id  mutex ID obtained by \ref osMutexNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMutexDelete(osMutexId_t mutex_id);

/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // _KERNEL_H_

/*------------------------------ End of file ---------------------------------*/
