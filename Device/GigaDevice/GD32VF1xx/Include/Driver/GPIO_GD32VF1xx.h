/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: GPIO Driver Definitions for GigaDevice GD32VF1xx
 */

#ifndef GPIO_GD32VF1XX_H_
#define GPIO_GD32VF1XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum GPIO_Pin {
  GPIO_PIN_0              = 0,
  GPIO_PIN_1              = 1,
  GPIO_PIN_2              = 2,
  GPIO_PIN_3              = 3,
  GPIO_PIN_4              = 4,
  GPIO_PIN_5              = 5,
  GPIO_PIN_6              = 6,
  GPIO_PIN_7              = 7,
  GPIO_PIN_8              = 8,
  GPIO_PIN_9              = 9,
  GPIO_PIN_10             = 10,
  GPIO_PIN_11             = 11,
  GPIO_PIN_12             = 12,
  GPIO_PIN_13             = 13,
  GPIO_PIN_14             = 14,
  GPIO_PIN_15             = 15,
  GPIO_PinReserved        = 0x7FFFFFFF
} GPIO_Pin_t;

typedef enum GPIO_PinFunc {
  GPIO_PIN_FUNC_0         = 0,
  GPIO_PIN_FUNC_1         = 1,
  GPIO_PIN_FUNC_2         = 2,
  GPIO_PIN_FUNC_3         = 3,
  GPIO_PIN_FUNC_Reserved  = 0x7FFFFFFF
} GPIO_PinFunc_t;

typedef enum GPIO_PinOut {
  GPIO_PIN_OUT_LOW        = 0,
  GPIO_PIN_OUT_HIGH       = 1,
  GPIO_PIN_OUT_Reserved   = 0x7FFFFFFF
} GPIO_PinOut_t;

typedef enum GPIO_PinPull {
  GPIO_PULL_DISABLE       = 0,
  GPIO_PULL_ENABLE        = 1,
  GPIO_PULL_Reserved      = 0x7FFFFFFF
} GPIO_PinPull_t;

/**
 * Pin Mode
 */
typedef enum GPIO_PinMode {
  GPIO_MODE_ANALOG        = 0x00,  //!< Analog Input
  GPIO_MODE_INPUT         = 0x01,  //!< General-purpose Input
  GPIO_MODE_OUT_PP        = 0x02,  //!< General-purpose Output push-pull
  GPIO_MODE_OUT_OD        = 0x06,  //!< General-purpose Output open-drain
  GPIO_MODE_Reserved      = 0x7FFFFFFF
} GPIO_PinMode_t;

typedef struct GPIO_PinCfg {
  GPIO_PinFunc_t  func;
  GPIO_PinMode_t  mode;
  GPIO_PinPull_t  pull;
} GPIO_PinCfg_t;

typedef enum GPIO_PortClk {
  GPIO_PORT_CLK_DISABLE,
  GPIO_PORT_CLK_ENABLE,
} GPIO_PortClk_t;

/**
 * @fn          void PortClock(GPIO_PortClk_t state)
 * @brief       Port Clock Control
 * @param[in]   state   GPIO_PORT_CLK_DISABLE - to disable
 *                      GPIO_PORT_CLK_ENABLE  - to enable

 * @fn          GPIO_PortClk_t GetPortClockState(void)
 * @brief       Get GPIO port clock state
 * @return      GPIO_PORT_CLK_DISABLE - disabled
 *              GPIO_PORT_CLK_ENABLE  - enabled

 * @fn          void PinConfig(GPIO_Pin_t pin, const GPIO_PinCfg_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   pin   Port pin number (0..15)
 * @param[in]   cfg   Pointer to a GPIO_PinCfg_t structure that contains the
 *                    configuration information for the specified pin.

 * @fn          uint16_t PortRead(void)
 * @brief       Read port pins
 * @return      port pin inputs

 * @fn          void PortWrite(uint16_t value)
 * @brief       Write port pins
 * @param[in]   value  Pin values

 * @fn          uint32_t PinRead(GPIO_Pin_t pin)
 * @brief       Read port pin
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)

 * @fn          void PinWrite(GPIO_Pin_t pin, GPIO_PinOut_t value)
 * @brief       Write port pin
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (0 or 1)

 * @fn          void PinToggle(GPIO_Pin_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   pin   Port pin number
 */

/**
 * @brief Access structure of the GPIO Driver.
 */
typedef struct Driver_GPIO {
  void            (*PortClock)        (GPIO_PortClk_t state);
  GPIO_PortClk_t  (*GetPortClockState)(void);
  void            (*PinConfig)        (GPIO_Pin_t pin, const GPIO_PinCfg_t *cfg);
  uint16_t        (*PortRead)         (void);
  void            (*PortWrite)        (uint16_t value);
  uint32_t        (*PinRead)          (GPIO_Pin_t pin);
  void            (*PinWrite)         (GPIO_Pin_t pin, GPIO_PinOut_t value);
  void            (*PinToggle)        (GPIO_Pin_t pin);
} const Driver_GPIO_t;

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern Driver_GPIO_t Driver_GPIOA;
extern Driver_GPIO_t Driver_GPIOB;
extern Driver_GPIO_t Driver_GPIOC;
extern Driver_GPIO_t Driver_GPIOD;
extern Driver_GPIO_t Driver_GPIOE;

#endif /* GPIO_GD32VF1XX_H_ */
