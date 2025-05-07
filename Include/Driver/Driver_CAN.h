/*
 * Copyright (c) 2015-2020 ARM Limited. All rights reserved.
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
 * $Revision:    V1.3
 *
 * Project:      CAN (Controller Area Network) Driver definitions
 */

/* History:
 *  Version 1.3
 *    Removed volatile from CAN_STATUS
 *  Version 1.2
 *    Added CAN_UNIT_STATE_BUS_OFF unit state and
 *    CAN_EVENT_UNIT_INACTIVE unit event
 *  Version 1.1
 *    CAN_STATUS made volatile
 *  Version 1.0
 *    Initial release
 */

#ifndef DRIVER_CAN_H_
#define DRIVER_CAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define CAN_API_VERSION DRIVER_VERSION_MAJOR_MINOR(1,3)  /* API version */


#define _Driver_CAN_(n)      Driver_CAN##n
#define  Driver_CAN_(n)     _Driver_CAN_(n)


/****** CAN Bitrate selection codes *****/
typedef enum _CAN_BITRATE_SELECT {
  CAN_BITRATE_NOMINAL,              ///< Select nominal (flexible data-rate arbitration) bitrate
  CAN_BITRATE_FD_DATA               ///< Select flexible data-rate data bitrate
} CAN_BITRATE_SELECT;

/****** CAN Bit Propagation Segment codes (PROP_SEG) *****/
#define CAN_BIT_PROP_SEG_Pos        0UL       ///< bits 7..0
#define CAN_BIT_PROP_SEG_Msk       (0xFFUL << CAN_BIT_PROP_SEG_Pos)
#define CAN_BIT_PROP_SEG(x)      (((x)     << CAN_BIT_PROP_SEG_Pos) & CAN_BIT_PROP_SEG_Msk)

/****** CAN Bit Phase Buffer Segment 1 (PHASE_SEG1) codes *****/
#define CAN_BIT_PHASE_SEG1_Pos      8UL       ///< bits 15..8
#define CAN_BIT_PHASE_SEG1_Msk     (0xFFUL << CAN_BIT_PHASE_SEG1_Pos)
#define CAN_BIT_PHASE_SEG1(x)    (((x)     << CAN_BIT_PHASE_SEG1_Pos) & CAN_BIT_PHASE_SEG1_Msk)

/****** CAN Bit Phase Buffer Segment 2 (PHASE_SEG2) codes *****/
#define CAN_BIT_PHASE_SEG2_Pos      16UL      ///< bits 23..16
#define CAN_BIT_PHASE_SEG2_Msk     (0xFFUL << CAN_BIT_PHASE_SEG2_Pos)
#define CAN_BIT_PHASE_SEG2(x)    (((x)     << CAN_BIT_PHASE_SEG2_Pos) & CAN_BIT_PHASE_SEG2_Msk)

/****** CAN Bit (Re)Synchronization Jump Width Segment (SJW) *****/
#define CAN_BIT_SJW_Pos             24UL      ///< bits 28..24
#define CAN_BIT_SJW_Msk            (0x1FUL << CAN_BIT_SJW_Pos)
#define CAN_BIT_SJW(x)           (((x)     << CAN_BIT_SJW_Pos) & CAN_BIT_SJW_Msk)

/****** CAN Mode codes *****/
typedef enum _CAN_MODE {
  CAN_MODE_INITIALIZATION,          ///< Initialization mode
  CAN_MODE_NORMAL,                  ///< Normal operation mode
  CAN_MODE_RESTRICTED,              ///< Restricted operation mode
  CAN_MODE_MONITOR,                 ///< Bus monitoring mode
  CAN_MODE_LOOPBACK_INTERNAL,       ///< Loopback internal mode
  CAN_MODE_LOOPBACK_EXTERNAL        ///< Loopback external mode
} CAN_MODE;

