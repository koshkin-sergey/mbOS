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
                .global  IRQ_PendSV
IRQ_NestLevel:
                .word    0                          // IRQ nesting level counter
IRQ_PendSV:
                .byte    0                          // Pending SVC flag



/*-----------------------------------------------------------------------------
 * Helper functions
 *----------------------------------------------------------------------------*/

                .section ".text"

                .type   GetModeCPU, %function
                .global GetModeCPU
GetModeCPU:
                MFPRS   A0, PSW
                MOVLL   A1, 0x300
                AND     A0, A1
                RTS
                .size   GetModeCPU, .-GetModeCPU


                .type   DisableIRQ, %function
                .global DisableIRQ
DisableIRQ:
                MFPRS   A0, PSW
                CST     IE_BIT
                RTS
                .size   DisableIRQ, .-DisableIRQ


                .type   RestoreIRQ, %function
                .global RestoreIRQ
RestoreIRQ:
                MOVLS   A1, IE_BIT
                AND     A0, A1
                BEQ     1$
                SST     IE_BIT
1$:
                RTS
                .size   RestoreIRQ, .-RestoreIRQ


                .end
