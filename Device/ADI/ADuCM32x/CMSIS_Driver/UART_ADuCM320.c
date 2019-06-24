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
 * Project: UART Driver for ADI ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "CLK_ADuCM320.h"
#include "UART_ADuCM320.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ARM_USART_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0)  /* driver version */

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_USART_API_VERSION,
    ARM_USART_DRV_VERSION
};

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

#if defined(USE_USART0)

static const GPIO_PIN_ID_t USART0_pin_tx = {
    USART0_TX_GPIO_PORT, USART0_TX_GPIO_PIN, USART0_TX_GPIO_FUNC
};

static const GPIO_PIN_ID_t USART0_pin_rx = {
    USART0_RX_GPIO_PORT, USART0_RX_GPIO_PIN, USART0_RX_GPIO_FUNC
};

static USART_INFO_t USART0_Info;

static const USART_RESOURCES_t USART0_Resources = {
    {   // Capabilities
        1,    ///< supports UART (Asynchronous) mode
        0,    ///< supports Synchronous Master mode
        0,    ///< supports Synchronous Slave mode
        0,    ///< supports UART Single-wire mode
        0,    ///< supports UART IrDA mode
        0,    ///< supports UART Smart Card mode
        0,    ///< Smart Card Clock generator available
        0,    ///< RTS Flow Control available
        0,    ///< CTS Flow Control available
        0,    ///< Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
        0,    ///< Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
        0,    ///< RTS Line: 0=not available, 1=available
        0,    ///< CTS Line: 0=not available, 1=available
        0,    ///< DTR Line: 0=not available, 1=available
        0,    ///< DSR Line: 0=not available, 1=available
        0,    ///< DCD Line: 0=not available, 1=available
        0,    ///< RI Line: 0=not available, 1=available
        0,    ///< Signal CTS change event: \ref ARM_USART_EVENT_CTS
        0,    ///< Signal DSR change event: \ref ARM_USART_EVENT_DSR
        0,    ///< Signal DCD change event: \ref ARM_USART_EVENT_DCD
        0,    ///< Signal RI change event: \ref ARM_USART_EVENT_RI
    },
    pADI_UART,
    {
        &USART0_pin_tx,
        &USART0_pin_rx,
    },
    UART_IRQn,
    NULL,
    NULL,
    &USART0_Info
};

#endif // USE_USART0

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Set baudrate dividers
 * @param[in]   baudrate  Usart baudrate
 * @param[in]   usart     Pointer to USART resources
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
static
int32_t USART_SetBaudrate(uint32_t baudrate, USART_RESOURCES_t *usart)
{
  int i1, iDiv, iRtC;
  unsigned long long ullRtClk = 80000000;            // The root clock speed

  iDiv = (pADI_CLKCTL->CLKCON1 & 0x0700);         // Read UART clock as set by CLKCON1[10:8]
  iDiv = iDiv >> 8;
  iDiv = 1 << iDiv;                                  // 2^iDiv

  iRtC = (pADI_CLKCTL->CLKCON0 & CLKCON0_CLKMUX_MSK); // Check what is the root clock

  switch (iRtC) {
    case CLKCON0_CLKMUX_SPLL:
      ullRtClk = 80000000;
      break;

    case CLKCON0_CLKMUX_UPLL:
      ullRtClk = 60000000;
      break;

    case CLKCON0_CLKMUX_HFOSC:
      ullRtClk = 16000000;
      break;

    case CLKCON0_CLKMUX_EXTCLK:
      ullRtClk = 80000000;                      //External clock is assumed to be 80MhZ, if different
                                                //clock speed is used, this should be changed
      break;

    default:
      break;
  }

  i1 = (ullRtClk/(32*iDiv))/baudrate;           // UART baud rate clock source is PCLK divided by 32
  usart->reg->COMDIV = i1;
  usart->reg->COMFBR = 0x8800|(((((2048/(32*iDiv))*ullRtClk)/i1)/baudrate)-2048);

  usart->info->baudrate = baudrate;

  return 0;
}

