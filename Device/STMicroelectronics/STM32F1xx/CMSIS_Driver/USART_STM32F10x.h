/*
 * Copyright (C) 2018 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: SPI Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef USART_STM32F10X_H_
#define USART_STM32F10X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f1xx.h"
#include "GPIO_STM32F10x.h"
#include "RCC_STM32F10x.h"
#include "DMA_STM32F10x.h"
#include "Driver_USART.h"

#include "Config/RTE_Device.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* USART1 configuration definitions */
#if (RTE_USART1 == 1)
  #define USE_USART1

  #if (RTE_USART1_RX_DMA == 1)
    #define USART1_RX_DMA_Instance    DMAx_CHANNELy(RTE_USART1_RX_DMA_NUMBER, RTE_USART1_RX_DMA_CHANNEL)
    #define USART1_RX_DMA_IRQn        DMAx_CHANNELy_IRQn(RTE_USART1_RX_DMA_NUMBER, RTE_USART1_RX_DMA_CHANNEL)
    #define USART1_RX_DMA_Channel     RTE_USART1_RX_DMA_CHANNEL
    #define USART1_RX_DMA_Priority    RTE_USART1_RX_DMA_PRIORITY

    #define USART1_RX_DMA_Handler     DMAx_CHANNELy_EVENT(RTE_USART1_RX_DMA_NUMBER, RTE_USART1_RX_DMA_CHANNEL)
  #endif
  #if (RTE_USART1_TX_DMA == 1)
    #define USART1_TX_DMA_Instance    DMAx_CHANNELy(RTE_USART1_TX_DMA_NUMBER, RTE_USART1_TX_DMA_CHANNEL)
    #define USART1_TX_DMA_IRQn        DMAx_CHANNELy_IRQn(RTE_USART1_TX_DMA_NUMBER, RTE_USART1_TX_DMA_CHANNEL)
    #define USART1_TX_DMA_Channel     RTE_USART1_TX_DMA_CHANNEL
    #define USART1_TX_DMA_Priority    RTE_USART1_TX_DMA_PRIORITY

    #define USART1_TX_DMA_Handler     DMAx_CHANNELy_EVENT(RTE_USART1_TX_DMA_NUMBER, RTE_USART1_TX_DMA_CHANNEL)
  #endif

  #if (RTE_USART1_TX == 1)
    #define USE_USART1_TX_Pin         1U
    #define USART1_TX_GPIOx           RTE_USART1_TX_PORT
    #define USART1_TX_GPIO_Pin        RTE_USART1_TX_BIT
  #endif

  #if (RTE_USART1_RX == 1)
    #define USE_USART1_RX_Pin         1U
    #define USART1_RX_GPIOx           RTE_USART1_RX_PORT
    #define USART1_RX_GPIO_Pin        RTE_USART1_RX_BIT
  #endif

  #if (RTE_USART1_CK == 1)
    #define USE_USART1_CK_Pin         1U
    #define USART1_CK_GPIOx           RTE_USART1_CK_PORT
    #define USART1_CK_GPIO_Pin        RTE_USART1_CK_BIT
  #endif

  #if (RTE_USART1_RTS == 1)
    #define USE_USART1_RTS_Pin        1U
    #define USART1_RTS_GPIOx          RTE_USART1_RTS_PORT
    #define USART1_RTS_GPIO_Pin       RTE_USART1_RTS_BIT
  #endif

  #if (RTE_USART1_CTS == 1)
    #define USE_USART1_CTS_Pin        1U
    #define USART1_CTS_GPIOx          RTE_USART1_CTS_PORT
    #define USART1_CTS_GPIO_Pin       RTE_USART1_CTS_BIT
  #endif

  #define USART1_REMAP_DEF            AFIO_USART1_NO_REMAP
  #define USART1_REMAP                RTE_USART1_AF_REMAP
#endif

