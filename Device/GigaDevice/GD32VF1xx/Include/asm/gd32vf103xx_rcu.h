/*
 * Copyright (C) 2024-2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef GD32VF103XX_RCU_H
#define GD32VF103XX_RCU_H

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

#define RCU       ((RCU_t *) RCU_BASE)        /*!< RCU configuration struct   */

/**
 * @brief Bit definition for AHBEN register
 */
#define RCU_AHBEN_DMA0EN_Pos              (0U)
#define RCU_AHBEN_DMA0EN_Msk              (0x1UL << RCU_AHBEN_DMA0EN_Pos)

#define RCU_AHBEN_DMA1EN_Pos              (1U)
#define RCU_AHBEN_DMA1EN_Msk              (0x1UL << RCU_AHBEN_DMA1EN_Pos)

#define RCU_AHBEN_SRAMSPEN_Pos            (2U)
#define RCU_AHBEN_SRAMSPEN_Msk            (0x1UL << RCU_AHBEN_SRAMSPEN_Pos)

#define RCU_AHBEN_FMCSPEN_Pos             (4U)
#define RCU_AHBEN_FMCSPEN_Msk             (0x1UL << RCU_AHBEN_FMCSPEN_Pos)

#define RCU_AHBEN_CRCEN_Pos               (6U)
#define RCU_AHBEN_CRCEN_Msk               (0x1UL << RCU_AHBEN_CRCEN_Pos)

#define RCU_AHBEN_EXMCEN_Pos              (8U)
#define RCU_AHBEN_EXMCEN_Msk              (0x1UL << RCU_AHBEN_EXMCEN_Pos)

#define RCU_AHBEN_USBFSEN_Pos             (12U)
#define RCU_AHBEN_USBFSEN_Msk             (0x1UL << RCU_AHBEN_USBFSEN_Pos)

/**
 * @brief Bit definition for APB2EN register
 */
#define RCU_APB2EN_AFEN_Pos               (0U)
#define RCU_APB2EN_AFEN_Msk               (0x1UL << RCU_APB2EN_AFEN_Pos)

#define RCU_APB2EN_PAEN_Pos               (2U)
#define RCU_APB2EN_PAEN_Msk               (0x1UL << RCU_APB2EN_PAEN_Pos)

#define RCU_APB2EN_PBEN_Pos               (3U)
#define RCU_APB2EN_PBEN_Msk               (0x1UL << RCU_APB2EN_PBEN_Pos)

#define RCU_APB2EN_PCEN_Pos               (4U)
#define RCU_APB2EN_PCEN_Msk               (0x1UL << RCU_APB2EN_PCEN_Pos)

#define RCU_APB2EN_PDEN_Pos               (5U)
#define RCU_APB2EN_PDEN_Msk               (0x1UL << RCU_APB2EN_PDEN_Pos)

#define RCU_APB2EN_PEEN_Pos               (6U)
#define RCU_APB2EN_PEEN_Msk               (0x1UL << RCU_APB2EN_PEEN_Pos)

#define RCU_APB2EN_ADC0EN_Pos             (9U)
#define RCU_APB2EN_ADC0EN_Msk             (0x1UL << RCU_APB2EN_ADC0EN_Pos)

#define RCU_APB2EN_ADC1EN_Pos             (10U)
#define RCU_APB2EN_ADC1EN_Msk             (0x1UL << RCU_APB2EN_ADC1EN_Pos)

#define RCU_APB2EN_TIMER0EN_Pos           (11U)
#define RCU_APB2EN_TIMER0EN_Msk           (0x1UL << RCU_APB2EN_TIMER0EN_Pos)

#define RCU_APB2EN_SPI0EN_Pos             (12U)
#define RCU_APB2EN_SPI0EN_Msk             (0x1UL << RCU_APB2EN_SPI0EN_Pos)

#define RCU_APB2EN_USART0EN_Pos           (14U)
#define RCU_APB2EN_USART0EN_Msk           (0x1UL << RCU_APB2EN_USART0EN_Pos)

/**
 * @brief Bit definition for APB1EN register
 */
#define RCU_APB1EN_TIMER1EN_Pos           (0U)
#define RCU_APB1EN_TIMER1EN_Msk           (0x1UL << RCU_APB1EN_TIMER1EN_Pos)

#define RCU_APB1EN_TIMER2EN_Pos           (1U)
#define RCU_APB1EN_TIMER2EN_Msk           (0x1UL << RCU_APB1EN_TIMER2EN_Pos)

#define RCU_APB1EN_TIMER3EN_Pos           (2U)
#define RCU_APB1EN_TIMER3EN_Msk           (0x1UL << RCU_APB1EN_TIMER3EN_Pos)

#define RCU_APB1EN_TIMER4EN_Pos           (3U)
#define RCU_APB1EN_TIMER4EN_Msk           (0x1UL << RCU_APB1EN_TIMER4EN_Pos)

