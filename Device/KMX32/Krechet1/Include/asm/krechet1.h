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
typedef enum Periph_Wnd {
  PRW_CPU  = 0U,
  PRW_WDT  = 1U,
  PRW_DBG  = 1U,
  PRW_ADSU = 1U,
  PRW_CHIN = 2U,
  PRW_DMA  = 3U,
  PRW_FMCU = 4U,
  PRW_GPIO = 5U,
  PRW_SPI0 = 8U,
  PRW_SPI1 = 9U,
  PRW_I2C0 = 10U,
  PRW_I2C1 = 11U,
  PRW_UART0= 12U,
  PRW_UART1= 13U,
  PRW_UART2= 14U,
  PRW_UART3= 15U,
  PRW_TMR0 = 16U,
  PRW_TMR1 = 17U,
  PRW_PWM0 = 18U,
  PRW_PWM1 = 19U
} Periph_Wnd_t;

/**
 * @brief Peripheral Register Address
 */
/****** PRW = 1 ***************************************************************/
#define WDT_CON_REG               0

#define DBG_CFG_REG               1
#define DBG_ADDR_REG              2
#define DBG_BP1_ADDR_REG          3
#define DBG_BP2_ADDR_REG          4
#define DBG_BP3_ADDR_REG          5
#define DBG_PC_REG                6
#define DBG_IPC_REG               7
#define DBG_BP4_ADDR_REG          8
#define DBG_BP5_ADDR_REG          9

#define ADSU_CLKCON_REG           17
#define ADSU_CLKCFG_REG           18
#define ADSU_GATE_REG             19
#define ADSU_WAKECFG_REG          20
#define ADSU_MAXLOAD_REG          23
#define ADSU_TRIM_REG             24

/****** PRW = 2 ***************************************************************/
#define CHIN_CFG0_REG             0
#define CHIN_CFG1_REG             1
#define CHIN_CFG2_REG             2
#define CHIN_CFG3_REG             3
#define CHIN_CFG4_REG             4
#define CHIN_CHECK_REG            8
#define CHIN_CON_REG              30
#define CHIN_TST_REG              31

/****** PRW = 3 ***************************************************************/
#define DMA_CHAN_REG              0
#define DMA_CON_REG               1
#define DMA_CFG_REG               2
#define DMA_SRC_REG               3
#define DMA_DST_REG               4
#define DMA_DCNT_REG              5
#define DMA_STAT_REG              6

/****** PRW = 4 ***************************************************************/
#define FMCU_CON_REG              0
#define FMCU_ADDR_REG             1
#define FMCU_ABUF_REG             2
#define FMCU_DCNT_REG             3
#define FMCU_ACCESS_REG           4
#define FMCU_1US_CYCLE_REG        5

/****** PRW = 5 ***************************************************************/
#define GPIO_IN_REG               0
#define GPIO_DIR_REG              1
#define GPIO_OUT_REG              2
#define GPIO_RISE_IE_REG          3
#define GPIO_DROP_IE_REG          4
#define GPIO_RISE_IF_REG          5
#define GPIO_DROP_IF_REG          6
#define GPIO_FILTER_REG           7
#define GPIO_PULL_REG             8

/****** PRW = 8 & PRW = 9 *****************************************************/
#define SPI_CFG_REG               0
#define SPI_INT_REG               1
#define SPI_STAT_REG              2
#define SPI_DAT_REG               3

/****** PRW = 10 & PRW = 11 ***************************************************/
#define I2C_CFG_REG               0
#define I2C_INT_REG               1
#define I2C_FIFO_REG              2
#define I2C_FLAGS_REG             3
#define I2C_CON_REG               3
#define I2C_STAT_REG              4
#define I2C_TDAT_REG              5
#define I2C_RDAT_REG              6

/****** PRW = 12 & PRW = 13 & PRW = 14 & PRW = 15 *****************************/
#define UART_CFG_REG              0
#define UART_INT_REG              1
#define UART_STAT_REG             2
#define UART_FIFO_REG             3
#define UART_CON_REG              4
#define UART_RDAT_REG             5
#define UART_TDAT_REG             6

