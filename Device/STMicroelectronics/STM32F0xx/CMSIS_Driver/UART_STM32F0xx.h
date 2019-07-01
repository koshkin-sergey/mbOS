/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2017 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        10. November 2017
 * $Revision:    V1.0
 *
 * Project:      UART Driver definitions for STMicroelectronics STM32F0xx
 * -------------------------------------------------------------------------- */

#ifndef __UART_STM32F0XX_H
#define __UART_STM32F0XX_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Driver_USART.h"
#include "stm32f0xx_hal.h"

#include "RTE_Components.h"
#include "MX_Device.h"

#ifdef HAL_UART_MODULE_ENABLED

#define  VM_ASYNC                       (1UL)
#define  VM_SYNC                        (2UL)
#define  VM_IRDA                        (3UL)
#define  VM_SMARTCARD                   (4UL)
#define  Asynchronous                   VM_ASYNC
#define  IrDA                           VM_IRDA

#define UART_HAL_STATUS(stat)           ((stat == HAL_OK)      ? ARM_DRIVER_OK :                \
                                        ((stat == HAL_BUSY)    ? ARM_DRIVER_ERROR_BUSY :        \
                                        ((stat == HAL_TIMEOUT) ? ARM_DRIVER_ERROR_TIMEOUT :     \
                                                                 ARM_DRIVER_ERROR)))

#define UARTx_RESOURCE_ALLOC(x)         extern UART_HandleTypeDef   huart##x;                   \
                                        static UART_INFO            UART##x##_Info;             \
                                        static UART_TRANSFER_INFO   UART##x##_TransferInfo;     \
                                        static const UART_RESOURCES UART##x##_Resources =  {    \
                                         &huart##x,                                             \
                                          UART##x##_PERIPHERAL,                                 \
                                         &UART##x##_Info,                                       \
                                         &UART##x##_TransferInfo,                               \
                                          UART##x##_DMA_USE_TX,                                 \
                                          UART##x##_DMA_USE_RX,                                 \
                                          0                                                     \
                                        }

#define UARTx_EXPORT_DRIVER(x)                                                                                                                                                          \
static int32_t                USART##x##_Initialize      (ARM_USART_SignalEvent_t cb_event)                  { return UART_Initialize (cb_event, &UART##x##_Resources); }               \
static int32_t                USART##x##_Uninitialize    (void)                                              { return UART_Uninitialize (&UART##x##_Resources); }                       \
static int32_t                USART##x##_PowerControl    (ARM_POWER_STATE state)                             { return UART_PowerControl (state, &UART##x##_Resources); }                \
static int32_t                USART##x##_Send            (const void *data, uint32_t num)                    { return UART_Send (data, num, &UART##x##_Resources); }                    \
static int32_t                USART##x##_Receive         (void *data, uint32_t num)                          { return UART_Receive (data, num, &UART##x##_Resources); }                 \
static int32_t                USART##x##_Transfer        (const void *data_out, void *data_in, uint32_t num) { return UART_Transfer (data_out, data_in, num, &UART##x##_Resources); }   \
static uint32_t               USART##x##_GetGetTxCount   (void)                                              { return UART_GetTxCount (&UART##x##_Resources); }                         \
static uint32_t               USART##x##_GetGetRxCount   (void)                                              { return UART_GetRxCount (&UART##x##_Resources); }                         \
static int32_t                USART##x##_Control         (uint32_t control, uint32_t arg)                    { return UART_Control (control, arg, &UART##x##_Resources); }              \
static ARM_USART_STATUS       USART##x##_GetStatus       (void)                                              { return UART_GetStatus (&UART##x##_Resources); }                          \
                                                                                                                                                                                        \
ARM_DRIVER_USART Driver_USART##x = {    \
  UART_GetVersion,                      \
  UART_GetCapabilities,                 \
  USART##x##_Initialize,                \
  USART##x##_Uninitialize,              \
  USART##x##_PowerControl,              \
  USART##x##_Send,                      \
  USART##x##_Receive,                   \
  USART##x##_Transfer,                  \
  USART##x##_GetGetTxCount,             \
  USART##x##_GetGetRxCount,             \
  USART##x##_Control,                   \
  USART##x##_GetStatus,                 \
  UART_SetModemControl,                 \
  UART_GetModemStatus                   \
}

// DMA Use
#define UART_DMA_USE_TX                 (1U << 0)
#define UART_DMA_USE_RX                 (1U << 1)
#define UART_DMA_USE_TX_RX              (USART_DMA_USE_TX | USART_DMA_USE_RX)

