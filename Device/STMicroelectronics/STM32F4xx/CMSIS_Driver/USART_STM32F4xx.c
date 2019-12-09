/*
 * Copyright (C) 2018-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: USART Driver for STMicroelectronics STM32F4xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "USART_STM32F4xx.h"

#if defined(USE_USART1) || defined(USE_USART2) || defined(USE_USART3) \
    defined(USE_UART4)  || defined(USE_UART5)  || defined(USE_USART6) \
    defined(USE_UART7)  || defined(USE_UART8)  || defined(USE_UART9)  \
    defined(USE_UART10)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ARM_USART_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

// Driver Version
static const ARM_DRIVER_VERSION usart_driver_version = {
  ARM_USART_API_VERSION,
  ARM_USART_DRV_VERSION
};

static const GPIO_PIN_CFG_t USART_pin_cfg_af = {
    GPIO_MODE_AF_PP, GPIO_PULL_UP, GPIO_SPEED_LOW
};

static const GPIO_PIN_CFG_t USART_pin_cfg_input = {
    GPIO_MODE_INPUT, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

static const GPIO_PIN_CFG_t USART_pin_cfg_output = {
    GPIO_MODE_OUT_PP, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

// USART1
#ifdef USE_USART1

// USART1 Run-Time Information
static USART_INFO          USART1_Info         = { 0U };
static USART_TRANSFER_INFO USART1_TransferInfo = { 0U };

#ifdef USE_USART1_TX_Pin
static const USART_PIN USART1_tx = {
    USART1_TX_GPIO_PORT,
    USART1_TX_GPIO_PIN,
    USART1_TX_GPIO_FUNC
};
#endif

#ifdef USE_USART1_RX_Pin
static const USART_PIN USART1_rx = {
    USART1_RX_GPIO_PORT,
    USART1_RX_GPIO_PIN,
    USART1_RX_GPIO_FUNC
};
#endif

#ifdef USE_USART1_CK_Pin
static const USART_PIN USART1_ck = {
    USART1_CK_GPIO_PORT,
    USART1_CK_GPIO_PIN,
    USART1_CK_GPIO_FUNC
};
#endif

#ifdef USE_USART1_RTS_Pin
static const USART_PIN USART1_rts = {
    USART1_RTS_GPIO_PORT,
    USART1_RTS_GPIO_PIN,
    USART1_RTS_GPIO_FUNC
};
#endif

#ifdef USE_USART1_CTS_Pin
static const USART_PIN USART1_cts = {
    USART1_CTS_GPIO_PORT,
    USART1_CTS_GPIO_PIN,
    USART1_CTS_GPIO_FUNC
};
#endif

// USART1 Resources
static const USART_RESOURCES USART1_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
#ifdef USE_USART1_CK_Pin
    1,  // supports Synchronous Master mode
#else
    0,  // supports Synchronous Master mode
#endif
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    1,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
#ifdef USE_USART1_RTS_Pin
    1,  // RTS Flow Control available
#else
    0,  // RTS Flow Control available
#endif
#ifdef USE_USART1_CTS_Pin
    1,  // CTS Flow Control available
#else
    0,  // CTS Flow Control available
#endif
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
#ifdef USE_USART1_RTS_Pin
    1,  // RTS Line: 0=not available, 1=available
#else
    0,  // RTS Line: 0=not available, 1=available
#endif
#ifdef USE_USART1_CTS_Pin
    1,  // CTS Line: 0=not available, 1=available
#else
    0,  // CTS Line: 0=not available, 1=available
#endif
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
#ifdef USE_USART1_CTS_Pin
    1,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#else
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#endif
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  USART1,

  // PINS
  {
#ifdef USE_USART1_TX_Pin
    &USART1_tx,
#else
    NULL,
#endif
#ifdef USE_USART1_RX_Pin
    &USART1_rx,
#else
    NULL,
#endif
#ifdef USE_USART1_CK_Pin
    &USART1_ck,
#else
    NULL,
#endif
#ifdef USE_USART1_RTS_Pin
    &USART1_rts,
#else
    NULL,
#endif
#ifdef USE_USART1_CTS_Pin
    &USART1_cts,
#else
    NULL,
#endif
  },

  USART1_IRQn,
  RCC_PERIPH_USART1,
  &USART1_Info,
  &USART1_TransferInfo,
};
#endif

// USART2
#ifdef USE_USART2

// USART2 Run-Time Information
static USART_INFO          USART2_Info         = { 0U };
static USART_TRANSFER_INFO USART2_TransferInfo = { 0U };

#ifdef USE_USART2_TX_Pin
static const USART_PIN USART2_tx = {
    USART2_TX_GPIO_PORT,
    USART2_TX_GPIO_PIN,
    USART2_TX_GPIO_FUNC
};
#endif

#ifdef USE_USART2_RX_Pin
static const USART_PIN USART2_rx = {
    USART2_RX_GPIO_PORT,
    USART2_RX_GPIO_PIN,
    USART2_RX_GPIO_FUNC
};
#endif

#ifdef USE_USART2_CK_Pin
static const USART_PIN USART2_ck = {
    USART2_CK_GPIO_PORT,
    USART2_CK_GPIO_PIN,
    USART2_CK_GPIO_FUNC
};
#endif

#ifdef USE_USART2_RTS_Pin
static const USART_PIN USART2_rts = {
    USART2_RTS_GPIO_PORT,
    USART2_RTS_GPIO_PIN,
    USART2_RTS_GPIO_FUNC
};
#endif

#ifdef USE_USART2_CTS_Pin
static const USART_PIN USART2_cts = {
    USART2_CTS_GPIO_PORT,
    USART2_CTS_GPIO_PIN,
    USART2_CTS_GPIO_FUNC
};
#endif

// USART2 Resources
static const USART_RESOURCES USART2_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
#ifdef USE_USART2_CK_Pin
    1,  // supports Synchronous Master mode
#else
    0,  // supports Synchronous Master mode
#endif
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    1,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
#ifdef USE_USART2_RTS_Pin
    1,  // RTS Flow Control available
#else
    0,  // RTS Flow Control available
#endif
#ifdef USE_USART2_CTS_Pin
    1,  // CTS Flow Control available
#else
    0,  // CTS Flow Control available
#endif
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
#ifdef USE_USART2_RTS_Pin
    1,  // RTS Line: 0=not available, 1=available
#else
    0,  // RTS Line: 0=not available, 1=available
#endif
#ifdef USE_USART2_CTS_Pin
    1,  // CTS Line: 0=not available, 1=available
#else
    0,  // CTS Line: 0=not available, 1=available
#endif
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
#ifdef USE_USART2_CTS_Pin
    1,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#else
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#endif
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  USART2,

  // PINS
  {
#ifdef USE_USART2_TX_Pin
    &USART2_tx,
#else
    NULL,
#endif
#ifdef USE_USART2_RX_Pin
    &USART2_rx,
#else
    NULL,
#endif
#ifdef USE_USART2_CK_Pin
    &USART2_ck,
#else
    NULL,
#endif
#ifdef USE_USART2_RTS_Pin
    &USART2_rts,
#else
    NULL,
#endif
#ifdef USE_USART2_CTS_Pin
    &USART2_cts,
#else
    NULL,
#endif
  },

  USART2_IRQn,
  RCC_PERIPH_USART2,
  &USART2_Info,
  &USART2_TransferInfo,
};
#endif

// USART3
#ifdef USE_USART3

// USART3 Run-Time Information
static USART_INFO          USART3_Info         = { 0U };
static USART_TRANSFER_INFO USART3_TransferInfo = { 0U };

#ifdef USE_USART3_TX_Pin
static const USART_PIN USART3_tx = {
    USART3_TX_GPIO_PORT,
    USART3_TX_GPIO_PIN,
    USART3_TX_GPIO_FUNC
};
#endif

#ifdef USE_USART3_RX_Pin
static const USART_PIN USART3_rx = {
    USART3_RX_GPIO_PORT,
    USART3_RX_GPIO_PIN,
    USART3_RX_GPIO_FUNC
};
#endif

#ifdef USE_USART3_CK_Pin
static const USART_PIN USART3_ck = {
    USART3_CK_GPIO_PORT,
    USART3_CK_GPIO_PIN,
    USART3_CK_GPIO_FUNC
};
#endif

#ifdef USE_USART3_RTS_Pin
static const USART_PIN USART3_rts = {
    USART3_RTS_GPIO_PORT,
    USART3_RTS_GPIO_PIN,
    USART3_RTS_GPIO_FUNC
};
#endif

#ifdef USE_USART3_CTS_Pin
static const USART_PIN USART3_cts = {
    USART3_CTS_GPIO_PORT,
    USART3_CTS_GPIO_PIN,
    USART3_CTS_GPIO_FUNC
};
#endif

// USART3 Resources
static const USART_RESOURCES USART3_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
#ifdef USE_USART3_CK_Pin
    1,  // supports Synchronous Master mode
#else
    0,  // supports Synchronous Master mode
#endif
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    1,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
#ifdef USE_USART3_RTS_Pin
    1,  // RTS Flow Control available
#else
    0,  // RTS Flow Control available
#endif
#ifdef USE_USART3_CTS_Pin
    1,  // CTS Flow Control available
#else
    0,  // CTS Flow Control available
#endif
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
#ifdef USE_USART3_RTS_Pin
    1,  // RTS Line: 0=not available, 1=available
#else
    0,  // RTS Line: 0=not available, 1=available
#endif
#ifdef USE_USART3_CTS_Pin
    1,  // CTS Line: 0=not available, 1=available
#else
    0,  // CTS Line: 0=not available, 1=available
#endif
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
#ifdef USE_USART3_CTS_Pin
    1,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#else
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#endif
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  USART3,

  // PINS
  {
#ifdef USE_USART3_TX_Pin
    &USART3_tx,
#else
    NULL,
#endif
#ifdef USE_USART3_RX_Pin
    &USART3_rx,
#else
    NULL,
#endif
#ifdef USE_USART3_CK_Pin
    &USART3_ck,
#else
    NULL,
#endif
#ifdef USE_USART3_RTS_Pin
    &USART3_rts,
#else
    NULL,
#endif
#ifdef USE_USART3_CTS_Pin
    &USART3_cts,
#else
    NULL,
#endif
  },

  USART3_IRQn,
  RCC_PERIPH_USART3,
  &USART3_Info,
  &USART3_TransferInfo,
};
#endif

// UART4
#ifdef USE_UART4

// UART4 Run-Time Information
static USART_INFO          UART4_Info         = { 0U };
static USART_TRANSFER_INFO UART4_TransferInfo = { 0U };

#ifdef USE_UART4_TX_Pin
static const USART_PIN UART4_tx = {
    UART4_TX_GPIO_PORT,
    UART4_TX_GPIO_PIN,
    UART4_TX_GPIO_FUNC
};
#endif

#ifdef USE_UART4_RX_Pin
static const USART_PIN UART4_rx = {
    UART4_RX_GPIO_PORT,
    UART4_RX_GPIO_PIN,
    UART4_RX_GPIO_FUNC
};
#endif

// UART4 Resources
static const USART_RESOURCES USART4_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
    0,  // supports Synchronous Master mode
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    0,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
    0,  // RTS Flow Control available
    0,  // CTS Flow Control available
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
    0,  // RTS Line: 0=not available, 1=available
    0,  // CTS Line: 0=not available, 1=available
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  UART4,

  // PINS
  {
#ifdef USE_UART4_TX_Pin
    &UART4_tx,
#else
    NULL,
#endif
#ifdef USE_UART4_RX_Pin
    &UART4_rx,
#else
    NULL,
#endif
    NULL,
    NULL,
    NULL,
  },

  UART4_IRQn,
  RCC_PERIPH_UART4,
  &UART4_Info,
  &UART4_TransferInfo
};
#endif

// UART5
#ifdef USE_UART5

// UART5 Run-Time Information
static USART_INFO          UART5_Info         = { 0U };
static USART_TRANSFER_INFO UART5_TransferInfo = { 0U };

#ifdef USE_UART5_TX_Pin
static const USART_PIN UART5_tx = {
    UART5_TX_GPIO_PORT,
    UART5_TX_GPIO_PIN,
    UART5_TX_GPIO_FUNC
};
#endif

#ifdef USE_UART5_RX_Pin
static const USART_PIN UART5_rx = {
    UART5_RX_GPIO_PORT,
    UART5_RX_GPIO_PIN,
    UART5_RX_GPIO_FUNC
};
#endif

// UART5 Resources
static const USART_RESOURCES USART5_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
    0,  // supports Synchronous Master mode
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    0,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
    0,  // RTS Flow Control available
    0,  // CTS Flow Control available
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
    0,  // RTS Line: 0=not available, 1=available
    0,  // CTS Line: 0=not available, 1=available
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  UART5,

  // PINS
  {
#ifdef USE_UART5_TX_Pin
    &UART5_tx,
#else
    NULL,
#endif
#ifdef USE_UART5_RX_Pin
    &UART5_rx,
#else
    NULL,
#endif
    NULL,
    NULL,
    NULL,
  },

  UART5_IRQn,
  RCC_PERIPH_UART5,
  &UART5_Info,
  &UART5_TransferInfo
};
#endif

// USART6
#ifdef USE_USART6

// USART6 Run-Time Information
static USART_INFO          USART6_Info         = { 0U };
static USART_TRANSFER_INFO USART6_TransferInfo = { 0U };

#ifdef USE_USART6_TX_Pin
static const USART_PIN USART6_tx = {
    USART6_TX_GPIO_PORT,
    USART6_TX_GPIO_PIN,
    USART6_TX_GPIO_FUNC
};
#endif

#ifdef USE_USART6_RX_Pin
static const USART_PIN USART6_rx = {
    USART6_RX_GPIO_PORT,
    USART6_RX_GPIO_PIN,
    USART6_RX_GPIO_FUNC
};
#endif

#ifdef USE_USART6_CK_Pin
static const USART_PIN USART6_ck = {
    USART6_CK_GPIO_PORT,
    USART6_CK_GPIO_PIN,
    USART6_CK_GPIO_FUNC
};
#endif

#ifdef USE_USART6_RTS_Pin
static const USART_PIN USART6_rts = {
    USART6_RTS_GPIO_PORT,
    USART6_RTS_GPIO_PIN,
    USART6_RTS_GPIO_FUNC
};
#endif

#ifdef USE_USART6_CTS_Pin
static const USART_PIN USART6_cts = {
    USART6_CTS_GPIO_PORT,
    USART6_CTS_GPIO_PIN,
    USART6_CTS_GPIO_FUNC
};
#endif

// USART6 Resources
static const USART_RESOURCES USART6_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
#ifdef USE_USART6_CK_Pin
    1,  // supports Synchronous Master mode
#else
    0,  // supports Synchronous Master mode
#endif
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    1,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
#ifdef USE_USART6_RTS_Pin
    1,  // RTS Flow Control available
#else
    0,  // RTS Flow Control available
#endif
#ifdef USE_USART6_CTS_Pin
    1,  // CTS Flow Control available
#else
    0,  // CTS Flow Control available
#endif
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
#ifdef USE_USART6_RTS_Pin
    1,  // RTS Line: 0=not available, 1=available
#else
    0,  // RTS Line: 0=not available, 1=available
#endif
#ifdef USE_USART6_CTS_Pin
    1,  // CTS Line: 0=not available, 1=available
#else
    0,  // CTS Line: 0=not available, 1=available
#endif
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
#ifdef USE_USART6_CTS_Pin
    1,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#else
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
#endif
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  USART6,

  // PINS
  {
#ifdef USE_USART6_TX_Pin
    &USART6_tx,
#else
    NULL,
#endif
#ifdef USE_USART6_RX_Pin
    &USART6_rx,
#else
    NULL,
#endif
#ifdef USE_USART6_CK_Pin
    &USART6_ck,
#else
    NULL,
#endif
#ifdef USE_USART6_RTS_Pin
    &USART6_rts,
#else
    NULL,
#endif
#ifdef USE_USART6_CTS_Pin
    &USART6_cts,
#else
    NULL,
#endif
  },

  USART6_IRQn,
  RCC_PERIPH_USART6,
  &USART6_Info,
  &USART6_TransferInfo
};
#endif

// UART7
#ifdef USE_UART7

// UART7 Run-Time Information
static USART_INFO          UART7_Info         = { 0U };
static USART_TRANSFER_INFO UART7_TransferInfo = { 0U };

#ifdef USE_UART7_TX_Pin
static const USART_PIN UART7_tx = {
    UART7_TX_GPIO_PORT,
    UART7_TX_GPIO_PIN,
    UART7_TX_GPIO_FUNC
};
#endif

#ifdef USE_UART7_RX_Pin
static const USART_PIN UART7_rx = {
    UART7_RX_GPIO_PORT,
    UART7_RX_GPIO_PIN,
    UART7_RX_GPIO_FUNC
};
#endif

// UART7 Resources
static const USART_RESOURCES USART7_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
    0,  // supports Synchronous Master mode
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    0,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
    0,  // RTS Flow Control available
    0,  // CTS Flow Control available
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
    0,  // RTS Line: 0=not available, 1=available
    0,  // CTS Line: 0=not available, 1=available
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  UART7,

  // PINS
  {
#ifdef USE_UART7_TX_Pin
    &UART7_tx,
#else
    NULL,
#endif
#ifdef USE_UART7_RX_Pin
    &UART7_rx,
#else
    NULL,
#endif
    NULL,
    NULL,
    NULL,
  },

  UART7_IRQn,
  RCC_PERIPH_UART7,
  &UART7_Info,
  &UART7_TransferInfo,
};
#endif

// UART8
#ifdef USE_UART8

// UART8 Run-Time Information
static USART_INFO          UART8_Info         = { 0U };
static USART_TRANSFER_INFO UART8_TransferInfo = { 0U };

#ifdef USE_UART8_TX_Pin
static const USART_PIN UART8_tx = {
    UART8_TX_GPIO_PORT,
    UART8_TX_GPIO_PIN,
    UART8_TX_GPIO_FUNC
};
#endif

#ifdef USE_UART8_RX_Pin
static const USART_PIN UART8_rx = {
    UART8_RX_GPIO_PORT,
    UART8_RX_GPIO_PIN,
    UART8_RX_GPIO_FUNC
};
#endif

// UART8 Resources
static const USART_RESOURCES USART8_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
    0,  // supports Synchronous Master mode
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    0,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
    0,  // RTS Flow Control available
    0,  // CTS Flow Control available
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
    0,  // RTS Line: 0=not available, 1=available
    0,  // CTS Line: 0=not available, 1=available
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  UART8,

  // PINS
  {
#ifdef USE_UART8_TX_Pin
    &UART8_tx,
#else
    NULL,
#endif
#ifdef USE_UART8_RX_Pin
    &UART8_rx,
#else
    NULL,
#endif
    NULL,
    NULL,
    NULL,
  },

  UART8_IRQn,
  RCC_PERIPH_UART8,
  &UART8_Info,
  &UART8_TransferInfo,
};
#endif

// UART9
#ifdef USE_UART9

// UART9 Run-Time Information
static USART_INFO          UART9_Info         = { 0U };
static USART_TRANSFER_INFO UART9_TransferInfo = { 0U };

#ifdef USE_UART9_TX_Pin
static const USART_PIN UART9_tx = {
    UART9_TX_GPIO_PORT,
    UART9_TX_GPIO_PIN,
    UART9_TX_GPIO_FUNC
};
#endif

#ifdef USE_UART9_RX_Pin
static const USART_PIN UART9_rx = {
    UART9_RX_GPIO_PORT,
    UART9_RX_GPIO_PIN,
    UART9_RX_GPIO_FUNC
};
#endif

// UART9 Resources
static const USART_RESOURCES USART9_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
    0,  // supports Synchronous Master mode
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    0,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
    0,  // RTS Flow Control available
    0,  // CTS Flow Control available
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
    0,  // RTS Line: 0=not available, 1=available
    0,  // CTS Line: 0=not available, 1=available
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  UART9,

  // PINS
  {
#ifdef USE_UART9_TX_Pin
    &UART9_tx,
#else
    NULL,
#endif
#ifdef USE_UART9_RX_Pin
    &UART9_rx,
#else
    NULL,
#endif
    NULL,
    NULL,
    NULL,
  },

  UART9_IRQn,
  RCC_PERIPH_UART9,
  &UART9_Info,
  &UART9_TransferInfo
};
#endif

// UART10
#ifdef USE_UART10

// UART10 Run-Time Information
static USART_INFO          UART10_Info         = { 0U };
static USART_TRANSFER_INFO UART10_TransferInfo = { 0U };

#ifdef USE_UART10_TX_Pin
static const USART_PIN UART10_tx = {
    UART10_TX_GPIO_PORT,
    UART10_TX_GPIO_PIN,
    UART10_TX_GPIO_FUNC
};
#endif

#ifdef USE_UART10_RX_Pin
static const USART_PIN UART10_rx = {
    UART10_RX_GPIO_PORT,
    UART10_RX_GPIO_PIN,
    UART10_RX_GPIO_FUNC
};
#endif

// UART10 Resources
static const USART_RESOURCES USART10_Resources = {
  {     // Capabilities
    1,  // supports UART (Asynchronous) mode
    0,  // supports Synchronous Master mode
    0,  // supports Synchronous Slave mode
    1,  // supports UART Single-wire mode
    1,  // supports UART IrDA mode
    0,  // supports UART Smart Card mode
    0,  // Smart Card Clock generator
    0,  // RTS Flow Control available
    0,  // CTS Flow Control available
    1,  // Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE
    1,  // Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT
    0,  // RTS Line: 0=not available, 1=available
    0,  // CTS Line: 0=not available, 1=available
    0,  // DTR Line: 0=not available, 1=available
    0,  // DSR Line: 0=not available, 1=available
    0,  // DCD Line: 0=not available, 1=available
    0,  // RI Line: 0=not available, 1=available
    0,  // Signal CTS change event: \ref ARM_USART_EVENT_CTS
    0,  // Signal DSR change event: \ref ARM_USART_EVENT_DSR
    0,  // Signal DCD change event: \ref ARM_USART_EVENT_DCD
    0,  // Signal RI change event: \ref ARM_USART_EVENT_RI
  },

  UART10,

  // PINS
  {
#ifdef USE_UART10_TX_Pin
    &UART10_tx,
#else
    NULL,
#endif
#ifdef USE_UART10_RX_Pin
    &UART10_rx,
#else
    NULL,
#endif
    NULL,
    NULL,
    NULL,
  },

  UART10_IRQn,
  RCC_PERIPH_UART10,
  &UART10_Info,
  &UART10_TransferInfo
};
#endif

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

static
int32_t USART_Receive(void *data, uint32_t num, USART_RESOURCES *usart);

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
  \fn          ARM_DRIVER_VERSION USARTx_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
static
ARM_DRIVER_VERSION USARTx_GetVersion(void)
{
  return usart_driver_version;
}

/**
  \fn          ARM_USART_CAPABILITIES USART_GetCapabilities(USART_RESOURCES *usart)
  \brief       Get driver capabilities
  \param[in]   usart     Pointer to USART resources
  \return      \ref ARM_USART_CAPABILITIES
*/
static
ARM_USART_CAPABILITIES USART_GetCapabilities(USART_RESOURCES *usart)
{
  return usart->capabilities;
}