/****** PRW = 16 & PRW = 17 ***************************************************/
#define TMR_CFG_REG               0
#define TMR_CON_REG               1
#define TMR_RANGE_REG             2
#define TMR_COUNT_REG             3

/****** PRW = 18 & PRW = 19 ***************************************************/
#define PWM_CON_REG               0
#define PWM_CFG_REG               1
#define PWM_STAT_REG              2
#define PWM_COUNT_A_REG           3
#define PWM_COUNT_B_REG           4
#define PWM_COUNT_C_REG           5
#define PWM_RANGE_A_REG           6
#define PWM_RANGE_B_REG           7
#define PWM_RANGE_C_REG           8
#define PWM_CMP_A_REG             9
#define PWM_CMP_B_REG             10
#define PWM_CMP_C_REG             11


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
 *                                 FMCU
 *----------------------------------------------------------------------------*/
/********************  Bit definition for FMCU_Con register  ******************/
#define FMCU_Con_Prog_Pos         (0U)
#define FMCU_Con_Prog_Msk         (0x1UL << FMCU_Con_Prog_Pos)
#define FMCU_Con_Prog             FMCU_Con_Prog_Msk

#define FMCU_Con_Ers_Pos          (1U)
#define FMCU_Con_Ers_Msk          (0x1UL << FMCU_Con_Ers_Pos)
#define FMCU_Con_Ers              FMCU_Con_Ers_Msk

#define FMCU_Con_Info_Pos         (4U)
#define FMCU_Con_Info_Msk         (0x1UL << FMCU_Con_Info_Pos)
#define FMCU_Con_Info             FMCU_Con_Info_Msk

#define FMCU_Con_MErs_Pos         (8U)
#define FMCU_Con_MErs_Msk         (0x7UL << FMCU_Con_MErs_Pos)

#define FMCU_Con_Sleep_Pos        (13U)
#define FMCU_Con_Sleep_Msk        (0x1UL << FMCU_Con_Sleep_Pos)
#define FMCU_Con_Sleep            FMCU_Con_Sleep_Msk

#define FMCU_Con_PDM25_Pos        (14U)
#define FMCU_Con_PDM25_Msk        (0x1UL << FMCU_Con_PDM25_Pos)
#define FMCU_Con_PDM25            FMCU_Con_PDM25_Msk

#define FMCU_Con_ErsOfRef_Pos     (15U)
#define FMCU_Con_ErsOfRef_Msk     (0x1UL << FMCU_Con_ErsOfRef_Pos)
#define FMCU_Con_ErsOfRef         FMCU_Con_ErsOfRef_Msk

#define FMCU_Con_EnNAct_Pos       (16U)
#define FMCU_Con_EnNAct_Msk       (0x1UL << FMCU_Con_EnNAct_Pos)
#define FMCU_Con_EnNAct           FMCU_Con_EnNAct_Msk

/********************  Bit definition for FMCU_Addr register  *****************/
#define FMCU_Addr_DW_Pos          (2U)
#define FMCU_Addr_DW_Msk          (0x7FUL << FMCU_Addr_DW_Pos)

#define FMCU_Addr_Str_Pos         (9U)
#define FMCU_Addr_Str_Msk         (0x7UL << FMCU_Addr_Str_Pos)

#define FMCU_Addr_Page_Pos        (12U)
#define FMCU_Addr_Page_Msk        (0x7FUL << FMCU_Addr_Page_Pos)

/********************  Bit definition for FMCU_ABuf register  *****************/
#define FMCU_ABuf_DWAddr_Pos      (0U)
#define FMCU_ABuf_DWAddr_Msk      (0xFFFFUL << FMCU_ABuf_DWAddr_Pos)

/********************  Bit definition for FMCU_DCnt register  *****************/
#define FMCU_DCnt_Bytes_Pos       (0U)
#define FMCU_DCnt_Bytes_Msk       (0x1FFUL << FMCU_DCnt_Bytes_Pos)

