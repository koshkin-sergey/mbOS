/*
 * Copyright (C) 2017-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver for ADI ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "I2C_ADUCM32x.h"
#include <string.h>

#if defined(USE_I2C0) || defined(USE_I2C1)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define SLAVE_MODE      0U
#define MASTER_MODE     1U
#define TX_DIRECTION    0U
#define RX_DIRECTION    1U

#define SCL_HIGH_TIME_100K        (5000U) // HIGH period of the SCL clock in ns.
#define SCL_LOW_TIME_100K         (5000U) // LOW period of the SCL clock in ns.

#define SCL_HIGH_TIME_400K        (1200U) // HIGH period of the SCL clock in ns.
#define SCL_LOW_TIME_400K         (1300U) // LOW period of the SCL clock in ns.

#define DUMMY_BYTE                ((uint8_t)0xFF)

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
  0            /* supports 10-bit addressing */
};

#if defined(USE_I2C0)
/* I2C0 Information (Run-Time) */
static I2C_Info_t I2C0_Info;

/* I2C0 Resources */
static I2C_Resources_t I2C0_Resources = {
  MMR_I2C0,
  {
    {I2C0_SCL_GPIO_PORT, I2C0_SCL_GPIO_PIN, I2C0_SCL_GPIO_FUNC},
    {I2C0_SDA_GPIO_PORT, I2C0_SDA_GPIO_PIN, I2C0_SDA_GPIO_FUNC},
  },
  CLK_PERIPH_I2C0,
  {
    I2C0_INT_PRIORITY,
    I2C0_Master_IRQn,
    I2C0_Slave_IRQn,
  },
  &I2C0_Info,
};
#endif /* USE_I2C0 */


#if defined(USE_I2C1)
/* I2C1 Information (Run-Time) */
static I2C_Info_t I2C1_Info;

/* I2C1 Resources */
static I2C_Resources_t I2C1_Resources = {
  MMR_I2C1,
  {
    {I2C1_SCL_GPIO_PORT, I2C1_SCL_GPIO_PIN, I2C1_SCL_GPIO_FUNC},
    {I2C1_SDA_GPIO_PORT, I2C1_SDA_GPIO_PIN, I2C1_SDA_GPIO_FUNC},
  },
  CLK_PERIPH_I2C1,
  {
    I2C1_INT_PRIORITY,
    I2C1_Master_IRQn,
    I2C1_Slave_IRQn,
  },
  &I2C1_Info,
};
#endif /* USE_I2C1 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
uint32_t GetFifoCntSlaveTx(MMR_I2C_t *mmr)
{
  uint32_t cnt = _FLD2VAL(I2CFSTA_STXFSTA, mmr->I2CFSTA);

  return (cnt);
}

static
uint32_t GetFifoCntSlaveRx(MMR_I2C_t *mmr)
{
  uint32_t cnt = _FLD2VAL(I2CFSTA_SRXFSTA, mmr->I2CFSTA);

  return (cnt);
}

static
uint32_t GetFifoCntMasterTx(MMR_I2C_t *mmr)
{
  uint32_t cnt = _FLD2VAL(I2CFSTA_MTXFSTA, mmr->I2CFSTA);

  return (cnt);
}

static
uint32_t GetFifoCntMasterRx(MMR_I2C_t *mmr)
{
  uint32_t cnt = _FLD2VAL(I2CFSTA_MRXFSTA, mmr->I2CFSTA);

  return (cnt);
}

/**
 * @brief   Get driver capabilities.
 * @return  \ref ARM_I2C_CAPABILITIES
 */
static
ARM_DRIVER_VERSION I2C_GetVersion(void)
{
  return (DriverVersion);
}

/**
 * @brief   Get driver capabilities.
 * @return  \ref ARM_I2C_CAPABILITIES
 */
static
ARM_I2C_CAPABILITIES I2C_GetCapabilities(void)
{
  return (DriverCapabilities);
}