/****** CAN Filter Operation codes *****/
typedef enum _CAN_FILTER_OPERATION {
  CAN_FILTER_ID_EXACT_ADD,          ///< Add    exact id filter
  CAN_FILTER_ID_EXACT_REMOVE,       ///< Remove exact id filter
  CAN_FILTER_ID_RANGE_ADD,          ///< Add    range id filter
  CAN_FILTER_ID_RANGE_REMOVE,       ///< Remove range id filter
  CAN_FILTER_ID_MASKABLE_ADD,       ///< Add    maskable id filter
  CAN_FILTER_ID_MASKABLE_REMOVE     ///< Remove maskable id filter
} CAN_FILTER_OPERATION;

/****** CAN Object Configuration codes *****/
typedef enum _CAN_OBJ_CONFIG {
  CAN_OBJ_INACTIVE,                 ///< CAN object inactive
  CAN_OBJ_TX,                       ///< CAN transmit object
  CAN_OBJ_RX,                       ///< CAN receive object
  CAN_OBJ_RX_RTR_TX_DATA,           ///< CAN object that on RTR reception automatically transmits Data Frame
  CAN_OBJ_TX_RTR_RX_DATA            ///< CAN object that transmits RTR and automatically receives Data Frame
} CAN_OBJ_CONFIG;

/**
\brief CAN Object Capabilities
*/
typedef struct _CAN_OBJ_CAPABILITIES {
  uint32_t tx               : 1;        ///< Object supports transmission
  uint32_t rx               : 1;        ///< Object supports reception
  uint32_t rx_rtr_tx_data   : 1;        ///< Object supports RTR reception and automatic Data Frame transmission
  uint32_t tx_rtr_rx_data   : 1;        ///< Object supports RTR transmission and automatic Data Frame reception
  uint32_t multiple_filters : 1;        ///< Object allows assignment of multiple filters to it
  uint32_t exact_filtering  : 1;        ///< Object supports exact identifier filtering
  uint32_t range_filtering  : 1;        ///< Object supports range identifier filtering
  uint32_t mask_filtering   : 1;        ///< Object supports mask identifier filtering
  uint32_t message_depth    : 8;        ///< Number of messages buffers (FIFO) for that object
  uint32_t reserved         : 16;       ///< Reserved (must be zero)
} CAN_OBJ_CAPABILITIES;

/****** CAN Control Function Operation codes *****/
#define CAN_CONTROL_Pos             0UL
#define CAN_CONTROL_Msk            (0xFFUL << CAN_CONTROL_Pos)
#define CAN_SET_FD_MODE            (1UL    << CAN_CONTROL_Pos)          ///< Set FD operation mode;                   arg: 0 = disable, 1 = enable
#define CAN_ABORT_MESSAGE_SEND     (2UL    << CAN_CONTROL_Pos)          ///< Abort sending of CAN message;            arg = object
#define CAN_CONTROL_RETRANSMISSION (3UL    << CAN_CONTROL_Pos)          ///< Enable/disable automatic retransmission; arg: 0 = disable, 1 = enable (default state)
#define CAN_SET_TRANSCEIVER_DELAY  (4UL    << CAN_CONTROL_Pos)          ///< Set transceiver delay;                   arg = delay in time quanta

/****** CAN ID Frame Format codes *****/
#define CAN_ID_IDE_Pos              31UL
#define CAN_ID_IDE_Msk             (1UL    << CAN_ID_IDE_Pos)

/****** CAN Identifier encoding *****/
#define CAN_STANDARD_ID(id)        (id & 0x000007FFUL)                      ///< CAN identifier in standard format (11-bits)
#define CAN_EXTENDED_ID(id)       ((id & 0x1FFFFFFFUL) | CAN_ID_IDE_Msk)///< CAN identifier in extended format (29-bits)

/**
\brief CAN Message Information
*/
typedef struct _CAN_MSG_INFO {
  uint32_t id;                          ///< CAN identifier with frame format specifier (bit 31)
  uint32_t rtr              : 1;        ///< Remote transmission request frame
  uint32_t edl              : 1;        ///< Flexible data-rate format extended data length
  uint32_t brs              : 1;        ///< Flexible data-rate format with bitrate switch 
  uint32_t esi              : 1;        ///< Flexible data-rate format error state indicator
  uint32_t dlc              : 4;        ///< Data length code
  uint32_t reserved         : 24;
} CAN_MSG_INFO;

