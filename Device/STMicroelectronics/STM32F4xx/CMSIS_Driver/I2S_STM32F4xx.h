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
 * Project: I2S Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef I2S_STM32F4XX_H_
#define I2S_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#include "asm/stm32f4xx.h"
#include "asm/RCC_STM32F4xx.h"
#include "asm/GPIO_STM32F4xx.h"
#include "asm/DMA_STM32F4xx.h"

#include "CMSIS/Driver/Driver_SAI.h"

#include "device_config.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#if ((defined(RTE_Drivers_SPI2) || \
      defined(RTE_Drivers_SPI3))   \
     && (RTE_SPI2 == 0)            \
     && (RTE_SPI3 == 0))
  #error "SPI not configured in RTE_Device.h!"
#endif

/* I2S2 configuration definitions */
#if defined (RTE_I2S2) && (RTE_I2S2 == 1)

  #if !defined(SPI2)
    #error "I2S2 not available for selected device!"
  #endif

  #define USE_I2S2

  #if (RTE_I2S2_RX_DMA == 1)
    #define I2S2_RX_DMA_Stream      DMAx_STREAMy(RTE_I2S2_RX_DMA_NUMBER, RTE_I2S2_RX_DMA_STREAM)
    #define I2S2_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_I2S2_RX_DMA_NUMBER, RTE_I2S2_RX_DMA_STREAM)
    #define I2S2_RX_DMA_Channel     DMA_CHANNEL_x(RTE_I2S2_RX_DMA_CHANNEL)
    #define I2S2_RX_DMA_Priority    DMA_PRIORITY(RTE_I2S2_RX_DMA_PRIORITY)
    #define I2S2_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_I2S2_RX_DMA_NUMBER, RTE_I2S2_RX_DMA_STREAM)
  #endif
  #if (RTE_I2S2_TX_DMA == 1)
    #define I2S2_TX_DMA_Stream      DMAx_STREAMy(RTE_I2S2_TX_DMA_NUMBER, RTE_I2S2_TX_DMA_STREAM)
    #define I2S2_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_I2S2_TX_DMA_NUMBER, RTE_I2S2_TX_DMA_STREAM)
    #define I2S2_TX_DMA_Channel     DMA_CHANNEL_x(RTE_I2S2_TX_DMA_CHANNEL)
    #define I2S2_TX_DMA_Priority    DMA_PRIORITY(RTE_I2S2_TX_DMA_PRIORITY)
    #define I2S2_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_I2S2_TX_DMA_NUMBER, RTE_I2S2_TX_DMA_STREAM)
  #endif

  #define I2S2_MCLK_GPIO_PORT       RTE_I2S2_MCLK_PORT
  #define I2S2_MCLK_GPIO_PIN        RTE_I2S2_MCLK_PIN
  #define I2S2_MCLK_GPIO_FUNC       RTE_I2S2_MCLK_FUNC
  #define I2S2_BCLK_GPIO_PORT       RTE_I2S2_BCLK_PORT
  #define I2S2_BCLK_GPIO_PIN        RTE_I2S2_BCLK_PIN
  #define I2S2_BCLK_GPIO_FUNC       RTE_I2S2_BCLK_FUNC
  #define I2S2_WCLK_GPIO_PORT       RTE_I2S2_WCLK_PORT
  #define I2S2_WCLK_GPIO_PIN        RTE_I2S2_WCLK_PIN
  #define I2S2_WCLK_GPIO_FUNC       RTE_I2S2_WCLK_FUNC
  #define I2S2_DIN_GPIO_PORT        RTE_I2S2_DIN_PORT
  #define I2S2_DIN_GPIO_PIN         RTE_I2S2_DIN_PIN
  #define I2S2_DIN_GPIO_FUNC        RTE_I2S2_DIN_FUNC
  #define I2S2_DOUT_GPIO_PORT       RTE_I2S2_DOUT_PORT
  #define I2S2_DOUT_GPIO_PIN        RTE_I2S2_DOUT_PIN
  #define I2S2_DOUT_GPIO_FUNC       RTE_I2S2_DOUT_FUNC
