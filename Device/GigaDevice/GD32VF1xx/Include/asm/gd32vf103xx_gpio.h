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

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct GPIO {
  __IOM uint32_t CTL0;
  __IOM uint32_t CTL1;
  __IOM uint32_t ISTAT;
  __IOM uint32_t OCTL;
  __IOM uint32_t BOP;
  __IOM uint32_t BC;
  __IOM uint32_t LOCK;
} GPIO_t;

#ifdef __cplusplus
}
#endif

#endif  /* GD32VF103XX_GPIO_H */
