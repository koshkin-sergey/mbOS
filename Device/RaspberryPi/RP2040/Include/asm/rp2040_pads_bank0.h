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

#ifndef RP2040_PADS_BANK0_H
#define RP2040_PADS_BANK0_H

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

#define PADS_BANK0                        ((PADS_BANK0_t*) PADS_BANK0_BASE)

/**
 * @brief Bit definition for VOLTAGE_SELECT register
 */
#define PADS_BANK0_VOLTAGE_SELECT_Pos     (0U)
#define PADS_BANK0_VOLTAGE_SELECT_Msk     (1UL << PADS_BANK0_VOLTAGE_SELECT_Pos)
#define PADS_BANK0_VOLTAGE_SELECT_3V3     (0UL << PADS_BANK0_VOLTAGE_SELECT_Pos)
#define PADS_BANK0_VOLTAGE_SELECT_1V8     (1UL << PADS_BANK0_VOLTAGE_SELECT_Pos)

/**
 * @brief Bit definition for GPIOx register
 */
#define PADS_BANK0_GPIO_SLEWFAST_Pos      (0U)
#define PADS_BANK0_GPIO_SLEWFAST_Msk      (1UL << PADS_BANK0_GPIO_SLEWFAST_Pos)
#define PADS_BANK0_GPIO_SLEWFAST_SLOW     (0UL << PADS_BANK0_GPIO_SLEWFAST_Pos)
#define PADS_BANK0_GPIO_SLEWFAST_FAST     (1UL << PADS_BANK0_GPIO_SLEWFAST_Pos)

#define PADS_BANK0_GPIO_SCHMITT_Pos       (1U)
#define PADS_BANK0_GPIO_SCHMITT_Msk       (1UL << PADS_BANK0_GPIO_SCHMITT_Pos)
#define PADS_BANK0_GPIO_SCHMITT_EN        (1UL << PADS_BANK0_GPIO_SCHMITT_Pos)

#define PADS_BANK0_GPIO_PDE_Pos           (2U)
#define PADS_BANK0_GPIO_PDE_Msk           (1UL << PADS_BANK0_GPIO_PDE_Pos)
#define PADS_BANK0_GPIO_PDE               (1UL << PADS_BANK0_GPIO_PDE_Pos)

#define PADS_BANK0_GPIO_PUE_Pos           (3U)
#define PADS_BANK0_GPIO_PUE_Msk           (1UL << PADS_BANK0_GPIO_PUE_Pos)
#define PADS_BANK0_GPIO_PUE               (1UL << PADS_BANK0_GPIO_PUE_Pos)

#define PADS_BANK0_GPIO_DRIVE_Pos         (4U)
#define PADS_BANK0_GPIO_DRIVE_Msk         (3UL << PADS_BANK0_GPIO_DRIVE_Pos)
#define PADS_BANK0_GPIO_DRIVE_2MA         (0UL << PADS_BANK0_GPIO_DRIVE_Pos)
#define PADS_BANK0_GPIO_DRIVE_4MA         (1UL << PADS_BANK0_GPIO_DRIVE_Pos)
#define PADS_BANK0_GPIO_DRIVE_8MA         (2UL << PADS_BANK0_GPIO_DRIVE_Pos)
#define PADS_BANK0_GPIO_DRIVE_12MA        (3UL << PADS_BANK0_GPIO_DRIVE_Pos)

#define PADS_BANK0_GPIO_IE_Pos            (6U)
#define PADS_BANK0_GPIO_IE_Msk            (1UL << PADS_BANK0_GPIO_IE_Pos)
#define PADS_BANK0_GPIO_IE                (1UL << PADS_BANK0_GPIO_IE_Pos)

#define PADS_BANK0_GPIO_OD_Pos            (7U)
#define PADS_BANK0_GPIO_OD_Msk            (1UL << PADS_BANK0_GPIO_OD_Pos)
#define PADS_BANK0_GPIO_OD                (1UL << PADS_BANK0_GPIO_OD_Pos)

/**
 * @brief Bit definition for SWCLK register
 */
#define PADS_BANK0_SWCLK_SLEWFAST_Pos     (0U)
#define PADS_BANK0_SWCLK_SLEWFAST_Msk     (1UL << PADS_BANK0_SWCLK_SLEWFAST_Pos)
#define PADS_BANK0_SWCLK_SLEWFAST_SLOW    (0UL << PADS_BANK0_SWCLK_SLEWFAST_Pos)
#define PADS_BANK0_SWCLK_SLEWFAST_FAST    (1UL << PADS_BANK0_SWCLK_SLEWFAST_Pos)

#define PADS_BANK0_SWCLK_SCHMITT_Pos      (1U)
#define PADS_BANK0_SWCLK_SCHMITT_Msk      (1UL << PADS_BANK0_SWCLK_SCHMITT_Pos)
#define PADS_BANK0_SWCLK_SCHMITT_EN       (1UL << PADS_BANK0_SWCLK_SCHMITT_Pos)

#define PADS_BANK0_SWCLK_PDE_Pos          (2U)
#define PADS_BANK0_SWCLK_PDE_Msk          (1UL << PADS_BANK0_SWCLK_PDE_Pos)
#define PADS_BANK0_SWCLK_PDE              (1UL << PADS_BANK0_SWCLK_PDE_Pos)

