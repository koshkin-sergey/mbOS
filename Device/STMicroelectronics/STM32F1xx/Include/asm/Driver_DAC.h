/*
 * Copyright (C) 2018-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
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
 * Project: DAC (Digital to Analog Converter) Driver definitions
 */

#ifndef DRIVER_DAC_H_
#define DRIVER_DAC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "CMSIS/Driver/Driver_Common.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define DAC_API_VERSION   ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */

/* DAC Event */
#define DAC_EVENT_CONVERT_COMPLETE    (1UL << 0)  ///< Data Convert completed

/*----- DAC Control Codes ----------------------------------------------------*/
#define DAC_CONTROL_Pos               (0U)
#define DAC_CONTROL_Msk               (0xFUL << DAC_CONTROL_Pos)

/*----- DAC Control Codes: Mode -----*/
#define DAC_MODE_NO_TRIGGER           (0UL << DAC_CONTROL_Pos)
#define DAC_MODE_SOFTWARE_TRIGGER     (1UL << DAC_CONTROL_Pos)
#define DAC_MODE_HARDWARE_TRIGGER     (2UL << DAC_CONTROL_Pos)

/*----- DAC Control Codes: Mode Parameters: Output Channel -----*/
#define DAC_OUTPUT_CHANNEL_Pos        (4U)
#define DAC_OUTPUT_CHANNEL_Msk        (0xFUL << DAC_OUTPUT_CHANNEL_Pos)
#define DAC_OUTPUT_CHANNEL_1          (0x0UL << DAC_OUTPUT_CHANNEL_Pos)
#define DAC_OUTPUT_CHANNEL_2          (0x1UL << DAC_OUTPUT_CHANNEL_Pos)
#define DAC_OUTPUT_CHANNEL_BOTH       (0x2UL << DAC_OUTPUT_CHANNEL_Pos)

/*----- DAC Control Codes: Mode Parameters: Output Buffer -----*/
#define DAC_OUTPUT_BUFFER_Pos         (8U)
#define DAC_OUTPUT_BUFFER_Msk         (1UL << DAC_OUTPUT_BUFFER_Pos)
#define DAC_OUTPUT_BUFFER_OFF         (0UL << DAC_OUTPUT_BUFFER_Pos)
#define DAC_OUTPUT_BUFFER_ON          (1UL << DAC_OUTPUT_BUFFER_Pos)

/*----- DAC Control Codes: Mode Parameters: Data Format -----*/
#define DAC_DATA_FORMAT_Pos           (9U)
#define DAC_DATA_FORMAT_Msk           (7UL << DAC_DATA_FORMAT_Pos)
#define DAC_DATA_FORMAT_12R           (0UL << DAC_DATA_FORMAT_Pos)
#define DAC_DATA_FORMAT_12L           (1UL << DAC_DATA_FORMAT_Pos)
#define DAC_DATA_FORMAT_8R            (2UL << DAC_DATA_FORMAT_Pos)

/*----- DAC Control Codes: Miscellaneous Controls  -----*/
#define DAC_SET_VALUE                 (3UL << DAC_CONTROL_Pos)
#define DAC_ABORT_CONVERT             (4UL << DAC_CONTROL_Pos)

/*----- DAC specific error codes ---------------------------------------------*/
#define DAC_ERROR_MODE                (ARM_DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Mode not supported
#define DAC_ERROR_DATA_FORMAT         (ARM_DRIVER_ERROR_SPECIFIC - 2)     ///< Specified Data Format not supported
#define DAC_ERROR_OUTPUT_CHANNEL      (ARM_DRIVER_ERROR_SPECIFIC - 3)     ///< Specified Output Channel not supported
#define DAC_ERROR_OUTPUT_BUFFER       (ARM_DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Output Buffer not supported

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* Signal DAC Event */
typedef void (*DAC_SignalEvent_t)(uint32_t event);

/**
 * @brief DAC Driver Capabilities.
 */
typedef struct _DAC_CAPABILITIES {
  uint32_t ch_num           : 4;        ///< Number of channels
  uint32_t output_buffer    : 1;        ///< Supports output buffer
  uint32_t trigger          : 1;        ///< Supports external triggers for conversion
  uint32_t noise_wave       : 1;        ///< Supports noise-wave generation
  uint32_t triangular_wave  : 1;        ///< Supports triangular-wave generation
  uint32_t reserved         : 24;       ///< Reserved (must be zero)
} DAC_CAPABILITIES;

/**
 * @brief DAC Status
 */
typedef volatile struct _DAC_STATUS {
  uint32_t busy             : 1;        ///< DAC busy flag
  uint32_t reserved         : 31;       ///< Reserved (must be zero)
} DAC_STATUS;

/**
 * @brief Access structure of the DAC Driver.
 */
typedef struct _DRIVER_DAC {
  ARM_DRIVER_VERSION   (*GetVersion)      (void);                             ///< Pointer to \ref ARM_SPI_GetVersion : Get driver version.
  DAC_CAPABILITIES     (*GetCapabilities) (void);                             ///< Pointer to \ref DAC_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (DAC_SignalEvent_t cb_event);       ///< Pointer to \ref DAC_Initialize : Initialize DAC Interface.
  int32_t              (*Uninitialize)    (void);                             ///< Pointer to \ref DAC_Uninitialize : De-initialize DAC Interface.
  int32_t              (*PowerControl)    (ARM_POWER_STATE state);            ///< Pointer to \ref DAC_PowerControl : Control DAC Interface Power.
  int32_t              (*Convert)         (const void *data, uint32_t num);   ///< Pointer to \ref DAC_Convert : Start transfer data to DAC Interface.
  uint32_t             (*GetCount)        (void);                             ///< Pointer to \ref DAC_GetCount : Get transferred data count.
  int32_t              (*Control)         (uint32_t control, uint32_t arg);   ///< Pointer to \ref DAC_Control : Control DAC Interface.
  DAC_STATUS           (*GetStatus)       (void);                             ///< Pointer to \ref DAC_GetStatus : Get DAC status.
} const DRIVER_DAC;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_DAC_H_ */

/* ----------------------------- End of file ---------------------------------*/
