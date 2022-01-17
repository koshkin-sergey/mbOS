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

#ifndef ADUC7023_H_
#define ADUC7023_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "CMSIS/Core_ARM/core_arm.h"
#include "system_aduc7023.h"

/*------------------------------------------------------------------------------
 *                                IRQ
 *----------------------------------------------------------------------------*/
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
  struct EXT_IRQ {
    __IOM uint32_t CONE;  /*!< This register configures the external interrupt
                               sources as rising edge, falling edge, or level
                               triggered.                                     */
    __IOM uint32_t CLRE;  /*!< Used to clear an edge level triggered interrupt
                               source.                                        */
  } EXT_IRQ;
  __IOM uint32_t STAN;    /*!< This register indicates the priority level of
                               an interrupt that has just caused an interrupt
                               exception.                                     */
} IRQ_t;

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

/********************  Bit definition for IRQCONE register  *******************/
#define IRQ_CONE_IRQ0SRC_Pos      (0U)
#define IRQ_CONE_IRQ0SRC_Msk      (0x3U << IRQ_CONE_IRQ0SRC_Pos)
#define IRQ_CONE_IRQ0SRC          IRQ_CONE_IRQ0SRC_Msk

#define IRQ_CONE_IRQ1SRC_Pos      (2U)
#define IRQ_CONE_IRQ1SRC_Msk      (0x3U << IRQ_CONE_IRQ1SRC_Pos)
#define IRQ_CONE_IRQ1SRC          IRQ_CONE_IRQ1SRC_Msk

#define IRQ_CONE_PLA0SRC_Pos      (4U)
#define IRQ_CONE_PLA0SRC_Msk      (0x3U << IRQ_CONE_PLA0SRC_Pos)
#define IRQ_CONE_PLA0SRC          IRQ_CONE_PLA0SRC_Msk

#define IRQ_CONE_IRQ2SRC_Pos      (6U)
#define IRQ_CONE_IRQ2SRC_Msk      (0x3U << IRQ_CONE_IRQ2SRC_Pos)
#define IRQ_CONE_IRQ2SRC          IRQ_CONE_IRQ2SRC_Msk

#define IRQ_CONE_IRQ3SRC_Pos      (8U)
#define IRQ_CONE_IRQ3SRC_Msk      (0x3U << IRQ_CONE_IRQ3SRC_Pos)
#define IRQ_CONE_IRQ3SRC          IRQ_CONE_IRQ3SRC_Msk

#define IRQ_CONE_PLA1SRC_Pos      (10U)
#define IRQ_CONE_PLA1SRC_Msk      (0x3U << IRQ_CONE_PLA1SRC_Pos)
#define IRQ_CONE_PLA1SRC          IRQ_CONE_PLA1SRC_Msk

/********************  Bit definition for IRQCLRE register  *******************/
#define IRQ_CLRE_IRQ0CLRI_Pos     (13U)
#define IRQ_CLRE_IRQ0CLRI_Msk     (0x1U << IRQ_CLRE_IRQ0CLRI_Pos)
#define IRQ_CLRE_IRQ0CLRI         IRQ_CLRE_IRQ0CLRI_Msk

#define IRQ_CLRE_IRQ1CLRI_Pos     (16U)
#define IRQ_CLRE_IRQ1CLRI_Msk     (0x1U << IRQ_CLRE_IRQ1CLRI_Pos)
#define IRQ_CLRE_IRQ1CLRI         IRQ_CLRE_IRQ1CLRI_Msk

#define IRQ_CLRE_PLA0CLRI_Pos     (17U)
#define IRQ_CLRE_PLA0CLRI_Msk     (0x1U << IRQ_CLRE_PLA0CLRI_Pos)
#define IRQ_CLRE_PLA0CLRI         IRQ_CLRE_PLA0CLRI_Msk

#define IRQ_CLRE_IRQ2CLRI_Pos     (18U)
#define IRQ_CLRE_IRQ2CLRI_Msk     (0x1U << IRQ_CLRE_IRQ2CLRI_Pos)
#define IRQ_CLRE_IRQ2CLRI         IRQ_CLRE_IRQ2CLRI_Msk

#define IRQ_CLRE_IRQ3CLRI_Pos     (19U)
#define IRQ_CLRE_IRQ3CLRI_Msk     (0x1U << IRQ_CLRE_IRQ3CLRI_Pos)
#define IRQ_CLRE_IRQ3CLRI         IRQ_CLRE_IRQ3CLRI_Msk