/********************  Bit definition for FMCU_Access register  ***************/
#define FMCU_Access_Delay_Pos     (0U)
#define FMCU_Access_Delay_Msk     (0x3FUL << FMCU_Access_Delay_Pos)

/********************  Bit definition for FMCU_1usCycle register  *************/
#define FMCU_1usCycle_Scale_Pos   (0U)
#define FMCU_1usCycle_Scale_Msk   (0x3FFUL << FMCU_1usCycle_Scale_Pos)


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
#define I2C_Cfg_AMode_7           (0x1UL << I2C_Cfg_AMode_Pos)
#define I2C_Cfg_AMode_10          (0x2UL << I2C_Cfg_AMode_Pos)
#define I2C_Cfg_AMode_7_10        (0x3UL << I2C_Cfg_AMode_Pos)

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
#define I2C_Int_ArbErrIE_Pos      (0U)
#define I2C_Int_ArbErrIE_Msk      (0x1UL << I2C_Int_ArbErrIE_Pos)
#define I2C_Int_ArbErrIE                    I2C_Int_ArbErrIE_Msk

#define I2C_Int_DatErrIE_Pos      (1U)
#define I2C_Int_DatErrIE_Msk      (0x1UL << I2C_Int_DatErrIE_Pos)
#define I2C_Int_DatErrIE                    I2C_Int_DatErrIE_Msk

#define I2C_Int_AdrErrIE_Pos      (2U)
#define I2C_Int_AdrErrIE_Msk      (0x1UL << I2C_Int_AdrErrIE_Pos)
#define I2C_Int_AdrErrIE                    I2C_Int_AdrErrIE_Msk

#define I2C_Int_RxIE_Pos          (3U)
#define I2C_Int_RxIE_Msk          (0x1UL << I2C_Int_RxIE_Pos)
#define I2C_Int_RxIE                        I2C_Int_RxIE_Msk

#define I2C_Int_TxIE_Pos          (4U)
#define I2C_Int_TxIE_Msk          (0x1UL << I2C_Int_TxIE_Pos)
#define I2C_Int_TxIE                        I2C_Int_TxIE_Msk

#define I2C_Int_RxOvfIE_Pos       (5U)
#define I2C_Int_RxOvfIE_Msk       (0x1UL << I2C_Int_RxOvfIE_Pos)
#define I2C_Int_RxOvfIE                     I2C_Int_RxOvfIE_Msk

#define I2C_Int_GenCIE_Pos        (6U)
#define I2C_Int_GenCIE_Msk        (0x1UL << I2C_Int_GenCIE_Pos)
#define I2C_Int_GenCIE                      I2C_Int_GenCIE_Msk

#define I2C_Int_StBytIE_Pos       (7U)
#define I2C_Int_StBytIE_Msk       (0x1UL << I2C_Int_StBytIE_Pos)
#define I2C_Int_StBytIE                     I2C_Int_StBytIE_Msk

#define I2C_Int_CBusIE_Pos        (8U)
#define I2C_Int_CBusIE_Msk        (0x1UL << I2C_Int_CBusIE_Pos)
#define I2C_Int_CBusIE                      I2C_Int_CBusIE_Msk

#define I2C_Int_HSIE_Pos          (9U)
#define I2C_Int_HSIE_Msk          (0x1UL << I2C_Int_HSIE_Pos)
#define I2C_Int_HSIE                        I2C_Int_HSIE_Msk

#define I2C_Int_SlvAdrIE_Pos      (10U)
#define I2C_Int_SlvAdrIE_Msk      (0x1UL << I2C_Int_SlvAdrIE_Pos)
#define I2C_Int_SlvAdrIE                    I2C_Int_SlvAdrIE_Msk

#define I2C_Int_Master_Pos        (11U)
#define I2C_Int_Master_Msk        (0x1UL << I2C_Int_Master_Pos)
#define I2C_Int_Master                      I2C_Int_Master_Msk

#define I2C_Int_DMARqEn_Pos       (12U)
#define I2C_Int_DMARqEn_Msk       (0x1UL << I2C_Int_DMARqEn_Pos)
#define I2C_Int_DMARqEn                     I2C_Int_DMARqEn_Msk

