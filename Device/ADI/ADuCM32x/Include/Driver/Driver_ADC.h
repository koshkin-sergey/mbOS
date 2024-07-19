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

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/Driver_Common.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/****** ADC Event *****/
#define ADC_EVENT_COMPLETE          (1UL << 0)                                  ///< Acquisition completed
#define ADC_EVENT_OVERFLOW          (1UL << 1)                                  ///< ADC data overflow

/****** ADC Control Codes *****/

#define ADC_CONTROL_Pos              0
#define ADC_CONTROL_Msk             (0xFFUL << ADC_CONTROL_Pos)

/*----- ADC Control Codes: Mode -----*/
#define ADC_MODE_NONSEQUENCE        (0x00UL << ADC_CONTROL_Pos)                 ///< ADC in nonsequencer mode; arg = sampling rate in sps
#define ADC_MODE_SEQUENCE           (0x01UL << ADC_CONTROL_Pos)                 ///< ADC in sequencer mode; arg = sampling rate in sps

/*----- ADC Control Codes: Mode Parameters: Trigger -----*/
#define ADC_TRIGGER_Pos              8
#define ADC_TRIGGER_Msk             (0x01UL << ADC_TRIGGER_Pos)
#define ADC_TRIGGER_SOFTWARE        (0x00UL << ADC_TRIGGER_Pos)                 ///< ADC starts by a software trigger (default)
#define ADC_TRIGGER_HARDWARE        (0x01UL << ADC_TRIGGER_Pos)                 ///< ADC starts by a hardware trigger

/*----- ADC Control Codes: Mode Parameters: Data Bits -----*/
#define ADC_DATA_BITS_Pos            9
#define ADC_DATA_BITS_Msk                  (0x3FUL  << ADC_DATA_BITS_Pos)
#define ADC_DATA_BITS(n)            (((n) & 0x3FUL) << ADC_DATA_BITS_Pos)       ///< Number of Data bits (1..32)

/*----- ADC Control Codes: Miscellaneous Controls  -----*/
#define ADC_CONTROL                 (0x10UL << ADC_CONTROL_Pos)                 ///< Control ADC conversion; arg: 0=disable (default), 1=enable
#define ADC_CHANNEL_SELECT          (0x11UL << ADC_CONTROL_Pos)                 ///< Select channel for nonsequence operation; arg provide additional configuration
#define ADC_CHANNEL_SCAN            (0x12UL << ADC_CONTROL_Pos)                 ///< Select channels for sequence operation; arg = mask (bit: 0=inactive, 1=active); each bit corresponds to an ADC channel

/****** ADC Channel Select (arg) *****/

/*----- ADC Channel Select (arg): Positive channel -----*/
#define ADC_POSITIVE_CHANNEL_Pos     0
#define ADC_POSITIVE_CHANNEL_Msk               (0x3FUL  << ADC_POSITIVE_CHANNEL_Pos)
#define ADC_POSITIVE_CHANNEL(n)     ((((n)+1UL)&0x3FUL) << ADC_POSITIVE_CHANNEL_Pos)  ///< Select channel (0..31) for ADC positive input

/*----- ADC Channel Select (arg): Negative channel -----*/
#define ADC_NEGATIVE_CHANNEL_Pos     16
#define ADC_NEGATIVE_CHANNEL_Msk               (0x3FUL  << ADC_NEGATIVE_CHANNEL_Pos)
#define ADC_NEGATIVE_CHANNEL(n)     ((((n)+1UL)&0x3FUL) << ADC_NEGATIVE_CHANNEL_Pos)  ///< Select channel (0..31) for ADC negative input

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @fn          void ADC_SignalEvent(uint32_t event)
 * @brief       Signal ADC Events.
 * @param[in]   event  Notification mask
 */
typedef void (*ADC_SignalEvent_t)(uint32_t event);

/**
 * @brief ADC Status
 */
typedef struct ADC_STATUS {
  uint32_t busy             : 1;            // ADC busy flag
  uint32_t overflow         : 1;            // Data overflow detected (cleared on start of next operation)
  uint32_t reserved         : 30;
} ADC_STATUS_t;

/**
 * Function documentation
 *
 * @fn          int32_t ADC_Initialize(ADC_SignalEvent_t cb_event)
 * @brief       Initialize ADC Interface.
 * @param[in]   cb_event  Pointer to ADC_SignalEvent
 * @return      Execution status
 *
 * @fn          int32_t ADC_Uninitialize(void)
 * @brief       De-initialize ADC Interface.
 * @return      Execution status
 *
 * @fn          int32_t ADC_PowerControl(ADC_POWER_STATE state)
 * @brief       Control ADC Interface Power.
 * @param[in]   state  Power state
 * @return      Execution status
 *
 * @fn          int32_t ADC_Control(uint32_t control, uint32_t arg)
 * @brief       Control ADC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 *
 * @fn          int32_t ADC_Acquire(void *data, uint32_t num)
 * @brief       Start acquisition data.
 * @param[out]  data  Pointer to buffer for data
 * @param[in]   num   Number of data items to acquire
 * @return      Execution status
 *
 * @fn          uint32_t ADC_GetCount(void)
 * @brief       Get acquired data count.
 * @return      Number of data items acquired
 *
 * @fn          ADC_STATUS_t ADC_GetStatus(void)
 * @brief       Get ADC status.
 * @return      ADC status
 */

/**
 * @brief Access structure of the ADC Driver.
 */
typedef struct Driver_ADC {
  int32_t       (*Initialize)   (ADC_SignalEvent_t cb_event);
  int32_t       (*Uninitialize) (void);
  int32_t       (*PowerControl) (POWER_STATE state);
  int32_t       (*Control)      (uint32_t control, uint32_t arg);
  int32_t       (*Acquire)      (int32_t *data, uint32_t num);
  uint32_t      (*GetCount)     (void);
  ADC_STATUS_t  (*GetStatus)    (void);
} const Driver_ADC_t;

#endif /* DRIVER_ADC_H_ */
