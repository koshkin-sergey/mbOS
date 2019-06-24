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
 * Project: RCC Driver Definitions for STMicroelectronics STM32F0xx
 */

#ifndef RCC_STM32F0XX_H_
#define RCC_STM32F0XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

#include "stm32f0xx.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define RCC_AHBENR_ID     (0x00000000UL)
#define RCC_APB1ENR_ID    (0x00008000UL)
#define RCC_APB2ENR_ID    (0x80000000UL)
#define RCC_PERIPHEN_MSK  (0x80008000UL)

#define RCC_PERIPH_DMA        (RCC_AHBENR_ID | RCC_AHBENR_DMAEN)
#if defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_DMA2       (RCC_AHBENR_ID | RCC_AHBENR_DMA2EN)
#endif
#define RCC_PERIPH_SRAM       (RCC_AHBENR_ID | RCC_AHBENR_SRAMEN)
#define RCC_PERIPH_FLITF      (RCC_AHBENR_ID | RCC_AHBENR_FLITFEN)
#define RCC_PERIPH_CRC        (RCC_AHBENR_ID | RCC_AHBENR_CRCEN)
#define RCC_PERIPH_GPIOA      (RCC_AHBENR_ID | RCC_AHBENR_GPIOAEN)
#define RCC_PERIPH_GPIOB      (RCC_AHBENR_ID | RCC_AHBENR_GPIOBEN)
#define RCC_PERIPH_GPIOC      (RCC_AHBENR_ID | RCC_AHBENR_GPIOCEN)
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_GPIOD      (RCC_AHBENR_ID | RCC_AHBENR_GPIODEN)
#endif
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_GPIOE      (RCC_AHBENR_ID | RCC_AHBENR_GPIOEEN)
#endif
#define RCC_PERIPH_GPIOF      (RCC_AHBENR_ID | RCC_AHBENR_GPIOFEN)
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_TSC        (RCC_AHBENR_ID | RCC_AHBENR_TSCEN)
#endif
#if defined(STM32F031x6) || defined(STM32F038xx) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_TIM2       (RCC_APB1ENR_ID | RCC_APB1ENR_TIM2EN)
#endif
#define RCC_PERIPH_TIM3       (RCC_APB1ENR_ID | RCC_APB1ENR_TIM3EN)
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_TIM6       (RCC_APB1ENR_ID | RCC_APB1ENR_TIM6EN)
#endif
#if defined(STM32F030xC) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_TIM7       (RCC_APB1ENR_ID | RCC_APB1ENR_TIM7EN)
#endif
#define RCC_PERIPH_TIM14      (RCC_APB1ENR_ID | RCC_APB1ENR_TIM14EN)
#define RCC_PERIPH_WWDG       (RCC_APB1ENR_ID | RCC_APB1ENR_WWDGEN)
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_SPI2       (RCC_APB1ENR_ID | RCC_APB1ENR_SPI2EN)
#endif
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_USART2     (RCC_APB1ENR_ID | RCC_APB1ENR_USART2EN)
#endif
#if defined(STM32F030xC) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_USART3     (RCC_APB1ENR_ID | RCC_APB1ENR_USART3EN)
#define RCC_PERIPH_USART4     (RCC_APB1ENR_ID | RCC_APB1ENR_USART4EN)
#endif
#if defined(STM32F030xC) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_USART5     (RCC_APB1ENR_ID | RCC_APB1ENR_USART5EN)
#endif
#define RCC_PERIPH_I2C1       (RCC_APB1ENR_ID | RCC_APB1ENR_I2C1EN)
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_I2C2       (RCC_APB1ENR_ID | RCC_APB1ENR_I2C2EN)
#endif
#if defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F072xB) || defined(STM32F078xx)
#define RCC_PERIPH_USB        (RCC_APB1ENR_ID | RCC_APB1ENR_USBEN)
#endif
#if defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_CAN        (RCC_APB1ENR_ID | RCC_APB1ENR_CANEN)
#endif
#if defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_CRS        (RCC_APB1ENR_ID | RCC_APB1ENR_CRSEN)
#endif
#define RCC_PERIPH_PWR        (RCC_APB1ENR_ID | RCC_APB1ENR_PWREN)
#if defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_DAC        (RCC_APB1ENR_ID | RCC_APB1ENR_DACEN)
#endif
#if defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_CEC        (RCC_APB1ENR_ID | RCC_APB1ENR_CECEN)
#endif
#define RCC_PERIPH_SYSCFGCOMP (RCC_APB2ENR_ID | RCC_APB2ENR_SYSCFGCOMPEN)
#if defined(STM32F030xC) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_USART6     (RCC_APB2ENR_ID | RCC_APB2ENR_USART6EN)
#endif
#if defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_USART7     (RCC_APB2ENR_ID | RCC_APB2ENR_USART7EN)
#define RCC_PERIPH_USART8     (RCC_APB2ENR_ID | RCC_APB2ENR_USART8EN)
#endif
#define RCC_PERIPH_ADC        (RCC_APB2ENR_ID | RCC_APB2ENR_ADCEN)
#define RCC_PERIPH_TIM1       (RCC_APB2ENR_ID | RCC_APB2ENR_TIM1EN)
#define RCC_PERIPH_SPI1       (RCC_APB2ENR_ID | RCC_APB2ENR_SPI1EN)
#define RCC_PERIPH_USART1     (RCC_APB2ENR_ID | RCC_APB2ENR_USART1EN)
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_TIM15      (RCC_APB2ENR_ID | RCC_APB2ENR_TIM15EN)
#endif
#define RCC_PERIPH_TIM16      (RCC_APB2ENR_ID | RCC_APB2ENR_TIM16EN)
#define RCC_PERIPH_TIM17      (RCC_APB2ENR_ID | RCC_APB2ENR_TIM17EN)
#define RCC_PERIPH_DBGMCU     (RCC_APB2ENR_ID | RCC_APB2ENR_DBGMCUEN)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum {
  RCC_FREQ_HSI,
  RCC_FREQ_HSI14,
  RCC_FREQ_HSI48,
  RCC_FREQ_SYSCLK,
  RCC_FREQ_HCLK,
  RCC_FREQ_PCLK,
} RCC_FREQ_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn      void RCC_ClkInit(void)
 * @brief   Setup the microcontroller system. Initialize the default HSI clock
 *          source and the PLL configuration is reset.
 */
extern
void RCC_ClkInit(void);

/**
 * @fn        uint32_t RCC_GetFreq(RCC_FREQ_t type)
 * @brief     Get Clock Frequency
 * @param[in] type  @ref RCC_FREQ_t
 * @return    Returns clock frequency in Hz
 */
extern
uint32_t RCC_GetFreq(RCC_FREQ_t type);

#endif /* RCC_STM32F0XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