/**
 * @brief       Initialize I2C Interface.
 * @param[in]   cb_event  Pointer to \ref ARM_I2C_SignalEvent
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_Resources_t *i2c)
{
  I2C_Info_t     *info;
  I2C_IO_t       *io;
  GPIO_PIN_CFG_t  pin_cfg;

  if (i2c->info->flags & I2C_FLAG_INIT) {
    return (ARM_DRIVER_OK);
  }

  io   = &i2c->io;
  info = i2c->info;

  pin_cfg.mode = GPIO_MODE_ANALOG;
  pin_cfg.pull = GPIO_PULL_DISABLE;

  /* Configure SCL Pin */
  pin_cfg.func = io->scl.func;
  io->scl.gpio->PinConfig(io->scl.pin, &pin_cfg);

  /* Configure SDA Pin */
  pin_cfg.func = io->sda.func;
  io->sda.gpio->PinConfig(io->sda.pin, &pin_cfg);

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2C_Info_t));

  info->cb_event = cb_event;
  info->flags    = I2C_FLAG_INIT;

  return (ARM_DRIVER_OK);
}

/**
 * @brief       De-initialize I2C Interface.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_Uninitialize(I2C_Resources_t *i2c)
{
  I2C_IO_t       *io;
  GPIO_PIN_CFG_t  pin_cfg;

  io = &i2c->io;

  pin_cfg.func = GPIO_PIN_FUNC_0;
  pin_cfg.mode = GPIO_MODE_ANALOG;
  pin_cfg.pull = GPIO_PULL_DISABLE;

  /* Unconfigure SCL Pin */
  io->scl.gpio->PinConfig(io->scl.pin, &pin_cfg);

  /* Unconfigure SDA Pin */
  io->sda.gpio->PinConfig(io->sda.pin, &pin_cfg);

  i2c->info->flags = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @brief       Control I2C Interface Power.
 * @param[in]   state   Power state
 * @param[in]   i2c     Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_PowerControl(ARM_POWER_STATE state, I2C_Resources_t *i2c)
{
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;
  I2C_Irq_t  *irq  = &i2c->irq;
  Driver_CLK_t *clk = &Driver_CLK;

  switch (state) {
    case ARM_POWER_OFF:
      /* Reset I2C peripheral */
      mmr->I2CMCON  = 0U;
      mmr->I2CSCON  = 0U;
      mmr->I2CSHCON |= I2CSHCON_RESET;

      /* Disable I2C peripheral clock */
      clk->PeriphDisable(i2c->clk_periph);

      /* Disable I2C interrupts */
      NVIC_DisableIRQ(irq->master_num);
      NVIC_DisableIRQ(irq->slave_num);

      info->status = 0U;
      info->flags &= (uint16_t)~I2C_FLAG_POWER;
      break;

    case ARM_POWER_FULL:
      if ((info->flags & I2C_FLAG_INIT) == 0U) {
        return (ARM_DRIVER_ERROR);
      }

      if ((info->flags & I2C_FLAG_POWER) != 0U) {
        return (ARM_DRIVER_OK);
      }

      /* Enable I2C peripheral clock */
      clk->PeriphEnable(i2c->clk_periph);

      /* Enable I2C interrupts */
      NVIC_ClearPendingIRQ(irq->master_num);
      NVIC_ClearPendingIRQ(irq->slave_num);
      NVIC_SetPriority(irq->master_num, irq->priority);
      NVIC_SetPriority(irq->slave_num, irq->priority);
      NVIC_EnableIRQ(irq->master_num);
      NVIC_EnableIRQ(irq->slave_num);

      /* Initial peripheral setup */
      mmr->I2CMCON = 0U;
      mmr->I2CSCON = 0U;

      info->flags |= I2C_FLAG_POWER;
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
int32_t I2C_Control(uint32_t control, uint32_t arg, I2C_Resources_t *i2c)
{
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;

  if ((info->flags & I2C_FLAG_POWER) == 0U) {
    /* Driver not powered */
    return (ARM_DRIVER_ERROR);
  }

  switch (control) {
    case ARM_I2C_OWN_ADDRESS: {
      uint16_t reg_val;

      /* Set Own Slave Address */
      if (arg == 0) {
        /* Disable slave */
        reg_val = 0U;
      }
      else {
        reg_val = I2CSCON_IENSRX | I2CSCON_IENSTX | I2CSCON_EARLYTXR | I2CSCON_SLVEN;

        if (arg & ARM_I2C_ADDRESS_GC) {
          /* General call enable */
          reg_val |= I2CSCON_GCEN;
        }
      }

      mmr->I2CID0  = (uint16_t)((arg << 1) & 0xFFU);
      mmr->I2CSCON = reg_val;
    }
      break;

    case ARM_I2C_BUS_SPEED: {
      Driver_CLK_t *clk = &Driver_CLK;
      uint64_t clk_val;
      uint16_t low;
      uint16_t high;

      /* Set Bus Speed */
      clk_val = clk->GetFrequency(CLK_FREQ_PCLK);

      switch (arg) {
        case ARM_I2C_BUS_SPEED_STANDARD:
          /* Standard Speed (100kHz) */
          low  = (uint16_t)(SCL_LOW_TIME_100K * clk_val / 1000000000U - 1U);
          high = (uint16_t)(SCL_HIGH_TIME_100K  * clk_val / 1000000000U - 2U);
          break;

        case ARM_I2C_BUS_SPEED_FAST:
          /* Fast Speed (400kHz) */
          low  = (uint16_t)(SCL_LOW_TIME_400K * clk_val / 1000000000U - 1U);
          high = (uint16_t)(SCL_HIGH_TIME_400K  * clk_val / 1000000000U - 2U);
          break;

        default:
          return (ARM_DRIVER_ERROR_UNSUPPORTED);
      }

      mmr->I2CDIV = (uint16_t)(_VAL2FLD(I2CDIV_HIGH, high) |
                               _VAL2FLD(I2CDIV_LOW, low));

      /* Master configured, clock set */
      info->flags |= I2C_FLAG_SETUP;
    }
      break;

    case ARM_I2C_BUS_CLEAR:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);

    case ARM_I2C_ABORT_TRANSFER:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }
  return (ARM_DRIVER_OK);
}

/**
 * @brief       Start transmitting data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[in]   data          Pointer to buffer with data to transmit to I2C Slave
 * @param[in]   num           Number of data bytes to transmit
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition
 *                            will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_MasterTransmit(uint32_t         addr,
                           const uint8_t   *data,
                           uint32_t         num,
                           bool             xfer_pending,
                           I2C_Resources_t *i2c)
{
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;
  I2C_TX_XferInfo_t *tx = &info->tx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & I2C_FLAG_SETUP) == 0U) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if ((info->xfer_ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer, check the SDA line is busy */
    if ((mmr->I2CMSTA & I2CMSTA_LINEBUSY) != 0U) {
      /* Bus is busy or locked */
      info->status = I2C_STATUS_BUS_ERROR;

      if (info->cb_event != NULL) {
        info->cb_event(ARM_I2C_EVENT_TRANSFER_DONE       |
                       ARM_I2C_EVENT_TRANSFER_INCOMPLETE |
                       ARM_I2C_EVENT_BUS_ERROR);
      }

      return (ARM_DRIVER_OK);
    }
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status    = I2C_STATUS_BUSY | I2C_STATUS_MASTER;
  info->xfer_ctrl = 0U;

  if (xfer_pending != false) {
    info->xfer_ctrl = XFER_CTRL_XPENDING;
  }

  tx->data = data;
  tx->num  = num;
  tx->cnt  = 0U;
  tx->dummy_cnt = 0U;

  /* Enable master */
  mmr->I2CMCON = (uint16_t)(I2CMCON_MASEN | I2CMCON_IENALOST);

  /* Fill the TX FIFO */
  mmr->I2CMTX = tx->data[tx->cnt++];
  if (tx->cnt == tx->num) {
    mmr->I2CMTX = DUMMY_BYTE;
    tx->dummy_cnt++;
  }
  else {
    mmr->I2CMTX = tx->data[tx->cnt++];
  }

  /* Enable transmit interrupt */
  mmr->I2CMCON |= (uint16_t)(I2CMCON_IENCMP | I2CMCON_IENMTX);
  /* Set slave address, transfer direction and generate start */
  mmr->I2CADR0 = (uint16_t)((addr << 1) & I2CADR0_ADR0_Msk);

  return (ARM_DRIVER_OK);
}