#define IRQ_CLRE_PLA1CLRI_Pos     (20U)
#define IRQ_CLRE_PLA1CLRI_Msk     (0x1U << IRQ_CLRE_PLA1CLRI_Pos)
#define IRQ_CLRE_PLA1CLRI         IRQ_CLRE_PLA1CLRI_Msk

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
 *                          SYSTEM CONTROL
 *----------------------------------------------------------------------------*/
/**
 * @brief System Control
 */
typedef struct SYS_s {
  __IOM uint32_t REMAP;   /*!< Remap control register. */
  RESERVED(0[3], uint32_t);
  __IOM uint32_t RSTSTA;  /*!< RSTSTA status MMR. */
  __OM  uint32_t RSTCLR;  /*!< RSTCLR MMR for clearing RSTSTA register. */
  RESERVED(1[4], uint32_t);
  __OM  uint32_t RSTKEY1; /*!< 0x76 should be written to this register before
                               writing to RSTCFG. */
  __IOM uint32_t RSTCFG;  /*!< This register allows the DAC and GPIO outputs to
                               retain state after a watchdog or software
                               reset. */
  __OM  uint32_t RSTKEY2; /*!< 0xB1 should be written to this register after
                               writing to RSTCFG. */
} SYS_t;

/********************  Bit definition for REMAP register  *********************/
#define SYS_REMAP_SRAM_Pos        (0U)
#define SYS_REMAP_SRAM_Msk        (0x1UL << SYS_REMAP_SRAM_Pos)
#define SYS_REMAP_SRAM            SYS_REMAP_SRAM_Msk

/********************  Bit definition for RSTSTA register  ********************/
#define SYS_RSTSTA_POR_Pos        (0U)
#define SYS_RSTSTA_POR_Msk        (0x1UL << SYS_RSTSTA_POR_Pos)
#define SYS_RSTSTA_POR            SYS_RSTSTA_POR_Msk

#define SYS_RSTSTA_WDR_Pos        (1U)
#define SYS_RSTSTA_WDR_Msk        (0x1UL << SYS_RSTSTA_WDR_Pos)
#define SYS_RSTSTA_WDR            SYS_RSTSTA_WDR_Msk

#define SYS_RSTSTA_SWR_Pos        (2U)
#define SYS_RSTSTA_SWR_Msk        (0x1UL << SYS_RSTSTA_SWR_Pos)
#define SYS_RSTSTA_SWR            SYS_RSTSTA_SWR_Msk

/********************  Bit definition for RSTCLR register  ********************/
#define SYS_RSTCLR_POR_Pos        (0U)
#define SYS_RSTCLR_POR_Msk        (0x1UL << SYS_RSTCLR_POR_Pos)
#define SYS_RSTCLR_POR            SYS_RSTCLR_POR_Msk

#define SYS_RSTCLR_WDR_Pos        (1U)
#define SYS_RSTCLR_WDR_Msk        (0x1UL << SYS_RSTCLR_WDR_Pos)
#define SYS_RSTCLR_WDR            SYS_RSTCLR_WDR_Msk

#define SYS_RSTCLR_SWR_Pos        (2U)
#define SYS_RSTCLR_SWR_Msk        (0x1UL << SYS_RSTCLR_SWR_Pos)
#define SYS_RSTCLR_SWR            SYS_RSTCLR_SWR_Msk

/********************  Bit definition for RSTCFG register  ********************/
#define SYS_RSTCFG_GPIO_HOLD_Pos  (0U)
#define SYS_RSTCFG_GPIO_HOLD_Msk  (0x1UL << SYS_RSTCFG_GPIO_HOLD_Pos)
#define SYS_RSTCFG_GPIO_HOLD      SYS_RSTCFG_GPIO_HOLD_Msk

#define SYS_RSTCFG_DAC_HOLD_Pos   (2U)
#define SYS_RSTCFG_DAC_HOLD_Msk   (0x1UL << SYS_RSTCFG_DAC_HOLD_Pos)
#define SYS_RSTCFG_DAC_HOLD       SYS_RSTCFG_DAC_HOLD_Msk

/********************  Bit definition for RSTKEY registers ********************/
#define SYS_RSTKEY1_VALUE         (0x76UL)
#define SYS_RSTKEY2_VALUE         (0xB1UL)

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

