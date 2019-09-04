/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: GPIO Driver for STMicroelectronics STM32F7xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>

#include "GPIO_STM32F7xx.h"
#include "RCC_STM32F7xx.h"

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
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
    GPIOI,
#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F750xx) || \
    defined(STM32F756xx) || defined(STM32F765xx) || defined(STM32F767xx) || \
    defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F779xx)
    GPIOJ,
    GPIOK,
#endif
};

static const RCC_Periph_t periph_ports[] = {
    RCC_PERIPH_GPIOA,
    RCC_PERIPH_GPIOB,
    RCC_PERIPH_GPIOC,
    RCC_PERIPH_GPIOD,
    RCC_PERIPH_GPIOE,
    RCC_PERIPH_GPIOF,
    RCC_PERIPH_GPIOG,
    RCC_PERIPH_GPIOH,
#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F750xx) || \
    defined(STM32F756xx) || defined(STM32F765xx) || defined(STM32F767xx) || \
    defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F779xx)
    RCC_PERIPH_GPIOJ,
    RCC_PERIPH_GPIOK,
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
  RCC_Periph_t gpio = periph_ports[port];

  if (state != GPIO_PORT_CLK_DISABLE)
    RCC_EnablePeriph(gpio);
  else
    RCC_DisablePeriph(gpio);
}

/**
 * @fn          bool GPIO_GetPortClockState(GPIO_PORT_t port)
 * @brief       Get GPIO port clock state
 * @param[in]   port    GPIO port
 * @return      false - disabled
 *              true  - enabled
 */
bool GPIO_GetPortClockState(GPIO_PORT_t port)
{
  RCC_Periph_t gpio = periph_ports[port];

  return (RCC_GetStatePeriph(gpio) != 0UL);
}

/**
 * @fn          void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   port  GPIO port
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
 * @param[in]   port  GPIO port
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (0 or 1)
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
 * @param[in]   port  GPIO port
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
 * @param[in]   port  GPIO port
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
 * @param[in]   port  GPIO port
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
 * @param[in]   port  GPIO port
 * @param[in]   pin   Port pin number (0..15)
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.
 */
void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
{
  GPIO_TypeDef *gpio;
  uint32_t shift;
  uint32_t moder, otyper, ospeedr, pupdr;

  if (cfg == NULL)
    return;

  gpio = ports[port];
  shift = (pin << 1);

  moder = (gpio->MODER & ~(3UL << shift));
  otyper = (gpio->OTYPER & ~(1UL << pin));
  ospeedr = (gpio->OSPEEDR & ~(3UL << shift));
  pupdr = (gpio->PUPDR & ~(3UL << shift));

  gpio->OTYPER = (otyper | (((cfg->mode >> 8) & 1UL) << pin));
  gpio->OSPEEDR = (ospeedr | ((cfg->speed & 3UL) << shift));
  gpio->PUPDR = (pupdr | ((cfg->pull_mode & 3UL) << shift));
  gpio->MODER = (moder | ((cfg->mode & 3UL) << shift));
}

/**
 * @fn          void GPIO_AFConfig(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_FUNC_t af_num)
 * @brief       Configure alternate functions
 * @param[in]   port    GPIO port
 * @param[in]   pin     Port pin number (0..15)
 * @param[in]   af_num  Alternate function number
 */
void GPIO_AFConfig(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_FUNC_t af_num)
{
  uint32_t afr;
  uint32_t shift = (((uint32_t)(pin & 7UL)) << 2);
  GPIO_TypeDef *gpio = ports[port];
  volatile uint32_t *pafr = &gpio->AFR[pin >> 3];

  afr = (*pafr & ~(0xF << shift));
  *pafr = (afr | ((uint32_t)af_num << shift));
}

/* ----------------------------- End of file ---------------------------------*/
