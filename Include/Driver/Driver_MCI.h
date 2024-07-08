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
 * Project:      MCI (Memory Card Interface) Driver definitions
 */

/* History:
 *  Version 2.4
 *    Removed volatile from MCI_STATUS
 *  Version 2.3
 *    MCI_STATUS made volatile
 *  Version 2.2
 *    Added timeout and error flags to MCI_STATUS
 *    Added support for controlling optional RST_n pin (eMMC)
 *    Removed explicit Clock Control (MCI_CONTROL_CLOCK)
 *    Removed event MCI_EVENT_BOOT_ACK_TIMEOUT
 *  Version 2.1
 *    Decoupled SPI mode from MCI driver
 *    Replaced function MCI_CardSwitchRead with MCI_ReadCD and MCI_ReadWP
 *  Version 2.0
 *    Added support for:
 *      SD UHS-I (Ultra High Speed)
 *      SD I/O Interrupt
 *      Read Wait (SD I/O)
 *      Suspend/Resume (SD I/O)
 *      MMC Interrupt
 *      MMC Boot
 *      Stream Data transfer (MMC)
 *      VCCQ Power Supply Control (eMMC)
 *      Command Completion Signal (CCS) for CE-ATA
 *    Added MCI_Control function
 *    Added MCI_GetStatus function
 *    Removed MCI_BusMode, MCI_BusDataWidth, MCI_BusSingaling functions
 *      (replaced by MCI_Control)
 *    Changed MCI_CardPower function (voltage parameter)
 *    Changed MCI_SendCommnad function (flags parameter)
 *    Changed MCI_SetupTransfer function (mode parameter)
 *    Removed MCI_ReadTransfer and MCI_WriteTransfer functions
 *    Changed prefix DRV -> DRIVER
 *    Changed return values of some functions to int32_t
 *  Version 1.10
 *    Namespace prefix  added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_MCI_H_
#define DRIVER_MCI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define MCI_API_VERSION      DRIVER_VERSION_MAJOR_MINOR(2,4)  /* API version */


#define _Driver_MCI_(n)      Driver_MCI##n
#define  Driver_MCI_(n)     _Driver_MCI_(n)


/****** MCI Send Command Flags *****/
#define MCI_RESPONSE_Pos             0
#define MCI_RESPONSE_Msk            (3UL << MCI_RESPONSE_Pos)
#define MCI_RESPONSE_NONE           (0UL << MCI_RESPONSE_Pos)   ///< No response expected (default)
#define MCI_RESPONSE_SHORT          (1UL << MCI_RESPONSE_Pos)   ///< Short response (48-bit)
#define MCI_RESPONSE_SHORT_BUSY     (2UL << MCI_RESPONSE_Pos)   ///< Short response with busy signal (48-bit)
#define MCI_RESPONSE_LONG           (3UL << MCI_RESPONSE_Pos)   ///< Long response (136-bit)

#define MCI_RESPONSE_INDEX          (1UL << 2)  ///< Check command index in response
#define MCI_RESPONSE_CRC            (1UL << 3)  ///< Check CRC in response

#define MCI_WAIT_BUSY               (1UL << 4)  ///< Wait until busy before sending the command

#define MCI_TRANSFER_DATA           (1UL << 5)  ///< Activate Data transfer

#define MCI_CARD_INITIALIZE         (1UL << 6)  ///< Execute Memory Card initialization sequence

#define MCI_INTERRUPT_COMMAND       (1UL << 7)  ///< Send Interrupt command (CMD40 - MMC only)
#define MCI_INTERRUPT_RESPONSE      (1UL << 8)  ///< Send Interrupt response (CMD40 - MMC only)

#define MCI_BOOT_OPERATION          (1UL << 9)  ///< Execute Boot operation (MMC only)
#define MCI_BOOT_ALTERNATIVE        (1UL << 10) ///< Execute Alternative Boot operation (MMC only)
#define MCI_BOOT_ACK                (1UL << 11) ///< Expect Boot Acknowledge (MMC only)

#define MCI_CCSD                    (1UL << 12) ///< Send Command Completion Signal Disable (CCSD) for CE-ATA device
#define MCI_CCS                     (1UL << 13) ///< Expect Command Completion Signal (CCS) for CE-ATA device


