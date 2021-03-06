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
  IRQ_VECTOR_COUNT  = 22
} IRQn_t;

/**
 * @brief Interrupt Priority Definition
 */
typedef enum {
  IRQ_PriorityRealtime    = 0,
  IRQ_PriorityAboveHigh   = 1,
  IRQ_PriorityHigh        = 2,
  IRQ_PriorityAboveNormal = 3,
  IRQ_PriorityNormal      = 4,
  IRQ_PriorityBelowNormal = 5,
  IRQ_PriorityAboveLow    = 6,
  IRQ_PriorityLow         = 7,
} IRQ_Priority_t;

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
  __IOM uint32_t P[3];    /*!< This register contains the interrupt priority
                               setting for Interrupt Source.                  */
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

typedef struct GPIO0_s {
  __IOM uint32_t CON;
  RESERVED(0[7], uint32_t);
  __IOM uint32_t DAT;
  __OM  uint32_t SET;
  __OM  uint32_t CLR;
  __IOM uint32_t PAR;
} GPIO0_t;

typedef struct GPIO1_s {
  __IOM uint32_t CON;
  RESERVED(0[10], uint32_t);
  __IOM uint32_t DAT;
  __OM  uint32_t SET;
  __OM  uint32_t CLR;
  __IOM uint32_t PAR;
} GPIO1_t;

typedef struct GPIO2_s {
  __IOM uint32_t CON;
  RESERVED(0[13], uint32_t);
  __IOM uint32_t DAT;
  __OM  uint32_t SET;
  __OM  uint32_t CLR;
  __IOM uint32_t PAR;
} GPIO2_t;

/* Power Clock Control */
typedef struct PCC_s {
  __OM  uint32_t POWKEY1;
  __IOM uint32_t POWCON0;
  __OM  uint32_t POWKEY2;
  __OM  uint32_t PLLKEY1;
  __IOM uint32_t PLLCON;
  __OM  uint32_t PLLKEY2;
  RESERVED(0[6], uint32_t);
  __OM  uint32_t POWKEY3;
  __IOM uint32_t POWCON1;
  __OM  uint32_t POWKEY4;
  __IOM uint32_t PSMCON;
  __IOM uint32_t CMPCON;
} PCC_t;

typedef struct FLASH_s {
  __IM  uint32_t STA;
  __IOM uint32_t MOD;
  __IOM uint32_t CON;
  __IOM uint32_t DAT;
  __IOM uint32_t ADR;
  RESERVED(0, uint32_t);
  __IM  uint32_t SIGN;
  __IOM uint32_t PRO;
  __IOM uint32_t HIDE;
} FLASH_t;

typedef struct I2C_s {
  __IOM uint32_t MCON;
  __IM  uint32_t MSTA;
  __IM  uint32_t MRX;
  __OM  uint32_t MTX;
  __IOM uint32_t MCNT0;
  __IM  uint32_t MCNT1;
  __IOM uint32_t ADR0;
  __IOM uint32_t ADR1;
  RESERVED(0, uint32_t);
  __IOM uint32_t DIV;
  __IOM uint32_t SCON;
  __IOM uint32_t SSTA;
  __IM  uint32_t SRX;
  __OM  uint32_t STX;
  __IOM uint32_t ALT;
  __IOM uint32_t ID0;
  __IOM uint32_t ID1;
  __IOM uint32_t ID2;
  __IOM uint32_t ID3;
  __IOM uint32_t FSTA;
} I2C_t;

#define FLASH_BASE            0x00080000UL
#define FLASH_END             0x0008F7FFUL
#define RAM_BASE              0x00010000UL

#define IRQ_BASE              0xFFFF0000UL  /*!< IRQ Address Base             */
#define FIQ_BASE              0xFFFF0100UL  /*!< FIQ Address Base             */
#define TIMER0_BASE           0xFFFF0300UL  /*!< Timer0 Address Base          */
#define TIMER1_BASE           0xFFFF0320UL  /*!< Timer1 Address Base          */
#define TIMER2_BASE           0xFFFF0360UL  /*!< Timer2 Address Base          */
#define PCC_BASE              0xFFFF0404UL  /*!< PLL/PSM Base Address         */
#define GPIO_BASE             0xFFFFF400UL  /*!< GPIO Address Base            */
#define FLASH_CTL_BASE        0xFFFFF800UL  /*!< FLASH Address Base           */
#define I2C0_BASE             0xFFFF0800UL  /*!< I2C0 Base Address            */
#define I2C1_BASE             0xFFFF0900UL  /*!< I2C1 Base Address            */

