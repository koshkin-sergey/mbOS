/*
 * Copyright (C) 2018-2020 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver for STMicroelectronics STM32F4xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "I2C_STM32F4xx.h"

#if defined(USE_I2C1) || defined(USE_I2C2) || defined(USE_I2C3)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

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

static const GPIO_PIN_CFG_t I2C_pin_cfg_af = {
    GPIO_MODE_AF_OD, GPIO_PULL_DISABLE, GPIO_SPEED_MEDIUM
};

static const GPIO_PIN_CFG_t I2C_pin_cfg_analog = {
    GPIO_MODE_ANALOG, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

#if defined(USE_I2C1)
/* I2C1 Information (Run-Time) */
static I2C_INFO I2C1_Info;

/* I2C1 Resources */
static I2C_RESOURCES I2C1_Resources = {
  I2C1,
  NULL,
  NULL,
  {
      I2C1_SCL_GPIO_PORT,
      I2C1_SCL_GPIO_PIN,
      I2C1_SCL_GPIO_FUNC,
      I2C1_SDA_GPIO_PORT,
      I2C1_SDA_GPIO_PIN,
      I2C1_SDA_GPIO_FUNC,
  },
  I2C1_EV_IRQn,
  I2C1_ER_IRQn,
  RCC_PERIPH_I2C1,
  &I2C1_Info,
};
#endif /* USE_I2C1 */


#if defined(USE_I2C2)
/* I2C2 Information (Run-Time) */
static I2C_INFO I2C2_Info;

/* I2C2 Resources */
static I2C_RESOURCES I2C2_Resources = {
  I2C2,
  NULL,
  NULL,
  {
      I2C2_SCL_GPIO_PORT,
      I2C2_SCL_GPIO_PIN,
      I2C2_SCL_GPIO_FUNC,
      I2C2_SDA_GPIO_PORT,
      I2C2_SDA_GPIO_PIN,
      I2C2_SDA_GPIO_FUNC,
  },
  I2C2_EV_IRQn,
  I2C2_ER_IRQn,
  RCC_PERIPH_I2C2,
  &I2C2_Info,
};
#endif /* USE_I2C2 */

#if defined(USE_I2C3)
/* I2C3 Information (Run-Time) */
static I2C_INFO I2C3_Info;

