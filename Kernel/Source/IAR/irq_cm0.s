;/*
; * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
; * All rights reserved
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; *
; * Project: uKernel real-time kernel
; */

                NAME      irq_cm0.s

                PRESERVE8
                SECTION   .rodata:DATA:NOROOT(2)


                EXPORT    irqLib
irqLib          DCB       0                   ; Non weak library reference


                SECTION   .text:CODE:NOROOT(2)
                THUMB

PendSV_Handler
                EXPORT    PendSV_Handler
                IMPORT    osInfo

                LDR       R3,=osInfo          ; in R3 - =run_task
                LDM       R3!,{R1,R2}         ; in R1 - current run task, in R2 - next run task
                CMP       R1,R2               ; Check if thread switch is required
                BEQ       Context_Exit        ; Exit when threads are the same

                CMP       R1,#0
                BEQ       Context_Switch      ; Branch if running thread is deleted
ContextSave
                MRS       R0,PSP              ; in PSP - process(task) stack pointer
                SUBS      R0,#32              ; allocate space for r4-r11
                STR       R0,[R1]             ; save own SP in TCB
                STMIA     R0!,{R4-R7}
                MOV       R4,R8
                MOV       R5,R9
                MOV       R6,R10
                MOV       R7,R11
                STMIA     R0!,{R4-R7}
Context_Switch
                SUBS      R3,#8               ; Adjust address
                STR       R2,[R3]             ; in r3 current run task
Context_Restore
                LDR       R0,[R2]             ; in r0 - new task SP
                ADDS      R0,#16              ; Adjust address
                LDMIA     R0!,{R4-R7}         ; Restore R8..R11
                MOV       R8,R4
                MOV       R9,R5
                MOV       R10,R6
                MOV       R11,R7
                MSR       PSP,R0              ; Set PSP
                SUBS      R0,#32              ; Adjust address
                LDMIA     R0!,{R4-R7}         ; Restore R4..R7

                LDR       R0,=0xFFFFFFFD      ; Set EXC_RETURN value
                BX        R0                  ; Exit from handler
Context_Exit
                BX        LR                  ; Exit from handler


SVC_Handler
                EXPORT    SVC_Handler

                MOV       R0,LR
                LSRS      R0,R0,#3            ; Determine return stack from EXC_RETURN bit 2
                BCC       SVC_MSP             ; Branch if return stack is MSP
                MRS       R0,PSP              ; Get PSP
SVC_Number
                LDR       R1,[R0,#24]         ; Read Saved PC from Stack
                SUBS      R1,R1,#2            ; Point to SVC Instruction
                LDRB      R1,[R1]             ; Load SVC Number
                CMP       R1,#0
                BNE       SVC_Exit            ; User SVC Number > 0

                PUSH      {R0,LR}             ; Save SP and EXC_RETURN
                LDMIA     R0,{R0-R3}          ; Read R0-R3 from stack
                BLX       R7                  ; Call service function
                POP       {R2,R3}             ; Restore SP and EXC_RETURN
                STMIA     R2!,{R0-R1}         ; Store return values
                MOV       LR,R3               ; Set EXC_RETURN
SVC_Exit
                BX        LR                  ; Exit from handler
SVC_MSP
                MRS       R0,MSP              ; Get MSP
                B         SVC_Number


SysTick_Handler
                EXPORT    SysTick_Handler
                IMPORT    osTick_Handler

                PUSH      {R0,LR}             ; Save EXC_RETURN
                BL        osTick_Handler      ; Call osTick_Handler
                POP       {R0,R1}             ; Restore EXC_RETURN
                MOV       LR,R1               ; Set EXC_RETURN
                BX        LR                  ; Exit from handler


                END
