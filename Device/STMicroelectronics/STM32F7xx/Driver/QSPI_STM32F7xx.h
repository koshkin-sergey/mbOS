/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: QUAD SPI Driver Definitions for STMicroelectronics STM32F7xx
 */

#ifndef QSPI_STM32F7XX_H_
#define QSPI_STM32F7XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "stm32f7xx.h"
#include "RCC_STM32F7xx.h"
#include "GPIO_STM32F7xx.h"
#include "DMA_STM32F7xx.h"

#include "Driver_QSPI.h"

#include "device_config.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* QSPI0 configuration definitions */
#if (DEV_QSPI0 == 1)
  #define USE_QSPI0

  #if !defined(QUADSPI)
    #error "QUADSPI not available for selected device!"
    #undef USE_QSPI0
  #endif

  #if (DEV_QSPI0_DMA == 1)
    #define QSPI0_DMA_Stream        DMAx_STREAMy(DEV_QSPI0_DMA_NUMBER, DEV_QSPI0_DMA_STREAM)
    #define QSPI0_DMA_IRQn          DMAx_STREAMy_IRQn(DEV_QSPI0_DMA_NUMBER, DEV_QSPI0_DMA_STREAM)
    #define QSPI0_DMA_Channel       DMA_CHANNEL_x(DEV_QSPI0_DMA_CHANNEL)
    #define QSPI0_DMA_Priority      DMA_PRIORITY(DEV_QSPI0_DMA_PRIORITY)
    #define QSPI0_DMA_Handler       DMAx_STREAMy_IRQ(DEV_QSPI0_DMA_NUMBER, DEV_QSPI0_DMA_STREAM)
  #endif

  #if (DEV_QSPI0_BK1_IO0 == 1)
    #define USE_QSPI0_BK1_IO0_Pin   1U
    #define QSPI0_BK1_IO0_GPIO_PORT DEV_QSPI0_BK1_IO0_PORT
    #define QSPI0_BK1_IO0_GPIO_PIN  DEV_QSPI0_BK1_IO0_PIN
    #define QSPI0_BK1_IO0_GPIO_FUNC DEV_QSPI0_BK1_IO0_FUNC
  #endif

  #if (DEV_QSPI0_BK1_IO1 == 1)
    #define USE_QSPI0_BK1_IO1_Pin   1U
    #define QSPI0_BK1_IO1_GPIO_PORT DEV_QSPI0_BK1_IO1_PORT
    #define QSPI0_BK1_IO1_GPIO_PIN  DEV_QSPI0_BK1_IO1_PIN
    #define QSPI0_BK1_IO1_GPIO_FUNC DEV_QSPI0_BK1_IO1_FUNC
  #endif

  #if (DEV_QSPI0_BK1_IO2 == 1)
    #define USE_QSPI0_BK1_IO2_Pin   1U
    #define QSPI0_BK1_IO2_GPIO_PORT DEV_QSPI0_BK1_IO2_PORT
    #define QSPI0_BK1_IO2_GPIO_PIN  DEV_QSPI0_BK1_IO2_PIN
    #define QSPI0_BK1_IO2_GPIO_FUNC DEV_QSPI0_BK1_IO2_FUNC
  #endif

  #if (DEV_QSPI0_BK1_IO3 == 1)
    #define USE_QSPI0_BK1_IO3_Pin   1U
    #define QSPI0_BK1_IO3_GPIO_PORT DEV_QSPI0_BK1_IO3_PORT
    #define QSPI0_BK1_IO3_GPIO_PIN  DEV_QSPI0_BK1_IO3_PIN
    #define QSPI0_BK1_IO3_GPIO_FUNC DEV_QSPI0_BK1_IO3_FUNC
  #endif

  #if (DEV_QSPI0_BK1_NCS == 1)
    #define USE_QSPI0_BK1_NCS_Pin   1U
    #define QSPI0_BK1_NCS_GPIO_PORT DEV_QSPI0_BK1_NCS_PORT
    #define QSPI0_BK1_NCS_GPIO_PIN  DEV_QSPI0_BK1_NCS_PIN
    #define QSPI0_BK1_NCS_GPIO_FUNC DEV_QSPI0_BK1_NCS_FUNC
  #endif

  #if (DEV_QSPI0_BK2_IO0 == 1)
    #define USE_QSPI0_BK2_IO0_Pin   1U
    #define QSPI0_BK2_IO0_GPIO_PORT DEV_QSPI0_BK2_IO0_PORT
    #define QSPI0_BK2_IO0_GPIO_PIN  DEV_QSPI0_BK2_IO0_PIN
    #define QSPI0_BK2_IO0_GPIO_FUNC DEV_QSPI0_BK2_IO0_FUNC
  #endif

  #if (DEV_QSPI0_BK2_IO1 == 1)
    #define USE_QSPI0_BK2_IO1_Pin   1U
    #define QSPI0_BK2_IO1_GPIO_PORT DEV_QSPI0_BK2_IO1_PORT
    #define QSPI0_BK2_IO1_GPIO_PIN  DEV_QSPI0_BK2_IO1_PIN
    #define QSPI0_BK2_IO1_GPIO_FUNC DEV_QSPI0_BK2_IO1_FUNC
  #endif

  #if (DEV_QSPI0_BK2_IO2 == 1)
    #define USE_QSPI0_BK2_IO2_Pin   1U
    #define QSPI0_BK2_IO2_GPIO_PORT DEV_QSPI0_BK2_IO2_PORT
    #define QSPI0_BK2_IO2_GPIO_PIN  DEV_QSPI0_BK2_IO2_PIN
    #define QSPI0_BK2_IO2_GPIO_FUNC DEV_QSPI0_BK2_IO2_FUNC
  #endif

  #if (DEV_QSPI0_BK2_IO3 == 1)
    #define USE_QSPI0_BK2_IO3_Pin   1U
    #define QSPI0_BK2_IO3_GPIO_PORT DEV_QSPI0_BK2_IO3_PORT
    #define QSPI0_BK2_IO3_GPIO_PIN  DEV_QSPI0_BK2_IO3_PIN
    #define QSPI0_BK2_IO3_GPIO_FUNC DEV_QSPI0_BK2_IO3_FUNC
  #endif

  #if (DEV_QSPI0_BK2_NCS == 1)
    #define USE_QSPI0_BK2_NCS_Pin   1U
    #define QSPI0_BK2_NCS_GPIO_PORT DEV_QSPI0_BK2_NCS_PORT
    #define QSPI0_BK2_NCS_GPIO_PIN  DEV_QSPI0_BK2_NCS_PIN
    #define QSPI0_BK2_NCS_GPIO_FUNC DEV_QSPI0_BK2_NCS_FUNC
  #endif

  #define USE_QSPI0_CLK_Pin         1U
  #define QSPI0_CLK_GPIO_PORT       DEV_QSPI0_CLK_PORT
  #define QSPI0_CLK_GPIO_PIN        DEV_QSPI0_CLK_PIN
  #define QSPI0_CLK_GPIO_FUNC       DEV_QSPI0_CLK_FUNC
