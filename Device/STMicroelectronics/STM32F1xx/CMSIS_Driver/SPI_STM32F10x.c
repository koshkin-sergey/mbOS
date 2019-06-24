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
 * Project: SPI Driver for STMicroelectronics STM32F1xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "SPI_STM32F10x.h"

#if defined(USE_SPI1) || defined(USE_SPI2) || defined(USE_SPI3)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ARM_SPI_DRV_VERSION   ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

// Driver Version
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_SPI_API_VERSION,
    ARM_SPI_DRV_VERSION
};

// Driver Capabilities
static const
ARM_SPI_CAPABILITIES DriverCapabilities = {
    0,  /* Simplex Mode (Master and Slave) */
    0,  /* TI Synchronous Serial Interface */
    0,  /* Microwire Interface */
    1   /* Signal Mode Fault event: \ref ARM_SPI_EVENT_MODE_FAULT */
};

static const GPIO_PIN_CFG_t SPI_pin_cfg_af = {
    GPIO_MODE_AF_PP, GPIO_PULL_DISABLE, GPIO_SPEED_HIGH
};

static const GPIO_PIN_CFG_t SPI_pin_cfg_analog = {
    GPIO_MODE_ANALOG, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

static const GPIO_PIN_CFG_t SPI_pin_cfg_out_pp = {
    GPIO_MODE_OUT_PP, GPIO_PULL_DISABLE, GPIO_SPEED_MEDIUM
};

#if defined(USE_SPI1)

/* SPI1 Run-Time Information */
static SPI_INFO          SPI1_Info         = { 0U };
static SPI_TRANSFER_INFO SPI1_TransferInfo = { 0U };

#ifdef USE_SPI1_MOSI_Pin
  static SPI_PIN SPI1_mosi = {SPI1_MOSI_GPIOx, SPI1_MOSI_GPIO_Pin};
#endif
#ifdef USE_SPI1_MISO_Pin
  static SPI_PIN SPI1_miso = {SPI1_MISO_GPIOx, SPI1_MISO_GPIO_Pin};
#endif
#ifdef USE_SPI1_NSS_Pin
  static SPI_PIN SPI1_nss  = {SPI1_NSS_GPIOx,  SPI1_NSS_GPIO_Pin};
#endif
  static SPI_PIN SPI1_sck  = {SPI1_SCK_GPIOx,  SPI1_SCK_GPIO_Pin};


#ifdef SPI1_RX_DMA_Instance
static SPI_DMA SPI1_DMA_Rx = {
  SPI1_RX_DMA_Instance,
  SPI1_RX_DMA_Channel,
  SPI1_RX_DMA_Priority,
  SPI1_RX_DMA_IRQn
};
#endif

#ifdef SPI1_TX_DMA_Instance
static SPI_DMA SPI1_DMA_Tx = {
  SPI1_TX_DMA_Instance,
  SPI1_TX_DMA_Channel,
  SPI1_TX_DMA_Priority,
  SPI1_TX_DMA_IRQn
};
#endif

/* SPI1 Resources */
static const SPI_RESOURCES SPI1_Resources = {
  SPI1,
  RCC_PERIPH_SPI1,
  // PINS
  {
#ifdef USE_SPI1_MOSI_Pin
    &SPI1_mosi,
#else
    NULL,
#endif
#ifdef USE_SPI1_MISO_Pin
    &SPI1_miso,
#else
    NULL,
#endif
#ifdef USE_SPI1_NSS_Pin
    &SPI1_nss,
#else
    NULL,
#endif
    &SPI1_sck,
    SPI1_REMAP_DEF,
    SPI1_REMAP
  },
  SPI1_IRQn,
#ifdef SPI1_RX_DMA_Instance
  &SPI1_DMA_Rx,
#else
  NULL,
#endif
#ifdef SPI1_TX_DMA_Instance
  &SPI1_DMA_Tx,
#else
  NULL,
#endif
  &SPI1_Info,
  &SPI1_TransferInfo
};
#endif /* USE_SPI1 */

#if defined(USE_SPI2)

/* SPI2 Run-Time Information */
static SPI_INFO          SPI2_Info         = { 0U };
static SPI_TRANSFER_INFO SPI2_TransferInfo = { 0U };


#ifdef USE_SPI2_MOSI_Pin
  static SPI_PIN SPI2_mosi = {SPI2_MOSI_GPIOx, SPI2_MOSI_GPIO_Pin};
#endif
#ifdef USE_SPI2_MISO_Pin
  static SPI_PIN SPI2_miso = {SPI2_MISO_GPIOx, SPI2_MISO_GPIO_Pin};
#endif
#ifdef USE_SPI2_NSS_Pin
  static SPI_PIN SPI2_nss  = {SPI2_NSS_GPIOx,  SPI2_NSS_GPIO_Pin};
#endif
  static SPI_PIN SPI2_sck  = {SPI2_SCK_GPIOx,  SPI2_SCK_GPIO_Pin};

#ifdef SPI2_RX_DMA_Instance
static SPI_DMA SPI2_DMA_Rx = {
  SPI2_RX_DMA_Instance,
  SPI2_RX_DMA_Channel,
  SPI2_RX_DMA_Priority,
  SPI2_RX_DMA_IRQn
};
#endif

#ifdef SPI2_TX_DMA_Instance
static SPI_DMA SPI2_DMA_Tx = {
  SPI2_TX_DMA_Instance,
  SPI2_TX_DMA_Channel,
  SPI2_TX_DMA_Priority,
  SPI2_TX_DMA_IRQn
};
#endif

/* SPI2 Resources */
static const SPI_RESOURCES SPI2_Resources = {
  SPI2,
  RCC_PERIPH_SPI2,
  // PINS
  {
#ifdef USE_SPI2_MOSI_Pin
    &SPI2_mosi,
#else
    NULL,
#endif
#ifdef USE_SPI2_MISO_Pin
    &SPI2_miso,
#else
    NULL,
#endif
#ifdef USE_SPI2_NSS_Pin
    &SPI2_nss,
#else
    NULL,
#endif
    &SPI2_sck,
    SPI2_REMAP_DEF,
    SPI2_REMAP
  },
  SPI2_IRQn,
#ifdef SPI2_RX_DMA_Instance
  &SPI2_DMA_Rx,
#else
  NULL,
#endif
#ifdef SPI2_TX_DMA_Instance
  &SPI2_DMA_Tx,
#else
  NULL,
#endif
  &SPI2_Info,
  &SPI2_TransferInfo
};
#endif /* USE_SPI2 */

#if defined(USE_SPI3)

/* SPI3 Run-Time Information */
static SPI_INFO          SPI3_Info         = { 0U };
static SPI_TRANSFER_INFO SPI3_TransferInfo = { 0U };


#ifdef USE_SPI3_MOSI_Pin
  static SPI_PIN SPI3_mosi = {SPI3_MOSI_GPIOx, SPI3_MOSI_GPIO_Pin};
#endif
#ifdef USE_SPI3_MISO_Pin
  static SPI_PIN SPI3_miso = {SPI3_MISO_GPIOx, SPI3_MISO_GPIO_Pin};
#endif
#ifdef USE_SPI3_NSS_Pin
  static SPI_PIN SPI3_nss  = {SPI3_NSS_GPIOx,  SPI3_NSS_GPIO_Pin};
#endif
  static SPI_PIN SPI3_sck  = {SPI3_SCK_GPIOx,  SPI3_SCK_GPIO_Pin};

#ifdef SPI3_RX_DMA_Instance
static SPI_DMA SPI3_DMA_Rx = {
  SPI3_RX_DMA_Instance,
  SPI3_RX_DMA_Channel,
  SPI3_RX_DMA_Priority,
  SPI3_RX_DMA_IRQn
};
#endif
#ifdef SPI3_TX_DMA_Instance
static SPI_DMA SPI3_DMA_Tx = {
  SPI3_TX_DMA_Instance,
  SPI3_TX_DMA_Channel,
  SPI3_TX_DMA_Priority,
  SPI3_TX_DMA_IRQn
  };
#endif

/* SPI3 Resources */
static const SPI_RESOURCES SPI3_Resources = {
  SPI3,
  RCC_PERIPH_SPI3,
  // PINS
  {
#ifdef USE_SPI3_MOSI_Pin
    &SPI3_mosi,
#else
    NULL,
#endif
#ifdef USE_SPI3_MISO_Pin
    &SPI3_miso,
#else
    NULL,
#endif
#ifdef USE_SPI3_NSS_Pin
    &SPI3_nss,
#else
    NULL,
#endif
    &SPI3_sck,
    SPI3_REMAP_DEF,
    SPI3_REMAP
  },
  SPI3_IRQn,
#ifdef SPI3_RX_DMA_Instance
  &SPI3_DMA_Rx,
#else
  NULL,
#endif
#ifdef SPI3_TX_DMA_Instance
  &SPI3_DMA_Tx,
#else
  NULL,
#endif
  &SPI3_Info,
  &SPI3_TransferInfo
};
#endif /* USE_SPI3 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          void PinConfig(const SPI_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
 * @brief       Configure Pin
 * @param[in]   io       Pointer to SPI_PIN
 * @param[in]   pin_cfg  Pointer to GPIO_PIN_CFG_t
 */
static
void PinConfig(const SPI_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
{
  if ((io == NULL) || (pin_cfg == NULL))
    return;

  if (GPIO_GetPortClockState(io->port) == GPIO_PORT_CLK_DISABLE)
    GPIO_PortClock(io->port, GPIO_PORT_CLK_ENABLE);

  GPIO_PinConfig(io->port, io->pin, pin_cfg);
}

/**
 *
 * @return
 */
int32_t CalcPrescalerValue(const SPI_RESOURCES *spi, uint32_t freq)
{
  int32_t val;

  uint32_t pclk = RCC_GetPeriphFreq(spi->periph);
  for (val = 0; val < 8; val++) {
    if (freq >= (pclk >> (val + 1)))
      break;
  }

  if ((val == 8) || (freq < (pclk >> (val + 1)))) {
    // Requested Bus Speed can not be configured
    val = -1;
  }

  return (val);
}

/**
 * @fn          ARM_DRIVER_VERSION SPIx_GetVersion(void)
 * @brief       Get SPI driver version.
 * @return      \ref ARM_DRV_VERSION
 */
static
ARM_DRIVER_VERSION SPIx_GetVersion(void)
{
  return DriverVersion;
}

/**
 * @fn          ARM_SPI_CAPABILITIES SPIx_GetCapabilities(void)
 * @brief       Get driver capabilities.
 * @return      \ref ARM_SPI_CAPABILITIES
 */
static
ARM_SPI_CAPABILITIES SPIx_GetCapabilities(void)
{
  return DriverCapabilities;
}

/**
 * @fn          int32_t SPI_Initialize(ARM_SPI_SignalEvent_t cb_event, const SPI_RESOURCES *spi)
 * @brief       Initialize SPI Interface.
 * @param[in]   cb_event  Pointer to \ref ARM_SPI_SignalEvent
 * @param[in]   spi       Pointer to SPI resources
 * @return      \ref execution_status
 */
static
int32_t SPI_Initialize(ARM_SPI_SignalEvent_t cb_event, const SPI_RESOURCES *spi)
{
  SPI_INFO *info = spi->info;

  if (info->state & SPI_INITIALIZED)
    return ARM_DRIVER_OK;

  /* Initialize SPI Run-Time Resources */
  info->cb_event          = cb_event;
  info->status.busy       = 0U;
  info->status.data_lost  = 0U;
  info->status.mode_fault = 0U;

  /* Clear transfer information */
  memset(spi->xfer, 0, sizeof(SPI_TRANSFER_INFO));

  /* Setup pin remap */
  GPIO_AFConfig(spi->io.afio);

  SPI_IO *io = &spi->io;
  const GPIO_PIN_CFG_t *pin_cfg = &SPI_pin_cfg_af;

  /* Configure MISO Pin */
  PinConfig(io->miso, pin_cfg);
  /* Configure MOSI Pin */
  PinConfig(io->mosi, pin_cfg);
  /* Configure SCK Pin */
  PinConfig(io->sck, pin_cfg);

#ifdef __SPI_DMA
  DMA_ChannelInitialize((DMA_INFO *)spi->rx_dma);
  DMA_ChannelInitialize((DMA_INFO *)spi->tx_dma);
#endif

  info->state = SPI_INITIALIZED;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t SPI_Uninitialize(const SPI_RESOURCES *spi)
 * @brief       De-initialize SPI Interface.
 * @param[in]   spi  Pointer to SPI resources
 * @return      \ref execution_status
 */
static
int32_t SPI_Uninitialize(const SPI_RESOURCES *spi)
{
  SPI_IO *io = &spi->io;
  const GPIO_PIN_CFG_t *pin_cfg = &SPI_pin_cfg_analog;

  /* Unconfigure MISO Pin */
  PinConfig(io->miso, pin_cfg);
  /* Unconfigure MOSI Pin */
  PinConfig(io->mosi, pin_cfg);
  /* Unconfigure SCK Pin */
  PinConfig(io->sck, pin_cfg);
  /* Unconfigure NSS Pin */
  PinConfig(io->nss, pin_cfg);

  /* Uncofigure pin remapping */
  GPIO_AFConfig(spi->io.afio_def);

#ifdef __SPI_DMA
  DMA_ChannelUninitialize((DMA_INFO *)spi->rx_dma);
  DMA_ChannelUninitialize((DMA_INFO *)spi->tx_dma);
#endif

  /* Clear SPI state */
  spi->info->state = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t SPI_PowerControl(ARM_POWER_STATE state, const SPI_RESOURCES *spi)
 * @brief       Control SPI Interface Power.
 * @param[in]   state  Power state
 * @param[in]   spi    Pointer to SPI resources
 * @return      \ref execution_status
 */
static
int32_t SPI_PowerControl(ARM_POWER_STATE state, const SPI_RESOURCES *spi)
{
  SPI_INFO *info = spi->info;

  switch (state) {
    case ARM_POWER_OFF:
      /* SPI peripheral reset */
      RCC_ResetPeriph(spi->periph);
      /* Disable SPI IRQ */
      NVIC_DisableIRQ(spi->irq_num);

      /* Disable SPI clock */
      RCC_DisablePeriph(spi->periph);

      /* Clear status flags */
      info->status.busy       = 0U;
      info->status.data_lost  = 0U;
      info->status.mode_fault = 0U;

      /* Clear powered flag */
      info->state &= ~SPI_POWERED;
      break;

    case ARM_POWER_FULL:
      if ((info->state & SPI_INITIALIZED) == 0U)
        return (ARM_DRIVER_ERROR);

      if ((info->state & SPI_POWERED) != 0U)
        return (ARM_DRIVER_OK);

      /* Clear status flags */
      info->status.busy       = 0U;
      info->status.data_lost  = 0U;
      info->status.mode_fault = 0U;

      spi->xfer->def_val      = 0U;

      /* Ready for operation - set powered flag */
      info->state |= SPI_POWERED;

      /* Enable SPI clock */
      RCC_EnablePeriph(spi->periph);

      /* SPI peripheral reset */
      RCC_ResetPeriph(spi->periph);

      /* Clear and Enable SPI IRQ */
      NVIC_ClearPendingIRQ(spi->irq_num);
      NVIC_SetPriority(spi->irq_num, RTE_SPI_INT_PRIORITY);
      NVIC_EnableIRQ(spi->irq_num);
      break;

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t SPI_Send(const void *data, uint32_t num, const SPI_RESOURCES *spi)
 * @brief       Start sending data to SPI transmitter.
 * @param[in]   data  Pointer to buffer with data to send to SPI transmitter
 * @param[in]   num   Number of data items to send
 * @param[in]   spi   Pointer to SPI resources
 * @return      \ref execution_status
 */
static
int32_t SPI_Send(const void *data, uint32_t num, const SPI_RESOURCES *spi)
{
  SPI_INFO *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_TypeDef *reg = spi->reg;
  uint32_t cr1, cr2;
  uint32_t value;
#ifdef __SPI_DMA
  uint32_t cfg;
#endif

  if ((data == NULL) || (num == 0U))
    return (ARM_DRIVER_ERROR_PARAMETER);

  if ((info->state & SPI_CONFIGURED) == 0U)
    return (ARM_DRIVER_ERROR);

  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

  cr1 = reg->CR1;
  cr2 = reg->CR2;

  /* Update SPI statuses */
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;
  info->status.mode_fault = 0U;

  /* Save transfer info */
  xfer->rx_buf = NULL;
  xfer->tx_buf = (uint8_t *)data;
  xfer->num    = num;
  xfer->rx_cnt = 0U;
  xfer->tx_cnt = 0U;

  value = (uint32_t)(*xfer->tx_buf++);

  if (cr1 & SPI_CR1_DFF) {
    value |= (uint32_t)(*xfer->tx_buf++ << 8U);
  }

  /* Write data to data register */
  reg->DR = value;
  ++xfer->tx_cnt;

#ifdef __SPI_DMA_RX
  if (spi->rx_dma != NULL) {
    /* Configure and enable rx DMA channel */
    cfg = DMA_PRIORITY(spi->rx_dma->priority) | DMA_PERIPHERAL_TO_MEMORY | DMA_TRANSFER_COMPLETE_INTERRUPT;

    if (cr1 & SPI_CR1_DFF) {
      /* 16 - bit data frame */
      cfg |= DMA_PERIPHERAL_DATA_16BIT | DMA_MEMORY_DATA_16BIT;
    }

    DMA_ChannelConfigure(spi->rx_dma->instance, cfg, (uint32_t)(&reg->DR), (uint32_t)(&xfer->dump_val), num);
    DMA_ChannelEnable(spi->rx_dma->instance);

    /* RX Buffer DMA enable */
    cr2 |= SPI_CR2_RXDMAEN;
  }
  else
#endif
  {
    /* Interrupt mode */
    /* RX Buffer not empty interrupt enable */
    cr2 |= SPI_CR2_RXNEIE;
  }

  if (num > 1U) {
#ifdef __SPI_DMA_TX
    if (spi->tx_dma != NULL) {
      cfg = DMA_PRIORITY(spi->tx_dma->priority) | DMA_MEMORY_TO_PERIPHERAL | DMA_MEMORY_INCREMENT | DMA_TRANSFER_COMPLETE_INTERRUPT;

      if (cr1 & SPI_CR1_DFF) {
        /* 16 - bit data frame */
        cfg |= DMA_PERIPHERAL_DATA_16BIT | DMA_MEMORY_DATA_16BIT;
      }

      DMA_ChannelConfigure(spi->tx_dma->instance, cfg, (uint32_t)&reg->DR, (uint32_t)xfer->tx_buf, num-1);
      DMA_ChannelEnable(spi->tx_dma->instance);

      /* TX Buffer DMA enable */
      cr2 |= SPI_CR2_TXDMAEN;
    }
    else
#endif
    {
      /* Interrupt mode */
      /* TX Buffer empty interrupt enable */
      cr2 |= SPI_CR2_TXEIE;
    }
  }

  reg->CR2 = cr2;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t SPI_Receive(void *data, uint32_t num, const SPI_RESOURCES *spi)
 * @brief       Start receiving data from SPI receiver.
 * @param[out]  data  Pointer to buffer for data to receive from SPI receiver
 * @param[in]   num   Number of data items to receive
 * @param[in]   spi   Pointer to SPI resources
 * @return      \ref execution_status
 */
static
int32_t SPI_Receive(void *data, uint32_t num, const SPI_RESOURCES *spi)
{
  SPI_INFO *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_TypeDef *reg = spi->reg;
  uint32_t cr2;
#ifdef __SPI_DMA
  uint32_t cr1;
  uint32_t cfg;
#endif

  if ((data == NULL) || (num == 0U))
    return (ARM_DRIVER_ERROR_PARAMETER);

  if ((info->state & SPI_CONFIGURED) == 0U)
    return (ARM_DRIVER_ERROR);

  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

#ifdef __SPI_DMA
  cr1 = reg->CR1;
#endif
  cr2 = reg->CR2;

  /* Update SPI statuses */
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;
  info->status.mode_fault = 0U;

  /* Save transfer info */
  xfer->rx_buf = (uint8_t *)data;
  xfer->tx_buf = NULL;
  xfer->num    = num;
  xfer->rx_cnt = 0U;
  xfer->tx_cnt = 0U;

  /* Write data to data register */
  reg->DR = (uint32_t)xfer->def_val;
  ++xfer->tx_cnt;

#ifdef __SPI_DMA_RX
  /* DMA mode */
  if (spi->rx_dma != NULL) {
    cfg = DMA_PRIORITY(spi->rx_dma->priority) | DMA_PERIPHERAL_TO_MEMORY | DMA_MEMORY_INCREMENT | DMA_TRANSFER_COMPLETE_INTERRUPT;

    if (cr1 & SPI_CR1_DFF) {
      /* 16 - bit data frame */
      cfg |= DMA_PERIPHERAL_DATA_16BIT | DMA_MEMORY_DATA_16BIT;
    }

    DMA_ChannelConfigure(spi->rx_dma->instance, cfg, (uint32_t)(&reg->DR), (uint32_t)xfer->rx_buf, num);
    DMA_ChannelEnable(spi->rx_dma->instance);

    /* RX Buffer DMA enable */
    cr2 |= SPI_CR2_RXDMAEN;
  }
  else
#endif
  {
    /* Interrupt mode */
    /* RX Buffer not empty interrupt enable */
    cr2 |= SPI_CR2_RXNEIE;
  }

  if (num > 1U) {
#ifdef __SPI_DMA_TX
    /* DMA mode */
    if (spi->tx_dma != NULL) {
      cfg = DMA_PRIORITY(spi->tx_dma->priority) | DMA_MEMORY_TO_PERIPHERAL | DMA_TRANSFER_COMPLETE_INTERRUPT;

      if (cr1 & SPI_CR1_DFF) {
        /* 16 - bit data frame */
        cfg |= DMA_PERIPHERAL_DATA_16BIT | DMA_MEMORY_DATA_16BIT;
      }

      DMA_ChannelConfigure(spi->tx_dma->instance, cfg, (uint32_t)(&reg->DR), (uint32_t)(&xfer->def_val), num-1);
      DMA_ChannelEnable(spi->tx_dma->instance);

      /* TX Buffer DMA enable */
      cr2 |= SPI_CR2_TXDMAEN;
    }
    else
#endif
    {
      /* Interrupt mode */
      /* TX Buffer empty interrupt enable */
      cr2 |= SPI_CR2_TXEIE;
    }
  }

  reg->CR2 = cr2;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t SPI_Transfer(const void *data_out, void *data_in, uint32_t num, const SPI_RESOURCES *spi)
 * @brief       Start sending/receiving data to/from SPI transmitter/receiver.
 * @param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
 * @param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
 * @param[in]   num       Number of data items to transfer
 * @param[in]   spi       Pointer to SPI resources
 * @return      \ref execution_status
 */
static
int32_t SPI_Transfer(const void *data_out, void *data_in, uint32_t num, const SPI_RESOURCES *spi)
{
  SPI_INFO *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_TypeDef *reg = spi->reg;
  uint32_t cr1, cr2;
  uint32_t value;
#ifdef __SPI_DMA
  uint32_t cfg;
#endif

  if ((data_out == NULL) || (data_in == NULL) || (num == 0U))
    return (ARM_DRIVER_ERROR_PARAMETER);

  if ((info->state & SPI_CONFIGURED) == 0U)
    return (ARM_DRIVER_ERROR);

  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

  cr1 = reg->CR1;
  cr2 = reg->CR2;

  /* Update SPI statuses */
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;
  info->status.mode_fault = 0U;

  /* Save transfer info */
  xfer->rx_buf = (uint8_t *)data_in;
  xfer->tx_buf = (uint8_t *)data_out;
  xfer->num    = num;
  xfer->rx_cnt = 0U;
  xfer->tx_cnt = 0U;

  value = (uint32_t)(*xfer->tx_buf++);

  if (cr1 & SPI_CR1_DFF) {
    value |= (uint32_t)(*xfer->tx_buf++ << 8U);
  }

  /* Write data to data register */
  reg->DR = value;
  ++xfer->tx_cnt;

#ifdef __SPI_DMA
  if ((spi->rx_dma != NULL) || (spi->tx_dma != NULL)) {
    /* DMA mode */

    if (spi->rx_dma != NULL) {
      cfg = DMA_PRIORITY(spi->rx_dma->priority) | DMA_PERIPHERAL_TO_MEMORY | DMA_MEMORY_INCREMENT | DMA_TRANSFER_COMPLETE_INTERRUPT;

      if (cr1 & SPI_CR1_DFF) {
        /* 16 - bit data frame */
        cfg |= DMA_PERIPHERAL_DATA_16BIT | DMA_MEMORY_DATA_16BIT;
      }

      DMA_ChannelConfigure(spi->rx_dma->instance, cfg, (uint32_t)(&reg->DR), (uint32_t)xfer->rx_buf, num);
      DMA_ChannelEnable(spi->rx_dma->instance);

      /* RX Buffer DMA enable */
      cr2 |= SPI_CR2_RXDMAEN;
    }

    if ((num > 1U) && (spi->tx_dma != NULL)) {
      cfg = DMA_PRIORITY(spi->tx_dma->priority) | DMA_MEMORY_TO_PERIPHERAL | DMA_MEMORY_INCREMENT | DMA_TRANSFER_COMPLETE_INTERRUPT;

      if (cr1 & SPI_CR1_DFF) {
        /* 16 - bit data frame */
        cfg |= DMA_PERIPHERAL_DATA_16BIT | DMA_MEMORY_DATA_16BIT;
      }

      DMA_ChannelConfigure(spi->tx_dma->instance, cfg, (uint32_t)(&reg->DR), (uint32_t)xfer->tx_buf, num-1);
      DMA_ChannelEnable(spi->tx_dma->instance);

      /* TX Buffer DMA enable */
      cr2 |= SPI_CR2_TXDMAEN;
    }
  }
  else
#endif
  {
    /* Interrupt mode */
    /* RX Buffer not empty interrupt enable */
    cr2 |= SPI_CR2_RXNEIE;

    if (num > 1U) {
      /* TX Buffer empty interrupt enable */
      cr2 |= SPI_CR2_TXEIE;
    }
  }

  reg->CR2 = cr2;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          uint32_t SPI_GetDataCount(const SPI_RESOURCES *spi)
 * @brief       Get transferred data count.
 * @param[in]   spi  Pointer to SPI resources
 * @return      number of data items transferred
 */
static
uint32_t SPI_GetDataCount(const SPI_RESOURCES *spi)
{
  return (spi->xfer->rx_cnt);
}

/**
 * @fn          int32_t SPI_Control(uint32_t control, uint32_t arg, const SPI_RESOURCES *spi)
 * @brief       Control SPI Interface.
 * @param[in]   control  operation
 * @param[in]   arg      argument of operation (optional)
 * @param[in]   spi      Pointer to SPI resources
 * @return      \ref execution_status
 */
static int32_t SPI_Control(uint32_t control, uint32_t arg, const SPI_RESOURCES *spi)
{
  int32_t br;
  uint32_t mode, val;
  uint32_t cr1, cr2;
  SPI_INFO *info = spi->info;
  SPI_TypeDef *reg = spi->reg;

  mode = 0U;
  val = 0U;
  cr1 = 0U;
  cr2 = 0U;

  if ((info->state & SPI_POWERED) == 0U)
    return (ARM_DRIVER_ERROR);

  if ((control & ARM_SPI_CONTROL_Msk) == ARM_SPI_ABORT_TRANSFER) {
    cr2 = reg->CR2;
    /* Send abort */
    if (spi->tx_dma != NULL) {
      /* DMA mode */
      /* TX buffer DMA disable */
      cr2 &= ~SPI_CR2_TXDMAEN;

      /* Disable TX DMA transfer */
      DMA_ChannelDisable(spi->tx_dma->instance);
    }
    else {
      /* Interrupt mode */
      /* Disable TX buffer empty interrupt */
      cr2 &= ~SPI_CR2_TXEIE;
    }

    /* Receive abort */
    if (spi->rx_dma != NULL) {
      /* DMA mode */
      /* RX buffer DMA disable */
      cr2 &= ~SPI_CR2_RXDMAEN;

      /* Disable RX DMA transfer */
      DMA_ChannelDisable(spi->rx_dma->instance);
    }
    else {
      /* Interrupt mode */
      /* Disable RX buffer not empty interrupt */
      cr2 &= ~SPI_CR2_RXNEIE;
    }

    reg->CR2 = cr2;

    memset(spi->xfer, 0, sizeof(SPI_TRANSFER_INFO));
    info->status.busy = 0U;

    return (ARM_DRIVER_OK);
  }

  /* Check for busy flag */
  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

  switch (control & ARM_SPI_CONTROL_Msk) {
    case ARM_SPI_MODE_INACTIVE:
      mode |= ARM_SPI_MODE_INACTIVE;
      break;

    case ARM_SPI_MODE_MASTER:
      mode |= ARM_SPI_MODE_MASTER;
      /* Master enabled */
      cr1 |= SPI_CR1_MSTR;
      break;

    case ARM_SPI_MODE_SLAVE:
      mode |= ARM_SPI_MODE_SLAVE;
      break;

    case ARM_SPI_MODE_MASTER_SIMPLEX:
    case ARM_SPI_MODE_SLAVE_SIMPLEX:
      return (ARM_SPI_ERROR_MODE);

    case ARM_SPI_SET_BUS_SPEED:
      /* Set SPI Bus Speed */
      br = CalcPrescalerValue(spi, arg);
      if (br < 0)
        return (ARM_DRIVER_ERROR);

      /* Disable SPI, update prescaler and enable SPI */
      reg->CR1 &= ~SPI_CR1_SPE;
      reg->CR1 = (reg->CR1 & ~SPI_CR1_BR_Msk) | (br << SPI_CR1_BR_Pos);
      reg->CR1 |= SPI_CR1_SPE;
      return (ARM_DRIVER_OK);

    case ARM_SPI_GET_BUS_SPEED:
      /* Return current bus speed */
      return (int32_t)(RCC_GetPeriphFreq(spi->periph) >> (((reg->CR1 & SPI_CR1_BR_Msk) >> SPI_CR1_BR_Pos) + 1U));

    case ARM_SPI_SET_DEFAULT_TX_VALUE:
      spi->xfer->def_val = (uint16_t)(arg & 0xFFFFU);
      return (ARM_DRIVER_OK);

    case ARM_SPI_CONTROL_SS:
      val = (info->mode & ARM_SPI_CONTROL_Msk);
      /* Master modes */
      if (val == ARM_SPI_MODE_MASTER) {
        val = info->mode & ARM_SPI_SS_MASTER_MODE_Msk;
        /* Check if NSS pin is available and
           software slave select master is selected */
        if ((spi->io.nss != NULL) && (val == ARM_SPI_SS_MASTER_SW)) {
          SPI_PIN *io = spi->io.nss;
          /* Set/Clear NSS pin */
          if (arg == ARM_SPI_SS_INACTIVE)
            GPIO_PinWrite(io->port, io->pin, GPIO_PIN_OUT_HIGH);
          else
            GPIO_PinWrite(io->port, io->pin, GPIO_PIN_OUT_LOW);
        }
        else {
          return (ARM_DRIVER_ERROR);
        }

        return (ARM_DRIVER_OK);
      }
      /* Slave modes */
      else if (val == ARM_SPI_MODE_SLAVE) {
        val = info->mode & ARM_SPI_SS_SLAVE_MODE_Msk;
        /* Check if slave select slave mode is selected */
        if (val == ARM_SPI_SS_SLAVE_SW) {
          if (arg == ARM_SPI_SS_ACTIVE) {
            reg->CR1 |= SPI_CR1_SSI;
          }
          else {
            reg->CR1 &= ~SPI_CR1_SSI;
          }
          return (ARM_DRIVER_OK);
        }
        else {
          return (ARM_DRIVER_ERROR);
        }
      }
      else {
        return (ARM_DRIVER_ERROR);
      }

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  /* Frame format: */
  switch (control & ARM_SPI_FRAME_FORMAT_Msk) {
    case ARM_SPI_CPOL0_CPHA0:
      break;
    case ARM_SPI_CPOL0_CPHA1:
      cr1 |= SPI_CR1_CPHA;
      break;
    case ARM_SPI_CPOL1_CPHA0:
      cr1 |= SPI_CR1_CPOL;
      break;
    case ARM_SPI_CPOL1_CPHA1:
      cr1 |= SPI_CR1_CPHA | SPI_CR1_CPOL;
      break;
    case ARM_SPI_TI_SSI:
    case ARM_SPI_MICROWIRE:
    default:
      return (ARM_SPI_ERROR_FRAME_FORMAT);
  }

  /* Data Bits */
  switch (control & ARM_SPI_DATA_BITS_Msk) {
    case ARM_SPI_DATA_BITS(8U):
      break;
    case ARM_SPI_DATA_BITS(16U):
      cr1 |= SPI_CR1_DFF;
      break;
    default:
      return (ARM_SPI_ERROR_DATA_BITS);
  }

  /* Bit order */
  if ((control & ARM_SPI_BIT_ORDER_Msk) == ARM_SPI_LSB_MSB) {
    cr1 |= SPI_CR1_LSBFIRST;
  }

  /* Slave select master modes */
  if (mode == ARM_SPI_MODE_MASTER) {
    switch (control & ARM_SPI_SS_MASTER_MODE_Msk) {
      case ARM_SPI_SS_MASTER_UNUSED:
        if (spi->io.nss != NULL) {
          /* Unconfigure NSS pin */
          PinConfig(spi->io.nss, &SPI_pin_cfg_analog);
        }
        /* Software slave management */
        /* Internal NSS always active, IO value is ignored */
        cr1 |= SPI_CR1_SSM | SPI_CR1_SSI;
        mode |= ARM_SPI_SS_MASTER_UNUSED;
        break;

      case ARM_SPI_SS_MASTER_HW_INPUT:
        if (spi->io.nss != NULL) {
          /* Configure NSS pin */
          PinConfig(spi->io.nss, &SPI_pin_cfg_af);
        }
        else {
          /* NSS pin is not available */
          return (ARM_SPI_ERROR_SS_MODE);
        }
        mode |= ARM_SPI_SS_MASTER_HW_INPUT;
        break;

      case ARM_SPI_SS_MASTER_SW:
        if (spi->io.nss != NULL) {
          /* Configure NSS pin as GPIO output */
          PinConfig(spi->io.nss, &SPI_pin_cfg_out_pp);
          /* Software slave management */
          cr1 |= SPI_CR1_SSM | SPI_CR1_SSI;
          mode |= ARM_SPI_SS_MASTER_SW;
        }
        else {
          /* NSS pin is not available */
          return (ARM_SPI_ERROR_SS_MODE);
        }
        break;

      case ARM_SPI_SS_MASTER_HW_OUTPUT:
        if (spi->io.nss != NULL) {
          /* Configure NSS pin - SPI NSS alternative function */
          PinConfig(spi->io.nss, &SPI_pin_cfg_af);
          /* Slave select output enable */
          cr2 |= SPI_CR2_SSOE;
          mode |= ARM_SPI_SS_MASTER_HW_OUTPUT;
        }
        else {
          /* NSS pin is not available */
          return (ARM_SPI_ERROR_SS_MODE);
        }
        break;

      default:
        return (ARM_SPI_ERROR_SS_MODE);
    }
  }

  /* Slave select slave modes */
  if (mode == ARM_SPI_MODE_SLAVE) {
    switch (control & ARM_SPI_SS_SLAVE_MODE_Msk) {
      case ARM_SPI_SS_SLAVE_HW:
        if (spi->io.nss != NULL) {
          /* Configure NSS pin - SPI NSS alternative function */
          PinConfig(spi->io.nss, &SPI_pin_cfg_af);
          mode |= ARM_SPI_SS_SLAVE_HW;
        }
        else {
          /* NSS pin is not available */
          return (ARM_SPI_ERROR_SS_MODE);
        }
        break;

      case ARM_SPI_SS_SLAVE_SW:
        if (spi->io.nss != NULL) {
          /* Unconfigure NSS pin */
          PinConfig(spi->io.nss, &SPI_pin_cfg_analog);
        }
        /* Enable software slave management */
        cr1 |= SPI_CR1_SSM;
        mode |= ARM_SPI_SS_SLAVE_SW;
        break;

      default:
        return (ARM_SPI_ERROR_SS_MODE);
    }
  }

  /* Set SPI Bus Speed */
  if ((mode & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_MASTER) {
    br = CalcPrescalerValue(spi, arg);
    if (br < 0)
      return ARM_DRIVER_ERROR;
    // Save prescaler value
    cr1 |= (br << SPI_CR1_BR_Pos);
  }

  info->mode = mode;

  /* Configure registers */
  reg->CR1 &= ~SPI_CR1_SPE;
  reg->CR2 = cr2 | SPI_CR2_ERRIE;
  reg->CR1 = cr1;

  if ((mode & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_INACTIVE) {
    info->state &= ~SPI_CONFIGURED;
  }
  else {
    info->state |= SPI_CONFIGURED;
  }

  /* Enable SPI */
  reg->CR1 |= SPI_CR1_SPE;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          ARM_SPI_STATUS SPI_GetStatus (const SPI_RESOURCES *spi)
 * @brief       Get SPI status.
 * @param[in]   spi  Pointer to SPI resources
 * @return      SPI status \ref ARM_SPI_STATUS
 */
static
ARM_SPI_STATUS SPI_GetStatus(const SPI_RESOURCES *spi)
{
  ARM_SPI_STATUS status;

  status.busy       = spi->info->status.busy;
  status.data_lost  = spi->info->status.data_lost;
  status.mode_fault = spi->info->status.mode_fault;

  return status;
}

/**
 * @fn          void SPI_IRQHandler(SPI_RESOURCES *spi)
 * @brief       SPI Interrupt handler.
 * @param[in]   spi  Pointer to SPI resources
 */
void SPI_IRQHandler(const SPI_RESOURCES *spi)
{
  uint32_t value;
  uint32_t event;
  register uint32_t sr, cr1, cr2;

  SPI_INFO *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_TypeDef *reg = spi->reg;

  event = 0U;

  /* Save control register 1 */
  cr1 = reg->CR1;
  /* Save control register 2 */
  cr2 = reg->CR2;
  /* Save status register */
  sr = reg->SR;

  if ((sr & (SPI_SR_OVR | SPI_SR_MODF)) != 0U) {
    if ((sr & SPI_SR_OVR) != 0U) {
      value = reg->DR;

      if ((xfer->rx_cnt < xfer->num) && (xfer->rx_buf != NULL)) {
        *xfer->rx_buf++ = (uint8_t)value;

        if (cr1 & SPI_CR1_DFF) {
          *xfer->rx_buf++ = (uint8_t)(value >> 8U);
        }
      }
      xfer->rx_cnt++;
      sr = reg->SR;

      info->status.data_lost = 1U;
      event |= ARM_SPI_EVENT_DATA_LOST;
    }

    if ((sr & SPI_SR_MODF) != 0U) {
      // Mode fault flag is set
      info->status.mode_fault = 1U;

      // Write CR1 register to clear MODF flag
      reg->CR1 = cr1;
      event |= ARM_SPI_EVENT_MODE_FAULT;
    }
  }

  if (((sr & SPI_SR_RXNE) != 0U) && ((cr2 & SPI_CR2_RXNEIE) != 0U)) {
    // Receive Buffer Not Empty
    if (xfer->rx_cnt < xfer->num) {
      value = reg->DR;

      if (xfer->rx_buf != NULL) {
        *xfer->rx_buf++ = (uint8_t)value;

        if (cr1 & SPI_CR1_DFF) {
          *xfer->rx_buf++ = (uint8_t)(value >> 8U);
        }
      }

      xfer->rx_cnt++;

      if (xfer->rx_cnt == xfer->num) {
        /* Disable RX Buffer Not Empty Interrupt */
        cr2 &= ~SPI_CR2_RXNEIE;
        /* Clear busy flag */
        info->status.busy = 0U;
        /* Transfer completed */
        event |= ARM_SPI_EVENT_TRANSFER_COMPLETE;
      }
    }
    else {
      // Unexpected transfer, data lost
      event |= ARM_SPI_EVENT_DATA_LOST;
    }
  }

  if (((sr & SPI_SR_TXE) != 0U) && ((cr2 & SPI_CR2_TXEIE) != 0U)) {
    if (xfer->tx_cnt < xfer->num) {
      if (xfer->tx_buf != NULL) {
        value = (uint32_t)(*xfer->tx_buf++);

        if (cr1 & SPI_CR1_DFF) {
          value |= (uint32_t)(*xfer->tx_buf++ << 8U);
        }
      }
      else {
        value = (uint32_t)xfer->def_val;
      }

      /* Write data to data register */
      reg->DR = value;

      if (++xfer->tx_cnt == xfer->num) {
        /* All data sent, disable TX Buffer Empty Interrupt */
        cr2 &= ~SPI_CR2_TXEIE;
      }
    }
    else {
      /* Unexpected transfer, data lost */
      event |= ARM_SPI_EVENT_DATA_LOST;
    }
  }

  reg->CR2 = cr2;

  /* Send event */
  if ((event != 0U) && ((info->cb_event != NULL))) {
    info->cb_event(event);
  }
}

#ifdef __SPI_DMA_TX
void SPI_TX_DMA_Complete(uint32_t events, const SPI_RESOURCES *spi) {

  DMA_ChannelDisable(spi->tx_dma->instance);

  if ((DMA_ChannelTransferItemCount(spi->tx_dma->instance) != 0) && (spi->xfer->num != 0)) {
    // TX DMA Complete caused by transfer abort
    return;
  }

  spi->xfer->tx_cnt = spi->xfer->num;
}
#endif

#ifdef __SPI_DMA_RX
void SPI_RX_DMA_Complete(uint32_t events, const SPI_RESOURCES *spi) {

  DMA_ChannelDisable(spi->rx_dma->instance);

  if ((DMA_ChannelTransferItemCount(spi->rx_dma->instance) != 0) && (spi->xfer->num != 0)) {
    // RX DMA Complete caused by transfer abort
    return;
  }

  spi->xfer->rx_cnt = spi->xfer->num;

  spi->info->status.busy = 0U;
  if (spi->info->cb_event != NULL) {
    spi->info->cb_event(ARM_SPI_EVENT_TRANSFER_COMPLETE);
  }
}
#endif

/* SPI1 */
#if defined(USE_SPI1)
static int32_t        SPI1_Initialize          (ARM_SPI_SignalEvent_t pSignalEvent)                { return SPI_Initialize (pSignalEvent, &SPI1_Resources); }
static int32_t        SPI1_Uninitialize        (void)                                              { return SPI_Uninitialize (&SPI1_Resources); }
static int32_t        SPI1_PowerControl        (ARM_POWER_STATE state)                             { return SPI_PowerControl (state, &SPI1_Resources); }
static int32_t        SPI1_Send                (const void *data, uint32_t num)                    { return SPI_Send (data, num, &SPI1_Resources); }
static int32_t        SPI1_Receive             (void *data, uint32_t num)                          { return SPI_Receive (data, num, &SPI1_Resources); }
static int32_t        SPI1_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SPI_Transfer (data_out, data_in, num, &SPI1_Resources); }
static uint32_t       SPI1_GetDataCount        (void)                                              { return SPI_GetDataCount (&SPI1_Resources); }
static int32_t        SPI1_Control             (uint32_t control, uint32_t arg)                    { return SPI_Control (control, arg, &SPI1_Resources); }
static ARM_SPI_STATUS SPI1_GetStatus           (void)                                              { return SPI_GetStatus (&SPI1_Resources); }
       void           SPI1_IRQHandler          (void)                                              {        SPI_IRQHandler (&SPI1_Resources); }

#if defined(SPI1_TX_DMA_Instance)
      void            SPI1_TX_DMA_Handler      (uint32_t events)                                   {        SPI_TX_DMA_Complete (events, &SPI1_Resources); }
#endif
#if defined(SPI1_RX_DMA_Instance)
      void            SPI1_RX_DMA_Handler      (uint32_t events)                                   {        SPI_RX_DMA_Complete (events, &SPI1_Resources); }
#endif

ARM_DRIVER_SPI Driver_SPI1 = {
  SPIx_GetVersion,
  SPIx_GetCapabilities,
  SPI1_Initialize,
  SPI1_Uninitialize,
  SPI1_PowerControl,
  SPI1_Send,
  SPI1_Receive,
  SPI1_Transfer,
  SPI1_GetDataCount,
  SPI1_Control,
  SPI1_GetStatus
};
#endif  /* USE_SPI1 */

/* SPI2 */
#if defined(USE_SPI2)
static int32_t        SPI2_Initialize          (ARM_SPI_SignalEvent_t pSignalEvent)                { return SPI_Initialize (pSignalEvent, &SPI2_Resources); }
static int32_t        SPI2_Uninitialize        (void)                                              { return SPI_Uninitialize (&SPI2_Resources); }
static int32_t        SPI2_PowerControl        (ARM_POWER_STATE state)                             { return SPI_PowerControl (state, &SPI2_Resources); }
static int32_t        SPI2_Send                (const void *data, uint32_t num)                    { return SPI_Send (data, num, &SPI2_Resources); }
static int32_t        SPI2_Receive             (void *data, uint32_t num)                          { return SPI_Receive (data, num, &SPI2_Resources); }
static int32_t        SPI2_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SPI_Transfer (data_out, data_in, num, &SPI2_Resources); }
static uint32_t       SPI2_GetDataCount        (void)                                              { return SPI_GetDataCount (&SPI2_Resources); }
static int32_t        SPI2_Control             (uint32_t control, uint32_t arg)                    { return SPI_Control (control, arg, &SPI2_Resources); }
static ARM_SPI_STATUS SPI2_GetStatus           (void)                                              { return SPI_GetStatus (&SPI2_Resources); }
       void           SPI2_IRQHandler          (void)                                              {        SPI_IRQHandler (&SPI2_Resources); }

#if defined(SPI2_TX_DMA_Instance)
       void           SPI2_TX_DMA_Handler      (uint32_t events)                                   {        SPI_TX_DMA_Complete (events, &SPI2_Resources); }
#endif
#if defined(SPI2_RX_DMA_Instance)
       void           SPI2_RX_DMA_Handler      (uint32_t events)                                   {        SPI_RX_DMA_Complete (events, &SPI2_Resources); }
#endif

ARM_DRIVER_SPI Driver_SPI2 = {
  SPIx_GetVersion,
  SPIx_GetCapabilities,
  SPI2_Initialize,
  SPI2_Uninitialize,
  SPI2_PowerControl,
  SPI2_Send,
  SPI2_Receive,
  SPI2_Transfer,
  SPI2_GetDataCount,
  SPI2_Control,
  SPI2_GetStatus
};
#endif  /* USE_SPI2 */

/* SPI3 */
#if defined(USE_SPI3)
static int32_t        SPI3_Initialize          (ARM_SPI_SignalEvent_t pSignalEvent)                { return SPI_Initialize (pSignalEvent, &SPI3_Resources); }
static int32_t        SPI3_Uninitialize        (void)                                              { return SPI_Uninitialize (&SPI3_Resources); }
static int32_t        SPI3_PowerControl        (ARM_POWER_STATE state)                             { return SPI_PowerControl (state, &SPI3_Resources); }
static int32_t        SPI3_Send                (const void *data, uint32_t num)                    { return SPI_Send (data, num, &SPI3_Resources); }
static int32_t        SPI3_Receive             (void *data, uint32_t num)                          { return SPI_Receive (data, num, &SPI3_Resources); }
static int32_t        SPI3_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SPI_Transfer (data_out, data_in, num, &SPI3_Resources); }
static uint32_t       SPI3_GetDataCount        (void)                                              { return SPI_GetDataCount (&SPI3_Resources); }
static int32_t        SPI3_Control             (uint32_t control, uint32_t arg)                    { return SPI_Control (control, arg, &SPI3_Resources); }
static ARM_SPI_STATUS SPI3_GetStatus           (void)                                              { return SPI_GetStatus (&SPI3_Resources); }
       void           SPI3_IRQHandler          (void)                                              {        SPI_IRQHandler (&SPI3_Resources); }

#if defined(SPI3_TX_DMA_Instance)
      void            SPI3_TX_DMA_Handler      (uint32_t events)                                   {        SPI_TX_DMA_Complete (events, &SPI3_Resources); }
#endif
#if defined(SPI3_RX_DMA_Instance)
      void            SPI3_RX_DMA_Handler      (uint32_t events)                                   {        SPI_RX_DMA_Complete (events, &SPI3_Resources); }
#endif

ARM_DRIVER_SPI Driver_SPI3 = {
  SPIx_GetVersion,
  SPIx_GetCapabilities,
  SPI3_Initialize,
  SPI3_Uninitialize,
  SPI3_PowerControl,
  SPI3_Send,
  SPI3_Receive,
  SPI3_Transfer,
  SPI3_GetDataCount,
  SPI3_Control,
  SPI3_GetStatus
};
#endif  /* USE_SPI3 */

#endif

/* ----------------------------- End of file ---------------------------------*/
