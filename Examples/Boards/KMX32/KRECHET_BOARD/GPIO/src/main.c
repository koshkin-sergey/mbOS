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

#include <asm/krechet1.h>

#define LED0_R                    (1UL << 24U)
#define LED0_G                    (1UL << 25U)
#define LED0_B                    (1UL << 26U)
#define LED1_R                    (1UL << 27U)
#define LED1_G                    (1UL << 28U)
#define LED1_B                    (1UL << 29U)

static void GPIO_Init(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_GATE_REG, __get_PeriphReg(ADSU_GATE_REG) | 0x00010000);

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_DIR_REG, LED0_R | LED0_B | LED1_R | LED1_B);
  __set_PeriphReg(GPIO_OUT_REG, LED0_R | LED1_B);
}

static void GPIO_PinToggle(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_OUT_REG, __get_PeriphReg(GPIO_OUT_REG) ^ (LED0_R | LED0_B | LED1_R | LED1_B));
}

int main(void)
{
  volatile uint32_t i;

  GPIO_Init();

  for (;;) {
      i = 100000U;
      while (--i);
      GPIO_PinToggle();
  }

  return (-1);
}
