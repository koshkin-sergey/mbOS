/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

                .equ    IE_BIT,           0x10      // When IE bit is set, IRQ is enabled
                .equ    PSW_IL_BIT,       0x0100
                .equ    K_STATE_RUNNING,  2         // osKernelState_t::osKernelRunning
                .equ    I_K_STATE_OFS,    16        // osInfo.kernel.state offset

                .section ".rodata"

                .global  irqLib                     // Non weak library reference
irqLib:
                .byte    0


                .section ".data"

                .global  IRQ_PendSV
IRQ_PendSV:     .long    0                          // Pending SVC flag
IRQ_NestLevel:  .long    0                          // IRQ nesting level counter
MSP:            .long    0


                .section ".text.os.handlers"
                .align   1

                .type   SWI_Handler, %function
                .global SWI_Handler
SWI_Handler:
                pushr   LC
                pushr   SMC
                pushr   CLR
                pushr   PRW
                push    DP2
                push    DP1
                mfprs   DP1, ILR_PC
                mfprs   DP2, ILR_PSW
                push    DP1
                push    DP2
                pushr   FB
                pushr   FA

                mtprs   USP, c7
                lda     dp1, osInfo + I_K_STATE_OFS // Load kernel state
                cmpl    dp1, K_STATE_RUNNING        // Check osKernelRunning
                blt     1$                          // Continue if kernel is not running
                lda     c7, MSP                     // Switch to Main Stack

1$:
                srfa    8
                srfb    1

                mov     b0, dp1

                lda     a0, IRQ_NestLevel
                addl    a0, 1                       // Increment IRQ nesting level
                sta     IRQ_NestLevel, a0

                cmpl    b0, K_STATE_RUNNING         // Check osKernelRunning
                blt     SWI_FuncCall                // Continue if kernel is not running
                jsr     osTickDisableIRQ            // Disable OS Tick interrupt

SWI_FuncCall:
                push    c0
                push    c1
                mfprs   c0, USP
                ldd     c0, (c0)
                lddo    a0, (c0), 0
                lddo    a1, (c0), 4
                lddo    a2, (c0), 8
                lddo    a3, (c0), 12
                lddo    c1, (c0), 16

                sst     IE_BIT                      // Re-enable interrupts
                ijsr    c1                          // Branch to SVC function
                cst     IE_BIT                      // Disable interrupts

                std     (c0), a0                    // Push return value to stack

                pop     c1
                pop     c0

                cmpl    b0, K_STATE_RUNNING         // Check osKernelRunning
                blt     SWI_ContextCheck            // Continue if kernel is not running
                jsr     osTickEnableIRQ             // Enable OS Tick interrupt

SWI_ContextCheck:
                jsr     ContextSwitch               // Continue in context switcher

                lda     a0, IRQ_NestLevel
                subl    a0, 1                       // Decrement IRQ nesting level
                sta     IRQ_NestLevel, a0

                rsfb    1
                rsfa    8

                sta     MSP, c7
                mfprs   c7, USP

                popr    FA
                popr    FB
                pop     DP1
                pop     DP2
                mtprs   ILR_PSW, DP1
                mtprs   ILR_PC,  DP2
                pop     DP1
                pop     DP2
                popr    PRW
                popr    CLR
                popr    SMC
                popr    LC

                rti
                .size   SWI_Handler, .-SWI_Handler


                .type   SysTick_Handler, %function
                .global SysTick_Handler
SysTick_Handler:
                pushr   LC
                pushr   SMC
                pushr   CLR
                pushr   PRW
                push    DP2
                push    DP1
                mfprs   DP2, ILR_PC
                mfprs   DP1, ILR_PSW
                push    DP2
                push    DP1
                pushr   FB
                pushr   FA

                mtprs   USP, c7
                lda     c7, MSP                     // Switch to Main Stack

                srfa    8

                lda     a0, IRQ_NestLevel
                addl    a0, 1                       // Increment IRQ nesting level
                sta     IRQ_NestLevel, a0

                jsr     osTickDisableIRQ            // Disable OS Tick interrupt

                sst     IE_BIT                      // Re-enable interrupts
                jsr     osTick_Handler              // Call osTick_Handler
                cst     IE_BIT                      // Disable interrupts

                jsr     osTickEnableIRQ             // Enable OS Tick interrupt

                jsr     ContextSwitch               // Continue in context switcher

                lda     a0, IRQ_NestLevel
                subl    a0, 1                       // Decrement IRQ nesting level
                sta     IRQ_NestLevel, a0

                rsfa    8

                sta     MSP, c7
                mfprs   c7, USP

                popr    FA
                popr    FB
                pop     DP1
                pop     DP2
                mtprs   ILR_PSW, DP1
                mtprs   ILR_PC,  DP2
                pop     DP1
                pop     DP2
                popr    PRW
                popr    CLR
                popr    SMC
                popr    LC
                rti
                .size   SysTick_Handler, .-SysTick_Handler


                .type   ContextSwitch, %function
                .global ContextSwitch
