/*
 * Copyright (C) 2018-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Project: mbOS real-time kernel
 */

                .syntax  unified

                .equ   MODE_IRQ,        0x12
                .equ   MODE_SVC,        0x13

                .equ   I_BIT,           0x80        // When I bit is set, IRQ is disabled
                .equ   F_BIT,           0x40        // When F bit is set, FIQ is disabled

                .section ".rodata"
                .global  irqLib                     // Non weak library reference
irqLib:
                .byte    0

                .section ".data"
                .global  IRQ_PendSV
IRQ_NestLevel:
                .word    0                          // IRQ nesting level counter
IRQ_PendSV:
                .byte    0                          // Pending SVC flag


                .arm
                .section ".text"
                .align   4


                .type    SWI_Handler, %function
                .global  SWI_Handler
                .fnstart
                .cantunwind
SWI_Handler:

                .fnend
                .size    SWI_Handler, .-SWI_Handler


                .type    IRQ_Handler, %function
                .global  IRQ_Handler
                .fnstart
                .cantunwind
IRQ_Handler:

                MOV     SP, R0                      // Save R0 in SP_irq
                SUB     R0, LR, #4                  // Put return address in R0
                MSR     CPSR_c, #(MODE_SVC | I_BIT) // Switch to Supervisor mode, IRQ disabled
                STMFD   SP!, {R0}                   // Save LR_irq to SVC stack
                STMFD   SP!, {R1-R3,R12,LR}         // Save APCS corruptible registers to SVC stack
                MOV     R0, SP                      // Make the SP_svc visible to IRQ mode
                SUB     SP, SP, #(2*4)              // Make room for stacking SPSR_irq, R0
                MSR     CPSR_c, #(MODE_IRQ | I_BIT) // Switch to IRQ mode, IRQ disabled
                MRS     R1, SPSR                    // Put the SPSR_irq in R1
                STMFD   R0, {R1,SP}                 // Save SPSR_irq, R0 to SVC stack
                MSR     CPSR_c, #(MODE_SVC | I_BIT) // Switch to Supervisor mode, IRQ disabled

                LDR     R0, =IRQ_NestLevel
                LDR     R1, [R0]
                ADD     R1, R1, #1                  // Increment IRQ nesting level
                STR     R1, [R0]

                MOV     R3, SP                      // Move SP into R3
                AND     R3, R3, #4                  // Get stack adjustment to ensure 8-byte alignment
                SUB     SP, SP, R3                  // Adjust stack
                STMFD   SP!, {R3, R4}               // Store stack adjustment(R3) and user data(R4)

                LDR     R12, =IRQ_GetActiveIRQ
                MOV     LR, PC
                BX      R12                         // Retrieve interrupt ID into R0
                MOV     R4, R0                      // Move interrupt ID to R4

                LDR     R12, =IRQ_GetHandler
                MOV     LR, PC
                BX      R12                         // Retrieve interrupt handler address for current ID
                CMP     R0, #0                      // Check if handler address is 0
                BEQ     IRQ_End                     // If 0, end interrupt and return

                MSR     CPSR_c, #MODE_SVC           // Re-enable interrupts
                MOV     LR, PC
                BX      R0                          // Call IRQ handler
                MSR     CPSR_c, #(MODE_SVC | I_BIT) // Disable interrupts

IRQ_End:
                MOV     R0, R4                      // Move interrupt ID to R0
                LDR     R12, =IRQ_EndOfInterrupt
                MOV     LR, PC
                BX      R12                         // Signal end of interrupt

                LDMFD   SP!, {R3, R4}               // Restore stack adjustment(R3) and user data(R4)
                ADD     SP, SP, R3                  // Unadjust stack

                BL      ContextSwitch               // Continue in context switcher

                LDR     R0, =IRQ_NestLevel
                LDR     R1, [R0]
                SUBS    R1, R1, #1                  // Decrement IRQ nesting level
                STR     R1, [R0]

                LDMFD   SP!, {R0}                   // Restore SPSR_irq in R0
                MSR     SPSR_cxsf, R0               // Move SPSR_irq to SPSR_svc
                LDMFD   SP!, {R0-R3, R12, LR, PC}^  // Restore stacked APCS registers and return from IRQ handler

                .fnend
                .size    IRQ_Handler, .-IRQ_Handler


                .type    ContextSwitch, %function
                .global  ContextSwitch
                .fnstart
                .cantunwind
ContextSwitch:

                STMFD    SP!, {LR}

                LDR     R0, =IRQ_NestLevel          // Check interrupt nesting level
                LDR     R1, [R0]                    // Load IRQ nest level
                CMP     R1, #1
                BNE     ContextExit                 // Nesting interrupts, exit context switcher

                LDR     R12, =osInfo                // Load address of osInfo.run
                LDM     R12, {R0, R1}               // Load osInfo.thread.run: curr & next
                LDR     R2, =IRQ_PendSV             // Load address of IRQ_PendSV flag
                LDRB    R3, [R2]                    // Load PendSV flag

                CMP     R0, R1                      // Check if context switch is required
                BNE     ContextCheck                // Not equal, check if context save required
                CMP     R3, #1                      // Compare IRQ_PendSV value
                BNE     ContextExit                 // No post processing (and no context switch requested)

ContextCheck:
                STR     R1, [R12]                   // Store run.next as run.curr
                // R0 = curr, R1 = next, R2 = &IRQ_PendSV, R3 = IRQ_PendSV, R12 = &osInfo.thread.run
                STMFD   SP!, {R1-R3, R12}
                CMP     R0, #0                      // Is osInfo.thread.run.curr == 0
                BEQ     PostProcess                 // Current deleted, skip context save

ContextSave:
                MOV     LR, R0                      // Move &osInfo.thread.run.curr to LR
                MOV     R0, SP                      // Move SP_svc into R0
                ADD     R0, R0, #20                 // Adjust SP_svc to R0 of the basic frame
                SUB     SP, SP, #4
                STM     SP, {SP}^                   // Save SP_usr to current stack
                POP     {R1}                        // Pop SP_usr into R1

                SUB     R1, R1, #64                 // Adjust SP_usr to R4 of the basic frame
                STMIA   R1!, {R4-R11}               // Save R4-R11 to user stack
                LDMIA   R0!, {R4-R8}                // Load stacked R0-R3,R12 into R4-R8
                STMIA   R1!, {R4-R8}                // Store them to user stack
                STM     R1, {LR}^                   // Store LR_usr directly
                ADD     R1, R1, #4                  // Adjust user sp to PC
                LDMIB   R0!, {R5-R6}                // Load current PC, CPSR
                STMIA   R1!, {R5-R6}                // Restore user PC and CPSR

                SUB     R1, R1, #64                 // Adjust SP_usr to stacked R4
                STR     R1, [LR]                    // Store user sp to osInfo.thread.run.curr

PostProcess:
                // IRQ post processing check
                POP     {R8-R11}                    // Pop R8 = run.next, R9 = &IRQ_PendSV, R10 = IRQ_PendSV, R11 = &osInfo.thread.run
                CMP     R10, #1                     // Compare PendSV value
                BNE     ContextRestore              // Skip post processing if not pending

PendExec:

PendCheck:

ContextRestore:

ContextExit:
                LDMFD    SP!, {PC}

                .fnend
                .size    ContextSwitch, .-ContextSwitch


                .end
