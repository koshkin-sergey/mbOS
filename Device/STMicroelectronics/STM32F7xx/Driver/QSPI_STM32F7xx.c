/*
 * Copyright (C) 2019-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: QUAD SPI Driver for STMicroelectronics STM32F7xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <string.h>

#include <asm/stm32f7xx.h>
#include <Driver/QSPI_STM32F7xx.h>

#if defined(USE_QSPI0)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define QSPI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

#ifdef QSPI_DMA
static void QSPIx_DMA_Callback(uint32_t event, const void *param);
#endif

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  QSPI_API_VERSION,
  QSPI_DRV_VERSION
};

/* Driver Capabilities */
static const QSPI_CAPABILITIES DriverCapabilities = {
  1,  /* all the operations are performed using the QSPI registers */
  1,  /* the external Flash memory is mapped to the address space */
  1,  /* supports DDR Mode */
  1,  /* supports Dual-flash Mode */
};

static const GPIO_PIN_CFG_t QSPI_pin_cfg_af = {
    GPIO_MODE_AF_PP, GPIO_PULL_DISABLE, GPIO_SPEED_VERY_HIGH
};

static const GPIO_PIN_CFG_t QSPI_pin_cfg_analog = {
    GPIO_MODE_ANALOG, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

#if defined(USE_QSPI0)

/* QSPI0 Information (Run-Time) */
static QSPI_INFO_t          QSPI0_Info;
static QSPI_TRANSFER_INFO_t QSPI0_TransferInfo;
static QSPI_RESOURCES_t     QSPI0_Resources;

#ifdef USE_QSPI0_BK1_IO0_Pin
  static QSPI_PIN_t QSPI0_bk1_io0_pin = {
      QSPI0_BK1_IO0_GPIO_PORT,
      QSPI0_BK1_IO0_GPIO_PIN,
      QSPI0_BK1_IO0_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK1_IO1_Pin
  static QSPI_PIN_t QSPI0_bk1_io1_pin = {
      QSPI0_BK1_IO1_GPIO_PORT,
      QSPI0_BK1_IO1_GPIO_PIN,
      QSPI0_BK1_IO1_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK1_IO2_Pin
  static QSPI_PIN_t QSPI0_bk1_io2_pin = {
      QSPI0_BK1_IO2_GPIO_PORT,
      QSPI0_BK1_IO2_GPIO_PIN,
      QSPI0_BK1_IO2_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK1_IO3_Pin
  static QSPI_PIN_t QSPI0_bk1_io3_pin = {
      QSPI0_BK1_IO3_GPIO_PORT,
      QSPI0_BK1_IO3_GPIO_PIN,
      QSPI0_BK1_IO3_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK1_NCS_Pin
  static QSPI_PIN_t QSPI0_bk1_ncs_pin = {
      QSPI0_BK1_NCS_GPIO_PORT,
      QSPI0_BK1_NCS_GPIO_PIN,
      QSPI0_BK1_NCS_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK2_IO0_Pin
  static QSPI_PIN_t QSPI0_bk2_io0_pin = {
      QSPI0_BK2_IO0_GPIO_PORT,
      QSPI0_BK2_IO0_GPIO_PIN,
      QSPI0_BK2_IO0_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK2_IO1_Pin
  static QSPI_PIN_t QSPI0_bk2_io1_pin = {
      QSPI0_BK2_IO1_GPIO_PORT,
      QSPI0_BK2_IO1_GPIO_PIN,
      QSPI0_BK2_IO1_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK2_IO2_Pin
  static QSPI_PIN_t QSPI0_bk2_io2_pin = {
      QSPI0_BK2_IO2_GPIO_PORT,
      QSPI0_BK2_IO2_GPIO_PIN,
      QSPI0_BK2_IO2_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK2_IO3_Pin
  static QSPI_PIN_t QSPI0_bk2_io3_pin = {
      QSPI0_BK2_IO3_GPIO_PORT,
      QSPI0_BK2_IO3_GPIO_PIN,
      QSPI0_BK2_IO3_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_BK2_NCS_Pin
  static QSPI_PIN_t QSPI0_bk2_ncs_pin = {
      QSPI0_BK2_NCS_GPIO_PORT,
      QSPI0_BK2_NCS_GPIO_PIN,
      QSPI0_BK2_NCS_GPIO_FUNC,
  };
#endif

#ifdef USE_QSPI0_CLK_Pin
  static QSPI_PIN_t QSPI0_clk_pin = {
      QSPI0_CLK_GPIO_PORT,
      QSPI0_CLK_GPIO_PIN,
      QSPI0_CLK_GPIO_FUNC,
  };
#endif

#ifdef QSPI0_DMA_Stream
static DMA_Handle_t QSPI0_DMA_Handle;
static const DMA_Resources_t QSPI0_DMA = {
  &QSPI0_DMA_Handle,
  QSPI0_DMA_Stream,
  QSPI0_DMA_Channel,
  QSPI0_DMA_Priority,
  QSPIx_DMA_Callback,
  &QSPI0_Resources,
  DEV_QSPI_DMA_INT_PRIORITY,
  QSPI0_DMA_IRQn,
};
#endif

/* QSPI0 Resources */
static QSPI_RESOURCES_t QSPI0_Resources = {
  QUADSPI,
  {
#ifdef USE_QSPI0_BK1_IO0_Pin
      &QSPI0_bk1_io0_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK1_IO1_Pin
      &QSPI0_bk1_io1_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK1_IO2_Pin
      &QSPI0_bk1_io2_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK1_IO3_Pin
      &QSPI0_bk1_io3_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK1_NCS_Pin
      &QSPI0_bk1_ncs_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK2_IO0_Pin
      &QSPI0_bk2_io0_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK2_IO1_Pin
      &QSPI0_bk2_io1_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK2_IO2_Pin
      &QSPI0_bk2_io2_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK2_IO3_Pin
      &QSPI0_bk2_io3_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_BK2_NCS_Pin
      &QSPI0_bk2_ncs_pin,
#else
      NULL,
#endif
#ifdef USE_QSPI0_CLK_Pin
      &QSPI0_clk_pin,
#else
      NULL,
#endif
  },
  RCC_PERIPH_QSPI,
  QUADSPI_IRQn,
#ifdef QSPI0_DMA_Stream
  &QSPI0_DMA,
#else
  NULL,
#endif
  &QSPI0_Info,
  &QSPI0_TransferInfo,
};

#endif /* USE_QSPI0 */

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @fn          void PinConfig(const QSPI_PIN *io, const GPIO_PIN_CFG_t *pin_cfg)
 * @brief       Configure Pin
 * @param[in]   io       Pointer to QSPI_PIN
 * @param[in]   pin_cfg  Pointer to GPIO_PIN_CFG_t
 */
static
void PinConfig(const QSPI_PIN_t *io, const GPIO_PIN_CFG_t *pin_cfg)
{
  if ((io == NULL) || (pin_cfg == NULL))
    return;

  if (GPIO_GetPortClockState(io->port) == false)
    GPIO_PortClock(io->port, GPIO_PORT_CLK_ENABLE);

  if (pin_cfg->mode == GPIO_MODE_AF_PP || pin_cfg->mode == GPIO_MODE_AF_OD)
    GPIO_AFConfig(io->port, io->pin, io->func);

  GPIO_PinConfig(io->port, io->pin, pin_cfg);
}

/**
 *
 * @return
 */
int32_t CalcPrescalerValue(QSPI_RESOURCES_t *qspi, uint32_t freq)
{
  int32_t val;

  uint32_t pclk = RCC_GetPeriphFreq(qspi->rcc);
  for (val = 0; val < 8; val++) {
    if (freq >= (pclk >> (val + 1)))
      break;
  }

  if ((val == 8) || (freq < (pclk >> (val + 1)))) {
    // Requested Bus Speed can not be configured
    val = -1;
  }

  return (val);
}

/**
 * @fn          ARM_DRIVER_VERSION QSPIx_GetVersion(void)
 * @brief       Get driver version.
 * @return      \ref ARM_DRIVER_VERSION
 */
static
ARM_DRIVER_VERSION QSPIx_GetVersion(void)
{
  return (DriverVersion);
}

/**
 * @fn          QSPI_CAPABILITIES QSPIx_GetCapabilities(void)
 * @brief       Get driver capabilities.
 * @return      QSPI_CAPABILITIES
 */
static
QSPI_CAPABILITIES QSPIx_GetCapabilities(void)
{
  return (DriverCapabilities);
}

/**
 * @fn          int32_t QSPI_Initialize(QSPI_SignalEvent_t cb_event, QSPI_RESOURCES *qspi)
 * @brief       Initialize QSPI Interface.
 * @param[in]   cb_event  Pointer to \ref QSPI_SignalEvent
 * @param[in]   qspi       Pointer to QSPI resources
 * @return      \ref execution_status
 */
static
int32_t QSPI_Initialize(QSPI_SignalEvent_t cb_event, QSPI_RESOURCES_t *qspi)
{
  QSPI_INFO_t *info = qspi->info;

  if (info->state & QSPI_INITIALIZED) {
    return (ARM_DRIVER_OK);
  }

  /* Initialize QSPI Run-Time Resources */
  info->cb_event          = cb_event;
  info->status.busy       = 0U;
  info->status.data_lost  = 0U;
  info->mode              = 0U;

  /* Clear transfer information */
  memset((void *)qspi->xfer, 0, sizeof(QSPI_TRANSFER_INFO_t));

  QSPI_IO_t *io = &qspi->io;
  const GPIO_PIN_CFG_t *pin_cfg = &QSPI_pin_cfg_af;

  /* Configure QSPI Pins */
  PinConfig(io->bk1_io0, pin_cfg);
  PinConfig(io->bk1_io1, pin_cfg);
  PinConfig(io->bk1_io2, pin_cfg);
  PinConfig(io->bk1_io3, pin_cfg);
  PinConfig(io->bk1_ncs, pin_cfg);
  PinConfig(io->bk2_io0, pin_cfg);
  PinConfig(io->bk2_io1, pin_cfg);
  PinConfig(io->bk2_io2, pin_cfg);
  PinConfig(io->bk2_io3, pin_cfg);
  PinConfig(io->bk2_ncs, pin_cfg);
  PinConfig(io->clk,     pin_cfg);

  info->state = QSPI_INITIALIZED;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t QSPI_Uninitialize(QSPI_RESOURCES *qspi)
 * @brief       De-initialize QSPI Interface.
 * @param[in]   qspi  Pointer to QSPI resources
 * @return      \ref execution_status
 */
static
int32_t QSPI_Uninitialize(QSPI_RESOURCES_t *qspi)
{
  QSPI_IO_t *io = &qspi->io;
  const GPIO_PIN_CFG_t *pin_cfg = &QSPI_pin_cfg_analog;

  /* Unconfigure QSPI Pins */
  PinConfig(io->bk1_io0, pin_cfg);
  PinConfig(io->bk1_io1, pin_cfg);
  PinConfig(io->bk1_io2, pin_cfg);
  PinConfig(io->bk1_io3, pin_cfg);
  PinConfig(io->bk1_ncs, pin_cfg);
  PinConfig(io->bk2_io0, pin_cfg);
  PinConfig(io->bk2_io1, pin_cfg);
  PinConfig(io->bk2_io2, pin_cfg);
  PinConfig(io->bk2_io3, pin_cfg);
  PinConfig(io->bk2_ncs, pin_cfg);
  PinConfig(io->clk,     pin_cfg);

  /* Clear QSPI state */
  qspi->info->state = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t QSPI_PowerControl(ARM_POWER_STATE state, QSPI_RESOURCES *qspi)
 * @brief       Control QSPI Interface Power.
 * @param[in]   state  Power state
 * @param[in]   qspi   Pointer to QSPI resources
 * @return      \ref  execution_status
 */
static
int32_t QSPI_PowerControl(ARM_POWER_STATE state, QSPI_RESOURCES_t *qspi)
{
  QSPI_INFO_t *info = qspi->info;

  switch (state) {
    case ARM_POWER_OFF:
      /* QSPI peripheral reset */
      RCC_ResetPeriph(qspi->rcc);
      /* Disable QSPI IRQ */
      NVIC_DisableIRQ(qspi->irq_num);

      /* Uninitialize DMA */
#ifdef QSPI_DMA
      if (qspi->dma != NULL) {
        DMA_Uninitialize(qspi->dma);
      }
#endif

      /* Disable peripheral clock */
      RCC_DisablePeriph(qspi->rcc);

      /* Clear status flags */
      info->status.busy       = 0U;
      info->status.data_lost  = 0U;

      /* Clear powered flag */
      info->state &= ~QSPI_POWERED;
      break;

    case ARM_POWER_FULL:
      if ((info->state & QSPI_INITIALIZED) == 0U) {
        return (ARM_DRIVER_ERROR);
      }

      if ((info->state & QSPI_POWERED) != 0U) {
        return (ARM_DRIVER_OK);
      }

      /* Clear status flags */
      info->status.busy       = 0U;
      info->status.data_lost  = 0U;

      /* Ready for operation - set powered flag */
      info->state |= QSPI_POWERED;

      /* Enable the peripheral clock */
      RCC_EnablePeriph(qspi->rcc);

      /* Clear and Enable QSPI IRQ */
      NVIC_ClearPendingIRQ(qspi->irq_num);
      NVIC_SetPriority(qspi->irq_num, DEV_QSPI_INT_PRIORITY);
      NVIC_EnableIRQ(qspi->irq_num);

      /* Initialize DMA */
#ifdef QSPI_DMA
      if (qspi->dma != NULL) {
        DMA_StreamConfig_t *cfg = &qspi->dma->handle->config;

        cfg->Mode      = DMA_MODE_NORMAL;
        cfg->FIFOMode  = DMA_FIFOMODE_DISABLE;
        cfg->MemBurst  = DMA_MBURST_SINGLE;
        cfg->PerBurst  = DMA_PBURST_SINGLE;

        DMA_Initialize(qspi->dma);
      }
#endif

      /* Reset the peripheral */
      RCC_ResetPeriph(qspi->rcc);
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t QSPI_Send(const void *data, uint32_t num, QSPI_RESOURCES_t *qspi)
 * @brief       Start sending data to QSPI transmitter.
 * @param[in]   data  Pointer to buffer with data to send to QSPI transmitter
 * @param[in]   num   Number of data items to send
 * @param[in]   qspi  Pointer to QSPI resources
 * @return      \ref  execution_status
 */
static
int32_t QSPI_Send(const void *data, uint32_t num, QSPI_RESOURCES_t *qspi)
{
  QSPI_INFO_t          *info = qspi->info;
  QSPI_TRANSFER_INFO_t *xfer = qspi->xfer;
  QUADSPI_TypeDef       *reg = qspi->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->state & QSPI_CONFIGURED) == 0U) {
    return (ARM_DRIVER_ERROR);
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Update QSPI statuses */
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;

  /* Save transfer info */
  xfer->buf = (uint8_t *)((uint32_t)data);
  xfer->num = num;
  xfer->cnt = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t QSPI_Receive(void *data, uint32_t num, QSPI_RESOURCES_t *qspi)
 * @brief       Start receiving data from QSPI receiver.
 * @param[out]  data  Pointer to buffer for data to receive from QSPI receiver
 * @param[in]   num   Number of data items to receive
 * @param[in]   qspi  Pointer to QSPI resources
 * @return      \ref  execution_status
 */
static
int32_t QSPI_Receive(void *data, uint32_t num, QSPI_RESOURCES_t *qspi)
{
  QSPI_INFO_t          *info = qspi->info;
  QSPI_TRANSFER_INFO_t *xfer = qspi->xfer;
  QUADSPI_TypeDef       *reg = qspi->reg;

  if ((data == NULL) || (num == 0U)) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((info->state & QSPI_CONFIGURED) == 0U) {
    return (ARM_DRIVER_ERROR);
  }

  if (info->status.busy) {
    return (ARM_DRIVER_ERROR_BUSY);
  }

  /* Update SPI statuses */
  info->status.busy       = 1U;
  info->status.data_lost  = 0U;

  /* Save transfer info */
  xfer->buf = (uint8_t *)data;
  xfer->num = num;
  xfer->cnt = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          uint32_t QSPI_GetDataCount(QSPI_RESOURCES *qspi)
 * @brief       Get transferred data count.
 * @param[in]   qspi  Pointer to QSPI resources
 * @return      Number of data items transferred
 */
static
uint32_t QSPI_GetDataCount(QSPI_RESOURCES_t *qspi)
{
  return (qspi->xfer->cnt);
}

/**
 * @fn          int32_t QSPI_Control(uint32_t control, uint32_t arg, QSPI_RESOURCES *qspi)
 * @brief       Control QSPI Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @param[in]   qspi     Pointer to QSPI resources
 * @return      \ref execution_status
 */
static
int32_t QSPI_Control(uint32_t control, uint32_t arg, QSPI_RESOURCES_t *qspi)
{
  QSPI_INFO_t     *info = qspi->info;
  QUADSPI_TypeDef *reg  = qspi->reg;

  if ((info->state & QSPI_POWERED) == 0U) {
    return (ARM_DRIVER_ERROR);
  }

  return (ARM_DRIVER_OK);
}

/**
 * @fn          QSPI_STATUS QSPI_GetStatus(QSPI_RESOURCES_t *qspi)
 * @brief       Get QSPI status.
 * @param[in]   qspi  Pointer to QSPI resources
 * @return      QSPI status \ref QSPI_STATUS
 */
static
QSPI_STATUS QSPI_GetStatus(QSPI_RESOURCES_t *qspi)
{
  QSPI_STATUS status;

  status.busy      = qspi->info->status.busy;
  status.data_lost = qspi->info->status.data_lost;

  return (status);
}

/**
 * @fn          void QSPI_IRQHandler(QSPI_RESOURCES_t *qspi)
 * @brief       QSPI Interrupt handler.
 * @param[in]   qspi  Pointer to QSPI resources
 */
void QSPI_IRQHandler(QSPI_RESOURCES_t *qspi)
{
  QSPI_INFO_t          *info = qspi->info;
  QSPI_TRANSFER_INFO_t *xfer = qspi->xfer;
  QUADSPI_TypeDef      *reg  = qspi->reg;

  uint32_t event = 0U;

  /* Send event */
  if ((event != 0U) && ((info->cb_event != NULL))) {
    info->cb_event(event);
  }
}

#ifdef QSPI_DMA
static
void QSPIx_DMA_Callback(uint32_t event, const void *param)
{
  QSPI_RESOURCES_t *qspi = param;

  if (event & DMA_EVENT_TRANSFER_COMPLETE) {

  }
}
#endif  /* QSPI_DMA */

#if defined(USE_QSPI0)
  QSPIx_EXPORT_DRIVER(0);
#endif  /* USE_QSPI0 */

#endif /* defined(USE_QSPI0) */

/* ----------------------------- End of file ---------------------------------*/
