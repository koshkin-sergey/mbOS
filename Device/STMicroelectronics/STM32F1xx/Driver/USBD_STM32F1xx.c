/*
 * Copyright (C) 2020 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
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
 * Project: USB Device Driver for STMicroelectronics STM32F1xx
 */

#include "USBD_STM32F1xx.h"

#include "asm/GPIO_STM32F1xx.h"

#define ARM_USBD_DRV_VERSION          ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)

// Driver Version
static const ARM_DRIVER_VERSION usbd_driver_version = {
  ARM_USBD_API_VERSION,
  ARM_USBD_DRV_VERSION
};

// Driver Capabilities
static const ARM_USBD_CAPABILITIES usbd_driver_capabilities = {
  0U,   // VBUS Detection
  0U,   // Event VBUS On
  0U    // Event VBUS Off
};

/* USBD Run-Time Information */
static USBD_INFO USBD_Info = { 0U };

static const GPIO_PIN_CFG_t USBD_con_pin_cfg_od = {
  GPIO_MODE_OUT_OD, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

static const GPIO_PIN_CFG_t USBD_con_pin_cfg_in = {
  GPIO_MODE_INPUT, GPIO_PULL_DISABLE, GPIO_SPEED_LOW
};

/* USBD Resources */
static const USBD_RESOURCES USBD_Resources = {
  USB,
  RCC_PERIPH_USB,
  USB_LP_CAN1_RX0_IRQn,
  &USBD_Info,
};

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

#if defined (USE_USBD_CON_PIN)

/**
 * @fn          void ConPinConfig(const GPIO_PIN_CFG_t *pin_cfg)
 * @brief       Configure CON pin (controls pull-up on D+ line)
 * @param[in]   pin_cfg  Pointer to GPIO_PIN_CFG_t
 */
static
void ConPinConfig(const GPIO_PIN_CFG_t *pin_cfg)
{
  if (GPIO_GetPortClockState(USBD_CON_GPIOx) == GPIO_PORT_CLK_DISABLE) {
    GPIO_PortClock(USBD_CON_GPIOx, GPIO_PORT_CLK_ENABLE);
  }

  GPIO_PinWrite(USBD_CON_GPIOx, USBD_CON_GPIO_Pin, (GPIO_PIN_OUT_t)(!USBD_CON_ACTIVE));
  GPIO_PinConfig(USBD_CON_GPIOx, USBD_CON_GPIO_Pin, pin_cfg);
}

#endif  /* USE_USB_DEVICE_CON_PIN */

/*******************************************************************************
 *  USBD Driver functions
 ******************************************************************************/

/**
 * @fn          ARM_DRIVER_VERSION USBD_GetVersion(void)
 * @brief       Get driver version.
 * @return      \ref ARM_DRIVER_VERSION
 */
static
ARM_DRIVER_VERSION USBD_GetVersion(void)
{
  return (usbd_driver_version);
}

/**
 * @fn          ARM_USBD_CAPABILITIES USBD_GetCapabilities(void)
 * @brief       Get driver capabilities.
 * @return      \ref ARM_USBD_CAPABILITIES
 */
static
ARM_USBD_CAPABILITIES USBD_GetCapabilities(void)
{
  return (usbd_driver_capabilities);
}

/**
 * @fn          int32_t USBD_Initialize(ARM_USBD_SignalDeviceEvent_t   cb_device_event,
                                        ARM_USBD_SignalEndpointEvent_t cb_endpoint_event)
 * @brief       Initialize USB Device Interface.
 * @param[in]   cb_device_event    Pointer to \ref ARM_USBD_SignalDeviceEvent
 * @param[in]   cb_endpoint_event  Pointer to \ref ARM_USBD_SignalEndpointEvent
 * @return      \ref execution_status
 */
static
int32_t USBD_Initialize(ARM_USBD_SignalDeviceEvent_t   cb_device_event,
                        ARM_USBD_SignalEndpointEvent_t cb_endpoint_event)
{
  USBD_INFO *info = USBD_Resources.info;

  if (info->state & USBD_INITIALIZED) {
    return (ARM_DRIVER_OK);
  }

  /* Initialize Run-Time Resources */
  info->cb_device_event   = cb_device_event;
  info->cb_endpoint_event = cb_endpoint_event;

#if defined (USE_USBD_CON_PIN)
  /* Configure CON pin (controls pull-up on D+ line) */
  ConPinConfig(&USBD_con_pin_cfg_od);
#endif

  info->state = USBD_INITIALIZED;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t USBD_Uninitialize(void)
 * @brief       De-initialize USB Device Interface.
 * @return      \ref execution_status
 */
static
int32_t USBD_Uninitialize(void)
{
  USBD_INFO *info = USBD_Resources.info;

  if (info->state == 0U) {
    return (ARM_DRIVER_OK);
  }

  /* Deinitialize Run-Time Resources */
  info->cb_device_event   = NULL;
  info->cb_endpoint_event = NULL;

#if defined (USE_USBD_CON_PIN)
  /* Unconfigure CON pin (controls pull-up on D+ line) */
  ConPinConfig(&USBD_con_pin_cfg_in);
#endif

  /* Clear state */
  info->state = 0U;

  return (ARM_DRIVER_OK);
}

/**
 * @fn          int32_t USBD_PowerControl(ARM_POWER_STATE state)
 * @brief       Control USB Device Interface Power.
 * @param[in]   state  Power state
 * @return      \ref execution_status
 */
static
int32_t USBD_PowerControl(ARM_POWER_STATE state)
{

}

/**
 * @fn          int32_t USBD_DeviceConnect(void)
 * @brief       Connect USB Device.
 * @return      \ref execution_status
 */
static
int32_t USBD_DeviceConnect(void)
{

}

/**
 * @fn          int32_t USBD_DeviceDisconnect(void)
 * @brief       Disconnect USB Device.
 * @return      \ref execution_status
 */
static
int32_t USBD_DeviceDisconnect(void)
{

}

/**
 * @fn          ARM_USBD_STATE USBD_DeviceGetState(void)
 * @brief       Get current USB Device State.
 * @return      Device State \ref ARM_USBD_STATE
 */
static
ARM_USBD_STATE USBD_DeviceGetState(void)
{

}

/**
 * @fn          int32_t USBD_DeviceRemoteWakeup(void)
 * @brief       Trigger USB Remote Wakeup.
 * @return      \ref execution_status
 */
static
int32_t USBD_DeviceRemoteWakeup(void)
{

}

/**
 * @fn          int32_t USBD_DeviceSetAddress(uint8_t dev_addr)
 * @brief       Set USB Device Address.
 * @param[in]   dev_addr  Device Address
 * @return      \ref execution_status
 */
static
int32_t USBD_DeviceSetAddress(uint8_t dev_addr)
{

}

/**
 * @fn          int32_t USBD_ReadSetupPacket(uint8_t *setup)
 * @brief       Read setup packet received over Control Endpoint.
 * @param[out]  setup  Pointer to buffer for setup packet
 * @return      \ref execution_status
 */
static
int32_t USBD_ReadSetupPacket(uint8_t *setup)
{

}

/**
 * @fn          int32_t USBD_EndpointConfigure(uint8_t ep_addr, uint8_t ep_type, uint16_t ep_max_packet_size)
 * @brief       Configure USB Endpoint.
 * @param[in]   ep_addr  Endpoint Address
 *               - ep_addr.0..7: Address
 *               - ep_addr.7:    Direction
 * @param[in]   ep_type  Endpoint Type (ARM_USB_ENDPOINT_xxx)
 * @param[in]   ep_max_packet_size Endpoint Maximum Packet Size
 * @return      \ref execution_status
 */
static
int32_t USBD_EndpointConfigure(uint8_t ep_addr, uint8_t ep_type, uint16_t ep_max_packet_size)
{

}

/**
 * @fn          int32_t USBD_EndpointUnconfigure(uint8_t ep_addr)
 * @brief       Unconfigure USB Endpoint.
 * @param[in]   ep_addr  Endpoint Address
 *               - ep_addr.0..7: Address
 *               - ep_addr.7:    Direction
 * @return      \ref execution_status
 */
static
int32_t USBD_EndpointUnconfigure(uint8_t ep_addr)
{

}

/**
 * @fn          int32_t USBD_EndpointStall(uint8_t ep_addr, bool stall)
 * @brief       Set/Clear Stall for USB Endpoint.
 * @param[in]   ep_addr  Endpoint Address
 *               - ep_addr.0..7: Address
 *               - ep_addr.7:    Direction
 * @param[in]   stall  Operation
 *               - \b false Clear
 *               - \b true Set
 * @return      \ref execution_status
 */
static
int32_t USBD_EndpointStall(uint8_t ep_addr, bool stall)
{

}

/**
 * @fn          int32_t USBD_EndpointTransfer(uint8_t ep_addr, uint8_t *data, uint32_t num)
 * @brief       Read data from or Write data to USB Endpoint.
 * @param[in]   ep_addr  Endpoint Address
 *               - ep_addr.0..7: Address
 *               - ep_addr.7:    Direction
 * @param[out]  data Pointer to buffer for data to read or with data to write
 * @param[in]   num  Number of data bytes to transfer
 * @return      \ref execution_status
 */
static
int32_t USBD_EndpointTransfer(uint8_t ep_addr, uint8_t *data, uint32_t num)
{

}

/**
 * @fn          uint32_t USBD_EndpointTransferGetResult(uint8_t ep_addr)
 * @brief       Get result of USB Endpoint transfer.
 * @param[in]   ep_addr  Endpoint Address
 *               - ep_addr.0..7: Address
 *               - ep_addr.7:    Direction
 * @return      number of successfully transferred data bytes
 */
static
uint32_t USBD_EndpointTransferGetResult(uint8_t ep_addr)
{

}

/**
 * @fn          int32_t USBD_EndpointTransferAbort(uint8_t ep_addr)
 * @brief       Abort current USB Endpoint transfer.
 * @param[in]   ep_addr  Endpoint Address
 *               - ep_addr.0..7: Address
 *               - ep_addr.7:    Direction
 * @return      \ref execution_status
 */
static
int32_t USBD_EndpointTransferAbort(uint8_t ep_addr)
{

}

/**
 * @fn          uint16_t USBD_GetFrameNumber(void)
 * @brief       Get current USB Frame Number.
 * @return      Frame Number
 */
static
uint16_t USBD_GetFrameNumber(void)
{

}

ARM_DRIVER_USBD Driver_USBD0 = {
  USBD_GetVersion,
  USBD_GetCapabilities,
  USBD_Initialize,
  USBD_Uninitialize,
  USBD_PowerControl,
  USBD_DeviceConnect,
  USBD_DeviceDisconnect,
  USBD_DeviceGetState,
  USBD_DeviceRemoteWakeup,
  USBD_DeviceSetAddress,
  USBD_ReadSetupPacket,
  USBD_EndpointConfigure,
  USBD_EndpointUnconfigure,
  USBD_EndpointStall,
  USBD_EndpointTransfer,
  USBD_EndpointTransferGetResult,
  USBD_EndpointTransferAbort,
  USBD_GetFrameNumber
};
