/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "Driver/ADC_ADUC7023.h"

#if defined(USE_ADC)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

static void ADC_IRQHandler(void);

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* ADC Information (Run-Time) */
static ADC_INFO ADC_Info;

/* ADC Resources */
static ADC_RESOURCES ADC_Resources = {
  ADC,
  /* Pin Configuration */
  {
#if defined(USE_ADC_IN4)
    &(ADC_PIN){ADC_IN4_GPIO_PORT, ADC_IN4_GPIO_PIN, ADC_IN4_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN5)
    &(ADC_PIN){ADC_IN5_GPIO_PORT, ADC_IN5_GPIO_PIN, ADC_IN5_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN6)
    &(ADC_PIN){ADC_IN6_GPIO_PORT, ADC_IN6_GPIO_PIN, ADC_IN6_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN7)
    &(ADC_PIN){ADC_IN7_GPIO_PORT, ADC_IN7_GPIO_PIN, ADC_IN7_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN8)
    &(ADC_PIN){ADC_IN8_GPIO_PORT, ADC_IN8_GPIO_PIN, ADC_IN8_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN9)
    &(ADC_PIN){ADC_IN9_GPIO_PORT, ADC_IN9_GPIO_PIN, ADC_IN9_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN10)
    &(ADC_PIN){ADC_IN10_GPIO_PORT, ADC_IN10_GPIO_PIN, ADC_IN10_GPIO_FUNC},
#else
    NULL,
#endif
#if defined(USE_ADC_IN12)
    &(ADC_PIN){ADC_IN12_GPIO_PORT, ADC_IN12_GPIO_PIN, ADC_IN12_GPIO_FUNC},
#else
    NULL,
#endif
  },
  &ADC_Info,
  /* Interrupt Configuration */
  {
    ADC_INT_PRIORITY,
    ADC_IRQn,
    ADC_IRQHandler,
  },
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Initialize ADC Interface.
 * @param[in]   cb_event  Pointer to ADC_SignalEvent
 * @return      Execution status
 */
static int32_t ADC_Initialize(ADC_SignalEvent_t cb_event)
{
  ADC_PIN  *adc_pin;
  ADC_INFO *info = ADC_Resources.info;

  if ((info->flags & ADC_FLAG_INITIALIZED) != 0U) {
    return (ADC_DRIVER_OK);
  }

  /* Configure ADC Pins */
  GPIO_PIN_CFG_t pin_cfg = {
    .mode      = GPIO_MODE_INPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  for (uint32_t i = 0U; i < ADC_PIN_NUM; ++i) {
    if (ADC_Resources.pin[i] != NULL) {
      adc_pin = ADC_Resources.pin[i];
      pin_cfg.func = adc_pin->func;
      adc_pin->gpio->PinConfig(adc_pin->pin, &pin_cfg);
    }
  }

  info->cb_event = cb_event;
  info->flags    = ADC_FLAG_INITIALIZED;

  return (ADC_DRIVER_OK);
}

/**
 * @brief       De-initialize ADC Interface.
 * @return      Execution status
 */
static int32_t ADC_Uninitialize(void)
{
  ADC_PIN  *adc_pin;
  ADC_INFO *info = ADC_Resources.info;

  /* Unconfigure ADC Pins */
  GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_INPUT,
    .pull_mode = GPIO_PULL_UP,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  for (uint32_t i = 0U; i < ADC_PIN_NUM; ++i) {
    if (ADC_Resources.pin[i] != NULL) {
      adc_pin = ADC_Resources.pin[i];
      adc_pin->gpio->PinConfig(adc_pin->pin, &pin_cfg);
    }
  }

  info->cb_event = NULL;
  info->flags    = 0U;

  return (ADC_DRIVER_OK);
}

/**
 * @brief       Control ADC Interface Power.
 * @param[in]   state  Power state
 * @return      Execution status
 */
static int32_t ADC_PowerControl(ADC_POWER_STATE state)
{
  ADC_INFO *info = ADC_Resources.info;
  ADC_IRQ  *irq  = &ADC_Resources.irq;
  ADC_t    *reg  = ADC_Resources.reg;

  switch (state) {
    case ADC_POWER_OFF:
      /* Disable peripheral */
      reg->CON &= ~ADCCON_PWR_UP;
      reg->TSCON &= ~TSCON_EN;
      REF->CON &= ~REFCON_OUT_EN;

      /* Disable ADC IRQ */
      IRQ_Disable(irq->num);

      info->flags &= ~ADC_FLAG_POWERED;
      break;

    case ADC_POWER_FULL:
      if ((info->flags & ADC_FLAG_INITIALIZED) == 0U) {
        return (ADC_DRIVER_ERROR);
      }

      if ((info->flags & ADC_FLAG_POWERED) != 0U) {
        return (ADC_DRIVER_OK);
      }

      /* Enable ADC IRQ */
      IRQ_SetPriority(irq->num, irq->priority);
      IRQ_SetHandler(irq->num, irq->handler);
      IRQ_SetMode(irq->num, IRQ_MODE_TYPE_IRQ);
      IRQ_Enable(irq->num);

      /* Initial peripheral setup */
      REF->CON |= REFCON_OUT_EN;
      reg->TSCON |= TSCON_EN;
      reg->CON |= ADCCON_PWR_UP;


      /* Ready for operation */
      info->flags |= ADC_FLAG_POWERED;
      break;

    default:
      return (ADC_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ADC_DRIVER_OK);
}

/**
 * @brief       Control ADC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 */
static int32_t ADC_Control(uint32_t control, uint32_t arg)
{
  uint32_t  con;
  uint32_t  value;
  ADC_INFO *info = ADC_Resources.info;
  ADC_t    *reg  = ADC_Resources.reg;

  if ((info->flags & ADC_FLAG_POWERED) == 0U) {
    /* ADC not powered */
    return (ADC_DRIVER_ERROR);
  }

  con = reg->CON;

  switch (control & ADC_CONTROL_Msk) {
    case ADC_CONFIGURE:
      /* Configure ADC Mode */
      value = (control & ADC_MODE_Msk) >> ADC_MODE_Pos;
      MODIFY_REG(con, ADCCON_CONV_MODE_Msk, value << ADCCON_CONV_MODE_Pos);

      /* Configure ADC Conversion Type */
      value = (control & ADC_TRG_Msk) >> ADC_TRG_Pos;
      MODIFY_REG(con, ADCCON_CONV_TYPE_Msk, value << ADCCON_CONV_TYPE_Pos);

      /* Configure ADC Acquisition Time */
      value = (control & ADC_ACQ_TIME_Msk) >> ADC_ACQ_TIME_Pos;
      MODIFY_REG(con, ADCCON_ACQ_TIME_Msk, value << ADCCON_ACQ_TIME_Pos);

      /* Configure ADC Clock Divider */
      value = (control & ADC_CLK_DIV_Msk) >> ADC_CLK_DIV_Pos;
      MODIFY_REG(con, ADCCON_CLK_DIV_Msk, value << ADCCON_CLK_DIV_Pos);

      /* Configure ADC Edge Triggered Mode */
      con |= ADCCON_CONV_TEMP;
      break;

    case ADC_CONTROL:
      if ((arg & ADC_CONV_Msk) == ADC_CONV_STOP) {
        con &= ~ADCCON_CONV_START;

        if ((con & ADCCON_CONV_TYPE_Msk) == ADCCON_CONV_TYPE_CONT) {
          MODIFY_REG(con, ADCCON_CONV_TYPE_Msk, ADCCON_CONV_TYPE_PIN);
        }

        info->flags &= ~ADC_FLAG_ENABLE;
      }
      else {
        info->flags |= ADC_FLAG_ENABLE;

        if ((arg & ADC_CONV_Msk) == ADC_CONV_SOFT_SINGLE) {
          MODIFY_REG(con, ADCCON_CONV_TYPE_Msk, ADCCON_CONV_TYPE_SINGLE);
        }
        else if ((arg & ADC_CONV_Msk) == ADC_CONV_SOFT_CONT) {
          MODIFY_REG(con, ADCCON_CONV_TYPE_Msk, ADCCON_CONV_TYPE_CONT);
        }

        con |= ADCCON_CONV_START;
      }
      break;

    case ADC_CHANNEL_SELECT:
      /* Configure ADC Channel Select */
      value = (arg & ADC_P_CNL_SEL_Msk) >> ADC_P_CNL_SEL_Pos;
      MODIFY_REG(reg->CP, ADCCP_SEL_CHN_P_Msk, value << ADCCP_SEL_CHN_P_Pos);

      value = (arg & ADC_N_CNL_SEL_Msk) >> ADC_N_CNL_SEL_Pos;
      MODIFY_REG(reg->CN, ADCCP_SEL_CHN_N_Msk, value << ADCCP_SEL_CHN_N_Pos);
      break;

    default:
      return (ADC_DRIVER_ERROR_UNSUPPORTED);
  }

  reg->CON = con;

  info->flags |= ADC_FLAG_CONFIGURED;

  return (ADC_DRIVER_OK);
}

/**
 * @brief       Start acquisition data.
 * @param[out]  data  Pointer to buffer for data
 * @param[in]   num   Number of data items to acquire
 * @return      Execution status
 */
static int32_t ADC_GetData(int16_t *data, uint32_t num)
{
  ADC_INFO *info = ADC_Resources.info;

  if ((data == NULL) || (num == 0U)) {
    return (ADC_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & ADC_FLAG_CONFIGURED) == 0U) {
    /* ADC is not configured */
    return (ADC_DRIVER_ERROR);
  }

  if (info->status.busy != 0U) {
    return (ADC_DRIVER_ERROR_BUSY);
  }

  info->status.busy     = 1U;
  info->status.overflow = 0U;

  ADC_ACQ_INFO *acq = &info->acq_info;

  acq->buf = data;
  acq->cnt = 0U;
  acq->num = num;

  return (ADC_DRIVER_OK);
}

/**
 * @brief       Get acquired data count.
 * @return      Number of data items acquired
 */
static uint32_t ADC_GetCount(void)
{
  return (ADC_Resources.info->acq_info.cnt);
}

/**
 * @brief       Get ADC status.
 * @return      ADC status
 */
static ADC_STATUS_t ADC_GetStatus(void)
{
  return (ADC_Resources.info->status);
}

/**
 * @brief       ADC Interrupt handler.
 */
static void ADC_IRQHandler(void)
{
  uint32_t  data;
  uint32_t  event;
  ADC_INFO *info = ADC_Resources.info;
  ADC_t    *reg  = ADC_Resources.reg;

  data  = reg->DAT;
  event = 0U;

  if ((info->flags & ADC_FLAG_ENABLE) != 0U) {
    if (info->status.busy == 0U) {
      /* Set ADC overflow event and flag */
      info->status.overflow = 1U;
      event |= ADC_EVENT_DATA_OVERFLOW;
    }
    else {
      ADC_ACQ_INFO *acq = &info->acq_info;

      *acq->buf++ = (int16_t)(data >> ADCDAT_DATA_Pos);

      if (++acq->cnt == acq->num) {
        info->status.busy = 0U;
        event |= ADC_EVENT_ACQ_COMPLETE;
      }
    }
  }

  if (event != 0U && info->cb_event != NULL) {
    info->cb_event(event);
  }
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

Driver_ADC_t Driver_ADC = {
    ADC_Initialize,
    ADC_Uninitialize,
    ADC_PowerControl,
    ADC_Control,
    ADC_GetData,
    ADC_GetCount,
    ADC_GetStatus,
};

#endif  /* defined(USE_ADC) */