/**
  \fn          int32_t USART_Initialize(ARM_USART_SignalEvent_t cb_event, USART_RESOURCES *usart)
  \brief       Initialize USART Interface.
  \param[in]   cb_event  Pointer to \ref ARM_USART_SignalEvent
  \param[in]   usart     Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_Initialize(ARM_USART_SignalEvent_t cb_event, USART_RESOURCES *usart)
{
  if (usart->info->flags & USART_FLAG_INITIALIZED) {
    // Driver is already initialized
    return ARM_DRIVER_OK;
  }

  USART_INFO *info = usart->info;
  USART_IO *io = &usart->io;

  // Initialize USART Run-time Resources
  info->cb_event = cb_event;

  info->status.tx_busy          = 0U;
  info->status.rx_busy          = 0U;
  info->status.tx_underflow     = 0U;
  info->status.rx_overflow      = 0U;
  info->status.rx_break         = 0U;
  info->status.rx_framing_error = 0U;
  info->status.rx_parity_error  = 0U;

  info->mode                    = 0U;
  usart->xfer->send_active      = 0U;

  // Clear transfer information
  memset(usart->xfer, 0, sizeof(USART_TRANSFER_INFO));

  // Enable TX pin port clock
  if (io->tx)
    GPIO_PortClock(io->tx->port, GPIO_PORT_CLK_ENABLE);

  // Enable RX pin port clock
  if (io->rx)
    GPIO_PortClock(io->rx->port, GPIO_PORT_CLK_ENABLE);

  // Enable CLK pin port clock
  if (io->ck)
    GPIO_PortClock(io->ck->port, GPIO_PORT_CLK_ENABLE);

  // Configure RTS pin
  if (io->rts)
    GPIO_PortClock(io->rts->port, GPIO_PORT_CLK_ENABLE);

  // Configure CTS pin
  if (io->cts)
    GPIO_PortClock(io->cts->port, GPIO_PORT_CLK_ENABLE);

  usart->info->flags = USART_FLAG_INITIALIZED;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t USART_Uninitialize(USART_RESOURCES *usart)
  \brief       De-initialize USART Interface.
  \param[in]   usart     Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_Uninitialize(USART_RESOURCES *usart)
{
  USART_IO *io = &usart->io;

  /* Unconfigure TX Pin */
  if (io->tx)
    GPIO_PinConfig(io->tx->port, io->tx->pin, &USART_pin_cfg_input);
  /* Unconfigure RX Pin */
  if (io->rx)
    GPIO_PinConfig(io->rx->port, io->rx->pin, &USART_pin_cfg_input);
  /* Unconfigure CK Pin */
  if (io->ck)
    GPIO_PinConfig(io->ck->port, io->ck->pin, &USART_pin_cfg_input);
  /* Unconfigure RTS Pin */
  if (io->rts)
    GPIO_PinConfig(io->rts->port, io->rts->pin, &USART_pin_cfg_input);
  /* Unconfigure CTS Pin */
  if (io->cts)
    GPIO_PinConfig(io->cts->port, io->cts->pin, &USART_pin_cfg_input);

  // Reset USART status flags
  usart->info->flags = 0U;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t USART_PowerControl(ARM_POWER_STATE state, USART_RESOURCES *usart)
  \brief       Control USART Interface Power.
  \param[in]   state  Power state
  \param[in]   usart  Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_PowerControl(ARM_POWER_STATE state, USART_RESOURCES *usart)
{
  USART_INFO *info = usart->info;
  USART_TRANSFER_INFO *xfer = usart->xfer;

  switch (state) {
    case ARM_POWER_OFF:
      // USART peripheral reset
      RCC_ResetPeriph(usart->rcc);

      /* Disable IRQ */
      NVIC_DisableIRQ(usart->irq_num);

      // Disable USART clock
      RCC_DisablePeriph(usart->rcc);

      // Clear Status flags
      info->status.tx_busy          = 0U;
      info->status.rx_busy          = 0U;
      info->status.tx_underflow     = 0U;
      info->status.rx_overflow      = 0U;
      info->status.rx_break         = 0U;
      info->status.rx_framing_error = 0U;
      info->status.rx_parity_error  = 0U;
      xfer->send_active             = 0U;

      info->flags &= ~USART_FLAG_POWERED;
      break;

    case ARM_POWER_LOW:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    case ARM_POWER_FULL:
      if ((info->flags & USART_FLAG_INITIALIZED) == 0U) {
        return ARM_DRIVER_ERROR;
      }

      if ((info->flags & USART_FLAG_POWERED) != 0U) {
        return ARM_DRIVER_OK;
      }

      // Clear Status flags
      info->status.tx_busy          = 0U;
      info->status.rx_busy          = 0U;
      info->status.tx_underflow     = 0U;
      info->status.rx_overflow      = 0U;
      info->status.rx_break         = 0U;
      info->status.rx_framing_error = 0U;
      info->status.rx_parity_error  = 0U;

      xfer->send_active             = 0U;
      xfer->def_val                 = 0U;
      xfer->sync_mode               = 0U;
      xfer->break_flag              = 0U;
      info->mode                    = 0U;
      info->flow_control            = 0U;

      info->flags = USART_FLAG_POWERED | USART_FLAG_INITIALIZED;

      // Enable USART clock
      RCC_EnablePeriph(usart->rcc);

      // Clear and Enable USART IRQ
      NVIC_ClearPendingIRQ(usart->irq_num);
      NVIC_SetPriority(usart->irq_num, RTE_USART_INT_PRIORITY);
      NVIC_EnableIRQ(usart->irq_num);

      // USART peripheral reset
      RCC_ResetPeriph(usart->rcc);

    break;
    default: return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t USART_Send(const void *data, uint32_t num, USART_RESOURCES *usart)
  \brief       Start sending data to USART transmitter.
  \param[in]   data  Pointer to buffer with data to send to USART transmitter
  \param[in]   num   Number of data items to send
  \param[in]   usart Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_Send(const void *data, uint32_t num, USART_RESOURCES *usart)
{
  USART_INFO *info = usart->info;
  USART_TRANSFER_INFO *xfer = usart->xfer;

  if ((data == NULL) || (num == 0U)) {
    // Invalid parameters
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((info->flags & USART_FLAG_CONFIGURED) == 0U) {
    // USART is not configured (mode not selected)
    return ARM_DRIVER_ERROR;
  }

  if (xfer->send_active != 0U) {
    // Send is not completed yet
    return ARM_DRIVER_ERROR_BUSY;
  }

  // Set Send active flag
  xfer->send_active = 1U;

  // Save transmit buffer info
  xfer->tx_buf = (uint8_t *)data;
  xfer->tx_num = num;
  xfer->tx_cnt = 0U;

  // Synchronous mode
  if (info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER) {
    if (xfer->sync_mode == 0U) {
      xfer->sync_mode = USART_SYNC_MODE_TX;
      // Start dummy reads
      if (USART_Receive(&xfer->dump_val, num, usart) == ARM_DRIVER_ERROR_BUSY)
        return ARM_DRIVER_ERROR_BUSY;
    }
  }

  // TXE interrupt enable
  usart->reg->CR1 |= USART_CR1_TXEIE;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t USART_Receive(void *data, uint32_t num, USART_RESOURCES *usart)
  \brief       Start receiving data from USART receiver.
  \param[out]  data  Pointer to buffer for data to receive from USART receiver
  \param[in]   num   Number of data items to receive
  \param[in]   usart Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_Receive(void *data, uint32_t num, USART_RESOURCES *usart)
{
  USART_INFO *info = usart->info;
  USART_TRANSFER_INFO *xfer = usart->xfer;

  if ((data == NULL) || (num == 0U)) {
    // Invalid parameters
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((info->flags & USART_FLAG_CONFIGURED) == 0U) {
    // USART is not configured (mode not selected)
    return ARM_DRIVER_ERROR;
  }

  // Check if receiver is busy
  if (info->status.rx_busy == 1U) {
    return ARM_DRIVER_ERROR_BUSY;
  }

  // Disable RXNE Interrupt
  usart->reg->CR1 &= ~USART_CR1_RXNEIE;

  // Save number of data to be received
  xfer->rx_num = num;

  // Clear RX statuses
  info->status.rx_break          = 0U;
  info->status.rx_framing_error  = 0U;
  info->status.rx_overflow       = 0U;
  info->status.rx_parity_error   = 0U;

  // Save receive buffer info
  xfer->rx_buf = (uint8_t *)data;
  xfer->rx_cnt =  0U;

  // Set RX busy flag
  info->status.rx_busy = 1U;

  // Enable RXNE and IDLE interrupt
  usart->reg->CR1 |= (USART_CR1_IDLEIE | USART_CR1_RXNEIE);

  // Synchronous mode
  if (info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER) {
    if (xfer->sync_mode == 0U) {
      xfer->sync_mode = USART_SYNC_MODE_RX;
      // Send dummy data
      if (USART_Send(&xfer->def_val, num, usart) == ARM_DRIVER_ERROR_BUSY)
        return ARM_DRIVER_ERROR_BUSY;
    }
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t USART_Transfer(const void *data_out, void *data_in, uint32_t num, USART_RESOURCES *usart)
  \brief       Start sending/receiving data to/from USART transmitter/receiver.
  \param[in]   data_out  Pointer to buffer with data to send to USART transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from USART receiver
  \param[in]   num       Number of data items to transfer
  \param[in]   usart     Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_Transfer(const void *data_out, void *data_in, uint32_t num, USART_RESOURCES *usart)
{
  int32_t status;

  if ((data_out == NULL) || (data_in == NULL) || (num == 0U)) {
    // Invalid parameters
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if ((usart->info->flags & USART_FLAG_CONFIGURED) == 0U) {
    // USART is not configured
    return ARM_DRIVER_ERROR;
  }

  if (usart->info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER) {
    // Set xfer mode
    usart->xfer->sync_mode = USART_SYNC_MODE_TX_RX;
    // Receive
    status = USART_Receive(data_in, num, usart);
    if (status != ARM_DRIVER_OK)
      return status;
    // Send
    status = USART_Send(data_out, num, usart);
    if (status != ARM_DRIVER_OK)
      return status;
  }
  else {
    // Only in synchronous mode
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          uint32_t USART_GetTxCount(USART_RESOURCES *usart)
  \brief       Get transmitted data count.
  \param[in]   usart     Pointer to USART resources
  \return      number of data items transmitted
*/
static
uint32_t USART_GetTxCount(USART_RESOURCES *usart)
{
  return usart->xfer->tx_cnt;
}

/**
  \fn          uint32_t USART_GetRxCount(USART_RESOURCES *usart)
  \brief       Get received data count.
  \param[in]   usart     Pointer to USART resources
  \return      number of data items received
*/
static
uint32_t USART_GetRxCount(USART_RESOURCES *usart)
{
  return usart->xfer->rx_cnt;
}

/**
  \fn          int32_t USART_Control(uint32_t control, uint32_t arg, USART_RESOURCES *usart)
  \brief       Control USART Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \param[in]   usart    Pointer to USART resources
  \return      common \ref execution_status and driver specific \ref usart_execution_status
*/
static
int32_t USART_Control(uint32_t control, uint32_t arg, USART_RESOURCES *usart)
{
  USART_INFO *info = usart->info;
  USART_TRANSFER_INFO *xfer = usart->xfer;
  uint32_t val, mode, flow_control, br, i;
  uint32_t cr1, cr2, cr3;

  if ((info->flags & USART_FLAG_POWERED) == 0U) {
    // USART not powered
    return ARM_DRIVER_ERROR;
  }

  cr1  = 0U;
  cr2  = 0U;
  cr3  = 0U;

  switch (control & ARM_USART_CONTROL_Msk) {
    // Control break
    case ARM_USART_CONTROL_BREAK:
      if (arg) {
        if (xfer->send_active != 0U)
          return ARM_DRIVER_ERROR_BUSY;

        // Set Send active and Break flag
        xfer->send_active = 1U;
        xfer->break_flag  = 1U;
        // Enable TX interrupt and send break
        usart->reg->CR1 |=  USART_CR1_TXEIE | USART_CR1_SBK;
      }
      else {
        if (xfer->break_flag) {
          // Disable TX interrupt
          usart->reg->CR1 &= ~USART_CR1_TXEIE;
          // Clear break and Send Active flag
          xfer->break_flag  = 0U;
          xfer->send_active = 0U;
        }
      }
      return ARM_DRIVER_OK;

    // Abort Send
    case ARM_USART_ABORT_SEND:
      // Disable TX and TC interrupt
      usart->reg->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_TCIE);
      // Clear break flag
      xfer->break_flag = 0U;
      // Clear Send active flag
      xfer->send_active = 0U;
      return ARM_DRIVER_OK;

    // Abort receive
    case ARM_USART_ABORT_RECEIVE:
      // Disable RX interrupt
      usart->reg->CR1 &= ~USART_CR1_RXNEIE;
      // Clear RX busy status
      info->status.rx_busy = 0U;
      return ARM_DRIVER_OK;

    // Abort transfer
    case ARM_USART_ABORT_TRANSFER:
      // Disable TX, TC and RX interrupt
      usart->reg->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_RXNEIE);
      // Clear busy statuses
      info->status.rx_busy = 0U;
      xfer->send_active    = 0U;
      return ARM_DRIVER_OK;

    // Control TX
    case ARM_USART_CONTROL_TX:
      // Check if TX pin available
      if (usart->io.tx == NULL)
        return ARM_DRIVER_ERROR;

      if (arg) {
        if (info->mode != ARM_USART_MODE_SMART_CARD) {
          // USART TX pin function selected
          GPIO_AFConfig(usart->io.tx->port, usart->io.tx->pin, usart->io.tx->func);
          GPIO_PinConfig(usart->io.tx->port, usart->io.tx->pin, &USART_pin_cfg_af);
        }
        info->flags |= USART_FLAG_TX_ENABLED;
        // Transmitter enable
        usart->reg->CR1 |= USART_CR1_TE;
      }
      else {
        // Transmitter disable
        usart->reg->CR1 &= ~USART_CR1_TE;

        info->flags &= ~USART_FLAG_TX_ENABLED;

        if (info->mode != ARM_USART_MODE_SMART_CARD) {
          // GPIO pin function selected
          GPIO_PinConfig(usart->io.tx->port, usart->io.tx->pin, &USART_pin_cfg_input);
        }
      }
      return ARM_DRIVER_OK;

    // Control RX
    case ARM_USART_CONTROL_RX:
      // Check if RX line available
      if (usart->io.rx == NULL)
        return ARM_DRIVER_ERROR;

      if (arg) {
        if ((info->mode != ARM_USART_MODE_SMART_CARD) &&
            (info->mode != ARM_USART_MODE_SINGLE_WIRE )) {
          // USART RX pin function selected
          GPIO_AFConfig(usart->io.rx->port, usart->io.rx->pin, usart->io.rx->func);
          GPIO_PinConfig(usart->io.rx->port, usart->io.rx->pin, &USART_pin_cfg_af);
        }
        info->flags |= USART_FLAG_RX_ENABLED;

        // Enable Error interrupt,
        usart->reg->CR3 |= USART_CR3_EIE;

        // Break detection interrupt enable
        usart->reg->CR2 |= USART_CR2_LBDIE;

        // Enable Idle line interrupt
        usart->reg->CR1 |= USART_CR1_IDLEIE;

        usart->reg->CR1 |= USART_CR1_RXNEIE;

        // Receiver enable
        usart->reg->CR1 |= USART_CR1_RE;
      }
      else {
        // Receiver disable
        usart->reg->CR1 &= ~USART_CR1_RE;

        info->flags &= ~USART_FLAG_RX_ENABLED;

        if ((info->mode != ARM_USART_MODE_SMART_CARD) &&
            (info->mode != ARM_USART_MODE_SINGLE_WIRE )) {
          // GPIO pin function selected
          GPIO_PinConfig(usart->io.rx->port, usart->io.rx->pin, &USART_pin_cfg_input);
        }
      }
      return ARM_DRIVER_OK;

    default:
      break;
  }

  // Check if busy
  if ((info->status.rx_busy != 0U) || (xfer->send_active != 0U))
    return ARM_DRIVER_ERROR_BUSY;

  if (((usart->reg->CR1 & USART_CR1_TE) != 0U) && ((usart->reg->SR & USART_SR_TC) == 0U))
    return ARM_DRIVER_ERROR_BUSY;

  switch (control & ARM_USART_CONTROL_Msk) {
    case ARM_USART_MODE_ASYNCHRONOUS:
      mode = ARM_USART_MODE_ASYNCHRONOUS;
      break;

    case ARM_USART_MODE_SYNCHRONOUS_MASTER:
      if (usart->capabilities.synchronous_master) {
        // Enable Clock pin
        cr2 |= USART_CR2_CLKEN;
        // Enable last bit clock pulse
        cr2 |= USART_CR2_LBCL;
      }
      else {
        return ARM_USART_ERROR_MODE;
      }

      mode = ARM_USART_MODE_SYNCHRONOUS_MASTER;
      break;

    case ARM_USART_MODE_SYNCHRONOUS_SLAVE:
      return ARM_USART_ERROR_MODE;

    case ARM_USART_MODE_SINGLE_WIRE:
      // Enable Half duplex
      cr3 |= USART_CR3_HDSEL;
      mode = ARM_USART_MODE_SINGLE_WIRE;
      break;

    case ARM_USART_MODE_IRDA:
      // Enable IrDA mode
      cr3 |= USART_CR3_IREN;
      mode = ARM_USART_MODE_IRDA;
      break;

    case ARM_USART_MODE_SMART_CARD:
      if (usart->capabilities.smart_card) {
        // Enable Smart card mode
        cr3 |= USART_CR3_SCEN;
      }
      else
        return ARM_USART_ERROR_MODE;

      mode = ARM_USART_MODE_SMART_CARD;
      break;

    // Default TX value
    case ARM_USART_SET_DEFAULT_TX_VALUE:
      xfer->def_val = (uint16_t)arg;
      return ARM_DRIVER_OK;

    // IrDA pulse
    case ARM_USART_SET_IRDA_PULSE:
      if (info->mode != ARM_USART_MODE_IRDA) {
        if (arg != 0U) {
          // IrDa low-power
          usart->reg->CR3 |= USART_CR3_IRLP;

          // Get clock
          val = RCC_GetPeriphFreq(usart->rcc);

          // Calculate period in ns
          val = 1000000000U / val;

          for (i = 1U; i < 256U; i++) {
            if ((val * i) > arg)
              break;
          }

          if (i == 256U)
            return ARM_DRIVER_ERROR;

          usart->reg->GTPR = (usart->reg->GTPR & ~USART_GTPR_PSC) | i;
        }
      }
      else
        return ARM_DRIVER_ERROR;

      return ARM_DRIVER_OK;

    // SmartCard guard time
    case ARM_USART_SET_SMART_CARD_GUARD_TIME:
      if (info->mode == ARM_USART_MODE_SMART_CARD) {
        if (arg > 255U)
          return ARM_DRIVER_ERROR;

        usart->reg->GTPR = (usart->reg->GTPR & ~USART_GTPR_GT) | arg;
      }
      else
        return ARM_DRIVER_ERROR;

      return ARM_DRIVER_OK;

    // SmartCard clock
    case ARM_USART_SET_SMART_CARD_CLOCK:
      if (info->mode == ARM_USART_MODE_SMART_CARD) {
        // Get clock
        val = RCC_GetPeriphFreq(usart->rcc);

        // Calculate period in ns
        val = 1000000000U / val;

        for (i = 1U; i <64U; i++) {
          // if in +-2% tolerance
          if (((val * i * 2U * 100U) < (arg * 102U)) &&
              ((val * i * 2U * 100U) > (arg * 98U))    ) {
            break;
          }
        }

        if (i == 64U)
          return ARM_DRIVER_ERROR;

        usart->reg->GTPR = (usart->reg->GTPR & ~USART_GTPR_PSC) | i;
      }
      else {
        return ARM_DRIVER_ERROR;
      }
      return ARM_DRIVER_OK;

    // SmartCard NACK
    case ARM_USART_CONTROL_SMART_CARD_NACK:
      if (info->mode == ARM_USART_MODE_SMART_CARD) {
        // SmartCard NACK Enable
        if (arg != 0U) { usart->reg->CR3 |= USART_CR3_NACK; }
      }
      else {
        return ARM_DRIVER_ERROR;
      }
      return ARM_DRIVER_OK;

    // Unsupported command
    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  // USART Data bits
  switch (control & ARM_USART_DATA_BITS_Msk) {
    case ARM_USART_DATA_BITS_7:
      if ((control & ARM_USART_PARITY_Msk) == ARM_USART_PARITY_NONE)
        return ARM_USART_ERROR_DATA_BITS;

      // 7 data bits, 8. data bit is parity bit
      break;

    case ARM_USART_DATA_BITS_8:
      if ((control & ARM_USART_PARITY_Msk) == ARM_USART_PARITY_NONE) {
        // 8-data bits, no parity
      }
      else {
        // 11-bit break detection
        cr2 |= USART_CR2_LBDL;
        // 8-data bits, 9. bit is parity bit
        cr1 |= USART_CR1_M;
      }
      break;

    case ARM_USART_DATA_BITS_9:
      if ((control & ARM_USART_PARITY_Msk) != ARM_USART_PARITY_NONE)
        return ARM_USART_ERROR_DATA_BITS;

      // 11-bit break detection
      cr2 |= USART_CR2_LBDL;
      // 9-data bits, no parity
      cr1 |= USART_CR1_M;
      break;

    default:
      return ARM_USART_ERROR_DATA_BITS;
  }

  // USART Parity
  switch (control & ARM_USART_PARITY_Msk) {
    case ARM_USART_PARITY_NONE:
      break;
    case ARM_USART_PARITY_EVEN:
      cr1 |=  USART_CR1_PCE;
      break;
    case ARM_USART_PARITY_ODD:
      cr1 |= (USART_CR1_PCE | USART_CR1_PS);
      break;
    default:
      return ARM_USART_ERROR_PARITY;
  }

  // USART Stop bits
  switch (control & ARM_USART_STOP_BITS_Msk) {
    case ARM_USART_STOP_BITS_1:
      break;
    case ARM_USART_STOP_BITS_2:
      cr2 |= USART_CR2_STOP_1;
      break;
    case ARM_USART_STOP_BITS_1_5:
      cr2 |= USART_CR2_STOP_0 | USART_CR2_STOP_1;
      break;
    case ARM_USART_STOP_BITS_0_5:
      cr2 |= USART_CR2_STOP_0;
      break;
    default:
      return ARM_USART_ERROR_STOP_BITS;
  }

  // USART Flow control
  switch (control & ARM_USART_FLOW_CONTROL_Msk) {
    case ARM_USART_FLOW_CONTROL_NONE:
      flow_control = ARM_USART_FLOW_CONTROL_NONE;
      break;
    case ARM_USART_FLOW_CONTROL_RTS:
      if (usart->capabilities.flow_control_rts) {
        flow_control = ARM_USART_FLOW_CONTROL_RTS;
        // RTS Enable
        cr3 |= USART_CR3_RTSE;
      }
      else {
        return ARM_USART_ERROR_FLOW_CONTROL;
      }
      break;
    case ARM_USART_FLOW_CONTROL_CTS:
      if (usart->capabilities.flow_control_cts) {
        flow_control = ARM_USART_FLOW_CONTROL_CTS;
        // CTS Enable, CTS interrupt enable
        cr3 |= USART_CR3_CTSE | USART_CR3_CTSIE;
      }
      else {
        return ARM_USART_ERROR_FLOW_CONTROL;
      }
      break;
    case ARM_USART_FLOW_CONTROL_RTS_CTS:
      if ((usart->capabilities.flow_control_rts != 0U) &&
          (usart->capabilities.flow_control_cts != 0U)) {
        flow_control = ARM_USART_FLOW_CONTROL_RTS_CTS;
        // RTS and CTS Enable, CTS interrupt enable
        cr3 |= (USART_CR3_RTSE | USART_CR3_CTSE | USART_CR3_CTSIE);
      }
      else {
        return ARM_USART_ERROR_FLOW_CONTROL;
      }
      break;
    default:
      return ARM_USART_ERROR_FLOW_CONTROL;
  }

  // Clock setting for synchronous mode
  if (mode == ARM_USART_MODE_SYNCHRONOUS_MASTER) {
    // Polarity
    switch (control & ARM_USART_CPOL_Msk) {
      case ARM_USART_CPOL0:
        break;
      case ARM_USART_CPOL1:
        cr2 |= USART_CR2_CPOL;
        break;
      default:
        return ARM_USART_ERROR_CPOL;
    }

    // Phase
    switch (control & ARM_USART_CPHA_Msk) {
      case ARM_USART_CPHA0:
        break;
      case ARM_USART_CPHA1:
        cr2 |= USART_CR2_CPHA;
        break;
      default:
        return ARM_USART_ERROR_CPHA;
    }
  }

  // USART Baudrate
  uint32_t freq = RCC_GetPeriphFreq(usart->rcc);
  val = (uint32_t)(USART_BAUDRATE_DIVIDER(freq, arg));
  br = ((freq << 4U) / (val & 0xFFFFU)) >> 4U;
  // If inside +/- 2% tolerance, baud rate configured correctly
  if (!(((br * 100U) < (arg * 102U)) && ((br * 100U) > (arg * 98U)))) {
    return ARM_USART_ERROR_BAUDRATE;
  }

  // USART Disable
  usart->reg->CR1 &= ~USART_CR1_UE;

  // Configure Baud rate register
  usart->reg->BRR = val;

  // Configuration is OK - Mode is valid
  info->mode = mode;

  // Save flow control mode
  info->flow_control = flow_control;

  // Configure TX pin regarding mode and transmitter state
  switch (info->mode) {
    case ARM_USART_MODE_SMART_CARD:
      // USART TX pin function selected
      GPIO_AFConfig(usart->io.tx->port, usart->io.tx->pin, usart->io.tx->func);
      GPIO_PinConfig(usart->io.tx->port, usart->io.tx->pin, &USART_pin_cfg_af);
      break;
    default:
      // Synchronous master/slave, asynchronous, single-wire and IrDA mode
      if (info->flags & USART_FLAG_TX_ENABLED) {
        // USART TX pin function selected
        GPIO_AFConfig(usart->io.tx->port, usart->io.tx->pin, usart->io.tx->func);
        GPIO_PinConfig(usart->io.tx->port, usart->io.tx->pin, &USART_pin_cfg_af);
      }
      else {
        // GPIO pin function selected
        GPIO_PinConfig(usart->io.tx->port, usart->io.tx->pin, &USART_pin_cfg_input);
      }
  }

  // Configure RX pin regarding mode and receiver state
  switch (info->mode) {
    case ARM_USART_MODE_SINGLE_WIRE:
    case ARM_USART_MODE_SMART_CARD:
      // GPIO pin function selected
      GPIO_PinConfig(usart->io.rx->port, usart->io.rx->pin, &USART_pin_cfg_input);
      break;
    default:
      // Synchronous master/slave, asynchronous and  IrDA mode
      if (info->flags & USART_FLAG_RX_ENABLED) {
        // USART RX pin function selected
        GPIO_AFConfig(usart->io.rx->port, usart->io.rx->pin, usart->io.rx->func);
        GPIO_PinConfig(usart->io.rx->port, usart->io.rx->pin, &USART_pin_cfg_af);
      } else {
       // GPIO pin function selected
        GPIO_PinConfig(usart->io.rx->port, usart->io.rx->pin, &USART_pin_cfg_input);
      }
      break;
  }

  // Configure CLK pin regarding mode
  if (usart->io.ck) {
    switch (info->mode) {
      case ARM_USART_MODE_SMART_CARD:
      case ARM_USART_MODE_SYNCHRONOUS_MASTER:
        // USART CK pin function selected
        GPIO_AFConfig(usart->io.ck->port, usart->io.ck->pin, usart->io.ck->func);
        GPIO_PinConfig(usart->io.ck->port, usart->io.ck->pin, &USART_pin_cfg_af);
        break;
      default:
        // Asynchronous, Single-wire and IrDA mode
        // GPIO pin function selected
        GPIO_PinConfig(usart->io.ck->port, usart->io.ck->pin, &USART_pin_cfg_input);
    }
  }

  // Configure RTS pin regarding Flow control configuration
  if (usart->io.rts) {
    if ((flow_control == ARM_USART_FLOW_CONTROL_RTS) ||
        (flow_control == ARM_USART_FLOW_CONTROL_RTS_CTS)) {
      // USART RTS Alternate function
      GPIO_AFConfig(usart->io.rts->port, usart->io.rts->pin, usart->io.rts->func);
      GPIO_PinConfig(usart->io.rts->port, usart->io.rts->pin, &USART_pin_cfg_af);
    }
    else {
      // GPIO output
      GPIO_PinConfig(usart->io.rts->port, usart->io.rts->pin, &USART_pin_cfg_output);
    }
  }

  // Configure CTS pin regarding Flow control configuration
  if (usart->io.cts) {
    if ((flow_control == ARM_USART_FLOW_CONTROL_CTS) ||
        (flow_control == ARM_USART_FLOW_CONTROL_RTS_CTS)) {
      // USART CTS Alternate function
      GPIO_AFConfig(usart->io.cts->port, usart->io.cts->pin, usart->io.cts->func);
      GPIO_PinConfig(usart->io.cts->port, usart->io.cts->pin, &USART_pin_cfg_af);
    }
    else {
      // GPIO input
      GPIO_PinConfig(usart->io.cts->port, usart->io.cts->pin, &USART_pin_cfg_input);
    }
  }

  // Configure USART control registers
  usart->reg->CR1 = cr1;
  usart->reg->CR2 = cr2;
  usart->reg->CR3 = cr3;

  // USART Enable
  usart->reg->CR1 |= USART_CR1_UE;

  // Set configured flag
  info->flags |= USART_FLAG_CONFIGURED;

  return ARM_DRIVER_OK;
}

/**
  \fn          ARM_USART_STATUS USART_GetStatus(USART_RESOURCES *usart)
  \brief       Get USART status.
  \param[in]   usart     Pointer to USART resources
  \return      USART status \ref ARM_USART_STATUS
*/
static
ARM_USART_STATUS USART_GetStatus(USART_RESOURCES *usart)
{
  ARM_USART_STATUS status;

  if (usart->xfer->send_active != 0U)
    status.tx_busy        = 1U;
  else
    status.tx_busy        = ((usart->reg->SR & USART_SR_TC) ? (0U) : (1U));

  status.rx_busy          = usart->info->status.rx_busy;
  status.tx_underflow     = usart->info->status.tx_underflow;
  status.rx_overflow      = usart->info->status.rx_overflow;
  status.rx_break         = usart->info->status.rx_break;
  status.rx_framing_error = usart->info->status.rx_framing_error;
  status.rx_parity_error  = usart->info->status.rx_parity_error;

  return status;
}

/**
  \fn          int32_t USART_SetModemControl(ARM_USART_MODEM_CONTROL control, USART_RESOURCES *usart)
  \brief       Set USART Modem Control line state.
  \param[in]   control   \ref ARM_USART_MODEM_CONTROL
  \param[in]   usart     Pointer to USART resources
  \return      \ref execution_status
*/
static
int32_t USART_SetModemControl(ARM_USART_MODEM_CONTROL control, USART_RESOURCES *usart)
{
  switch (control) {
    case ARM_USART_RTS_CLEAR:
      if ((usart->info->flow_control == ARM_USART_FLOW_CONTROL_NONE) ||
          (usart->info->flow_control == ARM_USART_FLOW_CONTROL_CTS)) {
        GPIO_PinWrite(usart->io.rts->port, usart->io.rts->pin, GPIO_PIN_OUT_HIGH);
      }
      else {
        // Hardware RTS
        return ARM_DRIVER_ERROR;
      }
      break;

    case ARM_USART_RTS_SET:
      if ((usart->info->flow_control == ARM_USART_FLOW_CONTROL_NONE) ||
          (usart->info->flow_control == ARM_USART_FLOW_CONTROL_CTS)) {
        GPIO_PinWrite(usart->io.rts->port, usart->io.rts->pin, GPIO_PIN_OUT_LOW);
      }
      else {
        // Hardware RTS
        return ARM_DRIVER_ERROR;
      }
      break;

    default:
      return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          ARM_USART_MODEM_STATUS USART_GetModemStatus(USART_RESOURCES *usart)
  \brief       Get USART Modem Status lines state.
  \param[in]   usart     Pointer to USART resources
  \return      modem status \ref ARM_USART_MODEM_STATUS
*/
static
ARM_USART_MODEM_STATUS USART_GetModemStatus(USART_RESOURCES *usart)
{
  ARM_USART_MODEM_STATUS modem_status;

  if ((usart->info->flow_control == ARM_USART_FLOW_CONTROL_NONE) ||
      (usart->info->flow_control == ARM_USART_FLOW_CONTROL_RTS)) {
    if (GPIO_PinRead(usart->io.cts->port, usart->io.cts->pin) == 0U)
      modem_status.cts = 1U;
    else
      modem_status.cts = 0U;
  }
  else {
    // Hardware CTS
    modem_status.cts = 0U;
  }

  modem_status.dsr = 0U;
  modem_status.ri  = 0U;
  modem_status.dcd = 0U;

  return modem_status;
}


/**
  \fn          void USART_IRQHandler(USART_RESOURCES *usart)
  \brief       USART Interrupt handler.
  \param[in]   usart     Pointer to USART resources
*/
void USART_IRQHandler(USART_RESOURCES *usart)
{
  uint32_t val, sr, event;
  uint16_t data;

  // Read USART status register
  sr = usart->reg->SR;

  // Reset local variables
  val = 0U;
  event = 0U;
  data = 0U;

  // Read Data register not empty
  if (sr & USART_SR_RXNE & usart->reg->CR1) {
    // Check for RX overflow
    if (usart->info->status.rx_busy == 0U) {
      // New receive has not been started
      // Dump RX data
      usart->reg->DR;
      usart->info->status.rx_overflow = 1;
      event |= ARM_USART_EVENT_RX_OVERFLOW;
    }
    else {
      if ((usart->info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER)
          && (usart->xfer->sync_mode == USART_SYNC_MODE_TX)) {
        // Dummy read in synchronous transmit only mode
        usart->reg->DR;
      }
      else {
        // Read data from RX FIFO into receive buffer
        data = (uint16_t) usart->reg->DR;
      }

      *(usart->xfer->rx_buf++) = (uint8_t) data;

      // If nine bit data, no parity
      val = usart->reg->CR1;
      if (((val & USART_CR1_PCE) == 0U) && ((val & USART_CR1_M) != 0U)) {
        *(usart->xfer->rx_buf++) = (uint8_t) (data >> 8U);
      }
      usart->xfer->rx_cnt++;

      // Check if requested amount of data is received
      if (usart->xfer->rx_cnt == usart->xfer->rx_num) {
        // Disable IDLE interrupt
        usart->reg->CR1 &= ~USART_CR1_IDLEIE;

        // Clear RX busy flag and set receive transfer complete event
        usart->info->status.rx_busy = 0U;
        if (usart->info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER) {
          val = usart->xfer->sync_mode;
          usart->xfer->sync_mode = 0U;
          switch (val) {
            case USART_SYNC_MODE_TX:
              event |= ARM_USART_EVENT_SEND_COMPLETE;
              break;
            case USART_SYNC_MODE_RX:
              event |= ARM_USART_EVENT_RECEIVE_COMPLETE;
              break;
            case USART_SYNC_MODE_TX_RX:
              event |= ARM_USART_EVENT_TRANSFER_COMPLETE;
              break;
            default:
              break;
          }
        }
        else {
          event |= ARM_USART_EVENT_RECEIVE_COMPLETE;
        }
      }
    }
  }

  // IDLE line
  if (sr & USART_SR_IDLE & usart->reg->CR1) {
    // Dummy read to clear IDLE interrupt
    usart->reg->DR;
    event |= ARM_USART_EVENT_RX_TIMEOUT;
  }

  // Transmit data register empty
  if (sr & USART_SR_TXE & usart->reg->CR1) {
    // Break handling
    if (usart->xfer->break_flag) {
      // Send break
      usart->reg->CR1 |= USART_CR1_SBK;
    }
    else {
      if (usart->xfer->tx_num != usart->xfer->tx_cnt) {
        if ((usart->info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER)
            && (usart->xfer->sync_mode == USART_SYNC_MODE_RX)) {
          // Dummy write in synchronous receive only mode
          data = usart->xfer->def_val;
        }
        else {
          // Write data to TX FIFO
          data = *(usart->xfer->tx_buf++);

          // If nine bit data, no parity
          val = usart->reg->CR1;
          if (((val & USART_CR1_PCE) == 0U) && ((val & USART_CR1_M) != 0U)) {
            data |= *(usart->xfer->tx_buf++) << 8U;
          }
        }
      }
      usart->xfer->tx_cnt++;

      // Write to data register
      usart->reg->DR = data;

      // Check if all data is transmitted
      if (usart->xfer->tx_num == usart->xfer->tx_cnt) {
        // Disable TXE interrupt
        usart->reg->CR1 &= ~USART_CR1_TXEIE;

        // Enable TC interrupt
        usart->reg->CR1 |= USART_CR1_TCIE;

        usart->xfer->send_active = 0U;

        // Set send complete event
        if (usart->info->mode == ARM_USART_MODE_SYNCHRONOUS_MASTER) {
          if ((usart->xfer->sync_mode == USART_SYNC_MODE_TX)
              && ((usart->info->flags & USART_FLAG_RX_ENABLED) == 0U)) {
            event |= ARM_USART_EVENT_SEND_COMPLETE;
          }
        }
        else {
          event |= ARM_USART_EVENT_SEND_COMPLETE;
        }
      }
    }
  }

  // Transmission complete
  if (sr & USART_SR_TC & usart->reg->CR1) {
    // Disable transmission complete interrupt
    usart->reg->CR1 &= ~USART_CR1_TCIE;
    event |= ARM_USART_EVENT_TX_COMPLETE;
  }

  // RX Overrun
  if ((sr & USART_SR_ORE) != 0U) {
    // Shift register has been overwritten
    // Dummy data read to clear the ORE flag
    usart->reg->DR;
    usart->info->status.rx_overflow = 1U;
    event |= ARM_USART_EVENT_RX_OVERFLOW;
  }

  // Framing error
  if ((sr & USART_SR_FE) != 0U) {
    // Dummy data read to clear the FE flag
    usart->reg->DR;
    usart->info->status.rx_framing_error = 1U;
    event |= ARM_USART_EVENT_RX_FRAMING_ERROR;
  }

  // Parity error
  if ((sr & USART_SR_PE) != 0U) {
    // Dummy data read to clear the PE flag
    usart->reg->DR;
    usart->info->status.rx_parity_error = 1U;
    event |= ARM_USART_EVENT_RX_PARITY_ERROR;
  }

  // Break Detection
  if ((sr & USART_SR_LBD) != 0U) {
    // Clear Break detection flag
    usart->reg->SR &= ~USART_SR_LBD;

    usart->info->status.rx_break = 1U;
    event |= ARM_USART_EVENT_RX_BREAK;
  }

  // CTS changed
  if ((sr & USART_SR_CTS) != 0U) {
    // Clear CTS flag
    usart->reg->SR &= ~USART_SR_CTS;

    event |= ARM_USART_EVENT_CTS;
  }

  // Send Event
  if ((event && usart->info->cb_event) != 0U) {
    usart->info->cb_event(event);
  }
}

#ifdef USE_USART1
// USART1 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART1_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART1_Resources);
}

static
int32_t USART1_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART1_Resources);
}

static
int32_t USART1_Uninitialize(void)
{
  return USART_Uninitialize(&USART1_Resources);
}

static
int32_t USART1_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART1_Resources);
}

static
int32_t USART1_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART1_Resources);
}

static
int32_t USART1_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART1_Resources);
}

static
int32_t USART1_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART1_Resources);
}

