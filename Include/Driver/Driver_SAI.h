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
 * $Revision:    V1.2
 *
 * Project:      SAI (Serial Audio Interface) Driver definitions
 */

/* History:
 *  Version 1.2
 *    Removed volatile from SAI_STATUS
 *  Version 1.1
 *    SAI_STATUS made volatile
 *  Version 1.0
 *    Initial release
 */

#ifndef DRIVER_SAI_H_
#define DRIVER_SAI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define SAI_API_VERSION      DRIVER_VERSION_MAJOR_MINOR(1,2)  /* API version */


#define _Driver_SAI_(n)      Driver_SAI##n
#define  Driver_SAI_(n)     _Driver_SAI_(n)


/****** SAI Control Codes *****/

#define SAI_CONTROL_Msk             (0xFFUL)
#define SAI_CONFIGURE_TX            (0x01UL)    ///< Configure Transmitter;  arg1 and arg2 provide additional configuration
#define SAI_CONFIGURE_RX            (0x02UL)    ///< Configure Receiver;     arg1 and arg2 provide additional configuration
#define SAI_CONTROL_TX              (0x03UL)    ///< Control Transmitter;    arg1.0: 0=disable (default), 1=enable; arg1.1: mute
#define SAI_CONTROL_RX              (0x04UL)    ///< Control Receiver;       arg1.0: 0=disable (default), 1=enable
#define SAI_MASK_SLOTS_TX           (0x05UL)    ///< Mask Transmitter slots; arg1 = mask (bit: 0=active, 1=inactive); all configured slots are active by default
#define SAI_MASK_SLOTS_RX           (0x06UL)    ///< Mask Receiver    slots; arg1 = mask (bit: 0=active, 1=inactive); all configured slots are active by default
#define SAI_ABORT_SEND              (0x07UL)    ///< Abort \ref SAI_Send
#define SAI_ABORT_RECEIVE           (0x08UL)    ///< Abort \ref SAI_Receive

/*----- SAI Control Codes: Configuration Parameters: Mode -----*/
#define SAI_MODE_Pos                 8
#define SAI_MODE_Msk                (1UL << SAI_MODE_Pos)
#define SAI_MODE_MASTER             (1UL << SAI_MODE_Pos)               ///< Master Mode
#define SAI_MODE_SLAVE              (0UL << SAI_MODE_Pos)               ///< Slave Mode (default)

/*----- SAI Control Codes: Configuration Parameters: Synchronization -----*/
#define SAI_SYNCHRONIZATION_Pos      9
#define SAI_SYNCHRONIZATION_Msk     (1UL << SAI_SYNCHRONIZATION_Pos)
#define SAI_ASYNCHRONOUS            (0UL << SAI_SYNCHRONIZATION_Pos)    ///< Asynchronous (default)
#define SAI_SYNCHRONOUS             (1UL << SAI_SYNCHRONIZATION_Pos)    ///< Synchronous

/*----- SAI Control Codes: Configuration Parameters: Protocol -----*/
#define SAI_PROTOCOL_Pos             10
#define SAI_PROTOCOL_Msk            (7UL << SAI_PROTOCOL_Pos)
#define SAI_PROTOCOL_USER           (0UL << SAI_PROTOCOL_Pos)           ///< User defined (default) 
#define SAI_PROTOCOL_I2S            (1UL << SAI_PROTOCOL_Pos)           ///< I2S
#define SAI_PROTOCOL_MSB_JUSTIFIED  (2UL << SAI_PROTOCOL_Pos)           ///< MSB (left) justified 
#define SAI_PROTOCOL_LSB_JUSTIFIED  (3UL << SAI_PROTOCOL_Pos)           ///< LSB (right) justified
#define SAI_PROTOCOL_PCM_SHORT      (4UL << SAI_PROTOCOL_Pos)           ///< PCM with short frame
#define SAI_PROTOCOL_PCM_LONG       (5UL << SAI_PROTOCOL_Pos)           ///< PCM with long frame
#define SAI_PROTOCOL_AC97           (6UL << SAI_PROTOCOL_Pos)           ///< AC'97