#define PADS_BANK0_SWCLK_PUE_Pos          (3U)
#define PADS_BANK0_SWCLK_PUE_Msk          (1UL << PADS_BANK0_SWCLK_PUE_Pos)
#define PADS_BANK0_SWCLK_PUE              (1UL << PADS_BANK0_SWCLK_PUE_Pos)

#define PADS_BANK0_SWCLK_DRIVE_Pos        (4U)
#define PADS_BANK0_SWCLK_DRIVE_Msk        (3UL << PADS_BANK0_SWCLK_DRIVE_Pos)
#define PADS_BANK0_SWCLK_DRIVE_2MA        (0UL << PADS_BANK0_SWCLK_DRIVE_Pos)
#define PADS_BANK0_SWCLK_DRIVE_4MA        (1UL << PADS_BANK0_SWCLK_DRIVE_Pos)
#define PADS_BANK0_SWCLK_DRIVE_8MA        (2UL << PADS_BANK0_SWCLK_DRIVE_Pos)
#define PADS_BANK0_SWCLK_DRIVE_12MA       (3UL << PADS_BANK0_SWCLK_DRIVE_Pos)

#define PADS_BANK0_SWCLK_IE_Pos           (6U)
#define PADS_BANK0_SWCLK_IE_Msk           (1UL << PADS_BANK0_SWCLK_IE_Pos)
#define PADS_BANK0_SWCLK_IE               (1UL << PADS_BANK0_SWCLK_IE_Pos)

#define PADS_BANK0_SWCLK_OD_Pos           (7U)
#define PADS_BANK0_SWCLK_OD_Msk           (1UL << PADS_BANK0_SWCLK_OD_Pos)
#define PADS_BANK0_SWCLK_OD               (1UL << PADS_BANK0_SWCLK_OD_Pos)

/**
 * @brief Bit definition for SWD register
 */
#define PADS_BANK0_SWD_SLEWFAST_Pos       (0U)
#define PADS_BANK0_SWD_SLEWFAST_Msk       (1UL << PADS_BANK0_SWD_SLEWFAST_Pos)
#define PADS_BANK0_SWD_SLEWFAST_SLOW      (0UL << PADS_BANK0_SWD_SLEWFAST_Pos)
#define PADS_BANK0_SWD_SLEWFAST_FAST      (1UL << PADS_BANK0_SWD_SLEWFAST_Pos)

#define PADS_BANK0_SWD_SCHMITT_Pos        (1U)
#define PADS_BANK0_SWD_SCHMITT_Msk        (1UL << PADS_BANK0_SWD_SCHMITT_Pos)
#define PADS_BANK0_SWD_SCHMITT_EN         (1UL << PADS_BANK0_SWD_SCHMITT_Pos)

#define PADS_BANK0_SWD_PDE_Pos            (2U)
#define PADS_BANK0_SWD_PDE_Msk            (1UL << PADS_BANK0_SWD_PDE_Pos)
#define PADS_BANK0_SWD_PDE                (1UL << PADS_BANK0_SWD_PDE_Pos)

#define PADS_BANK0_SWD_PUE_Pos            (3U)
#define PADS_BANK0_SWD_PUE_Msk            (1UL << PADS_BANK0_SWD_PUE_Pos)
#define PADS_BANK0_SWD_PUE                (1UL << PADS_BANK0_SWD_PUE_Pos)

#define PADS_BANK0_SWD_DRIVE_Pos          (4U)
#define PADS_BANK0_SWD_DRIVE_Msk          (3UL << PADS_BANK0_SWD_DRIVE_Pos)
#define PADS_BANK0_SWD_DRIVE_2MA          (0UL << PADS_BANK0_SWD_DRIVE_Pos)
#define PADS_BANK0_SWD_DRIVE_4MA          (1UL << PADS_BANK0_SWD_DRIVE_Pos)
#define PADS_BANK0_SWD_DRIVE_8MA          (2UL << PADS_BANK0_SWD_DRIVE_Pos)
#define PADS_BANK0_SWD_DRIVE_12MA         (3UL << PADS_BANK0_SWD_DRIVE_Pos)

#define PADS_BANK0_SWD_IE_Pos             (6U)
#define PADS_BANK0_SWD_IE_Msk             (1UL << PADS_BANK0_SWD_IE_Pos)
#define PADS_BANK0_SWD_IE                 (1UL << PADS_BANK0_SWD_IE_Pos)

#define PADS_BANK0_SWD_OD_Pos             (7U)
#define PADS_BANK0_SWD_OD_Msk             (1UL << PADS_BANK0_SWD_OD_Pos)
#define PADS_BANK0_SWD_OD                 (1UL << PADS_BANK0_SWD_OD_Pos)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @brief PADS_BANK0 (PADS_BANK0)
 */
typedef struct {                                /*!< PADS_BANK0 Structure                                                      */
  __IOM uint32_t  VOLTAGE_SELECT;               /*!< Voltage select. Per bank control                                          */
  __IOM uint32_t  GPIO[30];                     /*!< Pad control register                                                      */
  __IOM uint32_t  SWCLK;                        /*!< Pad control register                                                      */
  __IOM uint32_t  SWD;                          /*!< Pad control register                                                      */
} PADS_BANK0_t;                                 /*!< Size = 132 (0x84)                                                         */

#ifdef __cplusplus
}
#endif

#endif  /* RP2040_PADS_BANK0_H */