/****** MCI Setup Transfer Mode *****/
#define MCI_TRANSFER_READ           (0UL << 0)  ///< Data Read Transfer (from MCI)
#define MCI_TRANSFER_WRITE          (1UL << 0)  ///< Data Write Transfer (to MCI)
#define MCI_TRANSFER_BLOCK          (0UL << 1)  ///< Block Data transfer (default)
#define MCI_TRANSFER_STREAM         (1UL << 1)  ///< Stream Data transfer (MMC only)


/****** MCI Control Codes *****/
#define MCI_BUS_SPEED               (0x01UL)    ///< Set Bus Speed; arg = requested speed in bits/s; returns configured speed in bits/s
#define MCI_BUS_SPEED_MODE          (0x02UL)    ///< Set Bus Speed Mode as specified with arg
#define MCI_BUS_CMD_MODE            (0x03UL)    ///< Set CMD Line Mode as specified with arg
#define MCI_BUS_DATA_WIDTH          (0x04UL)    ///< Set Bus Data Width as specified with arg
#define MCI_DRIVER_STRENGTH         (0x05UL)    ///< Set SD UHS-I Driver Strength as specified with arg 
#define MCI_CONTROL_RESET           (0x06UL)    ///< Control optional RST_n Pin (eMMC); arg: 0=inactive, 1=active 
#define MCI_CONTROL_CLOCK_IDLE      (0x07UL)    ///< Control Clock generation on CLK Pin when idle; arg: 0=disabled, 1=enabled
#define MCI_UHS_TUNING_OPERATION    (0x08UL)    ///< Sampling clock Tuning operation (SD UHS-I); arg: 0=reset, 1=execute
#define MCI_UHS_TUNING_RESULT       (0x09UL)    ///< Sampling clock Tuning result (SD UHS-I); returns: 0=done, 1=in progress, -1=error
#define MCI_DATA_TIMEOUT            (0x0AUL)    ///< Set Data timeout; arg = timeout in bus cycles
#define MCI_CSS_TIMEOUT             (0x0BUL)    ///< Set Command Completion Signal (CCS) timeout; arg = timeout in bus cycles
#define MCI_MONITOR_SDIO_INTERRUPT  (0x0CUL)    ///< Monitor SD I/O interrupt: arg: 0=disabled, 1=enabled
#define MCI_CONTROL_READ_WAIT       (0x0DUL)    ///< Control Read/Wait for SD I/O; arg: 0=disabled, 1=enabled
#define MCI_SUSPEND_TRANSFER        (0x0EUL)    ///< Suspend Data transfer (SD I/O); returns number of remaining bytes to transfer
#define MCI_RESUME_TRANSFER         (0x0FUL)    ///< Resume Data transfer (SD I/O)

/*----- MCI Bus Speed Mode -----*/
#define MCI_BUS_DEFAULT_SPEED       (0x00UL)    ///< SD/MMC: Default Speed mode up to 25/26MHz
#define MCI_BUS_HIGH_SPEED          (0x01UL)    ///< SD/MMC: High    Speed mode up to 50/52MHz
#define MCI_BUS_UHS_SDR12           (0x02UL)    ///< SD: SDR12  (Single Data Rate) up to  25MHz,  12.5MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define MCI_BUS_UHS_SDR25           (0x03UL)    ///< SD: SDR25  (Single Data Rate) up to  50MHz,  25  MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define MCI_BUS_UHS_SDR50           (0x04UL)    ///< SD: SDR50  (Single Data Rate) up to 100MHz,  50  MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define MCI_BUS_UHS_SDR104          (0x05UL)    ///< SD: SDR104 (Single Data Rate) up to 208MHz, 104  MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define MCI_BUS_UHS_DDR50           (0x06UL)    ///< SD: DDR50  (Dual Data Rate)   up to  50MHz,  50  MB/s: UHS-I (Ultra High Speed) 1.8V signaling

/*----- MCI CMD Line Mode -----*/
#define MCI_BUS_CMD_PUSH_PULL       (0x00UL)    ///< Push-Pull CMD line (default)
#define MCI_BUS_CMD_OPEN_DRAIN      (0x01UL)    ///< Open Drain CMD line (MMC only)

