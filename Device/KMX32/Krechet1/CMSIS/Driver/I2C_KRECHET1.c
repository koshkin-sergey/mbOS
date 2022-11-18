/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver for KM211 KRECHET1
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <string.h>

#include "I2C_KRECHET1.h"

#if defined(USE_I2C0) || defined(USE_I2C1)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define I2C_FIFO_SIZE                   (8U)

#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

extern Driver_ADSU_t Driver_ADSU;
static Driver_ADSU_t *adsu = &Driver_ADSU;

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_I2C_API_VERSION,
  ARM_I2C_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_I2C_CAPABILITIES DriverCapabilities = {
  0U,          /* supports 10-bit addressing */
  0U
};

#if defined(USE_I2C0)
/* I2C0 Information (Run-Time) */
static I2C_INFO I2C0_Info;

/* I2C0 Resources */
static I2C_RESOURCES I2C0_Resources = {
  PRW_I2C0,
  ADSU_Periph_I2C0,
  I2C0_IRQn,
  I2C0_INT_PRIO,
  &I2C0_Info,
};
#endif /* USE_I2C0 */

#if defined(USE_I2C1)
/* I2C1 Information (Run-Time) */
static I2C_INFO I2C1_Info;

/* I2C1 Resources */
static I2C_RESOURCES I2C1_Resources = {
  PRW_I2C1,
  ADSU_Periph_I2C1,
  I2C1_IRQn,
  I2C1_INT_PRIO,
  &I2C1_Info,
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
  I2C_INFO *info = i2c->info;

  if (info->flags & I2C_INIT) {
    return (ARM_DRIVER_OK);
  }

  /* Reset Run-Time information structure */
  memset(info, 0x00, sizeof(I2C_INFO));

  /* Peripheral Enable */
  adsu->PeriphEnable(i2c->adsu_periph);

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
  /* Peripheral Disable */
  adsu->PeriphDisable(i2c->adsu_periph);

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
  I2C_INFO *info = i2c->info;
  uint32_t  value;
  uint32_t  offset;

  switch (state) {
    case ARM_POWER_OFF:
      __set_CpuReg(CPU_PRW_REG, PRW_I2C0);
      __set_PeriphReg(I2C_CFG_REG, I2C_Cfg_PullUp);

      info->flags &= ~I2C_POWER;
      break;

    case ARM_POWER_FULL:
      if ((info->flags & I2C_INIT) == 0U) {
        return (ARM_DRIVER_ERROR);
      }

      if ((info->flags & I2C_POWER) != 0U) {
        return (ARM_DRIVER_OK);
      }

      /* Setup I2C IRQ */
      __set_CpuReg(CPU_PRW_REG, PRW_CHIN);
      offset = ((i2c->irq_num - 3U) % 4U) * 8U;
      value  = __get_PeriphReg(CHIN_CFG1_REG) & ~(0xFFUL << offset);
      __set_PeriphReg(CHIN_CFG1_REG, value | (i2c->irq_prio << offset));

      /* Setup peripheral */
      __set_CpuReg(CPU_PRW_REG, i2c->prw);
      __set_PeriphReg(I2C_CFG_REG, I2C_Cfg_On);

      /* Ready for operation */
      info->flags |= I2C_POWER;
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
  uint32_t          state;
  I2C_INFO         *info = i2c->info;
  I2C_TX_XFER_INFO *tx   = &info->tx;

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

  __set_CpuReg(CPU_PRW_REG, i2c->prw);
  state = __get_PeriphReg(I2C_STAT_REG);

  if ((state & I2C_Stat_Host) == 0U) {
    /* New transfer, check the line is busy */
    if ((state & I2C_Stat_Busy) != 0U) {
      /* Bus is busy or locked */
      return (ARM_DRIVER_ERROR_BUSY);
    }
  }

  info->status    = (I2C_BUSY | I2C_MASTER | I2C_TRANSMITTER);
  info->xfer_ctrl = 0U;

  if (xfer_pending != false) {
    info->xfer_ctrl |= XFER_CTRL_XPENDING;
  }

  tx->data = data;
  tx->num  = num;
  tx->cnt  = 0U;

  __set_PeriphReg(I2C_TDAT_REG, I2C_TDat_Cond_Start | I2C_TDat_NoAck | (addr << 1U));

  /* Start Transfer */
  if ((state & I2C_Stat_Host) == 0U) {
    __set_PeriphReg(I2C_CON_REG, I2C_Con_StartTx);
  }

  __set_PeriphReg(I2C_INT_REG, I2C_Int_Master | I2C_Int_TxIE | I2C_Int_AdrErrIE | I2C_Int_DatErrIE | I2C_Int_ArbErrIE);

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
  uint32_t          state;
  I2C_INFO         *info = i2c->info;
  I2C_RX_XFER_INFO *rx   = &info->rx;

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

  __set_CpuReg(CPU_PRW_REG, i2c->prw);
  state = __get_PeriphReg(I2C_STAT_REG);

  if ((state & I2C_Stat_Host) == 0U) {
    /* New transfer, check the line is busy */
    if ((state & I2C_Stat_Busy) != 0U) {
      /* Bus is busy or locked */
      return (ARM_DRIVER_ERROR_BUSY);
    }
  }

  info->status    = (I2C_BUSY | I2C_MASTER | I2C_RECEIVER);
  info->xfer_ctrl = 0U;

  if (xfer_pending != false) {
    info->xfer_ctrl |= XFER_CTRL_XPENDING;
  }

  rx->data = data;
  rx->num  = num;
  rx->cnt  = 0U;

  __set_PeriphReg(I2C_TDAT_REG, I2C_TDat_Cond_Start | I2C_TDat_NoAck | ((addr << 1U) | 1U));

  /* Start Transfer */
  if ((state & I2C_Stat_Host) == 0U) {
    __set_PeriphReg(I2C_CON_REG, I2C_Con_StartTx);
  }

  __set_PeriphReg(I2C_INT_REG, I2C_Int_Master | I2C_Int_TxIE | I2C_Int_RxIE | I2C_Int_AdrErrIE | I2C_Int_DatErrIE | I2C_Int_ArbErrIE);

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
  I2C_INFO         *info = i2c->info;
  I2C_TX_XFER_INFO *tx   = &info->tx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_BUSY) != 0U) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status    = 0U;
  info->xfer_ctrl = 0U;

  tx->data      = data;
  tx->num       = num;
  tx->cnt       = 0U;

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
  I2C_INFO         *info = i2c->info;
  I2C_RX_XFER_INFO *rx   = &info->rx;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->status & I2C_BUSY) != 0U) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  info->status    = 0U;
  info->xfer_ctrl = 0U;

  rx->data = data;
  rx->num  = num;
  rx->cnt  = 0U;

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
  uint32_t  val;
  I2C_INFO *info = i2c->info;

  if ((info->status & I2C_MASTER)             == 0U &&
      (info->xfer_ctrl & XFER_CTRL_ADDR_DONE) == 0U) {
    return (-1);
  }

  if ((info->status & I2C_RECEIVER) == 0U) {
    val = info->tx.cnt;
  }
  else {
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
  uint32_t  master_freq;
  uint32_t  reg_value;
  uint32_t  scp;

  if ((info->flags & I2C_POWER) == 0U) {
    /* I2C not powered */
    return (ARM_DRIVER_ERROR);
  }

  switch (control) {
    case ARM_I2C_OWN_ADDRESS:
      break;

    case ARM_I2C_BUS_SPEED:
      switch (arg) {
        case ARM_I2C_BUS_SPEED_STANDARD:
          master_freq = 100000U;
          break;

        case ARM_I2C_BUS_SPEED_FAST:
          master_freq = 400000U;
          break;

        default:
          return (ARM_DRIVER_ERROR_UNSUPPORTED);
      }

      SystemCoreClockUpdate();
      scp = (SystemCoreClock / (4U * master_freq) - 1U) / 2U;
      __set_CpuReg(CPU_PRW_REG, i2c->prw);
      reg_value = __get_PeriphReg(I2C_CFG_REG) & ~I2C_Cfg_SCP_Msk;
      __set_PeriphReg(I2C_CFG_REG, reg_value | (scp << I2C_Cfg_SCP_Pos));
      __set_PeriphReg(I2C_FIFO_REG, 0U);

      /* Master configured, clock set */
      info->flags |= I2C_SETUP;
      break;

    case ARM_I2C_BUS_CLEAR:
      break;

    case ARM_I2C_ABORT_TRANSFER:
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
 * @fn          void I2C_IRQHandler(I2C_RESOURCES *i2c)
 * @brief       I2C Interrupt handler.
 * @param[in]   i2c   Pointer to I2C resources
 */
__NO_INLINE
void I2C_IRQHandler(I2C_RESOURCES *i2c)
{
  uint32_t event;
  uint32_t flags;
  uint32_t state;
  uint32_t cnt;
  I2C_INFO *info;
  I2C_TX_XFER_INFO *tx;
  I2C_RX_XFER_INFO *rx;

  event = 0U;
  info  = i2c->info;
  tx    = &info->tx;

  __set_CpuReg(CPU_PRW_REG, i2c->prw);

  state = __get_PeriphReg(I2C_STAT_REG);
  flags = __get_PeriphReg(I2C_FLAGS_REG);

  if ((flags & (I2C_Flags_StopErrIF | I2C_Flags_OddStopIF | I2C_Flags_SDAErrIF | I2C_Flags_StartErrIF)) != 0U) {
    info->status |= I2C_ARBITRATION_LOST;
    info->status &= ~(I2C_BUSY | I2C_MASTER);
    event = ARM_I2C_EVENT_TRANSFER_DONE | ARM_I2C_EVENT_ARBITRATION_LOST;
    __set_PeriphReg(I2C_CON_REG, I2C_Con_SDAErrIF | I2C_Con_StopErrIF | I2C_Con_OddStopIF | I2C_Con_StartErrIF);
    __set_PeriphReg(I2C_INT_REG, 0U);
  }
  else {
    if ((state & I2C_Stat_Host) != 0U) {
      /* Master Mode */
      if ((flags & (I2C_Flags_AdrErrIF | I2C_Flags_DatErrIF)) != 0U) {
        __set_PeriphReg(I2C_CON_REG, I2C_Con_AdrErrIF | I2C_Con_DatErrIF);
        __set_PeriphReg(I2C_TDAT_REG, I2C_TDat_Cond_Stop | I2C_TDat_NoAck | 0xFFU);
      }
      else if ((flags & I2C_Flags_TxIF) != 0U) {
        if ((info->status & I2C_RECEIVER) == 0U) {
          /* Master Transmit */
          cnt = (state & I2C_Stat_TxCnt_Msk) >> I2C_Stat_TxCnt_Pos;
          while (cnt < I2C_FIFO_SIZE) {
            if (tx->cnt < tx->num) {
              __set_PeriphReg(I2C_TDAT_REG, I2C_TDat_Cond_Data | I2C_TDat_NoAck | tx->data[tx->cnt++]);
              ++cnt;
            }
            else {
              if ((info->xfer_ctrl & XFER_CTRL_XPENDING) == 0U) {
                __set_PeriphReg(I2C_TDAT_REG, I2C_TDat_Cond_Stop | I2C_TDat_NoAck | 0xFFU);
              }
              else {
                event = ARM_I2C_EVENT_TRANSFER_DONE;
                __set_PeriphReg(I2C_INT_REG, I2C_Int_Master);
              }
              break;
            }
          }
        }
        else {
          /* Master Receive */
          cnt = (state & I2C_Stat_RxCnt_Msk) >> I2C_Stat_RxCnt_Pos;
        }
      }
      else if ((flags & I2C_Flags_RxIF) != 0U) {

      }
    }
    else if ((state & I2C_Stat_Slave) != 0U) {
      /* Slave Mode */

    }
    else {
      info->status &= ~(I2C_BUSY | I2C_MASTER);
      event |= ARM_I2C_EVENT_TRANSFER_DONE;
      if (tx->cnt == 0U) {
        event |= ARM_I2C_EVENT_ADDRESS_NACK;
      }
      __set_PeriphReg(I2C_INT_REG, 0U);
    }
  }

  /* Send events */
  if ((event != 0U) && (info->cb_event)) {
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