/* I2C3 Resources */
static I2C_RESOURCES I2C3_Resources = {
  I2C3,
  NULL,
  NULL,
  {
      I2C3_SCL_GPIO_PORT,
      I2C3_SCL_GPIO_PIN,
      I2C3_SCL_GPIO_FUNC,
      I2C3_SDA_GPIO_PORT,
      I2C3_SDA_GPIO_PIN,
      I2C3_SDA_GPIO_FUNC,
  },
  I2C3_EV_IRQn,
  I2C3_ER_IRQn,
  RCC_PERIPH_I2C3,
  &I2C3_Info,
};
#endif /* USE_I2C3 */

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn      ARM_DRIVER_VERSION I2C_GetVersion(void)
 * @brief   Get driver version.
 * @return  \ref ARM_DRIVER_VERSION
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
  if (i2c->info->flags & I2C_FLAG_INIT)
    return ARM_DRIVER_OK;

  I2C_IO *io = &i2c->io;
  I2C_INFO *info = i2c->info;

  /* Configure SCL Pin */
  GPIO_PortClock(io->scl_port, GPIO_PORT_CLK_ENABLE);
  GPIO_AFConfig(io->scl_port, io->scl_pin, io->scl_func);
  GPIO_PinConfig(io->scl_port, io->scl_pin, &I2C_pin_cfg_af);
  /* Configure SDA Pin */
  GPIO_PortClock(io->sda_port, GPIO_PORT_CLK_ENABLE);
  GPIO_AFConfig(io->sda_port, io->sda_pin, io->sda_func);
  GPIO_PinConfig(io->sda_port, io->sda_pin, &I2C_pin_cfg_af);

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2C_INFO));

  info->cb_event = cb_event;
  info->flags    = I2C_FLAG_INIT;

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
  I2C_IO *io = &i2c->io;

  /* Unconfigure SCL Pin */
  GPIO_PinConfig(io->scl_port, io->scl_pin, &I2C_pin_cfg_analog);
  /* Unconfigure SDA Pin */
  GPIO_PinConfig(io->sda_port, io->sda_pin, &I2C_pin_cfg_analog);

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
int32_t I2Cx_PowerControl(ARM_POWER_STATE state, I2C_RESOURCES *i2c)
{
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

      /* Disable peripheral clock */
      RCC_DisablePeriph(i2c->rcc);

      info->status.busy             = 0U;
      info->status.mode             = 0U;
      info->status.direction        = 0U;
      info->status.general_call     = 0U;
      info->status.arbitration_lost = 0U;
      info->status.bus_error        = 0U;

      info->flags &= ~I2C_FLAG_POWER;
      break;

    case ARM_POWER_FULL:
      if ((info->flags & I2C_FLAG_INIT) == 0U)
        return ARM_DRIVER_ERROR;

      if ((info->flags & I2C_FLAG_POWER) != 0U)
        return ARM_DRIVER_OK;

      /* Enable I2C clock */
      RCC_EnablePeriph(i2c->rcc);

      /* Clear and Enable I2C IRQ */
      NVIC_ClearPendingIRQ(i2c->ev_irq_num);
      NVIC_ClearPendingIRQ(i2c->er_irq_num);
      NVIC_SetPriority(i2c->ev_irq_num, RTE_I2C_INT_PRIORITY);
      NVIC_SetPriority(i2c->er_irq_num, RTE_I2C_INT_PRIORITY);
      NVIC_EnableIRQ(i2c->ev_irq_num);
      NVIC_EnableIRQ(i2c->er_irq_num);

      /* Reset the peripheral */
      RCC_ResetPeriph(i2c->rcc);

      /* Enable event and error interrupts */
      reg->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITERREN;
      /* Disable buffer interrupts */
      reg->CR2 &= ~I2C_CR2_ITBUFEN;

      /* Enable clock stretching */
      reg->CR1 &= ~I2C_CR1_NOSTRETCH;

      /* Enable I2C peripheral */
      reg->CR1 |= I2C_CR1_PE;

      /* Enable acknowledge */
      reg->CR1 |= I2C_CR1_ACK;

      /* Ready for operation */
      info->flags |= I2C_FLAG_POWER;
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
  I2C_TypeDef *reg = i2c->reg;

  if ((i2c->info->flags & I2C_FLAG_POWER) == 0U) {
    /* I2C not powered */
    return ARM_DRIVER_ERROR;
  }

  switch (control) {
    case ARM_I2C_OWN_ADDRESS:
      /* Enable/Disable General call */
      if (arg & ARM_I2C_ADDRESS_GC) {
        reg->CR1 |=  I2C_CR1_ENGC;
      }
      else {
        reg->CR1 &= ~I2C_CR1_ENGC;
      }
      /* Set own address and its length */
      if (arg & ARM_I2C_ADDRESS_10BIT) {
        reg->OAR1 = (arg & 0x03FFU) | (3U << 14);
      }
      else {
        reg->OAR1 = ((arg << 1) & 0x03FFU) | (1U << 14);
      }
      break;

    case ARM_I2C_BUS_SPEED:
    {
      uint32_t ccr, trise;
      uint32_t pclk = RCC_GetPeriphFreq(i2c->rcc);

      switch (arg) {
        case ARM_I2C_BUS_SPEED_STANDARD:
          /* Clock = 100kHz,  Rise Time = 1000ns */
          if (pclk > 50000000U) { return ARM_DRIVER_ERROR_UNSUPPORTED; }
          if (pclk <  2000000U) { return ARM_DRIVER_ERROR_UNSUPPORTED; }
          ccr   = (pclk /  100000U) / 2U;
          trise = (pclk / 1000000U) + 1U;
          break;
        case ARM_I2C_BUS_SPEED_FAST:
          /* Clock = 400kHz,  Rise Time = 300ns */
          if (pclk > 50000000U) { return ARM_DRIVER_ERROR_UNSUPPORTED; }
          if (pclk <  4000000U) { return ARM_DRIVER_ERROR_UNSUPPORTED; }
          if ((pclk >= 10000000U) && ((pclk % 10000000U) == 0U)) {
            ccr = I2C_CCR_FS | I2C_CCR_DUTY | ((pclk / 400000U) / 25U);
          } else {
            ccr = I2C_CCR_FS |                ((pclk / 400000U) / 3U);
          }
          trise = (((pclk / 1000000U) * 300U) / 1000U) + 1U;
          break;
        default:
          return ARM_DRIVER_ERROR_UNSUPPORTED;
      }

      reg->CR1   &= ~I2C_CR1_PE;           /* Disable I2C peripheral */
      reg->CR2   &= ~I2C_CR2_FREQ;
      reg->CR2   |=  pclk / 1000000U;
      reg->CCR    =  ccr;
      reg->TRISE  =  trise;
      reg->CR1   |=  I2C_CR1_PE;           /* Enable I2C peripheral */
      reg->CR1   |=  I2C_CR1_ACK;          /* Enable acknowledge    */
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
 * @fn          int32_t I2Cx_MasterTransmit(uint32_t addr,
 *                                          const uint8_t *data,
 *                                          uint32_t num,
 *                                          bool xfer_pending,
 *                                          I2C_RESOURCES *i2c)
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
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (info->status.busy) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  if ((info->xfer.ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer */
    while (reg->SR2 & I2C_SR2_BUSY) {
      ; /* Wait until bus released */
    }
  }

  info->status.busy             = 1U;
  info->status.mode             = 1U;
  info->status.direction        = 0U;
  info->status.bus_error        = 0U;
  info->status.arbitration_lost = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = 0U;
  info->xfer.data = (uint8_t *)data;
  info->xfer.addr = (uint16_t)(addr);
  info->xfer.ctrl = 0U;

  if (xfer_pending) {
    info->xfer.ctrl |= XFER_CTRL_XPENDING;
  }

  /* Generate start and enable event interrupts */
  reg->CR2 &= ~I2C_CR2_ITEVTEN;
  reg->CR1 |=  I2C_CR1_START;
  reg->CR2 |=  I2C_CR2_ITEVTEN;

  return ARM_DRIVER_OK;
}

/**
 * @fn                        int32_t I2Cx_MasterReceive(uint32_t addr,
 *                                                       uint8_t *data,
 *                                                       uint32_t num,
 *                                                       bool xfer_pending,
 *                                                       I2C_RESOURCES *i2c)
 * @brief                     Start receiving data as I2C Master.
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
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (info->status.busy) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  if ((info->xfer.ctrl & XFER_CTRL_XPENDING) == 0U) {
    /* New transfer */
    while (reg->SR2 & I2C_SR2_BUSY) {
      ; /* Wait until bus released */
    }
  }

  info->status.busy             = 1U;
  info->status.mode             = 1U;
  info->status.direction        = 1U;
  info->status.bus_error        = 0U;
  info->status.arbitration_lost = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = 0U;
  info->xfer.data = data;
  info->xfer.addr = (uint16_t)(addr);
  info->xfer.ctrl = 0U;

  if (xfer_pending) {
    info->xfer.ctrl |= XFER_CTRL_XPENDING;
  }

  /* Enable acknowledge generation */
  reg->CR1 |= I2C_CR1_ACK;

  /* Generate start and enable event interrupts */
  reg->CR2 &= ~I2C_CR2_ITEVTEN;
  reg->CR1 |=  I2C_CR1_START;
  reg->CR2 |=  I2C_CR2_ITEVTEN;

  return ARM_DRIVER_OK;
}

/**
 * @fn        int32_t I2Cx_SlaveTransmit (const uint8_t *data,
 *                                        uint32_t num,
 *                                        I2C_RESOURCES *i2c)
 * @brief     Start transmitting data as I2C Slave.
 * @param[in] data  Pointer to buffer with data to transmit to I2C Master
 * @param[in] num   Number of data bytes to transmit
 * @param[in] i2c   Pointer to I2C resources
 * @return    \ref  execution_status
*/
static
int32_t I2Cx_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (info->status.busy) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  info->status.bus_error    = 0U;
  info->status.general_call = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = 0U;
  info->xfer.data = (uint8_t *)data;
  info->xfer.ctrl = 0U;

  /* Enable acknowledge */
  reg->CR1 |= I2C_CR1_ACK;

  /* Enable event interrupts */
  reg->CR2 |= I2C_CR2_ITEVTEN;

  return ARM_DRIVER_OK;
}

