/******************************************************************************
 * @file    hci_tl.c
 * @brief   STM32 BlueNRG-MS HCI Transport Layer interface
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

#include "hci_tl.h"

#include <string.h>
#include <Kernel/kernel.h>

#include "../../includes/hci_const.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STK_SIZE               512U
#define BUFFER_SIZE                   128U
#define EVENT_POOL_CNT                5U
#define HCI_DEFAULT_TIMEOUT           1000U

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

static hci_packet_t* MemoryAlloc(void);
static void MemoryFree(hci_packet_t *packet);
static void EvtRxCallback(hci_packet_t *packet);

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static HCI_IO_t io;
static UserEvtRx_t user_evt_rx;
static HCI_Context_t hciContext = {
  &io,
  &user_evt_rx,
  {
      BUFFER_SIZE,
      MemoryAlloc,
      MemoryFree,
      EvtRxCallback,
  }
};

static uint8_t buf_tx[BUFFER_SIZE];

static osThread_t           thread_async_evt_cb;
static uint64_t             thread_async_evt_stack[THREAD_STK_SIZE/8U];
static const osThreadAttr_t thread_async_evt_attr = {
  .name       = NULL,
  .attr_bits  = 0U,
  .cb_mem     = &thread_async_evt_cb,
  .cb_size    = sizeof(thread_async_evt_cb),
  .stack_mem  = &thread_async_evt_stack[0],
  .stack_size = sizeof(thread_async_evt_stack),
  .priority   = osPriorityNormal,
};

static osMemoryPoolId_t         event_pool;
static osMemoryPool_t           event_pool_cb;
static uint8_t event_pool_mem[osMemoryPoolMemSize(EVENT_POOL_CNT, BUFFER_SIZE)];
static const osMemoryPoolAttr_t event_pool_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &event_pool_cb,
  .cb_size   = sizeof(event_pool_cb),
  .mp_mem    = &event_pool_mem[0],
  .mp_size   = osMemoryPoolMemSize(EVENT_POOL_CNT, BUFFER_SIZE),
};

static osDataQueueId_t         que_async_event;
static osDataQueue_t           que_async_event_cb;
static void* que_async_event_mem[EVENT_POOL_CNT];
static const osDataQueueAttr_t que_async_event_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &que_async_event_cb,
  .cb_size   = sizeof(que_async_event_cb),
  .dq_mem    = &que_async_event_mem[0],
  .dq_size   = sizeof(que_async_event_mem),
};

static osDataQueueId_t         que_cmd_event;
static osDataQueue_t           que_cmd_event_cb;
static void* que_cmd_event_mem[EVENT_POOL_CNT];
static const osDataQueueAttr_t que_cmd_event_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &que_cmd_event_cb,
  .cb_size   = sizeof(que_cmd_event_cb),
  .dq_mem    = &que_cmd_event_mem[0],
  .dq_size   = sizeof(que_cmd_event_mem),
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static hci_packet_t* MemoryAlloc(void)
{
  return (hci_packet_t *)osMemoryPoolAlloc(event_pool, osWaitForever);
}

static void MemoryFree(hci_packet_t *packet)
{
  osMemoryPoolFree(event_pool, packet);
}

static void EvtRxCallback(hci_packet_t *packet)
{
  if (packet->type != HCI_EVENT_PACKET) {
    return;
  }

  if ((packet->event.code == EVT_CMD_COMPLETE) ||
      (packet->event.code == EVT_CMD_STATUS)) {
    osDataQueuePut(que_cmd_event, &packet, osWaitForever);
  }
  else {
    osDataQueuePut(que_async_event, &packet, osWaitForever);
  }
}

/**
 * @fn          void HCI_UserEvtProc(void *param)
 * @brief       Processing function that must be called after an event is received
 *              from HCI interface. It will call user_notify() if necessary.
 */
