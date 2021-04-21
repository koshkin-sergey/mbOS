/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver for ADI ADUC7023
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <string.h>

#include "I2C_ADUC7023.h"

#if defined(USE_I2C0) || defined(USE_I2C0)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

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

static const GPIO_PIN_CFG_t out_pin_cfg = {
    GPIO_PIN_FUNC_0, GPIO_MODE_OUTPUT, GPIO_PULL_DISABLE, GPIO_STRENGTH_MEDIUM
};

static const GPIO_PIN_CFG_t in_pin_cfg = {
    GPIO_PIN_FUNC_0, GPIO_MODE_INPUT, GPIO_PULL_DISABLE, GPIO_STRENGTH_MEDIUM
};

#if defined(USE_I2C0)
/* I2C0 Information (Run-Time) */
static I2C_INFO      I2C0_Info;
static I2C_RESOURCES I2C0_Resources;

static I2C_PIN I2C0_scl = {
    I2C0_SCL_GPIO_PORT, I2C0_SCL_GPIO_PIN, I2C0_SCL_GPIO_FUNC
};
static I2C_PIN I2C0_sda = {
    I2C0_SDA_GPIO_PORT, I2C0_SDA_GPIO_PIN, I2C0_SDA_GPIO_FUNC
};

/* I2C0 Resources */
static I2C_RESOURCES I2C0_Resources = {
  I2C0,
  {
    &I2C0_scl,
    &I2C0_sda,
  },
  &I2C0_Info,
  I2C0_MASTER_IRQn,
  I2C0_SLAVE_IRQn,
};
#endif /* USE_I2C0 */

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

