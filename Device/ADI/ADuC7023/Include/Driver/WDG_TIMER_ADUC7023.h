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

#ifndef WDG_TIMER_ADUC7023_H_
#define WDG_TIMER_ADUC7023_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/aduc7023.h>
#include <device_config.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* WDG configuration definitions */
#if defined (DEV_WDG) && (DEV_WDG == 1)
  #define USE_WDG

  #if !defined(TIM2)
    #error "Watchdog timer not available for selected device!"
    #undef USE_WDG
  #endif

#if   (DEV_WDG_CLK == 0)
  #define WDG_CLK_PRESCALE          TIMER2_CON_CLKDIV_1
#elif (DEV_WDG_CLK == 1)
  #define WDG_CLK_PRESCALE          TIMER2_CON_CLKDIV_16
#elif (DEV_WDG_CLK == 2)
  #define WDG_CLK_PRESCALE          TIMER2_CON_CLKDIV_256
#else
  #error "WDG prescaler selection error!"
#endif

#endif

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * Function documentation
 *
 * @fn          int32_t WDG_Initialize(uint16_t cnt)
 * @brief       Initialize and start Watchdog Timer.
 * @param[in]   cnt  Value that is loaded into the counter.
 *
 * @fn          int32_t WDG_Reload(void)
 * @brief       Reload Watchdog Timer.
 */

/**
 * @brief Access structure of the WDG Driver.
 */
typedef struct Driver_WDG {
  void (*Initialize) (uint16_t cnt);
  void (*Reload)     (void);
} const Driver_WDG_t;

#endif /* WDG_TIMER_ADUC7023_H_ */
