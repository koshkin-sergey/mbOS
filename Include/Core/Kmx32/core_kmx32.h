/**************************************************************************//**
 * @file     core_kmx32.h
 * @brief    KMX32 Core Peripheral Access Layer Header File
 * @version  V1.0.0
 * @date     03. June 2022
 ******************************************************************************/
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

#ifndef __CORE_KMX32_H_GENERIC
#define __CORE_KMX32_H_GENERIC

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmsis_gcc.h"

#ifdef __cplusplus
}
#endif

#endif /* __CORE_KMX32_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_KMX32_H_DEPENDANT
#define __CORE_KMX32_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

 /* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __ARM_REV
    #define __ARM_REV              0x0000U
    #warning "__ARM_REV not defined in device header file; using default!"
  #endif
#endif

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
  #define   __I     volatile             /*!< \brief Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< \brief Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< \brief Defines 'write only' permissions */
#define     __IO    volatile             /*!< \brief Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*!< \brief Defines 'read only' structure member permissions */
#define     __OM     volatile            /*!< \brief Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*!< \brief Defines 'read / write' structure member permissions */
#define RESERVED(N, T) T RESERVED##N     // placeholder struct members used for "reserved" areas

#ifdef __cplusplus
}
#endif

#endif /* __CORE_KMX32_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
