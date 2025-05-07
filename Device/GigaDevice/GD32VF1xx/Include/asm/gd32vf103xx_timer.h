/*
 * Copyright (C) 2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef GD32VF103XX_TIMER_H
#define GD32VF103XX_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/gd32vf103xx.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define TIMER0  ((TIMER0_t *) TIMER0_BASE)    /*!< TIMER0 configuration struct */
#define TIMER1  ((TIMER1_t *) TIMER1_BASE)    /*!< TIMER1 configuration struct */
#define TIMER2  ((TIMER2_t *) TIMER2_BASE)    /*!< TIMER2 configuration struct */
#define TIMER3  ((TIMER3_t *) TIMER3_BASE)    /*!< TIMER3 configuration struct */
#define TIMER4  ((TIMER4_t *) TIMER4_BASE)    /*!< TIMER4 configuration struct */
#define TIMER5  ((TIMER5_t *) TIMER5_BASE)    /*!< TIMER5 configuration struct */
#define TIMER6  ((TIMER6_t *) TIMER6_BASE)    /*!< TIMER6 configuration struct */

/**
 * @brief Bit definition for CTL0 register
 */
#define TIM_CTL0_CEN_Pos                  (0U)
#define TIM_CTL0_CEN_Msk                  (0x1UL << TIM_CTL0_CEN_Pos)

#define TIM_CTL0_UPDIS_Pos                (1U)
#define TIM_CTL0_UPDIS_Msk                (0x1UL << TIM_CTL0_UPDIS_Pos)

#define TIM_CTL0_UPS_Pos                  (2U)
#define TIM_CTL0_UPS_Msk                  (0x1UL << TIM_CTL0_UPS_Pos)

#define TIM_CTL0_SPM_Pos                  (3U)
#define TIM_CTL0_SPM_Msk                  (0x1UL << TIM_CTL0_SPM_Pos)

#define TIM_CTL0_DIR_Pos                  (4U)
#define TIM_CTL0_DIR_Msk                  (0x1UL << TIM_CTL0_DIR_Pos)

#define TIM_CTL0_CAM_Pos                  (5U)
#define TIM_CTL0_CAM_Msk                  (0x3UL << TIM_CTL0_CAM_Pos)

#define TIM_CTL0_ARSE_Pos                 (7U)
#define TIM_CTL0_ARSE_Msk                 (0x1UL << TIM_CTL0_ARSE_Pos)

#define TIM_CTL0_CKDIV_Pos                (8U)
#define TIM_CTL0_CKDIV_Msk                (0x3UL << TIM_CTL0_CKDIV_Pos)

/**
 * @brief Bit definition for CTL1 register
 */
#define TIM_CTL1_CCSE_Pos                 (0U)
#define TIM_CTL1_CCSE_Msk                 (0x1UL << TIM_CTL1_CCSE_Pos)

#define TIM_CTL1_CCUC_Pos                 (2U)
#define TIM_CTL1_CCUC_Msk                 (0x1UL << TIM_CTL1_CCUC_Pos)

#define TIM_CTL1_DMAS_Pos                 (3U)
#define TIM_CTL1_DMAS_Msk                 (0x1UL << TIM_CTL1_DMAS_Pos)

#define TIM_CTL1_MMC_Pos                  (4U)
#define TIM_CTL1_MMC_Msk                  (0x7UL << TIM_CTL1_MMC_Pos)

#define TIM_CTL1_TI0S_Pos                 (7U)
#define TIM_CTL1_TI0S_Msk                 (0x1UL << TIM_CTL1_TI0S_Pos)

#define TIM_CTL1_ISO0_Pos                 (8U)
#define TIM_CTL1_ISO0_Msk                 (0x1UL << TIM_CTL1_ISO0_Pos)

#define TIM_CTL1_ISO0N_Pos                (9U)
#define TIM_CTL1_ISO0N_Msk                (0x1UL << TIM_CTL1_ISO0N_Pos)

#define TIM_CTL1_ISO1_Pos                 (10U)
#define TIM_CTL1_ISO1_Msk                 (0x1UL << TIM_CTL1_ISO1_Pos)

