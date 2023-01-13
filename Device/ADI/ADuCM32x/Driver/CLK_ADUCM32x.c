/*
 * Copyright (C) 2017-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Clock Driver for ADI ADuCM32x
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/CLK_ADUCM32x.h>

#include <asm/aducm32x.h>
#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define PLL_CLK_VALUE               80000000UL

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief   Returns Undivided System Clock Frequency (UCLK)
 */
static uint32_t GetFreqUCLK(void)
{
  uint32_t uClk;

  switch (MMR_CLKCTL->CLKCON0 & CLKCON0_CLKMUX_Msk) {
    case CLKCON0_CLKMUX_HFOSC:
      uClk = HF_CLK_VALUE;
      break;
    case CLKCON0_CLKMUX_SPLL:
      uClk = PLL_CLK_VALUE;
      break;
    case CLKCON0_CLKMUX_EXTCLK:
      uClk = XT_CLK_VALUE;
      break;
    default:
      uClk = 0;
      break;
  }

  return uClk;
}

/**
 * @brief       Setup the clock system. Initialize the default clock
 *              source.
 */
static void CLK_ClkReset(void)
{
  uint32_t reg_val;

  /* Change the system clock to the internal 16 MHz oscillator */
  reg_val = MMR_CLKCTL->CLKCON0 & ~CLKCON0_CLKMUX_Msk;
  MMR_CLKCTL->CLKCON0 = (uint16_t)(reg_val | CLKCON0_CLKMUX_HFOSC);

  /* Wait 5 clock cicles */
  __NOP();__NOP();__NOP();__NOP();__NOP();

  if ((MMR_CLKCTL->CLKCON0 & CLKCON0_PLLMUX_Msk) != CLKCON0_PLLMUX_HFOSC) {
    /* Switch the input to the SPLL */
    MMR_CLKCTL->CLKSTAT0 = (CLKSTAT0_SPLLUNLOCK | CLKSTAT0_SPLLLOCK);
    reg_val = MMR_CLKCTL->CLKCON0 & ~CLKCON0_PLLMUX_Msk;
    MMR_CLKCTL->CLKCON0 = (uint16_t)(reg_val | CLKCON0_PLLMUX_HFOSC);

    /* Wait until the SPLL has locked */
    while((MMR_CLKCTL->CLKSTAT0 & CLKSTAT0_SPLLLOCK) == 0);
  }

  /* Change the system clock to the SPLL clock */
  reg_val = MMR_CLKCTL->CLKCON0 & ~CLKCON0_CLKMUX_Msk;
  MMR_CLKCTL->CLKCON0 = (uint16_t)(reg_val | CLKCON0_CLKMUX_SPLL);

  /* Wait 5 clock cicles */
  __NOP();__NOP();__NOP();__NOP();__NOP();
}

/**
 * @brief       Initializes the CPU clock according to the specified
 *              parameters in the cfg argument.
 * @param[in]   cfg   CLK_Cfg_t structure that contains the configuration
 *                    information for the clock system.
 */
