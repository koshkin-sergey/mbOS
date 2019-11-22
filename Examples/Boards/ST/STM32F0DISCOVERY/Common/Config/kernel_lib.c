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
 * Project: mbOS real-time kernel
 * Title:   Kernel Library Configuration
 */

#include "Kernel/kernel.h"
#include "kernel_config.h"

/* Idle Thread Control Block */
static osThread_t os_idle_thread_cb __attribute__((section(".bss.os.thread.cb")));

/* Idle Thread Stack */
static uint64_t os_idle_thread_stack[OS_IDLE_THREAD_STACK_SIZE/8] __attribute__((section(".bss.os.thread.stack")));

/* Idle Thread Attributes */
static const osThreadAttr_t os_idle_thread_attr = {
#if defined(OS_IDLE_THREAD_NAME)
  OS_IDLE_THREAD_NAME,
#else
  NULL,
#endif
  osThreadDetached,
  &os_idle_thread_cb,
  (uint32_t)sizeof(os_idle_thread_cb),
  &os_idle_thread_stack[0],
  (uint32_t)sizeof(os_idle_thread_stack),
  osPriorityIdle,
#if defined(OS_IDLE_THREAD_TZ_MOD_ID)
  (uint32_t)OS_IDLE_THREAD_TZ_MOD_ID,
#else
  0U,
#endif
  0U
};

/* Timer Thread Control Block */
static osThread_t os_timer_thread_cb __attribute__((section(".bss.os.thread.cb")));

/* Timer Thread Stack */
static uint64_t os_timer_thread_stack[OS_TIMER_THREAD_STACK_SIZE/8] __attribute__((section(".bss.os.thread.stack")));

/* Timer Thread Attributes */
static const osThreadAttr_t os_timer_thread_attr = {
#if defined(OS_TIMER_THREAD_NAME)
  OS_TIMER_THREAD_NAME,
#else
  NULL,
#endif
  osThreadDetached,
  &os_timer_thread_cb,
  (uint32_t)sizeof(os_timer_thread_cb),
  &os_timer_thread_stack[0],
  (uint32_t)sizeof(os_timer_thread_stack),
  osPriorityISR,
#if defined(OS_TIMER_THREAD_TZ_MOD_ID)
  (uint32_t)OS_TIMER_THREAD_TZ_MOD_ID,
#else
  0U,
#endif
  0U
};

/* Timer Semaphore Control Block */
static osSemaphore_t os_timer_semaphore_cb __attribute__((section(".bss.os.semaphore.cb")));

/* Timer Semaphore Attributes */
static const osSemaphoreAttr_t os_timer_semaphore_attr = {
  NULL,
  0U,
  &os_timer_semaphore_cb,
  (uint32_t)sizeof(os_timer_semaphore_cb)
};

const osConfig_t osConfig __USED __attribute__((section(".rodata"))) = {
  0U     // Flags
#if (OS_PRIVILEGE_MODE != 0)
  | osConfigPrivilegedMode
#endif
#if (OS_STACK_CHECK != 0)
  | osConfigStackCheck
#endif
#if (OS_STACK_WATERMARK != 0)
  | osConfigStackWatermark
#endif
  ,
  (uint32_t)OS_TICK_FREQ,
#if (OS_ROBIN_ENABLE != 0)
  (uint32_t)OS_ROBIN_TIMEOUT,
#else
  0U,
#endif
  (uint32_t)MAX_API_INT_PRIO,
  &os_idle_thread_attr,
  &os_timer_thread_attr,
  &os_timer_semaphore_attr
};

/* Non weak reference to library irq module */
extern       uint8_t  irqLib;
extern const uint8_t *irqLibRef;
       const uint8_t *irqLibRef = &irqLib;

/* ----------------------------- End of file ---------------------------------*/