/**
 * @fn          int32_t I2Cx_SlaveReceive (uint8_t *data,
 *                                         uint32_t num,
 *                                         I2C_RESOURCES *i2c)
 * @brief       Start receiving data as I2C Slave.
 * @param[out]  data  Pointer to buffer for data to receive from I2C Master
 * @param[in]   num   Number of data bytes to receive
 * @param[in]   i2c   Pointer to I2C resources
 * @return      \ref execution_status
*/
static
int32_t I2Cx_SlaveReceive(uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (info->status.busy) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  info->status.bus_error    = 0U;
  info->status.general_call = 0U;

  info->xfer.num  = num;
  info->xfer.cnt  = 0U;
  info->xfer.data = data;
  info->xfer.ctrl = 0U;

  /* Enable acknowledge generation */
  reg->CR2 |= I2C_CR2_LAST;
  /* Enable acknowledge */
  reg->CR1 |= I2C_CR1_ACK;
  /* Enable event interrupts */
  reg->CR2 |= I2C_CR2_ITEVTEN;

  return ARM_DRIVER_OK;
}

/**
 * @brief       Get transferred data count.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      Number of data bytes transferred;
 *              -1 when Slave is not addressed by Master
 */
static
int32_t I2Cx_GetDataCount(I2C_RESOURCES *i2c)
{
  return i2c->info->xfer.cnt;
}

