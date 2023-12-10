/*
 * Copyright (C) 2019-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: RCC Driver Definitions for STMicroelectronics STM32F7xx
 */

#ifndef RCC_STM32F7XX_H_
#define RCC_STM32F7XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <asm/stm32f7xx.h>

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

#define RCC_PLL_NONE                    (0U)
#define RCC_PLL_ON                      (1U)
#define RCC_PLL_OFF                     (2U)

#define RCC_PLL_SRC_HSE                 RCC_PLLCFGR_PLLSRC_HSE
#define RCC_PLL_SRC_HSI                 RCC_PLLCFGR_PLLSRC_HSI

#define RCC_CLK_TYPE_SYSCLK             (1U << 0)
#define RCC_CLK_TYPE_HCLK               (1U << 1)
#define RCC_CLK_TYPE_PCLK1              (1U << 2)
#define RCC_CLK_TYPE_PCLK2              (1U << 3)

#define RCC_SYSCLK_SRC_HSI              RCC_CFGR_SW_HSI
#define RCC_SYSCLK_SRC_HSE              RCC_CFGR_SW_HSE
#define RCC_SYSCLK_SRC_PLLCLK           RCC_CFGR_SW_PLL

#define RCC_SYSCLK_DIV1                 RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2                 RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4                 RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8                 RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16                RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64                RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128               RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256               RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512               RCC_CFGR_HPRE_DIV512

#define RCC_HCLK_DIV1                   (0U)
#define RCC_HCLK_DIV2                   (4U)
#define RCC_HCLK_DIV4                   (5U)
#define RCC_HCLK_DIV8                   (6U)
#define RCC_HCLK_DIV16                  (7U)

#define FLASH_LATENCY_0                 FLASH_ACR_LATENCY_0WS
#define FLASH_LATENCY_1                 FLASH_ACR_LATENCY_1WS
#define FLASH_LATENCY_2                 FLASH_ACR_LATENCY_2WS
#define FLASH_LATENCY_3                 FLASH_ACR_LATENCY_3WS
#define FLASH_LATENCY_4                 FLASH_ACR_LATENCY_4WS
#define FLASH_LATENCY_5                 FLASH_ACR_LATENCY_5WS
#define FLASH_LATENCY_6                 FLASH_ACR_LATENCY_6WS
#define FLASH_LATENCY_7                 FLASH_ACR_LATENCY_7WS
#define FLASH_LATENCY_8                 FLASH_ACR_LATENCY_8WS
#define FLASH_LATENCY_9                 FLASH_ACR_LATENCY_9WS
#define FLASH_LATENCY_10                FLASH_ACR_LATENCY_10WS
#define FLASH_LATENCY_11                FLASH_ACR_LATENCY_11WS
#define FLASH_LATENCY_12                FLASH_ACR_LATENCY_12WS
#define FLASH_LATENCY_13                FLASH_ACR_LATENCY_13WS
#define FLASH_LATENCY_14                FLASH_ACR_LATENCY_14WS
#define FLASH_LATENCY_15                FLASH_ACR_LATENCY_15WS

#define RCC_PERIPH_BUS_MASK             ((uint64_t)(0xFFFFFFFF)    << 32U)
#define RCC_PERIPH_AHB1_MASK            ((uint64_t)(RCC_BASE+0x30) << 32U)
#define RCC_PERIPH_AHB2_MASK            ((uint64_t)(RCC_BASE+0x34) << 32U)
#define RCC_PERIPH_AHB3_MASK            ((uint64_t)(RCC_BASE+0x38) << 32U)
#define RCC_PERIPH_APB1_MASK            ((uint64_t)(RCC_BASE+0x40) << 32U)
#define RCC_PERIPH_APB2_MASK            ((uint64_t)(RCC_BASE+0x44) << 32U)

  /* RCC_PERIPH_AHB1 */
