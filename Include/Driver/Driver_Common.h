/*
 * Copyright (c) 2013-2017 ARM Limited
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *
 * Project: Common Driver definitions
 */

#ifndef DRIVER_COMMON_H_
#define DRIVER_COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define DRIVER_VERSION_MAJOR_MINOR(major,minor) (((major) << 8) | (minor))

/**
\brief Driver Version
*/
typedef struct _DRIVER_VERSION {
  uint16_t api;                         ///< API version
  uint16_t drv;                         ///< Driver version
} DRIVER_VERSION;

/* General return codes */
#define DRIVER_OK                     0 ///< Operation succeeded
#define DRIVER_ERROR                 -1 ///< Unspecified error
#define DRIVER_ERROR_BUSY            -2 ///< Driver is busy
#define DRIVER_ERROR_TIMEOUT         -3 ///< Timeout occurred
#define DRIVER_ERROR_UNSUPPORTED     -4 ///< Operation not supported
#define DRIVER_ERROR_PARAMETER       -5 ///< Parameter error
#define DRIVER_ERROR_SPECIFIC        -6 ///< Start of driver specific errors

/**
\brief General power states
*/ 
typedef enum _POWER_STATE {
  POWER_OFF,                            ///< Power off: no operation possible
  POWER_LOW,                            ///< Low Power mode: retain state, detect and signal wake-up events
  POWER_FULL                            ///< Power on: full operation at maximum performance
} POWER_STATE;

#endif /* DRIVER_COMMON_H_ */