ContextSwitch:
                lda     a0, IRQ_NestLevel           // Load IRQ nesting level
                cmpl    a0, 1                       // Check interrupt nesting level
                bne     ContextExit                 // Nesting interrupts, exit context switcher

                lda     a0, osInfo                  // Load osInfo.thread.run.curr to a0
                lda     a1, osInfo + 4              // Load osInfo.thread.run.next to a1
                lda     a2, IRQ_PendSV              // Load IRQ_PendSV to a2

                cmp     a0, a1                      // Check if context switch is required
                bne     ContextCheck                // Not equal, check if context save required
                cmpl    a2, 1                       // Compare IRQ_PendSV value
                bne     ContextExit                 // No post processing (and no context switch requested)

ContextCheck:
                sta     osInfo, a1                  // Store run.next as run.curr
                cmpl    a0, 0                       // Is osInfo.thread.run.curr == 0
                beq     PostProcess                 // Current thread deleted, skip context save

ContextSave:
                pushu   c7
                pushu   c6
                pushu   c5
                pushu   c4
                pushu   c3
                pushu   c2
                pushu   c1
                pushu   c0
                mov     c0, a0
                mfprs   dp1, USP
                std     (c0), dp1

PostProcess:
                cmpl    a2, 1                       // Compare IRQ_PendSV value
                bne     ContextRestore              // Skip post processing if not pending

                pushr   CLR
                srfb    2

                mov     b0, c7
                movl    a4, 4
                and     b0, a4
                sub     c7, b0                      // Adjust stack to ensure 8-byte alignment

                jsr     osTickDisableIRQ            // Disable OS Tick interrupt

                movl    b1, 0                       // Set PendSV clear value
                jmp     PendCheck

PendExec:
                sta     IRQ_PendSV, b1              // Clear PendSV flag
                sst     IE_BIT                      // Re-enable interrupts
                jsr     osPendSV_Handler            // Post process pending objects
                cst     IE_BIT                      // Disable interrupts

PendCheck:
                lda     a1, osInfo + 4              // Load osInfo.thread.run.next to a1
                sta     osInfo, a1                  // Store run.next as run.curr
                lda     a2, IRQ_PendSV              // Load IRQ_PendSV to a2
                cmpl    a2, 1                       // Compare IRQ_PendSV value
                beq     PendExec                    // Branch to PendExec if PendSV is set

                jsr     osTickEnableIRQ             // Enable OS Tick interrupt

                add     c7, b0                      // Restore stack adjustment

                rsfb    2
                popr    CLR

ContextRestore:
                lda     c0, osInfo
                ldd     dp1, (c0)
                mtprs   USP, dp1
                popu    c0
                popu    c1
                popu    c2
                popu    c3
                popu    c4
                popu    c5
                popu    c6
                addl    dp1, 0x20
                mtprs   USP, dp1

ContextExit:
                rts
                .size   ContextSwitch, .-ContextSwitch

/*-----------------------------------------------------------------------------
 * Helper functions
 *----------------------------------------------------------------------------*/

                .section ".text"

                .type   GetModeCPU, %function
                .global GetModeCPU
GetModeCPU:
                mfprs   a0, PSW
                rts
                .size   GetModeCPU, .-GetModeCPU


                .type   DisableIRQ, %function
                .global DisableIRQ
DisableIRQ:
                mfprs   a0, PSW
                cst     IE_BIT
                rts
                .size   DisableIRQ, .-DisableIRQ


                .type   RestoreIRQ, %function
                .global RestoreIRQ
RestoreIRQ:
                movls   a1, IE_BIT
                and     a0, a1
                beq     1$
                sst     IE_BIT
1$:
                rts
                .size   RestoreIRQ, .-RestoreIRQ


                .end
