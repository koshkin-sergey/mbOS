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

                .equ   K_STATE_RUNNING, 2           // osKernelState_t::osKernelRunning
                .equ   I_K_STATE_OFS,   16          // osInfo.kernel.state offset

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


                .section ".text.os.handlers"
                .align   2


                .type    ECM_Handler, %function
                .global  ECM_Handler
ECM_Handler:

                j   ECM_Handler
                .size    ECM_Handler, .-ECM_Handler

                .end