/*----- SAI Control Codes: Configuration Parameters: Data Size -----*/
#define SAI_DATA_SIZE_Pos            13
#define SAI_DATA_SIZE_Msk                      (0x1FUL  << SAI_DATA_SIZE_Pos)
#define SAI_DATA_SIZE(n)            ((((n)-1UL)&0x1FUL) << SAI_DATA_SIZE_Pos) ///< Data size in bits (8..32)

/*----- SAI Control Codes: Configuration Parameters: Bit Order -----*/
#define SAI_BIT_ORDER_Pos            18
#define SAI_BIT_ORDER_Msk           (1UL << SAI_BIT_ORDER_Pos)
#define SAI_MSB_FIRST               (0UL << SAI_BIT_ORDER_Pos)          ///< Data is transferred with MSB first (default)
#define SAI_LSB_FIRST               (1UL << SAI_BIT_ORDER_Pos)          ///< Data is transferred with LSB first; User Protocol only (ignored otherwise)

/*----- SAI Control Codes: Configuration Parameters: Mono Mode -----*/
#define SAI_MONO_MODE               (1UL << 19)                         ///< Mono Mode (only for I2S, MSB/LSB justified)

/*----- SAI Control Codes:Configuration Parameters: Companding -----*/
#define SAI_COMPANDING_Pos           20
#define SAI_COMPANDING_Msk          (3UL << SAI_COMPANDING_Pos)
#define SAI_COMPANDING_NONE         (0UL << SAI_COMPANDING_Pos)         ///< No companding (default)
#define SAI_COMPANDING_A_LAW        (2UL << SAI_COMPANDING_Pos)         ///< A-Law companding
#define SAI_COMPANDING_U_LAW        (3UL << SAI_COMPANDING_Pos)         ///< u-Law companding

/*----- SAI Control Codes: Configuration Parameters: Clock Polarity -----*/
#define SAI_CLOCK_POLARITY_Pos       23
#define SAI_CLOCK_POLARITY_Msk      (1UL << SAI_CLOCK_POLARITY_Pos)
#define SAI_CLOCK_POLARITY_0        (0UL << SAI_CLOCK_POLARITY_Pos)     ///< Drive on falling edge, Capture on rising  edge (default)
#define SAI_CLOCK_POLARITY_1        (1UL << SAI_CLOCK_POLARITY_Pos)     ///< Drive on rising  edge, Capture on falling edge

/*----- SAI Control Codes: Configuration Parameters: Master Clock Pin -----*/
#define SAI_MCLK_PIN_Pos             24
#define SAI_MCLK_PIN_Msk            (3UL << SAI_MCLK_PIN_Pos)
#define SAI_MCLK_PIN_INACTIVE       (0UL << SAI_MCLK_PIN_Pos)           ///< MCLK not used (default)
#define SAI_MCLK_PIN_OUTPUT         (1UL << SAI_MCLK_PIN_Pos)           ///< MCLK is output (Master only)
#define SAI_MCLK_PIN_INPUT          (2UL << SAI_MCLK_PIN_Pos)           ///< MCLK is input  (Master only)


/****** SAI Configuration (arg1) *****/

/*----- SAI Configuration (arg1): Frame Length -----*/
#define SAI_FRAME_LENGTH_Pos          0
#define SAI_FRAME_LENGTH_Msk                    (0x3FFUL  << SAI_FRAME_LENGTH_Pos)
#define SAI_FRAME_LENGTH(n)          ((((n)-1UL)&0x3FFUL) << SAI_FRAME_LENGTH_Pos)  ///< Frame length in bits (8..1024); default depends on protocol and data

