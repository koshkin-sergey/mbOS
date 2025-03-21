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