#define IRQ                   ((IRQ_t *)        IRQ_BASE)
#define FIQ                   ((FIQ_t *)        FIQ_BASE)
#define RTOS_TIMER            ((RTOS_TIMER_t *) TIMER0_BASE)
#define GP_TIMER              ((  GP_TIMER_t *) TIMER1_BASE)
#define WDG_TIMER             (( WDG_TIMER_t *) TIMER2_BASE)
#define GPIO0                 ((GPIO0_t *)      GPIO_BASE + 0U)
#define GPIO1                 ((GPIO1_t *)      GPIO_BASE + 4U)
#define GPIO2                 ((GPIO2_t *)      GPIO_BASE + 8U)
#define PCC                   ((PCC_t *)        PCC_BASE)
#define FLASH                 ((FLASH_t *)      FLASH_CTL_BASE)
#define I2C0                  ((I2C_t *)        I2C0_BASE)
#define I2C1                  ((I2C_t *)        I2C1_BASE)

#define SYS_REMAP             (*(volatile uint32_t *) 0xFFFF0220)

/*------------------------------------------------------------------------------
 *                                IRQ
 *----------------------------------------------------------------------------*/
#define IRQ_SWICFG_Pos            (1U)
#define IRQ_SWICFG_Msk            (0x3U << IRQ_SWICFG_Pos)
#define IRQ_SWICFG                IRQ_SWICFG_Msk
#define IRQ_SWICFG_0              (0x1U << IRQ_SWICFG_Pos)
#define IRQ_SWICFG_1              (0x2U << IRQ_SWICFG_Pos)

#define IRQ_BASER_Pos             (0U)
#define IRQ_BASER_Msk             (0xFFFFU << IRQ_BASER_Pos)
#define IRQ_BASER                 IRQ_BASER_Msk

#define IRQ_VEC_ID_Pos            (2U)
#define IRQ_VEC_ID_Msk            (0x1FU << IRQ_VEC_ID_Pos)
#define IRQ_VEC_ID                IRQ_VEC_ID_Msk

#define IRQ_VEC_BASE_Pos          (7U)
#define IRQ_VEC_BASE_Msk          (0xFFFFU << IRQ_VEC_BASE_Pos)
#define IRQ_VEC_BASE              IRQ_VEC_BASE_Msk

#define IRQ_CONN_ENIRQN_Pos       (0U)
#define IRQ_CONN_ENIRQN_Msk       (0x1U << IRQ_CONN_ENIRQN_Pos)
#define IRQ_CONN_ENIRQN           IRQ_CONN_ENIRQN_Msk

#define IRQ_CONN_ENFIQN_Pos       (1U)
#define IRQ_CONN_ENFIQN_Msk       (0x1U << IRQ_CONN_ENFIQN_Pos)
#define IRQ_CONN_ENFIQN           IRQ_CONN_ENFIQN_Msk

#define FIQ_VEC_ID_Pos            (2U)
#define FIQ_VEC_ID_Msk            (0x1FU << FIQ_VEC_ID_Pos)
#define FIQ_VEC_ID                FIQ_VEC_ID_Msk

#define FIQ_VEC_BASE_Pos          (7U)
#define FIQ_VEC_BASE_Msk          (0xFFFFU << FIQ_VEC_BASE_Pos)
#define FIQ_VEC_BASE              FIQ_VEC_BASE_Msk

#define IRQ_PRIORITY_BIT_Msk      (7U)
#define IRQ_PRIORITY_IDX(irqn)    (irqn >> 3U)
#define IRQ_PRIORITY_OFS(irqn)    ((irqn & IRQ_PRIORITY_BIT_Msk) << 2U)

#define IRQ_CLR_DEF_VALUE         (0xFFFFFFFFUL)
#define FIQ_CLR_DEF_VALUE         (0xFFFFFFFFUL)
#define IRQ_PRIO_DEF_VALUE        (0x00000000UL)

/*------------------------------------------------------------------------------
 *                               GPIO
 *----------------------------------------------------------------------------*/
#define GP0CON                    (volatile uint32_t *) 0xFFFFF400
#define GP1CON                    (volatile uint32_t *) 0xFFFFF404
#define GP2CON                    (volatile uint32_t *) 0xFFFFF408
#define GP0DAT                    (volatile uint32_t *) 0xFFFFF420
#define GP0SET                    (volatile uint32_t *) 0xFFFFF424
#define GP0CLR                    (volatile uint32_t *) 0xFFFFF428
#define GP0PAR                    (volatile uint32_t *) 0xFFFFF42C
#define GP1DAT                    (volatile uint32_t *) 0xFFFFF430
#define GP1SET                    (volatile uint32_t *) 0xFFFFF434
#define GP1CLR                    (volatile uint32_t *) 0xFFFFF438
#define GP1PAR                    (volatile uint32_t *) 0xFFFFF43C
#define GP2DAT                    (volatile uint32_t *) 0xFFFFF440
#define GP2SET                    (volatile uint32_t *) 0xFFFFF444
#define GP2CLR                    (volatile uint32_t *) 0xFFFFF448
#define GP2PAR                    (volatile uint32_t *) 0xFFFFF44C

#define GPIO_CON_P0_Pos           (0U)
#define GPIO_CON_P0_Msk           (0x3U << GPIO_CON_P0_Pos)
#define GPIO_CON_P0               GPIO_CON_P0_Msk
#define GPIO_CON_P0_0             (0x1U << GPIO_CON_P0_Pos)
#define GPIO_CON_P0_1             (0x2U << GPIO_CON_P0_Pos)