#define TIM_CTL1_ISO1N_Pos                (11U)
#define TIM_CTL1_ISO1N_Msk                (0x1UL << TIM_CTL1_ISO1N_Pos)

#define TIM_CTL1_ISO2_Pos                 (12U)
#define TIM_CTL1_ISO2_Msk                 (0x1UL << TIM_CTL1_ISO2_Pos)

#define TIM_CTL1_ISO2N_Pos                (13U)
#define TIM_CTL1_ISO2N_Msk                (0x1UL << TIM_CTL1_ISO2N_Pos)

#define TIM_CTL1_ISO3_Pos                 (14U)
#define TIM_CTL1_ISO3_Msk                 (0x1UL << TIM_CTL1_ISO3_Pos)

/**
 * @brief Bit definition for SMCFG register
 */
#define TIM_SMCFG_SMC_Pos                 (0U)
#define TIM_SMCFG_SMC_Msk                 (0x7UL << TIM_SMCFG_SMC_Pos)

#define TIM_SMCFG_TRGS_Pos                (4U)
#define TIM_SMCFG_TRGS_Msk                (0x7UL << TIM_SMCFG_TRGS_Pos)

#define TIM_SMCFG_MSM_Pos                 (7U)
#define TIM_SMCFG_MSM_Msk                 (0x1UL << TIM_SMCFG_MSM_Pos)

#define TIM_SMCFG_ETFC_Pos                (8U)
#define TIM_SMCFG_ETFC_Msk                (0xFUL << TIM_SMCFG_ETFC_Pos)

#define TIM_SMCFG_ETPSC_Pos               (12U)
#define TIM_SMCFG_ETPSC_Msk               (0x3UL << TIM_SMCFG_ETPSC_Pos)

#define TIM_SMCFG_SMC1_Pos                (14U)
#define TIM_SMCFG_SMC1_Msk                (0x1UL << TIM_SMCFG_SMC1_Pos)

#define TIM_SMCFG_ETP_Pos                 (15U)
#define TIM_SMCFG_ETP_Msk                 (0x1UL << TIM_SMCFG_ETP_Pos)

/**
 * @brief Bit definition for DMAINTEN register
 */
#define TIM_DMAINTEN_UPIE_Pos             (0U)
#define TIM_DMAINTEN_UPIE_Msk             (0x1UL << TIM_DMAINTEN_UPIE_Pos)

#define TIM_DMAINTEN_CH0IE_Pos            (1U)
#define TIM_DMAINTEN_CH0IE_Msk            (0x1UL << TIM_DMAINTEN_CH0IE_Pos)

#define TIM_DMAINTEN_CH1IE_Pos            (2U)
#define TIM_DMAINTEN_CH1IE_Msk            (0x1UL << TIM_DMAINTEN_CH1IE_Pos)

#define TIM_DMAINTEN_CH2IE_Pos            (3U)
#define TIM_DMAINTEN_CH2IE_Msk            (0x1UL << TIM_DMAINTEN_CH2IE_Pos)

#define TIM_DMAINTEN_CH3IE_Pos            (4U)
#define TIM_DMAINTEN_CH3IE_Msk            (0x1UL << TIM_DMAINTEN_CH3IE_Pos)

#define TIM_DMAINTEN_CMTIE_Pos            (5U)
#define TIM_DMAINTEN_CMTIE_Msk            (0x1UL << TIM_DMAINTEN_CMTIE_Pos)

#define TIM_DMAINTEN_TRGIE_Pos            (6U)
#define TIM_DMAINTEN_TRGIE_Msk            (0x1UL << TIM_DMAINTEN_TRGIE_Pos)

#define TIM_DMAINTEN_BRKIE_Pos            (7U)
#define TIM_DMAINTEN_BRKIE_Msk            (0x1UL << TIM_DMAINTEN_BRKIE_Pos)

#define TIM_DMAINTEN_UPDEN_Pos            (8U)
#define TIM_DMAINTEN_UPDEN_Msk            (0x1UL << TIM_DMAINTEN_UPDEN_Pos)

