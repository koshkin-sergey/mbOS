/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <asm/Driver_GPIO.h>
#include <stddef.h>
#include "asm/aduc7023.h"

typedef const struct _GPIO_RESOURCES {
  __IOM uint32_t *CON;
  __IOM uint32_t *DAT;
  __OM  uint32_t *SET;
  __OM  uint32_t *CLR;
  __IOM uint32_t *PAR;
} GPIO_RESOURCES;

/* GPIO0 Resources */
static const GPIO_RESOURCES GPIO0_Resources = {
  GP0CON,
  GP0DAT,
  GP0SET,
  GP0CLR,
  GP0PAR,
};

/* GPIO1 Resources */
static const GPIO_RESOURCES GPIO1_Resources = {
  GP1CON,
  GP1DAT,
  GP1SET,
  GP1CLR,
  GP1PAR,
};

/* GPIO2 Resources */
static const GPIO_RESOURCES GPIO2_Resources = {
  GP2CON,
  GP2DAT,
  GP2SET,
  GP2CLR,
  GP2PAR,
};

/**
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   pin   Port pin number (0..7)
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.
 */
static
void GPIO_PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg, const GPIO_RESOURCES *gpio)
{
  uint32_t con;
  uint32_t dat;
  uint32_t par;
  uint32_t dat_pos;
  uint32_t pin_pos;

  if (cfg == NULL) {
    return;
  }

  pin_pos = pin * 4U;

  con = *gpio->CON & ~(3UL << pin_pos);
  *gpio->CON = con | (cfg->func << pin_pos);

  if (cfg->func == GPIO_PIN_FUNC_0) {
    dat_pos = GPIO_DAT_DIR_Pos + pin;

    par = *gpio->PAR & ~(7UL << pin_pos);
    dat = *gpio->DAT & ~(1UL << dat_pos);

    *gpio->PAR = par | ((cfg->pull_mode | cfg->strength) << pin_pos);
    *gpio->DAT = dat | (cfg->mode << dat_pos);
  }
}

/**
 * @brief       Read port pins
 * @return      port  pin inputs
 */
static
uint8_t GPIO_PortRead(const GPIO_RESOURCES *gpio)
{
  return ((uint8_t)((*gpio->DAT & GPIO_DAT_INPUT_Msk) >> GPIO_DAT_INPUT_Pos));
}

/**
 * @brief       Write port pins
 * @param[in]   value Pin values
 */
static
void GPIO_PortWrite(uint8_t value, const GPIO_RESOURCES *gpio)
{
  *gpio->DAT = ((uint32_t)value << GPIO_DAT_OUTPUT_Pos) & GPIO_DAT_OUTPUT_Msk;
}

/**
 * @brief       Read port pin
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)
 */
static
uint32_t GPIO_PinRead(GPIO_PIN_t pin, const GPIO_RESOURCES *gpio)
{
  uint8_t value = (uint8_t)((*gpio->DAT & GPIO_DAT_INPUT_Msk) >> GPIO_DAT_INPUT_Pos);
  return ((value >> pin) & 1U);
}

/**
 * @brief       Write port pin
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (0 or 1)
 */
static
void GPIO_PinWrite(GPIO_PIN_t pin, GPIO_PIN_OUT_t value, const GPIO_RESOURCES *gpio)
{
  if (value == GPIO_PIN_OUT_LOW) {
    *gpio->CLR = (1UL << GPIO_CLR_BIT_Pos) << pin;
  }
  else {
    *gpio->SET = (1UL << GPIO_SET_BIT_Pos) << pin;
  }
}

/**
 * @brief       Toggle the output of the port pin
 * @param[in]   pin   Port pin number
 */
static
void GPIO_PinToggle(GPIO_PIN_t pin, const GPIO_RESOURCES *gpio)
{
  *gpio->DAT ^= (1UL << GPIO_DAT_OUTPUT_Pos) << pin;
}

static void      GPIO0_PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)  {         GPIO_PinConfig(pin, cfg, &GPIO0_Resources);   };
static uint8_t   GPIO0_PortRead(void)                                        { return (GPIO_PortRead(&GPIO0_Resources));             };
static void      GPIO0_PortWrite(uint8_t value)                              {         GPIO_PortWrite(value, &GPIO0_Resources);      };
static uint32_t  GPIO0_PinRead(GPIO_PIN_t pin)                               { return (GPIO_PinRead(pin, &GPIO0_Resources));         };
static void      GPIO0_PinWrite(GPIO_PIN_t pin, GPIO_PIN_OUT_t value)        {         GPIO_PinWrite(pin, value, &GPIO0_Resources);  };
static void      GPIO0_PinToggle(GPIO_PIN_t pin)                             {         GPIO_PinToggle(pin, &GPIO0_Resources);        };

DRIVER_GPIO DRIVER_GPIO0 = {
  GPIO0_PinConfig,
  GPIO0_PortRead,
  GPIO0_PortWrite,
  GPIO0_PinRead,
  GPIO0_PinWrite,
  GPIO0_PinToggle,
};

static void      GPIO1_PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)  {         GPIO_PinConfig(pin, cfg, &GPIO1_Resources);   };
static uint8_t   GPIO1_PortRead(void)                                        { return (GPIO_PortRead(&GPIO1_Resources));             };
static void      GPIO1_PortWrite(uint8_t value)                              {         GPIO_PortWrite(value, &GPIO1_Resources);      };
static uint32_t  GPIO1_PinRead(GPIO_PIN_t pin)                               { return (GPIO_PinRead(pin, &GPIO1_Resources));         };
static void      GPIO1_PinWrite(GPIO_PIN_t pin, GPIO_PIN_OUT_t value)        {         GPIO_PinWrite(pin, value, &GPIO1_Resources);  };
static void      GPIO1_PinToggle(GPIO_PIN_t pin)                             {         GPIO_PinToggle(pin, &GPIO1_Resources);        };

DRIVER_GPIO DRIVER_GPIO1 = {
  GPIO1_PinConfig,
  GPIO1_PortRead,
  GPIO1_PortWrite,
  GPIO1_PinRead,
  GPIO1_PinWrite,
  GPIO1_PinToggle,
};

static void      GPIO2_PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)  {         GPIO_PinConfig(pin, cfg, &GPIO2_Resources);   };
static uint8_t   GPIO2_PortRead(void)                                        { return (GPIO_PortRead(&GPIO2_Resources));             };
static void      GPIO2_PortWrite(uint8_t value)                              {         GPIO_PortWrite(value, &GPIO2_Resources);      };
static uint32_t  GPIO2_PinRead(GPIO_PIN_t pin)                               { return (GPIO_PinRead(pin, &GPIO2_Resources));         };
static void      GPIO2_PinWrite(GPIO_PIN_t pin, GPIO_PIN_OUT_t value)        {         GPIO_PinWrite(pin, value, &GPIO2_Resources);  };
static void      GPIO2_PinToggle(GPIO_PIN_t pin)                             {         GPIO_PinToggle(pin, &GPIO2_Resources);        };

DRIVER_GPIO DRIVER_GPIO2 = {
  GPIO2_PinConfig,
  GPIO2_PortRead,
  GPIO2_PortWrite,
  GPIO2_PinRead,
  GPIO2_PinWrite,
  GPIO2_PinToggle,
};
