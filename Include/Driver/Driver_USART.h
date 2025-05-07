/*
 * Copyright (c) 2013-2020 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
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
 * $Date:        31. March 2020
 * $Revision:    V2.4
 *
 * Project:      USART (Universal Synchronous Asynchronous Receiver Transmitter)
 *               Driver definitions
 */

/* History:
 *  Version 2.4
 *    Removed volatile from USART_STATUS and USART_MODEM_STATUS
 *  Version 2.3
 *    USART_STATUS and USART_MODEM_STATUS made volatile
 *  Version 2.2
 *    Corrected USART_CPOL_Pos and USART_CPHA_Pos definitions 
 *  Version 2.1
 *    Removed optional argument parameter from Signal Event
 *  Version 2.0
 *    New simplified driver:
 *      complexity moved to upper layer (especially data handling)
 *      more unified API for different communication interfaces
 *      renamed driver UART -> USART (Asynchronous & Synchronous)
 *    Added modes:
 *      Synchronous
 *      Single-wire
 *      IrDA
 *      Smart Card  
 *    Changed prefix DRV -> DRIVER
 *  Version 1.10
 *    Namespace prefix  added
 *  Version 1.01
 *    Added events:
 *      UART_EVENT_TX_EMPTY,     UART_EVENT_RX_TIMEOUT
 *      UART_EVENT_TX_THRESHOLD, UART_EVENT_RX_THRESHOLD
 *    Added functions: SetTxThreshold, SetRxThreshold
 *    Added "rx_timeout_event" to capabilities
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_USART_H_
#define DRIVER_USART_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define USART_API_VERSION      DRIVER_VERSION_MAJOR_MINOR(2,4)  /* API version */


#define _Driver_USART_(n)      Driver_USART##n
#define  Driver_USART_(n)     _Driver_USART_(n)


/****** USART Control Codes *****/

#define USART_CONTROL_Pos                0
#define USART_CONTROL_Msk               (0xFFUL << USART_CONTROL_Pos)

/*----- USART Control Codes: Mode -----*/
#define USART_MODE_ASYNCHRONOUS         (0x01UL << USART_CONTROL_Pos)   ///< UART (Asynchronous); arg = Baudrate
#define USART_MODE_SYNCHRONOUS_MASTER   (0x02UL << USART_CONTROL_Pos)   ///< Synchronous Master (generates clock signal); arg = Baudrate
#define USART_MODE_SYNCHRONOUS_SLAVE    (0x03UL << USART_CONTROL_Pos)   ///< Synchronous Slave (external clock signal)
#define USART_MODE_SINGLE_WIRE          (0x04UL << USART_CONTROL_Pos)   ///< UART Single-wire (half-duplex); arg = Baudrate
#define USART_MODE_IRDA                 (0x05UL << USART_CONTROL_Pos)   ///< UART IrDA; arg = Baudrate
#define USART_MODE_SMART_CARD           (0x06UL << USART_CONTROL_Pos)   ///< UART Smart Card; arg = Baudrate

/*----- USART Control Codes: Mode Parameters: Data Bits -----*/
#define USART_DATA_BITS_Pos              8
#define USART_DATA_BITS_Msk             (7UL << USART_DATA_BITS_Pos)
#define USART_DATA_BITS_5               (5UL << USART_DATA_BITS_Pos)    ///< 5 Data bits
#define USART_DATA_BITS_6               (6UL << USART_DATA_BITS_Pos)    ///< 6 Data bit
#define USART_DATA_BITS_7               (7UL << USART_DATA_BITS_Pos)    ///< 7 Data bits
#define USART_DATA_BITS_8               (0UL << USART_DATA_BITS_Pos)    ///< 8 Data bits (default)
#define USART_DATA_BITS_9               (1UL << USART_DATA_BITS_Pos)    ///< 9 Data bits