/**
 * @brief       Get I2C status.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      I2C status \ref ARM_I2C_STATUS
 */
static
ARM_I2C_STATUS I2Cx_GetStatus(I2C_RESOURCES *i2c)
{
  return i2c->info->status;
}

/**
 * @fn          void I2Cx_EV_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Event Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2Cx_EV_IRQHandler(I2C_RESOURCES *i2c)
{
  I2C_TRANSFER_INFO *tr = &i2c->info->xfer;
  uint8_t  data;
  uint16_t sr1, sr2;
  uint32_t event;

  sr1 = (uint16_t)i2c->reg->SR1;

  if (sr1 & I2C_SR1_SB) {
    /* (EV5): start bit generated, send address */

    if (tr->addr & ARM_I2C_ADDRESS_10BIT) {
      /* 10-bit addressing mode */
      data = (uint8_t)(0xF0U | ((tr->addr >> 7) & 0x06U));
    }
    else {
      /* 7-bit addressing mode */
      data  = (uint8_t)tr->addr << 1;
      data |= (uint8_t)i2c->info->status.direction;
    }
    i2c->reg->DR = data;
  }
  else if (sr1 & I2C_SR1_ADD10) {
    /* (EV9): 10-bit address header sent, send device address LSB */
    i2c->reg->DR = (uint8_t)tr->addr;

    if (i2c->info->status.direction) {
      /* Master receiver generates repeated start in 10-bit addressing mode */
      tr->ctrl |= XFER_CTRL_RSTART;
    }
  }
  else if (sr1 & I2C_SR1_ADDR) {
    /* (EV6): addressing complete */
    if (tr->ctrl & XFER_CTRL_ADDR_DONE) {
      /* Restart condition, end previous transfer */
      i2c->info->status.busy = 0U;

      event = ARM_I2C_EVENT_TRANSFER_DONE;

      if (tr->cnt < tr->num) {
        event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
      }

      if (i2c->info->status.general_call) {
        event |= ARM_I2C_EVENT_GENERAL_CALL;
      }

      if (i2c->info->cb_event != NULL) {
        i2c->info->cb_event (event);
      }
    }

    if ((i2c->info->status.mode != 0U) && (i2c->info->status.direction != 0U)) {
      /* Master mode, receiver */
      if (tr->num == 1U) {
        i2c->reg->CR1 &= ~I2C_CR1_ACK;
      }

      /* Clear ADDR flag */
      i2c->reg->SR1;
      i2c->reg->SR2;

      if (tr->ctrl & XFER_CTRL_RSTART) {
        tr->ctrl &= ~XFER_CTRL_RSTART;
        /* Generate repeated start */
        i2c->reg->CR1 |= I2C_CR1_START;
      }
      else {
        if (tr->num == 1U) {
          if ((tr->ctrl & XFER_CTRL_XPENDING) == 0U) {
            i2c->reg->CR1 |= I2C_CR1_STOP;
          }
        }
        else if (tr->num == 2U) {
          i2c->reg->CR1 &= ~I2C_CR1_ACK;
          i2c->reg->CR1 |= I2C_CR1_POS;

          /* Wait until BTF == 1 */
          tr->ctrl |= XFER_CTRL_WAIT_BTF;
        }
        else {
          if (tr->num == 3U) {
            /* Wait until BTF == 1 */
            tr->ctrl |= XFER_CTRL_WAIT_BTF;
          }
        }
      }
    }
    else {
      /* Master transmitter or slave mode */
      sr2 = (uint16_t)i2c->reg->SR2;

      if (i2c->info->status.mode == 0U) {
        /* Slave mode */

        if (sr2 & I2C_SR2_GENCALL) {
          i2c->info->status.general_call = 1U;
        } else {
          i2c->info->status.general_call = 0U;
        }

        if (sr2 & I2C_SR2_TRA) {
          i2c->info->status.direction = 0U;
        } else {
          i2c->info->status.direction = 1U;
        }

        event = 0U;

        if (tr->data == NULL) {
          if (i2c->info->status.direction) {
            event |= ARM_I2C_EVENT_SLAVE_RECEIVE;
          }
          else {
            event |= ARM_I2C_EVENT_SLAVE_TRANSMIT;
          }
        }

        if (i2c->info->status.general_call) {
          event |= ARM_I2C_EVENT_GENERAL_CALL;
        }

        if ((event != 0U) && (i2c->info->cb_event != NULL)) {
          i2c->info->cb_event (event);
        }

        i2c->info->status.busy = 1U;
      }
    }

    tr->ctrl |= XFER_CTRL_ADDR_DONE | XFER_CTRL_XACTIVE;

    if ((i2c->dma_rx != NULL) && (i2c->dma_tx != NULL)) {
      /* Enable DMA data transfer */
      i2c->reg->CR2 |= I2C_CR2_DMAEN;
    }
    else {
      /* Enable IRQ data transfer */
      i2c->reg->CR2 |= I2C_CR2_ITBUFEN;
    }

  }
  else if (sr1 & I2C_SR1_STOPF) {
    /* STOP condition detected */
    tr->data = NULL;
    tr->ctrl = 0U;

    /* Reenable ACK */
    i2c->reg->CR1 |= I2C_CR1_ACK;

    i2c->info->status.busy = 0U;

    event = ARM_I2C_EVENT_TRANSFER_DONE;
    if (tr->cnt < tr->num) {
      event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    }
    if (i2c->info->status.general_call) {
      event |= ARM_I2C_EVENT_GENERAL_CALL;
    }

    if (i2c->info->cb_event) {
      i2c->info->cb_event (event);
    }
  }
  else if (tr->ctrl & XFER_CTRL_XACTIVE) {
    /* BTF, RxNE or TxE interrupt */
    if (tr->ctrl & XFER_CTRL_DMA_DONE) {
      /* BTF triggered this event */
      if (i2c->info->status.mode) {
        if (i2c->info->xfer.ctrl & XFER_CTRL_XPENDING) {
          /* Disable event interrupt */
          i2c->reg->CR2 &= ~I2C_CR2_ITEVTEN;
        }
        else {
          /* Generate stop condition */
          i2c->reg->CR1 |= I2C_CR1_STOP;
        }
        tr->data  =  NULL;
        tr->ctrl &= ~XFER_CTRL_XACTIVE;

        i2c->info->status.busy = 0U;
        i2c->info->status.mode = 0U;

        if (i2c->info->cb_event) {
          i2c->info->cb_event (ARM_I2C_EVENT_TRANSFER_DONE);
        }
      }
    }
    else if (sr1 & I2C_SR1_TXE) {
      if (i2c->info->status.mode) {
        /* Master transmitter */
        if (tr->ctrl & XFER_CTRL_WAIT_BTF) {
          if (sr1 & I2C_SR1_BTF) {
            /* End master transmit operation */
            i2c->reg->CR2 &= ~I2C_CR2_ITBUFEN;

            if (tr->ctrl & XFER_CTRL_XPENDING) {
              i2c->reg->CR2 &= ~I2C_CR2_ITEVTEN;
            }
            else {
              i2c->reg->CR1 |= I2C_CR1_STOP;
            }

            tr->data  = NULL;
            tr->ctrl &= ~XFER_CTRL_XACTIVE;

            i2c->info->status.busy = 0U;
            i2c->info->status.mode = 0U;

            if (i2c->info->cb_event) {
              i2c->info->cb_event (ARM_I2C_EVENT_TRANSFER_DONE);
            }
          }
        }
        else {
          i2c->reg->DR = tr->data[tr->cnt];

          tr->cnt++;
          if (tr->cnt == tr->num) {
            tr->ctrl |= XFER_CTRL_WAIT_BTF;
          }
        }
      }
      else {
        /* Slave transmitter */
        if (tr->data == NULL) {
          if (i2c->info->cb_event) {
            i2c->info->cb_event (ARM_I2C_EVENT_SLAVE_TRANSMIT);
          }
        }

        if (tr->data) {
          i2c->reg->DR = tr->data[tr->cnt];

          tr->cnt++;
          if (tr->cnt == tr->num) {
            tr->data = NULL;
          }
        }
        else {
          /* Master requests more data as we have */
          i2c->reg->DR = (uint8_t)0xFF;
        }
      }
    }
    else if (sr1 & I2C_SR1_RXNE) {
      if (i2c->info->status.mode) {
        /* Master receiver */
        if (tr->ctrl & XFER_CTRL_WAIT_BTF) {
          if (sr1 & I2C_SR1_BTF) {
            if ((tr->num == 2U) || (tr->cnt == (tr->num - 2U))) {
              /* Two bytes remaining */
              i2c->reg->CR2 &= ~I2C_CR2_ITBUFEN;

              if (tr->ctrl & XFER_CTRL_XPENDING) {
                i2c->reg->CR2 &= ~I2C_CR2_ITEVTEN;
              }
              else {
                i2c->reg->CR1 |= I2C_CR1_STOP;
              }

              /* Read data N-1 and N */
              tr->data[tr->cnt] = (uint8_t)i2c->reg->DR;
              tr->cnt++;
              tr->data[tr->cnt] = (uint8_t)i2c->reg->DR;
              tr->cnt++;

              tr->data  = NULL;
              tr->ctrl &= ~XFER_CTRL_XACTIVE;

              i2c->info->status.busy = 0U;
              i2c->info->status.mode = 0U;

              i2c->reg->CR1 &= ~I2C_CR1_POS;

              if (i2c->info->cb_event) {
                i2c->info->cb_event (ARM_I2C_EVENT_TRANSFER_DONE);
              }
            }
            else {
              /* Three bytes remaining */
              i2c->reg->CR1 &= ~I2C_CR1_ACK;
              /* Read data N-2 */
              tr->data[tr->cnt] = (uint8_t)i2c->reg->DR;
              tr->cnt++;
            }
          }
        }
        else {
          tr->data[tr->cnt] = (uint8_t)i2c->reg->DR;
          tr->cnt++;

          if (tr->num == 1U) {
            /* Single byte transfer completed */
            i2c->reg->CR2 &= ~I2C_CR2_ITBUFEN;

            if (tr->ctrl & XFER_CTRL_XPENDING) {
              i2c->reg->CR2 &= ~I2C_CR2_ITEVTEN;
            }
            /* (STOP was already sent during ADDR phase) */

            tr->data  = NULL;
            tr->ctrl &= ~XFER_CTRL_XACTIVE;

            i2c->info->status.busy = 0U;
            i2c->info->status.mode = 0U;

            if (i2c->info->cb_event) {
              i2c->info->cb_event (ARM_I2C_EVENT_TRANSFER_DONE);
            }
          }
          else {
            if (tr->cnt == (tr->num - 3U)) {
              /* N > 2 byte reception, begin N-2 data reception */
              i2c->reg->CR2 &= ~I2C_CR2_ITBUFEN;
              /* Wait until BTF == 1 */
              tr->ctrl |= XFER_CTRL_WAIT_BTF;
            }
          }
        }
      }
      else {
        /* Slave receiver */
        data = (uint8_t)i2c->reg->DR;

        if (tr->data == NULL) {
          /* Receive buffer full: Disable ACK */
          i2c->reg->CR1 &= ~I2C_CR1_ACK;
        }
        else {
          if (tr->cnt < tr->num) {
            tr->data[tr->cnt] = data;

            tr->cnt++;
            if (tr->cnt == tr->num) {
              tr->data = NULL;
            }
          }
        }
      }
    }
  }
}

