/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Title:   uKernel Configuration definitions
 */

#ifndef _RTOS_CONFIG_H_
#define _RTOS_CONFIG_H_

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h>System Configuration
// =======================

//   <o>Kernel Tick Frequency [Hz] <1-1000000>
//   <i> Defines base time unit for delays and timeouts.
//   <i> Default: 1000 (1ms tick)
#ifndef OS_TICK_FREQ
#define OS_TICK_FREQ                1000
#endif

//   <e>Round-Robin Thread switching
//   <i> Enables Round-Robin Thread switching.
#ifndef OS_ROBIN_ENABLE
#define OS_ROBIN_ENABLE             0
#endif

//     <o>Round-Robin Timeout <1-1000>
//     <i> Defines how many ticks a thread will execute before a thread switch.
//     <i> Default: 5
#ifndef OS_ROBIN_TIMEOUT
#define OS_ROBIN_TIMEOUT            5
#endif

//   </e>

//   <o>Maximum priority of interrupts <1-255>
//   <i> Defines the maximum priority of interrupts from which ISR safe API functions can be called.
//   <i> Should be always greater than 0.
#ifndef MAX_API_INT_PRIO
#define MAX_API_INT_PRIO            1
#endif

// </h>

// <h>Thread Configuration
// =======================

//   <o>Default Thread Stack size [bytes] <96-1073741824:8>
//   <i> Defines stack size for threads with zero stack size specified.
//   <i> Default: 256
#ifndef OS_STACK_SIZE
#define OS_STACK_SIZE               256
#endif

//   <o>Idle Thread Stack size [bytes] <72-1073741824:8>
//   <i> Defines stack size for Idle thread.
//   <i> Default: 256
#ifndef OS_IDLE_THREAD_STACK_SIZE
#define OS_IDLE_THREAD_STACK_SIZE   256
#endif

//   <o>Idle Thread TrustZone Module Identifier
//   <i> Defines TrustZone Thread Context Management Identifier.
//   <i> Applies only to cores with TrustZone technology.
//   <i> Default: 0 (not used)
#ifndef OS_IDLE_THREAD_TZ_MOD_ID
#define OS_IDLE_THREAD_TZ_MOD_ID    0
#endif

//   <q>Stack overrun checking
//   <i> Enables stack overrun check at thread switch.
//   <i> Enabling this option increases slightly the execution time of a thread switch.
#ifndef OS_STACK_CHECK
#define OS_STACK_CHECK              0
#endif

//   <q>Stack usage watermark
//   <i> Initializes thread stack with watermark pattern for analyzing stack usage.
//   <i> Enabling this option increases significantly the execution time of thread creation.
#ifndef OS_STACK_WATERMARK
#define OS_STACK_WATERMARK          0
#endif

//   <o>Processor mode for Thread execution
//     <0=> Unprivileged mode
//     <1=> Privileged mode
//   <i> Default: Privileged mode
#ifndef OS_PRIVILEGE_MODE
#define OS_PRIVILEGE_MODE           1
#endif

// </h>

// <h>Timer Configuration
// ======================

//   <o>Timer Thread Priority
//      <2=> Low <7=> Below Normal  <12=> Normal  <17=> Above Normal <22=> High <27=> Realtime
//   <i> Defines priority for timer thread
//   <i> Default: High
#ifndef OS_TIMER_THREAD_PRIO
#define OS_TIMER_THREAD_PRIO        22
#endif

//   <o>Timer Thread Stack size [bytes] <0-1073741824:8>
//   <i> Defines stack size for Timer thread.
//   <i> Default: 256
#ifndef OS_TIMER_THREAD_STACK_SIZE
#define OS_TIMER_THREAD_STACK_SIZE  256
#endif

//   <o>Timer Thread TrustZone Module Identifier
//   <i> Defines TrustZone Thread Context Management Identifier.
//   <i> Applies only to cores with TrustZone technology.
//   <i> Default: 0 (not used)
#ifndef OS_TIMER_THREAD_TZ_MOD_ID
#define OS_TIMER_THREAD_TZ_MOD_ID   0
#endif

// </h>

//------------- <<< end of configuration section >>> ---------------------------

#endif  /* _RTOS_CONFIG_H_ */

/* ----------------------------- End of file ---------------------------------*/
