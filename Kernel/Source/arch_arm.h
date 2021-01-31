/******************************************************************************
 * @file    arch_arm.h
 * @brief   
 * @author  Sergey Koshkin
 * @version V1.0.0
 ******************************************************************************/
/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef ARCH_ARM_H_
#define ARCH_ARM_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include "CMSIS/Core_ARM/cmsis_compiler.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* CPSR bit definitions */
#define CPSR_I_Pos                    7U
#define CPSR_I_Msk                    (1UL << CPSR_I_Pos)

/* CPSR mode bitmasks */
#define CPSR_MODE_USER                0x10U
#define CPSR_MODE_SYSTEM              0x1FU


#define BEGIN_CRITICAL_SECTION        uint32_t cpsr = __get_CPSR(); \
                                      __set_CPSR(cpsr | CPSR_I_Msk);

#define END_CRITICAL_SECTION          __set_CPSR(cpsr);

#define SVC_INDIRECT_REG              "r12"

#define SVC_0(func)                                   (uint32_t)svc_0((uint32_t)(func))
#define SVC_1(param1, func)                           (uint32_t)svc_1((uint32_t)(param1), (uint32_t)(func))
#define SVC_2(param1, param2, func)                   (uint32_t)svc_2((uint32_t)(param1), (uint32_t)(param2), (uint32_t)(func))
#define SVC_3(param1, param2, param3, func)           (uint32_t)svc_3((uint32_t)(param1), (uint32_t)(param2), (uint32_t)(param3), (uint32_t)(func))
#define SVC_4(param1, param2, param3, param4, func)   (uint32_t)svc_4((uint32_t)(param1), (uint32_t)(param2), (uint32_t)(param3), (uint32_t)(param4), (uint32_t)(func))

/*******************************************************************************
 *  exported functions
 ******************************************************************************/

/**
 * @fn          bool IsPrivileged(void)
 * @brief       Check if running Privileged
 *
 * @return      true=privileged, false=unprivileged
 */
__STATIC_INLINE
bool IsPrivileged(void)
{
  return (__get_mode() != CPSR_MODE_USER);
}

/**
 * @fn          bool IsIrqMode(void)
 * @brief       Check if in IRQ Mode
 * @return      true=IRQ, false=thread
 */
__STATIC_INLINE
bool IsIrqMode(void)
{
  return ((__get_mode() != CPSR_MODE_USER) && (__get_mode() != CPSR_MODE_SYSTEM));
}

/**
 * @fn          bool IsIrqMasked(void)
 * @brief       Check if IRQ is Masked
 * @return      true=masked, false=not masked
 */
__STATIC_INLINE
bool IsIrqMasked(void)
{
  return (false);
}

__STATIC_INLINE
uint32_t SystemIsrInit(void)
{
  return (0U);
}

/**
 * @fn          void setPrivilegedMode(uint32_t)
 * @brief
 *
 * @param       flag
 */
__STATIC_INLINE
void setPrivilegedMode(uint32_t flag)
{
  (void) flag;
}

__STATIC_FORCEINLINE
void archSwitchContextRequest(void)
{

}

__STATIC_FORCEINLINE
uint32_t svc_0(uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_0(void);

  SVC_FUNC(func);

  return __svc_0();

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0");

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_1(uint32_t param1, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_1(uint32_t);

  SVC_FUNC(func);

  return __svc_1(param1);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_2(uint32_t param1, uint32_t param2, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1, r1=param2}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_2(uint32_t, uint32_t);

  SVC_FUNC(func);

  return __svc_2(param1, param2);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;
  register uint32_t __r1 __ASM("r1") = param2;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_3(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1, r1=param2, r2=param3}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_3(uint32_t, uint32_t, uint32_t);

  SVC_FUNC(func);

  return __svc_3(param1, param2, param3);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;
  register uint32_t __r1 __ASM("r1") = param2;
  register uint32_t __r2 __ASM("r2") = param3;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_4(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1, r1=param2, r2=param3, r3=param4}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_4(uint32_t, uint32_t, uint32_t, uint32_t);

  SVC_FUNC(func);

  return __svc_4(param1, param2, param3, param4);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;
  register uint32_t __r1 __ASM("r1") = param2;
  register uint32_t __r2 __ASM("r2") = param3;
  register uint32_t __r3 __ASM("r3") = param4;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2),"r"(__r3)
  );

  return (__r0);

#endif
}

#endif /* ARCH_ARM_H_ */