#define TIM_DMAINTEN_CH0DEN_Pos           (9U)
#define TIM_DMAINTEN_CH0DEN_Msk           (0x1UL << TIM_DMAINTEN_CH0DEN_Pos)

#define TIM_DMAINTEN_CH1DEN_Pos           (10U)
#define TIM_DMAINTEN_CH1DEN_Msk           (0x1UL << TIM_DMAINTEN_CH1DEN_Pos)

#define TIM_DMAINTEN_CH2DEN_Pos           (11U)
#define TIM_DMAINTEN_CH2DEN_Msk           (0x1UL << TIM_DMAINTEN_CH2DEN_Pos)

#define TIM_DMAINTEN_CH3DEN_Pos           (12U)
#define TIM_DMAINTEN_CH3DEN_Msk           (0x1UL << TIM_DMAINTEN_CH3DEN_Pos)

#define TIM_DMAINTEN_CMTDEN_Pos           (13U)
#define TIM_DMAINTEN_CMTDEN_Msk           (0x1UL << TIM_DMAINTEN_CMTDEN_Pos)

#define TIM_DMAINTEN_TRGDEN_Pos           (14U)
#define TIM_DMAINTEN_TRGDEN_Msk           (0x1UL << TIM_DMAINTEN_TRGDEN_Pos)

/**
 * @brief Bit definition for INTF register
 */
#define TIM_INTF_UPIF_Pos                 (0U)
#define TIM_INTF_UPIF_Msk                 (0x1UL << TIM_INTF_UPIF_Pos)

#define TIM_INTF_CH0IF_Pos                (1U)
#define TIM_INTF_CH0IF_Msk                (0x1UL << TIM_INTF_CH0IF_Pos)

#define TIM_INTF_CH1IF_Pos                (2U)
#define TIM_INTF_CH1IF_Msk                (0x1UL << TIM_INTF_CH1IF_Pos)

#define TIM_INTF_CH2IF_Pos                (3U)
#define TIM_INTF_CH2IF_Msk                (0x1UL << TIM_INTF_CH2IF_Pos)

#define TIM_INTF_CH3IF_Pos                (4U)
#define TIM_INTF_CH3IF_Msk                (0x1UL << TIM_INTF_CH3IF_Pos)

#define TIM_INTF_CMTIF_Pos                (5U)
#define TIM_INTF_CMTIF_Msk                (0x1UL << TIM_INTF_CMTIF_Pos)

#define TIM_INTF_TRGIF_Pos                (6U)
#define TIM_INTF_TRGIF_Msk                (0x1UL << TIM_INTF_TRGIF_Pos)

#define TIM_INTF_BRKIF_Pos                (7U)
#define TIM_INTF_BRKIF_Msk                (0x1UL << TIM_INTF_BRKIF_Pos)

#define TIM_INTF_CH0OF_Pos                (9U)
#define TIM_INTF_CH0OF_Msk                (0x1UL << TIM_INTF_CH0OF_Pos)

#define TIM_INTF_CH1OF_Pos                (10U)
#define TIM_INTF_CH1OF_Msk                (0x1UL << TIM_INTF_CH1OF_Pos)

#define TIM_INTF_CH2OF_Pos                (11U)
#define TIM_INTF_CH2OF_Msk                (0x1UL << TIM_INTF_CH2OF_Pos)

#define TIM_INTF_CH3OF_Pos                (12U)
#define TIM_INTF_CH3OF_Msk                (0x1UL << TIM_INTF_CH3OF_Pos)

/**
 * @brief Bit definition for SWEVG register
 */
#define TIM_SWEVG_UPG_Pos                 (0U)
#define TIM_SWEVG_UPG_Msk                 (0x1UL << TIM_SWEVG_UPG_Pos)

#define TIM_SWEVG_CH0G_Pos                (1U)
#define TIM_SWEVG_CH0G_Msk                (0x1UL << TIM_SWEVG_CH0G_Pos)

