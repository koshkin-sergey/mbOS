/*
 * Copyright (C) 2018-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: GPIO Driver for STMicroelectronics STM32F4xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>

#include "asm/stm32f1xx.h"
#include "asm/GPIO_STM32F10x.h"
#include "asm/RCC_STM32F10x.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static GPIO_TypeDef* const ports[] = {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
#if defined(STM32F100xB) || defined(STM32F100xE) ||                         \
    defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
    GPIOE,
#if defined(STM32F100xE) ||                         \
    defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xE) || defined(STM32F103xG)
    GPIOF,
    GPIOG,
#endif
#endif
};

static const RCC_Periph_t periph_ports[] = {
    RCC_PERIPH_GPIOA,
    RCC_PERIPH_GPIOB,
    RCC_PERIPH_GPIOC,
    RCC_PERIPH_GPIOD,
#if defined(STM32F100xB) || defined(STM32F100xE) ||                         \
    defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
    RCC_PERIPH_GPIOE,
#if defined(STM32F100xE) ||                         \
    defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xE) || defined(STM32F103xG)
    RCC_PERIPH_GPIOF,
    RCC_PERIPH_GPIOG,
#endif
#endif
};

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/
/**
 * @fn          void GPIO_PortClock(GPIO_PORT_t port, GPIO_PORT_CLK_t state)
 * @brief       Port Clock Control
 * @param[in]   port    GPIO port
 * @param[in]   state   GPIO_PORT_CLK_DISABLE - to disable
 *                      GPIO_PORT_CLK_ENABLE  - to enable
 */
void GPIO_PortClock(GPIO_PORT_t port, GPIO_PORT_CLK_t state)
{
  RCC_Periph_t periph = periph_ports[port];

  if (state != GPIO_PORT_CLK_DISABLE)
    RCC_EnablePeriph(periph);
  else
    RCC_DisablePeriph(periph);
}

/**
 * @fn          GPIO_PORT_CLK_t GPIO_GetPortClockState(GPIO_PORT_t port)
 * @brief       Get GPIO port clock state
 * @param[in]   port    GPIO port (A..G)
 * @return      GPIO_PORT_CLK_DISABLE - disabled
 *              GPIO_PORT_CLK_ENABLE  - enabled
 */
GPIO_PORT_CLK_t GPIO_GetPortClockState(GPIO_PORT_t port)
{
  GPIO_PORT_CLK_t state = GPIO_PORT_CLK_DISABLE;
  RCC_Periph_t periph = periph_ports[port];

  if (RCC_GetStatePeriph(periph) != 0UL) {
    state = GPIO_PORT_CLK_ENABLE;
  }

  return (state);
}

/**
 * @fn          void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 */
void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin)
{
  GPIO_TypeDef *gpio = ports[port];

  gpio->ODR ^= (1UL << pin);
}

/**
 * @fn          void GPIO_PinWrite(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_OUT_t value)
 * @brief       Write port pin
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (GPIO_PIN_OUT_LOW or GPIO_PIN_OUT_HIGH)
 */
void GPIO_PinWrite(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_OUT_t value)
{
  GPIO_TypeDef *gpio = ports[port];
  uint32_t shift = 0;

  if (value == GPIO_PIN_OUT_LOW)
    shift = 16;

  gpio->BSRR = ((1UL << pin) << shift);
}

/**
 * @fn          uint32_t GPIO_PinRead(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Read port pin
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)
 */
uint32_t GPIO_PinRead(GPIO_PORT_t port, GPIO_PIN_t pin)
{
  GPIO_TypeDef *gpio = ports[port];

  return ((gpio->IDR >> pin) & 1UL);
}

/**
 * @fn          void GPIO_PortWrite(GPIO_PORT_t port, uint16_t value)
 * @brief       Write port pins
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   value Pin values
 */
void GPIO_PortWrite(GPIO_PORT_t port, uint16_t value)
{
  GPIO_TypeDef *gpio = ports[port];

  gpio->ODR = (uint32_t)value;
}

/**
 * @fn          uint16_t GPIO_PortRead(GPIO_PORT_t port)
 * @brief       Read port pins
 * @param[in]   port  GPIO port (A..G)
 * @return      port  pin inputs
 */
uint16_t GPIO_PortRead(GPIO_PORT_t port)
{
  GPIO_TypeDef *gpio = ports[port];

  return (uint16_t)gpio->IDR;
}

/**
 * @fn          void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.
 */
void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
{
  GPIO_TypeDef *gpio;
  uint32_t shift;
  uint32_t cr, odr, mode;
  uint32_t *cr_addr;

  if (cfg == NULL)
    return;

  gpio = ports[port];
  cr_addr = &((uint32_t *)gpio)[pin >> 3U];
  shift = (((uint32_t)(pin & 7UL)) << 2);

  cr = *cr_addr & ~(0xF << shift);

  mode = cfg->mode;

  switch (cfg->mode) {
    case GPIO_MODE_ANALOG:
      break;

    case GPIO_MODE_INPUT:
      if (cfg->pull_mode != GPIO_PULL_DISABLE) {
        mode ^= 0xC;
        odr = gpio->ODR & ~(1UL << pin);
        if (cfg->pull_mode == GPIO_PULL_UP) {
          odr |= (1UL << pin);
        }
        gpio->ODR = odr;
      }
      break;

    default:
      mode ^= cfg->speed;
      break;
  }

  *cr_addr = cr | (mode << shift);
}

/**
 * @fn          void GPIO_AFConfig(AFIO_REMAP af_type)
 * @brief       Configure alternate functions
 * @param[in]   af_type  Alternate function remap type
 */
void GPIO_AFConfig(AFIO_REMAP af_type)
{
  uint32_t msk, val, offset;
  __IO uint32_t mapr;

  if (af_type != AFIO_UNAVAILABLE_REMAP) {
    msk = (af_type >> 5) & 0x07;
    val = (af_type >> 8) & 0x0F;
    offset = af_type & 0x1F;

    if (RCC_GetStatePeriph(RCC_PERIPH_AFIO) == 0UL) {
      /* Enable AFIO peripheral clock */
      RCC_EnablePeriph(RCC_PERIPH_AFIO);
    }

    if (af_type & (1UL << 12U)) {
      /* AF remap and debug I/O config register 2 */
      mapr  = AFIO->MAPR2 & ~(msk << offset);
      AFIO->MAPR2 = mapr | (val << offset);
    }
    else {
      /* AF remap and debug I/O config register */
      mapr  = AFIO->MAPR & ~(msk << offset);

      if (offset != 24U) {
        /* Serial wire JTAG configuration */
        mapr |= 7UL << 24U;
      }

      AFIO->MAPR = mapr | (val << offset);
    }
  }
}

/* ----------------------------- End of file ---------------------------------*/
