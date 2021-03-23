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

#ifndef ADUC7023_H_
#define ADUC7023_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "CMSIS/Core_ARM/core_arm.h"
#include "system_aduc7023.h"

/**
 * @brief Interrupt Number Definition
 */
typedef enum {
  ANY_FIQ_IRQn      = 0,    /*!< All interrupts OR’ed (FIQ only)              */
  SWI_IRQn          = 1,    /*!< Software Interrupt                           */
  RTOS_TIMER_IRQn   = 2,    /*!< RTOS Timer Interrupt                         */
  GP_TIMER_IRQn     = 3,    /*!< General-Purpose Timer Interrupt              */
  WDG_TIMER_IRQn    = 4,    /*!< Watchdog Timer Interrupt                     */
  FLASH_IRQn        = 5,    /*!< Flash Interrupt                              */
  ADC_IRQn          = 6,    /*!< ADC Interrupt                                */
  PLL_IRQn          = 7,    /*!< PLL Interrupt                                */
  I2C0_MASTER_IRQn  = 8,    /*!< I2C0 Master Interrupt                        */
  I2C0_SLAVE_IRQn   = 9,    /*!< I2C0 Slave Interrupt                         */
  I2C1_MASTER_IRQn  = 10,   /*!< I2C1 Master Interrupt                        */
  I2C1_SLAVE_IRQn   = 11,   /*!< I2C1 Slave Interrupt                         */
  SPI_IRQn          = 12,   /*!< SPI Interrupt                                */
  EXT_IRQ0_IRQn     = 13,   /*!< External IRQ0 Interrupt                      */
  COMPARATOR_IRQn   = 14,   /*!< Comparator Interrupt                         */
  PSM_IRQn          = 15,   /*!< PSM Interrupt                                */
  EXT_IRQ1_IRQn     = 16,   /*!< External IRQ1 Interrupt                      */
  PLA_IRQ0_IRQn     = 17,   /*!< PLA IRQ0 Interrupt                           */
  EXT_IRQ2_IRQn     = 18,   /*!< External IRQ2 Interrupt                      */
  EXT_IRQ3_IRQn     = 19,   /*!< External IRQ3 Interrupt                      */
  PLA_IRQ1_IRQn     = 20,   /*!< PLA IRQ1 Interrupt                           */
  PWM_IRQn          = 21,   /*!< PWM Interrupt                                */
  VECTOR_NUMBER     = 22
} IRQn_t;

/**
 * @brief Interrupt Controller
 */
typedef struct IRQ_s {
  __IM  uint32_t STA;     /*!< Active IRQ source                              */
  __IM  uint32_t SIG;     /*!< Current state of all IRQ sources
                               (enabled and disabled)                         */
  __IOM uint32_t EN;      /*!< Enabled IRQ sources.                           */
  __OM  uint32_t CLR;     /*!< Disable IRQ sources                            */
  __OM  uint32_t SWICFG;  /*!< Software interrupt configuration               */
  __IOM uint32_t BASE;    /*!< Base address of all vectors. Points to start of
                               a 64-byte memory block which can contain up to
                               32 pointers to separate subroutine handlers.   */
  RESERVED(0, uint32_t);
  __IM  uint32_t VEC;     /*!< This register contains the subroutine address
                               for the currently active IRQ source.           */
  __IOM uint32_t P0;      /*!< This register contains the interrupt priority
                               setting for Interrupt Source 1 to Interrupt
                               Source 7.                                      */
  __IOM uint32_t P1;      /*!< This register contains the interrupt priority
                               setting for Interrupt Source 8 to Interrupt
                               Source 15.                                     */
  __IOM uint32_t P2;      /*!< This register contains the interrupt priority
                               setting for Interrupt Source 16 to Interrupt
                               Source 21.                                     */
  RESERVED(1, uint32_t);
  __IOM uint32_t CONN;    /*!< Used to enable IRQ and FIQ interrupt nesting.  */
  __IOM uint32_t CONE;    /*!< This register configures the external interrupt
                               sources as rising edge, falling edge, or level
                               triggered.                                     */
  __IOM uint32_t CLRE;    /*!< Used to clear an edge level triggered interrupt
                               source.                                        */
  __IOM uint32_t STAN;    /*!< This register indicates the priority level of
                               an interrupt that has just caused an interrupt
                               exception.                                     */
} IRQ_t;

/**
 * @brief Fast Interrupt Controller
 */
typedef struct FIQ_s {
  __IM  uint32_t STA;     /*!< Active FIQ source */
  __IM  uint32_t SIG;     /*!< Current state of all FIQ sources
                               (enabled and disabled)                         */
  __IOM uint32_t EN;      /*!< Enabled FIQ sources. */
  __OM  uint32_t CLR;     /*!< Disable FIQ sources */
  RESERVED(0[4], uint32_t);
  __IM  uint32_t VEC;     /*!< FIQ interrupt vector.                          */
  __IOM uint32_t STAN;    /*!< This register indicates the priority level of
                               an FIQ that has just caused an FIQ exception.  */
} FIQ_t;

