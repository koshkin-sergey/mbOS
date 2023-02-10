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
 * @fn      ARM_DRIVER_VERSION I2C_GetVersion(void)
 * @brief   Get driver capabilities.
 * @return  \ref ARM_I2C_CAPABILITIES
 */
static
ARM_DRIVER_VERSION I2C_GetVersion(void)
{
  return DriverVersion;
}

/**
 * @fn      ARM_I2C_CAPABILITIES I2C_GetCapabilities(void)
 * @brief   Get driver capabilities.
 * @return  \ref ARM_I2C_CAPABILITIES
 */
static
ARM_I2C_CAPABILITIES I2C_GetCapabilities(void)
{
  return DriverCapabilities;
}

/**
 * @fn          int32_t I2Cx_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_RESOURCES *i2c)
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
 * @fn          int32_t I2Cx_Uninitialize(I2C_RESOURCES *i2c)
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

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t I2Cx_PowerControl(ARM_POWER_STATE state, I2C_RESOURCES *i2c)
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
 * @fn          int32_t I2Cx_Control(uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
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
          low  = (uint16_t)(SCL_HIGH_TIME_100K * clk_val / 1000000000U - 1U);
          high = (uint16_t)(SCL_LOW_TIME_100K  * clk_val / 1000000000U - 2U);
          break;

        case ARM_I2C_BUS_SPEED_FAST:
          /* Fast Speed (400kHz) */
          low  = (uint16_t)(SCL_HIGH_TIME_400K * clk_val / 1000000000U - 1U);
          high = (uint16_t)(SCL_LOW_TIME_400K  * clk_val / 1000000000U - 2U);
          break;

        default:
          return ARM_DRIVER_ERROR_UNSUPPORTED;
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
 * @fn          int32_t I2Cx_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending, I2C_RESOURCES *i2c)
 * @brief       Start transmitting data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[in]   data          Pointer to buffer with data to transmit to I2C Slave
 * @param[in]   num           Number of data bytes to transmit
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
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

  if ((addr & ~((uint32_t)ARM_I2C_ADDRESS_10BIT | (uint32_t)ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->flags & I2C_FLAG_SETUP) == 0U) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  if ((info->xfer_ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer, check the line is busy */
    if ((mmr->I2CMSTA & I2CMSTA_LINEBUSY) != 0U) {
      /* Bus is busy or locked */
      return (ARM_DRIVER_ERROR_BUSY);
    }
  }

  info->status    = I2C_STATUS_BUSY | I2C_STATUS_MASTER;
  info->xfer_ctrl = 0U;

  if (xfer_pending != false) {
    info->xfer_ctrl = XFER_CTRL_XPENDING;
  }

  tx->data = data;
  tx->num  = num;
  tx->cnt  = 0U;

  mmr->I2CMCON = (uint16_t)(I2CMCON_IENACK   |
                            I2CMCON_IENALOST |
                            I2CMCON_IENMTX   |
                            I2CMCON_MASEN);
  mmr->I2CADR0 = (uint16_t)((addr << 1) & I2CADR0_ADR0_Msk);

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2Cx_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending, I2C_RESOURCES *i2c)
 * @brief       Start receiving data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[out]  data          Pointer to buffer for data to receive from I2C Slave
 * @param[in]   num           Number of data bytes to receive
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return                    \ref execution_status
 */
static
int32_t I2C_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_Resources_t *i2c)
{
  ADI_I2C_TypeDef *reg = i2c->reg;
  I2C_CTRL *ctrl = i2c->ctrl;

  if (!data || !num || (num > 256) || (addr > 0x7F)) {
    /* Invalid parameters */
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(ctrl->flags & I2C_FLAG_SETUP)) {
    /* Driver not yet configured */
    return ARM_DRIVER_ERROR;
  }

  if (ctrl->status.busy) {
    /* Transfer operation in progress */
    return ARM_DRIVER_ERROR_BUSY;
  }

  /* Set control variables */
  ctrl->flags &= ~(I2C_FLAG_TX_RESTART | I2C_FLAG_RX_RESTART);
  if (xfer_pending)
    ctrl->flags |= I2C_FLAG_RX_RESTART;
  ctrl->data = data;
  ctrl->num = num;
  ctrl->cnt = 0;

  /* Update driver status */
  ctrl->status.busy             = 1U;
  ctrl->status.mode             = MASTER_MODE;
  ctrl->status.direction        = RX_DIRECTION;
  ctrl->status.arbitration_lost = 0U;
  ctrl->status.bus_error        = 0U;

  reg->I2CMCON |= (I2CMCON_IENMRX | I2CMCON_MASEN);

  reg->I2CMRXCNT = num - 1;
  reg->I2CADR0 = (addr << 1) | 0x01;

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t I2Cx_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
 * @brief       Start transmitting data as I2C Slave.
 * @param[in]   data  Pointer to buffer with data to transmit to I2C Master
 * @param[in]   num   Number of data bytes to transmit
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_Resources_t *i2c)
{
  I2C_CTRL *ctrl = i2c->ctrl;

  if (!data || !num) {
    /* Invalid parameters */
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (ctrl->status.busy) {
    /* Transfer operation in progress */
    return ARM_DRIVER_ERROR_BUSY;
  }

  /* Set control variables */
  ctrl->data  = (uint8_t *)data;
  ctrl->num   = num;
  ctrl->data_cnt = 0;

  if (ctrl->flags & I2C_FLAG_SLAVE_BUF_EMPTY) {
    ctrl->flags &= ~I2C_FLAG_SLAVE_BUF_EMPTY;
    /* Enable slave transmit request interrupt */
    i2c->reg->I2CSCON |= I2CSCON_IENSTX;
  }
  else {
    ctrl->flags &= ~I2C_FLAG_SLAVE_RX;
    ctrl->cnt   = -1;

    /* Update driver status */
    ctrl->status.general_call = 0;
    ctrl->status.bus_error    = 0;
  }

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t I2Cx_SlaveReceive(uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
 * @brief       Start receiving data as I2C Slave.
 * @param[out]  data  Pointer to buffer for data to receive from I2C Master
 * @param[in]   num   Number of data bytes to receive
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2C_SlaveReceive(uint8_t *data, uint32_t num, I2C_Resources_t *i2c)
{
  I2C_CTRL *ctrl = i2c->ctrl;

  if (!data || !num) {
    /* Invalid parameters */
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (ctrl->status.busy) {
    /* Transfer operation in progress */
    return ARM_DRIVER_ERROR_BUSY;
  }

  /* Set control variables */
  ctrl->flags |= I2C_FLAG_SLAVE_RX;
  ctrl->data  = data;
  ctrl->num   = num;
  ctrl->cnt   = -1;

  /* Update driver status */
  ctrl->status.general_call = 0;
  ctrl->status.bus_error    = 0;

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t I2Cx_GetDataCount(I2C_RESOURCES *i2c)
 * @brief       Get transferred data count.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      Number of data bytes transferred;
 *              -1 when Slave is not addressed by Master
 */
static
int32_t I2C_GetDataCount(I2C_Resources_t *i2c)
{
  int32_t cnt = i2c->ctrl->cnt;
  I2C_CTRL *ctrl = i2c->ctrl;

  if ((ctrl->status.direction == TX_DIRECTION) && (cnt > 0)) {
    int32_t fifo_cnt;

    if (ctrl->status.mode == SLAVE_MODE) {
      fifo_cnt = GetSlaveTxFifoCnt(i2c);
    }
    else {
      fifo_cnt = GetMasterTxFifoCnt(i2c);
    }

    cnt -= fifo_cnt;
  }

  return cnt;
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
  uint32_t event  = 0UL;
  register ADI_I2C_TypeDef *reg = i2c->reg;
  register I2C_CTRL *ctrl = i2c->ctrl;
  uint16_t status = reg->I2CMSTA;

  if (status & I2CMSTA_MBUSY) {
    if (status & I2CMSTA_MTXREQ) {
      if (ctrl->cnt < ctrl->num) {
        reg->I2CMTX = ctrl->data[ctrl->cnt++];

        if (ctrl->cnt == ctrl->num) {
          reg->I2CMCON &= ~I2CMCON_IENMTX;

          if (ctrl->flags & I2C_FLAG_TX_RESTART) {
            ctrl->status.busy = 0;
            event = ARM_I2C_EVENT_TRANSFER_DONE;
          }
        }
      }
    }
    else if (status & I2CMSTA_MRXREQ) {
      uint32_t rx_cnt = GetMasterRxFifoCnt(i2c);

      while (rx_cnt--) {
        ctrl->data[ctrl->cnt++] = (uint8_t)reg->I2CMRX;
      }

      if (ctrl->cnt == ctrl->num) {
        if (ctrl->flags & I2C_FLAG_RX_RESTART) {
          ctrl->status.busy = 0;
          event = ARM_I2C_EVENT_TRANSFER_DONE;
        }
      }
    }
    else if (status & (I2CMSTA_NACKADDR | I2CMSTA_NACKDATA)) {
      if (ctrl->status.direction == TX_DIRECTION) {
        uint32_t fifo_cnt = GetMasterTxFifoCnt(i2c);

        if (fifo_cnt != 0) {
          ctrl->cnt -= fifo_cnt;
          reg->I2CFSTA = I2CFSTA_MFLUSH;
        }
      }

      if (status & I2CMSTA_NACKADDR) {
        ctrl->cnt--;
        ctrl->flags |= I2C_FLAG_ADDRESS_NACK;
      }
    }
    else if (status & I2CMSTA_ALOST) {
      ctrl->status.arbitration_lost = 1U;
    }
  }
  else if (status & I2C0MSTA_MSTOP) {
    reg->I2CMCON &= ~I2CMCON_MASEN;

    event = ARM_I2C_EVENT_TRANSFER_DONE;

    if (ctrl->flags & I2C_FLAG_ADDRESS_NACK)
      event |= ARM_I2C_EVENT_ADDRESS_NACK;

    if (ctrl->status.arbitration_lost == 1U)
      event |= ARM_I2C_EVENT_ARBITRATION_LOST;

    if (ctrl->cnt < ctrl->num)
      event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;

    ctrl->data = NULL;
    ctrl->flags &= ~(I2C_FLAG_TX_RESTART | I2C_FLAG_RX_RESTART | I2C_FLAG_ADDRESS_NACK);
    ctrl->status.busy = 0U;
    ctrl->status.mode = SLAVE_MODE;
  }

  /* Callback event notification */
  if (event && ctrl->cb_event) {
    ctrl->cb_event(event);
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
  uint32_t event  = 0U;
  register ADI_I2C_TypeDef *reg = i2c->reg;
  register I2C_CTRL *ctrl = i2c->ctrl;
  uint16_t status = reg->I2CSSTA;

  if (status & I2CSSTA_SBUSY) {
    if (status & I2CSSTA_REPSTART) {
      goto stop;
    }
    
		if (!(ctrl->flags & I2C_FLAG_SLAVE_ADDR)) {
      if (status & I2CSSTA_STXREQ) {
        ctrl->status.direction = TX_DIRECTION;
        event = ARM_I2C_EVENT_SLAVE_TRANSMIT;
      }
      else if (status & I2CSSTA_SRXREQ) {
        ctrl->status.direction = RX_DIRECTION;
        event = ARM_I2C_EVENT_SLAVE_RECEIVE;
      }

      if ((ctrl->data == NULL) ||
          ((status & I2CSSTA_STXREQ) && (ctrl->flags & I2C_FLAG_SLAVE_RX)) ||
          ((status & I2CSSTA_SRXREQ) && !(ctrl->flags & I2C_FLAG_SLAVE_RX)))
      {
        /* Buffer unavailable */
        if (ctrl->cb_event) {
          ctrl->cb_event(event);
        }
      }

      event = 0;
      ctrl->status.busy = 1;
      ctrl->cnt = 0;
      ctrl->flags |= I2C_FLAG_SLAVE_ADDR;
    }

    if (status & I2CSSTA_STXREQ) {
      reg->I2CSTX = ctrl->data[ctrl->data_cnt++];
      ctrl->cnt++;

      if (ctrl->data_cnt == ctrl->num) {
        /* Disable slave transmit request interrupt */
        reg->I2CSCON &= ~I2CSCON_IENSTX;
        ctrl->status.busy = 0;
        ctrl->flags |= I2C_FLAG_SLAVE_BUF_EMPTY;
        event = ARM_I2C_EVENT_SLAVE_TRANSMIT;
      }
    }
    else if (status & I2CSSTA_SRXREQ) {
      uint8_t rx_data = (uint8_t)reg->I2CSRX;

      if (ctrl->cnt < ctrl->num) {
        ctrl->data[ctrl->cnt++] = rx_data;
      }
    }
  }
  else if (status & I2CSSTA_STOP) {
    /* STOP received */
stop:
    if (ctrl->status.direction == TX_DIRECTION) {
      uint32_t fifo_cnt = GetSlaveTxFifoCnt(i2c);

      if (fifo_cnt != 0) {
        ctrl->cnt -= fifo_cnt;
        reg->I2CFSTA = I2CFSTA_SFLUSH;
      }

      /* Enable slave transmit request interrupt */
      reg->I2CSCON |= I2CSCON_IENSTX;
    }

    ctrl->status.busy = 0;
    /* Slave operation completed, generate events */
    event = ARM_I2C_EVENT_TRANSFER_DONE;

    if (ctrl->status.general_call) {
      event |= ARM_I2C_EVENT_GENERAL_CALL;
    }

    if (ctrl->cnt < ctrl->num) {
      event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    }

    ctrl->data = NULL;
    ctrl->flags &= ~(I2C_FLAG_SLAVE_ADDR | I2C_FLAG_SLAVE_BUF_EMPTY);
  }


  /* Callback event notification */
  if (event && ctrl->cb_event) {
    ctrl->cb_event(event);
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