static
uint32_t USART1_GetTxCount(void)
{
  return USART_GetTxCount(&USART1_Resources);
}

static
uint32_t USART1_GetRxCount(void)
{
  return USART_GetRxCount(&USART1_Resources);
}

static
int32_t USART1_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART1_Resources);
}

static
ARM_USART_STATUS USART1_GetStatus(void)
{
  return USART_GetStatus (&USART1_Resources);
}

static
int32_t USART1_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART1_Resources);
}

static
ARM_USART_MODEM_STATUS USART1_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART1_Resources);
}

void USART1_IRQHandler(void)
{
  USART_IRQHandler(&USART1_Resources);
}

// USART1 Driver Control Block
ARM_DRIVER_USART Driver_USART1 = {
    USARTx_GetVersion,
    USART1_GetCapabilities,
    USART1_Initialize,
    USART1_Uninitialize,
    USART1_PowerControl,
    USART1_Send,
    USART1_Receive,
    USART1_Transfer,
    USART1_GetTxCount,
    USART1_GetRxCount,
    USART1_Control,
    USART1_GetStatus,
    USART1_SetModemControl,
    USART1_GetModemStatus
};
#endif

#ifdef USE_USART2
// USART2 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART2_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART2_Resources);
}

static
int32_t USART2_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART2_Resources);
}

