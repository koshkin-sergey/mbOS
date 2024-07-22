/**
 * @authors Sergey Koshkin <skoshkin@neoros.ru>
 *          Pimonov Vladimir <vpimonov@neoros.ru>
 * @copyright (C) 2024 “Neoros” LLC <info@neoros.ru>
 * All rights reserved
 *
 * File Name  : ADC_ADUCM32x.c
 * Description: Драйвер АЦП микроконтроллеров ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "ADC_ADUCM32x.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ADC_CLOCK                     (20000000UL)
#define ADC_CHANNEL_NUM               (28)

#if defined(USE_ADC)

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

void LVD1_IRQHandler(void);

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* ADC Information (Run-Time) */
static ADC_INFO ADC_Info;

/* Configure ADC Pins */
static const GPIO_PIN_CFG_t pin_cfg_adc = {
  GPIO_PIN_FUNC_1,
  GPIO_MODE_ANALOG,
  GPIO_PULL_DISABLE,
};

static const GPIO_PIN_CFG_t pin_cfg_reset = {
  GPIO_PIN_FUNC_0,
  GPIO_MODE_ANALOG,
  GPIO_PULL_DISABLE,
};

/* ADC Resources */
static ADC_RESOURCES ADC_Resources = {
  MMR_ADC,
  &ADC_Info,
  /* Interrupt Configuration */
  {
    ADC_INT_PRIORITY,
    LVD1_IRQn,
  },
  &Driver_GPIO4,
  {
#if defined(USE_ADC_IN8)
    &(ADC_Pin_t){ADC_IN8_GPIO_PIN},
#else
    NULL,
#endif
#if defined(USE_ADC_IN9)
    &(ADC_Pin_t){ADC_IN9_GPIO_PIN},
#else
    NULL,
#endif
#if defined(USE_ADC_IN12)
    &(ADC_Pin_t){ADC_IN12_GPIO_PIN},
#else
    NULL,
#endif
#if defined(USE_ADC_IN13)
    &(ADC_Pin_t){ADC_IN13_GPIO_PIN},
#else
    NULL,
#endif
#if defined(USE_ADC_IN14)
    &(ADC_Pin_t){ADC_IN14_GPIO_PIN},
#else
    NULL,
#endif
#if defined(USE_ADC_IN15)
    &(ADC_Pin_t){ADC_IN15_GPIO_PIN},
#else
    NULL,
#endif
  },
};

static ADC_RESOURCES *adc = &ADC_Resources;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void StartSoftwareConversion(void)
{
  MMR_ADC_t *reg = adc->reg;

  switch (adc->info->mode & ADC_CONTROL_Msk) {
    case ADC_MODE_NONSEQUENCE:
      reg->ADCCON |= adc->info->acq_info.num == 1U ? ADCCON_C_TYPE_SINGLE : ADCCON_C_TYPE_CONT;
      MMR_LV_INT->INTSEL |= INTSEL_SEL_ADC_SOFTCONV_1_EN;
      break;

    case ADC_MODE_SEQUENCE:
      reg->ADCSEQC &= ~ADCSEQC_T_Msk;
      reg->ADCCON  |= ADCCON_C_TYPE_CONT;
      reg->ADCSEQ  |= ADCSEQ_EN | ADCSEQ_ST;
      MMR_LV_INT->INTSEL |= INTSEL_SEL_ADC_SEQ_1_EN;
      break;
  }
}

/**
 * @brief       Initialize ADC Interface.
 * @param[in]   cb_event  Pointer to ADC_SignalEvent
 * @return      Execution status
 */
static
int32_t ADC_Initialize(ADC_SignalEvent_t cb_event)
{
  ADC_Pin_t *adc_pin;
  ADC_INFO  *info = adc->info;

  if ((info->flags & ADC_FLAG_INITIALIZED) != 0U) {
    return (DRIVER_OK);
  }

  for (uint32_t i = 0U; i < ADC_CFG_PIN_NUM; ++i) {
    adc_pin = adc->pin[i];
    if (adc_pin != NULL) {
      adc->gpio->PinConfig(adc_pin->pin, &pin_cfg_adc);
    }
  }

  info->cb_event = cb_event;
  info->flags    = ADC_FLAG_INITIALIZED;

  return (DRIVER_OK);
}