#define TIM_SWEVG_CH1G_Pos                (2U)
#define TIM_SWEVG_CH1G_Msk                (0x1UL << TIM_SWEVG_CH1G_Pos)

#define TIM_SWEVG_CH2G_Pos                (3U)
#define TIM_SWEVG_CH2G_Msk                (0x1UL << TIM_SWEVG_CH2G_Pos)

#define TIM_SWEVG_CH3G_Pos                (4U)
#define TIM_SWEVG_CH3G_Msk                (0x1UL << TIM_SWEVG_CH3G_Pos)

#define TIM_SWEVG_CMTG_Pos                (5U)
#define TIM_SWEVG_CMTG_Msk                (0x1UL << TIM_SWEVG_CMTG_Pos)

#define TIM_SWEVG_TRGG_Pos                (6U)
#define TIM_SWEVG_TRGG_Msk                (0x1UL << TIM_SWEVG_TRGG_Pos)

#define TIM_SWEVG_BRKG_Pos                (7U)
#define TIM_SWEVG_BRKG_Msk                (0x1UL << TIM_SWEVG_BRKG_Pos)

/**
 * @brief Bit definition for CHCTL0 register
 */
#define TIM_CHCTL0_CH0MS_Pos              (0U)
#define TIM_CHCTL0_CH0MS_Msk              (0x3UL << TIM_CHCTL0_CH0MS_Pos)

#define TIM_CHCTL0_CH0COMFEN_Pos          (2U)
#define TIM_CHCTL0_CH0COMFEN_Msk          (0x1UL << TIM_CHCTL0_CH0COMFEN_Pos)

#define TIM_CHCTL0_CH0COMSEN_Pos          (3U)
#define TIM_CHCTL0_CH0COMSEN_Msk          (0x1UL << TIM_CHCTL0_CH0COMSEN_Pos)

#define TIM_CHCTL0_CH0CAPPSC_Pos          (2U)
#define TIM_CHCTL0_CH0CAPPSC_Msk          (0x3UL << TIM_CHCTL0_CH0CAPPSC_Pos)

#define TIM_CHCTL0_CH0COMCTL_Pos          (4U)
#define TIM_CHCTL0_CH0COMCTL_Msk          (0x7UL << TIM_CHCTL0_CH0COMCTL_Pos)

#define TIM_CHCTL0_CH0COMCEN_Pos          (7U)
#define TIM_CHCTL0_CH0COMCEN_Msk          (0x7UL << TIM_CHCTL0_CH0COMCEN_Pos)

#define TIM_CHCTL0_CH0CAPFLT_Pos          (4U)
#define TIM_CHCTL0_CH0CAPFLT_Msk          (0xFUL << TIM_CHCTL0_CH0CAPFLT_Pos)

#define TIM_CHCTL0_CH1MS_Pos              (8U)
#define TIM_CHCTL0_CH1MS_Msk              (0x3UL << TIM_CHCTL0_CH1MS_Pos)

#define TIM_CHCTL0_CH1COMFEN_Pos          (10U)
#define TIM_CHCTL0_CH1COMFEN_Msk          (0x1UL << TIM_CHCTL0_CH1COMFEN_Pos)

#define TIM_CHCTL0_CH1COMSEN_Pos          (11U)
#define TIM_CHCTL0_CH1COMSEN_Msk          (0x1UL << TIM_CHCTL0_CH1COMSEN_Pos)

#define TIM_CHCTL0_CH1CAPPSC_Pos          (10U)
#define TIM_CHCTL0_CH1CAPPSC_Msk          (0x3UL << TIM_CHCTL0_CH1CAPPSC_Pos)

#define TIM_CHCTL0_CH1COMCTL_Pos          (12U)
#define TIM_CHCTL0_CH1COMCTL_Msk          (0x7UL << TIM_CHCTL0_CH1COMCTL_Pos)

#define TIM_CHCTL0_CH1COMCEN_Pos          (15U)
#define TIM_CHCTL0_CH1COMCEN_Msk          (0x7UL << TIM_CHCTL0_CH1COMCEN_Pos)

