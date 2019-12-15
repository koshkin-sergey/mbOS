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
 * Project: RCC Driver for STMicroelectronics STM32F1xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "RCC_STM32F10x.h"

#include "stm32f1xx.h"
#include "Config/RTE_Device.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct {
  __IO uint32_t *reg;
  uint32_t mask;
} Reg_Mask_t;

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

#if defined(STM32F105xC) || defined(STM32F107xC)
  static const
  uint8_t pllmul_tbl[16] = {0, 0, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 13, 0, 0};
  static const
  uint8_t pllmul2_tbl[16] = {0, 0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 0, 16, 20};
#elif defined(STM32F100xB) || defined(STM32F100xE)
  static const
  uint8_t pllmul_tbl[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 16};
#else
  static const
  uint8_t pllmul_tbl[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 16};
#endif

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void GetClockEnableReg(RCC_Periph_t periph, Reg_Mask_t *param)
{
  if (((periph & RCC_PERIPH_APB1_MASK) == RCC_PERIPH_APB1_MASK)) {
    param->reg = &RCC->APB1ENR;
    param->mask = (uint32_t)periph & ~RCC_PERIPH_APB1_MASK;
  }
  else if (((periph & RCC_PERIPH_APB2_MASK) == RCC_PERIPH_APB2_MASK)) {
    param->reg = &RCC->APB2ENR;
    param->mask = (uint32_t)periph & ~RCC_PERIPH_APB2_MASK;
  }
  else {
    param->reg = &RCC->AHBENR;
    param->mask = (uint32_t)periph & ~RCC_PERIPH_AHB_MASK;
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn      void RCC_ClkReset(void)
 * @brief   Setup the microcontroller system. Initialize the default HSI clock
 *          source and the PLL configuration is reset.
 * @note    This function should be used only after reset.
 */
void RCC_ClkReset(void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  RCC->CFGR &= ~(RCC_CFGR_SW | RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2 | RCC_CFGR_ADCPRE | RCC_CFGR_MCO);

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);

  /* Reset HSEBYP bit */
  RCC->CR &= ~(RCC_CR_HSEBYP);

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#if defined(STM32F105xC) || defined(STM32F107xC)
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= ~(RCC_CR_PLL2ON | RCC_CR_PLL3ON);

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#elif defined(STM32F100xB) || defined(STM32F100xE)
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#else
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#endif
}

/**
 * @fn          void RCC_OscInit(const RCC_OscInit_t *init)
 * @brief       Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInit_t.
 * @note        Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
 *              supported. User should request a transition to HSE Off first and then HSE On or HSE Bypass.
 * @param[in]   init  Pointer to an RCC_OscInitTypeDef structure that contains the configuration information
 *                    for the RCC Oscillators.
 */
void RCC_OscInit(const RCC_OscInit_t *init)
{
  /* HSE Configuration */
  if (init->OSC_Type & RCC_OSC_TYPE_HSE) {
    switch (init->HSE_State) {
      case RCC_HSE_BYPASS:
        RCC->CR |= RCC_CR_HSEBYP;
        /* no break */

      case RCC_HSE_ON:
        RCC->CR |= RCC_CR_HSEON;
        while ((RCC->CR & RCC_CR_HSERDY) == 0U);
        break;

      default:
        RCC->CR &= ~RCC_CR_HSEON;
        while ((RCC->CR & RCC_CR_HSERDY) != 0U);
        break;
    }
  }

  /* HSI Configuration */
  if (init->OSC_Type & RCC_OSC_TYPE_HSI) {

  }

  /* LSE Configuration */
  if (init->OSC_Type & RCC_OSC_TYPE_LSE) {

  }

  /* LSI Configuration */
  if (init->OSC_Type & RCC_OSC_TYPE_LSI) {
    switch (init->LSI_State) {
      case RCC_HSE_ON:
        RCC->CSR |= RCC_CSR_LSION;
        while ((RCC->CSR & RCC_CSR_LSIRDY) == 0U);
        break;

      case RCC_LSI_OFF:
      default:
        RCC->CSR &= ~RCC_CSR_LSION;
        while ((RCC->CSR & RCC_CSR_LSIRDY) != 0U);
        break;
    }
  }

  /* PLL Configuration */
  if (init->PLL.state != RCC_PLL_NONE) {
    /* Disable the main PLL */
    RCC->CR &= ~RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) != 0U);

    if (init->PLL.state == RCC_PLL_ON) {
      /* Configure the main PLL */
      RCC->CFGR = (init->PLL.source & (RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE)) | (init->PLL.mul & RCC_CFGR_PLLMULL);
#if defined(RCC_CFGR2_PREDIV1)
      RCC->CFGR2 = init->PLL.source & RCC_CFGR2_PREDIV1;
#endif
      /* Enable the main PLL */
      RCC->CR |= RCC_CR_PLLON;
      while ((RCC->CR & RCC_CR_PLLRDY) == 0U);
    }
  }
}

