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
 * Project: SPI Driver Definitions for STMicroelectronics STM32F7xx
 */

#ifndef SPI_STM32F7XX_H_
#define SPI_STM32F7XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#include <asm/stm32f7xx.h>
#include <Driver/RCC_STM32F7xx.h>
#include <Driver/GPIO_STM32F7xx.h>
#include <Driver/DMA_STM32F7xx.h>

#include <Driver/Driver_SPI.h>

#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* SPI1 configuration definitions */
#if (DEV_SPI1 == 1)
  #define USE_SPI1

  #if !defined(SPI1)
    #error "SPI1 not available for selected device!"
    #undef USE_SPI1
  #endif

  #if (DEV_SPI1_RX_DMA == 1)
    #define SPI1_RX_DMA_Stream      DMAx_STREAMy(DEV_SPI1_RX_DMA_NUMBER, DEV_SPI1_RX_DMA_STREAM)
    #define SPI1_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI1_RX_DMA_NUMBER, DEV_SPI1_RX_DMA_STREAM)
    #define SPI1_RX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI1_RX_DMA_CHANNEL)
    #define SPI1_RX_DMA_Priority    DMA_PRIORITY(DEV_SPI1_RX_DMA_PRIORITY)
  #endif
  #if (DEV_SPI1_TX_DMA == 1)
    #define SPI1_TX_DMA_Stream      DMAx_STREAMy(DEV_SPI1_TX_DMA_NUMBER, DEV_SPI1_TX_DMA_STREAM)
    #define SPI1_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI1_TX_DMA_NUMBER, DEV_SPI1_TX_DMA_STREAM)
    #define SPI1_TX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI1_TX_DMA_CHANNEL)
    #define SPI1_TX_DMA_Priority    DMA_PRIORITY(DEV_SPI1_TX_DMA_PRIORITY)
  #endif

  #if (DEV_SPI1_MISO == 1)
    #define USE_SPI1_MISO_Pin       1U
    #define SPI1_MISO_GPIO_PORT     DEV_SPI1_MISO_PORT
    #define SPI1_MISO_GPIO_PIN      DEV_SPI1_MISO_PIN
    #define SPI1_MISO_GPIO_FUNC     DEV_SPI1_MISO_FUNC
  #endif

  #if (DEV_SPI1_MOSI == 1)
    #define USE_SPI1_MOSI_Pin       1U
    #define SPI1_MOSI_GPIO_PORT     DEV_SPI1_MOSI_PORT
    #define SPI1_MOSI_GPIO_PIN      DEV_SPI1_MOSI_PIN
    #define SPI1_MOSI_GPIO_FUNC     DEV_SPI1_MOSI_FUNC
  #endif

  #define USE_SPI1_SCK_Pin          1U
  #define SPI1_SCK_GPIO_PORT        DEV_SPI1_SCK_PORT
  #define SPI1_SCK_GPIO_PIN         DEV_SPI1_SCK_PIN
  #define SPI1_SCK_GPIO_FUNC        DEV_SPI1_SCK_FUNC

  #if (DEV_SPI1_NSS == 1)
    #define USE_SPI1_NSS_Pin        1U
    #define SPI1_NSS_GPIO_PORT      DEV_SPI1_NSS_PORT
    #define SPI1_NSS_GPIO_PIN       DEV_SPI1_NSS_PIN
    #define SPI1_NSS_GPIO_FUNC      DEV_SPI1_NSS_FUNC
  #endif
#endif

