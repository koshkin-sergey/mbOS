/*
 * Copyright (C) 2018-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef I2C_STM32F4XX_H_
#define I2C_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#include <asm/stm32f4xx.h>
#include <Driver/RCC_STM32F4xx.h>
#include <Driver/GPIO_STM32F4xx.h>

#include <Driver/Driver_I2C.h>

#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define I2C_CLR_TIMEOUT_US          5

/* I2C1 configuration definitions */
#if defined (RTE_I2C1) && (RTE_I2C1 == 1)
  #define USE_I2C1

  #define I2C1_SCL_GPIO_PORT        RTE_I2C1_SCL_PORT
  #define I2C1_SCL_GPIO_PIN         RTE_I2C1_SCL_PIN
  #define I2C1_SCL_GPIO_FUNC        RTE_I2C1_SCL_FUNC
  #define I2C1_SDA_GPIO_PORT        RTE_I2C1_SDA_PORT
  #define I2C1_SDA_GPIO_PIN         RTE_I2C1_SDA_PIN
  #define I2C1_SDA_GPIO_FUNC        RTE_I2C1_SDA_FUNC
#endif

/* I2C2 configuration definitions */
#if defined (RTE_I2C2) && (RTE_I2C2 == 1)

  #if !defined(I2C2)
    #error "I2C2 not available for selected device!"
  #endif

  #define USE_I2C2

  #define I2C2_SCL_GPIO_PORT        RTE_I2C2_SCL_PORT
  #define I2C2_SCL_GPIO_PIN         RTE_I2C2_SCL_PIN
  #define I2C2_SCL_GPIO_FUNC        RTE_I2C2_SCL_FUNC
  #define I2C2_SDA_GPIO_PORT        RTE_I2C2_SDA_PORT
  #define I2C2_SDA_GPIO_PIN         RTE_I2C2_SDA_PIN
  #define I2C2_SDA_GPIO_FUNC        RTE_I2C2_SDA_FUNC
#endif

/* I2C3 configuration definitions */
#if defined (RTE_I2C3) && (RTE_I2C3 == 1)

  #if !defined(I2C3)
    #error "I2C3 not available for selected device!"
  #endif

  #define USE_I2C3

  #define I2C3_SCL_GPIO_PORT        RTE_I2C3_SCL_PORT
  #define I2C3_SCL_GPIO_PIN         RTE_I2C3_SCL_PIN
  #define I2C3_SCL_GPIO_FUNC        RTE_I2C3_SCL_FUNC
  #define I2C3_SDA_GPIO_PORT        RTE_I2C3_SDA_PORT
  #define I2C3_SDA_GPIO_PIN         RTE_I2C3_SDA_PIN
  #define I2C3_SDA_GPIO_FUNC        RTE_I2C3_SDA_FUNC
#endif

#define I2Cx_EXPORT_DRIVER(x)                                                                                                                                                                                 \
static int32_t        I2C##x##_Initialize       (ARM_I2C_SignalEvent_t cb_event)                                      { return (I2C_Initialize       (cb_event, &I2C##x##_Resources));                      } \
static int32_t        I2C##x##_Uninitialize     (void)                                                                { return (I2C_Uninitialize     (&I2C##x##_Resources));                                } \
static int32_t        I2C##x##_PowerControl     (ARM_POWER_STATE state)                                               { return (I2C_PowerControl     (state, &I2C##x##_Resources));                         } \
static int32_t        I2C##x##_MasterTransmit   (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending) { return (I2C_MasterTransmit   (addr, data, num, xfer_pending, &I2C##x##_Resources)); } \
static int32_t        I2C##x##_MasterReceive    (uint32_t addr,       uint8_t *data, uint32_t num, bool xfer_pending) { return (I2C_MasterReceive    (addr, data, num, xfer_pending, &I2C##x##_Resources)); } \
static int32_t        I2C##x##_SlaveTransmit    (               const uint8_t *data, uint32_t num)                    { return (I2C_SlaveTransmit    (data, num, &I2C##x##_Resources));                     } \
static int32_t        I2C##x##_SlaveReceive     (                     uint8_t *data, uint32_t num)                    { return (I2C_SlaveReceive     (data, num, &I2C##x##_Resources));                     } \
static int32_t        I2C##x##_GetDataCount     (void)                                                                { return (I2C_GetDataCount     (&I2C##x##_Resources));                                } \
static int32_t        I2C##x##_Control          (uint32_t control, uint32_t arg)                                      { return (I2C_Control          (control, arg, &I2C##x##_Resources));                  } \
static ARM_I2C_STATUS I2C##x##_GetStatus        (void)                                                                { return (I2C_GetStatus        (&I2C##x##_Resources));                                } \
extern void           I2C##x##_EV_IRQHandler    (void);                                                                                                                                                       \
extern void           I2C##x##_ER_IRQHandler    (void);                                                                                                                                                       \
       void           I2C##x##_EV_IRQHandler    (void)                                                                {         I2C_EV_IRQHandler    (&I2C##x##_Resources);                                 } \
       void           I2C##x##_ER_IRQHandler    (void)                                                                {         I2C_ER_IRQHandler    (&I2C##x##_Resources);                                 } \
                                  \
