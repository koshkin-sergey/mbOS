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
 * Project: RCC Driver for STMicroelectronics STM32F0xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "RCC_STM32F0xx.h"

#include "RTE_Device.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static const
uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

static const
uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn      void RCC_ClkInit(void)
 * @brief   Setup the microcontroller system. Initialize the default HSI clock
 *          source and the PLL configuration is reset.
 */
void RCC_ClkInit(void)
{
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001U;

#if defined (STM32F051x8) || defined (STM32F058x8)
  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFB80CU;
#else
  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
  RCC->CFGR &= (uint32_t)0x08FFB80CU;
#endif /* STM32F051x8 or STM32F058x8 */

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFFU;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFFU;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFFU;

  /* Reset PREDIV[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0U;

#if defined (STM32F072xB) || defined (STM32F078xx)
  /* Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFCFE2CU;
#elif defined (STM32F071xB)
  /* Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFCEACU;
#elif defined (STM32F091xC) || defined (STM32F098xx)
  /* Reset USART3SW[1:0], USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFF0FEACU;
#elif defined (STM32F030x6) || defined (STM32F030x8) || defined (STM32F031x6) || defined (STM32F038xx) || defined (STM32F030xC)
  /* Reset USART1SW[1:0], I2C1SW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEECU;
#elif defined (STM32F051x8) || defined (STM32F058xx)
  /* Reset USART1SW[1:0], I2C1SW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEACU;
#elif defined (STM32F042x6) || defined (STM32F048xx)
  /* Reset USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFE2CU;
#elif defined (STM32F070x6) || defined (STM32F070xB)
  /* Reset USART1SW[1:0], I2C1SW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFE6CU;
  /* Set default USB clock to PLLCLK, since there is no HSI48 */
  RCC->CFGR3 |= (uint32_t)0x00000080U;
#else
 #warning "No target selected"
#endif

  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFEU;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000U;
}

/**
 * @fn        uint32_t RCC_GetFreq(RCC_FREQ_t type)
 * @brief     Get Clock Frequency
 * @param[in] type  @ref RCC_FREQ_t
 * @return    Returns clock frequency in Hz
 */
uint32_t RCC_GetFreq(RCC_FREQ_t type)
{
  switch (type) {
    case RCC_FREQ_HSI:
      return RTE_HSI;
    case RCC_FREQ_HSI14:
      return RTE_HSI14;
    case RCC_FREQ_HSI48:
      return RTE_HSI48;
  }

  uint32_t pllmull = 0, predivfactor = 0;
  uint32_t sysclk;
  uint32_t rcc_cfgr = RCC->CFGR;

  /* Get SYSCLK Frequency ----------------------------------------------------*/
  switch (rcc_cfgr & RCC_CFGR_SWS) {
    case RCC_CFGR_SWS_HSI:  /* HSI used as system clock */
      sysclk = RTE_HSI;
      break;
    case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
      sysclk = RTE_HSE;
      break;
#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx)
    case RCC_CFGR_SWS_HSI48:
      sysclk = RTE_HSI48;
      break;
#endif /* defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx) */
    case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor */
      pllmull = ((rcc_cfgr & RCC_CFGR_PLLMUL) >> 18) + 2;
      predivfactor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;

      switch (rcc_cfgr & RCC_CFGR_PLLSRC) {
        case RCC_CFGR_PLLSRC_HSE_PREDIV:
          /* HSE used as PLL clock source : SystemCoreClock = HSE/PREDIV * PLLMUL */
          sysclk = (RTE_HSE/predivfactor) * pllmull;
          break;
#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx)
        case RCC_CFGR_PLLSRC_HSI48_PREDIV:
          /* HSI48 used as PLL clock source : SystemCoreClock = HSI48/PREDIV * PLLMUL */
          sysclk = (RTE_HSI48/predivfactor) * pllmull;
          break;
#endif /* defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx) */
        case RCC_CFGR_PLLSRC_HSI_DIV2:
          /* HSI used as PLL clock source : SystemCoreClock = HSI/2 * PLLMUL */
          sysclk = (RTE_HSI >> 1) * pllmull;
          break;
#if defined(STM32F042x6) || defined(STM32F048xx)  || defined(STM32F070x6) || defined(STM32F078xx) || defined(STM32F071xB)  || defined(STM32F072xB) || defined(STM32F070xB) || defined(STM32F091xC) || defined(STM32F098xx)  || defined(STM32F030xC)
        case RCC_CFGR_PLLSRC_HSI_PREDIV:
          /* HSI used as PLL clock source : SystemCoreClock = HSI/PREDIV * PLLMUL */
          sysclk = (RTE_HSI/predivfactor) * pllmull;
          break;
#endif /* defined(STM32F042x6) || defined(STM32F048xx)  || defined(STM32F070x6) || defined(STM32F078xx) || defined(STM32F071xB)  || defined(STM32F072xB) || defined(STM32F070xB) || defined(STM32F091xC) || defined(STM32F098xx)  || defined(STM32F030xC) */
      }
      break;
    default: /* HSI used as system clock */
      sysclk = RTE_HSI;
      break;
  }

  if (type == RCC_FREQ_SYSCLK)
    return sysclk;

  /* Compute HCLK clock frequency --------------------------------------------*/
  uint32_t hclk = (sysclk >> AHBPrescTable[((rcc_cfgr & RCC_CFGR_HPRE) >> 4)]);

  if (type == RCC_FREQ_HCLK)
    return hclk;

  /* Compute PCLK clock frequency --------------------------------------------*/
  uint32_t pclk = (hclk >> APBPrescTable[((rcc_cfgr & RCC_CFGR_PPRE) >> 8)]);

  return pclk;
}

/* ----------------------------- End of file ---------------------------------*/
