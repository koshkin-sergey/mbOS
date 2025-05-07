/*
 * Copyright (c) 2013-2020 ARM Limited. All rights reserved.
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
 *
 * $Date:        24. January 2020
 * $Revision:    V2.2
 *
 * Project:      Ethernet PHY and MAC Driver common definitions
 */

/* History:
 *  Version 2.2
 *    Removed volatile from ETH_LINK_INFO
 *  Version 2.1
 *    ETH_LINK_INFO made volatile
 *  Version 2.0
 *    Removed ETH_STATUS enumerator
 *    Removed ETH_MODE enumerator
 *  Version 1.10
 *    Namespace prefix  added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_ETH_H_
#define DRIVER_ETH_H_

#include "Driver_Common.h"

/**
\brief Ethernet Media Interface type
*/
#define ETH_INTERFACE_MII           (0U)    ///< Media Independent Interface (MII)
#define ETH_INTERFACE_RMII          (1U)    ///< Reduced Media Independent Interface (RMII)
#define ETH_INTERFACE_SMII          (2U)    ///< Serial Media Independent Interface (SMII)

/**
\brief Ethernet link speed
*/
#define ETH_SPEED_10M               (0U)    ///< 10 Mbps link speed
#define ETH_SPEED_100M              (1U)    ///< 100 Mbps link speed
#define ETH_SPEED_1G                (2U)    ///< 1 Gpbs link speed

/**
\brief Ethernet duplex mode
*/
#define ETH_DUPLEX_HALF             (0U)    ///< Half duplex link
#define ETH_DUPLEX_FULL             (1U)    ///< Full duplex link

/**
\brief Ethernet link state
*/
typedef enum _ETH_LINK_STATE {
  ETH_LINK_DOWN,                        ///< Link is down
  ETH_LINK_UP                           ///< Link is up
} ETH_LINK_STATE;

/**
\brief Ethernet link information
*/
typedef struct _ETH_LINK_INFO {
  uint32_t speed    : 2;                ///< Link speed: 0= 10 MBit, 1= 100 MBit, 2= 1 GBit
  uint32_t duplex   : 1;                ///< Duplex mode: 0= Half, 1= Full
  uint32_t reserved : 29;
} ETH_LINK_INFO;

/**
\brief Ethernet MAC Address
*/
typedef struct _ETH_MAC_ADDR {
  uint8_t b[6];                         ///< MAC Address (6 bytes), MSB first
} ETH_MAC_ADDR;

#endif /* DRIVER_ETH_H_ */
