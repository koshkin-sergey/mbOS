/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef TICK_H_
#define TICK_H_

#include <stdint.h>

/// IRQ Handler.
#ifndef IRQHANDLER_T
#define IRQHANDLER_T
typedef void (*IRQHandler_t) (void);
#endif

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)  */

/**
 * @brief       Setup OS Tick timer to generate periodic RTOS Kernel Ticks
 * @param[in]   freq      tick frequency in Hz
 * @param[in]   handler   tick IRQ handler
 * @return      0 on success, -1 on error.
 */
int32_t  osTickSetup(uint32_t freq, IRQHandler_t handler);

/**
 * @brief       Enable and start the OS Tick timer to generate periodic RTOS
 *              Kernel Tick interrupts
 */
void     osTickEnable(void);

/**
 * @brief       Stop the OS Tick timer and disable generation of RTOS Kernel
 *              Tick interrupts
 */
void     osTickDisable(void);

/**
 * @brief       Enable generation of RTOS Kernel Tick interrupts
 *              without changing the operating mode of the OS Tick timer
 */
void     osTickEnableIRQ(void);

/**
 * @brief       Disable generation of RTOS Kernel Tick interrupts
 *              without changing the operating mode of the OS Tick timer
 */
void     osTickDisableIRQ(void);

/**
 * @brief       Acknowledge execution of OS Tick timer interrupt
 */
void     osTickAcknowledgeIRQ(void);

/**
 * @brief       Get OS Tick timer clock frequency
 * @return      OS Tick timer clock frequency in Hz
 */
uint32_t osTickGetClock(void);

/**
 * @brief       Get OS Tick timer interval reload value
 * @return      OS Tick timer interval reload value
 */
uint32_t osTickGetInterval(void);

/**
 * @brief       Get OS Tick timer counter value
 * @return      OS Tick timer counter value
 */
uint32_t osTickGetCount(void);

/**
 * @brief       Get OS Tick timer overflow status
 * @return      OS Tick overflow status (1 - overflow, 0 - no overflow).
 */
uint32_t osTickGetOverflow(void);

#endif /* TICK_H_ */
