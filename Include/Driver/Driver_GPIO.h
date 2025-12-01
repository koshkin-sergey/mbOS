/*
 * Copyright (c) 2023-2025 ARM Limited.
 * Copyright (C) 2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *
 * $Date:        23. November 2025
 * $Revision:    V1.0
 *
 * Project:      GPIO (General-purpose Input/Output) Driver definitions
 */

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"


/**
\brief GPIO Pin
*/
typedef uint32_t GPIO_Pin_t;

/**
\brief GPIO Direction
*/
typedef enum {
  GPIO_INPUT,                       ///< Input (default)
  GPIO_OUTPUT                       ///< Output
} GPIO_DIRECTION;

/**
\brief GPIO Output Mode
*/
typedef enum {
  GPIO_PUSH_PULL,                   ///< Push-pull (default)
  GPIO_OPEN_DRAIN                   ///< Open-drain
} GPIO_OUTPUT_MODE;

/**
\brief GPIO Pull Resistor
*/
typedef enum {
  GPIO_PULL_NONE,                   ///< None (default)
  GPIO_PULL_UP,                     ///< Pull-up
  GPIO_PULL_DOWN                    ///< Pull-down
} GPIO_PULL_RESISTOR;

/**
\brief GPIO Event Trigger
*/
typedef enum {
  GPIO_TRIGGER_NONE,                ///< None (default)
  GPIO_TRIGGER_RISING_EDGE,         ///< Rising-edge
  GPIO_TRIGGER_FALLING_EDGE,        ///< Falling-edge
  GPIO_TRIGGER_EITHER_EDGE          ///< Either edge (rising and falling)
} GPIO_EVENT_TRIGGER;


/****** GPIO Event *****/
#define GPIO_EVENT_RISING_EDGE      (1UL << 0)  ///< Rising-edge detected
#define GPIO_EVENT_FALLING_EDGE     (1UL << 1)  ///< Falling-edge detected
#define GPIO_EVENT_EITHER_EDGE      (1UL << 2)  ///< Either edge detected (only when hardware cannot distinguish between rising and falling edge)


/****** GPIO specific error codes *****/
#define GPIO_ERROR_PIN              (DRIVER_ERROR_SPECIFIC - 1) ///< Specified Pin not available


// Function documentation
/**
  \fn          int32_t GPIO_Setup (GPIO_Pin_t pin, GPIO_SignalEvent_t cb_event)
  \brief       Setup GPIO Interface.
  \param[in]   pin  GPIO Pin
  \param[in]   cb_event  Pointer to \ref GPIO_SignalEvent
  \return      \ref execution_status

  \fn          int32_t GPIO_SetDirection (GPIO_Pin_t pin, GPIO_DIRECTION direction)
  \brief       Set GPIO Direction.
  \param[in]   pin  GPIO Pin
  \param[in]   direction  \ref GPIO_DIRECTION
  \return      \ref execution_status

  \fn          int32_t GPIO_SetOutputMode (GPIO_Pin_t pin, GPIO_OUTPUT_MODE mode)
  \brief       Set GPIO Output Mode.
  \param[in]   pin  GPIO Pin
  \param[in]   mode  \ref GPIO_OUTPUT_MODE
  \return      \ref execution_status

  \fn          int32_t GPIO_SetPullResistor (GPIO_Pin_t pin, GPIO_PULL_RESISTOR resistor)
  \brief       Set GPIO Pull Resistor.
  \param[in]   pin  GPIO Pin
  \param[in]   resistor  \ref GPIO_PULL_RESISTOR
  \return      \ref execution_status

  \fn          int32_t GPIO_SetEventTrigger (GPIO_Pin_t pin, GPIO_EVENT_TRIGGER trigger)
  \brief       Set GPIO Event Trigger.
  \param[in]   pin  GPIO Pin
  \param[in]   trigger  \ref GPIO_EVENT_TRIGGER
  \return      \ref execution_status

  \fn          void GPIO_SetOutput (GPIO_Pin_t pin, uint32_t val)
  \brief       Set GPIO Output Level.
  \param[in]   pin  GPIO Pin
  \param[in]   val  GPIO Pin Level (0 or 1)

  \fn          uint32_t GPIO_GetInput (GPIO_Pin_t pin)
  \brief       Get GPIO Input Level.
  \param[in]   pin  GPIO Pin
  \return      GPIO Pin Level (0 or 1)

  \fn          void GPIO_SignalEvent (GPIO_Pin_t pin, uint32_t event)
  \brief       Signal GPIO Events.
  \param[in]   pin    GPIO Pin on which event occurred
  \param[in]   event  \ref GPIO_events notification mask
*/

typedef void (*GPIO_SignalEvent_t) (GPIO_Pin_t pin, uint32_t event);  /* Pointer to \ref GPIO_SignalEvent : Signal GPIO Event */


/**
\brief Access structure of the GPIO Driver.
*/
typedef struct _DRIVER_GPIO {
  int32_t  (*Setup)           (GPIO_Pin_t pin, GPIO_SignalEvent_t cb_event);    ///< Pointer to \ref GPIO_Setup : Setup GPIO Interface.
  int32_t  (*SetDirection)    (GPIO_Pin_t pin, GPIO_DIRECTION direction);       ///< Pointer to \ref GPIO_SetDirection : Set GPIO Direction.
  int32_t  (*SetOutputMode)   (GPIO_Pin_t pin, GPIO_OUTPUT_MODE mode);          ///< Pointer to \ref GPIO_SetOutputMode : Set GPIO Output Mode.
  int32_t  (*SetPullResistor) (GPIO_Pin_t pin, GPIO_PULL_RESISTOR resistor);    ///< Pointer to \ref GPIO_SetPullResistor : Set GPIO Pull Resistor.
  int32_t  (*SetEventTrigger) (GPIO_Pin_t pin, GPIO_EVENT_TRIGGER trigger);     ///< Pointer to \ref GPIO_SetEventTrigger : Set GPIO Event Trigger.
  void     (*SetOutput)       (GPIO_Pin_t pin, uint32_t val);                   ///< Pointer to \ref GPIO_SetOutput : Set GPIO Output Level.
  uint32_t (*GetInput)        (GPIO_Pin_t pin);                                 ///< Pointer to \ref GPIO_GetInput : Get GPIO Input Level.
} const DRIVER_GPIO;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H_ */
