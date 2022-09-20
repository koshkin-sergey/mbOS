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


#include <stddef.h>
#include "asm/system_aduc7023.h"
#include "Driver/GPIO_ADUC7023.h"
#include "Kernel/kernel.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (250UL)
#define THREAD_STACK_SIZE             (256U)

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
    .priority   = osPriorityNormal,
};

static osTimerId_t         timer1;
static osTimer_t           timer1_cb;
static const osTimerAttr_t timer1_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer1_cb,
    .cb_size   = sizeof(timer1_cb)
};

static osTimerId_t         timer2;
static osTimer_t           timer2_cb;
static const osTimerAttr_t timer2_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer2_cb,
    .cb_size   = sizeof(timer2_cb)
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void GPIO_Init(void)
{
  const GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_OUTPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  DRIVER_GPIO0.PinConfig(GPIO_PIN_7, &pin_cfg);
}

static void init_proc(void *param)
{
  (void) param;

  GPIO_Init();

  osTimerStart(timer1, TIMEOUT);
  osTimerStart(timer2, TIMEOUT / 4U);
}

static void timer1_func(void *argument)
{
  (void) argument;

  DRIVER_GPIO0.PinWrite(GPIO_PIN_7, GPIO_PIN_OUT_LOW);
}

static void timer2_func(void *argument)
{
  (void) argument;

  DRIVER_GPIO0.PinWrite(GPIO_PIN_7, GPIO_PIN_OUT_HIGH);
}

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

    timer1 = osTimerNew(timer1_func, osTimerPeriodic, NULL, &timer1_attr);
    if (timer1 == NULL) {
        goto error;
    }

    timer2 = osTimerNew(timer2_func, osTimerPeriodic, NULL, &timer2_attr);
    if (timer2 == NULL) {
        goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