#define I2C_Int_TxDMARq_Pos       (13U)
#define I2C_Int_TxDMARq_Msk       (0x1UL << I2C_Int_TxDMARq_Pos)
#define I2C_Int_TxDMARq                     I2C_Int_TxDMARq_Msk

/********************  Bit definition for I2C_FIFO register  ******************/
#define I2C_FIFO_RxCntLim_Pos     (0U)
#define I2C_FIFO_RxCntLim_Msk     (0xFUL << I2C_FIFO_RxCntLim_Pos)

#define I2C_FIFO_TxCntLim_Pos     (4U)
#define I2C_FIFO_TxCntLim_Msk     (0xFUL << I2C_FIFO_TxCntLim_Pos)

/********************  Bit definition for I2C_Flags register  *****************/
#define I2C_Flags_Attentn_Pos     (0U)
#define I2C_Flags_Attentn_Msk     (0x1UL << I2C_Flags_Attentn_Pos)
#define I2C_Flags_Attentn                   I2C_Flags_Attentn_Msk

#define I2C_Flags_StartErrIF_Pos  (1U)
#define I2C_Flags_StartErrIF_Msk  (0x1UL << I2C_Flags_StartErrIF_Pos)
#define I2C_Flags_StartErrIF                I2C_Flags_StartErrIF_Msk

#define I2C_Flags_SDAErrIF_Pos    (2U)
#define I2C_Flags_SDAErrIF_Msk    (0x1UL << I2C_Flags_SDAErrIF_Pos)
#define I2C_Flags_SDAErrIF                  I2C_Flags_SDAErrIF_Msk

#define I2C_Flags_OddStopIF_Pos   (3U)
#define I2C_Flags_OddStopIF_Msk   (0x1UL << I2C_Flags_OddStopIF_Pos)
#define I2C_Flags_OddStopIF                 I2C_Flags_OddStopIF_Msk

#define I2C_Flags_StopErrIF_Pos   (4U)
#define I2C_Flags_StopErrIF_Msk   (0x1UL << I2C_Flags_StopErrIF_Pos)
#define I2C_Flags_StopErrIF                 I2C_Flags_StopErrIF_Msk

#define I2C_Flags_DatErrIF_Pos    (5U)
#define I2C_Flags_DatErrIF_Msk    (0x1UL << I2C_Flags_DatErrIF_Pos)
#define I2C_Flags_DatErrIF                  I2C_Flags_DatErrIF_Msk

#define I2C_Flags_AdrErrIF_Pos    (6U)
#define I2C_Flags_AdrErrIF_Msk    (0x1UL << I2C_Flags_AdrErrIF_Pos)
#define I2C_Flags_AdrErrIF                  I2C_Flags_AdrErrIF_Msk

#define I2C_Flags_RxIF_Pos        (7U)
#define I2C_Flags_RxIF_Msk        (0x1UL << I2C_Flags_RxIF_Pos)
#define I2C_Flags_RxIF                      I2C_Flags_RxIF_Msk

#define I2C_Flags_TxIF_Pos        (8U)
#define I2C_Flags_TxIF_Msk        (0x1UL << I2C_Flags_TxIF_Pos)
#define I2C_Flags_TxIF                      I2C_Flags_TxIF_Msk

#define I2C_Flags_RxOvfIF_Pos     (9U)
#define I2C_Flags_RxOvfIF_Msk     (0x1UL << I2C_Flags_RxOvfIF_Pos)
#define I2C_Flags_RxOvfIF                   I2C_Flags_RxOvfIF_Msk

#define I2C_Flags_GenCIF_Pos      (10U)
#define I2C_Flags_GenCIF_Msk      (0x1UL << I2C_Flags_GenCIF_Pos)
#define I2C_Flags_GenCIF                    I2C_Flags_GenCIF_Msk

#define I2C_Flags_StBytIF_Pos     (11U)
#define I2C_Flags_StBytIF_Msk     (0x1UL << I2C_Flags_StBytIF_Pos)
#define I2C_Flags_StBytIF                   I2C_Flags_StBytIF_Msk

