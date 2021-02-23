;/*
; * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
; * Project: mbOS real-time kernel
; */

                NAME    irq_cm4f.s


                PRESERVE8
                SECTION .rodata:DATA:NOROOT(2)


                EXPORT   irqLib
irqLib          DCB      0                      ; Non weak library reference


                THUMB
                SECTION .text:CODE:NOROOT(2)


SVC_Handler
                EXPORT   SVC_Handler
                IMPORT   osInfo

                TST      LR,#0x04               ; Determine return stack from EXC_RETURN bit 2
                ITE      EQ
                MRSEQ    R0,MSP                 ; Get MSP if return stack is MSP
                MRSNE    R0,PSP                 ; Get PSP if return stack is PSP

                LDR      R1,[R0,#24]            ; Load saved PC from stack
                LDRB     R1,[R1,#-2]            ; Load SVC number
                CBNZ     R1,SVC_Exit            ; Branch if not SVC 0

                PUSH     {R0,LR}                ; Save SP and EXC_RETURN
                LDM      R0,{R0-R3,R12}         ; Load function parameters and address from stack
                BLX      R12                    ; Call service function
                POP      {R12,LR}               ; Restore SP and EXC_RETURN
                STM      R12,{R0-R1}            ; Store function return values

SVC_Context
                LDR      R3,=osInfo             ; Load address of osInfo
                LDM      R3,{R1,R2}             ; Load osInfo.thread.run: curr & next
                CMP      R1,R2                  ; Check if thread switch is required
                IT       EQ
                BXEQ     LR                     ; Exit when threads are the same

                CBNZ     R1,SVC_ContextSave     ; Branch if running thread is not deleted
                TST      LR,#0x10               ; Check if extended stack frame
                BNE      SVC_ContextSwitch
                LDR      R1,=0xE000EF34         ; FPCCR Address
                LDR      R0,[R1]                ; Load FPCCR
                BIC      R0,R0,#1               ; Clear LSPACT (Lazy state)
                STR      R0,[R1]                ; Store FPCCR
                B        SVC_ContextSwitch

SVC_ContextSave
                STMDB    R12!,{R4-R11}          ; Save R4..R11
                TST      LR,#0x10               ; Check if extended stack frame
                IT       EQ
                VSTMDBEQ R12!,{S16-S31}         ; Save VFP S16.S31
                STR      R12,[R1]               ; Store SP
                STR      LR, [R1,#4]            ; Store stack frame information

SVC_ContextSwitch
                STR      R2,[R3]                ; osInfo.thread.run: curr = next

SVC_ContextRestore
                LDR      R0,[R2]                ; Load SP
                LDR      LR,[R2,#4]             ; Load EXC_RETURN value
                TST      LR,#0x10               ; Check if extended stack frame
                IT       EQ
                VLDMIAEQ R0!,{S16-S31}          ; Restore VFP S16..S31
                LDMIA    R0!,{R4-R11}           ; Restore R4..R11
                MSR      PSP,R0                 ; Set PSP

SVC_Exit
                BX       LR                     ; Exit from handler


PendSV_Handler
                EXPORT   PendSV_Handler
                IMPORT   osPendSV_Handler

                PUSH     {R0,LR}                ; Save EXC_RETURN
                BL       osPendSV_Handler       ; Call osPendSV_Handler
                POP      {R0,LR}                ; Restore EXC_RETURN
                MRS      R12,PSP
                B        SVC_Context


SysTick_Handler
                EXPORT   SysTick_Handler
                IMPORT   osTick_Handler

                PUSH     {R0,LR}                ; Save EXC_RETURN
                BL       osTick_Handler         ; Call osTick_Handler
                POP      {R0,LR}                ; Restore EXC_RETURN
                MRS      R12,PSP
                B        SVC_Context


                END