#define GPIO_CON_P1_Pos           (4U)
#define GPIO_CON_P1_Msk           (0x3U << GPIO_CON_P1_Pos)
#define GPIO_CON_P1               GPIO_CON_P1_Msk
#define GPIO_CON_P1_0             (0x1U << GPIO_CON_P1_Pos)
#define GPIO_CON_P1_1             (0x2U << GPIO_CON_P1_Pos)

#define GPIO_CON_P2_Pos           (8U)
#define GPIO_CON_P2_Msk           (0x3U << GPIO_CON_P2_Pos)
#define GPIO_CON_P2               GPIO_CON_P2_Msk
#define GPIO_CON_P2_0             (0x1U << GPIO_CON_P2_Pos)
#define GPIO_CON_P2_1             (0x2U << GPIO_CON_P2_Pos)

#define GPIO_CON_P3_Pos           (12U)
#define GPIO_CON_P3_Msk           (0x3U << GPIO_CON_P3_Pos)
#define GPIO_CON_P3               GPIO_CON_P3_Msk
#define GPIO_CON_P3_0             (0x1U << GPIO_CON_P3_Pos)
#define GPIO_CON_P3_1             (0x2U << GPIO_CON_P3_Pos)

#define GPIO_CON_P4_Pos           (16U)
#define GPIO_CON_P4_Msk           (0x3U << GPIO_CON_P4_Pos)
#define GPIO_CON_P4               GPIO_CON_P4_Msk
#define GPIO_CON_P4_0             (0x1U << GPIO_CON_P4_Pos)
#define GPIO_CON_P4_1             (0x2U << GPIO_CON_P4_Pos)

#define GPIO_CON_P5_Pos           (20U)
#define GPIO_CON_P5_Msk           (0x3U << GPIO_CON_P5_Pos)
#define GPIO_CON_P5               GPIO_CON_P5_Msk
#define GPIO_CON_P5_0             (0x1U << GPIO_CON_P5_Pos)
#define GPIO_CON_P5_1             (0x2U << GPIO_CON_P5_Pos)

#define GPIO_CON_P6_Pos           (24U)
#define GPIO_CON_P6_Msk           (0x3U << GPIO_CON_P6_Pos)
#define GPIO_CON_P6               GPIO_CON_P6_Msk
#define GPIO_CON_P6_0             (0x1U << GPIO_CON_P6_Pos)
#define GPIO_CON_P6_1             (0x2U << GPIO_CON_P6_Pos)

#define GPIO_CON_P7_Pos           (28U)
#define GPIO_CON_P7_Msk           (0x3U << GPIO_CON_P7_Pos)
#define GPIO_CON_P7               GPIO_CON_P7_Msk
#define GPIO_CON_P7_0             (0x1U << GPIO_CON_P7_Pos)
#define GPIO_CON_P7_1             (0x2U << GPIO_CON_P7_Pos)

#define GPIO_PAR_P0_Pos           (0U)
#define GPIO_PAR_P0_Msk           (0x7U << GPIO_PAR_P0_Pos)
#define GPIO_PAR_P0               GPIO_PAR_P0_Msk
#define GPIO_PAR_P0_0             (0x1U << GPIO_PAR_P0_Pos)
#define GPIO_PAR_P0_1             (0x2U << GPIO_PAR_P0_Pos)
#define GPIO_PAR_P0_2             (0x4U << GPIO_PAR_P0_Pos)

#define GPIO_PAR_P1_Pos           (4U)
#define GPIO_PAR_P1_Msk           (0x7U << GPIO_PAR_P1_Pos)
#define GPIO_PAR_P1               GPIO_PAR_P1_Msk
#define GPIO_PAR_P1_0             (0x1U << GPIO_PAR_P1_Pos)
#define GPIO_PAR_P1_1             (0x2U << GPIO_PAR_P1_Pos)
#define GPIO_PAR_P1_2             (0x4U << GPIO_PAR_P1_Pos)

#define GPIO_PAR_P2_Pos           (8U)
#define GPIO_PAR_P2_Msk           (0x7U << GPIO_PAR_P2_Pos)
#define GPIO_PAR_P2               GPIO_PAR_P2_Msk
#define GPIO_PAR_P2_0             (0x1U << GPIO_PAR_P2_Pos)
#define GPIO_PAR_P2_1             (0x2U << GPIO_PAR_P2_Pos)
#define GPIO_PAR_P2_2             (0x4U << GPIO_PAR_P2_Pos)

#define GPIO_PAR_P3_Pos           (12U)
#define GPIO_PAR_P3_Msk           (0x7U << GPIO_PAR_P3_Pos)
#define GPIO_PAR_P3               GPIO_PAR_P3_Msk
#define GPIO_PAR_P3_0             (0x1U << GPIO_PAR_P3_Pos)
#define GPIO_PAR_P3_1             (0x2U << GPIO_PAR_P3_Pos)
#define GPIO_PAR_P3_2             (0x4U << GPIO_PAR_P3_Pos)

