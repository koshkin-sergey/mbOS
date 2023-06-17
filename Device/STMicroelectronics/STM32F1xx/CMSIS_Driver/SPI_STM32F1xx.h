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
 * Project: SPI Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef SPI_STM32F1XX_H_
#define SPI_STM32F1XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#include "device_config.h"
#include "asm/stm32f1xx.h"
#include "asm/DMA_STM32F1xx.h"
#include "asm/GPIO_STM32F1xx.h"
#include "asm/RCC_STM32F1xx.h"

#include "Driver/Driver_SPI.h"


/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* SPI1 configuration definitions */
#if (DEV_SPI1 == 1)
  #define USE_SPI1

  #if (DEV_SPI1_RX_DMA == 1)
    #define SPI1_RX_DMA_Instance    DMAx_CHANNELy(DEV_SPI1_RX_DMA_NUMBER, DEV_SPI1_RX_DMA_CHANNEL)
    #define SPI1_RX_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_SPI1_RX_DMA_NUMBER, DEV_SPI1_RX_DMA_CHANNEL)
    #define SPI1_RX_DMA_Channel     DEV_SPI1_RX_DMA_CHANNEL
    #define SPI1_RX_DMA_Priority    DEV_SPI1_RX_DMA_PRIORITY

    #define SPI1_RX_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_SPI1_RX_DMA_NUMBER, DEV_SPI1_RX_DMA_CHANNEL)
  #endif
  #if (DEV_SPI1_TX_DMA == 1)
    #define SPI1_TX_DMA_Instance    DMAx_CHANNELy(DEV_SPI1_TX_DMA_NUMBER, DEV_SPI1_TX_DMA_CHANNEL)
    #define SPI1_TX_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_SPI1_TX_DMA_NUMBER, DEV_SPI1_TX_DMA_CHANNEL)
    #define SPI1_TX_DMA_Channel     DEV_SPI1_TX_DMA_CHANNEL
    #define SPI1_TX_DMA_Priority    DEV_SPI1_TX_DMA_PRIORITY

    #define SPI1_TX_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_SPI1_TX_DMA_NUMBER, DEV_SPI1_TX_DMA_CHANNEL)
  #endif

  #if (DEV_SPI1_MISO == 1)
    #define USE_SPI1_MISO_Pin       1U
    #define SPI1_MISO_GPIOx         DEV_SPI1_MISO_PORT
    #define SPI1_MISO_GPIO_Pin      DEV_SPI1_MISO_BIT
  #endif

  #if (DEV_SPI1_MOSI == 1)
    #define USE_SPI1_MOSI_Pin       1U
    #define SPI1_MOSI_GPIOx         DEV_SPI1_MOSI_PORT
    #define SPI1_MOSI_GPIO_Pin      DEV_SPI1_MOSI_BIT
  #endif

  #define USE_SPI1_SCK_Pin          1U
  #define SPI1_SCK_GPIOx            DEV_SPI1_SCK_PORT
  #define SPI1_SCK_GPIO_Pin         DEV_SPI1_SCK_BIT

  #if (DEV_SPI1_NSS == 1)
    #define USE_SPI1_NSS_Pin        1U
    #define SPI1_NSS_GPIOx          DEV_SPI1_NSS_PORT
    #define SPI1_NSS_GPIO_Pin       DEV_SPI1_NSS_BIT
  #endif

  #define SPI1_REMAP_DEF            AFIO_SPI1_NO_REMAP
  #define SPI1_REMAP                DEV_SPI1_AF_REMAP
#endif

