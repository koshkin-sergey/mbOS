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

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

// Function documentation
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

extern Driver_FLASH_t Flash;

#endif /* DRIVER_FLASH_H_ */
