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

#ifndef KRECHET1_H_
#define KRECHET1_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/*------------------------------------------------------------------------------
 *                                IRQ
 *----------------------------------------------------------------------------*/
/**
 * @brief Interrupt Number Definition
 */
typedef enum {
/****** Non Maskable KMX32 Processor Exceptions Numbers ***********************/
  RESET_IRQn        = 0,    /*!< Reset Interrupt                              */
  SYS_ER_IRQn       = 1,    /*!< System Error Interrupt                       */
  WDT_IRQn          = 2,    /*!< Watchdog Timer Interrupt                     */

/****** Maskable Krechet1 specific Interrupt Numbers **************************/
  DMA_EV_IRQn       = 3,    /*!< DMA Event Interrupt                          */
  DMA_ER_IRQn       = 4,    /*!< DMA Error Interrupt                          */
  GPIO_IRQn         = 5,    /*!< GPIO global Interrupt                        */
  RESERVED0_IRQn    = 6,    /*!< Reserved Interrupt                           */
  SPI0_IRQn         = 7,    /*!< SPI0 global Interrupt                        */
  SPI1_IRQn         = 8,    /*!< SPI1 global Interrupt                        */
  I2C0_IRQn         = 9,    /*!< I2C0 global Interrupt                        */
  I2C1_IRQn         = 10,   /*!< I2C1 global Interrupt                        */
  UART0_IRQn        = 11,   /*!< UART0 global Interrupt                       */
  UART1_IRQn        = 12,   /*!< UART1 global Interrupt                       */
  UART2_IRQn        = 13,   /*!< UART2 global Interrupt                       */
  UART3_IRQn        = 14,   /*!< UART3 global Interrupt                       */
  TIM0_IRQn         = 15,   /*!< Timer0 global Interrupt                      */
  TIM1_IRQn         = 16,   /*!< Timer1 global Interrupt                      */
  PWM0_CNT_IRQn     = 17,   /*!< PWM0 Counter Interrupt                       */
  PWM0_CAP_IRQn     = 18,   /*!< PWM0 Capture Interrupt                       */
  PWM1_CNT_IRQn     = 19,   /*!< PWM1 Counter Interrupt                       */
  PWM1_CAP_IRQn     = 20,   /*!< PWM1 Capture Interrupt                       */
  RESERVED1_IRQn    = 21,   /*!< Reserved Interrupt                           */
  RESERVED2_IRQn    = 22,   /*!< Reserved Interrupt                           */
  IRQ_VECTOR_COUNT  = 23
} IRQn_t;

#include <stdint.h>
#include <CMSIS/Core/Kmx32/core_kmx32.h>
#include "system_krechet1.h"

/**
 * @brief CPU Register Address
 */
#define CPU_FA_REG                0U
#define CPU_FB_REG                1U
#define CPU_LC_REG                3U
#define CPU_SMC_REG               4U
#define CPU_DP1ID_REG             5U
#define CPU_DP2ID_REG             6U
#define CPU_PSW_REG               7U
#define CPU_CLR_REG               8U
#define CPU_PRW_REG               10U
#define CPU_CMBB_REG              16U
#define CPU_CMFB_REG              17U
#define CPU_DMBB_REG              18U
#define CPU_DMFB_REG              19U
#define CPU_NMBB_REG              20U
#define CPU_NMFB_REG              21U
#define CPU_SCFB_REG              22U
#define CPU_FLBR_REG              23U
#define CPU_CSP_REG               24U
#define CPU_ILR_PC_REG            24U
#define CPU_CSD_REG               25U
#define CPU_ILR_PSW_REG           25U
#define CPU_ERR_REG               26U
#define CPU_CONF_REG              27U
#define CPU_INTCFG_REG            28U
#define CPU_USP_REG               30U

/**
 * @brief PRW Register Value
 */
#define PRW_CPU                   0U
#define PRW_WDT                   1U
#define PRW_DBG                   1U
#define PRW_ADSU                  1U
#define PRW_CHIN                  2U
#define PRW_DMA                   3U
#define PRW_FMCU                  4U
#define PRW_GPIO                  5U
#define PRW_SPI0                  8U
#define PRW_SPI1                  9U
#define PRW_I2C0                  10U
#define PRW_I2C1                  11U
#define PRW_UART0                 12U
#define PRW_UART1                 13U
#define PRW_UART2                 14U
#define PRW_UART3                 15U
#define PRW_TMR0                  16U
#define PRW_TMR1                  17U
#define PRW_PWM0                  18U
#define PRW_PWM1                  19U

