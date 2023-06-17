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
#include <Driver/Driver_Flash.h>

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

extern ARM_DRIVER_FLASH ARM_Driver_Flash_(0);

static ARM_DRIVER_FLASH *flash = &ARM_Driver_Flash_(0);
static Driver_GPIO_t    *gpio  = &Driver_GPIO2;
static Driver_EXTI_t    *exti  = &Driver_EXTI0;

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
  if (event == EXTI_EVENT_FALLING_EDGE) {
    gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_LOW);
#if 0
    flash->EraseSector(0x2000UL);
#else
    static const uint8_t test[24] = "Test1234Dead5678DeadBeaf";
    flash->ProgramData(0x2000UL, &test[0], sizeof(test)/sizeof(uint64_t));
#endif
  }
}

static void FLASH_Callback(uint32_t event)
{
  if (event & ARM_FLASH_EVENT_READY) {
    gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_HIGH);
  }
}

static void init_proc(void *param)
{
  (void) param;

  GPIO_Init();

  flash->Initialize(FLASH_Callback);
  flash->PowerControl(ARM_POWER_FULL);

  exti->Initialize(EXTI_Callback);
  exti->Control(EXTI_MODE_ACTIVE | EXTI_TRG_FALLING_EDGE);
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
