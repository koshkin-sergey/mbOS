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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "VDAC_ADUCM32x.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#if defined(USE_DAC0) || defined(USE_DAC1) || \
    defined(USE_DAC2) || defined(USE_DAC3) || \
    defined(USE_DAC4) || defined(USE_DAC5) || \
    defined(USE_DAC6) || defined(USE_DAC7)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Configure DAC Pins */
static const GPIO_PIN_CFG_t pin_cfg_dac = {
  GPIO_PIN_FUNC_1,
  GPIO_MODE_ANALOG,
  GPIO_PULL_DISABLE,
};

static const GPIO_PIN_CFG_t pin_cfg_reset = {
  GPIO_PIN_FUNC_0,
  GPIO_MODE_ANALOG,
  GPIO_PULL_DISABLE,
};

#if defined(USE_DAC0)
/* DAC0 Information (Run-Time) */
static DAC_Info_t DAC0_Info;

/* DAC0 Resources */
static DAC_Resources_t DAC0_Resources = {
  MMR_VDAC0,
  &DAC0_Info,
  DAC0_OUTPUT_RANGE,
  &(DAC_Pin_t){DAC0_GPIO_PORT, DAC0_GPIO_PIN}
};
#endif /* USE_DAC0 */

#if defined(USE_DAC1)
/* DAC1 Information (Run-Time) */
static DAC_Info_t DAC1_Info;

/* DAC1 Resources */
static DAC_Resources_t DAC1_Resources = {
  MMR_VDAC1,
  &DAC1_Info,
  DAC1_OUTPUT_RANGE,
  NULL
};
#endif /* USE_DAC1 */

#if defined(USE_DAC2)
/* DAC2 Information (Run-Time) */
static DAC_Info_t DAC2_Info;

/* DAC2 Resources */
static DAC_Resources_t DAC2_Resources = {
  MMR_VDAC2,
  &DAC2_Info,
  DAC2_OUTPUT_RANGE,
  &(DAC_Pin_t){DAC2_GPIO_PORT, DAC2_GPIO_PIN}
};
#endif /* USE_DAC2 */

#if defined(USE_DAC3)
/* DAC3 Information (Run-Time) */
static DAC_Info_t DAC3_Info;

/* DAC3 Resources */
static DAC_Resources_t DAC3_Resources = {
  MMR_VDAC3,
  &DAC3_Info,
  DAC3_OUTPUT_RANGE,
  &(DAC_Pin_t){DAC3_GPIO_PORT, DAC3_GPIO_PIN}
};
#endif /* USE_DAC3 */

#if defined(USE_DAC4)
/* DAC4 Information (Run-Time) */
static DAC_Info_t DAC4_Info;

/* DAC4 Resources */
static DAC_Resources_t DAC4_Resources = {
  MMR_VDAC4,
  &DAC4_Info,
  DAC4_OUTPUT_RANGE,
  NULL
};
#endif /* USE_DAC4 */

#if defined(USE_DAC5)
/* DAC5 Information (Run-Time) */
static DAC_Info_t DAC5_Info;

/* DAC5 Resources */
static DAC_Resources_t DAC5_Resources = {
  MMR_VDAC5,
  &DAC5_Info,
  DAC5_OUTPUT_RANGE,
  NULL
};
#endif /* USE_DAC5 */

#if defined(USE_DAC6)
/* DAC6 Information (Run-Time) */
static DAC_Info_t DAC6_Info;

/* DAC6 Resources */
static DAC_Resources_t DAC6_Resources = {
  MMR_VDAC6,
  &DAC6_Info,
  DAC6_OUTPUT_RANGE,
  &(DAC_Pin_t){DAC6_GPIO_PORT, DAC6_GPIO_PIN}
};
#endif /* USE_DAC6 */

#if defined(USE_DAC7)
/* DAC7 Information (Run-Time) */
static DAC_Info_t DAC7_Info;

