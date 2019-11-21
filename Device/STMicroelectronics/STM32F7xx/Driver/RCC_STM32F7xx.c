/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: RCC Driver for STMicroelectronics STM32F7xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>
#include "RCC_STM32F7xx.h"
#include "device_config.h"

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
       uint32_t  mask;
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

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

__STATIC_INLINE
void GetClockEnableReg(RCC_Periph_t periph, Reg_Mask_t *param)
{
  param->reg  = (uint32_t *)(uint32_t)(periph >> 32U);
  param->mask = (uint32_t)periph;
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
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSEON, CSSON, PLLON and PLLI2SON bits */
  RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON | RCC_CR_PLLI2SON |
               RCC_CR_PLLSAION);

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x24003010;

  /* Reset PLLI2SCFGR register */
  RCC->PLLI2SCFGR = 0x24003000;

  /* Reset PLLSAICFGR register */
  RCC->PLLSAICFGR = 0x24003000;

  /* Reset HSEBYP bit */
  RCC->CR &= ~RCC_CR_HSEBYP;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;
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

  }

  /* PLL Configuration */
  if (init->PLL.state != RCC_PLL_NONE) {
    if (init->PLL.state == RCC_PLL_ON) {
      RCC_PllInit_t pll = init->PLL;

      /* Disable the main PLL */
      RCC->CR &= ~RCC_CR_PLLON;
      while ((RCC->CR & RCC_CR_PLLRDY) != 0U);

      if (pll.m < 2U || pll.m > 63U) {
        pll.m = 16U;
      }

      if (pll.n < 50U || pll.n > 432U) {
        pll.n = 192U;
      }

      if (((pll.p & 0xFFFFFF1) != 0U) || pll.p > 8U) {
        pll.p = 2U;
      }

      if (pll.q < 2U || pll.q > 15U) {
        pll.q = 4U;
      }

      if (pll.r < 2U || pll.r > 7U) {
        pll.r = 2U;
      }

      /* Configure the main PLL */
      RCC->PLLCFGR = (pll.source | pll.m |
                     (pll.n << RCC_PLLCFGR_PLLN_Pos)                |
                     (((pll.p >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos) |
                     (pll.q << RCC_PLLCFGR_PLLQ_Pos)                |
                     (pll.r << RCC_PLLCFGR_PLLR_Pos)                 );

      /* Enable the main PLL */
      RCC->CR |= RCC_CR_PLLON;
      while ((RCC->CR & RCC_CR_PLLRDY) == 0U);
    }
    else {
      RCC->CR &= ~RCC_CR_PLLON;
      while ((RCC->CR & RCC_CR_PLLRDY) != 0U);
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
    RCC->CFGR = (tmp | init->AHB_clk_div);
  }

  /* SYSCLK Configuration */
  if (init->type & RCC_CLK_TYPE_SYSCLK) {
    tmp = (RCC->CFGR & ~RCC_CFGR_SW);
    RCC->CFGR = (tmp | init->sys_clk_src);
  }

  if (flash_latency < (FLASH->ACR & FLASH_ACR_LATENCY)) {
    tmp = (FLASH->ACR & ~FLASH_ACR_LATENCY);
    FLASH->ACR = (tmp | flash_latency);
  }

  /* PCLK1 Configuration */
  if (init->type & RCC_CLK_TYPE_PCLK1) {
    tmp = (RCC->CFGR & ~RCC_CFGR_PPRE1);
    RCC->CFGR = (tmp | (init->APB1_clk_div << RCC_CFGR_PPRE1_Pos));
  }

  /* PCLK2 Configuration */
  if (init->type & RCC_CLK_TYPE_PCLK2) {
    tmp = (RCC->CFGR & ~RCC_CFGR_PPRE2);
    RCC->CFGR = (tmp | (init->APB2_clk_div << RCC_CFGR_PPRE2_Pos));
  }

  if (flash_latency != 0U) {
    FLASH->ACR |= FLASH_ACR_PRFTEN;
  }
}

/**
 * @fn        uint32_t RCC_GetFreq(RCC_FREQ_t type)
 * @brief     Get Clock Frequency
 * @param[in] type  @ref RCC_FREQ_t
 * @return    Returns clock frequency in Hz
 */
uint32_t RCC_GetFreq(RCC_FREQ_t type)
{
  if (type == RCC_FREQ_HSI)
    return HSI_CLK;

  if (type == RCC_FREQ_HSE)
    return HSE_CLK;

  uint32_t sysclk;
  uint32_t rcc_cfgr = RCC->CFGR;

  /* Get SYSCLK Frequency ----------------------------------------------------*/
  switch (rcc_cfgr & RCC_CFGR_SWS) {
    case RCC_CFGR_SWS_HSI:  /* HSI used as system clock */
      sysclk = HSI_CLK;
      break;
    case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
      sysclk = HSE_CLK;
      break;
    case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
    {
      /*
       * PLL_VCO_OUT = (PLL_VCO_IN / PLLM) * PLLN
       * SYSCLK = PLL_VCO_OUT / PLLP
       */
      uint32_t pllm, plln, pllp, vco_in;
      uint32_t rcc_pllcfgr = RCC->PLLCFGR;

      pllm = (rcc_pllcfgr & RCC_PLLCFGR_PLLM);
      plln = (rcc_pllcfgr & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
      pllp = (((rcc_pllcfgr & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1U) * 2U;

      if (rcc_pllcfgr & RCC_PLLCFGR_PLLSRC)
        vco_in = HSE_CLK;
      else
        vco_in = HSI_CLK;

      sysclk = vco_in / pllm * plln /pllp;
      break;
    }
    default: /* HSI used as system clock */
      sysclk = HSI_CLK;
      break;
  }

  if (type == RCC_FREQ_SYSCLK)
    return sysclk;

  /* Compute HCLK clock frequency --------------------------------------------*/
  uint32_t hclk = (sysclk >> AHBPrescTable[(rcc_cfgr & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos]);

  if (type == RCC_FREQ_AHB)
    return hclk;

  /* Compute PCLK clock frequency --------------------------------------------*/
  if (type == RCC_FREQ_APB1)
    return (hclk >> APBPrescTable[(rcc_cfgr & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]);

  return (hclk >> APBPrescTable[(rcc_cfgr & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]);
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
  uint64_t periph_mask = periph & RCC_PERIPH_BUS_MASK;

  if (periph_mask == RCC_PERIPH_APB1_MASK) {
    clk = RCC_GetFreq(RCC_FREQ_APB1);
    if (((rcc_cfgr & RCC_CFGR_PPRE1_Msk) != RCC_CFGR_PPRE1_DIV1) &&
        ((periph == RCC_PERIPH_TIM2) || (periph == RCC_PERIPH_TIM3) || (periph == RCC_PERIPH_TIM4) ||
         (periph == RCC_PERIPH_TIM5) || (periph == RCC_PERIPH_TIM6) || (periph == RCC_PERIPH_TIM7) ||
         (periph == RCC_PERIPH_TIM12) || (periph == RCC_PERIPH_TIM13) || (periph == RCC_PERIPH_TIM14)))
    {
      clk <<= 1U;
    }
  }
  else if (periph_mask == RCC_PERIPH_APB2_MASK) {
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
  Reg_Mask_t tmp;

  GetClockEnableReg(periph, &tmp);

  tmp.reg -= 8U;

  *tmp.reg |= tmp.mask;
  __NOP();__NOP();__NOP();__NOP();
  *tmp.reg &= ~tmp.mask;
}

/* ----------------------------- End of file ---------------------------------*/
