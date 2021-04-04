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

extern __NO_RETURN void __iar_program_start(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
            void Vectors       (void) __attribute__ ((naked, section(".vectors")));
__NO_RETURN void Reset_Handler (void) __attribute__ ((naked));
__NO_RETURN void __do_reset    (void);

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
__arm void Vectors(void)
{
  __ASM volatile(
      "LDR    PC, =Reset_Handler                        \n"
      "LDR    PC, =Undef_Handler                        \n"
      "LDR    PC, =SWI_Handler                          \n"
      "LDR    PC, =PAbt_Handler                         \n"
      "LDR    PC, =DAbt_Handler                         \n"
      "NOP                                              \n"
      "LDR    PC, =IRQ_Handler                          \n"
      "LDR    PC, =FIQ_Handler                          \n"
  );
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN
__arm void Reset_Handler(void)
{
  // Setup Stack for each exceptional mode
  __ASM volatile(
      "IMPORT FIQ_STACK                         \n"
      "IMPORT IRQ_STACK$$Limit                         \n"
      "IMPORT SVC_STACK$$Limit                         \n"
      "IMPORT ABT_STACK$$Limit                         \n"
      "IMPORT UND_STACK$$Limit                         \n"
      "IMPORT SYS_STACK$$Limit                         \n"
      "MSR    CPSR_c, #0xD1                            \n"
      "LDR    SP, =SFE(FIQ_STACK)                      \n"
      "MSR    CPSR_c, #0xD2                            \n"
      "LDR    SP, =IRQ_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xD3                            \n"
      "LDR    SP, =SVC_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xD7                            \n"
      "LDR    SP, =ABT_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xDB                            \n"
      "LDR    SP, =UND_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xD0                            \n"
      "LDR    SP, =SYS_STACK$$Limit                    \n"
      // Call __do_reset
      "B      __do_reset                               \n"
  );
}

__NO_RETURN
__arm void __do_reset(void)
{
  SystemInit();                      /* CMSIS System Initialization           */
  __iar_program_start();             /* Enter PreMain (C library entry point) */
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
__arm void Default_Handler(void) {
  while(1);
}
