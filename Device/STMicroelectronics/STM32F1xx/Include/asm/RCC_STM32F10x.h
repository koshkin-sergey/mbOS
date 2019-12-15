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
 * Project: RCC Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef RCC_STM32F10X_H_
#define RCC_STM32F10X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define RCC_OSC_TYPE_NONE               (0U)
#define RCC_OSC_TYPE_HSE                (1U << 0)
#define RCC_OSC_TYPE_HSI                (1U << 1)
#define RCC_OSC_TYPE_LSE                (1U << 2)
#define RCC_OSC_TYPE_LSI                (1U << 3)

#define RCC_HSE_OFF                     (0U)
#define RCC_HSE_ON                      (1U)
#define RCC_HSE_BYPASS                  (2U)

#define RCC_LSI_OFF                     (0U)
#define RCC_LSI_ON                      (1U)

#define RCC_PLL_NONE                    (0U)
#define RCC_PLL_ON                      (1U)
#define RCC_PLL_OFF                     (2U)

#if defined(STM32F100xB) || defined(STM32F100xE)

/* PLL entry clock source */
#define RCC_PLL_SRC_HSI_Div2            (0UL << 16U)
#define RCC_PLL_SRC_HSE                 (1UL << 16U)
#define RCC_PLL_SRC_HSE_Div2            ((3UL << 16U) | 1UL)
#define RCC_PLL_SRC_HSE_Div3            ((1UL << 16U) | 2UL)
#define RCC_PLL_SRC_HSE_Div4            ((3UL << 16U) | 3UL)
#define RCC_PLL_SRC_HSE_Div5            ((1UL << 16U) | 4UL)
#define RCC_PLL_SRC_HSE_Div6            ((3UL << 16U) | 5UL)
#define RCC_PLL_SRC_HSE_Div7            ((1UL << 16U) | 6UL)
#define RCC_PLL_SRC_HSE_Div8            ((3UL << 16U) | 7UL)
#define RCC_PLL_SRC_HSE_Div9            ((1UL << 16U) | 8UL)
#define RCC_PLL_SRC_HSE_Div10           ((3UL << 16U) | 9UL)
#define RCC_PLL_SRC_HSE_Div11           ((1UL << 16U) | 10UL)
#define RCC_PLL_SRC_HSE_Div12           ((3UL << 16U) | 11UL)
#define RCC_PLL_SRC_HSE_Div13           ((1UL << 16U) | 12UL)
#define RCC_PLL_SRC_HSE_Div14           ((3UL << 16U) | 13UL)
#define RCC_PLL_SRC_HSE_Div15           ((1UL << 16U) | 14UL)
#define RCC_PLL_SRC_HSE_Div16           ((3UL << 16U) | 15UL)
/* PLL multiplication factor */
#define RCC_PLL_MUL_2                   (0UL << 18U)
#define RCC_PLL_MUL_3                   (1UL << 18U)
#define RCC_PLL_MUL_4                   (2UL << 18U)
#define RCC_PLL_MUL_5                   (3UL << 18U)
#define RCC_PLL_MUL_6                   (4UL << 18U)
#define RCC_PLL_MUL_7                   (5UL << 18U)
#define RCC_PLL_MUL_8                   (6UL << 18U)
#define RCC_PLL_MUL_9                   (7UL << 18U)
#define RCC_PLL_MUL_10                  (8UL << 18U)
#define RCC_PLL_MUL_11                  (9UL << 18U)
#define RCC_PLL_MUL_12                  (10UL << 18U)
#define RCC_PLL_MUL_13                  (11UL << 18U)
#define RCC_PLL_MUL_14                  (12UL << 18U)
#define RCC_PLL_MUL_15                  (13UL << 18U)
#define RCC_PLL_MUL_16                  (14UL << 18U)

#elif defined(STM32F105xC) || defined(STM32F107xC)
/* TODO Дописать определения источника тактирования */
/* PLL multiplication factor */
#define RCC_PLL_MUL_4                   (2UL << 18U)
#define RCC_PLL_MUL_5                   (3UL << 18U)
#define RCC_PLL_MUL_6                   (4UL << 18U)
#define RCC_PLL_MUL_7                   (5UL << 18U)
#define RCC_PLL_MUL_8                   (6UL << 18U)
#define RCC_PLL_MUL_9                   (7UL << 18U)
#define RCC_PLL_MUL_6_5                 (13UL << 18U)

#else