/* USART2 configuration definitions */
#if (RTE_USART2 == 1)
  #define USE_USART2

  #if (RTE_USART2_RX_DMA == 1)
    #define USART2_RX_DMA_Instance    DMAx_CHANNELy(RTE_USART2_RX_DMA_NUMBER, RTE_USART2_RX_DMA_CHANNEL)
    #define USART2_RX_DMA_IRQn        DMAx_CHANNELy_IRQn(RTE_USART2_RX_DMA_NUMBER, RTE_USART2_RX_DMA_CHANNEL)
    #define USART2_RX_DMA_Channel     RTE_USART2_RX_DMA_CHANNEL
    #define USART2_RX_DMA_Priority    RTE_USART2_RX_DMA_PRIORITY

    #define USART2_RX_DMA_Handler     DMAx_CHANNELy_EVENT(RTE_USART2_RX_DMA_NUMBER, RTE_USART2_RX_DMA_CHANNEL)
  #endif
  #if (RTE_USART2_TX_DMA == 1)
    #define USART2_TX_DMA_Instance    DMAx_CHANNELy(RTE_USART2_TX_DMA_NUMBER, RTE_USART2_TX_DMA_CHANNEL)
    #define USART2_TX_DMA_IRQn        DMAx_CHANNELy_IRQn(RTE_USART2_TX_DMA_NUMBER, RTE_USART2_TX_DMA_CHANNEL)
    #define USART2_TX_DMA_Channel     RTE_USART2_TX_DMA_CHANNEL
    #define USART2_TX_DMA_Priority    RTE_USART2_TX_DMA_PRIORITY

    #define USART2_TX_DMA_Handler     DMAx_CHANNELy_EVENT(RTE_USART2_TX_DMA_NUMBER, RTE_USART2_TX_DMA_CHANNEL)
  #endif

  #if (RTE_USART2_TX == 1)
    #define USE_USART2_TX_Pin         1U
    #define USART2_TX_GPIOx           RTE_USART2_TX_PORT
    #define USART2_TX_GPIO_Pin        RTE_USART2_TX_BIT
  #endif

  #if (RTE_USART2_RX == 1)
    #define USE_USART2_RX_Pin         1U
    #define USART2_RX_GPIOx           RTE_USART2_RX_PORT
    #define USART2_RX_GPIO_Pin        RTE_USART2_RX_BIT
  #endif

  #if (RTE_USART2_CK == 1)
    #define USE_USART2_CK_Pin         1U
    #define USART2_CK_GPIOx           RTE_USART2_CK_PORT
    #define USART2_CK_GPIO_Pin        RTE_USART2_CK_BIT
  #endif

  #if (RTE_USART2_RTS == 1)
    #define USE_USART2_RTS_Pin        1U
    #define USART2_RTS_GPIOx          RTE_USART2_RTS_PORT
    #define USART2_RTS_GPIO_Pin       RTE_USART2_RTS_BIT
  #endif

  #if (RTE_USART2_CTS == 1)
    #define USE_USART2_CTS_Pin        1U
    #define USART2_CTS_GPIOx          RTE_USART2_CTS_PORT
    #define USART2_CTS_GPIO_Pin       RTE_USART2_CTS_BIT
  #endif

  #define USART2_REMAP_DEF            AFIO_USART2_NO_REMAP
  #define USART2_REMAP                RTE_USART2_AF_REMAP
#endif