/**
 * @brief General-Purpose Timer 32 bits
 */
typedef struct TIMER1 {
  __IOM uint32_t LD;      /*!< Timer load register                            */
  __IM  uint32_t VAL;     /*!< Timer value register                           */
  __IOM uint32_t CON;     /*!< Timer control register                         */
  __OM  uint8_t  CLRI;    /*!< Timer interrupt clear register                 */
  RESERVED(0[3], uint8_t);
  __IM  uint32_t CAP;     /*!< Timer capture register                         */
} TIMER1_t;

#define TIMER1_CON_SRCCLK_Pos     (0U)
#define TIMER1_CON_SRCCLK_Msk     (0xFU << TIMER1_CON_SRCCLK_Pos)
#define TIMER1_CON_SRCCLK_1       (0x0U << TIMER1_CON_SRCCLK_Pos)
#define TIMER1_CON_SRCCLK_16      (0x4U << TIMER1_CON_SRCCLK_Pos)
#define TIMER1_CON_SRCCLK_256     (0x8U << TIMER1_CON_SRCCLK_Pos)
#define TIMER1_CON_SRCCLK_32768   (0xFU << TIMER1_CON_SRCCLK_Pos)

#define TIMER1_CON_FORMAT_Pos     (4U)
#define TIMER1_CON_FORMAT_Msk     (0x3U << TIMER1_CON_FORMAT_Pos)
#define TIMER1_CON_FORMAT_BIN     (0x0U << TIMER1_CON_FORMAT_Pos)
#define TIMER1_CON_FORMAT_HMS1    (0x2U << TIMER1_CON_FORMAT_Pos)
#define TIMER1_CON_FORMAT_HMS2    (0x3U << TIMER1_CON_FORMAT_Pos)

#define TIMER1_CON_FORMAT_Pos     (4U)
#define TIMER1_CON_FORMAT_Msk     (0x3U << TIMER1_CON_FORMAT_Pos)

#define TIMER1_CON_PER_MODE_Pos   (6U)
#define TIMER1_CON_PER_MODE_Msk   (0x1U << TIMER1_CON_PER_MODE_Pos)
#define TIMER1_CON_PER_MODE       TIMER1_CON_PER_MODE_Msk

#define TIMER1_CON_ENABLE_Pos     (7U)
#define TIMER1_CON_ENABLE_Msk     (0x1U << TIMER1_CON_ENABLE_Pos)
#define TIMER1_CON_ENABLE         TIMER1_CON_ENABLE_Msk

#define TIMER1_CON_CNT_UP_Pos     (8U)
#define TIMER1_CON_CNT_UP_Msk     (0x1U << TIMER1_CON_CNT_UP_Pos)
#define TIMER1_CON_CNT_UP         TIMER1_CON_CNT_UP_Msk

#define TIMER1_CON_CLKSEL_Pos     (9U)
#define TIMER1_CON_CLKSEL_Msk     (0x7U << TIMER1_CON_CLKSEL_Pos)
#define TIMER1_CON_CLKSEL_HCLK    (0x0U << TIMER1_CON_CLKSEL_Pos)
#define TIMER1_CON_CLKSEL_32K     (0x1U << TIMER1_CON_CLKSEL_Pos)
#define TIMER1_CON_CLKSEL_UCLK    (0x2U << TIMER1_CON_CLKSEL_Pos)
#define TIMER1_CON_CLKSEL_P1      (0x3U << TIMER1_CON_CLKSEL_Pos)

#define TIMER1_CON_EV_RANGE_Pos   (12U)
#define TIMER1_CON_EV_RANGE_Msk   (0x1FU << TIMER1_CON_EV_RANGE_Pos)
#define TIMER1_CON_EV_RANGE       TIMER1_CON_EV_RANGE_Msk

#define TIMER1_CON_EV_SEL_Pos     (17U)
#define TIMER1_CON_EV_SEL_Msk     (0x1U << TIMER1_CON_EV_SEL_Pos)
#define TIMER1_CON_EV_SEL         TIMER1_CON_EV_SEL_Msk

/**
 * @brief WatchDog Timer (Timer2)
 */
typedef struct TIMER2 {
  __IOM uint16_t LD;      /*!< Timer load register                            */
  RESERVED(0, uint16_t);
  __IM  uint16_t VAL;     /*!< Timer value register                           */
  RESERVED(1, uint16_t);
  __IOM uint16_t CON;     /*!< Timer control register                         */
  RESERVED(2, uint16_t);
  __OM  uint8_t  CLRI;    /*!< Timer interrupt clear register                 */
  RESERVED(3[3], uint8_t);
} TIMER2_t;