/* DAC7 Resources */
static DAC_Resources_t DAC7_Resources = {
  MMR_VDAC7,
  &DAC7_Info,
  DAC7_OUTPUT_RANGE,
  &(DAC_Pin_t){DAC7_GPIO_PORT, DAC7_GPIO_PIN}
};
#endif /* USE_DAC7 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          int32_t DAC_Initialize(void)
 * @brief       Initialize DAC Interface.
 * @return      Execution status
 */
static
int32_t DAC_Initialize(DAC_Resources_t *dac)
{
  if ((dac->info->flags & DAC_FLAG_INITIALIZED) != 0U) {
    return (DRIVER_OK);
  }

  if (dac->pin != NULL) {
    dac->pin->gpio->PinConfig(dac->pin->pin, &pin_cfg_dac);
  }

  dac->reg->DACDAT = 0UL;
  dac->reg->DACCON = (uint16_t)dac->output_range;

  dac->info->flags = DAC_FLAG_INITIALIZED;

  return (DRIVER_OK);
}

/**
 * @fn          int32_t DAC_Uninitialize(void)
 * @brief       De-initialize DAC Interface.
 * @return      Execution status
 */
static
int32_t DAC_Uninitialize(DAC_Resources_t *dac)
{
  dac->reg->DACCON = (uint16_t)DACCON_PD;

  if (dac->pin != NULL) {
    dac->pin->gpio->PinConfig(dac->pin->pin, &pin_cfg_reset);
  }

  dac->info->flags = 0U;

  return (DRIVER_OK);
}

/**
 * @fn          int32_t DAC_Control(uint32_t control, uint32_t arg)
 * @brief       Control DAC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 */
static
int32_t DAC_Control(uint32_t control, uint32_t arg, DAC_Resources_t *dac)
{
  DAC_Info_t *info = dac->info;

  if ((info->flags & DAC_FLAG_INITIALIZED) == 0U) {
    /* ADC not initialized */
    return (DRIVER_ERROR);
  }

  switch (control & DAC_CONTROL_Msk) {
    case DAC_CONFIGURE:
      break;

    case DAC_CONTROL:
      if (arg == 0U) {
        dac->reg->DACCON &= (uint16_t)~DACCON_EN;
      }
      else {
        dac->reg->DACCON |=  DACCON_EN;
      }
      return (DRIVER_OK);

    default:
      return (DRIVER_ERROR);
  }

  /* Trigger Mode */
  switch (control & DAC_TRIGGER_Msk) {
    case DAC_TRIGGER_NONE:
      info->mode = DAC_TRIGGER_NONE;
      break;

    default:
      return (DRIVER_ERROR_UNSUPPORTED);
  }

  /* Data Bits */
  info->data_bits = (control & DAC_DATA_BITS_Msk) >> DAC_DATA_BITS_Pos;
  if (info->data_bits > DAC_RESOLUTION) {
    return (DRIVER_ERROR_UNSUPPORTED);
  }

  info->flags |= DAC_FLAG_CONFIGURED;

  return (DRIVER_OK);
}

/**
 * @fn          int32_t DAC_WriteSample(uint32_t value)
 * @brief       Write the sample value.
 * @param[in]   value  Sample value.
 * @return      Execution status
 */
static
int32_t DAC_WriteSample(uint32_t value, DAC_Resources_t *dac)
{
  DAC_Info_t *info = dac->info;

  if ((info->flags & DAC_FLAG_CONFIGURED) == 0U) {
    return (DRIVER_ERROR);
  }

  if (value > ((1UL << info->data_bits) - 1UL)) {
    return (DRIVER_ERROR_PARAMETER);
  }

  dac->reg->DACDAT = DACDAT_DAT(value);

  return (DRIVER_OK);
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

#if defined(USE_DAC4)
  DACx_EXPORT_DRIVER(4);
#endif  /* USE_DAC4 */

#if defined(USE_DAC5)
  DACx_EXPORT_DRIVER(5);
#endif  /* USE_DAC5 */

#if defined(USE_DAC6)
  DACx_EXPORT_DRIVER(6);
#endif  /* USE_DAC6 */

#if defined(USE_DAC7)
  DACx_EXPORT_DRIVER(7);
#endif  /* USE_DAC7 */

#endif  /* defined(USE_DAC) */