/*----- SAI Configuration (arg1): Frame Sync Width -----*/
#define SAI_FRAME_SYNC_WIDTH_Pos      10
#define SAI_FRAME_SYNC_WIDTH_Msk                (0xFFUL  << SAI_FRAME_SYNC_WIDTH_Pos)
#define SAI_FRAME_SYNC_WIDTH(n)      ((((n)-1UL)&0xFFUL) << SAI_FRAME_SYNC_WIDTH_Pos) ///< Frame Sync width in bits (1..256); default=1; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Frame Sync Polarity -----*/
#define SAI_FRAME_SYNC_POLARITY_Pos   18
#define SAI_FRAME_SYNC_POLARITY_Msk  (1UL << SAI_FRAME_SYNC_POLARITY_Pos)
#define SAI_FRAME_SYNC_POLARITY_HIGH (0UL << SAI_FRAME_SYNC_POLARITY_Pos)           ///< Frame Sync is active high (default); User Protocol only (ignored otherwise)
#define SAI_FRAME_SYNC_POLARITY_LOW  (1UL << SAI_FRAME_SYNC_POLARITY_Pos)           ///< Frame Sync is active low; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Frame Sync Early -----*/
#define SAI_FRAME_SYNC_EARLY         (1UL << 19)                                    ///< Frame Sync one bit before the first bit of the frame; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Slot Count -----*/
#define SAI_SLOT_COUNT_Pos            20
#define SAI_SLOT_COUNT_Msk                      (0x1FUL  << SAI_SLOT_COUNT_Pos)
#define SAI_SLOT_COUNT(n)            ((((n)-1UL)&0x1FUL) << SAI_SLOT_COUNT_Pos)     ///< Number of slots in frame (1..32); default=1; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Slot Size -----*/
#define SAI_SLOT_SIZE_Pos             25
#define SAI_SLOT_SIZE_Msk            (3UL << SAI_SLOT_SIZE_Pos)
#define SAI_SLOT_SIZE_DEFAULT        (0UL << SAI_SLOT_SIZE_Pos)                     ///< Slot size is equal to data size (default)
#define SAI_SLOT_SIZE_16             (1UL << SAI_SLOT_SIZE_Pos)                     ///< Slot size = 16 bits; User Protocol only (ignored otherwise)
#define SAI_SLOT_SIZE_32             (3UL << SAI_SLOT_SIZE_Pos)                     ///< Slot size = 32 bits; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Slot Offset -----*/
#define SAI_SLOT_OFFSET_Pos           27
#define SAI_SLOT_OFFSET_Msk               (0x1FUL  << SAI_SLOT_OFFSET_Pos)
#define SAI_SLOT_OFFSET(n)           (((n)&0x1FUL) << SAI_SLOT_OFFSET_Pos)          ///< Offset of first data bit in slot (0..31); default=0; User Protocol only (ignored otherwise)

/****** SAI Configuration (arg2) *****/

/*----- SAI Control Codes: Configuration Parameters: Audio Frequency (Master only) -----*/
#define SAI_AUDIO_FREQ_Msk          (0x0FFFFFUL)                                    ///< Audio frequency mask

/*----- SAI Control Codes: Configuration Parameters: Master Clock Prescaler (Master only and MCLK Pin) -----*/
#define SAI_MCLK_PRESCALER_Pos       20
#define SAI_MCLK_PRESCALER_Msk      (0xFFFUL << SAI_MCLK_PRESCALER_Pos)
#define SAI_MCLK_PRESCALER(n)       ((((n)-1UL)&0xFFFUL) << SAI_MCLK_PRESCALER_Pos) ///< MCLK prescaler; Audio_frequency = MCLK/n; n = 1..4096 (default=1)


