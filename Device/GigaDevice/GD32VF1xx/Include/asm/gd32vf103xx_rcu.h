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
 * @brief Bit definition for APB2EN register
 */
#define APB2EN_AFEN_Pos               (0U)
#define APB2EN_AFEN_Msk               (0x1UL << APB2EN_AFEN_Pos)
#define APB2EN_AFEN                             APB2EN_AFEN_Msk

#define APB2EN_PAEN_Pos               (2U)
#define APB2EN_PAEN_Msk               (0x1UL << APB2EN_PAEN_Pos)
#define APB2EN_PAEN                             APB2EN_PAEN_Msk

#define APB2EN_PBEN_Pos               (3U)
#define APB2EN_PBEN_Msk               (0x1UL << APB2EN_PBEN_Pos)
#define APB2EN_PBEN                             APB2EN_PBEN_Msk

#define APB2EN_PCEN_Pos               (4U)
#define APB2EN_PCEN_Msk               (0x1UL << APB2EN_PCEN_Pos)
#define APB2EN_PCEN                             APB2EN_PCEN_Msk

#define APB2EN_PDEN_Pos               (5U)
#define APB2EN_PDEN_Msk               (0x1UL << APB2EN_PDEN_Pos)
#define APB2EN_PDEN                             APB2EN_PDEN_Msk

#define APB2EN_PEEN_Pos               (6U)
#define APB2EN_PEEN_Msk               (0x1UL << APB2EN_PEEN_Pos)
#define APB2EN_PEEN                             APB2EN_PEEN_Msk

#define APB2EN_ADC0EN_Pos             (9U)
#define APB2EN_ADC0EN_Msk             (0x1UL << APB2EN_ADC0EN_Pos)
#define APB2EN_ADC0EN                           APB2EN_ADC0EN_Msk

#define APB2EN_ADC1EN_Pos             (10U)
#define APB2EN_ADC1EN_Msk             (0x1UL << APB2EN_ADC1EN_Pos)
#define APB2EN_ADC1EN                           APB2EN_ADC1EN_Msk

#define APB2EN_TIMER0EN_Pos           (11U)
#define APB2EN_TIMER0EN_Msk           (0x1UL << APB2EN_TIMER0EN_Pos)
#define APB2EN_TIMER0EN                         APB2EN_TIMER0EN_Msk

#define APB2EN_SPI0EN_Pos             (12U)
#define APB2EN_SPI0EN_Msk             (0x1UL << APB2EN_SPI0EN_Pos)
#define APB2EN_SPI0EN                           APB2EN_SPI0EN_Msk

#define APB2EN_USART0EN_Pos           (14U)
#define APB2EN_USART0EN_Msk           (0x1UL << APB2EN_USART0EN_Pos)
#define APB2EN_USART0EN                         APB2EN_USART0EN_Msk

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