#define GPIO_PAR_P4_Pos           (16U)
#define GPIO_PAR_P4_Msk           (0x7U << GPIO_PAR_P4_Pos)
#define GPIO_PAR_P4               GPIO_PAR_P4_Msk
#define GPIO_PAR_P4_0             (0x1U << GPIO_PAR_P4_Pos)
#define GPIO_PAR_P4_1             (0x2U << GPIO_PAR_P4_Pos)
#define GPIO_PAR_P4_2             (0x4U << GPIO_PAR_P4_Pos)

#define GPIO_PAR_P5_Pos           (20U)
#define GPIO_PAR_P5_Msk           (0x7U << GPIO_PAR_P5_Pos)
#define GPIO_PAR_P5               GPIO_PAR_P5_Msk
#define GPIO_PAR_P5_0             (0x1U << GPIO_PAR_P5_Pos)
#define GPIO_PAR_P5_1             (0x2U << GPIO_PAR_P5_Pos)
#define GPIO_PAR_P5_2             (0x4U << GPIO_PAR_P5_Pos)

#define GPIO_PAR_P6_Pos           (24U)
#define GPIO_PAR_P6_Msk           (0x7U << GPIO_PAR_P6_Pos)
#define GPIO_PAR_P6               GPIO_PAR_P6_Msk
#define GPIO_PAR_P6_0             (0x1U << GPIO_PAR_P6_Pos)
#define GPIO_PAR_P6_1             (0x2U << GPIO_PAR_P6_Pos)
#define GPIO_PAR_P6_2             (0x4U << GPIO_PAR_P6_Pos)

#define GPIO_PAR_P7_Pos           (28U)
#define GPIO_PAR_P7_Msk           (0x7U << GPIO_PAR_P7_Pos)
#define GPIO_PAR_P7               GPIO_PAR_P7_Msk
#define GPIO_PAR_P7_0             (0x1U << GPIO_PAR_P7_Pos)
#define GPIO_PAR_P7_1             (0x2U << GPIO_PAR_P7_Pos)
#define GPIO_PAR_P7_2             (0x4U << GPIO_PAR_P7_Pos)

#define GPIO_DAT_INPUT_Pos        (0U)
#define GPIO_DAT_INPUT_Msk        (0xFF << GPIO_DAT_INPUT_Pos)
#define GPIO_DAT_INPUT            GPIO_DAT_INPUT_Msk

#define GPIO_DAT_RESET_Pos        (8U)
#define GPIO_DAT_RESET_Msk        (0xFF << GPIO_DAT_RESET_Pos)
#define GPIO_DAT_RESET            GPIO_DAT_RESET_Msk

#define GPIO_DAT_OUTPUT_Pos       (16U)
#define GPIO_DAT_OUTPUT_Msk       (0xFF << GPIO_DAT_OUTPUT_Pos)
#define GPIO_DAT_OUTPUT           GPIO_DAT_OUTPUT_Msk

#define GPIO_DAT_DIR_Pos          (24U)
#define GPIO_DAT_DIR_Msk          (0xFF << GPIO_DAT_DIR_Pos)
#define GPIO_DAT_DIR              GPIO_DAT_DIR_Msk

#define GPIO_SET_BIT_Pos          (16U)
#define GPIO_SET_BIT_Msk          (0xFF << GPIO_SET_BIT_Pos)
#define GPIO_SET_BIT              GPIO_SET_BIT_Msk

#define GPIO_CLR_BIT_Pos          (16U)
#define GPIO_CLR_BIT_Msk          (0xFF << GPIO_CLR_BIT_Pos)
#define GPIO_CLR_BIT              GPIO_CLR_BIT_Msk


/*------------------------------------------------------------------------------
 *                             RTOS TIMER
 *----------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
 *                          POWER CLOCK CONTROL
 *----------------------------------------------------------------------------*/
#define PCC_POWKEY1_VALUE         ((uint16_t)0x0001)
#define PCC_POWKEY2_VALUE         ((uint16_t)0x00F4)
#define PCC_POWKEY3_VALUE         ((uint16_t)0x0076)
#define PCC_POWKEY4_VALUE         ((uint16_t)0x00B1)
#define PCC_PLLKEY1_VALUE         ((uint16_t)0x00AA)
#define PCC_PLLKEY2_VALUE         ((uint16_t)0x0055)

/*------------------------------------------------------------------------------
 *                          FLASH CONTROL
 *----------------------------------------------------------------------------*/