/****** CAN specific error code *****/
#define CAN_INVALID_BITRATE_SELECT (DRIVER_ERROR_SPECIFIC - 1)          ///< Bitrate selection not supported
#define CAN_INVALID_BITRATE        (DRIVER_ERROR_SPECIFIC - 2)          ///< Requested bitrate not supported
#define CAN_INVALID_BIT_PROP_SEG   (DRIVER_ERROR_SPECIFIC - 3)          ///< Propagation segment value not supported
#define CAN_INVALID_BIT_PHASE_SEG1 (DRIVER_ERROR_SPECIFIC - 4)          ///< Phase segment 1 value not supported
#define CAN_INVALID_BIT_PHASE_SEG2 (DRIVER_ERROR_SPECIFIC - 5)          ///< Phase segment 2 value not supported
#define CAN_INVALID_BIT_SJW        (DRIVER_ERROR_SPECIFIC - 6)          ///< SJW value not supported
#define CAN_NO_MESSAGE_AVAILABLE   (DRIVER_ERROR_SPECIFIC - 7)          ///< Message is not available

/****** CAN Status codes *****/
#define CAN_UNIT_STATE_INACTIVE    (0U)             ///< Unit state: Not active on bus (initialization)
#define CAN_UNIT_STATE_ACTIVE      (1U)             ///< Unit state: Active on bus (can generate active error frame)
#define CAN_UNIT_STATE_PASSIVE     (2U)             ///< Unit state: Error passive (can not generate active error frame)
#define CAN_UNIT_STATE_BUS_OFF     (3U)             ///< Unit state: Bus-off (can recover to active state)
#define CAN_LEC_NO_ERROR           (0U)             ///< Last error code: No error
#define CAN_LEC_BIT_ERROR          (1U)             ///< Last error code: Bit error
#define CAN_LEC_STUFF_ERROR        (2U)             ///< Last error code: Bit stuffing error
#define CAN_LEC_CRC_ERROR          (3U)             ///< Last error code: CRC error
#define CAN_LEC_FORM_ERROR         (4U)             ///< Last error code: Illegal fixed-form bit
#define CAN_LEC_ACK_ERROR          (5U)             ///< Last error code: Acknowledgment error

/**
\brief CAN Status
*/
typedef struct _CAN_STATUS {
  uint32_t unit_state       : 4;        ///< Unit bus state
  uint32_t last_error_code  : 4;        ///< Last error code
  uint32_t tx_error_count   : 8;        ///< Transmitter error count
  uint32_t rx_error_count   : 8;        ///< Receiver error count
  uint32_t reserved         : 8;
} CAN_STATUS;


/****** CAN Unit Event *****/
#define CAN_EVENT_UNIT_INACTIVE    (0U)             ///< Unit entered Inactive state
#define CAN_EVENT_UNIT_ACTIVE      (1U)             ///< Unit entered Error Active state
#define CAN_EVENT_UNIT_WARNING     (2U)             ///< Unit entered Error Warning state (one or both error counters >= 96)
#define CAN_EVENT_UNIT_PASSIVE     (3U)             ///< Unit entered Error Passive state
#define CAN_EVENT_UNIT_BUS_OFF     (4U)             ///< Unit entered Bus-off state

/****** CAN Send/Receive Event *****/
#define CAN_EVENT_SEND_COMPLETE    (1UL << 0)       ///< Send complete
#define CAN_EVENT_RECEIVE          (1UL << 1)       ///< Message received
#define CAN_EVENT_RECEIVE_OVERRUN  (1UL << 2)       ///< Received message overrun


