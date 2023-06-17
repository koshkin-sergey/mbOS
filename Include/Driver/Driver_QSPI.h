/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved.
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
 * $Date:        4 Sep 2019
 * $Revision:    V1.0
 *
 * Project:      QUAD SPI (QUAD Serial Peripheral Interface) Driver definitions
 */

/* History:
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_QSPI_H_
#define DRIVER_QSPI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver/Driver_Common.h"

#define QSPI_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */


/****** QSPI Control Codes *****/

#define QSPI_CONTROL_Pos                 0
#define QSPI_CONTROL_Msk                (0xFFUL << QSPI_CONTROL_Pos)

/*----- QSPI Control Codes: Mode -----*/
#define QSPI_MODE_INDIRECT              (0x00UL << QSPI_CONTROL_Pos)            ///< QSPI Indirect functional mode
#define QSPI_MODE_AUTO_POLLING          (0x01UL << QSPI_CONTROL_Pos)            ///< QSPI Auto-polling functional mode
#define QSPI_MODE_MEMORY_MAPPED         (0x02UL << QSPI_CONTROL_Pos)            ///< QSPI Memory-mapped functional mode

/*----- QSPI Control Codes: Mode Parameters: Data rate mode -----*/
#define QSPI_DATA_RATE_MODE_Pos          8
#define QSPI_DATA_RATE_MODE_Msk         (1UL << QSPI_DATA_RATE_MODE_Pos)
#define QSPI_SDR_MODE                   (0UL << QSPI_DATA_RATE_MODE_Pos)        ///< QSPI operates in single data rate mode
#define QSPI_DDR_MODE                   (1UL << QSPI_DATA_RATE_MODE_Pos)        ///< QSPI operates in double data rate mode

/*----- QSPI Control Codes: Mode Parameters: Dual-flash mode -----*/
#define QSPI_DUAL_FLASH_MODE_Pos         9
#define QSPI_DUAL_FLASH_MODE_Msk        (1UL << QSPI_DUAL_FLASH_MODE_Pos)
#define QSPI_NOT_DUAL_FLASH_MODE        (0UL << QSPI_DUAL_FLASH_MODE_Pos)       ///< QSPI is not in dual-flash mode
#define QSPI_DUAL_FLASH_MODE            (1UL << QSPI_DUAL_FLASH_MODE_Pos)       ///< QSPI is in dual-flash mode

/*----- QSPI Control Codes: Mode Parameters: OpCode phase mode -----*/
#define QSPI_OPCODE_BITS_Pos             8
#define QSPI_OPCODE_BITS_Msk            (3UL << QSPI_OPCODE_BITS_Pos)
#define QSPI_OPCODE_BITS(n)             (((n) & 3UL) << QSPI_OPCODE_BITS_Pos)   ///< Number of OpCode bits sent at a time

/*----- QSPI Control Codes: Mode Parameters: Address phase mode -----*/
#define QSPI_ADDRESS_BITS_Pos            10
#define QSPI_ADDRESS_BITS_Msk           (3UL << QSPI_ADDRESS_BITS_Pos)
#define QSPI_ADDRESS_BITS(n)            (((n) & 3UL) << QSPI_ADDRESS_BITS_Pos)  ///< Number of Address bits sent at a time

/*----- QSPI Control Codes: Mode Parameters: Alternate-bytes phase mode -----*/
#define QSPI_ALT_BYTES_BITS_Pos          12
#define QSPI_ALT_BYTES_BITS_Msk         (3UL << QSPI_ALT_BYTES_BITS_Pos)
#define QSPI_ALT_BYTES_BITS(n)          (((n) & 3UL) << QSPI_ALT_BYTES_BITS_Pos)///< Number of Alternate-bytes bits sent at a time

/*----- QSPI Control Codes: Mode Parameters: Data phase mode -----*/
#define QSPI_DATA_BITS_Pos               14
#define QSPI_DATA_BITS_Msk              (3UL << QSPI_DATA_BITS_Pos)
#define QSPI_DATA_BITS(n)               (((n) & 3UL) << QSPI_DATA_BITS_Pos)     ///< Number of Data bits sent at a time

/*----- SPI Control Codes: Miscellaneous Controls  -----*/
#define QSPI_SET_BUS_SPEED              (0x10UL << QSPI_CONTROL_Pos)            ///< Set Bus Speed in bps; arg = value
#define QSPI_GET_BUS_SPEED              (0x11UL << QSPI_CONTROL_Pos)            ///< Get Bus Speed in bps
#define QSPI_ABORT_TRANSFER             (0x12UL << QSPI_CONTROL_Pos)            ///< Abort current data transfer