/* SPI2 configuration definitions */
#if (DEV_SPI2 == 1)

  #if defined (STM32F101x6) || defined (STM32F102x6) || defined(STM32F103x6)
    #error "SPI2 not available for selected device!"
  #endif

  #define USE_SPI2

  #if (DEV_SPI2_RX_DMA == 1)
    #define SPI2_RX_DMA_Instance    DMAx_CHANNELy(DEV_SPI2_RX_DMA_NUMBER, DEV_SPI2_RX_DMA_CHANNEL)
    #define SPI2_RX_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_SPI2_RX_DMA_NUMBER, DEV_SPI2_RX_DMA_CHANNEL)
    #define SPI2_RX_DMA_Channel     DEV_SPI2_RX_DMA_CHANNEL
    #define SPI2_RX_DMA_Priority    DEV_SPI2_RX_DMA_PRIORITY

    #define SPI2_RX_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_SPI2_RX_DMA_NUMBER, DEV_SPI2_RX_DMA_CHANNEL)
  #endif
  #if (DEV_SPI2_TX_DMA == 1)
    #define SPI2_TX_DMA_Instance    DMAx_CHANNELy(DEV_SPI2_TX_DMA_NUMBER, DEV_SPI2_TX_DMA_CHANNEL)
    #define SPI2_TX_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_SPI2_TX_DMA_NUMBER, DEV_SPI2_TX_DMA_CHANNEL)
    #define SPI2_TX_DMA_Channel     DEV_SPI2_TX_DMA_CHANNEL
    #define SPI2_TX_DMA_Priority    DEV_SPI2_TX_DMA_PRIORITY

    #define SPI2_TX_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_SPI2_TX_DMA_NUMBER, DEV_SPI2_TX_DMA_CHANNEL)
  #endif

  #if (DEV_SPI2_MISO == 1)
    #define USE_SPI2_MISO_Pin       1U
    #define SPI2_MISO_GPIOx         DEV_SPI2_MISO_PORT
    #define SPI2_MISO_GPIO_Pin      DEV_SPI2_MISO_BIT
  #endif

  #if (DEV_SPI2_MOSI == 1)
    #define USE_SPI2_MOSI_Pin       1U
    #define SPI2_MOSI_GPIOx         DEV_SPI2_MOSI_PORT
    #define SPI2_MOSI_GPIO_Pin      DEV_SPI2_MOSI_BIT
  #endif

  #define USE_SPI2_SCK_Pin          1U
  #define SPI2_SCK_GPIOx            DEV_SPI2_SCK_PORT
  #define SPI2_SCK_GPIO_Pin         DEV_SPI2_SCK_BIT

  #if (DEV_SPI2_NSS == 1)
    #define USE_SPI2_NSS_Pin        1U
    #define SPI2_NSS_GPIOx          DEV_SPI2_NSS_PORT
    #define SPI2_NSS_GPIO_Pin       DEV_SPI2_NSS_BIT
  #endif

  #define SPI2_REMAP_DEF            AFIO_UNAVAILABLE_REMAP
  #define SPI2_REMAP                AFIO_UNAVAILABLE_REMAP
#endif

