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
/****** Unprotected KMX32 Processor Registers *********************************/
#define CPU_FA_REG                0U
#define CPU_FB_REG                1U
#define CPU_LC_REG                3U
#define CPU_SMC_REG               4U
#define CPU_DP1ID_REG             5U
#define CPU_DP2ID_REG             6U
#define CPU_PSW_REG               7U
#define CPU_CLR_REG               8U
#define CPU_PRW_REG               10U
/****** Protected KMX32 Processor Registers ***********************************/
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
 *                                ADSU
 *----------------------------------------------------------------------------*/
/********************  Bit definition for ADSU_ClkCon register  ***************/
#define ADSU_ClkCon_EnRCOsc_Pos   (0U)
#define ADSU_ClkCon_EnRCOsc_Msk   (0x1UL << ADSU_ClkCon_EnRCOsc_Pos)
#define ADSU_ClkCon_EnRCOsc                 ADSU_ClkCon_EnRCOsc_Msk

#define ADSU_ClkCon_EnXTOsc_Pos   (1U)
#define ADSU_ClkCon_EnXTOsc_Msk   (0x1UL << ADSU_ClkCon_EnXTOsc_Pos)
#define ADSU_ClkCon_EnXTOsc                 ADSU_ClkCon_EnXTOsc_Msk

#define ADSU_ClkCon_EnHRCOsc_Pos  (2U)
#define ADSU_ClkCon_EnHRCOsc_Msk  (0x1UL << ADSU_ClkCon_EnHRCOsc_Pos)
#define ADSU_ClkCon_EnHRCOsc                ADSU_ClkCon_EnHRCOsc_Msk

/********************  Bit definition for ADSU_ClkCfg register  ***************/
#define ADSU_ClkCfg_Osc_Pos       (0U)
#define ADSU_ClkCfg_Osc_Msk       (0x3UL << ADSU_ClkCfg_Osc_Pos)
#define ADSU_ClkCfg_Osc_RC        (0x0UL << ADSU_ClkCfg_Osc_Pos)
#define ADSU_ClkCfg_Osc_XT        (0x1UL << ADSU_ClkCfg_Osc_Pos)
#define ADSU_ClkCfg_Osc_HRC       (0x2UL << ADSU_ClkCfg_Osc_Pos)

#define ADSU_ClkCfg_DivOsc_Pos    (2U)
#define ADSU_ClkCfg_DivOsc_Msk    (0x7UL << ADSU_ClkCfg_DivOsc_Pos)
#define ADSU_ClkCfg_DivOsc_1      (0x0UL << ADSU_ClkCfg_DivOsc_Pos)
#define ADSU_ClkCfg_DivOsc_2      (0x1UL << ADSU_ClkCfg_DivOsc_Pos)
#define ADSU_ClkCfg_DivOsc_4      (0x2UL << ADSU_ClkCfg_DivOsc_Pos)
#define ADSU_ClkCfg_DivOsc_8      (0x3UL << ADSU_ClkCfg_DivOsc_Pos)
#define ADSU_ClkCfg_DivOsc_16     (0x4UL << ADSU_ClkCfg_DivOsc_Pos)

#define ADSU_ClkCfg_EnCLK_OUT_Pos (5U)
#define ADSU_ClkCfg_EnCLK_OUT_Msk (0x1UL << ADSU_ClkCfg_EnCLK_OUT_Pos)
#define ADSU_ClkCfg_EnCLK_OUT               ADSU_ClkCfg_EnCLK_OUT_Msk

/********************  Bit definition for ADSU_Gate register  *****************/
#define ADSU_Gate_FMCU_Pos        (3U)
#define ADSU_Gate_FMCU_Msk        (0x1UL << ADSU_Gate_FMCU_Pos)
#define ADSU_Gate_FMCU                      ADSU_Gate_FMCU_Msk

#define ADSU_Gate_TMR0_Pos        (12U)
#define ADSU_Gate_TMR0_Msk        (0x1UL << ADSU_Gate_TMR0_Pos)
#define ADSU_Gate_TMR0                      ADSU_Gate_TMR0_Msk

#define ADSU_Gate_TMR1_Pos        (13U)
#define ADSU_Gate_TMR1_Msk        (0x1UL << ADSU_Gate_TMR1_Pos)
#define ADSU_Gate_TMR1                      ADSU_Gate_TMR1_Msk

#define ADSU_Gate_PWM0_Pos        (14U)
#define ADSU_Gate_PWM0_Msk        (0x1UL << ADSU_Gate_PWM0_Pos)
#define ADSU_Gate_PWM0                      ADSU_Gate_PWM0_Msk

#define ADSU_Gate_PWM1_Pos        (15U)
#define ADSU_Gate_PWM1_Msk        (0x1UL << ADSU_Gate_PWM1_Pos)
#define ADSU_Gate_PWM1                      ADSU_Gate_PWM1_Msk