/****** SAI specific error codes *****/
#define SAI_ERROR_SYNCHRONIZATION       (DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Synchronization not supported
#define SAI_ERROR_PROTOCOL              (DRIVER_ERROR_SPECIFIC - 2)     ///< Specified Protocol not supported
#define SAI_ERROR_DATA_SIZE             (DRIVER_ERROR_SPECIFIC - 3)     ///< Specified Data size not supported
#define SAI_ERROR_BIT_ORDER             (DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Bit order not supported
#define SAI_ERROR_MONO_MODE             (DRIVER_ERROR_SPECIFIC - 5)     ///< Specified Mono mode not supported
#define SAI_ERROR_COMPANDING            (DRIVER_ERROR_SPECIFIC - 6)     ///< Specified Companding not supported
#define SAI_ERROR_CLOCK_POLARITY        (DRIVER_ERROR_SPECIFIC - 7)     ///< Specified Clock polarity not supported
#define SAI_ERROR_AUDIO_FREQ            (DRIVER_ERROR_SPECIFIC - 8)     ///< Specified Audio frequency not supported
#define SAI_ERROR_MCLK_PIN              (DRIVER_ERROR_SPECIFIC - 9)     ///< Specified MCLK Pin setting not supported
#define SAI_ERROR_MCLK_PRESCALER        (DRIVER_ERROR_SPECIFIC - 10)    ///< Specified MCLK Prescaler not supported
#define SAI_ERROR_FRAME_LENGTH          (DRIVER_ERROR_SPECIFIC - 11)    ///< Specified Frame length not supported
#define SAI_ERROR_FRAME_LENGHT          (DRIVER_ERROR_SPECIFIC - 11)    ///< Specified Frame length not supported @deprecated use \ref SAI_ERROR_FRAME_LENGTH instead
#define SAI_ERROR_FRAME_SYNC_WIDTH      (DRIVER_ERROR_SPECIFIC - 12)    ///< Specified Frame Sync width not supported
#define SAI_ERROR_FRAME_SYNC_POLARITY   (DRIVER_ERROR_SPECIFIC - 13)    ///< Specified Frame Sync polarity not supported
#define SAI_ERROR_FRAME_SYNC_EARLY      (DRIVER_ERROR_SPECIFIC - 14)    ///< Specified Frame Sync early not supported
#define SAI_ERROR_SLOT_COUNT            (DRIVER_ERROR_SPECIFIC - 15)    ///< Specified Slot count not supported
#define SAI_ERROR_SLOT_SIZE             (DRIVER_ERROR_SPECIFIC - 16)    ///< Specified Slot size not supported
#define SAI_ERROR_SLOT_OFFESET          (DRIVER_ERROR_SPECIFIC - 17)    ///< Specified Slot offset not supported


/**
\brief SAI Status
*/
typedef struct _SAI_STATUS {
  uint32_t tx_busy          : 1;        ///< Transmitter busy flag
  uint32_t rx_busy          : 1;        ///< Receiver busy flag
  uint32_t tx_underflow     : 1;        ///< Transmit data underflow detected (cleared on start of next send operation)
  uint32_t rx_overflow      : 1;        ///< Receive data overflow detected (cleared on start of next receive operation)
  uint32_t frame_error      : 1;        ///< Sync Frame error detected (cleared on start of next send/receive operation)
  uint32_t reserved         : 27;
} SAI_STATUS;


/****** SAI Event *****/
#define SAI_EVENT_SEND_COMPLETE     (1UL << 0)  ///< Send completed
#define SAI_EVENT_RECEIVE_COMPLETE  (1UL << 1)  ///< Receive completed
#define SAI_EVENT_TX_UNDERFLOW      (1UL << 2)  ///< Transmit data not available
#define SAI_EVENT_RX_OVERFLOW       (1UL << 3)  ///< Receive data overflow
#define SAI_EVENT_FRAME_ERROR       (1UL << 4)  ///< Sync Frame error in Slave mode (optional)


// Function documentation
/**
  \fn          DRIVER_VERSION SAI_GetVersion (void)
  \brief       Get driver version.
  \return      \ref DRIVER_VERSION

  \fn          SAI_CAPABILITIES SAI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref SAI_CAPABILITIES

  \fn          int32_t SAI_Initialize (SAI_SignalEvent_t cb_event)
  \brief       Initialize SAI Interface.
  \param[in]   cb_event  Pointer to \ref SAI_SignalEvent
  \return      \ref execution_status

  \fn          int32_t SAI_Uninitialize (void)
  \brief       De-initialize SAI Interface.
  \return      \ref execution_status

  \fn          int32_t SAI_PowerControl (POWER_STATE state)
  \brief       Control SAI Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t SAI_Send (const void *data, uint32_t num)
  \brief       Start sending data to SAI transmitter.
  \param[in]   data  Pointer to buffer with data to send to SAI transmitter
  \param[in]   num   Number of data items to send
  \return      \ref execution_status

  \fn          int32_t SAI_Receive (void *data, uint32_t num)
  \brief       Start receiving data from SAI receiver.
  \param[out]  data  Pointer to buffer for data to receive from SAI receiver
  \param[in]   num   Number of data items to receive
  \return      \ref execution_status

  \fn          uint32_t SAI_GetTxCount (void)
  \brief       Get transmitted data count.
  \return      number of data items transmitted

  \fn          uint32_t SAI_GetRxCount (void)
  \brief       Get received data count.
  \return      number of data items received

  \fn          int32_t SAI_Control (uint32_t control, uint32_t arg1, uint32_t arg2)
  \brief       Control SAI Interface.
  \param[in]   control  Operation
  \param[in]   arg1     Argument 1 of operation (optional)
  \param[in]   arg2     Argument 2 of operation (optional)
  \return      common \ref execution_status and driver specific \ref sai_execution_status

  \fn          SAI_STATUS SAI_GetStatus (void)
  \brief       Get SAI status.
  \return      SAI status \ref SAI_STATUS

  \fn          void SAI_SignalEvent (uint32_t event)
  \brief       Signal SAI Events.
  \param[in]   event \ref SAI_events notification mask
  \return      none
*/