/*----- MCI Bus Data Width -----*/
#define MCI_BUS_DATA_WIDTH_1        (0x00UL)    ///< Bus data width: 1 bit (default)
#define MCI_BUS_DATA_WIDTH_4        (0x01UL)    ///< Bus data width: 4 bits
#define MCI_BUS_DATA_WIDTH_8        (0x02UL)    ///< Bus data width: 8 bits
#define MCI_BUS_DATA_WIDTH_4_DDR    (0x03UL)    ///< Bus data width: 4 bits, DDR (Dual Data Rate) - MMC only
#define MCI_BUS_DATA_WIDTH_8_DDR    (0x04UL)    ///< Bus data width: 8 bits, DDR (Dual Data Rate) - MMC only

/*----- MCI Driver Strength -----*/
#define MCI_DRIVER_TYPE_A           (0x01UL)    ///< SD UHS-I Driver Type A
#define MCI_DRIVER_TYPE_B           (0x00UL)    ///< SD UHS-I Driver Type B (default)
#define MCI_DRIVER_TYPE_C           (0x02UL)    ///< SD UHS-I Driver Type C
#define MCI_DRIVER_TYPE_D           (0x03UL)    ///< SD UHS-I Driver Type D


/****** MCI Card Power *****/
#define MCI_POWER_VDD_Pos            0
#define MCI_POWER_VDD_Msk           (0x0FUL << MCI_POWER_VDD_Pos)
#define MCI_POWER_VDD_OFF           (0x01UL << MCI_POWER_VDD_Pos)   ///< VDD (VCC) turned off
#define MCI_POWER_VDD_3V3           (0x02UL << MCI_POWER_VDD_Pos)   ///< VDD (VCC) = 3.3V
#define MCI_POWER_VDD_1V8           (0x03UL << MCI_POWER_VDD_Pos)   ///< VDD (VCC) = 1.8V
#define MCI_POWER_VCCQ_Pos           4
#define MCI_POWER_VCCQ_Msk          (0x0FUL << MCI_POWER_VCCQ_Pos)
#define MCI_POWER_VCCQ_OFF          (0x01UL << MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ turned off
#define MCI_POWER_VCCQ_3V3          (0x02UL << MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ = 3.3V
#define MCI_POWER_VCCQ_1V8          (0x03UL << MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ = 1.8V
#define MCI_POWER_VCCQ_1V2          (0x04UL << MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ = 1.2V


/**
\brief MCI Status
*/
typedef struct _MCI_STATUS {
  uint32_t command_active   : 1;        ///< Command active flag
  uint32_t command_timeout  : 1;        ///< Command timeout flag (cleared on start of next command)
  uint32_t command_error    : 1;        ///< Command error flag (cleared on start of next command)
  uint32_t transfer_active  : 1;        ///< Transfer active flag
  uint32_t transfer_timeout : 1;        ///< Transfer timeout flag (cleared on start of next command)
  uint32_t transfer_error   : 1;        ///< Transfer error flag (cleared on start of next command)
  uint32_t sdio_interrupt   : 1;        ///< SD I/O Interrupt flag (cleared on start of monitoring)
  uint32_t ccs              : 1;        ///< CCS flag (cleared on start of next command)
  uint32_t reserved         : 24;
} MCI_STATUS;


/****** MCI Card Event *****/
#define MCI_EVENT_CARD_INSERTED     (1UL << 0)  ///< Memory Card inserted
#define MCI_EVENT_CARD_REMOVED      (1UL << 1)  ///< Memory Card removed
#define MCI_EVENT_COMMAND_COMPLETE  (1UL << 2)  ///< Command completed
#define MCI_EVENT_COMMAND_TIMEOUT   (1UL << 3)  ///< Command timeout
#define MCI_EVENT_COMMAND_ERROR     (1UL << 4)  ///< Command response error (CRC error or invalid response)
#define MCI_EVENT_TRANSFER_COMPLETE (1UL << 5)  ///< Data transfer completed
#define MCI_EVENT_TRANSFER_TIMEOUT  (1UL << 6)  ///< Data transfer timeout
#define MCI_EVENT_TRANSFER_ERROR    (1UL << 7)  ///< Data transfer CRC failed
#define MCI_EVENT_SDIO_INTERRUPT    (1UL << 8)  ///< SD I/O Interrupt
#define MCI_EVENT_CCS               (1UL << 9)  ///< Command Completion Signal (CCS)
#define MCI_EVENT_CCS_TIMEOUT       (1UL << 10) ///< Command Completion Signal (CCS) Timeout