#define RCC_PERIPH_GPIOA                ((uint64_t)(RCC_AHB1ENR_GPIOAEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOB                ((uint64_t)(RCC_AHB1ENR_GPIOBEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOC                ((uint64_t)(RCC_AHB1ENR_GPIOCEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOD                ((uint64_t)(RCC_AHB1ENR_GPIODEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOE                ((uint64_t)(RCC_AHB1ENR_GPIOEEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOF                ((uint64_t)(RCC_AHB1ENR_GPIOFEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOG                ((uint64_t)(RCC_AHB1ENR_GPIOGEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOH                ((uint64_t)(RCC_AHB1ENR_GPIOHEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOI                ((uint64_t)(RCC_AHB1ENR_GPIOIEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOJ                ((uint64_t)(RCC_AHB1ENR_GPIOJEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_GPIOK                ((uint64_t)(RCC_AHB1ENR_GPIOKEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_CRC                  ((uint64_t)(RCC_AHB1ENR_CRCEN       | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_BKPSRAM              ((uint64_t)(RCC_AHB1ENR_BKPSRAMEN   | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_DTCMRAM              ((uint64_t)(RCC_AHB1ENR_DTCMRAMEN   | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_DMA1                 ((uint64_t)(RCC_AHB1ENR_DMA1EN      | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_DMA2                 ((uint64_t)(RCC_AHB1ENR_DMA2EN      | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_DMA2D                ((uint64_t)(RCC_AHB1ENR_DMA2DEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_ETHMAC               ((uint64_t)(RCC_AHB1ENR_ETHMACEN    | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_ETHMACTX             ((uint64_t)(RCC_AHB1ENR_ETHMACTXEN  | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_ETHMACRX             ((uint64_t)(RCC_AHB1ENR_ETHMACRXEN  | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_ETHMACPTP            ((uint64_t)(RCC_AHB1ENR_ETHMACPTPEN | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_OTGHS                ((uint64_t)(RCC_AHB1ENR_OTGHSEN     | RCC_PERIPH_AHB1_MASK))
#define RCC_PERIPH_OTGHSULPI            ((uint64_t)(RCC_AHB1ENR_OTGHSULPIEN | RCC_PERIPH_AHB1_MASK))

  /* RCC_PERIPH_AHB2 */
#define RCC_PERIPH_DCMI                 ((uint64_t)(RCC_AHB2ENR_DCMIEN      | RCC_PERIPH_AHB2_MASK))
#if defined(STM32F767xx) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F779xx)
#define RCC_PERIPH_JPEG                 ((uint64_t)(RCC_AHB2ENR_JPEGEN      | RCC_PERIPH_AHB2_MASK))
#endif
#if defined(STM32F750xx) || defined(STM32F756xx) || defined(STM32F777xx) || \
    defined(STM32F779xx)
#define RCC_PERIPH_CRYP                 ((uint64_t)(RCC_AHB2ENR_CRYPEN      | RCC_PERIPH_AHB2_MASK))
#define RCC_PERIPH_HASH                 ((uint64_t)(RCC_AHB2ENR_HASHEN      | RCC_PERIPH_AHB2_MASK))
#endif
#define RCC_PERIPH_RNG                  ((uint64_t)(RCC_AHB2ENR_RNGEN       | RCC_PERIPH_AHB2_MASK))
#define RCC_PERIPH_OTGFS                ((uint64_t)(RCC_AHB2ENR_OTGFSEN     | RCC_PERIPH_AHB2_MASK))

  /* RCC_PERIPH_AHB3 */
#define RCC_PERIPH_FMC                  ((uint64_t)(RCC_AHB3ENR_FMCEN       | RCC_PERIPH_AHB3_MASK))
#define RCC_PERIPH_QSPI                 ((uint64_t)(RCC_AHB3ENR_QSPIEN      | RCC_PERIPH_AHB3_MASK))

  /* RCC_PERIPH_APB1 */
