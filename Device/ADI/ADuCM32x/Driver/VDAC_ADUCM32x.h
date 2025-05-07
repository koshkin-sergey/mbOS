/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: VDAC Driver for ADI ADuCM32x
 */

#ifndef VDAC_ADUCM32x_H_
#define VDAC_ADUCM32x_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/aducm32x.h>
#include <device_config.h>
#include <Driver/Driver_VDAC.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define DAC_RESOLUTION              (12U)

/* DAC0 configuration definitions */
#if defined (DEV_DAC0) && (DEV_DAC0 == 1)
  #define USE_DAC0

  #if !defined(MMR_VDAC0)
    #error "VDAC0 not available for selected device!"
    #undef USE_DAC0
  #endif

  #if (DEV_DAC0_OUTPUT_RANGE == 0)
    #define DAC0_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC0_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif

  #define DAC0_GPIO_PORT              &Driver_GPIO5
  #define DAC0_GPIO_PIN               GPIO_PIN_3
#endif

/* DAC1 configuration definitions */
#if defined (DEV_DAC1) && (DEV_DAC1 == 1)
  #define USE_DAC1

  #if !defined(MMR_VDAC1)
    #error "VDAC1 not available for selected device!"
    #undef USE_DAC1
  #endif

  #if (DEV_DAC1_OUTPUT_RANGE == 0)
    #define DAC1_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC1_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif
#endif

/* DAC2 configuration definitions */
#if defined (DEV_DAC2) && (DEV_DAC2 == 1)
  #define USE_DAC2

  #if !defined(MMR_VDAC2)
    #error "VDAC2 not available for selected device!"
    #undef USE_DAC2
  #endif

  #if (DEV_DAC2_OUTPUT_RANGE == 0)
    #define DAC2_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC2_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif

  #define DAC2_GPIO_PORT              &Driver_GPIO3
  #define DAC2_GPIO_PIN               GPIO_PIN_7
#endif

/* DAC3 configuration definitions */
#if defined (DEV_DAC3) && (DEV_DAC3 == 1)
  #define USE_DAC3

  #if !defined(MMR_VDAC3)
    #error "VDAC3 not available for selected device!"
    #undef USE_DAC3
  #endif

  #if (DEV_DAC3_OUTPUT_RANGE == 0)
    #define DAC3_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC3_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif

  #define DAC3_GPIO_PORT              &Driver_GPIO5
  #define DAC3_GPIO_PIN               GPIO_PIN_0
#endif

/* DAC4 configuration definitions */
#if defined (DEV_DAC4) && (DEV_DAC4 == 1)
  #define USE_DAC4

  #if !defined(MMR_VDAC4)
    #error "VDAC4 not available for selected device!"
    #undef USE_DAC4
  #endif

  #if (DEV_DAC4_OUTPUT_RANGE == 0)
    #define DAC4_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC4_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif
#endif

/* DAC5 configuration definitions */
#if defined (DEV_DAC5) && (DEV_DAC5 == 1)
  #define USE_DAC5

  #if !defined(MMR_VDAC5)
    #error "VDAC5 not available for selected device!"
    #undef USE_DAC5
  #endif

  #if (DEV_DAC5_OUTPUT_RANGE == 0)
    #define DAC5_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC5_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif
#endif

/* DAC6 configuration definitions */
#if defined (DEV_DAC6) && (DEV_DAC6 == 1)
  #define USE_DAC6

  #if !defined(MMR_VDAC6)
    #error "VDAC6 not available for selected device!"
    #undef USE_DAC6
  #endif

  #if (DEV_DAC6_OUTPUT_RANGE == 0)
    #define DAC6_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC6_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif

  #define DAC6_GPIO_PORT              &Driver_GPIO5
  #define DAC6_GPIO_PIN               GPIO_PIN_1
#endif

/* DAC7 configuration definitions */
#if defined (DEV_DAC7) && (DEV_DAC7 == 1)
  #define USE_DAC7

  #if !defined(MMR_VDAC7)
    #error "VDAC7 not available for selected device!"
    #undef USE_DAC7
  #endif

  #if (DEV_DAC7_OUTPUT_RANGE == 0)
    #define DAC7_OUTPUT_RANGE         DACCON_RN_IREF
  #else
    #define DAC7_OUTPUT_RANGE         DACCON_RN_AVDD
  #endif

  #define DAC7_GPIO_PORT              &Driver_GPIO5
  #define DAC7_GPIO_PIN               GPIO_PIN_2
#endif

#define DACx_EXPORT_DRIVER(x)                                                                                                            \
static int32_t DAC##x##_Initialize   (void)                           { return (DAC_Initialize   (              &DAC##x##_Resources)); } \
static int32_t DAC##x##_Uninitialize (void)                           { return (DAC_Uninitialize (              &DAC##x##_Resources)); } \
static int32_t DAC##x##_Control      (uint32_t control, uint32_t arg) { return (DAC_Control      (control, arg, &DAC##x##_Resources)); } \
static int32_t DAC##x##_WriteSample  (uint16_t value)                 { return (DAC_WriteSample  (value,        &DAC##x##_Resources)); } \
                                                                                                                                         \
extern                                                                                                                                   \
Driver_DAC_t Driver_DAC##x;                                                                                                              \
Driver_DAC_t Driver_DAC##x = {                                                                                                           \
  DAC##x##_Initialize,                                                                                                                   \
  DAC##x##_Uninitialize,                                                                                                                 \
  DAC##x##_Control,                                                                                                                      \
  DAC##x##_WriteSample,                                                                                                                  \
}

/****** Current driver status flag definition *****/
#define DAC_FLAG_INITIALIZED        (1UL << 0)                                  ///< DAC Initialized
#define DAC_FLAG_CONFIGURED         (1UL << 1)                                  ///< DAC Configured

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* DAC Pin Configuration */
typedef const struct DAC_Pin {
  Driver_GPIO_t             *gpio;        // Pointer to GPIO driver
  GPIO_PIN_t                  pin;        // IO pin
} DAC_Pin_t;

/* DAC Information (Run-Time) */
typedef struct DAC_Info {
  uint32_t                  flags;        // Current state flags
  uint32_t              data_bits;        // Number of Data bits
  uint32_t                   mode;        // Mode
} DAC_Info_t;

/* DAC Resource Configuration */
typedef struct DAC_Resources {
  MMR_VDAC_t                 *reg;        // DAC peripheral register interface
  DAC_Info_t                *info;        // Run-Time information
  uint32_t           output_range;        // DAC output range
  DAC_Pin_t                  *pin;
} const DAC_Resources_t;

#endif /* VDAC_ADUCM32x_H_ */