/* I2C1 Resources */
static I2C_RESOURCES I2C1_Resources = {
  I2C1,
  {
    &I2C1_scl,
    &I2C1_sda,
  },
  &I2C1_Info,
  I2C1_MASTER_IRQn,
  I2C1_SLAVE_IRQn,
};
#endif /* USE_I2C1 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

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
  GPIO_PIN_CFG_t pin_cfg;

  if (info->flags & I2C_INIT) {
    return (ARM_DRIVER_OK);
  }

  pin_cfg = in_pin_cfg;

  /* Configure SCL Pin */
  pin_cfg.func = io->scl->func;
  io->scl->gpio->PinConfig(io->scl->pin, &pin_cfg);
  /* Configure SDA Pin */
  pin_cfg.func = io->sda->func;
  io->sda->gpio->PinConfig(io->sda->pin, &pin_cfg);

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
  io->scl->gpio->PinConfig(io->scl->pin, &in_pin_cfg);
  /* Unconfigure SDA Pin */
  io->sda->gpio->PinConfig(io->sda->pin, &in_pin_cfg);

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
  uint32_t  cr1;
  I2C_INFO *info = i2c->info;
  I2C_t    *reg  = i2c->reg;

  switch (state) {
    case ARM_POWER_OFF:
      /* Disable I2C peripheral */

      /* Disable I2C IRQ */

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

      /* Clear and Enable I2C IRQ */

      /* Initial peripheral setup */

      /* Enable IRQ/DMA rx/tx requests */

      /* Apply setup and enable peripheral */

      /* Ready for operation */
      info->flags |= I2C_POWER;
      break;

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2C_MasterTransmit(uint32_t addr,
 *                                         const uint8_t *data,
 *                                         uint32_t num,
 *                                         bool xfer_pending,
 *                                         I2C_RESOURCES *i2c)
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
  bool      restart;
  I2C_INFO *info    = i2c->info;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~((uint32_t)ARM_I2C_ADDRESS_10BIT | (uint32_t)ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if (!(info->flags & I2C_SETUP)) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  restart = (info->xfer.ctrl & XFER_CTRL_RESTART) != 0U;

  if (!restart) {
    /* New transfer */
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

  /* Set number of bytes to transfer */

  /* Apply transfer setup */

  /* Generate start */

  /* Enable transfer complete interrupt */

  return (ARM_DRIVER_OK);
}

/**
 * @fn                        int32_t I2C_MasterReceive(uint32_t addr,
 *                                                      uint8_t *data,
 *                                                      uint32_t num,
 *                                                      bool xfer_pending,
 *                                                      I2C_RESOURCES *i2c)
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
  bool restart;
  I2C_INFO *info = i2c->info;
  I2C_t *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if (!(info->flags & I2C_SETUP)) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  restart = (info->xfer.ctrl & XFER_CTRL_RESTART) != 0U;

  if (!restart) {
    /* New transfer */
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

  /* Set number of bytes to transfer */

  /* Apply transfer setup */

  /* Generate start */

  /* Enable transfer complete interrupt */

  return (ARM_DRIVER_OK);
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
  I2C_INFO *info    = i2c->info;
  I2C_t    *i2c_reg = i2c->reg;

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

  return (ARM_DRIVER_OK);
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

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
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
  i2c->reg->CR2 = (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_RELOAD; /* Send 1 byte and enable NBYTES reload */

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2C_GetDataCount(I2C_RESOURCES *i2c)
 * @brief       Get transferred data count.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      Number of data bytes transferred;
 *              -1 when Slave is not addressed by Master
 */
static
int32_t I2C_GetDataCount(I2C_RESOURCES *i2c)
{
  return (i2c->info->xfer.cnt);
}

/**
 * @fn          int32_t I2C_Control(uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
 * @brief       Control I2C Interface.
 * @param[in]   control   Operation
 * @param[in]   arg   Argument of operation (optional)
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_Control(uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
{
  I2C_INFO    *info = i2c->info;
  I2C_TypeDef *reg  = i2c->reg;
  uint32_t     val;

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
      uint32_t i2cclk = RCC_GetPeriphFreq(i2c->rcc)/1000000;
      int32_t presc = ((T_I2CCLK * i2cclk / 1000) - 1);

      if (presc < 0) {
        return (ARM_DRIVER_ERROR_UNSUPPORTED);
      }

      switch (arg) {
        case ARM_I2C_BUS_SPEED_STANDARD:
          timing = ((presc << I2C_TIMINGR_PRESC_Pos)               |
                   ((STD_MODE_SCLDEL-1) << I2C_TIMINGR_SCLDEL_Pos) |
                   (STD_MODE_SDADEL << I2C_TIMINGR_SDADEL_Pos)     |
                   ((STD_MODE_SCLH-1) << I2C_TIMINGR_SCLH_Pos)     |
                   (STD_MODE_SCLL-1));
          break;

        case ARM_I2C_BUS_SPEED_FAST:
          timing = ((presc << I2C_TIMINGR_PRESC_Pos)               |
                   ((FST_MODE_SCLDEL-1) << I2C_TIMINGR_SCLDEL_Pos) |
                   (FST_MODE_SDADEL << I2C_TIMINGR_SDADEL_Pos)     |
                   ((FST_MODE_SCLH-1) << I2C_TIMINGR_SCLH_Pos)     |
                   (FST_MODE_SCLL-1));
          break;

        case ARM_I2C_BUS_SPEED_FAST_PLUS:
          timing = ((presc << I2C_TIMINGR_PRESC_Pos)               |
                   ((FSTP_MODE_SCLDEL-1) << I2C_TIMINGR_SCLDEL_Pos) |
                   (FSTP_MODE_SDADEL << I2C_TIMINGR_SDADEL_Pos)     |
                   ((FSTP_MODE_SCLH-1) << I2C_TIMINGR_SCLH_Pos)     |
                   (FSTP_MODE_SCLL-1));
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
      /* Save CR1 register */
      val = reg->CR1;

      /* Disable DMA requests and peripheral interrupts */
      reg->CR1 &= ~(I2C_CR1_RXDMAEN |
                    I2C_CR1_TXDMAEN |
                    I2C_CR1_ERRIE   |
                    I2C_CR1_TCIE    |
                    I2C_CR1_STOPIE  |
                    I2C_CR1_NACKIE  |
                    I2C_CR1_ADDRIE  |
                    I2C_CR1_RXIE    |
                    I2C_CR1_TXIE)   ;

      if (info->status.mode != 0U) {
        /* Master generates stop after the current byte transfer */
        reg->CR2 |= I2C_CR2_STOP;
      }
      else {
        /* Slave receiver will send NACK */
        reg->CR2 |= I2C_CR2_NACK;
      }

#ifdef I2C_DMA_TX
      if (i2c->dma_tx != NULL) {
        DMA_Abort(i2c->dma_tx);
        DMA_WaitAbort(i2c->dma_tx);
      }
#endif

#ifdef I2C_DMA_RX
      if (i2c->dma_rx != NULL) {
        DMA_Abort(i2c->dma_rx);
        DMA_WaitAbort(i2c->dma_rx);
      }
#endif

      info->xfer.num                = 0U;
      info->xfer.cnt                = 0U;
      info->xfer.data               = NULL;
      info->xfer.ctrl               = 0U;

      info->status.busy             = 0U;
      info->status.mode             = 0U;
      info->status.direction        = 0U;
      info->status.general_call     = 0U;
      info->status.arbitration_lost = 0U;
      info->status.bus_error        = 0U;

      /* Disable peripheral (I2C lines will be released */
      reg->CR1 &= ~I2C_CR1_PE;

      /* Clear pending interrupts */
      reg->ICR = I2C_ICR_OVRCF  |
                 I2C_ICR_ARLOCF |
                 I2C_ICR_BERRCF |
                 I2C_ICR_STOPCF |
                 I2C_ICR_NACKCF |
                 I2C_ICR_ADDRCF ;

      /* Restore settings and enable peripheral */
      reg->CR1 = val;
      break;

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          ARM_I2C_STATUS I2C_GetStatus(I2C_RESOURCES *i2c)
 * @brief       Get I2C status.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      I2C status \ref ARM_I2C_STATUS
 */
static
ARM_I2C_STATUS I2C_GetStatus(I2C_RESOURCES *i2c)
{
  return (i2c->info->status);
}

/**
 * @fn          void I2C_EV_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Event Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_EV_IRQHandler(I2C_RESOURCES *i2c)
{
  uint32_t           event = 0;
  I2C_TRANSFER_INFO *xfer = &i2c->info->xfer;
  I2C_INFO          *info = i2c->info;
  I2C_TypeDef       *reg = i2c->reg;
  uint32_t           isr = reg->ISR;

  if ((isr & I2C_ISR_RXNE) && (info->status.mode != 0U)) {
    /* Receive data register not empty */
    xfer->data[xfer->cnt++] = reg->RXDR;
    return;
  }
  else if (isr & I2C_ISR_TXIS) {
    /* Transmit data register empty */
    reg->TXDR = xfer->data[xfer->cnt++];
    return;
  }

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

      /* Slave receive mode */
      if ((info->status.direction == 1U) && (info->status.mode == 0)) {
        if (xfer->data != NULL) {
          if ((uint32_t)xfer->cnt < xfer->num) {
            xfer->data[xfer->cnt++] = (uint8_t)reg->RXDR;
            if ((uint32_t)xfer->cnt == xfer->num) {
              xfer->data = NULL;
            }
            cr |= (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_RELOAD;
          }
        }
        else {
          reg->RXDR;
          cr |= I2C_CR2_NACK;
          cr |= (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_RELOAD;
        }

        i2c->reg->CR2 = cr;
      }
      /* Other modes */
      else {
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

        reg->CR2 = (cnt << I2C_CR2_NBYTES_Pos) | cr;
      }
    }
  }
  else if (isr & (I2C_ISR_STOPF | I2C_ISR_NACKF | I2C_ISR_ADDR)) {
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

/**
 * @fn          void I2C_ER_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Error Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_ER_IRQHandler(I2C_RESOURCES *i2c)
{
  uint32_t           event = 0;
  I2C_TRANSFER_INFO *xfer = &i2c->info->xfer;
  I2C_INFO          *info = i2c->info;
  I2C_TypeDef       *reg = i2c->reg;
  uint32_t           isr = reg->ISR;
  uint32_t           icr = 0;

  if (isr & I2C_ISR_ARLO) {
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

  /* Send events */
  if ((event) && (info->cb_event)) {
    info->cb_event(event);
  }
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_I2C0)
  I2Cx_EXPORT_DRIVER(0);
#endif  /* USE_I2C0 */

#if defined(USE_I2C1)
  I2Cx_EXPORT_DRIVER(1);
#endif  /* USE_I2C1 */

#endif /* defined(USE_I2C0) || defined(USE_I2C0) */
