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
 *  defines and macros
 ******************************************************************************/

/* GPIO return codes */
#define GPIO_DRIVER_OK                0                                         ///< Operation succeeded
#define GPIO_DRIVER_ERROR            -1                                         ///< Unspecified error

/* GPIO Pin Config Codes */
#define PIN_MODE_Pos                  0
#define PIN_MODE_Msk                  (3UL << PIN_MODE_Pos)
#define PIN_MODE_INPUT                (0UL << PIN_MODE_Pos)                     ///< General-purpose Input (default)
#define PIN_MODE_OUTPUT               (1UL << PIN_MODE_Pos)                     ///< General-purpose Output
#define PIN_MODE_ALT_FUNC             (2UL << PIN_MODE_Pos)                     ///< Alternate function
#define PIN_MODE_ANALOG               (3UL << PIN_MODE_Pos)                     ///< Analog Input/Output

#define PIN_OUTPUT_Pos                4
#define PIN_OUTPUT_Msk                (1UL << PIN_OUTPUT_Pos)
#define PIN_OUTPUT_PUSH_PULL          (0UL << PIN_OUTPUT_Pos)                   ///< Output push-pull (default)
#define PIN_OUTPUT_OPEN_DRAIN         (1UL << PIN_OUTPUT_Pos)                   ///< Output open-drain

#define PIN_OUTPUT_SPEED_Pos          8
#define PIN_OUTPUT_SPEED_Msk          (3UL << PIN_OUTPUT_SPEED_Pos)
#define PIN_OUTPUT_SPEED_LOW          (0UL << PIN_OUTPUT_SPEED_Pos)             ///< Max speed 2 MHz (default)
#define PIN_OUTPUT_SPEED_MEDIUM       (1UL << PIN_OUTPUT_SPEED_Pos)             ///< Max speed 10 MHz
#define PIN_OUTPUT_SPEED_HIGH         (2UL << PIN_OUTPUT_SPEED_Pos)             ///< Max speed 50 MHz

#define PIN_PULL_Pos                  12
#define PIN_PULL_Msk                  (3UL << PIN_PULL_Pos)
#define PIN_PULL_DISABLE              (0UL << PIN_PULL_Pos)                     ///< Pin no pull-up, pull-down (default)
#define PIN_PULL_UP                   (1UL << PIN_PULL_Pos)                     ///< Pin pull-up
#define PIN_PULL_DOWN                 (2UL << PIN_PULL_Pos)                     ///< Pin pull-down

#define PIN_OUTPUT_VALUE_Pos          16
#define PIN_OUTPUT_VALUE_Msk          (1UL << PIN_OUTPUT_VALUE_Pos)
#define PIN_OUTPUT_VALUE_LOW          (0UL << PIN_OUTPUT_VALUE_Pos)             ///< Pin output low (default)
#define PIN_OUTPUT_VALUE_HIGH         (1UL << PIN_OUTPUT_VALUE_Pos)             ///< Pin output high

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum GPIO_Pin {
  GPIO_PIN_0              = 0,                                                  ///< GPIO_PIN_0
  GPIO_PIN_1              = 1,                                                  ///< GPIO_PIN_1
  GPIO_PIN_2              = 2,                                                  ///< GPIO_PIN_2
  GPIO_PIN_3              = 3,                                                  ///< GPIO_PIN_3
  GPIO_PIN_4              = 4,                                                  ///< GPIO_PIN_4
  GPIO_PIN_5              = 5,                                                  ///< GPIO_PIN_5
  GPIO_PIN_6              = 6,                                                  ///< GPIO_PIN_6
  GPIO_PIN_7              = 7,                                                  ///< GPIO_PIN_7
  GPIO_PIN_8              = 8,                                                  ///< GPIO_PIN_8
  GPIO_PIN_9              = 9,                                                  ///< GPIO_PIN_9
  GPIO_PIN_10             = 10,                                                 ///< GPIO_PIN_10
  GPIO_PIN_11             = 11,                                                 ///< GPIO_PIN_11
  GPIO_PIN_12             = 12,                                                 ///< GPIO_PIN_12
  GPIO_PIN_13             = 13,                                                 ///< GPIO_PIN_13
  GPIO_PIN_14             = 14,                                                 ///< GPIO_PIN_14
  GPIO_PIN_15             = 15,                                                 ///< GPIO_PIN_15
  GPIO_PinReserved        = 0x7FFFFFFF                                          ///< GPIO_PinReserved
} GPIO_Pin_t;

/**
 * @fn          int32_t GPIO_Initialize(void)
 * @brief       Initialize GPIO Interface.
 * @return      execution_status

 * @fn          int32_t GPIO_Uninitialize(void)
 * @brief       De-initialize GPIO Interface.
 * @return      execution_status

 * @fn          int32_t GPIO_PinConfig(GPIO_Pin_t pin, uint32_t cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   pin   Port pin number
 * @param[in]   cfg   contains the configuration information for the
 *                    specified pin.

 * @fn          uint32_t GPIO_PortRead(void)
 * @brief       Read port pins
 * @return      port pin inputs

 * @fn          void GPIO_PortWrite(uint32_t value)
 * @brief       Write port pins
 * @param[in]   value  Pin values

 * @fn          uint32_t GPIO_PinRead(GPIO_Pin_t pin)
 * @brief       Read port pin
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)

 * @fn          void GPIO_PinWrite(GPIO_Pin_t pin, uint32_t value)
 * @brief       Write port pin
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (0 or 1)

 * @fn          void GPIO_PinToggle(GPIO_Pin_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   pin   Port pin number
 */

/**
 * @brief Access structure of the GPIO Driver.
 */
typedef struct Driver_GPIO {
  int32_t   (*Initialize)   (void);
  int32_t   (*Uninitialize) (void);
  int32_t   (*PinConfig)    (GPIO_Pin_t pin, uint32_t cfg);
  uint32_t  (*PortRead)     (void);
  void      (*PortWrite)    (uint32_t value);
  uint32_t  (*PinRead)      (GPIO_Pin_t pin);
  void      (*PinWrite)     (GPIO_Pin_t pin, uint32_t value);
  void      (*PinToggle)    (GPIO_Pin_t pin);
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
