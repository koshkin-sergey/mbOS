/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include "kernel_lib.h"

#ifdef  SysTick

#ifndef SYSTICK_IRQ_PRIORITY
#define SYSTICK_IRQ_PRIORITY    0xFFU
#endif

static uint8_t PendST;

/**
 * @brief       Setup OS Tick timer to generate periodic RTOS Kernel Ticks
 * @param[in]   freq      tick frequency in Hz
 * @param[in]   handler   tick IRQ handler
 * @return      0 on success, -1 on error.
 */
__WEAK int32_t osTickSetup(uint32_t freq, IRQHandler_t handler)
{
  uint32_t load;
  (void)handler;

  if (freq == 0U) {
    return (-1);
  }

  load = (SystemCoreClock / freq) - 1U;
  if (load > 0x00FFFFFFU) {
    return (-1);
  }

  /* Set SysTick Interrupt Priority */
#if   ((defined(__ARM_ARCH_8M_MAIN__)   && (__ARM_ARCH_8M_MAIN__   != 0)) || \
       (defined(__ARM_ARCH_8_1M_MAIN__) && (__ARM_ARCH_8_1M_MAIN__ != 0)) || \
       (defined(__CORTEX_M)             && (__CORTEX_M             == 7U)))
  SCB->SHPR[11] = SYSTICK_IRQ_PRIORITY;
#elif  (defined(__ARM_ARCH_8M_BASE__)   && (__ARM_ARCH_8M_BASE__   != 0))
  SCB->SHPR[1] |= ((uint32_t)SYSTICK_IRQ_PRIORITY << 24);
#elif ((defined(__ARM_ARCH_7M__)        && (__ARM_ARCH_7M__        != 0)) || \
       (defined(__ARM_ARCH_7EM__)       && (__ARM_ARCH_7EM__       != 0)))
  SCB->SHP[11]  = SYSTICK_IRQ_PRIORITY;
#elif  (defined(__ARM_ARCH_6M__)        && (__ARM_ARCH_6M__        != 0))
  SCB->SHP[1]  |= ((uint32_t)SYSTICK_IRQ_PRIORITY << 24);
#else
#error "Unknown ARM Core!"
#endif

  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
  SysTick->LOAD = load;
  SysTick->VAL  = 0U;

  PendST = 0U;

  return (0);
}

/**
 * @brief       Enable OS Tick timer interrupt
 */
__WEAK void osTickEnable(void)
{
  if (PendST != 0U) {
    PendST = 0U;
    SCB->ICSR = SCB_ICSR_PENDSTSET_Msk;
  }

  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief       Disable OS Tick timer interrupt
 */
__WEAK void osTickDisable(void)
{
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

  if ((SCB->ICSR & SCB_ICSR_PENDSTSET_Msk) != 0U) {
    SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
    PendST = 1U;
  }
}

/**
 * @brief       Acknowledge execution of OS Tick timer interrupt
 */
__WEAK void osTickAcknowledgeIRQ(void)
{
  (void)SysTick->CTRL;
}

/**
 * @brief       Get OS Tick timer clock frequency
 * @return      OS Tick timer clock frequency in Hz
 */
__WEAK uint32_t osTickGetClock(void)
{
  return (SystemCoreClock);
}

/**
 * @brief       Get OS Tick timer interval reload value
 * @return      OS Tick timer interval reload value
 */
__WEAK uint32_t osTickGetInterval(void)
{
  return (SysTick->LOAD + 1U);
}

/**
 * @brief       Get OS Tick timer counter value
 * @return      OS Tick timer counter value
 */
__WEAK uint32_t osTickGetCount(void)
{
  uint32_t load = SysTick->LOAD;
  return  (load - SysTick->VAL);
}

/**
 * @brief       Get OS Tick timer overflow status
 * @return      OS Tick overflow status (1 - overflow, 0 - no overflow).
 */
__WEAK uint32_t osTickGetOverflow(void)
{
  return ((SysTick->CTRL >> 16) & 1U);
}

#endif  /* SysTick */