/**
 * @brief Peripheral Register Address
 */
/****** PRW = 1 ***************************************************************/
#define WDT_CON_REG               0U

#define DBG_CFG_REG               1U
#define DBG_ADDR_REG              2U
#define DBG_BP1_ADDR_REG          3U
#define DBG_BP2_ADDR_REG          4U
#define DBG_BP3_ADDR_REG          5U
#define DBG_PC_REG                6U
#define DBG_IPC_REG               7U
#define DBG_BP4_ADDR_REG          8U
#define DBG_BP5_ADDR_REG          9U

#define ADSU_CLKCON_REG           17U
#define ADSU_CLKCFG_REG           18U
#define ADSU_GATE_REG             19U
#define ADSU_WAKECFG_REG          20U
#define ADSU_MAXLOAD_REG          23U
#define ADSU_TRIM_REG             24U

/****** PRW = 2 ***************************************************************/
#define CHIN_CFG0_REG             0U
#define CHIN_CFG1_REG             1U
#define CHIN_CFG2_REG             2U
#define CHIN_CFG3_REG             3U
#define CHIN_CFG4_REG             4U
#define CHIN_CHECK_REG            8U
#define CHIN_CON_REG              30U
#define CHIN_TST_REG              31U

/****** PRW = 3 ***************************************************************/
#define DMA_CHAN_REG              0U
#define DMA_CON_REG               1U
#define DMA_CFG_REG               2U
#define DMA_SRC_REG               3U
#define DMA_DST_REG               4U
#define DMA_DCNT_REG              5U
#define DMA_STAT_REG              6U

/****** PRW = 4 ***************************************************************/
#define FMCU_CON_REG              0U
#define FMCU_ADDR_REG             1U
#define FMCU_ABUF_REG             2U
#define FMCU_DCNT_REG             3U
#define FMCU_ACCESS_REG           4U
#define FMCU_1US_CYCLE_REG        5U

/****** PRW = 5 ***************************************************************/
#define GPIO_IN_REG               0U
#define GPIO_DIR_REG              1U
#define GPIO_OUT_REG              2U
#define GPIO_RISE_IE_REG          3U
#define GPIO_DROP_IE_REG          4U
#define GPIO_RISE_IF_REG          5U
#define GPIO_DROP_IF_REG          6U
#define GPIO_FILTER_REG           7U
#define GPIO_PULL_REG             8U

/****** PRW = 8 ***************************************************************/
#define SPI0_CFG_REG              0U
#define SPI0_INT_REG              1U
#define SPI0_STAT_REG             2U
#define SPI0_DAT_REG              3U

/****** PRW = 9 ***************************************************************/
#define SPI1_CFG_REG              0U
#define SPI1_INT_REG              1U
#define SPI1_STAT_REG             2U
#define SPI1_DAT_REG              3U

/****** PRW = 10 **************************************************************/
#define I2C0_CFG_REG              0U
#define I2C0_INT_REG              1U
#define I2C0_FIFO_REG             2U
#define I2C0_FLAGS_REG            3U
#define I2C0_CON_REG              3U
#define I2C0_STAT_REG             4U
#define I2C0_TDAT_REG             5U
#define I2C0_RDAT_REG             6U

/****** PRW = 11 **************************************************************/
#define I2C1_CFG_REG              0U
#define I2C1_INT_REG              1U
#define I2C1_FIFO_REG             2U
#define I2C1_FLAGS_REG            3U
#define I2C1_CON_REG              3U
#define I2C1_STAT_REG             4U
#define I2C1_TDAT_REG             5U
#define I2C1_RDAT_REG             6U

/****** PRW = 12 **************************************************************/
#define UART0_CFG_REG             0U
#define UART0_INT_REG             1U
#define UART0_STAT_REG            2U
#define UART0_FIFO_REG            3U
#define UART0_CON_REG             4U
#define UART0_RDAT_REG            5U
#define UART0_TDAT_REG            6U

/****** PRW = 13 **************************************************************/
#define UART1_CFG_REG             0U
#define UART1_INT_REG             1U
#define UART1_STAT_REG            2U
#define UART1_FIFO_REG            3U
#define UART1_CON_REG             4U
#define UART1_RDAT_REG            5U
#define UART1_TDAT_REG            6U

