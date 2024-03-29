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

#define THREAD_INITIAL_MSTATUS        (MSTATUS_MPP_M      | \
                                       MSTATUS_MPIE       | \
                                       MSTATUS_FS_INITIAL | \
                                       MSTATUS_VS_INITIAL)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct thread_stack_frame {
  uint32_t epc;         /* epc - epc    - program counter                     */
  uint32_t ra;          /* x1  - ra     - return address for jumps            */
  uint32_t t0;          /* x5  - t0     - temporary register 0                */
  uint32_t t1;          /* x6  - t1     - temporary register 1                */
  uint32_t t2;          /* x7  - t2     - temporary register 2                */
  uint32_t s0_fp;       /* x8  - s0/fp  - saved register 0 or frame pointer   */
  uint32_t s1;          /* x9  - s1     - saved register 1                    */
  uint32_t a0;          /* x10 - a0     - return value or function argument 0 */
  uint32_t a1;          /* x11 - a1     - return value or function argument 1 */
  uint32_t a2;          /* x12 - a2     - function argument 2                 */
  uint32_t a3;          /* x13 - a3     - function argument 3                 */
  uint32_t a4;          /* x14 - a4     - function argument 4                 */
  uint32_t a5;          /* x15 - a5     - function argument 5                 */
#ifndef __riscv_32e
  uint32_t a6;          /* x16 - a6     - function argument 6                 */
  uint32_t a7;          /* x17 - s7     - function argument 7                 */
  uint32_t s2;          /* x18 - s2     - saved register 2                    */
  uint32_t s3;          /* x19 - s3     - saved register 3                    */
  uint32_t s4;          /* x20 - s4     - saved register 4                    */
  uint32_t s5;          /* x21 - s5     - saved register 5                    */
  uint32_t s6;          /* x22 - s6     - saved register 6                    */
  uint32_t s7;          /* x23 - s7     - saved register 7                    */
  uint32_t s8;          /* x24 - s8     - saved register 8                    */
  uint32_t s9;          /* x25 - s9     - saved register 9                    */
  uint32_t s10;         /* x26 - s10    - saved register 10                   */
  uint32_t s11;         /* x27 - s11    - saved register 11                   */
  uint32_t t3;          /* x28 - t3     - temporary register 3                */
  uint32_t t4;          /* x29 - t4     - temporary register 4                */
  uint32_t t5;          /* x30 - t5     - temporary register 5                */
  uint32_t t6;          /* x31 - t6     - temporary register 6                */
#endif
  uint32_t mstatus;     /*              - machine status register             */
} thread_stack_frame_t;

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
  (void) privileged;
  thread_stack_frame_t *frame;

  frame = (thread_stack_frame_t *)(attr->stk_mem + attr->stk_size);
  frame -= sizeof(thread_stack_frame_t);

  for (uint32_t i = 0U; i < sizeof(thread_stack_frame_t) / sizeof(uint32_t); ++i) {
    ((uint32_t *)frame)[i] = 0xdeadbeef;
  }

  frame->a0      = attr->func_param;
  frame->epc     = attr->func_addr;
  frame->ra      = attr->func_exit;
  frame->mstatus = THREAD_INITIAL_MSTATUS;

  return ((uint32_t)frame);
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
