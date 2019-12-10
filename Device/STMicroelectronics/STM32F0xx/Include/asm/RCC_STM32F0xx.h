/*
 * Copyright (C) 2017-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#if 0
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
#define RCC_PERIPH_ADC        (RCC_APB2ENR_ID | RCC_APB2ENR_ADCEN)
#define RCC_PERIPH_TIM1       (RCC_APB2ENR_ID | RCC_APB2ENR_TIM1EN)
#define RCC_PERIPH_SPI1       (RCC_APB2ENR_ID | RCC_APB2ENR_SPI1EN)
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPH_TIM15      (RCC_APB2ENR_ID | RCC_APB2ENR_TIM15EN)
#endif
#define RCC_PERIPH_TIM16      (RCC_APB2ENR_ID | RCC_APB2ENR_TIM16EN)
#define RCC_PERIPH_TIM17      (RCC_APB2ENR_ID | RCC_APB2ENR_TIM17EN)
#define RCC_PERIPH_DBGMCU     (RCC_APB2ENR_ID | RCC_APB2ENR_DBGMCUEN)
#endif

#define RCC_PERIPH_AHB_MASK             (0xFE81FFA8)
#define RCC_PERIPH_APB1_MASK            (0x8501B6CC)
#define RCC_PERIPH_APB2_MASK            (0xFFB8A51E)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum {
  RCC_FREQ_HSI,
  RCC_FREQ_HSI14,
  RCC_FREQ_HSI48,
  RCC_FREQ_HSE,
  RCC_FREQ_SYSCLK,
  RCC_FREQ_AHB,
  RCC_FREQ_APB,
  RCC_FREQ_Reserved = 0x7FFFFFFF
} RCC_FREQ_t;

typedef enum {
  /* AHB */
  RCC_PERIPH_GPIOA = (int32_t)(RCC_AHBENR_GPIOAEN | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_GPIOB = (int32_t)(RCC_AHBENR_GPIOBEN | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_GPIOC = (int32_t)(RCC_AHBENR_GPIOCEN | RCC_PERIPH_AHB_MASK),
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
  RCC_PERIPH_GPIOD = (int32_t)(RCC_AHBENR_GPIODEN | RCC_PERIPH_AHB_MASK),
#endif
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
  RCC_PERIPH_GPIOE = (int32_t)(RCC_AHBENR_GPIOEEN | RCC_PERIPH_AHB_MASK),
#endif
  RCC_PERIPH_GPIOF = (int32_t)(RCC_AHBENR_GPIOFEN | RCC_PERIPH_AHB_MASK),

  /* APB1 */
#if defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
  RCC_PERIPH_USART2 = (int32_t)(RCC_APB1ENR_USART2EN | RCC_PERIPH_APB1_MASK),
#endif
#if defined(STM32F030xC) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
  RCC_PERIPH_USART3 = (int32_t)(RCC_APB1ENR_USART3EN | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART4 = (int32_t)(RCC_APB1ENR_USART4EN | RCC_PERIPH_APB1_MASK),
#endif
#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
  RCC_PERIPH_USART5 = (int32_t)(RCC_APB1ENR_USART5EN | RCC_PERIPH_APB1_MASK),
#endif

  /* APB2 */
  RCC_PERIPH_USART1 = (int32_t)(RCC_APB2ENR_USART1EN | RCC_PERIPH_APB2_MASK),
#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
  RCC_PERIPH_USART6 = (int32_t)(RCC_APB2ENR_USART6EN | RCC_PERIPH_APB2_MASK),
#endif
#if defined(STM32F091xC) || defined(STM32F098xx)
  RCC_PERIPH_USART7 = (int32_t)(RCC_APB2ENR_USART7EN | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_USART8 = (int32_t)(RCC_APB2ENR_USART8EN | RCC_PERIPH_APB2_MASK),
#endif
} RCC_Periph_t;

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
void RCC_ClkInit(void);

/**
 * @fn        uint32_t RCC_GetFreq(RCC_FREQ_t type)
 * @brief     Get Clock Frequency
 * @param[in] type  @ref RCC_FREQ_t
 * @return    Returns clock frequency in Hz
 */
uint32_t RCC_GetFreq(RCC_FREQ_t type);

/**
 * @fn        uint32_t RCC_GetPeriphFreq(RCC_Periph_t periph)
 * @brief     Get Periph Clock Frequency
 * @param[in] type  @ref RCC_Periph_t
 * @return    Returns Perith clock frequency in Hz
 */
uint32_t RCC_GetPeriphFreq(RCC_Periph_t periph);

/**
 * @fn          void RCC_EnablePeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
void RCC_EnablePeriph(RCC_Periph_t periph);

/**
 * @fn          void RCC_DisablePeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
void RCC_DisablePeriph(RCC_Periph_t periph);

/**
 * @fn          uint32_t RCC_GetStatePeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
uint32_t RCC_GetStatePeriph(RCC_Periph_t periph);

/**
 * @fn          void RCC_ResetPeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
void RCC_ResetPeriph(RCC_Periph_t periph);

#endif /* RCC_STM32F0XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
