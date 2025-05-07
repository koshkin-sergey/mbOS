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

#ifndef GD32VF103XX_ECLIC_H
#define GD32VF103XX_ECLIC_H

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

#define CLIC_CLICCFG_NLBIT_Pos              1U                                  /*!< CLIC CLICCFG: NLBIT Position */
#define CLIC_CLICCFG_NLBIT_Msk              (0xFUL << CLIC_CLICCFG_NLBIT_Pos)   /*!< CLIC CLICCFG: NLBIT Mask */

#define CLIC_CLICINFO_CTLBIT_Pos            21U                                 /*!< CLIC INTINFO: __ECLIC_GetInfoCtlbits() Position */
#define CLIC_CLICINFO_CTLBIT_Msk            (0xFUL << CLIC_CLICINFO_CTLBIT_Pos) /*!< CLIC INTINFO: __ECLIC_GetInfoCtlbits() Mask */

#define CLIC_CLICINFO_VER_Pos               13U                                 /*!< CLIC CLICINFO: VERSION Position */
#define CLIC_CLICINFO_VER_Msk               (0xFFUL << CLIC_CLICCFG_NLBIT_Pos)  /*!< CLIC CLICINFO: VERSION Mask */

#define CLIC_CLICINFO_NUM_Pos               0U                                  /*!< CLIC CLICINFO: NUM Position */
#define CLIC_CLICINFO_NUM_Msk               (0xFFFUL << CLIC_CLICINFO_NUM_Pos)  /*!< CLIC CLICINFO: NUM Mask */

#define CLIC_INTIP_IP_Pos                   0U                                  /*!< CLIC INTIP: IP Position */
#define CLIC_INTIP_IP_Msk                   (0x1UL << CLIC_INTIP_IP_Pos)        /*!< CLIC INTIP: IP Mask */

#define CLIC_INTIE_IE_Pos                   0U                                  /*!< CLIC INTIE: IE Position */
#define CLIC_INTIE_IE_Msk                   (0x1UL << CLIC_INTIE_IE_Pos)        /*!< CLIC INTIE: IE Mask */

#define CLIC_INTATTR_TRIG_Pos               1U                                  /*!< CLIC INTATTR: TRIG Position */
#define CLIC_INTATTR_TRIG_Msk               (0x3UL << CLIC_INTATTR_TRIG_Pos)    /*!< CLIC INTATTR: TRIG Mask */

#define CLIC_INTATTR_SHV_Pos                0U                                  /*!< CLIC INTATTR: SHV Position */
#define CLIC_INTATTR_SHV_Msk                (0x1UL << CLIC_INTATTR_SHV_Pos)     /*!< CLIC INTATTR: SHV Mask */

#define ECLIC_MAX_NLBITS                    8U                                  /*!< Max nlbit of the CLICINTCTLBITS */
#define ECLIC_MODE_MTVEC_Msk                3U                                  /*!< ECLIC Mode mask for MTVT CSR Register */

#define ECLIC_NON_VECTOR_INTERRUPT          0x0                                 /*!< Non-Vector Interrupt Mode of ECLIC */
#define ECLIC_VECTOR_INTERRUPT              0x1                                 /*!< Vector Interrupt Mode of ECLIC */

#ifndef __ECLIC_BASEADDR
/* Base address of ECLIC(__ECLIC_BASEADDR) should be defined in <Device.h> */
#error "__ECLIC_BASEADDR is not defined, please check!"
#endif

/* ECLIC Memory mapping of Device */
#define ECLIC_BASE                          __ECLIC_BASEADDR                    /*!< ECLIC Base Address */
#define ECLIC                               ((CLIC_t *) ECLIC_BASE)             /*!< CLIC configuration struct */

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @brief  Union type to access CLICFG configure register.
 */
typedef union {
  struct {
    __IM uint8_t  reserved0: 1;
    __IOM uint8_t    nlbits: 4;     /*!< bit:     1..4 specified the bit-width of level and priority in the register clicintctl[i] */
    __IM uint8_t     nmbits: 2;     /*!< bit:     5..6 ties to 1 if supervisor-level interrupt supported, or else it's reserved */
    __IM uint8_t  reserved1: 1;
  } b;                              /*!< Structure used for bit  access */
  uint8_t w;                        /*!< Type      used for byte access */
} CLICCFG_t;

/**
 * @brief  Union type to access CLICINFO information register.
 */
typedef union {
  struct {
    __IM uint32_t     numint: 13;   /*!< bit:  0..12   number of maximum interrupt inputs supported */
    __IM uint32_t    version: 8;    /*!< bit:  13..20  20:17 for architecture version,16:13 for implementation version */
    __IM uint32_t intctlbits: 4;    /*!< bit:  21..24  specifies how many hardware bits are actually implemented in the clicintctl registers */
    __IM uint32_t  reserved0: 7;    /*!< bit:  25..31  Reserved */
  } b;                              /*!< Structure used for bit  access */
  __IM uint32_t w;                  /*!< Type      used for word access */
} CLICINFO_t;

/**
 * @brief Access to the machine mode register structure of INTIP, INTIE, INTATTR, INTCTL.
 */
typedef struct {
  __IOM uint8_t intip;              /*!< Offset: 0x000 (R/W)  Interrupt set pending register */
  __IOM uint8_t intie;              /*!< Offset: 0x001 (R/W)  Interrupt set enable register */
  __IOM uint8_t intattr;            /*!< Offset: 0x002 (R/W)  Interrupt set attributes register */
  __IOM uint8_t intctrl;            /*!< Offset: 0x003 (R/W)  Interrupt configure register */
} CLIC_CTRL_t;

/**
 * @brief Access to the structure of ECLIC Memory Map, which is compatible with TEE.
 */
typedef struct {
  __IOM uint8_t             cfg;    /*!< Offset: 0x000 (R/W)  CLIC configuration register */
  __IM uint8_t     reserved0[3];
  __IM uint32_t            info;    /*!< Offset: 0x004 (R/ )  CLIC information register */
  __IM uint8_t        reserved1;
  __IM uint8_t        reserved2;
  __IM uint8_t        reserved3;
  __IOM uint8_t             mth;    /*!< Offset: 0x00B(R/W)  CLIC machine mode interrupt-level threshold */
  uint32_t      reserved4[1021];
  CLIC_CTRL_t        ctrl[4096];    /*!< Offset: 0x1000 (R/W) CLIC machine mode register structure for INTIP, INTIE, INTATTR, INTCTL */
} CLIC_t;

/**
 * @brief ECLIC Trigger Enum for different Trigger Type
 */
typedef enum ECLIC_TRIGGER {
    ECLIC_LEVEL_TRIGGER = 0x0,          /*!< Level Triggerred, trig[0] = 0 */
    ECLIC_POSTIVE_EDGE_TRIGGER = 0x1,   /*!< Postive/Rising Edge Triggered, trig[0] = 1, trig[1] = 0 */
    ECLIC_NEGTIVE_EDGE_TRIGGER = 0x3,   /*!< Negtive/Falling Edge Triggered, trig[0] = 1, trig[1] = 1 */
    ECLIC_MAX_TRIGGER = 0x3             /*!< MAX Supported Trigger Mode */
} ECLIC_TRIGGER_t;

#ifdef __cplusplus
}
#endif

#endif  /* GD32VF103XX_ECLIC_H */