/**
 * @brief       I2C Master state event handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2Cx_ER_IRQHandler(I2C_RESOURCES *i2c)
{
  uint32_t sr1 = i2c->reg->SR1;
  uint32_t evt = 0U;
  uint32_t err = 0U;

  if (sr1 & I2C_SR1_SMBALERT) {
    /* SMBus alert */
    err |= I2C_SR1_SMBALERT;
  }
  if (sr1 & I2C_SR1_TIMEOUT) {
    /* Timeout - SCL remained LOW for 25ms */
    err |= I2C_SR1_TIMEOUT;
  }
  if (sr1 & I2C_SR1_PECERR) {
    /* PEC Error in reception */
    err |= I2C_SR1_PECERR;
  }
  if (sr1 & I2C_SR1_OVR) {
    /* Overrun/Underrun */
    err |= I2C_SR1_OVR;
  }

  if (sr1 & I2C_SR1_AF) {
    /* Acknowledge failure */
    err |= I2C_SR1_AF;

    /* Reset the communication */
    i2c->reg->CR1 |= I2C_CR1_STOP;

    i2c->info->status.busy = 0U;
    i2c->info->status.mode = 0U;

    i2c->info->xfer.data = NULL;
    i2c->info->xfer.ctrl = 0U;

    evt = ARM_I2C_EVENT_TRANSFER_DONE;

    if ((i2c->info->xfer.ctrl & XFER_CTRL_ADDR_DONE) == 0U) {
      /* Addressing not done */
      evt |= ARM_I2C_EVENT_ADDRESS_NACK;
    }
  }

  if (sr1 & I2C_SR1_ARLO) {
    /* Arbitration lost */
    err |= I2C_SR1_ARLO;

    /* Switch to slave mode */
    i2c->info->status.busy             = 0U;
    i2c->info->status.mode             = 0U;
    i2c->info->status.arbitration_lost = 1U;

    i2c->info->xfer.data = NULL;
    i2c->info->xfer.ctrl = 0U;

    evt = ARM_I2C_EVENT_TRANSFER_DONE | ARM_I2C_EVENT_ARBITRATION_LOST;
  }

  if (sr1 & I2C_SR1_BERR) {
    /* Bus error - misplaced start/stop */
    err |= I2C_SR1_BERR;

    i2c->info->status.bus_error = 1U;

    if (i2c->info->status.mode == 0U) {
      /* Lines are released in slave mode */
      i2c->info->status.busy = 0U;

      i2c->info->xfer.data = NULL;
      i2c->info->xfer.ctrl = 0U;
    }

    evt = ARM_I2C_EVENT_TRANSFER_DONE | ARM_I2C_EVENT_BUS_ERROR;

  }

  /* Clear error flags */
  i2c->reg->SR1 &= ~err;

  if ((evt != 0) && (i2c->info->cb_event != NULL)) {
    if (i2c->info->xfer.cnt < i2c->info->xfer.num) {
      evt |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    }
    i2c->info->cb_event (evt);
  }
}

