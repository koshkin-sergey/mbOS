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
 * $Date:        31. March 2020
 * $Revision:    V2.3
 *
 * Project:      USB Host Driver definitions
*/

/* History:
 *  Version 2.3
 *    Removed volatile from USBH_PORT_STATE
 *  Version 2.2
 *    USBH_PORT_STATE made volatile
 *  Version 2.1
 *    Renamed structure USBH_EP_HANDLE to USBH_PIPE_HANDLE
 *    Renamed functions USBH_Endpoint... to USBH_Pipe...
 *    Renamed function USBH_SignalEndpointEvent to USBH_SignalPipeEvent
 *  Version 2.0
 *    Replaced function USBH_PortPowerOnOff with USBH_PortVbusOnOff
 *    Changed function USBH_EndpointCreate parameters
 *    Replaced function USBH_EndpointConfigure with USBH_EndpointModify
 *    Replaced function USBH_EndpointClearHalt with USBH_EndpointReset
 *    Replaced function USBH_URB_Submit with USBH_EndpointTransfer
 *    Replaced function USBH_URB_Abort with USBH_EndpointTransferAbort
 *    Added function USBH_EndpointTransferGetResult
 *    Added function USBH_GetFrameNumber
 *    Changed prefix DRV -> DRIVER
 *  Version 1.20
 *    Added API for OHCI/EHCI Host Controller Interface (HCI)
 *  Version 1.10
 *    Namespace prefix  added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_USBH_H_
#define DRIVER_USBH_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_USB.h"

#define USBH_API_VERSION      DRIVER_VERSION_MAJOR_MINOR(2,3)  /* API version */


#define _Driver_USBH_(n)      Driver_USBH##n
#define  Driver_USBH_(n)     _Driver_USBH_(n)


/**
\brief USB Host Port State
*/
typedef struct _USBH_PORT_STATE {
  uint32_t connected   : 1;             ///< USB Host Port connected flag
  uint32_t overcurrent : 1;             ///< USB Host Port overcurrent flag
  uint32_t speed       : 2;             ///< USB Host Port speed setting (USB_SPEED_xxx)
  uint32_t reserved    : 28;
} USBH_PORT_STATE;

/**
\brief USB Host Pipe Handle
*/
typedef uint32_t USBH_PIPE_HANDLE;
#define USBH_EP_HANDLE USBH_PIPE_HANDLE  /* Legacy name */


/****** USB Host Packet Information *****/
#define USBH_PACKET_TOKEN_Pos         0
#define USBH_PACKET_TOKEN_Msk        (0x0FUL << USBH_PACKET_TOKEN_Pos)
#define USBH_PACKET_SETUP            (0x01UL << USBH_PACKET_TOKEN_Pos)  ///< SETUP Packet
#define USBH_PACKET_OUT              (0x02UL << USBH_PACKET_TOKEN_Pos)  ///< OUT Packet
#define USBH_PACKET_IN               (0x03UL << USBH_PACKET_TOKEN_Pos)  ///< IN Packet
#define USBH_PACKET_PING             (0x04UL << USBH_PACKET_TOKEN_Pos)  ///< PING Packet

#define USBH_PACKET_DATA_Pos          4
#define USBH_PACKET_DATA_Msk         (0x0FUL << USBH_PACKET_DATA_Pos)
#define USBH_PACKET_DATA0            (0x01UL << USBH_PACKET_DATA_Pos)   ///< DATA0 PID
#define USBH_PACKET_DATA1            (0x02UL << USBH_PACKET_DATA_Pos)   ///< DATA1 PID

#define USBH_PACKET_SPLIT_Pos         8
#define USBH_PACKET_SPLIT_Msk        (0x0FUL << USBH_PACKET_SPLIT_Pos)
#define USBH_PACKET_SSPLIT           (0x08UL << USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet
#define USBH_PACKET_SSPLIT_S         (0x09UL << USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet: Data Start
#define USBH_PACKET_SSPLIT_E         (0x0AUL << USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet: Data End
#define USBH_PACKET_SSPLIT_S_E       (0x0BUL << USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet: Data All
#define USBH_PACKET_CSPLIT           (0x0CUL << USBH_PACKET_SPLIT_Pos)  ///< CSPLIT Packet

