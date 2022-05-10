/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 */

#ifndef DRIVER_FLASH_H_
#define DRIVER_FLASH_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* Return codes */
#define FLASH_DRIVER_OK                 0     ///< Operation succeeded
#define FLASH_DRIVER_ERROR             -1     ///< Unspecified error
#define FLASH_DRIVER_ERROR_PARAMETER   -2     ///< Parameter error

/****** Flash Event *****/
#define FLASH_EVENT_READY               (1UL << 0)  ///< Flash Ready
#define FLASH_EVENT_ERROR               (1UL << 1)  ///< Program/Erase Error

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef void (*FLASH_SignalEvent_t)(uint32_t event);

/**
\brief Flash Sector information
*/
typedef struct FLASH_SECTOR_s {
  uint32_t start;                       ///< Sector Start address
  uint32_t end;                         ///< Sector End address (start+size-1)
} const FLASH_SECTOR_t;

/**
\brief Flash memory information
*/
typedef struct FLASH_INFO_s {
  uint32_t          flash_base;         ///< Flash Base Address
  FLASH_SECTOR_t   *sector_info;        ///< Sector layout information (NULL=Uniform sectors)
  uint32_t          sector_count;       ///< Number of sectors
  uint32_t          sector_size;        ///< Uniform sector size in bytes (0=sector_info used)
  uint32_t          program_unit;       ///< Smallest programmable unit in bytes
} const FLASH_INFO_t;

/* Function documentation */

/**
 * @fn          int32_t Initialize(FLASH_SignalEvent_t cb_event)
 * @brief       Initialize FLASH Interface.
 * @param[in]   cb_event  Pointer to FLASH_SignalEvent_t
 * @return      Execution status
 *                - FLASH_DRIVER_OK              : Operation successful
 *                - FLASH_DRIVER_ERROR           : Operation failed
 */
/**
 * @fn          int32_t Uninitialize(void)
 * @brief       De-initialize FLASH Interface.
 * @return      Execution status
 *                - FLASH_DRIVER_OK              : Operation successful
 *                - FLASH_DRIVER_ERROR           : Operation failed
 */
/**
 * @fn          int32_t EraseSector(uint32_t)
 * @brief       Erase Flash Sector.
 * @param[in]   addr  Sector address
 * @return      Execution status
 *                - FLASH_DRIVER_OK              : Operation successful
 *                - FLASH_DRIVER_ERROR           : Operation failed
 *                - FLASH_DRIVER_ERROR_PARAMETER : Parameter error
 */
/**
 * @fn          int32_t EraseChip(void)
 * @brief       Erase complete Flash.
 * @return      Execution status
 *                - FLASH_DRIVER_OK              : Operation successful
 *                - FLASH_DRIVER_ERROR           : Operation failed
 */
/**
 * @fn          int32_t ProgramData(uint32_t addr, const void *data, size_t size)
 * @brief       Program data to Flash.
 * @param[in]   addr  Data address.
 * @param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
 * @param[in]   size  Data size (in byte).
 * @return      Execution status
 *                - FLASH_DRIVER_OK              : Operation successful
 *                - FLASH_DRIVER_ERROR           : Operation failed
 *                - FLASH_DRIVER_ERROR_PARAMETER : Parameter error
 */

/**
\brief Access structure of the FLASH Driver.
*/
typedef struct Driver_FLASH_s {
  int32_t (*Initialize)   (FLASH_SignalEvent_t cb_event);
  int32_t (*Uninitialize) (void);
  int32_t (*EraseSector)  (uint32_t addr);
  int32_t (*EraseChip)    (void);
  int32_t (*ProgramData)  (uint32_t addr, const void *data, size_t size);
} const Driver_FLASH_t;

/*******************************************************************************
 *  exported global variable
 ******************************************************************************/

extern FLASH_INFO_t   FLASH_Info;
extern Driver_FLASH_t Driver_Flash0;

#endif /* DRIVER_FLASH_H_ */
