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

#ifndef GD32VF103XX_SYSTIMER_H
#define GD32VF103XX_SYSTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/gd32vf103xx.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* Machine Timer Control / Status Register Definitions */
#define MTIMECTL_TIMESTOP_Pos       0U
#define MTIMECTL_TIMESTOP_Msk       (0x1UL << MTIMECTL_TIMESTOP_Pos)
#define MTIMECTL_TIMESTOP                     MTIMECTL_TIMESTOP_Msk

#define MTIMECTL_CMPCLREN_Pos       1U
#define MTIMECTL_CMPCLREN_Msk       (0x1UL << MTIMECTL_CMPCLREN_Pos)
#define MTIMECTL_CMPCLREN                     MTIMECTL_CMPCLREN_Msk

#define MTIMECTL_CLKSRC_Pos         2U
#define MTIMECTL_CLKSRC_Msk         (0x1UL << MTIMECTL_CLKSRC_Pos)
#define MTIMECTL_CLKSRC                       MTIMECTL_CLKSRC_Msk

#define MSIP_MSIP_Pos               0U
#define MSIP_MSIP_Msk               (0x1UL << MSIP_MSIP_Pos)
#define MSIP_MSIP                             MSIP_MSIP_Msk

#define MSFRST_KEY                  (0x80000A5FUL)

#ifndef __SYSTIMER_BASEADDR
/* Base address of SYSTIMER(__SYSTIMER_BASEADDR) should be defined in <Device.h> */
#error "__SYSTIMER_BASEADDR is not defined, please check!"
#endif
/* System Timer Memory mapping of Device  */
#define SysTimer_BASE               __SYSTIMER_BASEADDR                         /*!< SysTick Base Address */
#define SysTimer                    ((SysTimer_t *) SysTimer_BASE)              /*!< SysTick configuration struct */

#define SYSTIMER_IRQ_PRIORITY       0U

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Structure type to access the System Timer (SysTimer).
 * @details     Structure definition to access the system timer(SysTimer).
 */
typedef struct SysTimer_s {
  __IOM uint32_t MTIMEL;            /*!< (R/W) System Timer current value low */
  __IOM uint32_t MTIMEH;            /*!< (R/W) System Timer current value high */
  __IOM uint32_t MTIMECMPL;         /*!< (R/W) System Timer compare Value low */
  __IOM uint32_t MTIMECMPH;         /*!< (R/W) System Timer compare Value high */
  __IOM uint32_t RESERVED0[0x3F8];  /*!< - 0xFEC Reserved */
  __IOM uint32_t MSFTRST;           /*!< (R/W)  System Timer Software Core Reset Register */
  __IOM uint32_t RESERVED1;         /*!< Reserved */
  __IOM uint32_t MTIMECTL;          /*!< (R/W)  System Timer Control Register, previously MSTOP register */
  __IOM uint32_t MSIP;              /*!< (R/W)  System Timer SW interrupt Register */
} SysTimer_t;

#ifdef __cplusplus
}
#endif

#endif  /* GD32VF103XX_SYSTIMER_H */
