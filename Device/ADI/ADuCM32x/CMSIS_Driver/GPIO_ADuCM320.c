/*
 * Copyright (C) 2017 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: GPIO Driver for ADI ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "stddef.h"
#include "ADuCM320.h"
#include "GPIO_ADuCM320.h"

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

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
ADI_GPIO_TypeDef* GetPort(GPIO_PORT_t port_num)
{
  ADI_GPIO_TypeDef *port = NULL;

  switch (port_num) {
    case GPIO_PORT_0:
      port = pADI_GP0;
      break;
    case GPIO_PORT_1:
      port = pADI_GP1;
      break;
    case GPIO_PORT_2:
      port = pADI_GP2;
      break;
    case GPIO_PORT_3:
      port = pADI_GP3;
      break;
    case GPIO_PORT_4:
      port = pADI_GP4;
      break;
    case GPIO_PORT_5:
      port = pADI_GP5;
      break;
  }

  return port;
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Write port pin
 * @param[in]   port_num  GPIO number (0..5)
 * @param[in]   pin_num   Port pin number
 * @param[in]   val       Port pin value, should be one of the following:
 *                        - GPIO_PIN_OUT_LOW
 *                        - GPIO_PIN_OUT_HIGH
 */
void GPIO_PinWrite(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, GPIO_PIN_OUT_t val)
{
  ADI_GPIO_TypeDef *port = GetPort(port_num);

  if (val == GPIO_PIN_OUT_HIGH)
    port->GPSET = (uint8_t)(1U << pin_num);
  else
    port->GPCLR = (uint8_t)(1U << pin_num);
}

/**
 * @brief       Toggle the output of the port pin
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   pin_num    Port pin number
 */
void GPIO_PinToggle(GPIO_PORT_t port_num, GPIO_PIN_t pin_num)
{
  ADI_GPIO_TypeDef *port = GetPort(port_num);

  port->GPTGL = (uint8_t)(1U << pin_num);
}

/**
 * @brief       Read port pin
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   pin_num    Port pin number
 * @return      pin value (0 or 1)
 */
uint8_t GPIO_PinRead(GPIO_PORT_t port_num, GPIO_PIN_t pin_num)
{
  ADI_GPIO_TypeDef *port = GetPort(port_num);

  return ((port->GPIN >> pin_num) & 1U);
}

/**
 * @brief       Write port pins
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   val        Pin values
 */
void GPIO_PortWrite(GPIO_PORT_t port_num, uint8_t val)
{
  ADI_GPIO_TypeDef *port = GetPort(port_num);

  port->GPOUT = val;
}

/**
 * @brief       Read port pins
 * @param[in]   port_num   GPIO number (0..5)
 * @return      port pin inputs
 */
uint8_t GPIO_PortRead(GPIO_PORT_t port_num)
{
  ADI_GPIO_TypeDef *port = GetPort(port_num);

  return port->GPIN;
}

/**
 * @fn          void GPIO_PinConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   port_num  GPIO port (0..5)
 * @param[in]   pin_num   Port pin number (0..7)
 * @param[in]   cfg       Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                        configuration information for the specified pin.
 */
void GPIO_PinConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, const GPIO_PIN_CFG_t *cfg)
{
  ADI_GPIO_TypeDef *port;
  uint8_t pin;
  uint8_t oer, ier, pulr, oder;

  if (cfg == NULL)
    return;

  port = GetPort(port_num);
  pin = (uint8_t)(1U << pin_num);

  oer = (port->GPOE & ~pin);
  ier = (port->GPIE & ~pin);
  oder = (port->GPODE & ~pin);
  pulr = (port->GPPUL & ~pin);

  port->GPIE = (ier | (((cfg->mode >> 0) & 1U) << pin_num));
  port->GPOE = (oer | (((cfg->mode >> 1) & 1U) << pin_num));
  port->GPODE = (oder | (((cfg->mode >> 2) & 1U) << pin_num));
  port->GPPUL = (pulr | ((cfg->pull_mode & 1U) << pin_num));
}

/**
 * @fn          void GPIO_AFConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, GPIO_PIN_FUNC_t af_num)
 * @brief       Configure alternate functions
 * @param[in]   port_num  GPIO port (0..5)
 * @param[in]   pin_num   Port pin number (0..7)
 * @param[in]   af_num  Alternate function number
 */
void GPIO_AFConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, GPIO_PIN_FUNC_t af_num)
{
  ADI_GPIO_TypeDef *port = GetPort(port_num);
  uint32_t shift = (pin_num << 1);
  uint16_t con = (port->GPCON & ~(3U << shift));

  port->GPCON = (con | ((uint16_t)af_num << shift));
}

/* ----------------------------- End of file ---------------------------------*/