// Function documentation
/**
  \fn          DRIVER_VERSION CAN_GetVersion (void)
  \brief       Get driver version.
  \return      \ref DRIVER_VERSION

  \fn          CAN_CAPABILITIES CAN_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref CAN_CAPABILITIES

  \fn          int32_t CAN_Initialize (CAN_SignalUnitEvent_t   cb_unit_event,
                                           CAN_SignalObjectEvent_t cb_object_event)
  \brief       Initialize CAN interface and register signal (callback) functions.
  \param[in]   cb_unit_event   Pointer to \ref CAN_SignalUnitEvent callback function
  \param[in]   cb_object_event Pointer to \ref CAN_SignalObjectEvent callback function
  \return      \ref execution_status

  \fn          int32_t CAN_Uninitialize (void)
  \brief       De-initialize CAN interface.
  \return      \ref execution_status

  \fn          int32_t CAN_PowerControl (POWER_STATE state)
  \brief       Control CAN interface power.
  \param[in]   state  Power state
                 - \ref POWER_OFF :  power off: no operation possible
                 - \ref POWER_LOW :  low power mode: retain state, detect and signal wake-up events
                 - \ref POWER_FULL : power on: full operation at maximum performance
  \return      \ref execution_status

  \fn          uint32_t CAN_GetClock (void)
  \brief       Retrieve CAN base clock frequency.
  \return      base clock frequency

  \fn          int32_t CAN_SetBitrate (CAN_BITRATE_SELECT select, uint32_t bitrate, uint32_t bit_segments)
  \brief       Set bitrate for CAN interface.
  \param[in]   select       Bitrate selection
                 - \ref CAN_BITRATE_NOMINAL : nominal (flexible data-rate arbitration) bitrate
                 - \ref CAN_BITRATE_FD_DATA : flexible data-rate data bitrate
  \param[in]   bitrate      Bitrate
  \param[in]   bit_segments Bit segments settings
                 - \ref CAN_BIT_PROP_SEG(x) :   number of time quanta for propagation time segment
                 - \ref CAN_BIT_PHASE_SEG1(x) : number of time quanta for phase buffer segment 1
                 - \ref CAN_BIT_PHASE_SEG2(x) : number of time quanta for phase buffer Segment 2
                 - \ref CAN_BIT_SJW(x) :        number of time quanta for (re-)synchronization jump width
  \return      \ref execution_status

  \fn          int32_t CAN_SetMode (CAN_MODE mode)
  \brief       Set operating mode for CAN interface.
  \param[in]   mode   Operating mode
                 - \ref CAN_MODE_INITIALIZATION :    initialization mode
                 - \ref CAN_MODE_NORMAL :            normal operation mode
                 - \ref CAN_MODE_RESTRICTED :        restricted operation mode
                 - \ref CAN_MODE_MONITOR :           bus monitoring mode
                 - \ref CAN_MODE_LOOPBACK_INTERNAL : loopback internal mode
                 - \ref CAN_MODE_LOOPBACK_EXTERNAL : loopback external mode
  \return      \ref execution_status

  \fn          CAN_OBJ_CAPABILITIES CAN_ObjectGetCapabilities (uint32_t obj_idx)
  \brief       Retrieve capabilities of an object.
  \param[in]   obj_idx  Object index
  \return      \ref CAN_OBJ_CAPABILITIES

  \fn          int32_t CAN_ObjectSetFilter (uint32_t obj_idx, CAN_FILTER_OPERATION operation, uint32_t id, uint32_t arg)
  \brief       Add or remove filter for message reception.
  \param[in]   obj_idx      Object index of object that filter should be or is assigned to
  \param[in]   operation    Operation on filter
                 - \ref CAN_FILTER_ID_EXACT_ADD :       add    exact id filter
                 - \ref CAN_FILTER_ID_EXACT_REMOVE :    remove exact id filter
                 - \ref CAN_FILTER_ID_RANGE_ADD :       add    range id filter
                 - \ref CAN_FILTER_ID_RANGE_REMOVE :    remove range id filter
                 - \ref CAN_FILTER_ID_MASKABLE_ADD :    add    maskable id filter
                 - \ref CAN_FILTER_ID_MASKABLE_REMOVE : remove maskable id filter
  \param[in]   id           ID or start of ID range (depending on filter type)
  \param[in]   arg          Mask or end of ID range (depending on filter type)
  \return      \ref execution_status

  \fn          int32_t CAN_ObjectConfigure (uint32_t obj_idx, CAN_OBJ_CONFIG obj_cfg)
  \brief       Configure object.
  \param[in]   obj_idx  Object index
  \param[in]   obj_cfg  Object configuration state
                 - \ref CAN_OBJ_INACTIVE :       deactivate object
                 - \ref CAN_OBJ_RX :             configure object for reception
                 - \ref CAN_OBJ_TX :             configure object for transmission
                 - \ref CAN_OBJ_RX_RTR_TX_DATA : configure object that on RTR reception automatically transmits Data Frame
                 - \ref CAN_OBJ_TX_RTR_RX_DATA : configure object that transmits RTR and automatically receives Data Frame
  \return      \ref execution_status

  \fn          int32_t CAN_MessageSend (uint32_t obj_idx, CAN_MSG_INFO *msg_info, const uint8_t *data, uint8_t size)
  \brief       Send message on CAN bus.
  \param[in]   obj_idx  Object index
  \param[in]   msg_info Pointer to CAN message information
  \param[in]   data     Pointer to data buffer
  \param[in]   size     Number of data bytes to send
  \return      value >= 0  number of data bytes accepted to send
  \return      value < 0   \ref execution_status

  \fn          int32_t CAN_MessageRead (uint32_t obj_idx, CAN_MSG_INFO *msg_info, uint8_t *data, uint8_t size)
  \brief       Read message received on CAN bus.
  \param[in]   obj_idx  Object index
  \param[out]  msg_info Pointer to read CAN message information
  \param[out]  data     Pointer to data buffer for read data
  \param[in]   size     Maximum number of data bytes to read
  \return      value >= 0  number of data bytes read
  \return      value < 0   \ref execution_status

  \fn          int32_t CAN_Control (uint32_t control, uint32_t arg)
  \brief       Control CAN interface.
  \param[in]   control  Operation
                 - \ref CAN_SET_FD_MODE :            set FD operation mode
                 - \ref CAN_ABORT_MESSAGE_SEND :     abort sending of CAN message
                 - \ref CAN_CONTROL_RETRANSMISSION : enable/disable automatic retransmission
                 - \ref CAN_SET_TRANSCEIVER_DELAY :  set transceiver delay
  \param[in]   arg      Argument of operation
  \return      \ref execution_status

  \fn          CAN_STATUS CAN_GetStatus (void)
  \brief       Get CAN status.
  \return      CAN status \ref CAN_STATUS

  \fn          void CAN_SignalUnitEvent (uint32_t event)
  \brief       Signal CAN unit event.
  \param[in]   event \ref CAN_unit_events
  \return      none

  \fn          void CAN_SignalObjectEvent (uint32_t obj_idx, uint32_t event)
  \brief       Signal CAN object event.
  \param[in]   obj_idx  Object index
  \param[in]   event \ref CAN_events
  \return      none
*/

