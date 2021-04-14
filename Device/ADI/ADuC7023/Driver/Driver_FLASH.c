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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "asm/aduc7023.h"
#include "asm/Driver_FLASH.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#if   defined ( __GNUC__ )
  #define __RAMFUNC                 __attribute__((section(".ramfunc")))
#elif defined ( __ICCARM__ )
  #define __RAMFUNC                 __ramfunc
#endif

#define FLASH_SECTOR_SIZE               (512UL)
#define FLASH_SECTOR_COUNT              (124UL)
#define FLASH_PROGRAM_UNIT              (2UL)

/* Current driver status flag definition */
#define FLASH_INITIALIZED               ((uint8_t)1)  ///< FLASH initialized

/**
 * @brief       FLASH Keys
 */
#define FLASH_KEY1                      ((uint16_t)0xFFC3U)
#define FLASH_KEY2                      ((uint16_t)0x3CFFU)

/**
 * @brief       Flash Function Mode
 */
#define FLASH_MODE_NONE                 ((uint8_t)0)
#define FLASH_MODE_ERASE_SECTOR         ((uint8_t)1)
#define FLASH_MODE_ERASE_CHIP           ((uint8_t)2)
#define FLASH_MODE_PROGRAM_PAGE         ((uint8_t)3)

#define FLASH_SECTOR_INFO(addr,size)    { (addr), (addr)+(size)-1 }

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/


/**
\brief Flash Sector information
*/
typedef struct FLASH_Sector_s {
  uint32_t start;                       ///< Sector Start address
  uint32_t end;                         ///< Sector End address (start+size-1)
} const FLASH_Sector_t;

/**
\brief Flash memory information
*/
typedef struct FLASH_Mem_Info_s {
  FLASH_Sector_t   *sector_info;        ///< Sector layout information (NULL=Uniform sectors)
  uint32_t          sector_count;       ///< Number of sectors
  uint32_t          sector_size;        ///< Uniform sector size in bytes (0=sector_info used)
  uint32_t          program_unit;       ///< Smallest programmable unit in bytes
} const FLASH_Mem_Info_t;

/**
\brief Flash information
*/
typedef struct FLASH_Info_s {
  FLASH_SignalEvent_t cb_event;
  uint16_t               *addr;
  const uint16_t         *data;
  size_t                  size;
  uint8_t                state;
  uint8_t                 mode;
  uint16_t            reserved;
} FLASH_Info_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static FLASH_Mem_Info_t mem_info = {
  NULL,
  FLASH_SECTOR_COUNT,
  FLASH_SECTOR_SIZE,
  FLASH_PROGRAM_UNIT,
};

static FLASH_Info_t FLASH_Info;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void writeflash(FLASH_Info_t *info)
{
  FLASH->ADR  = *info->addr++;          // set address
  FLASH->DAT  = *info->data++;          // set data value
  FLASH->MOD  = 0x18;
  FLASH->CON  = FLASH_CMD_SINGLE_WRITE; // write command
}

/**
 * @fn          int32_t FLASH_Initialize(FLASH_SignalEvent_t cb_event)
 * @brief       Initialize FLASH Interface.
 * @param[in]   cb_event  Pointer to FLASH_SignalEvent_t
 * @return      Execution status
 */
static int32_t FLASH_Initialize(FLASH_SignalEvent_t cb_event)
{
  FLASH_Info_t *info = &FLASH_Info;

  if (info->state == FLASH_INITIALIZED) {
    return (FLASH_DRIVER_OK);
  }

  /* Enable the erase and write commands */
  FLASH->MOD = (uint16_t)FLASH_MOD_DIS_PROT;

  /* Initialize FLASH Run-Time Resources */
  info->cb_event = cb_event;
  info->addr     = 0UL;
  info->data     = NULL;
  info->size     = 0UL;
  info->mode     = FLASH_MODE_NONE;
  info->state    = FLASH_INITIALIZED;

  return (FLASH_DRIVER_OK);
}

/**
 * @fn          int32_t FLASH_Uninitialize(void)
 * @brief       De-initialize FLASH Interface.
 * @return      Execution status
 */
static int32_t FLASH_Uninitialize(void)
{
  FLASH_Info_t *info = &FLASH_Info;

  /* Uninitialize FLASH Run-Time Resources */
  info->cb_event = NULL;
  info->state    = 0U;

  /* Protect the Flash */
  FLASH->MOD = (uint16_t)0;

  return (FLASH_DRIVER_OK);
}

