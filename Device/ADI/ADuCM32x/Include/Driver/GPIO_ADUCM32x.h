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
 * Project: GPIO Driver Definitions for ADI ADuCM32x
 */

#ifndef GPIO_ADUCM32X_H_
#define GPIO_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum {
  GPIO_PIN_0    = 0,
  GPIO_PIN_1    = 1,
  GPIO_PIN_2    = 2,
  GPIO_PIN_3    = 3,
  GPIO_PIN_4    = 4,
  GPIO_PIN_5    = 5,
  GPIO_PIN_6    = 6,
  GPIO_PIN_7    = 7,
} GPIO_PIN_t;

typedef enum {
  GPIO_PIN_FUNC_0 = 0,
  GPIO_PIN_FUNC_1 = 1,
  GPIO_PIN_FUNC_2 = 2,
  GPIO_PIN_FUNC_3 = 3
} GPIO_PIN_FUNC_t;

typedef enum {
  GPIO_PIN_OUT_LOW  = 0,
  GPIO_PIN_OUT_HIGH = 1,
} GPIO_PIN_OUT_t;

typedef enum {
  GPIO_PULL_DISABLE = 0,
  GPIO_PULL_ENABLE  = 1,
} GPIO_PULL_t;

/**
 * Pin Mode
 */
typedef enum {
  GPIO_MODE_ANALOG  = 0x00,  //!< Analog Input
  GPIO_MODE_INPUT   = 0x01,  //!< General-purpose Input
  GPIO_MODE_OUT_PP  = 0x02,  //!< General-purpose Output push-pull
  GPIO_MODE_OUT_OD  = 0x06,  //!< General-purpose Output open-drain
} GPIO_MODE_t;

typedef struct _GPIO_PIN_CFG {
  GPIO_PIN_FUNC_t func;
  GPIO_MODE_t     mode;
  GPIO_PULL_t     pull;
} GPIO_PIN_CFG_t;

/**
 * @fn          void PinConfig(GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   pin   Port pin number (0..7)
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.

 * @fn          uint8_t PortRead(void)
 * @brief       Read port pins
 * @return      port pin inputs

 * @fn          void PortWrite(uint8_t value)
 * @brief       Write port pins
 * @param[in]   value  Pin values

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

/**
 * @brief Access structure of the GPIO Driver.
 */
typedef struct Driver_GPIO {
  void      (*PinConfig)  (GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg);
  uint8_t   (*PortRead)   (void);
  void      (*PortWrite)  (uint8_t value);
  uint32_t  (*PinRead)    (GPIO_PIN_t pin);
  void      (*PinWrite)   (GPIO_PIN_t pin, GPIO_PIN_OUT_t value);
  void      (*PinToggle)  (GPIO_PIN_t pin);
} const Driver_GPIO_t;

#endif /* GPIO_ADUCM32X_H_ */