/* USART3 configuration definitions */
#if (RTE_USART3 == 1)

  #if defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6)
    #error "USART3 is not available for selected device!"
  #endif

  #define USE_USART3

  #if (RTE_USART3_RX_DMA == 1)
    #define USART3_RX_DMA_Instance    DMAx_CHANNELy(RTE_USART3_RX_DMA_NUMBER, RTE_USART3_RX_DMA_CHANNEL)
    #define USART3_RX_DMA_IRQn        DMAx_CHANNELy_IRQn(RTE_USART3_RX_DMA_NUMBER, RTE_USART3_RX_DMA_CHANNEL)
    #define USART3_RX_DMA_Channel     RTE_USART3_RX_DMA_CHANNEL
    #define USART3_RX_DMA_Priority    RTE_USART3_RX_DMA_PRIORITY

    #define USART3_RX_DMA_Handler     DMAx_CHANNELy_EVENT(RTE_USART3_RX_DMA_NUMBER, RTE_USART3_RX_DMA_CHANNEL)
  #endif
  #if (RTE_USART3_TX_DMA == 1)
    #define USART3_TX_DMA_Instance    DMAx_CHANNELy(RTE_USART3_TX_DMA_NUMBER, RTE_USART3_TX_DMA_CHANNEL)
    #define USART3_TX_DMA_IRQn        DMAx_CHANNELy_IRQn(RTE_USART3_TX_DMA_NUMBER, RTE_USART3_TX_DMA_CHANNEL)
    #define USART3_TX_DMA_Channel     RTE_USART3_TX_DMA_CHANNEL
    #define USART3_TX_DMA_Priority    RTE_USART3_TX_DMA_PRIORITY

    #define USART3_TX_DMA_Handler     DMAx_CHANNELy_EVENT(RTE_USART3_TX_DMA_NUMBER, RTE_USART3_TX_DMA_CHANNEL)
  #endif

  #if (RTE_USART3_TX == 1)
    #define USE_USART3_TX_Pin         1U
    #define USART3_TX_GPIOx           RTE_USART3_TX_PORT
    #define USART3_TX_GPIO_Pin        RTE_USART3_TX_BIT
  #endif

  #if (RTE_USART3_RX == 1)
    #define USE_USART3_RX_Pin         1U
    #define USART3_RX_GPIOx           RTE_USART3_RX_PORT
    #define USART3_RX_GPIO_Pin        RTE_USART3_RX_BIT
  #endif

  #if (RTE_USART3_CK == 1)
    #define USE_USART3_CK_Pin         1U
    #define USART3_CK_GPIOx           RTE_USART3_CK_PORT
    #define USART3_CK_GPIO_Pin        RTE_USART3_CK_BIT
  #endif

  #if (RTE_USART3_RTS == 1)
    #define USE_USART3_RTS_Pin        1U
    #define USART3_RTS_GPIOx          RTE_USART3_RTS_PORT
    #define USART3_RTS_GPIO_Pin       RTE_USART3_RTS_BIT
  #endif

  #if (RTE_USART3_CTS == 1)
    #define USE_USART3_CTS_Pin        1U
    #define USART3_CTS_GPIOx          RTE_USART3_CTS_PORT
    #define USART3_CTS_GPIO_Pin       RTE_USART3_CTS_BIT
  #endif

  #define USART3_REMAP_DEF            AFIO_USART3_NO_REMAP
  #define USART3_REMAP                RTE_USART3_AF_REMAP
#endif

