/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: SPI Driver Definitions for ADI ADuCM32x
 */

#ifndef SPI_ADUCM32X_H_
#define SPI_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <string.h>
#include "asm/aducm32x.h"
#include "device_config.h"
#include "Driver/Driver_SPI.h"
#include "Driver/Driver_CLK.h"
#include "Driver/Driver_DMA.h"
#include "Driver/Driver_GPIO.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* I2C0 configuration definitions */
#if defined (DEV_SPI0) && (DEV_SPI0 == 1)
  #define USE_SPI0

  #if !defined(MMR_SPI0)
    #error "SPI0 not available for selected device!"
    #undef USE_SPI0
  #endif

  #if (DEV_SPI0_MOSI != 0)
    #define USE_SPI0_MOSI             DEV_SPI0_MOSI
    #define SPI0_MOSI_GPIO_PORT       DEV_SPI0_MOSI_PORT
    #define SPI0_MOSI_GPIO_PIN        DEV_SPI0_MOSI_PIN
    #define SPI0_MOSI_GPIO_FUNC       DEV_SPI0_MOSI_FUNC
  #endif

  #if (DEV_SPI0_MISO != 0)
    #define USE_SPI0_MISO             DEV_SPI0_MISO
    #define SPI0_MISO_GPIO_PORT       DEV_SPI0_MISO_PORT
    #define SPI0_MISO_GPIO_PIN        DEV_SPI0_MISO_PIN
    #define SPI0_MISO_GPIO_FUNC       DEV_SPI0_MISO_FUNC
  #endif

  #if (DEV_SPI0_CS != 0)
    #define USE_SPI0_CS               DEV_SPI0_CS
    #define SPI0_CS_GPIO_PORT         DEV_SPI0_CS_PORT
    #define SPI0_CS_GPIO_PIN          DEV_SPI0_CS_PIN
    #define SPI0_CS_GPIO_FUNC         DEV_SPI0_CS_FUNC
  #endif

  #define SPI0_SCLK_GPIO_PORT       DEV_SPI0_SCLK_PORT
  #define SPI0_SCLK_GPIO_PIN        DEV_SPI0_SCLK_PIN
  #define SPI0_SCLK_GPIO_FUNC       DEV_SPI0_SCLK_FUNC

  #define SPI0_INT_PRIORITY         (IRQ_Priority_t)DEV_SPI0_INT_PRIO
#endif

/* I2C0 configuration definitions */
#if defined (DEV_SPI1) && (DEV_SPI1 == 1)
  #define USE_SPI1

  #if !defined(MMR_SPI1)
    #error "SPI1 not available for selected device!"
    #undef USE_SPI1
  #endif

  #if (DEV_SPI1_MOSI != 0)
    #define USE_SPI1_MOSI             DEV_SPI1_MOSI
    #define SPI1_MOSI_GPIO_PORT       DEV_SPI1_MOSI_PORT
    #define SPI1_MOSI_GPIO_PIN        DEV_SPI1_MOSI_PIN
    #define SPI1_MOSI_GPIO_FUNC       DEV_SPI1_MOSI_FUNC
  #endif

  #if (DEV_SPI1_MISO != 0)
    #define USE_SPI1_MISO             DEV_SPI1_MISO
    #define SPI1_MISO_GPIO_PORT       DEV_SPI1_MISO_PORT
    #define SPI1_MISO_GPIO_PIN        DEV_SPI1_MISO_PIN
    #define SPI1_MISO_GPIO_FUNC       DEV_SPI1_MISO_FUNC
  #endif

  #if (DEV_SPI1_CS != 0)
    #define USE_SPI1_CS               DEV_SPI1_CS
    #define SPI1_CS_GPIO_PORT         DEV_SPI1_CS_PORT
    #define SPI1_CS_GPIO_PIN          DEV_SPI1_CS_PIN
    #define SPI1_CS_GPIO_FUNC         DEV_SPI1_CS_FUNC
  #endif

  #define SPI1_SCLK_GPIO_PORT       DEV_SPI1_SCLK_PORT
  #define SPI1_SCLK_GPIO_PIN        DEV_SPI1_SCLK_PIN
  #define SPI1_SCLK_GPIO_FUNC       DEV_SPI1_SCLK_FUNC

  #define SPI1_INT_PRIORITY         (IRQ_Priority_t)DEV_SPI1_INT_PRIO
#endif

