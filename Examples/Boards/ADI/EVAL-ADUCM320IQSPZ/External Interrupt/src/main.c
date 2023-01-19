/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include <Kernel/kernel.h>
#include <asm/system_aducm32x.h>
#include <Driver/GPIO_ADUCM32x.h>
#include <Driver/EXTI_ADUCM32x.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STACK_SIZE             (256U)
#define LED_PIN                       (GPIO_PIN_4)

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

static Driver_GPIO_t *gpio = &Driver_GPIO2;
static Driver_EXTI_t *exti = &Driver_EXTI0;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void GPIO_Init(void)
{
  const GPIO_PIN_CFG_t led_cfg = {
    .func = GPIO_PIN_FUNC_0,
    .mode = GPIO_MODE_OUT_PP,
    .pull = GPIO_PULL_DISABLE
  };

  gpio->PinConfig(LED_PIN, &led_cfg);
  gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_HIGH);
}

static void EXTI_Callback(uint32_t event)
{
  uint32_t control;

  if (event == EXTI_EVENT_LOW_LEVEL) {
    gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_LOW);
    control = EXTI_MODE_ACTIVE | EXTI_TRG_HIGH_LEVEL;
  }
  else {
    gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_HIGH);
    control = EXTI_MODE_ACTIVE | EXTI_TRG_LOW_LEVEL;
  }

  exti->Control(control);
}

static void init_proc(void *param)
{
  (void) param;

  GPIO_Init();
  exti->Initialize(EXTI_Callback);
  exti->Control(EXTI_MODE_ACTIVE | EXTI_TRG_LOW_LEVEL);
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

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