/**
 * @brief       Start receiving data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[out]  data          Pointer to buffer for data to receive from I2C Slave
 * @param[in]   num           Number of data bytes to receive
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition
 *                            will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return                    \ref execution_status
 */
static
int32_t I2C_MasterReceive(uint32_t         addr,
                          uint8_t         *data,
                          uint32_t         num,
                          bool             xfer_pending,
                          I2C_Resources_t *i2c)
{
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;
  I2C_RX_XferInfo_t *rx = &info->rx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & I2C_FLAG_SETUP) == 0U) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if ((info->xfer_ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer, check the SDA line is busy */
    if ((mmr->I2CMSTA & I2CMSTA_LINEBUSY) != 0U) {
      /* Bus is busy or locked */
      info->status = I2C_STATUS_BUS_ERROR;

      if (info->cb_event != NULL) {
        info->cb_event(ARM_I2C_EVENT_TRANSFER_DONE       |
                       ARM_I2C_EVENT_TRANSFER_INCOMPLETE |
                       ARM_I2C_EVENT_BUS_ERROR);
      }

      return (ARM_DRIVER_OK);
    }
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status    = I2C_STATUS_BUSY | I2C_STATUS_MASTER | I2C_STATUS_RECEIVER;
  info->xfer_ctrl = 0U;

  if (xfer_pending != false) {
    info->xfer_ctrl = XFER_CTRL_XPENDING;
  }

  rx->data = data;
  rx->num  = num;
  rx->cnt  = 0U;

  /* Enable master */
  mmr->I2CMCON = (uint16_t)(I2CMCON_MASEN | I2CMCON_IENALOST);
  /* Set number of bytes to transfer */
  mmr->I2CMRXCNT = (uint16_t)((num - 1U) & I2CMRXCNT_COUNT_Msk);
  /* Enable receive interrupt */
  mmr->I2CMCON |= (uint16_t)(I2CMCON_IENCMP | I2CMCON_IENMRX);
  /* Set slave address, transfer direction and generate start */
  mmr->I2CADR0 = (uint16_t)(((addr << 1) | 1UL) & I2CADR0_ADR0_Msk);

  return (ARM_DRIVER_OK);
}

/**
 * @brief       Start transmitting data as I2C Slave.
 * @param[in]   data  Pointer to buffer with data to transmit to I2C Master
 * @param[in]   num   Number of data bytes to transmit
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_Resources_t *i2c)
{
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;
  I2C_TX_XferInfo_t *tx = &info->tx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status    = 0U;
  info->xfer_ctrl = 0U;

  tx->data      = data;
  tx->num       = num;
  tx->cnt       = 0U;
  tx->dummy_cnt = 0U;

  /* Flush the Slave TX FIFO */
  mmr->I2CFSTA = I2CFSTA_SFLUSH;

  /* Fill the Slave TX FIFO */
  mmr->I2CSTX = tx->data[tx->cnt++];
  if (tx->cnt == tx->num) {
    mmr->I2CSTX = DUMMY_BYTE;
    tx->dummy_cnt++;
  }
  else {
    mmr->I2CSTX = tx->data[tx->cnt++];
  }

  /* Enable TX interrupt */
  mmr->I2CSCON |= I2CSCON_IENSTX;

  return (ARM_DRIVER_OK);
}

