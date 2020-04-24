/******************************************************************************
 * @file    thread_ble_tl.c
 * @brief   Thread for BlueNRG-MS transport layer.
 * @author  Sergey Koshkin
 * @version V1.0.0
 ******************************************************************************/
/*
 * Copyright (C) 2020 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "app.h"
#include <asm/EXTI_STM32F7xx.h>
#include <CMSIS/Driver/Driver_SPI.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STK_SIZE               (512U)
#define DRIVER_SPI_NUM                 1

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern ARM_DRIVER_SPI ARM_Driver_SPI_(DRIVER_SPI_NUM);

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThread_t           thread_cb;
static uint64_t             thread_stack[THREAD_STK_SIZE/8U];
static const osThreadAttr_t thread_attr = {
  .name       = NULL,
  .attr_bits  = 0U,
  .cb_mem     = &thread_cb,
  .cb_size    = sizeof(thread_cb),
  .stack_mem  = &thread_stack[0],
  .stack_size = sizeof(thread_stack),
  .priority   = osPriorityNormal,
};

static ARM_DRIVER_SPI *driver_spi = &ARM_Driver_SPI_(DRIVER_SPI_NUM);

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void SPI_Callback(uint32_t event)
{

}

__NO_RETURN static
void thread_ble_tl(void *param)
{
  (void) param;
  int32_t ret;

  DEBUG_LOG("Created thread for BLE transport layer\r\n");
  driver_spi->Initialize(SPI_Callback);
  driver_spi->PowerControl(ARM_POWER_FULL);
  ret = driver_spi->Control(ARM_SPI_MODE_MASTER  |
                            ARM_SPI_CPOL0_CPHA0  |
                            ARM_SPI_SS_MASTER_SW |
                            ARM_SPI_DATA_BITS(8), 8000000);
  if (ret != ARM_DRIVER_OK) {
    DEBUG_LOG("Error SPI interface configuration %d\r\n", ret);
    osThreadExit();
  }
  ret = driver_spi->Control(ARM_SPI_GET_BUS_SPEED, 0U);
  DEBUG_LOG("BLE module SPI interface clock = %d Hz\r\n", ret);

  for(;;) {
    osDelay(500);
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void CreateThreadBleTransportLayer(const void*)
 * @brief       Create BLE transport layer thread.
 *
 * @param[in]   pConf  Pointer to configuration struct
 */
void CreateThreadBleTransportLayer(const void* pConf)
{
  osThreadNew(thread_ble_tl, (void*)pConf, &thread_attr);
}

/* ----------------------------- End of file ---------------------------------*/
