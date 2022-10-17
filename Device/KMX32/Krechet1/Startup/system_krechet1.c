/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <Driver/ADSU_KRECHET1.h>

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

/*!< System Clock Frequency (Core Clock)  */
uint32_t SystemCoreClock = 12000000U;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

extern Driver_ADSU_t Driver_ADSU;

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Update SystemCoreClock variable.
 */
void SystemCoreClockUpdate(void)
{
  SystemCoreClock = Driver_ADSU.GetFrequency(ADSU_FREQ_SYS);
}

/**
 * @brief       Initialize the System.
 */
void SystemInit(void)
{
  const Driver_ADSU_t *adsu = &Driver_ADSU;

  static const ADSU_ClkCfg_t clk_cfg = {
    .clk_src      = ADSU_OSC_XT,
    .clk_div      = ADSU_CLK_DIV_1,
    .clk_out      = ADSU_CLK_OUT_DISABLE,
    .flash_delay  = 0U
  };

  adsu->ClkReset();
  adsu->OscConfig(ADSU_OSC_XT, ADSU_OSC_ENABLE);
  adsu->ClkConfig(&clk_cfg);
}
