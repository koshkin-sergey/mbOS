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
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static GPIO_SignalEvent_t gpio_callback[GPIO_MAX_PINS];

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

// Setup GPIO Interface
static
int32_t GPIO_Setup(GPIO_Pin_t pin, GPIO_SignalEvent_t cb_event)
{
  int32_t result = DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    uint32_t ofs;

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

    ofs = 4U * (pin % 8U);
    IO_BANK0->PROC[SIO->CPUID].INT_ENABLE[pin / 8U] &= ~(0xFUL << ofs);
    IO_BANK0->PROC[SIO->CPUID].INT_FORCE[pin / 8U] &= ~(0xFUL << ofs);

    gpio_callback[pin] = cb_event;
    if (cb_event != NULL) {
      NVIC_ClearPendingIRQ(IO_IRQ_BANK0_IRQn);
      NVIC_EnableIRQ(IO_IRQ_BANK0_IRQn);
    }
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
  (void) pin;
  (void) mode;

  return (DRIVER_ERROR_UNSUPPORTED);
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
    uint32_t ofs;
    uint32_t val;

    ofs = 4U * (pin % 8U);
    val = IO_BANK0->PROC[SIO->CPUID].INT_ENABLE[pin / 8U];
    val &= ~(0xFUL << ofs);
    IO_BANK0->INT_RAW[pin / 8U] |= 0xFUL << ofs;

    switch (trigger) {
      case GPIO_TRIGGER_NONE:
        break;

      case GPIO_TRIGGER_RISING_EDGE:
        val |= IO_BANK0_GPIO_INT_EDGE_HIGH << ofs;
        break;

      case GPIO_TRIGGER_FALLING_EDGE:
        val |= IO_BANK0_GPIO_INT_EDGE_LOW << ofs;
        break;

      case GPIO_TRIGGER_EITHER_EDGE:
        val |= (IO_BANK0_GPIO_INT_EDGE_HIGH | IO_BANK0_GPIO_INT_EDGE_LOW) << ofs;
        break;

      case GPIO_TRIGGER_HIGH_LEVEL:
        val |= IO_BANK0_GPIO_INT_LEVEL_HIGH << ofs;
        break;

      case GPIO_TRIGGER_LOW_LEVEL:
        val |= IO_BANK0_GPIO_INT_LEVEL_LOW << ofs;
        break;

      default:
        result = DRIVER_ERROR_PARAMETER;
        break;
    }

    IO_BANK0->PROC[SIO->CPUID].INT_ENABLE[pin / 8U] = val;
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

extern
void IO_BANK0_IRQHandler(void);
void IO_BANK0_IRQHandler(void)
{
  for (uint32_t pin = 0U; pin < GPIO_MAX_PINS; pin += 8U) {
    uint32_t int_stat = IO_BANK0->PROC[SIO->CPUID].INT_STATUS[pin / 8U];
    uint32_t mask = 0x0000000FUL;
    for (uint32_t i = pin; int_stat != 0U && i < pin+8U; ++i) {
      uint32_t stat = int_stat & 0xFUL;
      if (stat != 0U) {
        IO_BANK0->INT_RAW[pin / 8U] |= mask;
        if (gpio_callback[i] != NULL) {
          uint32_t event = 0U;

          if (stat & IO_BANK0_GPIO_INT_LEVEL_LOW) {
            event |= GPIO_EVENT_LOW_LEVEL;
          }

          if (stat & IO_BANK0_GPIO_INT_LEVEL_HIGH) {
            event |= GPIO_EVENT_HIGH_LEVEL;
          }

          if (stat & IO_BANK0_GPIO_INT_EDGE_LOW) {
            event |= GPIO_EVENT_FALLING_EDGE;
          }

          if (stat & IO_BANK0_GPIO_INT_EDGE_HIGH) {
            event |= GPIO_EVENT_RISING_EDGE;
          }

          gpio_callback[i](i, event);
        }
      }
      int_stat >>= 4U;
      mask     <<= 4U;
    }
  }
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