extern                            \
ARM_DRIVER_I2C Driver_I2C##x;     \
ARM_DRIVER_I2C Driver_I2C##x = {  \
  I2Cx_GetVersion,                \
  I2Cx_GetCapabilities,           \
  I2C##x##_Initialize,            \
  I2C##x##_Uninitialize,          \
  I2C##x##_PowerControl,          \
  I2C##x##_MasterTransmit,        \
  I2C##x##_MasterReceive,         \
  I2C##x##_SlaveTransmit,         \
  I2C##x##_SlaveReceive,          \
  I2C##x##_GetDataCount,          \
  I2C##x##_Control,               \
  I2C##x##_GetStatus              \
}

/* Current driver status flag definition */
#define I2C_FLAG_INIT       (1UL << 0)      // I2C initialized
#define I2C_FLAG_POWER      (1UL << 1)      // I2C powered on
#define I2C_FLAG_SETUP      (1UL << 2)      // I2C Master configured, clock set

/* Transfer status flags definitions */
#define XFER_CTRL_XPENDING  (1UL << 0)      // Transfer pending
#define XFER_CTRL_RSTART    (1UL << 1)      // Generate repeated start and readdress
#define XFER_CTRL_ADDR_DONE (1UL << 2)      // Addressing done
#define XFER_CTRL_DMA_DONE  (1UL << 3)      // DMA transfer done
#define XFER_CTRL_WAIT_BTF  (1UL << 4)      // Wait for byte transfer finished
#define XFER_CTRL_XACTIVE   (1UL << 5)      // Transfer active

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef void* I2C_DMA;

/* I2C Input/Output Configuration */
typedef const struct _I2C_IO {
  GPIO_PORT_t           scl_port;           // SCL IO port
  GPIO_PIN_t            scl_pin;            // SCL IO pin
  GPIO_PIN_FUNC_t       scl_func;           // SCL AF pin configuration
  GPIO_PORT_t           sda_port;           // SDA IO port
  GPIO_PIN_t            sda_pin;            // SDA IO pin
  GPIO_PIN_FUNC_t       sda_func;           // SDA AF pin configuration
} I2C_IO;

/* I2C Transfer Information (Run-Time) */
typedef struct _I2C_TRANSFER_INFO {
  uint32_t              num;                // Number of data to transfer
  uint32_t              cnt;                // Data transfer counter
  uint8_t              *data;               // Data pointer
  uint32_t              addr;               // Device address
  uint32_t              ctrl;               // Transfer control flags
} I2C_TRANSFER_INFO;

/* I2C Information (Run-Time) */
typedef struct _I2C_INFO {
  ARM_I2C_SignalEvent_t cb_event;           // Event Callback
  ARM_I2C_STATUS        status;             // Status flags
  I2C_TRANSFER_INFO     xfer;               // Transfer information
  uint32_t              flags;              // Current I2C state flags
} I2C_INFO;

/* I2C Resource Configuration */
typedef struct {
  I2C_TypeDef          *reg;                // I2C peripheral register interface
  I2C_DMA              *dma_rx;             // I2C DMA Configuration
  I2C_DMA              *dma_tx;             // I2C DMA Configuration
  I2C_IO                io;                 // I2C Input/Output pins
  I2C_INFO             *info;               // Run-Time information
  RCC_Periph_t          rcc;                // RCC Clock/Reset registers
  IRQn_Type             ev_irq_num;         // I2C Event IRQ Number
  IRQn_Type             er_irq_num;         // I2C Error IRQ Number
  uint8_t               reserved[6];
} const I2C_RESOURCES;

#endif /* I2C_STM32F4XX_H_ */