#endif


#if (defined(USE_QSPI0) && defined(QSPI0_DMA_Handler))
  #define QSPI_DMA
#endif

#define QSPIx_EXPORT_DRIVER(x)                                                                                                                                             \
static int32_t     QSPI##x##_Initialize   (QSPI_SignalEvent_t pSignalEvent) { return QSPI_Initialize (pSignalEvent, &QSPI##x##_Resources); } \
static int32_t     QSPI##x##_Uninitialize (void)                            { return QSPI_Uninitialize (&QSPI##x##_Resources);             } \
static int32_t     QSPI##x##_PowerControl (ARM_POWER_STATE state)           { return QSPI_PowerControl (state, &QSPI##x##_Resources);      } \
static int32_t     QSPI##x##_Send         (const void *data, uint32_t num)  { return QSPI_Send (data, num, &QSPI##x##_Resources);          } \
static int32_t     QSPI##x##_Receive      (void *data, uint32_t num)        { return QSPI_Receive (data, num, &QSPI##x##_Resources);       } \
static uint32_t    QSPI##x##_GetDataCount (void)                            { return QSPI_GetDataCount (&QSPI##x##_Resources);             } \
static int32_t     QSPI##x##_Control      (uint32_t control, uint32_t arg)  { return QSPI_Control (control, arg, &QSPI##x##_Resources);    } \
static QSPI_STATUS QSPI##x##_GetStatus    (void)                            { return QSPI_GetStatus (&QSPI##x##_Resources);                } \
       void        QUADSPI_IRQHandler     (void)                            {        QSPI_IRQHandler(&QSPI##x##_Resources);                } \
                                                                                                                                             \
DRIVER_QSPI Driver_QSPI##x = {                                                                                                               \
  QSPIx_GetVersion,                                                                                                                          \
  QSPIx_GetCapabilities,                                                                                                                     \
  QSPI##x##_Initialize,                                                                                                                      \
  QSPI##x##_Uninitialize,                                                                                                                    \
  QSPI##x##_PowerControl,                                                                                                                    \
  QSPI##x##_Send,                                                                                                                            \
  QSPI##x##_Receive,                                                                                                                         \
  QSPI##x##_GetDataCount,                                                                                                                    \
  QSPI##x##_Control,                                                                                                                         \
  QSPI##x##_GetStatus                                                                                                                        \
}

#define QSPIx_DMA_ALLOC(x) \
  void QSPI##x##_DMA_Handler(void) { DMA_IRQ_Handle(&QSPI##x##_DMA, &QSPI##x##_Resources); }


/* Current driver status flag definition */
#define QSPI_INITIALIZED          ((uint8_t)(1U))          // QSPI initialized
#define QSPI_POWERED              ((uint8_t)(1U << 1))     // QSPI powered on
#define QSPI_CONFIGURED           ((uint8_t)(1U << 2))     // QSPI configured
#define QSPI_DATA_LOST            ((uint8_t)(1U << 3))     // QSPI data lost occurred

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* QSPI Pin */
typedef const struct _QSPI_PIN {
  GPIO_PORT_t               port;           // IO port
  GPIO_PIN_t                 pin;           // IO pin
  GPIO_PIN_FUNC_t           func;           // AF pin configuration
} QSPI_PIN;

/* QSPI Input/Output Configuration */
typedef const struct _SPI_IO {
  QSPI_PIN              *bk1_io0;           // Pointer to MISO pin configuration
  QSPI_PIN              *bk1_io1;           // Pointer to MOSI pin configuration
  QSPI_PIN              *bk1_io2;           // Pointer to SCK pin configuration
  QSPI_PIN              *bk1_io3;           // Pointer to SCK pin configuration
  QSPI_PIN              *bk1_ncs;           // Pointer to NSS pin configuration
  QSPI_PIN              *bk2_io0;           // Pointer to MISO pin configuration
  QSPI_PIN              *bk2_io1;           // Pointer to MOSI pin configuration
  QSPI_PIN              *bk2_io2;           // Pointer to SCK pin configuration
  QSPI_PIN              *bk2_io3;           // Pointer to SCK pin configuration
  QSPI_PIN              *bk2_ncs;           // Pointer to NSS pin configuration
  QSPI_PIN                  *clk;           // Pointer to NSS pin configuration
} QSPI_IO;

typedef struct _QSPI_STATUS {
  uint8_t                   busy;           // Transmitter/Receiver busy flag
  uint8_t              data_lost;           // Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
} QSPI_STATUS;

/* QSPI Information (Run-Time) */
typedef struct _QSPI_INFO {
  QSPI_SignalEvent_t    cb_event;           // Event Callback
  QSPI_STATUS             status;           // Status flags
  uint8_t                  state;           // Current QSPI state
  uint32_t                  mode;           // Current QSPI mode
} QSPI_INFO;

/* QSPI Transfer Information (Run-Time) */
typedef struct _QSPI_TRANSFER_INFO {
  uint32_t                   num;           // Total number of transfers
  uint32_t                   cnt;           // Number of data transfered
  uint8_t                   *buf;           // Pointer to data buffer
} QSPI_TRANSFER_INFO;

/* QSPI Resource Configuration */
typedef struct _QSPI_RESOURSES {
  QUADSPI_TypeDef           *reg;           // QSPI peripheral register interface
  QSPI_IO                     io;           // QSPI Input/Output pins
  RCC_Periph_t               rcc;           // RCC registers
  IRQn_Type              irq_num;           // QSPI IRQ Number
  DMA_Resources_t           *dma;           // Transmit stream register interface
  QSPI_INFO                *info;           // Run-Time information
  QSPI_TRANSFER_INFO       *xfer;           // QSPI transfer information
} const QSPI_RESOURCES;

#endif /* QSPI_STM32F7XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
