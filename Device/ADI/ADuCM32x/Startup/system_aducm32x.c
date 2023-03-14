/*
 * Copyright (C) 2022-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/system_aducm32x.h>

#include <Driver/CLK_ADUCM32x.h>
#include <Driver/WDT_ADUCM32x.h>

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

uint32_t SystemCoreClock;           /*!< System Clock Frequency (Core Clock)  */

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Update SystemCoreClock variable.
 */
void SystemCoreClockUpdate(void)
{
  Driver_CLK_t *clk = &Driver_CLK;

  SystemCoreClock = clk->GetFrequency(CLK_FREQ_HCLK);
}

/**
 * @brief       Initialize the System.
 */
void SystemInit(void)
{
  Driver_CLK_t *clk = &Driver_CLK;
  Driver_WDT_t *wdt = &Driver_WDT;

  wdt->Disable();
  clk->ClkReset();
}