/********************  Bit definition for FEESTA register  ********************/
#define FLASH_STA_PASS_Pos        (0U)
#define FLASH_STA_PASS_Msk        (0x1UL << FLASH_STA_PASS_Pos)
#define FLASH_STA_PASS            FLASH_STA_PASS_Msk
#define FLASH_STA_FAIL_Pos        (1U)
#define FLASH_STA_FAIL_Msk        (0x1UL << FLASH_STA_FAIL_Pos)
#define FLASH_STA_FAIL            FLASH_STA_FAIL_Msk
#define FLASH_STA_BUSY_Pos        (2U)
#define FLASH_STA_BUSY_Msk        (0x1UL << FLASH_STA_BUSY_Pos)
#define FLASH_STA_BUSY            FLASH_STA_BUSY_Msk
#define FLASH_STA_INT_Pos         (3U)
#define FLASH_STA_INT_Msk         (0x1UL << FLASH_STA_INT_Pos)
#define FLASH_STA_INT             FLASH_STA_INT_Msk

/********************  Bit definition for FEEMOD register  ********************/
#define FLASH_MOD_DIS_PROT_Pos    (3U)
#define FLASH_MOD_DIS_PROT_Msk    (0x1UL << FLASH_MOD_DIS_PROT_Pos)
#define FLASH_MOD_DIS_PROT        FLASH_MOD_DIS_PROT_Msk
#define FLASH_MOD_INT_EN_Pos      (4U)
#define FLASH_MOD_INT_EN_Msk      (0x1UL << FLASH_MOD_INT_EN_Pos)
#define FLASH_MOD_INT_EN          FLASH_MOD_INT_EN_Msk

/********************  Bit definition for FEECON register  ********************/
#define FLASH_CON_Pos             (0U)
#define FLASH_CON_Msk             (0xFFUL << FLASH_CON_Pos)
#define FLASH_CON                 FLASH_CON_Msk
#define FLASH_CMD_IDLE            ((uint8_t)0x00)
#define FLASH_CMD_SINGLE_READ     ((uint8_t)0x01)
#define FLASH_CMD_SINGLE_WRITE    ((uint8_t)0x02)
#define FLASH_CMD_ERASE_WRITE     ((uint8_t)0x03)
#define FLASH_CMD_SINGLE_VERIFY   ((uint8_t)0x04)
#define FLASH_CMD_SINGLE_ERASE    ((uint8_t)0x05)
#define FLASH_CMD_MASS_ERASE      ((uint8_t)0x06)
#define FLASH_CMD_SIGNATURE       ((uint8_t)0x0B)
#define FLASH_CMD_PROTECT         ((uint8_t)0x0C)
#define FLASH_CMD_PING            ((uint8_t)0x0F)

/********************  Bit definition for FEEDAT register  ********************/
#define FLASH_DAT_Pos             (0U)
#define FLASH_DAT_Msk             (0xFFFFUL << FLASH_DAT_Pos)
#define FLASH_DAT                 FLASH_DAT_Msk

/********************  Bit definition for FEEADR register  ********************/
#define FLASH_ADR_Pos             (0U)
#define FLASH_ADR_Msk             (0xFFFFUL << FLASH_ADR_Pos)
#define FLASH_ADR                 FLASH_ADR_Msk

/********************  Bit definition for FEESIGN register  *******************/
#define FLASH_SIGN_Pos            (0U)
#define FLASH_SIGN_Msk            (0xFFFFFFUL << FLASH_SIGN_Pos)
#define FLASH_SIGN                FLASH_SIGN_Msk

/*------------------------------------------------------------------------------
 *                               I2C
 *----------------------------------------------------------------------------*/
/*******************  Bit definition for I2CMCON register  ********************/
#define I2CMCON_MEN_Pos           (0U)
#define I2CMCON_MEN_Msk           (0x1UL << I2CMCON_MEN_Pos)
#define I2CMCON_MEN               I2CMCON_MEN_Msk
#define I2CMCON_BD_Pos            (1U)
#define I2CMCON_BD_Msk            (0x1UL << I2CMCON_BD_Pos)
#define I2CMCON_BD                I2CMCON_BD_Msk
#define I2CMCON_ILEN_Pos          (2U)
#define I2CMCON_ILEN_Msk          (0x1UL << I2CMCON_ILEN_Pos)
#define I2CMCON_ILEN              I2CMCON_ILEN_Msk
#define I2CMCON_MRENI_Pos         (4U)
#define I2CMCON_MRENI_Msk         (0x1UL << I2CMCON_MRENI_Pos)
#define I2CMCON_MRENI             I2CMCON_MRENI_Msk
#define I2CMCON_MTENI_Pos         (5U)
#define I2CMCON_MTENI_Msk         (0x1UL << I2CMCON_MTENI_Pos)
#define I2CMCON_MTENI             I2CMCON_MTENI_Msk
#define I2CMCON_ALENI_Pos         (6U)
#define I2CMCON_ALENI_Msk         (0x1UL << I2CMCON_ALENI_Pos)
#define I2CMCON_ALENI             I2CMCON_ALENI_Msk
#define I2CMCON_NACKENI_Pos       (7U)
#define I2CMCON_NACKENI_Msk       (0x1UL << I2CMCON_NACKENI_Pos)
#define I2CMCON_NACKENI           I2CMCON_NACKENI_Msk
#define I2CMCON_MCENI_Pos         (8U)
#define I2CMCON_MCENI_Msk         (0x1UL << I2CMCON_MCENI_Pos)
#define I2CMCON_MCENI             I2CMCON_MCENI_Msk

