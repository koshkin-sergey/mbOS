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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "Driver/DAC_ADUC7023.h"

#if defined(USE_DAC0) || defined(USE_DAC1) || \
    defined(USE_DAC2) || defined(USE_DAC3)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

#if defined(USE_DAC0)
/* DAC0 Information (Run-Time) */
static DAC_INFO DAC0_Info;

/* DAC0 Resources */
static DAC_RESOURCES DAC0_Resources = {
  DAC0,
  &DAC0_Info,
  DAC0_OUTPUT_RANGE,
};
#endif /* USE_DAC0 */

#if defined(USE_DAC1)
/* DAC1 Information (Run-Time) */
static DAC_INFO DAC1_Info;

/* DAC1 Resources */
static DAC_RESOURCES DAC1_Resources = {
  DAC1,
  &DAC1_Info,
  DAC1_OUTPUT_RANGE,
};
#endif /* USE_DAC1 */

#if defined(USE_DAC2)
/* DAC2 Information (Run-Time) */
static DAC_INFO DAC2_Info;

/* DAC2 Resources */
static DAC_RESOURCES DAC2_Resources = {
  DAC2,
  &DAC2_Info,
  DAC2_OUTPUT_RANGE,
};
#endif /* USE_DAC2 */

#if defined(USE_DAC3)
/* DAC3 Information (Run-Time) */
static DAC_INFO DAC3_Info;

/* DAC3 Resources */
static DAC_RESOURCES DAC3_Resources = {
  DAC3,
  &DAC3_Info,
  DAC3_OUTPUT_RANGE,
};
#endif /* USE_DAC3 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          int32_t DAC_Initialize(void)
 * @brief       Initialize DAC Interface.
 * @return      Execution status
 */
static int32_t DAC_Initialize(DAC_RESOURCES *dac)
{
  int32_t   status = DAC_DRIVER_OK;
  DAC_INFO *info   = dac->info;

  if ((info->flags & DAC_FLAG_INITIALIZED) != 0U) {
    return (status);
  }

  REF->CON |= REFCON_OUT_EN;

  if (dac->output_range == 0U) {
    dac->reg->CON = DACCON_CLR | DACCON_RANGE_VREF;
  }
  else if (dac->output_range == 1U) {
    dac->reg->CON = DACCON_CLR | DACCON_RANGE_AVDD;
  }
  else {
    status = DAC_DRIVER_ERROR_UNSUPPORTED;
  }

  info->flags = DAC_FLAG_INITIALIZED;

  return (status);
}

/**
 * @fn          int32_t DAC_Uninitialize(void)
 * @brief       De-initialize DAC Interface.
 * @return      Execution status
 */
static int32_t DAC_Uninitialize(DAC_RESOURCES *dac)
{
  dac->reg->CON    = 0U;
  dac->info->flags = 0U;

  return (DAC_DRIVER_OK);
}

/**
 * @fn          int32_t DAC_Control(uint32_t control, uint32_t arg)
 * @brief       Control DAC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 */
static int32_t DAC_Control(uint32_t control, uint32_t arg, DAC_RESOURCES *dac)
{
  if ((dac->info->flags & DAC_FLAG_INITIALIZED) == 0U) {
    return (DAC_DRIVER_ERROR);
  }

  switch (control & DAC_CONTROL_Msk) {
    case DAC_CONTROL_OUTPUT_BUFFER:
      if (arg == 0U) {
        MODIFY_REG(dac->reg->CON, DACCON_BYPASS_Msk, 0U << DACCON_BYPASS_Pos);
      }
      else {
        MODIFY_REG(dac->reg->CON, DACCON_BYPASS_Msk, 1U << DACCON_BYPASS_Pos);
      }
      break;

    default:
      return (DAC_DRIVER_ERROR_UNSUPPORTED);
  }

  return (DAC_DRIVER_OK);
}

/**
 * @fn          int32_t DAC_WriteSample(uint32_t value)
 * @brief       Write the sample value.
 * @param[in]   value  Sample value.
 * @return      Execution status
 */
static int32_t DAC_WriteSample(uint32_t value, DAC_RESOURCES *dac)
{
  DAC_INFO *info = dac->info;

  if ((value & ~0xFFFU) != 0U) {
    return (DAC_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & DAC_FLAG_INITIALIZED) == 0U) {
    return (DAC_DRIVER_ERROR);
  }

  dac->reg->DAT = (value << DACDAT_DATA_Pos) & DACDAT_DATA_Msk;

  return (DAC_DRIVER_OK);
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

#if defined(USE_DAC0)
  DACx_EXPORT_DRIVER(0);
#endif  /* USE_DAC0 */

#if defined(USE_DAC1)
  DACx_EXPORT_DRIVER(1);
#endif  /* USE_DAC1 */

#if defined(USE_DAC2)
  DACx_EXPORT_DRIVER(2);
#endif  /* USE_DAC2 */

#if defined(USE_DAC3)
  DACx_EXPORT_DRIVER(3);
#endif  /* USE_DAC3 */

#endif  /* defined(USE_DAC) */
