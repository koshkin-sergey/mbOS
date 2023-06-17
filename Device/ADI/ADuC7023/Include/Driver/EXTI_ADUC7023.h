/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef EXTI_ADUC7023_H_
#define EXTI_ADUC7023_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include <asm/aduc7023.h>
#include <device_config.h>
#include <Core/Arm/irq_ctrl.h>
#include <Driver/GPIO_ADUC7023.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* EXTI configuration definitions */
#if defined (DEV_EXTI) && (DEV_EXTI == 1)
  #if defined (DEV_EXTI_IRQ0) && (DEV_EXTI_IRQ0 == 1)
    #define USE_EXTI_IRQ0
    #define EXTI_IRQ0_GPIO_PORT     DEV_EXTI_IRQ0_PORT
    #define EXTI_IRQ0_GPIO_PIN      DEV_EXTI_IRQ0_PIN
    #define EXTI_IRQ0_GPIO_FUNC     DEV_EXTI_IRQ0_FUNC
    #define EXTI_IRQ0_PULL_UP       DEV_EXTI_IRQ0_PULL_UP
    #define EXTI_IRQ0_INT_PRIO      DEV_EXTI_IRQ0_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ1) && (DEV_EXTI_IRQ1 == 1)
    #define USE_EXTI_IRQ1
    #define EXTI_IRQ1_GPIO_PORT     DEV_EXTI_IRQ1_PORT
    #define EXTI_IRQ1_GPIO_PIN      DEV_EXTI_IRQ1_PIN
    #define EXTI_IRQ1_GPIO_FUNC     DEV_EXTI_IRQ1_FUNC
    #define EXTI_IRQ1_PULL_UP       DEV_EXTI_IRQ1_PULL_UP
    #define EXTI_IRQ1_INT_PRIO      DEV_EXTI_IRQ1_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ2) && (DEV_EXTI_IRQ2 == 1)
    #define USE_EXTI_IRQ2
    #define EXTI_IRQ2_GPIO_PORT     DEV_EXTI_IRQ2_PORT
    #define EXTI_IRQ2_GPIO_PIN      DEV_EXTI_IRQ2_PIN
    #define EXTI_IRQ2_GPIO_FUNC     DEV_EXTI_IRQ2_FUNC
    #define EXTI_IRQ2_PULL_UP       DEV_EXTI_IRQ2_PULL_UP
    #define EXTI_IRQ2_INT_PRIO      DEV_EXTI_IRQ2_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ3) && (DEV_EXTI_IRQ3 == 1)
    #define USE_EXTI_IRQ3
    #define EXTI_IRQ3_GPIO_PORT     DEV_EXTI_IRQ3_PORT
    #define EXTI_IRQ3_GPIO_PIN      DEV_EXTI_IRQ3_PIN
    #define EXTI_IRQ3_GPIO_FUNC     DEV_EXTI_IRQ3_FUNC
    #define EXTI_IRQ3_PULL_UP       DEV_EXTI_IRQ3_PULL_UP
    #define EXTI_IRQ3_INT_PRIO      DEV_EXTI_IRQ3_INT_PRIO
  #endif
#endif

/****** EXTI error codes *****/
#define EXTI_DRIVER_OK                 0                                        ///< Operation succeeded
#define EXTI_DRIVER_ERROR             -1                                        ///< Unspecified error
#define EXTI_DRIVER_ERROR_BUSY        -2                                        ///< Driver is busy
#define EXTI_DRIVER_ERROR_TIMEOUT     -3                                        ///< Timeout occurred
#define EXTI_DRIVER_ERROR_UNSUPPORTED -4                                        ///< Operation not supported
#define EXTI_DRIVER_ERROR_PARAMETER   -5                                        ///< Parameter error

/****** Current driver status flag definition *****/
#define EXTI_FLAG_INITIALIZED         (1UL << 0)                                ///< EXTI initialized
#define EXTI_FLAG_POWERED             (1UL << 1)                                ///< EXTI powered on
#define EXTI_FLAG_CONFIGURED          (1UL << 2)                                ///< EXTI is configured
#define EXTI_FLAG_ENABLE              (1UL << 3)                                ///< EXTI is enabled