#define RCC_PERIPH_TIM2                 ((uint64_t)(RCC_APB1ENR_TIM2EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM3                 ((uint64_t)(RCC_APB1ENR_TIM3EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM4                 ((uint64_t)(RCC_APB1ENR_TIM4EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM5                 ((uint64_t)(RCC_APB1ENR_TIM5EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM6                 ((uint64_t)(RCC_APB1ENR_TIM6EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM7                 ((uint64_t)(RCC_APB1ENR_TIM7EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM12                ((uint64_t)(RCC_APB1ENR_TIM12EN     | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM13                ((uint64_t)(RCC_APB1ENR_TIM13EN     | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_TIM14                ((uint64_t)(RCC_APB1ENR_TIM14EN     | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_LPTIM1               ((uint64_t)(RCC_APB1ENR_LPTIM1EN    | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_RTC                  ((uint64_t)(RCC_APB1ENR_RTCEN       | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_WWDG                 ((uint64_t)(RCC_APB1ENR_WWDGEN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_CAN3                 ((uint64_t)(RCC_APB1ENR_CAN3EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_SPI2                 ((uint64_t)(RCC_APB1ENR_SPI2EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_SPI3                 ((uint64_t)(RCC_APB1ENR_SPI3EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_SPDIFRX              ((uint64_t)(RCC_APB1ENR_SPDIFRXEN   | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_USART2               ((uint64_t)(RCC_APB1ENR_USART2EN    | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_USART3               ((uint64_t)(RCC_APB1ENR_USART3EN    | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_UART4                ((uint64_t)(RCC_APB1ENR_UART4EN     | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_UART5                ((uint64_t)(RCC_APB1ENR_UART5EN     | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_I2C1                 ((uint64_t)(RCC_APB1ENR_I2C1EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_I2C2                 ((uint64_t)(RCC_APB1ENR_I2C2EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_I2C3                 ((uint64_t)(RCC_APB1ENR_I2C3EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_I2C4                 ((uint64_t)(RCC_APB1ENR_I2C4EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_CAN1                 ((uint64_t)(RCC_APB1ENR_CAN1EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_CAN2                 ((uint64_t)(RCC_APB1ENR_CAN2EN      | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_CEC                  ((uint64_t)(RCC_APB1ENR_CECEN       | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_PWR                  ((uint64_t)(RCC_APB1ENR_PWREN       | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_DAC                  ((uint64_t)(RCC_APB1ENR_DACEN       | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_UART7                ((uint64_t)(RCC_APB1ENR_UART7EN     | RCC_PERIPH_APB1_MASK))
#define RCC_PERIPH_UART8                ((uint64_t)(RCC_APB1ENR_UART8EN     | RCC_PERIPH_APB1_MASK))

  /* RCC_PERIPH_APB2 */
#define RCC_PERIPH_TIM1                 ((uint64_t)(RCC_APB2ENR_TIM1EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_TIM8                 ((uint64_t)(RCC_APB2ENR_TIM8EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_USART1               ((uint64_t)(RCC_APB2ENR_USART1EN    | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_USART6               ((uint64_t)(RCC_APB2ENR_USART6EN    | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SDMMC2               ((uint64_t)(RCC_APB2ENR_SDMMC2EN    | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_ADC1                 ((uint64_t)(RCC_APB2ENR_ADC1EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_ADC2                 ((uint64_t)(RCC_APB2ENR_ADC2EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_ADC3                 ((uint64_t)(RCC_APB2ENR_ADC3EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SDMMC1               ((uint64_t)(RCC_APB2ENR_SDMMC1EN    | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SPI1                 ((uint64_t)(RCC_APB2ENR_SPI1EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SPI4                 ((uint64_t)(RCC_APB2ENR_SPI4EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SYSCFG               ((uint64_t)(RCC_APB2ENR_SYSCFGEN    | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_TIM9                 ((uint64_t)(RCC_APB2ENR_TIM9EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_TIM10                ((uint64_t)(RCC_APB2ENR_TIM10EN     | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_TIM11                ((uint64_t)(RCC_APB2ENR_TIM11EN     | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SPI5                 ((uint64_t)(RCC_APB2ENR_SPI5EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SPI6                 ((uint64_t)(RCC_APB2ENR_SPI6EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SAI1                 ((uint64_t)(RCC_APB2ENR_SAI1EN      | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_SAI2                 ((uint64_t)(RCC_APB2ENR_SAI2EN      | RCC_PERIPH_APB2_MASK))
#if defined(STM32F746xx) || defined(STM32F750xx) || defined(STM32F756xx) || \
    defined(STM32F767xx) || defined(STM32F769xx) || defined(STM32F777xx) || \
    defined(STM32F779xx)
#define RCC_PERIPH_LTDC                 ((uint64_t)(RCC_APB2ENR_LTDCEN      | RCC_PERIPH_APB2_MASK))
#endif
#if defined(STM32F769xx) || defined(STM32F779xx)
#define RCC_PERIPH_DSI                  ((uint64_t)(RCC_APB2ENR_DSIEN       | RCC_PERIPH_APB2_MASK))
#endif
#define RCC_PERIPH_DFSDM1               ((uint64_t)(RCC_APB2ENR_DFSDM1EN    | RCC_PERIPH_APB2_MASK))
#define RCC_PERIPH_MDIO                 ((uint64_t)(RCC_APB2ENR_MDIOEN      | RCC_PERIPH_APB2_MASK))

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

typedef uint64_t RCC_Periph_t;

typedef struct RCC_PllInit_s {
  uint32_t state;
  uint32_t source;
  uint32_t m;
  uint32_t n;
  uint32_t p;
  uint32_t q;
  uint32_t r;
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

#endif /* RCC_STM32F7XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
