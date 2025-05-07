/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <Driver/IWDG_STM32F4xx.h>

#include <stddef.h>
#include <asm/stm32f4xx.h>

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          int32_t IWDG_Initialize(IWDG_Init_t*)
 * @brief       Initialize the IWDG according to the specified parameters in the
 *              IWDG_Init_t and start watchdog.
 *
 * @param[in]   init  Pointer to a IWDG_Init_t structure that contains
 *                    the configuration information.
 * @return      Execution status
 */
int32_t IWDG_Initialize(const IWDG_Init_t *init)
{
  if (init == NULL) {
    return (IWDG_DRIVER_ERROR_PARAMETER);
  }

  if ((RCC->CSR & RCC_CSR_LSION) == 0UL) {
    RCC->CSR |= RCC_CSR_LSION;
    while ((RCC->CSR & RCC_CSR_LSIRDY) == 0UL);
  }

  /* Enable IWDG */
  IWDG->KR = IWDG_KEY_ENABLE;
  /* Enable write access */
  IWDG->KR = IWDG_KEY_WRITE_ACCESS_ENABLE;
  /* Write to IWDG registers the Prescaler & Reload values to work with */
  IWDG->PR  = init->Prescaler;
  IWDG->RLR = init->Reload;
  /* Wait for register to be updated */
  while (IWDG->SR != 0UL);
  /* Reload IWDG */
  IWDG->KR = IWDG_KEY_RELOAD;

  return (IWDG_DRIVER_OK);
}

/**
 * @fn          int32_t IWDG_Reload(void)
 * @brief       Reload the IWDG.
 *
 * @return      Execution status
 */
int32_t IWDG_Reload(void)
{
  IWDG->KR = IWDG_KEY_RELOAD;

  return (IWDG_DRIVER_OK);
}