/* UART4 configuration definitions */
#if (RTE_UART4 == 1)

  #if !defined(STM32F100xE) && !defined(STM32F101xE) && !defined(STM32F101xG) && !defined(STM32F103xE) && !defined(STM32F103xG) && !defined(STM32F105xC) && !defined(STM32F107xC)
    #error "UART4 is not available for selected device!"
  #endif

  #define USE_UART4

  #if (RTE_UART4_RX_DMA == 1)
    #define UART4_RX_DMA_Instance     DMAx_CHANNELy(RTE_UART4_RX_DMA_NUMBER, RTE_UART4_RX_DMA_CHANNEL)
    #define UART4_RX_DMA_IRQn         DMAx_CHANNELy_IRQn(RTE_UART4_RX_DMA_NUMBER, RTE_UART4_RX_DMA_CHANNEL)
    #define UART4_RX_DMA_Channel      RTE_UART4_RX_DMA_CHANNEL
    #define UART4_RX_DMA_Priority     RTE_UART4_RX_DMA_PRIORITY

    #define UART4_RX_DMA_Handler      DMAx_CHANNELy_EVENT(RTE_UART4_RX_DMA_NUMBER, RTE_UART4_RX_DMA_CHANNEL)
  #endif
  #if (RTE_UART4_TX_DMA == 1)
    #define UART4_TX_DMA_Instance     DMAx_CHANNELy(RTE_UART4_TX_DMA_NUMBER, RTE_UART4_TX_DMA_CHANNEL)
    #define UART4_TX_DMA_IRQn         DMAx_CHANNELy_IRQn(RTE_UART4_TX_DMA_NUMBER, RTE_UART4_TX_DMA_CHANNEL)
    #define UART4_TX_DMA_Channel      RTE_UART4_TX_DMA_CHANNEL
    #define UART4_TX_DMA_Priority     RTE_UART4_TX_DMA_PRIORITY

    #define UART4_TX_DMA_Handler      DMAx_CHANNELy_EVENT(RTE_UART4_TX_DMA_NUMBER, RTE_UART4_TX_DMA_CHANNEL)
  #endif

  #if (RTE_UART4_TX == 1)
    #define USE_UART4_TX_Pin          1U
    #define UART4_TX_GPIOx            RTE_UART4_TX_PORT
    #define UART4_TX_GPIO_Pin         RTE_UART4_TX_BIT
  #endif

  #if (RTE_UART4_RX == 1)
    #define USE_UART4_RX_Pin          1U
    #define UART4_RX_GPIOx            RTE_UART4_RX_PORT
    #define UART4_RX_GPIO_Pin         RTE_UART4_RX_BIT
  #endif

  #define UART4_REMAP_DEF             AFIO_UNAVAILABLE_REMAP
  #define UART4_REMAP                 AFIO_UNAVAILABLE_REMAP
#endif

/* UART5 configuration definitions */
#if (RTE_UART5 == 1)

  #if !defined(STM32F100xE) && !defined(STM32F101xE) && !defined(STM32F101xG) && !defined(STM32F103xE) && !defined(STM32F103xG) && !defined(STM32F105xC) && !defined(STM32F107xC)
    #error "UART5 is not available for selected device!"
  #endif

  #define USE_UART5

  #if (RTE_UART5_RX_DMA == 1)
    #define UART5_RX_DMA_Instance     DMAx_CHANNELy(RTE_UART5_RX_DMA_NUMBER, RTE_UART5_RX_DMA_CHANNEL)
    #define UART5_RX_DMA_IRQn         DMAx_CHANNELy_IRQn(RTE_UART5_RX_DMA_NUMBER, RTE_UART5_RX_DMA_CHANNEL)
    #define UART5_RX_DMA_Channel      RTE_UART5_RX_DMA_CHANNEL
    #define UART5_RX_DMA_Priority     RTE_UART5_RX_DMA_PRIORITY

    #define UART5_RX_DMA_Handler      DMAx_CHANNELy_EVENT(RTE_UART5_RX_DMA_NUMBER, RTE_UART5_RX_DMA_CHANNEL)
  #endif
  #if (RTE_UART5_TX_DMA == 1)
    #define UART5_TX_DMA_Instance     DMAx_CHANNELy(RTE_UART5_TX_DMA_NUMBER, RTE_UART5_TX_DMA_CHANNEL)
    #define UART5_TX_DMA_IRQn         DMAx_CHANNELy_IRQn(RTE_UART5_TX_DMA_NUMBER, RTE_UART5_TX_DMA_CHANNEL)
    #define UART5_TX_DMA_Channel      RTE_UART5_TX_DMA_CHANNEL
    #define UART5_TX_DMA_Priority     RTE_UART5_TX_DMA_PRIORITY

    #define UART5_TX_DMA_Handler      DMAx_CHANNELy_EVENT(RTE_UART5_TX_DMA_NUMBER, RTE_UART5_TX_DMA_CHANNEL)
  #endif

  #if (RTE_UART5_TX == 1)
    #define USE_UART5_TX_Pin          1U
    #define UART5_TX_GPIOx            RTE_UART5_TX_PORT
    #define UART5_TX_GPIO_Pin         RTE_UART5_TX_BIT
  #endif

  #if (RTE_UART5_RX == 1)
    #define USE_UART5_RX_Pin          1U
    #define UART5_RX_GPIOx            RTE_UART5_RX_PORT
    #define UART5_RX_GPIO_Pin         RTE_UART5_RX_BIT
  #endif

  #define UART5_REMAP_DEF             AFIO_UNAVAILABLE_REMAP
  #define UART5_REMAP                 AFIO_UNAVAILABLE_REMAP
