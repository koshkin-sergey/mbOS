/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef ARCH_RISCV_H_
#define ARCH_RISCV_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <Core/Riscv/compiler.h>
#include <Core/Riscv/core_riscv.h>

extern uint8_t IRQ_NestLevel;
extern uint8_t IRQ_PendSV;

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define INIT_EXC_RETURN               0xFFFFFFFDUL
#define OS_TICK_HANDLER               osTick_Handler

#define IsPrivileged()                false
#define SystemIsrInit()
#define setPrivilegedMode(flag)

#define BEGIN_CRITICAL_SECTION        uint32_t mode = CSR_READ_CLEAR(CSR_MSTATUS, MSTATUS_MIE);
#define END_CRITICAL_SECTION          CSR_WRITE(CSR_MSTATUS, mode);

#define INITIAL_MSTATUS               (MSTATUS_MPP_M      | \
                                       MSTATUS_MPIE       | \
                                       MSTATUS_FS_INITIAL | \
                                       MSTATUS_VS_INITIAL)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/*******************************************************************************
 *  exported functions
 ******************************************************************************/

/**
 * @fn          bool IsIrqMode(void)
 * @brief       Check if in IRQ Mode
 * @return      true=IRQ, false=thread
 */
__STATIC_FORCEINLINE
bool IsIrqMode(void)
{
  return (CSR_READ(CSR_MIP) != 0U);
}

/**
 * @fn          bool IsIrqMasked(void)
 * @brief       Check if in IRQ Mode
 * @return      true=IRQ, false=thread
 */
__STATIC_FORCEINLINE
bool IsIrqMasked(void)
{
  return ((CSR_READ(CSR_MSTATUS) & MSTATUS_MIE_Msk) == 0U);
}

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
  uint32_t *stk = (uint32_t *)(attr->stk_mem + attr->stk_size);

#ifndef __riscv_32e
  *(--stk) = 0x31313131;        /* x31 - t6     - temporary register 6        */
  *(--stk) = 0x30303030;        /* x30 - t5     - temporary register 5        */
  *(--stk) = 0x29292929;        /* x29 - t4     - temporary register 4        */
  *(--stk) = 0x28282828;        /* x28 - t3     - temporary register 3        */
  *(--stk) = 0x17171717;        /* x17 - a7     - function argument 7         */
  *(--stk) = 0x16161616;        /* x16 - a6     - function argument 6         */
#endif
  *(--stk) = INITIAL_MSTATUS;   /* mstatus      - status register             */
  *(--stk) = attr->func_addr;   /* epc - epc    - program counter             */
  *(--stk) = attr->func_exit;   /* x1  - ra     - return address for jumps    */
  *(--stk) = 0x07070707;        /* x7  - t2     - temporary register 2        */
  *(--stk) = 0x06060606;        /* x6  - t1     - temporary register 1        */
  *(--stk) = 0x05050505;        /* x5  - t0     - temporary register 0        */
  *(--stk) = 0x15151515;        /* x15 - a5     - function argument 5         */
  *(--stk) = 0x14141414;        /* x14 - a4     - function argument 4         */
  *(--stk) = 0x13131313;        /* x13 - a3     - function argument 3         */
  *(--stk) = 0x12121212;        /* x12 - a2     - function argument 2         */
  *(--stk) = 0x11111111;        /* x11 - a1     - function argument 1         */
  *(--stk) = attr->func_param;  /* x10 - a0     - thread's function argument  */
#ifndef __riscv_32e
  *(--stk) = 0x27272727;        /* x27 - s11    - saved register 11           */
  *(--stk) = 0x26262626;        /* x26 - s10    - saved register 10           */
  *(--stk) = 0x25252525;        /* x25 - s9     - saved register 9            */
  *(--stk) = 0x24242424;        /* x24 - s8     - saved register 8            */
  *(--stk) = 0x23232323;        /* x23 - s7     - saved register 7            */
  *(--stk) = 0x22222222;        /* x22 - s6     - saved register 6            */
  *(--stk) = 0x21212121;        /* x21 - s5     - saved register 5            */
  *(--stk) = 0x20202020;        /* x20 - s4     - saved register 4            */
  *(--stk) = 0x19191919;        /* x19 - s3     - saved register 3            */
  *(--stk) = 0x18181818;        /* x18 - s2     - saved register 2            */
#endif
  *(--stk) = 0x09090909;        /* x9  - s1     - saved register 1            */
  *(--stk) = 0x08080808;        /* x8  - s0     - saved register 0            */

  return ((uint32_t)stk);
}

__STATIC_FORCEINLINE
uint32_t svc_0(uint32_t func)
{
  register uint32_t __r0 __ASM("a0");
  register uint32_t __rf __ASM("a5") = func;

  __ASM volatile (
      "ecall \n\t"
      :"=r"(__r0)
      :"r"(__rf)
  );

  return (__r0);
}

__STATIC_FORCEINLINE
uint32_t svc_1(uint32_t param1, uint32_t func)
{
  register uint32_t __r0 __ASM("a0") = param1;
  register uint32_t __rf __ASM("a5") = func;

  __ASM volatile (
      "ecall \n\t"
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
  register uint32_t __rf __ASM("a5") = func;

  __ASM volatile (
      "ecall \n\t"
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
  register uint32_t __rf __ASM("a5") = func;

  __ASM volatile (
      "ecall \n\t"
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
  register uint32_t __rf __ASM("a5") = func;

  __ASM volatile (
      "ecall \n\t"
      :"=r"(__r0)
      :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2),"r"(__r3)
  );

  return (__r0);
}

#endif /* ARCH_RISCV_H_ */