/**
 * @brief       Start receiving data as I2C Slave.
 * @param[out]  data  Pointer to buffer for data to receive from I2C Master
 * @param[in]   num   Number of data bytes to receive
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_SlaveReceive(uint8_t *data, uint32_t num, I2C_Resources_t *i2c)
{
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;
  I2C_RX_XferInfo_t *rx = &info->rx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status    = 0U;
  info->xfer_ctrl = 0U;

  rx->data = data;
  rx->num  = num;
  rx->cnt  = 0U;

  /* Enable RX interrupt */
  mmr->I2CSCON |= I2CSCON_IENSRX;

  return (ARM_DRIVER_OK);
}

/**
 * @brief       Get transferred data count.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      Number of data bytes transferred;
 *              -1 when Slave is not addressed by Master
 */
static
int32_t I2C_GetDataCount(I2C_Resources_t *i2c)
{
  uint32_t  val;
  uint32_t  fifo_cnt;
  MMR_I2C_t  *mmr  = i2c->mmr;
  I2C_Info_t *info = i2c->info;

  if ((info->status & I2C_STATUS_MASTER)      == 0U &&
      (info->xfer_ctrl & XFER_CTRL_ADDR_DONE) == 0U) {
    return (-1);
  }

  if ((info->status & I2C_STATUS_RECEIVER) == 0U) {
    val = info->tx.cnt;

    if (val > 0U) {
      if ((info->status & I2C_STATUS_MASTER) == 0U) {
        fifo_cnt = GetFifoCntSlaveTx(mmr);
      }
      else {
        fifo_cnt = GetFifoCntMasterTx(mmr);
      }

      val -= fifo_cnt - info->tx.dummy_cnt;
    }
  }
  else {
    val = info->rx.cnt;

    if (val > 0U) {
      if ((info->status & I2C_STATUS_MASTER) == 0U) {
        fifo_cnt = GetFifoCntSlaveRx(mmr);
      }
      else {
        fifo_cnt = GetFifoCntMasterRx(mmr);
      }

      val -= fifo_cnt;
    }
  }

  return ((int32_t)val);
}

