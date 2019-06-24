/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
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
 *
 * Project: uKernel real-time kernel
 * Title:   uKernel Configuration
 */

#include "RCC_STM32F4xx.h"
#include "ukernel.h"

/* OS Idle Thread */
__NO_RETURN
void osIdleThread(void *argument)
{
  (void) argument;

  for (;;) {
    /* Wait for interrupt */
    __WFI();
  }
}

/* SysTick timer initialization */
void osSysTickInit(uint32_t hz)
{
  uint32_t hclk = RCC_GetFreq(RCC_FREQ_AHB);

  SysTick_Config(hclk/hz);
}

/* ----------------------------- End of file ---------------------------------*/