// Function documentation
/**
  \fn            DRIVER_VERSION MCI_GetVersion (void)
  \brief         Get driver version.
  \return        \ref DRIVER_VERSION
*/
/**
  \fn            MCI_CAPABILITIES MCI_GetCapabilities (void)
  \brief         Get driver capabilities.
  \return        \ref MCI_CAPABILITIES
*/
/**
  \fn            int32_t MCI_Initialize (MCI_SignalEvent_t cb_event)
  \brief         Initialize the Memory Card Interface
  \param[in]     cb_event  Pointer to \ref MCI_SignalEvent
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_Uninitialize (void)
  \brief         De-initialize Memory Card Interface.
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_PowerControl (POWER_STATE state)
  \brief         Control Memory Card Interface Power.
  \param[in]     state   Power state \ref POWER_STATE
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_CardPower (uint32_t voltage)
  \brief         Set Memory Card Power supply voltage.
  \param[in]     voltage  Memory Card Power supply voltage
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_ReadCD (void)
  \brief         Read Card Detect (CD) state.
  \return        1:card detected, 0:card not detected, or error
*/
/**
  \fn            int32_t MCI_ReadWP (void)
  \brief         Read Write Protect (WP) state.
  \return        1:write protected, 0:not write protected, or error
*/
/**
  \fn            int32_t MCI_SendCommand (uint32_t  cmd,
                                              uint32_t  arg,
                                              uint32_t  flags,
                                              uint32_t *response)
  \brief         Send Command to card and get the response.
  \param[in]     cmd       Memory Card command
  \param[in]     arg       Command argument
  \param[in]     flags     Command flags
  \param[out]    response  Pointer to buffer for response
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_SetupTransfer (uint8_t *data,
                                                uint32_t block_count,
                                                uint32_t block_size,
                                                uint32_t mode)
  \brief         Setup read or write transfer operation.
  \param[in,out] data         Pointer to data block(s) to be written or read
  \param[in]     block_count  Number of blocks
  \param[in]     block_size   Size of a block in bytes
  \param[in]     mode         Transfer mode
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_AbortTransfer (void)
  \brief         Abort current read/write data transfer.
  \return        \ref execution_status
*/
/**
  \fn            int32_t MCI_Control (uint32_t control, uint32_t arg)
  \brief         Control MCI Interface.
  \param[in]     control  Operation
  \param[in]     arg      Argument of operation (optional)
  \return        \ref execution_status
*/
/**
  \fn            MCI_STATUS MCI_GetStatus (void)
  \brief         Get MCI status.
  \return        MCI status \ref MCI_STATUS
*/

/**
  \fn            void MCI_SignalEvent (uint32_t event)
  \brief         Callback function that signals a MCI Card Event.
  \param[in]     event \ref mci_event_gr
  \return        none
*/

