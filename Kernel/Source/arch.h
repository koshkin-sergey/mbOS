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

#include <stdint.h>

/// Attributes structure for StackInit function.
typedef struct StackAttr_s {
  uint32_t          func_addr;
  uint32_t         func_param;
  uint32_t          func_exit;
  uint32_t            stk_mem;
  uint32_t           stk_size;
} StackAttr_t;

#if   ((defined(__ARM_ARCH_6M__)      && (__ARM_ARCH_6M__      != 0)) ||       \
       (defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) ||       \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) ||       \
       (defined(__ARM_ARCH_8M_BASE__) && (__ARM_ARCH_8M_BASE__ != 0)) ||       \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))

#include "CMSIS/Core/cmsis_compiler.h"
#include "arch_cm.h"

#elif ((defined(__ARM_ARCH_4T__)      && (__ARM_ARCH_4T__      != 0)) ||       \
       (defined(__ARM_ARCH_5T__)      && (__ARM_ARCH_5T__      != 0)))

#include "CMSIS/Core_ARM/cmsis_compiler.h"
#include "arch_arm.h"

#endif

#define FILL_STACK_VALUE              (0xFFFFFFFFU)
/* Minimal thread stack size in bytes */
#define MIN_THREAD_STK_SIZE           64U

#define SVC_0(func)                                   (uint32_t)svc_0((uint32_t)(func))
#define SVC_1(param1, func)                           (uint32_t)svc_1((uint32_t)(param1), (uint32_t)(func))
#define SVC_2(param1, param2, func)                   (uint32_t)svc_2((uint32_t)(param1), (uint32_t)(param2), (uint32_t)(func))
#define SVC_3(param1, param2, param3, func)           (uint32_t)svc_3((uint32_t)(param1), (uint32_t)(param2), (uint32_t)(param3), (uint32_t)(func))
#define SVC_4(param1, param2, param3, param4, func)   (uint32_t)svc_4((uint32_t)(param1), (uint32_t)(param2), (uint32_t)(param3), (uint32_t)(param4), (uint32_t)(func))

#endif  // _ARCH_H_

/*------------------------------ End of file ---------------------------------*/
