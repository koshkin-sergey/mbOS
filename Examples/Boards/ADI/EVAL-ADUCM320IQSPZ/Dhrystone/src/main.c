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

#include "dhry.h"
#include <asm/system_aducm32x.h>
#include <Driver/Driver_GPIO.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define LED_PIN                       (GPIO_PIN_4)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

extern Driver_GPIO_t Driver_GPIO2;
static Driver_GPIO_t *gpio = &Driver_GPIO2;

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
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

int main(void)
{
  SystemCoreClockUpdate();
  GPIO_Init();
  scope_clr();

  dhrystone();

  for (;;);
}

void scope_set(void)
{
  gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_LOW);
}

void scope_clr(void)
{
  gpio->PinWrite(LED_PIN, GPIO_PIN_OUT_HIGH);
}
