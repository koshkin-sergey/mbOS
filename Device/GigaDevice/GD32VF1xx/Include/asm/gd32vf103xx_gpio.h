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

#ifndef GD32VF103XX_GPIO_H
#define GD32VF103XX_GPIO_H

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

#define GPIOA   ((GPIO_t *) GPIOA_BASE)       /*!< GPIOA configuration struct */
#define GPIOB   ((GPIO_t *) GPIOB_BASE)       /*!< GPIOB configuration struct */
#define GPIOC   ((GPIO_t *) GPIOC_BASE)       /*!< GPIOC configuration struct */
#define GPIOD   ((GPIO_t *) GPIOD_BASE)       /*!< GPIOD configuration struct */
#define GPIOE   ((GPIO_t *) GPIOE_BASE)       /*!< GPIOE configuration struct */
#define AFIO    ((AFIO_t *) AFIO_BASE)        /*!< AFIO  configuration struct */

/**
 * @brief Bit definition for CTL register
 */
#define CTL_MD_Pos                    (0U)
#define CTL_MD_Msk                    (0x3UL << CTL_MD_Pos)
#define CTL_MD_0                      (0x1UL << CTL_MD_Pos)
#define CTL_MD_1                      (0x2UL << CTL_MD_Pos)

#define CTL_CTL_Pos                   (2U)
#define CTL_CTL_Msk                   (0x3UL << CTL_CTL_Pos)
#define CTL_CTL_0                     (0x1UL << CTL_CTL_Pos)
#define CTL_CTL_1                     (0x2UL << CTL_CTL_Pos)

/**
 * @brief Bit definition for ISTAT register
 */
#define ISTAT_ISTAT_Pos               (0U)
#define ISTAT_ISTAT_Msk               (0xFFFFUL << ISTAT_ISTAT_Pos)

/**
 * @brief Bit definition for OCTL register
 */
#define OCTL_OCTL_Pos                 (0U)
#define OCTL_OCTL_Msk                 (0xFFFFUL << OCTL_OCTL_Pos)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct GPIO_s {
  __IOM uint32_t CTL0;    /*!< Offset: 0x000 (R/W) Port control register 0 */
  __IOM uint32_t CTL1;    /*!< Offset: 0x004 (R/W) Port control register 1 */
  __IM  uint32_t ISTAT;   /*!< Offset: 0x008 (R/ ) Port input status register */
  __IOM uint32_t OCTL;    /*!< Offset: 0x00C (R/W) Port output control register */
  __OM  uint32_t BOP;     /*!< Offset: 0x010 ( /W) Port bit operate register */
  __OM  uint32_t BC;      /*!< Offset: 0x014 ( /W) Port bit clear register */
  __IOM uint32_t LOCK;    /*!< Offset: 0x018 (R/W) Port configuration lock register */
} GPIO_t;

typedef struct AFIO_s {
  __IOM uint32_t EC;      /*!< Offset: 0x000 (R/W) Event control register */
  __IOM uint32_t PCF0;    /*!< Offset: 0x004 (R/W) AFIO port configuration register 0 */
  __IOM uint32_t EXTISS0; /*!< Offset: 0x008 (R/W) EXTI sources selection register 0 */
  __IOM uint32_t EXTISS1; /*!< Offset: 0x00C (R/W) EXTI sources selection register 1 */
  __IOM uint32_t EXTISS2; /*!< Offset: 0x010 (R/W) EXTI sources selection register 2 */
  __IOM uint32_t EXTISS3; /*!< Offset: 0x014 (R/W) EXTI sources selection register 3 */
  RESERVED(0, uint32_t);
  __IOM uint32_t PCF1;    /*!< Offset: 0x01C (R/W) AFIO port configuration register 1 */
} AFIO_t;

#ifdef __cplusplus
}
#endif

#endif  /* GD32VF103XX_GPIO_H */