#endif

/* I2S3 configuration definitions */
#if defined (RTE_I2S3) && (RTE_I2S3 == 1)

  #if !defined(SPI3)
    #error "I2S3 not available for selected device!"
  #endif

  #define USE_I2S3

  #if (RTE_I2S3_RX_DMA == 1)
    #define I2S3_RX_DMA_Stream      DMAx_STREAMy(RTE_I2S3_RX_DMA_NUMBER, RTE_I2S3_RX_DMA_STREAM)
    #define I2S3_RX_DMA_Channel     DMA_CHANNEL_x(RTE_I2S3_RX_DMA_CHANNEL)
    #define I2S3_RX_DMA_Priority    DMA_PRIORITY(RTE_I2S3_RX_DMA_PRIORITY)
    #define I2S3_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_I2S3_RX_DMA_NUMBER, RTE_I2S3_RX_DMA_STREAM)
    #define I2S3_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_I2S3_RX_DMA_NUMBER, RTE_I2S3_RX_DMA_STREAM)
  #endif
  #if (RTE_I2S3_TX_DMA == 1)
    #define I2S3_TX_DMA_Stream      DMAx_STREAMy(RTE_I2S3_TX_DMA_NUMBER, RTE_I2S3_TX_DMA_STREAM)
    #define I2S3_TX_DMA_Channel     DMA_CHANNEL_x(RTE_I2S3_TX_DMA_CHANNEL)
    #define I2S3_TX_DMA_Priority    DMA_PRIORITY(RTE_I2S3_TX_DMA_PRIORITY)
    #define I2S3_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_I2S3_TX_DMA_NUMBER, RTE_I2S3_TX_DMA_STREAM)
    #define I2S3_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_I2S3_TX_DMA_NUMBER, RTE_I2S3_TX_DMA_STREAM)
  #endif

  #define I2S3_MCLK_GPIO_PORT       RTE_I2S3_MCLK_PORT
  #define I2S3_MCLK_GPIO_PIN        RTE_I2S3_MCLK_PIN
  #define I2S3_MCLK_GPIO_FUNC       RTE_I2S3_MCLK_FUNC
  #define I2S3_BCLK_GPIO_PORT       RTE_I2S3_BCLK_PORT
  #define I2S3_BCLK_GPIO_PIN        RTE_I2S3_BCLK_PIN
  #define I2S3_BCLK_GPIO_FUNC       RTE_I2S3_BCLK_FUNC
  #define I2S3_WCLK_GPIO_PORT       RTE_I2S3_WCLK_PORT
  #define I2S3_WCLK_GPIO_PIN        RTE_I2S3_WCLK_PIN
  #define I2S3_WCLK_GPIO_FUNC       RTE_I2S3_WCLK_FUNC
  #define I2S3_DIN_GPIO_PORT        RTE_I2S3_DIN_PORT
  #define I2S3_DIN_GPIO_PIN         RTE_I2S3_DIN_PIN
  #define I2S3_DIN_GPIO_FUNC        RTE_I2S3_DIN_FUNC
  #define I2S3_DOUT_GPIO_PORT       RTE_I2S3_DOUT_PORT
  #define I2S3_DOUT_GPIO_PIN        RTE_I2S3_DOUT_PIN
  #define I2S3_DOUT_GPIO_FUNC       RTE_I2S3_DOUT_FUNC
#endif

#if (RTE_I2S2_RX_DMA == 1) || (RTE_I2S3_RX_DMA == 1)
  #define I2S_RX_DMA
#endif

#if (RTE_I2S2_TX_DMA == 1) || (RTE_I2S3_TX_DMA == 1)
  #define I2S_TX_DMA
#endif