#define RCU_APB1EN_TIMER5EN_Pos           (4U)
#define RCU_APB1EN_TIMER5EN_Msk           (0x1UL << RCU_APB1EN_TIMER5EN_Pos)

#define RCU_APB1EN_TIMER6EN_Pos           (5U)
#define RCU_APB1EN_TIMER6EN_Msk           (0x1UL << RCU_APB1EN_TIMER6EN_Pos)

#define RCU_APB1EN_WWDGTEN_Pos            (11U)
#define RCU_APB1EN_WWDGTEN_Msk            (0x1UL << RCU_APB1EN_WWDGTEN_Pos)

#define RCU_APB1EN_SPI1EN_Pos             (14U)
#define RCU_APB1EN_SPI1EN_Msk             (0x1UL << RCU_APB1EN_SPI1EN_Pos)

#define RCU_APB1EN_SPI2EN_Pos             (15U)
#define RCU_APB1EN_SPI2EN_Msk             (0x1UL << RCU_APB1EN_SPI2EN_Pos)

#define RCU_APB1EN_USART1EN_Pos           (17U)
#define RCU_APB1EN_USART1EN_Msk           (0x1UL << RCU_APB1EN_USART1EN_Pos)

#define RCU_APB1EN_USART2EN_Pos           (18U)
#define RCU_APB1EN_USART2EN_Msk           (0x1UL << RCU_APB1EN_USART2EN_Pos)

#define RCU_APB1EN_USART3EN_Pos           (19U)
#define RCU_APB1EN_USART3EN_Msk           (0x1UL << RCU_APB1EN_USART3EN_Pos)

#define RCU_APB1EN_USART4EN_Pos           (20U)
#define RCU_APB1EN_USART4EN_Msk           (0x1UL << RCU_APB1EN_USART4EN_Pos)

#define RCU_APB1EN_I2C0EN_Pos             (21U)
#define RCU_APB1EN_I2C0EN_Msk             (0x1UL << RCU_APB1EN_I2C0EN_Pos)

#define RCU_APB1EN_I2C1EN_Pos             (22U)
#define RCU_APB1EN_I2C1EN_Msk             (0x1UL << RCU_APB1EN_I2C1EN_Pos)

#define RCU_APB1EN_CAN0EN_Pos             (25U)
#define RCU_APB1EN_CAN0EN_Msk             (0x1UL << RCU_APB1EN_CAN0EN_Pos)

#define RCU_APB1EN_CAN1EN_Pos             (26U)
#define RCU_APB1EN_CAN1EN_Msk             (0x1UL << RCU_APB1EN_CAN1EN_Pos)

#define RCU_APB1EN_BKPIEN_Pos             (27U)
#define RCU_APB1EN_BKPIEN_Msk             (0x1UL << RCU_APB1EN_BKPIEN_Pos)

#define RCU_APB1EN_PMUEN_Pos              (28U)
#define RCU_APB1EN_PMUEN_Msk              (0x1UL << RCU_APB1EN_PMUEN_Pos)

#define RCU_APB1EN_DACEN_Pos              (29U)
#define RCU_APB1EN_DACEN_Msk              (0x1UL << RCU_APB1EN_DACEN_Pos)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct RCU_s {
  __IOM uint32_t CTL;     /*!< Offset: 0x000 (R/W) Control register */
  __IOM uint32_t CFG0;    /*!< Offset: 0x004 (R/W) Clock configuration register 0 */
  __IOM uint32_t INT;     /*!< Offset: 0x008 (R/W) Clock interrupt register */
  __IOM uint32_t APB2RST; /*!< Offset: 0x00C (R/W) APB2 reset register */
  __IOM uint32_t APB1RST; /*!< Offset: 0x010 (R/W) APB1 reset register */
  __IOM uint32_t AHBEN;   /*!< Offset: 0x014 (R/W) AHB enable register */
  __IOM uint32_t APB2EN;  /*!< Offset: 0x018 (R/W) APB2 enable register */
  __IOM uint32_t APB1EN;  /*!< Offset: 0x01C (R/W) APB1 enable register */
  __IOM uint32_t BDCTL;   /*!< Offset: 0x020 (R/W) Backup domain control register */
  __IOM uint32_t RSTSCK;  /*!< Offset: 0x024 (R/W) Reset source/clock register */
  __IOM uint32_t AHBRST;  /*!< Offset: 0x028 (R/W) AHB reset register */
  __IOM uint32_t CFG1;    /*!< Offset: 0x02C (R/W) Clock configuration register 1 */
  RESERVED(0, uint32_t);
  __IOM uint32_t DSV;     /*!< Offset: 0x034 (R/W) Deep-sleep mode voltage register */
} RCU_t;

#ifdef __cplusplus
}
#endif

#endif  /* GD32VF103XX_RCU_H */