/****** PRW = 14 **************************************************************/
#define UART2_CFG_REG             0U
#define UART2_INT_REG             1U
#define UART2_STAT_REG            2U
#define UART2_FIFO_REG            3U
#define UART2_CON_REG             4U
#define UART2_RDAT_REG            5U
#define UART2_TDAT_REG            6U

/****** PRW = 15 **************************************************************/
#define UART3_CFG_REG             0U
#define UART3_INT_REG             1U
#define UART3_STAT_REG            2U
#define UART3_FIFO_REG            3U
#define UART3_CON_REG             4U
#define UART3_RDAT_REG            5U
#define UART3_TDAT_REG            6U

/****** PRW = 16 **************************************************************/
#define TMR0_CFG_REG              0U
#define TMR0_CON_REG              1U
#define TMR0_RANGE_REG            2U
#define TMR0_COUNT_REG            3U

/****** PRW = 17 **************************************************************/
#define TMR1_CFG_REG              0U
#define TMR1_CON_REG              1U
#define TMR1_RANGE_REG            2U
#define TMR1_COUNT_REG            3U

/****** PRW = 18 **************************************************************/
#define PWM0_CON_REG              0U
#define PWM0_CFG_REG              1U
#define PWM0_STAT_REG             2U
#define PWM0_COUNT_A_REG          3U
#define PWM0_COUNT_B_REG          4U
#define PWM0_COUNT_C_REG          5U
#define PWM0_RANGE_A_REG          6U
#define PWM0_RANGE_B_REG          7U
#define PWM0_RANGE_C_REG          8U
#define PWM0_CMP_A_REG            9U
#define PWM0_CMP_B_REG            10U
#define PWM0_CMP_C_REG            11U

/****** PRW = 19 **************************************************************/
#define PWM1_CON_REG              0U
#define PWM1_CFG_REG              1U
#define PWM1_STAT_REG             2U
#define PWM1_COUNT_A_REG          3U
#define PWM1_COUNT_B_REG          4U
#define PWM1_COUNT_C_REG          5U
#define PWM1_RANGE_A_REG          6U
#define PWM1_RANGE_B_REG          7U
#define PWM1_RANGE_C_REG          8U
#define PWM1_CMP_A_REG            9U
#define PWM1_CMP_B_REG            10U
#define PWM1_CMP_C_REG            11U

/*------------------------------------------------------------------------------
 *                                TIMER
 *----------------------------------------------------------------------------*/
/********************  Bit definition for TIM_CFG register  *******************/
#define TIM_CFG_IE_Pos            (0U)
#define TIM_CFG_IE_Msk            (0x1UL << TIM_CFG_IE_Pos)
#define TIM_CFG_IE                TIM_CFG_IE_Msk

#define TIM_CFG_CPS_Pos           (1U)
#define TIM_CFG_CPS_Msk           (0x3UL << TIM_CFG_CPS_Pos)
#define TIM_CFG_CPS               TIM_CFG_CPS_Msk

#define TIM_CFG_CPE_Pos           (3U)
#define TIM_CFG_CPE_Msk           (0x1UL << TIM_CFG_CPE_Pos)
#define TIM_CFG_CPE               TIM_CFG_CPE_Msk

/********************  Bit definition for TIM_CON register  *******************/
#define TIM_CON_ST_Pos            (0U)
#define TIM_CON_ST_Msk            (0x1UL << TIM_CON_ST_Pos)
#define TIM_CON_ST                TIM_CON_ST_Msk

#define TIM_CON_SUSP_Pos          (1U)
#define TIM_CON_SUSP_Msk          (0x1UL << TIM_CON_SUSP_Pos)
#define TIM_CON_SUSP              TIM_CON_SUSP_Msk

#define TIM_CON_IF_Pos            (2U)
#define TIM_CON_IF_Msk            (0x1UL << TIM_CON_IF_Pos)
#define TIM_CON_IF                TIM_CON_IF_Msk

#define TIM_CON_ERR_Pos           (3U)
#define TIM_CON_ERR_Msk           (0x1UL << TIM_CON_ERR_Pos)
#define TIM_CON_ERR               TIM_CON_ERR_Msk

#ifdef __cplusplus
}
#endif

#endif /* KRECHET1_H_ */
