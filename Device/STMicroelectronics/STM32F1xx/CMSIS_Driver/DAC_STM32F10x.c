/*
 * Copyright (C) 2018 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: DAC Driver for STMicroelectronics STM32F1xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <string.h>

#include "DAC_STM32F10x.h"

#if defined(USE_DAC1)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define DAC_DRV_VERSION             ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    DAC_API_VERSION,
    DAC_DRV_VERSION
};

/* Driver Capabilities */
static const
DAC_CAPABILITIES DriverCapabilities = {
    2,  /* Number of channels                         */
    1,  /* Supports output buffer                     */
    0,  /* Supports external triggers for conversion  */
    0,  /* Supports noise-wave generation             */
    0,  /* Supports triangular-wave generation        */
};

static const GPIO_PIN_CFG_t DAC_pin_cfg_analog = {
    GPIO_MODE_ANALOG, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

#if defined(USE_DAC1)

/* DAC1 Run-Time Information */
static DAC_INFO          DAC1_Info         = { 0U };
static DAC_TRANSFER_INFO DAC1_TransferInfo = { 0U };

#ifdef USE_DAC1_CH1_OUT_Pin
  static DAC_PIN DAC1_ch1_out = {DAC1_CH1_OUT_GPIOx, DAC1_CH1_OUT_GPIO_Pin};
#endif
#ifdef USE_DAC1_CH2_OUT_Pin
  static DAC_PIN DAC1_ch2_out = {DAC1_CH2_OUT_GPIOx, DAC1_CH2_OUT_GPIO_Pin};
#endif


#ifdef DAC1_CH1_DMA_Instance
static DAC_DMA DAC1_DMA_CH1 = {
  DAC1_CH1_DMA_Instance,
  DAC1_CH1_DMA_Channel,
  DAC1_CH1_DMA_Priority,
  DAC1_CH1_DMA_IRQn
};
#endif

#ifdef DAC1_CH2_DMA_Instance
static DAC_DMA DAC1_DMA_CH2 = {
  DAC1_CH2_DMA_Instance,
  DAC1_CH2_DMA_Channel,
  DAC1_CH2_DMA_Priority,
  DAC1_CH2_DMA_IRQn
};
#endif

#ifdef DAC1_TRG_TIMER_Instance
static DAC_TRIGGER DAC1_Trigger = {
  DAC1_TRG_TIMER_Instance,
  DAC1_TRG_TIMER_Periph,
  DAC1_TRG_TIMER_IRQn,
};
#endif

/* DAC1 Resources */
static const DAC_RESOURCES DAC1_Resources = {
  DAC,
  RCC_PERIPH_DAC,
#ifdef DAC1_TRG_TIMER_Instance
  &DAC1_Trigger,
#else
  NULL,
#endif
  // PINS
  {
#ifdef USE_DAC1_CH1_OUT_Pin
    &DAC1_ch1_out,
#else
    NULL,
#endif
#ifdef USE_DAC1_CH2_OUT_Pin
    &DAC1_ch2_out,
#else
    NULL,
#endif
  },
#ifdef DAC1_CH1_DMA_Instance
  &DAC1_DMA_CH1,
#else
  NULL,
#endif
#ifdef DAC1_CH2_DMA_Instance
  &DAC1_DMA_CH2,
#else
  NULL,
#endif
  &DAC1_Info,
  &DAC1_TransferInfo
};
#endif /* USE_DAC1 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          void PinConfig(const DAC_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
 * @brief       Configure Pin
 * @param[in]   io       Pointer to DAC_PIN
 * @param[in]   pin_cfg  Pointer to GPIO_PIN_CFG_t
 */
static
void PinConfig(const DAC_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
{
  if ((io == NULL) || (pin_cfg == NULL))
    return;

  if (GPIO_GetPortClockState(io->port) == GPIO_PORT_CLK_DISABLE)
    GPIO_PortClock(io->port, GPIO_PORT_CLK_ENABLE);

  GPIO_PinConfig(io->port, io->pin, pin_cfg);
}

/**
 * @fn          ARM_DRIVER_VERSION DACx_GetVersion(void)
 * @brief       Get DAC driver version.
 * @return      \ref ARM_DRV_VERSION
 */
static
ARM_DRIVER_VERSION DACx_GetVersion(void)
{
  return DriverVersion;
}

/**
 * @fn          DAC_CAPABILITIES DACx_GetCapabilities(void)
 * @brief       Get driver capabilities.
 * @return      \ref DAC_CAPABILITIES
 */
static
DAC_CAPABILITIES DACx_GetCapabilities(void)
{
  return DriverCapabilities;
}

/**
 * @fn          int32_t DAC_Initialize(DAC_SignalEvent_t cb_event, const DAC_RESOURCES *dac)
 * @brief       Initialize DAC Interface.
 * @param[in]   cb_event  Pointer to \ref ARM_SPI_SignalEvent
 * @return      \ref execution_status
 */
static
int32_t DAC_Initialize(DAC_SignalEvent_t cb_event, const DAC_RESOURCES *dac)
{
  DAC_INFO *info = dac->info;

  if (info->state & DAC_INITIALIZED)
    return (ARM_DRIVER_OK);

  /* Initialize DAC Run-Time Resources */
  info->cb_event          = cb_event;
  info->status.busy       = 0U;

  /* Clear transfer information */
  memset(dac->xfer, 0, sizeof(DAC_TRANSFER_INFO));

  DAC_IO *io = &dac->io;
  const GPIO_PIN_CFG_t *pin_cfg = &DAC_pin_cfg_analog;

  /* Configure CH1_OUT Pin */
  PinConfig(io->ch1_out, pin_cfg);
  /* Configure CH2_OUT Pin */
  PinConfig(io->ch2_out, pin_cfg);

#ifdef __DAC_DMA_CH1
  DMA_ChannelInitialize((DMA_INFO *)dac->ch1_dma);
#endif
#ifdef __DAC_DMA_CH2
  DMA_ChannelInitialize((DMA_INFO *)dac->ch2_dma);
#endif

  info->state = DAC_INITIALIZED;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t DAC_Uninitialize(const DAC_RESOURCES *dac)
 * @brief       De-initialize DAC Interface.
 * @return      \ref execution_status
 */
static
int32_t DAC_Uninitialize(const DAC_RESOURCES *dac)
{
#ifdef __DAC_DMA_CH1
  DMA_ChannelUninitialize((DMA_INFO *)dac->ch1_dma);
#endif
#ifdef __DAC_DMA_CH2
  DMA_ChannelUninitialize((DMA_INFO *)dac->ch2_dma);
#endif

  /* Clear DAC state */
  dac->info->state = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t DAC_PowerControl(ARM_POWER_STATE state, const DAC_RESOURCES *dac)
 * @brief       Control DAC Interface Power.
 * @param[in]   state  Power state
 * @return      \ref execution_status
 */
static
int32_t DAC_PowerControl(ARM_POWER_STATE state, const DAC_RESOURCES *dac)
{
  DAC_INFO *info = dac->info;

  switch (state) {
    case ARM_POWER_OFF:
#ifdef DAC1_TRG_TIMER_Instance
      /* Disable Timer clock */
      RCC_DisablePeriph(dac->trigger->periph);
      /* Timer peripheral reset */
      RCC_ResetPeriph(dac->trigger->periph);
      /* Disable Timer IRQ */
      NVIC_DisableIRQ(dac->trigger->irq_num);
#endif

      /* DAC peripheral reset */
      RCC_ResetPeriph(dac->periph);
      /* Disable DAC clock */
      RCC_DisablePeriph(dac->periph);
      /* Clear status flags */
      info->status.busy = 0U;
      /* Clear powered flag */
      info->state &= ~DAC_POWERED;
      break;

    case ARM_POWER_FULL:
      if ((info->state & DAC_INITIALIZED) == 0U)
        return (ARM_DRIVER_ERROR);

      if ((info->state & DAC_POWERED) != 0U)
        return (ARM_DRIVER_OK);

      /* Clear status flags */
      info->status.busy = 0U;
      /* Enable DAC clock */
      RCC_EnablePeriph(dac->periph);
      /* DAC peripheral reset */
      RCC_ResetPeriph(dac->periph);

#ifdef DAC1_TRG_TIMER_Instance
      /* Enable Timer clock */
      RCC_EnablePeriph(dac->trigger->periph);
      /* Timer peripheral reset */
      RCC_ResetPeriph(dac->trigger->periph);
      /* Clear and Enable Timer IRQ */
      NVIC_ClearPendingIRQ(dac->trigger->irq_num);
      NVIC_SetPriority(dac->trigger->irq_num, RTE_DAC_INT_PRIORITY);
      NVIC_EnableIRQ(dac->trigger->irq_num);
#endif  /* DAC1_TRG_TIMER_Instance */

      /* Ready for operation - set powered flag */
      info->state |= DAC_POWERED;
      break;

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t DAC_Convert(const void *data, uint32_t num, const DAC_RESOURCES *dac)
 * @brief       Start transfer data to DAC Interface.
 * @param[in]   data  Pointer to buffer with data to transfer to DAC Interface
 * @param[in]   num   Number of data items to send
 * @return      \ref execution_status
 */
static
int32_t DAC_Convert(const void *data, uint32_t num, const DAC_RESOURCES *dac)
{
  DAC_INFO *info;

  if ((data == NULL) || (num == 0U))
    return (ARM_DRIVER_ERROR_PARAMETER);

  info = dac->info;

  if ((info->state & DAC_CONFIGURED) == 0U || DriverCapabilities.trigger == 0U)
    return (ARM_DRIVER_ERROR);

  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

  /* TODO Implement function */

  return (ARM_DRIVER_OK);
}

/**
 * @fn          uint32_t DAC_GetCount(const DAC_RESOURCES *dac)
 * @brief       Get transferred data count.
 * @return      number of data items transferred
 */
static
uint32_t DAC_GetCount(const DAC_RESOURCES *dac)
{
  /* TODO Implement function */
  return 0UL;
}

/**
 * @fn          int32_t DAC_Control(uint32_t control, uint32_t arg, const DAC_RESOURCES *dac)
 * @brief       Control DAC Interface.
 * @param[in]   control  operation
 * @param[in]   arg      argument of operation (optional)
 * @return      \ref execution_status
 */
static
int32_t DAC_Control(uint32_t control, uint32_t arg, const DAC_RESOURCES *dac)
{
  uint32_t dac_cr;
  uint32_t mode, val;
  DAC_INFO *info = dac->info;

  if ((info->state & DAC_POWERED) == 0U)
    return (ARM_DRIVER_ERROR);

  if ((control & DAC_CONTROL_Msk) == DAC_ABORT_CONVERT) {
    return (ARM_DRIVER_OK);
  }

  /* Check for busy flag */
  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

  dac_cr = 0U;
  mode = 0U;

  /* Mode */
  switch (control & DAC_CONTROL_Msk) {
    case DAC_MODE_NO_TRIGGER:
      mode |= DAC_MODE_NO_TRIGGER;
      break;

    case DAC_MODE_SOFTWARE_TRIGGER:
      mode |= DAC_MODE_SOFTWARE_TRIGGER;
      dac_cr |= (DAC_CR_TEN1 | DAC_TRIGGER_SOFTWARE);
      break;

    case DAC_MODE_HARDWARE_TRIGGER:
      if (dac->trigger == NULL)
        return DAC_ERROR_MODE;

      mode |= DAC_MODE_HARDWARE_TRIGGER;

      switch (dac->trigger->periph) {
        case RCC_PERIPH_TIM6:
          val = DAC_TRIGGER_TIM6;
          break;
        case RCC_PERIPH_TIM7:
          val = DAC_TRIGGER_TIM7;
          break;
      }

      dac_cr |= (DAC_CR_TEN1 | val);
      /* TODO Add timer initialization */
      break;

    case DAC_SET_VALUE:
      if ((info->state & DAC_CONFIGURED) == 0U)
        return (ARM_DRIVER_ERROR);

      switch (control & DAC_OUTPUT_CHANNEL_Msk) {
        case DAC_OUTPUT_CHANNEL_1:
          switch (info->mode & DAC_DATA_FORMAT_Msk) {
            case DAC_DATA_FORMAT_12R:
              dac->reg->DHR12R1 = arg;
              break;
            case DAC_DATA_FORMAT_12L:
              dac->reg->DHR12L1 = arg;
              break;
            case DAC_DATA_FORMAT_8R:
              dac->reg->DHR8R1 = arg;
              break;
          }
          break;
        case DAC_OUTPUT_CHANNEL_2:
          switch (info->mode & DAC_DATA_FORMAT_Msk) {
            case DAC_DATA_FORMAT_12R:
              dac->reg->DHR12R2 = arg;
              break;
            case DAC_DATA_FORMAT_12L:
              dac->reg->DHR12L2 = arg;
              break;
            case DAC_DATA_FORMAT_8R:
              dac->reg->DHR8R2 = arg;
              break;
          }
          break;
        case DAC_OUTPUT_CHANNEL_BOTH:
          switch (info->mode & DAC_DATA_FORMAT_Msk) {
            case DAC_DATA_FORMAT_12R:
              dac->reg->DHR12RD = arg;
              break;
            case DAC_DATA_FORMAT_12L:
              dac->reg->DHR12LD = arg;
              break;
            case DAC_DATA_FORMAT_8R:
              dac->reg->DHR8RD = arg;
              break;
          }
          break;
        default:
          return (DAC_ERROR_OUTPUT_CHANNEL);
      }
      return (ARM_DRIVER_OK);

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  /* Output Buffer */
  switch (control & DAC_OUTPUT_BUFFER_Msk) {
    case DAC_OUTPUT_BUFFER_OFF:
      break;
    case DAC_OUTPUT_BUFFER_ON:
      if (DriverCapabilities.output_buffer == 0)
        return (DAC_ERROR_OUTPUT_BUFFER);
      dac_cr |= DAC_CR_BOFF1;
      break;
    default:
      return (DAC_ERROR_OUTPUT_BUFFER);
  }

  /* Data format */
  switch (control & DAC_DATA_FORMAT_Msk) {
    case DAC_DATA_FORMAT_12R:
      mode |= DAC_DATA_FORMAT_12R;
      break;
    case DAC_DATA_FORMAT_12L:
      mode |= DAC_DATA_FORMAT_12L;
      break;
    case DAC_DATA_FORMAT_8R:
      mode |= DAC_DATA_FORMAT_8R;
      break;
    default:
      return (DAC_ERROR_DATA_FORMAT);
  }

  info->mode = mode;

  /* Enable DAC */
  switch (control & DAC_OUTPUT_CHANNEL_Msk) {
    case DAC_OUTPUT_CHANNEL_1:
      val = (dac_cr | DAC_CR_EN1);
      break;
    case DAC_OUTPUT_CHANNEL_2:
      val = ((dac_cr << 16U) | DAC_CR_EN2);
      break;
    case DAC_OUTPUT_CHANNEL_BOTH:
      val = (dac_cr | DAC_CR_EN1) | ((dac_cr << 16U) | DAC_CR_EN2);
      break;
    default:
      return (DAC_ERROR_OUTPUT_CHANNEL);
  }

  /* Configure registers */
  dac->reg->CR = val;

  info->state |= DAC_CONFIGURED;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          DAC_STATUS DAC_GetStatus(const DAC_RESOURCES *dac)
 * @brief       Get DAC status.
 * @return      DAC status \ref DAC_STATUS
 */
static
DAC_STATUS DAC_GetStatus(const DAC_RESOURCES *dac)
{
  DAC_STATUS status;

  status.busy = dac->info->status.busy;

  return status;
}

/* DAC1 */
#if defined(USE_DAC1)
static
int32_t DAC1_Initialize(DAC_SignalEvent_t cb_event)
{
  return DAC_Initialize(cb_event, &DAC1_Resources);
}

static
int32_t DAC1_Uninitialize(void)
{
  return DAC_Uninitialize(&DAC1_Resources);
}

static
int32_t DAC1_PowerControl(ARM_POWER_STATE state)
{
  return DAC_PowerControl(state, &DAC1_Resources);
}

static
int32_t DAC1_Convert(const void *data, uint32_t num)
{
  return DAC_Convert(data, num, &DAC1_Resources);
}

static
uint32_t DAC1_GetCount(void)
{
  return DAC_GetCount(&DAC1_Resources);
}

static
int32_t DAC1_Control(uint32_t control, uint32_t arg)
{
  return DAC_Control(control, arg, &DAC1_Resources);
}

static
DAC_STATUS DAC1_GetStatus(void)
{
  return DAC_GetStatus(&DAC1_Resources);
}

DRIVER_DAC Driver_DAC1 = {
  DACx_GetVersion,
  DACx_GetCapabilities,
  DAC1_Initialize,
  DAC1_Uninitialize,
  DAC1_PowerControl,
  DAC1_Convert,
  DAC1_GetCount,
  DAC1_Control,
  DAC1_GetStatus
};
#endif  /* USE_DAC1 */

#endif  /* USE_DAC1 */

/* ----------------------------- End of file ---------------------------------*/
