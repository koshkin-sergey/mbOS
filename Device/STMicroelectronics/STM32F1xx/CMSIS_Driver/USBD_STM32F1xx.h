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
 * Project: USB Device Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef USBD_STM32F1XX_H_
#define USBD_STM32F1XX_H_

#include "device_config.h"
#include "Driver/Driver_USBD.h"

#include "asm/stm32f1xx.h"
#include "asm/RCC_STM32F1xx.h"

/* USB Device configuration definitions */
#if (DEV_USB_DEVICE == 1)
  #define USE_USB_DEVICE

  #if !defined(USB)
    #error "USB not available for selected device!"
    #undef USE_USB_DEVICE
  #endif

  #if (DEV_USB_DEVICE_CON_PIN == 1)
    #define USE_USBD_CON_PIN          1U
    #define USBD_CON_ACTIVE           DEV_USB_DEVICE_CON_ACTIVE
    #define USBD_CON_GPIOx            (GPIO_PORT_t)DEV_USB_DEVICE_CON_PORT
    #define USBD_CON_GPIO_Pin         (GPIO_PIN_t) DEV_USB_DEVICE_CON_BIT
  #endif
#endif

/* Current driver state flags definition */
#define USBD_INITIALIZED          ((uint8_t)(1U << 0U))   // USBD initialized
#define USBD_POWERED              ((uint8_t)(1U << 1U))   // USBD powered on
#define USBD_CONFIGURED           ((uint8_t)(1U << 2U))   // USBD configured

/* USBD Information (Run-time) */
typedef struct USBD_INFO_s {
  ARM_USBD_SignalDeviceEvent_t    cb_device_event;    // Device Event Callback
  ARM_USBD_SignalEndpointEvent_t  cb_endpoint_event;  // Endpoint Event Callback
  uint8_t                         state;              // Current state
} USBD_INFO;

/* USBD Resources definition */
typedef struct USBD_RESOURCES_s {
  USB_TypeDef          *reg;            // USB peripheral pointer
  RCC_Periph_t          periph;         // Peripheral
  IRQn_Type             irq_num;        // USBD IRQ Number
//  USBD_IO               io;             // USBD pins
  USBD_INFO            *info;           // Run-Time Information
//  USBD_TRANSFER_INFO   *xfer;           // SPI transfer information
} USBD_RESOURCES;

#endif /* USBD_STM32F1XX_H_ */