#define I2C_Flags_CBusIF_Pos      (12U)
#define I2C_Flags_CBusIF_Msk      (0x1UL << I2C_Flags_CBusIF_Pos)
#define I2C_Flags_CBusIF                    I2C_Flags_CBusIF_Msk

#define I2C_Flags_HSIF_Pos        (13U)
#define I2C_Flags_HSIF_Msk        (0x1UL << I2C_Flags_HSIF_Pos)
#define I2C_Flags_HSIF                      I2C_Flags_HSIF_Msk

#define I2C_Flags_SlvAdrIF_Pos    (14U)
#define I2C_Flags_SlvAdrIF_Msk    (0x1UL << I2C_Flags_SlvAdrIF_Pos)
#define I2C_Flags_SlvAdrIF                  I2C_Flags_SlvAdrIF_Msk

#define I2C_Flags_SlvNoAckIF_Pos  (15U)
#define I2C_Flags_SlvNoAckIF_Msk  (0x1UL << I2C_Flags_SlvNoAckIF_Pos)
#define I2C_Flags_SlvNoAckIF                I2C_Flags_SlvNoAckIF_Msk

/********************  Bit definition for I2C_Con register  *******************/
#define I2C_Con_StartTx_Pos       (0U)
#define I2C_Con_StartTx_Msk       (0x1UL << I2C_Con_StartTx_Pos)
#define I2C_Con_StartTx                     I2C_Con_StartTx_Msk

#define I2C_Con_StartErrIF_Pos    (1U)
#define I2C_Con_StartErrIF_Msk    (0x1UL << I2C_Con_StartErrIF_Pos)
#define I2C_Con_StartErrIF                  I2C_Con_StartErrIF_Msk

#define I2C_Con_SDAErrIF_Pos      (2U)
#define I2C_Con_SDAErrIF_Msk      (0x1UL << I2C_Con_SDAErrIF_Pos)
#define I2C_Con_SDAErrIF                    I2C_Con_SDAErrIF_Msk

#define I2C_Con_OddStopIF_Pos     (3U)
#define I2C_Con_OddStopIF_Msk     (0x1UL << I2C_Con_OddStopIF_Pos)
#define I2C_Con_OddStopIF                   I2C_Con_OddStopIF_Msk

#define I2C_Con_StopErrIF_Pos     (4U)
#define I2C_Con_StopErrIF_Msk     (0x1UL << I2C_Con_StopErrIF_Pos)
#define I2C_Con_StopErrIF                   I2C_Con_StopErrIF_Msk

#define I2C_Con_DatErrIF_Pos      (5U)
#define I2C_Con_DatErrIF_Msk      (0x1UL << I2C_Con_DatErrIF_Pos)
#define I2C_Con_DatErrIF                    I2C_Con_DatErrIF_Msk

#define I2C_Con_AdrErrIF_Pos      (6U)
#define I2C_Con_AdrErrIF_Msk      (0x1UL << I2C_Con_AdrErrIF_Pos)
#define I2C_Con_AdrErrIF                    I2C_Con_AdrErrIF_Msk

#define I2C_Con_RxOvfIF_Pos       (9U)
#define I2C_Con_RxOvfIF_Msk       (0x1UL << I2C_Con_RxOvfIF_Pos)
#define I2C_Con_RxOvfIF                     I2C_Con_RxOvfIF_Msk

#define I2C_Con_GenCIF_Pos        (10U)
#define I2C_Con_GenCIF_Msk        (0x1UL << I2C_Con_GenCIF_Pos)
#define I2C_Con_GenCIF                      I2C_Con_GenCIF_Msk

#define I2C_Con_StBytIF_Pos       (11U)
#define I2C_Con_StBytIF_Msk       (0x1UL << I2C_Con_StBytIF_Pos)
#define I2C_Con_StBytIF                     I2C_Con_StBytIF_Msk

#define I2C_Con_CBusIF_Pos        (12U)
#define I2C_Con_CBusIF_Msk        (0x1UL << I2C_Con_CBusIF_Pos)
#define I2C_Con_CBusIF                      I2C_Con_CBusIF_Msk