#define TIM_CHCTL0_CH1CAPFLT_Pos          (12U)
#define TIM_CHCTL0_CH1CAPFLT_Msk          (0xFUL << TIM_CHCTL0_CH1CAPFLT_Pos)

/**
 * @brief Bit definition for CHCTL1 register
 */
#define TIM_CHCTL1_CH2MS_Pos              (0U)
#define TIM_CHCTL1_CH2MS_Msk              (0x3UL << TIM_CHCTL1_CH2MS_Pos)

#define TIM_CHCTL1_CH2COMFEN_Pos          (2U)
#define TIM_CHCTL1_CH2COMFEN_Msk          (0x1UL << TIM_CHCTL1_CH2COMFEN_Pos)

#define TIM_CHCTL1_CH2COMSEN_Pos          (3U)
#define TIM_CHCTL1_CH2COMSEN_Msk          (0x1UL << TIM_CHCTL1_CH2COMSEN_Pos)

#define TIM_CHCTL1_CH2CAPPSC_Pos          (2U)
#define TIM_CHCTL1_CH2CAPPSC_Msk          (0x3UL << TIM_CHCTL1_CH2CAPPSC_Pos)

#define TIM_CHCTL1_CH2COMCTL_Pos          (4U)
#define TIM_CHCTL1_CH2COMCTL_Msk          (0x7UL << TIM_CHCTL1_CH2COMCTL_Pos)

#define TIM_CHCTL1_CH2COMCEN_Pos          (7U)
#define TIM_CHCTL1_CH2COMCEN_Msk          (0x7UL << TIM_CHCTL1_CH2COMCEN_Pos)

#define TIM_CHCTL1_CH2CAPFLT_Pos          (4U)
#define TIM_CHCTL1_CH2CAPFLT_Msk          (0xFUL << TIM_CHCTL1_CH2CAPFLT_Pos)

#define TIM_CHCTL1_CH3MS_Pos              (8U)
#define TIM_CHCTL1_CH3MS_Msk              (0x3UL << TIM_CHCTL1_CH3MS_Pos)

#define TIM_CHCTL1_CH3COMFEN_Pos          (10U)
#define TIM_CHCTL1_CH3COMFEN_Msk          (0x1UL << TIM_CHCTL1_CH3COMFEN_Pos)

#define TIM_CHCTL1_CH3COMSEN_Pos          (11U)
#define TIM_CHCTL1_CH3COMSEN_Msk          (0x1UL << TIM_CHCTL1_CH3COMSEN_Pos)

#define TIM_CHCTL1_CH3CAPPSC_Pos          (10U)
#define TIM_CHCTL1_CH3CAPPSC_Msk          (0x3UL << TIM_CHCTL1_CH3CAPPSC_Pos)

#define TIM_CHCTL1_CH3COMCTL_Pos          (12U)
#define TIM_CHCTL1_CH3COMCTL_Msk          (0x7UL << TIM_CHCTL1_CH3COMCTL_Pos)

#define TIM_CHCTL1_CH3COMCEN_Pos          (15U)
#define TIM_CHCTL1_CH3COMCEN_Msk          (0x7UL << TIM_CHCTL1_CH3COMCEN_Pos)

#define TIM_CHCTL1_CH3CAPFLT_Pos          (12U)
#define TIM_CHCTL1_CH3CAPFLT_Msk          (0xFUL << TIM_CHCTL1_CH3CAPFLT_Pos)

/**
 * @brief Bit definition for CHCTL2 register
 */
#define TIM_CHCTL2_CH0EN_Pos              (0U)
#define TIM_CHCTL2_CH0EN_Msk              (0x1UL << TIM_CHCTL2_CH0EN_Pos)

#define TIM_CHCTL2_CH0P_Pos               (1U)
#define TIM_CHCTL2_CH0P_Msk               (0x1UL << TIM_CHCTL2_CH0P_Pos)

#define TIM_CHCTL2_CH0NEN_Pos             (2U)
#define TIM_CHCTL2_CH0NEN_Msk             (0x1UL << TIM_CHCTL2_CH0NEN_Pos)