/**
 * @fn          void RCC_ClkInit(const RCC_ClkInit_t *init, uint32_t flash_latency)
 * @brief       Initializes the CPU, AHB and APB buses clocks according to the specified
 *              parameters in the init.
 * @param[in]   init  Pointer to an RCC_ClkInit_t structure that contains the configuration
 *                    information for the RCC peripheral.
 * @param[in]   flash_latency   FLASH Latency
 */
void RCC_ClkInit(const RCC_ClkInit_t *init, uint32_t flash_latency)
{
  uint32_t tmp;

  if (flash_latency > (FLASH->ACR & FLASH_ACR_LATENCY)) {
    tmp = (FLASH->ACR & ~FLASH_ACR_LATENCY);
    FLASH->ACR = (tmp | flash_latency);
  }

  /* HCLK Configuration */
  if (init->type & RCC_CLK_TYPE_HCLK) {
    tmp = (RCC->CFGR & ~RCC_CFGR_HPRE);
    RCC->CFGR = (tmp | (init->AHB_clk_div & RCC_CFGR_HPRE));
  }

  /* SYSCLK Configuration */
  if (init->type & RCC_CLK_TYPE_SYSCLK) {
    tmp = (RCC->CFGR & ~RCC_CFGR_SW);
    RCC->CFGR = (tmp | (init->sys_clk_src & RCC_CFGR_SW));
  }

  if (flash_latency < (FLASH->ACR & FLASH_ACR_LATENCY)) {
    tmp = (FLASH->ACR & ~FLASH_ACR_LATENCY);
    FLASH->ACR = (tmp | flash_latency);
  }

  /* PCLK1 Configuration */
  if (init->type & RCC_CLK_TYPE_PCLK1) {
    tmp = (RCC->CFGR & ~RCC_CFGR_PPRE1);
    RCC->CFGR = (tmp | (init->APB1_clk_div << 8U));
  }

  /* PCLK2 Configuration */
  if (init->type & RCC_CLK_TYPE_PCLK2) {
    tmp = (RCC->CFGR & ~RCC_CFGR_PPRE2);
    RCC->CFGR = (tmp | (init->APB2_clk_div << 11U));
  }

  /* Enable Prefetch buffer */
  FLASH->ACR |= FLASH_ACR_PRFTBE;
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
    case RCC_FREQ_HSE:
      return RTE_HSE;
  }

  uint32_t sysclk;
  uint32_t rcc_cfgr = RCC->CFGR;

  /* Get SYSCLK Frequency ----------------------------------------------------*/
  switch (rcc_cfgr & RCC_CFGR_SWS) {
    default: /* HSI used as system clock */
    case RCC_CFGR_SWS_HSI:  /* HSI used as system clock */
      sysclk = RTE_HSI;
      break;

    case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
      sysclk = RTE_HSE;
      break;

    case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
    {
      uint32_t pllm, prediv;

      pllm = pllmul_tbl[(rcc_cfgr & RCC_CFGR_PLLMULL_Msk) >> RCC_CFGR_PLLMULL_Pos];

      if ((rcc_cfgr & RCC_CFGR_PLLSRC) == 0U) {
        /* HSI used as PLL clock source : PLLCLK = HSI/2 * PLLMUL */
        sysclk = (RTE_HSI >> 1U) * pllm;
      }
      else {
#if defined(STM32F105xC) || defined(STM32F107xC)
        uint32_t rcc_cfgr2 = RCC->CFGR2;

        prediv = ((rcc_cfgr2 & RCC_CFGR2_PREDIV1_Msk) >> RCC_CFGR2_PREDIV1_Pos) +1U;

        if ((rcc_cfgr2 & RCC_CFGR2_PREDIV1SRC) == 0U) {
          /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
          sysclk = RTE_HSE * pllm / prediv;
        }
        else {
          /* PLL2 selected as Prediv1 source */
          /* PLLCLK = PLL2CLK / PREDIV1 * PLLMUL with PLL2CLK = HSE/PREDIV2 * PLL2MUL */
          uint32_t prediv2 = ((rcc_cfgr2 & RCC_CFGR2_PREDIV2) >> RCC_CFGR2_PREDIV2_Pos) + 1U;
          uint32_t pll2m = pllmul2_tbl[(rcc_cfgr2 & RCC_CFGR2_PLL2MUL) >> RCC_CFGR2_PLL2MUL_Pos];
          sysclk = (uint32_t)(((uint64_t)RTE_HSE * (uint64_t)pll2m * (uint64_t)pllm) / ((uint64_t)prediv2 * (uint64_t)prediv));
        }
#elif defined(STM32F100xB) || defined(STM32F100xE)
        /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
        prediv = ((RCC->CFGR2 & RCC_CFGR2_PREDIV1_Msk) >> RCC_CFGR2_PREDIV1_Pos) + 1U;
        sysclk = RTE_HSE * pllm / prediv;
#else
        /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
        prediv = ((rcc_cfgr & RCC_CFGR_PLLXTPRE_Msk) >> RCC_CFGR_PLLXTPRE_Pos) +1U;
        sysclk = RTE_HSE * pllm / prediv;
#endif
      }
      break;
    }
  }

  if (type == RCC_FREQ_SYSCLK)
    return sysclk;

  /* Compute HCLK clock frequency --------------------------------------------*/
  uint32_t hclk = (sysclk >> AHBPrescTable[(rcc_cfgr & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos]);

  if (type == RCC_FREQ_AHB)
    return hclk;

  /* Compute PCLK clock frequency --------------------------------------------*/
  if (type == RCC_FREQ_APB1)
    return (hclk >> APBPrescTable[(rcc_cfgr & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos]);

  return (hclk >> APBPrescTable[(rcc_cfgr & RCC_CFGR_PPRE2_Msk) >> RCC_CFGR_PPRE2_Pos]);
}

/**
 * @fn        uint32_t RCC_GetPeriphFreq(RCC_Periph_t periph)
 * @brief     Get Periph Clock Frequency
 * @param[in] type  @ref RCC_Periph_t
 * @return    Returns Periph clock frequency in Hz
 */
uint32_t RCC_GetPeriphFreq(RCC_Periph_t periph)
{
  uint32_t clk = 0U;
  uint32_t rcc_cfgr = RCC->CFGR;

  if (((periph & RCC_PERIPH_APB1_MASK) == RCC_PERIPH_APB1_MASK)) {
    clk = RCC_GetFreq(RCC_FREQ_APB1);
    if (((rcc_cfgr & RCC_CFGR_PPRE1_Msk) != RCC_CFGR_PPRE1_DIV1) &&
        ((periph == RCC_PERIPH_TIM2) || (periph == RCC_PERIPH_TIM3) || (periph == RCC_PERIPH_TIM4) ||
         (periph == RCC_PERIPH_TIM5) || (periph == RCC_PERIPH_TIM6) || (periph == RCC_PERIPH_TIM7) ||
         (periph == RCC_PERIPH_TIM12) || (periph == RCC_PERIPH_TIM13) || (periph == RCC_PERIPH_TIM14)))
    {
      clk <<= 1U;
    }
  }
  else if (((periph & RCC_PERIPH_APB2_MASK) == RCC_PERIPH_APB2_MASK)) {
    clk = RCC_GetFreq(RCC_FREQ_APB2);
    if (((rcc_cfgr & RCC_CFGR_PPRE2_Msk) != RCC_CFGR_PPRE2_DIV1) &&
        ((periph == RCC_PERIPH_TIM1) || (periph == RCC_PERIPH_TIM8) || (periph == RCC_PERIPH_TIM9) ||
         (periph == RCC_PERIPH_TIM10) || (periph == RCC_PERIPH_TIM11)))
    {
      clk <<= 1U;
    }
  }
  else {
    clk = RCC_GetFreq(RCC_FREQ_AHB);
  }

  return clk;
}

/**
 * @fn          void RCC_EnablePeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
void RCC_EnablePeriph(RCC_Periph_t periph)
{
  Reg_Mask_t tmp;

  GetClockEnableReg(periph, &tmp);

  *tmp.reg |= tmp.mask;
}

/**
 * @fn          void RCC_DisablePeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
void RCC_DisablePeriph(RCC_Periph_t periph)
{
  Reg_Mask_t tmp;

  GetClockEnableReg(periph, &tmp);

  *tmp.reg &= ~tmp.mask;
}

/**
 * @fn          uint32_t RCC_GetStatePeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
uint32_t RCC_GetStatePeriph(RCC_Periph_t periph)
{
  Reg_Mask_t tmp;

  GetClockEnableReg(periph, &tmp);

  return (uint32_t)(*tmp.reg & tmp.mask);
}

/**
 * @fn          void RCC_ResetPeriph(RCC_Periph_t periph)
 * @param[in]   periph
 */
void RCC_ResetPeriph(RCC_Periph_t periph)
{
  __IO uint32_t *reg;
  uint32_t mask;

#if !defined(STM32F105xC) && !defined(STM32F107xC)
  if ((periph & RCC_PERIPH_AHB_MASK) == RCC_PERIPH_AHB_MASK)
    return;
#endif

  if (((periph & RCC_PERIPH_APB1_MASK) == RCC_PERIPH_APB1_MASK)) {
    reg = &RCC->APB1RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_APB1_MASK;
  }
  else if (((periph & RCC_PERIPH_APB2_MASK) == RCC_PERIPH_APB2_MASK)) {
    reg = &RCC->APB2RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_APB2_MASK;
  }
#if defined(STM32F105xC) || defined(STM32F107xC)
  else if ((periph & RCC_PERIPH_AHB_MASK) == RCC_PERIPH_AHB_MASK) {
    reg = &RCC->AHBRSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_AHB_MASK;
  }
#endif

  *reg |= mask;
  __NOP();__NOP();__NOP();__NOP();
  *reg &= ~mask;
}

/* ----------------------------- End of file ---------------------------------*/
