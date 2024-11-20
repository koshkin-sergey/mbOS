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
 *
 * Project: VDAC Driver Definitions for ADI ADuCM32x
 */

#ifndef DRIVER_VDAC_H_
#define DRIVER_VDAC_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/Driver_Common.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/****** DAC Control Codes *****/

#define DAC_CONTROL_Pos              0
#define DAC_CONTROL_Msk             (0xFFUL << DAC_CONTROL_Pos)

/*----- DAC Control Codes: Mode -----*/
#define DAC_CONFIGURE               (0x00UL << DAC_CONTROL_Pos)                 ///< Configure DAC
#define DAC_CONTROL                 (0x01UL << DAC_CONTROL_Pos)                 ///< Control DAC; arg: 0=disable, 1=enable

/*----- DAC Control Codes: Mode Parameters: Trigger -----*/
#define DAC_TRIGGER_Pos              8
#define DAC_TRIGGER_Msk             (0x03UL << DAC_TRIGGER_Pos)
#define DAC_TRIGGER_NONE            (0x00UL << DAC_TRIGGER_Pos)                 ///< DAC conversion immediately (default)
#define DAC_TRIGGER_SOFTWARE        (0x01UL << DAC_TRIGGER_Pos)                 ///< DAC conversion by a software trigger
#define DAC_TRIGGER_HARDWARE        (0x02UL << DAC_TRIGGER_Pos)                 ///< DAC conversion by a hardware trigger

/*----- DAC Control Codes: Mode Parameters: Data Bits -----*/
#define DAC_DATA_BITS_Pos            10
#define DAC_DATA_BITS_Msk                  (0x3FUL  << DAC_DATA_BITS_Pos)
#define DAC_DATA_BITS(n)            (((n) & 0x3FUL) << DAC_DATA_BITS_Pos)       ///< Number of Data bits (1..32)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * Function documentation
 *
 * @fn          int32_t DAC_Initialize(void)
 * @brief       Initialize DAC Interface.
 * @return      Execution status
 *
 * @fn          int32_t DAC_Uninitialize(void)
 * @brief       De-initialize DAC Interface.
 * @return      Execution status
 *
 * @fn          int32_t DAC_Control(uint32_t control, uint32_t arg)
 * @brief       Control DAC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 *
 * @fn          int32_t DAC_WriteSample(uint32_t value)
 * @brief       Write the sample value.
 * @param[in]   value  Sample value.
 * @return      Execution status
 */

/**
 * @brief Access structure of the DAC Driver.
 */
typedef struct Driver_DAC {
  int32_t       (*Initialize)   (void);
  int32_t       (*Uninitialize) (void);
  int32_t       (*Control)      (uint32_t control, uint32_t arg);
  int32_t       (*WriteSample)  (uint16_t value);
} const Driver_DAC_t;

#endif /* DRIVER_VDAC_H_ */
