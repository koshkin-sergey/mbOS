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

        .section ".rodata"
        .global  irqLib               // Non weak library reference
irqLib:
        .byte    0


        .thumb
        .section ".text"
        .align   2

        .thumb_func
        .type    PendSV_Handler, %function
        .global  PendSV_Handler
        .fnstart
        .cantunwind
PendSV_Handler:

        LDR       R3,=osInfo          // in R3 - =run_task
        LDM       R3,{R1,R2}          // in R1 - current run task, in R2 - next run task
        CMP       R1,R2               // Check if thread switch is required
        BEQ       Context_Exit        // Exit when threads are the same

        CBZ       R1,Context_Switch   // Branch if running thread is deleted

ContextSave:
        MRS       R0,PSP              // in PSP - process(task) stack pointer
        STMDB     R0!,{R4-R11}
        STR       R0,[R1]             // save own SP in TCB

Context_Switch:
        STR       R2,[R3]             // in r3 - =tn_curr_run_task

Context_Restore:
        LDR       R0,[R2]             // in r0 - new task SP
        LDMIA     R0!,{R4-R11}
        MSR       PSP,R0

        MVN       LR,#~0xFFFFFFFD     // Set EXC_RETURN value

Context_Exit:
        BX        LR                  // Exit from handler

        .fnend
        .size    PendSV_Handler, .-PendSV_Handler


        .thumb_func
        .type    SVC_Handler, %function
        .global  SVC_Handler
        .fnstart
        .cantunwind
SVC_Handler:

        TST       LR,#0x04            // Determine return stack from EXC_RETURN bit 2
        ITE       EQ
        MRSEQ     R0,MSP              // Get MSP if return stack is MSP
        MRSNE     R0,PSP              // Get PSP if return stack is PSP

        LDR       R1,[R0,#24]         // Read Saved PC from Stack
        LDRB      R1,[R1,#-2]         // Load SVC Number
        CBNZ      R1,SVC_Exit

        PUSH      {R0,LR}             // Save SP and EXC_RETURN
        LDM       R0,{R0-R3,R12}      // Read R0-R3,R12 from stack
        BLX       R12                 // Call SVC Function
        POP       {R12,LR}            // Restore SP and EXC_RETURN
        STM       R12,{R0-R1}         // Store return values

SVC_Exit:
        BX        LR                  // Exit from handler

        .fnend
        .size    SVC_Handler, .-SVC_Handler


        .thumb_func
        .type    SysTick_Handler, %function
        .global  SysTick_Handler
        .fnstart
        .cantunwind
SysTick_Handler:

        PUSH     {R0,LR}                // Save EXC_RETURN
        BL       osTick_Handler         // Call osTick_Handler
        POP      {R0,LR}                // Restore EXC_RETURN
        BX       LR                     // Exit from handler

        .fnend
        .size    SysTick_Handler, .-SysTick_Handler


        .end