#define TIMER2_CON_WDGIRQ_Pos     (1U)
#define TIMER2_CON_WDGIRQ_Msk     (0x1U << TIMER2_CON_WDGIRQ_Pos)
#define TIMER2_CON_WDGIRQ         TIMER2_CON_WDGIRQ_Msk

#define TIMER2_CON_CLKDIV_Pos     (2U)
#define TIMER2_CON_CLKDIV_Msk     (0x3U << TIMER2_CON_CLKDIV_Pos)
#define TIMER2_CON_CLKDIV_1       (0x0U << TIMER2_CON_CLKDIV_Pos)
#define TIMER2_CON_CLKDIV_16      (0x1U << TIMER2_CON_CLKDIV_Pos)
#define TIMER2_CON_CLKDIV_256     (0x2U << TIMER2_CON_CLKDIV_Pos)

#define TIMER2_CON_SECURE_Pos     (4U)
#define TIMER2_CON_SECURE_Msk     (0x1U << TIMER2_CON_SECURE_Pos)
#define TIMER2_CON_SECURE         TIMER2_CON_SECURE_Msk

#define TIMER2_CON_WDGMODE_Pos    (5U)
#define TIMER2_CON_WDGMODE_Msk    (0x1U << TIMER2_CON_WDGMODE_Pos)
#define TIMER2_CON_WDGMODE        TIMER2_CON_WDGMODE_Msk

#define TIMER2_CON_PER_MODE_Pos   (6U)
#define TIMER2_CON_PER_MODE_Msk   (0x1U << TIMER2_CON_PER_MODE_Pos)
#define TIMER2_CON_PER_MODE       TIMER2_CON_PER_MODE_Msk

#define TIMER2_CON_ENABLE_Pos     (7U)
#define TIMER2_CON_ENABLE_Msk     (0x1U << TIMER2_CON_ENABLE_Pos)
#define TIMER2_CON_ENABLE         TIMER2_CON_ENABLE_Msk

#define TIMER2_CON_CNT_UP_Pos     (8U)
#define TIMER2_CON_CNT_UP_Msk     (0x1U << TIMER2_CON_CNT_UP_Pos)
#define TIMER2_CON_CNT_UP         TIMER2_CON_CNT_UP_Msk

/*------------------------------------------------------------------------------
 *                          POWER CLOCK CONTROL
 *----------------------------------------------------------------------------*/
/**
 * @brief Power Clock Control
 */
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

#define PCC_POWKEY1_VALUE         ((uint16_t)0x0001)
#define PCC_POWKEY2_VALUE         ((uint16_t)0x00F4)
#define PCC_POWKEY3_VALUE         ((uint16_t)0x0076)
#define PCC_POWKEY4_VALUE         ((uint16_t)0x00B1)
#define PCC_PLLKEY1_VALUE         ((uint16_t)0x00AA)
#define PCC_PLLKEY2_VALUE         ((uint16_t)0x0055)

/*------------------------------------------------------------------------------
 *                          BAND GAP REFERENCE
 *----------------------------------------------------------------------------*/
/**
 * @brief Band Gap Reference
 */
typedef struct REF {
  __IOM uint32_t CON;     /*!< Reference control register                     */
} REF_t;

/********************  Bit definition for REFCON register  ********************/
#define REFCON_OUT_EN_Pos         (0U)
#define REFCON_OUT_EN_Msk         (0x1UL << REFCON_OUT_EN_Pos)
#define REFCON_OUT_EN             REFCON_OUT_EN_Msk

/*------------------------------------------------------------------------------
 *                          ANALOG-TO-DIGITAL CONVERTER
 *----------------------------------------------------------------------------*/
/**
 * @brief The analog-to-digital converter (ADC)
 */
typedef struct ADC {
  __IOM uint32_t CON;     /*!< ADC control register                           */
  __IOM uint32_t CP;      /*!< ADC positive channel selection register        */
  __IOM uint32_t CN;      /*!< ADC negative channel selection register        */
  __IM  uint32_t STA;     /*!< ADC status register                            */
  __IM  uint32_t DAT;     /*!< ADC  data output register                      */
  __IOM uint32_t RST;     /*!< ADC reset register                             */
  RESERVED(0[6], uint32_t);
  __IOM uint32_t GN;      /*!< ADC gain calibration register                  */
  __IOM uint32_t OF;      /*!< ADC offset calibration register                */
  RESERVED(1[3], uint32_t);
  __IOM uint32_t TSCON;   /*!< Temperature sensor chopping enable register    */
  __IOM uint32_t TEMPREF; /*!< Temperature sensor reference value             */
} ADC_t;

