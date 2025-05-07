/*
 * Copyright (C) 2018 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: GPIO Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef GPIO_STM32F4XX_H_
#define GPIO_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef enum {
  GPIO_PORT_A,
  GPIO_PORT_B,
  GPIO_PORT_C,
#if defined(STM32F401xC) || defined(STM32F401xE) ||                                                 \
    defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F411xE) ||                                                                         \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  GPIO_PORT_D,
  GPIO_PORT_E,
#endif
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  GPIO_PORT_F,
  GPIO_PORT_G,
#endif
  GPIO_PORT_H,
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  GPIO_PORT_I,
#endif
#if defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  GPIO_PORT_J,
  GPIO_PORT_K,
#endif
  GPIO_PORT_Reserved = 0x7FFFFFFF,
} GPIO_PORT_t;

typedef enum {
  GPIO_PIN_0    = 0,
  GPIO_PIN_1    = 1,
  GPIO_PIN_2    = 2,
  GPIO_PIN_3    = 3,
  GPIO_PIN_4    = 4,
  GPIO_PIN_5    = 5,
  GPIO_PIN_6    = 6,
  GPIO_PIN_7    = 7,
  GPIO_PIN_8    = 8,
  GPIO_PIN_9    = 9,
  GPIO_PIN_10   = 10,
  GPIO_PIN_11   = 11,
  GPIO_PIN_12   = 12,
  GPIO_PIN_13   = 13,
  GPIO_PIN_14   = 14,
  GPIO_PIN_15   = 15,
  GPIO_PIN_Reserved = 0x7FFFFFFF,
} GPIO_PIN_t;

typedef enum {
  GPIO_PIN_OUT_LOW  = 0,
  GPIO_PIN_OUT_HIGH = 1,
} GPIO_PIN_OUT_t;

typedef enum {
  GPIO_PULL_DISABLE = 0,
  GPIO_PULL_UP      = 1,
  GPIO_PULL_DOWN    = 2,
} GPIO_PULL_t;

typedef enum {
  GPIO_SPEED_LOW        = 0,
  GPIO_SPEED_MEDIUM     = 1,
  GPIO_SPEED_HIGH       = 2,
  GPIO_SPEED_VERY_HIGH  = 3,
} GPIO_SPEED_t;

typedef enum {
  GPIO_PIN_FUNC_0 = 0,
  GPIO_PIN_FUNC_1 = 1,
  GPIO_PIN_FUNC_2 = 2,
  GPIO_PIN_FUNC_3 = 3,
  GPIO_PIN_FUNC_4 = 4,
  GPIO_PIN_FUNC_5 = 5,
  GPIO_PIN_FUNC_6 = 6,
  GPIO_PIN_FUNC_7 = 7,
  GPIO_PIN_FUNC_8 = 8,
  GPIO_PIN_FUNC_9 = 9,
  GPIO_PIN_FUNC_10 = 10,
  GPIO_PIN_FUNC_11 = 11,
  GPIO_PIN_FUNC_12 = 12,
  GPIO_PIN_FUNC_13 = 13,
  GPIO_PIN_FUNC_14 = 14,
  GPIO_PIN_FUNC_15 = 15,
  GPIO_PIN_FUNC_Reserved = 0x7FFFFFFF,
} GPIO_PIN_FUNC_t;

/**
 * Pin Mode
 * PP = push-pull, OD = open-drain, AF = alternate function.
 */
typedef enum {
  GPIO_MODE_INPUT   = 0x0000,  //!< General-purpose Input
  GPIO_MODE_ANALOG  = 0x0003,  //!< Analog Input
  GPIO_MODE_OUT_PP  = 0x0001,  //!< General-purpose Output push-pull
  GPIO_MODE_OUT_OD  = 0x0101,  //!< General-purpose Output open-drain
  GPIO_MODE_AF_PP   = 0x0002,  //!< Alternate function push-pull
  GPIO_MODE_AF_OD   = 0x0102,  //!< Alternate function open-drain
} GPIO_MODE_t;

typedef struct _GPIO_PIN_CFG {
  GPIO_MODE_t mode;
  GPIO_PULL_t pull_mode;
  GPIO_SPEED_t speed;
} GPIO_PIN_CFG_t;

typedef enum {
  GPIO_PORT_CLK_DISABLE,
  GPIO_PORT_CLK_ENABLE,
} GPIO_PORT_CLK_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn          void GPIO_PortClock(GPIO_PORT_t port, GPIO_PORT_CLK_t state)
 * @brief       Port Clock Control
 * @param[in]   port    GPIO port (A..F)
 * @param[in]   state   GPIO_PORT_CLK_DISABLE - to disable
 *                      GPIO_PORT_CLK_ENABLE  - to enable
 */
extern
void GPIO_PortClock(GPIO_PORT_t port, GPIO_PORT_CLK_t state);

/**
 * @fn          bool GPIO_GetPortClockState(GPIO_PORT_t port)
 * @brief       Get GPIO port clock state
 * @param[in]   port    GPIO port (A..F)
 * @return      false - disabled
 *              true  - enabled
 */
extern
bool GPIO_GetPortClockState(GPIO_PORT_t port);

/**
 * @fn          void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   port  GPIO port (A..F)
 * @param[in]   pin   Port pin number
 */
extern
void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin);

/**
 * @fn          void GPIO_PinWrite(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_OUT_t value)
 * @brief       Write port pin
 * @param[in]   port  GPIO port (A..F)
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (0 or 1)
 */
extern
void GPIO_PinWrite(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_OUT_t value);

/**
 * @fn          uint32_t GPIO_PinRead(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Read port pin
 * @param[in]   port  GPIO port (A..F)
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)
 */
extern
uint32_t GPIO_PinRead(GPIO_PORT_t port, GPIO_PIN_t pin);

/**
 * @fn          void GPIO_PortWrite(GPIO_PORT_t port, uint16_t value)
 * @brief       Write port pins
 * @param[in]   port  GPIO port (A..F)
 * @param[in]   value Pin values
 */
extern
void GPIO_PortWrite(GPIO_PORT_t port, uint16_t value);

/**
 * @fn          uint16_t GPIO_PortRead(GPIO_PORT_t port)
 * @brief       Read port pins
 * @param[in]   port  GPIO port (A..F)
 * @return      port  pin inputs
 */
extern
uint16_t GPIO_PortRead(GPIO_PORT_t port);

/**
 * @fn          void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   port  GPIO port (A..F)
 * @param[in]   pin   Port pin number (0..15)
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.
 */
extern
void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg);

/**
 * @fn          void GPIO_AFConfig(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_FUNC_t af_num)
 * @brief       Configure alternate functions
 * @param[in]   port    GPIO port (A..F)
 * @param[in]   pin     Port pin number (0..15)
 * @param[in]   af_num  Alternate function number
 */
extern
void GPIO_AFConfig(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_FUNC_t af_num);

#endif /* GPIO_STM32F4XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