#define USBH_PACKET_PRE              (1UL << 12)                        ///< PRE Token


/****** USB Host Port Event *****/
#define USBH_EVENT_CONNECT           (1UL << 0)     ///< USB Device Connected to Port
#define USBH_EVENT_DISCONNECT        (1UL << 1)     ///< USB Device Disconnected from Port
#define USBH_EVENT_OVERCURRENT       (1UL << 2)     ///< USB Device caused Overcurrent
#define USBH_EVENT_RESET             (1UL << 3)     ///< USB Reset completed
#define USBH_EVENT_SUSPEND           (1UL << 4)     ///< USB Suspend occurred
#define USBH_EVENT_RESUME            (1UL << 5)     ///< USB Resume occurred
#define USBH_EVENT_REMOTE_WAKEUP     (1UL << 6)     ///< USB Device activated Remote Wakeup

/****** USB Host Pipe Event *****/
#define USBH_EVENT_TRANSFER_COMPLETE (1UL << 0)     ///< Transfer completed
#define USBH_EVENT_HANDSHAKE_NAK     (1UL << 1)     ///< NAK Handshake received
#define USBH_EVENT_HANDSHAKE_NYET    (1UL << 2)     ///< NYET Handshake received
#define USBH_EVENT_HANDSHAKE_MDATA   (1UL << 3)     ///< MDATA Handshake received
#define USBH_EVENT_HANDSHAKE_STALL   (1UL << 4)     ///< STALL Handshake received
#define USBH_EVENT_HANDSHAKE_ERR     (1UL << 5)     ///< ERR Handshake received
#define USBH_EVENT_BUS_ERROR         (1UL << 6)     ///< Bus Error detected


#ifndef __DOXYGEN_MW__                  // exclude from middleware documentation

