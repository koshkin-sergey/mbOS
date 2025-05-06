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

#include "dhry.h"
#include <asm/system_aduc7023.h>
#include <Driver/GPIO_ADUC7023.h>

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
  DRIVER_GPIO0.PinWrite(GPIO_PIN_7, GPIO_PIN_OUT_LOW);
}

void scope_clr(void)
{
  DRIVER_GPIO0.PinWrite(GPIO_PIN_7, GPIO_PIN_OUT_HIGH);
}
