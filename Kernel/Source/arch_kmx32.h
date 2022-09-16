/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef ARCH_KMX32_H_
#define ARCH_KMX32_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include "CMSIS/Core/Kmx32/cmsis_gcc.h"

extern uint32_t GetModeCPU(void);
extern uint32_t DisableIRQ(void);
extern     void RestoreIRQ(uint32_t);

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define INIT_EXC_RETURN               0xFFFFFFFDUL
#define OS_TICK_HANDLER               osTick_Handler

/* PSW bit definitions */
#define PSW_IL_Pos                    8U
#define PSW_IL_Msk                    (3UL << PSW_IL_Pos)

#define PSW_UM_Pos                    7U
#define PSW_UM_Msk                    (1UL << PSW_UM_Pos)

#define IsIrqMasked()                 false
#define SystemIsrInit()
#define setPrivilegedMode(flag)

#define BEGIN_CRITICAL_SECTION        uint32_t mode = DisableIRQ();
#define END_CRITICAL_SECTION          RestoreIRQ(mode);

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
  return ((GetModeCPU() & PSW_UM_Msk) == 0U);
}

/**
 * @fn          bool IsIrqMode(void)
 * @brief       Check if in IRQ Mode
 * @return      true=IRQ, false=thread
 */
__STATIC_INLINE
bool IsIrqMode(void)
{
  uint32_t mode = GetModeCPU();

  return ((mode & PSW_IL_Msk) != 0U);
}

extern uint8_t IRQ_PendSV;

/**
 * @fn          void PendServCallReq(void)
 * @brief       Set Pending SV (Service Call) Flag.
 */
__STATIC_FORCEINLINE
void PendServCallReq(void)
{
  IRQ_PendSV = 1U;
}

__STATIC_INLINE
uint32_t StackInit(StackAttr_t *attr, bool privileged)
{
  (void) privileged;
  uint32_t fa_base;
  uint32_t fb_base;
  uint32_t *stk = (uint32_t *)(attr->stk_mem + attr->stk_size);

  *(--stk) = 0xB7B7B7B7UL;                      //-- b7
  *(--stk) = 0xB6B6B6B6UL;                      //-- b6
  *(--stk) = 0xB5B5B5B5UL;                      //-- b5
  *(--stk) = 0xB4B4B4B4UL;                      //-- b4
  *(--stk) = 0xB3B3B3B3UL;                      //-- b3
  *(--stk) = 0xB2B2B2B2UL;                      //-- b2
  *(--stk) = 0xB1B1B1B1UL;                      //-- b1
  *(--stk) = 0xB0B0B0B0UL;                      //-- b0
  fb_base  = (uint32_t)stk;

  *(--stk) = 0xA7A7A7A7UL;                      //-- a7
  *(--stk) = 0xA6A6A6A6UL;                      //-- a6
  *(--stk) = 0xA5A5A5A5UL;                      //-- a5
  *(--stk) = 0xA4A4A4A4UL;                      //-- a4
  *(--stk) = 0xA3A3A3A3UL;                      //-- a3
  *(--stk) = 0xA2A2A2A2UL;                      //-- a2
  *(--stk) = 0xA1A1A1A1UL;                      //-- a1
  *(--stk) = attr->func_param;                  //-- a0 - thread's function argument
  fa_base  = (uint32_t)stk;

  *(--stk) = 1UL;                               //-- LC
  *(--stk) = 1UL;                               //-- SMC
  *(--stk) = attr->func_exit;                   //-- CLR
  *(--stk) = 0UL;                               //-- PRW
  *(--stk) = 0UL;                               //-- DP2
  *(--stk) = 0UL;                               //-- DP1
  *(--stk) = attr->func_addr;                   //-- ILR_PC
  *(--stk) = 0x10UL;                            //-- ILR_PSW
  *(--stk) = fb_base;                           //-- FB
  *(--stk) = fa_base;                           //-- FA
  *(--stk) = 0xC7C7C7C7UL;                      //-- c7
  *(--stk) = 0xC6C6C6C6UL;                      //-- c6
  *(--stk) = 0xC5C5C5C5UL;                      //-- c5
  *(--stk) = 0xC4C4C4C4UL;                      //-- c4
  *(--stk) = 0xC3C3C3C3UL;                      //-- c3
  *(--stk) = 0xC2C2C2C2UL;                      //-- c2
  *(--stk) = 0xC1C1C1C1UL;                      //-- c1
  *(--stk) = 0xC0C0C0C0UL;                      //-- c0

  return ((uint32_t)stk);
}

__STATIC_FORCEINLINE
uint32_t svc_0(uint32_t func)
{
  register uint32_t __r0 __ASM("a0");
  register uint32_t __rf __ASM("a4") = func;

  __ASM volatile ("trap 0"
                 :"=r"(__r0)
                 :"r"(__rf)
  );

  return (__r0);
}

__STATIC_FORCEINLINE
uint32_t svc_1(uint32_t param1, uint32_t func)
{
  register uint32_t __r0 __ASM("a0") = param1;
  register uint32_t __rf __ASM("a4") = func;

  __ASM volatile ("trap 0"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0)
  );

  return (__r0);
}

__STATIC_FORCEINLINE
uint32_t svc_2(uint32_t param1, uint32_t param2, uint32_t func)
{
  register uint32_t __r0 __ASM("a0") = param1;
  register uint32_t __r1 __ASM("a1") = param2;
  register uint32_t __rf __ASM("a4") = func;

  __ASM volatile ("trap 0"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1)
  );

  return (__r0);
}

__STATIC_FORCEINLINE
uint32_t svc_3(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t func)
{
  register uint32_t __r0 __ASM("a0") = param1;
  register uint32_t __r1 __ASM("a1") = param2;
  register uint32_t __r2 __ASM("a2") = param3;
  register uint32_t __rf __ASM("a4") = func;

  __ASM volatile ("trap 0"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2)
  );

  return (__r0);
}

__STATIC_FORCEINLINE
uint32_t svc_4(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t func)
{
  register uint32_t __r0 __ASM("a0") = param1;
  register uint32_t __r1 __ASM("a1") = param2;
  register uint32_t __r2 __ASM("a2") = param3;
  register uint32_t __r3 __ASM("a3") = param4;
  register uint32_t __rf __ASM("a4") = func;

  __ASM volatile ("trap 0"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2),"r"(__r3)
  );

  return (__r0);
}

#endif /* ARCH_KMX32_H_ */
