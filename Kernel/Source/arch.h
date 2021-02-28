/******************************************************************************
 * @file    arch.h
 * @brief
 * @author  Sergey Koshkin
 * @version V1.0.0
 ******************************************************************************/
/*
 * Copyright (C) 2017-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef  _ARCH_H_
#define  _ARCH_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include "CMSIS/Core/cmsis_compiler.h"

#if   ((defined(__ARM_ARCH_6M__)      && (__ARM_ARCH_6M__      != 0)) ||       \
       (defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) ||       \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) ||       \
       (defined(__ARM_ARCH_8M_BASE__) && (__ARM_ARCH_8M_BASE__ != 0)) ||       \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))

#include "arch_cm.h"

#elif ((defined(__ARM_ARCH_4T__)      && (__ARM_ARCH_4T__      != 0)) ||       \
       (defined(__ARM_ARCH_5T__)      && (__ARM_ARCH_5T__      != 0)))

#include "arch_arm.h"

#endif

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define FILL_STACK_VALUE              (0xFFFFFFFFU)

#endif  // _ARCH_H_

/*------------------------------ End of file ---------------------------------*/
