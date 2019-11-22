/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *
 * Description: This file contains definitions for Debug.
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdint.h>

typedef struct Debug_s {
    uint32_t (*Initialize)(void);
    uint32_t (*Uninitialize)(void);
     int32_t (*printf)(const char *template, ...);
} const Debug_t;

#if defined(DEBUG)
  extern Debug_t Debug;
  #define DEBUG_INIT()                  Debug.Initialize()
  #define DEBUG_LOG(...)                Debug.printf(__VA_ARGS__)
#else
  #define DEBUG_INIT()
  #define DEBUG_LOG(...)
#endif

/* Debug return codes */
#define DEBUG_OK                      0 ///< Operation succeeded
#define DEBUG_ERROR                  -1 ///< Unspecified error

#endif /* DEBUG_H_ */

/* ----------------------------- End of file ---------------------------------*/
