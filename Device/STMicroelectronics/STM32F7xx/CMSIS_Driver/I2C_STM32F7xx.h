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
 * Project: I2C Driver Definitions for STMicroelectronics STM32F7xx
 */

#ifndef I2C_STM32F7XX_H_
#define I2C_STM32F7XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>

#include "asm/stm32f7xx.h"
#include "asm/GPIO_STM32F7xx.h"
#include "asm/RCC_STM32F7xx.h"
#include "asm/DMA_STM32F7xx.h"

#include "Driver/Driver_I2C.h"

#include "device_config.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* I2C1 configuration definitions */
#if defined (DEV_I2C1) && (DEV_I2C1 == 1)
  #define USE_I2C1

  #if !defined(I2C1)
    #error "I2C1 not available for selected device!"
    #undef USE_I2C1
  #endif

  #if (DEV_I2C1_RX_DMA == 1)
    #define I2C1_RX_DMA_Stream      DMAx_STREAMy(DEV_I2C1_RX_DMA_NUMBER, DEV_I2C1_RX_DMA_STREAM)
    #define I2C1_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C1_RX_DMA_NUMBER, DEV_I2C1_RX_DMA_STREAM)
    #define I2C1_RX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C1_RX_DMA_CHANNEL)
    #define I2C1_RX_DMA_Priority    DMA_PRIORITY(DEV_I2C1_RX_DMA_PRIORITY)
  #endif
  #if (DEV_I2C1_TX_DMA == 1)
    #define I2C1_TX_DMA_Stream      DMAx_STREAMy(DEV_I2C1_TX_DMA_NUMBER, DEV_I2C1_TX_DMA_STREAM)
    #define I2C1_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C1_TX_DMA_NUMBER, DEV_I2C1_TX_DMA_STREAM)
    #define I2C1_TX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C1_TX_DMA_CHANNEL)
    #define I2C1_TX_DMA_Priority    DMA_PRIORITY(DEV_I2C1_TX_DMA_PRIORITY)
  #endif

  #define I2C1_SCL_GPIO_PORT        DEV_I2C1_SCL_PORT
  #define I2C1_SCL_GPIO_PIN         DEV_I2C1_SCL_PIN
  #define I2C1_SCL_GPIO_FUNC        DEV_I2C1_SCL_FUNC

  #define I2C1_SDA_GPIO_PORT        DEV_I2C1_SDA_PORT
  #define I2C1_SDA_GPIO_PIN         DEV_I2C1_SDA_PIN
  #define I2C1_SDA_GPIO_FUNC        DEV_I2C1_SDA_FUNC
#endif

/* I2C2 configuration definitions */
#if defined (DEV_I2C2) && (DEV_I2C2 == 1)
  #define USE_I2C2

  #if !defined(I2C2)
    #error "I2C2 not available for selected device!"
    #undef USE_I2C2
  #endif

  #if (DEV_I2C2_RX_DMA == 1)
    #define I2C2_RX_DMA_Stream      DMAx_STREAMy(DEV_I2C2_RX_DMA_NUMBER, DEV_I2C2_RX_DMA_STREAM)
    #define I2C2_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C2_RX_DMA_NUMBER, DEV_I2C2_RX_DMA_STREAM)
    #define I2C2_RX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C2_RX_DMA_CHANNEL)
    #define I2C2_RX_DMA_Priority    DMA_PRIORITY(DEV_I2C2_RX_DMA_PRIORITY)
  #endif
  #if (DEV_I2C2_TX_DMA == 1)
    #define I2C2_TX_DMA_Stream      DMAx_STREAMy(DEV_I2C2_TX_DMA_NUMBER, DEV_I2C2_TX_DMA_STREAM)
    #define I2C2_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C2_TX_DMA_NUMBER, DEV_I2C2_TX_DMA_STREAM)
    #define I2C2_TX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C2_TX_DMA_CHANNEL)
    #define I2C2_TX_DMA_Priority    DMA_PRIORITY(DEV_I2C2_TX_DMA_PRIORITY)
  #endif

  #define I2C2_SCL_GPIO_PORT        DEV_I2C2_SCL_PORT
  #define I2C2_SCL_GPIO_PIN         DEV_I2C2_SCL_PIN
  #define I2C2_SCL_GPIO_FUNC        DEV_I2C2_SCL_FUNC

  #define I2C2_SDA_GPIO_PORT        DEV_I2C2_SDA_PORT
  #define I2C2_SDA_GPIO_PIN         DEV_I2C2_SDA_PIN
  #define I2C2_SDA_GPIO_FUNC        DEV_I2C2_SDA_FUNC
#endif