/**
 * @brief       De-initialize ADC Interface.
 * @return      Execution status
 */
static
int32_t ADC_Uninitialize(void)
{
  ADC_Pin_t  *adc_pin;
  ADC_INFO *info = adc->info;

  for (uint32_t i = 0U; i < ADC_CFG_PIN_NUM; ++i) {
    adc_pin = adc->pin[i];
    if (adc_pin != NULL) {
      adc->gpio->PinConfig(adc_pin->pin, &pin_cfg_reset);
    }
  }

  info->cb_event = NULL;
  info->flags    = 0U;

  return (DRIVER_OK);
}

/**
 * @brief       Control ADC Interface Power.
 * @param[in]   state  Power state
 * @return      Execution status
 */
static
int32_t ADC_PowerControl(POWER_STATE state)
{
  ADC_INFO  *info = adc->info;
  ADC_IRQ   *irq  = &adc->irq;
  MMR_ADC_t *reg  = adc->reg;

  switch (state) {
    case POWER_OFF:
      /* Disable peripheral */
      reg->ADCCON        = 0U;
      MMR_AFE->AFETEMPC &= ~AFETEMPC_PD;
      MMR_AFE->AFEREFC   =  0x03;

      /* Disable ADC IRQ */
      NVIC_DisableIRQ(irq->num);

      info->flags           &= ~(ADC_FLAG_POWERED | ADC_FLAG_ENABLE);
      info->status.busy      = 0U;
      info->status.overflow  = 0U;
      break;

    case POWER_FULL:
      if ((info->flags & ADC_FLAG_INITIALIZED) == 0U) {
        return (DRIVER_ERROR);
      }

      if ((info->flags & ADC_FLAG_POWERED) != 0U) {
        return (DRIVER_OK);
      }

      /* Initial peripheral setup */
      MMR_AFE->AFEREFC = 0U;
      MMR_InBuf->IBUFCON = 0x000F;
      MMR_LV_RST->LVRST = 1U;
      MMR_LV_INT->INTSEL &= ~(INTSEL_SEL_ADC_SOFTCONV_1_EN | INTSEL_SEL_ADC_SEQ_1_EN);

#if defined (USE_VREF2V5_OUT) && (USE_VREF2V5_OUT == 1)
      MMR_AFE->AFEREFC |=  AFEREFC_B2MA_PDB;
#else
      MMR_AFE->AFEREFC &= ~AFEREFC_B2MA_PDB;
#endif

//#if defined (ADC_VREF_SRC) && (ADC_VREF_SRC == 1)
//      reg->ADCCON      &= ~ADCCON_REFB_PUP;
//      MMR_AFE->AFEREFC |=  AFEREFC_REF;
//#else
//      MMR_AFE->AFEREFC &= ~AFEREFC_REF;
//      reg->ADCCON      |=  ADCCON_REFB_PUP;
//#endif

      /* Enable ADC IRQ ------------------------------------ */
      NVIC_ClearPendingIRQ(irq->num);
      NVIC_SetPriority(irq->num, irq->priority);
      NVIC_EnableIRQ(irq->num);

      reg->ADCCON = ADCCON_REFB_PUP | ADCCON_PUP;

      /* Ready for operation */
      info->flags |= ADC_FLAG_POWERED;
      break;

    default:
      return (DRIVER_ERROR_UNSUPPORTED);
  }

  return (DRIVER_OK);
}

/**
 * @brief       Control ADC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 */
