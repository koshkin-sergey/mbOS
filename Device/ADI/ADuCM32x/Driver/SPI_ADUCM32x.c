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
 * Project: SPI Driver for ADI ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "SPI_ADUCM32x.h"

#if defined(USE_SPI0) || defined(USE_SPI1)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define SPI_DRV_VERSION  DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

#define SPI_FIFO_SIZE               (4U)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

extern Driver_CLK_t Driver_CLK;
//extern Driver_DMA_t Driver_DMA;

/* Driver Version */
static const DRIVER_VERSION DriverVersion = {
  SPI_API_VERSION,
  SPI_DRV_VERSION
};

/* Driver Capabilities */
static const SPI_CAPABILITIES DriverCapabilities = {
  0, /* Reserved (must be zero) */
  0, /* TI Synchronous Serial Interface */
  0, /* Microwire Interface */
  0, /* Signal Mode Fault event: \ref SPI_EVENT_MODE_FAULT */
  0  /* Reserved (must be zero) */
};

static const GPIO_PIN_CFG_t pin_cfg_gpio_in = {
  GPIO_PIN_FUNC_0,
  GPIO_MODE_ANALOG,
  GPIO_PULL_DISABLE,
};

static const GPIO_PIN_CFG_t pin_cfg_gpio_out_pp = {
  GPIO_PIN_FUNC_0,
  GPIO_MODE_OUT_PP,
  GPIO_PULL_DISABLE,
};

#if defined(USE_SPI0)

/* SPI0 Information (Run-Time) */
static SPI_Info_t         SPI0_Info;
static SPI_TRANSFER_INFO  SPI0_Xfer;
static SPI_Irq_t          SPI0_Irq = {
    SPI0_IRQn,
    SPI0_INT_PRIORITY,
    0,
    DMA_SPI0_TX_IRQn,
    DMA_SPI0_RX_IRQn,
};