/**
 * @brief   Get driver version.
 * @return  ARM_DRIVER_VERSION
 */
static
ARM_DRIVER_VERSION USARTx_GetVersion(void)
{
  return DriverVersion;
}

/**
 * @brief     Get driver capabilities.
 * @param[in] uart  Pointer to USART resources.
 * @return    ARM_USART_CAPABILITIES
 */
static
ARM_USART_CAPABILITIES USART_GetCapabilities(USART_RESOURCES_t *uart)
{
  return uart->capabilities;
}

/**
 * @brief     Initialize USART Interface.
 * @param[in] cb_event  Pointer to ARM_USART_SignalEvent
 * @param[in] uart      Pointer to USART resources
 * @return    Execution_status
 */
static
int32_t USART_Initialize(ARM_USART_SignalEvent_t cb_event, USART_RESOURCES_t *usart)
{
  if (usart->info->flags & USART_FLAG_INITIALIZED) {
    // Driver is already initialized
    return ARM_DRIVER_OK;
  }

  // Initialize USART Run-time Resources
  usart->info->cb_event = cb_event;

  usart->info->rx_status.rx_busy          = 0U;
  usart->info->rx_status.rx_overflow      = 0U;
  usart->info->rx_status.rx_break         = 0U;
  usart->info->rx_status.rx_framing_error = 0U;
  usart->info->rx_status.rx_parity_error  = 0U;

  usart->info->xfer.send_active           = 0U;

  // DMA Initialize
  if (usart->dma_tx || usart->dma_rx) {
    DMA_Initialize();
  }

  usart->info->flags = USART_FLAG_INITIALIZED;

  return ARM_DRIVER_OK;
}

/**
 * @brief     De-initialize USART Interface.
 * @param[in] usart   Pointer to USART resources
 * @return    Execution_status
 */
static
int32_t USART_Uninitialize(USART_RESOURCES_t *usart)
{
  USART_PINS_t *pins = &usart->pins;

  // Reset TX pin configuration
  GPIO_AFConfig(pins->tx->port, pins->tx->pin, GPIO_PIN_FUNC_0);

  // Reset RX pin configuration
  GPIO_AFConfig(pins->rx->port, pins->rx->pin, GPIO_PIN_FUNC_0);

  // DMA Uninitialize
  if (usart->dma_tx || usart->dma_rx)
    DMA_Uninitialize();

  // Reset USART status flags
  usart->info->flags = 0U;

  return ARM_DRIVER_OK;
}

/**
 * @brief       Control USART Interface Power.
 * @param[in]   state   Power state
 * @param[in]   usart    Pointer to USART resources
 * @return      Execution_status
 */
