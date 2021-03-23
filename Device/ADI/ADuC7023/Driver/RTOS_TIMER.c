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

#include "Kernel/tick.h"
#include "Kernel/irq.h"
#include "asm/aduc7023.h"
#include "asm/system_aduc7023.h"

#define RTIM_IRQ_PRIORITY           0xFFU

/**
 * @brief       Setup OS Tick timer to generate periodic RTOS Kernel Ticks
 * @param[in]   freq      tick frequency in Hz
 * @param[in]   handler   tick IRQ handler
 * @return      0 on success, -1 on error.
 */
int32_t osTickSetup(uint32_t freq, IRQHandler_t handler)
{
  uint32_t load;

  if (freq == 0U) {
    return (-1);
  }

  load = SystemCoreClock / freq;
  if (load > 0xFFFFUL) {
    return (-1);
  }

  /* Set periodic mode and disable Timer */
  RTOS_TIMER->CON = RTOS_TIMER_CON_MODE;
  /* Set load value */
  RTOS_TIMER->LD = (uint16_t)load;

  /* Disable corresponding IRQ */
  IRQ_Disable     (RTOS_TIMER_IRQn);
  IRQ_ClearPending(RTOS_TIMER_IRQn);

  /* Set Timer interrupt priority */
  IRQ_SetPriority(RTOS_TIMER_IRQn, RTIM_IRQ_PRIORITY);
  /* Register tick interrupt handler function */
  IRQ_SetHandler(RTOS_TIMER_IRQn, handler);
  /* Enable corresponding interrupt */
  IRQ_Enable(RTOS_TIMER_IRQn);

  return (0);
}

/**
 * @brief       Enable OS Tick timer interrupt
 */
void osTickEnable(void)
{
  RTOS_TIMER->CON |= RTOS_TIMER_CON_EN;
}

/**
 * @brief       Disable OS Tick timer interrupt
 */
void osTickDisable(void)
{
  RTOS_TIMER->CON &= ~RTOS_TIMER_CON_EN;
}

/**
 * @brief       Acknowledge execution of OS Tick timer interrupt
 */
void osTickAcknowledgeIRQ(void)
{
  RTOS_TIMER->CLRI = 0U;
}

/**
 * @brief       Get OS Tick timer IRQ number
 * @return      OS Tick IRQ number
 */
int32_t osTickGetIRQn(void)
{

}

/**
 * @brief       Get OS Tick timer clock frequency
 * @return      OS Tick timer clock frequency in Hz
 */
uint32_t osTickGetClock(void)
{
  return (SystemCoreClock);
}

/**
 * @brief       Get OS Tick timer interval reload value
 * @return      OS Tick timer interval reload value
 */
uint32_t osTickGetInterval(void)
{

}

/**
 * @brief       Get OS Tick timer counter value
 * @return      OS Tick timer counter value
 */
uint32_t osTickGetCount(void)
{
  return (RTOS_TIMER->VAL);
}

/**
 * @brief       Get OS Tick timer overflow status
 * @return      OS Tick overflow status (1 - overflow, 0 - no overflow).
 */
uint32_t osTickGetOverflow(void)
{

}
