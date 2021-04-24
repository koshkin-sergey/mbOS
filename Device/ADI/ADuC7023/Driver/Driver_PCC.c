/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "asm/aduc7023.h"
#include "asm/Driver_PCC.h"

/**
 * @brief
 */
void PCC_ClkReset(void)
{
  PCC->POWKEY1 = PCC_POWKEY1_VALUE;
  PCC->POWCON0 = (uint8_t) 0U;
  PCC->POWKEY2 = PCC_POWKEY2_VALUE;

  PCC->PLLKEY1 = PCC_PLLKEY1_VALUE;
  PCC->PLLCON  = (uint8_t) 0x21U;
  PCC->PLLKEY2 = PCC_PLLKEY2_VALUE;

  PCC->POWKEY3 = PCC_POWKEY3_VALUE;
  PCC->POWCON1 = (uint8_t) 0U;
  PCC->POWKEY4 = PCC_POWKEY4_VALUE;
}

/**
 * @brief
 * @param periph
 */
void PCC_EnablePeriph(PCC_Periph_t periph)
{
  PCC->POWKEY3 = PCC_POWKEY3_VALUE;
  PCC->POWCON1 |= periph;
  PCC->POWKEY4 = PCC_POWKEY4_VALUE;
}

/**
 * @brief
 * @param periph
 */
void PCC_DisablePeriph(PCC_Periph_t periph)
{
  PCC->POWKEY3 = PCC_POWKEY3_VALUE;
  PCC->POWCON1 &= ~periph;
  PCC->POWKEY4 = PCC_POWKEY4_VALUE;
}
