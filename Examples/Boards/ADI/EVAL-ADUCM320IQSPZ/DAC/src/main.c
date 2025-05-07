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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>
#include <Kernel/kernel.h>
#include <asm/system_aducm32x.h>
#include <Driver/Driver_GPIO.h>
#include <Driver/Driver_VDAC.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (384U)
#define DAC_VREF                      (2510)
#define DAC_RESOLUTION                (12)
#define LED_PIN                       (GPIO_PIN_4)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t         thread_id;
static osThread_t           thread_cb;
static uint64_t             thread_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t thread_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &thread_cb,
    .cb_size    = sizeof(thread_cb),
    .stack_mem  = &thread_stack[0],
    .stack_size = sizeof(thread_stack),
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

extern Driver_GPIO_t Driver_GPIO2;
static Driver_GPIO_t *gpio_led = &Driver_GPIO2;

extern Driver_DAC_t Driver_DAC1;
static Driver_DAC_t *dac = &Driver_DAC1;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void GPIO_Init(void)
{
  const GPIO_PIN_CFG_t gpio_cfg = {
    .func = GPIO_PIN_FUNC_0,
    .mode = GPIO_MODE_OUT_PP,
    .pull = GPIO_PULL_DISABLE
  };

  gpio_led->PinConfig(LED_PIN, &gpio_cfg);
}

__NO_RETURN
static void main_proc(void *param)
{
  (void) param;
  uint16_t sample;

  GPIO_Init();

  osTimerStart(timer_id, TIMEOUT);

  dac->Initialize();
  dac->Control(DAC_CONFIGURE | DAC_DATA_BITS(DAC_RESOLUTION), 0U);
  dac->Control(DAC_CONTROL, 1U);

  sample = 0U;

  for (;;) {
    sample += 10U;
    dac->WriteSample(sample & ((1UL << DAC_RESOLUTION) - 1U));
    osDelay(1U);
  }
}

static void timer_proc(void *argument)
{
  (void) argument;

  gpio_led->PinToggle(LED_PIN);
}

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();

  status = osKernelInitialize();
  if (status == osOK) {
    thread_id = osThreadNew(main_proc, NULL, &thread_attr);
    if (thread_id == NULL) {
      goto error;
    }

    timer_id = osTimerNew(timer_proc, osTimerPeriodic, NULL, &timer_attr);
    if (timer_id == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