/*----- USART Control Codes: Mode Parameters: Parity -----*/
#define USART_PARITY_Pos                 12
#define USART_PARITY_Msk                (3UL << USART_PARITY_Pos)
#define USART_PARITY_NONE               (0UL << USART_PARITY_Pos)       ///< No Parity (default)
#define USART_PARITY_EVEN               (1UL << USART_PARITY_Pos)       ///< Even Parity
#define USART_PARITY_ODD                (2UL << USART_PARITY_Pos)       ///< Odd Parity

/*----- USART Control Codes: Mode Parameters: Stop Bits -----*/
#define USART_STOP_BITS_Pos              14
#define USART_STOP_BITS_Msk             (3UL << USART_STOP_BITS_Pos)
#define USART_STOP_BITS_1               (0UL << USART_STOP_BITS_Pos)    ///< 1 Stop bit (default)
#define USART_STOP_BITS_2               (1UL << USART_STOP_BITS_Pos)    ///< 2 Stop bits
#define USART_STOP_BITS_1_5             (2UL << USART_STOP_BITS_Pos)    ///< 1.5 Stop bits
#define USART_STOP_BITS_0_5             (3UL << USART_STOP_BITS_Pos)    ///< 0.5 Stop bits

/*----- USART Control Codes: Mode Parameters: Flow Control -----*/
#define USART_FLOW_CONTROL_Pos           16
#define USART_FLOW_CONTROL_Msk          (3UL << USART_FLOW_CONTROL_Pos)
#define USART_FLOW_CONTROL_NONE         (0UL << USART_FLOW_CONTROL_Pos) ///< No Flow Control (default)
#define USART_FLOW_CONTROL_RTS          (1UL << USART_FLOW_CONTROL_Pos) ///< RTS Flow Control
#define USART_FLOW_CONTROL_CTS          (2UL << USART_FLOW_CONTROL_Pos) ///< CTS Flow Control
#define USART_FLOW_CONTROL_RTS_CTS      (3UL << USART_FLOW_CONTROL_Pos) ///< RTS/CTS Flow Control

/*----- USART Control Codes: Mode Parameters: Clock Polarity (Synchronous mode) -----*/
#define USART_CPOL_Pos                   18
#define USART_CPOL_Msk                  (1UL << USART_CPOL_Pos)
#define USART_CPOL0                     (0UL << USART_CPOL_Pos)         ///< CPOL = 0 (default)
#define USART_CPOL1                     (1UL << USART_CPOL_Pos)         ///< CPOL = 1

/*----- USART Control Codes: Mode Parameters: Clock Phase (Synchronous mode) -----*/
#define USART_CPHA_Pos                   19
#define USART_CPHA_Msk                  (1UL << USART_CPHA_Pos)
#define USART_CPHA0                     (0UL << USART_CPHA_Pos)         ///< CPHA = 0 (default)
#define USART_CPHA1                     (1UL << USART_CPHA_Pos)         ///< CPHA = 1


/*----- USART Control Codes: Miscellaneous Controls  -----*/
#define USART_SET_DEFAULT_TX_VALUE      (0x10UL << USART_CONTROL_Pos)   ///< Set default Transmit value (Synchronous Receive only); arg = value
#define USART_SET_IRDA_PULSE            (0x11UL << USART_CONTROL_Pos)   ///< Set IrDA Pulse in ns; arg: 0=3/16 of bit period  
#define USART_SET_SMART_CARD_GUARD_TIME (0x12UL << USART_CONTROL_Pos)   ///< Set Smart Card Guard Time; arg = number of bit periods
#define USART_SET_SMART_CARD_CLOCK      (0x13UL << USART_CONTROL_Pos)   ///< Set Smart Card Clock in Hz; arg: 0=Clock not generated
#define USART_CONTROL_SMART_CARD_NACK   (0x14UL << USART_CONTROL_Pos)   ///< Smart Card NACK generation; arg: 0=disabled, 1=enabled
#define USART_CONTROL_TX                (0x15UL << USART_CONTROL_Pos)   ///< Transmitter; arg: 0=disabled, 1=enabled
#define USART_CONTROL_RX                (0x16UL << USART_CONTROL_Pos)   ///< Receiver; arg: 0=disabled, 1=enabled
#define USART_CONTROL_BREAK             (0x17UL << USART_CONTROL_Pos)   ///< Continuous Break transmission; arg: 0=disabled, 1=enabled
#define USART_ABORT_SEND                (0x18UL << USART_CONTROL_Pos)   ///< Abort \ref USART_Send
#define USART_ABORT_RECEIVE             (0x19UL << USART_CONTROL_Pos)   ///< Abort \ref USART_Receive
#define USART_ABORT_TRANSFER            (0x1AUL << USART_CONTROL_Pos)   ///< Abort \ref USART_Transfer