#endif

#ifdef USE_USART1
#if (defined(USART1_RX_DMA_Instance) || defined(USART1_TX_DMA_Instance))
#ifndef USART1_RX_DMA_Instance
  #error "USART1 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#ifndef USART1_TX_DMA_Instance
  #error "USART1 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#endif
#endif

#ifdef USE_USART2
#if (defined(USART2_RX_DMA_Instance) || defined(USART2_TX_DMA_Instance))
#ifndef USART2_RX_DMA_Instance
  #error "USART2 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#ifndef USART2_TX_DMA_Instance
  #error "USART2 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#endif
#endif

#ifdef USE_USART3
#if (defined(USART3_RX_DMA_Instance) || defined(USART3_TX_DMA_Instance))
#ifndef USART3_RX_DMA_Instance
  #error "USART3 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#ifndef USART3_TX_DMA_Instance
  #error "USART3 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#endif
#endif

#ifdef USE_UART4
#if (defined(UART4_RX_DMA_Instance) || defined(UART4_TX_DMA_Instance))
#ifndef UART4_RX_DMA_Instance
  #error "UART4 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#ifndef UART4_TX_DMA_Instance
  #error "UART4 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#endif
#endif

#ifdef USE_UART5
#if (defined(UART5_RX_DMA_Instance) || defined(UART5_TX_DMA_Instance))
#ifndef UART5_RX_DMA_Instance
  #error "UART5 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#ifndef UART5_TX_DMA_Instance
  #error "UART5 using DMA requires Rx and Tx DMA channel enabled in RTE_Device.h or Device.h!"
#endif
#endif
#endif

#if (defined(USART1_RX_DMA_Instance) || \
     defined(USART2_RX_DMA_Instance) || \
     defined(USART3_RX_DMA_Instance) || \
     defined(UART4_RX_DMA_Instance ) || \
     defined(UART5_RX_DMA_Instance ))
#define __USART_DMA_RX
#endif
#if (defined(USART1_TX_DMA_Instance) || \
     defined(USART2_TX_DMA_Instance) || \
     defined(USART3_TX_DMA_Instance) || \
     defined(UART4_TX_DMA_Instance ) || \
     defined(UART5_TX_DMA_Instance ))
#define __USART_DMA_TX
#endif
#if (defined(__USART_DMA_RX) && defined(__USART_DMA_TX))
#define __USART_DMA
#endif

// USART BRR macro
#define USART_DIVIDER(_PCLK_, _BAUD_)           (((_PCLK_)*25)/(4*(_BAUD_)))
#define USART_DIVIDER_MANTISA(_PCLK_, _BAUD_)     (USART_DIVIDER((_PCLK_), (_BAUD_))/100)
#define USART_DIVIDER_FRACTION(_PCLK_, _BAUD_)  (((USART_DIVIDER((_PCLK_), (_BAUD_)) - (USART_DIVIDER_MANTISA((_PCLK_), (_BAUD_)) * 100)) * 16 + 50) / 100)
#define USART_BAUDRATE_DIVIDER(_PCLK_, _BAUD_)   ((USART_DIVIDER_MANTISA((_PCLK_), (_BAUD_)) << 4)|(USART_DIVIDER_FRACTION((_PCLK_), (_BAUD_)) & 0x0F))