static
int32_t USART2_Uninitialize(void)
{
  return USART_Uninitialize(&USART2_Resources);
}

static
int32_t USART2_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART2_Resources);
}

static
int32_t USART2_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART2_Resources);
}

static
int32_t USART2_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART2_Resources);
}

static
int32_t USART2_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART2_Resources);
}

static
uint32_t USART2_GetTxCount(void)
{
  return USART_GetTxCount(&USART2_Resources);
}

static
uint32_t USART2_GetRxCount(void)
{
  return USART_GetRxCount(&USART2_Resources);
}

static
int32_t USART2_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART2_Resources);
}

static
ARM_USART_STATUS USART2_GetStatus(void)
{
  return USART_GetStatus(&USART2_Resources);
}

static
int32_t USART2_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART2_Resources);
}

static
ARM_USART_MODEM_STATUS USART2_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART2_Resources);
}

void USART2_IRQHandler(void)
{
  USART_IRQHandler(&USART2_Resources);
}

// USART2 Driver Control Block
ARM_DRIVER_USART Driver_USART2 = {
    USARTx_GetVersion,
    USART2_GetCapabilities,
    USART2_Initialize,
    USART2_Uninitialize,
    USART2_PowerControl,
    USART2_Send,
    USART2_Receive,
    USART2_Transfer,
    USART2_GetTxCount,
    USART2_GetRxCount,
    USART2_Control,
    USART2_GetStatus,
    USART2_SetModemControl,
    USART2_GetModemStatus
};
#endif