/**
 * @fn          int32_t FLASH_EraseSector(uint32_t)
 * @brief       Erase Flash Sector.
 * @param[in]   addr  Sector address
 * @return      Execution status
 */
static int32_t FLASH_EraseSector(uint32_t addr)
{
  FLASH_Info_t *info = &FLASH_Info;

  if (((info->state & FLASH_INITIALIZED) == 0UL) ||
       (FLASH->STA  & FLASH_STA_BUSY   ) != 0UL) {
    return (FLASH_DRIVER_ERROR);
  }

  if (addr < FLASH_ADR_START || addr > FLASH_ADR_END) {
    return (FLASH_DRIVER_ERROR_PARAMETER);
  }

  info->mode = FLASH_MODE_ERASE_SECTOR;

  /* Start Erase Sector Command */
  FLASH->MOD = (uint16_t)0x18;
  FLASH->ADR = addr;
  FLASH->CON = FLASH_CMD_SINGLE_ERASE;

  return (FLASH_DRIVER_OK);
}

/**
 * @fn          int32_t FLASH_EraseChip(void)
 * @brief       Erase complete Flash.
 * @return      Execution status
 */
static int32_t FLASH_EraseChip(void)
{
  FLASH_Info_t *info = &FLASH_Info;

  if (((info->state & FLASH_INITIALIZED) == 0UL) ||
       (FLASH->STA  & FLASH_STA_BUSY   ) != 0UL) {
    return (FLASH_DRIVER_ERROR);
  }

  info->mode = FLASH_MODE_ERASE_CHIP;

  /* Mass Erase Block */
  FLASH->MOD = (uint16_t)0x18;
  FLASH->ADR = FLASH_KEY1;
  FLASH->DAT = FLASH_KEY2;
  FLASH->CON = FLASH_CMD_MASS_ERASE;

  return (FLASH_DRIVER_OK);
}

/**
 * @fn          int32_t FLASH_ProgramData(uint32_t addr, const void *data, size_t size)
 * @brief       Program data to Flash.
 *
 * @param[in]   addr  Data address.
 * @param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
 * @param[in]   size  Data size (in byte).
 * @return      Execution status
 */
static int32_t FLASH_ProgramData(uint32_t addr, const void *data, size_t size)
{
  FLASH_Info_t *info = &FLASH_Info;

  if (((info->state & FLASH_INITIALIZED) == 0UL) ||
       (FLASH->STA  & FLASH_STA_BUSY   ) != 0UL) {
    return (FLASH_DRIVER_ERROR);
  }

  if (addr < FLASH_ADR_START || addr > FLASH_ADR_END) {
    return (FLASH_DRIVER_ERROR_PARAMETER);
  }

  if ((data == NULL) || (size == 0UL)) {
    return (FLASH_DRIVER_ERROR_PARAMETER);
  }

  info->addr = (      uint16_t *)addr;
  info->data = (const uint16_t *)data;
  /* Adjust size for Half Words */
  info->size = ((size + 1UL) & ~1UL) >> 1UL;
  info->mode = FLASH_MODE_PROGRAM_PAGE;

  /* Start Program Command */
  writeflash(info);

  return (FLASH_DRIVER_OK);
}

void FLASH_IRQHandler(void)
{
  uint32_t event = 0UL;
  FLASH_Info_t *info = &FLASH_Info;
  register uint8_t sta = FLASH->STA;

  if ((sta & FLASH_STA_FAIL) != 0U) {
    info->mode = FLASH_MODE_NONE;
    event      = FLASH_EVENT_READY | FLASH_EVENT_ERROR;
  }
  else if (sta & FLASH_STA_PASS) {
    switch (info->mode) {
      case FLASH_MODE_ERASE_SECTOR:
        info->mode = FLASH_MODE_NONE;
        event = FLASH_EVENT_READY;
        break;

      case FLASH_MODE_ERASE_CHIP:
        info->mode = FLASH_MODE_NONE;
        event = FLASH_EVENT_READY;
        break;

      case FLASH_MODE_PROGRAM_PAGE:
        info->size--;
        if (info->size != 0UL) {
          writeflash(info);
        }
        else {
          info->mode = FLASH_MODE_NONE;
          event = FLASH_EVENT_READY;
        }
        break;

      default:
        break;
    }
  }

  if (event != 0UL && info->cb_event != NULL) {
    info->cb_event(event);
  }
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

Driver_FLASH_t Flash = {
  FLASH_Initialize,
  FLASH_Uninitialize,
  FLASH_EraseSector,
  FLASH_EraseChip,
  FLASH_ProgramData,
};