#if defined(USE_I2C1)
/* I2C1 Driver wrapper functions */

static
int32_t I2C1_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
  return (I2Cx_Initialize(cb_event, &I2C1_Resources));
}

static
int32_t I2C1_Uninitialize(void)
{
  return (I2Cx_Uninitialize(&I2C1_Resources));
}

static
int32_t I2C1_PowerControl(ARM_POWER_STATE state)
{
  return (I2Cx_PowerControl(state, &I2C1_Resources));
}

static
int32_t I2C1_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterTransmit(addr, data, num, xfer_pending, &I2C1_Resources));
}

static
int32_t I2C1_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterReceive(addr, data, num, xfer_pending, &I2C1_Resources));
}

static
int32_t I2C1_SlaveTransmit(const uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveTransmit(data, num, &I2C1_Resources));
}

static
int32_t I2C1_SlaveReceive(uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveReceive(data, num, &I2C1_Resources));
}

static
int32_t I2C1_GetDataCount(void)
{
  return (I2Cx_GetDataCount(&I2C1_Resources));
}

static
int32_t I2C1_Control(uint32_t control, uint32_t arg)
{
  return (I2Cx_Control(control, arg, &I2C1_Resources));
}

static
ARM_I2C_STATUS I2C1_GetStatus(void)
{
  return (I2Cx_GetStatus(&I2C1_Resources));
}