/**
 * @fn          ARM_I2C_STATUS I2Cx_GetStatus(I2C_RESOURCES *i2c)
 * @brief       Get I2C status.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      I2C status \ref ARM_I2C_STATUS
 */
static
ARM_I2C_STATUS I2C_GetStatus(I2C_Resources_t *i2c)
{
  ARM_I2C_STATUS *status = (ARM_I2C_STATUS *)&i2c->info->status;

  return (*status);
}

/**
 * @fn          void I2Cx_MasterHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Master state event handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_Master_IRQHandler(I2C_Resources_t *i2c)
{
  register uint32_t  state;
  register uint32_t  ctrl;
  register uint32_t  event;
  I2C_Info_t        *info = i2c->info;
  MMR_I2C_t         *mmr  = i2c->mmr;
  I2C_RX_XferInfo_t *rx   = &info->rx;
  I2C_TX_XferInfo_t *tx   = &info->tx;

  ctrl   = mmr->I2CMCON;
  state  = mmr->I2CMSTA;
  event  = 0U;

  if ((ctrl & I2CMCON_IENMTX) != 0U && (state & I2CMSTA_MTXREQ) != 0U) {
    if (tx->cnt != tx->num) {
      mmr->I2CMTX = tx->data[tx->cnt++];
    }
    else {
      if (tx->dummy_cnt != 0U) {
        tx->dummy_cnt = 0U;
        mmr->I2CFSTA = I2CFSTA_MFLUSH;
      }
      mmr->I2CMCON &= (uint16_t)~I2CMCON_IENMTX;
      if ((info->xfer_ctrl & XFER_CTRL_XPENDING) != 0U) {
        info->status &= ~I2C_STATUS_BUSY;
        event = ARM_I2C_EVENT_TRANSFER_DONE;
      }
    }
  }

  if ((ctrl & I2CMCON_IENMRX) != 0U && (state & I2CMSTA_MRXREQ) != 0U) {
    if (rx->cnt < rx->num) {
      rx->data[rx->cnt++] = (uint8_t)mmr->I2CMRX;
      if (rx->cnt == rx->num) {
        mmr->I2CMCON &= (uint16_t)~I2CMCON_IENMRX;
        if ((info->xfer_ctrl & XFER_CTRL_XPENDING) != 0U) {
          info->status &= ~I2C_STATUS_BUSY;
          event = ARM_I2C_EVENT_TRANSFER_DONE;
        }
      }
    }
  }

  if ((state & I2CMSTA_ALOST) != 0U) {
    info->status = (info->status & ~I2C_STATUS_BUSY) | I2C_STATUS_ARBITRATION_LOST;
    event = ARM_I2C_EVENT_ARBITRATION_LOST |
            ARM_I2C_EVENT_TRANSFER_DONE    |
            ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
  }

  if ((state & I2CMSTA_MSTOP) != 0U) {
    if ((info->status & I2C_STATUS_BUSY) != 0U) {
      info->status &= ~I2C_STATUS_BUSY;
      event = ARM_I2C_EVENT_TRANSFER_DONE;

      if ((state & I2CMSTA_NACKADDR) != 0U) {
        tx->cnt = 0U;
        mmr->I2CFSTA = I2CFSTA_MFLUSH;
        event |= (ARM_I2C_EVENT_ADDRESS_NACK |
                  ARM_I2C_EVENT_TRANSFER_INCOMPLETE);
      }

      if ((state & I2CMSTA_NACKDATA) != 0U) {
        tx->cnt -= GetFifoCntMasterTx(mmr) + 1U;
        mmr->I2CFSTA = I2CFSTA_MFLUSH;
        event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
      }
    }

    /* Disable master */
    mmr->I2CMCON = 0U;
  }

  /* Send events */
  if ((event != 0U) && (info->cb_event)) {
    info->cb_event(event);
  }
}