#ifdef USE_USART3
// USART3 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART3_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART3_Resources);
}

static
int32_t USART3_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART3_Resources);
}

static
int32_t USART3_Uninitialize(void)
{
  return USART_Uninitialize(&USART3_Resources);
}

static
int32_t USART3_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART3_Resources);
}

static
int32_t USART3_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART3_Resources);
}

static
int32_t USART3_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART3_Resources);
}

static
int32_t USART3_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART3_Resources);
}

static
uint32_t USART3_GetTxCount(void)
{
  return USART_GetTxCount(&USART3_Resources);
}

static
uint32_t USART3_GetRxCount(void)
{
  return USART_GetRxCount(&USART3_Resources);
}

static
int32_t USART3_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART3_Resources);
}

static
ARM_USART_STATUS USART3_GetStatus(void)
{
  return USART_GetStatus(&USART3_Resources);
}

static
int32_t USART3_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART3_Resources);
}

static
ARM_USART_MODEM_STATUS USART3_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART3_Resources);
}

void USART3_IRQHandler(void)
{
  USART_IRQHandler(&USART3_Resources);
}

// USART3 Driver Control Block
ARM_DRIVER_USART Driver_USART3 = {
    USARTx_GetVersion,
    USART3_GetCapabilities,
    USART3_Initialize,
    USART3_Uninitialize,
    USART3_PowerControl,
    USART3_Send,
    USART3_Receive,
    USART3_Transfer,
    USART3_GetTxCount,
    USART3_GetRxCount,
    USART3_Control,
    USART3_GetStatus,
    USART3_SetModemControl,
    USART3_GetModemStatus
};
#endif