static
int32_t ADC_Control(uint32_t control, uint32_t arg)
{
  ADC_INFO   *info = adc->info;
  MMR_ADC_t  *reg  = adc->reg;

  if ((info->flags & ADC_FLAG_POWERED) == 0U) {
    /* ADC not powered */
    return (DRIVER_ERROR);
  }

  if ((control & ADC_CONTROL_Msk) == ADC_CONTROL) {
    if ((info->flags & ADC_FLAG_CONFIGURED) == 0U) {
      return (DRIVER_ERROR);
    }

    if ((arg & 1UL) == 0U) {
      reg->ADCCON &= ~ADCCON_C_TYPE_Msk;
      reg->ADCSEQC |= ADCSEQC_T_Msk;
      info->flags &= ~ADC_FLAG_ENABLE;
    }
    else {
      if ((info->mode & ADC_TRIGGER_Msk) == ADC_TRIGGER_SOFTWARE) {
        StartSoftwareConversion();
      }
      else {
        MMR_LV_INT->INTSEL |= INTSEL_SEL_ADC_SOFTCONV_1_EN;
      }

      info->flags |= ADC_FLAG_ENABLE;
    }

    return (DRIVER_OK);
  }

  if ((control & ADC_CONTROL_Msk) == ADC_ABORT) {
    ADC_ACQ_INFO *acq = &info->acq_info;

    /* Disable interrupts */
    MMR_LV_INT->INTSEL &= ~(INTSEL_SEL_ADC_SOFTCONV_1_EN | INTSEL_SEL_ADC_SEQ_1_EN);
    /* Clear counters and status */
    info->status.busy     = 0U;
    info->status.overflow = 0U;
    acq->cnt = 0U;
    acq->num = 0U;

    if ((info->flags & ADC_FLAG_ENABLE) != 0U) {
      if ((info->mode & ADC_TRIGGER_Msk) == ADC_TRIGGER_SOFTWARE) {
        StartSoftwareConversion();
      }
      else {
        MMR_LV_INT->INTSEL |= INTSEL_SEL_ADC_SOFTCONV_1_EN;
      }
    }

    return (DRIVER_OK);
  }

  if (info->status.busy != 0U) {
    return (DRIVER_ERROR_BUSY);
  }

  switch (control & ADC_CONTROL_Msk) {
    case ADC_MODE_NONSEQUENCE:
      info->mode = ADC_MODE_NONSEQUENCE;
      break;

    case ADC_MODE_SEQUENCE:
      info->mode = ADC_MODE_SEQUENCE;
      break;

    case ADC_CHANNEL_SELECT:
      if ((info->mode & ADC_CONTROL_Msk) == ADC_MODE_SEQUENCE) {
        return (DRIVER_ERROR);
      }

      uint16_t channel;

      channel = (arg & ADC_NEGATIVE_CHANNEL_Msk) >> ADC_NEGATIVE_CHANNEL_Pos;
      if (channel == 0U) {
        channel = ADCCHA_ADCCN_VREFN_NADC;
      }
      else {
        channel = (channel - 1U) << ADCCHA_ADCCN_Pos;
      }

      channel |= (arg & ADC_POSITIVE_CHANNEL_Msk) - 1U;

      reg->ADCCHA = channel;
      return (DRIVER_OK);

    case ADC_CHANNEL_SCAN:
      if ((info->mode & ADC_CONTROL_Msk) == ADC_MODE_NONSEQUENCE) {
        return (DRIVER_ERROR);
      }

      reg->ADCSEQ = (arg & ADCSEQ_CH_MSK);
      return (DRIVER_OK);

    default:
      return (DRIVER_ERROR_UNSUPPORTED);
  }

  info->data_bits = (control & ADC_DATA_BITS_Msk) >> ADC_DATA_BITS_Pos;
  info->mode |= (control & ADC_TRIGGER_Msk);

  if (arg == 0U) {
    return (DRIVER_ERROR_PARAMETER);
  }

  uint32_t cnvc = (ADC_CLOCK / arg) & ADCCNVC_CNVC_Msk;
  cnvc |= (cnvc / 2U) << ADCCNVC_CNVD_Pos;
  reg->ADCCNVC = cnvc;

  info->flags |= ADC_FLAG_CONFIGURED;

  return (DRIVER_OK);
}