/****** USART specific error codes *****/
#define USART_ERROR_MODE                (DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Mode not supported
#define USART_ERROR_BAUDRATE            (DRIVER_ERROR_SPECIFIC - 2)     ///< Specified baudrate not supported
#define USART_ERROR_DATA_BITS           (DRIVER_ERROR_SPECIFIC - 3)     ///< Specified number of Data bits not supported
#define USART_ERROR_PARITY              (DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Parity not supported
#define USART_ERROR_STOP_BITS           (DRIVER_ERROR_SPECIFIC - 5)     ///< Specified number of Stop bits not supported
#define USART_ERROR_FLOW_CONTROL        (DRIVER_ERROR_SPECIFIC - 6)     ///< Specified Flow Control not supported
#define USART_ERROR_CPOL                (DRIVER_ERROR_SPECIFIC - 7)     ///< Specified Clock Polarity not supported
#define USART_ERROR_CPHA                (DRIVER_ERROR_SPECIFIC - 8)     ///< Specified Clock Phase not supported


/**
\brief USART Status
*/
typedef struct _USART_STATUS {
  uint32_t tx_busy          : 1;        ///< Transmitter busy flag
  uint32_t rx_busy          : 1;        ///< Receiver busy flag
  uint32_t tx_underflow     : 1;        ///< Transmit data underflow detected (cleared on start of next send operation)
  uint32_t rx_overflow      : 1;        ///< Receive data overflow detected (cleared on start of next receive operation)
  uint32_t rx_break         : 1;        ///< Break detected on receive (cleared on start of next receive operation)
  uint32_t rx_framing_error : 1;        ///< Framing error detected on receive (cleared on start of next receive operation)
  uint32_t rx_parity_error  : 1;        ///< Parity error detected on receive (cleared on start of next receive operation)
  uint32_t reserved         : 25;
} USART_STATUS;

/**
\brief USART Modem Control
*/
typedef enum _USART_MODEM_CONTROL {
  USART_RTS_CLEAR,                      ///< Deactivate RTS
  USART_RTS_SET,                        ///< Activate RTS
  USART_DTR_CLEAR,                      ///< Deactivate DTR
  USART_DTR_SET                         ///< Activate DTR
} USART_MODEM_CONTROL;

/**
\brief USART Modem Status
*/
typedef struct _USART_MODEM_STATUS {
  uint32_t cts      : 1;                ///< CTS state: 1=Active, 0=Inactive
  uint32_t dsr      : 1;                ///< DSR state: 1=Active, 0=Inactive
  uint32_t dcd      : 1;                ///< DCD state: 1=Active, 0=Inactive
  uint32_t ri       : 1;                ///< RI  state: 1=Active, 0=Inactive
  uint32_t reserved : 28;
} USART_MODEM_STATUS;


