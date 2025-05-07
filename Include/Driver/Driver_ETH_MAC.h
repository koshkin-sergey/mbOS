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
 * Project:      Ethernet MAC (Media Access Control) Driver definitions
 */

/* History:
 *  Version 2.2
 *    Removed volatile from ETH_LINK_INFO
 *  Version 2.1
 *    Added ETH_MAC_SLEEP Control
 *  Version 2.0
 *    Changed MAC Address handling:
 *      moved from ETH_MAC_Initialize
 *      to new functions ETH_MAC_GetMacAddress and ETH_MAC_SetMacAddress
 *    Replaced ETH_MAC_SetMulticastAddr function with ETH_MAC_SetAddressFilter
 *    Extended ETH_MAC_SendFrame function with flags
 *    Added ETH_MAC_Control function:
 *      more control options (Broadcast, Multicast, Checksum offload, VLAN, ...)
 *      replaces ETH_MAC_SetMode
 *      replaces ETH_MAC_EnableTx, ETH_MAC_EnableRx
 *    Added optional event on transmitted frame
 *    Added support for PTP (Precision Time Protocol) through new functions:
 *       ETH_MAC_ControlTimer
 *       ETH_MAC_GetRxFrameTime
 *       ETH_MAC_GetTxFrameTime
 *    Changed prefix DRV -> DRIVER
 *    Changed return values of some functions to int32_t
 *  Version 1.10
 *    Name space prefix  added
 *  Version 1.01
 *    Renamed capabilities items for checksum offload
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_ETH_MAC_H_
#define DRIVER_ETH_MAC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_ETH.h"

#define ETH_MAC_API_VERSION DRIVER_VERSION_MAJOR_MINOR(2,2)  /* API version */


#define _Driver_ETH_MAC_(n)      Driver_ETH_MAC##n
#define  Driver_ETH_MAC_(n)     _Driver_ETH_MAC_(n)


/****** Ethernet MAC Control Codes *****/

#define ETH_MAC_CONFIGURE           (0x01UL)    ///< Configure MAC; arg = configuration
#define ETH_MAC_CONTROL_TX          (0x02UL)    ///< Transmitter; arg: 0=disabled (default), 1=enabled
#define ETH_MAC_CONTROL_RX          (0x03UL)    ///< Receiver; arg: 0=disabled (default), 1=enabled
#define ETH_MAC_FLUSH               (0x04UL)    ///< Flush buffer; arg = ETH_MAC_FLUSH_...
#define ETH_MAC_SLEEP               (0x05UL)    ///< Sleep mode; arg: 1=enter and wait for Magic packet, 0=exit
#define ETH_MAC_VLAN_FILTER         (0x06UL)    ///< VLAN Filter for received frames; arg15..0: VLAN Tag; arg16: optional ETH_MAC_VLAN_FILTER_ID_ONLY; 0=disabled (default)

/*----- Ethernet MAC Configuration -----*/
#define ETH_MAC_SPEED_Pos            0
#define ETH_MAC_SPEED_Msk           (3UL             << ETH_MAC_SPEED_Pos)
#define ETH_MAC_SPEED_10M           (ETH_SPEED_10M   << ETH_MAC_SPEED_Pos)  ///< 10 Mbps link speed
#define ETH_MAC_SPEED_100M          (ETH_SPEED_100M  << ETH_MAC_SPEED_Pos)  ///< 100 Mbps link speed
#define ETH_MAC_SPEED_1G            (ETH_SPEED_1G    << ETH_MAC_SPEED_Pos)  ///< 1 Gpbs link speed
#define ETH_MAC_DUPLEX_Pos           2
#define ETH_MAC_DUPLEX_Msk          (1UL             << ETH_MAC_DUPLEX_Pos)
#define ETH_MAC_DUPLEX_HALF         (ETH_DUPLEX_HALF << ETH_MAC_DUPLEX_Pos) ///< Half duplex link
#define ETH_MAC_DUPLEX_FULL         (ETH_DUPLEX_FULL << ETH_MAC_DUPLEX_Pos) ///< Full duplex link
#define ETH_MAC_LOOPBACK            (1UL << 4)  ///< Loop-back test mode
#define ETH_MAC_CHECKSUM_OFFLOAD_RX (1UL << 5)  ///< Receiver Checksum offload
#define ETH_MAC_CHECKSUM_OFFLOAD_TX (1UL << 6)  ///< Transmitter Checksum offload
#define ETH_MAC_ADDRESS_BROADCAST   (1UL << 7)  ///< Accept frames with Broadcast address
#define ETH_MAC_ADDRESS_MULTICAST   (1UL << 8)  ///< Accept frames with any Multicast address
#define ETH_MAC_ADDRESS_ALL         (1UL << 9)  ///< Accept frames with any address (Promiscuous Mode)

/*----- Ethernet MAC Flush Flags -----*/
#define ETH_MAC_FLUSH_RX            (1UL << 0)  ///< Flush Receive buffer
#define ETH_MAC_FLUSH_TX            (1UL << 1)  ///< Flush Transmit buffer