/********************  Bit definition for ADCCON register  ********************/
#define ADCCON_CONV_TYPE_Pos      (0U)
#define ADCCON_CONV_TYPE_Msk      (0x7UL << ADCCON_CONV_TYPE_Pos)
#define ADCCON_CONV_TYPE          ADCCON_CONV_TYPE_Msk
/* ADC conversion type */
#define ADCCON_CONV_TYPE_PIN      (0x0UL << ADCCON_CONV_TYPE_Pos)
#define ADCCON_CONV_TYPE_TMR1     (0x1UL << ADCCON_CONV_TYPE_Pos)
#define ADCCON_CONV_TYPE_TMR0     (0x2UL << ADCCON_CONV_TYPE_Pos)
#define ADCCON_CONV_TYPE_SINGLE   (0x3UL << ADCCON_CONV_TYPE_Pos)
#define ADCCON_CONV_TYPE_CONT     (0x4UL << ADCCON_CONV_TYPE_Pos)
#define ADCCON_CONV_TYPE_PLA      (0x5UL << ADCCON_CONV_TYPE_Pos)

#define ADCCON_CONV_MODE_Pos      (3U)
#define ADCCON_CONV_MODE_Msk      (0x3UL << ADCCON_CONV_MODE_Pos)
#define ADCCON_CONV_MODE          ADCCON_CONV_MODE_Msk
/* ADC conversion mode */
#define ADCCON_CONV_MODE_SE       (0x0UL << ADCCON_CONV_MODE_Pos)
#define ADCCON_CONV_MODE_DIF      (0x1UL << ADCCON_CONV_MODE_Pos)

#define ADCCON_PWR_UP_Pos         (5U)
#define ADCCON_PWR_UP_Msk         (0x1UL << ADCCON_PWR_UP_Pos)
#define ADCCON_PWR_UP             ADCCON_PWR_UP_Msk

#define ADCCON_CONV_START_Pos     (7U)
#define ADCCON_CONV_START_Msk     (0x1UL << ADCCON_CONV_START_Pos)
#define ADCCON_CONV_START         ADCCON_CONV_START_Msk

#define ADCCON_ACQ_TIME_Pos       (8U)
#define ADCCON_ACQ_TIME_Msk       (0x3UL << ADCCON_ACQ_TIME_Pos)
#define ADCCON_ACQ_TIME           ADCCON_ACQ_TIME_Msk
/* ADC acquisition time */
#define ADCCON_ACQ_TIME_2C        (0x0UL << ADCCON_ACQ_TIME_Pos)
#define ADCCON_ACQ_TIME_4C        (0x1UL << ADCCON_ACQ_TIME_Pos)
#define ADCCON_ACQ_TIME_8C        (0x2UL << ADCCON_ACQ_TIME_Pos)
#define ADCCON_ACQ_TIME_16C       (0x3UL << ADCCON_ACQ_TIME_Pos)

#define ADCCON_CLK_DIV_Pos        (10U)
#define ADCCON_CLK_DIV_Msk        (0x7UL << ADCCON_CLK_DIV_Pos)
#define ADCCON_CLK_DIV            ADCCON_CLK_DIV_Msk
/* ADC clock speed */
#define ADCCON_CLK_DIV_1          (0x0UL << ADCCON_CLK_DIV_Pos)
#define ADCCON_CLK_DIV_2          (0x1UL << ADCCON_CLK_DIV_Pos)
#define ADCCON_CLK_DIV_4          (0x2UL << ADCCON_CLK_DIV_Pos)
#define ADCCON_CLK_DIV_8          (0x3UL << ADCCON_CLK_DIV_Pos)
#define ADCCON_CLK_DIV_16         (0x4UL << ADCCON_CLK_DIV_Pos)
#define ADCCON_CLK_DIV_32         (0x5UL << ADCCON_CLK_DIV_Pos)