typedef void (*CAN_SignalUnitEvent_t)   (uint32_t event);                   ///< Pointer to \ref CAN_SignalUnitEvent   : Signal CAN Unit Event.
typedef void (*CAN_SignalObjectEvent_t) (uint32_t obj_idx, uint32_t event); ///< Pointer to \ref CAN_SignalObjectEvent : Signal CAN Object Event.


/**
\brief CAN Device Driver Capabilities.
*/
typedef struct _CAN_CAPABILITIES {
  uint32_t num_objects            : 8;  ///< Number of \ref can_objects available
  uint32_t reentrant_operation    : 1;  ///< Support for reentrant calls to \ref CAN_MessageSend, \ref CAN_MessageRead, \ref CAN_ObjectConfigure and abort message sending used by \ref CAN_Control
  uint32_t fd_mode                : 1;  ///< Support for CAN with flexible data-rate mode (CAN_FD) (set by \ref CAN_Control)
  uint32_t restricted_mode        : 1;  ///< Support for restricted operation mode (set by \ref CAN_SetMode)
  uint32_t monitor_mode           : 1;  ///< Support for bus monitoring mode (set by \ref CAN_SetMode)
  uint32_t internal_loopback      : 1;  ///< Support for internal loopback mode (set by \ref CAN_SetMode)
  uint32_t external_loopback      : 1;  ///< Support for external loopback mode (set by \ref CAN_SetMode)
  uint32_t reserved               : 18; ///< Reserved (must be zero)
} CAN_CAPABILITIES;