#define TIM_CHCTL2_CH0NP_Pos              (3U)
#define TIM_CHCTL2_CH0NP_Msk              (0x1UL << TIM_CHCTL2_CH0NP_Pos)

#define TIM_CHCTL2_CH1EN_Pos              (4U)
#define TIM_CHCTL2_CH1EN_Msk              (0x1UL << TIM_CHCTL2_CH1EN_Pos)

#define TIM_CHCTL2_CH1P_Pos               (5U)
#define TIM_CHCTL2_CH1P_Msk               (0x1UL << TIM_CHCTL2_CH1P_Pos)

#define TIM_CHCTL2_CH1NEN_Pos             (6U)
#define TIM_CHCTL2_CH1NEN_Msk             (0x1UL << TIM_CHCTL2_CH1NEN_Pos)

#define TIM_CHCTL2_CH1NP_Pos              (7U)
#define TIM_CHCTL2_CH1NP_Msk              (0x1UL << TIM_CHCTL2_CH1NP_Pos)

#define TIM_CHCTL2_CH2EN_Pos              (8U)
#define TIM_CHCTL2_CH2EN_Msk              (0x1UL << TIM_CHCTL2_CH2EN_Pos)

#define TIM_CHCTL2_CH2P_Pos               (9U)
#define TIM_CHCTL2_CH2P_Msk               (0x1UL << TIM_CHCTL2_CH2P_Pos)

#define TIM_CHCTL2_CH2NEN_Pos             (10U)
#define TIM_CHCTL2_CH2NEN_Msk             (0x1UL << TIM_CHCTL2_CH2NEN_Pos)

#define TIM_CHCTL2_CH2NP_Pos              (11U)
#define TIM_CHCTL2_CH2NP_Msk              (0x1UL << TIM_CHCTL2_CH2NP_Pos)

#define TIM_CHCTL2_CH3EN_Pos              (12U)
#define TIM_CHCTL2_CH3EN_Msk              (0x1UL << TIM_CHCTL2_CH3EN_Pos)

#define TIM_CHCTL2_CH3P_Pos               (13U)
#define TIM_CHCTL2_CH3P_Msk               (0x1UL << TIM_CHCTL2_CH3P_Pos)

/**
 * @brief Bit definition for CNT register
 */
#define TIM_CNT_CNT_Pos                   (0U)
#define TIM_CNT_CNT_Msk                   (0xFFFFUL << TIM_CNT_CNT_Pos)

/**
 * @brief Bit definition for PSC register
 */
#define TIM_PSC_PSC_Pos                   (0U)
#define TIM_PSC_PSC_Msk                   (0xFFFFUL << TIM_PSC_PSC_Pos)

/**
 * @brief Bit definition for CAR register
 */
#define TIM_CAR_CARL_Pos                  (0U)
#define TIM_CAR_CARL_Msk                  (0xFFFFUL << TIM_CAR_CARL_Pos)

/**
 * @brief Bit definition for CREP register
 */
#define TIM_CREP_CREP_Pos                 (0U)
#define TIM_CREP_CREP_Msk                 (0xFFUL << TIM_CREP_CREP_Pos)

/**
 * @brief Bit definition for CH0CV register
 */
#define TIM_CH0CV_CH0VAL_Pos              (0U)
#define TIM_CH0CV_CH0VAL_Msk              (0xFFFFUL << TIM_CH0CV_CH0VAL_Pos)

/**
 * @brief Bit definition for CH1CV register
 */
#define TIM_CH1CV_CH1VAL_Pos              (0U)
#define TIM_CH1CV_CH1VAL_Msk              (0xFFFFUL << TIM_CH1CV_CH1VAL_Pos)

/**
 * @brief Bit definition for CH2CV register
 */
#define TIM_CH2CV_CH2VAL_Pos              (0U)
#define TIM_CH2CV_CH2VAL_Msk              (0xFFFFUL << TIM_CH2CV_CH2VAL_Pos)

/**
 * @brief Bit definition for CH3CV register
 */