// Function documentation
/**
  \fn          DRIVER_VERSION USBH_GetVersion (void)
  \brief       Get driver version.
  \return      \ref DRIVER_VERSION
*/
/**
  \fn          USBH_CAPABILITIES USBH_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref USBH_CAPABILITIES
*/
/**
  \fn          int32_t USBH_Initialize (USBH_SignalPortEvent_t cb_port_event,
                                            USBH_SignalPipeEvent_t cb_pipe_event)
  \brief       Initialize USB Host Interface.
  \param[in]   cb_port_event  Pointer to \ref USBH_SignalPortEvent
  \param[in]   cb_pipe_event  Pointer to \ref USBH_SignalPipeEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_Uninitialize (void)
  \brief       De-initialize USB Host Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PowerControl (POWER_STATE state)
  \brief       Control USB Host Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PortVbusOnOff (uint8_t port, bool vbus)
  \brief       Root HUB Port VBUS on/off.
  \param[in]   port  Root HUB Port Number
  \param[in]   vbus
                - \b false VBUS off
                - \b true  VBUS on
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PortReset (uint8_t port)
  \brief       Do Root HUB Port Reset.
  \param[in]   port  Root HUB Port Number
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PortSuspend (uint8_t port)
  \brief       Suspend Root HUB Port (stop generating SOFs).
  \param[in]   port  Root HUB Port Number
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PortResume (uint8_t port)
  \brief       Resume Root HUB Port (start generating SOFs).
  \param[in]   port  Root HUB Port Number
  \return      \ref execution_status
*/
/**
  \fn          USBH_PORT_STATE USBH_PortGetState (uint8_t port)
  \brief       Get current Root HUB Port State.
  \param[in]   port  Root HUB Port Number
  \return      Port State \ref USBH_PORT_STATE
*/
/**
  \fn          USBH_PIPE_HANDLE USBH_PipeCreate (uint8_t  dev_addr,
                                                         uint8_t  dev_speed,
                                                         uint8_t  hub_addr,
                                                         uint8_t  hub_port,
                                                         uint8_t  ep_addr,
                                                         uint8_t  ep_type,
                                                         uint16_t ep_max_packet_size,
                                                         uint8_t  ep_interval)
  \brief       Create Pipe in System.
  \param[in]   dev_addr   Device Address
  \param[in]   dev_speed  Device Speed
  \param[in]   hub_addr   Hub Address
  \param[in]   hub_port   Hub Port
  \param[in]   ep_addr    Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \param[in]   ep_type    Endpoint Type (USB_ENDPOINT_xxx)
  \param[in]   ep_max_packet_size Endpoint Maximum Packet Size
  \param[in]   ep_interval        Endpoint Polling Interval
  \return      Pipe Handle \ref USBH_PIPE_HANDLE
*/
/**
  \fn          int32_t USBH_PipeModify (USBH_PIPE_HANDLE pipe_hndl,
                                            uint8_t              dev_addr,
                                            uint8_t              dev_speed,
                                            uint8_t              hub_addr,
                                            uint8_t              hub_port,
                                            uint16_t             ep_max_packet_size)
  \brief       Modify Pipe in System.
  \param[in]   pipe_hndl  Pipe Handle
  \param[in]   dev_addr   Device Address
  \param[in]   dev_speed  Device Speed
  \param[in]   hub_addr   Hub Address
  \param[in]   hub_port   Hub Port
  \param[in]   ep_max_packet_size Endpoint Maximum Packet Size
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PipeDelete (USBH_PIPE_HANDLE pipe_hndl)
  \brief       Delete Pipe from System.
  \param[in]   pipe_hndl  Pipe Handle
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PipeReset (USBH_PIPE_HANDLE pipe_hndl)
  \brief       Reset Pipe.
  \param[in]   pipe_hndl  Pipe Handle
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_PipeTransfer (USBH_PIPE_HANDLE pipe_hndl,
                                              uint32_t             packet,
                                              uint8_t             *data,
                                              uint32_t             num)
  \brief       Transfer packets through USB Pipe.
  \param[in]   pipe_hndl  Pipe Handle
  \param[in]   packet     Packet information
  \param[in]   data       Pointer to buffer with data to send or for data to receive
  \param[in]   num        Number of data bytes to transfer
  \return      \ref execution_status
*/
/**
  \fn          uint32_t USBH_PipeTransferGetResult (USBH_PIPE_HANDLE pipe_hndl)
  \brief       Get result of USB Pipe transfer.
  \param[in]   pipe_hndl  Pipe Handle
  \return      number of successfully transferred data bytes
*/
/**
  \fn          int32_t USBH_PipeTransferAbort (USBH_PIPE_HANDLE pipe_hndl)
  \brief       Abort current USB Pipe transfer.
  \param[in]   pipe_hndl  Pipe Handle
  \return      \ref execution_status
*/
/**
  \fn          uint16_t USBH_GetFrameNumber (void)
  \brief       Get current USB Frame Number.
  \return      Frame Number
*/

/**
  \fn          void USBH_SignalPortEvent (uint8_t port, uint32_t event)
  \brief       Signal Root HUB Port Event.
  \param[in]   port  Root HUB Port Number
  \param[in]   event \ref USBH_port_events
  \return      none
*/
/**
  \fn          void USBH_SignalPipeEvent (USBH_PIPE_HANDLE pipe_hndl, uint32_t event)
  \brief       Signal Pipe Event.
  \param[in]   pipe_hndl  Pipe Handle
  \param[in]   event  \ref USBH_pipe_events
  \return      none
*/

typedef void (*USBH_SignalPortEvent_t) (uint8_t port, uint32_t event);                ///< Pointer to \ref USBH_SignalPortEvent : Signal Root HUB Port Event.
typedef void (*USBH_SignalPipeEvent_t) (USBH_PIPE_HANDLE pipe_hndl, uint32_t event);  ///< Pointer to \ref USBH_SignalPipeEvent : Signal Pipe Event.
#define USBH_SignalEndpointEvent_t USBH_SignalPipeEvent_t  /* Legacy name */