/**
 * @fn          void I2Cx_SlaveHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Slave state event handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_Slave_IRQHandler(I2C_Resources_t *i2c)
{
  register uint32_t  state;
  register uint32_t  event;
  uint8_t            data;
  uint32_t           fifo_cnt;
  I2C_Info_t        *info;
  MMR_I2C_t         *mmr;
  I2C_RX_XferInfo_t *rx;
  I2C_TX_XferInfo_t *tx;

  mmr   = i2c->mmr;
  state = mmr->I2CSSTA;
  info  = i2c->info;
  rx    = &info->rx;
  tx    = &info->tx;

  /* Slave Transmit request */
  if ((state & I2CSSTA_STXREQ) != 0U) {
    if (tx->num == 0U) {
      mmr->I2CSCON &= (uint16_t)~I2CSCON_IENSTX;

      if ((state & I2CSSTA_GCINT) != 0U) {
        info->status |= I2C_STATUS_GENERAL_CALL;
      }

      if (info->cb_event != NULL) {
        info->cb_event(ARM_I2C_EVENT_SLAVE_TRANSMIT);
      }

      if (tx->num == 0U) {
        return;
      }
    }

    if ((info->xfer_ctrl & XFER_CTRL_ADDR_DONE) == 0U) {
      info->xfer_ctrl |= XFER_CTRL_ADDR_DONE;
      info->status    |= I2C_STATUS_BUSY;
    }

    if (tx->cnt != tx->num) {
      mmr->I2CSTX = tx->data[tx->cnt++];
    }
    else if (tx->dummy_cnt == 0U) {
      mmr->I2CSTX = DUMMY_BYTE;
      tx->dummy_cnt++;
    }
    else {
      info->status &= ~I2C_STATUS_BUSY;
      tx->num = 0U;
      /* Transfer completed */
      if (info->cb_event != NULL) {
        event = ARM_I2C_EVENT_TRANSFER_DONE;

        if ((info->status & I2C_STATUS_GENERAL_CALL) != 0U) {
          event |= ARM_I2C_EVENT_GENERAL_CALL;
        }

        info->cb_event(event);
      }
    }
  }

  /* Slave Receive request */
  if ((state & I2CSSTA_SRXREQ) != 0U) {
    if (rx->num == 0U) {
      mmr->I2CSCON &= (uint16_t)~I2CSCON_IENSRX;
      event = ARM_I2C_EVENT_SLAVE_RECEIVE;

      if ((state & I2CSSTA_GCINT) != 0U) {
        info->status |= I2C_STATUS_GENERAL_CALL;
        event |= ARM_I2C_EVENT_GENERAL_CALL;
      }

      if (info->cb_event != NULL) {
        info->cb_event(event);
      }

      if (rx->num == 0U) {
        return;
      }
    }

    if ((info->xfer_ctrl & XFER_CTRL_ADDR_DONE) == 0U) {
      info->xfer_ctrl |= XFER_CTRL_ADDR_DONE;
      info->status    |= (I2C_STATUS_BUSY | I2C_STATUS_RECEIVER);
    }

    if (rx->cnt != rx->num) {
      rx->data[rx->cnt++] = (uint8_t)mmr->I2CSRX;

      if (rx->cnt == rx->num) {
        mmr->I2CSCON &= (uint16_t)~I2CSCON_IENSRX;
        info->status &= ~I2C_STATUS_BUSY;
        rx->num = 0U;
        /* Transfer completed */
        if (info->cb_event != NULL) {
          event = ARM_I2C_EVENT_TRANSFER_DONE;

          if ((info->status & I2C_STATUS_GENERAL_CALL) != 0U) {
            event |= ARM_I2C_EVENT_GENERAL_CALL;
          }

          info->cb_event(event);
        }
      }
    }
  }

  /* Slave Stop Condition */
  if ((state & I2CSSTA_STOP) != 0U) {
    if ((info->status & I2C_STATUS_BUSY) != 0U) {
      info->status &= ~I2C_STATUS_BUSY;
      event = ARM_I2C_EVENT_TRANSFER_DONE;

      if ((info->status & I2C_STATUS_RECEIVER) == 0U) {
        fifo_cnt = GetFifoCntSlaveTx(mmr);

        if (fifo_cnt != tx->dummy_cnt) {
          event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
        }

        tx->num = 0U;
      }
      else {
        fifo_cnt = GetFifoCntSlaveRx(mmr);

        while (fifo_cnt--) {
          data = (uint8_t)mmr->I2CSRX;
          if (rx->cnt < rx->num) {
            rx->data[rx->cnt++] = data;
          }
        }

        if (rx->cnt < rx->num) {
          event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
        }

        rx->num = 0U;
      }

      if (info->cb_event != NULL) {

        if ((info->status & I2C_STATUS_GENERAL_CALL) != 0U) {
          event |= ARM_I2C_EVENT_GENERAL_CALL;
        }

        info->cb_event(event);
      }
    }

    /* Enable slave request interrupts */
    mmr->I2CSCON |= I2CSCON_IENSTX | I2CSCON_IENSRX;
  }
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_I2C0)
  I2Cx_EXPORT_DRIVER(0);
#endif

#if defined(USE_I2C1)
  I2Cx_EXPORT_DRIVER(1);
#endif

#endif /* defined(USE_I2C0) || defined(USE_I2C0) */
