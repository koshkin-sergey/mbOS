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

/* CPSR bit definitions */
#define CPSR_I_Pos                    7U
#define CPSR_I_Msk                    (1UL << CPSR_I_Pos)

#define CPSR_T_Pos                    5U
#define CPSR_T_Msk                    (1UL << CPSR_T_Pos)

/* CPSR mode bitmasks */
#define CPSR_MODE_USER                0x10U
#define CPSR_MODE_SYSTEM              0x1FU

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
  return (GetModeCPU() != CPSR_MODE_USER);
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

  return ((mode != CPSR_MODE_USER) && (mode != CPSR_MODE_SYSTEM));
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
  uint32_t psr;
  bool     thumb = (attr->func_addr & 1U) != 0U;

  if (privileged) {
    if (thumb) {
      psr = CPSR_MODE_SYSTEM | CPSR_T_Msk;
    } else {
      psr = CPSR_MODE_SYSTEM;
    }
  } else {
    if (thumb) {
      psr = CPSR_MODE_USER   | CPSR_T_Msk;
    } else {
      psr = CPSR_MODE_USER;
    }
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
  return (0U);
}

__STATIC_FORCEINLINE
uint32_t svc_1(uint32_t param1, uint32_t func)
{
  return (0U);
}

__STATIC_FORCEINLINE
uint32_t svc_2(uint32_t param1, uint32_t param2, uint32_t func)
{
  return (0U);
}

__STATIC_FORCEINLINE
uint32_t svc_3(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t func)
{
  return (0U);
}

__STATIC_FORCEINLINE
uint32_t svc_4(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t func)
{
  return (0U);
}

#endif /* ARCH_KMX32_H_ */
