/*
 * Copyright (C) 2017 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <string.h>
#include "I2C_ADuCM320.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define SLAVE_MODE      0U
#define MASTER_MODE     1U
#define TX_DIRECTION    0U
#define RX_DIRECTION    1U

#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

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

/* I2C0 Control Information */
static I2C_CTRL I2C0_Ctrl = { 0 };

static const GPIO_PIN_ID_t I2C0_pin_scl = {
    I2C0_SCL_GPIO_PORT, I2C0_SCL_GPIO_PIN, I2C0_SCL_GPIO_FUNC
};

static const GPIO_PIN_ID_t I2C0_pin_sda = {
    I2C0_SDA_GPIO_PORT, I2C0_SDA_GPIO_PIN, I2C0_SDA_GPIO_FUNC
};

/* I2C0 Resources */
static I2C_RESOURCES I2C0_Resources = {
  pADI_I2C0,
  {
      &I2C0_pin_scl,
      &I2C0_pin_sda,
  },
  I2C0M_IRQn,
  I2C0S_IRQn,
  CLK_PERIPH_I2C0,
  &I2C0_Ctrl,
};
#endif /* USE_I2C0 */


#if defined(USE_I2C1)

/* I2C1 Control Information */
static I2C_CTRL I2C1_Ctrl = { 0 };

static const GPIO_PIN_ID_t I2C1_pin_scl = {
    I2C1_SCL_GPIO_PORT, I2C1_SCL_GPIO_PIN, I2C1_SCL_GPIO_FUNC
};

static const GPIO_PIN_ID_t I2C1_pin_sda = {
    I2C1_SDA_GPIO_PORT, I2C1_SDA_GPIO_PIN, I2C1_SDA_GPIO_FUNC
};

/* I2C1 Resources */
static I2C_RESOURCES I2C1_Resources = {
  pADI_I2C1,
  {
      &I2C1_pin_scl,
      &I2C1_pin_sda,
  },
  I2C1M_IRQn,
  I2C1S_IRQn,
  CLK_PERIPH_I2C1,
  &I2C1_Ctrl,
};
#endif /* USE_I2C1 */

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 *
 * @param i2c
 * @return
 */
__attribute__((always_inline)) static
uint32_t GetMasterRxFifoCnt(I2C_RESOURCES *i2c)
{
  return ((i2c->reg->I2CFSTA & I2CFSTA_MRXFSTA_MSK) >> 6);
}

/**
 *
 * @param i2c
 * @return
 */
__attribute__((always_inline)) static
uint32_t GetMasterTxFifoCnt(I2C_RESOURCES *i2c)
{
  return ((i2c->reg->I2CFSTA & I2CFSTA_MTXFSTA_MSK) >> 4);
}

/**
 *
 * @param i2c
 * @return
 */
