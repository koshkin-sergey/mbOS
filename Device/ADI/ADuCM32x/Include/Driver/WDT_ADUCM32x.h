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

#ifndef WDT_ADUCM32X_H_
#define WDT_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/****** WDT error codes *****/
#define WDT_DRIVER_OK                  0      ///< Operation succeeded
#define WDT_DRIVER_ERROR              -1      ///< Unspecified error
#define ARM_DRIVER_ERROR_PARAMETER    -2      ///< Parameter error

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @fn          void WDT_SignalEvent(void)
 * @brief       Signal WatchDog Timer Event.
 */
typedef void (*WDT_SignalEvent_t)(void);

/**
 * Function documentation
 *
 * @fn          int32_t WDT_Setup(uint32_t interval, WDT_SignalEvent_t cb_event)
 * @brief       Setup Watchdog timer to generate periodic interrupts or resets.
 * @param[in]   interval  Watchdog interval in msec.
 * @param[in]   cb_event  Watchdog event hadler.
 * @return      status code that indicates the execution status of the function.
 *
 * @fn          int32_t WDT_Enable(void)
 * @brief       Enable Watchdog Tick timer.
 * @return      status code that indicates the execution status of the function.
 *
 * @fn          int32_t WDT_Disable(void)
 * @brief       Disable Watchdog Tick timer.
 * @return      status code that indicates the execution status of the function.
 *
 * @fn          uint32_t WDT_GetInterval(void)
 * @brief       Get Watchdog timer interval reload value.
 * @return      Watchdog timer interval reload value in msec.
 *
 * @fn          uint32_t WDT_GetCount(void)
 * @brief       Get Watchdog timer counter value.
 * @return      Watchdog timer counter value.
 *
 * @fn          int32_t WDT_Reload(void)
 * @brief       Clear Watchdog.
 * @return      status code that indicates the execution status of the function.
 */

/**
 * @brief Access structure of the WDT Driver.
 */
typedef struct Driver_WDT {
  int32_t   (*Setup)        (uint32_t interval, WDT_SignalEvent_t cb_event);
  int32_t   (*Enable)       (void);
  int32_t   (*Disable)      (void);
  uint32_t  (*GetInterval)  (void);
  uint32_t  (*GetCount)     (void);
  int32_t   (*Reload)       (void);
} const Driver_WDT_t;

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern Driver_WDT_t Driver_WDT;

#endif /* WDT_ADUCM32X_H_ */
