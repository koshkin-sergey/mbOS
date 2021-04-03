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

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#include <stdint.h>

typedef enum {
  GPIO_PIN_0    = 0,
  GPIO_PIN_1    = 1,
  GPIO_PIN_2    = 2,
  GPIO_PIN_3    = 3,
  GPIO_PIN_4    = 4,
  GPIO_PIN_5    = 5,
  GPIO_PIN_6    = 6,
  GPIO_PIN_7    = 7,
  GPIO_PIN_Reserved = 0x7FFFFFFF,
} GPIO_PIN_t;

typedef enum {
  GPIO_PIN_OUT_LOW  = 0,
  GPIO_PIN_OUT_HIGH = 1,
} GPIO_PIN_OUT_t;

typedef enum {
  GPIO_PULL_UP      = 0,
  GPIO_PULL_DISABLE = 1,
} GPIO_PULL_t;

typedef enum {
  GPIO_STRENGTH_MEDIUM  = 0x00,
  GPIO_STRENGTH_LOW     = 0x02,
  GPIO_STRENGTH_HIGH    = 0x04,
} GPIO_STRENGTH_t;

typedef enum {
  GPIO_PIN_FUNC_0 = 0,
  GPIO_PIN_FUNC_1 = 1,
  GPIO_PIN_FUNC_2 = 2,
  GPIO_PIN_FUNC_3 = 3,
  GPIO_PIN_FUNC_Reserved = 0x7FFFFFFF,
} GPIO_PIN_FUNC_t;

/**
 * Pin Mode
 * PP = push-pull, OD = open-drain, AF = alternate function.
 */
typedef enum {
  GPIO_MODE_INPUT   = 0x0000,  //!< General-purpose Input
  GPIO_MODE_OUTPUT  = 0x0001,  //!< General-purpose Output push-pull
} GPIO_MODE_t;

typedef struct _GPIO_PIN_CFG {
  GPIO_MODE_t          mode;
  GPIO_PULL_t     pull_mode;
  GPIO_STRENGTH_t  strength;
} GPIO_PIN_CFG_t;

/**
 * @fn          void PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   pin   Port pin number (0..7)
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.

 * @fn          void AFConfig(GPIO_PIN_t pin, GPIO_PIN_FUNC_t af_num)
 * @brief       Configure alternate functions
 * @param[in]   pin     Port pin number (0..7)
 * @param[in]   af_num  Alternate function number

 * @fn          uint8_t PortRead(void)
 * @brief       Read port pins
 * @return      port  pin inputs

 * @fn          void PortWrite(uint8_t value)
 * @brief       Write port pins
 * @param[in]   value Pin values

 * @fn          uint32_t PinRead(GPIO_PIN_t pin)
 * @brief       Read port pin
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)

 * @fn          void PinWrite(GPIO_PIN_t pin, GPIO_PIN_OUT_t value)
 * @brief       Write port pin
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (0 or 1)

 * @fn          void PinToggle(GPIO_PIN_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   pin   Port pin number
 */

typedef struct _DRIVER_GPIO {
  void      (*PinConfig)  (GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg);
  void      (*AFConfig)   (GPIO_PIN_t pin, GPIO_PIN_FUNC_t af_num);
  uint8_t   (*PortRead)   (void);
  void      (*PortWrite)  (uint8_t value);
  uint32_t  (*PinRead)    (GPIO_PIN_t pin);
  void      (*PinWrite)   (GPIO_PIN_t pin, GPIO_PIN_OUT_t value);
  void      (*PinToggle)  (GPIO_PIN_t pin);
} const DRIVER_GPIO;

extern DRIVER_GPIO DRIVER_GPIO0;
extern DRIVER_GPIO DRIVER_GPIO1;
extern DRIVER_GPIO DRIVER_GPIO2;

#endif /* DRIVER_GPIO_H_ */