/* PLL entry clock source */
#define RCC_PLL_SRC_HSI_Div2            (0UL << 16U)
#define RCC_PLL_SRC_HSE                 (1UL << 16U)
#define RCC_PLL_SRC_HSE_Div2            (3UL << 16U)
/* PLL multiplication factor */
#define RCC_PLL_MUL_2                   (0UL << 18U)
#define RCC_PLL_MUL_3                   (1UL << 18U)
#define RCC_PLL_MUL_4                   (2UL << 18U)
#define RCC_PLL_MUL_5                   (3UL << 18U)
#define RCC_PLL_MUL_6                   (4UL << 18U)
#define RCC_PLL_MUL_7                   (5UL << 18U)
#define RCC_PLL_MUL_8                   (6UL << 18U)
#define RCC_PLL_MUL_9                   (7UL << 18U)
#define RCC_PLL_MUL_10                  (8UL << 18U)
#define RCC_PLL_MUL_11                  (9UL << 18U)
#define RCC_PLL_MUL_12                  (10UL << 18U)
#define RCC_PLL_MUL_13                  (11UL << 18U)
#define RCC_PLL_MUL_14                  (12UL << 18U)
#define RCC_PLL_MUL_15                  (13UL << 18U)
#define RCC_PLL_MUL_16                  (14UL << 18U)

#endif

#define RCC_CLK_TYPE_SYSCLK             (1U << 0)
#define RCC_CLK_TYPE_HCLK               (1U << 1)
#define RCC_CLK_TYPE_PCLK1              (1U << 2)
#define RCC_CLK_TYPE_PCLK2              (1U << 3)

#define RCC_SYSCLK_SRC_HSI              (0UL << 0U)
#define RCC_SYSCLK_SRC_HSE              (1UL << 0U)
#define RCC_SYSCLK_SRC_PLLCLK           (2UL << 0U)

#define RCC_SYSCLK_DIV1                 (0UL << 4U)
#define RCC_SYSCLK_DIV2                 (8UL << 4U)
#define RCC_SYSCLK_DIV4                 (9UL << 4U)
#define RCC_SYSCLK_DIV8                 (10UL << 4U)
#define RCC_SYSCLK_DIV16                (11UL << 4U)
#define RCC_SYSCLK_DIV64                (12UL << 4U)
#define RCC_SYSCLK_DIV128               (13UL << 4U)
#define RCC_SYSCLK_DIV256               (14UL << 4U)
#define RCC_SYSCLK_DIV512               (15UL << 4U)

#define RCC_HCLK_DIV1                   (0U)
#define RCC_HCLK_DIV2                   (4U)
#define RCC_HCLK_DIV4                   (5U)
#define RCC_HCLK_DIV8                   (6U)
#define RCC_HCLK_DIV16                  (7U)

#define FLASH_LATENCY_0                 (0UL)
#define FLASH_LATENCY_1                 (1UL)
#define FLASH_LATENCY_2                 (2UL)

#define RCC_PERIPH_AHB_MASK             (0xFFFE2AA8)
#define RCC_PERIPH_APB1_MASK            (0x81013600)
#define RCC_PERIPH_APB2_MASK            (0xFFC00002)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum {
  RCC_FREQ_HSI,
  RCC_FREQ_HSE,
  RCC_FREQ_SYSCLK,
  RCC_FREQ_AHB,
  RCC_FREQ_APB1,
  RCC_FREQ_APB2,
  RCC_FREQ_Reserved = 0x7FFFFFFF
} RCC_FREQ_t;