__attribute__((always_inline)) static
uint32_t GetSlaveTxFifoCnt(I2C_RESOURCES *i2c)
{
  return (i2c->reg->I2CFSTA & I2CFSTA_STXFSTA_MSK);
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
int32_t I2Cx_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_RESOURCES *i2c)
{
  I2C_CTRL *ctrl = i2c->ctrl;
  I2C_PIN *pin = &i2c->pin;

  if (ctrl->flags & I2C_FLAG_INIT) {
    return ARM_DRIVER_OK;
  }

  /* Configure SCL Pin */
  GPIO_AFConfig(pin->scl->port, pin->scl->pin, pin->scl->func);
  /* Configure SDA Pin */
  GPIO_AFConfig(pin->sda->port, pin->sda->pin, pin->sda->func);

  /* Reset Run-Time information structure */
  memset(ctrl, 0x00, sizeof(I2C_CTRL));

  ctrl->cb_event = cb_event;
  ctrl->flags    = I2C_FLAG_INIT;

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t I2Cx_Uninitialize(I2C_RESOURCES *i2c)
 * @brief       De-initialize I2C Interface.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2Cx_Uninitialize(I2C_RESOURCES *i2c)
{
  I2C_PIN *pin = &i2c->pin;

  /* Unconfigure SCL Pin */
  GPIO_AFConfig(pin->scl->port, pin->scl->pin, GPIO_PIN_FUNC_0);
  /* Unconfigure SDA Pin */
  GPIO_AFConfig(pin->sda->port, pin->sda->pin, GPIO_PIN_FUNC_0);

  i2c->ctrl->flags = 0;

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
int32_t I2Cx_PowerControl(ARM_POWER_STATE state, I2C_RESOURCES *i2c)
{
  ADI_I2C_TypeDef *reg = i2c->reg;
  I2C_CTRL *ctrl = i2c->ctrl;

  switch (state) {
    case ARM_POWER_OFF:
      /* Disable I2C interrupts */
      NVIC_Disable_IRQ(i2c->i2c_master_irq);
      NVIC_Disable_IRQ(i2c->i2c_slave_irq);

      ctrl->status.busy             = 0U;
      ctrl->status.mode             = 0U;
      ctrl->status.direction        = 0U;
      ctrl->status.general_call     = 0U;
      ctrl->status.arbitration_lost = 0U;
      ctrl->status.bus_error        = 0U;

      ctrl->num = 0U;

      ctrl->flags  &= ~I2C_FLAG_POWER;

      /* Reset I2C peripheral */
      reg->I2CMCON &= ~I2CMCON_MASEN;
      reg->I2CSCON &= ~I2CSCON_SLVEN;
      reg->I2CSHCON |= I2CSHCON_RESET;

      /* Disable I2C peripheral clock */
      CLK_PeriphGateControl(i2c->clk_periph, CLOCK_OFF);
      break;

    case ARM_POWER_FULL:
      if ((ctrl->flags & I2C_FLAG_INIT) == 0U) {
        return ARM_DRIVER_ERROR;
      }

      if ((ctrl->flags & I2C_FLAG_POWER) != 0U) {
        return ARM_DRIVER_OK;
      }

      /* Enable I2C peripheral clock */
      CLK_PeriphGateControl(i2c->clk_periph, CLOCK_ON);

      /* Reset I2C peripheral */
      reg->I2CMCON &= ~I2CMCON_MASEN;
      reg->I2CSCON &= ~I2CSCON_SLVEN;
      reg->I2CSHCON |= I2CSHCON_RESET;

      /* Enable I2C interrupts */
      NVIC_ClearPendingIRQ(i2c->i2c_master_irq);
      NVIC_ClearPendingIRQ(i2c->i2c_slave_irq);
      NVIC_Enable_IRQ(i2c->i2c_master_irq, HAL_I2C_INT_PRIO);
      NVIC_Enable_IRQ(i2c->i2c_slave_irq, HAL_I2C_INT_PRIO);

      ctrl->flags |= I2C_FLAG_POWER;
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
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
int32_t I2Cx_Control(uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
{
  ADI_I2C_TypeDef *reg = i2c->reg;
  I2C_CTRL *ctrl = i2c->ctrl;

  if (!(ctrl->flags & I2C_FLAG_POWER)) {
    /* Driver not powered */
    return ARM_DRIVER_ERROR;
  }

  switch (control) {
    case ARM_I2C_OWN_ADDRESS:
      /* Set Own Slave Address */
      if (arg == 0) {
        /* Disable slave */
        reg->I2CSCON = 0;
      }
      else {
        uint16_t val = (I2CSCON_IENREPST | I2CSCON_IENSRX | I2CSCON_IENSTX |
            I2CSCON_IENSTOP | I2CSCON_EARLYTXR | I2CSCON_SLVEN);

        if (arg & ARM_I2C_ADDRESS_GC) {
          /* General call enable */
          val |= I2CSCON_GCEN;
        }

        reg->I2CID0 = (uint16_t)((arg << 1) & 0xFF);
        reg->I2CSCON = val;
      }
      break;

    case ARM_I2C_BUS_SPEED:
    {
      uint16_t div;
      uint32_t clk;

      /* Set Bus Speed */
      clk = CLK_GetFreqPCLK();

      switch (arg) {
        case ARM_I2C_BUS_SPEED_STANDARD:
          /* Standard Speed (100kHz) */
          clk /= 100000;
          break;
        case ARM_I2C_BUS_SPEED_FAST:
          /* Fast Speed     (400kHz) */
          clk /= 400000;
          break;
        default:
          return ARM_DRIVER_ERROR_UNSUPPORTED;
      }

      div = ((clk >> 1) - 1);
      div |= (((clk >> 1) - 2) << 8);

      reg->I2CDIV = div;
      reg->I2CMCON = (I2CMCON_IENCMP | I2CMCON_IENACK | I2CMCON_IENALOST);

      /* Speed configured, I2C Master active */
      ctrl->flags |= I2C_FLAG_SETUP;
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
int32_t I2Cx_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_RESOURCES *i2c)
{
  ADI_I2C_TypeDef *reg = i2c->reg;
  I2C_CTRL *ctrl = i2c->ctrl;

  if (!data || !num || (addr > 0x7F)) {
    /* Invalid parameters */
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(ctrl->flags & I2C_FLAG_SETUP)) {
    /* Driver not yet configured */
    return ARM_DRIVER_ERROR;
  }

  if (ctrl->flags & I2C_FLAG_TX_RESTART)
    return ARM_DRIVER_ERROR_UNSUPPORTED;

  if (ctrl->status.busy) {
    /* Transfer operation in progress */
    return ARM_DRIVER_ERROR_BUSY;
  }

  /* Set control variables */
  ctrl->flags &= ~(I2C_FLAG_TX_RESTART | I2C_FLAG_RX_RESTART);
  if (xfer_pending) {
    ctrl->flags |= I2C_FLAG_TX_RESTART;
  }
  ctrl->data = (uint8_t *)data;
  ctrl->num  = num;
  ctrl->cnt  = 0;

  /* Update driver status */
  ctrl->status.busy             = 1U;
  ctrl->status.mode             = MASTER_MODE;
  ctrl->status.direction        = TX_DIRECTION;
  ctrl->status.arbitration_lost = 0U;
  ctrl->status.bus_error        = 0U;

  reg->I2CMCON |= (I2CMCON_IENMTX | I2CMCON_MASEN);
  reg->I2CADR0 = (addr << 1) & 0xFE;

  return ARM_DRIVER_OK;
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
int32_t I2Cx_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_RESOURCES *i2c)
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
int32_t I2Cx_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
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
int32_t I2Cx_SlaveReceive(uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
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
int32_t I2Cx_GetDataCount(I2C_RESOURCES *i2c)
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
ARM_I2C_STATUS I2Cx_GetStatus(I2C_RESOURCES *i2c)
{
  return (i2c->ctrl->status);
}

/**
 * @fn          void I2Cx_MasterHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Master state event handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2Cx_MasterHandler(I2C_RESOURCES *i2c)
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
void I2Cx_SlaveHandler(I2C_RESOURCES *i2c)
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

#if defined(USE_I2C0)
/* I2C0 Driver wrapper functions */
/**
 *
 * @param cb_event
 * @return
 */
static
int32_t I2C0_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
  return (I2Cx_Initialize(cb_event, &I2C0_Resources));
}

/**
 *
 * @return
 */
static
int32_t I2C0_Uninitialize(void)
{
  return (I2Cx_Uninitialize(&I2C0_Resources));
}

/**
 *
 * @param state
 * @return
 */
static
int32_t I2C0_PowerControl(ARM_POWER_STATE state)
{
  return (I2Cx_PowerControl(state, &I2C0_Resources));
}

/**
 *
 * @param addr
 * @param data
 * @param num
 * @param xfer_pending
 * @return
 */
static
int32_t I2C0_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterTransmit(addr, data, num, xfer_pending, &I2C0_Resources));
}

/**
 *
 * @param addr
 * @param data
 * @param num
 * @param xfer_pending
 * @return
 */
static
int32_t I2C0_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterReceive(addr, data, num, xfer_pending, &I2C0_Resources));
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t I2C0_SlaveTransmit(const uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveTransmit(data, num, &I2C0_Resources));
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t I2C0_SlaveReceive(uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveReceive(data, num, &I2C0_Resources));
}

/**
 *
 * @return
 */
static
int32_t I2C0_GetDataCount(void)
{
  return (I2Cx_GetDataCount(&I2C0_Resources));
}

/**
 *
 * @param control
 * @param arg
 * @return
 */
static
int32_t I2C0_Control(uint32_t control, uint32_t arg)
{
  return (I2Cx_Control(control, arg, &I2C0_Resources));
}

/**
 *
 * @return
 */
static
ARM_I2C_STATUS I2C0_GetStatus(void)
{
  return (I2Cx_GetStatus(&I2C0_Resources));
}

/**
 *
 */
void I2C0_Slave_Int_Handler(void)
{
  I2Cx_SlaveHandler(&I2C0_Resources);
}

/**
 *
 */
void I2C0_Master_Int_Handler(void)
{
  I2Cx_MasterHandler(&I2C0_Resources);
}
#endif

#if defined(USE_I2C1)
/* I2C1 Driver wrapper functions */
/**
 *
 * @param cb_event
 * @return
 */
static
int32_t I2C1_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
  return (I2Cx_Initialize(cb_event, &I2C1_Resources));
}

/**
 *
 * @return
 */
static
int32_t I2C1_Uninitialize(void)
{
  return (I2Cx_Uninitialize(&I2C1_Resources));
}

/**
 *
 * @param state
 * @return
 */
static
int32_t I2C1_PowerControl(ARM_POWER_STATE state)
{
  return (I2Cx_PowerControl(state, &I2C1_Resources));
}

/**
 *
 * @param addr
 * @param data
 * @param num
 * @param xfer_pending
 * @return
 */
static
int32_t I2C1_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterTransmit(addr, data, num, xfer_pending, &I2C1_Resources));
}