/****** QSPI specific error codes *****/
#define QSPI_ERROR_MODE                 (ARM_DRIVER_ERROR_SPECIFIC - 1)         ///< Specified Mode not supported


/**
\brief QSPI Status
*/
typedef volatile struct _QSPI_STATUS {
  uint32_t busy       : 1;              ///< Transmitter/Receiver busy flag
  uint32_t data_lost  : 1;              ///< Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint32_t reserved   : 30;
} QSPI_STATUS;


/****** QSPI Event *****/
#define QSPI_EVENT_TRANSFER_COMPLETE    (1UL << 0)  ///< Data Transfer completed
#define QSPI_EVENT_DATA_LOST            (1UL << 1)  ///< Data lost: Receive overflow / Transmit underflow


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION QSPI_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          QSPI_CAPABILITIES QSPI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref QSPI_CAPABILITIES

  \fn          int32_t QSPI_Initialize (QSPI_SignalEvent_t cb_event)
  \brief       Initialize QSPI Interface.
  \param[in]   cb_event  Pointer to QSPI_SignalEvent
  \return      \ref execution_status

  \fn          int32_t QSPI_Uninitialize (void)
  \brief       De-initialize QSPI Interface.
  \return      \ref execution_status

  \fn          int32_t QSPI_PowerControl (ARM_POWER_STATE state)
  \brief       Control QSPI Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t QSPI_Send (const void *data, uint32_t num)
  \brief       Start sending data to QSPI transmitter.
  \param[in]   data  Pointer to buffer with data to send to QSPI transmitter
  \param[in]   num   Number of data items to send
  \return      \ref execution_status

  \fn          int32_t QSPI_Receive (void *data, uint32_t num)
  \brief       Start receiving data from QSPI receiver.
  \param[out]  data  Pointer to buffer for data to receive from QSPI receiver
  \param[in]   num   Number of data items to receive
  \return      \ref execution_status

  \fn          uint32_t QSPI_GetDataCount (void)
  \brief       Get transferred data count.
  \return      number of data items transferred

  \fn          int32_t QSPI_Control (uint32_t control, uint32_t arg)
  \brief       Control QSPI Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      common \ref execution_status and driver specific \ref qspi_execution_status

  \fn          QSPI_STATUS QSPI_GetStatus (void)
  \brief       Get QSPI status.
  \return      QSPI status \ref QSPI_STATUS

  \fn          void QSPI_SignalEvent (uint32_t event)
  \brief       Signal QSPI Events.
  \param[in]   event \ref QSPI_events notification mask
  \return      none
*/

typedef void (*QSPI_SignalEvent_t)(uint32_t event);  ///< Pointer to QSPI_SignalEvent : Signal QSPI Event.


/**
\brief QSPI Driver Capabilities.
*/
typedef struct _QSPI_CAPABILITIES {
  uint32_t indirect_mode      : 1;      ///< all the operations are performed using the QSPI registers
  uint32_t memory_mapped_mode : 1;      ///< the external Flash memory is mapped to the address space
  uint32_t ddr_mode           : 1;      ///< supports DDR Mode
  uint32_t dual_flash         : 1;      ///< supports Dual-flash Mode
  uint32_t reserved           : 28;     ///< Reserved (must be zero)
} QSPI_CAPABILITIES;


/**
\brief Access structure of the QSPI Driver.
*/
typedef struct _DRIVER_QSPI {
  ARM_DRIVER_VERSION   (*GetVersion)      (void);                             ///< Pointer to QSPI_GetVersion : Get driver version.
  QSPI_CAPABILITIES    (*GetCapabilities) (void);                             ///< Pointer to QSPI_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (QSPI_SignalEvent_t cb_event);      ///< Pointer to QSPI_Initialize : Initialize QSPI Interface.
  int32_t              (*Uninitialize)    (void);                             ///< Pointer to QSPI_Uninitialize : De-initialize QSPI Interface.
  int32_t              (*PowerControl)    (ARM_POWER_STATE state);            ///< Pointer to QSPI_PowerControl : Control QSPI Interface Power.
  int32_t              (*Send)            (const void *data, uint32_t num);   ///< Pointer to QSPI_Send : Start sending data to QSPI Interface.
  int32_t              (*Receive)         (      void *data, uint32_t num);   ///< Pointer to QSPI_Receive : Start receiving data from QSPI Interface.
  uint32_t             (*GetDataCount)    (void);                             ///< Pointer to QSPI_GetDataCount : Get transferred data count.
  int32_t              (*Control)         (uint32_t control, uint32_t arg);   ///< Pointer to QSPI_Control : Control QSPI Interface.
  QSPI_STATUS          (*GetStatus)       (void);                             ///< Pointer to QSPI_GetStatus : Get QSPI status.
} const DRIVER_QSPI;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_QSPI_H_ */