/* SPI0 Resources */
static SPI_Resources_t SPI0_Resources = {
    MMR_SPI0,
    {
#if defined(USE_SPI0_MOSI)
        &(SPI_Pin_t){SPI0_MOSI_GPIO_PORT, SPI0_MOSI_GPIO_PIN, {SPI0_MOSI_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#else
        NULL,
#endif
#if defined(USE_SPI0_MISO)
        &(SPI_Pin_t){SPI0_MISO_GPIO_PORT, SPI0_MISO_GPIO_PIN, {SPI0_MISO_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#else
        NULL,
#endif
        &(SPI_Pin_t){SPI0_SCLK_GPIO_PORT, SPI0_SCLK_GPIO_PIN, {SPI0_SCLK_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#if defined(USE_SPI0_CS)
        &(SPI_Pin_t){SPI0_CS_GPIO_PORT, SPI0_CS_GPIO_PIN, {SPI0_CS_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#else
        NULL,
#endif
    },
    CLK_PERIPH_SPI0,
    &SPI0_Info,
    &SPI0_Xfer,
    &SPI0_Irq,
};
#endif /* USE_SPI0 */

#if defined(USE_SPI1)

/* SPI1 Information (Run-Time) */
static SPI_Info_t         SPI1_Info;
static SPI_TRANSFER_INFO  SPI1_Xfer;
static SPI_Irq_t          SPI1_Irq = {
    SPI1_IRQn,
    SPI1_INT_PRIORITY,
    0,
    DMA_SPI1_TX_IRQn,
    DMA_SPI1_RX_IRQn,
};

/* SPI1 Resources */
static SPI_Resources_t SPI1_Resources = {
    MMR_SPI1,
    {
#if defined(USE_SPI1_MOSI)
        &(SPI_Pin_t){SPI1_MOSI_GPIO_PORT, SPI1_MOSI_GPIO_PIN, {SPI1_MOSI_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#else
        NULL,
#endif
#if defined(USE_SPI1_MISO)
        &(SPI_Pin_t){SPI1_MISO_GPIO_PORT, SPI1_MISO_GPIO_PIN, {SPI1_MISO_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#else
        NULL,
#endif
        &(SPI_Pin_t){SPI1_SCLK_GPIO_PORT, SPI1_SCLK_GPIO_PIN, {SPI1_SCLK_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#if defined(USE_SPI1_CS)
        &(SPI_Pin_t){SPI1_CS_GPIO_PORT, SPI1_CS_GPIO_PIN, {SPI1_CS_GPIO_FUNC, GPIO_MODE_ANALOG, GPIO_PULL_DISABLE}},
#else
        NULL,
#endif
    },
    CLK_PERIPH_SPI1,
    &SPI1_Info,
    &SPI1_Xfer,
    &SPI1_Irq,
};
#endif /* USE_SPI1 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          void PinConfig(const SPI_Pin_t *io, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin
 * @param[in]   io   Pointer to SPI_Pin_t
 * @param[in]   cfg  Pointer to GPIO_PIN_CFG_t. Can be NULL.
 */
static
void PinConfig(const SPI_Pin_t *io, const GPIO_PIN_CFG_t *cfg)
{
  if (io == NULL) {
    return;
  }

  if (cfg == NULL) {
    cfg = &io->cfg;
  }

  io->gpio->PinConfig(io->pin, cfg);
}

static
DRIVER_VERSION SPI_GetVersion(void)
{
  return (DriverVersion);
}

static
SPI_CAPABILITIES SPI_GetCapabilities(void)
{
  return (DriverCapabilities);
}

/**
 * @brief       Initialize SPI Interface.
 * @param[in]   cb_event  Pointer to SPI_SignalEvent
 * @return      Execution status
 */
static
int32_t SPI_Initialize(SPI_SignalEvent_t cb_event, SPI_Resources_t *spi)
{
  SPI_Info_t *info = spi->info;

  if (info->state & SPI_INITIALIZED) {
    return (DRIVER_OK);
  }

  /* Initialize SPI Run-Time Resources */
  info->cb_event = cb_event;

  /* Clear transfer information */
  memset((void *)spi->xfer, 0, sizeof(SPI_TRANSFER_INFO));

  SPI_IO_t *io = &spi->io;

  /* Configure MISO Pin */
  PinConfig(io->miso, NULL);
  /* Configure MOSI Pin */
  PinConfig(io->mosi, NULL);
  /* Configure SCK Pin */
  PinConfig(io->sclk, NULL);
  /* Configure NSS Pin */
  PinConfig(io->cs,   NULL);

  info->state = SPI_INITIALIZED;

  return (DRIVER_OK);
}

/**
 * @brief       De-initialize SPI Interface.
 * @return      Execution status
 */
static
int32_t SPI_Uninitialize(SPI_Resources_t *spi)
{
  SPI_IO_t *io = &spi->io;
  const GPIO_PIN_CFG_t *pin_cfg = &pin_cfg_gpio_in;

  /* Unconfigure MISO Pin */
  PinConfig(io->miso, pin_cfg);
  /* Unconfigure MOSI Pin */
  PinConfig(io->mosi, pin_cfg);
  /* Unconfigure SCK Pin */
  PinConfig(io->sclk, pin_cfg);
  /* Unconfigure NSS Pin */
  PinConfig(io->cs,   pin_cfg);

  /* Clear SPI state */
  spi->info->state = 0U;

  return (DRIVER_OK);
}

/**
 * @brief       Control SPI Interface Power.
 * @param[in]   state  Power state
 * @return      Execution status
 */
static
int32_t SPI_PowerControl(POWER_STATE state, SPI_Resources_t *spi)
{
  SPI_Info_t    *info = spi->info;
  SPI_Irq_t     *irq  = spi->irq;
  Driver_CLK_t  *clk  = &Driver_CLK;

  if ((info->state & SPI_INITIALIZED) == 0U) {
    return (DRIVER_ERROR);
  }

  switch (state) {
    case POWER_OFF:
      /* Disable I2C peripheral clock */
      clk->PeriphDisable(spi->clk_periph);

      /* Disable I2C interrupts */
      if (irq->dma_en) {
        NVIC_DisableIRQ(irq->dma_tx_num);
        NVIC_DisableIRQ(irq->dma_rx_num);
      }
      else {
        NVIC_DisableIRQ(irq->num);
      }

      memset((void *)spi->xfer, 0, sizeof(SPI_TRANSFER_INFO));

      /* Clear powered flag */
      info->state &= ~(SPI_POWERED | SPI_CONFIGURED);
      break;

    case POWER_FULL:
      if ((info->state & SPI_POWERED) != 0U) {
        return (DRIVER_OK);
      }

      /* Clear status flags */
      info->status.busy       = 0U;
      info->status.data_lost  = 0U;
      info->status.mode_fault = 0U;

      spi->xfer->def_val      = 0U;

      /* Enable SPI peripheral clock */
      clk->PeriphEnable(spi->clk_periph);

      /* Enable SPI interrupts */
      if (irq->dma_en) {
        NVIC_ClearPendingIRQ(irq->dma_tx_num);
        NVIC_ClearPendingIRQ(irq->dma_rx_num);
        NVIC_SetPriority(irq->dma_tx_num, irq->priority);
        NVIC_SetPriority(irq->dma_rx_num, irq->priority);
        NVIC_EnableIRQ(irq->dma_tx_num);
        NVIC_EnableIRQ(irq->dma_rx_num);
      }
      else {
        NVIC_ClearPendingIRQ(irq->num);
        NVIC_SetPriority(irq->num, irq->priority);
        NVIC_EnableIRQ(irq->num);
      }

      /* Ready for operation - set powered flag */
      info->state |= SPI_POWERED;
      break;

    default:
      return (DRIVER_ERROR_UNSUPPORTED);
  }

  return (DRIVER_OK);
}

/**
 * @brief       Control SPI Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 */
static
int32_t SPI_Control(uint32_t control, uint32_t arg, SPI_Resources_t *spi)
{
  MMR_SPI_t    *mmr;
  Driver_CLK_t *clk;
  SPI_IO_t     *io;
  uint32_t      spi_clk;
  uint32_t      div;
  uint16_t      con;
  uint32_t      mode;
  SPI_Info_t   *info = spi->info;

  if ((info->state & SPI_POWERED) == 0U) {
    return (DRIVER_ERROR);
  }

  mmr = spi->mmr;

  if ((control & SPI_CONTROL_Msk) == SPI_ABORT_TRANSFER) {
    mmr->SPICON |= (uint16_t) (SPICON_TFLUSH | SPICON_RFLUSH);
    mmr->SPICON &= (uint16_t)~(SPICON_TFLUSH | SPICON_RFLUSH);

    memset((void *)spi->xfer, 0, sizeof(SPI_TRANSFER_INFO));
    info->status.busy = 0U;

    return (DRIVER_OK);
  }

  /* Check for busy flag */
  if (info->status.busy) {
    return (DRIVER_ERROR_BUSY);
  }

  clk  = &Driver_CLK;
  io   = &spi->io;
  con  = 0U;
  div  = 0U;
  mode = 0U;

  switch (control & SPI_CONTROL_Msk) {
    case SPI_MODE_INACTIVE:             // SPI Inactive
      info->mode  = SPI_MODE_INACTIVE;
      mmr->SPICON = 0U;
      info->state &= ~SPI_CONFIGURED;
      return (DRIVER_OK);

    case SPI_MODE_MASTER:               // SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
      mode |= SPI_MODE_MASTER;
      con  |= SPICON_MASEN;
      break;

    case SPI_MODE_SLAVE:                // SPI Slave  (Output on MISO, Input on MOSI)
      mode |= SPI_MODE_SLAVE;
      break;

    case SPI_SET_BUS_SPEED:             // Set Bus Speed in bps; arg = value
      if (arg == 0U) {
        return (DRIVER_ERROR);
      }
      spi_clk = clk->GetFrequency(CLK_FREQ_HCLK);
      div = (spi_clk / (2 * arg)) - 1;
      if (div > SPIDIV_DIV_MSK) {
        div = SPIDIV_DIV_MSK;
      }
      mmr->SPIDIV = (mmr->SPIDIV & (uint16_t)~SPIDIV_DIV_MSK) | (uint16_t)div;
      return (DRIVER_OK);

    case SPI_GET_BUS_SPEED:             // Get Bus Speed in bps
      spi_clk = clk->GetFrequency(CLK_FREQ_HCLK);
      div = (mmr->SPIDIV & SPIDIV_DIV_MSK);
      return ((int32_t)(spi_clk / (2U * (div + 1U))));

    case SPI_SET_DEFAULT_TX_VALUE:      // Set default Transmit value; arg = value
      spi->xfer->def_val = (arg & 0xFFFFU);
      return (DRIVER_OK);

    case SPI_CONTROL_SS:                // Control Slave Select; arg = 0:inactive, 1:active
      if (((info->mode & SPI_CONTROL_Msk)        != SPI_MODE_MASTER)  ||
          ((info->mode & SPI_SS_MASTER_MODE_Msk) != SPI_SS_MASTER_SW)) {
        return (DRIVER_ERROR);
      }

      if (io->cs == NULL) {
        return (DRIVER_ERROR);
      }

      if (arg == SPI_SS_INACTIVE) {
        io->cs->gpio->PinWrite(io->cs->pin, GPIO_PIN_OUT_HIGH);
      } else {
        io->cs->gpio->PinWrite(io->cs->pin, GPIO_PIN_OUT_LOW);
      }
      return (DRIVER_OK);

    default:
      return (DRIVER_ERROR_UNSUPPORTED);
  }

  /* Frame format */
  switch (control & SPI_FRAME_FORMAT_Msk) {
    case SPI_CPOL0_CPHA0:
      break;
    case SPI_CPOL0_CPHA1:
      con |= SPICON_CPHA;
      break;
    case SPI_CPOL1_CPHA0:
      con |= SPICON_CPOL;
      break;
    case SPI_CPOL1_CPHA1:
      con |= SPICON_CPOL | SPICON_CPHA;
      break;
    default:
      return SPI_ERROR_FRAME_FORMAT;
  }

  /* Data Bits */
  switch (control & SPI_DATA_BITS_Msk) {
    case SPI_DATA_BITS(8U):
      break;
    default:
      return SPI_ERROR_DATA_BITS;
  }

  /* Bit order */
  if ((control & SPI_BIT_ORDER_Msk) == SPI_LSB_MSB) {
    con |= SPICON_LSB;
  }

  /* Slave select master modes */
  if ((mode & SPI_CONTROL_Msk) == SPI_MODE_MASTER) {
    switch (control & SPI_SS_MASTER_MODE_Msk) {
      case SPI_SS_MASTER_UNUSED:
        if (io->cs != NULL) {
          /* Unconfigure CS pin */
          PinConfig(io->cs, &pin_cfg_gpio_in);
        }
        mode |= SPI_SS_MASTER_UNUSED;
        break;

      case SPI_SS_MASTER_SW:
        if (io->cs != NULL) {
          /* Configure CS pin as GPIO output */
          PinConfig(io->cs, &pin_cfg_gpio_out_pp);
          mode |= SPI_SS_MASTER_SW;
        }
        else {
          /* CS pin is not available */
          return (SPI_ERROR_SS_MODE);
        }
        break;

      case SPI_SS_MASTER_HW_OUTPUT:
        if (io->cs != NULL) {
          /* Configure NSS pin */
          PinConfig(io->cs, NULL);
          mode |= SPI_SS_MASTER_HW_OUTPUT;
        }
        else {
          /* NSS pin is not available */
          return (SPI_ERROR_SS_MODE);
        }
        break;

      case SPI_SS_MASTER_HW_INPUT:
        if (io->cs != NULL) {
          /* Configure NSS pin */
          PinConfig(io->cs, NULL);
          mode |= SPI_SS_MASTER_HW_INPUT;
        }
        else {
          /* NSS pin is not available */
          return (SPI_ERROR_SS_MODE);
        }
        break;

      default:
        return (SPI_ERROR_SS_MODE);
    }
  }
  /* Slave select slave modes */
  else if ((mode & SPI_CONTROL_Msk) == SPI_MODE_SLAVE) {
    switch (control & SPI_SS_SLAVE_MODE_Msk) {
      case SPI_SS_SLAVE_HW:
        if (io->cs != NULL) {
          /* Configure NSS pin */
          PinConfig(io->cs, NULL);
          mode |= SPI_SS_SLAVE_HW;
        }
        else {
          /* NSS pin is not available */
          return (SPI_ERROR_SS_MODE);
        }
        break;

      case SPI_SS_SLAVE_SW:
        if (io->cs != NULL) {
          /* Unconfigure NSS pin */
          PinConfig(io->cs, &pin_cfg_gpio_in);
        }
        mode |= SPI_SS_SLAVE_SW;
        break;

      default:
        return SPI_ERROR_SS_MODE;
    }
  }

  /* Set SPI Bus Speed */
  if ((mode & SPI_CONTROL_Msk) == SPI_MODE_MASTER) {
    if (arg == 0U) {
      return (DRIVER_ERROR);
    }
    spi_clk = clk->GetFrequency(CLK_FREQ_HCLK);
    div = (spi_clk / (2 * arg)) - 1;
    if (div > SPIDIV_DIV_MSK) {
      div = SPIDIV_DIV_MSK;
    }
  }

  info->mode  = mode;
  mmr->SPICON = (uint16_t)(con | SPICON_ENABLE | SPICON_CON | SPICON_TIM);
  mmr->SPIDIV = (uint16_t)div;

  info->state |= SPI_CONFIGURED;

  return (DRIVER_OK);
}

/**
 * @brief       Start transmit data.
 * @param[in]   data  Pointer to buffer for data
 * @param[in]   num   Number of data items to transmit
 * @return      Execution status
 */
static
int32_t SPI_Send(const void *data, uint32_t num, SPI_Resources_t *spi)
{
  MMR_SPI_t         *mmr  = spi->mmr;
  SPI_Info_t        *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_Irq_t         *irq  = spi->irq;
//  Driver_DMA_t      *dma = &Driver_DMA;
//  DMA_CHNL_CFG_t     dma_cfg;

  if ((data == NULL) || (num == 0U)) {
    return (DRIVER_ERROR_PARAMETER);
  }

  if ((info->state & SPI_CONFIGURED) == 0U) {
    return (DRIVER_ERROR);
  }

  if ((info->status.busy) != 0U) {
    return (DRIVER_ERROR_BUSY);
  }

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

  if (irq->dma_en) {
//    dma_cfg.dir               = DMA_DIR_PERIPH_DST;
//
//    dma_cfg.periph_addr       = (uint32_t)&mmr->SPITX;
//    dma_cfg.periph_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.periph_inc        = DMA_INC_DISABLE;
//
//    dma_cfg.memory_addr       = (uint32_t)xfer->tx_buf;
//    dma_cfg.memory_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.memory_inc        = DMA_INC_HALF_WORD;
//
//    dma_cfg.buffer_size       = (xfer->num / 2) + (xfer->num % 2);
//    dma_cfg.priority          = DMA_PRIORITY_DEFAULT;
//    dma_cfg.mode              = DMA_MODE_BASIC;
//
//    dma->ChannelConfig(irq->dma_tx_num - DMA_SPI0_TX_IRQn, &dma_cfg);
//    dma->ChannelEnable(irq->dma_tx_num - DMA_SPI0_TX_IRQn);
//
//    mmr->SPICNT = xfer->num;
//    mmr->SPICON &= ~SPICON_TFLUSH;
//    mmr->SPICON |=  SPICON_RFLUSH;
//
//    mmr->SPIDMA |=  SPI_DMA_IENTXDMA | SPI_DMA_ENABLE;
  }
  else {
    xfer->tx_cnt++;
    mmr->SPITX = (uint8_t)(*xfer->tx_buf++);
  }

  return (DRIVER_OK);
}

/**
 * @brief      Start receive data.
 * @param[out] data  Pointer to buffer for data
 * @param[in]  num   Number of data items to receive
 * @return     Execution status
 */
static
int32_t SPI_Receive(void *data, uint32_t num, SPI_Resources_t *spi)
{
  MMR_SPI_t         *mmr  = spi->mmr;
  SPI_Info_t        *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_Irq_t         *irq  = spi->irq;
//  Driver_DMA_t      *dma = &Driver_DMA;
//  DMA_CHNL_CFG_t     dma_cfg;

  if ((data == NULL) || (num == 0U)) {
    return (DRIVER_ERROR_PARAMETER);
  }

  if ((info->state & SPI_CONFIGURED) == 0U) {
    return (DRIVER_ERROR);
  }

  if ((info->status.busy) != 0U) {
    return (DRIVER_ERROR_BUSY);
  }

  // Update SPI statuses
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;
  info->status.mode_fault = 0U;

  // Save transfer info
  xfer->rx_buf = (uint8_t *)data;
  xfer->tx_buf = NULL;
  xfer->num    = num;
  xfer->rx_cnt = 0U;
  xfer->tx_cnt = 0U;

  if (irq->dma_en) {
    // Tx DMA
//    dma_cfg.dir               = DMA_DIR_PERIPH_DST;
//
//    dma_cfg.periph_addr       = (uint32_t)&mmr->SPITX;
//    dma_cfg.periph_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.periph_inc        = DMA_INC_DISABLE;
//
//    dma_cfg.memory_addr       = (uint32_t)&xfer->def_val;
//    dma_cfg.memory_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.memory_inc        = DMA_INC_DISABLE;
//
//    dma_cfg.buffer_size       = (xfer->num / 2) + (xfer->num % 2);
//    dma_cfg.priority          = DMA_PRIORITY_DEFAULT;
//    dma_cfg.mode              = DMA_MODE_BASIC;
//
//    dma->ChannelConfig(irq->dma_tx_num - DMA_SPI0_TX_IRQn, &dma_cfg);
//    dma->ChannelEnable(irq->dma_tx_num - DMA_SPI0_TX_IRQn);
//
//    //Rx DMA
//    dma_cfg.dir               = DMA_DIR_PERIPH_SRC;
//
//    dma_cfg.periph_addr       = (uint32_t)&mmr->SPIRX;
//    dma_cfg.periph_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.periph_inc        = DMA_INC_DISABLE;
//
//    dma_cfg.memory_addr       = (uint32_t)xfer->rx_buf;
//    dma_cfg.memory_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.memory_inc        = DMA_INC_HALF_WORD;
//
//    dma_cfg.buffer_size       = (xfer->num / 2) + (xfer->num % 2);
//    dma_cfg.priority          = DMA_PRIORITY_DEFAULT;
//    dma_cfg.mode              = DMA_MODE_BASIC;
//
//    dma->ChannelConfig(irq->dma_rx_num - DMA_SPI0_TX_IRQn, &dma_cfg);
//    dma->ChannelEnable(irq->dma_rx_num - DMA_SPI0_TX_IRQn);
//    // ------
//
//    mmr->SPICNT = xfer->num;
//    mmr->SPICON &= ~SPICON_TFLUSH;
//    mmr->SPICON &= ~SPICON_RFLUSH;
//
//    mmr->SPIDMA |=  SPI_DMA_IENTXDMA | SPI_DMA_ENABLE;
  }
  else {
    xfer->tx_cnt++;
    mmr->SPITX = (uint8_t)xfer->def_val;
  }

  return (DRIVER_OK);
}

/**
 * @brief       Start transfer data.
 * @param[out]  data_out  Pointer to buffer for data to transmit
 * @param[in]   data_in   Pointer to buffer for data to receive
 * @param[in]   num   Number of data items to transfer
 * @return      Execution status
 */
static
int32_t SPI_Transfer(const void *data_out, void *data_in, uint32_t num, SPI_Resources_t *spi)
{
  MMR_SPI_t         *mmr  = spi->mmr;
  SPI_Info_t        *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;
  SPI_Irq_t         *irq  = spi->irq;
//  Driver_DMA_t      *dma = &Driver_DMA;
//  DMA_CHNL_CFG_t     dma_cfg;

  if ((data_out == NULL) || (data_in == NULL) || (num == 0U)) {
    return (DRIVER_ERROR_PARAMETER);
  }

  if ((info->state & SPI_CONFIGURED) == 0U) {
    return (DRIVER_ERROR);
  }

  if ((info->status.busy) != 0U) {
    return (DRIVER_ERROR_BUSY);
  }

  /* Update SPI statuses */
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;
  info->status.mode_fault = 0U;

  /* Save transfer info */
  xfer->tx_buf = (uint8_t *)data_out;
  xfer->rx_buf = (uint8_t *)data_in;
  xfer->num    = num;
  xfer->rx_cnt = 0U;
  xfer->tx_cnt = 0U;

  if (irq->dma_en) {
    // Tx DMA
//    dma_cfg.dir               = DMA_DIR_PERIPH_DST;
//
//    dma_cfg.periph_addr       = (uint32_t)&mmr->SPITX;
//    dma_cfg.periph_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.periph_inc        = DMA_INC_DISABLE;
//
//    dma_cfg.memory_addr       = (uint32_t)xfer->tx_buf;
//    dma_cfg.memory_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.memory_inc        = DMA_INC_HALF_WORD;
//
//    dma_cfg.buffer_size       = (xfer->num / 2) + (xfer->num % 2);
//    dma_cfg.priority          = DMA_PRIORITY_DEFAULT;
//    dma_cfg.mode              = DMA_MODE_BASIC;
//
//    dma->ChannelConfig(irq->dma_tx_num - DMA_SPI0_TX_IRQn, &dma_cfg);
//    dma->ChannelEnable(irq->dma_tx_num - DMA_SPI0_TX_IRQn);
//
//    //Rx DMA
//    dma_cfg.dir               = DMA_DIR_PERIPH_SRC;
//
//    dma_cfg.periph_addr       = (uint32_t)&mmr->SPIRX;
//    dma_cfg.periph_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.periph_inc        = DMA_INC_DISABLE;
//
//    dma_cfg.memory_addr       = (uint32_t)xfer->rx_buf;
//    dma_cfg.memory_data_size  = DMA_DATA_SIZE_HALF_WORD;
//    dma_cfg.memory_inc        = DMA_INC_HALF_WORD;
//
//    dma_cfg.buffer_size       = (xfer->num / 2) + (xfer->num % 2);
//    dma_cfg.priority          = DMA_PRIORITY_DEFAULT;
//    dma_cfg.mode              = DMA_MODE_BASIC;
//
//    dma->ChannelConfig(irq->dma_rx_num - DMA_SPI0_TX_IRQn, &dma_cfg);
//    dma->ChannelEnable(irq->dma_rx_num - DMA_SPI0_TX_IRQn);
//    // ------
//
//    mmr->SPICNT = xfer->num;
//    mmr->SPICON &= ~SPICON_TFLUSH;
//    mmr->SPICON &= ~SPICON_RFLUSH;
//
//    mmr->SPIDMA |=  SPI_DMA_IENRXDMA | SPI_DMA_IENTXDMA | SPI_DMA_ENABLE;
  }
  else {
    xfer->tx_cnt++;
    mmr->SPITX = (uint8_t)(*xfer->tx_buf++);
  }

  return (DRIVER_OK);
}

/**
 * @brief       Get transfered data count.
 * @return      Number of data items transfered
 */
static
uint32_t SPI_GetDataCount(SPI_Resources_t *spi)
{
  return (spi->xfer->rx_cnt);
}

/**
 * @brief       Get SPI status.
 * @return      SPI status
 */
static
SPI_STATUS SPI_GetStatus(SPI_Resources_t *spi)
{
  return (spi->info->status);
}

/**
 * @brief       SPI DMA Interrupt handler.
 */
static
void DMA_SPI_TX_IRQHandler(SPI_Resources_t *spi)
{
  MMR_SPI_t         *mmr  = spi->mmr;
  mmr->SPIDMA = 0U;

  SPI_Info_t        *info = spi->info;
  SPI_Irq_t         *irq  = spi->irq;
//  Driver_DMA_t      *dma = &Driver_DMA;

  uint32_t event = 0;

  if ((irq->dma_en) == 0U) {
    return;
  }

//  if ((dma->GetChannelStatus(irq->dma_tx_num - DMA_SPI0_TX_IRQn) & DMA_CHNL_CFG_CYCLE_CTRL_Msk) != DMA_CHNL_CFG_CYCLE_CTRL_STOP) {
//    return;
//  }

  info->status.busy = 0U;
  event |= SPI_EVENT_TRANSFER_COMPLETE;

  /* Send event */
  if ((event != 0U) && ((info->cb_event != NULL))) {
    info->cb_event(event);
  }
}

static
void DMA_SPI_RX_IRQHandler(SPI_Resources_t *spi)
{
  MMR_SPI_t         *mmr  = spi->mmr;

  mmr->SPIDMA = 0U;
}

/**
 * @brief       SPI Interrupt handler.
 */
static
void SPI_IRQHandler(SPI_Resources_t *spi)
{
  register uint8_t  data;
  register uint32_t num;
  register uint32_t sta;
  register uint32_t event;

  MMR_SPI_t         *mmr  = spi->mmr;
  SPI_Info_t        *info = spi->info;
  SPI_TRANSFER_INFO *xfer = spi->xfer;

  event = 0;
  sta = mmr->SPISTA;

  if ((sta & SPISTA_RXOF) != 0U) {
    info->status.data_lost = 1U;
    event |= SPI_EVENT_DATA_LOST;
  }

  if ((sta & (SPISTA_RX | SPISTA_TX)) != 0U) {
    if ((sta & SPISTA_TX) != 0U) {
      if (xfer->tx_cnt == xfer->num) {
        mmr->SPICON &= (uint16_t)~SPICON_TIM;
      }
      else {
        if (xfer->tx_buf != NULL) {
          data = *xfer->tx_buf++;
        }
        else {
          data = (uint8_t)xfer->def_val;
        }
        mmr->SPITX = data;
        xfer->tx_cnt++;
      }
    }

    num = (sta & SPISTA_RXFSTA_MSK) >> 8;
    while (num--) {
      if (xfer->rx_cnt == (xfer->num - 1U)) {
        mmr->SPICON |= (uint16_t)SPICON_TIM;
        info->status.busy = 0U;
        event |= SPI_EVENT_TRANSFER_COMPLETE;
      }
      data = (uint8_t)mmr->SPIRX;
      if (xfer->rx_buf != NULL) {
        *xfer->rx_buf++ = data;
      }
      xfer->rx_cnt++;
    }
  }

  /* Send event */
  if (info->cb_event != NULL && event != 0U) {
    info->cb_event(event);
  }
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_SPI0)
  SPIx_EXPORT_DRIVER(0);
#endif  /* USE_SPI0 */

#if defined(USE_SPI1)
  SPIx_EXPORT_DRIVER(1);
#endif  /* USE_SPI1 */

#endif /* defined(USE_SPI0) || defined(USE_SPI1) */
