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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "Driver/WDG_TIMER_ADUC7023.h"

#if defined(USE_WDG)

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Initialize and start Watchdog Timer.
 * @param[in]   cnt  Value that is loaded into the counter.
 */
static void WDG_Initialize(uint16_t cnt)
{
  TIMER2_t *reg = TIM2;

  reg->LD  = cnt;
  reg->CON = WDG_CLK_PRESCALE    |
             TIMER2_CON_WDGMODE  |
             TIMER2_CON_PER_MODE |
             TIMER2_CON_ENABLE;
}

/**
 * @brief       Reload Watchdog Timer.
 */
static void WDG_Reload(void)
{
  TIMER2_t *reg = TIM2;

  reg->CLRI = 0xFFU;
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

Driver_WDG_t Driver_WDG = {
  WDG_Initialize,
  WDG_Reload,
};

#endif /* defined(USE_WDG) */
