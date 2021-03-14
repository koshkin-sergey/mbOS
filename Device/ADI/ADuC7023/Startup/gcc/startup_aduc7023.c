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

#include <CMSIS/Core_ARM/cmsis_compiler.h>
#include <asm/system_aduc7023.h>

/*----------------------------------------------------------------------------
  Definitions
 *----------------------------------------------------------------------------*/
#define USR_MODE 0x10            // User mode
#define FIQ_MODE 0x11            // Fast Interrupt Request mode
#define IRQ_MODE 0x12            // Interrupt Request mode
#define SVC_MODE 0x13            // Supervisor mode
#define ABT_MODE 0x17            // Abort mode
#define UND_MODE 0x1B            // Undefined Instruction mode
#define SYS_MODE 0x1F            // System mode

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Vectors       (void) __attribute__ ((naked, section("RESET")));
void Reset_Handler (void) __attribute__ ((naked));

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
void Vectors(void) {
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
void Reset_Handler(void) {
  __ASM volatile(
  // Setup Stack for each exceptional mode
  "MSR    CPSR_c, #0xD1                            \n"
  "LDR    SP, =Image$$FIQ_STACK$$ZI$$Limit         \n"
  "MSR    CPSR_c, #0xD2                            \n"
  "LDR    SP, =Image$$IRQ_STACK$$ZI$$Limit         \n"
  "MSR    CPSR_c, #0xD3                            \n"
  "LDR    SP, =Image$$SVC_STACK$$ZI$$Limit         \n"
  "MSR    CPSR_c, #0xD7                            \n"
  "LDR    SP, =Image$$ABT_STACK$$ZI$$Limit         \n"
  "MSR    CPSR_c, #0xDB                            \n"
  "LDR    SP, =Image$$UND_STACK$$ZI$$Limit         \n"
  "MSR    CPSR_c, #0xDF                            \n"
  "LDR    SP, =Image$$SYS_STACK$$ZI$$Limit         \n"

  // Call SystemInit
  "BL     SystemInit                               \n"
  // Call __main
  "BL     _start                                   \n"
  );
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void) {
  while(1);
}