typedef void (*MCI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref MCI_SignalEvent : Signal MCI Card Event.


/**
\brief  MCI Driver Capabilities.
*/
typedef struct _MCI_CAPABILITIES {
  uint32_t cd_state          : 1;       ///< Card Detect State available
  uint32_t cd_event          : 1;       ///< Signal Card Detect change event
  uint32_t wp_state          : 1;       ///< Write Protect State available
  uint32_t vdd               : 1;       ///< Supports VDD Card Power Supply Control
  uint32_t vdd_1v8           : 1;       ///< Supports 1.8 VDD Card Power Supply
  uint32_t vccq              : 1;       ///< Supports VCCQ Card Power Supply Control (eMMC)
  uint32_t vccq_1v8          : 1;       ///< Supports 1.8 VCCQ Card Power Supply (eMMC)
  uint32_t vccq_1v2          : 1;       ///< Supports 1.2 VCCQ Card Power Supply (eMMC)
  uint32_t data_width_4      : 1;       ///< Supports 4-bit data
  uint32_t data_width_8      : 1;       ///< Supports 8-bit data
  uint32_t data_width_4_ddr  : 1;       ///< Supports 4-bit data, DDR (Dual Data Rate) - MMC only
  uint32_t data_width_8_ddr  : 1;       ///< Supports 8-bit data, DDR (Dual Data Rate) - MMC only
  uint32_t high_speed        : 1;       ///< Supports SD/MMC High Speed Mode
  uint32_t uhs_signaling     : 1;       ///< Supports SD UHS-I (Ultra High Speed) 1.8V signaling 
  uint32_t uhs_tuning        : 1;       ///< Supports SD UHS-I tuning 
  uint32_t uhs_sdr50         : 1;       ///< Supports SD UHS-I SDR50  (Single Data Rate) up to  50MB/s
  uint32_t uhs_sdr104        : 1;       ///< Supports SD UHS-I SDR104 (Single Data Rate) up to 104MB/s
  uint32_t uhs_ddr50         : 1;       ///< Supports SD UHS-I DDR50  (Dual   Data Rate) up to  50MB/s
  uint32_t uhs_driver_type_a : 1;       ///< Supports SD UHS-I Driver Type A
  uint32_t uhs_driver_type_c : 1;       ///< Supports SD UHS-I Driver Type C
  uint32_t uhs_driver_type_d : 1;       ///< Supports SD UHS-I Driver Type D 
  uint32_t sdio_interrupt    : 1;       ///< Supports SD I/O Interrupt 
  uint32_t read_wait         : 1;       ///< Supports Read Wait (SD I/O)
  uint32_t suspend_resume    : 1;       ///< Supports Suspend/Resume (SD I/O)
  uint32_t mmc_interrupt     : 1;       ///< Supports MMC Interrupt 
  uint32_t mmc_boot          : 1;       ///< Supports MMC Boot 
  uint32_t rst_n             : 1;       ///< Supports RST_n Pin Control (eMMC)
  uint32_t ccs               : 1;       ///< Supports Command Completion Signal (CCS) for CE-ATA
  uint32_t ccs_timeout       : 1;       ///< Supports Command Completion Signal (CCS) timeout for CE-ATA
  uint32_t reserved          : 3;       ///< Reserved (must be zero)
} MCI_CAPABILITIES;


/**
\brief  Access structure of the MCI Driver.
*/
typedef struct _DRIVER_MCI {
  DRIVER_VERSION   (*GetVersion)     (void);                           ///< Pointer to \ref MCI_GetVersion : Get driver version.
  MCI_CAPABILITIES (*GetCapabilities)(void);                           ///< Pointer to \ref MCI_GetCapabilities : Get driver capabilities.
  int32_t          (*Initialize)     (MCI_SignalEvent_t cb_event);     ///< Pointer to \ref MCI_Initialize : Initialize MCI Interface.
  int32_t          (*Uninitialize)   (void);                           ///< Pointer to \ref MCI_Uninitialize : De-initialize MCI Interface.
  int32_t          (*PowerControl)   (POWER_STATE state);              ///< Pointer to \ref MCI_PowerControl : Control MCI Interface Power.
  int32_t          (*CardPower)      (uint32_t voltage);               ///< Pointer to \ref MCI_CardPower : Set card power supply voltage.
  int32_t          (*ReadCD)         (void);                           ///< Pointer to \ref MCI_ReadCD : Read Card Detect (CD) state.
  int32_t          (*ReadWP)         (void);                           ///< Pointer to \ref MCI_ReadWP : Read Write Protect (WP) state.
  int32_t          (*SendCommand)    (uint32_t cmd,
                                      uint32_t arg,
                                      uint32_t flags,
                                      uint32_t *response);             ///< Pointer to \ref MCI_SendCommand : Send Command to card and get the response.
  int32_t          (*SetupTransfer)  (uint8_t *data,
                                      uint32_t block_count,
                                      uint32_t block_size,
                                      uint32_t mode);                  ///< Pointer to \ref MCI_SetupTransfer : Setup data transfer operation.
  int32_t          (*AbortTransfer)  (void);                           ///< Pointer to \ref MCI_AbortTransfer : Abort current data transfer.
  int32_t          (*Control)        (uint32_t control, uint32_t arg); ///< Pointer to \ref MCI_Control : Control MCI Interface.
  MCI_STATUS       (*GetStatus)      (void);                           ///< Pointer to \ref MCI_GetStatus : Get MCI status.
} const DRIVER_MCI;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_MCI_H_ */