/* I2C3 configuration definitions */
#if defined (DEV_I2C3) && (DEV_I2C3 == 1)
  #define USE_I2C3

  #if !defined(I2C3)
    #error "I2C3 not available for selected device!"
    #undef USE_I2C3
  #endif

  #if (DEV_I2C3_RX_DMA == 1)
    #define I2C3_RX_DMA_Stream      DMAx_STREAMy(DEV_I2C3_RX_DMA_NUMBER, DEV_I2C3_RX_DMA_STREAM)
    #define I2C3_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C3_RX_DMA_NUMBER, DEV_I2C3_RX_DMA_STREAM)
    #define I2C3_RX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C3_RX_DMA_CHANNEL)
    #define I2C3_RX_DMA_Priority    DMA_PRIORITY(DEV_I2C3_RX_DMA_PRIORITY)
  #endif
  #if (DEV_I2C3_TX_DMA == 1)
    #define I2C3_TX_DMA_Stream      DMAx_STREAMy(DEV_I2C3_TX_DMA_NUMBER, DEV_I2C3_TX_DMA_STREAM)
    #define I2C3_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C3_TX_DMA_NUMBER, DEV_I2C3_TX_DMA_STREAM)
    #define I2C3_TX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C3_TX_DMA_CHANNEL)
    #define I2C3_TX_DMA_Priority    DMA_PRIORITY(DEV_I2C3_TX_DMA_PRIORITY)
  #endif

  #define I2C3_SCL_GPIO_PORT        DEV_I2C3_SCL_PORT
  #define I2C3_SCL_GPIO_PIN         DEV_I2C3_SCL_PIN
  #define I2C3_SCL_GPIO_FUNC        DEV_I2C3_SCL_FUNC

  #define I2C3_SDA_GPIO_PORT        DEV_I2C3_SDA_PORT
  #define I2C3_SDA_GPIO_PIN         DEV_I2C3_SDA_PIN
  #define I2C3_SDA_GPIO_FUNC        DEV_I2C3_SDA_FUNC
#endif

/* I2C4 configuration definitions */
#if defined (DEV_I2C4) && (DEV_I2C4 == 1)
  #define USE_I2C4

  #if !defined(I2C4)
    #error "I2C4 not available for selected device!"
    #undef USE_I2C4
  #endif

  #if (DEV_I2C4_RX_DMA == 1)
    #define I2C4_RX_DMA_Stream      DMAx_STREAMy(DEV_I2C4_RX_DMA_NUMBER, DEV_I2C4_RX_DMA_STREAM)
    #define I2C4_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C4_RX_DMA_NUMBER, DEV_I2C4_RX_DMA_STREAM)
    #define I2C4_RX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C4_RX_DMA_CHANNEL)
    #define I2C4_RX_DMA_Priority    DMA_PRIORITY(DEV_I2C4_RX_DMA_PRIORITY)
  #endif
  #if (DEV_I2C4_TX_DMA == 1)
    #define I2C4_TX_DMA_Stream      DMAx_STREAMy(DEV_I2C4_TX_DMA_NUMBER, DEV_I2C4_TX_DMA_STREAM)
    #define I2C4_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_I2C4_TX_DMA_NUMBER, DEV_I2C4_TX_DMA_STREAM)
    #define I2C4_TX_DMA_Channel     DMA_CHANNEL_x(DEV_I2C4_TX_DMA_CHANNEL)
    #define I2C4_TX_DMA_Priority    DMA_PRIORITY(DEV_I2C4_TX_DMA_PRIORITY)
  #endif

  #define I2C4_SCL_GPIO_PORT        DEV_I2C4_SCL_PORT
  #define I2C4_SCL_GPIO_PIN         DEV_I2C4_SCL_PIN
  #define I2C4_SCL_GPIO_FUNC        DEV_I2C4_SCL_FUNC

  #define I2C4_SDA_GPIO_PORT        DEV_I2C4_SDA_PORT
  #define I2C4_SDA_GPIO_PIN         DEV_I2C4_SDA_PIN
  #define I2C4_SDA_GPIO_FUNC        DEV_I2C4_SDA_FUNC
#endif

#if ((defined(USE_I2C1) && defined(I2C1_RX_DMA_Stream)) || \
     (defined(USE_I2C2) && defined(I2C2_RX_DMA_Stream)) || \
     (defined(USE_I2C3) && defined(I2C3_RX_DMA_Stream)) || \
     (defined(USE_I2C4) && defined(I2C4_RX_DMA_Stream)))
  #define I2C_DMA_RX
#endif

#if ((defined(USE_I2C1) && defined(I2C1_TX_DMA_Stream)) || \
     (defined(USE_I2C2) && defined(I2C2_TX_DMA_Stream)) || \
     (defined(USE_I2C3) && defined(I2C3_TX_DMA_Stream)) || \
     (defined(USE_I2C4) && defined(I2C4_TX_DMA_Stream)))
  #define I2C_DMA_TX
#endif

#if (defined(I2C_DMA_RX) && defined(I2C_DMA_TX))
  #define I2C_DMA
#endif