#define I2C_Con_HSIF_Pos          (13U)
#define I2C_Con_HSIF_Msk          (0x1UL << I2C_Con_HSIF_Pos)
#define I2C_Con_HSIF                        I2C_Con_HSIF_Msk

#define I2C_Con_SlvAdrIF_Pos      (14U)
#define I2C_Con_SlvAdrIF_Msk      (0x1UL << I2C_Con_SlvAdrIF_Pos)
#define I2C_Con_SlvAdrIF                    I2C_Con_SlvAdrIF_Msk

#define I2C_Con_SlvNoAckIF_Pos    (15U)
#define I2C_Con_SlvNoAckIF_Msk    (0x1UL << I2C_Con_SlvNoAckIF_Pos)
#define I2C_Con_SlvNoAckIF                  I2C_Con_SlvNoAckIF_Msk

/********************  Bit definition for I2C_Stat register  ******************/
#define I2C_Stat_Slave_Pos        (0U)
#define I2C_Stat_Slave_Msk        (0x1UL << I2C_Stat_Slave_Pos)
#define I2C_Stat_Slave                      I2C_Stat_Slave_Msk

#define I2C_Stat_ReadOp_Pos       (1U)
#define I2C_Stat_ReadOp_Msk       (0x1UL << I2C_Stat_ReadOp_Pos)
#define I2C_Stat_ReadOp                     I2C_Stat_ReadOp_Msk

#define I2C_Stat_TxNow_Pos        (2U)
#define I2C_Stat_TxNow_Msk        (0x1UL << I2C_Stat_TxNow_Pos)
#define I2C_Stat_TxNow                      I2C_Stat_TxNow_Msk

#define I2C_Stat_Host_Pos         (3U)
#define I2C_Stat_Host_Msk         (0x1UL << I2C_Stat_Host_Pos)
#define I2C_Stat_Host                       I2C_Stat_Host_Msk

#define I2C_Stat_Busy_Pos         (4U)
#define I2C_Stat_Busy_Msk         (0x1UL << I2C_Stat_Busy_Pos)
#define I2C_Stat_Busy                       I2C_Stat_Busy_Msk

#define I2C_Stat_RxCnt_Pos        (8U)
#define I2C_Stat_RxCnt_Msk        (0xFUL << I2C_Stat_RxCnt_Pos)

#define I2C_Stat_TxCnt_Pos        (12U)
#define I2C_Stat_TxCnt_Msk        (0xFUL << I2C_Stat_TxCnt_Pos)

/********************  Bit definition for I2C_TDat register  ******************/
#define I2C_TDat_Data_Pos         (0U)
#define I2C_TDat_Data_Msk         (0xFFUL << I2C_TDat_Data_Pos)

#define I2C_TDat_NoAck_Pos        (8U)
#define I2C_TDat_NoAck_Msk        (0x1UL << I2C_TDat_NoAck_Pos)
#define I2C_TDat_NoAck                      I2C_TDat_NoAck_Msk

#define I2C_TDat_Cond_Pos         (9U)
#define I2C_TDat_Cond_Msk         (0x3UL << I2C_TDat_Cond_Pos)
#define I2C_TDat_Cond_Data        (0x0UL << I2C_TDat_Cond_Pos)
#define I2C_TDat_Cond_Start       (0x1UL << I2C_TDat_Cond_Pos)
#define I2C_TDat_Cond_Stop        (0x2UL << I2C_TDat_Cond_Pos)
#define I2C_TDat_Cond_Slv         (0x3UL << I2C_TDat_Cond_Pos)

/********************  Bit definition for I2C_RDat register  ******************/
#define I2C_RDat_Data_Pos         (0U)
#define I2C_RDat_Data_Msk         (0xFFUL << I2C_RDat_Data_Pos)

#define I2C_RDat_NoAck_Pos        (8U)
#define I2C_RDat_NoAck_Msk        (0x1UL << I2C_RDat_NoAck_Pos)
#define I2C_RDat_NoAck                      I2C_RDat_NoAck_Msk


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
