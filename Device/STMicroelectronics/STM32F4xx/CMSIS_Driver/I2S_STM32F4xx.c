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
 * Project: I2S Driver for STMicroelectronics STM32F4xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "I2S_STM32F4xx.h"

#if defined(USE_I2S2) || defined(USE_I2S3)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ARM_SAI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

#define I2S_MODE_MASTER_TX            (2U << SPI_I2SCFGR_I2SCFG_Pos)
#define I2S_MODE_MASTER_RX            (3U << SPI_I2SCFGR_I2SCFG_Pos)
#define I2S_MODE_SLAVE_TX             (0U << SPI_I2SCFGR_I2SCFG_Pos)
#define I2S_MODE_SLAVE_RX             (1U << SPI_I2SCFGR_I2SCFG_Pos)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

#ifdef I2S2_TX_DMA_Stream
static void I2S2_TX_DMA_Complete(uint32_t event);
#endif // I2S2_TX_DMA_Stream

#ifdef I2S2_RX_DMA_Stream
static void I2S2_RX_DMA_Complete(uint32_t event);
#endif // I2S2_RX_DMA_Stream

#ifdef I2S3_TX_DMA_Stream
static void I2S3_TX_DMA_Complete(uint32_t event);
#endif // I2S3_TX_DMA_Stream

#ifdef I2S3_RX_DMA_Stream
static void I2S3_RX_DMA_Complete(uint32_t event);
#endif // I2S3_RX_DMA_Stream

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_SAI_API_VERSION,
  ARM_SAI_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_SAI_CAPABILITIES DriverCapabilities = {
  1, /* supports asynchronous Transmit/Receive */
  0, /* supports synchronous Transmit/Receive */
  0, /* supports user defined Protocol */
  1, /* supports I2S Protocol */
  0, /* supports MSB/LSB justified Protocol */
  0, /* supports PCM short/long frame Protocol */
  0, /* supports AC'97 Protocol */
  0, /* supports Mono mode */
  0, /* supports Companding */
  1, /* supports MCLK (Master Clock) pin */
  0  /* supports Frame error event: \ref ARM_SAI_EVENT_FRAME_ERROR */
};

static const GPIO_PIN_CFG_t I2S_pin_cfg_af = {
    GPIO_MODE_AF_PP, GPIO_PULL_DISABLE, GPIO_SPEED_VERY_HIGH
};

