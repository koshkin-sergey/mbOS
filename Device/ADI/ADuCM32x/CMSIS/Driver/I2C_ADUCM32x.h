/*
 * Copyright (C) 2017-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver Definitions for ADI ADuCM32x
 */

#ifndef I2C_ADUCM32X_H_
#define I2C_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/aducm32x.h>
#include <device_config.h>
#include <Driver/CLK_ADUCM32x.h>
#include <Driver/GPIO_ADUCM32x.h>
#include <CMSIS/Driver/Driver_I2C.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* I2C0 configuration definitions */
#if defined (DEV_I2C0) && (DEV_I2C0 == 1)
  #define USE_I2C0

  #if !defined(MMR_I2C0)
    #error "I2C0 not available for selected device!"
    #undef USE_I2C0
  #endif

  #define I2C0_SCL_GPIO_PORT        DEV_I2C0_SCL_PORT
  #define I2C0_SCL_GPIO_PIN         DEV_I2C0_SCL_PIN
  #define I2C0_SCL_GPIO_FUNC        DEV_I2C0_SCL_FUNC

  #define I2C0_SDA_GPIO_PORT        DEV_I2C0_SDA_PORT
  #define I2C0_SDA_GPIO_PIN         DEV_I2C0_SDA_PIN
  #define I2C0_SDA_GPIO_FUNC        DEV_I2C0_SDA_FUNC

  #define I2C0_INT_PRIORITY         DEV_I2C0_INT_PRIO
#endif

/* I2C1 configuration definitions */
#if defined (DEV_I2C1) && (DEV_I2C1 == 1)
  #define USE_I2C1

  #if !defined(MMR_I2C1)
    #error "I2C1 not available for selected device!"
    #undef USE_I2C1
  #endif

  #define I2C1_SCL_GPIO_PORT        DEV_I2C1_SCL_PORT
  #define I2C1_SCL_GPIO_PIN         DEV_I2C1_SCL_PIN
  #define I2C1_SCL_GPIO_FUNC        DEV_I2C1_SCL_FUNC

  #define I2C1_SDA_GPIO_PORT        DEV_I2C1_SDA_PORT
  #define I2C1_SDA_GPIO_PIN         DEV_I2C1_SDA_PIN
  #define I2C1_SDA_GPIO_FUNC        DEV_I2C1_SDA_FUNC

  #define I2C1_INT_PRIORITY         DEV_I2C1_INT_PRIO
#endif

#define I2Cx_EXPORT_DRIVER(x)     \
static int32_t        I2C##x##_Initialize       (ARM_I2C_SignalEvent_t cb_event)                                      { return (I2C_Initialize       (cb_event,                      &I2C##x##_Resources)); } \
static int32_t        I2C##x##_Uninitialize     (void)                                                                { return (I2C_Uninitialize     (                               &I2C##x##_Resources)); } \
static int32_t        I2C##x##_PowerControl     (ARM_POWER_STATE state)                                               { return (I2C_PowerControl     (state,                         &I2C##x##_Resources)); } \
static int32_t        I2C##x##_MasterTransmit   (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending) { return (I2C_MasterTransmit   (addr, data, num, xfer_pending, &I2C##x##_Resources)); } \
static int32_t        I2C##x##_MasterReceive    (uint32_t addr,       uint8_t *data, uint32_t num, bool xfer_pending) { return (I2C_MasterReceive    (addr, data, num, xfer_pending, &I2C##x##_Resources)); } \
static int32_t        I2C##x##_SlaveTransmit    (               const uint8_t *data, uint32_t num)                    { return (I2C_SlaveTransmit    (      data, num,               &I2C##x##_Resources)); } \
static int32_t        I2C##x##_SlaveReceive     (                     uint8_t *data, uint32_t num)                    { return (I2C_SlaveReceive     (      data, num,               &I2C##x##_Resources)); } \
static int32_t        I2C##x##_GetDataCount     (void)                                                                { return (I2C_GetDataCount     (                               &I2C##x##_Resources)); } \
static int32_t        I2C##x##_Control          (uint32_t control, uint32_t arg)                                      { return (I2C_Control          (control, arg,                  &I2C##x##_Resources)); } \
static ARM_I2C_STATUS I2C##x##_GetStatus        (void)                                                                { return (I2C_GetStatus        (                               &I2C##x##_Resources)); } \
extern void           I2C##x##_Master_IRQHandler(void);                                                                                                                                                       \
extern void           I2C##x##_Slave_IRQHandler (void);                                                                                                                                                       \
       void           I2C##x##_Master_IRQHandler(void)                                                                {         I2C_Master_IRQHandler(                               &I2C##x##_Resources);  } \
       void           I2C##x##_Slave_IRQHandler (void)                                                                {         I2C_Slave_IRQHandler (                               &I2C##x##_Resources);  } \
                                  \
