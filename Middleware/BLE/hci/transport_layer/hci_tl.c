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

#include "hci_tl.h"

#include <stddef.h>

static HCI_Context_t hciContext;

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
  if (UserEvtRx != NULL) {
    hciContext.UserEvtRx = UserEvtRx;
  }

  /* Register bus function */
  hciContext.io.Init    = fops->Init;
  hciContext.io.DeInit  = fops->DeInit;
  hciContext.io.Reset   = fops->Reset;
  hciContext.io.Receive = fops->Receive;
  hciContext.io.Send    = fops->Send;

  /* Initialize low level driver */
  if (hciContext.io.Init != NULL) {
    hciContext.io.Init(pConf);
  }
  /* Reset Bluetooth module */
  if (hciContext.io.Reset != NULL) {
    hciContext.io.Reset();
  }
}

/**
 * @fn          void HCI_UserEvtProc(void)
 * @brief       Processing function that must be called after an event is received
 *              from HCI interface. It must be called outside ISR.
 *              It will call user_notify() if necessary.
 */
void HCI_UserEvtProc(void)
{

}

/**
 * @fn          int32_t HCI_NotifyAsynchEvt(void*)
 * @brief       Interrupt service routine that must be called when the BlueNRG
 *              reports a packet received or an event to the host through the
 *              BlueNRG-MS interrupt line.
 *
 * @param[in]   pdata   Packet or event pointer
 * @return      0: packet/event processed
 *              1: no packet/event processed
 */
int32_t HCI_NotifyAsynchEvt(void* pdata)
{
  return 0;
}

/**
 * @fn          void hci_resume_flow(void)
 * @brief       This function resume the User Event Flow which has been stopped
 *              on return from UserEvtRx() when the User Event has not been
 *              processed.
 */
void hci_resume_flow(void)
{

}

/**
 * @fn          void hci_cmd_resp_wait(uint32_t)
 * @brief       This function is called when an ACI/HCI command is sent and the response
 *              is waited from the BLE core.
 *              The application shall implement a mechanism to not return from this function
 *              until the waited event is received.
 *              This is notified to the application with hci_cmd_resp_release().
 *              It is called from the same context the HCI command has been sent.
 *
 * @param[in]   timeout  Waiting timeout
 */
void hci_cmd_resp_wait(uint32_t timeout)
{

}

/**
 * @fn          void hci_cmd_resp_release(uint32_t)
 * @brief       This function is called when an ACI/HCI command is sent and the response is
 *              received from the BLE core.
 *
 * @param[in]   flag  Release flag
 */
void hci_cmd_resp_release(uint32_t flag)
{

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
  return 0;
}
