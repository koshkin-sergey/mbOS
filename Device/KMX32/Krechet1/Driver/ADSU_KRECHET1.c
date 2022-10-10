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

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void ADSU_ClkReset(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_CLKCON_REG,  ADSU_ClkCon_EnRCOsc);
  __set_PeriphReg(ADSU_CLKCFG_REG,  0U);
  __set_PeriphReg(ADSU_GATE_REG,    0U);
  __set_PeriphReg(ADSU_WAKECFG_REG, 0U);
  __set_PeriphReg(ADSU_MAXLOAD_REG, 0U);
}

static void ADSU_OscConfig(ADSU_OscCfg_t cfg)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_CLKCON_REG, cfg & ADSU_ClkCon_Msk);
}

static void ADSU_ClkConfig(ADSU_ClkCfg_t cfg)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_CLKCFG_REG, cfg & ADSU_ClkCfg_Msk);
}

static uint32_t ADSU_GetFrequency(ADSU_Freq_t type)
{
  uint32_t value = 0U;

  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);

  switch (type) {
    case ADSU_FREQ_RC:

      break;

    case ADSU_FREQ_HRC:

      break;

    case ADSU_FREQ_XT:

      break;

    case ADSU_FREQ_OSC:

      break;

    case ADSU_FREQ_SYS:

      break;
  }

  return (value);
}

static void ADSU_PeriphEnable(ADSU_Periph_t periph)
{

}

static void ADSU_PeriphDisable(ADSU_Periph_t periph)
{

}

static uint32_t ADSU_GetStatePeriph(ADSU_Periph_t periph)
{
  uint32_t value = 0U;

  return (value);
}

static void ADSU_PeriphReset(ADSU_Periph_t periph)
{

}

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

Driver_ADSU_t Driver_ADSU = {
  ADSU_ClkReset,
  ADSU_OscConfig,
  ADSU_ClkConfig,
  ADSU_GetFrequency,
  ADSU_PeriphEnable,
  ADSU_PeriphDisable,
  ADSU_GetStatePeriph,
  ADSU_PeriphReset
};
