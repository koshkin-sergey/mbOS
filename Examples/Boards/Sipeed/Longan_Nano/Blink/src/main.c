/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include <asm/system_gd32vf1xx.h>
#include <Driver/GPIO_GD32VF1xx.h>
#include <Kernel/kernel.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (256U)

#define LED_GREEN_PIN                 (GPIO_PIN_1)
#define LED_BLUE_PIN                  (GPIO_PIN_2)

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

static osTimerId_t         timer_id;
static osTimer_t           timer_cb;
static const osTimerAttr_t timer_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer_cb,
    .cb_size   = sizeof(timer_cb)
};

static Driver_GPIO_t *gpio = &Driver_GPIOA;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void GPIO_Init(void)
{
  gpio->Initialize();
  gpio->PinConfig(LED_GREEN_PIN, 0U);
  gpio->PinConfig(LED_BLUE_PIN,  0U);
  gpio->PinWrite(LED_GREEN_PIN, GPIO_PIN_OUT_LOW);
  gpio->PinWrite(LED_BLUE_PIN,  GPIO_PIN_OUT_LOW);
}

static void init_proc(void *param)
{
  (void) param;

  GPIO_Init();

  osTimerStart(timer_id, TIMEOUT);

  for (;;) {
    gpio->PinToggle(LED_BLUE_PIN);
    osDelay(TIMEOUT);
  }
}

static void timer_func(void *argument)
{
  (void) argument;

  gpio->PinToggle(LED_GREEN_PIN);
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