static
int32_t USART_PowerControl(ARM_POWER_STATE state, USART_RESOURCES_t *usart)
{
  switch (state) {
    case ARM_POWER_OFF:
      // Disable USART IRQ
      NVIC_Disable_IRQ(usart->irq_num);

      // If DMA mode - disable TX DMA channel
      if ((usart->dma_tx) && (usart->info->xfer.send_active != 0U))
        DMA_ChannelDisable(usart->dma_tx->channel);

      // If DMA mode - disable DMA channel
      if ((usart->dma_rx) && (usart->info->rx_status.rx_busy))
        DMA_ChannelDisable(usart->dma_rx->channel);

      // Clear USART flags
      usart->reg->COMLSR;

      // Disable interrupts
      usart->reg->COMIEN = COMIEN_RVAL;

      // Disable USART peripheral clock
      CLK_PeriphGateControl(CLK_PERIPH_UART, CLOCK_OFF);

      // Clear pending USART interrupts in NVIC
      NVIC_ClearPendingIRQ(usart->irq_num);

      // Clear driver variables
      usart->info->rx_status.rx_busy          = 0U;
      usart->info->rx_status.rx_overflow      = 0U;
      usart->info->rx_status.rx_break         = 0U;
      usart->info->rx_status.rx_framing_error = 0U;
      usart->info->rx_status.rx_parity_error  = 0U;
      usart->info->xfer.send_active           = 0U;

      usart->info->flags &= ~USART_FLAG_POWERED;
      break;

    case ARM_POWER_FULL:
      if ((usart->info->flags & USART_FLAG_INITIALIZED) == 0U)
        return ARM_DRIVER_ERROR;

      if ((usart->info->flags & USART_FLAG_POWERED) != 0U)
        return ARM_DRIVER_OK;

      // Enable USART peripheral clock
      CLK_PeriphGateControl(CLK_PERIPH_UART, CLOCK_ON);

      // Clear USART flags
      usart->reg->COMLSR;

      // Disable interrupts
      usart->reg->COMIEN = COMIEN_RVAL;

      // Clear driver variables
      usart->info->rx_status.rx_busy          = 0U;
      usart->info->rx_status.rx_overflow      = 0U;
      usart->info->rx_status.rx_break         = 0U;
      usart->info->rx_status.rx_framing_error = 0U;
      usart->info->rx_status.rx_parity_error  = 0U;

      usart->info->flags                      = 0U;
      usart->info->xfer.send_active           = 0U;

      usart->info->flags = USART_FLAG_POWERED | USART_FLAG_INITIALIZED;

      // Clear and Enable USART IRQ
      NVIC_ClearPendingIRQ(usart->irq_num);
      NVIC_Enable_IRQ(usart->irq_num, HAL_USART_INT_PRIO);
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/**
 * @brief       Start sending data to USART transmitter.
 * @param[in]   data  Pointer to buffer with data to send to USART transmitter
 * @param[in]   num   Number of data items to send
 * param[in]    usart Pointer to USART resources
 * @return      Execution_status
 */
static
int32_t USART_Send(const void *data, uint32_t num, USART_RESOURCES_t *usart)
{
  if ((data == NULL) || (num == 0U)) {
    // Invalid parameters
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((usart->info->flags & USART_FLAG_CONFIGURED) == 0U) {
    // USART is not configured (mode not selected)
    return ARM_DRIVER_ERROR;
  }

  if (usart->info->xfer.send_active != 0U) {
    // Send is not completed yet
    return ARM_DRIVER_ERROR_BUSY;
  }

  // Set Send active flag
  usart->info->xfer.send_active = 1U;

  // Save transmit buffer info
  usart->info->xfer.tx_buf = (uint8_t *)data;
  usart->info->xfer.tx_num = num;
  usart->info->xfer.tx_cnt = 0U;

  // Fill TX holding register
  if (usart->reg->COMLSR & COMLSR_THRE)
    usart->reg->COMTX = usart->info->xfer.tx_buf[usart->info->xfer.tx_cnt++];

  // Enable transmit holding register empty interrupt
  usart->reg->COMIEN |= COMIEN_ETBEI;

  return ARM_DRIVER_OK;
}

/**
 * @brief       Start receiving data from USART receiver.
 * @param[out]  data  Pointer to buffer for data to receive from USART receiver
 * @param[in]   num   Number of data items to receive
 * @param[in]   usart Pointer to USART resources
 * @return      Execution_status
 */
static
int32_t USART_Receive(void *data, uint32_t num, USART_RESOURCES_t *usart)
{
  if ((data == NULL) || (num == 0U)) {
    // Invalid parameters
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((usart->info->flags & USART_FLAG_CONFIGURED) == 0U) {
    // USART is not configured (mode not selected)
    return ARM_DRIVER_ERROR;
  }

  // Check if receiver is busy
  if (usart->info->rx_status.rx_busy == 1U) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  // Set RX busy flag
  usart->info->rx_status.rx_busy = 1U;

  // Clear RX statuses
  usart->info->rx_status.rx_break          = 0U;
  usart->info->rx_status.rx_framing_error  = 0U;
  usart->info->rx_status.rx_overflow       = 0U;
  usart->info->rx_status.rx_parity_error   = 0U;

  // Save receive buffer info
  usart->info->xfer.rx_buf = (uint8_t *)data;
  usart->info->xfer.rx_num = num;
  usart->info->xfer.rx_cnt = 0U;

  // Enable receive data available interrupt
  usart->reg->COMIEN |= COMIEN_ERBFI;

  return ARM_DRIVER_OK;
}

/**
 * @brief       Start sending/receiving data to/from USART transmitter/receiver.
 * @param[in]   data_out  Pointer to buffer with data to send to USART transmitter
 * @param[out]  data_in   Pointer to buffer for data to receive from USART receiver
 * @param[in]   num       Number of data items to transfer
 * @param[in]   usart     Pointer to USART resources
 * @return      Execution_status
 */
static
int32_t USART_Transfer(const void *data_out, void *data_in, uint32_t num,
    USART_RESOURCES_t *uart)
{
  // Only in synchronous mode
  return ARM_DRIVER_ERROR;
}

/**
 * @brief       Get transmitted data count.
 * @param[in]   usart     Pointer to USART resources
 * @return      number of data items transmitted
 */
static
uint32_t USART_GetTxCount(USART_RESOURCES_t *usart)
{
  uint32_t cnt;

  if (usart->dma_tx) {
    cnt = DMA_ChannelGetCount(usart->dma_tx->channel);
  } else {
    cnt = usart->info->xfer.tx_cnt;
  }

  return cnt;
}

/**
 * @brief       Get received data count.
 * @param[in]   usart     Pointer to USART resources
 * @return      number of data items received
 */
static
uint32_t USART_GetRxCount(USART_RESOURCES_t *usart)
{
  uint32_t cnt;

  if (usart->dma_rx) {
    cnt = DMA_ChannelGetCount(usart->dma_rx->channel);
  } else {
    cnt = usart->info->xfer.rx_cnt;
  }

  return cnt;
}

/**
 * @brief       Control USART Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @param[in]   usart    Pointer to USART resources
 * @return      common execution_status and driver specific usart_execution_status
 */
static
int32_t USART_Control(uint32_t control, uint32_t arg, USART_RESOURCES_t *usart)
{
  uint16_t lcr;
  USART_PINS_t *pins = &usart->pins;

  if ((usart->info->flags & USART_FLAG_POWERED) == 0U) {
    // USART not powered
    return ARM_DRIVER_ERROR;
  }

  switch (control & ARM_USART_CONTROL_Msk) {
    // Control TX
    case ARM_USART_CONTROL_TX:
      // Check if TX line available
      if (usart->pins.tx == NULL)
        return ARM_DRIVER_ERROR;

      if (arg) {
        GPIO_AFConfig(pins->tx->port, pins->tx->pin, pins->tx->func);
        usart->info->flags |= USART_FLAG_TX_ENABLED;
      }
      else {
        usart->info->flags &= ~USART_FLAG_TX_ENABLED;
        GPIO_AFConfig(pins->tx->port, pins->tx->pin, GPIO_PIN_FUNC_0);
      }
      return ARM_DRIVER_OK;

    // Control RX
    case ARM_USART_CONTROL_RX:
      if (usart->pins.rx == NULL)
        return ARM_DRIVER_ERROR;

      // RX Line interrupt enable (overrun, framing, parity error, break)
      if (arg) {
        GPIO_AFConfig(pins->rx->port, pins->rx->pin, pins->rx->func);
        usart->info->flags |= USART_FLAG_RX_ENABLED;
        usart->reg->COMIEN |= COMIEN_ELSI;
      }
      else {
        usart->info->flags &= ~USART_FLAG_RX_ENABLED;
        usart->reg->COMIEN &= ~COMIEN_ELSI;
        GPIO_AFConfig(pins->rx->port, pins->rx->pin, GPIO_PIN_FUNC_0);
      }
      return ARM_DRIVER_OK;

    // Control break
    case ARM_USART_CONTROL_BREAK:
      if (arg) {
        if (usart->info->xfer.send_active != 0U)
          return ARM_DRIVER_ERROR_BUSY;

        usart->reg->COMLCR |= COMLCR_BRK_EN;
        // Set Send active flag
        usart->info->xfer.send_active = 1U;
      }
      else {
        usart->reg->COMLCR &= ~COMLCR_BRK_EN;
        // Clear Send active flag
        usart->info->xfer.send_active = 0U;
      }
      return ARM_DRIVER_OK;

    // Abort Send
    case ARM_USART_ABORT_SEND:
      // Disable transmit holding register empty interrupt
      usart->reg->COMIEN &= ~COMIEN_ETBEI;

      // If DMA mode - disable DMA channel
      if ((usart->dma_tx) && (usart->info->xfer.send_active != 0U)) {
        DMA_ChannelDisable(usart->dma_tx->channel);
      }

      // Clear Send active flag
      usart->info->xfer.send_active = 0U;
      return ARM_DRIVER_OK;

    // Abort receive
    case ARM_USART_ABORT_RECEIVE:
      // Disable receive data available interrupt
      usart->reg->COMIEN &= ~COMIEN_ERBFI;

      // If DMA mode - disable DMA channel
      if ((usart->dma_rx) && (usart->info->rx_status.rx_busy)) {
        DMA_ChannelDisable(usart->dma_rx->channel);
      }

      // Clear RX busy status
      usart->info->rx_status.rx_busy = 0U;
      return ARM_DRIVER_OK;

    // Abort transfer
    case ARM_USART_ABORT_TRANSFER:
      // Disable transmit holding register empty and
      // receive data available interrupts
      usart->reg->COMIEN &= ~(COMIEN_ERBFI | COMIEN_ETBEI);

      // If DMA mode - disable DMA channel
      if ((usart->dma_tx) && (usart->info->xfer.send_active != 0U)) {
        DMA_ChannelDisable(usart->dma_tx->channel);
      }
      if ((usart->dma_rx) && (usart->info->rx_status.rx_busy)) {
        DMA_ChannelDisable (usart->dma_rx->channel);
      }

      // Clear busy statuses
      usart->info->rx_status.rx_busy = 0U;
      usart->info->xfer.send_active  = 0U;
      return ARM_DRIVER_OK;

    case ARM_USART_MODE_ASYNCHRONOUS:
      break;

    // Unsupported command
    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  // Check if Receiver/Transmitter is busy
  if (usart->info->rx_status.rx_busy || (usart->info->xfer.send_active != 0U)) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  // USART Data bits
  switch (control & ARM_USART_DATA_BITS_Msk) {
    case ARM_USART_DATA_BITS_5:
      lcr = COMLCR_WLS_FIVEBITS;
      break;
    case ARM_USART_DATA_BITS_6:
      lcr = COMLCR_WLS_SIXBITS;
      break;
    case ARM_USART_DATA_BITS_7:
      lcr = COMLCR_WLS_SEVENBITS;
      break;
    case ARM_USART_DATA_BITS_8:
      lcr = COMLCR_WLS_EIGHTBITS;
      break;
    default:
      return ARM_USART_ERROR_DATA_BITS;
  }

  // USART Parity
  switch (control & ARM_USART_PARITY_Msk) {
    case ARM_USART_PARITY_NONE:
      break;
    case ARM_USART_PARITY_EVEN:
      lcr |= (COMLCR_EPS_EVEN | COMLCR_PEN);
      break;
    case ARM_USART_PARITY_ODD:
      lcr |= COMLCR_PEN;
      break;
    default:
      return ARM_USART_ERROR_PARITY;
  }

  // USART Stop bits
  switch (control & ARM_USART_STOP_BITS_Msk) {
    case ARM_USART_STOP_BITS_1:
      break;
    default:
      return ARM_USART_ERROR_STOP_BITS;
  }

  // USART Baudrate
  if (USART_SetBaudrate(arg, usart) == -1) {
    return ARM_USART_ERROR_BAUDRATE;
  }

  // Configure TX pin regarding mode and transmitter state
  if (usart->info->flags & USART_FLAG_TX_ENABLED) {
    // Pin function = USART TX
    GPIO_AFConfig(pins->tx->port, pins->tx->pin, pins->tx->func);
  } else {
    // Pin function = GPIO
    GPIO_AFConfig(pins->tx->port, pins->tx->pin, GPIO_PIN_FUNC_0);
  }

  // Configure RX pin regarding mode and receiver state
  if (usart->info->flags & USART_FLAG_RX_ENABLED) {
    // Pin function = USART RX
    GPIO_AFConfig(pins->rx->port, pins->rx->pin, pins->rx->func);
  } else {
    // Pin function = GPIO
    GPIO_AFConfig(pins->rx->port, pins->rx->pin, GPIO_PIN_FUNC_0);
  }

  // Configure Line control register
  usart->reg->COMLCR = ((usart->reg->COMLCR & (COMLCR_BRK | COMLCR_SP)) | lcr);

  // Set configured flag
  usart->info->flags |= USART_FLAG_CONFIGURED;

  return ARM_DRIVER_OK;
}

/**
 * @brief       Get USART status.
 * @param[in]   usart     Pointer to USART resources
 * @return      USART status ARM_USART_STATUS
 */
static
ARM_USART_STATUS USART_GetStatus(USART_RESOURCES_t *usart)
{
  ARM_USART_STATUS stat;

  stat.tx_busy          = (usart->reg->COMLSR & COMLSR_TEMT ? (0U) : (1U));
  stat.rx_busy          = usart->info->rx_status.rx_busy;
  stat.tx_underflow     = 0U;
  stat.rx_overflow      = usart->info->rx_status.rx_overflow;
  stat.rx_break         = usart->info->rx_status.rx_break;
  stat.rx_framing_error = usart->info->rx_status.rx_framing_error;
  stat.rx_parity_error  = usart->info->rx_status.rx_parity_error;

  return stat;
}

/**
 * @brief       Set USART Modem Control line state.
 * @param[in]   control   ARM_USART_MODEM_CONTROL
 * @param[in]   usart     Pointer to USART resources
 * @return      Execution_status
 */
static
int32_t USART_SetModemControl(ARM_USART_MODEM_CONTROL control, USART_RESOURCES_t *usart)
{
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
 * @brief       Get USART Modem Status lines state.
 * @param[in]   usart     Pointer to USART resources
 * @return      modem status ARM_USART_MODEM_STATUS
 */
static
ARM_USART_MODEM_STATUS USART_GetModemStatus(USART_RESOURCES_t *uart)
{
  ARM_USART_MODEM_STATUS modem_status;

  modem_status.cts = 0U;
  modem_status.dsr = 0U;
  modem_status.ri  = 0U;
  modem_status.dcd = 0U;

  return modem_status;
}

/**
 * @brief       USART Interrupt handler.
 * @param[in]   usart     Pointer to USART resources
 */
static
void USART_IRQHandler(USART_RESOURCES_t *usart)
{
  uint32_t event = 0U;
  uint16_t iir = usart->reg->COMIIR;
  uint16_t lsr;
  volatile uint16_t msr;

  if ((iir & COMIIR_NIRQ) == 0U) {
    switch (iir & COMIIR_STA_MSK) {
      /* Modem status interrupt */
      case COMIIR_STA_MODEMSTATUS:
        msr = usart->reg->COMMSR;
        break;

      /* Transmit buffer empty interrupt */
      case COMIIR_STA_TXBUFEMPTY:
        if (usart->info->xfer.tx_num != usart->info->xfer.tx_cnt) {
          usart->reg->COMTX = usart->info->xfer.tx_buf[usart->info->xfer.tx_cnt++];
        }

        // Check if all data is transmitted
        if (usart->info->xfer.tx_num == usart->info->xfer.tx_cnt) {
          // Disable THRE interrupt
          usart->reg->COMIEN &= ~COMIEN_ETBEI;
          // Clear TX busy flag
          usart->info->xfer.send_active = 0U;
          event |= ARM_USART_EVENT_SEND_COMPLETE;
        }
        break;

      /* Receive buffer full interrupt */
      case COMIIR_STA_RXBUFFULL:
        // Read data from RX buffer register into receive buffer
        usart->info->xfer.rx_buf[usart->info->xfer.rx_cnt++] = usart->reg->COMRX;
        // Check if requested amount of data is received
        if (usart->info->xfer.rx_cnt == usart->info->xfer.rx_num) {
          // Disable RDA interrupt
          usart->reg->COMIEN &= ~COMIEN_ERBFI;
          // Clear RX busy flag and set receive transfer complete event
          usart->info->rx_status.rx_busy = 0U;
          event |= ARM_USART_EVENT_RECEIVE_COMPLETE;
        }
        break;

      /* Receive line status interrupt */
      case COMIIR_STA_RXLINESTATUS:
        lsr = usart->reg->COMLSR;
        // OverRun error
        if (lsr & COMLSR_OE) {
          usart->info->rx_status.rx_overflow = 1U;
          event |= ARM_USART_EVENT_RX_OVERFLOW;
        }

        // Parity error
        if (lsr & COMLSR_PE) {
          usart->info->rx_status.rx_parity_error = 1U;
          event |= ARM_USART_EVENT_RX_PARITY_ERROR;
        }

        // Break detected
        if (lsr & COMLSR_BI) {
          usart->info->rx_status.rx_break = 1U;
          event |= ARM_USART_EVENT_RX_BREAK;
        }

        // Framing error
        if(lsr & COMLSR_FE) {
          usart->info->rx_status.rx_framing_error = 1U;
          event |= ARM_USART_EVENT_RX_FRAMING_ERROR;
        }
        break;
    }
  }

  if ((usart->info->cb_event != NULL) && (event != 0U)) {
    usart->info->cb_event(event);
  }
}

#if defined(USE_USART0)

/* - USART0 Driver wrapper functions -----------------------------------------*/

/**
 * @brief   Get driver capabilities.
 * @return
 */
static
ARM_USART_CAPABILITIES USART0_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART0_Resources);
}

/**
 *
 * @param cb_event
 * @return
 */
static
int32_t USART0_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART0_Resources);
}

/**
 *
 * @return
 */
static
int32_t USART0_Uninitialize(void)
{
  return USART_Uninitialize(&USART0_Resources);
}

/**
 *
 * @param state
 * @return
 */
static
int32_t USART0_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART0_Resources);
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t USART0_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART0_Resources);
}

