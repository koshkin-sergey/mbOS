/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
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
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/ADSU_KRECHET1.h>
#include <asm/krechet1.h>
#include <device_config.h>

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

static void ADSU_ClkReset(void);
static void ADSU_OscConfig(ADSU_Osc_t osc, ADSU_OscCfg_t cfg);
static void ADSU_ClkConfig(const ADSU_ClkCfg_t *cfg);
static uint32_t ADSU_GetFrequency(ADSU_Freq_t type);
static void ADSU_PeriphEnable(ADSU_Periph_t periph);
static void ADSU_PeriphDisable(ADSU_Periph_t periph);
static uint32_t ADSU_GetStatePeriph(ADSU_Periph_t periph);
static void ADSU_PeriphReset(ADSU_Periph_t periph);

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void SetFlashAccess(uint32_t delay)
{
  if (delay > FMCU_Access_Delay_Msk) {
    delay = FMCU_Access_Delay_Msk;
  }

  ADSU_PeriphEnable(ADSU_Periph_FMCU);

  __set_CpuReg(CPU_PRW_REG, PRW_FMCU);
  __set_PeriphReg(FMCU_ACCESS_REG, delay);

  ADSU_PeriphDisable(ADSU_Periph_FMCU);
}

static void ADSU_ClkReset(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_CLKCON_REG,  ADSU_ClkCon_EnRCOsc);
  __set_PeriphReg(ADSU_CLKCFG_REG,  0U);
  __set_PeriphReg(ADSU_GATE_REG,    0U);
  __set_PeriphReg(ADSU_WAKECFG_REG, 0U);
  __set_PeriphReg(ADSU_MAXLOAD_REG, 0U);
}

static void ADSU_OscConfig(ADSU_Osc_t osc, ADSU_OscCfg_t cfg)
{
  uint32_t reg_val;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  reg_val = __get_PeriphReg(ADSU_CLKCON_REG);

  switch (osc) {
    case ADSU_OSC_RC:
      if (cfg == ADSU_OSC_ENABLE) {
        reg_val |= ADSU_ClkCon_EnRCOsc;
      }
      else {
        reg_val &= ~ADSU_ClkCon_EnRCOsc;
      }
      break;

    case ADSU_OSC_HRC:
      if (cfg == ADSU_OSC_ENABLE) {
        reg_val |= ADSU_ClkCon_EnHRCOsc;
      }
      else {
        reg_val &= ~ADSU_ClkCon_EnHRCOsc;
      }
      break;

    case ADSU_OSC_XT:
      if (cfg == ADSU_OSC_ENABLE) {
        reg_val |= ADSU_ClkCon_EnXTOsc;
      }
      else {
        reg_val &= ~ADSU_ClkCon_EnXTOsc;
      }
      break;

    default:
      break;
  }

  __set_PeriphReg(ADSU_CLKCON_REG, reg_val);
}

static void ADSU_ClkConfig(const ADSU_ClkCfg_t *cfg)
{
  uint32_t flash_delay;
  uint32_t reg_val = 0U;

  switch (cfg->clk_src) {
    default:
    case ADSU_OSC_RC:
      break;

    case ADSU_OSC_HRC:
      reg_val |= ADSU_ClkCfg_Osc_HRC;
      break;

    case ADSU_OSC_XT:
      reg_val |= ADSU_ClkCfg_Osc_XT;
      break;
  }

  switch (cfg->clk_div) {
    default:
    case ADSU_CLK_DIV_1:
      break;

    case ADSU_CLK_DIV_2:
      reg_val |= ADSU_ClkCfg_DivOsc_2;
      break;

    case ADSU_CLK_DIV_4:
      reg_val |= ADSU_ClkCfg_DivOsc_4;
      break;

    case ADSU_CLK_DIV_8:
      reg_val |= ADSU_ClkCfg_DivOsc_8;
      break;

    case ADSU_CLK_DIV_16:
      reg_val |= ADSU_ClkCfg_DivOsc_16;
      break;
  }

  if (cfg->clk_out != ADSU_CLK_OUT_DISABLE) {
    reg_val |= ADSU_ClkCfg_EnCLK_OUT;
  }

  __set_CpuReg(CPU_PRW_REG, PRW_FMCU);
  flash_delay = __get_PeriphReg(FMCU_ACCESS_REG);

  if (cfg->flash_delay > flash_delay) {
    SetFlashAccess(cfg->flash_delay);
  }

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __NOP();__NOP();__NOP();__NOP();
  __set_PeriphReg(ADSU_CLKCFG_REG, reg_val);
  __NOP();__NOP();__NOP();__NOP();

  if (cfg->flash_delay < flash_delay) {
    SetFlashAccess(cfg->flash_delay);
  }
}