#ifdef USE_UART4
// USART4 Driver Wrapper functions
static
ARM_USART_CAPABILITIES USART4_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART4_Resources);
}

static
int32_t USART4_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART4_Resources);
}

static
int32_t USART4_Uninitialize(void)
{
  return USART_Uninitialize(&USART4_Resources);
}

static
int32_t USART4_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART4_Resources);
}

static
int32_t USART4_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART4_Resources);
}

static
int32_t USART4_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART4_Resources);
}

static
int32_t USART4_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART4_Resources);
}

static
uint32_t USART4_GetTxCount(void)
{
  return USART_GetTxCount(&USART4_Resources);
}

static
uint32_t USART4_GetRxCount(void)
{
  return USART_GetRxCount(&USART4_Resources);
}

static
int32_t USART4_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART4_Resources);
}

static
ARM_USART_STATUS USART4_GetStatus(void)
{
  return USART_GetStatus(&USART4_Resources);
}

static
int32_t USART4_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART4_Resources);
}

static
ARM_USART_MODEM_STATUS USART4_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART4_Resources);
}

void UART4_IRQHandler(void)
{
  USART_IRQHandler(&USART4_Resources);
}

// USART4 Driver Control Block
ARM_DRIVER_USART Driver_USART4 = {
    USARTx_GetVersion,
    USART4_GetCapabilities,
    USART4_Initialize,
    USART4_Uninitialize,
    USART4_PowerControl,
    USART4_Send,
    USART4_Receive,
    USART4_Transfer,
    USART4_GetTxCount,
    USART4_GetRxCount,
    USART4_Control,
    USART4_GetStatus,
    USART4_SetModemControl,
    USART4_GetModemStatus
};
#endif