/****** USART Event *****/
#define USART_EVENT_SEND_COMPLETE       (1UL << 0)  ///< Send completed; however USART may still transmit data
#define USART_EVENT_RECEIVE_COMPLETE    (1UL << 1)  ///< Receive completed
#define USART_EVENT_TRANSFER_COMPLETE   (1UL << 2)  ///< Transfer completed
#define USART_EVENT_TX_COMPLETE         (1UL << 3)  ///< Transmit completed (optional)
#define USART_EVENT_TX_UNDERFLOW        (1UL << 4)  ///< Transmit data not available (Synchronous Slave)
#define USART_EVENT_RX_OVERFLOW         (1UL << 5)  ///< Receive data overflow
#define USART_EVENT_RX_TIMEOUT          (1UL << 6)  ///< Receive character timeout (optional)
#define USART_EVENT_RX_BREAK            (1UL << 7)  ///< Break detected on receive
#define USART_EVENT_RX_FRAMING_ERROR    (1UL << 8)  ///< Framing error detected on receive
#define USART_EVENT_RX_PARITY_ERROR     (1UL << 9)  ///< Parity error detected on receive
#define USART_EVENT_CTS                 (1UL << 10) ///< CTS state changed (optional)
#define USART_EVENT_DSR                 (1UL << 11) ///< DSR state changed (optional)
#define USART_EVENT_DCD                 (1UL << 12) ///< DCD state changed (optional)
#define USART_EVENT_RI                  (1UL << 13) ///< RI  state changed (optional)


// Function documentation
/**
  \fn          DRIVER_VERSION USART_GetVersion (void)
  \brief       Get driver version.
  \return      \ref DRIVER_VERSION

  \fn          USART_CAPABILITIES USART_GetCapabilities (void)
  \brief       Get driver capabilities
  \return      \ref USART_CAPABILITIES

  \fn          int32_t USART_Initialize (USART_SignalEvent_t cb_event)
  \brief       Initialize USART Interface.
  \param[in]   cb_event  Pointer to \ref USART_SignalEvent
  \return      \ref execution_status

  \fn          int32_t USART_Uninitialize (void)
  \brief       De-initialize USART Interface.
  \return      \ref execution_status

  \fn          int32_t USART_PowerControl (POWER_STATE state)
  \brief       Control USART Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t USART_Send (const void *data, uint32_t num)
  \brief       Start sending data to USART transmitter.
  \param[in]   data  Pointer to buffer with data to send to USART transmitter
  \param[in]   num   Number of data items to send
  \return      \ref execution_status

  \fn          int32_t USART_Receive (void *data, uint32_t num)
  \brief       Start receiving data from USART receiver.
  \param[out]  data  Pointer to buffer for data to receive from USART receiver
  \param[in]   num   Number of data items to receive
  \return      \ref execution_status

  \fn          int32_t USART_Transfer (const void *data_out,
                                                 void *data_in,
                                           uint32_t    num)
  \brief       Start sending/receiving data to/from USART transmitter/receiver.
  \param[in]   data_out  Pointer to buffer with data to send to USART transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from USART receiver
  \param[in]   num       Number of data items to transfer
  \return      \ref execution_status

  \fn          uint32_t USART_GetTxCount (void)
  \brief       Get transmitted data count.
  \return      number of data items transmitted

  \fn          uint32_t USART_GetRxCount (void)
  \brief       Get received data count.
  \return      number of data items received

  \fn          int32_t USART_Control (uint32_t control, uint32_t arg)
  \brief       Control USART Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      common \ref execution_status and driver specific \ref usart_execution_status

  \fn          USART_STATUS USART_GetStatus (void)
  \brief       Get USART status.
  \return      USART status \ref USART_STATUS

  \fn          int32_t USART_SetModemControl (USART_MODEM_CONTROL control)
  \brief       Set USART Modem Control line state.
  \param[in]   control  \ref USART_MODEM_CONTROL
  \return      \ref execution_status 

  \fn          USART_MODEM_STATUS USART_GetModemStatus (void)
  \brief       Get USART Modem Status lines state.
  \return      modem status \ref USART_MODEM_STATUS

  \fn          void USART_SignalEvent (uint32_t event)
  \brief       Signal USART Events.
  \param[in]   event  \ref USART_events notification mask
  \return      none
*/

