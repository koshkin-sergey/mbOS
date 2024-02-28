/*
 * Copyright (C) 2017-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#define SCL_HIGH_TIME_100K        (5000U) // HIGH period of the SCL clock in ns.
#define SCL_LOW_TIME_100K         (5000U) // LOW period of the SCL clock in ns.

#define SCL_HIGH_TIME_400K        (1200U) // HIGH period of the SCL clock in ns.
#define SCL_LOW_TIME_400K         (1300U) // LOW period of the SCL clock in ns.

#define SCL_TIME_CLR              (SCL_LOW_TIME_100K / 1000U)

#define CLOCK_STRETCH_TIME        (5)

#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,1) /* driver version */

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

static const GPIO_PIN_CFG_t pin_cfg_gpio_in = {
  GPIO_PIN_FUNC_0,
  GPIO_MODE_ANALOG,
  GPIO_PULL_DISABLE,
};

static const GPIO_PIN_CFG_t pin_cfg_gpio_od = {
  GPIO_PIN_FUNC_0,
  GPIO_MODE_OUT_OD,
  GPIO_PULL_DISABLE,
};

#if defined(USE_I2C0)
/* I2C0 Information (Run-Time) */
static I2C_Info_t I2C0_Info;

/* I2C0 Resources */
static I2C_Resources_t I2C0_Resources = {
  MMR_I2C0,
  {
    {
      I2C0_SCL_GPIO_PORT,
      I2C0_SCL_GPIO_PIN,
      {
        I2C0_SCL_GPIO_FUNC,
        GPIO_MODE_ANALOG,
        GPIO_PULL_DISABLE,
      }
    },
    {
      I2C0_SDA_GPIO_PORT,
      I2C0_SDA_GPIO_PIN,
      {
        I2C0_SDA_GPIO_FUNC,
        GPIO_MODE_ANALOG,
        GPIO_PULL_DISABLE,
      }
    },
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
    {
      I2C1_SCL_GPIO_PORT,
      I2C1_SCL_GPIO_PIN,
      {
        I2C1_SCL_GPIO_FUNC,
        GPIO_MODE_ANALOG,
        GPIO_PULL_DISABLE,
      }
    },
    {
      I2C1_SDA_GPIO_PORT,
      I2C1_SDA_GPIO_PIN,
      {
        I2C1_SDA_GPIO_FUNC,
        GPIO_MODE_ANALOG,
        GPIO_PULL_DISABLE,
      }
    },
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
void delay(uint32_t us)
{
  const uint32_t timeout = MicroSecToSysTimerCount(us);
  const uint32_t tick = GetSysTimerCount();

  while ((GetSysTimerCount() - tick) < timeout) {
    __NOP();
  };
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
  I2C_Info_t *info;
  I2C_IO_t   *io;

  if (i2c->info->flags & I2C_FLAG_INIT) {
    return (ARM_DRIVER_OK);
  }

  io   = &i2c->io;
  info = i2c->info;

  /* Configure SCL Pin */
  io->scl.gpio->PinConfig(io->scl.pin, &io->scl.cfg);

  /* Configure SDA Pin */
  io->sda.gpio->PinConfig(io->sda.pin, &io->sda.cfg);

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
  I2C_IO_t *io = &i2c->io;

  /* Unconfigure SCL Pin */
  io->scl.gpio->PinConfig(io->scl.pin, &pin_cfg_gpio_in);

  /* Unconfigure SDA Pin */
  io->sda.gpio->PinConfig(io->sda.pin, &pin_cfg_gpio_in);

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

    case ARM_POWER_LOW:
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
        reg_val = I2CSCON_IENSRX   |
                  I2CSCON_IENSTX   |
                  I2CSCON_IENSTOP  |
                  I2CSCON_EARLYTXR |
                  I2CSCON_SLVEN;

        if (arg & ARM_I2C_ADDRESS_GC) {
          /* General call enable */
          reg_val |= I2CSCON_GCEN;
        }
      }

      mmr->I2CID0  = (uint16_t)((arg << 1) & 0xFFU);
      mmr->I2CSCON = reg_val;
      mmr->I2CASSCL |= (uint16_t)_VAL2FLD(I2CASSCL_SSTRCON, CLOCK_STRETCH_TIME);
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
      mmr->I2CASSCL |= (uint16_t)_VAL2FLD(I2CASSCL_MSTRCON, CLOCK_STRETCH_TIME);

      /* Master configured, clock set */
      info->flags |= I2C_FLAG_SETUP;
    }
      break;

    case ARM_I2C_BUS_CLEAR:
      /* Disable I2C interrupts */
      NVIC_DisableIRQ(i2c->irq.master_num);

      {
        I2C_IO_t *io = &i2c->io;

        /* Configure SDA Pin as GPIO */
        io->sda.gpio->PinWrite(io->sda.pin, GPIO_PIN_OUT_HIGH);
        io->sda.gpio->PinConfig(io->sda.pin, &pin_cfg_gpio_od);

        /* Configure SCL Pin as GPIO */
        io->scl.gpio->PinWrite(io->scl.pin, GPIO_PIN_OUT_HIGH);
        io->scl.gpio->PinConfig(io->scl.pin, &pin_cfg_gpio_od);

        for (uint32_t i = 0; i < 9U; ++i) {
          if (io->sda.gpio->PinRead(io->sda.pin) != 0U) {
            break;
          }

          io->scl.gpio->PinWrite(io->scl.pin, GPIO_PIN_OUT_LOW);
          delay(SCL_TIME_CLR);
          io->scl.gpio->PinWrite(io->scl.pin, GPIO_PIN_OUT_HIGH);
          delay(SCL_TIME_CLR);
        }

        io->scl.gpio->PinWrite(io->scl.pin, GPIO_PIN_OUT_LOW);
        io->sda.gpio->PinWrite(io->sda.pin, GPIO_PIN_OUT_LOW);
        delay(SCL_TIME_CLR);

        /* Configure SCL Pin as I2C */
        io->scl.gpio->PinConfig(io->scl.pin, &io->scl.cfg);
        delay(SCL_TIME_CLR);
        /* Configure SDA Pin as I2C */
        io->sda.gpio->PinConfig(io->sda.pin, &io->sda.cfg);
      }

      /* Disable I2C master */
      mmr->I2CMCON = 0U;
      /* Reset I2C block */
      mmr->I2CSHCON |= I2CSHCON_RESET;

      info->status = 0U;
      info->xfer   = 0U;

      /* Enable I2C interrupts */
      NVIC_ClearPendingIRQ(i2c->irq.master_num);
      NVIC_EnableIRQ(i2c->irq.master_num);
      break;

    case ARM_I2C_ABORT_TRANSFER:
    {
      IRQn_Type irq_num;

      if ((info->status & I2C_STATUS_MASTER) != 0U) {
        irq_num = i2c->irq.master_num;

        /* Disable I2C interrupts */
        NVIC_DisableIRQ(irq_num);

        if ((info->status & I2C_STATUS_RECEIVER) == 0U) {
          mmr->I2CMCON &= (uint16_t)~I2CMCON_IENMTX;
          mmr->I2CFSTA = I2CFSTA_MFLUSH;
        }
        else {
          mmr->I2CMRXCNT = 0U;
        }
      }
      else {
        irq_num = i2c->irq.slave_num;

        /* Disable I2C interrupts */
        NVIC_DisableIRQ(irq_num);

        /* Flush the Slave TX FIFO */
        mmr->I2CFSTA = I2CFSTA_SFLUSH;
      }

      info->status = 0U;
      info->xfer   = 0U;

      /* Enable I2C interrupts */
      NVIC_ClearPendingIRQ(irq_num);
      NVIC_EnableIRQ(irq_num);
    }
      break;

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
  I2C_XferInfo_t *xx = &info->tx;

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

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Disable I2C interrupts */
  NVIC_DisableIRQ(i2c->irq.master_num);

  info->status = I2C_STATUS_BUSY | I2C_STATUS_MASTER;
  info->xfer = xfer_pending ? XFER_PENDING : 0U;

  xx->data = (uint8_t *)data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Enable master and transmit interrupt */
  mmr->I2CMCON = I2CMCON_MASEN | I2CMCON_IENMTX | I2CMCON_IENALOST | I2CMCON_IENACK | I2CMCON_IENCMP;
  /* Fill the Master TX FIFO */
  while ((mmr->I2CFSTA & I2CFSTA_MTXFSTA_Msk) != I2CFSTA_MTXFSTA_TWOBYTES && xx->cnt < xx->num) {
    mmr->I2CMTX = xx->data[xx->cnt++];
  }
  /* Set slave address, transfer direction and generate start */
  mmr->I2CADR0 = (addr << 1) & I2CADR0_ADR0_Msk;

  /* Enable I2C interrupts */
  NVIC_EnableIRQ(i2c->irq.master_num);

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
  I2C_XferInfo_t *xx = &info->rx;

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

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Disable I2C interrupts */
  NVIC_DisableIRQ(i2c->irq.master_num);

  info->status = I2C_STATUS_BUSY | I2C_STATUS_MASTER | I2C_STATUS_RECEIVER;
  info->xfer = xfer_pending ? XFER_PENDING : 0U;

  xx->data = data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Enable master and receive interrupt */
  mmr->I2CMCON = I2CMCON_MASEN | I2CMCON_IENMRX | I2CMCON_IENALOST | I2CMCON_IENACK | I2CMCON_IENCMP;
  /* Set number of bytes to transfer */
  mmr->I2CMRXCNT = (num - 1U) & I2CMRXCNT_COUNT_Msk;
  /* Set slave address, transfer direction and generate start */
  mmr->I2CADR0 = ((addr << 1) | 1UL) & I2CADR0_ADR0_Msk;

  /* Enable I2C interrupts */
  NVIC_EnableIRQ(i2c->irq.master_num);

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
  I2C_XferInfo_t *xx = &info->tx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Disable I2C interrupts */
  NVIC_DisableIRQ(i2c->irq.slave_num);

  info->status = 0U;
  info->xfer = 0U;

  xx->data = (uint8_t *)data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Fill the Slave TX FIFO */
  while ((mmr->I2CFSTA & I2CFSTA_STXFSTA_Msk) != I2CFSTA_STXFSTA_TWOBYTES && xx->cnt < xx->num) {
    mmr->I2CSTX = xx->data[xx->cnt++];
  }

  /* Enable TX interrupt */
  mmr->I2CSCON |= I2CSCON_IENSTX;

  /* Enable I2C interrupts */
  NVIC_EnableIRQ(i2c->irq.slave_num);

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
  I2C_Info_t *info = i2c->info;
  I2C_XferInfo_t *xx = &info->rx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    /* Transfer operation in progress */
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Disable I2C interrupts */
  NVIC_DisableIRQ(i2c->irq.slave_num);

  info->status = 0U;
  info->xfer = 0U;

  xx->data = data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Enable I2C interrupts */
  NVIC_EnableIRQ(i2c->irq.slave_num);

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
  I2C_XferInfo_t *xx;
  I2C_Info_t     *info = i2c->info;

  if ((info->status & I2C_STATUS_MASTER) == 0U &&
      (info->xfer   & XFER_SLAVE_ADDR  ) == 0U)
  {
    return (-1);
  }

  xx = info->status & I2C_STATUS_RECEIVER ? &info->rx : &info->tx;

  return ((int32_t)xx->cnt);
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
  register uint32_t  event;
  register uint32_t  cntrl;
  I2C_XferInfo_t    *xx;
  I2C_Info_t        *info = i2c->info;
  MMR_I2C_t         *mmr  = i2c->mmr;

  state = mmr->I2CMSTA;
  cntrl = mmr->I2CMCON;
  event = 0U;

  /* Bus Error */
  if ((state & (I2CMSTA_TCOMP | I2CMSTA_MBUSY | I2CMSTA_LINEBUSY)) == I2CMSTA_MBUSY) {
    /* Disable master */
    cntrl = 0U;
    info->status = (info->status & ~I2C_STATUS_BUSY) | I2C_STATUS_BUS_ERROR;
    event = ARM_I2C_EVENT_BUS_ERROR      |
            ARM_I2C_EVENT_TRANSFER_DONE  |
            ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    goto error;
  }

  /* Arbitration lost Error */
  if ((state & I2CMSTA_ALOST) != 0U) {
    /* Disable master */
    cntrl = 0U;
    info->status = (info->status & ~(I2C_STATUS_BUSY | I2C_STATUS_MASTER)) |
                   I2C_STATUS_ARBITRATION_LOST;
    event = ARM_I2C_EVENT_ARBITRATION_LOST |
            ARM_I2C_EVENT_TRANSFER_DONE    |
            ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    goto error;
  }

  if ((state & I2CMSTA_NACKADDR) != 0U) {
    info->xfer |= XFER_MASTER_NADDR;
  }

  if ((state & I2CMSTA_NACKDATA) != 0U) {
    info->xfer |= XFER_MASTER_NDATA;
  }

  if ((state & I2CMSTA_MTXREQ) != 0U) {
    xx = &info->tx;
    /* Fill the Master TX FIFO */
    while ((mmr->I2CFSTA & I2CFSTA_MTXFSTA_Msk) != I2CFSTA_MTXFSTA_TWOBYTES && xx->cnt < xx->num) {
      mmr->I2CMTX = xx->data[xx->cnt++];
    }
    if (xx->cnt == xx->num) {
      if ((info->xfer & XFER_PENDING) != 0U) {
        if (xx->num == 1U && (mmr->I2CFSTA & I2CFSTA_MTXFSTA_Msk) != I2CFSTA_MTXFSTA_EMPTY) {
          return;
        }
        info->status &= ~I2C_STATUS_BUSY;
        event |= ARM_I2C_EVENT_TRANSFER_DONE;
      }
      cntrl &= ~I2CMCON_IENMTX;
    }
  }

  if ((state & I2CMSTA_MRXREQ) != 0U) {
    xx = &info->rx;
    do {
      uint8_t data = (uint8_t)mmr->I2CMRX;
      if (xx->cnt < xx->num) {
        xx->data[xx->cnt++] = data;
        if (xx->cnt == xx->num) {
          if ((info->xfer & XFER_PENDING) != 0U) {
            info->status &= ~I2C_STATUS_BUSY;
            event |= ARM_I2C_EVENT_TRANSFER_DONE;
          }
          cntrl &= ~I2CMCON_IENMRX;
        }
      }
    } while ((mmr->I2CFSTA & I2CFSTA_MRXFSTA_Msk) != I2CFSTA_MRXFSTA_EMPTY);
  }

  if ((state & (I2CMSTA_TCOMP | I2CMSTA_MBUSY)) == I2CMSTA_TCOMP) {
    /* Disable master */
    cntrl = 0U;

    if ((info->status & I2C_STATUS_BUSY) != 0U) {
      info->status &= ~I2C_STATUS_BUSY;
      event |= ARM_I2C_EVENT_TRANSFER_DONE;

      xx = info->status & I2C_STATUS_RECEIVER ? &info->rx : &info->tx;

      if ((info->xfer & (XFER_MASTER_NADDR | XFER_MASTER_NDATA)) != 0U) {
        if ((info->xfer & XFER_MASTER_NADDR) != 0U) {
          event |= ARM_I2C_EVENT_ADDRESS_NACK;
          xx->cnt = 0U;
        }
        else {
          xx->cnt -= _FLD2VAL(I2CFSTA_MTXFSTA, mmr->I2CFSTA) + 1U;
        }
        mmr->I2CFSTA = I2CFSTA_MFLUSH;
      }

      if (xx->cnt < xx->num) {
        event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
      }
    }
  }

error:
  mmr->I2CMCON = (uint16_t)cntrl;

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
  I2C_XferInfo_t    *xx;
  I2C_Info_t        *info = i2c->info;
  MMR_I2C_t         *mmr  = i2c->mmr;

  state = mmr->I2CSSTA;

  /* General call status */
  if ((state & I2CSSTA_GCINT) != 0U) {
    info->status |= I2C_STATUS_GENERAL_CALL;
    mmr->I2CSCON |= I2CSCON_GCSBCLR;
  }

  /* Slave Transmit request */
  if ((state & I2CSSTA_STXREQ) != 0U) {
    xx = &info->tx;
    if ((info->xfer & XFER_SLAVE_TX) == 0U) {
      if (xx->num == 0U) {
        mmr->I2CSCON &= (uint16_t)~I2CSCON_IENSTX;
        if (info->cb_event != NULL) {
          info->status &= ~I2C_STATUS_BUSY;
          info->cb_event(ARM_I2C_EVENT_SLAVE_TRANSMIT);
        }
      }

      info->status |= I2C_STATUS_BUSY;
      info->xfer |= XFER_SLAVE_ADDR | XFER_SLAVE_TX;
    }

    if (xx->num != 0U) {
      while ((mmr->I2CFSTA & I2CFSTA_STXFSTA_Msk) != I2CFSTA_STXFSTA_TWOBYTES && xx->cnt < xx->num) {
        mmr->I2CSTX = xx->data[xx->cnt++];
      }
      if (xx->cnt == xx->num) {
        mmr->I2CSCON &= (uint16_t)~I2CSCON_IENSTX;
        info->status &= ~I2C_STATUS_BUSY;
        info->xfer &= (uint16_t)~XFER_SLAVE_TX;
        xx->num = 0U;
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

  /* Slave Receive request */
  if ((state & I2CSSTA_SRXREQ) != 0U) {
    xx = &info->rx;
    do {
      uint8_t data = (uint8_t)mmr->I2CSRX;

      if ((info->xfer & XFER_SLAVE_RX) == 0U) {
        if (xx->num == 0U) {
          if (info->cb_event != NULL) {
            info->status &= ~I2C_STATUS_BUSY;
            info->cb_event(ARM_I2C_EVENT_SLAVE_RECEIVE);
          }
        }

        info->status |= I2C_STATUS_RECEIVER | I2C_STATUS_BUSY;
        info->xfer |= XFER_SLAVE_ADDR | XFER_SLAVE_RX;
      }

      if (xx->num != 0U && xx->cnt < xx->num) {
        xx->data[xx->cnt++] = data;
        if (xx->cnt == xx->num) {
          info->status &= ~I2C_STATUS_BUSY;
          info->xfer &= (uint16_t)~XFER_SLAVE_RX;
          xx->num = 0U;
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
    } while ((mmr->I2CFSTA & I2CFSTA_SRXFSTA_Msk) != I2CFSTA_SRXFSTA_EMPTY);
  }

  /* Slave Stop Condition */
  if ((state & I2CSSTA_STOP) != 0U) {
    if ((info->status & I2C_STATUS_BUSY) != 0U) {
      info->status &= ~I2C_STATUS_BUSY;
      info->xfer &= (uint16_t)~(XFER_SLAVE_TX | XFER_SLAVE_RX);
      event = ARM_I2C_EVENT_TRANSFER_DONE;

      xx = info->status & I2C_STATUS_RECEIVER ? &info->rx : &info->tx;
      if (xx->cnt < xx->num) {
        event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
      }

      xx->num = 0U;

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