typedef void (*SAI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref SAI_SignalEvent : Signal SAI Event.


/**
\brief SAI Driver Capabilities.
*/
typedef struct _SAI_CAPABILITIES {
  uint32_t asynchronous          : 1;   ///< supports asynchronous Transmit/Receive
  uint32_t synchronous           : 1;   ///< supports synchronous Transmit/Receive
  uint32_t protocol_user         : 1;   ///< supports user defined Protocol
  uint32_t protocol_i2s          : 1;   ///< supports I2S Protocol
  uint32_t protocol_justified    : 1;   ///< supports MSB/LSB justified Protocol
  uint32_t protocol_pcm          : 1;   ///< supports PCM short/long frame Protocol
  uint32_t protocol_ac97         : 1;   ///< supports AC'97 Protocol
  uint32_t mono_mode             : 1;   ///< supports Mono mode
  uint32_t companding            : 1;   ///< supports Companding
  uint32_t mclk_pin              : 1;   ///< supports MCLK (Master Clock) pin
  uint32_t event_frame_error     : 1;   ///< supports Frame error event: \ref SAI_EVENT_FRAME_ERROR
  uint32_t reserved              : 21;  ///< Reserved (must be zero)
} SAI_CAPABILITIES;


/**
\brief Access structure of the SAI Driver.
*/
typedef struct _DRIVER_SAI {
  DRIVER_VERSION   (*GetVersion)      (void);                                            ///< Pointer to \ref SAI_GetVersion : Get driver version.
  SAI_CAPABILITIES (*GetCapabilities) (void);                                            ///< Pointer to \ref SAI_GetCapabilities : Get driver capabilities.
  int32_t          (*Initialize)      (SAI_SignalEvent_t cb_event);                      ///< Pointer to \ref SAI_Initialize : Initialize SAI Interface.
  int32_t          (*Uninitialize)    (void);                                            ///< Pointer to \ref SAI_Uninitialize : De-initialize SAI Interface.
  int32_t          (*PowerControl)    (POWER_STATE state);                               ///< Pointer to \ref SAI_PowerControl : Control SAI Interface Power.
  int32_t          (*Send)            (const void *data, uint32_t num);                  ///< Pointer to \ref SAI_Send : Start sending data to SAI Interface.
  int32_t          (*Receive)         (      void *data, uint32_t num);                  ///< Pointer to \ref SAI_Receive : Start receiving data from SAI Interface.
  uint32_t         (*GetTxCount)      (void);                                            ///< Pointer to \ref SAI_GetTxCount : Get transmitted data count.
  uint32_t         (*GetRxCount)      (void);                                            ///< Pointer to \ref SAI_GetRxCount : Get received data count.
  int32_t          (*Control)         (uint32_t control, uint32_t arg1, uint32_t arg2);  ///< Pointer to \ref SAI_Control : Control SAI Interface.
  SAI_STATUS       (*GetStatus)       (void);                                            ///< Pointer to \ref SAI_GetStatus : Get SAI status.
} const DRIVER_SAI;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_SAI_H_ */