typedef enum {
  /* AHB */
#if defined(STM32F105xC) || defined(STM32F107xC)
  RCC_PERIPH_DMA1     = (int32_t)((1UL << 0U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_DMA2     = (int32_t)((1UL << 1U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_SRAM     = (int32_t)((1UL << 2U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_FLITF    = (int32_t)((1UL << 4U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_CRC      = (int32_t)((1UL << 6U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_OTGFS    = (int32_t)((1UL << 12U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_ETHMAC   = (int32_t)((1UL << 14U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_ETHMACTX = (int32_t)((1UL << 15U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_ETHMACRX = (int32_t)((1UL << 16U) | RCC_PERIPH_AHB_MASK),
#elif defined(STM32F100xB) || defined(STM32F100xE)
  RCC_PERIPH_DMA1     = (int32_t)((1UL << 0U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_DMA2     = (int32_t)((1UL << 1U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_SRAM     = (int32_t)((1UL << 2U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_FLITF    = (int32_t)((1UL << 4U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_CRC      = (int32_t)((1UL << 6U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_FSMC     = (int32_t)((1UL << 8U) | RCC_PERIPH_AHB_MASK),
#else
  RCC_PERIPH_DMA1     = (int32_t)((1UL << 0U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_DMA2     = (int32_t)((1UL << 1U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_SRAM     = (int32_t)((1UL << 2U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_FLITF    = (int32_t)((1UL << 4U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_CRC      = (int32_t)((1UL << 6U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_FSMC     = (int32_t)((1UL << 8U) | RCC_PERIPH_AHB_MASK),
  RCC_PERIPH_SDIO     = (int32_t)((1UL << 10U) | RCC_PERIPH_AHB_MASK),
#endif

  /* APB1 */
#if defined(STM32F105xC) || defined(STM32F107xC)
  RCC_PERIPH_TIM2     = (int32_t)((1UL << 0U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM3     = (int32_t)((1UL << 1U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM4     = (int32_t)((1UL << 2U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM5     = (int32_t)((1UL << 3U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM6     = (int32_t)((1UL << 4U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM7     = (int32_t)((1UL << 5U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_WWDG     = (int32_t)((1UL << 11U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_SPI2     = (int32_t)((1UL << 14U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_SPI3     = (int32_t)((1UL << 15U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART2   = (int32_t)((1UL << 17U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART3   = (int32_t)((1UL << 18U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_UART4    = (int32_t)((1UL << 19U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_UART5    = (int32_t)((1UL << 20U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_I2C1     = (int32_t)((1UL << 21U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_I2C2     = (int32_t)((1UL << 22U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_CAN1     = (int32_t)((1UL << 25U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_CAN2     = (int32_t)((1UL << 26U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_BKP      = (int32_t)((1UL << 27U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_PWR      = (int32_t)((1UL << 28U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_DAC      = (int32_t)((1UL << 29U) | RCC_PERIPH_APB1_MASK),
#elif defined(STM32F100xB) || defined(STM32F100xE)
  RCC_PERIPH_TIM2     = (int32_t)((1UL << 0U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM3     = (int32_t)((1UL << 1U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM4     = (int32_t)((1UL << 2U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM5     = (int32_t)((1UL << 3U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM6     = (int32_t)((1UL << 4U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM7     = (int32_t)((1UL << 5U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM12    = (int32_t)((1UL << 6U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM13    = (int32_t)((1UL << 7U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM14    = (int32_t)((1UL << 8U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_WWDG     = (int32_t)((1UL << 11U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_SPI2     = (int32_t)((1UL << 14U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_SPI3     = (int32_t)((1UL << 15U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART2   = (int32_t)((1UL << 17U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART3   = (int32_t)((1UL << 18U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_UART4    = (int32_t)((1UL << 19U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_UART5    = (int32_t)((1UL << 20U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_I2C1     = (int32_t)((1UL << 21U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_I2C2     = (int32_t)((1UL << 22U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_BKP      = (int32_t)((1UL << 27U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_PWR      = (int32_t)((1UL << 28U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_DAC      = (int32_t)((1UL << 29U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_CEC      = (int32_t)((1UL << 30U) | RCC_PERIPH_APB1_MASK),
#else
  RCC_PERIPH_TIM2     = (int32_t)((1UL << 0U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM3     = (int32_t)((1UL << 1U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM4     = (int32_t)((1UL << 2U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM5     = (int32_t)((1UL << 3U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM6     = (int32_t)((1UL << 4U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM7     = (int32_t)((1UL << 5U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM12    = (int32_t)((1UL << 6U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM13    = (int32_t)((1UL << 7U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_TIM14    = (int32_t)((1UL << 8U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_WWDG     = (int32_t)((1UL << 11U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_SPI2     = (int32_t)((1UL << 14U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_SPI3     = (int32_t)((1UL << 15U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART2   = (int32_t)((1UL << 17U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USART3   = (int32_t)((1UL << 18U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_UART4    = (int32_t)((1UL << 19U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_UART5    = (int32_t)((1UL << 20U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_I2C1     = (int32_t)((1UL << 21U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_I2C2     = (int32_t)((1UL << 22U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_USB      = (int32_t)((1UL << 23U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_CAN      = (int32_t)((1UL << 25U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_BKP      = (int32_t)((1UL << 27U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_PWR      = (int32_t)((1UL << 28U) | RCC_PERIPH_APB1_MASK),
  RCC_PERIPH_DAC      = (int32_t)((1UL << 29U) | RCC_PERIPH_APB1_MASK),
#endif

  /* APB2 */
#if defined(STM32F105xC) || defined(STM32F107xC)
  RCC_PERIPH_AFIO     = (int32_t)((1UL << 0U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOA    = (int32_t)((1UL << 2U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOB    = (int32_t)((1UL << 3U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOC    = (int32_t)((1UL << 4U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOD    = (int32_t)((1UL << 5U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOE    = (int32_t)((1UL << 6U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_ADC1     = (int32_t)((1UL << 9U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_ADC2     = (int32_t)((1UL << 10U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM1     = (int32_t)((1UL << 11U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_SPI1     = (int32_t)((1UL << 12U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_USART1   = (int32_t)((1UL << 14U) | RCC_PERIPH_APB2_MASK),
#elif defined(STM32F100xB) || defined(STM32F100xE)
  RCC_PERIPH_AFIO     = (int32_t)((1UL << 0U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOA    = (int32_t)((1UL << 2U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOB    = (int32_t)((1UL << 3U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOC    = (int32_t)((1UL << 4U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOD    = (int32_t)((1UL << 5U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOE    = (int32_t)((1UL << 6U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOF    = (int32_t)((1UL << 7U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOG    = (int32_t)((1UL << 8U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_ADC1     = (int32_t)((1UL << 9U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM1     = (int32_t)((1UL << 11U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_SPI1     = (int32_t)((1UL << 12U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_USART1   = (int32_t)((1UL << 14U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM15    = (int32_t)((1UL << 16U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM16    = (int32_t)((1UL << 17U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM17    = (int32_t)((1UL << 18U) | RCC_PERIPH_APB2_MASK),
#else
  RCC_PERIPH_AFIO     = (int32_t)((1UL << 0U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOA    = (int32_t)((1UL << 2U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOB    = (int32_t)((1UL << 3U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOC    = (int32_t)((1UL << 4U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOD    = (int32_t)((1UL << 5U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOE    = (int32_t)((1UL << 6U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOF    = (int32_t)((1UL << 7U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_GPIOG    = (int32_t)((1UL << 8U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_ADC1     = (int32_t)((1UL << 9U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_ADC2     = (int32_t)((1UL << 10U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM1     = (int32_t)((1UL << 11U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_SPI1     = (int32_t)((1UL << 12U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM8     = (int32_t)((1UL << 13U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_USART1   = (int32_t)((1UL << 14U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_ADC3     = (int32_t)((1UL << 15U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM9     = (int32_t)((1UL << 19U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM10    = (int32_t)((1UL << 20U) | RCC_PERIPH_APB2_MASK),
  RCC_PERIPH_TIM11    = (int32_t)((1UL << 21U) | RCC_PERIPH_APB2_MASK),
#endif
} RCC_Periph_t;

typedef struct RCC_PllInit_s {
  uint32_t state;
  uint32_t source;
  uint32_t mul;
} RCC_PllInit_t;

typedef struct RCC_OscInit_s {
  uint32_t OSC_Type;
  uint32_t HSE_State;
  uint32_t LSE_State;
  uint32_t HSI_State;
  uint32_t LSI_State;
  RCC_PllInit_t PLL;
} RCC_OscInit_t;

typedef struct RCC_ClkInit_s {
  uint32_t type;
  uint32_t sys_clk_src;
  uint32_t AHB_clk_div;
  uint32_t APB1_clk_div;
  uint32_t APB2_clk_div;
} RCC_ClkInit_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn      void RCC_ClkReset(void)
 * @brief   Setup the microcontroller system. Initialize the default HSI clock
 *          source and the PLL configuration is reset.
 * @note    This function should be used only after reset.
 */
void RCC_ClkReset(void);

/**
 * @fn          void RCC_OscInit(const RCC_OscInit_t *init)
 * @brief       Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInit_t.
 * @note        Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
 *              supported. User should request a transition to HSE Off first and then HSE On or HSE Bypass.
 * @param[in]   init  Pointer to an RCC_OscInitTypeDef structure that contains the configuration information
 *                    for the RCC Oscillators.
 */
void RCC_OscInit(const RCC_OscInit_t *init);

/**
 * @fn          void RCC_ClkInit(const RCC_ClkInit_t *init, uint32_t flash_latency)
 * @brief       Initializes the CPU, AHB and APB buses clocks according to the specified
 *              parameters in the init.
 * @param[in]   init  Pointer to an RCC_ClkInit_t structure that contains the configuration
 *                    information for the RCC peripheral.
 * @param[in]   flash_latency   FLASH Latency
 */
void RCC_ClkInit(const RCC_ClkInit_t *init, uint32_t flash_latency);

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

#endif /* RCC_STM32F10X_H_ */

/* ----------------------------- End of file ---------------------------------*/
