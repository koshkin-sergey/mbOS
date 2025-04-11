/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <Kernel/tick.h>
#include <Core/Riscv/irq_riscv.h>
#include <asm/gd32vf103xx_systimer.h>

#if defined(__SYSTIMER_PRESENT) && (__SYSTIMER_PRESENT == 1)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static uint32_t ticks;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Set system timer load value
 * @details     This function set the system timer load value in MTIMER register.
 * @param [in]  value   value to set system timer MTIMER register.
 */
static
void SetLoadValue(uint64_t value)
{
  SysTimer->mtime_lo = 0UL;
  SysTimer->mtime_hi = (uint32_t)(value >> 32);
  SysTimer->mtime_lo = (uint32_t)value;
}

/**
 * @brief       Get system timer load value
 * @details     This function get the system timer current value in MTIMER register.
 * @return      current value (64bit) of system timer MTIMER register.
 */
static
uint64_t GetLoadValue(void)
{
  uint64_t value;
  uint32_t hi;
  uint32_t lo;

  hi = SysTimer->mtime_hi;
  lo = SysTimer->mtime_lo;
  value = SysTimer->mtime_hi;
  if (hi != value) {
    lo = SysTimer->mtime_lo;
  }

  return ((value << 32) | lo);
}

/**
 * @brief       Set system timer compare value in machine mode
 * @details     This function set the system Timer compare value in MTIMERCMP register.
 * @param [in]  value   compare value to set system timer MTIMERCMP register.
 */
static
void SetCompareValue(uint64_t value)
{
  SysTimer->mtimecmp_lo = -1U;
  SysTimer->mtimecmp_hi = (uint32_t)(value >> 32);
  SysTimer->mtimecmp_lo = (uint32_t)value;
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Setup OS Tick timer to generate periodic RTOS Kernel Ticks
 * @param[in]   freq      tick frequency in Hz
 * @param[in]   handler   tick IRQ handler
 * @return      0 on success, -1 on error.
 */
int32_t osTickSetup(uint32_t freq, IRQHandler_t handler)
{
  (void) handler;

  if (freq == 0U) {
    return (-1);
  }

  ticks = SystemCoreClock / (freq * 4U);

  SysTimer->mtimectl |= MTIMECTL_TIMESTOP;
  SetLoadValue(0U);
  SetCompareValue(ticks);

  /* Disable corresponding IRQ */
  IRQ_Disable(CLIC_INT_TMR);
  IRQ_ClearPending(CLIC_INT_TMR);

  /* Set Timer interrupt priority */
  IRQ_SetPriority(CLIC_INT_TMR, SYSTIMER_IRQ_PRIORITY);
  /* Enable corresponding interrupt */
  IRQ_Enable(CLIC_INT_TMR);

  return (0);
}

/**
 * @brief       Enable OS Tick timer interrupt
 */
void osTickEnable(void)
{
  SysTimer->mtimectl &= ~MTIMECTL_TIMESTOP;
}

/**
 * @brief       Disable OS Tick timer interrupt
 */
void osTickDisable(void)
{
  SysTimer->mtimectl |= MTIMECTL_TIMESTOP;
}

/**
 * @brief       Enable generation of RTOS Kernel Tick interrupts
 *              without changing the operating mode of the OS Tick timer
 */
void osTickEnableIRQ(void)
{
  IRQ_Enable(CLIC_INT_TMR);
}

/**
 * @brief       Disable generation of RTOS Kernel Tick interrupts
 *              without changing the operating mode of the OS Tick timer
 */
void osTickDisableIRQ(void)
{
  IRQ_Disable(CLIC_INT_TMR);
}

/**
 * @brief       Acknowledge execution of OS Tick timer interrupt
 */
void osTickAcknowledgeIRQ(void)
{
  uint64_t cur_ticks = GetLoadValue();
  uint64_t reload_ticks = ticks + cur_ticks;

  if (__USUALLY(reload_ticks > cur_ticks)) {
    SetCompareValue(reload_ticks);
  }
  else {
    /* When added the ticks value, then the MTIMERCMP < TIMER,
     * which means the MTIMERCMP is overflowed,
     * so we need to reset the counter to zero */
    SetLoadValue(0);
    SetCompareValue(ticks);
  }
}

/**
 * @brief       Get OS Tick timer clock frequency
 * @return      OS Tick timer clock frequency in Hz
 */
uint32_t osTickGetClock(void)
{
  return (SystemCoreClock / 4U);
}

/**
 * @brief       Get OS Tick timer interval reload value
 * @return      OS Tick timer interval reload value
 */
uint32_t osTickGetInterval(void)
{
  return (ticks);
}

/**
 * @brief       Get OS Tick timer counter value
 * @details     Return the current value of the OS Tick counter: 0 ... (reload value -1).
 *              The reload value is returned by the function osTickGetInterval.
 * @return      OS Tick timer counter value
 */
uint32_t osTickGetCount(void)
{
  return (SysTimer->mtime_lo % ticks);
}

/**
 * @brief       Get OS Tick timer overflow status
 * @return      OS Tick overflow status (1 - overflow, 0 - no overflow).
 */
uint32_t osTickGetOverflow(void)
{
  return (IRQ_GetPending(CLIC_INT_TMR));
}

#endif /* defined(__SYSTIMER_PRESENT) && (__SYSTIMER_PRESENT == 1) */