/*******************  Bit definition for I2CMSTA register  ********************/
#define I2CMSTA_MTFSTA_Pos        (0U)
#define I2CMSTA_MTFSTA_Msk        (0x3UL << I2CMSTA_MTFSTA_Pos)
#define I2CMSTA_MTFSTA            I2CMSTA_MTFSTA_Msk
#define I2CMSTA_MTFSTA_0          (0x1UL << I2CMSTA_MTFSTA_Pos)
#define I2CMSTA_MTFSTA_1          (0x2UL << I2CMSTA_MTFSTA_Pos)
#define I2CMSTA_MTXQ_Pos          (2U)
#define I2CMSTA_MTXQ_Msk          (0x1UL << I2CMSTA_MTXQ_Pos)
#define I2CMSTA_MTXQ              I2CMSTA_MTXQ_Msk
#define I2CMSTA_MRXQ_Pos          (3U)
#define I2CMSTA_MRXQ_Msk          (0x1UL << I2CMSTA_MRXQ_Pos)
#define I2CMSTA_MRXQ              I2CMSTA_MRXQ_Msk
#define I2CMSTA_MNA_Pos           (4U)
#define I2CMSTA_MNA_Msk           (0x1UL << I2CMSTA_MNA_Pos)
#define I2CMSTA_MNA               I2CMSTA_MNA_Msk
#define I2CMSTA_AL_Pos            (5U)
#define I2CMSTA_AL_Msk            (0x1UL << I2CMSTA_AL_Pos)
#define I2CMSTA_AL                I2CMSTA_AL_Msk
#define I2CMSTA_MBUSY_Pos         (6U)
#define I2CMSTA_MBUSY_Msk         (0x1UL << I2CMSTA_MBUSY_Pos)
#define I2CMSTA_MBUSY             I2CMSTA_MBUSY_Msk
#define I2CMSTA_MNACK_Pos         (7U)
#define I2CMSTA_MNACK_Msk         (0x1UL << I2CMSTA_MNACK_Pos)
#define I2CMSTA_MNACK             I2CMSTA_MNACK_Msk
#define I2CMSTA_MTC_Pos           (8U)
#define I2CMSTA_MTC_Msk           (0x1UL << I2CMSTA_MTC_Pos)
#define I2CMSTA_MTC               I2CMSTA_MTC_Msk
#define I2CMSTA_MRXFO_Pos         (9U)
#define I2CMSTA_MRXFO_Msk         (0x1UL << I2CMSTA_MRXFO_Pos)
#define I2CMSTA_MRXFO             I2CMSTA_MRXFO_Msk
#define I2CMSTA_BBUSY_Pos         (10U)
#define I2CMSTA_BBUSY_Msk         (0x1UL << I2CMSTA_BBUSY_Pos)
#define I2CMSTA_BBUSY             I2CMSTA_BBUSY_Msk

/*******************  Bit definition for I2CMRX register  *********************/
#define I2CMRX_Pos                (0U)
#define I2CMRX_Msk                (0xFFUL << I2CMRX_Pos)
#define I2CMRX                    I2CMRX_Msk

/*******************  Bit definition for I2CMTX register  *********************/
#define I2CMTX_Pos                (0U)
#define I2CMTX_Msk                (0xFFUL << I2CMTX_Pos)
#define I2CMTX                    I2CMTX_Msk

/*******************  Bit definition for I2CMCNT0 register  *******************/
#define I2CMCNT0_RCNT_Pos         (0U)
#define I2CMCNT0_RCNT_Msk         (0xFFUL << I2CMCNT0_RCNT_Pos)
#define I2CMCNT0_RCNT             I2CMCNT0_RCNT_Msk

/*******************  Bit definition for I2CMCNT1 register  *******************/
#define I2CMCNT1_Pos              (0U)
#define I2CMCNT1_Msk              (0xFFUL << I2CMCNT1_Pos)
#define I2CMCNT1                  I2CMCNT1_Msk

/*******************  Bit definition for I2CADR0 register  ********************/
#define I2CADR0_Pos               (0U)
#define I2CADR0_Msk               (0xFFUL << I2CADR0_Pos)
#define I2CADR0                   I2CADR0_Msk

/*******************  Bit definition for I2CADR1 register  ********************/
#define I2CADR1_Pos               (0U)
#define I2CADR1_Msk               (0xFFUL << I2CADR1_Pos)
#define I2CADR1                   I2CADR1_Msk

/*******************  Bit definition for I2CDIV register  *********************/
#define I2CDIV_DIVL_Pos           (0U)
#define I2CDIV_DIVL_Msk           (0xFFUL << I2CDIV_DIVL_Pos)
#define I2CDIV_DIVL               I2CDIV_DIVL_Msk
#define I2CDIV_DIVH_Pos           (8U)
#define I2CDIV_DIVH_Msk           (0xFFUL << I2CDIV_DIVH_Pos)
#define I2CDIV_DIVH               I2CDIV_DIVH_Msk