__NO_RETURN
static void HCI_UserEvtProc(void *param)
{
  hci_packet_t *packet;
  UserEvtRx_t   UserEvtRx = *hciContext.UserEvtRx;

  for(;;) {
    osDataQueueGet(que_async_event, &packet, osWaitForever);

    if (UserEvtRx != NULL) {
      UserEvtRx(&packet->event);
    }

    MemoryFree(packet);
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void HCI_Init(UserEvtRx_t, const void*, HCI_IO_t*)
 * @brief       Initialize the Host Controller Interface.
 *              This function must be called before any data can be received
 *              from BLE controller.
 *
 * @param[in]   UserEvtRx  ACI events callback function pointer. This callback
 *                         is triggered when an user event is received from
 *                         the BLE core device.
 * @param[in]   pConf      Configuration structure pointer
 * @param[in]   fops       The HCI IO structure managing the IO BUS
 */
void HCI_Init(UserEvtRx_t UserEvtRx, const void* pConf, const HCI_IO_t* fops)
{
  HCI_IO_t *io = hciContext.io;

  if (UserEvtRx != NULL) {
    *hciContext.UserEvtRx = UserEvtRx;
  }

  if (fops != NULL) {
    /* Register bus function */
    io->Init    = fops->Init;
    io->DeInit  = fops->DeInit;
    io->Reset   = fops->Reset;
    io->Receive = fops->Receive;
    io->Send    = fops->Send;
  }

  /* Create Event Pool */
  event_pool = osMemoryPoolNew(EVENT_POOL_CNT, BUFFER_SIZE, &event_pool_attr);
  /* Create Event Queue */
  que_async_event = osDataQueueNew(EVENT_POOL_CNT, sizeof(void*), &que_async_event_attr);
  /* Create Command Event Queue */
  que_cmd_event = osDataQueueNew(EVENT_POOL_CNT, sizeof(void*), &que_cmd_event_attr);
  /* Create Thread */
  osThreadNew(HCI_UserEvtProc, NULL, &thread_async_evt_attr);

  /* Initialize low level driver */
  if (io->Init != NULL) {
    io->Init(&hciContext.init_conf);
  }

  /* Reset Bluetooth module */
  if (io->Reset != NULL) {
    io->Reset();
  }
}

/**
 * @fn          int32_t HCI_SendReq(struct hci_request*, bool)
 * @brief       Send an HCI request either in synchronous or in asynchronous
 *              mode.
 *
 * @param[in]   r      The HCI request
 * @param[in]   async  true: if asynchronous mode,
 *                     false: if synchronous mode
 * @return      0: when success,
 *             -1: when failure
 */
int32_t HCI_SendReq(struct hci_request* r, bool async)
{
  (void)async;
  uint32_t cmd_busy;
  osStatus_t status;
  opcode_t opcode;
  HCI_IO_t *io = hciContext.io;
  hci_packet_t *packet = (hci_packet_t *)buf_tx;

  if (io->Send == NULL) {
    return (-1);
  }

  cmd_busy = 1U;

  opcode.ogf = r->ogf;
  opcode.ocf = r->ocf;
  packet->type = HCI_COMMAND_PACKET;
  packet->cmd.opcode.value = opcode.value;
  packet->cmd.plen = r->clen;
  memcpy(packet->cmd.params, r->cparam, r->clen);

  io->Send((const uint8_t *)packet, sizeof(hci_cmd_t) + r->clen +1U);

  while(cmd_busy) {
    status = osDataQueueGet(que_cmd_event, &packet, HCI_DEFAULT_TIMEOUT);
    if (status != osOK) {
      return (-1);
    }

    if (packet->event.code == EVT_CMD_STATUS) {
      hci_cs_evt_t *cmd_status_evt = (hci_cs_evt_t *)packet->event.payload;
      if (cmd_status_evt->opcode == opcode.value) {
        *(uint8_t *)(r->rparam) = cmd_status_evt->status;
      }

      if (cmd_status_evt->numcmd != 0U) {
        cmd_busy = 0U;
      }
    }
    else {
      hci_cc_evt_t *cmd_complete_evt = (hci_cc_evt_t *)packet->event.payload;
      if (cmd_complete_evt->opcode == opcode.value) {
        if (r->rlen > packet->event.plen) {
          r->rlen = packet->event.plen;
        }
        memcpy(r->rparam, cmd_complete_evt->payload, r->rlen);
      }

      if (cmd_complete_evt->numcmd != 0U) {
        cmd_busy = 0U;
      }
    }

    MemoryFree(packet);
  }

  return (0);
}