typedef void (*USART_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref USART_SignalEvent : Signal USART Event.


/**
\brief USART Device Driver Capabilities.
*/
typedef struct _USART_CAPABILITIES {
  uint32_t asynchronous       : 1;      ///< supports UART (Asynchronous) mode 
  uint32_t synchronous_master : 1;      ///< supports Synchronous Master mode
  uint32_t synchronous_slave  : 1;      ///< supports Synchronous Slave mode
  uint32_t single_wire        : 1;      ///< supports UART Single-wire mode
  uint32_t irda               : 1;      ///< supports UART IrDA mode
  uint32_t smart_card         : 1;      ///< supports UART Smart Card mode
  uint32_t smart_card_clock   : 1;      ///< Smart Card Clock generator available
  uint32_t flow_control_rts   : 1;      ///< RTS Flow Control available
  uint32_t flow_control_cts   : 1;      ///< CTS Flow Control available
  uint32_t event_tx_complete  : 1;      ///< Transmit completed event: \ref USART_EVENT_TX_COMPLETE
  uint32_t event_rx_timeout   : 1;      ///< Signal receive character timeout event: \ref USART_EVENT_RX_TIMEOUT
  uint32_t rts                : 1;      ///< RTS Line: 0=not available, 1=available
  uint32_t cts                : 1;      ///< CTS Line: 0=not available, 1=available
  uint32_t dtr                : 1;      ///< DTR Line: 0=not available, 1=available
  uint32_t dsr                : 1;      ///< DSR Line: 0=not available, 1=available
  uint32_t dcd                : 1;      ///< DCD Line: 0=not available, 1=available
  uint32_t ri                 : 1;      ///< RI Line: 0=not available, 1=available
  uint32_t event_cts          : 1;      ///< Signal CTS change event: \ref USART_EVENT_CTS
  uint32_t event_dsr          : 1;      ///< Signal DSR change event: \ref USART_EVENT_DSR
  uint32_t event_dcd          : 1;      ///< Signal DCD change event: \ref USART_EVENT_DCD
  uint32_t event_ri           : 1;      ///< Signal RI change event: \ref USART_EVENT_RI
  uint32_t reserved           : 11;     ///< Reserved (must be zero)
} USART_CAPABILITIES;


/**
\brief Access structure of the USART Driver.
*/
typedef struct _DRIVER_USART {
  DRIVER_VERSION     (*GetVersion)      (void);                              ///< Pointer to \ref USART_GetVersion : Get driver version.
  USART_CAPABILITIES (*GetCapabilities) (void);                              ///< Pointer to \ref USART_GetCapabilities : Get driver capabilities.
  int32_t            (*Initialize)      (USART_SignalEvent_t cb_event);      ///< Pointer to \ref USART_Initialize : Initialize USART Interface.
  int32_t            (*Uninitialize)    (void);                              ///< Pointer to \ref USART_Uninitialize : De-initialize USART Interface.
  int32_t            (*PowerControl)    (POWER_STATE state);                 ///< Pointer to \ref USART_PowerControl : Control USART Interface Power.
  int32_t            (*Send)            (const void *data, uint32_t num);    ///< Pointer to \ref USART_Send : Start sending data to USART transmitter.
  int32_t            (*Receive)         (      void *data, uint32_t num);    ///< Pointer to \ref USART_Receive : Start receiving data from USART receiver.
  int32_t            (*Transfer)        (const void *data_out,
                                               void *data_in,
                                         uint32_t    num);                   ///< Pointer to \ref USART_Transfer : Start sending/receiving data to/from USART.
  uint32_t           (*GetTxCount)      (void);                              ///< Pointer to \ref USART_GetTxCount : Get transmitted data count.
  uint32_t           (*GetRxCount)      (void);                              ///< Pointer to \ref USART_GetRxCount : Get received data count.
  int32_t            (*Control)         (uint32_t control, uint32_t arg);    ///< Pointer to \ref USART_Control : Control USART Interface.
  USART_STATUS       (*GetStatus)       (void);                              ///< Pointer to \ref USART_GetStatus : Get USART status.
  int32_t            (*SetModemControl) (USART_MODEM_CONTROL control);       ///< Pointer to \ref USART_SetModemControl : Set USART Modem Control line state.
  USART_MODEM_STATUS (*GetModemStatus)  (void);                              ///< Pointer to \ref USART_GetModemStatus : Get USART Modem Status lines state.
} const DRIVER_USART;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_USART_H_ */
