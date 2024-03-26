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

#define IsIrqMasked()                 false
#define IsPrivileged()                false
#define SystemIsrInit()
#define setPrivilegedMode(flag)

#define BEGIN_CRITICAL_SECTION        uint32_t mode = CSR_READ_CLEAR(CSR_MSTATUS, MSTATUS_MIE);
#define END_CRITICAL_SECTION          CSR_WRITE(CSR_MSTATUS, mode);

/*******************************************************************************
 *  exported functions
 ******************************************************************************/

/**
 * @fn          bool IsIrqMode(void)
 * @brief       Check if in IRQ Mode
 * @return      true=IRQ, false=thread
 */
__STATIC_INLINE
bool IsIrqMode(void)
{
  return (IRQ_NestLevel > 0U);
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
  uint32_t psr;
//  bool     thumb = (attr->func_addr & 1U) != 0U;

  if (privileged) {
//    if (thumb) {
//      psr = CPSR_MODE_SYSTEM | CPSR_T_Msk;
//    } else {
//      psr = CPSR_MODE_SYSTEM;
//    }
//  } else {
//    if (thumb) {
//      psr = CPSR_MODE_USER   | CPSR_T_Msk;
//    } else {
//      psr = CPSR_MODE_USER;
//    }
  }

  uint32_t *stk = (uint32_t *)(attr->stk_mem + attr->stk_size);

  *(--stk) = psr;                               //-- xPSR
  *(--stk) = attr->func_addr;                   //-- Entry Point (PC)
  *(--stk) = attr->func_exit;                   //-- R14 (LR)
  *(--stk) = 0x12121212L;                       //-- R12
  *(--stk) = 0x03030303L;                       //-- R3
  *(--stk) = 0x02020202L;                       //-- R2
  *(--stk) = 0x01010101L;                       //-- R1
  *(--stk) = attr->func_param;                  //-- R0 - thread's function argument
  *(--stk) = 0x11111111L;                       //-- R11
  *(--stk) = 0x10101010L;                       //-- R10
  *(--stk) = 0x09090909L;                       //-- R9
  *(--stk) = 0x08080808L;                       //-- R8
  *(--stk) = 0x07070707L;                       //-- R7
  *(--stk) = 0x06060606L;                       //-- R6
  *(--stk) = 0x05050505L;                       //-- R5
  *(--stk) = 0x04040404L;                       //-- R4

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
