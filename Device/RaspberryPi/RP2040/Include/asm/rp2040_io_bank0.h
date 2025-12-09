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

#ifndef RP2040_IO_BANK0_H
#define RP2040_IO_BANK0_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/rp2040.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define IO_BANK0                          ((IO_BANK0_t*) IO_BANK0_BASE)

/**
 * @brief Bit definition for GPIOx_STATUS register
 */
#define IO_BANK0_GPIO_STAT_OUTFROMPERI_Pos  (8U)
#define IO_BANK0_GPIO_STAT_OUTFROMPERI_Msk  (1UL << IO_BANK0_GPIO_STAT_OUTFROMPERI_Pos)
#define IO_BANK0_GPIO_STAT_OUTFROMPERI              IO_BANK0_GPIO_STAT_OUTFROMPERI_Msk

#define IO_BANK0_GPIO_STAT_OUTTOPAD_Pos     (9U)
#define IO_BANK0_GPIO_STAT_OUTTOPAD_Msk     (1UL << IO_BANK0_GPIO_STAT_OUTTOPAD_Pos)
#define IO_BANK0_GPIO_STAT_OUTTOPAD                 IO_BANK0_GPIO_STAT_OUTTOPAD_Msk

#define IO_BANK0_GPIO_STAT_OEFROMPERI_Pos   (12U)
#define IO_BANK0_GPIO_STAT_OEFROMPERI_Msk   (1UL << IO_BANK0_GPIO_STAT_OEFROMPERI_Pos)
#define IO_BANK0_GPIO_STAT_OEFROMPERI               IO_BANK0_GPIO_STAT_OEFROMPERI_Msk

#define IO_BANK0_GPIO_STAT_OETOPAD_Pos      (13U)
#define IO_BANK0_GPIO_STAT_OETOPAD_Msk      (1UL << IO_BANK0_GPIO_STAT_OETOPAD_Pos)
#define IO_BANK0_GPIO_STAT_OETOPAD                  IO_BANK0_GPIO_STAT_OETOPAD_Msk

#define IO_BANK0_GPIO_STAT_INFROMPAD_Pos    (17U)
#define IO_BANK0_GPIO_STAT_INFROMPAD_Msk    (1UL << IO_BANK0_GPIO_STAT_INFROMPAD_Pos)
#define IO_BANK0_GPIO_STAT_INFROMPAD                IO_BANK0_GPIO_STAT_INFROMPAD_Msk

#define IO_BANK0_GPIO_STAT_INTOPERI_Pos     (19U)
#define IO_BANK0_GPIO_STAT_INTOPERI_Msk     (1UL << IO_BANK0_GPIO_STAT_INTOPERI_Pos)
#define IO_BANK0_GPIO_STAT_INTOPERI                 IO_BANK0_GPIO_STAT_INTOPERI_Msk

#define IO_BANK0_GPIO_STAT_IRQFROMPAD_Pos   (24U)
#define IO_BANK0_GPIO_STAT_IRQFROMPAD_Msk   (1UL << IO_BANK0_GPIO_STAT_IRQFROMPAD_Pos)
#define IO_BANK0_GPIO_STAT_IRQFROMPAD               IO_BANK0_GPIO_STAT_IRQFROMPAD_Msk

#define IO_BANK0_GPIO_STAT_IRQTOPROC_Pos    (26U)
#define IO_BANK0_GPIO_STAT_IRQTOPROC_Msk    (1UL << IO_BANK0_GPIO_STAT_IRQTOPROC_Pos)
#define IO_BANK0_GPIO_STAT_IRQTOPROC                IO_BANK0_GPIO_STAT_IRQTOPROC_Msk

/**
 * @brief Bit definition for GPIOx_CTRL register
 */
#define IO_BANK0_GPIO_CTRL_FUNCSEL_Pos      (0U)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_Msk      (1FUL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_SPI      (01UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_UART     (02UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_I2C      (03UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_PWM      (04UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_SIO      (05UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_PIO0     (06UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_PIO1     (07UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_CLOCK    (08UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_USB      (09UL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_NULL     (1FUL << IO_BANK0_GPIO_CTRL_FUNCSEL_Pos)

#define IO_BANK0_GPIO_CTRL_OUTOVER_Pos      (8U)
#define IO_BANK0_GPIO_CTRL_OUTOVER_Msk      (3UL << IO_BANK0_GPIO_CTRL_OUTOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OUTOVER_NORMAL   (0UL << IO_BANK0_GPIO_CTRL_OUTOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OUTOVER_INVERT   (1UL << IO_BANK0_GPIO_CTRL_OUTOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OUTOVER_LOW      (2UL << IO_BANK0_GPIO_CTRL_OUTOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OUTOVER_HIGH     (3UL << IO_BANK0_GPIO_CTRL_OUTOVER_Pos)

#define IO_BANK0_GPIO_CTRL_OEOVER_Pos       (12U)
#define IO_BANK0_GPIO_CTRL_OEOVER_Msk       (3UL << IO_BANK0_GPIO_CTRL_OEOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OEOVER_NORMAL    (0UL << IO_BANK0_GPIO_CTRL_OEOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OEOVER_INVERT    (1UL << IO_BANK0_GPIO_CTRL_OEOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OEOVER_DISABLE   (2UL << IO_BANK0_GPIO_CTRL_OEOVER_Pos)
#define IO_BANK0_GPIO_CTRL_OEOVER_ENABLE    (3UL << IO_BANK0_GPIO_CTRL_OEOVER_Pos)

