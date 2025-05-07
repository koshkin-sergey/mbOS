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
 * $Date:        24. January 2020
 * $Revision:    V2.3
 *
 * Project:      Flash Driver definitions
 */

/* History:
 *  Version 2.3
 *    Removed volatile from FLASH_STATUS
 *  Version 2.2
 *    Padding bytes added to FLASH_INFO
 *  Version 2.1
 *    FLASH_STATUS made volatile
 *  Version 2.0
 *    Renamed driver NOR -> Flash (more generic)
 *    Non-blocking operation
 *    Added Events, Status and Capabilities
 *    Linked Flash information (GetInfo)
 *  Version 1.11
 *    Changed prefix DRV -> DRIVER
 *  Version 1.10
 *    Namespace prefix  added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_FLASH_H_
#define DRIVER_FLASH_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define FLASH_API_VERSION     DRIVER_VERSION_MAJOR_MINOR(2,3)  /* API version */


#define _Driver_Flash_(n)      Driver_Flash##n
#define  Driver_Flash_(n)     _Driver_Flash_(n)


#define FLASH_SECTOR_INFO(addr,size) { (addr), (addr)+(size)-1 }

/**
\brief Flash Sector information
*/
typedef struct _FLASH_SECTOR {
  uint32_t start;                       ///< Sector Start address
  uint32_t end;                         ///< Sector End address (start+size-1)
} const FLASH_SECTOR;

/**
\brief Flash information
*/
typedef struct _FLASH_INFO {
  FLASH_SECTOR     *sector_info;        ///< Sector layout information (NULL=Uniform sectors)
  uint32_t          sector_count;       ///< Number of sectors
  uint32_t          sector_size;        ///< Uniform sector size in bytes (0=sector_info used) 
  uint32_t          page_size;          ///< Optimal programming page size in bytes
  uint32_t          program_unit;       ///< Smallest programmable unit in bytes
  uint8_t           erased_value;       ///< Contents of erased memory (usually 0xFF)
  uint8_t           reserved[3];        ///< Reserved (must be zero)
} const FLASH_INFO;


/**
\brief Flash Status
*/
typedef struct _FLASH_STATUS {
  uint32_t busy     : 1;                ///< Flash busy flag
  uint32_t error    : 1;                ///< Read/Program/Erase error flag (cleared on start of next operation)
  uint32_t reserved : 30;
} FLASH_STATUS;


/****** Flash Event *****/
#define FLASH_EVENT_READY               (1UL << 0)  ///< Flash Ready
#define FLASH_EVENT_ERROR               (1UL << 1)  ///< Read/Program/Erase Error


// Function documentation
/**
  \fn          DRIVER_VERSION Flash_GetVersion (void)
  \brief       Get driver version.
  \return      \ref DRIVER_VERSION
*/
/**
  \fn          FLASH_CAPABILITIES Flash_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref FLASH_CAPABILITIES
*/
/**
  \fn          int32_t Flash_Initialize (Flash_SignalEvent_t cb_event)
  \brief       Initialize the Flash Interface.
  \param[in]   cb_event  Pointer to \ref Flash_SignalEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t Flash_Uninitialize (void)
  \brief       De-initialize the Flash Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t Flash_PowerControl (POWER_STATE state)
  \brief       Control the Flash interface power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t Flash_ReadData (uint32_t addr, void *data, uint32_t cnt)
  \brief       Read data from Flash.
  \param[in]   addr  Data address.
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   cnt   Number of data items to read.
  \return      number of data items read or \ref execution_status
*/
/**
  \fn          int32_t Flash_ProgramData (uint32_t addr, const void *data, uint32_t cnt)
  \brief       Program data to Flash.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or \ref execution_status
*/
/**
  \fn          int32_t Flash_EraseSector (uint32_t addr)
  \brief       Erase Flash Sector.
  \param[in]   addr  Sector address
  \return      \ref execution_status
*/
/**
  \fn          int32_t Flash_EraseChip (void)
  \brief       Erase complete Flash.
               Optional function for faster full chip erase.
  \return      \ref execution_status
*/
/**
  \fn          FLASH_STATUS Flash_GetStatus (void)
  \brief       Get Flash status.
  \return      Flash status \ref FLASH_STATUS
*/
/**
  \fn          FLASH_INFO * Flash_GetInfo (void)
  \brief       Get Flash information.
  \return      Pointer to Flash information \ref FLASH_INFO
*/

/**
  \fn          void Flash_SignalEvent (uint32_t event)
  \brief       Signal Flash event.
  \param[in]   event  Event notification mask
  \return      none
*/

typedef void (*Flash_SignalEvent_t) (uint32_t event);    ///< Pointer to \ref Flash_SignalEvent : Signal Flash Event.


/**
\brief Flash Driver Capabilities.
*/
typedef struct _FLASH_CAPABILITIES {
  uint32_t event_ready  : 1;            ///< Signal Flash Ready event
  uint32_t data_width   : 2;            ///< Data width: 0=8-bit, 1=16-bit, 2=32-bit
  uint32_t erase_chip   : 1;            ///< Supports EraseChip operation
  uint32_t reserved     : 28;           ///< Reserved (must be zero)
} FLASH_CAPABILITIES;


/**
\brief Access structure of the Flash Driver
*/
typedef struct _DRIVER_FLASH {
  DRIVER_VERSION     (*GetVersion)     (void);                                          ///< Pointer to \ref Flash_GetVersion : Get driver version.
  FLASH_CAPABILITIES (*GetCapabilities)(void);                                          ///< Pointer to \ref Flash_GetCapabilities : Get driver capabilities.
  int32_t            (*Initialize)     (Flash_SignalEvent_t cb_event);                  ///< Pointer to \ref Flash_Initialize : Initialize Flash Interface.
  int32_t            (*Uninitialize)   (void);                                          ///< Pointer to \ref Flash_Uninitialize : De-initialize Flash Interface.
  int32_t            (*PowerControl)   (POWER_STATE state);                             ///< Pointer to \ref Flash_PowerControl : Control Flash Interface Power.
  int32_t            (*ReadData)       (uint32_t addr,       void *data, uint32_t cnt); ///< Pointer to \ref Flash_ReadData : Read data from Flash.
  int32_t            (*ProgramData)    (uint32_t addr, const void *data, uint32_t cnt); ///< Pointer to \ref Flash_ProgramData : Program data to Flash.
  int32_t            (*EraseSector)    (uint32_t addr);                                 ///< Pointer to \ref Flash_EraseSector : Erase Flash Sector.
  int32_t            (*EraseChip)      (void);                                          ///< Pointer to \ref Flash_EraseChip : Erase complete Flash.
  FLASH_STATUS       (*GetStatus)      (void);                                          ///< Pointer to \ref Flash_GetStatus : Get Flash status.
  FLASH_INFO *       (*GetInfo)        (void);                                          ///< Pointer to \ref Flash_GetInfo : Get Flash information.
} const DRIVER_FLASH;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_FLASH_H_ */
