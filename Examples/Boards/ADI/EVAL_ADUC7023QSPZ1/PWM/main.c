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

#include "asm/system_aduc7023.h"
#include "Driver/GPIO_ADUC7023.h"
#include "Driver/PWM_ADUC7023.h"
#include "Kernel/kernel.h"

#define TIMEOUT                       (250UL)
#define THREAD_STACK_SIZE             (256U)

#define PWM_LENGTH                    (20900U)

extern Driver_PWM_t Driver_PWM;

static Driver_PWM_t *pwm = &Driver_PWM;

static osThreadId_t         thread;
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

static void SetDuty(float duty)
{
  pwm->Control(PWM_CONFIGURE | PWM0_COMPARE0, 0U);
  pwm->Control(PWM_CONFIGURE | PWM0_COMPARE1, PWM_LENGTH / 100UL * duty);
}

__NO_RETURN
static void thread_func(void *param)
{
  (void) param;
  float  duty = 0.f;

  const GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_OUTPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  DRIVER_GPIO0.PinConfig(GPIO_PIN_7, &pin_cfg);

  pwm->Initialize();
  pwm->PowerControl(PWM_POWER_FULL);
  pwm->Control(PWM_CONFIGURE | PWM0_LENGTH, PWM_LENGTH);
  pwm->Control(PWM_CONTROL, 1U);

  for (;;) {
    DRIVER_GPIO0.PinToggle(GPIO_PIN_7);

    SetDuty(duty);
    ++duty;
    if (duty > 100.f) {
      duty = 0.f;
    }

    osDelay(500);
  }
}

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();

  status = osKernelInitialize();
  if (status == osOK) {
    thread = osThreadNew(thread_func, NULL, &thread_attr);
    if (thread == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
