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

#ifndef SYSTEM_ADUCM32X_H_
#define SYSTEM_ADUCM32X_H_

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)  */

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Update SystemCoreClock variable.
 */
extern void SystemCoreClockUpdate(void);

/**
 * @brief       Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_ADUCM32X_H_ */
