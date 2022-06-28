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

                .equ   IE_BIT,          0x10        // When IE bit is set, IRQ is enabled

                .equ   K_STATE_RUNNING, 2           // osKernelState_t::osKernelRunning
                .equ   I_K_STATE_OFS,   16          // osInfo.kernel.state offset
                .equ   I_TICK_IRQN_OFS, 24          // osInfo.tick_irqn offset

                .section ".rodata"

                .global  irqLib                     // Non weak library reference
irqLib:
                .byte    0

                .section ".data"

                .global  IRQ_NestLevel
IRQ_NestLevel:
                .long    0                          // IRQ nesting level counter

                .global  IRQ_PendSV
IRQ_PendSV:
                .byte    0                          // Pending SVC flag


                .section ".text.os.handlers"

                .type   SWI_Handler, %function
                .global SWI_Handler
SWI_Handler:
                cst     0x10                        // Disable interrupts
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
                ldrzs   FB, lo(__SWI_FB_Base)
                ldrzs   FA, lo(__SWI_FA_Base)

                lda     a0, IRQ_NestLevel
                addl    a0, 1                       // Increment IRQ nesting level
                sta     IRQ_NestLevel, a0

                push    c0
                push    c1
                lds     c0, 2
                lddo    a0, (c0), 0
                lddo    a1, (c0), 4
                lddo    a2, (c0), 8
                lddo    a3, (c0), 12
                lddo    c1, (c0), 16
                pushr   CLR
                ijsr    c1
                std     (c0), a0
                popr    CLR
                pop     c1
                pop     c0

                jsr     ContextSwitch               // Continue in context switcher

                lda     a0, IRQ_NestLevel
                subl    a0, 1                       // Decrement IRQ nesting level
                sta     IRQ_NestLevel, a0

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
                ldrzs   FB, lo(__IRQ_FB_Base)
                ldrzs   FA, lo(__IRQ_FA_Base)

                lda     a0, IRQ_NestLevel
                addl    a0, 1                       // Increment IRQ nesting level
                sta     IRQ_NestLevel, a0

                mov     a0, c7
                movl    a1, 4
                and     a0, a1
                sub     c7, a0                      // Adjust stack to ensure 8-byte alignment
                push    a1
                push    a0

                pushr   CLR
                jsr     osTick_Handler              // Call osTick_Handler
                popr    CLR

                pop     a0
                pop     a1
                add     c7, a0                      // Unadjust stack

                sst     0x10                        // Re-enable interrupts
                jsr     ContextSwitch               // Continue in context switcher
                cst     0x10                        // Disable interrupts

                lda     a0, IRQ_NestLevel
                subl    a0, 1                       // Decrement IRQ nesting level
                sta     IRQ_NestLevel, a0

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
                lda     a0, IRQ_NestLevel
                cmpl    a0, 1
                bne     ContextExit

                lda     a0, osInfo                  // Load osInfo.thread.run.curr to a0
                lda     a1, osInfo + 4              // Load osInfo.thread.run.next to a1
                lda     a2, IRQ_PendSV              // Load IRQ_PendSV to a2

                cmp     a0, a1                      // Check if context switch is required
                bne     ContextCheck                // Not equal, check if context save required
                cmpl    a2, 1                       // Compare IRQ_PendSV value
                bne     ContextExit                 // No post processing (and no context switch requested)
ContextCheck:
                cmpl    a0, 0                       // Is osInfo.thread.run.curr == 0
                beq     PostProcess                 // Current thread deleted, skip context save
ContextSave:
                pushc   7
                mov     c6, a0
                std     (c6), c7
PostProcess:
                sta     osInfo, a1
ContextRestore:
                mov     c6, a1
                ldd     c7, (c6)
                popc    7
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
