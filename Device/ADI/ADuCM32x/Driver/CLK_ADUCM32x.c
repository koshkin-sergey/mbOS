/*
 * Copyright (C) 2017-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <aducm32x.h>

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* define the clock multiplexer input frequencies */
#define __HFOSC    16000000
#define __SPLL     80000000

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* Frequency of the external clock source connected to P1.0 */
static uint32_t SystemExtClock = 0;

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief   Returns Undivided System Clock Frequency (UCLK)
 */
static
uint32_t GetFreqUCLK(void)
{
  uint32_t uClk;

  switch (pADI_CLKCTL->CLKCON0 & CLKCON0_CLKMUX_MSK ) {
    case CLKCON0_CLKMUX_HFOSC:
      uClk = __HFOSC;
      break;
    case CLKCON0_CLKMUX_SPLL:
      uClk = __SPLL;
      break;
    case CLKCON0_CLKMUX_EXTCLK:
      uClk = SystemExtClock;
      break;
    default:
      uClk = 0;
      break;
  }

  return uClk;
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief   Changes the clock source for the 80 MHz SPLL from the internal
 *          16 MHz oscillator to the external HFXTAL.
 */
void CLK_SourceHFXTAL(void)
{
  /* Check that HFXTAL is stable */
  while((pADI_CLKCTL->CLKSTAT0 & CLKSTAT0_HFXTALOK) == 0);
  /* Change the system clock to the internal 16 MHz oscillator */
  pADI_CLKCTL->CLKCON0 &= ~CLKCON0_CLKMUX_MSK;

  /* Switch the input to the SPLL */
  pADI_CLKCTL->CLKSTAT0 = (CLKSTAT0_SPLLUNLOCK | CLKSTAT0_SPLLLOCK);
  pADI_CLKCTL->CLKCON0 |= CLKCON0_PLLMUX_HFXTAL;

  /* Wait until the SPLL has locked */
  while((pADI_CLKCTL->CLKSTAT0 & CLKSTAT0_SPLLLOCK) == 0);
  /* Change the system clock to the SPLL clock */
  pADI_CLKCTL->CLKCON0 |= CLKCON0_CLKMUX_SPLL;
}

/**
 * @brief     Get Core Clock Frequency (HCLK)
 * @return
 */
uint32_t CLK_GetFreqHCLK(void)
{
  return (GetFreqUCLK() >> (pADI_CLKCTL->CLKCON1 & CLKCON1_CDHCLK_MSK));
}

/**
 * @brief     Get Peripheral Clock Frequency (PCLK)
 * @return
 */
uint32_t CLK_GetFreqPCLK(void)
{
  return (GetFreqUCLK() >> (pADI_CLKCTL->CLKCON1 & CLKCON1_CDPCLK_MSK));
}

/**
 * @brief     Get D2D Clock Frequency (HCLK)
 * @return
 */
uint32_t CLK_GetFreqD2DCLK(void)
{
  return (GetFreqUCLK() >> (pADI_CLKCTL->CLKCON1 & CLKCON1_CDD2DCLK_MSK));
}


void CLK_PeriphGateControl(CLK_PERIPH clk, CLK_MODE mode)
{
  if (mode == CLOCK_ON)
    pADI_CLKCTL->CLKCON5 &= ~clk;
  else
    pADI_CLKCTL->CLKCON5 |= clk;
}

/* ----------------------------- End of file ---------------------------------*/