#define ADCCON_CONV_TEMP_Pos      (13U)
#define ADCCON_CONV_TEMP_Msk      (0x1UL << ADCCON_CONV_TEMP_Pos)
#define ADCCON_CONV_TEMP          ADCCON_CONV_TEMP_Msk

/********************  Bit definition for ADCCP  register  ********************/
#define ADCCP_SEL_CHN_P_Pos       (0U)
#define ADCCP_SEL_CHN_P_Msk       (0x1FUL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P           ADCCP_SEL_CHN_P_Msk
/* Positive channel selection bits */
#define ADCCP_SEL_CHN_P_ADC0      (0x00UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC1      (0x01UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC2      (0x02UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC3      (0x03UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC4      (0x04UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC5      (0x05UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC6      (0x06UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC7      (0x07UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC8      (0x08UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC9      (0x09UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC10     (0x0AUL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_ADC12     (0x0CUL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_DAC0      (0x0EUL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_DAC1      (0x0FUL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_TEMP      (0x10UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_AGND      (0x11UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_IREF      (0x12UL << ADCCP_SEL_CHN_P_Pos)
#define ADCCP_SEL_CHN_P_AVDD      (0x13UL << ADCCP_SEL_CHN_P_Pos)

/********************  Bit definition for ADCCN  register  ********************/
#define ADCCP_SEL_CHN_N_Pos       (0U)
#define ADCCP_SEL_CHN_N_Msk       (0x1FUL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N           ADCCP_SEL_CHN_N_Msk
/* Negative channel selection bits */
#define ADCCP_SEL_CHN_N_ADC0      (0x00UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC1      (0x01UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC2      (0x02UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC3      (0x03UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC4      (0x04UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC5      (0x05UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC6      (0x06UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC7      (0x07UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC8      (0x08UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC9      (0x09UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC10     (0x0AUL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_ADC12     (0x0CUL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_DAC1      (0x0FUL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_TEMP      (0x10UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_AGND      (0x11UL << ADCCP_SEL_CHN_N_Pos)
#define ADCCP_SEL_CHN_N_IREF      (0x12UL << ADCCP_SEL_CHN_N_Pos)

/********************  Bit definition for ADCSTA register  ********************/
#define ADCSTA_READY_Pos          (0U)
#define ADCSTA_READY_Msk          (0x1UL << ADCSTA_READY_Pos)
#define ADCSTA_READY              ADCSTA_READY_Msk

/********************  Bit definition for ADCDAT register  ********************/
#define ADCDAT_DATA_Pos           (16U)
#define ADCDAT_DATA_Msk           (0xFFFFUL << ADCDAT_DATA_Pos)
#define ADCDAT_DATA               ADCDAT_DATA_Msk

/********************  Bit definition for ADCRST register  ********************/
#define ADCRST_VALUE_Pos          (0U)
#define ADCRST_VALUE_Msk          (0xFFU << ADCRST_VALUE_Pos)
#define ADCRST_VALUE              ADCRST_VALUE_Msk

/********************  Bit definition for TSCON register  *********************/
#define TSCON_EN_Pos              (0U)
#define TSCON_EN_Msk              (0x1U << TSCON_EN_Pos)
#define TSCON_EN                  TSCON_EN_Msk

/********************  Bit definition for TEMPREF register  *******************/
#define TEMPREF_OFFSET_Pos        (0U)
#define TEMPREF_OFFSET_Msk        (0xFFU << TEMPREF_OFFSET_Pos)
#define TEMPREF_OFFSET            TEMPREF_OFFSET_Msk

#define TEMPREF_SIGN_Pos          (8U)
#define TEMPREF_SIGN_Msk          (0x1U << TEMPREF_SIGN_Pos)
#define TEMPREF_SIGN              TEMPREF_SIGN_Msk

/*------------------------------------------------------------------------------
 *                          DIGITAL-TO-ANALOG CONVERTER
 *----------------------------------------------------------------------------*/
/**
 * @brief The digital-to-analog converter (DAC)
 */
typedef struct DAC {
  __IOM uint32_t CON;     /*!< DAC control register                           */
  __IOM uint32_t DAT;     /*!< DAC data register                              */
} DAC_t;

/********************  Bit definition for DACCON register  ********************/
#define DACCON_RANGE_Pos          (0U)
#define DACCON_RANGE_Msk          (0x3UL << DACCON_RANGE_Pos)
#define DACCON_RANGE              DACCON_RANGE_Msk
/* DAC range */
#define DACCON_RANGE_TRIS         (0x0UL << DACCON_RANGE_Pos)
#define DACCON_RANGE_VREF         (0x2UL << DACCON_RANGE_Pos)
#define DACCON_RANGE_AVDD         (0x3UL << DACCON_RANGE_Pos)

