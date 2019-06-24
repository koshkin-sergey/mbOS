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
 * Project: UART Driver Definitions for ADI ADuCM32x
 */

#ifndef UART_ADUCM320_H_
#define UART_ADUCM320_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "Driver_USART.h"

#include "RTE_Device.h"
#include "GPIO_ADuCM320.h"
#include "DMA_ADuCM320.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* USART0 configuration definitions */
#if defined (RTE_USART0) && (RTE_USART0 == 1)
  #define USE_USART0

  #define USART0_TX_GPIO_PORT        RTE_USART0_TX_PORT
  #define USART0_TX_GPIO_PIN         RTE_USART0_TX_PIN
  #define USART0_TX_GPIO_FUNC        RTE_USART0_TX_FUNC
  #define USART0_RX_GPIO_PORT        RTE_USART0_RX_PORT
  #define USART0_RX_GPIO_PIN         RTE_USART0_RX_PIN
  #define USART0_RX_GPIO_FUNC        RTE_USART0_RX_FUNC
#endif

// USART flags
#define USART_FLAG_INITIALIZED       (1U << 0)
#define USART_FLAG_POWERED           (1U << 1)
#define USART_FLAG_CONFIGURED        (1U << 2)
#define USART_FLAG_TX_ENABLED        (1U << 3)
#define USART_FLAG_RX_ENABLED        (1U << 4)
#define USART_FLAG_SEND_ACTIVE       (1U << 5)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

// USART Transfer Information (Run-Time)
typedef struct _USART_TRANSFER_INFO {
  uint32_t                rx_num;        // Total number of data to be received
  uint32_t                tx_num;        // Total number of data to be send
  uint8_t                *rx_buf;        // Pointer to in data buffer
  uint8_t                *tx_buf;        // Pointer to out data buffer
  uint32_t                rx_cnt;        // Number of data received
  uint32_t                tx_cnt;        // Number of data sent
  uint8_t                 send_active;   // Send active flag
} USART_TRANSFER_INFO;

typedef struct _USART_RX_STATUS {
  uint8_t rx_busy;                       // Receiver busy flag
  uint8_t rx_overflow;                   // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t rx_break;                      // Break detected on receive (cleared on start of next receive operation)
  uint8_t rx_framing_error;              // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t rx_parity_error;               // Parity error detected on receive (cleared on start of next receive operation)
} USART_RX_STATUS;

// USART Information (Run-Time)
typedef struct _USART_INFO {
  ARM_USART_SignalEvent_t cb_event;      // Event callback
  USART_RX_STATUS         rx_status;     // Receive status flags
  USART_TRANSFER_INFO     xfer;          // Transfer information
  uint8_t                 flags;         // USART driver flags
  uint32_t                baudrate;      // Baudrate
} USART_INFO_t;

// USART Pin Configuration
typedef const struct _USART_PINS {
  const GPIO_PIN_ID_t    *tx;            // TX Pin identifier
  const GPIO_PIN_ID_t    *rx;            // RX Pin identifier
} USART_PINS_t;

// USART DMA
typedef const struct _USART_DMA {
  uint8_t                 channel;       // DMA Channel
  uint8_t                 peripheral;    // DMA mux
  uint8_t                 peripheral_sel;// DMA mux selection
  DMA_SignalEvent_t       cb_event;      // DMA Event callback
} USART_DMA_t;

// USART Resources definitions
typedef struct {
  ARM_USART_CAPABILITIES   capabilities;  // Capabilities
  ADI_UART_TypeDef        *reg;           // Pointer to UART peripheral
  USART_PINS_t             pins;          // USART pins configuration
  IRQn_Type                irq_num;       // USART IRQ Number
  USART_DMA_t             *dma_tx;
  USART_DMA_t             *dma_rx;
  USART_INFO_t            *info;          // Run-Time Information
} const USART_RESOURCES_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

#endif /* UART_ADUCM320_H_ */

/* ----------------------------- End of file ---------------------------------*/
