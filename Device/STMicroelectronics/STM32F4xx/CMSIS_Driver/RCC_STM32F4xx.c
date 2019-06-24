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
 * Project: RCC Driver for STMicroelectronics STM32F4xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "RCC_STM32F4xx.h"
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
  else if (((periph & RCC_PERIPH_AHB1_MASK) == RCC_PERIPH_AHB1_MASK)) {
    param->reg = &RCC->AHB1ENR;
    param->mask = (uint32_t)periph & ~RCC_PERIPH_AHB1_MASK;
  }
  else if (((periph & RCC_PERIPH_AHB2_MASK) == RCC_PERIPH_AHB2_MASK)) {
    param->reg = &RCC->AHB2ENR;
    param->mask = (uint32_t)periph & ~RCC_PERIPH_AHB2_MASK;
  }
  else {
    param->reg = &RCC->AHB3ENR;
    param->mask = (uint32_t)periph & ~RCC_PERIPH_AHB3_MASK;
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn      void RCC_ClkReset(void)
 * @brief   Setup the microcontroller system. Initialize the default HSI clock
 *          source and the PLL configuration is reset.
 */
void RCC_ClkReset(void)
{
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC->CR |= (uint32_t)(RCC_CR_HSION | RCC_CR_HSITRIM_4);

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSEON, CSSON, PLLON and PLLI2SON bits */
  RCC->CR &= ~(uint32_t)(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON| RCC_CR_PLLI2SON);

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x24003010;

  /* Reset PLLI2SCFGR register */
  RCC->PLLI2SCFGR = 0x20003000;

  /* Reset HSEBYP bit */
  RCC->CR &= ~(uint32_t)RCC_CR_HSEBYP;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;
}

void RCC_OscInit(RCC_OscInit_t *init)
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
      /* Disable the main PLL */
      RCC->CR &= ~RCC_CR_PLLON;
      while ((RCC->CR & RCC_CR_PLLRDY) != 0U);

      /* Configure the main PLL */
      RCC->PLLCFGR = (init->PLL.source                                     |
                      init->PLL.m                                          |
                      (init->PLL.n << RCC_PLLCFGR_PLLN_Pos)                |
                      (((init->PLL.p >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos) |
                      (init->PLL.q << RCC_PLLCFGR_PLLQ_Pos));

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

void RCC_ClkInit(RCC_ClkInit_t *init, uint32_t flash_latency)
{
  uint32_t tmp;
  uint32_t chip_id;

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

  chip_id = (DBGMCU->IDCODE >> 16U);
  if (chip_id != 0x1000) {
    FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN);
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
    return RTE_HSI;

  if (type == RCC_FREQ_HSE)
    return RTE_HSE;

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
        vco_in = RTE_HSE;
      else
        vco_in = RTE_HSI;

      sysclk = vco_in / pllm * plln /pllp;
      break;
    }
    default: /* HSI used as system clock */
      sysclk = RTE_HSI;
      break;
  }

  if (type == RCC_FREQ_SYSCLK)
    return sysclk;

  /* Compute HCLK clock frequency --------------------------------------------*/
  uint32_t hclk = (sysclk >> AHBPrescTable[(rcc_cfgr & RCC_CFGR_HPRE) >> 4U]);

  if (type == RCC_FREQ_AHB)
    return hclk;

  /* Compute PCLK clock frequency --------------------------------------------*/
  if (type == RCC_FREQ_APB1)
    return (hclk >> APBPrescTable[(rcc_cfgr & RCC_CFGR_PPRE1) >> 10U]);

  return (hclk >> APBPrescTable[(rcc_cfgr & RCC_CFGR_PPRE2) >> 13U]);
}

/**
 * @fn        uint32_t RCC_GetPeriphFreq(RCC_Periph_t periph)
 * @brief     Get Periph Clock Frequency
 * @param[in] type  @ref RCC_Periph_t
 * @return    Returns Perith clock frequency in Hz
 */
uint32_t RCC_GetPeriphFreq(RCC_Periph_t periph)
{
  RCC_FREQ_t type;

  if (((periph & RCC_PERIPH_APB1_MASK) == RCC_PERIPH_APB1_MASK)) {
    type = RCC_FREQ_APB1;
  }
  else if (((periph & RCC_PERIPH_APB2_MASK) == RCC_PERIPH_APB2_MASK)) {
    type = RCC_FREQ_APB2;
  }
  else {
    type = RCC_FREQ_AHB;
  }

  return RCC_GetFreq(type);
}

/**
 * @fn          uint32_t RCC_I2SPLL_Config(uint32_t plln, uint32_t pllr)
 * @param[in]   plln
 * @param[in]   pllr
 * @return      Returns I2SPLL clock frequency in Hz
 */
uint32_t RCC_I2SPLL_Config(uint32_t plln, uint32_t pllr)
{
  if ((pllr < 2U) || (pllr > 7U) || (plln < 100U) || (plln > 432U))
    return 0U;

  /* Disable I2S PLL */
  if (RCC->CR & RCC_CR_PLLI2SRDY) {
    RCC->CR &= ~RCC_CR_PLLI2SON;
    while (RCC->CR & RCC_CR_PLLI2SRDY);
  }

  /* Set PLLI2SCFGR register */
  RCC->PLLI2SCFGR = ((pllr << RCC_PLLI2SCFGR_PLLI2SR_Pos) | (plln << RCC_PLLI2SCFGR_PLLI2SN_Pos));

  /* Enable I2S PLL */
  RCC->CR |= RCC_CR_PLLI2SON;
  while (!(RCC->CR & RCC_CR_PLLI2SRDY));

  return (plln * 1000000U / pllr);
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

  if (((periph & RCC_PERIPH_APB1_MASK) == RCC_PERIPH_APB1_MASK)) {
    reg = &RCC->APB1RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_APB1_MASK;
  }
  else if (((periph & RCC_PERIPH_APB2_MASK) == RCC_PERIPH_APB2_MASK)) {
    reg = &RCC->APB2RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_APB2_MASK;
  }
  else if (((periph & RCC_PERIPH_AHB1_MASK) == RCC_PERIPH_AHB1_MASK)) {
    reg = &RCC->AHB1RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_AHB1_MASK;
  }
  else if (((periph & RCC_PERIPH_AHB2_MASK) == RCC_PERIPH_AHB2_MASK)) {
    reg = &RCC->AHB2RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_AHB2_MASK;
  }
  else {
    reg = &RCC->AHB3RSTR;
    mask = (uint32_t)periph & ~RCC_PERIPH_AHB3_MASK;
  }

  *reg |= mask;
  __NOP();__NOP();__NOP();__NOP();
  *reg &= ~mask;
}

/* ----------------------------- End of file ---------------------------------*/
