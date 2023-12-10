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
 * Project: I2C Driver for STMicroelectronics STM32F0xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "I2C_STM32F0xx.h"

#include <string.h>
#include <asm/stm32f0xx.h>
#include <Driver/GPIO_STM32F0xx.h>
#include <Driver/RCC_STM32F0xx.h>

#if defined(USE_I2C1) || defined(USE_I2C2)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define RCC_APB_I2C1_MASK     ((uint32_t)(1U << 21))
#define RCC_APB_I2C2_MASK     ((uint32_t)(1U << 22))

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
      RTE_I2C1_SCL_PORT,
      RTE_I2C1_SCL_PIN,
      RTE_I2C1_SCL_FUNC,
      RTE_I2C1_SDA_PORT,
      RTE_I2C1_SDA_PIN,
      RTE_I2C1_SDA_FUNC,
  },
  I2C1_IRQn,
  RCC_APB_I2C1_MASK,
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
      RTE_I2C2_SCL_PORT,
      RTE_I2C2_SCL_PIN,
      RTE_I2C2_SCL_FUNC,
      RTE_I2C2_SDA_PORT,
      RTE_I2C2_SDA_PIN,
      RTE_I2C2_SDA_FUNC,
  },
  I2C2_IRQn,
  RCC_APB_I2C2_MASK,
  &I2C2_Info,
};
#endif /* HAL_I2C2 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
uint32_t GetI2CCLK(I2C_RESOURCES *i2c)
{
  uint32_t clk = 0;
  RCC_FREQ_t freq_type = RCC_FREQ_APB;

  if (i2c->reg == I2C1) {
    if ((RCC->CFGR3 & RCC_CFGR3_I2C1SW) != 0)
      freq_type = RCC_FREQ_SYSCLK;
    else
      freq_type = RCC_FREQ_HSI;
  }

  clk = RCC_GetFreq(freq_type) / 1000000;

  return (clk);
}

/**
 * @fn      ARM_DRIVER_VERSION I2C_GetVersion(void)
 * @brief   Get driver version.
 * @return  \ref ARM_DRIVER_VERSION
 */
static
ARM_DRIVER_VERSION I2C_GetVersion(void)
{
  return (DriverVersion);
}

/**
 * @fn      ARM_I2C_CAPABILITIES I2C_GetCapabilities(void)
 * @brief   Get driver capabilities.
 * @return  \ref ARM_I2C_CAPABILITIES
 */
