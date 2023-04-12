/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Flash Driver for ADI ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "FEE_ADUCM32x.h"

#if defined(USE_FEE)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define ARM_FLASH_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

#define FLASH_SECTOR_INFO           NULL
#define FLASH_SECTOR_COUNT          128U
#define FLASH_SECTOR_SIZE           2048U
#define FLASH_PAGE_SIZE             8U
#define FLASH_PROGRAM_UNIT          8U
#define FLASH_ERASED_VALUE          0xFFU

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Flash Information */
static ARM_FLASH_INFO FlashInfo = {
  FLASH_SECTOR_INFO,
  FLASH_SECTOR_COUNT,
  FLASH_SECTOR_SIZE,
  FLASH_PAGE_SIZE,
  FLASH_PROGRAM_UNIT,
  FLASH_ERASED_VALUE,
  {0U, 0U, 0U}
};

/* Flash Status */
static ARM_FLASH_STATUS FlashStatus;

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_FLASH_API_VERSION,
  ARM_FLASH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
  1U, /* event_ready */
  2U, /* data_width = 0:8-bit, 1:16-bit, 2:32-bit */
  1U, /* erase_chip */
  0U  /* reserved (must be zero) */
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static ARM_DRIVER_VERSION Flash_GetVersion(void)
{
  return (DriverVersion);
}

static ARM_FLASH_CAPABILITIES Flash_GetCapabilities(void)
{
  return (DriverCapabilities);
}

static int32_t Flash_Initialize(ARM_Flash_SignalEvent_t cb_event)
{
  return (ARM_DRIVER_OK);
}

static int32_t Flash_Uninitialize(void)
{
  return (ARM_DRIVER_OK);
}

static int32_t Flash_PowerControl(ARM_POWER_STATE state)
{
  switch (state) {
    case ARM_POWER_OFF:
      break;

    case ARM_POWER_LOW:
      break;

    case ARM_POWER_FULL:
      break;
  }

  return (ARM_DRIVER_OK);
}

static int32_t Flash_ReadData(uint32_t addr, void *data, uint32_t cnt)
{
  return (ARM_DRIVER_OK);
}

static int32_t Flash_ProgramData(uint32_t addr, const void *data, uint32_t cnt)
{
  return (ARM_DRIVER_OK);
}

static int32_t Flash_EraseSector(uint32_t addr)
{
  return (ARM_DRIVER_OK);
}

static int32_t Flash_EraseChip(void)
{
  return (ARM_DRIVER_OK);
}

static ARM_FLASH_STATUS Flash_GetStatus(void)
{
  return (FlashStatus);
}

static ARM_FLASH_INFO* Flash_GetInfo(void)
{
  return (&FlashInfo);
}

extern \
void FLASH_IRQHandler(void);
void FLASH_IRQHandler(void)
{

}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

extern \
ARM_DRIVER_FLASH Driver_Flash;
ARM_DRIVER_FLASH Driver_Flash = {
  Flash_GetVersion,
  Flash_GetCapabilities,
  Flash_Initialize,
  Flash_Uninitialize,
  Flash_PowerControl,
  Flash_ReadData,
  Flash_ProgramData,
  Flash_EraseSector,
  Flash_EraseChip,
  Flash_GetStatus,
  Flash_GetInfo
};

#endif /* defined(USE_FEE) */