/* USART flags */
#define USART_FLAG_INITIALIZED      ((uint8_t)(1U << 0U))
#define USART_FLAG_POWERED          ((uint8_t)(1U << 1U))
#define USART_FLAG_CONFIGURED       ((uint8_t)(1U << 2U))
#define USART_FLAG_TX_ENABLED       ((uint8_t)(1U << 3U))
#define USART_FLAG_RX_ENABLED       ((uint8_t)(1U << 4U))

/* USART synchronous transfer modes */
#define USART_SYNC_MODE_TX           (1UL)
#define USART_SYNC_MODE_RX           (2UL)
#define USART_SYNC_MODE_TX_RX        (USART_SYNC_MODE_TX | USART_SYNC_MODE_RX)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* USART DMA */
typedef const DMA_INFO USART_DMA;

/* USART pin */
typedef const struct _USART_PIN {
  GPIO_PORT_t           port;           // Port
  GPIO_PIN_t            pin;            // Pin
} USART_PIN;

/* USART Input/Output Configuration */
typedef const struct _USART_IO {
  USART_PIN            *tx;             // TX  Pin identifier
  USART_PIN            *rx;             // RX  Pin identifier
  USART_PIN            *ck;             // CLK Pin identifier
  USART_PIN            *rts;            // RTS Pin identifier
  USART_PIN            *cts;            // CTS Pin identifier
  AFIO_REMAP            afio_def;       // Default pin remapping setting
  AFIO_REMAP            afio;           // Pin remapping information
} USART_IO;

// USART Transfer Information (Run-Time)
typedef struct _USART_TRANSFER_INFO {
  uint32_t              rx_num;         // Total number of receive data
  uint32_t              tx_num;         // Total number of transmit data
  uint8_t              *rx_buf;         // Pointer to in data buffer
  uint8_t              *tx_buf;         // Pointer to out data buffer
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              tx_cnt;         // Number of data sent
  uint16_t              dump_val;       // Variable for dumping DMA data
  uint16_t              def_val;        // Default transfer value
  uint32_t              sync_mode;      // Synchronous mode flag
  uint8_t               break_flag;     // Transmit break flag
  uint8_t               send_active;    // Send active flag
} USART_TRANSFER_INFO;

typedef struct _USART_STATUS {
  uint8_t tx_busy;                      // Transmitter busy flag
  uint8_t rx_busy;                      // Receiver busy flag
  uint8_t tx_underflow;                 // Transmit data underflow detected (cleared on start of next send operation)
  uint8_t rx_overflow;                  // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t rx_break;                     // Break detected on receive (cleared on start of next receive operation)
  uint8_t rx_framing_error;             // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t rx_parity_error;              // Parity error detected on receive (cleared on start of next receive operation)
} USART_STATUS;

// USART Information (Run-time)
typedef struct _USART_INFO {
  ARM_USART_SignalEvent_t cb_event;            // Event Callback
  USART_STATUS            status;              // Status flags
  uint8_t                 flags;               // Current USART flags
  uint32_t                mode;                // Current USART mode
  uint32_t                flow_control;        // Flow control
} USART_INFO;

// USART Resources definition
typedef const struct {
  ARM_USART_CAPABILITIES  capabilities;        // Capabilities
  USART_TypeDef          *reg;                 // USART peripheral pointer
  RCC_Periph_t            periph;              // Peripheral
  USART_IO                io;                  // USART Input/Output pins
  IRQn_Type               irq_num;             // USART IRQ Number
  USART_DMA               *dma_tx;             // Transmit stream register interface
  USART_DMA               *dma_rx;             // Receive stream register interface
  USART_INFO              *info;               // Run-Time Information
  USART_TRANSFER_INFO     *xfer;               // USART transfer information
} USART_RESOURCES;

#endif /* USART_STM32F10X_H_ */