static const GPIO_PIN_CFG_t I2S_pin_cfg_analog = {
    GPIO_MODE_ANALOG, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

static const I2S_FreqParam_t i2s_pll_param[] = {
  /* When the master clock is generated */
  { 8000, 256, 5},
  {16000, 213, 2},
  {22050, 429, 4},
  {32000, 213, 2},
  {44100, 271, 2},
  {48000, 258, 3},
  {96000, 344, 2},
};

#if defined(USE_I2S2)
/* SAI2 Information (Run-Time) */
static I2S_INFO I2S2_Info;

#ifdef I2S2_TX_DMA_Stream

static DMA_Handle_t I2S2_TX_DMA_Handle;
static const DMA_Resources_t I2S2_TX_DMA = {
  &I2S2_TX_DMA_Handle,
  I2S2_TX_DMA_Stream,
  I2S2_TX_DMA_Channel,
  I2S2_TX_DMA_Priority,
  I2S2_TX_DMA_Complete,
  RTE_I2S_DMA_INT_PRIORITY,
  I2S2_TX_DMA_IRQn,
};

#endif

#ifdef I2S2_RX_DMA_Stream

static DMA_Handle_t I2S2_RX_DMA_Handle;
static const DMA_Resources_t I2S2_RX_DMA = {
  &I2S2_RX_DMA_Handle,
  I2S2_RX_DMA_Stream,
  I2S2_RX_DMA_Channel,
  I2S2_RX_DMA_Priority,
  I2S2_RX_DMA_Complete,
  RTE_I2S_DMA_INT_PRIORITY,
  I2S2_RX_DMA_IRQn,
};

#endif

/* SAI2 Resources */
static I2S_RESOURCES I2S2_Resources = {
  SPI2,
  I2S2ext,
  {
    I2S2_MCLK_GPIO_PORT,
    I2S2_MCLK_GPIO_PIN,
    I2S2_MCLK_GPIO_FUNC,
    I2S2_BCLK_GPIO_PORT,
    I2S2_BCLK_GPIO_PIN,
    I2S2_BCLK_GPIO_FUNC,
    I2S2_WCLK_GPIO_PORT,
    I2S2_WCLK_GPIO_PIN,
    I2S2_WCLK_GPIO_FUNC,
    I2S2_DIN_GPIO_PORT,
    I2S2_DIN_GPIO_PIN,
    I2S2_DIN_GPIO_FUNC,
    I2S2_DOUT_GPIO_PORT,
    I2S2_DOUT_GPIO_PIN,
    I2S2_DOUT_GPIO_FUNC,
  },
#ifdef I2S2_TX_DMA_Stream
  &I2S2_TX_DMA,
#else
  NULL,
#endif
#ifdef I2S2_RX_DMA_Stream
  &I2S2_RX_DMA,
#else
  NULL,
#endif
  SPI2_IRQn,
  RCC_PERIPH_SPI2,
  &I2S2_Info,
};
#endif /* USE_I2S2 */

#if defined(USE_I2S3)
/* SAI3 Information (Run-Time) */
static I2S_INFO I2S3_Info;

#ifdef I2S3_TX_DMA_Stream

static DMA_Handle_t I2S3_TX_DMA_Handle;
static const DMA_Resources_t I2S3_TX_DMA = {
  &I2S3_TX_DMA_Handle,
  I2S3_TX_DMA_Stream,
  I2S3_TX_DMA_Channel,
  I2S3_TX_DMA_Priority,
  I2S3_TX_DMA_Complete,
  RTE_I2S_DMA_INT_PRIORITY,
  I2S3_TX_DMA_IRQn,
};

#endif

#ifdef I2S3_RX_DMA_Stream

static DMA_Handle_t I2S3_RX_DMA_Handle;
static const DMA_Resources_t I2S3_RX_DMA = {
  &I2S3_RX_DMA_Handle,
  I2S3_RX_DMA_Stream,
  I2S3_RX_DMA_Channel,
  I2S3_RX_DMA_Priority,
  I2S3_RX_DMA_Complete,
  RTE_I2S_DMA_INT_PRIORITY,
  I2S3_RX_DMA_IRQn,
};

#endif

/* SAI3 Resources */
static I2S_RESOURCES I2S3_Resources = {
  SPI3,
  I2S3ext,
  {
    I2S3_MCLK_GPIO_PORT,
    I2S3_MCLK_GPIO_PIN,
    I2S3_MCLK_GPIO_FUNC,
    I2S3_BCLK_GPIO_PORT,
    I2S3_BCLK_GPIO_PIN,
    I2S3_BCLK_GPIO_FUNC,
    I2S3_WCLK_GPIO_PORT,
    I2S3_WCLK_GPIO_PIN,
    I2S3_WCLK_GPIO_FUNC,
    I2S3_DIN_GPIO_PORT,
    I2S3_DIN_GPIO_PIN,
    I2S3_DIN_GPIO_FUNC,
    I2S3_DOUT_GPIO_PORT,
    I2S3_DOUT_GPIO_PIN,
    I2S3_DOUT_GPIO_FUNC,
  },
#ifdef I2S3_TX_DMA_Stream
  &I2S3_TX_DMA,
#else
  NULL,
#endif
#ifdef I2S3_RX_DMA_Stream
  &I2S3_RX_DMA,
#else
  NULL,
#endif
  SPI3_IRQn,
  RCC_PERIPH_SPI3,
  &I2S3_Info,
};
#endif /* USE_I2S3 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          ARM_DRIVER_VERSION SAIx_GetVersion(void)
 * @brief       Get driver version.
 * @return      \ref ARM_DRIVER_VERSION
 */
static
ARM_DRIVER_VERSION I2Sx_GetVersion(void)
{
  return DriverVersion;
}

/**
 * @fn          ARM_SAI_CAPABILITIES SAIx_GetCapabilities(void)
 * @brief       Get driver capabilities.
 * @return      \ref ARM_SAI_CAPABILITIES
 */
static
ARM_SAI_CAPABILITIES I2Sx_GetCapabilities(void)
{
  return DriverCapabilities;
}

/**
 * @fn          int32_t SAI_Initialize(ARM_SAI_SignalEvent_t cb_event, I2S_RESOURCES *i2s)
 * @brief       Initialize SAI Interface.
 * @param[in]   cb_event  Pointer to \ref ARM_SAI_SignalEvent
 * @param[in]   i2s       Pointer to SAI resources
 * @return      \ref execution_status
 */
static
int32_t I2S_Initialize(ARM_SAI_SignalEvent_t cb_event, I2S_RESOURCES *i2s)
{
  if (i2s->info->flags & I2S_FLAG_INITIALIZED)
    return ARM_DRIVER_OK;

  I2S_IO *io = &i2s->io;
  I2S_INFO *info = i2s->info;

  /* Configure MCLK Pin */
  GPIO_PortClock(io->mclk_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->mclk_port, io->mclk_pin, &I2S_pin_cfg_af);
  GPIO_AFConfig(io->mclk_port, io->mclk_pin, io->mclk_func);
  /* Configure BCLK Pin */
  GPIO_PortClock(io->bclk_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->bclk_port, io->bclk_pin, &I2S_pin_cfg_af);
  GPIO_AFConfig(io->bclk_port, io->bclk_pin, io->bclk_func);
  /* Configure WCLK Pin */
  GPIO_PortClock(io->wclk_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->wclk_port, io->wclk_pin, &I2S_pin_cfg_af);
  GPIO_AFConfig(io->wclk_port, io->wclk_pin, io->wclk_func);
  /* Configure DOUT Pin */
  GPIO_PortClock(io->dout_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->dout_port, io->dout_pin, &I2S_pin_cfg_af);
  GPIO_AFConfig(io->dout_port, io->dout_pin, io->dout_func);
  /* Configure DIN Pin */
  GPIO_PortClock(io->din_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->din_port, io->din_pin, &I2S_pin_cfg_af);
  GPIO_AFConfig(io->din_port, io->din_pin, io->din_func);

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2S_INFO));

  info->cb_event = cb_event;
  info->flags    = I2S_FLAG_INITIALIZED;

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t SAI_Uninitialize(I2S_RESOURCES *i2s)
 * @brief       De-initialize SAI Interface.
 * @param[in]   i2s   Pointer to SAI resources
 * @return      \ref execution_status
 */
