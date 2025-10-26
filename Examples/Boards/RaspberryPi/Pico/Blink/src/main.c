/*
 * Copyright (C) 2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <stddef.h>
#include <asm/system_rp2040.h>
#include <Kernel/kernel.h>
#include "BSP.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (256U)
#define THREAD_PRIORITY               osPriorityNormal

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t init_id;
static osThread_t   init_cb;
static uint64_t     init_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t init_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &init_cb,
    .cb_size    = sizeof(init_cb),
    .stack_mem  = &init_stack[0],
    .stack_size = sizeof(init_stack),
    .priority   = THREAD_PRIORITY,
};

static osTimerId_t         timer_id;
static osTimer_t           timer_cb;
static const osTimerAttr_t timer_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer_cb,
    .cb_size   = sizeof(timer_cb)
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void init_proc(void *param)
{
  (void) param;

  BSP_Init();

  osTimerStart(timer_id, TIMEOUT);
}

static void timer_func(void *argument)
{
  (void) argument;

  BSP_ToggleLED(0);  // Toggles LED Pin
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();

  status = osKernelInitialize();
  if (status == osOK) {
    init_id = osThreadNew(init_proc, NULL, &init_attr);
    if (init_id == NULL) {
        goto error;
    }

    timer_id = osTimerNew(timer_func, osTimerPeriodic, NULL, &timer_attr);
    if (timer_id == NULL) {
        goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
