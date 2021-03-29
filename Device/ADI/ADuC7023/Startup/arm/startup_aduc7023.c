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

#include "asm/aduc7023.h"

#pragma arm

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Vectors       (void) __attribute__ ((section("RESET")));
void Reset_Handler (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
void Undef_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void SWI_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PAbt_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void DAbt_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void IRQ_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void FIQ_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector Table
 *----------------------------------------------------------------------------*/
__ASM void Vectors(void)
{
  PRESERVE8
  
  IMPORT Undef_Handler
  IMPORT SWI_Handler
  IMPORT PAbt_Handler
  IMPORT DAbt_Handler
  IMPORT IRQ_Handler
  IMPORT FIQ_Handler

  LDR    PC, =Reset_Handler
  LDR    PC, =Undef_Handler
  LDR    PC, =SWI_Handler
  LDR    PC, =PAbt_Handler
  LDR    PC, =DAbt_Handler
  NOP
  LDR    PC, =IRQ_Handler
  LDR    PC, =FIQ_Handler
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__ASM void Reset_Handler(void)
{
  PRESERVE8
  
  IMPORT |Image$$FIQ_STACK$$ZI$$Limit|
  IMPORT |Image$$IRQ_STACK$$ZI$$Limit|
  IMPORT |Image$$SVC_STACK$$ZI$$Limit|
  IMPORT |Image$$ABT_STACK$$ZI$$Limit|
  IMPORT |Image$$UND_STACK$$ZI$$Limit|
  IMPORT |Image$$ARM_LIB_STACK$$ZI$$Limit|
  
  // Setup Stack for each exceptional mode
  MSR    CPSR_c, #0xD1
  LDR    SP, =|Image$$FIQ_STACK$$ZI$$Limit|
  MSR    CPSR_c, #0xD2
  LDR    SP, =|Image$$IRQ_STACK$$ZI$$Limit|
  MSR    CPSR_c, #0xD3
  LDR    SP, =|Image$$SVC_STACK$$ZI$$Limit|
  MSR    CPSR_c, #0xD7
  LDR    SP, =|Image$$ABT_STACK$$ZI$$Limit|
  MSR    CPSR_c, #0xDB
  LDR    SP, =|Image$$UND_STACK$$ZI$$Limit|
  MSR    CPSR_c, #0xD0
  LDR    SP, =|Image$$ARM_LIB_STACK$$ZI$$Limit|

  // Call SystemInit
  IMPORT SystemInit
  BL     SystemInit

  // Call __main
  IMPORT __main
  BL     __main
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void) {
  while(1);
}