/* SPI2 configuration definitions */
#if (DEV_SPI2 == 1)
  #define USE_SPI2

  #if !defined(SPI2)
    #error "SPI2 not available for selected device!"
    #undef USE_SPI2
  #endif

  #if (DEV_SPI2_RX_DMA == 1)
    #define SPI2_RX_DMA_Stream      DMAx_STREAMy(DEV_SPI2_RX_DMA_NUMBER, DEV_SPI2_RX_DMA_STREAM)
    #define SPI2_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI2_RX_DMA_NUMBER, DEV_SPI2_RX_DMA_STREAM)
    #define SPI2_RX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI2_RX_DMA_CHANNEL)
    #define SPI2_RX_DMA_Priority    DMA_PRIORITY(DEV_SPI2_RX_DMA_PRIORITY)
  #endif
  #if (DEV_SPI2_TX_DMA == 1)
    #define SPI2_TX_DMA_Stream      DMAx_STREAMy(DEV_SPI2_TX_DMA_NUMBER, DEV_SPI2_TX_DMA_STREAM)
    #define SPI2_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI2_TX_DMA_NUMBER, DEV_SPI2_TX_DMA_STREAM)
    #define SPI2_TX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI2_TX_DMA_CHANNEL)
    #define SPI2_TX_DMA_Priority    DMA_PRIORITY(DEV_SPI2_TX_DMA_PRIORITY)
  #endif

  #if (DEV_SPI2_MISO == 1)
    #define USE_SPI2_MISO_Pin       1U
    #define SPI2_MISO_GPIO_PORT     DEV_SPI2_MISO_PORT
    #define SPI2_MISO_GPIO_PIN      DEV_SPI2_MISO_PIN
    #define SPI2_MISO_GPIO_FUNC     DEV_SPI2_MISO_FUNC
  #endif

  #if (DEV_SPI2_MOSI == 1)
    #define USE_SPI2_MOSI_Pin       1U
    #define SPI2_MOSI_GPIO_PORT     DEV_SPI2_MOSI_PORT
    #define SPI2_MOSI_GPIO_PIN      DEV_SPI2_MOSI_PIN
    #define SPI2_MOSI_GPIO_FUNC     DEV_SPI2_MOSI_FUNC
  #endif

  #define USE_SPI2_SCK_Pin          1U
  #define SPI2_SCK_GPIO_PORT        DEV_SPI2_SCK_PORT
  #define SPI2_SCK_GPIO_PIN         DEV_SPI2_SCK_PIN
  #define SPI2_SCK_GPIO_FUNC        DEV_SPI2_SCK_FUNC

  #if (DEV_SPI2_NSS == 1)
    #define USE_SPI2_NSS_Pin        1U
    #define SPI2_NSS_GPIO_PORT      DEV_SPI2_NSS_PORT
    #define SPI2_NSS_GPIO_PIN       DEV_SPI2_NSS_PIN
    #define SPI2_NSS_GPIO_FUNC      DEV_SPI2_NSS_FUNC
  #endif
#endif

/* SPI3 configuration definitions */
#if (DEV_SPI3 == 1)
  #define USE_SPI3

  #if !defined(SPI3)
    #error "SPI3 not available for selected device!"
    #undef USE_SPI3
  #endif

  #if (DEV_SPI3_RX_DMA == 1)
    #define SPI3_RX_DMA_Stream      DMAx_STREAMy(DEV_SPI3_RX_DMA_NUMBER, DEV_SPI3_RX_DMA_STREAM)
    #define SPI3_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI3_RX_DMA_NUMBER, DEV_SPI3_RX_DMA_STREAM)
    #define SPI3_RX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI3_RX_DMA_CHANNEL)
    #define SPI3_RX_DMA_Priority    DMA_PRIORITY(DEV_SPI3_RX_DMA_PRIORITY)
  #endif
  #if (DEV_SPI3_TX_DMA == 1)
    #define SPI3_TX_DMA_Stream      DMAx_STREAMy(DEV_SPI3_TX_DMA_NUMBER, DEV_SPI3_TX_DMA_STREAM)
    #define SPI3_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI3_TX_DMA_NUMBER, DEV_SPI3_TX_DMA_STREAM)
    #define SPI3_TX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI3_TX_DMA_CHANNEL)
    #define SPI3_TX_DMA_Priority    DMA_PRIORITY(DEV_SPI3_TX_DMA_PRIORITY)
  #endif

  #if (DEV_SPI3_MISO == 1)
    #define USE_SPI3_MISO_Pin       1U
    #define SPI3_MISO_GPIO_PORT     DEV_SPI3_MISO_PORT
    #define SPI3_MISO_GPIO_PIN      DEV_SPI3_MISO_PIN
    #define SPI3_MISO_GPIO_FUNC     DEV_SPI3_MISO_FUNC
  #endif

  #if (DEV_SPI3_MOSI == 1)
    #define USE_SPI3_MOSI_Pin       1U
    #define SPI3_MOSI_GPIO_PORT     DEV_SPI3_MOSI_PORT
    #define SPI3_MOSI_GPIO_PIN      DEV_SPI3_MOSI_PIN
    #define SPI3_MOSI_GPIO_FUNC     DEV_SPI3_MOSI_FUNC
  #endif

  #define USE_SPI3_SCK_Pin          1U
  #define SPI3_SCK_GPIO_PORT        DEV_SPI3_SCK_PORT
  #define SPI3_SCK_GPIO_PIN         DEV_SPI3_SCK_PIN
  #define SPI3_SCK_GPIO_FUNC        DEV_SPI3_SCK_FUNC

  #if (DEV_SPI3_NSS == 1)
    #define USE_SPI3_NSS_Pin        1U
    #define SPI3_NSS_GPIO_PORT      DEV_SPI3_NSS_PORT
    #define SPI3_NSS_GPIO_PIN       DEV_SPI3_NSS_PIN
    #define SPI3_NSS_GPIO_FUNC      DEV_SPI3_NSS_FUNC
  #endif
