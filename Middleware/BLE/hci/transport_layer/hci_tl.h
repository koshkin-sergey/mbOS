/******************************************************************************
 * @file    hci_tl.h
 * @brief   Header file for framework required for handling HCI interface.
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

#ifndef HCI_TL_H_
#define HCI_TL_H_

#include <stdbool.h>
#include <BLE/ble.h>

/**
 * @struct HCI_Context_s
 * @brief Contain the HCI context
 */
typedef struct HCI_Context_s {
  HCI_IO_t          *io;        ///< Manage the BUS IO operations.
  UserEvtRx_t       *UserEvtRx; ///< ACI events callback function pointer.
  HCI_TL_InitConf_t  init_conf;
} const HCI_Context_t;

/**
 * @struct hci_request
 * @brief Structure hosting the HCI request
 */
struct hci_request {
  uint16_t  ogf;    ///< Opcode Group Field
  uint16_t  ocf;    ///< Opcode Command Field
  uint32_t  event;  ///< HCI Event
  void     *cparam; ///< HCI Command from MCU to Host
  uint32_t  clen;   ///< Command Length
  void     *rparam; ///< Response from Host to MCU
  uint32_t  rlen;   ///< Response Length
};

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
int32_t HCI_SendReq(struct hci_request* r, bool async);

#endif /* HCI_TL_H_ */