/**
 * @brief       Start acquisition data.
 * @param[out]  data  Pointer to buffer for data
 * @param[in]   num   Number of data items to acquire
 * @return      Execution status
 */
static
int32_t ADC_Acquire(int32_t *data, uint32_t num)
{
  ADC_INFO *info = adc->info;

  if ((info->flags & ADC_FLAG_CONFIGURED) == 0U) {
    /* ADC is not configured */
    return (DRIVER_ERROR);
  }

  if ((data == NULL) || (num == 0U)) {
    return (DRIVER_ERROR_PARAMETER);
  }

  if (info->status.busy != 0U) {
    return (DRIVER_ERROR_BUSY);
  }

  info->status.busy     = 1U;
  info->status.overflow = 0U;

  ADC_ACQ_INFO *acq = &info->acq_info;

  acq->buf = data;
  acq->cnt = 0U;
  acq->num = num;

  if ((info->flags & ADC_FLAG_ENABLE) != 0U) {
    if ((info->mode  & ADC_TRIGGER_Msk) == ADC_TRIGGER_SOFTWARE) {
      StartSoftwareConversion();
    }
    else {
      MMR_LV_INT->INTSEL |= INTSEL_SEL_ADC_SOFTCONV_1_EN;
    }
  }

  return (DRIVER_OK);
}

/**
 * @brief       Get acquired data count.
 * @return      Number of data items acquired
 */
static
uint32_t ADC_GetCount(void)
{
  return (adc->info->acq_info.cnt);
}

/**
 * @brief       Get ADC status.
 * @return      ADC status
 */
static
ADC_STATUS_t ADC_GetStatus(void)
{
  return (adc->info->status);
}

/**
 * @brief       ADC Interrupt handler.
 */
void LVD1_IRQHandler(void)
{
  uint32_t    event;
  register uint32_t status;
  ADC_INFO   *info = adc->info;
  MMR_ADC_t  *reg  = adc->reg;
  ADC_ACQ_INFO *acq = &info->acq_info;

  event = 0U;

  status = (uint16_t)MMR_LV_INT->INTSTA;

  if ((status & (INTSTA_ADC_SEQ | INTSTA_ADC_SOFTCONV)) != 0U) {
    if (acq->num == 0U) {
      MMR_LV_INT->INTSEL &= ~(INTSEL_SEL_ADC_SOFTCONV_1_EN | INTSEL_SEL_ADC_SEQ_1_EN);
      /* Set ADC overflow event and flag */
      info->status.overflow = 1U;
      event |= ADC_EVENT_OVERFLOW;
    }
    else {
      uint32_t value;
      uint32_t data_offset = ADCDAT_DAT_Pos + (16 - info->data_bits);

      if ((status & INTSTA_ADC_SOFTCONV) != 0U) {
        value = reg->ADCDAT[reg->ADCCHA & ADCCHA_ADCCP_Msk] & ADCDAT_DAT_Msk;
        acq->buf[acq->cnt++] = (int32_t)value >> data_offset;
      }
      else {
        uint32_t i = 0;
        uint32_t mask = reg->ADCSEQ;

        while (mask != 0U && acq->cnt < acq->num) {
          if ((mask & 1UL) != 0U) {
            value = reg->ADCDAT[i] & ADCDAT_DAT_Msk;
            acq->buf[acq->cnt++] = (int32_t)value >> data_offset;
          }
          mask >>= 1;
          ++i;
        }
      }

      if (acq->cnt == acq->num) {
        reg->ADCCON &= ~ADCCON_C_TYPE_Msk;
        MMR_LV_INT->INTSEL &= ~(INTSEL_SEL_ADC_SOFTCONV_1_EN | INTSEL_SEL_ADC_SEQ_1_EN);
        info->status.busy = 0U;
        acq->num = 0U;
        event |= ADC_EVENT_COMPLETE;
      }
    }
  }

  MMR_LV_INT->INTCLR = (uint16_t)status;

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
  ADC_Acquire,
  ADC_GetCount,
  ADC_GetStatus,
};

#endif  /* defined(USE_ADC) */