/* SPI3 configuration definitions */
#if (DEV_SPI3 == 1)

  #if defined (STM32F100xB) ||                          \
      defined (STM32F101x6) || defined (STM32F101xB) || \
      defined (STM32F102x6) || defined (STM32F102xB) || \
      defined (STM32F103x6) || defined (STM32F103xB)
    #error "SPI3 is not available for selected device!"
  #endif

  #define USE_SPI3

  #if (DEV_SPI3_RX_DMA == 1)
    #define SPI3_RX_DMA_Instance    DMAx_CHANNELy(DEV_SPI3_RX_DMA_NUMBER, DEV_SPI3_RX_DMA_CHANNEL)
    #define SPI3_RX_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_SPI3_RX_DMA_NUMBER, DEV_SPI3_RX_DMA_CHANNEL)
    #define SPI3_RX_DMA_Channel     DEV_SPI3_RX_DMA_CHANNEL
    #define SPI3_RX_DMA_Priority    DEV_SPI3_RX_DMA_PRIORITY

    #define SPI3_RX_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_SPI3_RX_DMA_NUMBER, DEV_SPI3_RX_DMA_CHANNEL)
  #endif
  #if (DEV_SPI3_TX_DMA == 1)
    #define SPI3_TX_DMA_Instance    DMAx_CHANNELy(DEV_SPI3_TX_DMA_NUMBER, DEV_SPI3_TX_DMA_CHANNEL)
    #define SPI3_TX_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_SPI3_TX_DMA_NUMBER, DEV_SPI3_TX_DMA_CHANNEL)
    #define SPI3_TX_DMA_Channel     DEV_SPI3_TX_DMA_CHANNEL
    #define SPI3_TX_DMA_Priority    DEV_SPI3_TX_DMA_PRIORITY

    #define SPI3_TX_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_SPI3_TX_DMA_NUMBER, DEV_SPI3_TX_DMA_CHANNEL)
  #endif

  #if (DEV_SPI3_MISO == 1)
    #define USE_SPI3_MISO_Pin       1U
    #define SPI3_MISO_GPIOx         DEV_SPI3_MISO_PORT
    #define SPI3_MISO_GPIO_Pin      DEV_SPI3_MISO_BIT
  #endif

  #if (DEV_SPI3_MOSI == 1)
    #define USE_SPI3_MOSI_Pin       1U
    #define SPI3_MOSI_GPIOx         DEV_SPI3_MOSI_PORT
    #define SPI3_MOSI_GPIO_Pin      DEV_SPI3_MOSI_BIT
  #endif

  #define USE_SPI3_SCK_Pin          1U
  #define SPI3_SCK_GPIOx            DEV_SPI3_SCK_PORT
  #define SPI3_SCK_GPIO_Pin         DEV_SPI3_SCK_BIT

  #if (DEV_SPI3_NSS == 1)
    #define USE_SPI3_NSS_Pin        1U
    #define SPI3_NSS_GPIOx          DEV_SPI3_NSS_PORT
    #define SPI3_NSS_GPIO_Pin       DEV_SPI3_NSS_BIT
  #endif

  #if defined(STM32F105xC) || defined(STM32F107xC)
    /* SPI3 remap is available only in connectivity line devices */
    #define SPI3_REMAP_DEF          AFIO_SPI3_NO_REMAP
    #define SPI3_REMAP              DEV_SPI3_AF_REMAP
  #else
    #if (DEV_SPI3_REMAP != 0)
      #error "SPI3 remap is available only in connectivity line devices!"
    #endif
    #define SPI3_REMAP_DEF          AFIO_UNAVAILABLE_REMAP
    #define SPI3_REMAP              AFIO_UNAVAILABLE_REMAP
  #endif
#endif

#ifdef USE_SPI1
#if (defined(SPI1_RX_DMA_Instance) || defined(SPI1_TX_DMA_Instance))
#ifndef SPI1_RX_DMA_Instance
  #error "SPI1 using DMA requires Rx and Tx DMA channel enabled in device_config.h!"
#endif
#ifndef SPI1_TX_DMA_Instance
  #error "SPI1 using DMA requires Rx and Tx DMA channel enabled in device_config.h!"
#endif
#endif
#endif

#ifdef USE_SPI2
#if (defined(SPI2_RX_DMA_Instance) || defined(SPI2_TX_DMA_Instance))
#ifndef SPI2_RX_DMA_Instance
  #error "SPI2 using DMA requires Rx and Tx DMA channel enabled in device_config.h!"
#endif
#ifndef SPI2_TX_DMA_Instance
  #error "SPI2 using DMA requires Rx and Tx DMA channel enabled in device_config.h!"
#endif
#endif
#endif

#ifdef USE_SPI3
#if (defined(SPI3_RX_DMA_Instance) || defined(SPI3_TX_DMA_Instance))
#ifndef SPI3_RX_DMA_Instance
  #error "SPI3 using DMA requires Rx and Tx DMA channel enabled in device_config.h!"
#endif
#ifndef SPI3_TX_DMA_Instance
  #error "SPI3 using DMA requires Rx and Tx DMA channel enabled in device_config.h!"
