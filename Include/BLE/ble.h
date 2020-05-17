/******************************************************************************
 * @file    ble.h
 * @brief   Header file for framework required for handling HCI interface
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

#ifndef BLE_H_
#define BLE_H_

#include <CMSIS/Core/cmsis_compiler.h>

/**
 * @brief     HCI packet indicator
 * @note      HCI does not provide the ability to differentiate the four HCI
 *            packet types. Therefore, if the HCI packets are sent via a common
 *            physical interface, an HCI packet indicator has to be added.
 */
#define HCI_COMMAND_PACKET            0x01U
#define HCI_ACL_DATA_PACKET           0x02U
#define HCI_SYNC_DATA_PACKET          0x03U
#define HCI_EVENT_PACKET              0x04U

/* Function documentation */
/**
  @fn         int32_t IO_Init(void* pConf)
  @brief      Initializes the peripherals communication with the Bluetooth
              module (via SPI, I2C, USART, ...)
  @param[in]  pConf  Pointer to configuration struct
  @return     Execution Status

  @fn         int32_t IO_DeInit(void)
  @brief      DeInitializes the peripherals communication with the Bluetooth
              module (via SPI, I2C, USART, ...)
  @return     Execution Status

  @fn         int32_t IO_Reset(void)
  @brief      Reset Bluetooth module
  @return     Execution Status

  @fn         int32_t IO_Receive(uint8_t* buffer, uint16_t size)
  @brief      Reads from Bluetooth module and store data into local buffer
  @param[out] buffer  Pointer to data buffer
  @param[in]  size    Buffer size
  @return     Number of read bytes

  @fn         int32_t IO_Send(uint8_t* buffer, uint16_t size)
  @brief      Writes data from local buffer to Bluetooth module
  @param[in]  buffer  Data buffer to be written
  @param[in]  size    Size of the data buffer
  @return     Number of bytes are written
*/

/**
 * @struct HCI_IO_s
 * @brief Structure used to manage the BUS IO operations.
 *        All the structure fields will point to functions defined at user level.
 */
typedef struct HCI_IO_s {
  int32_t (* Init)    (const void* pConf);        ///< Pointer to \ref IO_Init: IO Bus initialization.
  int32_t (* DeInit)  (void);                     ///< Pointer to \ref IO_DeInit: IO Bus de-initialization.
  int32_t (* Reset)   (void);                     ///< Pointer to \ref IO_Reset: IO Bus reset.
  int32_t (* Receive) (uint8_t*, uint16_t);       ///< Pointer to \ref IO_Receive: IO Bus data reception.
  int32_t (* Send)    (const uint8_t*, uint16_t); ///< Pointer to \ref IO_Send: IO Bus data transmission.
} HCI_IO_t;

typedef union opcode_u {
  struct {
    uint16_t ocf:10;  // OpCode Command Field
    uint16_t ogf:6;   // OpCode Group Field
  };
  uint16_t value;
} opcode_t;

typedef __PACKED_STRUCT hci_cmd_hdr_s {
  opcode_t opcode;
  uint8_t  plen;       // Parameter Total Length
  uint8_t  params[];
} hci_cmd_t;

typedef __PACKED_STRUCT hci_event_hdr_s {
  uint8_t code;
  uint8_t plen;
  uint8_t params[];
} hci_event_t;

typedef __PACKED_STRUCT hci_event_packet_s {
  uint8_t type;
  __PACKED_UNION {
    hci_cmd_t   cmd;
    hci_event_t event;
  };
} hci_packet_t;
/**
 * @fn          void (*)(void*)
 * @brief       This callback is triggered when an user event is received from
 *              the BLE core device.
 *
 * @param[in]   pData
 */
typedef void(* UserEvtRx_t)(void* pData);

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
void HCI_Init(UserEvtRx_t UserEvtRx, const void* pConf, const HCI_IO_t* fops);

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
int32_t HCI_NotifyAsynchEvt(void* pdata);

/**
 * @fn          void HCI_UserEvtProc(void)
 * @brief       Processing function that must be called after an event is received
 *              from HCI interface. It must be called outside ISR.
 *              It will call user_notify() if necessary.
 */
void HCI_UserEvtProc(void);

/**
 * @fn          int32_t HCI_GetEvent(hci_event_t*, opcode_t)
 * @brief       Get HCI Event.
 *
 * @param[out]  event   Pointer to Event buffer.
 * @param[in]   opcode
 * @return      Execution Status
 */
int32_t HCI_GetEvent(hci_event_t *event, opcode_t opcode);

/**
 * @fn          int32_t HCI_GetCmdEvent(hci_event_t*, opcode_t)
 * @brief       Get HCI Command Event.
 *
 * @param[out]  event   Pointer to Event buffer.
 * @param[in]   opcode
 * @return      Execution Status
 */
int32_t HCI_GetCmdEvent(hci_event_t *event, opcode_t opcode);

#endif /* BLE_H_ */
