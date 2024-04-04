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

#include <Kernel/tick.h>
#include <Core/Riscv/irq_riscv.h>
#include <asm/gd32vf103xx.h>

#if defined(__SYSTIMER_PRESENT) && (__SYSTIMER_PRESENT == 1)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* Timer Control / Status Register Definitions */
#define MTIMECTL_TIMESTOP_Pos       0U
#define MTIMECTL_TIMESTOP_Msk       (0x1UL << MTIMECTL_TIMESTOP_Pos)
#define MTIMECTL_TIMESTOP                     MTIMECTL_TIMESTOP_Msk

#define MTIMECTL_CMPCLREN_Pos       1U
#define MTIMECTL_CMPCLREN_Msk       (0x1UL << MTIMECTL_CMPCLREN_Pos)
#define MTIMECTL_CMPCLREN                     MTIMECTL_CMPCLREN_Msk

#define MTIMECTL_CLKSRC_Pos         2U
#define MTIMECTL_CLKSRC_Msk         (0x1UL << MTIMECTL_CLKSRC_Pos)
#define MTIMECTL_CLKSRC                       MTIMECTL_CLKSRC_Msk

#define MSIP_MSIP_Pos               0U
#define MSIP_MSIP_Msk               (0x1UL << MSIP_MSIP_Pos)
#define MSIP_MSIP                             MSIP_MSIP_Msk

#define MTIMER_Msk                  (0xFFFFFFFFFFFFFFFFULL)
#define MTIMERCMP_Msk               (0xFFFFFFFFFFFFFFFFULL)
#define MTIMECTL_Msk                (0xFFFFFFFFUL)
#define MSIP_Msk                    (0xFFFFFFFFUL)
#define MSFTRST_Msk                 (0xFFFFFFFFUL)

#define MSFRST_KEY                  (0x80000A5FUL)

#ifndef __SYSTIMER_BASEADDR
/* Base address of SYSTIMER(__SYSTIMER_BASEADDR) should be defined in <Device.h> */
#error "__SYSTIMER_BASEADDR is not defined, please check!"
#endif
/* System Timer Memory mapping of Device  */
#define SysTimer_BASE               __SYSTIMER_BASEADDR                         /*!< SysTick Base Address */
#define SysTimer                    ((SysTimer_t *) SysTimer_BASE)              /*!< SysTick configuration struct */

#define SYSTIMER_IRQ_PRIORITY       0U

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Structure type to access the System Timer (SysTimer).
 * @details     Structure definition to access the system timer(SysTimer).
 */
typedef struct SysTimer_s {
  __IOM uint32_t MTIMERL;           /*!< (R/W) System Timer current value low */
  __IOM uint32_t MTIMERH;           /*!< (R/W) System Timer current value high */
  __IOM uint32_t MTIMERCMPL;        /*!< (R/W) System Timer compare Value low */
  __IOM uint32_t MTIMERCMPH;        /*!< (R/W) System Timer compare Value high */
  __IOM uint32_t RESERVED0[0x3F8];  /*!< - 0xFEC Reserved */
  __IOM uint32_t MSFTRST;           /*!< (R/W)  System Timer Software Core Reset Register */
  __IOM uint32_t RESERVED1;         /*!< Reserved */
  __IOM uint32_t MTIMECTL;          /*!< (R/W)  System Timer Control Register, previously MSTOP register */
  __IOM uint32_t MSIP;              /*!< (R/W)  System Timer SW interrupt Register */
} SysTimer_t;

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
  SysTimer->MTIMERL = 0U;
  SysTimer->MTIMERH = value >> 32;
  SysTimer->MTIMERL = value;
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

  hi = SysTimer->MTIMERH;
  lo = SysTimer->MTIMERL;
  value = SysTimer->MTIMERH;
  if (hi != value) {
    lo = SysTimer->MTIMERL;
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
  SysTimer->MTIMERCMPL = -1U;
  SysTimer->MTIMERCMPH = value >> 32;
  SysTimer->MTIMERCMPL = value;
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
  if (freq == 0U) {
    return (-1);
  }

  ticks = SystemCoreClock / (freq * 4U);

  SetLoadValue(0U);
  SetCompareValue(ticks);

  /* Disable corresponding IRQ */
  IRQ_Disable(CLIC_INT_TMR);
  /* Set Timer interrupt priority */
  IRQ_SetPriority(CLIC_INT_TMR, SYSTIMER_IRQ_PRIORITY);
  /* Register tick interrupt handler function */
  IRQ_SetHandler(CLIC_INT_TMR, handler);
  /* Set IRQ mode interrupt */
  IRQ_SetMode(CLIC_INT_TMR, IRQ_MODE_TYPE_IRQ);
  /* Enable corresponding interrupt */
  IRQ_Enable(CLIC_INT_TMR);

  return (0);
}

/**
 * @brief       Enable OS Tick timer interrupt
 */
void osTickEnable(void)
{
  SysTimer->MTIMECTL &= ~MTIMECTL_TIMESTOP;
}

/**
 * @brief       Disable OS Tick timer interrupt
 */
void osTickDisable(void)
{
  SysTimer->MTIMECTL |= MTIMECTL_TIMESTOP;
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
 * @return      OS Tick timer counter value
 */
uint32_t osTickGetCount(void)
{
  return (SysTimer->MTIMERL);
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