#define TIM_CH3CV_CH3VAL_Pos              (0U)
#define TIM_CH3CV_CH3VAL_Msk              (0xFFFFUL << TIM_CH3CV_CH3VAL_Pos)

/**
 * @brief Bit definition for CCHP register
 */
#define TIM_CCHP_DTCFG_Pos                (0U)
#define TIM_CCHP_DTCFG_Msk                (0xFFUL << TIM_CCHP_DTCFG_Pos)

#define TIM_CCHP_PROT_Pos                 (8U)
#define TIM_CCHP_PROT_Msk                 (0x3UL << TIM_CCHP_PROT_Pos)

#define TIM_CCHP_IOS_Pos                  (10U)
#define TIM_CCHP_IOS_Msk                  (0x1UL << TIM_CCHP_IOS_Pos)

#define TIM_CCHP_ROS_Pos                  (11U)
#define TIM_CCHP_ROS_Msk                  (0x1UL << TIM_CCHP_ROS_Pos)

#define TIM_CCHP_BRKEN_Pos                (12U)
#define TIM_CCHP_BRKEN_Msk                (0x1UL << TIM_CCHP_BRKEN_Pos)

#define TIM_CCHP_BRKP_Pos                 (13U)
#define TIM_CCHP_BRKP_Msk                 (0x1UL << TIM_CCHP_BRKP_Pos)

#define TIM_CCHP_OAEN_Pos                 (14U)
#define TIM_CCHP_OAEN_Msk                 (0x1UL << TIM_CCHP_OAEN_Pos)

#define TIM_CCHP_POEN_Pos                 (15U)
#define TIM_CCHP_POEN_Msk                 (0x1UL << TIM_CCHP_POEN_Pos)

/**
 * @brief Bit definition for DMACFG register
 */
#define TIM_DMACFG_DMATA_Pos              (0U)
#define TIM_DMACFG_DMATA_Msk              (0x1FUL << TIM_DMACFG_DMATA_Pos)

#define TIM_DMACFG_DMATC_Pos              (8U)
#define TIM_DMACFG_DMATC_Msk              (0x1FUL << TIM_DMACFG_DMATC_Pos)

/**
 * @brief Bit definition for DMATB register
 */
#define TIM_DMATB_DMATB_Pos               (0U)
#define TIM_DMATB_DMATB_Msk               (0xFFFFUL << TIM_DMATB_DMATB_Pos)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct TIMER0_s {
  __IOM uint32_t CTL0;    /*!< Offset: 0x000 (R/W) Control register 0 */
  __IOM uint32_t CTL1;    /*!< Offset: 0x004 (R/W) Control register 1 */
  __IOM uint32_t SMCFG;   /*!< Offset: 0x008 (R/W) Slave mode configuration register */
  __IOM uint32_t DMAINTEN;/*!< Offset: 0x00C (R/W) DMA and interrupt enable register */
  __IOM uint32_t INTF;    /*!< Offset: 0x010 (R/W) Interrupt flag register */
  __OM  uint32_t SWEVG;   /*!< Offset: 0x014 ( /W) Software event generation register */
  __IOM uint32_t CHCTL0;  /*!< Offset: 0x018 (R/W) Channel control register 0 */
  __IOM uint32_t CHCTL1;  /*!< Offset: 0x01C (R/W) Channel control register 1 */
  __IOM uint32_t CHCTL2;  /*!< Offset: 0x020 (R/W) Channel control register 2 */
  __IOM uint32_t CNT;     /*!< Offset: 0x024 (R/W) Counter register */
  __IOM uint32_t PSC;     /*!< Offset: 0x028 (R/W) Prescaler register */
  __IOM uint32_t CAR;     /*!< Offset: 0x02C (R/W) Counter auto reload register */
  __IOM uint32_t CREP;    /*!< Offset: 0x030 (R/W) Counter repetition register */
  __IOM uint32_t CH0CV;   /*!< Offset: 0x034 (R/W) Channel 0 capture/compare value register */
  __IOM uint32_t CH1CV;   /*!< Offset: 0x038 (R/W) Channel 1 capture/compare value register */
  __IOM uint32_t CH2CV;   /*!< Offset: 0x03C (R/W) Channel 2 capture/compare value register */
  __IOM uint32_t CH3CV;   /*!< Offset: 0x040 (R/W) Channel 3 capture/compare value register */
  __IOM uint32_t CCHP;    /*!< Offset: 0x044 (R/W) Complementary channel protection register */
  __IOM uint32_t DMACFG;  /*!< Offset: 0x048 (R/W) DMA configuration register */
  __IOM uint32_t DMATB;   /*!< Offset: 0x04C (R/W) DMA transfer buffer register */
} TIMER0_t;