extern                            \
ARM_DRIVER_I2C Driver_I2C##x;     \
ARM_DRIVER_I2C Driver_I2C##x = {  \
  I2C_GetVersion,                 \
  I2C_GetCapabilities,            \
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

/* I2C Driver state flags */
#define I2C_FLAG_INIT             (1UL << 0)    // Driver initialized
#define I2C_FLAG_POWER            (1UL << 1)    // Driver power on
#define I2C_FLAG_SETUP            (1UL << 2)    // Master configured, clock set
#define I2C_FLAG_SLAVE_RX         (1UL << 3)    // Slave receive registered
#define I2C_FLAG_SLAVE_ADDR       (1UL << 4)    // Addressed Slave
#define I2C_FLAG_TX_RESTART       (1UL << 5)
#define I2C_FLAG_RX_RESTART       (1UL << 6)
#define I2C_FLAG_ADDRESS_NACK     (1UL << 7)
#define I2C_FLAG_SLAVE_BUF_EMPTY  (1UL << 8)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* I2C Pin Configuration */
typedef const struct I2C_Pin {
  Driver_GPIO_t        *gpio;               // Pointer to GPIO driver
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
} I2C_Pin_t;

/* I2C Input/Output Configuration */
typedef const struct I2C_IO {
  I2C_Pin_t             scl;                // Pointer to SCL pin configuration
  I2C_Pin_t             sda;                // Pointer to SDA pin configuration
} I2C_IO_t;

/* I2C IRQ Configuration */
typedef const struct I2C_Irq {
  IRQ_Priority_t        priority;           // I2C interrupt priority
  IRQn_Type             master_num;         // I2C Master IRQ Number
  IRQn_Type             slave_num;          // I2C Slave IRQ Number
} I2C_Irq_t;

/* I2C RX Transfer Information (Run-Time) */
typedef struct I2C_RX_XferInfo {
  uint8_t              *data;               // Data pointer
  uint32_t              num;                // Number of data to transfer
  uint32_t              cnt;                // Data transfer counter
} I2C_RX_XferInfo_t;

/* I2C TX Transfer Information (Run-Time) */
typedef struct I2C_TX_XferInfo {
  const uint8_t        *data;               // Data pointer
  uint32_t              num;                // Number of data to transfer
  uint32_t              cnt;                // Data transfer counter
  uint32_t              dummy_cnt;          // Dummy byte counter
} I2C_TX_XferInfo_t;

/* I2C Information (Run-Time) */
typedef struct I2C_Info {
  ARM_I2C_SignalEvent_t cb_event;           // Event Callback
  uint32_t              status;             // Status flags
  I2C_RX_XferInfo_t     rx;                 // RX transfer information
  I2C_TX_XferInfo_t     tx;                 // TX transfer information
  uint16_t              flags;              // Current I2C state flags
  uint16_t              xfer_ctrl;          // Transfer control (current)
} I2C_Info_t;

/* I2C Resource Configuration */
typedef struct {
  MMR_I2C_t            *mmr;                // I2C register interface
  I2C_IO_t              io;                 // I2C pin configuration
  CLK_Periph_t          clk_periph;         // I2C clock control
  I2C_Irq_t             irq;                // I2C interrupt information
  I2C_Info_t           *info;               // Run-Time control information
} const I2C_Resources_t;

#endif /* I2C_ADUCM32X_H_ */