#define ADSU_Gate_GPIO_Pos        (16U)
#define ADSU_Gate_GPIO_Msk        (0x1UL << ADSU_Gate_GPIO_Pos)
#define ADSU_Gate_GPIO                      ADSU_Gate_GPIO_Msk

#define ADSU_Gate_SPI0_Pos        (23U)
#define ADSU_Gate_SPI0_Msk        (0x1UL << ADSU_Gate_SPI0_Pos)
#define ADSU_Gate_SPI0                      ADSU_Gate_SPI0_Msk

#define ADSU_Gate_SPI1_Pos        (24U)
#define ADSU_Gate_SPI1_Msk        (0x1UL << ADSU_Gate_SPI1_Pos)
#define ADSU_Gate_SPI1                      ADSU_Gate_SPI1_Msk

#define ADSU_Gate_UART0_Pos       (25U)
#define ADSU_Gate_UART0_Msk       (0x1UL << ADSU_Gate_UART0_Pos)
#define ADSU_Gate_UART0                     ADSU_Gate_UART0_Msk

#define ADSU_Gate_UART1_Pos       (26U)
#define ADSU_Gate_UART1_Msk       (0x1UL << ADSU_Gate_UART1_Pos)
#define ADSU_Gate_UART1                     ADSU_Gate_UART1_Msk

#define ADSU_Gate_I2C0_Pos        (27U)
#define ADSU_Gate_I2C0_Msk        (0x1UL << ADSU_Gate_I2C0_Pos)
#define ADSU_Gate_I2C0                      ADSU_Gate_I2C0_Msk

#define ADSU_Gate_I2C1_Pos        (28U)
#define ADSU_Gate_I2C1_Msk        (0x1UL << ADSU_Gate_I2C1_Pos)
#define ADSU_Gate_I2C1                      ADSU_Gate_I2C1_Msk

#define ADSU_Gate_UART2_Pos       (29U)
#define ADSU_Gate_UART2_Msk       (0x1UL << ADSU_Gate_UART2_Pos)
#define ADSU_Gate_UART2                     ADSU_Gate_UART2_Msk

#define ADSU_Gate_UART3_Pos       (30U)
#define ADSU_Gate_UART3_Msk       (0x1UL << ADSU_Gate_UART3_Pos)
#define ADSU_Gate_UART3                     ADSU_Gate_UART3_Msk

#define ADSU_Gate_ChIN_Pos        (31U)
#define ADSU_Gate_ChIN_Msk        (0x1UL << ADSU_Gate_ChIN_Pos)
#define ADSU_Gate_ChIN                      ADSU_Gate_ChIN_Msk

/********************  Bit definition for ADSU_WakeCfg register  **************/
#define ADSU_WakeCfg_Delay_Pos    (0U)
#define ADSU_WakeCfg_Delay_Msk    (0xFFFFUL << ADSU_WakeCfg_Delay_Pos)

/********************  Bit definition for ADSU_MaxLoad register  **************/
#define ADSU_MaxLoad_JTAG_Pos     (1U)
#define ADSU_MaxLoad_JTAG_Msk     (0x1UL << ADSU_MaxLoad_JTAG_Pos)
#define ADSU_MaxLoad_JTAG                   ADSU_MaxLoad_JTAG_Msk

#define ADSU_MaxLoad_SPI0_Pos     (2U)
#define ADSU_MaxLoad_SPI0_Msk     (0x1UL << ADSU_MaxLoad_SPI0_Pos)
#define ADSU_MaxLoad_SPI0                   ADSU_MaxLoad_SPI0_Msk

#define ADSU_MaxLoad_SPI1_Pos     (3U)
#define ADSU_MaxLoad_SPI1_Msk     (0x1UL << ADSU_MaxLoad_SPI1_Pos)
#define ADSU_MaxLoad_SPI1                   ADSU_MaxLoad_SPI1_Msk

#define ADSU_MaxLoad_I2C0_Pos     (4U)
#define ADSU_MaxLoad_I2C0_Msk     (0x1UL << ADSU_MaxLoad_I2C0_Pos)
#define ADSU_MaxLoad_I2C0                   ADSU_MaxLoad_I2C0_Msk

#define ADSU_MaxLoad_I2C1_Pos     (5U)
#define ADSU_MaxLoad_I2C1_Msk     (0x1UL << ADSU_MaxLoad_I2C1_Pos)
#define ADSU_MaxLoad_I2C1                   ADSU_MaxLoad_I2C1_Msk

#define ADSU_MaxLoad_UART0_Pos    (6U)
#define ADSU_MaxLoad_UART0_Msk    (0x1UL << ADSU_MaxLoad_UART0_Pos)
#define ADSU_MaxLoad_UART0                  ADSU_MaxLoad_UART0_Msk

