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
#define WDT_DRIVER_OK                  0                                        ///< Operation succeeded
#define WDT_DRIVER_ERROR              -1                                        ///< Unspecified error
#define ARM_DRIVER_ERROR_BUSY         -2                                        ///< Driver is busy
#define WDT_DRIVER_ERROR_UNSUPPORTED  -3                                        ///< Operation not supported
#define ARM_DRIVER_ERROR_PARAMETER    -4                                        ///< Parameter error

/****** WDT Control Codes *****/
#define WDT_CONTROL_Pos                0
#define WDT_CONTROL_Msk               (0xFFUL)


/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @fn          void WDT_SignalEvent(void)
 * @brief       Signal WatchDog Timer Event.
 */
typedef void (*WDT_SignalEvent_t)(void);

/**
 * @brief Access structure of the WDT Driver.
 */
typedef struct Driver_WDT {
  int32_t (*SetSignalEvent) (WDT_SignalEvent_t cb_event);
  int32_t (*Control)        (uint32_t control, uint32_t arg);
  int32_t (*Reload)         (void);
} const Driver_WDT_t;

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern Driver_WDT_t Driver_WDT;

#endif /* WDT_ADUCM32X_H_ */