#define DACCON_CLR_Pos            (4U)
#define DACCON_CLR_Msk            (0x1UL << DACCON_CLR_Pos)
#define DACCON_CLR                DACCON_CLR_Msk

#define DACCON_CLK_Pos            (5U)
#define DACCON_CLK_Msk            (0x1UL << DACCON_CLK_Pos)
#define DACCON_CLK                DACCON_CLK_Msk

#define DACCON_BYPASS_Pos         (6U)
#define DACCON_BYPASS_Msk         (0x1UL << DACCON_BYPASS_Pos)
#define DACCON_BYPASS             DACCON_BYPASS_Msk

/********************  Bit definition for DACDAT register  ********************/
#define DACDAT_DATA_Pos           (16U)
#define DACDAT_DATA_Msk           (0xFFFUL << DACDAT_DATA_Pos)
#define DACDAT_DATA               DACDAT_DATA_Msk

/**
 * @brief DAC Buffers in Operational Amplifier Mode
 */
typedef struct DACB {
  __OM  uint32_t KEY0;    /*!< DAC KEY0 register                              */
  __IOM uint32_t CFG;     /*!< DAC configuration register                     */
  __OM  uint32_t KEY1;    /*!< DAC KEY1 register                              */
} DACB_t;

/********************  Bit definition for DACBKEY0 register  ******************/
#define DACBKEY0_VALUE            ((uint16_t)0x9AU)

/********************  Bit definition for DACBCFG  register  ******************/
#define DACBCFG_DAC0_Pos          (0U)
#define DACBCFG_DAC0_Msk          (0x1UL << DACBCFG_DAC0_Pos)
#define DACBCFG_DAC0              DACBCFG_DAC0_Msk

#define DACBCFG_DAC1_Pos          (1U)
#define DACBCFG_DAC1_Msk          (0x1UL << DACBCFG_DAC1_Pos)
#define DACBCFG_DAC1              DACBCFG_DAC1_Msk

#define DACBCFG_DAC2_Pos          (2U)
#define DACBCFG_DAC2_Msk          (0x1UL << DACBCFG_DAC2_Pos)
#define DACBCFG_DAC2              DACBCFG_DAC2_Msk

#define DACBCFG_DAC3_Pos          (3U)
#define DACBCFG_DAC3_Msk          (0x1UL << DACBCFG_DAC3_Pos)
#define DACBCFG_DAC3              DACBCFG_DAC3_Msk

/********************  Bit definition for DACBKEY1 register  ******************/
#define DACBKEY1_VALUE            ((uint16_t)0x0CU)

/*------------------------------------------------------------------------------
 *                          FLASH CONTROL
 *----------------------------------------------------------------------------*/
/**
 * @brief Flash Memory
 */
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
/**
 * @brief I2C
 */
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
#define I2CMSTA_TFSTA_Pos         (0U)
#define I2CMSTA_TFSTA_Msk         (0x3UL << I2CMSTA_TFSTA_Pos)
#define I2CMSTA_TFSTA             I2CMSTA_TFSTA_Msk
#define I2CMSTA_TFSTA_0           (0x1UL << I2CMSTA_TFSTA_Pos)
#define I2CMSTA_TFSTA_1           (0x2UL << I2CMSTA_TFSTA_Pos)
#define I2CMSTA_TXQ_Pos           (2U)
#define I2CMSTA_TXQ_Msk           (0x1UL << I2CMSTA_TXQ_Pos)
#define I2CMSTA_TXQ               I2CMSTA_TXQ_Msk
#define I2CMSTA_RXQ_Pos           (3U)
#define I2CMSTA_RXQ_Msk           (0x1UL << I2CMSTA_RXQ_Pos)
#define I2CMSTA_RXQ               I2CMSTA_RXQ_Msk
#define I2CMSTA_NADDR_Pos         (4U)
#define I2CMSTA_NADDR_Msk         (0x1UL << I2CMSTA_NADDR_Pos)
#define I2CMSTA_NADDR             I2CMSTA_NADDR_Msk
#define I2CMSTA_AL_Pos            (5U)
#define I2CMSTA_AL_Msk            (0x1UL << I2CMSTA_AL_Pos)
#define I2CMSTA_AL                I2CMSTA_AL_Msk
#define I2CMSTA_BUSY_Pos          (6U)
#define I2CMSTA_BUSY_Msk          (0x1UL << I2CMSTA_BUSY_Pos)
#define I2CMSTA_BUSY              I2CMSTA_BUSY_Msk
#define I2CMSTA_NDATA_Pos         (7U)
#define I2CMSTA_NDATA_Msk         (0x1UL << I2CMSTA_NDATA_Pos)
#define I2CMSTA_NDATA             I2CMSTA_NDATA_Msk
#define I2CMSTA_TC_Pos            (8U)
#define I2CMSTA_TC_Msk            (0x1UL << I2CMSTA_TC_Pos)
#define I2CMSTA_TC                I2CMSTA_TC_Msk
#define I2CMSTA_RXFO_Pos          (9U)
#define I2CMSTA_RXFO_Msk          (0x1UL << I2CMSTA_RXFO_Pos)
#define I2CMSTA_RXFO              I2CMSTA_RXFO_Msk
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