#define I2Cx_EXPORT_DRIVER(x)                                                                                                                                                                          \
static int32_t        I2C##x##_Initialize     (ARM_I2C_SignalEvent_t cb_event)                                      { return I2C_Initialize    (cb_event, &I2C##x##_Resources);                      } \
static int32_t        I2C##x##_Uninitialize   (void)                                                                { return I2C_Uninitialize  (&I2C##x##_Resources);                                } \
static int32_t        I2C##x##_PowerControl   (ARM_POWER_STATE state)                                               { return I2C_PowerControl  (state, &I2C##x##_Resources);                         } \
static int32_t        I2C##x##_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending) { return I2C_MasterTransmit(addr, data, num, xfer_pending, &I2C##x##_Resources); } \
static int32_t        I2C##x##_MasterReceive  (uint32_t addr,       uint8_t *data, uint32_t num, bool xfer_pending) { return I2C_MasterReceive (addr, data, num, xfer_pending, &I2C##x##_Resources); } \
static int32_t        I2C##x##_SlaveTransmit  (               const uint8_t *data, uint32_t num)                    { return I2C_SlaveTransmit (data, num, &I2C##x##_Resources);                     } \
static int32_t        I2C##x##_SlaveReceive   (                     uint8_t *data, uint32_t num)                    { return I2C_SlaveReceive  (data, num, &I2C##x##_Resources);                     } \
static int32_t        I2C##x##_GetDataCount   (void)                                                                { return I2C_GetDataCount  (&I2C##x##_Resources);                                } \
static int32_t        I2C##x##_Control        (uint32_t control, uint32_t arg)                                      { return I2C_Control       (control, arg, &I2C##x##_Resources);                  } \
static ARM_I2C_STATUS I2C##x##_GetStatus      (void)                                                                { return I2C_GetStatus     (&I2C##x##_Resources);                                } \
       void           I2C##x##_EV_IRQHandler  (void)                                                                {        I2C_EV_IRQHandler (&I2C##x##_Resources);                                } \
       void           I2C##x##_ER_IRQHandler  (void)                                                                {        I2C_ER_IRQHandler (&I2C##x##_Resources);                                } \
                                                                                                                                                                                                       \
ARM_DRIVER_I2C Driver_I2C##x = { \
  I2Cx_GetVersion,               \
  I2Cx_GetCapabilities,          \
  I2C##x##_Initialize,           \
  I2C##x##_Uninitialize,         \
  I2C##x##_PowerControl,         \
  I2C##x##_MasterTransmit,       \
  I2C##x##_MasterReceive,        \
  I2C##x##_SlaveTransmit,        \
  I2C##x##_SlaveReceive,         \
  I2C##x##_GetDataCount,         \
  I2C##x##_Control,              \
  I2C##x##_GetStatus             \
}

/* Current driver status flag definition */
#define I2C_INIT            ((uint8_t)0x01)   // I2C initialized
#define I2C_POWER           ((uint8_t)0x02)   // I2C powered on
#define I2C_SETUP           ((uint8_t)0x04)   // I2C Master configured, clock set

/* Transfer status flags definitions */
#define XFER_CTRL_RESTART   ((uint8_t)0x01)   // Transfer pending
#define XFER_CTRL_STOP      ((uint8_t)0x02)   // Generate repeated start and readdress
#define XFER_CTRL_ADDR_NACK ((uint8_t)0x04)   // Slave address not acknowledged
#define XFER_CTRL_ADDR_DONE ((uint8_t)0x08)   // Addressing done

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* I2C Pin */
typedef const struct _I2C_PIN {
  GPIO_PORT_t           port;               // IO port
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
  uint8_t               reserved;           // Reserved
} I2C_PIN;

/* I2C Input/Output Configuration */
typedef const struct _I2C_IO {
  I2C_PIN               *scl;               // Pointer to SCL pin configuration
  I2C_PIN               *sda;               // Pointer to SDA pin configuration
} I2C_IO;

/* I2C Transfer Information (Run-Time) */
typedef struct _I2C_TRANSFER_INFO {
  uint32_t              num;                // Number of data to transfer
  int32_t               cnt;                // Data transfer counter
  uint8_t              *data;               // Data pointer
  uint8_t               ctrl;               // Transfer control flags
  uint8_t               reserved[3];        // Reserved
} I2C_TRANSFER_INFO;

/* I2C Information (Run-Time) */
typedef struct _I2C_INFO {
  ARM_I2C_SignalEvent_t cb_event;           // Event Callback
  ARM_I2C_STATUS        status;             // Status flags
  I2C_TRANSFER_INFO     xfer;               // Transfer information
  uint8_t               flags;              // Current I2C state flags
  uint8_t               reserved[3];        // Reserved
} I2C_INFO;

/* I2C Resource Configuration */
typedef struct {
  I2C_TypeDef          *reg;                // I2C peripheral register interface
  DMA_Resources_t      *dma_rx;             // I2C DMA Configuration
  DMA_Resources_t      *dma_tx;             // I2C DMA Configuration
  I2C_IO                io;                 // I2C Input/Output pins
  RCC_Periph_t          rcc;                // RCC registers
  I2C_INFO             *info;               // Run-Time information
  IRQn_Type             ev_irq_num;         // I2C Event IRQ Number
  IRQn_Type             er_irq_num;         // I2C Error IRQ Number
} const I2C_RESOURCES;

#endif /* I2C_STM32F7XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