static void CLK_ClkConfig(const CLK_Cfg_t *cfg)
{
  uint32_t reg_val;

  /* Change the system clock to the internal 16 MHz oscillator */
  reg_val = MMR_CLKCTL->CLKCON0 & ~CLKCON0_CLKMUX_Msk;
  MMR_CLKCTL->CLKCON0 = (uint16_t)(reg_val | CLKCON0_CLKMUX_HFOSC);

  /* Wait 5 clock cicles */
  __NOP();__NOP();__NOP();__NOP();__NOP();

  if (cfg->SPLL_src == CLK_SPLL_SRC_HFXTAL) {
    /* Check that HFXTAL is stable */
    while((MMR_CLKCTL->CLKSTAT0 & CLKSTAT0_HFXTALOK) == 0);
  }

  if ((MMR_CLKCTL->CLKCON0 & CLKCON0_PLLMUX_Msk) != (cfg->SPLL_src << CLKCON0_PLLMUX_Pos)) {
    /* Switch the input to the SPLL */
    MMR_CLKCTL->CLKSTAT0 = (CLKSTAT0_SPLLUNLOCK | CLKSTAT0_SPLLLOCK);
    reg_val = MMR_CLKCTL->CLKCON0 & ~CLKCON0_PLLMUX_Msk;
    MMR_CLKCTL->CLKCON0 = (uint16_t)(reg_val | (cfg->SPLL_src << CLKCON0_PLLMUX_Pos));

    /* Wait until the SPLL has locked */
    while((MMR_CLKCTL->CLKSTAT0 & CLKSTAT0_SPLLLOCK) == 0);
  }

  /* Change the system clock to the SPLL clock */
  reg_val = MMR_CLKCTL->CLKCON0 & ~CLKCON0_CLKMUX_Msk;
  MMR_CLKCTL->CLKCON0 = (uint16_t)(reg_val | (cfg->UCLK_src << CLKCON0_CLKMUX_Pos));

  /* Wait 5 clock cicles */
  __NOP();__NOP();__NOP();__NOP();__NOP();

  /* Set HCLK divide */
  reg_val = MMR_CLKCTL->CLKCON1 & ~CLKCON1_CDHCLK_Msk;
  MMR_CLKCTL->CLKCON1 = (uint16_t)(reg_val | (cfg->HCLK_div << CLKCON1_CDHCLK_Pos));

  /* Set PCLK divide */
  reg_val = MMR_CLKCTL->CLKCON1 & ~CLKCON1_CDPCLK_Msk;
  MMR_CLKCTL->CLKCON1 = (uint16_t)(reg_val | (cfg->PCLK_div << CLKCON1_CDPCLK_Pos));
}

/**
 * @brief       Gets Clock Frequency.
 * @param[in]   type  CLK_Freq_t.
 * @return      Returns clock frequency in Hz.
 */
static uint32_t CLK_GetFrequency(CLK_Freq_t type)
{
  uint32_t clk;

  clk = GetFreqUCLK();

  switch (type) {
    case CLK_FREQ_HCLK:
      clk >>= (MMR_CLKCTL->CLKCON1 & CLKCON1_CDHCLK_Msk) >> CLKCON1_CDHCLK_Pos;
      break;
    case CLK_FREQ_PCLK:
      clk >>= (MMR_CLKCTL->CLKCON1 & CLKCON1_CDPCLK_Msk) >> CLKCON1_CDPCLK_Pos;
      break;
    case CLK_FREQ_ACLK:
      clk >>= 2U;
      break;
  }

  return (clk);
}

/**
 * @brief       Enables the peripheral specified by the periph argument.
 * @param[in]   periph  CLK_Periph_t.
 */
static void CLK_PeriphEnable(CLK_Periph_t periph)
{
  MMR_CLKCTL->CLKCON5 = (uint16_t)(MMR_CLKCTL->CLKCON5 & ~periph);
}

/**
 * @brief       Disables the peripheral specified by the periph argument.
 * @param[in]   periph  CLK_Periph_t.
 */
static void CLK_PeriphDisable(CLK_Periph_t periph)
{
  MMR_CLKCTL->CLKCON5 = (uint16_t)(MMR_CLKCTL->CLKCON5 | periph);
}

/**
 * @brief       Gets the current state of the peripheral specified
 *              by the periph argument.
 * @param[in]   periph  CLK_Periph_t.
 * @return      Returns state of the peripheral:
 *                0 - The peripheral is disabled;
 *                1 - The peripheral is enabled.
 */
static uint32_t CLK_GetStatePeriph(CLK_Periph_t periph)
{
  return ((uint32_t)((MMR_CLKCTL->CLKCON5 & periph) == 0U));
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

Driver_CLK_t Driver_CLK = {
  CLK_ClkReset,
  CLK_ClkConfig,
  CLK_GetFrequency,
  CLK_PeriphEnable,
  CLK_PeriphDisable,
  CLK_GetStatePeriph
};
