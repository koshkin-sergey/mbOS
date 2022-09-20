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

#include "Kernel/tick.h"
//#include "Kernel/irq.h"
#include "asm/krechet1.h"

/**
 * @brief       Setup OS Tick timer to generate periodic RTOS Kernel Ticks
 * @param[in]   freq      tick frequency in Hz
 * @param[in]   handler   tick IRQ handler
 * @return      0 on success, -1 on error.
 */
int32_t osTickSetup(uint32_t freq, IRQHandler_t handler)
{
  (void)   handler;
  uint32_t load;

  if (freq == 0U) {
    return (-1);
  }

  load = SystemCoreClock / freq;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_GATE_REG, __get_PeriphReg(ADSU_GATE_REG) | (1UL << 12));
  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  __set_PeriphReg(TMR0_CFG_REG, TIM_CFG_IE);
  __set_PeriphReg(TMR0_RANGE_REG, load - 1);

  return (0);
}

/**
 * @brief       Enable OS Tick timer interrupt
 */
void osTickEnable(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  __set_PeriphReg(TMR0_CON_REG, __get_PeriphReg(TMR0_CON_REG) | TIM_CON_ST);
}

/**
 * @brief       Disable OS Tick timer interrupt
 */
void osTickDisable(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  __set_PeriphReg(TMR0_CON_REG, __get_PeriphReg(TMR0_CON_REG) & ~TIM_CON_ST);
}

/**
 * @brief       Enable generation of RTOS Kernel Tick interrupts
 *              without changing the operating mode of the OS Tick timer
 */
void osTickEnableIRQ(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  __set_PeriphReg(TMR0_CFG_REG, __get_PeriphReg(TMR0_CFG_REG) | TIM_CFG_IE);
}

/**
 * @brief       Disable generation of RTOS Kernel Tick interrupts
 *              without changing the operating mode of the OS Tick timer
 */
void osTickDisableIRQ(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  __set_PeriphReg(TMR0_CFG_REG, __get_PeriphReg(TMR0_CFG_REG) & ~TIM_CFG_IE);
}

/**
 * @brief       Acknowledge execution of OS Tick timer interrupt
 */
void osTickAcknowledgeIRQ(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  __set_PeriphReg(TMR0_CON_REG, __get_PeriphReg(TMR0_CON_REG));
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
  uint32_t interval;

  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  interval = __get_PeriphReg(TMR0_RANGE_REG);
  if (interval != 0U) {
    ++interval;
  }

  return (interval);
}

/**
 * @brief       Get OS Tick timer counter value
 * @return      OS Tick timer counter value
 */
uint32_t osTickGetCount(void)
{
  uint32_t count;

  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  count = __get_PeriphReg(TMR0_COUNT_REG);

  return (count);
}

/**
 * @brief       Get OS Tick timer overflow status
 * @return      OS Tick overflow status (1 - overflow, 0 - no overflow).
 */
uint32_t osTickGetOverflow(void)
{
  uint32_t ovf;

  __set_CpuReg(CPU_PRW_REG, PRW_TMR0);
  ovf = (__get_PeriphReg(TMR0_CON_REG) & TIM_CON_ERR_Msk) >> TIM_CON_ERR_Pos;

  return (ovf);
}