static uint32_t ADSU_GetFrequency(ADSU_Freq_t type)
{
  uint32_t value = 0U;
  uint32_t clk_con;
  uint32_t clk_cfg;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  clk_con = __get_PeriphReg(ADSU_CLKCON_REG);
  clk_cfg = __get_PeriphReg(ADSU_CLKCFG_REG);

  switch (type) {
    case ADSU_FREQ_RC:
      if (clk_con & ADSU_ClkCon_EnRCOsc) {
        value = RC_CLK_VALUE;
      }
      break;

    case ADSU_FREQ_HRC:
      if (clk_con & ADSU_ClkCon_EnHRCOsc) {
        value = HRC_CLK_VALUE;
      }
      break;

    case ADSU_FREQ_XT:
      if (clk_con & ADSU_ClkCon_EnXTOsc) {
        value = XT_CLK_VALUE;
      }
      break;

    case ADSU_FREQ_SYS:
      switch (clk_cfg & ADSU_ClkCfg_Osc_Msk) {
        case ADSU_ClkCfg_Osc_RC:
          if (clk_con & ADSU_ClkCon_EnRCOsc) {
            value = RC_CLK_VALUE;
          }
          break;

        case ADSU_ClkCfg_Osc_XT:
          if (clk_con & ADSU_ClkCon_EnXTOsc) {
            value = XT_CLK_VALUE;
          }
          break;

        case ADSU_ClkCfg_Osc_HRC:
          if (clk_con & ADSU_ClkCon_EnHRCOsc) {
            value = HRC_CLK_VALUE;
          }
          break;
      }

      value >>= (clk_cfg & ADSU_ClkCfg_DivOsc_Msk) >> ADSU_ClkCfg_DivOsc_Pos;
      break;

    default:
      break;
  }

  return (value);
}

static void ADSU_PeriphEnable(ADSU_Periph_t periph)
{
  uint32_t reg_val;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  reg_val = __get_PeriphReg(ADSU_GATE_REG) | (uint32_t)periph;
  __set_PeriphReg(ADSU_GATE_REG, reg_val);
}

static void ADSU_PeriphDisable(ADSU_Periph_t periph)
{
  uint32_t reg_val;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  reg_val = __get_PeriphReg(ADSU_GATE_REG) & ~(uint32_t)periph;
  __set_PeriphReg(ADSU_GATE_REG, reg_val);
}

static uint32_t ADSU_GetStatePeriph(ADSU_Periph_t periph)
{
  uint32_t reg_val;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  reg_val = __get_PeriphReg(ADSU_GATE_REG) & (uint32_t)periph;

  return ((uint32_t)(reg_val != 0U));
}

static void ADSU_PeriphReset(ADSU_Periph_t periph)
{
  uint32_t reg_val;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  reg_val = __get_PeriphReg(ADSU_GATE_REG);

  if ((reg_val & (uint32_t)periph) != 0U) {
    __set_PeriphReg(ADSU_GATE_REG, reg_val & ~(uint32_t)periph);
    __NOP();__NOP();__NOP();__NOP();
    __set_PeriphReg(ADSU_GATE_REG, reg_val |  (uint32_t)periph);
  }
}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

const Driver_ADSU_t Driver_ADSU = {
  ADSU_ClkReset,
  ADSU_OscConfig,
  ADSU_ClkConfig,
  ADSU_GetFrequency,
  ADSU_PeriphEnable,
  ADSU_PeriphDisable,
  ADSU_GetStatePeriph,
  ADSU_PeriphReset
};