// UART1 Configuration
#ifdef MX_USART1
#if   (MX_USART1_VM == VM_ASYNC)

// Peripheral: USART1
#define UART1_PERIPHERAL                USART1

// USART1 used in Asynchronous mode
#define USART1_MODE_ASYNC               1

// UART1 DMA USE
#ifdef MX_USART1_TX_DMA_Instance
  #define UART1_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART1_DMA_USE_TX              0
#endif
#ifdef MX_USART1_RX_DMA_Instance
  #define UART1_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART1_DMA_USE_RX              0
#endif
#define UART1_DMA_USE                   (UART1_DMA_USE_TX | UART1_DMA_USE_RX)
#endif
#endif

// UART2 Configuration
#ifdef MX_USART2
#if   (MX_USART2_VM == VM_ASYNC)

// Peripheral: USART2
#define UART2_PERIPHERAL                USART2

// USART2 used in Asynchronous mode
#define USART2_MODE_ASYNC               1

// UART2 DMA USE
#ifdef MX_USART2_TX_DMA_Instance
  #define UART2_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART2_DMA_USE_TX              0
#endif
#ifdef MX_USART2_RX_DMA_Instance
  #define UART2_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART2_DMA_USE_RX              0
#endif
#define UART2_DMA_USE                   (UART2_DMA_USE_TX | UART2_DMA_USE_RX)
#endif
#endif

// UART3 Configuration
#ifdef MX_USART3
#if   (MX_USART3_VM == VM_ASYNC)

// Peripheral: USART3
#define UART3_PERIPHERAL                USART3

// USART3 used in Asynchronous mode
#define USART3_MODE_ASYNC               1

// UART3 DMA USE
#ifdef MX_USART3_TX_DMA_Instance
  #define UART3_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART3_DMA_USE_TX              0
#endif
#ifdef MX_USART3_RX_DMA_Instance
  #define UART3_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART3_DMA_USE_RX              0
#endif
#define UART3_DMA_USE                   (UART3_DMA_USE_TX | UART3_DMA_USE_RX)
#endif
#endif

// UART4 Configuration
#ifdef MX_USART4
#if   (MX_USART4_VM == VM_ASYNC)

// Peripheral: USART4
#define UART4_PERIPHERAL                USART4

// USART4 used in Asynchronous mode
#define USART4_MODE_ASYNC               1

// UART4 DMA USE
#ifdef MX_USART4_TX_DMA_Instance
  #define UART4_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART4_DMA_USE_TX              0
#endif
#ifdef MX_USART4_RX_DMA_Instance
  #define UART4_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART4_DMA_USE_RX              0
#endif
#define UART4_DMA_USE                   (UART4_DMA_USE_TX | UART4_DMA_USE_RX)
#endif
#endif

// UART5 Configuration
#ifdef MX_USART5
#if   (MX_USART5_VM == VM_ASYNC)

// Peripheral: UART5
#define UART5_PERIPHERAL                USART5

// USART5 used in Asynchronous mode
#define USART5_MODE_ASYNC               1

// UART5 DMA USE
#ifdef MX_USART5_TX_DMA_Instance
  #define UART5_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART5_DMA_USE_TX              0
#endif
#ifdef MX_USART5_RX_DMA_Instance
  #define UART5_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART5_DMA_USE_RX              0
#endif
#define UART5_DMA_USE                   (UART5_DMA_USE_TX | UART5_DMA_USE_RX)
#endif
#endif

// UART6 Configuration
#ifdef MX_USART6
#if   (MX_USART6_VM == VM_ASYNC)

// Peripheral: USART6
#define UART6_PERIPHERAL                USART6

// USART6 used in Asynchronous mode
#define USART6_MODE_ASYNC               1

// UART6 DMA USE
#ifdef MX_USART6_TX_DMA_Instance
  #define UART6_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART6_DMA_USE_TX              0
#endif
#ifdef MX_USART6_RX_DMA_Instance
  #define UART6_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART6_DMA_USE_RX              0
#endif
#define UART6_DMA_USE                   (UART6_DMA_USE_TX | UART6_DMA_USE_RX)
#endif
#endif

// UART7 Configuration
#ifdef MX_USART7
#if   (MX_USART7_VM == VM_ASYNC)

// Peripheral: USART7
#define UART7_PERIPHERAL                USART7

