/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: I2C Driver Definitions for KM211 KRECHET1
 */

#ifndef I2C_KRECHET1_H_
#define I2C_KRECHET1_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/krechet1.h>
#include <Driver/ADSU_KRECHET1.h>
#include <CMSIS/Driver/Driver_I2C.h>

#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* I2C0 configuration definitions */
#if defined (DEV_I2C0) && (DEV_I2C0 == 1)
  #define USE_I2C0

  #define I2C0_INT_PRIO           DEV_I2C0_INT_PRIO
  #define I2C0_IRQHandler         Interruptx_Handler(DEV_I2C0_INT_PRIO)
#endif

/* I2C1 configuration definitions */
#if defined (DEV_I2C1) && (DEV_I2C1 == 1)
  #define USE_I2C1

  #define I2C1_INT_PRIO           DEV_I2C1_INT_PRIO
  #define I2C1_IRQHandler         Interruptx_Handler(DEV_I2C1_INT_PRIO)
#endif

#define I2Cx_EXPORT_DRIVER(x)                                                                                                                                                                                \
static int32_t        I2C##x##_Initialize       (ARM_I2C_SignalEvent_t cb_event)                                      { return (I2C_Initialize      (cb_event, &I2C##x##_Resources));                      } \
static int32_t        I2C##x##_Uninitialize     (void)                                                                { return (I2C_Uninitialize    (&I2C##x##_Resources));                                } \
static int32_t        I2C##x##_PowerControl     (ARM_POWER_STATE state)                                               { return (I2C_PowerControl    (state, &I2C##x##_Resources));                         } \
static int32_t        I2C##x##_MasterTransmit   (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending) { return (I2C_MasterTransmit  (addr, data, num, xfer_pending, &I2C##x##_Resources)); } \
static int32_t        I2C##x##_MasterReceive    (uint32_t addr,       uint8_t *data, uint32_t num, bool xfer_pending) { return (I2C_MasterReceive   (addr, data, num, xfer_pending, &I2C##x##_Resources)); } \
static int32_t        I2C##x##_SlaveTransmit    (               const uint8_t *data, uint32_t num)                    { return (I2C_SlaveTransmit   (data, num, &I2C##x##_Resources));                     } \
static int32_t        I2C##x##_SlaveReceive     (                     uint8_t *data, uint32_t num)                    { return (I2C_SlaveReceive    (data, num, &I2C##x##_Resources));                     } \
static int32_t        I2C##x##_GetDataCount     (void)                                                                { return (I2C_GetDataCount    (&I2C##x##_Resources));                                } \
static int32_t        I2C##x##_Control          (uint32_t control, uint32_t arg)                                      { return (I2C_Control         (control, arg, &I2C##x##_Resources));                  } \
static ARM_I2C_STATUS I2C##x##_GetStatus        (void)                                                                { return (I2C_GetStatus       (&I2C##x##_Resources));                                } \
                                                                                                                                                                                                             \
void I2C##x##_IRQHandler(void) __attribute__ ((fast_interrupt));                                                                                                                                             \
void I2C##x##_IRQHandler(void)                                                                                                                                                                               \
{                                                                                                                                                                                                            \
  __isr_prologue();                                                                                                                                                                                          \
  I2C_IRQHandler(&I2C##x##_Resources);                                                                                                                                                                       \
  __isr_epilogue();                                                                                                                                                                                          \
}                                                                                                                                                                                                            \
                                                                                                                                                                                                             \
ARM_DRIVER_I2C Driver_I2C##x = {                                                                                                                                                                             \
  I2Cx_GetVersion,                                                                                                                                                                                           \
  I2Cx_GetCapabilities,                                                                                                                                                                                      \
  I2C##x##_Initialize,                                                                                                                                                                                       \
  I2C##x##_Uninitialize,                                                                                                                                                                                     \
  I2C##x##_PowerControl,                                                                                                                                                                                     \
  I2C##x##_MasterTransmit,                                                                                                                                                                                   \
  I2C##x##_MasterReceive,                                                                                                                                                                                    \
  I2C##x##_SlaveTransmit,                                                                                                                                                                                    \
  I2C##x##_SlaveReceive,                                                                                                                                                                                     \
  I2C##x##_GetDataCount,                                                                                                                                                                                     \
  I2C##x##_Control,                                                                                                                                                                                          \
  I2C##x##_GetStatus                                                                                                                                                                                         \
}

/* Current driver status flag definition */
#define I2C_INIT              ((uint16_t)0x01)    // I2C initialized
#define I2C_POWER             ((uint16_t)0x02)    // I2C powered on
#define I2C_SETUP             ((uint16_t)0x04)    // I2C Master configured, clock set

/* I2C status flags definitions */
#define I2C_BUSY              (1UL << 0U)
#define I2C_MASTER            (1UL << 1U)
#define I2C_TRANSMITTER       (0UL << 2U)
#define I2C_RECEIVER          (1UL << 2U)
#define I2C_GENERAL_CALL      (1UL << 3U)
#define I2C_ARBITRATION_LOST  (1UL << 4U)
#define I2C_BUS_ERROR         (1UL << 5U)

/* Transfer status flags definitions */
#define XFER_CTRL_XPENDING    ((uint16_t)0x0001)  // Transfer pending
#define XFER_CTRL_ADDR_DONE   ((uint16_t)0x0002)  // Addressing done

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

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
} I2C_TX_XFER_INFO;

/* I2C Information (Run-Time) */
typedef struct _I2C_INFO {
  ARM_I2C_SignalEvent_t cb_event;           // Event Callback
  uint32_t              status;             // Status flags
  I2C_RX_XFER_INFO      rx;                 // RX transfer information
  I2C_TX_XFER_INFO      tx;                 // TX transfer information
  uint16_t              flags;              // Current I2C state flags
  uint16_t              xfer_ctrl;          // Transfer control (current)
} I2C_INFO;

/* I2C Resource Configuration */
typedef struct {
  Periph_Wnd_t          prw;
  ADSU_Periph_t         adsu_periph;
  IRQn_t                irq_num;            // I2C IRQ Number
  uint32_t              irq_prio;           // I2C IRQ Priority
  I2C_INFO             *info;               // Run-Time information
} const I2C_RESOURCES;

#endif /* I2C_KRECHET1_H_ */

/* ----------------------------- End of file ---------------------------------*/
