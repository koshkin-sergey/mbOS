/*
 * Copyright (C) 2024-2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef __riscv_32e

#define STACK_RESERVE       16

.macro CONTEXT_SAVE
                addi  tp, tp, -12 * 4
                sw    s0,   0 * 4(tp)
                sw    s1,   1 * 4(tp)
                sw    s2,   2 * 4(tp)
                sw    s3,   3 * 4(tp)
                sw    s4,   4 * 4(tp)
                sw    s5,   5 * 4(tp)
                sw    s6,   6 * 4(tp)
                sw    s7,   7 * 4(tp)
                sw    s8,   8 * 4(tp)
                sw    s9,   9 * 4(tp)
                sw    s10, 10 * 4(tp)
                sw    s11, 11 * 4(tp)
.endm

.macro CONTEXT_RESTORE
                lw    s0,   0 * 4(tp)
                lw    s1,   1 * 4(tp)
                lw    s2,   2 * 4(tp)
                lw    s3,   3 * 4(tp)
                lw    s4,   4 * 4(tp)
                lw    s5,   5 * 4(tp)
                lw    s6,   6 * 4(tp)
                lw    s7,   7 * 4(tp)
                lw    s8,   8 * 4(tp)
                lw    s9,   9 * 4(tp)
                lw    s10, 10 * 4(tp)
                lw    s11, 11 * 4(tp)
                addi  tp, tp, 12 * 4
.endm

#else

#define STACK_RESERVE       4

.macro CONTEXT_SAVE
                addi  tp, tp, -2 * 4
                sw    s0, 0 * 4(tp)
                sw    s1, 1 * 4(tp)
.endm

.macro CONTEXT_RESTORE
                lw    s0, 0 * 4(tp)
                lw    s1, 1 * 4(tp)
                addi  tp, tp, 2 * 4
.endm

#endif

                .section ".rodata"
                .global  irqLib                     // Non weak library reference
irqLib:
                .byte    0


                .section ".text.os.handlers"
                .align   2

                .type    SVC_Handler, %function
                .global  SVC_Handler
SVC_Handler:
                addi  sp, sp, -STACK_RESERVE
                sw    ra, 0(sp)

                lw    t0, 10 * 4(tp)
                addi  t0, t0, 4
                sw    t0, 10 * 4(tp)

SVC_FuncCall:
                lw    a0,  0 * 4(tp)
                lw    a1,  1 * 4(tp)
                lw    a2,  2 * 4(tp)
                lw    a3,  3 * 4(tp)
                lw    a5,  5 * 4(tp)

                jalr  a5

                sw    a0,  0 * 4(tp)              // Store function return values
SVC_ContextCheck:
                la    a0, osInfo                  // Load address of osInfo
                lw    a1, 0(a0)                   // Load osInfo.thread.run.curr to a1
                lw    a2, 4(a0)                   // Load osInfo.thread.run.next to a2
                beq   a1, a2, SVC_Exit            // Exit when threads are the same
                beqz  a1, SVC_ContextSwitch       // Branch if running thread is deleted
SVC_ContextSave:
                CONTEXT_SAVE
                sw    tp, 0(a1)
SVC_ContextSwitch:
                sw    a2, 0(a0)
SVC_ContextRestore:
                lw    tp, 0(a2)
                CONTEXT_RESTORE
SVC_Exit:
                lw    ra, 0(sp)
                addi  sp, sp, +STACK_RESERVE
                ret

                .size    SVC_Handler, .-SVC_Handler


                .type    SysTick_Handler, %function
                .global  SysTick_Handler
SysTick_Handler:

                addi  sp, sp, -STACK_RESERVE
                sw    ra, 0(sp)
                call  osTick_Handler
                j     SVC_ContextCheck

                .size    SysTick_Handler, .-SysTick_Handler


                .type    PendSV_Handler, %function
                .global  PendSV_Handler
PendSV_Handler:

                addi  sp, sp, -STACK_RESERVE
                sw    ra, 0(sp)
                call  osPendSV_Handler
                call  IRQ_ClearSWI
                j     SVC_ContextCheck

                .size    PendSV_Handler, .-PendSV_Handler

                .end