#define ADSU_MaxLoad_UART1_Pos    (7U)
#define ADSU_MaxLoad_UART1_Msk    (0x1UL << ADSU_MaxLoad_UART1_Pos)
#define ADSU_MaxLoad_UART1                  ADSU_MaxLoad_UART1_Msk

#define ADSU_MaxLoad_UART2_Pos    (8U)
#define ADSU_MaxLoad_UART2_Msk    (0x1UL << ADSU_MaxLoad_UART2_Pos)
#define ADSU_MaxLoad_UART2                  ADSU_MaxLoad_UART2_Msk

#define ADSU_MaxLoad_UART3_Pos    (9U)
#define ADSU_MaxLoad_UART3_Msk    (0x1UL << ADSU_MaxLoad_UART3_Pos)
#define ADSU_MaxLoad_UART3                  ADSU_MaxLoad_UART3_Msk

#define ADSU_MaxLoad_GP30_Pos     (10U)
#define ADSU_MaxLoad_GP30_Msk     (0x1UL << ADSU_MaxLoad_GP30_Pos)
#define ADSU_MaxLoad_GP30                   ADSU_MaxLoad_GP30_Msk

#define ADSU_MaxLoad_GP31_Pos     (11U)
#define ADSU_MaxLoad_GP31_Msk     (0x1UL << ADSU_MaxLoad_GP31_Pos)
#define ADSU_MaxLoad_GP31                   ADSU_MaxLoad_GP31_Msk

#define ADSU_MaxLoad_PWM0_Pos     (12U)
#define ADSU_MaxLoad_PWM0_Msk     (0x1UL << ADSU_MaxLoad_PWM0_Pos)
#define ADSU_MaxLoad_PWM0                   ADSU_MaxLoad_PWM0_Msk

#define ADSU_MaxLoad_PWM1_Pos     (13U)
#define ADSU_MaxLoad_PWM1_Msk     (0x1UL << ADSU_MaxLoad_PWM1_Pos)
#define ADSU_MaxLoad_PWM1                   ADSU_MaxLoad_PWM1_Msk

/********************  Bit definition for ADSU_Trim register  *****************/
#define ADSU_Trim_Clk_Pos         (12U)
#define ADSU_Trim_Clk_Msk         (0xFUL << ADSU_Trim_Clk_Pos)

#define ADSU_Trim_VRef_Pos        (24U)
#define ADSU_Trim_VRef_Msk        (0xFFUL << ADSU_Trim_VRef_Pos)


/*------------------------------------------------------------------------------
 *                                 I2C
 *----------------------------------------------------------------------------*/
/********************  Bit definition for I2C_Cfg register  *******************/
#define I2C_Cfg_Adr7_Pos          (0U)
#define I2C_Cfg_Adr7_Msk          (0x7FUL << I2C_Cfg_Adr7_Pos)

#define I2C_Cfg_Adr10_Pos         (7U)
#define I2C_Cfg_Adr10_Msk         (0x7UL << I2C_Cfg_Adr10_Pos)

#define I2C_Cfg_AMode_Pos         (11U)
#define I2C_Cfg_AMode_Msk         (0x3UL << I2C_Cfg_AMode_Pos)

#define I2C_Cfg_EnMTS_Pos         (13U)
#define I2C_Cfg_EnMTS_Msk         (0x1UL << I2C_Cfg_EnMTS_Pos)
#define I2C_Cfg_EnMTS                       I2C_Cfg_EnMTS_Msk

#define I2C_Cfg_On_Pos            (15U)
#define I2C_Cfg_On_Msk            (0x1UL << I2C_Cfg_On_Pos)
#define I2C_Cfg_On                          I2C_Cfg_On_Msk

#define I2C_Cfg_SCP_Pos           (16U)
#define I2C_Cfg_SCP_Msk           (0xFFFUL << I2C_Cfg_SCP_Pos)

#define I2C_Cfg_EnSRd_Pos         (28U)
#define I2C_Cfg_EnSRd_Msk         (0x1UL << I2C_Cfg_EnSRd_Pos)
#define I2C_Cfg_EnSRd                       I2C_Cfg_EnSRd_Msk

#define I2C_Cfg_EnSWr_Pos         (29U)
#define I2C_Cfg_EnSWr_Msk         (0x1UL << I2C_Cfg_EnSWr_Pos)
#define I2C_Cfg_EnSWr                       I2C_Cfg_EnSWr_Msk

#define I2C_Cfg_PullUp_Pos        (31U)
#define I2C_Cfg_PullUp_Msk        (0x1UL << I2C_Cfg_PullUp_Pos)
#define I2C_Cfg_PullUp                      I2C_Cfg_PullUp_Msk