/*******************  Bit definition for I2CSCON register  ********************/
#define I2CSCON_SEN_Pos           (0U)
#define I2CSCON_SEN_Msk           (0x1UL << I2CSCON_SEN_Pos)
#define I2CSCON_SEN               I2CSCON_SEN_Msk
#define I2CSCON_ADR10EN_Pos       (1U)
#define I2CSCON_ADR10EN_Msk       (0x1UL << I2CSCON_ADR10EN_Pos)
#define I2CSCON_ADR10EN           I2CSCON_ADR10EN_Msk
#define I2CSCON_GCEN_Pos          (2U)
#define I2CSCON_GCEN_Msk          (0x1UL << I2CSCON_GCEN_Pos)
#define I2CSCON_GCEN              I2CSCON_GCEN_Msk
#define I2CSCON_HGCEN_Pos         (3U)
#define I2CSCON_HGCEN_Msk         (0x1UL << I2CSCON_HGCEN_Pos)
#define I2CSCON_HGCEN             I2CSCON_HGCEN_Msk
#define I2CSCON_GCCLR_Pos         (4U)
#define I2CSCON_GCCLR_Msk         (0x1UL << I2CSCON_GCCLR_Pos)
#define I2CSCON_GCCLR             I2CSCON_GCCLR_Msk
#define I2CSCON_SETEN_Pos         (5U)
#define I2CSCON_SETEN_Msk         (0x1UL << I2CSCON_SETEN_Pos)
#define I2CSCON_SETEN             I2CSCON_SETEN_Msk
#define I2CSCON_NACKEN_Pos        (7U)
#define I2CSCON_NACKEN_Msk        (0x1UL << I2CSCON_NACKEN_Pos)
#define I2CSCON_NACKEN            I2CSCON_NACKEN_Msk
#define I2CSCON_SSENI_Pos         (8U)
#define I2CSCON_SSENI_Msk         (0x1UL << I2CSCON_SSENI_Pos)
#define I2CSCON_SSENI             I2CSCON_SSENI_Msk
#define I2CSCON_SRXENI_Pos        (9U)
#define I2CSCON_SRXENI_Msk        (0x1UL << I2CSCON_SRXENI_Pos)
#define I2CSCON_SRXENI            I2CSCON_SRXENI_Msk
#define I2CSCON_STXENI_Pos        (10U)
#define I2CSCON_STXENI_Msk        (0x1UL << I2CSCON_STXENI_Pos)
#define I2CSCON_STXENI            I2CSCON_STXENI_Msk

/*******************  Bit definition for I2CSSTA register  ********************/
#define I2CSSTA_ETSTA_Pos         (0U)
#define I2CSSTA_ETSTA_Msk         (0x1UL << I2CSSTA_ETSTA_Pos)
#define I2CSSTA_ETSTA             I2CSSTA_ETSTA_Msk
#define I2CSSTA_STFE_Pos          (1U)
#define I2CSSTA_STFE_Msk          (0x1UL << I2CSSTA_STFE_Pos)
#define I2CSSTA_STFE              I2CSSTA_STFE_Msk
#define I2CSSTA_STXQ_Pos          (2U)
#define I2CSSTA_STXQ_Msk          (0x1UL << I2CSSTA_STXQ_Pos)
#define I2CSSTA_STXQ              I2CSSTA_STXQ_Msk
#define I2CSSTA_SRXQ_Pos          (3U)
#define I2CSSTA_SRXQ_Msk          (0x1UL << I2CSSTA_SRXQ_Pos)
#define I2CSSTA_SRXQ              I2CSSTA_SRXQ_Msk
#define I2CSSTA_SRXFO_Pos         (4U)
#define I2CSSTA_SRXFO_Msk         (0x1UL << I2CSSTA_SRXFO_Pos)
#define I2CSSTA_SRXFO             I2CSSTA_SRXFO_Msk
#define I2CSSTA_SNACK_Pos         (5U)
#define I2CSSTA_SNACK_Msk         (0x1UL << I2CSSTA_SNACK_Pos)
#define I2CSSTA_SNACK             I2CSSTA_SNACK_Msk
#define I2CSSTA_SBUSY_Pos         (6U)
#define I2CSSTA_SBUSY_Msk         (0x1UL << I2CSSTA_SBUSY_Pos)
#define I2CSSTA_SBUSY             I2CSSTA_SBUSY_Msk
#define I2CSSTA_GC_Pos            (7U)
#define I2CSSTA_GC_Msk            (0x1UL << I2CSSTA_GC_Pos)
#define I2CSSTA_GC                I2CSSTA_GC_Msk
#define I2CSSTA_GCID_Pos          (8U)
#define I2CSSTA_GCID_Msk          (0x3UL << I2CSSTA_GCID_Pos)
#define I2CSSTA_GCID              I2CSSTA_GCID_Msk
#define I2CSSTA_GCID_0            (0x1UL << I2CSSTA_GCID_Pos)
#define I2CSSTA_GCID_1            (0x2UL << I2CSSTA_GCID_Pos)
#define I2CSSTA_SS_Pos            (10U)
#define I2CSSTA_SS_Msk            (0x1UL << I2CSSTA_SS_Pos)
#define I2CSSTA_SS                I2CSSTA_SS_Msk
#define I2CSSTA_ID_Pos            (11U)
#define I2CSSTA_ID_Msk            (0x3UL << I2CSSTA_ID_Pos)
#define I2CSSTA_ID                I2CSSTA_ID_Msk
#define I2CSSTA_ID_0              (0x1UL << I2CSSTA_ID_Pos)
#define I2CSSTA_ID_1              (0x2UL << I2CSSTA_ID_Pos)
#define I2CSSTA_REPS_Pos          (13U)
#define I2CSSTA_REPS_Msk          (0x1UL << I2CSSTA_REPS_Pos)
#define I2CSSTA_REPS              I2CSSTA_REPS_Msk
#define I2CSSTA_STA_Pos           (14U)
#define I2CSSTA_STA_Msk           (0x1UL << I2CSSTA_STA_Pos)
#define I2CSSTA_STA               I2CSSTA_STA_Msk