/*----- Ethernet MAC VLAN Filter Flag -----*/
#define ETH_MAC_VLAN_FILTER_ID_ONLY (1UL << 16) ///< Compare only the VLAN Identifier (12-bit)


/****** Ethernet MAC Frame Transmit Flags *****/
#define ETH_MAC_TX_FRAME_FRAGMENT   (1UL << 0)  ///< Indicate frame fragment
#define ETH_MAC_TX_FRAME_EVENT      (1UL << 1)  ///< Generate event when frame is transmitted
#define ETH_MAC_TX_FRAME_TIMESTAMP  (1UL << 2)  ///< Capture frame time stamp


/****** Ethernet MAC Timer Control Codes *****/
#define ETH_MAC_TIMER_GET_TIME      (0x01UL)    ///< Get current time
#define ETH_MAC_TIMER_SET_TIME      (0x02UL)    ///< Set new time
#define ETH_MAC_TIMER_INC_TIME      (0x03UL)    ///< Increment current time
#define ETH_MAC_TIMER_DEC_TIME      (0x04UL)    ///< Decrement current time
#define ETH_MAC_TIMER_SET_ALARM     (0x05UL)    ///< Set alarm time
#define ETH_MAC_TIMER_ADJUST_CLOCK  (0x06UL)    ///< Adjust clock frequency; time->ns: correction factor * 2^31


/**
\brief Ethernet MAC Time
*/
typedef struct _ETH_MAC_TIME {
  uint32_t ns;                          ///< Nano seconds
  uint32_t sec;                         ///< Seconds
} ETH_MAC_TIME;


/****** Ethernet MAC Event *****/
#define ETH_MAC_EVENT_RX_FRAME      (1UL << 0)  ///< Frame Received
#define ETH_MAC_EVENT_TX_FRAME      (1UL << 1)  ///< Frame Transmitted
#define ETH_MAC_EVENT_WAKEUP        (1UL << 2)  ///< Wake-up (on Magic Packet)
#define ETH_MAC_EVENT_TIMER_ALARM   (1UL << 3)  ///< Timer Alarm


// Function documentation
/**
  \fn          DRIVER_VERSION ETH_MAC_GetVersion (void)
  \brief       Get driver version.
  \return      \ref DRIVER_VERSION
*/
/**
  \fn          ETH_MAC_CAPABILITIES ETH_MAC_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ETH_MAC_CAPABILITIES
*/
/**
  \fn          int32_t ETH_MAC_Initialize (ETH_MAC_SignalEvent_t cb_event)
  \brief       Initialize Ethernet MAC Device.
  \param[in]   cb_event  Pointer to \ref ETH_MAC_SignalEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_Uninitialize (void)
  \brief       De-initialize Ethernet MAC Device.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_PowerControl (POWER_STATE state)
  \brief       Control Ethernet MAC Device Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_GetMacAddress (ETH_MAC_ADDR *ptr_addr)
  \brief       Get Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_SetMacAddress (const ETH_MAC_ADDR *ptr_addr)
  \brief       Set Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_SetAddressFilter (const ETH_MAC_ADDR *ptr_addr,
                                                           uint32_t          num_addr)
  \brief       Configure Address Filter.
  \param[in]   ptr_addr  Pointer to addresses
  \param[in]   num_addr  Number of addresses to configure
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags)
  \brief       Send Ethernet frame.
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \param[in]   flags  Frame transmit flags (see ETH_MAC_TX_FRAME_...)
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_ReadFrame (uint8_t *frame, uint32_t len)
  \brief       Read data of received Ethernet frame.
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with \ref execution_status 
*/
/**
  \fn          uint32_t ETH_MAC_GetRxFrameSize (void)
  \brief       Get size of received Ethernet frame.
  \return      number of bytes in received frame
*/
/**
  \fn          int32_t ETH_MAC_GetRxFrameTime (ETH_MAC_TIME *time)
  \brief       Get time of received Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_GetTxFrameTime (ETH_MAC_TIME *time)
  \brief       Get time of transmitted Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_Control (uint32_t control, uint32_t arg)
  \brief       Control Ethernet Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_ControlTimer (uint32_t control, ETH_MAC_TIME *time)
  \brief       Control Precision Timer.
  \param[in]   control  Operation
  \param[in]   time     Pointer to time structure
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      \ref execution_status
*/
/**
  \fn          int32_t ETH_MAC_PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      \ref execution_status
*/

/**
  \fn          void ETH_MAC_SignalEvent (uint32_t event)
  \brief       Callback function that signals a Ethernet Event.
  \param[in]   event  event notification mask
  \return      none
*/