/**
\brief USB Host Driver Capabilities.
*/
typedef struct _USBH_CAPABILITIES {
  uint32_t port_mask          : 15;     ///< Root HUB available Ports Mask
  uint32_t auto_split         :  1;     ///< Automatic SPLIT packet handling
  uint32_t event_connect      :  1;     ///< Signal Connect event
  uint32_t event_disconnect   :  1;     ///< Signal Disconnect event
  uint32_t event_overcurrent  :  1;     ///< Signal Overcurrent event
  uint32_t reserved           : 13;     ///< Reserved (must be zero)
} USBH_CAPABILITIES;


/**
\brief Access structure of USB Host Driver.
*/
typedef struct _DRIVER_USBH {
  DRIVER_VERSION    (*GetVersion)            (void);                                     ///< Pointer to \ref USBH_GetVersion : Get driver version.
  USBH_CAPABILITIES (*GetCapabilities)       (void);                                     ///< Pointer to \ref USBH_GetCapabilities : Get driver capabilities.
  int32_t           (*Initialize)            (USBH_SignalPortEvent_t cb_port_event,
                                              USBH_SignalPipeEvent_t cb_pipe_event);     ///< Pointer to \ref USBH_Initialize : Initialize USB Host Interface.
  int32_t           (*Uninitialize)          (void);                                     ///< Pointer to \ref USBH_Uninitialize : De-initialize USB Host Interface.
  int32_t           (*PowerControl)          (POWER_STATE state);                        ///< Pointer to \ref USBH_PowerControl : Control USB Host Interface Power.
  int32_t           (*PortVbusOnOff)         (uint8_t port, bool vbus);                  ///< Pointer to \ref USBH_PortVbusOnOff : Root HUB Port VBUS on/off.
  int32_t           (*PortReset)             (uint8_t port);                             ///< Pointer to \ref USBH_PortReset : Do Root HUB Port Reset.
  int32_t           (*PortSuspend)           (uint8_t port);                             ///< Pointer to \ref USBH_PortSuspend : Suspend Root HUB Port (stop generating SOFs).
  int32_t           (*PortResume)            (uint8_t port);                             ///< Pointer to \ref USBH_PortResume : Resume Root HUB Port (start generating SOFs).
  USBH_PORT_STATE   (*PortGetState)          (uint8_t port);                             ///< Pointer to \ref USBH_PortGetState : Get current Root HUB Port State.
  USBH_PIPE_HANDLE  (*PipeCreate)            (uint8_t dev_addr,
                                              uint8_t dev_speed,
                                              uint8_t hub_addr,
                                              uint8_t hub_port,
                                              uint8_t ep_addr,
                                              uint8_t ep_type,
                                              uint16_t ep_max_packet_size,
                                              uint8_t ep_interval);                      ///< Pointer to \ref USBH_PipeCreate : Create Pipe in System.
  int32_t           (*PipeModify)            (USBH_PIPE_HANDLE pipe_hndl,
                                              uint8_t dev_addr,
                                              uint8_t dev_speed,
                                              uint8_t hub_addr,
                                              uint8_t hub_port,
                                              uint16_t ep_max_packet_size);              ///< Pointer to \ref USBH_PipeModify : Modify Pipe in System.
  int32_t           (*PipeDelete)            (USBH_PIPE_HANDLE pipe_hndl);               ///< Pointer to \ref USBH_PipeDelete : Delete Pipe from System.
  int32_t           (*PipeReset)             (USBH_PIPE_HANDLE pipe_hndl);               ///< Pointer to \ref USBH_PipeReset : Reset Pipe.
  int32_t           (*PipeTransfer)          (USBH_PIPE_HANDLE pipe_hndl,
                                              uint32_t packet,
                                              uint8_t *data,
                                              uint32_t num);                             ///< Pointer to \ref USBH_PipeTransfer : Transfer packets through USB Pipe.
  uint32_t          (*PipeTransferGetResult) (USBH_PIPE_HANDLE pipe_hndl);               ///< Pointer to \ref USBH_PipeTransferGetResult : Get result of USB Pipe transfer.
  int32_t           (*PipeTransferAbort)     (USBH_PIPE_HANDLE pipe_hndl);               ///< Pointer to \ref USBH_PipeTransferAbort : Abort current USB Pipe transfer.
  uint16_t          (*GetFrameNumber)        (void);                                     ///< Pointer to \ref USBH_GetFrameNumber : Get current USB Frame Number.
} const DRIVER_USBH;