/********************  Bit definition for I2C_Int register  *******************/
#define I2C_Cfg_ArbErrIE_Pos      (0U)
#define I2C_Cfg_ArbErrIE_Msk      (0x1UL << I2C_Cfg_ArbErrIE_Pos)
#define I2C_Cfg_ArbErrIE                    I2C_Cfg_ArbErrIE_Msk

#define I2C_Cfg_DatErrIE_Pos      (1U)
#define I2C_Cfg_DatErrIE_Msk      (0x1UL << I2C_Cfg_DatErrIE_Pos)
#define I2C_Cfg_DatErrIE                    I2C_Cfg_DatErrIE_Msk

#define I2C_Cfg_AdrErrIE_Pos      (2U)
#define I2C_Cfg_AdrErrIE_Msk      (0x1UL << I2C_Cfg_AdrErrIE_Pos)
#define I2C_Cfg_AdrErrIE                    I2C_Cfg_AdrErrIE_Msk

#define I2C_Cfg_RxIE_Pos          (3U)
#define I2C_Cfg_RxIE_Msk          (0x1UL << I2C_Cfg_RxIE_Pos)
#define I2C_Cfg_RxIE                        I2C_Cfg_RxIE_Msk

#define I2C_Cfg_TxIE_Pos          (4U)
#define I2C_Cfg_TxIE_Msk          (0x1UL << I2C_Cfg_TxIE_Pos)
#define I2C_Cfg_TxIE                        I2C_Cfg_TxIE_Msk

#define I2C_Cfg_RxOvfIE_Pos       (5U)
#define I2C_Cfg_RxOvfIE_Msk       (0x1UL << I2C_Cfg_RxOvfIE_Pos)
#define I2C_Cfg_RxOvfIE                     I2C_Cfg_RxOvfIE_Msk

#define I2C_Cfg_GenCIE_Pos        (6U)
#define I2C_Cfg_GenCIE_Msk        (0x1UL << I2C_Cfg_GenCIE_Pos)
#define I2C_Cfg_GenCIE                      I2C_Cfg_GenCIE_Msk

#define I2C_Cfg_StBytIE_Pos       (7U)
#define I2C_Cfg_StBytIE_Msk       (0x1UL << I2C_Cfg_StBytIE_Pos)
#define I2C_Cfg_StBytIE                     I2C_Cfg_StBytIE_Msk

#define I2C_Cfg_CBusIE_Pos        (8U)
#define I2C_Cfg_CBusIE_Msk        (0x1UL << I2C_Cfg_CBusIE_Pos)
#define I2C_Cfg_CBusIE                      I2C_Cfg_CBusIE_Msk

#define I2C_Cfg_HSIE_Pos          (9U)
#define I2C_Cfg_HSIE_Msk          (0x1UL << I2C_Cfg_HSIE_Pos)
#define I2C_Cfg_HSIE                        I2C_Cfg_HSIE_Msk

#define I2C_Cfg_SlvAdrIE_Pos      (10U)
#define I2C_Cfg_SlvAdrIE_Msk      (0x1UL << I2C_Cfg_SlvAdrIE_Pos)
#define I2C_Cfg_SlvAdrIE                    I2C_Cfg_SlvAdrIE_Msk

#define I2C_Cfg_Master_Pos        (11U)
#define I2C_Cfg_Master_Msk        (0x1UL << I2C_Cfg_Master_Pos)
#define I2C_Cfg_Master                      I2C_Cfg_Master_Msk

#define I2C_Cfg_DMARqEn_Pos       (12U)
#define I2C_Cfg_DMARqEn_Msk       (0x1UL << I2C_Cfg_DMARqEn_Pos)
#define I2C_Cfg_DMARqEn                     I2C_Cfg_DMARqEn_Msk

#define I2C_Cfg_TxDMARq_Pos       (13U)
#define I2C_Cfg_TxDMARq_Msk       (0x1UL << I2C_Cfg_TxDMARq_Pos)
#define I2C_Cfg_TxDMARq                     I2C_Cfg_TxDMARq_Msk

/********************  Bit definition for I2C_FIFO register  ******************/
#define I2C_FIFO_RxCntLim_Pos     (0U)
#define I2C_FIFO_RxCntLim_Msk     (0xFUL << I2C_FIFO_RxCntLim_Pos)

#define I2C_FIFO_TxCntLim_Pos     (4U)
#define I2C_FIFO_TxCntLim_Msk     (0xFUL << I2C_FIFO_TxCntLim_Pos)

/********************  Bit definition for I2C_Flags register  *****************/
/********************  Bit definition for I2C_Con register  *******************/
/********************  Bit definition for I2C_Stat register  ******************/
/********************  Bit definition for I2C_TDat register  ******************/
/********************  Bit definition for I2C_RDat register  *******************/


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