static
int32_t I2S_Uninitialize(I2S_RESOURCES *i2s)
{
  I2S_IO *io = &i2s->io;

  /* Unconfigure MCLK Pin */
  GPIO_PinConfig(io->mclk_port, io->mclk_pin, &I2S_pin_cfg_analog);
  /* Unconfigure BCLK Pin */
  GPIO_PinConfig(io->bclk_port, io->bclk_pin, &I2S_pin_cfg_analog);
  /* Unconfigure WCLK Pin */
  GPIO_PinConfig(io->wclk_port, io->wclk_pin, &I2S_pin_cfg_analog);
  /* Unconfigure DOUT Pin */
  GPIO_PinConfig(io->dout_port, io->dout_pin, &I2S_pin_cfg_analog);
  /* Unconfigure DIN Pin */
  GPIO_PinConfig(io->din_port, io->din_pin, &I2S_pin_cfg_analog);

  i2s->info->flags = 0U;

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t SAI_PowerControl(ARM_POWER_STATE state, I2S_RESOURCES *i2s)
 * @brief       Control SAI Interface Power.
 * @param[in]   state   Power state
 * @param[in]   i2s     Pointer to SAI resources
 * @return      \ref execution_status
 */
static
int32_t I2S_PowerControl(ARM_POWER_STATE state, I2S_RESOURCES *i2s)
{
  I2S_INFO *info = i2s->info;
  SPI_TypeDef *reg = i2s->tx_reg;

  switch (state) {
    case ARM_POWER_OFF:
      /* Enable I2S clock */
      RCC_EnablePeriph(i2s->rcc);

      /* Disable I2S peripheral */
      reg->I2SCFGR = 0U;

      /* Disable I2S IRQ */
      NVIC_DisableIRQ(i2s->irq_num);

      /* Uninitialize DMA */
#ifdef I2S_TX_DMA
      if (i2s->tx_dma != NULL)
        DMA_Uninitialize(i2s->tx_dma);
#endif

#ifdef I2S_RX_DMA
      if (i2s->rx_dma != NULL)
        DMA_Uninitialize(i2s->rx_dma);
#endif

      /* Disable peripheral clock */
      RCC_DisablePeriph(i2s->rcc);

      info->status.tx_busy      = 0U;
      info->status.rx_busy      = 0U;
      info->status.tx_underflow = 0U;
      info->status.rx_overflow  = 0U;
      info->status.frame_error  = 0U;

      info->flags &= ~I2S_FLAG_POWERED;
      break;

    case ARM_POWER_FULL:
      if ((info->flags & I2S_FLAG_INITIALIZED) == 0U)
        return ARM_DRIVER_ERROR;

      if ((info->flags & I2S_FLAG_POWERED) != 0U)
        return ARM_DRIVER_OK;

      /* Enable the peripheral clock */
      RCC_EnablePeriph(i2s->rcc);

      /* Clear and Enable I2S IRQ */
      NVIC_ClearPendingIRQ(i2s->irq_num);
      NVIC_SetPriority(i2s->irq_num, RTE_I2S_INT_PRIORITY);
      NVIC_EnableIRQ(i2s->irq_num);

      /* Initialize DMA */
#ifdef I2S_TX_DMA
      if (i2s->tx_dma != NULL) {
        DMA_StreamConfig_t *cfg = &i2s->tx_dma->handle->config;

        cfg->Direction    = DMA_DIR_MEM_TO_PER;
        cfg->PerInc       = DMA_PINC_DISABLE;
        cfg->MemInc       = DMA_MINC_ENABLE;
        cfg->PerDataAlign = DMA_PDATAALIGN_HALFWORD;
        cfg->MemDataAlign = DMA_MDATAALIGN_HALFWORD;
        cfg->Mode         = DMA_MODE_NORMAL;
        cfg->FIFOMode     = DMA_FIFOMODE_DISABLE;
        cfg->MemBurst     = DMA_MBURST_SINGLE;
        cfg->PerBurst     = DMA_PBURST_SINGLE;


        DMA_Initialize(i2s->tx_dma);
      }
#endif

#ifdef I2S_RX_DMA
      if (i2s->rx_dma != NULL) {
        DMA_StreamConfig_t *cfg = &i2s->rx_dma->handle->config;

        cfg->Direction    = DMA_DIR_PER_TO_MEM;
        cfg->PerInc       = DMA_PINC_DISABLE;
        cfg->MemInc       = DMA_MINC_ENABLE;
        cfg->PerDataAlign = DMA_PDATAALIGN_HALFWORD;
        cfg->MemDataAlign = DMA_MDATAALIGN_HALFWORD;
        cfg->Mode         = DMA_MODE_NORMAL;
        cfg->FIFOMode     = DMA_FIFOMODE_DISABLE;
        cfg->MemBurst     = DMA_MBURST_SINGLE;
        cfg->PerBurst     = DMA_PBURST_SINGLE;

        DMA_Initialize(i2s->rx_dma);
      }
#endif

      /* Reset the peripheral */
      RCC_ResetPeriph(i2s->rcc);

      /* Enable interrupts */
      reg->CR2 |= SPI_CR2_ERRIE;

      /* Select I2S Mode */
      reg->I2SCFGR |= SPI_I2SCFGR_I2SMOD;

      /* Ready for operation */
      info->flags |= I2S_FLAG_POWERED;
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t SAI_Send(const void *data, uint32_t num, I2S_RESOURCES *i2s)
 * @brief       Start sending data to SAI transmitter.
 * @param[in]   data  Pointer to buffer with data to send to SAI transmitter
 * @param[in]   num   Number of data items to send
 * @param[in]   i2s   Pointer to SAI resources
 * @return      \ref execution_status
 */
static
int32_t I2S_Send(const void *data, uint32_t num, I2S_RESOURCES *i2s)
{
  I2S_INFO *info = i2s->info;
  SPI_TypeDef *reg = i2s->tx_reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((info->flags & I2S_FLAG_CONFIGURED) == 0U || (info->flags & I2S_FLAG_TX_ENABLE) == 0U) {
    /* I2S is not configured (mode not selected) */
    return ARM_DRIVER_ERROR;
  }

  if (info->status.tx_busy) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  info->status.tx_busy      = 1U;
  info->status.tx_underflow = 0U;
  info->status.frame_error  = 0U;

  info->tx.buf = (uint16_t *)data;
  info->tx.cnt = 0U;
  info->tx.num = num;

#ifdef I2S_TX_DMA
  /* DMA mode */
  if (i2s->tx_dma != NULL) {
    /* Initialize and start DMA Stream */
    DMA_StreamConfig(i2s->tx_dma);
    DMA_StreamEnable(i2s->tx_dma, (uint32_t)&reg->DR, (uint32_t)data, num);
    /* TX Buffer DMA enable */
    reg->CR2 |= SPI_CR2_TXDMAEN;
  }
  else
#endif
  /* Interrupt mode */
  {
    /* Enable TX buffer empty interrupt */
    reg->CR2 |= SPI_CR2_TXEIE;
  }

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t SAI_Receive(void *data, uint32_t num, I2S_RESOURCES *i2s)
 * @brief       Start receiving data from SAI receiver.
 * @param[out]  data  Pointer to buffer for data to receive from SAI receiver
 * @param[in]   num   Number of data items to receive
 * @param[in]   i2s   Pointer to SAI resources
 * @return      \ref execution_status
 */
static
int32_t I2S_Receive(void *data, uint32_t num, I2S_RESOURCES *i2s)
{
  I2S_INFO *info = i2s->info;
  SPI_TypeDef *reg = i2s->rx_reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((info->flags & I2S_FLAG_CONFIGURED) == 0U || (info->flags & I2S_FLAG_RX_ENABLE) == 0U) {
    /* I2S is not configured (mode not selected) */
    return ARM_DRIVER_ERROR;
  }

  if (info->status.rx_busy) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  info->status.rx_busy      = 1U;
  info->status.rx_overflow  = 0U;
  info->status.frame_error  = 0U;

  info->rx.buf = (uint16_t *)data;
  info->rx.cnt = 0U;
  info->rx.num = num;

#ifdef I2S_RX_DMA
  /* DMA mode */
  if (i2s->rx_dma != NULL) {
    /* Initialize and start DMA Stream */
    DMA_StreamConfig(i2s->rx_dma);
    DMA_StreamEnable(i2s->rx_dma, (uint32_t)&reg->DR, (uint32_t)data, num);
    /* RX Buffer DMA enable */
    reg->CR2 |= SPI_CR2_RXDMAEN;
  }
  else
#endif
  /* Interrupt mode */
  {
    /* Enable RX buffer not empty interrupt */
    reg->CR2 |= SPI_CR2_RXNEIE;
  }

  return ARM_DRIVER_OK;
}

/**
 * @fn          uint32_t SAI_GetTxCount(I2S_RESOURCES *i2s)
 * @brief       Get transmitted data count.
 * @param[in]   i2s  Pointer to SAI resources
 * @return      Number of data items transmitted
 */
static
uint32_t I2S_GetTxCount(I2S_RESOURCES *i2s)
{
  return i2s->info->tx.cnt;
}

/**
 * @fn          uint32_t SAI_GetRxCount(I2S_RESOURCES *i2s)
 * @brief       Get received data count.
 * @param[in]   i2s  Pointer to SAI resources
 * @return      Number of data items received
 */
static
uint32_t I2S_GetRxCount(I2S_RESOURCES *i2s)
{
  return i2s->info->rx.cnt;
}

/**
 * @fn          int32_t SAI_Control(uint32_t control, uint32_t arg1, uint32_t arg2, I2S_RESOURCES *i2s)
 * @brief       Control SAI Interface.
 * @param[in]   control  Operation
 * @param[in]   arg1     Argument 1 of operation (optional)
 * @param[in]   arg2     Argument 2 of operation (optional)
 * @param[in]   i2s      Pointer to SAI resources
 * @return      Common \ref execution_status and driver specific \ref sai_execution_status
 */
static
int32_t I2S_Control(uint32_t control, uint32_t arg1, uint32_t arg2, I2S_RESOURCES *i2s)
{
  uint32_t mode;
  uint32_t i2scfgr = 0x0800, i2spr = 0x0002;
  uint32_t data_len;

  if ((i2s->info->flags & I2S_FLAG_POWERED) == 0U) {
    /* SAI not powered */
    return ARM_DRIVER_ERROR;
  }

  switch (control & ARM_SAI_CONTROL_Msk) {
    case ARM_SAI_CONTROL_TX:
      if ((arg1 & 1U) == 0U) {
        /* Disable TX buffer empty interrupt */
        i2s->tx_reg->CR2 &= ~SPI_CR2_TXEIE;

        /* Clear flag */
        i2s->info->flags &= ~I2S_FLAG_TX_ENABLE;

#ifdef I2S_TX_DMA
        if (i2s->tx_dma) {
          if (i2s->info->status.tx_busy != 0U) {
            i2s->tx_reg->CR2 &= ~SPI_CR2_TXDMAEN;
            /* Disable DMA channel */
            DMA_StreamDisable(i2s->tx_dma);
          }
        }
#endif  // I2S_TX_DMA

        while ((i2s->tx_reg->SR & SPI_SR_TXE) == 0U);
        while ((i2s->tx_reg->SR & SPI_SR_BSY) != 0U);

        /* Disable I2S peripheral */
        i2s->tx_reg->I2SCFGR &= ~SPI_I2SCFGR_I2SE;
      }
      else {
        /* Reset counters */
        i2s->info->tx.cnt = 0U;
        i2s->info->tx.num = 0U;
        /* Clear busy flag */
        i2s->info->status.tx_busy = 0U;
        /* Enable I2S peripheral */
        i2s->tx_reg->I2SCFGR |= SPI_I2SCFGR_I2SE;
        /* Set flag */
        i2s->info->flags |= I2S_FLAG_TX_ENABLE;
        /* Enable TX buffer empty interrupt */
        i2s->tx_reg->CR2 |= SPI_CR2_TXEIE;
      }
      return ARM_DRIVER_OK;

    case ARM_SAI_CONTROL_RX:
      if ((arg1 & 1U) == 0U) {
        /* Disable Receive Interrupt */
        i2s->rx_reg->CR2 &= ~SPI_CR2_RXNEIE;
        /* Disable I2S ext peripheral */
        i2s->rx_reg->I2SCFGR &= ~SPI_I2SCFGR_I2SE;
      }
      else {
        /* Reset counters */
        i2s->info->rx.cnt = 0U;
        i2s->info->rx.num = 0U;
        /* Clear busy flag */
        i2s->info->status.rx_busy = 0U;
        /* Enable I2S ext peripheral */
        i2s->rx_reg->I2SCFGR |= SPI_I2SCFGR_I2SE;
        /* Set flag */
        i2s->info->flags |= I2S_FLAG_RX_ENABLE;
        /* Enable Receive Interrupt */
        i2s->rx_reg->CR2 |= SPI_CR2_RXNEIE;
      }
      return ARM_DRIVER_OK;

    case ARM_SAI_CONFIGURE_TX:
      mode = ARM_SAI_CONFIGURE_TX;
      i2scfgr |= I2S_MODE_SLAVE_TX;
      break;

    case ARM_SAI_CONFIGURE_RX:
      mode = ARM_SAI_CONFIGURE_RX;
      i2scfgr |= I2S_MODE_SLAVE_RX;
      break;

    case ARM_SAI_MASK_SLOTS_TX:
      return ARM_DRIVER_ERROR;

    case ARM_SAI_MASK_SLOTS_RX:
      return ARM_DRIVER_ERROR;

    case ARM_SAI_ABORT_SEND:
      /* Disable TX interrupt */
      i2s->tx_reg->CR2 &= ~SPI_CR2_TXEIE;

#ifdef I2S_TX_DMA
      if (i2s->tx_dma) {
        if (i2s->info->status.tx_busy != 0U) {
          /* Disable DMA channel */
          DMA_StreamDisable(i2s->tx_dma);
        }
      }
#endif  // I2S_TX_DMA

      /* Reset counters */
      i2s->info->tx.cnt = 0U;
      i2s->info->tx.num = 0U;

      /* Clear busy flag */
      i2s->info->status.tx_busy = 0U;

      if (i2s->tx_reg->I2SCFGR & SPI_I2SCFGR_I2SE) {
        /* Transmitter is enabled */
        /* Enable TX interrupt, to detect TX overflow */
        i2s->tx_reg->CR2 |= SPI_CR2_TXEIE;
      }
      return ARM_DRIVER_OK;

    case ARM_SAI_ABORT_RECEIVE:
      /* Disable RX interrupt */
      i2s->tx_reg->CR2 &= ~SPI_CR2_RXNEIE;

#ifdef I2S_RX_DMA
      if (i2s->rx_dma) {
        if (i2s->info->status.rx_busy != 0U) {
          /* Disable DMA channel */
          DMA_StreamDisable(i2s->rx_dma);
        }
      }
#endif  // I2S_RX_DMA

      /* Reset counters */
      i2s->info->rx.cnt = 0U;
      i2s->info->rx.num = 0U;

      // Clear busy flag
      i2s->info->status.rx_busy = 0U;

      if (i2s->rx_reg->I2SCFGR & SPI_I2SCFGR_I2SE) {
        /* Receiver is enabled */
        /* Enable RX interrupt, to detect RX overflow */
        i2s->tx_reg->CR2 |= SPI_CR2_RXNEIE;
      }
      return ARM_DRIVER_OK;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  data_len = ((control & ARM_SAI_DATA_SIZE_Msk) >> ARM_SAI_DATA_SIZE_Pos) + 1;

  if ((control & ARM_SAI_MODE_Msk) == ARM_SAI_MODE_MASTER) {

    if (mode == ARM_SAI_CONFIGURE_RX)
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    i2scfgr |= I2S_MODE_MASTER_TX;

    /* Configure I2S PLL */
    int idx, freq_idx = -1;
    uint32_t pres_div = 2U, pres_odd = 0U, length = 1U, i2sclk, tmp;

    for (idx = 0; idx < sizeof(i2s_pll_param)/sizeof(i2s_pll_param[0]); ++idx) {
      if (i2s_pll_param[idx].freq == arg2) {
        freq_idx = idx;
        break;
      }
    }

    if (freq_idx == -1)
      return ARM_SAI_ERROR_AUDIO_FREQ;

    i2sclk = RCC_I2SPLL_Config(i2s_pll_param[freq_idx].plln, i2s_pll_param[freq_idx].pllr);

    /* Configure I2S prescaler */
    if (data_len != 16U)
      length = 2U;

    switch (control & ARM_SAI_MCLK_PIN_Msk) {
      case ARM_SAI_MCLK_PIN_INACTIVE:
        tmp = (i2sclk / (32U * length) * 10U / arg2 + 5U);
        break;

      case ARM_SAI_MCLK_PIN_OUTPUT:
        i2spr = SPI_I2SPR_MCKOE;
        tmp = (i2sclk / 256U * 10U / arg2 + 5U);
        break;

      default:
        return ARM_SAI_ERROR_MCLK_PIN;
    }

    tmp /= 10U;
    pres_odd = (tmp & 1U);
    pres_div = (tmp - pres_odd) / 2U;

    if ((pres_div < 2U) || (pres_div > 255U))
      return ARM_SAI_ERROR_AUDIO_FREQ;

    i2spr |= ((pres_div << SPI_I2SPR_I2SDIV_Pos) | (pres_odd << SPI_I2SPR_ODD_Pos));
  }

  /* Configure I2S Protocol */
  switch (control & ARM_SAI_PROTOCOL_Msk) {
    case ARM_SAI_PROTOCOL_I2S:
      break;

    case ARM_SAI_PROTOCOL_MSB_JUSTIFIED:
      i2scfgr |= (1U << SPI_I2SCFGR_I2SSTD_Pos);
      break;

    case ARM_SAI_PROTOCOL_LSB_JUSTIFIED:
      i2scfgr |= (2U << SPI_I2SCFGR_I2SSTD_Pos);
      break;

    case ARM_SAI_PROTOCOL_PCM_SHORT:
      i2scfgr |= (3U << SPI_I2SCFGR_I2SSTD_Pos);
      break;

    case ARM_SAI_PROTOCOL_PCM_LONG:
      i2scfgr |= ((3U << SPI_I2SCFGR_I2SSTD_Pos) | SPI_I2SCFGR_PCMSYNC);
      break;

    default:
      return ARM_SAI_ERROR_PROTOCOL;
  }

  /* Configure Data length */
  switch (data_len) {
    case 16U:
      break;

    case 24U:
      i2scfgr |= (1U << SPI_I2SCFGR_DATLEN_Pos);
      break;

    case 32U:
      i2scfgr |= (2U << SPI_I2SCFGR_DATLEN_Pos);
      break;

    default:
      return ARM_SAI_ERROR_DATA_SIZE;
  }

  if (mode == ARM_SAI_CONFIGURE_TX) {
    i2s->info->tx.data_bits = data_len;
    /* Configure I2S configuration register */
    i2s->tx_reg->I2SCFGR = i2scfgr;
    /* Configure I2S prescaler register */
    i2s->tx_reg->I2SPR = i2spr;
  }
  else {
    i2s->info->rx.data_bits = data_len;
    i2s->rx_reg->I2SCFGR = i2scfgr;
  }

  i2s->info->flags |= I2S_FLAG_CONFIGURED;

  return ARM_DRIVER_OK;
}

/**
 * @fn          ARM_SAI_STATUS SAI_GetStatus(I2S_RESOURCES *i2s)
 * @brief       Get SAI status.
 * @param[in]   i2s  Pointer to SAI resources
 * @return      SAI status \ref ARM_SAI_STATUS
 */
static
ARM_SAI_STATUS I2S_GetStatus(I2S_RESOURCES *i2s)
{
  ARM_SAI_STATUS status;

  status.frame_error  = i2s->info->status.frame_error;
  status.rx_busy      = i2s->info->status.rx_busy;
  status.rx_overflow  = i2s->info->status.rx_overflow;
  status.tx_busy      = i2s->info->status.tx_busy;
  status.tx_underflow = i2s->info->status.tx_underflow;

  return status;
}

/**
 * @fn          void I2S_IRQHandler(I2S_RESOURCES *i2s)
 * @brief       I2S Interrupt handler.
 * @param[in]   i2s  Pointer to SAI resources
 */
void I2S_IRQHandler(I2S_RESOURCES *i2s)
{
  I2S_INFO *info = i2s->info;
  uint32_t event = 0U;

  /* RX interrupt */
  if (info->flags & I2S_FLAG_RX_ENABLE) {
    SPI_TypeDef *reg = i2s->rx_reg;
    I2S_TRANSFER_INFO *rx = &i2s->info->rx;

    if (rx->num == 0U) {
      /* Set RX overflow event and flag */
      info->status.rx_overflow = 1U;
      event |= ARM_SAI_EVENT_RX_OVERFLOW;

      /* Disable RX Interrupt */
      reg->CR2 &= ~SPI_CR2_RXNEIE;
    }
    else if (reg->SR & SPI_SR_RXNE) {
      *rx->buf++ = reg->DR;

      if (++rx->cnt == rx->num) {
        /* Clear busy flag */
        info->status.rx_busy = 0U;
        rx->num = 0U;
        event |= ARM_SAI_EVENT_RECEIVE_COMPLETE;
      }
    }
  }

  /* TX interrupt */
  if (info->flags & I2S_FLAG_TX_ENABLE) {
    SPI_TypeDef *reg = i2s->tx_reg;
    I2S_TRANSFER_INFO *tx = &i2s->info->tx;

    if (tx->num == 0U) {
      /* Set TX underflow event and flag */
      info->status.tx_underflow = 1U;
      event |= ARM_SAI_EVENT_TX_UNDERFLOW;

      /* Disable TX Buffer Empty Interrupt */
      reg->CR2 &= ~SPI_CR2_TXEIE;
    }
    else if (reg->SR & SPI_SR_TXE) {
      reg->DR = *tx->buf++;

      if (++tx->cnt == tx->num) {
        /* Clear busy flag */
        info->status.tx_busy = 0U;
        tx->num = 0U;
        event |= ARM_SAI_EVENT_SEND_COMPLETE;
      }
    }
  }

  if ((event != 0U) && (info->cb_event != NULL)) {
    info->cb_event(event);
  }
}

#ifdef I2S_TX_DMA
static
void I2S_TX_DMA_Complete(uint32_t event, I2S_RESOURCES *i2s)
{
  I2S_INFO *info = i2s->info;

  if (event & (DMA_EVENT_TRANSFER_COMPLETE | DMA_EVENT_TRANSFER_ABORT)) {
    info->tx.cnt = info->tx.num;
    info->status.tx_busy = 0U;

    /* Clear TX num and enable TX interrupt to detect TX underflow */
    info->tx.num = 0U;

    if ((info->cb_event != NULL) && (event & DMA_EVENT_TRANSFER_COMPLETE))
      info->cb_event(ARM_SAI_EVENT_SEND_COMPLETE);
  }
}
#endif  // I2S_TX_DMA

#ifdef I2S_RX_DMA
static
void I2S_RX_DMA_Complete(uint32_t event, I2S_RESOURCES *i2s)
{
  I2S_INFO *info = i2s->info;

  if (event & (DMA_EVENT_TRANSFER_COMPLETE | DMA_EVENT_TRANSFER_ABORT)) {
    info->rx.cnt = info->rx.num;
    info->status.rx_busy = 0U;

    /* Clear RX num and enable RX interrupt to detect RX overflow */
    info->rx.num = 0U;

    if ((info->cb_event != NULL) && (event & DMA_EVENT_TRANSFER_COMPLETE))
      info->cb_event(ARM_SAI_EVENT_RECEIVE_COMPLETE);
  }
}
#endif  // I2S_RX_DMA

#if defined(USE_I2S2)
/* I2S2 Driver wrapper functions */

static
int32_t I2S2_Initialize(ARM_SAI_SignalEvent_t cb_event)
{
  return I2S_Initialize(cb_event, &I2S2_Resources);
}

static
int32_t I2S2_Uninitialize(void)
{
  return I2S_Uninitialize(&I2S2_Resources);
}

static
int32_t I2S2_PowerControl(ARM_POWER_STATE state)
{
  return I2S_PowerControl(state, &I2S2_Resources);
}

static
int32_t I2S2_Send(const void *data, uint32_t num)
{
  return I2S_Send(data, num, &I2S2_Resources);
}

static
int32_t I2S2_Receive(void *data, uint32_t num)
{
  return I2S_Receive(data, num, &I2S2_Resources);
}

static
uint32_t I2S2_GetTxCount(void)
{
  return I2S_GetTxCount(&I2S2_Resources);
}

static
uint32_t I2S2_GetRxCount(void)
{
  return I2S_GetRxCount(&I2S2_Resources);
}

static
int32_t I2S2_Control(uint32_t control, uint32_t arg1, uint32_t arg2)
{
  return I2S_Control(control, arg1, arg2, &I2S2_Resources);
}

static
ARM_SAI_STATUS I2S2_GetStatus(void)
{
  return I2S_GetStatus(&I2S2_Resources);
}

void SPI2_IRQHandler(void)
{
  I2S_IRQHandler(&I2S2_Resources);
}

#ifdef I2S2_TX_DMA_Stream
void I2S2_TX_DMA_Handler(void)
{
  DMA_IRQ_Handle(&I2S2_TX_DMA);
}

void I2S2_TX_DMA_Complete(uint32_t event)
{
  I2S_TX_DMA_Complete(event, &I2S2_Resources);
}
#endif // I2S2_TX_DMA_Stream

#ifdef I2S2_RX_DMA_Stream
void I2S2_RX_DMA_Handler(void)
{
  DMA_IRQ_Handle(&I2S2_RX_DMA);
}

void I2S2_RX_DMA_Complete(uint32_t event)
{
  I2S_RX_DMA_Complete(event, &I2S2_Resources);
}
#endif // I2S2_RX_DMA_Stream

#endif  /* USE_I2S2 */

#if defined(USE_I2S3)
/* I2S3 Driver wrapper functions */

static
int32_t I2S3_Initialize(ARM_SAI_SignalEvent_t cb_event)
{
  return I2S_Initialize(cb_event, &I2S3_Resources);
}

static
int32_t I2S3_Uninitialize(void)
{
  return I2S_Uninitialize(&I2S3_Resources);
}

static
int32_t I2S3_PowerControl(ARM_POWER_STATE state)
{
  return I2S_PowerControl(state, &I2S3_Resources);
}

static
int32_t I2S3_Send(const void *data, uint32_t num)
{
  return I2S_Send(data, num, &I2S3_Resources);
}

static
int32_t I2S3_Receive(void *data, uint32_t num)
{
  return I2S_Receive(data, num, &I2S3_Resources);
}

static
uint32_t I2S3_GetTxCount(void)
{
  return I2S_GetTxCount(&I2S3_Resources);
}

static
uint32_t I2S3_GetRxCount(void)
{
  return I2S_GetRxCount(&I2S3_Resources);
}

static
int32_t I2S3_Control(uint32_t control, uint32_t arg1, uint32_t arg2)
{
  return I2S_Control(control, arg1, arg2, &I2S3_Resources);
}

static
ARM_SAI_STATUS I2S3_GetStatus(void)
{
  return I2S_GetStatus(&I2S3_Resources);
}

void SPI3_IRQHandler(void)
{
  I2S_IRQHandler(&I2S3_Resources);
}

#ifdef I2S3_TX_DMA_Stream
void I2S3_TX_DMA_Handler(void)
{
  DMA_IRQ_Handle(&I2S3_TX_DMA);
}

static
void I2S3_TX_DMA_Complete(uint32_t event)
{
  I2S_TX_DMA_Complete(event, &I2S3_Resources);
}
#endif // I2S3_TX_DMA_Stream

#ifdef I2S3_RX_DMA_Stream
void I2S3_RX_DMA_Handler(void)
{
  DMA_IRQ_Handle(&I2S3_RX_DMA);
}

void I2S3_RX_DMA_Complete(uint32_t event)
{
  I2S_RX_DMA_Complete(event, &I2S3_Resources);
}
#endif // I2S3_RX_DMA_Stream

#endif  /* USE_I2S3 */

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_I2S2)

ARM_DRIVER_SAI Driver_SAI2 = {
  I2Sx_GetVersion,
  I2Sx_GetCapabilities,
  I2S2_Initialize,
  I2S2_Uninitialize,
  I2S2_PowerControl,
  I2S2_Send,
  I2S2_Receive,
  I2S2_GetTxCount,
  I2S2_GetRxCount,
  I2S2_Control,
  I2S2_GetStatus
};

#endif  /* USE_I2S2 */

#if defined(USE_I2S3)

ARM_DRIVER_SAI Driver_SAI3 = {
  I2Sx_GetVersion,
  I2Sx_GetCapabilities,
  I2S3_Initialize,
  I2S3_Uninitialize,
  I2S3_PowerControl,
  I2S3_Send,
  I2S3_Receive,
  I2S3_GetTxCount,
  I2S3_GetRxCount,
  I2S3_Control,
  I2S3_GetStatus
};

#endif  /* USE_I2S3 */

#endif /* defined(USE_I2S2) || defined(USE_I2S3) */

/* ----------------------------- End of file ---------------------------------*/