// USART7 used in Asynchronous mode
#define USART7_MODE_ASYNC               1

// UART7 DMA USE
#ifdef MX_USART7_TX_DMA_Instance
  #define UART7_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART7_DMA_USE_TX              0
#endif
#ifdef MX_USART7_RX_DMA_Instance
  #define UART7_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART7_DMA_USE_RX              0
#endif
#define UART7_DMA_USE                   (UART7_DMA_USE_TX | UART7_DMA_USE_RX)
#endif
#endif

// UART8 Configuration
#ifdef MX_USART8
#if   (MX_USART8_VM == VM_ASYNC)

// Peripheral: USART8
#define UART8_PERIPHERAL                USART8

// USART8 used in Asynchronous mode
#define USART8_MODE_ASYNC               1

// UART8 DMA USE
#ifdef MX_USART8_TX_DMA_Instance
  #define UART8_DMA_USE_TX              UART_DMA_USE_TX
#else
  #define UART8_DMA_USE_TX              0
#endif
#ifdef MX_USART8_RX_DMA_Instance
  #define UART8_DMA_USE_RX              UART_DMA_USE_RX
#else
  #define UART8_DMA_USE_RX              0
#endif
#define UART8_DMA_USE                   (UART8_DMA_USE_TX | UART8_DMA_USE_RX)
#endif
#endif

#if defined(USART1_MODE_ASYNC) ||       \
    defined(USART2_MODE_ASYNC) ||       \
    defined(USART3_MODE_ASYNC) ||       \
    defined(USART4_MODE_ASYNC) ||       \
    defined(USART5_MODE_ASYNC) ||       \
    defined(USART6_MODE_ASYNC) ||       \
    defined(USART7_MODE_ASYNC) ||       \
    defined(USART8_MODE_ASYNC)

#define USARTx_MODE_ASYNC               1

// USART flags
#define UART_FLAG_INITIALIZED           ((uint8_t)(1U))
#define UART_FLAG_POWERED               ((uint8_t)(1U << 1))
#define UART_FLAG_CONFIGURED            ((uint8_t)(1U << 2))
#define UART_FLAG_TX_ENABLED            ((uint8_t)(1U << 3))
#define UART_FLAG_RX_ENABLED            ((uint8_t)(1U << 4))

// UART Transfer Information (Run-Time)
typedef struct _UART_TRANSFER_INFO {
  uint32_t              rx_num;         // Total number of receive data
  uint32_t              tx_num;         // Total number of transmit data
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              tx_cnt;         // Number of data sent
  uint16_t              def_val;        // Default transfer value
  uint16_t              reserved;
} UART_TRANSFER_INFO;

typedef struct _UART_STATUS {
  uint8_t tx_busy;                      // Transmitter busy flag
  uint8_t rx_busy;                      // Receiver busy flag
  uint8_t tx_underflow;                 // Transmit data underflow detected (cleared on start of next send operation)
  uint8_t rx_overflow;                  // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t rx_break;                     // Break detected on receive (cleared on start of next receive operation)
  uint8_t rx_framing_error;             // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t rx_parity_error;              // Parity error detected on receive (cleared on start of next receive operation)
} UART_STATUS;

// UART Information (Run-time)
typedef struct _USART_INFO {
  ARM_USART_SignalEvent_t    cb_event;  // Event Callback
  UART_STATUS                status;    // Status flags
  uint8_t                    flags;     // Current USART flags
} UART_INFO;

// UART Resources definition
typedef const struct {
  UART_HandleTypeDef        *h;
  void                      *reg;       // UART peripheral pointer
  UART_INFO                 *info;      // Run-Time Information
  UART_TRANSFER_INFO        *xfer;      // UART transfer information
  uint8_t                    dma_use_tx;
  uint8_t                    dma_use_rx;
  uint16_t                   reserved;
} UART_RESOURCES;

// Global functions and variables exported by driver .c module
#ifdef USART1_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART1;
#endif

#ifdef USART2_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART2;
#endif

#ifdef USART3_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART3;
#endif

#ifdef USART4_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART4;
#endif

#ifdef USART5_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART5;
#endif

#ifdef USART6_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART6;
#endif

#ifdef USART7_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART7;
#endif

#ifdef USART8_MODE_ASYNC
extern ARM_DRIVER_USART Driver_USART8;
#endif

#endif

#endif /* HAL_UART_MODULE_ENABLED */
#endif /* __UART_STM32F0XX_H */
