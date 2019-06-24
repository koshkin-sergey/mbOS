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
 * Project: GPIO Driver Definitions for ADI ADuCM32x
 */

#ifndef GPIO_ADUCM320_H_
#define GPIO_ADUCM320_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef enum {
  GPIO_PORT_0   = 0,
  GPIO_PORT_1   = 1,
  GPIO_PORT_2   = 2,
  GPIO_PORT_3   = 3,
  GPIO_PORT_4   = 4,
  GPIO_PORT_5   = 5,
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
} GPIO_PIN_t;

typedef enum {
  GPIO_PIN_FUNC_0 = 0,
  GPIO_PIN_FUNC_1 = 1,
  GPIO_PIN_FUNC_2 = 2,
  GPIO_PIN_FUNC_3 = 3
} GPIO_PIN_FUNC_t;

typedef enum {
  GPIO_PIN_OUT_LOW  = 0,
  GPIO_PIN_OUT_HIGH  = 1,
} GPIO_PIN_OUT_t;

typedef enum {
  GPIO_PULL_DISABLE = 0,
  GPIO_PULL_ENABLE  = 1,
} GPIO_PULL_t;

/**
 * Pin Mode
 * PP = push-pull, OD = open-drain, AF = alternate function.
 */
typedef enum {
  GPIO_MODE_INPUT   = 0x01,  //!< General-purpose Input
  GPIO_MODE_ANALOG  = 0x00,  //!< Analog Input
  GPIO_MODE_OUT_PP  = 0x03,  //!< General-purpose Output push-pull
  GPIO_MODE_OUT_OD  = 0x07,  //!< General-purpose Output open-drain
} GPIO_MODE_t;

typedef struct _GPIO_PIN_CFG {
  GPIO_MODE_t mode;
  GPIO_PULL_t pull_mode;
} GPIO_PIN_CFG_t;

// Pin identifier
typedef struct _PIN_ID {
  GPIO_PORT_t     port;
  GPIO_PIN_t      pin;
  GPIO_PIN_FUNC_t func;
} GPIO_PIN_ID_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Write port pin
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   pin_num    Port pin number
 * @param[in]   val        Port pin value (0 or 1)
 */
extern
void GPIO_PinWrite(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, GPIO_PIN_OUT_t val);

/**
 * @brief       Toggle the output of the port pin
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   pin_num    Port pin number
 */
extern
void GPIO_PinToggle(GPIO_PORT_t port_num, GPIO_PIN_t pin_num);

/**
 * @brief       Read port pin
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   pin_num    Port pin number
 * @return      pin value (0 or 1)
 */
extern
uint8_t GPIO_PinRead(GPIO_PORT_t port_num, GPIO_PIN_t pin_num);

/**
 * @brief       Write port pins
 * @param[in]   port_num   GPIO number (0..5)
 * @param[in]   val        Pin values
 */
extern
void GPIO_PortWrite(GPIO_PORT_t port_num, uint8_t val);

/**
 * @brief       Read port pins
 * @param[in]   port_num   GPIO number (0..5)
 * @return      port pin inputs
 */
extern
uint8_t GPIO_PortRead(GPIO_PORT_t port_num);

/**
 * @fn          void GPIO_PinConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   port_num  GPIO port (0..5)
 * @param[in]   pin_num   Port pin number (0..7)
 * @param[in]   cfg       Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                        configuration information for the specified pin.
 */
extern
void GPIO_PinConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, const GPIO_PIN_CFG_t *cfg);

/**
 * @fn          void GPIO_AFConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, GPIO_PIN_FUNC_t af_num)
 * @brief       Configure alternate functions
 * @param[in]   port_num  GPIO port (0..5)
 * @param[in]   pin_num   Port pin number (0..7)
 * @param[in]   af_num  Alternate function number
 */
extern
void GPIO_AFConfig(GPIO_PORT_t port_num, GPIO_PIN_t pin_num, GPIO_PIN_FUNC_t af_num);

#endif /* GPIO_ADUCM320_H_ */

/* ----------------------------- End of file ---------------------------------*/