typedef void (*ETH_MAC_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ETH_MAC_SignalEvent : Signal Ethernet Event.


/**
\brief Ethernet MAC Capabilities
*/
typedef struct _ETH_MAC_CAPABILITIES {
  uint32_t checksum_offload_rx_ip4  : 1;        ///< 1 = IPv4 header checksum verified on receive
  uint32_t checksum_offload_rx_ip6  : 1;        ///< 1 = IPv6 checksum verification supported on receive
  uint32_t checksum_offload_rx_udp  : 1;        ///< 1 = UDP payload checksum verified on receive
  uint32_t checksum_offload_rx_tcp  : 1;        ///< 1 = TCP payload checksum verified on receive
  uint32_t checksum_offload_rx_icmp : 1;        ///< 1 = ICMP payload checksum verified on receive
  uint32_t checksum_offload_tx_ip4  : 1;        ///< 1 = IPv4 header checksum generated on transmit
  uint32_t checksum_offload_tx_ip6  : 1;        ///< 1 = IPv6 checksum generation supported on transmit
  uint32_t checksum_offload_tx_udp  : 1;        ///< 1 = UDP payload checksum generated on transmit
  uint32_t checksum_offload_tx_tcp  : 1;        ///< 1 = TCP payload checksum generated on transmit
  uint32_t checksum_offload_tx_icmp : 1;        ///< 1 = ICMP payload checksum generated on transmit
  uint32_t media_interface          : 2;        ///< Ethernet Media Interface type
  uint32_t mac_address              : 1;        ///< 1 = driver provides initial valid MAC address
  uint32_t event_rx_frame           : 1;        ///< 1 = callback event \ref ETH_MAC_EVENT_RX_FRAME generated
  uint32_t event_tx_frame           : 1;        ///< 1 = callback event \ref ETH_MAC_EVENT_TX_FRAME generated
  uint32_t event_wakeup             : 1;        ///< 1 = wakeup event \ref ETH_MAC_EVENT_WAKEUP generated
  uint32_t precision_timer          : 1;        ///< 1 = Precision Timer supported
  uint32_t reserved                 : 15;       ///< Reserved (must be zero)
} ETH_MAC_CAPABILITIES;


/**
\brief Access structure of the Ethernet MAC Driver
*/
typedef struct _DRIVER_ETH_MAC {
  DRIVER_VERSION       (*GetVersion)      (void);                                                ///< Pointer to \ref ETH_MAC_GetVersion : Get driver version.
  ETH_MAC_CAPABILITIES (*GetCapabilities) (void);                                                ///< Pointer to \ref ETH_MAC_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (ETH_MAC_SignalEvent_t cb_event);                      ///< Pointer to \ref ETH_MAC_Initialize : Initialize Ethernet MAC Device.
  int32_t              (*Uninitialize)    (void);                                                ///< Pointer to \ref ETH_MAC_Uninitialize : De-initialize Ethernet MAC Device.
  int32_t              (*PowerControl)    (POWER_STATE state);                                   ///< Pointer to \ref ETH_MAC_PowerControl : Control Ethernet MAC Device Power.
  int32_t              (*GetMacAddress)   (      ETH_MAC_ADDR *ptr_addr);                        ///< Pointer to \ref ETH_MAC_GetMacAddress : Get Ethernet MAC Address.
  int32_t              (*SetMacAddress)   (const ETH_MAC_ADDR *ptr_addr);                        ///< Pointer to \ref ETH_MAC_SetMacAddress : Set Ethernet MAC Address.
  int32_t              (*SetAddressFilter)(const ETH_MAC_ADDR *ptr_addr, uint32_t num_addr);     ///< Pointer to \ref ETH_MAC_SetAddressFilter : Configure Address Filter.
  int32_t              (*SendFrame)       (const uint8_t *frame, uint32_t len, uint32_t flags);  ///< Pointer to \ref ETH_MAC_SendFrame : Send Ethernet frame.
  int32_t              (*ReadFrame)       (      uint8_t *frame, uint32_t len);                  ///< Pointer to \ref ETH_MAC_ReadFrame : Read data of received Ethernet frame.
  uint32_t             (*GetRxFrameSize)  (void);                                                ///< Pointer to \ref ETH_MAC_GetRxFrameSize : Get size of received Ethernet frame.
  int32_t              (*GetRxFrameTime)  (ETH_MAC_TIME *time);                                  ///< Pointer to \ref ETH_MAC_GetRxFrameTime : Get time of received Ethernet frame.
  int32_t              (*GetTxFrameTime)  (ETH_MAC_TIME *time);                                  ///< Pointer to \ref ETH_MAC_GetTxFrameTime : Get time of transmitted Ethernet frame.
  int32_t              (*ControlTimer)    (uint32_t control, ETH_MAC_TIME *time);                ///< Pointer to \ref ETH_MAC_ControlTimer : Control Precision Timer.
  int32_t              (*Control)         (uint32_t control, uint32_t arg);                      ///< Pointer to \ref ETH_MAC_Control : Control Ethernet Interface.
  int32_t              (*PHY_Read)        (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);  ///< Pointer to \ref ETH_MAC_PHY_Read : Read Ethernet PHY Register through Management Interface.
  int32_t              (*PHY_Write)       (uint8_t phy_addr, uint8_t reg_addr, uint16_t  data);  ///< Pointer to \ref ETH_MAC_PHY_Write : Write Ethernet PHY Register through Management Interface.
} const DRIVER_ETH_MAC;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_ETH_MAC_H_ */
