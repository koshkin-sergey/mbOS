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

#ifndef __riscv_32e
#define ContexRegNum              18
#else
#define ContexRegNum              12
#endif

#define CONTEXT_SIZE              (ContexRegNum * 4)

.equ    K_STATE_RUNNING, 2           // osKernelState_t::osKernelRunning
.equ    I_K_STATE_OFS,   16          // osInfo.kernel.state offset

                .section ".rodata"
                .global  irqLib                     // Non weak library reference
irqLib:
                .byte    0

                .section ".data"
                .global  IRQ_NestLevel
IRQ_NestLevel:
                .word    0                          // IRQ nesting level counter

                .global  IRQ_PendSV
IRQ_PendSV:
                .byte    0                          // Pending SVC flag


/**
 * @brief       Macro for context save
 * @details     This macro save ABI defined caller saved registers in the stack.
 * @remarks     This Macro could use to save context when you enter to exception
 *              or interrupt
 */
.macro SAVE_CONTEXT
  addi    sp, sp, -CONTEXT_SIZE
  sw      a0,  0 * 4(sp)
  sw      a1,  1 * 4(sp)
  sw      a2,  2 * 4(sp)
  sw      a3,  3 * 4(sp)
  sw      a4,  4 * 4(sp)
  sw      a5,  5 * 4(sp)
  sw      t0,  6 * 4(sp)
  sw      t1,  7 * 4(sp)
  sw      t2,  8 * 4(sp)
  sw      ra,  9 * 4(sp)
  csrr    t0, mepc
  sw      t0, 10 * 4(sp)
  csrr    t0, mstatus
  sw      t0, 11 * 4(sp)
#ifndef __riscv_32e
  sw      a6, 12 * 4(sp)
  sw      a7, 13 * 4(sp)
  sw      t3, 14 * 4(sp)
  sw      t4, 15 * 4(sp)
  sw      t5, 16 * 4(sp)
  sw      t6, 17 * 4(sp)
#endif /* __riscv_32e */
.endm

/**
 * @brief       Macro for restore caller registers
 * @details     This macro restore ABI defined caller saved registers from stack.
 * @remarks     You could use this macro to restore context before you want return
 *              from interrupt or exeception
 */
.macro RESTORE_CONTEXT
  lw      t0, 11 * 4(sp)
  csrw    mstatus, t0
  lw      t0, 10 * 4(sp)
  csrw    mepc, t0
  lw      a0,  0 * 4(sp)
  lw      a1,  1 * 4(sp)
  lw      a2,  2 * 4(sp)
  lw      a3,  3 * 4(sp)
  lw      a4,  4 * 4(sp)
  lw      a5,  5 * 4(sp)
  lw      t0,  6 * 4(sp)
  lw      t1,  7 * 4(sp)
  lw      t2,  8 * 4(sp)
  lw      ra,  9 * 4(sp)
#ifndef __riscv_32e
  lw      a6, 12 * 4(sp)
  lw      a7, 13 * 4(sp)
  lw      t3, 14 * 4(sp)
  lw      t4, 15 * 4(sp)
  lw      t5, 16 * 4(sp)
  lw      t6, 17 * 4(sp)
#endif /* __riscv_32e */
  addi    sp, sp, CONTEXT_SIZE
.endm

                .section ".text.os.handlers"
                .align   2

                .type    exc_entry, %function
                .global  exc_entry
exc_entry:

                SAVE_CONTEXT

                csrr    a0, mcause
                jal     IRQ_GetHandler
                beqz    a0, 1f
                jalr    a0
1:

                RESTORE_CONTEXT
                mret
                .size    exc_entry, .-exc_entry

                .type    ECM_Handler, %function
                .global  ECM_Handler
ECM_Handler:

                lw    t0, 10 * 4(sp)
                addi  t0, t0, 4
                sw    t0, 10 * 4(sp)

//                la    t0, osInfo + I_K_STATE_OFS // Load kernel state
//                lw    t0, 0(t0)
//                beqz  t0, 1f
//                csrrw s0, mscratch, s0
//1:
                lw    a0,  0 * 4(sp)
                lw    a1,  1 * 4(sp)
                lw    a2,  2 * 4(sp)
                lw    a3,  3 * 4(sp)
                lw    a5,  5 * 4(sp)

                addi  sp, sp, -4
                sw    ra, 0(sp)
                jalr  a5
                lw    ra, 0(sp)
                addi  sp, sp, +4

                sw    a0,  0 * 4(sp)              // Store function return values
ECM_Context:
                la    a0, osInfo                  // Load address of osInfo
                lw    a1, 0(a0)                   // Load osInfo.thread.run.curr to a1
                lw    a2, 4(a0)                   // Load osInfo.thread.run.next to a2
                beq   a1, a2, ECM_Exit            // Exit when threads are the same
                beqz  a1, ECM_ContextSwitch       // Branch if running thread is deleted
ECM_ContextSave:
#ifndef __riscv_32e
                addi  sp, sp, -10 * 4
                sw    s2,  0 * 4(sp)
                sw    s3,  1 * 4(sp)
                sw    s4,  2 * 4(sp)
                sw    s5,  3 * 4(sp)
                sw    s6,  4 * 4(sp)
                sw    s7,  5 * 4(sp)
                sw    s8,  6 * 4(sp)
                sw    s9,  7 * 4(sp)
                sw    s10, 8 * 4(sp)
                sw    s11, 9 * 4(sp)
#endif /* __riscv_32e */
                addi  sp, sp, -2 * 4
                sw    s0, 0 * 4(sp)
                sw    s1, 1 * 4(sp)
                sw    sp, 0(a1)
ECM_ContextSwitch:
                sw    a2, 0(a0)
ECM_ContextRestore:
                lw    sp, 0(a2)
                lw    s0, 0 * 4(sp)
                lw    s1, 1 * 4(sp)
                addi  sp, sp, 2 * 4
#ifndef __riscv_32e
                lw    s2,  0 * 4(sp)
                lw    s3,  1 * 4(sp)
                lw    s4,  2 * 4(sp)
                lw    s5,  3 * 4(sp)
                lw    s6,  4 * 4(sp)
                lw    s7,  5 * 4(sp)
                lw    s8,  6 * 4(sp)
                lw    s9,  7 * 4(sp)
                lw    s10, 8 * 4(sp)
                lw    s11, 9 * 4(sp)
                addi  sp, sp, 10 * 4
#endif /* __riscv_32e */
ECM_Exit:
                ret

                .size    ECM_Handler, .-ECM_Handler

                .end