#endif
#endif
#endif


#if ((defined(USE_SPI1) && defined(SPI1_RX_DMA_Instance)) || \
     (defined(USE_SPI2) && defined(SPI2_RX_DMA_Instance)) || \
     (defined(USE_SPI3) && defined(SPI3_RX_DMA_Instance)))
#define __SPI_DMA_RX
#endif
#if ((defined(USE_SPI1) && defined(SPI1_TX_DMA_Instance)) || \
     (defined(USE_SPI2) && defined(SPI2_TX_DMA_Instance)) || \
     (defined(USE_SPI3) && defined(SPI3_TX_DMA_Instance)))
#define __SPI_DMA_TX
#endif
#if (defined(__SPI_DMA_RX) && defined(__SPI_DMA_TX))
#define __SPI_DMA
#endif


// Current driver status flag definition
#define SPI_INITIALIZED           ((uint8_t)(1U << 0U))   // SPI initialized
#define SPI_POWERED               ((uint8_t)(1U << 1U))   // SPI powered on
#define SPI_CONFIGURED            ((uint8_t)(1U << 2U))   // SPI configured
#define SPI_DATA_LOST             ((uint8_t)(1U << 3U))   // SPI data lost occurred
#define SPI_MODE_FAULT            ((uint8_t)(1U << 4U))   // SPI mode fault occurred

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* SPI Dma */
typedef const DMA_INFO SPI_DMA;

// SPI pin
typedef const struct _SPI_PIN {
  GPIO_PORT_t           port;           // Port
  GPIO_PIN_t            pin;            // Pin
} SPI_PIN;

// SPI Input/Output Configuration
typedef const struct _SPI_IO {
  SPI_PIN              *mosi;           // Pointer to MOSI pin configuration
  SPI_PIN              *miso;           // Pointer to MISO pin configuration
  SPI_PIN              *nss;            // Pointer to NSS pin configuration
  SPI_PIN              *sck;            // Pointer to SCK pin configuration
  AFIO_REMAP            afio_def;       // Default pin remapping setting
  AFIO_REMAP            afio;           // Pin remapping information
} SPI_IO;

typedef struct _SPI_STATUS {
  uint8_t busy;                         // Transmitter/Receiver busy flag
  uint8_t data_lost;                    // Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint8_t mode_fault;                   // Mode fault detected; optional (cleared on start of transfer operation)
} SPI_STATUS;

// SPI Information (Run-time)
typedef struct _SPI_INFO {
  ARM_SPI_SignalEvent_t cb_event;       // Event Callback
  SPI_STATUS            status;         // Status flags
  uint8_t               state;          // Current SPI state
  uint32_t              mode;           // Current SPI mode
} SPI_INFO;

// SPI Transfer Information (Run-Time)
typedef struct _SPI_TRANSFER_INFO {
  uint32_t              num;            // Total number of transfers
  uint8_t              *rx_buf;         // Pointer to in data buffer
  uint8_t              *tx_buf;         // Pointer to out data buffer
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              tx_cnt;         // Number of data sent
  uint32_t              dump_val;       // Variable for dumping DMA data
  uint16_t              def_val;        // Default transfer value
} SPI_TRANSFER_INFO;


// SPI Resources definition
typedef struct {
  SPI_TypeDef          *reg;            // SPI peripheral pointer
  RCC_Periph_t          periph;         // Peripheral
  SPI_IO                io;             // SPI Input/Output pins
  IRQn_Type             irq_num;        // SPI IRQ Number
  SPI_DMA              *rx_dma;         // Receive stream register interface
  SPI_DMA              *tx_dma;         // Transmit stream register interface
  SPI_INFO             *info;           // Run-Time Information
  SPI_TRANSFER_INFO    *xfer;           // SPI transfer information
} SPI_RESOURCES;

#endif /* SPI_STM32F1XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