#define I2CMCNT0_RECNT_Pos        (8U)
#define I2CMCNT0_RECNT_Msk        (0x1UL << I2CMCNT0_RECNT_Pos)
#define I2CMCNT0_RECNT            I2CMCNT0_RECNT_Msk

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

#define FLASH_BASE            0x00080000UL
#define FLASH_END             0x0008F7FFUL
#define RAM_BASE              0x00010000UL

#define IRQ_BASE              0xFFFF0000UL  /*!< IRQ Address Base             */
#define FIQ_BASE              0xFFFF0100UL  /*!< FIQ Address Base             */
#define SYS_BASE              0xFFFF0220UL  /*!< SYS Address Base             */
#define TIMER0_BASE           0xFFFF0300UL  /*!< Timer0 Address Base          */
#define TIMER1_BASE           0xFFFF0320UL  /*!< Timer1 Address Base          */
#define TIMER2_BASE           0xFFFF0360UL  /*!< Timer2 Address Base          */
#define PCC_BASE              0xFFFF0404UL  /*!< PLL/PSM Base Address         */
#define REF_BASE              0xFFFF048CUL  /*!< REF Address Base             */
#define ADC_BASE              0xFFFF0500UL  /*!< ADC Address Base             */
#define DAC0_BASE             0xFFFF0600UL  /*!< DAC0 Address Base            */
#define DAC1_BASE             0xFFFF0608UL  /*!< DAC1 Address Base            */
#define DAC2_BASE             0xFFFF0610UL  /*!< DAC2 Address Base            */
#define DAC3_BASE             0xFFFF0618UL  /*!< DAC3 Address Base            */
#define DACB_BASE             0xFFFF0650UL  /*!< DACB Address Base            */
#define I2C0_BASE             0xFFFF0800UL  /*!< I2C0 Base Address            */
#define I2C1_BASE             0xFFFF0900UL  /*!< I2C1 Base Address            */
#define FLASH_CTL_BASE        0xFFFFF800UL  /*!< FLASH Address Base           */

#define IRQ                   ((IRQ_t *)        IRQ_BASE)
#define FIQ                   ((FIQ_t *)        FIQ_BASE)
#define SYS                   ((SYS_t *)        SYS_BASE)
#define RTOS_TIMER            ((RTOS_TIMER_t *) TIMER0_BASE)
#define TIM1                  ((TIMER1_t *)     TIMER1_BASE)
#define TIM2                  ((TIMER2_t *)     TIMER2_BASE)
#define PCC                   ((PCC_t *)        PCC_BASE)
#define REF                   ((REF_t *)        REF_BASE)
#define ADC                   ((ADC_t *)        ADC_BASE)
#define DAC0                  ((DAC_t *)        DAC0_BASE)
#define DAC1                  ((DAC_t *)        DAC1_BASE)
#define DAC2                  ((DAC_t *)        DAC2_BASE)
#define DAC3                  ((DAC_t *)        DAC3_BASE)
#define DACB                  ((DACB_t *)       DACB_BASE)
#define I2C0                  ((I2C_t *)        I2C0_BASE)
#define I2C1                  ((I2C_t *)        I2C1_BASE)
#define FLASH                 ((FLASH_t *)      FLASH_CTL_BASE)

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#ifdef __cplusplus
}
#endif

#endif /* ADUC7023_H_ */
