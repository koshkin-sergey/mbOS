/*
 * Copyright (C) 2017-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <stddef.h>
#include <Driver/GPIO_ADUCM32x.h>

#include <asm/aducm32x.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define GPIOx_EXPORT_DRIVER(x)    \
static void      GPIO##x##_PinConfig (GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)  {         GPIO_PinConfig (pin, cfg,   MMR_GPIO##x ); } \
static uint8_t   GPIO##x##_PortRead  (void)                                       { return (GPIO_PortRead  (            MMR_GPIO##x)); } \
static void      GPIO##x##_PortWrite (uint8_t value)                              {         GPIO_PortWrite (     value, MMR_GPIO##x ); } \
static uint32_t  GPIO##x##_PinRead   (GPIO_PIN_t pin)                             { return (GPIO_PinRead   (pin,        MMR_GPIO##x)); } \
static void      GPIO##x##_PinWrite  (GPIO_PIN_t pin, GPIO_PIN_OUT_t value)       {         GPIO_PinWrite  (pin, value, MMR_GPIO##x ); } \
static void      GPIO##x##_PinToggle (GPIO_PIN_t pin)                             {         GPIO_PinToggle (pin,        MMR_GPIO##x ); } \
\
extern                            \
Driver_GPIO_t Driver_GPIO##x;     \
Driver_GPIO_t Driver_GPIO##x = {  \
  GPIO##x##_PinConfig,            \
  GPIO##x##_PortRead,             \
  GPIO##x##_PortWrite,            \
  GPIO##x##_PinRead,              \
  GPIO##x##_PinWrite,             \
  GPIO##x##_PinToggle,            \
}

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   pin   Port pin number (0..7)
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.
 */
static void GPIO_PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg, MMR_GPIO_t *mmr)
{
  uint8_t oer;
  uint8_t ier;
  uint8_t pulr;
  uint8_t oder;
  uint16_t conr;

  if (cfg == NULL) {
    return;
  }

  conr = (mmr->GPCON & ~GPIO_CON(3U, pin));
  oer  = (mmr->GPOE  & ~GPIO_OE (1U, pin));
  ier  = (mmr->GPIE  & ~GPIO_IE (1U, pin));
  oder = (mmr->GPODE & ~GPIO_ODE(1U, pin));
  pulr = (mmr->GPPUL & ~GPIO_PUL(1U, pin));

  mmr->GPCON = (conr | GPIO_CON(cfg->func >> 0, pin));
  mmr->GPIE  = (ier  | GPIO_IE (cfg->mode >> 0, pin));
  mmr->GPOE  = (oer  | GPIO_OE (cfg->mode >> 1, pin));
  mmr->GPODE = (oder | GPIO_ODE(cfg->mode >> 2, pin));
  mmr->GPPUL = (pulr | GPIO_PUL(cfg->pull >> 0, pin));
}

/**
 * @brief       Read port pins
 * @return      port pin inputs
 */
static uint8_t GPIO_PortRead(MMR_GPIO_t *mmr)
{
  return (mmr->GPIN);
}

/**
 * @brief       Write port pins
 * @param[in]   value  Pin values
 */
static void GPIO_PortWrite(uint8_t value, MMR_GPIO_t *mmr)
{
  mmr->GPOUT = value;
}

/**
 * @brief       Read port pin
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)
 */
static uint32_t GPIO_PinRead(GPIO_PIN_t pin, MMR_GPIO_t *mmr)
{
  return ((mmr->GPIN >> pin) & 1U);
}

/**
 * @brief       Write port pin
 * @param[in]   pin     Port pin number
 * @param[in]   value   Port pin value, should be one of the following:
 *                        - GPIO_PIN_OUT_LOW
 *                        - GPIO_PIN_OUT_HIGH
 */
static void GPIO_PinWrite(GPIO_PIN_t pin, GPIO_PIN_OUT_t value, MMR_GPIO_t *mmr)
{
  if (value == GPIO_PIN_OUT_HIGH)
    mmr->GPSET = GPIO_SET(pin);
  else
    mmr->GPCLR = GPIO_CLR(pin);
}

/**
 * @fn          void PinToggle(GPIO_PIN_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   pin   Port pin number
 */
static void GPIO_PinToggle(GPIO_PIN_t pin, MMR_GPIO_t *mmr)
{
  mmr->GPTGL = GPIO_TGL(pin);
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

GPIOx_EXPORT_DRIVER(0);
GPIOx_EXPORT_DRIVER(1);
GPIOx_EXPORT_DRIVER(2);
GPIOx_EXPORT_DRIVER(3);
GPIOx_EXPORT_DRIVER(4);
GPIOx_EXPORT_DRIVER(5);