#endif

/* SPI4 configuration definitions */
#if (DEV_SPI4 == 1)
  #define USE_SPI4

  #if !defined(SPI4)
    #error "SPI4 not available for selected device!"
    #undef USE_SPI4
  #endif

  #if (DEV_SPI4_RX_DMA == 1)
    #define SPI4_RX_DMA_Stream      DMAx_STREAMy(DEV_SPI4_RX_DMA_NUMBER, DEV_SPI4_RX_DMA_STREAM)
    #define SPI4_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI4_RX_DMA_NUMBER, DEV_SPI4_RX_DMA_STREAM)
    #define SPI4_RX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI4_RX_DMA_CHANNEL)
    #define SPI4_RX_DMA_Priority    DMA_PRIORITY(DEV_SPI4_RX_DMA_PRIORITY)
  #endif
  #if (DEV_SPI4_TX_DMA == 1)
    #define SPI4_TX_DMA_Stream      DMAx_STREAMy(DEV_SPI4_TX_DMA_NUMBER, DEV_SPI4_TX_DMA_STREAM)
    #define SPI4_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI4_TX_DMA_NUMBER, DEV_SPI4_TX_DMA_STREAM)
    #define SPI4_TX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI4_TX_DMA_CHANNEL)
    #define SPI4_TX_DMA_Priority    DMA_PRIORITY(DEV_SPI4_TX_DMA_PRIORITY)
  #endif

  #if (DEV_SPI4_MISO == 1)
    #define USE_SPI4_MISO_Pin       1U
    #define SPI4_MISO_GPIO_PORT     DEV_SPI4_MISO_PORT
    #define SPI4_MISO_GPIO_PIN      DEV_SPI4_MISO_PIN
    #define SPI4_MISO_GPIO_FUNC     DEV_SPI4_MISO_FUNC
  #endif

  #if (DEV_SPI4_MOSI == 1)
    #define USE_SPI4_MOSI_Pin       1U
    #define SPI4_MOSI_GPIO_PORT     DEV_SPI4_MOSI_PORT
    #define SPI4_MOSI_GPIO_PIN      DEV_SPI4_MOSI_PIN
    #define SPI4_MOSI_GPIO_FUNC     DEV_SPI4_MOSI_FUNC
  #endif

  #define USE_SPI4_SCK_Pin          1U
  #define SPI4_SCK_GPIO_PORT        DEV_SPI4_SCK_PORT
  #define SPI4_SCK_GPIO_PIN         DEV_SPI4_SCK_PIN
  #define SPI4_SCK_GPIO_FUNC        DEV_SPI4_SCK_FUNC

  #if (DEV_SPI4_NSS == 1)
    #define USE_SPI4_NSS_Pin        1U
    #define SPI4_NSS_GPIO_PORT      DEV_SPI4_NSS_PORT
    #define SPI4_NSS_GPIO_PIN       DEV_SPI4_NSS_PIN
    #define SPI4_NSS_GPIO_FUNC      DEV_SPI4_NSS_FUNC
  #endif
#endif

