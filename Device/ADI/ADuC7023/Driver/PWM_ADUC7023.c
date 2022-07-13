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

#include <string.h>

#include "Driver/PWM_ADUC7023.h"

#if defined(USE_PWM)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* PWM Information (Run-Time) */
static PWM_INFO PWM_Info;

/* PWM Resources */
static PWM_RESOURCES PWM_Resources = {
  PWM,
  /* Pin Configuration */
  {
#if defined(USE_PWM_OUT0)
    &(PWM_PIN){PWM_OUT0_GPIO_PORT, PWM_OUT0_GPIO_PIN, PWM_OUT0_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_PWM_OUT1)
    &(PWM_PIN){PWM_OUT1_GPIO_PORT, PWM_OUT1_GPIO_PIN, PWM_OUT1_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_PWM_OUT2)
    &(PWM_PIN){PWM_OUT2_GPIO_PORT, PWM_OUT2_GPIO_PIN, PWM_OUT2_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_PWM_OUT3)
    &(PWM_PIN){PWM_OUT3_GPIO_PORT, PWM_OUT3_GPIO_PIN, PWM_OUT3_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_PWM_OUT4)
    &(PWM_PIN){PWM_OUT4_GPIO_PORT, PWM_OUT4_GPIO_PIN, PWM_OUT4_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_PWM_TRIP)
    &(PWM_PIN){PWM_TRIP_GPIO_PORT, PWM_TRIP_GPIO_PIN, PWM_TRIP_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_PWM_SYNC)
    &(PWM_PIN){PWM_SYNC_GPIO_PORT, PWM_SYNC_GPIO_PIN, PWM_SYNC_GPIO_FUNC},
#else
    NULL,
#endif
  },
  &PWM_Info,
  PCC_PERIPH_PWM
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Initialize Pulse-Width Modulator.
 * @return      Execution status
 */
static int32_t PWM_Initialize(void)
{
  PWM_PIN  *pin;
  PWM_INFO *info = PWM_Resources.info;

  if ((info->flags & PWM_FLAG_INITIALIZED) != 0U) {
    return (PWM_DRIVER_OK);
  }

  /* Configure PWM Pins */
  GPIO_PIN_CFG_t pin_cfg = {
    .mode      = GPIO_MODE_INPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  for (uint32_t i = 0U; i < PWM_PIN_NUM; ++i) {
    if (PWM_Resources.pin[i] != NULL) {
      pin = PWM_Resources.pin[i];
      pin_cfg.func = pin->func;
      pin->gpio->PinConfig(pin->pin, &pin_cfg);
    }
  }

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(PWM_INFO));

  info->flags = PWM_FLAG_INITIALIZED;

  return (PWM_DRIVER_OK);
}

/**
 * @brief       De-initialize Pulse-Width Modulator.
 * @return      Execution status
 */
static int32_t PWM_Uninitialize(void)
{
  PWM_PIN  *pin;
  PWM_INFO *info = PWM_Resources.info;

  /* Unconfigure PWM Pins */
  GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_INPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  for (uint32_t i = 0U; i < PWM_PIN_NUM; ++i) {
    if (PWM_Resources.pin[i] != NULL) {
      pin = PWM_Resources.pin[i];
      pin->gpio->PinConfig(pin->pin, &pin_cfg);
    }
  }

  info->flags = 0U;

  return (PWM_DRIVER_OK);
}

/**
 * @brief       Control PWM Interface Power.
 * @param[in]   state  Power state
 * @return      Execution status
 */
static int32_t PWM_PowerControl(PWM_POWER_STATE state)
{
  PWM_INFO *info = PWM_Resources.info;
  PWM_t    *reg  = PWM_Resources.reg;

  switch (state) {
    case PWM_POWER_OFF:
      /* Disable peripheral */
      reg->PWMCON1 = 0U;

      /* Disable PWM peripheral clock */
      PCC_DisablePeriph(PWM_Resources.pcc_periph);

      info->flags &= ~PWM_FLAG_POWERED;
      break;

    case PWM_POWER_FULL:
      if ((info->flags & PWM_FLAG_INITIALIZED) == 0U) {
        return (PWM_DRIVER_ERROR);
      }

      if ((info->flags & PWM_FLAG_POWERED) != 0U) {
        return (PWM_DRIVER_OK);
      }

      /* Enable I2C peripheral clock */
      PCC_EnablePeriph(PWM_Resources.pcc_periph);

      /* Initial peripheral setup */
      reg->PWMCON1 = 0U;

      /* Ready for operation */
      info->flags |= PWM_FLAG_POWERED;
      break;

    default:
      return (PWM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (PWM_DRIVER_OK);
}

/**
 * @brief       Control PWM Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 */
static int32_t PWM_Control(uint32_t control, uint32_t arg)
{
  PWM_INFO *info = PWM_Resources.info;
  PWM_t    *reg  = PWM_Resources.reg;

  if ((info->flags & PWM_FLAG_POWERED) == 0U) {
    return (PWM_DRIVER_ERROR);
  }

  switch (control & PWM_CONTROL_Msk) {
    case PWM_CONFIGURE:
      switch (control & PWM_COMPARE_Msk) {
        case PWM0_COMPARE0:
          reg->PWM0COM0 = arg & PWM0COM0_VAL_Msk;
          break;

        case PWM0_COMPARE1:
          reg->PWM0COM1 = arg & PWM0COM1_VAL_Msk;
          break;

        case PWM0_COMPARE2:
          reg->PWM0COM2 = arg & PWM0COM2_VAL_Msk;
          break;

        case PWM0_LENGTH:
          reg->PWM0LEN = arg & PWM0LEN_VAL_Msk;
          break;

        case PWM1_COMPARE0:
          reg->PWM1COM0 = arg & PWM1COM0_VAL_Msk;
          break;

        case PWM1_COMPARE1:
          reg->PWM1COM1 = arg & PWM1COM1_VAL_Msk;
          break;

        case PWM1_COMPARE2:
          reg->PWM1COM2 = arg & PWM1COM2_VAL_Msk;
          break;

        case PWM1_LENGTH:
          reg->PWM1LEN = arg & PWM1LEN_VAL_Msk;
          break;

        case PWM2_COMPARE0:
          reg->PWM2COM0 = arg & PWM2COM0_VAL_Msk;
          break;

        case PWM2_COMPARE1:
          reg->PWM2COM1 = arg & PWM2COM1_VAL_Msk;
          break;

        case PWM2_LENGTH:
          reg->PWM2LEN = arg & PWM2LEN_VAL_Msk;
          break;
      }
      break;

    case PWM_CONTROL:
      if ((arg & 1UL) == 0U) {
        reg->PWMCON1 = 0U;
      }
      else {
        reg->PWMCON1 = PWMCON1_PWMEN | PWM_CLK_PRESCALE;
      }
      break;
  }

  return (PWM_DRIVER_OK);
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

Driver_PWM_t Driver_PWM = {
  PWM_Initialize,
  PWM_Uninitialize,
  PWM_PowerControl,
  PWM_Control
};

#endif /* defined(USE_PWM) */
