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

#if defined(USE_I2C0) || defined(USE_I2C1)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define I2CCLK_100K_DIVL    ((uint16_t) (0xCFU << 0U))
#define I2CCLK_100K_DIVH    ((uint16_t) (0xCFU << 8U))
#define I2CCLK_400K_DIVL    ((uint16_t) (0x3CU << 0U))
#define I2CCLK_400K_DIVH    ((uint16_t) (0x28U << 8U))

#define FIFO_SIZE           (2U)
#define DUMMY_BYTE          ((uint8_t)0xFF)

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

static void I2C0_Master_IRQHandler(void);
static void I2C0_Slave_IRQHandler(void);

/* I2C0 Resources */
static I2C_RESOURCES I2C0_Resources = {
  I2C0,
  {
    &I2C0_scl,
    &I2C0_sda,
  },
  &I2C0_Info,
  PCC_PERIPH_I2C0,
  {
    I2C0_INT_PRIORITY,
    I2C0_MASTER_IRQn,
    I2C0_SLAVE_IRQn,
    I2C0_Master_IRQHandler,
    I2C0_Slave_IRQHandler,
  }
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

static void I2C1_Master_IRQHandler(void);
static void I2C1_Slave_IRQHandler(void);

/* I2C1 Resources */
static I2C_RESOURCES I2C1_Resources = {
  I2C1,
  {
    &I2C1_scl,
    &I2C1_sda,
  },
  &I2C1_Info,
  PCC_PERIPH_I2C1,
  {
    I2C1_INT_PRIORITY,
    I2C1_MASTER_IRQn,
    I2C1_SLAVE_IRQn,
    I2C1_Master_IRQHandler,
    I2C1_Slave_IRQHandler,
  }
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
  I2C_IO         *io;
  GPIO_PIN_CFG_t  pin_cfg;
  I2C_INFO       *info = i2c->info;

  if (info->flags & I2C_INIT) {
    return (ARM_DRIVER_OK);
  }

  io      = &i2c->io;
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
  I2C_INFO *info =  i2c->info;
  I2C_IRQ  *irq  = &i2c->irq;
  I2C_t    *reg  =  i2c->reg;

  switch (state) {
    case ARM_POWER_OFF:
      /* Disable I2C peripheral */
      reg->MCON = 0U;
      reg->SCON = 0U;

      /* Disable I2C peripheral clock */
      PCC_DisablePeriph(i2c->pcc_periph);

      /* Disable I2C IRQ */
      IRQ_Disable(irq->master_num);
      IRQ_Disable(irq->slave_num);

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

      /* Enable I2C peripheral clock */
      PCC_EnablePeriph(i2c->pcc_periph);

      /* Enable I2C IRQ */
      IRQ_SetPriority(irq->master_num, irq->priority);
      IRQ_SetPriority(irq->slave_num, irq->priority);
      IRQ_SetHandler(irq->master_num, irq->master_handler);
      IRQ_SetHandler(irq->slave_num, irq->slave_handler);
      IRQ_SetMode(irq->master_num, IRQ_MODE_TYPE_IRQ);
      IRQ_SetMode(irq->slave_num, IRQ_MODE_TYPE_IRQ);
      IRQ_Enable(irq->master_num);
      IRQ_Enable(irq->slave_num);

      /* Initial peripheral setup */
      reg->MCON = 0U;
      reg->SCON = 0U;

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
  I2C_INFO *info = i2c->info;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~((uint32_t)ARM_I2C_ADDRESS_10BIT | (uint32_t)ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & I2C_SETUP) == 0U) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  if ((info->ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer */
  }

  info->status.busy             = 1U;
  info->status.mode             = I2C_MODE_MASTER;
  info->status.direction        = I2C_DIR_TX;
  info->status.bus_error        = 0U;
  info->status.arbitration_lost = 0U;

  info->tx.data = (uint8_t *)data;
  info->tx.num  = num;
  info->tx.cnt  = 0U;

  info->ctrl = 0U;

  if (xfer_pending) {
    info->ctrl |= XFER_CTRL_XPENDING;
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
  I2C_INFO *info = i2c->info;
  I2C_t *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & I2C_SETUP) == 0U) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  if ((info->ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer */
  }

  info->status.busy             = 1U;
  info->status.mode             = I2C_MODE_MASTER;
  info->status.direction        = I2C_DIR_RX;
  info->status.bus_error        = 0U;
  info->status.arbitration_lost = 0U;

  info->tx.data = data;
  info->tx.num  = num;
  info->tx.cnt  = 0U;

  info->ctrl = 0U;

  if (xfer_pending) {
    info->ctrl |= XFER_CTRL_XPENDING;
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
  I2C_INFO *info = i2c->info;
  I2C_t    *reg  = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if (info->status.busy != 0U) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status.bus_error    = 0U;
  info->status.general_call = 0U;

  info->tx.data      = (uint8_t *)data;
  info->tx.num       = (int32_t)num;
  info->tx.cnt       = -1;
  info->tx.dummy_cnt = 0U;

  reg->FSTA = I2CFSTA_FSTX;
  reg->STX = *data;
  reg->SCON |= I2CSCON_STXENI;

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

  if (info->status.busy != 0U) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status.bus_error    = 0U;
  info->status.general_call = 0U;

  info->rx.data = data;
  info->rx.num  = (int32_t)num;
  info->rx.cnt  = -1;

  i2c->reg->SCON |= I2CSCON_SRXENI;

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
  int32_t   val;
  I2C_INFO *info = i2c->info;

  if (info->status.direction == I2C_DIR_TX) {
    val = info->tx.cnt;
  } else {
    val = info->rx.cnt;
  }

  return (val);
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
  I2C_INFO *info = i2c->info;
  I2C_t    *reg  = i2c->reg;
  uint32_t  val;

  if ((info->flags & I2C_POWER) == 0U) {
    /* I2C not powered */
    return (ARM_DRIVER_ERROR);
  }

  switch (control) {
    case ARM_I2C_OWN_ADDRESS:
      if (arg == 0) {
        /* Disable slave */
        val = 0U;
      }
      else {
        /* Enable slave */
        val = I2CSCON_STXENI | I2CSCON_SRXENI | I2CSCON_SSENI | I2CSCON_SETEN |
              I2CSCON_SEN;

        if (arg & ARM_I2C_ADDRESS_GC) {
          /* Enable general call */
          val |= I2CSCON_GCEN;
        }

        if (arg & ARM_I2C_ADDRESS_10BIT) {
          /* Enable 10-bit address mode */
          val |= I2CSCON_ADR10EN;
        }
      }

      reg->ID0  = ((arg << 1U) & 0xFF);
      reg->SCON = (uint16_t)val;
      break;

    case ARM_I2C_BUS_SPEED:
      switch (arg) {
        case ARM_I2C_BUS_SPEED_STANDARD:
          val = I2CCLK_100K_DIVH | I2CCLK_100K_DIVL;
          break;

        case ARM_I2C_BUS_SPEED_FAST:
          val = I2CCLK_400K_DIVH | I2CCLK_400K_DIVL;
          break;

        default:
          return (ARM_DRIVER_ERROR_UNSUPPORTED);
      }

      /* Configure period of SCL */
      reg->DIV  = (uint16_t)val;
      /* Enable master */
      reg->MCON = (uint16_t)(I2CMCON_MCENI | I2CMCON_NACKENI | I2CMCON_ALENI | I2CMCON_MEN);

      /* Master configured, clock set */
      info->flags |= I2C_SETUP;
      break;

    case ARM_I2C_BUS_CLEAR:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);

    case ARM_I2C_ABORT_TRANSFER:
      /* Disable peripheral interrupts */

      if (info->status.mode != 0U) {
        /* Master generates stop after the current byte transfer */
      }
      else {
        /* Slave receiver will send NACK */
      }

      info->rx.num                  = 0;
      info->rx.cnt                  = 0;
      info->tx.num                  = 0;
      info->tx.cnt                  = 0;

      info->ctrl                    = 0U;

      info->status.busy             = 0U;
      info->status.mode             = 0U;
      info->status.direction        = 0U;
      info->status.general_call     = 0U;
      info->status.arbitration_lost = 0U;
      info->status.bus_error        = 0U;

      /* Disable peripheral (I2C lines will be released */

      /* Clear pending interrupts */

      /* Restore settings and enable peripheral */
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
 * @fn          void I2C_Master_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Master Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_Master_IRQHandler(I2C_RESOURCES *i2c)
{
  uint32_t  event = 0;
  I2C_INFO *info  = i2c->info;
  I2C_t    *reg   = i2c->reg;

  /* Send events */
  if ((event) && (info->cb_event)) {
    info->cb_event(event);
  }
}

/**
 * @fn          void I2C_Slave_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Slave Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_Slave_IRQHandler(I2C_RESOURCES *i2c)
{
  register uint32_t  status;
  register uint32_t  event;
  uint8_t            data;
  I2C_INFO          *info = i2c->info;
  I2C_t             *reg  = i2c->reg;
  I2C_RX_XFER_INFO  *rx   = &info->rx;
  I2C_TX_XFER_INFO  *tx   = &info->tx;

  status = reg->SSTA;

  if ((status & I2CSSTA_REPS) == 0U) {
    if ((status & I2CSSTA_STXQ) != 0U) {
      if (tx->num == 0) {
        reg->SCON &= ~I2CSCON_STXENI;

        if ((status & I2CSSTA_GC) != 0U) {
          info->status.general_call = 1U;
        }

        if (info->cb_event != NULL) {
          info->cb_event(ARM_I2C_EVENT_SLAVE_TRANSMIT);
        }
      }

      if (tx->cnt < tx->num) {
        if (tx->cnt == -1) {
          tx->cnt = 1;
          info->status.direction = I2C_DIR_TX;
          info->status.busy = 1U;
        }

        reg->STX = tx->data[tx->cnt++];
      }
      else {
        reg->STX = DUMMY_BYTE;
        tx->dummy_cnt++;
        if (tx->dummy_cnt == FIFO_SIZE) {
          reg->SCON &= ~I2CSCON_STXENI;
          info->status.busy = 0U;
          tx->num = 0;
          /* Transfer completed */
          if (info->cb_event != NULL) {
            event = ARM_I2C_EVENT_TRANSFER_DONE;

            if (info->status.general_call == 1U) {
              event |= ARM_I2C_EVENT_GENERAL_CALL;
            }

            info->cb_event(event);
          }
        }
      }
    }
    else if ((status & I2CSSTA_SRXQ) != 0U) {
      if (rx->num == 0) {
        reg->SCON &= ~I2CSCON_SRXENI;
        event = ARM_I2C_EVENT_SLAVE_RECEIVE;

        if ((status & I2CSSTA_GC) != 0U) {
          info->status.general_call = 1U;
          event |= ARM_I2C_EVENT_GENERAL_CALL;
        }

        if (info->cb_event != NULL) {
          info->cb_event(event);
        }
      }

      if (rx->cnt < rx->num) {
        if (rx->cnt == -1) {
          rx->cnt = 0;
          info->status.direction = I2C_DIR_RX;
          info->status.busy = 1U;
        }

        rx->data[rx->cnt++] = (uint8_t)reg->SRX;

        if (rx->cnt == rx->num) {
          reg->SCON &= ~I2CSCON_SRXENI;
          info->status.busy = 0U;
          rx->num = 0U;
          /* Transfer completed */
          if (info->cb_event != NULL) {
            event = ARM_I2C_EVENT_TRANSFER_DONE;

            if (info->status.general_call == 1U) {
              event |= ARM_I2C_EVENT_GENERAL_CALL;
            }

            info->cb_event(event);
          }
        }
      }
    }
  }

  if ((status & (I2CSSTA_SS | I2CSSTA_REPS)) != 0U) {
    /* Enable slave request interrupts */
    reg->SCON |= I2CSCON_STXENI | I2CSCON_SRXENI;

    if (info->status.busy != 0U) {
      info->status.busy = 0U;
      event = ARM_I2C_EVENT_TRANSFER_DONE;

      if (info->status.direction == I2C_DIR_TX) {
        uint32_t fifo_cnt = reg->FSTA & I2CFSTA_STXSTA;

        if (fifo_cnt != 0U) {
          --fifo_cnt;
          tx->cnt -= (fifo_cnt - tx->dummy_cnt);
        }

        if (tx->cnt < tx->num) {
          event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
        }

        tx->num = 0;
      }
      else {
        while ((reg->FSTA & I2CFSTA_SRXSTA) != 0U) {
          data = (uint8_t)reg->SRX;
          if (rx->cnt < rx->num) {
            rx->data[rx->cnt++] = data;
          }
        }

        if (rx->cnt < rx->num) {
          event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
        }

        rx->num = 0;
      }

      if (info->cb_event != NULL) {

        if (info->status.general_call == 1U) {
          event |= ARM_I2C_EVENT_GENERAL_CALL;
        }

        info->cb_event(event);
      }
    }
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