/**
 * @brief RTOS Timer
 */
typedef struct RTOS_TIMER_s {
  __IOM uint16_t LD;      /*!< Timer load register                            */
  RESERVED(0, uint16_t);
  __IM  uint16_t VAL;     /*!< Timer value register                           */
  RESERVED(1, uint16_t);
  __IOM uint16_t CON;     /*!< Timer control register                         */
  RESERVED(2, uint16_t);
  __OM  uint8_t  CLRI;    /*!< Timer interrupt clear register                 */
} RTOS_TIMER_t;

/**
 * @brief Timer 32 bits
 */
typedef struct GP_TIMER_s {
  __IOM uint32_t LD;      /*!< Timer load register                            */
  __IM  uint32_t VAL;     /*!< Timer value register                           */
  __IOM uint32_t CON;     /*!< Timer control register                         */
  __OM  uint8_t  CLRI;    /*!< Timer interrupt clear register                 */
  RESERVED(0[3], uint8_t);
  __IM  uint32_t CAP;     /*!< Timer capture register                         */
} GP_TIMER_t;

/**
 * @brief RTOS Timer
 */
typedef struct WDG_TIMER_s {
  __IOM uint16_t LD;      /*!< Timer load register                            */
  RESERVED(0, uint16_t);
  __IM  uint16_t VAL;     /*!< Timer value register                           */
  RESERVED(1, uint16_t);
  __IOM uint16_t CON;     /*!< Timer control register                         */
  RESERVED(2, uint16_t);
  __OM  uint8_t  CLRI;    /*!< Timer interrupt clear register                 */
} WDG_TIMER_t;

#define IRQ_BASE              0xFFFF0000UL  /*!< IRQ Address Base             */
#define FIQ_BASE              0xFFFF0100UL  /*!< FIQ Address Base             */
#define TIMER0_BASE           0xFFFF0300UL  /*!< Timer0 Address Base          */
#define TIMER1_BASE           0xFFFF0320UL  /*!< Timer1 Address Base          */
#define TIMER2_BASE           0xFFFF0360UL  /*!< Timer2 Address Base          */

#define IRQ                   ((IRQ_t *) IRQ_BASE)
#define FIQ                   ((FIQ_t *) FIQ_BASE)
#define RTOS_TIMER            ((RTOS_TIMER_t *) TIMER0_BASE)
#define GP_TIMER              ((  GP_TIMER_t *) TIMER1_BASE)
#define WDG_TIMER             (( WDG_TIMER_t *) TIMER2_BASE)

/*                             RTOS TIMER                                     */
#define RTOS_TIMER_LD_Pos         (0U)
#define RTOS_TIMER_LD_Msk         (0xFFFFU << RTOS_TIMER_LD_Pos)
#define RTOS_TIMER_LD             RTOS_TIMER_LD_Msk

#define RTOS_TIMER_VAL_Pos        (0U)
#define RTOS_TIMER_VAL_Msk        (0xFFFFU << RTOS_TIMER_VAL_Pos)
#define RTOS_TIMER_VAL            RTOS_TIMER_VAL_Msk

#define RTOS_TIMER_CON_PSC_Pos    (2U)
#define RTOS_TIMER_CON_PSC_Msk    (0x3U << RTOS_TIMER_CON_PSC_Pos)
#define RTOS_TIMER_CON_PSC        RTOS_TIMER_CON_PSC_Msk
#define RTOS_TIMER_CON_PSC_0      (0x1U << RTOS_TIMER_CON_PSC_Pos)
#define RTOS_TIMER_CON_PSC_1      (0x2U << RTOS_TIMER_CON_PSC_Pos)

#define RTOS_TIMER_CON_CLK_Pos    (4U)
#define RTOS_TIMER_CON_CLK_Msk    (0x3U << RTOS_TIMER_CON_CLK_Pos)
#define RTOS_TIMER_CON_CLK        RTOS_TIMER_CON_CLK_Msk
#define RTOS_TIMER_CON_CLK_0      (0x1U << RTOS_TIMER_CON_CLK_Pos)
#define RTOS_TIMER_CON_CLK_1      (0x2U << RTOS_TIMER_CON_CLK_Pos)

#define RTOS_TIMER_CON_MODE_Pos   (6U)
#define RTOS_TIMER_CON_MODE_Msk   (0x1U << RTOS_TIMER_CON_MODE_Pos)
#define RTOS_TIMER_CON_MODE       RTOS_TIMER_CON_MODE_Msk

#define RTOS_TIMER_CON_EN_Pos     (7U)
#define RTOS_TIMER_CON_EN_Msk     (0x1U << RTOS_TIMER_CON_EN_Pos)
#define RTOS_TIMER_CON_EN         RTOS_TIMER_CON_EN_Msk

#ifdef __cplusplus
}
#endif

#endif /* ADUC7023_H_ */