#define IO_BANK0_GPIO_CTRL_INOVER_Pos       (16U)
#define IO_BANK0_GPIO_CTRL_INOVER_Msk       (3UL << IO_BANK0_GPIO_CTRL_INOVER_Pos)
#define IO_BANK0_GPIO_CTRL_INOVER_NORMAL    (0UL << IO_BANK0_GPIO_CTRL_INOVER_Pos)
#define IO_BANK0_GPIO_CTRL_INOVER_INVERT    (1UL << IO_BANK0_GPIO_CTRL_INOVER_Pos)
#define IO_BANK0_GPIO_CTRL_INOVER_LOW       (2UL << IO_BANK0_GPIO_CTRL_INOVER_Pos)
#define IO_BANK0_GPIO_CTRL_INOVER_HIGH      (3UL << IO_BANK0_GPIO_CTRL_INOVER_Pos)

#define IO_BANK0_GPIO_CTRL_IRQOVER_Pos      (28U)
#define IO_BANK0_GPIO_CTRL_IRQOVER_Msk      (3UL << IO_BANK0_GPIO_CTRL_IRQOVER_Pos)
#define IO_BANK0_GPIO_CTRL_IRQOVER_NORMAL   (0UL << IO_BANK0_GPIO_CTRL_IRQOVER_Pos)
#define IO_BANK0_GPIO_CTRL_IRQOVER_INVERT   (1UL << IO_BANK0_GPIO_CTRL_IRQOVER_Pos)
#define IO_BANK0_GPIO_CTRL_IRQOVER_LOW      (2UL << IO_BANK0_GPIO_CTRL_IRQOVER_Pos)
#define IO_BANK0_GPIO_CTRL_IRQOVER_HIGH     (3UL << IO_BANK0_GPIO_CTRL_IRQOVER_Pos)

/**
 * @brief Bit definition for GPIO_INT register
 */
#define IO_BANK0_GPIO_INT_LEVEL_LOW_Pos     (0U)
#define IO_BANK0_GPIO_INT_LEVEL_LOW_Msk     (1UL << IO_BANK0_GPIO_INT_LEVEL_LOW_Pos)
#define IO_BANK0_GPIO_INT_LEVEL_LOW                 IO_BANK0_GPIO_INT_LEVEL_LOW_Msk

#define IO_BANK0_GPIO_INT_LEVEL_HIGH_Pos    (1U)
#define IO_BANK0_GPIO_INT_LEVEL_HIGH_Msk    (1UL << IO_BANK0_GPIO_INT_LEVEL_HIGH_Pos)
#define IO_BANK0_GPIO_INT_LEVEL_HIGH                IO_BANK0_GPIO_INT_LEVEL_HIGH_Msk

#define IO_BANK0_GPIO_INT_EDGE_LOW_Pos      (2U)
#define IO_BANK0_GPIO_INT_EDGE_LOW_Msk      (1UL << IO_BANK0_GPIO_INT_EDGE_LOW_Pos)
#define IO_BANK0_GPIO_INT_EDGE_LOW                  IO_BANK0_GPIO_INT_EDGE_LOW_Msk

#define IO_BANK0_GPIO_INT_EDGE_HIGH_Pos     (3U)
#define IO_BANK0_GPIO_INT_EDGE_HIGH_Msk     (1UL << IO_BANK0_GPIO_INT_EDGE_HIGH_Pos)
#define IO_BANK0_GPIO_INT_EDGE_HIGH                 IO_BANK0_GPIO_INT_EDGE_HIGH_Msk

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @brief IO_BANK0 (IO_BANK0)
 */
typedef struct {                                /*!< IO_BANK0 Structure                                                        */
  struct {
    __IOM uint32_t  STATUS;                     /*!< GPIO status                                                               */
    __IOM uint32_t  CTRL;                       /*!< GPIO control including function select and overrides.                     */
  } GPIO[30];
  __IOM uint32_t    INT_RAW[4];                 /*!< Raw Interrupts                                                            */
  struct {
    __IOM uint32_t  INT_ENABLE[4];              /*!< Interrupt Enable                                                          */
    __IOM uint32_t  INT_FORCE[4];               /*!< Interrupt Force                                                           */
    __IOM uint32_t  INT_STATUS[4];              /*!< Interrupt status after masking & forcing                                  */
  } PROC[2];
  struct {
    __IOM uint32_t  INT_ENABLE[4];              /*!< Interrupt Enable for dormant_wake                                         */
    __IOM uint32_t  INT_FORCE[4];               /*!< Interrupt Force for dormant_wake                                          */
    __IOM uint32_t  INT_STATUS[4];              /*!< Interrupt status after masking & forcing for dormant_wake                 */
  } DORMANT_WAKE;
} IO_BANK0_t;                                   /*!< Size = 400 (0x190)                                                        */

#ifdef __cplusplus
}
#endif

#endif  /* RP2040_IO_BANK0_H */