// HCI (OHCI/EHCI)

// Function documentation
/**
  \fn          DRIVER_VERSION USBH_HCI_GetVersion (void)
  \brief       Get USB Host HCI (OHCI/EHCI) driver version.
  \return      \ref DRIVER_VERSION
*/
/**
  \fn          USBH_HCI_CAPABILITIES USBH_HCI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref USBH_HCI_CAPABILITIES
*/
/**
  \fn          int32_t USBH_HCI_Initialize (USBH_HCI_Interrupt_t *cb_interrupt)
  \brief       Initialize USB Host HCI (OHCI/EHCI) Interface.
  \param[in]   cb_interrupt Pointer to Interrupt Handler Routine
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_HCI_Uninitialize (void)
  \brief       De-initialize USB Host HCI (OHCI/EHCI) Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_HCI_PowerControl (POWER_STATE state)
  \brief       Control USB Host HCI (OHCI/EHCI) Interface Power.
  \param[in]   state Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t USBH_HCI_PortVbusOnOff (uint8_t port, bool vbus)
  \brief       USB Host HCI (OHCI/EHCI) Root HUB Port VBUS on/off.
  \param[in]   port  Root HUB Port Number
  \param[in]   vbus
                - \b false VBUS off
                - \b true  VBUS on
  \return      \ref execution_status
*/

/**
  \fn          void USBH_HCI_Interrupt (void)
  \brief       USB Host HCI Interrupt Handler.
  \return      none
*/

typedef void (*USBH_HCI_Interrupt_t) (void);  ///< Pointer to Interrupt Handler Routine.


/**
\brief USB Host HCI (OHCI/EHCI) Driver Capabilities.
*/
typedef struct _USBH_HCI_CAPABILITIES {
  uint32_t port_mask : 15;              ///< Root HUB available Ports Mask
  uint32_t reserved  : 17;              ///< Reserved (must be zero)
} USBH_HCI_CAPABILITIES;


/**
  \brief Access structure of USB Host HCI (OHCI/EHCI) Driver.
*/
typedef struct _DRIVER_USBH_HCI {
  DRIVER_VERSION        (*GetVersion)      (void);                                  ///< Pointer to \ref USBH_HCI_GetVersion : Get USB Host HCI (OHCI/EHCI) driver version.
  USBH_HCI_CAPABILITIES (*GetCapabilities) (void);                                  ///< Pointer to \ref USBH_HCI_GetCapabilities : Get driver capabilities.
  int32_t               (*Initialize)      (USBH_HCI_Interrupt_t cb_interrupt);     ///< Pointer to \ref USBH_HCI_Initialize : Initialize USB Host HCI (OHCI/EHCI) Interface.
  int32_t               (*Uninitialize)    (void);                                  ///< Pointer to \ref USBH_HCI_Uninitialize : De-initialize USB Host HCI (OHCI/EHCI) Interface.
  int32_t               (*PowerControl)    (POWER_STATE state);                     ///< Pointer to \ref USBH_HCI_PowerControl : Control USB Host HCI (OHCI/EHCI) Interface Power.
  int32_t               (*PortVbusOnOff)   (uint8_t port, bool vbus);               ///< Pointer to \ref USBH_HCI_PortVbusOnOff : USB Host HCI (OHCI/EHCI) Root HUB Port VBUS on/off.
} const DRIVER_USBH_HCI;

#endif /* __DOXYGEN_MW__ */

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_USBH_H_ */
