/*
 * Copyright (C) 2021-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

static const GPIO_PIN_CFG_t pin_cfg_gpio_in = {
    GPIO_PIN_FUNC_0, GPIO_MODE_INPUT, GPIO_PULL_DISABLE, GPIO_STRENGTH_MEDIUM
};

#if defined(USE_I2C0)
/* I2C0 Information (Run-Time) */
static I2C_INFO I2C0_Info;

static I2C_PIN I2C0_scl = {
  I2C0_SCL_GPIO_PORT,
  I2C0_SCL_GPIO_PIN,
  {
    I2C0_SCL_GPIO_FUNC,
    GPIO_MODE_INPUT,
    GPIO_PULL_DISABLE,
    GPIO_STRENGTH_MEDIUM,
  }
};

static I2C_PIN I2C0_sda = {
  I2C0_SDA_GPIO_PORT,
  I2C0_SDA_GPIO_PIN,
  {
    I2C0_SDA_GPIO_FUNC,
    GPIO_MODE_INPUT,
    GPIO_PULL_DISABLE,
    GPIO_STRENGTH_MEDIUM,
  }
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
static I2C_INFO I2C1_Info;

static I2C_PIN I2C1_scl = {
  I2C1_SCL_GPIO_PORT,
  I2C1_SCL_GPIO_PIN,
  {
    I2C1_SCL_GPIO_FUNC,
    GPIO_MODE_INPUT,
    GPIO_PULL_DISABLE,
    GPIO_STRENGTH_MEDIUM,
  }
};

static I2C_PIN I2C1_sda = {
  I2C1_SDA_GPIO_PORT,
  I2C1_SDA_GPIO_PIN,
  {
    I2C1_SDA_GPIO_FUNC,
    GPIO_MODE_INPUT,
    GPIO_PULL_DISABLE,
    GPIO_STRENGTH_MEDIUM,
  }
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

static
uint32_t GetFifoCntMasterTx(I2C_t *reg)
{
  uint32_t cnt;

  cnt = (reg->FSTA & I2CFSTA_MTXSTA_Msk) >> I2CFSTA_MTXSTA_Pos;

  if (cnt != 0U) {
    --cnt;
  }

  return (cnt);
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
  I2C_IO   *io;
  I2C_INFO *info = i2c->info;

  if (info->flags & I2C_FLAG_INIT) {
    return (ARM_DRIVER_OK);
  }

  io = &i2c->io;

  /* Configure SCL Pin */
  io->scl->gpio->PinConfig(io->scl->pin, &io->scl->cfg);
  /* Configure SDA Pin */
  io->sda->gpio->PinConfig(io->sda->pin, &io->sda->cfg);

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2C_INFO));

  info->cb_event = cb_event;
  info->flags    = I2C_FLAG_INIT;

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
  io->scl->gpio->PinConfig(io->scl->pin, &pin_cfg_gpio_in);
  /* Unconfigure SDA Pin */
  io->sda->gpio->PinConfig(io->sda->pin, &pin_cfg_gpio_in);

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
      reg->MCON = 1U;
      reg->SCON = 0U;
      reg->MCON = 0U;

      /* Disable I2C peripheral clock */
      PCC_DisablePeriph(i2c->pcc_periph);

      /* Disable I2C IRQ */
      IRQ_Disable(irq->master_num);
      IRQ_Disable(irq->slave_num);

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
      info->flags |= I2C_FLAG_POWER;
      break;

    default:
      return (ARM_DRIVER_ERROR_UNSUPPORTED);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2C_MasterTransmit(uint32_t       addr,
 *                                         const uint8_t *data,
 *                                         uint32_t       num,
 *                                         bool           xfer_pending,
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
int32_t I2C_MasterTransmit(uint32_t       addr,
                           const uint8_t *data,
                           uint32_t       num,
                           bool           xfer_pending,
                           I2C_RESOURCES *i2c)
{
  I2C_t         *reg  = i2c->reg;
  I2C_INFO      *info = i2c->info;
  I2C_XFER_INFO *xx   = &info->tx;

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

  /* Disable I2C interrupts */
  IRQ_Disable(i2c->irq.master_num);

  info->status = I2C_STATUS_BUSY | I2C_STATUS_MASTER;
  info->xfer = xfer_pending ? XFER_PENDING : 0U;

  xx->data = (uint8_t *)data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Enable master and transmit interrupt */
  reg->MCON = I2CMCON_MEN | I2CMCON_MTENI | I2CMCON_MCENI | I2CMCON_ALENI;

  while ((reg->FSTA & I2CFSTA_MTXSTA_Msk) != I2CFSTA_MTXSTA_TWOBYTES && xx->cnt < xx->num) {
    reg->MTX = xx->data[xx->cnt++];
  }

  /* Set slave address, transfer direction and generate start */
  reg->ADR0 = (addr << 1U) & I2CADR0;

  /* Enable I2C interrupts */
  IRQ_Enable(i2c->irq.master_num);

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t I2C_MasterReceive(uint32_t       addr,
 *                                        uint8_t       *data,
 *                                        uint32_t       num,
 *                                        bool           xfer_pending,
 *                                        I2C_RESOURCES *i2c)
 * @brief                     Start receiving data as I2C Master.
 * @param[in]   addr          Slave address (7-bit or 10-bit)
 * @param[out]  data          Pointer to buffer for data to receive from I2C Slave
 * @param[in]   num           Number of data bytes to receive
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return                    \ref execution_status
 */
static
int32_t I2C_MasterReceive(uint32_t       addr,
                          uint8_t       *data,
                          uint32_t       num,
                          bool           xfer_pending,
                          I2C_RESOURCES *i2c)
{
  I2C_t         *reg  = i2c->reg;
  I2C_INFO      *info = i2c->info;
  I2C_XFER_INFO *xx   = &info->rx;

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
  IRQ_Disable(i2c->irq.master_num);

  info->status = I2C_STATUS_BUSY | I2C_STATUS_MASTER | I2C_STATUS_RECEIVER;
  info->xfer = xfer_pending ? XFER_PENDING : 0U;

  xx->data = data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Enable master and receive interrupt */
  reg->MCON = I2CMCON_MEN | I2CMCON_MRENI | I2CMCON_MCENI | I2CMCON_ALENI;
  /* Set number of bytes to transfer */
  reg->MCNT0 = (num - 1U) & I2CMCNT0_RCNT;
  /* Set slave address, transfer direction and generate start */
  reg->ADR0 = ((addr << 1U) | 1UL) & I2CADR0;

  /* Enable I2C interrupts */
  IRQ_Enable(i2c->irq.master_num);

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
  I2C_t         *reg  = i2c->reg;
  I2C_INFO      *info = i2c->info;
  I2C_XFER_INFO *xx   = &info->tx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Disable I2C interrupts */
  IRQ_Disable(i2c->irq.slave_num);

  info->status = 0U;
  info->xfer = 0U;

  xx->data = (uint8_t *)data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Fill the Slave TX FIFO */
  while ((reg->FSTA & I2CFSTA_STXSTA_Msk) != I2CFSTA_STXSTA_TWOBYTES && xx->cnt < xx->num) {
    reg->STX = xx->data[xx->cnt++];
  }

  /* Enable TX interrupt */
  reg->SCON |= I2CSCON_STXENI;

  /* Enable I2C interrupts */
  IRQ_Enable(i2c->irq.slave_num);

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
  I2C_INFO      *info = i2c->info;
  I2C_XFER_INFO *xx   = &info->rx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_STATUS_BUSY) != 0U) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Disable I2C interrupts */
  IRQ_Disable(i2c->irq.slave_num);

  info->status = 0U;
  info->xfer = 0U;

  xx->data = data;
  xx->num  = num;
  xx->cnt  = 0U;

  /* Enable I2C interrupts */
  IRQ_Enable(i2c->irq.slave_num);

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
  I2C_XFER_INFO  *xx;
  I2C_INFO       *info = i2c->info;

  if ((info->status & I2C_STATUS_MASTER) == 0U &&
      (info->xfer & XFER_SLAVE_ADDR) == 0U) {
    return (-1);
  }

  xx = info->status & I2C_STATUS_RECEIVER ? &info->rx : &info->tx;

  return ((int32_t)xx->cnt);
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

  if ((info->flags & I2C_FLAG_POWER) == 0U) {
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
        val = I2CSCON_STXENI |
              I2CSCON_SRXENI |
              I2CSCON_SSENI  |
              I2CSCON_SETEN  |
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
      /* Master configured, clock set */
      info->flags |= I2C_FLAG_SETUP;
      break;

    case ARM_I2C_BUS_CLEAR:
      /* Disable I2C interrupts */
      IRQ_Disable(i2c->irq.master_num);

      {
        GPIO_PIN_CFG_t pin_cfg = pin_cfg_gpio_in;
        I2C_IO         *io = &i2c->io;

        io->sda->gpio->PinWrite(io->sda->pin, GPIO_PIN_OUT_LOW);
        io->scl->gpio->PinWrite(io->scl->pin, GPIO_PIN_OUT_LOW);

        for (uint32_t i = 0; i < 9U; ++i) {
          if (io->sda->gpio->PinRead(io->sda->pin) != 0U) {
            break;
          }

          pin_cfg.mode = GPIO_MODE_OUTPUT;
          io->scl->gpio->PinConfig(io->scl->pin, &pin_cfg);

          pin_cfg.mode = GPIO_MODE_INPUT;
          io->scl->gpio->PinConfig(io->scl->pin, &pin_cfg);
        }

        pin_cfg.mode = GPIO_MODE_OUTPUT;
        io->scl->gpio->PinConfig(io->scl->pin, &pin_cfg);
        io->sda->gpio->PinConfig(io->sda->pin, &pin_cfg);

        /* Configure SCL Pin as I2C */
        io->scl->gpio->PinConfig(io->scl->pin, &io->scl->cfg);
        /* Configure SDA Pin as I2C */
        io->sda->gpio->PinConfig(io->sda->pin, &io->sda->cfg);
      }

      /* Disable I2C master */
      reg->MCON = 0U;

      info->xfer   = 0U;
      info->status = 0U;

      /* Enable I2C interrupts */
      IRQ_Enable(i2c->irq.master_num);
      break;

    case ARM_I2C_ABORT_TRANSFER:
      if ((info->status & I2C_STATUS_MASTER) != 0U) {
        /* Disable I2C interrupts */
        IRQ_Disable(i2c->irq.master_num);

        if ((info->status & I2C_STATUS_RECEIVER) == 0U) {
          reg->MCON &= (uint16_t)~I2CMCON_MTENI;
          reg->FSTA = I2CFSTA_FMTX;
        }
        else {
          reg->MCNT0 = 0U;
        }

        /* Enable I2C interrupts */
        IRQ_Enable(i2c->irq.master_num);
      }
      else {
        /* Flush the Slave TX FIFO */
        reg->FSTA = I2CFSTA_FSTX;
      }

      info->status = 0U;
      info->xfer   = 0U;
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
  ARM_I2C_STATUS *status = (ARM_I2C_STATUS *)&i2c->info->status;

  return (*status);
}

/**
 * @fn          void I2C_Master_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Master Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2C_Master_IRQHandler(I2C_RESOURCES *i2c)
{
  register uint32_t  state;
  register uint32_t  event;
  I2C_XFER_INFO     *xx;
  I2C_INFO          *info = i2c->info;
  I2C_t             *reg  = i2c->reg;

  state = reg->MSTA;
  event = 0U;

  if ((state & I2CMSTA_NADDR) != 0U) {
    info->xfer |= XFER_MASTER_NADDR;
  }

  if ((state & I2CMSTA_NDATA) != 0U) {
    info->xfer |= XFER_MASTER_NDATA;
  }

  if ((state & I2CMSTA_TXQ) != 0U) {
    xx = &info->tx;
    while ((reg->FSTA & I2CFSTA_MTXSTA_Msk) != I2CFSTA_MTXSTA_TWOBYTES && xx->cnt < xx->num) {
      reg->MTX = xx->data[xx->cnt++];
    }
    if (xx->cnt == xx->num) {
      if ((info->xfer & XFER_PENDING) != 0U) {
        if (xx->num == 1U && (reg->FSTA & I2CFSTA_MTXSTA_Msk) != I2CFSTA_MTXSTA_EMPTY) {
          return;
        }
        info->status &= ~I2C_STATUS_BUSY;
        event = ARM_I2C_EVENT_TRANSFER_DONE;
      }
      reg->MCON &= (uint16_t)~I2CMCON_MTENI;
    }
  }

  if ((state & I2CMSTA_RXQ) != 0U) {
    xx = &info->rx;
    do {
      uint8_t data = (uint8_t)reg->MRX;
      if (xx->cnt < xx->num) {
        xx->data[xx->cnt++] = data;
#if 0
        if (xx->cnt == xx->num) {
          ctrl &= ~I2CMCON_MRENI;
          if ((info->xfer & XFER_PENDING) != 0U) {
            info->status &= ~I2C_STATUS_BUSY;
            ctrl &= ~I2CMCON_MCENI;
            event = ARM_I2C_EVENT_TRANSFER_DONE;
          }
          reg->MCON = (uint16_t)ctrl;
        }
#endif
      }
    } while ((reg->FSTA & I2CFSTA_MRXSTA_Msk) != I2CFSTA_MRXSTA_EMPTY);
  }

  if ((state & I2CMSTA_AL) != 0U) {
    /* Disable master */
    reg->MCON = 0U;
    info->status = (info->status & ~(I2C_STATUS_BUSY | I2C_STATUS_MASTER)) | I2C_STATUS_ARBITRATION_LOST;
    info->xfer = 0U;
    event = ARM_I2C_EVENT_ARBITRATION_LOST |
            ARM_I2C_EVENT_TRANSFER_DONE    |
            ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
  }

  if ((state & (I2CMSTA_TC | I2CMSTA_BUSY)) == I2CMSTA_TC) {
    if ((info->status & I2C_STATUS_BUSY) != 0U) {
      info->status &= ~I2C_STATUS_BUSY;
      event = ARM_I2C_EVENT_TRANSFER_DONE;

      xx = info->status & I2C_STATUS_RECEIVER ? &info->rx : &info->tx;

      if ((info->xfer & (XFER_MASTER_NADDR | XFER_MASTER_NDATA)) != 0U) {
        if ((info->xfer & XFER_MASTER_NADDR) != 0U) {
          event |= ARM_I2C_EVENT_ADDRESS_NACK;
          xx->cnt = 0U;
        }
        else {
          xx->cnt -= GetFifoCntMasterTx(reg) + 1U;
        }
        reg->FSTA = I2CFSTA_FMTX;
      }

      if (xx->cnt < xx->num) {
        event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
      }

      /* Disable master */
      reg->MCON = 0U;
      info->xfer = 0U;
    }
  }

  /* Send events */
  if ((event != 0U) && (info->cb_event)) {
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
  register uint32_t  state;
  register uint32_t  event;
  I2C_XFER_INFO     *xx;
  I2C_INFO          *info = i2c->info;
  I2C_t             *reg  = i2c->reg;

  state = reg->SSTA;

  /* General call status */
  if ((state & I2CSSTA_GC) != 0U) {
    info->status |= I2C_STATUS_GENERAL_CALL;
    reg->SCON |= I2CSCON_GCCLR;
  }

  /* Slave Transmit request */
  if ((state & I2CSSTA_STXQ) != 0U) {
    xx = &info->tx;
    if ((info->xfer & XFER_SLAVE_TX) == 0U) {
      if (xx->num == 0U) {
        reg->SCON &= (uint16_t)~I2CSCON_STXENI;
        if (info->cb_event != NULL) {
          info->status &= ~I2C_STATUS_BUSY;
          info->cb_event(ARM_I2C_EVENT_SLAVE_TRANSMIT);
        }
      }

      info->status |= I2C_STATUS_BUSY;
      info->xfer |= XFER_SLAVE_ADDR | XFER_SLAVE_TX;
    }

    if (xx->num != 0U) {
      while ((reg->FSTA & I2CFSTA_STXSTA_Msk) != I2CFSTA_STXSTA_TWOBYTES && xx->cnt < xx->num) {
        reg->STX = xx->data[xx->cnt++];
      }
      if (xx->cnt == xx->num) {
        reg->SCON &= (uint16_t)~I2CSCON_STXENI;
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
  if ((state & I2CSSTA_SRXQ) != 0U) {
    xx = &info->rx;
    do {
      uint8_t data = (uint8_t)reg->SRX;

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
    } while ((reg->FSTA & I2CFSTA_SRXSTA_Msk) != I2CFSTA_SRXSTA_EMPTY);
  }

  /* Slave Stop Condition */
  if ((state & I2CSSTA_SS) != 0U) {
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
    reg->SCON |= I2CSCON_STXENI | I2CSCON_SRXENI;
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