/* SPI5 configuration definitions */
#if (DEV_SPI5 == 1)
  #define USE_SPI5

  #if !defined(SPI5)
    #error "SPI5 not available for selected device!"
    #undef USE_SPI5
  #endif

  #if (DEV_SPI5_RX_DMA == 1)
    #define SPI5_RX_DMA_Stream      DMAx_STREAMy(DEV_SPI5_RX_DMA_NUMBER, DEV_SPI5_RX_DMA_STREAM)
    #define SPI5_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI5_RX_DMA_NUMBER, DEV_SPI5_RX_DMA_STREAM)
    #define SPI5_RX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI5_RX_DMA_CHANNEL)
    #define SPI5_RX_DMA_Priority    DMA_PRIORITY(DEV_SPI5_RX_DMA_PRIORITY)
  #endif
  #if (DEV_SPI5_TX_DMA == 1)
    #define SPI5_TX_DMA_Stream      DMAx_STREAMy(DEV_SPI5_TX_DMA_NUMBER, DEV_SPI5_TX_DMA_STREAM)
    #define SPI5_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI5_TX_DMA_NUMBER, DEV_SPI5_TX_DMA_STREAM)
    #define SPI5_TX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI5_TX_DMA_CHANNEL)
    #define SPI5_TX_DMA_Priority    DMA_PRIORITY(DEV_SPI5_TX_DMA_PRIORITY)
  #endif

  #if (DEV_SPI5_MISO == 1)
    #define USE_SPI5_MISO_Pin       1U
    #define SPI5_MISO_GPIO_PORT     DEV_SPI5_MISO_PORT
    #define SPI5_MISO_GPIO_PIN      DEV_SPI5_MISO_PIN
    #define SPI5_MISO_GPIO_FUNC     DEV_SPI5_MISO_FUNC
  #endif

  #if (DEV_SPI5_MOSI == 1)
    #define USE_SPI5_MOSI_Pin       1U
    #define SPI5_MOSI_GPIO_PORT     DEV_SPI5_MOSI_PORT
    #define SPI5_MOSI_GPIO_PIN      DEV_SPI5_MOSI_PIN
    #define SPI5_MOSI_GPIO_FUNC     DEV_SPI5_MOSI_FUNC
  #endif

  #define USE_SPI5_SCK_Pin          1U
  #define SPI5_SCK_GPIO_PORT        DEV_SPI5_SCK_PORT
  #define SPI5_SCK_GPIO_PIN         DEV_SPI5_SCK_PIN
  #define SPI5_SCK_GPIO_FUNC        DEV_SPI5_SCK_FUNC

  #if (DEV_SPI5_NSS == 1)
    #define USE_SPI5_NSS_Pin        1U
    #define SPI5_NSS_GPIO_PORT      DEV_SPI5_NSS_PORT
    #define SPI5_NSS_GPIO_PIN       DEV_SPI5_NSS_PIN
    #define SPI5_NSS_GPIO_FUNC      DEV_SPI5_NSS_FUNC
  #endif
#endif