#define SPIx_EXPORT_DRIVER(x)     \
static int32_t        SPI##x##_Initialize    (SPI_SignalEvent_t cb_event)                         { return (SPI_Initialize    (cb_event,                &SPI##x##_Resources)); } \
static int32_t        SPI##x##_Uninitialize  (void)                                               { return (SPI_Uninitialize  (                         &SPI##x##_Resources)); } \
static int32_t        SPI##x##_PowerControl  (POWER_STATE state)                                  { return (SPI_PowerControl  (state,                   &SPI##x##_Resources)); } \
static int32_t        SPI##x##_Send          (const void *data, uint32_t num)                     { return (SPI_Send          (data, num,               &SPI##x##_Resources)); } \
static int32_t        SPI##x##_Receive       (      void *data, uint32_t num)                     { return (SPI_Receive       (data, num,               &SPI##x##_Resources)); } \
static int32_t        SPI##x##_Transfer      (const void *data_out, void *data_in, uint32_t num)  { return (SPI_Transfer      (data_out, data_in, num,  &SPI##x##_Resources)); } \
static uint32_t       SPI##x##_GetDataCount  (void)                                               { return (SPI_GetDataCount  (                         &SPI##x##_Resources)); } \
static int32_t        SPI##x##_Control       (uint32_t control, uint32_t arg)                     { return (SPI_Control       (control, arg,            &SPI##x##_Resources)); } \
static SPI_STATUS     SPI##x##_GetStatus     (void)                                               { return (SPI_GetStatus     (                         &SPI##x##_Resources)); } \
       void           SPI##x##_IRQHandler    (void)                                               {         SPI_IRQHandler    (                         &SPI##x##_Resources);  } \
       void       DMA_SPI##x##_TX_IRQHandler (void)                                               {     DMA_SPI_TX_IRQHandler (                         &SPI##x##_Resources);  } \
       void       DMA_SPI##x##_RX_IRQHandler (void)                                               {     DMA_SPI_RX_IRQHandler (                         &SPI##x##_Resources);  } \
                                  \
extern                            \
DRIVER_SPI Driver_SPI##x;         \
DRIVER_SPI Driver_SPI##x = {      \
  SPI_GetVersion,                 \
  SPI_GetCapabilities,            \
  SPI##x##_Initialize,            \
  SPI##x##_Uninitialize,          \
  SPI##x##_PowerControl,          \
  SPI##x##_Send,                  \
  SPI##x##_Receive,               \
  SPI##x##_Transfer,              \
  SPI##x##_GetDataCount,          \
  SPI##x##_Control,               \
  SPI##x##_GetStatus              \
}

/* Current driver status flag definition */
#define SPI_INITIALIZED           (1U << 0)                // SPI initialized
#define SPI_POWERED               (1U << 1)                // SPI powered on
#define SPI_CONFIGURED            (1U << 2)                // SPI configured

#define SPI_DMA_ENABLE            ((uint8_t)(1U << 0))     // SPI DMA enable
#define SPI_DMA_IENTXDMA          ((uint8_t)(1U << 1))     // SPI DMA TX irq enable
#define SPI_DMA_IENRXDMA          ((uint8_t)(1U << 2))     // SPI configured

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* SPI Pin Configuration */
typedef const struct SPI_Pin {
  Driver_GPIO_t        *gpio;        // Pointer to GPIO driver
  GPIO_PIN_t            pin;         // IO pin
  GPIO_PIN_CFG_t        cfg;         // AF pin configuration
} SPI_Pin_t;

/* SPI Input/Output Configuration */
typedef const struct SPI_IO {
  SPI_Pin_t            *mosi;        // Pointer to MOSI pin configuration
  SPI_Pin_t            *miso;        // Pointer to MISO pin configuration
  SPI_Pin_t            *sclk;        // Pointer to SCLK pin configuration
  SPI_Pin_t            *cs;          // Pointer to CS   pin configuration
} SPI_IO_t;

/* SPI IRQ Configuration */
typedef const struct SPI_Irq {
  IRQn_Type             num;         // SPI IRQ Number
  IRQ_Priority_t        priority;    // SPI interrupt priority
  uint32_t              dma_en;
  IRQn_Type             dma_tx_num;  // SPI DMA TX IRQ Number
  IRQn_Type             dma_rx_num;  // SPI DMA RX IRQ Number
} SPI_Irq_t;

/* SPI Information (Run-Time) */
typedef struct SPI_Info {
  SPI_SignalEvent_t     cb_event;           // Event Callback
  SPI_STATUS            status;             // Status flags
  uint32_t              state;              // Current SPI state
  uint32_t              mode;               // Current SPI mode
} SPI_Info_t;

/* SPI Transfer Information (Run-Time) */
typedef struct _SPI_TRANSFER_INFO {
  uint32_t              num;                // Total number of transfers
  uint8_t              *rx_buf;             // Pointer to in data buffer
  uint8_t              *tx_buf;             // Pointer to out data buffer
  uint32_t              rx_cnt;             // Number of data received
  uint32_t              tx_cnt;             // Number of data sent
  uint32_t              def_val;            // Default transfer value
} SPI_TRANSFER_INFO;

/* SPI Resource Configuration */
typedef struct {
  MMR_SPI_t            *mmr;                // SPI register interface
  CLK_Periph_t          clk_periph;         // SPI clock control
  SPI_IO_t              io;                 // SPI pin configuration
  SPI_Irq_t             irq;                // SPI interrupt information
  SPI_Info_t           *info;               // Run-Time control information
  SPI_TRANSFER_INFO    *xfer;               // SPI transfer information
} const SPI_Resources_t;

#endif /* SPI_ADUCM32X_H_ */