typedef struct TIMER1_s { // @suppress("Multiple variable declaration")
  __IOM uint32_t CTL0;    /*!< Offset: 0x000 (R/W) Control register 0 */
  __IOM uint32_t CTL1;    /*!< Offset: 0x004 (R/W) Control register 1 */
  __IOM uint32_t SMCFG;   /*!< Offset: 0x008 (R/W) Slave mode configuration register */
  __IOM uint32_t DMAINTEN;/*!< Offset: 0x00C (R/W) DMA and interrupt enable register */
  __IOM uint32_t INTF;    /*!< Offset: 0x010 (R/W) Interrupt flag register */
  __OM  uint32_t SWEVG;   /*!< Offset: 0x014 ( /W) Software event generation register */
  __IOM uint32_t CHCTL0;  /*!< Offset: 0x018 (R/W) Channel control register 0 */
  __IOM uint32_t CHCTL1;  /*!< Offset: 0x01C (R/W) Channel control register 1 */
  __IOM uint32_t CHCTL2;  /*!< Offset: 0x020 (R/W) Channel control register 2 */
  __IOM uint32_t CNT;     /*!< Offset: 0x024 (R/W) Counter register */
  __IOM uint32_t PSC;     /*!< Offset: 0x028 (R/W) Prescaler register */
  __IOM uint32_t CAR;     /*!< Offset: 0x02C (R/W) Counter auto reload register */
  RESERVED(0, uint32_t);
  __IOM uint32_t CH0CV;   /*!< Offset: 0x034 (R/W) Channel 0 capture/compare value register */
  __IOM uint32_t CH1CV;   /*!< Offset: 0x038 (R/W) Channel 1 capture/compare value register */
  __IOM uint32_t CH2CV;   /*!< Offset: 0x03C (R/W) Channel 2 capture/compare value register */
  __IOM uint32_t CH3CV;   /*!< Offset: 0x040 (R/W) Channel 3 capture/compare value register */
  RESERVED(1, uint32_t);
  __IOM uint32_t DMACFG;  /*!< Offset: 0x048 (R/W) DMA configuration register */
  __IOM uint32_t DMATB;   /*!< Offset: 0x04C (R/W) DMA transfer buffer register */
} TIMER1_t, TIMER2_t, TIMER3_t, TIMER4_t;

typedef struct TIMER5_s { // @suppress("Multiple variable declaration")
  __IOM uint32_t CTL0;    /*!< Offset: 0x000 (R/W) Control register 0 */
  __IOM uint32_t CTL1;    /*!< Offset: 0x004 (R/W) Control register 1 */
  RESERVED(0, uint32_t);
  __IOM uint32_t DMAINTEN;/*!< Offset: 0x00C (R/W) DMA and interrupt enable register */
  __IOM uint32_t INTF;    /*!< Offset: 0x010 (R/W) Interrupt flag register */
  __OM  uint32_t SWEVG;   /*!< Offset: 0x014 ( /W) Software event generation register */
  RESERVED(1[3], uint32_t);
  __IOM uint32_t CNT;     /*!< Offset: 0x024 (R/W) Counter register */
  __IOM uint32_t PSC;     /*!< Offset: 0x028 (R/W) Prescaler register */
  __IOM uint32_t CAR;     /*!< Offset: 0x02C (R/W) Counter auto reload register */
} TIMER5_t, TIMER6_t;

#ifdef __cplusplus
}
#endif

#endif  /* GD32VF103XX_TIMER_H */