/****** EXTI Control Codes *****/
#define EXTI_CONTROL_Pos               0
#define EXTI_CONTROL_Msk              (0xFFUL)
#define EXTI_MODE_INACTIVE            (0x00UL << EXTI_CONTROL_Pos)              ///< Disable EXTI;  arg = External IRQ number
#define EXTI_MODE_ACTIVE              (0x01UL << EXTI_CONTROL_Pos)              ///< Enable and configure EXTI; arg = External IRQ number

/*----- EXTI Control Codes: Configuration Parameters: Trigger Mode -----------*/
#define EXTI_TRG_Pos                   8
#define EXTI_TRG_Msk                  (3UL << EXTI_TRG_Pos)
#define EXTI_TRG_HIGH_LEVEL           (0UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on high level (default)
#define EXTI_TRG_LOW_LEVEL            (1UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on low level
#define EXTI_TRG_RISING_EDGE          (2UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on rising edge
#define EXTI_TRG_FALLING_EDGE         (3UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on falling edge

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum EXT_IRQn {
  EXT_IRQ0                = 0,  /*!< External IRQ0 Interrupt                  */
  EXT_IRQ1                = 1,  /*!< External IRQ1 Interrupt                  */
  EXT_IRQ2                = 2,  /*!< External IRQ2 Interrupt                  */
  EXT_IRQ3                = 3,  /*!< External IRQ3 Interrupt                  */
  EXT_IRQ_NUM,
} EXT_IRQn_t;

/****** EXTI Event *****/
typedef enum EXTI_EVENT {
  EXTI_EVENT_HIGH_LEVEL   = 0,
  EXTI_EVENT_LOW_LEVEL    = 1,
  EXTI_EVENT_RISING_EDGE  = 2,
  EXTI_EVENT_FALLING_EDGE = 3,
} EXTI_EVENT_t;

/**
 * @fn          void EXTI_SignalEvent(uint32_t event)
 * @brief       Signal External Interrupt Events.
 * @param[in]   event  Notification mask
 */
typedef void (*EXTI_SignalEvent_t)(EXT_IRQn_t irqn, EXTI_EVENT_t event);

/* EXTI Pin */
typedef const struct _EXTI_PIN {
  DRIVER_GPIO                *gpio;        // Pointer to GPIO driver
  GPIO_PIN_t                   pin;        // IO pin
  GPIO_PIN_FUNC_t             func;        // AF pin configuration
  GPIO_PULL_t               pullup;        // Pin Pull Up
} EXTI_PIN;

/* EXT IRQ Configuration */
typedef const struct _EXTI_IRQ {
  IRQ_Priority_t          priority;        // EXTI interrupt priority
  IRQn_t                       num;        // EXTI IRQ Number
  IRQHandler_t             handler;        // EXTI IRQ handler
} EXTI_IRQ;

/* EXTI Information (Run-Time) */
typedef struct _EXTI_INFO {
  EXTI_SignalEvent_t      cb_event;        // Event Callback
  uint32_t                   flags;        // Current state flags
} EXTI_INFO;

/* EXTI Resource Configuration */
typedef struct {
  struct EXT_IRQ              *reg;        // EXTI peripheral register interface
  EXTI_PIN       *pin[EXT_IRQ_NUM];        // EXTI Input pins
  EXTI_IRQ       *irq[EXT_IRQ_NUM];        // EXTI interrupt information
  EXTI_INFO                  *info;        // Run-Time information
} const EXTI_RESOURCES;

/**
 * @brief Access structure of the EXTI Driver.
 */
typedef struct Driver_EXTI {
  int32_t       (*Initialize)   (EXTI_SignalEvent_t cb_event);
  int32_t       (*Uninitialize) (void);
  int32_t       (*Control)      (uint32_t control, uint32_t arg);
} const Driver_EXTI_t;

#endif /* EXTI_ADUC7023_H_ */
