;/*
; * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
; * All rights reserved
; *
; * Licensed under the Apache License, Version 2.0 (the "License");
; * you may not use this file except in compliance with the License.
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

MODE_IRQ        EQU      0x12
MODE_SVC        EQU      0x13

I_BIT           EQU      0x80                       ; When I bit is set, IRQ is disabled
F_BIT           EQU      0x40                       ; When F bit is set, FIQ is disabled

K_STATE_RUNNING EQU      2                          ; osKernelState_t::osKernelRunning
I_K_STATE_OFS   EQU      16                         ; osInfo.kernel.state offset
I_TICK_IRQN_OFS EQU      24                         ; osInfo.tick_irqn offset

                PRESERVE8


                AREA     |.constdata|, DATA, READONLY
                EXPORT   irqLib
irqLib          DCB      0                          ; Non weak library reference

                AREA     |.data|, DATA, READWRITE
                EXPORT   IRQ_PendSV
IRQ_NestLevel   DCD      0                          ; IRQ nesting level counter
IRQ_PendSV      DCB      0                          ; Pending SVC flag


                AREA     |.text|, CODE, READONLY
                ARM

SWI_Handler\
                PROC
                EXPORT  SWI_Handler
                IMPORT  IRQ_Disable
                IMPORT  IRQ_Enable
                IMPORT  osInfo

                SUB     SP, SP, #(2*4)              ; Make room for stacking SPSR_svc, LR_svc
                PUSH    {R0-R3, R12, LR}            ; Save APCS corruptible registers to SVC stack
                ADD     R0, SP, #(6*4)              ; Adjust SP_svc to R0
                MOV     R1, LR                      ; Move LR_svc to R1
                MRS     R12, SPSR                   ; Move SPSR_svc to R12
                STMIA   R0, {R1, R12}               ; Save SPSR_svc and LR_svc to SVC stack

                LDR     R0, =IRQ_NestLevel
                LDR     R1, [R0]
                ADD     R1, R1, #1                  ; Increment IRQ nesting level
                STR     R1, [R0]

                LDR     R0, =osInfo
                LDR     R1, [R0, #I_K_STATE_OFS]    ; Load kernel state
                CMP     R1, #K_STATE_RUNNING        ; Check osKernelRunning
                BLT     SWI_FuncCall                ; Continue if kernel is not running
                LDR     R0, [R0, #I_TICK_IRQN_OFS]  ; Load OS Tick irqn
                LDR     R12, =IRQ_Disable
                MOV     LR, PC
                BX      R12                         ; Disable OS Tick interrupt

SWI_FuncCall
                POP     {R0-R3}
                LDR     R12, [SP]

                MSR     CPSR_c, #MODE_SVC           ; Re-enable interrupts
                MOV     LR, PC
                BX      R12                         ; Branch to SVC function
                MSR     CPSR_c,#(MODE_SVC:OR:I_BIT) ; Disable interrupts

                SUB     SP, SP, #4
                STM     SP, {SP}^                   ; Store SP_usr onto stack
                NOP
                POP     {R12}                       ; Pop SP_usr into R12
                SUB     R12, R12, #16               ; Adjust pointer to SP_usr
                LDMDB   R12, {R2,R3}                ; Load return values from SVC function
                PUSH    {R0-R3}                     ; Push return values to stack

                LDR     R0, =osInfo
                LDR     R1, [R0, #I_K_STATE_OFS]    ; Load kernel state
                CMP     R1, #K_STATE_RUNNING        ; Check osKernelRunning
                BLT     SWI_ContextCheck            ; Continue if kernel is not running
                LDR     R0, [R0, #I_TICK_IRQN_OFS]  ; Load OS Tick irqn
                LDR     R12, =IRQ_Enable
                MOV     LR, PC
                BX      R12                         ; Enable OS Tick interrupt

SWI_ContextCheck
                BL      ContextSwitch               ; Continue in context switcher

                LDR     R0, =IRQ_NestLevel
                LDR     R1, [R0]
                SUB     R1, R1, #1                  ; Decrement IRQ nesting level
                STR     R1, [R0]

                MOV     R0, SP                      ; Move SP_svc to R0
                ADD     SP, SP, #(8*4)              ; Fake unstacking 8 registers from SP_svc
                LDR     R1, [R0, #(7*4)]            ; Restore SPSR_svc in R1
                MSR     SPSR_cxsf, R1               ; Move R1 to SPSR_svc
                LDMFD   R0, {R0-R3, R12, LR, PC}^   ; Restore stacked APCS registers and return from IRQ handler

                ENDP


IRQ_Handler\
                PROC
                EXPORT  IRQ_Handler
                IMPORT  IRQ_GetActiveIRQ
                IMPORT  IRQ_GetHandler
                IMPORT  IRQ_EndOfInterrupt

                MOV     SP, R0                      ; Save R0 in SP_irq
                SUB     R0, LR, #4                  ; Put return address in R0
                MOV     LR, R1                      ; Save R1 in LR_irq
                MRS     R1, SPSR                    ; Put the SPSR_irq in R1
                MSR     CPSR_c,#(MODE_SVC:OR:I_BIT) ; Switch to Supervisor mode, IRQ disabled
                STMFD   SP!, {R0,R1}                ; Save SPSR_irq and LR_irq to SVC stack
                STMFD   SP!, {R2,R3,R12,LR}         ; Save APCS corruptible registers to SVC stack
                MOV     R0, SP                      ; Make the SP_svc visible to IRQ mode
                SUB     SP, SP, #(2*4)              ; Make room for stacking R0, R1
                MSR     CPSR_c,#(MODE_IRQ:OR:I_BIT) ; Switch to IRQ mode, IRQ disabled
                STMFD   R0, {SP,LR}                 ; Save R0, R1 to SVC stack
                MSR     CPSR_c,#(MODE_SVC:OR:I_BIT) ; Switch to Supervisor mode, IRQ disabled

                LDR     R0, =IRQ_NestLevel
                LDR     R1, [R0]
                ADD     R1, R1, #1                  ; Increment IRQ nesting level
                STR     R1, [R0]

                MOV     R3, SP                      ; Move SP into R3
                AND     R3, R3, #4                  ; Get stack adjustment to ensure 8-byte alignment
                SUB     SP, SP, R3                  ; Adjust stack
                STMFD   SP!, {R3, R4}               ; Store stack adjustment(R3) and user data(R4)

                LDR     R12, =IRQ_GetActiveIRQ
                MOV     LR, PC
                BX      R12                         ; Retrieve interrupt ID into R0
                MOV     R4, R0                      ; Move interrupt ID to R4

                LDR     R12, =IRQ_GetHandler
                MOV     LR, PC
                BX      R12                         ; Retrieve interrupt handler address for current ID
                CMP     R0, #0                      ; Check if handler address is 0
                BEQ     IRQ_End                     ; If 0, end interrupt and return

                MSR     CPSR_c, #MODE_SVC           ; Re-enable interrupts
                MOV     LR, PC
                BX      R0                          ; Call IRQ handler
                MSR     CPSR_c,#(MODE_SVC:OR:I_BIT) ; Disable interrupts

IRQ_End
                MOV     R0, R4                      ; Move interrupt ID to R0
                LDR     R12, =IRQ_EndOfInterrupt
                MOV     LR, PC
                BX      R12                         ; Signal end of interrupt

                LDMFD   SP!, {R3, R4}               ; Restore stack adjustment(R3) and user data(R4)
                ADD     SP, SP, R3                  ; Unadjust stack

                BL      ContextSwitch               ; Continue in context switcher

                LDR     R0, =IRQ_NestLevel
                LDR     R1, [R0]
                SUBS    R1, R1, #1                  ; Decrement IRQ nesting level
                STR     R1, [R0]

                MOV     R0, SP                      ; Move SP_svc to R0
                ADD     SP, SP, #(8*4)              ; Fake unstacking 8 registers from SP_svc
                LDR     R1, [R0, #(7*4)]            ; Restore SPSR_irq in R1
                MSR     SPSR_cxsf, R1               ; Move SPSR_irq to SPSR_svc
                LDMFD   R0, {R0-R3, R12, LR, PC}^   ; Restore stacked APCS registers and return from IRQ handler

                ENDP


ContextSwitch\
                PROC
                EXPORT  ContextSwitch
                IMPORT  osPendSV_Handler
                IMPORT  osInfo
                IMPORT  IRQ_Disable
                IMPORT  IRQ_Enable

                PUSH    {LR}

                LDR     R0, =IRQ_NestLevel          ; Check interrupt nesting level
                LDR     R1, [R0]                    ; Load IRQ nest level
                CMP     R1, #1
                BNE     ContextExit                 ; Nesting interrupts, exit context switcher

                LDR     R12, =osInfo                ; Load address of osInfo.run
                LDM     R12, {R0, R1}               ; Load osInfo.thread.run: curr & next
                LDR     R2, =IRQ_PendSV             ; Load address of IRQ_PendSV flag
                LDRB    R3, [R2]                    ; Load PendSV flag

                CMP     R0, R1                      ; Check if context switch is required
                BNE     ContextCheck                ; Not equal, check if context save required
                CMP     R3, #1                      ; Compare IRQ_PendSV value
                BNE     ContextExit                 ; No post processing (and no context switch requested)

ContextCheck
                STR     R1, [R12]                   ; Store run.next as run.curr
                ; R0 = curr, R1 = next, R2 = &IRQ_PendSV, R3 = IRQ_PendSV, R12 = &osInfo.thread.run
                PUSH    {R1-R3, R12}
                CMP     R0, #0                      ; Is osInfo.thread.run.curr == 0
                BEQ     PostProcess                 ; Current deleted, skip context save

ContextSave
                MOV     LR, R0                      ; Move &osInfo.thread.run.curr to LR
                MOV     R0, SP                      ; Move SP_svc into R0
                ADD     R0, R0, #20                 ; Adjust SP_svc to R0 of the basic frame
                SUB     SP, SP, #4
                STM     SP, {SP}^                   ; Save SP_usr to current stack
                NOP
                POP     {R1}                        ; Pop SP_usr into R1
                ; R0 = SP_svc, R1 = SP_usr
                SUB     R1, R1, #64                 ; Adjust SP_usr to R4 of the basic frame
                STMIA   R1!, {R4-R11}               ; Save R4-R11 to user stack
                LDMIA   R0!, {R4-R8}                ; Load stacked R0-R3,R12 into R4-R8
                STMIA   R1!, {R4-R8}                ; Store them to user stack
                STM     R1, {LR}^                   ; Store LR_usr directly
                ADD     R1, R1, #4                  ; Adjust user sp to PC
                LDMIB   R0!, {R5-R6}                ; Load current PC, CPSR
                STMIA   R1!, {R5-R6}                ; Restore user PC and CPSR

                SUB     R1, R1, #64                 ; Adjust SP_usr to stacked R4
                STR     R1, [LR]                    ; Store user sp to osInfo.thread.run.curr

PostProcess
                ; IRQ post processing check
                POP     {R8-R11}                    ; Pop R8 = run.next, R9 = &IRQ_PendSV, R10 = IRQ_PendSV, R11 = &osInfo.thread.run
                CMP     R10, #1                     ; Compare PendSV value
                BNE     ContextRestore              ; Skip post processing if not pending

                MOV     R4, SP                      ; Move SP_svc into R4
                AND     R4, R4, #4                  ; Get stack adjustment to ensure 8-byte alignment
                SUB     SP, SP, R4                  ; Adjust stack

                ; Disable OS Tick
                LDR     R5, =osInfo                 ; Load address of osInfo
                LDR     R5, [R5, #I_TICK_IRQN_OFS]  ; Load OS Tick irqn
                MOV     R0, R5                      ; Set it as function parameter
                LDR     R12, =IRQ_Disable
                MOV     LR, PC
                BX      R12                         ; Disable OS Tick interrupt
                MOV     R6, #0                      ; Set PendSV clear value
                B       PendCheck

PendExec
                STRB    R6, [R9]                    ; Clear PendSV flag
                MSR     CPSR_c, #MODE_SVC           ; Re-enable interrupts
                LDR     R12, =osPendSV_Handler
                MOV     LR, PC
                BX      R12                         ; Post process pending objects
                MSR     CPSR_c,#(MODE_SVC:OR:I_BIT) ; Disable interrupts

PendCheck
                LDR     R8, [R11, #4]               ; Load osInfo.thread.run.next
                STR     R8, [R11]                   ; Store run.next as run.curr
                LDRB    R0, [R9]                    ; Load PendSV flag
                CMP     R0, #1                      ; Compare PendSV value
                BEQ     PendExec                    ; Branch to PendExec if PendSV is set

                ; Re-enable OS Tick
                MOV     R0, R5                      ; Restore irqn as function parameter
                LDR     R12, =IRQ_Enable
                MOV     LR, PC
                BX      R12                         ; Enable OS Tick interrupt

                ADD     SP, SP, R4                  ; Restore stack adjustment

ContextRestore
                LDR     LR, [R8]                    ; Load next osThread_t.sp
                LDMIA   LR!, {R4-R11}               ; Restore R4-R11
                ADD     R12, LR, #32                ; Adjust sp and save it into R12
                PUSH    {R12}                       ; Push sp onto stack
                LDM     SP, {SP}^                   ; Restore SP_usr directly
                NOP
                ADD     SP, SP, #4                  ; Adjust SP_svc
                LDMIA   LR!, {R0-R3, R12}           ; Load user registers R0-R3,R12
                STMIB   SP!, {R0-R3, R12}           ; Store them to SP_svc
                LDM     LR, {LR}^                   ; Restore LR_usr directly
                NOP
                LDMIB   LR!, {R0-R1}                ; Load user registers PC,CPSR
                ADD     SP, SP, #4
                STMIB   SP!, {R0-R1}                ; Store them to SP_svc
                SUB     SP, SP, #32                 ; Adjust SP_svc to stacked LR

ContextExit
                POP     {PC}                        ; Return

                ENDP

;/*----------------------------------------------------------------------------
; * Helper functions
; *---------------------------------------------------------------------------*/

GetModeCPU\
                PROC
                EXPORT  GetModeCPU

                MRS     R0, CPSR
                AND     R0, R0, #0x1F
                BX      LR

                ENDP


DisableIRQ\
                PROC
                EXPORT  DisableIRQ

                MRS     R0, CPSR
                ORR     R1, R0, #I_BIT
                MSR     CPSR_c, R1
                BX      LR

                ENDP


RestoreIRQ\
                PROC
                EXPORT  RestoreIRQ

                MSR     CPSR_c, R0
                BX      LR

                ENDP


                END
