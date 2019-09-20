/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver for STMicroelectronics STM32F7xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <string.h>
#include "I2C_STM32F7xx.h"

#if defined(USE_I2C1) || defined(USE_I2C2) || defined(USE_I2C3) || \
    defined(USE_I2C4)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define T_I2CCLK              125UL // tI2CCLK = 125 ns
#define STD_MODE_SCLL         40UL  // 40*tI2CCLK = 5000 ns
#define STD_MODE_SCLH         32UL  // 32*tI2CCLK = 4000 ns
#define STD_MODE_SDADEL       4UL   // 4*tI2CCLK = 500 ns
#define STD_MODE_SCLDEL       10UL  // 10*tI2CCLK = 1250 ns
#define FST_MODE_SCLL         10UL  // 10*tI2CCLK = 1250 ns
#define FST_MODE_SCLH         4UL   // 4*tI2CCLK = 500 ns
#define FST_MODE_SDADEL       1UL   // 1*tI2CCLK = 125 ns
#define FST_MODE_SCLDEL       4UL   // 4*tI2CCLK = 500 ns

#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

#ifdef I2C_DMA_TX
static void I2Cx_TX_DMA_Callback(uint32_t event, const void *param);
#endif

#ifdef I2C_DMA_RX
static void I2Cx_RX_DMA_Callback(uint32_t event, const void *param);
#endif

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_I2C_API_VERSION,
  ARM_I2C_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_I2C_CAPABILITIES DriverCapabilities = {
  0,           /* supports 10-bit addressing */
};

static const GPIO_PIN_CFG_t I2C_pin_cfg_af = {
    GPIO_MODE_AF_OD, GPIO_PULL_DISABLE, GPIO_SPEED_HIGH
};