static
ARM_I2C_CAPABILITIES I2C_GetCapabilities(void)
{
  return (DriverCapabilities);
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
  if (i2c->info->flags & I2C_FLAG_INIT) {
    return (ARM_DRIVER_OK);
  }

  I2C_IO *io = &i2c->io;
  I2C_INFO *info = i2c->info;

  /* Configure SCL Pin */
  GPIO_PortClock(io->scl_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->scl_port, io->scl_pin, &I2C_pin_cfg_af);
  GPIO_AFConfig(io->scl_port, io->scl_pin, io->scl_func);
  /* Configure SDA Pin */
  GPIO_PortClock(io->scl_port, GPIO_PORT_CLK_ENABLE);
  GPIO_PinConfig(io->sda_port, io->sda_pin, &I2C_pin_cfg_af);
  GPIO_AFConfig(io->sda_port, io->sda_pin, io->sda_func);

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2C_INFO));

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
int32_t I2Cx_Uninitialize(I2C_RESOURCES *i2c)
{
  I2C_IO *io = &i2c->io;

  /* Unconfigure SCL Pin */
  GPIO_PinConfig(io->scl_port, io->scl_pin, &I2C_pin_cfg_analog);
  /* Unconfigure SDA Pin */
  GPIO_PinConfig(io->sda_port, io->sda_pin, &I2C_pin_cfg_analog);

  i2c->info->flags = 0U;

  return (ARM_DRIVER_OK);
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
  uint32_t cr1;
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  switch (state) {
    case ARM_POWER_OFF:
      /* Enable I2C clock */
      RCC->APB1ENR |= i2c->rcc_mask;

      /* Disable I2C peripheral */
      reg->CR1 = 0;

      /* Disable I2C IRQ */
      NVIC_DisableIRQ(i2c->irq_num);

      /* Disable peripheral clock */
      RCC->APB1ENR &= ~i2c->rcc_mask;

      info->status.busy             = 0U;
      info->status.mode             = 0U;
      info->status.direction        = 0U;
      info->status.general_call     = 0U;
      info->status.arbitration_lost = 0U;
      info->status.bus_error        = 0U;

      info->flags &= ~I2C_FLAG_POWER;
      break;

    case ARM_POWER_FULL:
      if ((info->flags & I2C_FLAG_INIT) == 0U) {
        return (ARM_DRIVER_ERROR);
      }

      if ((info->flags & I2C_FLAG_POWER) != 0U) {
        return (ARM_DRIVER_OK);
      }

      /* Enable I2C clock */
      RCC->APB1ENR |= i2c->rcc_mask;

      /* Clear and Enable I2C IRQ */
      NVIC_ClearPendingIRQ(i2c->irq_num);
      NVIC_EnableIRQ(i2c->irq_num);

      /* Reset the peripheral */
      RCC->APB1RSTR |=  i2c->rcc_mask;
      __NOP(); __NOP(); __NOP(); __NOP();
      RCC->APB1RSTR &= ~i2c->rcc_mask;

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
int32_t I2Cx_Control(uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *reg = i2c->reg;

  if ((info->flags & I2C_FLAG_POWER) == 0U) {
    /* I2C not powered */
    return (ARM_DRIVER_ERROR);
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

      if (presc < 0) {
        return (ARM_DRIVER_ERROR_UNSUPPORTED);
      }

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
        return (ARM_DRIVER_ERROR_UNSUPPORTED);
      }

      reg->CR1 &= ~I2C_CR1_PE;
      reg->TIMINGR = timing;
      reg->CR1 |= I2C_CR1_PE;

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
 * @param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * @param[in]   i2c           Pointer to I2C resources
 * @return      \ref execution_status
 */
static
int32_t I2Cx_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_RESOURCES *i2c)
{
  uint32_t cr2;
  uint32_t cnt;
  bool restart;
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if (!(info->flags & I2C_FLAG_SETUP)) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
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

  return (ARM_DRIVER_OK);
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
int32_t I2Cx_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num,
    bool xfer_pending, I2C_RESOURCES *i2c)
{
  uint32_t cr2;
  uint32_t cnt;
  bool restart;
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((addr & ~(ARM_I2C_ADDRESS_10BIT | ARM_I2C_ADDRESS_GC)) > 0x3FFU) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if (!(info->flags & I2C_FLAG_SETUP)) {
    /* Driver not yet configured */
    return (ARM_DRIVER_ERROR);
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
int32_t I2Cx_SlaveTransmit(const uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

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
int32_t I2Cx_SlaveReceive(uint8_t *data, uint32_t num, I2C_RESOURCES *i2c)
{
  I2C_INFO *info = i2c->info;
  I2C_TypeDef *i2c_reg = i2c->reg;

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
  if (num < 256) {
    i2c_reg->CR2 = (num << 16);
  }
  else {
    /* Send 255 data bytes and enable NBYTES reload */
    i2c_reg->CR2 = (255 << 16) | I2C_CR2_RELOAD;
  }

  return (ARM_DRIVER_OK);
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
  return (i2c->info->xfer.cnt);
}

/**
 * @brief       Get I2C status.
 * @param[in]   i2c   Pointer to I2C resources
 * @return      I2C status \ref ARM_I2C_STATUS
 */
static
ARM_I2C_STATUS I2Cx_GetStatus(I2C_RESOURCES *i2c)
{
  return (i2c->info->status);
}

/**
 * @brief       I2C Master state event handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
static
void I2Cx_IRQHandler(I2C_RESOURCES *i2c)
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
void I2C1_IRQHandler(void)
{
  I2Cx_IRQHandler(&I2C1_Resources);
}
#endif  /* USE_I2C1 */

#if defined(USE_I2C2)
/* I2C2 Driver wrapper functions */
/**
 *
 * @param cb_event
 * @return
 */
static
int32_t I2C2_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
  return (I2Cx_Initialize(cb_event, &I2C2_Resources));
}

/**
 *
 * @return
 */
static
int32_t I2C2_Uninitialize(void)
{
  return (I2Cx_Uninitialize(&I2C2_Resources));
}

/**
 *
 * @param state
 * @return
 */
static
int32_t I2C2_PowerControl(ARM_POWER_STATE state)
{
  return (I2Cx_PowerControl(state, &I2C2_Resources));
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
int32_t I2C2_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterTransmit(addr, data, num, xfer_pending, &I2C2_Resources));
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
int32_t I2C2_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
  return (I2Cx_MasterReceive(addr, data, num, xfer_pending, &I2C2_Resources));
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t I2C2_SlaveTransmit(const uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveTransmit(data, num, &I2C2_Resources));
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t I2C2_SlaveReceive(uint8_t *data, uint32_t num)
{
  return (I2Cx_SlaveReceive(data, num, &I2C2_Resources));
}

/**
 *
 * @return
 */
static
int32_t I2C2_GetDataCount(void)
{
  return (I2Cx_GetDataCount(&I2C2_Resources));
}

/**
 *
 * @param control
 * @param arg
 * @return
 */
static
int32_t I2C2_Control(uint32_t control, uint32_t arg)
{
  return (I2Cx_Control(control, arg, &I2C2_Resources));
}

/**
 *
 * @return
 */
static
ARM_I2C_STATUS I2C2_GetStatus(void)
{
  return (I2Cx_GetStatus(&I2C2_Resources));
}

/**
 *
 */
void I2C2_IRQHandler(void)
{
  I2Cx_IRQHandler(&I2C2_Resources);
}
#endif

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
/* I2C1 Driver Control Block */
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
#endif

#endif /* defined(USE_I2C1) || defined(USE_I2C2) */