/*******************  Bit definition for I2CSRX register  *********************/
#define I2CSRX_Pos                (0U)
#define I2CSRX_Msk                (0xFFUL << I2CSRX_Pos)
#define I2CSRX                    I2CSRX_Msk

/*******************  Bit definition for I2CSTX register  *********************/
#define I2CSTX_Pos                (0U)
#define I2CSTX_Msk                (0xFFUL << I2CSTX_Pos)
#define I2CSTX                    I2CSTX_Msk

/*******************  Bit definition for I2CALT register  *********************/
#define I2CALT_Pos                (0U)
#define I2CALT_Msk                (0xFFUL << I2CALT_Pos)
#define I2CALT                    I2CALT_Msk

/*******************  Bit definition for I2CID0 register  *********************/
#define I2CID0_Pos                (0U)
#define I2CID0_Msk                (0xFFUL << I2CID0_Pos)
#define I2CID0                    I2CID0_Msk

/*******************  Bit definition for I2CID1 register  *********************/
#define I2CID1_Pos                (0U)
#define I2CID1_Msk                (0xFFUL << I2CID1_Pos)
#define I2CID1                    I2CID1_Msk

/*******************  Bit definition for I2CID2 register  *********************/
#define I2CID2_Pos                (0U)
#define I2CID2_Msk                (0xFFUL << I2CID2_Pos)
#define I2CID2                    I2CID2_Msk

/*******************  Bit definition for I2CID3 register  *********************/
#define I2CID3_Pos                (0U)
#define I2CID3_Msk                (0xFFUL << I2CID3_Pos)
#define I2CID3                    I2CID3_Msk

/*******************  Bit definition for I2CFSTA register  ********************/
#define I2CFSTA_STXSTA_Pos        (0U)
#define I2CFSTA_STXSTA_Msk        (0x3UL << I2CFSTA_STXSTA_Pos)
#define I2CFSTA_STXSTA            I2CFSTA_STXSTA_Msk
#define I2CFSTA_SRXSTA_Pos        (2U)
#define I2CFSTA_SRXSTA_Msk        (0x3UL << I2CFSTA_SRXSTA_Pos)
#define I2CFSTA_SRXSTA            I2CFSTA_SRXSTA_Msk
#define I2CFSTA_MTXSTA_Pos        (4U)
#define I2CFSTA_MTXSTA_Msk        (0x3UL << I2CFSTA_MTXSTA_Pos)
#define I2CFSTA_MTXSTA            I2CFSTA_MTXSTA_Msk
#define I2CFSTA_MRXSTA_Pos        (6U)
#define I2CFSTA_MRXSTA_Msk        (0x3UL << I2CFSTA_MRXSTA_Pos)
#define I2CFSTA_MRXSTA            I2CFSTA_MRXSTA_Msk
#define I2CFSTA_FSTX_Pos          (8U)
#define I2CFSTA_FSTX_Msk          (0x1UL << I2CFSTA_FSTX_Pos)
#define I2CFSTA_FSTX              I2CFSTA_FSTX_Msk
#define I2CFSTA_FMTX_Pos          (9U)
#define I2CFSTA_FMTX_Msk          (0x1UL << I2CFSTA_FMTX_Pos)
#define I2CFSTA_FMTX              I2CFSTA_FMTX_Msk

/*------------------------------------------------------------------------------
 *                          SYSTEM CONTROL
 *----------------------------------------------------------------------------*/

/********************  Bit definition for REMAP register  *********************/
#define SYS_REMAP_SRAM_Pos        (0U)
#define SYS_REMAP_SRAM_Msk        (0x1UL << SYS_REMAP_SRAM_Pos)
#define SYS_REMAP_SRAM            SYS_REMAP_SRAM_Msk

#ifdef __cplusplus
}
#endif

#endif /* ADUC7023_H_ */