static const GPIO_PIN_CFG_t I2C_pin_cfg_analog = {
    GPIO_MODE_ANALOG, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

#if defined(USE_I2C1)
/* I2C1 Information (Run-Time) */
static I2C_INFO      I2C1_Info;
static I2C_RESOURCES I2C1_Resources;

static I2C_PIN I2C1_scl = {
    I2C1_SCL_GPIO_PORT, I2C1_SCL_GPIO_PIN, I2C1_SCL_GPIO_FUNC
};
static I2C_PIN I2C1_sda = {
    I2C1_SDA_GPIO_PORT, I2C1_SDA_GPIO_PIN, I2C1_SDA_GPIO_FUNC
};

#ifdef I2C1_TX_DMA_Stream
static DMA_Handle_t I2C1_TX_DMA_Handle;
static const DMA_Resources_t I2C1_TX_DMA = {
  &I2C1_TX_DMA_Handle,
  I2C1_TX_DMA_Stream,
  I2C1_TX_DMA_Channel,
  I2C1_TX_DMA_Priority,
  I2Cx_TX_DMA_Callback,
  &I2C1_Resources,
  DEV_I2C_DMA_INT_PRIORITY,
  I2C1_TX_DMA_IRQn,
};
#endif

#ifdef I2C1_RX_DMA_Stream
static DMA_Handle_t I2C1_RX_DMA_Handle;
static const DMA_Resources_t I2C1_RX_DMA = {
  &I2C1_RX_DMA_Handle,
  I2C1_RX_DMA_Stream,
  I2C1_RX_DMA_Channel,
  I2C1_RX_DMA_Priority,
  I2Cx_RX_DMA_Callback,
  &I2C1_Resources,
  DEV_I2C_DMA_INT_PRIORITY,
  I2C1_RX_DMA_IRQn,
};
#endif

/* I2C1 Resources */
static I2C_RESOURCES I2C1_Resources = {
  I2C1,
#ifdef I2C1_RX_DMA_Stream
  &I2C1_RX_DMA,
#else
  NULL,
#endif
#ifdef I2C1_TX_DMA_Stream
  &I2C1_TX_DMA,
#else
  NULL,
#endif
  {
      &I2C1_scl,
      &I2C1_sda,
  },
  RCC_PERIPH_I2C1,
  &I2C1_Info,
  I2C1_EV_IRQn,
  I2C1_ER_IRQn,
};
#endif /* USE_I2C1 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          void PinConfig(const I2C_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
 * @brief       Configure Pin
 * @param[in]   io       Pointer to I2C_PIN
 * @param[in]   pin_cfg  Pointer to GPIO_PIN_CFG_t
 */
static
void PinConfig(const I2C_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
{
  if ((io == NULL) || (pin_cfg == NULL))
    return;

  if (GPIO_GetPortClockState(io->port) == false)
    GPIO_PortClock(io->port, GPIO_PORT_CLK_ENABLE);

  if (pin_cfg->mode == GPIO_MODE_AF_PP || pin_cfg->mode == GPIO_MODE_AF_OD)
    GPIO_AFConfig(io->port, io->pin, io->func);

  GPIO_PinConfig(io->port, io->pin, pin_cfg);
}

static
uint32_t GetI2CCLK(I2C_RESOURCES *i2c)
{
//  uint32_t clk = 0;
//  RCC_FREQ_t freq_type = RCC_FREQ_PCLK;
//
//  if (i2c->reg == I2C1) {
//    if ((RCC->CFGR3 & RCC_CFGR3_I2C1SW) != 0)
//      freq_type = RCC_FREQ_SYSCLK;
//    else
//      freq_type = RCC_FREQ_HSI;
//  }
//
//  clk = RCC_GetFreq(freq_type) / 1000000;
//
//  return clk;
}

/**
 * @fn      ARM_DRIVER_VERSION I2C_GetVersion(void)
 * @brief   Get driver version.
 * @return  \ref ARM_DRIVER_VERSION
 */
static
ARM_DRIVER_VERSION I2Cx_GetVersion(void)
{
  return (DriverVersion);
}

/**
 * @fn      ARM_I2C_CAPABILITIES I2C_GetCapabilities(void)
 * @brief   Get driver capabilities.
 * @return  \ref ARM_I2C_CAPABILITIES
 */
static
ARM_I2C_CAPABILITIES I2Cx_GetCapabilities(void)
{
  return (DriverCapabilities);
}

/**
 * @fn          int32_t I2C_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_RESOURCES *i2c)
 * @brief       Initialize I2C Interface.
 * @param[in]   cb_event  Pointer to \ref ARM_I2C_SignalEvent
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_RESOURCES *i2c)
{
  I2C_IO *io = &i2c->io;
  I2C_INFO *info = i2c->info;

  if (info->flags & I2C_INIT) {
    return (ARM_DRIVER_OK);
  }

  /* Configure SCL Pin */
  PinConfig(io->scl, &I2C_pin_cfg_af);
  /* Configure SDA Pin */
  PinConfig(io->sda, &I2C_pin_cfg_af);

  /* Initialize DMA */
#ifdef I2C_DMA_TX
  if (i2c->dma_tx != NULL) {
    DMA_StreamConfig_t *cfg = &i2c->dma_tx->handle->config;

    cfg->Direction    = DMA_DIR_MEM_TO_PER;
    cfg->PerInc       = DMA_PINC_DISABLE;
    cfg->MemInc       = DMA_MINC_ENABLE;
    cfg->PerDataAlign = DMA_PDATAALIGN_BYTE;
    cfg->MemDataAlign = DMA_MDATAALIGN_BYTE;
    cfg->Mode         = DMA_MODE_NORMAL;
    cfg->FIFOMode     = DMA_FIFOMODE_DISABLE;
    cfg->MemBurst     = DMA_MBURST_SINGLE;
    cfg->PerBurst     = DMA_PBURST_SINGLE;

    DMA_Initialize(i2c->dma_tx);
  }
#endif

#ifdef I2C_DMA_RX
  if (i2c->dma_rx != NULL) {
    DMA_StreamConfig_t *cfg = &i2c->dma_rx->handle->config;

    cfg->Direction    = DMA_DIR_PER_TO_MEM;
    cfg->PerInc       = DMA_PINC_DISABLE;
    cfg->MemInc       = DMA_MINC_ENABLE;
    cfg->PerDataAlign = DMA_PDATAALIGN_BYTE;
    cfg->MemDataAlign = DMA_MDATAALIGN_BYTE;
    cfg->Mode         = DMA_MODE_NORMAL;
    cfg->FIFOMode     = DMA_FIFOMODE_DISABLE;
    cfg->MemBurst     = DMA_MBURST_SINGLE;
    cfg->PerBurst     = DMA_PBURST_SINGLE;

    DMA_Initialize(i2c->dma_rx);
  }
#endif

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2C_INFO));

  info->cb_event = cb_event;
  info->flags    = I2C_INIT;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2C_Uninitialize(I2C_RESOURCES *i2c)
 * @brief       De-initialize I2C Interface.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_Uninitialize(I2C_RESOURCES *i2c)
{
  I2C_IO *io = &i2c->io;

  /* Unconfigure SCL Pin */
  PinConfig(io->scl, &I2C_pin_cfg_analog);
  /* Unconfigure SDA Pin */
  PinConfig(io->sda, &I2C_pin_cfg_analog);

  i2c->info->flags = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2C_PowerControl(ARM_POWER_STATE state, I2C_RESOURCES *i2c)
 * @brief       Control I2C Interface Power.
 * @param[in]   state   Power state
 * @param[in]   i2c     Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_PowerControl(ARM_POWER_STATE state, I2C_RESOURCES *i2c)
{
  uint32_t cr1;
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  switch (state) {
    case ARM_POWER_OFF:
      /* Enable I2C clock */
      RCC_EnablePeriph(i2c->rcc);

      /* Disable I2C peripheral */
      reg->CR1 = 0;

      /* Disable I2C IRQ */
      NVIC_DisableIRQ(i2c->ev_irq_num);
      NVIC_DisableIRQ(i2c->er_irq_num);

      /* Abort DMA streams */
#ifdef I2C_DMA_TX
      if (i2c->dma_tx != NULL) {
        DMA_Abort(i2c->dma_tx);
        DMA_WaitAbort(i2c->dma_tx);
        DMA_Uninitialize(i2c->dma_tx);
      }
#endif

#ifdef I2C_DMA_RX
      if (i2c->dma_rx != NULL) {
        DMA_Abort(i2c->dma_rx);
        DMA_WaitAbort(i2c->dma_rx);
        DMA_Uninitialize(i2c->dma_rx);
      }
#endif

      /* Disable peripheral clock */
      RCC_DisablePeriph(i2c->rcc);

      info->status.busy             = 0U;
      info->status.mode             = 0U;
      info->status.direction        = 0U;
      info->status.general_call     = 0U;
      info->status.arbitration_lost = 0U;
      info->status.bus_error        = 0U;

      info->flags &= ~I2C_POWER;
      break;

    case ARM_POWER_FULL:
      if ((info->flags & I2C_INIT) == 0U) {
        return (ARM_DRIVER_ERROR);
      }

      if ((info->flags & I2C_POWER) != 0U) {
        return (ARM_DRIVER_OK);
      }

      /* Enable I2C clock */
      RCC_EnablePeriph(i2c->rcc);

      /* Clear and Enable I2C IRQ */
      NVIC_ClearPendingIRQ(i2c->ev_irq_num);
      NVIC_ClearPendingIRQ(i2c->er_irq_num);
      NVIC_SetPriority(i2c->ev_irq_num, DEV_I2C_INT_PRIORITY);
      NVIC_SetPriority(i2c->er_irq_num, DEV_I2C_INT_PRIORITY);
      NVIC_EnableIRQ(i2c->ev_irq_num);
      NVIC_EnableIRQ(i2c->er_irq_num);

      /* Reset the peripheral */
      RCC_ResetPeriph(i2c->rcc);

      /* Initial peripheral setup */
      cr1 = I2C_CR1_SBC    | /* Slave byte control enabled          */
            I2C_CR1_ERRIE  | /* Error interrupts enabled            */
            I2C_CR1_TCIE   | /* Transfer complete interrupt enabled */
            I2C_CR1_STOPIE | /* STOP detection interrupt enabled    */
            I2C_CR1_NACKIE | /* NACK interrupt enabled              */
            I2C_CR1_ADDRIE ; /* Address match interrupt enabled     */

      /* Enable IRQ/DMA rx/tx requests */
      if (i2c->dma_rx == NULL) {
        cr1 |= I2C_CR1_RXIE;
      }
      else {
        cr1 |= I2C_CR1_RXDMAEN;
      }

      if (i2c->dma_tx == NULL) {
        cr1 |= I2C_CR1_TXIE;
      }
      else {
        cr1 |= I2C_CR1_TXDMAEN;
      }

      /* Apply setup and enable peripheral */
      reg->CR1 = cr1 | I2C_CR1_PE;

      /* Ready for operation */
      info->flags |= I2C_POWER;
      break;

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @brief       Control I2C Interface.
 * @param[in]   control   Operation
 * @param[in]   arg   Argument of operation (optional)
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_Control(uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  if ((info->flags & I2C_POWER) == 0U) {
    /* I2C not powered */
    return ARM_DRIVER_ERROR;
  }

  switch (control) {
    case ARM_I2C_OWN_ADDRESS:
      if (arg == 0) {
        /* Disable slave */
        reg->OAR1 = 0;
      }
      else {
        uint32_t val;

        if (arg & ARM_I2C_ADDRESS_GC) {
          /* Enable general call */
          reg->CR1 |=  I2C_CR1_GCEN;
        } else {
          /* Disable general call */
          reg->CR1 &= ~I2C_CR1_GCEN;
        }

        if (arg & ARM_I2C_ADDRESS_10BIT) {
          val = (arg & 0x3FF ) | I2C_OAR1_OA1MODE;
        } else {
          val = (arg & 0x7F) << 1;
        }

        reg->OAR1 = val | I2C_OAR1_OA1EN;
      }
      break;

    case ARM_I2C_BUS_SPEED:
    {
      uint32_t timing = 0;
      uint32_t i2cclk = GetI2CCLK(i2c);
      int32_t presc = ((T_I2CCLK * i2cclk / 1000) - 1);

      if (presc < 0)
        return ARM_DRIVER_ERROR_UNSUPPORTED;

      switch (arg) {
      case ARM_I2C_BUS_SPEED_STANDARD:
        timing = ((presc << 28) | ((STD_MODE_SCLDEL-1) << 20) |
            (STD_MODE_SDADEL << 16) | ((STD_MODE_SCLH-1) << 8) | (STD_MODE_SCLL-1));
        break;
      case ARM_I2C_BUS_SPEED_FAST:
        timing = ((presc << 28) | ((FST_MODE_SCLDEL-1) << 20) |
            (FST_MODE_SDADEL << 16) | ((FST_MODE_SCLH-1) << 8) | (FST_MODE_SCLL-1));
        break;
      default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
      }

      reg->CR1 &= ~I2C_CR1_PE;
      reg->TIMINGR = timing;
      reg->CR1 |= I2C_CR1_PE;

      /* Master configured, clock set */
      info->flags |= I2C_SETUP;
    }
    break;

    case ARM_I2C_BUS_CLEAR:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    case ARM_I2C_ABORT_TRANSFER:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/**
 * @brief       Start transmitting data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[in]   data          Pointer to buffer with data to transmit to I2C Slave
 * @param[in]   num           Number of data bytes to transmit
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_RESOURCES *i2c)
{
  uint32_t cr2, cnt;
  bool restart;
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(info->flags & I2C_SETUP)) {
    /* Driver not yet configured */
    return ARM_DRIVER_ERROR;
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  restart = (info->xfer.ctrl & XFER_CTRL_RESTART) != 0U;

  if (!restart) {
    /* New transfer */
    while (i2c_reg->ISR & I2C_ISR_BUSY) {
      ; /* Wait until bus released */
    }
  }

  info->status.busy             = 1U;
  info->status.mode             = 1U;
  info->status.direction        = 0U;
  info->status.bus_error        = 0U;
  info->status.arbitration_lost = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = 0;
  info->xfer.data = (uint8_t *)data;
  info->xfer.ctrl = 0U;

  if (xfer_pending) {
    info->xfer.ctrl = XFER_CTRL_RESTART;
  }

  /* Set slave address and transfer direction */
  if (addr & ARM_I2C_ADDRESS_10BIT) {
    cr2 = (addr & 0x3FF) | I2C_CR2_ADD10;
  }
  else {
    cr2 = (addr & 0x7F) << 1;
  }

  /* Set number of bytes to transfer */
  if (num < 256) {
    cnt = num;
    /* Send all data bytes and enable automatic STOP */
    if (!xfer_pending && !restart) {
      cr2 |= I2C_CR2_AUTOEND;
    }
  }
  else {
    cnt = 255;
    /* Send 255 data bytes and enable NBYTES reload */
    cr2 |= I2C_CR2_RELOAD;
  }

  /* Apply transfer setup */
  i2c_reg->CR2 = (cnt << 16) | cr2;

  /* Generate start */
  i2c_reg->CR2 |= I2C_CR2_START;
  /* Enable transfer complete interrupt */
  i2c_reg->CR1 |= I2C_CR1_TCIE;

  return ARM_DRIVER_OK;
}

/**
 * @brief                     Start receiving data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[out]  data          Pointer to buffer for data to receive from I2C Slave
 * @param[in]   num           Number of data bytes to receive
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return                    \ref execution_status
 */
static
int32_t I2C_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_RESOURCES *i2c)
{
  uint32_t cr2, cnt;
  bool restart;
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U))
    return ARM_DRIVER_ERROR_PARAMETER;

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU)
    return ARM_DRIVER_ERROR_PARAMETER;

  if (!(info->flags & I2C_SETUP)) {
    /* Driver not yet configured */
    return ARM_DRIVER_ERROR;
  }

  if (info->status.busy)
    return (ARM_DRIVER_ERROR_BUSY);

  restart = (info->xfer.ctrl & XFER_CTRL_RESTART) != 0U;

  if (!restart) {
    /* New transfer */
    while (i2c_reg->ISR & I2C_ISR_BUSY) {
      ; /* Wait until bus released */
    }
  }

  info->status.busy             = 1U;
  info->status.mode             = 1U;
  info->status.direction        = 1U;
  info->status.bus_error        = 0U;
  info->status.arbitration_lost = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = 0;
  info->xfer.data = (uint8_t *)data;
  info->xfer.ctrl = 0U;

  if (xfer_pending) {
    info->xfer.ctrl = XFER_CTRL_RESTART;
  }

  /* Set slave address and transfer direction */
  if ((addr & ARM_I2C_ADDRESS_10BIT) != 0) {
    cr2 = (addr & 0x3FF) | I2C_CR2_ADD10 | I2C_CR2_RD_WRN;
  }
  else {
    cr2 = ((addr & 0x7F) << 1) | I2C_CR2_RD_WRN;
  }

  /* Set number of bytes to transfer */
  if (num < 256) {
    cnt = num;
    /* Send all data bytes and enable automatic STOP */
    if (!xfer_pending && !restart) {
      cr2 |= I2C_CR2_AUTOEND;
    }
  }
  else {
    cnt = 255;
    /* Send 255 data bytes and enable NBYTES reload */
    cr2 |= I2C_CR2_RELOAD;
  }

  /* Apply transfer setup */
  i2c_reg->CR2 = (cnt << 16) | cr2;

  /* Generate start */
  i2c_reg->CR2 |= I2C_CR2_START;
  /* Enable transfer complete interrupt */
  i2c_reg->CR1 |= I2C_CR1_TCIE;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t I2Cx_SlaveTransmit (const uint8_t *data,
                                           uint32_t       num,
                                           I2C_RESOURCES *i2c)
  \brief       Start transmitting data as I2C Slave.
  \param[in]   data  Pointer to buffer with data to transmit to I2C Master
  \param[in]   num   Number of data bytes to transmit
  \param[in]   i2c   Pointer to I2C resources
  \return      \ref execution_status
*/
static
int32_t I2C_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status.bus_error    = 0U;
  info->status.general_call = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = -1;
  info->xfer.data = (uint8_t *)data;
  info->xfer.ctrl = 0U;

  /* Set number of bytes to transfer */
  if (num < 256) {
    i2c_reg->CR2 = (num << 16);
  }
  else {
    /* Send 255 data bytes and enable NBYTES reload */
    i2c_reg->CR2 = (255 << 16) | I2C_CR2_RELOAD;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t I2Cx_SlaveReceive (uint8_t       *data,
                                          uint32_t       num,
                                          I2C_RESOURCES *i2c)
  \brief       Start receiving data as I2C Slave.
  \param[out]  data  Pointer to buffer for data to receive from I2C Master
  \param[in]   num   Number of data bytes to receive
  \param[in]   i2c   Pointer to I2C resources
  \return      \ref execution_status
*/
static
int32_t I2C_SlaveReceive(uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status.bus_error    = 0U;
  info->status.general_call = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = -1;
  info->xfer.data = data;
  info->xfer.ctrl = 0U;

  /* Set number of bytes to transfer */
  if (num < 256) {
    i2c_reg->CR2 = (num << 16);
  }
  else {
    /* Send 255 data bytes and enable NBYTES reload */
    i2c_reg->CR2 = (255 << 16) | I2C_CR2_RELOAD;
  }

  return ARM_DRIVER_OK;
}

/**
 * @brief       Get transferred data count.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      Number of data bytes transferred;
 *              -1 when Slave is not addressed by Master
 */
static
int32_t I2C_GetDataCount(I2C_RESOURCES *i2c)
{
  return i2c->info->xfer.cnt;
}

/**
 * @brief       Get I2C status.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      I2C status \ref ARM_I2C_STATUS
 */
static
ARM_I2C_STATUS I2C_GetStatus(I2C_RESOURCES *i2c)
{
  return i2c->info->status;
}

/**
 * @brief       I2C Master state event handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_IRQHandler(I2C_RESOURCES *i2c)
{
  I2C_TRANSFER_INFO *xfer = &i2c->info->xfer;
  I2C_TypeDef *reg = i2c->reg;
  uint32_t isr = reg->ISR;

  if (isr & I2C_ISR_RXNE) {
    /* Receive data register not empty */
    xfer->data[xfer->cnt++] = reg->RXDR;
    return;
  }
  else if (isr & I2C_ISR_TXIS) {
    /* Transmit data register empty */
    reg->TXDR = xfer->data[xfer->cnt++];
    return;
  }

  uint32_t event = 0;
  I2C_INFO *info = i2c->info;

  if (isr & (I2C_ISR_TC | I2C_ISR_TCR)) {
    if (isr & I2C_ISR_TC) {
      /* Transfer Complete */
      info->status.busy = 0U;

      if (xfer->ctrl & XFER_CTRL_RESTART) {
        /* Wait for pending transfer */
        reg->CR1 &= ~I2C_CR1_TCIE;

        event = ARM_I2C_EVENT_TRANSFER_DONE;
      }
      else {
        /* Send stop */
        reg->CR2 |= I2C_CR2_STOP;
      }
    }
    else {  // if (isr & I2C_ISR_TCR)
      /* Transfer Complete Reload */
      uint32_t cr = reg->CR2;

      cr &= ~(I2C_CR2_RELOAD | I2C_CR2_NBYTES);

      uint32_t cnt = xfer->num - xfer->cnt;

      if (cnt < 256) {
        if ((xfer->ctrl & XFER_CTRL_RESTART) == 0) {
          cr |= I2C_CR2_AUTOEND;
        }
      }
      else {
        cnt = 255;
        cr |= I2C_CR2_RELOAD;
      }

      reg->CR2 = (cnt << 16) | cr;
    }
  }
  else if (isr & (I2C_ISR_STOPF | I2C_ISR_NACKF | I2C_ISR_ADDR | I2C_ISR_ARLO | I2C_ISR_BERR)) {
    uint32_t icr = 0;

    if (isr & I2C_ISR_STOPF) {
      /* Stop detection flag */
      icr |= I2C_ICR_STOPCF;

      if (xfer->ctrl & XFER_CTRL_ADDR_NACK) {
        /* Slave address not acknowledged */
        event = ARM_I2C_EVENT_TRANSFER_DONE | ARM_I2C_EVENT_ADDRESS_NACK;
      }
      else {
        event = ARM_I2C_EVENT_TRANSFER_DONE;

        if (xfer->cnt < xfer->num) {
          event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
        }

        if (info->status.general_call) {
          event |= ARM_I2C_EVENT_GENERAL_CALL;
        }
      }

      xfer->data = NULL;
      xfer->ctrl = 0U;

      info->status.busy = 0U;
      info->status.mode = 0U;
    }
    else if (isr & I2C_ISR_ADDR) {
      /* Address matched (slave mode) */
      icr |= I2C_ICR_ADDRCF;

      info->status.mode = 0U;

      if ((isr & I2C_ISR_ADDCODE) == 0) {
        /* General call */
        info->status.general_call = 1U;

        event = ARM_I2C_EVENT_GENERAL_CALL;
      }

      /* Set transfer direction */
      if ((isr & I2C_ISR_DIR) == 0U) {
        info->status.direction = 1U; /* Slave enters receiver mode */

        event |= ARM_I2C_EVENT_SLAVE_RECEIVE;
      }
      else {
        info->status.direction = 0U; /* Slave enters transmitter mode */

        event |= ARM_I2C_EVENT_SLAVE_TRANSMIT;
      }

      if ((xfer->data == NULL) || (info->status.general_call != 0U)) {
        if (info->cb_event != NULL) {
          info->cb_event(event);
        }
        event = 0U;
      }

      info->status.busy  = 1U;
      xfer->cnt = 0;
      xfer->ctrl |= XFER_CTRL_ADDR_DONE;
    }
    else if (isr & I2C_ISR_NACKF) {
      /* NACK received */
      icr |= I2C_ICR_NACKCF;

      /* Master sends STOP after slave NACK */
      /* Slave already released the lines   */
      if (info->status.mode) {
        if (xfer->cnt == 0) {
          xfer->ctrl |= XFER_CTRL_ADDR_NACK;
        }
        else {
          xfer->cnt--;

          if ((isr & I2C_ISR_TXE) == 0U) {
            reg->ISR = I2C_ISR_TXE;
            xfer->cnt--;
          }
        }
      }
    }
    else if (isr & I2C_ISR_ARLO) {
      /* Arbitration lost */
      icr |= I2C_ICR_ARLOCF;

      /* Switch to slave mode */
      info->status.busy             = 0U;
      info->status.mode             = 0U;
      info->status.arbitration_lost = 1U;

      xfer->data = NULL;
      xfer->ctrl = 0U;

      event = ARM_I2C_EVENT_TRANSFER_DONE | ARM_I2C_EVENT_ARBITRATION_LOST;
    }
    else if (isr & I2C_ISR_BERR) {
      /* Bus error (misplaced start/stop) */
      icr |= I2C_ICR_BERRCF;

      info->status.bus_error = 1U;

      if (info->status.mode == 0U) {
        /* Lines are released in slave mode */
        info->status.busy = 0U;

        xfer->data = NULL;
        xfer->ctrl = 0U;
      }

      event = ARM_I2C_EVENT_TRANSFER_DONE | ARM_I2C_EVENT_BUS_ERROR;
    }

    /* Clear status flags */
    reg->ICR = icr;
  }

  /* Send events */
  if ((event) && (info->cb_event)) {
    info->cb_event(event);
  }
}

#ifdef I2C_DMA_RX
static void I2Cx_RX_DMA_Callback(uint32_t event, const void *param)
{

}
#endif

#ifdef I2C_DMA_TX
static void I2Cx_TX_DMA_Callback(uint32_t event, const void *param)
{

}
#endif

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_I2C1)
  I2Cx_EXPORT_DRIVER(1);
#endif  /* USE_I2C1 */

#endif /* defined(USE_I2C1) || defined(USE_I2C2) || defined(USE_I2C3) ...     */

/* ----------------------------- End of file ---------------------------------*/
