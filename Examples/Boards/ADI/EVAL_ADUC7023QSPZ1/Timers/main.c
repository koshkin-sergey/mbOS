/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include "asm/Driver_GPIO.h"
#include "Kernel/kernel.h"

#define TIMEOUT                       (250UL)
#define THREAD_STACK_SIZE             (256U)

static osThreadId_t         threadA;
static osThread_t           threadA_cb;
static uint64_t             threadA_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t threadA_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &threadA_cb,
    .cb_size    = sizeof(threadA_cb),
    .stack_mem  = &threadA_stack[0],
    .stack_size = sizeof(threadA_stack),
    .priority   = osPriorityNormal,
};

__NO_RETURN
static void threadA_func(void *param)
{
  (void) param;

  const GPIO_PIN_CFG_t pin_cfg = {
    .mode      = GPIO_MODE_OUTPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  DRIVER_GPIO0.PinConfig(GPIO_PIN_7, &pin_cfg);

  for (;;) {
    DRIVER_GPIO0.PinToggle(GPIO_PIN_7);
    osDelay(500);
  }
}

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();

  status = osKernelInitialize();
  if (status == osOK) {
    threadA = osThreadNew(threadA_func, NULL, &threadA_attr);
    if (threadA == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