#ifdef USE_UART5
// USART5 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART5_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART5_Resources);
}

static
int32_t USART5_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART5_Resources);
}

static
int32_t USART5_Uninitialize(void)
{
  return USART_Uninitialize(&USART5_Resources);
}

static
int32_t USART5_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART5_Resources);
}

static
int32_t USART5_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART5_Resources);
}

static
int32_t USART5_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART5_Resources);
}

static
int32_t USART5_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART5_Resources);
}

static
uint32_t USART5_GetTxCount(void)
{
  return USART_GetTxCount(&USART5_Resources);
}

static
uint32_t USART5_GetRxCount(void)
{
  return USART_GetRxCount(&USART5_Resources);
}

static
int32_t USART5_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART5_Resources);
}

static
ARM_USART_STATUS USART5_GetStatus(void)
{
  return USART_GetStatus(&USART5_Resources);
}

static
int32_t USART5_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART5_Resources);
}

static
ARM_USART_MODEM_STATUS USART5_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART5_Resources);
}

void UART5_IRQHandler(void)
{
  USART_IRQHandler(&USART5_Resources);
}

// USART5 Driver Control Block
ARM_DRIVER_USART Driver_USART5 = {
    USARTx_GetVersion,
    USART5_GetCapabilities,
    USART5_Initialize,
    USART5_Uninitialize,
    USART5_PowerControl,
    USART5_Send,
    USART5_Receive,
    USART5_Transfer,
    USART5_GetTxCount,
    USART5_GetRxCount,
    USART5_Control,
    USART5_GetStatus,
    USART5_SetModemControl,
    USART5_GetModemStatus
};
#endif

