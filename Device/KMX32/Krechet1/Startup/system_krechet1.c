/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Kernel/irq.h>

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

/*!< System Clock Frequency (Core Clock)  */
uint32_t SystemCoreClock = 15000000U;

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Update SystemCoreClock variable.
 */
void SystemCoreClockUpdate(void)
{
  SystemCoreClock = 15000000U;
}

/**
 * @brief       Initialize the System.
 */
void SystemInit(void)
{
  IRQ_Initialize();
}
