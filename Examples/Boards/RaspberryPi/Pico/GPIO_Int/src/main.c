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
#include <Driver/Driver_GPIO.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define LED_PIN                       (25U)
#define BTN_PIN                       (1U)

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

extern DRIVER_GPIO Driver_GPIO;
static DRIVER_GPIO *gpio = &Driver_GPIO;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void GPIO_SignalEvent(GPIO_Pin_t pin, uint32_t event)
{
  if (pin == BTN_PIN) {
    if ((event & GPIO_EVENT_LOW_LEVEL) != 0U) {
      gpio->SetEventTrigger(BTN_PIN, GPIO_TRIGGER_HIGH_LEVEL);
      gpio->SetOutput(LED_PIN, 1U);
    }
    else if ((event & GPIO_EVENT_HIGH_LEVEL) != 0U) {
      gpio->SetEventTrigger(BTN_PIN, GPIO_TRIGGER_LOW_LEVEL);
      gpio->SetOutput(LED_PIN, 0U);
    }
  }
}

static void init_proc(void *param)
{
  (void) param;

  gpio->Setup(LED_PIN, NULL);
  gpio->SetDirection(LED_PIN, GPIO_OUTPUT);

  gpio->Setup(BTN_PIN, GPIO_SignalEvent);
  gpio->SetDirection(BTN_PIN, GPIO_INPUT);
  gpio->SetPullResistor(BTN_PIN, GPIO_PULL_UP);
  gpio->SetEventTrigger(BTN_PIN, GPIO_TRIGGER_LOW_LEVEL);
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

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