void I2C1_EV_IRQHandler(void)
{
  I2Cx_EV_IRQHandler(&I2C1_Resources);
}

void I2C1_ER_IRQHandler(void)
{
  I2Cx_ER_IRQHandler(&I2C1_Resources);
}

#endif  /* USE_I2C1 */

#if defined(USE_I2C2)
/* I2C2 Driver wrapper functions */

static
int32_t I2C2_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
  return (I2Cx_Initialize(cb_event, &I2C2_Resources));
}

static
int32_t I2C2_Uninitialize(void)
{
  return (I2Cx_Uninitialize(&I2C2_Resources));
}

static
int32_t I2C2_PowerControl(ARM_POWER_STATE state)
{
  return (I2Cx_PowerControl(state, &I2C2_Resources));
}

static
int32_t I2C2_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterTransmit(addr, data, num, xfer_pending, &I2C2_Resources));
}

static
int32_t I2C2_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterReceive(addr, data, num, xfer_pending, &I2C2_Resources));
}

static
int32_t I2C2_SlaveTransmit(const uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveTransmit(data, num, &I2C2_Resources));
}

static
int32_t I2C2_SlaveReceive(uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveReceive(data, num, &I2C2_Resources));
}

static
int32_t I2C2_GetDataCount(void)
{
  return (I2Cx_GetDataCount(&I2C2_Resources));
}

