/*
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
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/Driver_GPIO.h>
#include <asm/rp2040_reset.h>
#include <asm/rp2040_sio.h>
#include <asm/rp2040_pads_bank0.h>
#include <asm/rp2040_io_bank0.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

// Pin mapping
#define GPIO_MAX_PINS               (30U)
#define PIN_IS_AVAILABLE(n)         ((n) < GPIO_MAX_PINS)

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

// Setup GPIO Interface
static
int32_t GPIO_Setup(GPIO_Pin_t pin, GPIO_SignalEvent_t cb_event)
{
  (void) cb_event;
  int32_t result = DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    /* Get pads and GPIO out of reset */
    uint32_t reset = RESETS->RESET;
    if ((reset & (RESETS_RESET_IO_BANK0 | RESETS_RESET_PADS_BANK0)) != 0U) {
      reset &= ~(RESETS_RESET_IO_BANK0 | RESETS_RESET_PADS_BANK0);
      RESETS->RESET = reset;
    }

    /* Clear Output and Output enable */
    SIO->GPIO_OE_CLR  = SIO_GPIO_MASK(pin);
    SIO->GPIO_OUT_CLR = SIO_GPIO_MASK(pin);

    /* Set PAD config to input enable */
    PADS_BANK0->GPIO[pin] = (
        PADS_BANK0_GPIO_SCHMITT_EN |
        PADS_BANK0_GPIO_DRIVE_4MA  |
        PADS_BANK0_GPIO_IE);

    /* Set GPIO Control to alt func SIO */
    IO_BANK0->GPIO[pin].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_SIO;
  } else {
    result = GPIO_ERROR_PIN;
  }

  return (result);
}

// Set GPIO Direction
static
int32_t GPIO_SetDirection(GPIO_Pin_t pin, GPIO_DIRECTION direction)
{
  int32_t result = DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    switch (direction) {
      case GPIO_INPUT:
        SIO->GPIO_OE_CLR = SIO_GPIO_MASK(pin);
        break;

      case GPIO_OUTPUT:
        SIO->GPIO_OE_SET = SIO_GPIO_MASK(pin);
        break;

      default:
        result = DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = GPIO_ERROR_PIN;
  }

  return (result);
}

// Set GPIO Output Mode
static
int32_t GPIO_SetOutputMode(GPIO_Pin_t pin, GPIO_OUTPUT_MODE mode)
{
  int32_t result = DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    switch (mode) {
      case GPIO_PUSH_PULL:
        break;
      case GPIO_OPEN_DRAIN:
        break;
      default:
        result = DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = GPIO_ERROR_PIN;
  }

  return (result);
}

// Set GPIO Pull Resistor
static
int32_t GPIO_SetPullResistor(GPIO_Pin_t pin, GPIO_PULL_RESISTOR resistor)
{
  uint32_t gpio;
  int32_t result = DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    gpio = PADS_BANK0->GPIO[pin] & ~(PADS_BANK0_GPIO_PDE | PADS_BANK0_GPIO_PUE);

    switch (resistor) {
      case GPIO_PULL_NONE:
        break;

      case GPIO_PULL_UP:
        gpio |= PADS_BANK0_GPIO_PUE;
        break;

      case GPIO_PULL_DOWN:
        gpio |= PADS_BANK0_GPIO_PDE;
        break;

      default:
        result = DRIVER_ERROR_PARAMETER;
        break;
    }

    PADS_BANK0->GPIO[pin] = gpio;
  } else {
    result = GPIO_ERROR_PIN;
  }

  return (result);
}

// Set GPIO Event Trigger
static
int32_t GPIO_SetEventTrigger(GPIO_Pin_t pin, GPIO_EVENT_TRIGGER trigger)
{
  int32_t result = DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    switch (trigger) {
      case GPIO_TRIGGER_NONE:
        break;
      case GPIO_TRIGGER_RISING_EDGE:
        break;
      case GPIO_TRIGGER_FALLING_EDGE:
        break;
      case GPIO_TRIGGER_EITHER_EDGE:
        break;
      default:
        result = DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = GPIO_ERROR_PIN;
  }

  return (result);
}

// Set GPIO Output Level
static
void GPIO_SetOutput(GPIO_Pin_t pin, uint32_t val)
{
  if (PIN_IS_AVAILABLE(pin)) {
    if (val != 0U) {
      SIO->GPIO_OUT_SET = SIO_GPIO_MASK(pin);
    }
    else {
      SIO->GPIO_OUT_CLR = SIO_GPIO_MASK(pin);
    }
  }
}

// Get GPIO Input Level
static
uint32_t GPIO_GetInput(GPIO_Pin_t pin)
{
  uint32_t val = 0U;

  if (PIN_IS_AVAILABLE(pin)) {
    val = (SIO->GPIO_IN >> pin) & 1UL;
  }

  return (val);
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

// GPIO Driver access structure
extern
DRIVER_GPIO Driver_GPIO;
DRIVER_GPIO Driver_GPIO = {
  GPIO_Setup,
  GPIO_SetDirection,
  GPIO_SetOutputMode,
  GPIO_SetPullResistor,
  GPIO_SetEventTrigger,
  GPIO_SetOutput,
  GPIO_GetInput
};
