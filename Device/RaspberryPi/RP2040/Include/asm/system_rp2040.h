/*
 * Copyright (C) 2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef SYSTEM_RP2040_H_
#define SYSTEM_RP2040_H_

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @brief System Clock Frequency (Core Clock)
 */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Update SystemCoreClock variable.
 *
 * Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate(void);

/**
 * @brief       Setup the microcontroller system.
 *
 * Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_RP2040_H_ */
