/******************************************************************************
 * @file    thread_ble.c
 * @brief   Thread for Bluetooth LE stack.
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
#include <BLE/ble.h>

#include "../Middleware/BlueNRG_MS/hci/transport_layer/hci_le.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STK_SIZE               (512U)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

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

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void UserEvtRx(void *data)
{
  hci_event_t *evt = (hci_event_t *)data;

  hci_reset();
}

static void BLE_Init(void)
{
  HCI_IO_t hci_io = {
    .Init    = BLE_InitTransportLayer,
    .DeInit  = BLE_DeInit,
    .Reset   = BLE_Reset,
    .Send    = BLE_Send,
  };

  HCI_Init(UserEvtRx, NULL, &hci_io);
}

__NO_RETURN static
void thread_ble(void *param)
{
  (void) param;

  DEBUG_LOG("Created thread for Bluetooth LE stack\r\n");
  BLE_Init();

  for(;;) {
    osDelay(500);
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void CreateThreadBluetooth(void)
 * @brief       Create Bluetooth thread.
 *
 */
void CreateThreadBluetooth(void)
{
  osThreadNew(thread_ble, NULL, &thread_attr);
}

/* ----------------------------- End of file ---------------------------------*/