/* SPI6 configuration definitions */
#if (DEV_SPI6 == 1)
  #define USE_SPI6

  #if !defined(SPI6)
    #error "SPI6 not available for selected device!"
    #undef USE_SPI6
  #endif

  #if (DEV_SPI6_RX_DMA == 1)
    #define SPI6_RX_DMA_Stream      DMAx_STREAMy(DEV_SPI6_RX_DMA_NUMBER, DEV_SPI6_RX_DMA_STREAM)
    #define SPI6_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI6_RX_DMA_NUMBER, DEV_SPI6_RX_DMA_STREAM)
    #define SPI6_RX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI6_RX_DMA_CHANNEL)
    #define SPI6_RX_DMA_Priority    DMA_PRIORITY(DEV_SPI6_RX_DMA_PRIORITY)
  #endif
  #if (DEV_SPI6_TX_DMA == 1)
    #define SPI6_TX_DMA_Stream      DMAx_STREAMy(DEV_SPI6_TX_DMA_NUMBER, DEV_SPI6_TX_DMA_STREAM)
    #define SPI6_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_SPI6_TX_DMA_NUMBER, DEV_SPI6_TX_DMA_STREAM)
    #define SPI6_TX_DMA_Channel     DMA_CHANNEL_x(DEV_SPI6_TX_DMA_CHANNEL)
    #define SPI6_TX_DMA_Priority    DMA_PRIORITY(DEV_SPI6_TX_DMA_PRIORITY)
  #endif

  #if (DEV_SPI6_MISO == 1)
    #define USE_SPI6_MISO_Pin       1U
    #define SPI6_MISO_GPIO_PORT     DEV_SPI6_MISO_PORT
    #define SPI6_MISO_GPIO_PIN      DEV_SPI6_MISO_PIN
    #define SPI6_MISO_GPIO_FUNC     DEV_SPI6_MISO_FUNC
  #endif

  #if (DEV_SPI6_MOSI == 1)
    #define USE_SPI6_MOSI_Pin       1U
    #define SPI6_MOSI_GPIO_PORT     DEV_SPI6_MOSI_PORT
    #define SPI6_MOSI_GPIO_PIN      DEV_SPI6_MOSI_PIN
    #define SPI6_MOSI_GPIO_FUNC     DEV_SPI6_MOSI_FUNC
  #endif

  #define USE_SPI6_SCK_Pin          1U
  #define SPI6_SCK_GPIO_PORT        DEV_SPI6_SCK_PORT
  #define SPI6_SCK_GPIO_PIN         DEV_SPI6_SCK_PIN
  #define SPI6_SCK_GPIO_FUNC        DEV_SPI6_SCK_FUNC

  #if (DEV_SPI6_NSS == 1)
    #define USE_SPI6_NSS_Pin        1U
    #define SPI6_NSS_GPIO_PORT      DEV_SPI6_NSS_PORT
    #define SPI6_NSS_GPIO_PIN       DEV_SPI6_NSS_PIN
    #define SPI6_NSS_GPIO_FUNC      DEV_SPI6_NSS_FUNC
  #endif
#endif

#if ((defined(USE_SPI1) && defined(SPI1_RX_DMA_Stream)) || \
     (defined(USE_SPI2) && defined(SPI2_RX_DMA_Stream)) || \
     (defined(USE_SPI3) && defined(SPI3_RX_DMA_Stream)) || \
     (defined(USE_SPI4) && defined(SPI4_RX_DMA_Stream)) || \
     (defined(USE_SPI5) && defined(SPI5_RX_DMA_Stream)) || \
     (defined(USE_SPI6) && defined(SPI6_RX_DMA_Stream)))
  #define SPI_DMA_RX
#endif

#if ((defined(USE_SPI1) && defined(SPI1_TX_DMA_Stream)) || \
     (defined(USE_SPI2) && defined(SPI2_TX_DMA_Stream)) || \
     (defined(USE_SPI3) && defined(SPI3_TX_DMA_Stream)) || \
     (defined(USE_SPI4) && defined(SPI4_TX_DMA_Stream)) || \
     (defined(USE_SPI5) && defined(SPI5_TX_DMA_Stream)) || \
     (defined(USE_SPI6) && defined(SPI6_TX_DMA_Stream)))
  #define SPI_DMA_TX
#endif

#if (defined(SPI_DMA_RX) && defined(SPI_DMA_TX))
  #define SPI_DMA
#endif

#define SPIx_EXPORT_DRIVER(x)                                                                                                                                             \
static int32_t        SPI##x##_Initialize      (ARM_SPI_SignalEvent_t pSignalEvent)                { return SPI_Initialize (pSignalEvent, &SPI##x##_Resources);         } \
static int32_t        SPI##x##_Uninitialize    (void)                                              { return SPI_Uninitialize (&SPI##x##_Resources);                     } \
static int32_t        SPI##x##_PowerControl    (ARM_POWER_STATE state)                             { return SPI_PowerControl (state, &SPI##x##_Resources);              } \
static int32_t        SPI##x##_Send            (const void *data, uint32_t num)                    { return SPI_Send (data, num, &SPI##x##_Resources);                  } \
static int32_t        SPI##x##_Receive         (void *data, uint32_t num)                          { return SPI_Receive (data, num, &SPI##x##_Resources);               } \
static int32_t        SPI##x##_Transfer        (const void *data_out, void *data_in, uint32_t num) { return SPI_Transfer (data_out, data_in, num, &SPI##x##_Resources); } \
static uint32_t       SPI##x##_GetDataCount    (void)                                              { return SPI_GetDataCount (&SPI##x##_Resources);                     } \
static int32_t        SPI##x##_Control         (uint32_t control, uint32_t arg)                    { return SPI_Control (control, arg, &SPI##x##_Resources);            } \
static ARM_SPI_STATUS SPI##x##_GetStatus       (void)                                              { return SPI_GetStatus (&SPI##x##_Resources);                        } \
       void           SPI##x##_IRQHandler      (void)                                              {        SPI_IRQHandler(&SPI##x##_Resources);                        } \
                                                                                                                                                                          \
