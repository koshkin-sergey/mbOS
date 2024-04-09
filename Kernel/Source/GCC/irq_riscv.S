/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

                .section ".rodata"
                .global  irqLib                     // Non weak library reference
irqLib:
                .byte    0


                .section ".text.os.handlers"
                .align   2

                .type    SVC_Handler, %function
                .global  SVC_Handler
SVC_Handler:
                csrr  tp, mscratch

                lw    t0, 10 * 4(tp)
                addi  t0, t0, 4
                sw    t0, 10 * 4(tp)

SVC_FuncCall:
                lw    a0,  0 * 4(tp)
                lw    a1,  1 * 4(tp)
                lw    a2,  2 * 4(tp)
                lw    a3,  3 * 4(tp)
                lw    a5,  5 * 4(tp)

                addi  sp, sp, -4
                sw    ra, 0(sp)
                jalr  a5
                lw    ra, 0(sp)
                addi  sp, sp, +4

                sw    a0,  0 * 4(tp)              // Store function return values
SVC_ContextCheck:
                la    a0, osInfo                  // Load address of osInfo
                lw    a1, 0(a0)                   // Load osInfo.thread.run.curr to a1
                lw    a2, 4(a0)                   // Load osInfo.thread.run.next to a2
                beq   a1, a2, SVC_Exit            // Exit when threads are the same
                beqz  a1, SVC_ContextSwitch       // Branch if running thread is deleted
SVC_ContextSave:
                csrr  tp, mscratch
#ifndef __riscv_32e
                addi  tp, tp, -10 * 4
                sw    s2,  0 * 4(tp)
                sw    s3,  1 * 4(tp)
                sw    s4,  2 * 4(tp)
                sw    s5,  3 * 4(tp)
                sw    s6,  4 * 4(tp)
                sw    s7,  5 * 4(tp)
                sw    s8,  6 * 4(tp)
                sw    s9,  7 * 4(tp)
                sw    s10, 8 * 4(tp)
                sw    s11, 9 * 4(tp)
#endif /* __riscv_32e */
                addi  tp, tp, -2 * 4
                sw    s0, 0 * 4(tp)
                sw    s1, 1 * 4(tp)
                sw    tp, 0(a1)
SVC_ContextSwitch:
                sw    a2, 0(a0)
SVC_ContextRestore:
                lw    tp, 0(a2)
                lw    s0, 0 * 4(tp)
                lw    s1, 1 * 4(tp)
                addi  tp, tp, 2 * 4
#ifndef __riscv_32e
                lw    s2,  0 * 4(tp)
                lw    s3,  1 * 4(tp)
                lw    s4,  2 * 4(tp)
                lw    s5,  3 * 4(tp)
                lw    s6,  4 * 4(tp)
                lw    s7,  5 * 4(tp)
                lw    s8,  6 * 4(tp)
                lw    s9,  7 * 4(tp)
                lw    s10, 8 * 4(tp)
                lw    s11, 9 * 4(tp)
                addi  tp, tp, 10 * 4
#endif /* __riscv_32e */
SVC_Exit:
                csrw  mscratch, tp
                ret

                .size    SVC_Handler, .-SVC_Handler


                .type    SysTick_Handler, %function
                .global  SysTick_Handler
SysTick_Handler:

                addi  sp, sp, -8
                sw    ra, 4(sp)
                call  osTick_Handler
                lw    ra, 4(sp)
                addi  sp, sp, +8
                j     SVC_ContextCheck

                .size    SysTick_Handler, .-SysTick_Handler


                .type    PendSV_Handler, %function
                .global  PendSV_Handler
PendSV_Handler:

                addi  sp, sp, -8
                sw    ra, 4(sp)
                call  osPendSV_Handler
                call  IRQ_ClearSWI
                lw    ra, 4(sp)
                addi  sp, sp, +8
                j     SVC_ContextCheck

                .size    PendSV_Handler, .-PendSV_Handler

                .end
