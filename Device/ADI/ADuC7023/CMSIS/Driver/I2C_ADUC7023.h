/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver Definitions for ADI ADUC7023
 */

#ifndef I2C_ADUC7023_H_
#define I2C_ADUC7023_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>

#include <asm/aduc7023.h>
#include <Kernel/irq.h>
#include <CMSIS/Driver/Driver_I2C.h>

#include <device_config.h>
#include <Driver/GPIO_ADUC7023.h>
#include <Driver/PCC_ADUC7023.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* I2C0 configuration definitions */
#if defined (DEV_I2C0) && (DEV_I2C0 == 1)
  #define USE_I2C0

  #if !defined(I2C0)
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

  #if !defined(I2C1)
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
       void           I2C##x##_Master_IRQHandler(void)                                                                {         I2C_Master_IRQHandler(&I2C##x##_Resources);                                 } \
       void           I2C##x##_Slave_IRQHandler (void)                                                                {         I2C_Slave_IRQHandler (&I2C##x##_Resources);                                 } \
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
#define I2C_INIT              ((uint16_t)0x01)    // I2C initialized
#define I2C_POWER             ((uint16_t)0x02)    // I2C powered on
#define I2C_SETUP             ((uint16_t)0x04)    // I2C Master configured, clock set

#define I2C_MODE_SLAVE        ((uint8_t)0x00)     // Mode: slave
#define I2C_MODE_MASTER       ((uint8_t)0x01)     // Mode: master

#define I2C_DIR_TX            ((uint8_t)0x00)     // Direction: transmitter
#define I2C_DIR_RX            ((uint8_t)0x01)     // Direction: receiver

/* Transfer status flags definitions */
#define XFER_CTRL_XPENDING    ((uint16_t)0x0001)  // Transfer pending
#define XFER_CTRL_ADDR_DONE   ((uint16_t)0x0002)  // Addressing done

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* I2C Pin */
typedef const struct _I2C_PIN {
  DRIVER_GPIO          *gpio;               // Pointer to GPIO driver
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
} I2C_PIN;

/* I2C Input/Output Configuration */
typedef const struct _I2C_IO {
  I2C_PIN              *scl;                // Pointer to SCL pin configuration
  I2C_PIN              *sda;                // Pointer to SDA pin configuration
} I2C_IO;

/* I2C RX Transfer Information (Run-Time) */
typedef struct _I2C_RX_XFER_INFO {
  uint8_t              *data;               // Data pointer
  uint32_t              num;                // Number of data to transfer
  uint32_t              cnt;                // Data transfer counter
} I2C_RX_XFER_INFO;

/* I2C TX Transfer Information (Run-Time) */
typedef struct _I2C_TX_XFER_INFO {
  const uint8_t        *data;               // Data pointer
  uint32_t              num;                // Number of data to transfer
  uint32_t              cnt;                // Data transfer counter
  uint32_t              dummy_cnt;          // Dummy byte counter
} I2C_TX_XFER_INFO;

/* I2C Information (Run-Time) */
typedef struct _I2C_INFO {
  ARM_I2C_SignalEvent_t cb_event;           // Event Callback
  ARM_I2C_STATUS        status;             // Status flags
  I2C_RX_XFER_INFO      rx;                 // RX transfer information
  I2C_TX_XFER_INFO      tx;                 // TX transfer information
  uint16_t              flags;              // Current I2C state flags
  uint16_t              xfer_ctrl;          // Transfer control (current)
} I2C_INFO;

/* I2C IRQ Configuration */
typedef const struct _I2C_IRQ {
  IRQ_Priority_t        priority;           // I2C interrupt priority
  IRQn_t                master_num;         // I2C Master IRQ Number
  IRQn_t                slave_num;          // I2C Slave IRQ Number
  IRQHandler_t          master_handler;     // I2C Master IRQ handler
  IRQHandler_t          slave_handler;      // I2C Slave IRQ handler
} I2C_IRQ;

/* I2C Resource Configuration */
typedef struct {
  I2C_t                *reg;                // I2C peripheral register interface
  I2C_IO                io;                 // I2C Input/Output pins
  I2C_INFO             *info;               // Run-Time information
  PCC_Periph_t          pcc_periph;         // I2C PCC peripheral
  I2C_IRQ               irq;                // I2C interrupt information
} const I2C_RESOURCES;

#endif /* I2C_ADUC7023_H_ */

/* ----------------------------- End of file ---------------------------------*/