static
int32_t I2C2_Control(uint32_t control, uint32_t arg)
{
  return (I2Cx_Control(control, arg, &I2C2_Resources));
}

static
ARM_I2C_STATUS I2C2_GetStatus(void)
{
  return (I2Cx_GetStatus(&I2C2_Resources));
}

void I2C2_EV_IRQHandler(void)
{
  I2Cx_EV_IRQHandler(&I2C2_Resources);
}

void I2C2_ER_IRQHandler(void)
{
  I2Cx_ER_IRQHandler(&I2C2_Resources);
}

#endif  /* USE_I2C2 */

#if defined(USE_I2C3)
/* I2C3 Driver wrapper functions */

static
int32_t I2C3_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
  return (I2Cx_Initialize(cb_event, &I2C3_Resources));
}

static
int32_t I2C3_Uninitialize(void)
{
  return (I2Cx_Uninitialize(&I2C3_Resources));
}

static
int32_t I2C3_PowerControl(ARM_POWER_STATE state)
{
  return (I2Cx_PowerControl(state, &I2C3_Resources));
}

static
int32_t I2C3_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterTransmit(addr, data, num, xfer_pending, &I2C3_Resources));
}

static
int32_t I2C3_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterReceive(addr, data, num, xfer_pending, &I2C3_Resources));
}

static
int32_t I2C3_SlaveTransmit(const uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveTransmit(data, num, &I2C3_Resources));
}

static
int32_t I2C3_SlaveReceive(uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveReceive(data, num, &I2C3_Resources));
}

static
int32_t I2C3_GetDataCount(void)
{
  return (I2Cx_GetDataCount(&I2C3_Resources));
}

static
int32_t I2C3_Control(uint32_t control, uint32_t arg)
{
  return (I2Cx_Control(control, arg, &I2C3_Resources));
}

static
ARM_I2C_STATUS I2C3_GetStatus(void)
{
  return (I2Cx_GetStatus(&I2C3_Resources));
}

void I2C3_EV_IRQHandler(void)
{
  I2Cx_EV_IRQHandler(&I2C3_Resources);
}

void I2C3_ER_IRQHandler(void)
{
  I2Cx_ER_IRQHandler(&I2C3_Resources);
}

#endif  /* USE_I2C3 */

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

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

#endif  /* USE_I2C1 */

#if defined(USE_I2C2)

/* I2C2 Driver Control Block */
ARM_DRIVER_I2C Driver_I2C2 = {
  I2C_GetVersion,
  I2C_GetCapabilities,
  I2C2_Initialize,
  I2C2_Uninitialize,
  I2C2_PowerControl,
  I2C2_MasterTransmit,
  I2C2_MasterReceive,
  I2C2_SlaveTransmit,
  I2C2_SlaveReceive,
  I2C2_GetDataCount,
  I2C2_Control,
  I2C2_GetStatus
};

#endif  /* USE_I2C2 */

#if defined(USE_I2C3)

/* I2C3 Driver Control Block */
ARM_DRIVER_I2C Driver_I2C3 = {
  I2C_GetVersion,
  I2C_GetCapabilities,
  I2C3_Initialize,
  I2C3_Uninitialize,
  I2C3_PowerControl,
  I2C3_MasterTransmit,
  I2C3_MasterReceive,
  I2C3_SlaveTransmit,
  I2C3_SlaveReceive,
  I2C3_GetDataCount,
  I2C3_Control,
  I2C3_GetStatus
};

#endif  /* USE_I2C3 */

#endif /* defined(USE_I2C1) || defined(USE_I2C2) || defined(USE_I2C3) */

/* ----------------------------- End of file ---------------------------------*/