/* Current driver status flag definition */
#define I2S_FLAG_INITIALIZED        (1U << 0) // I2S Initialized
#define I2S_FLAG_POWERED            (1U << 1) // I2S powered on
#define I2S_FLAG_CONFIGURED         (1U << 2) // I2S is configured
#define I2S_FLAG_TX_ENABLE          (1U << 3)
#define I2S_FLAG_RX_ENABLE          (1U << 4)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* SAI Frequency parameters */
typedef struct I2S_FreqParam_s {
  uint32_t freq;    // Audio sample rate
  uint32_t plln;    // Multiplication factor for I2S PLL VCO. Must be between 100 and 432
  uint32_t pllr;    // Division factor for I2S PLL. Must be between 2 and 7
} I2S_FreqParam_t;

/* SAI Input/Output Configuration */
typedef const struct _I2S_IO {
  GPIO_PORT_t           mclk_port;          // MCLK IO port
  GPIO_PIN_t            mclk_pin;           // MCLK IO pin
  GPIO_PIN_FUNC_t       mclk_func;          // MCLK AF pin configuration
  GPIO_PORT_t           bclk_port;          // BCLK IO port
  GPIO_PIN_t            bclk_pin;           // BCLK IO pin
  GPIO_PIN_FUNC_t       bclk_func;          // BCLK AF pin configuration
  GPIO_PORT_t           wclk_port;          // WCLK IO port
  GPIO_PIN_t            wclk_pin;           // WCLK IO pin
  GPIO_PIN_FUNC_t       wclk_func;          // WCLK AF pin configuration
  GPIO_PORT_t           din_port;           // DIN IO port
  GPIO_PIN_t            din_pin;            // DIN IO pin
  GPIO_PIN_FUNC_t       din_func;           // DIN AF pin configuration
  GPIO_PORT_t           dout_port;          // DOUT IO port
  GPIO_PIN_t            dout_pin;           // DOUT IO pin
  GPIO_PIN_FUNC_t       dout_func;          // DOUT AF pin configuration
} I2S_IO;

/* I2S Transfer Information (Run-Time) */
typedef struct _I2S_TRANSFER_INFO {
  uint32_t              num;                // Total number of data to be transmited/received
  uint16_t             *buf;                // Pointer to data buffer
  uint32_t              cnt;                // Number of data transmited/receive
  uint8_t               data_bits;          // Number of data bits
  uint8_t               master;             // Master flag
} I2S_TRANSFER_INFO;

typedef struct _I2S_STATUS {
  uint8_t               tx_busy;            // Transmitter busy flag
  uint8_t               rx_busy;            // Receiver busy flag
  uint8_t               tx_underflow;       // Transmit data underflow detected (cleared on start of next send operation)
  uint8_t               rx_overflow;        // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t               frame_error;        // Sync Frame error detected (cleared on start of next send/receive operation)
} I2S_STATUS;

/* SAI Information (Run-Time) */
typedef struct _I2S_INFO {
  ARM_SAI_SignalEvent_t cb_event;           // Event Callback
  I2S_STATUS            status;             // Status flags
  I2S_TRANSFER_INFO     tx;                 // Transmit information
  I2S_TRANSFER_INFO     rx;                 // Receive information
  uint8_t               flags;              // Current state flags
} I2S_INFO;

/* SAI Resource Configuration */
typedef struct _I2S_RESOURSES {
  SPI_TypeDef          *tx_reg;             // SPI peripheral register interface
  SPI_TypeDef          *rx_reg;             // SPI peripheral register interface
  I2S_IO                io;                 // I2S Input/Output pins
  DMA_Resources_t      *tx_dma;             // Transmit stream register interface
  DMA_Resources_t      *rx_dma;             // Receive stream register interface
  IRQn_Type             irq_num;            // SPI IRQ Number
  RCC_Periph_t          rcc;                // RCC registers
  I2S_INFO             *info;               // Run-Time information
} const I2S_RESOURCES;

#endif /* I2S_STM32F4XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
