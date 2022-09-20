;/*
; * Copyright (C) 2017-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

                PRESERVE8
                THUMB


                AREA     |.constdata|, DATA, READONLY
                EXPORT   irqLib
irqLib          DCB      0                      ; Non weak library reference


                AREA     |.text|, CODE, READONLY


SVC_Handler     PROC
                EXPORT   SVC_Handler
                IMPORT   osInfo

                MOV      R0,LR
                LSRS     R0,R0,#3               ; Determine return stack from EXC_RETURN bit 2
                BCC      SVC_MSP                ; Branch if return stack is MSP
                MRS      R0,PSP                 ; Get PSP

SVC_Number
                LDR      R1,[R0,#24]            ; Load saved PC from stack
                SUBS     R1,R1,#2               ; Point to SVC instruction
                LDRB     R1,[R1]                ; Load SVC number
                CMP      R1,#0
                BNE      SVC_Exit               ; Branch if not SVC 0

                PUSH     {R0,LR}                ; Save SP and EXC_RETURN
                LDMIA    R0,{R0-R3}             ; Load function parameters from stack
                BLX      R7                     ; Call service function
                POP      {R2,R3}                ; Restore SP and EXC_RETURN
                STR      R0,[R2]                ; Store function return values
                MOV      LR,R3                  ; Set EXC_RETURN

SVC_Context
                LDR      R3,=osInfo             ; Load address of osInfo
                LDMIA    R3!,{R1,R2}            ; Load osInfo.thread.run: curr & next
                CMP      R1,R2                  ; Check if thread switch is required
                BEQ      SVC_Exit               ; Branch when threads are the same

                CMP      R1,#0
                BEQ      SVC_ContextSwitch      ; Branch if running thread is deleted

SVC_ContextSave
                MRS      R0,PSP                 ; Get PSP
                SUBS     R0,R0,#32              ; Allocate space for r4-r11
                STR      R0,[R1]                ; Store SP
                STMIA    R0!,{R4-R7}            ; Save R4..R7
                MOV      R4,R8
                MOV      R5,R9
                MOV      R6,R10
                MOV      R7,R11
                STMIA    R0!,{R4-R7}            ; Save R8..R11

SVC_ContextSwitch
                SUBS     R3,R3,#8               ; Adjust address
                STR      R2,[R3]                ; osInfo.thread.run: curr = next

SVC_ContextRestore
                LDR      R0,[R2]                ; Load SP
                ADDS     R0,R0,#16              ; Adjust address
                LDMIA    R0!,{R4-R7}            ; Restore R8..R11
                MOV      R8,R4
                MOV      R9,R5
                MOV      R10,R6
                MOV      R11,R7
                MSR      PSP,R0                 ; Set PSP
                SUBS     R0,R0,#32              ; Adjust address
                LDMIA    R0!,{R4-R7}            ; Restore R4..R7

                LDR      R0,[R2,#4]             ; Load EXC_RETURN value
                BX       R0                     ; Exit from handler

SVC_MSP
                MRS      R0,MSP                 ; Get MSP
                B        SVC_Number

SVC_Exit
                BX       LR                     ; Exit from handler

                ALIGN
                ENDP


PendSV_Handler  PROC
                EXPORT   PendSV_Handler
                IMPORT   osPendSV_Handler

                PUSH     {R0,LR}                ; Save EXC_RETURN
                BL       osPendSV_Handler       ; Call osPendSV_Handler
                POP      {R0,R1}                ; Restore EXC_RETURN
                MOV      LR,R1                  ; Set EXC_RETURN
                B        SVC_Context

                ALIGN
                ENDP


SysTick_Handler PROC
                EXPORT   SysTick_Handler
                IMPORT   osTick_Handler

                PUSH     {R0,LR}                ; Save EXC_RETURN
                BL       osTick_Handler         ; Call osTick_Handler
                POP      {R0,R1}                ; Restore EXC_RETURN
                MOV      LR,R1                  ; Set EXC_RETURN
                B        SVC_Context

                ALIGN
                ENDP


                END