/**
 *
 * @param data
 * @param num
 * @return
 */
static
int32_t USART0_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART0_Resources);
}

/**
 *
 * @param data_out
 * @param data_in
 * @param num
 * @return
 */
static
int32_t USART0_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART0_Resources);
}

/**
 *
 * @return
 */
static
uint32_t USART0_GetTxCount(void)
{
  return USART_GetTxCount(&USART0_Resources);
}

/**
 *
 * @return
 */
static
uint32_t USART0_GetRxCount(void)
{
  return USART_GetRxCount(&USART0_Resources);
}

/**
 *
 * @param control
 * @param arg
 * @return
 */
static
int32_t USART0_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART0_Resources);
}

/**
 *
 * @return
 */
static
ARM_USART_STATUS USART0_GetStatus(void)
{
  return USART_GetStatus(&USART0_Resources);
}

/**
 *
 * @param control
 * @return
 */
static
int32_t USART0_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART0_Resources);
}

/**
 *
 * @return
 */
static
ARM_USART_MODEM_STATUS USART0_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART0_Resources);
}

/**
 * @brief UART interrupt handler
 * @param
 * @return
 */
void UART0_Int_Handler(void)
{
  USART_IRQHandler(&USART0_Resources);
}

#endif // USE_USART0

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

#if defined(USE_USART0)
/* USART0 Driver Control Block */
ARM_DRIVER_USART Driver_USART0 = {
    USARTx_GetVersion,
    USART0_GetCapabilities,
    USART0_Initialize,
    USART0_Uninitialize,
    USART0_PowerControl,
    USART0_Send,
    USART0_Receive,
    USART0_Transfer,
    USART0_GetTxCount,
    USART0_GetRxCount,
    USART0_Control,
    USART0_GetStatus,
    USART0_SetModemControl,
    USART0_GetModemStatus
};
#endif // USE_USART0

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/* ----------------------------- End of file ---------------------------------*/
