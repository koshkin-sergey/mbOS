/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef DAC_ADUC7023_H_
#define DAC_ADUC7023_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/aduc7023.h>
#include <device_config.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* DAC0 configuration definitions */
#if defined (DEV_DAC0) && (DEV_DAC0 == 1)
  #define USE_DAC0

  #if !defined(DAC0)
    #error "DAC0 not available for selected device!"
    #undef USE_DAC0
  #endif

  #define DAC0_OUTPUT_RANGE         DEV_DAC0_OUTPUT_RANGE
#endif

/* DAC1 configuration definitions */
#if defined (DEV_DAC1) && (DEV_DAC1 == 1)
  #define USE_DAC1

  #if !defined(DAC1)
    #error "DAC1 not available for selected device!"
    #undef USE_DAC1
  #endif

  #define DAC1_OUTPUT_RANGE         DEV_DAC1_OUTPUT_RANGE
#endif

/* DAC2 configuration definitions */
#if defined (DEV_DAC2) && (DEV_DAC2 == 1)
  #define USE_DAC2

  #if !defined(DAC2)
    #error "DAC2 not available for selected device!"
    #undef USE_DAC2
  #endif

  #define DAC2_OUTPUT_RANGE         DEV_DAC2_OUTPUT_RANGE
#endif

/* DAC3 configuration definitions */
#if defined (DEV_DAC3) && (DEV_DAC3 == 1)
  #define USE_DAC3

  #if !defined(DAC3)
    #error "DAC3 not available for selected device!"
    #undef USE_DAC3
  #endif

  #define DAC3_OUTPUT_RANGE         DEV_DAC3_OUTPUT_RANGE
#endif

#define DACx_EXPORT_DRIVER(x)                                                                                                            \
static int32_t DAC##x##_Initialize   (void)                           { return (DAC_Initialize   (&DAC##x##_Resources));               } \
static int32_t DAC##x##_Uninitialize (void)                           { return (DAC_Uninitialize (&DAC##x##_Resources));               } \
static int32_t DAC##x##_Control      (uint32_t control, uint32_t arg) { return (DAC_Control      (control, arg, &DAC##x##_Resources)); } \
static int32_t DAC##x##_WriteSample  (uint16_t value)                 { return (DAC_WriteSample  (value, &DAC##x##_Resources));        } \
                                                                                                                                         \
Driver_DAC_t Driver_DAC##x = {                                                                                                           \
  DAC##x##_Initialize,                                                                                                                   \
  DAC##x##_Uninitialize,                                                                                                                 \
  DAC##x##_Control,                                                                                                                      \
  DAC##x##_WriteSample,                                                                                                                  \
}

/****** DAC error codes *****/
#define DAC_DRIVER_OK                 0                                         ///< Operation succeeded
#define DAC_DRIVER_ERROR             -1                                         ///< Unspecified error
#define DAC_DRIVER_ERROR_UNSUPPORTED -2                                         ///< Operation not supported
#define DAC_DRIVER_ERROR_PARAMETER   -3                                         ///< Parameter error

/****** Current driver status flag definition *****/
#define DAC_FLAG_INITIALIZED        (1UL << 0)                                  ///< DAC initialized

/****** DAC Control Codes *****/
#define DAC_CONTROL_Pos               0
#define DAC_CONTROL_Msk              (0xFFUL << DAC_CONTROL_Pos)
#define DAC_CONTROL_OUTPUT_BUFFER    (0x00UL << DAC_CONTROL_Pos)                ///< Control DAC Output buffer; arg: 0=enable (default), 1=disable

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* DAC Information (Run-Time) */
typedef struct _DAC_INFO {
  uint32_t                  flags;        // Current state flags
} DAC_INFO;

/* DAC Resource Configuration */
typedef struct _DAC_RESOURCES {
  DAC_t                      *reg;        // DAC peripheral register interface
  DAC_INFO                  *info;        // Run-Time information
  uint32_t           output_range;        // DAC output range
} const DAC_RESOURCES;

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

#endif /* DAC_ADUC7023_H_ */