/**
\brief Access structure of the CAN Driver.
*/
typedef struct _DRIVER_CAN {
  DRIVER_VERSION       (*GetVersion)            (void);                             ///< Pointer to \ref CAN_GetVersion            : Get driver version.
  CAN_CAPABILITIES     (*GetCapabilities)       (void);                             ///< Pointer to \ref CAN_GetCapabilities       : Get driver capabilities.
  int32_t                  (*Initialize)            (CAN_SignalUnitEvent_t   cb_unit_event,                     
                                                     CAN_SignalObjectEvent_t cb_object_event); ///< Pointer to \ref CAN_Initialize : Initialize CAN interface.
  int32_t                  (*Uninitialize)          (void);                             ///< Pointer to \ref CAN_Uninitialize          : De-initialize CAN interface.
  int32_t                  (*PowerControl)          (POWER_STATE          state);   ///< Pointer to \ref CAN_PowerControl          : Control CAN interface power.
  uint32_t                 (*GetClock)              (void);                             ///< Pointer to \ref CAN_GetClock              : Retrieve CAN base clock frequency.
  int32_t                  (*SetBitrate)            (CAN_BITRATE_SELECT   select,
                                                     uint32_t                 bitrate,
                                                     uint32_t                 bit_segments);       ///< Pointer to \ref CAN_SetBitrate : Set bitrate for CAN interface.
  int32_t                  (*SetMode)               (CAN_MODE             mode);    ///< Pointer to \ref CAN_SetMode               : Set operating mode for CAN interface.
  CAN_OBJ_CAPABILITIES (*ObjectGetCapabilities) (uint32_t                 obj_idx); ///< Pointer to \ref CAN_ObjectGetCapabilities : Retrieve capabilities of an object.
  int32_t                  (*ObjectSetFilter)       (uint32_t                 obj_idx,
                                                     CAN_FILTER_OPERATION operation,
                                                     uint32_t                 id,
                                                     uint32_t                 arg);     ///< Pointer to \ref CAN_ObjectSetFilter       : Add or remove filter for message reception.
  int32_t                  (*ObjectConfigure)       (uint32_t                 obj_idx,
                                                     CAN_OBJ_CONFIG       obj_cfg); ///< Pointer to \ref CAN_ObjectConfigure       : Configure object.
  int32_t                  (*MessageSend)           (uint32_t                 obj_idx,
                                                     CAN_MSG_INFO        *msg_info,
                                                     const uint8_t           *data,
                                                     uint8_t                  size);    ///< Pointer to \ref CAN_MessageSend           : Send message on CAN bus.
  int32_t                  (*MessageRead)           (uint32_t                 obj_idx,
                                                     CAN_MSG_INFO        *msg_info,
                                                     uint8_t                 *data,
                                                     uint8_t                  size);    ///< Pointer to \ref CAN_MessageRead           : Read message received on CAN bus.
  int32_t                  (*Control)               (uint32_t                 control,
                                                     uint32_t                 arg);     ///< Pointer to \ref CAN_Control               : Control CAN interface.
  CAN_STATUS           (*GetStatus)             (void);                             ///< Pointer to \ref CAN_GetStatus             : Get CAN status.
} const DRIVER_CAN;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_CAN_H_ */