#ifdef USE_USART6
// USART6 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART6_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART6_Resources);
}

static
int32_t USART6_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART6_Resources);
}

static
int32_t USART6_Uninitialize(void)
{
  return USART_Uninitialize(&USART6_Resources);
}

static
int32_t USART6_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART6_Resources);
}

static
int32_t USART6_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART6_Resources);
}

static
int32_t USART6_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART6_Resources);
}

static
int32_t USART6_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART6_Resources);
}

static
uint32_t USART6_GetTxCount(void)
{
  return USART_GetTxCount(&USART6_Resources);
}

static
uint32_t USART6_GetRxCount(void)
{
  return USART_GetRxCount(&USART6_Resources);
}

static
int32_t USART6_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART6_Resources);
}

static
ARM_USART_STATUS USART6_GetStatus(void)
{
  return USART_GetStatus(&USART6_Resources);
}

static
int32_t USART6_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART6_Resources);
}

static
ARM_USART_MODEM_STATUS USART6_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART6_Resources);
}

void USART6_IRQHandler(void)
{
  USART_IRQHandler(&USART6_Resources);
}

// USART6 Driver Control Block
ARM_DRIVER_USART Driver_USART6 = {
    USARTx_GetVersion,
    USART6_GetCapabilities,
    USART6_Initialize,
    USART6_Uninitialize,
    USART6_PowerControl,
    USART6_Send,
    USART6_Receive,
    USART6_Transfer,
    USART6_GetTxCount,
    USART6_GetRxCount,
    USART6_Control,
    USART6_GetStatus,
    USART6_SetModemControl,
    USART6_GetModemStatus
};
#endif

#ifdef USE_UART7
// USART7 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART7_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART7_Resources);
}

static
int32_t USART7_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART7_Resources);
}

static
int32_t USART7_Uninitialize(void)
{
  return USART_Uninitialize(&USART7_Resources);
}

static
int32_t USART7_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART7_Resources);
}

static
int32_t USART7_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART7_Resources);
}

static
int32_t USART7_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART7_Resources);
}

static
int32_t USART7_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART7_Resources);
}

static
uint32_t USART7_GetTxCount(void)
{
  return USART_GetTxCount(&USART7_Resources);
}

static
uint32_t USART7_GetRxCount(void)
{
  return USART_GetRxCount(&USART7_Resources);
}

static
int32_t USART7_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART7_Resources);
}

static
ARM_USART_STATUS USART7_GetStatus(void)
{
  return USART_GetStatus(&USART7_Resources);
}

static
int32_t USART7_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART7_Resources);
}

static
ARM_USART_MODEM_STATUS USART7_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART7_Resources);
}

void UART7_IRQHandler(void)
{
  USART_IRQHandler(&USART7_Resources);
}

// USART7 Driver Control Block
ARM_DRIVER_USART Driver_USART7 = {
    USARTx_GetVersion,
    USART7_GetCapabilities,
    USART7_Initialize,
    USART7_Uninitialize,
    USART7_PowerControl,
    USART7_Send,
    USART7_Receive,
    USART7_Transfer,
    USART7_GetTxCount,
    USART7_GetRxCount,
    USART7_Control,
    USART7_GetStatus,
    USART7_SetModemControl,
    USART7_GetModemStatus
};
#endif

#ifdef USE_UART8
// USART8 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART8_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART8_Resources);
}

static
int32_t USART8_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART8_Resources);
}

static
int32_t USART8_Uninitialize(void)
{
  return USART_Uninitialize(&USART8_Resources);
}

static
int32_t USART8_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART8_Resources);
}

static
int32_t USART8_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART8_Resources);
}

static
int32_t USART8_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART8_Resources);
}

static
int32_t USART8_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART8_Resources);
}

static
uint32_t USART8_GetTxCount(void)
{
  return USART_GetTxCount(&USART8_Resources);
}

static
uint32_t USART8_GetRxCount(void)
{
  return USART_GetRxCount(&USART8_Resources);
}

static
int32_t USART8_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART8_Resources);
}

static
ARM_USART_STATUS USART8_GetStatus(void)
{
  return USART_GetStatus(&USART8_Resources);
}

static
int32_t USART8_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART8_Resources);
}

static
ARM_USART_MODEM_STATUS USART8_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART8_Resources);
}

void UART8_IRQHandler(void)
{
  USART_IRQHandler(&USART8_Resources);
}

// USART8 Driver Control Block
ARM_DRIVER_USART Driver_USART8 = {
    USARTx_GetVersion,
    USART8_GetCapabilities,
    USART8_Initialize,
    USART8_Uninitialize,
    USART8_PowerControl,
    USART8_Send,
    USART8_Receive,
    USART8_Transfer,
    USART8_GetTxCount,
    USART8_GetRxCount,
    USART8_Control,
    USART8_GetStatus,
    USART8_SetModemControl,
    USART8_GetModemStatus
};
#endif

#ifdef USE_UART9
// USART9 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART9_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART9_Resources);
}

static
int32_t USART9_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART9_Resources);
}

static
int32_t USART9_Uninitialize(void)
{
  return USART_Uninitialize(&USART9_Resources);
}

static
int32_t USART9_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART9_Resources);
}

static
int32_t USART9_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART9_Resources);
}

static
int32_t USART9_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART9_Resources);
}

static
int32_t USART9_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART9_Resources);
}

static
uint32_t USART9_GetTxCount(void)
{
  return USART_GetTxCount(&USART9_Resources);
}

static
uint32_t USART9_GetRxCount(void)
{
  return USART_GetRxCount(&USART9_Resources);
}

static
int32_t USART9_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART9_Resources);
}

static
ARM_USART_STATUS USART9_GetStatus(void)
{
  return USART_GetStatus(&USART9_Resources);
}

static
int32_t USART9_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART9_Resources);
}

static
ARM_USART_MODEM_STATUS USART9_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART9_Resources);
}

void UART9_IRQHandler(void)
{
  USART_IRQHandler(&USART9_Resources);
}

// USART9 Driver Control Block
ARM_DRIVER_USART Driver_USART9 = {
    USARTx_GetVersion,
    USART9_GetCapabilities,
    USART9_Initialize,
    USART9_Uninitialize,
    USART9_PowerControl,
    USART9_Send,
    USART9_Receive,
    USART9_Transfer,
    USART9_GetTxCount,
    USART9_GetRxCount,
    USART9_Control,
    USART9_GetStatus,
    USART9_SetModemControl,
    USART9_GetModemStatus
};
#endif

#ifdef USE_UART10
// USART10 Driver Wrapper functions

static
ARM_USART_CAPABILITIES USART10_GetCapabilities(void)
{
  return USART_GetCapabilities(&USART10_Resources);
}

static
int32_t USART10_Initialize(ARM_USART_SignalEvent_t cb_event)
{
  return USART_Initialize(cb_event, &USART10_Resources);
}

static
int32_t USART10_Uninitialize(void)
{
  return USART_Uninitialize(&USART10_Resources);
}

static
int32_t USART10_PowerControl(ARM_POWER_STATE state)
{
  return USART_PowerControl(state, &USART10_Resources);
}

static
int32_t USART10_Send(const void *data, uint32_t num)
{
  return USART_Send(data, num, &USART10_Resources);
}

static
int32_t USART10_Receive(void *data, uint32_t num)
{
  return USART_Receive(data, num, &USART10_Resources);
}

static
int32_t USART10_Transfer(const void *data_out, void *data_in, uint32_t num)
{
  return USART_Transfer(data_out, data_in, num, &USART10_Resources);
}

static
uint32_t USART10_GetTxCount(void)
{
  return USART_GetTxCount(&USART10_Resources);
}

static
uint32_t USART10_GetRxCount(void)
{
  return USART_GetRxCount(&USART10_Resources);
}

static
int32_t USART10_Control(uint32_t control, uint32_t arg)
{
  return USART_Control(control, arg, &USART10_Resources);
}

static
ARM_USART_STATUS USART10_GetStatus(void)
{
  return USART_GetStatus(&USART10_Resources);
}

static
int32_t USART10_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
  return USART_SetModemControl(control, &USART10_Resources);
}

static
ARM_USART_MODEM_STATUS USART10_GetModemStatus(void)
{
  return USART_GetModemStatus(&USART10_Resources);
}

void UART10_IRQHandler(void)
{
  USART_IRQHandler(&USART10_Resources);
}

// USART10 Driver Control Block
ARM_DRIVER_USART Driver_USART10 = {
    USARTx_GetVersion,
    USART10_GetCapabilities,
    USART10_Initialize,
    USART10_Uninitialize,
    USART10_PowerControl,
    USART10_Send,
    USART10_Receive,
    USART10_Transfer,
    USART10_GetTxCount,
    USART10_GetRxCount,
    USART10_Control,
    USART10_GetStatus,
    USART10_SetModemControl,
    USART10_GetModemStatus
};
#endif

#endif /* defined(USE_USART1) || defined(USE_USART2) || defined(USE_USART3) ... */

/* ----------------------------- End of file ---------------------------------*/
