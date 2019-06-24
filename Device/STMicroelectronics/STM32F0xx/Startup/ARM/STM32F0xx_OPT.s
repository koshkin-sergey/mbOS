;/**************************************************************************//**
; * @file     STM32F0xx_OPT.s
; * @brief    STM32F0xx Flash Option Bytes
; * @version  V1.01
; * @date     15. January 2015
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2015 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


;// <e> Flash Option Bytes
FLASH_OPT       EQU     1

;// <h> Flash Read Protection
;//     <i> Read protection is used to protect the software code stored in Flash memory
;//   <o0> Read Protection Level
;//     <i> Level 0: No Protection 
;//     <i> Level 1: Read Protection of Memories (debug features limited)
;//     <i> Level 2: Chip Protection (debug and boot in RAM features disabled)
;//          <0xAA=> Level 0 (No Protection) 
;//          <0xA5=> Level 1 (Read Protection of Memories)
;//          <0xCC=> Level 2 (Chip Protection. It's no more possible to go back to level 1 or 0!)
;// </h>
RDP             EQU     0xAA
nRDP            EQU     RDP:EOR:0xFF


;// <h> Flash Write Protection
;//   <h> WRP0..WRP1
;//     <o0.0> Page 0..3
;//     <o0.1> Page 4..7
;//     <o0.2> Page 8..11
;//     <o0.3> Page 12..15
;//     <o0.4> Page 16..19
;//     <o0.5> Page 20..23
;//     <o0.6> Page 24..27
;//     <o0.7> Page 28..31
;//     <o1.0> Page 32..35
;//     <o1.1> Page 36..39
;//     <o1.2> Page 40..43
;//     <o1.3> Page 44..47
;//     <o1.4> Page 48..51
;//     <o1.5> Page 52..55
;//     <o1.6> Page 56..59
;//     <o1.7> Page 60..63
;//   </h>
;//   <e4> WRP2..WRP3 (only STM32F07x, STM32F09x)
;//     <i> Available on STM32F07x, STM32F09x devices only
;//     <o2.0> Page 64..67
;//     <o2.1> Page 68..71
;//     <o2.2> Page 72..75
;//     <o2.3> Page 76..79
;//     <o2.4> Page 80..83
;//     <o2.5> Page 84..87
;//     <o2.6> Page 88..91
;//     <o2.7> Page 92..95
;//     <o3.0> Page 96..99
;//     <o3.1> Page 100..103
;//     <o3.2> Page 104..107
;//     <o3.3> Page 108..111
;//     <o3.4> Page 112..115
;//     <o3.5> Page 116..119
;//     <o3.6> Page 120..123
;//     <o3.7> Page 124..127
;//   </e>
;// </h>
nWRP0           EQU     0x00
nWRP1           EQU     0x00
nWRP2           EQU     0x00
nWRP3           EQU     0x00
USE_WRP2_WRP3   EQU     0
WRP0            EQU     nWRP0:EOR:0xFF
WRP1            EQU     nWRP1:EOR:0xFF
WRP2            EQU     nWRP2:EOR:0xFF
WRP3            EQU     nWRP3:EOR:0xFF

;// <h> User Configuration
;//   <o0.0> WDG_SW     
;//       <0=> HW Watchdog <1=> SW Watchdog
;//   <o0.1> nRST_STOP
;//     <i> Generate Reset when entering STOP Mode
;//       <0=> Generate Reset
;//       <1=> Do not generate Reset
;//   <o0.2> nRST_STDBY
;//     <i> Generate Reset when entering Standby Mode
;//       <0=> Generate Reset
;//       <1=> Do not generate Reset
;//   <o0.3> nBOOT0 (only STM32F04x, STM32F09x)
;//     <i> Boot0 mode
;//     <i> Available on STM32F04x, STM32F09x devices only.
;//       <0=> Reset
;//       <1=> Set
;//   <o0.4> nBOOT1
;//     <i> Boot1 mode
;//       <0=> Reset
;//       <1=> Set
;//   <o0.5> VDDA_MONITOR
;//     <i> Analog monitoring on VDDA Power source
;//       <0=> VDDA power supply supervisor disabled
;//       <1=> VDDA power supply supervisor enabled
;//   <o0.6> RAM_PARITY_CHECK
;//     <i> RAM parity check
;//       <0=> Enabled
;//       <1=> Disabled
;//   <o0.7> BOOT_SEL (only STM32F04x, STM32F09x)
;//     <i> BOOT0 signal source selection
;//     <i> Available on STM32F04x, STM32F09x devices only. Considered as “1” on other devices.
;//       <0=> nBOOT0 option bit
;//       <1=> BOOT0 pin value
;// </h>
USER            EQU     0xFF
nUSER           EQU     USER:EOR:0xFF

;// <h> User Data
;//   <o0> Byte 0 <0x00-0xFF>
;//   <o1> Byte 1 <0x00-0xFF>
;// </h>
DATA0           EQU     0xFF
DATA1           EQU     0xFF
nDATA0          EQU     DATA0:EOR:0xFF
nDATA1          EQU     DATA1:EOR:0xFF

;// </e>


                IF      FLASH_OPT <> 0
                AREA    |.ARM.__AT_0x1FFFF800|, CODE, READONLY
                DCB     RDP,   nRDP
                DCB     USER,  nUSER
                DCB     DATA0, nDATA0, DATA1, nDATA1
                DCB     WRP0,  nWRP0,  WRP1,  nWRP1
                IF      USE_WRP2_WRP3 <> 0
                DCB     WRP2,  nWRP2,  WRP3,  nWRP3
                ENDIF ; USE_WRP2_WRP3
                ENDIF ; FLASH_OPT


                END