ARM_DRIVER_SPI Driver_SPI##x = {                                                                                                                                          \
  SPIx_GetVersion,                                                                                                                                                        \
  SPIx_GetCapabilities,                                                                                                                                                   \
  SPI##x##_Initialize,                                                                                                                                                    \
  SPI##x##_Uninitialize,                                                                                                                                                  \
  SPI##x##_PowerControl,                                                                                                                                                  \
  SPI##x##_Send,                                                                                                                                                          \
  SPI##x##_Receive,                                                                                                                                                       \
  SPI##x##_Transfer,                                                                                                                                                      \
  SPI##x##_GetDataCount,                                                                                                                                                  \
  SPI##x##_Control,                                                                                                                                                       \
  SPI##x##_GetStatus                                                                                                                                                      \
}

/* Current driver status flag definition */
#define SPI_INITIALIZED           ((uint8_t)(1U))          // SPI initialized
#define SPI_POWERED               ((uint8_t)(1U << 1))     // SPI powered on
#define SPI_CONFIGURED            ((uint8_t)(1U << 2))     // SPI configured
#define SPI_DATA_LOST             ((uint8_t)(1U << 3))     // SPI data lost occurred
#define SPI_MODE_FAULT            ((uint8_t)(1U << 4))     // SPI mode fault occurred

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* SPI Pin */
typedef const struct _SPI_PIN {
  GPIO_PORT_t           port;               // IO port
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
} SPI_PIN;

/* SPI Input/Output Configuration */
typedef const struct _SPI_IO {
  SPI_PIN               *miso;              // Pointer to MISO pin configuration
  SPI_PIN               *mosi;              // Pointer to MOSI pin configuration
  SPI_PIN               *sck;               // Pointer to SCK pin configuration
  SPI_PIN               *nss;               // Pointer to NSS pin configuration
} SPI_IO;

typedef struct _SPI_STATUS {
  uint8_t               busy;               // Transmitter/Receiver busy flag
  uint8_t               data_lost;          // Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint8_t               mode_fault;         // Mode fault detected; optional (cleared on start of transfer operation)
} SPI_STATUS;

/* SPI Information (Run-Time) */
typedef struct _SPI_INFO {
  ARM_SPI_SignalEvent_t cb_event;           // Event Callback
  SPI_STATUS            status;             // Status flags
  uint8_t               state;              // Current SPI state
  uint32_t              mode;               // Current SPI mode
} SPI_INFO;

/* SPI Transfer Information (Run-Time) */
typedef struct _SPI_TRANSFER_INFO {
  uint32_t              num;                // Total number of transfers
  void                 *rx_buf;             // Pointer to in data buffer
  const void           *tx_buf;             // Pointer to out data buffer
  uint32_t              rx_cnt;             // Number of data received
  uint32_t              tx_cnt;             // Number of data sent
  uint32_t              dump_val;           // Variable for dumping DMA data
  uint16_t              def_val;            // Default transfer value
  uint16_t              reserved;           // Reserved
} SPI_TRANSFER_INFO;

/* SPI Resource Configuration */
typedef struct _SPI_RESOURSES {
  SPI_TypeDef          *reg;                // SPI peripheral register interface
  SPI_IO                io;                 // SPI Input/Output pins
  RCC_Periph_t          rcc;                // RCC registers
  DMA_Resources_t      *tx_dma;             // Transmit stream register interface
  DMA_Resources_t      *rx_dma;             // Receive stream register interface
  SPI_INFO             *info;               // Run-Time information
  SPI_TRANSFER_INFO    *xfer;               // SPI transfer information
  IRQn_Type             irq_num;            // SPI IRQ Number
  uint8_t               reserved[3];        // Reserved
} const SPI_RESOURCES;

#endif /* SPI_STM32F7XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