/**
 *
 * @param addr
 * @param data
 * @param num
 * @param xfer_pending
 * @return
 */
static
int32_t I2C1_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterReceive(addr, data, num, xfer_pending, &I2C1_Resources));
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t I2C1_SlaveTransmit(const uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveTransmit(data, num, &I2C1_Resources));
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t I2C1_SlaveReceive(uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveReceive(data, num, &I2C1_Resources));
}

/**
 *
 * @return
 */
static
int32_t I2C1_GetDataCount(void)
{
  return (I2Cx_GetDataCount(&I2C1_Resources));
}

/**
 *
 * @param control
 * @param arg
 * @return
 */
static
int32_t I2C1_Control(uint32_t control, uint32_t arg)
{
  return (I2Cx_Control(control, arg, &I2C1_Resources));
}

/**
 *
 * @return
 */
static
ARM_I2C_STATUS I2C1_GetStatus(void)
{
  return (I2Cx_GetStatus(&I2C1_Resources));
}

/**
 *
 */
void I2C1_Slave_Int_Handler(void)
{
  I2Cx_SlaveHandler(&I2C1_Resources);
}

/**
 *
 */
void I2C1_Master_Int_Handler(void)
{
  I2Cx_MasterHandler(&I2C1_Resources);
}
#endif

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_I2C0)
/* I2C0 Driver Control Block */
ARM_DRIVER_I2C Driver_I2C0 = {
  I2C_GetVersion,
  I2C_GetCapabilities,
  I2C0_Initialize,
  I2C0_Uninitialize,
  I2C0_PowerControl,
  I2C0_MasterTransmit,
  I2C0_MasterReceive,
  I2C0_SlaveTransmit,
  I2C0_SlaveReceive,
  I2C0_GetDataCount,
  I2C0_Control,
  I2C0_GetStatus
};
#endif

#if defined(USE_I2C1)
/* I2C1 Driver Control Block */
ARM_DRIVER_I2C Driver_I2C1 = {
  I2C_GetVersion,
  I2C_GetCapabilities,
  I2C1_Initialize,
  I2C1_Uninitialize,
  I2C1_PowerControl,
  I2C1_MasterTransmit,
  I2C1_MasterReceive,
  I2C1_SlaveTransmit,
  I2C1_SlaveReceive,
  I2C1_GetDataCount,
  I2C1_Control,
  I2C1_GetStatus
};
#endif

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/* ----------------------------- End of file ---------------------------------*/
