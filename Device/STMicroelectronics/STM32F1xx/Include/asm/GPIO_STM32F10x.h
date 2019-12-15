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
 * Project: GPIO Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef GPIO_STM32F10X_H_
#define GPIO_STM32F10X_H_

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
  GPIO_PORT_A   = 0,
  GPIO_PORT_B   = 1,
  GPIO_PORT_C   = 2,
  GPIO_PORT_D   = 3,
#if defined(STM32F100xB) || defined(STM32F100xE) ||                         \
    defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
  GPIO_PORT_E   = 4,
#if defined(STM32F100xE) ||                         \
    defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xE) || defined(STM32F103xG)
  GPIO_PORT_F   = 5,
  GPIO_PORT_G   = 6,
#endif
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
  GPIO_SPEED_LOW        = 1,    /* Max speed 2 MHz */
  GPIO_SPEED_MEDIUM     = 2,    /* Max speed 10 MHz */
  GPIO_SPEED_HIGH       = 0,    /* Max speed 50 MHz */
} GPIO_SPEED_t;

/**
 * Pin Mode
 * PP = push-pull, OD = open-drain, AF = alternate function.
 */
typedef enum {
  GPIO_MODE_INPUT   = 0x04,     //!< General-purpose Input
  GPIO_MODE_ANALOG  = 0x00,     //!< Analog Input
  GPIO_MODE_OUT_PP  = 0x03,     //!< General-purpose Output push-pull
  GPIO_MODE_OUT_OD  = 0x07,     //!< General-purpose Output open-drain
  GPIO_MODE_AF_PP   = 0x0B,     //!< Alternate function push-pull
  GPIO_MODE_AF_OD   = 0x0F,     //!< Alternate function open-drain
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

/* Alternate function definition macro */
#define AFIO_FUNC_DEF(bit, mask, val, reg) ((bit) | (mask << 5) | (val << 8) | (reg << 12))

/// Alternate function I/O remap
typedef enum {
  /* AF remap and debug I/O config register */
  AFIO_SPI1_NO_REMAP         = AFIO_FUNC_DEF (0,  1, 0, 0),
  AFIO_SPI1_REMAP            = AFIO_FUNC_DEF (0,  1, 1, 0),
  AFIO_I2C1_NO_REMAP         = AFIO_FUNC_DEF (1,  1, 0, 0),
  AFIO_I2C1_REMAP            = AFIO_FUNC_DEF (1,  1, 1, 0),
  AFIO_USART1_NO_REMAP       = AFIO_FUNC_DEF (2,  1, 0, 0),
  AFIO_USART1_REMAP          = AFIO_FUNC_DEF (2,  1, 1, 0),
  AFIO_USART2_NO_REMAP       = AFIO_FUNC_DEF (3,  1, 0, 0),
  AFIO_USART2_REMAP          = AFIO_FUNC_DEF (3,  1, 1, 0),
  AFIO_USART3_NO_REMAP       = AFIO_FUNC_DEF (4,  3, 0, 0),
  AFIO_USART3_REMAP_PARTIAL  = AFIO_FUNC_DEF (4,  3, 1, 0),
  AFIO_USART3_REMAP_FULL     = AFIO_FUNC_DEF (4,  3, 3, 0),
  AFIO_TIM1_NO_REMAP         = AFIO_FUNC_DEF (6,  3, 0, 0),
  AFIO_TIM1_REMAP_PARTIAL    = AFIO_FUNC_DEF (6,  3, 1, 0),
  AFIO_TIM1_REMAP_FULL       = AFIO_FUNC_DEF (6,  3, 3, 0),
  AFIO_TIM2_NO_REMAP         = AFIO_FUNC_DEF (8,  3, 0, 0),
  AFIO_TIM2_REMAP_PARTIAL_1  = AFIO_FUNC_DEF (8,  3, 1, 0),
  AFIO_TIM2_REMAP_PARTIAL_2  = AFIO_FUNC_DEF (8,  3, 2, 0),
  AFIO_TIM2_REMAP_FULL       = AFIO_FUNC_DEF (8,  3, 3, 0),
  AFIO_TIM3_NO_REMAP         = AFIO_FUNC_DEF (10, 3, 0, 0),
  AFIO_TIM3_REMAP_PARTIAL    = AFIO_FUNC_DEF (10, 3, 2, 0),
  AFIO_TIM3_REMAP_FULL       = AFIO_FUNC_DEF (10, 3, 3, 0),
  AFIO_TIM4_NO_REMAP         = AFIO_FUNC_DEF (12, 1, 0, 0),
  AFIO_TIM4_REMAP            = AFIO_FUNC_DEF (12, 1, 1, 0),
  AFIO_CAN_PA11_PA12         = AFIO_FUNC_DEF (13, 3, 0, 0),
  AFIO_CAN_PB8_PB9           = AFIO_FUNC_DEF (13, 3, 2, 0),
  AFIO_CAN_PD0_PD1           = AFIO_FUNC_DEF (13, 3, 3, 0),
  AFIO_PD01_NO_REMAP         = AFIO_FUNC_DEF (15, 1, 0, 0),
  AFIO_PD01_REMAP            = AFIO_FUNC_DEF (15, 1, 1, 0),
  AFIO_TIM5CH4_NO_REMAP      = AFIO_FUNC_DEF (16, 1, 0, 0),
  AFIO_TIM5CH4_REMAP         = AFIO_FUNC_DEF (16, 1, 1, 0),
  AFIO_ADC1_ETRGINJ_NO_REMAP = AFIO_FUNC_DEF (17, 1, 0, 0),
  AFIO_ADC1_ETRGINJ_REMAP    = AFIO_FUNC_DEF (17, 1, 1, 0),
  AFIO_ADC1_ETRGREG_NO_REMAP = AFIO_FUNC_DEF (18, 1, 0, 0),
  AFIO_ADC1_ETRGREG_REMAP    = AFIO_FUNC_DEF (18, 1, 1, 0),
  AFIO_ADC2_ETRGINJ_NO_REMAP = AFIO_FUNC_DEF (19, 1, 0, 0),
  AFIO_ADC2_ETRGINJ_REMAP    = AFIO_FUNC_DEF (19, 1, 1, 0),
  AFIO_ADC2_ETRGREG_NO_REMAP = AFIO_FUNC_DEF (20, 1, 0, 0),
  AFIO_ADC2_ETRGREG_REMAP    = AFIO_FUNC_DEF (20, 1, 1, 0),
#if defined(STM32F105xC) || defined(STM32F107xC)
  AFIO_ETH_NO_REMAP          = AFIO_FUNC_DEF (21, 1, 0, 0),
  AFIO_ETH_REMAP             = AFIO_FUNC_DEF (21, 1, 1, 0),
  AFIO_CAN2_NO_REMAP         = AFIO_FUNC_DEF (22, 1, 0, 0),
  AFIO_CAN2_REMAP            = AFIO_FUNC_DEF (22, 1, 1, 0),
  AFIO_ETH_MII_SEL           = AFIO_FUNC_DEF (23, 1, 0, 0),
  AFIO_ETH_RMII_SEL          = AFIO_FUNC_DEF (23, 1, 1, 0),
#endif
  AFIO_SWJ_FULL              = AFIO_FUNC_DEF (24, 7, 0, 0),
  AFIO_SWJ_FULL_NO_NJTRST    = AFIO_FUNC_DEF (24, 7, 1, 0),
  AFIO_SWJ_JTAG_NO_SW        = AFIO_FUNC_DEF (24, 7, 2, 0),
  AFIO_SWJ_NO_JTAG_NO_SW     = AFIO_FUNC_DEF (24, 7, 4, 0),
#if defined(STM32F105xC) || defined(STM32F107xC)
  AFIO_SPI3_NO_REMAP         = AFIO_FUNC_DEF (28, 1, 0, 0),
  AFIO_SPI3_REMAP            = AFIO_FUNC_DEF (28, 1, 1, 0),
  AFIO_TIM2ITR_NO_REMAP      = AFIO_FUNC_DEF (29, 1, 0, 0),
  AFIO_TIM2ITR_REMAP         = AFIO_FUNC_DEF (29, 1, 1, 0),
  AFIO_PTP_PPS_NO_REMAP      = AFIO_FUNC_DEF (30, 1, 0, 0),
  AFIO_PTP_PPS_REMAP         = AFIO_FUNC_DEF (30, 1, 1, 0),
#endif

  /* AF remap and debug I/O config register 2 */
  AFIO_TIM15_NO_REMAP        = AFIO_FUNC_DEF (0,  1, 0, 1),
  AFIO_TIM15_REMAP           = AFIO_FUNC_DEF (0,  1, 1, 1),
  AFIO_TIM16_NO_REMAP        = AFIO_FUNC_DEF (1,  1, 0, 1),
  AFIO_TIM16_REMAP           = AFIO_FUNC_DEF (1,  1, 1, 1),
  AFIO_TIM17_NO_REMAP        = AFIO_FUNC_DEF (2,  1, 0, 1),
  AFIO_TIM17_REMAP           = AFIO_FUNC_DEF (2,  1, 1, 1),
  AFIO_CEC_NO_REMAP          = AFIO_FUNC_DEF (3,  1, 0, 1),
  AFIO_CEC_REMAP             = AFIO_FUNC_DEF (3,  1, 1, 1),
  AFIO_TIM1_DMA_NO_REMAP     = AFIO_FUNC_DEF (4,  1, 0, 1),
  AFIO_TIM1_DMA_REMAP        = AFIO_FUNC_DEF (4,  1, 1, 1),

  AFIO_TIM9_NO_REMAP         = AFIO_FUNC_DEF (5,  1, 0, 1),
  AFIO_TIM9_REMAP            = AFIO_FUNC_DEF (5,  1, 1, 1),
  AFIO_TIM10_NO_REMAP        = AFIO_FUNC_DEF (6,  1, 0, 1),
  AFIO_TIM10_REMAP           = AFIO_FUNC_DEF (6,  1, 1, 1),
  AFIO_TIM11_NO_REMAP        = AFIO_FUNC_DEF (7,  1, 0, 1),
  AFIO_TIM11_REMAP           = AFIO_FUNC_DEF (7,  1, 1, 1),
  AFIO_TIM13_NO_REMAP        = AFIO_FUNC_DEF (8,  1, 0, 1),
  AFIO_TIM13_REMAP           = AFIO_FUNC_DEF (8,  1, 0, 1),
  AFIO_TIM14_NO_REMAP        = AFIO_FUNC_DEF (9,  1, 0, 1),
  AFIO_TIM14_REMAP           = AFIO_FUNC_DEF (9,  1, 1, 1),
  AFIO_FSMC_NADV_NO_REMAP    = AFIO_FUNC_DEF (10, 1, 0, 1),
  AFIO_FSMC_NADV_REMAP       = AFIO_FUNC_DEF (10, 1, 1, 1),

  AFIO_TIM67_DAC_DMA_NO_REMAP = AFIO_FUNC_DEF(11, 1, 0, 1),
  AFIO_TIM67_DAC_DMA_REMAP   = AFIO_FUNC_DEF (11, 1, 1, 1),
  AFIO_TIM12_NO_REMAP        = AFIO_FUNC_DEF (12, 1, 0, 1),
  AFIO_TIM12_REMAP           = AFIO_FUNC_DEF (12, 1, 1, 1),
  AFIO_MISC_NO_REMAP         = AFIO_FUNC_DEF (13, 1, 0, 1),
  AFIO_MISC_REMAP            = AFIO_FUNC_DEF (13, 1, 1, 1),

  /* Reserved value */
  AFIO_UNAVAILABLE_REMAP     = AFIO_FUNC_DEF (0,  0, 0, 0)
} AFIO_REMAP;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn          void GPIO_PortClock(GPIO_PORT_t port, GPIO_PORT_CLK_t state)
 * @brief       Port Clock Control
 * @param[in]   port    GPIO port (A..G)
 * @param[in]   state   GPIO_PORT_CLK_DISABLE - to disable
 *                      GPIO_PORT_CLK_ENABLE  - to enable
 */
extern
void GPIO_PortClock(GPIO_PORT_t port, GPIO_PORT_CLK_t state);

/**
 * @fn          GPIO_PORT_CLK_t GPIO_GetPortClockState(GPIO_PORT_t port)
 * @brief       Get GPIO port clock state
 * @param[in]   port    GPIO port (A..G)
 * @return      GPIO_PORT_CLK_DISABLE - disabled
 *              GPIO_PORT_CLK_ENABLE  - enabled
 */
extern
GPIO_PORT_CLK_t GPIO_GetPortClockState(GPIO_PORT_t port);

/**
 * @fn          void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Toggle the output of the port pin
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 */
extern
void GPIO_PinToggle(GPIO_PORT_t port, GPIO_PIN_t pin);

/**
 * @fn          void GPIO_PinWrite(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_OUT_t value)
 * @brief       Write port pin
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 * @param[in]   value Port pin value (GPIO_PIN_OUT_LOW or GPIO_PIN_OUT_HIGH)
 */
extern
void GPIO_PinWrite(GPIO_PORT_t port, GPIO_PIN_t pin, GPIO_PIN_OUT_t value);

/**
 * @fn          uint32_t GPIO_PinRead(GPIO_PORT_t port, GPIO_PIN_t pin)
 * @brief       Read port pin
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 * @return      pin value (0 or 1)
 */
extern
uint32_t GPIO_PinRead(GPIO_PORT_t port, GPIO_PIN_t pin);

/**
 * @fn          void GPIO_PortWrite(GPIO_PORT_t port, uint16_t value)
 * @brief       Write port pins
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   value Pin values
 */
extern
void GPIO_PortWrite(GPIO_PORT_t port, uint16_t value);

/**
 * @fn          uint16_t GPIO_PortRead(GPIO_PORT_t port)
 * @brief       Read port pins
 * @param[in]   port  GPIO port (A..G)
 * @return      port  pin inputs
 */
extern
uint16_t GPIO_PortRead(GPIO_PORT_t port);

/**
 * @fn          void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg)
 * @brief       Configure Pin corresponding to specified parameters
 * @param[in]   port  GPIO port (A..G)
 * @param[in]   pin   Port pin number
 * @param[in]   cfg   Pointer to a GPIO_PIN_CFG_t structure that contains the
 *                    configuration information for the specified pin.
 */
extern
void GPIO_PinConfig(GPIO_PORT_t port, GPIO_PIN_t pin, const GPIO_PIN_CFG_t *cfg);

/**
 * @fn          void GPIO_AFConfig(AFIO_REMAP af_type)
 * @brief       Configure alternate functions
 * @param[in]   af_type  Alternate function remap type
 */
extern
void GPIO_AFConfig(AFIO_REMAP af_type);

#endif /* GPIO_STM32F10X_H_ */

/* ----------------------------- End of file ---------------------------------*/
