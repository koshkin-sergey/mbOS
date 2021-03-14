/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*-----------------------------------------------------------------------------
//             <<< Use Configuration Wizard in Context Menu >>>
 -----------------------------------------------------------------------------*/

/*---------------------- Flash Configuration ----------------------------------
//  <h> Flash Configuration
//    <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
//    <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
//  </h>
 -----------------------------------------------------------------------------*/
__ROM_BASE = 0x08000000;
__ROM_SIZE = 0x00010000;

/*--------------------- RAM Configuration -----------------------------------
// <h> RAM Configuration
//   <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
//   <o1> RAM Total Size (in Bytes) <0x0-0xFFFFFFFF:8>
//   <h> Stack / Heap Configuration
//     <o4>  Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//     <o5>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
//     <h> Exceptional Modes
//       <o6> UND Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o7> ABT Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o8> SVC Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o9> IRQ Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o10> FIQ Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//     </h>
//   </h>
// </h>
 *----------------------------------------------------------------------------*/
#define __RAM_BASE       0x80200000
#define __RAM_SIZE       0x00200000

#define __STACK_SIZE     0x00001000
#define __HEAP_SIZE      0x00000000

#define __UND_STACK_SIZE 0x00000100
#define __ABT_STACK_SIZE 0x00000100
#define __SVC_STACK_SIZE 0x00000100
#define __IRQ_STACK_SIZE 0x00000100
#define __FIQ_STACK_SIZE 0x00000100

/*-----------------------------------------------------------------------------
//                   <<< end of configuration section >>>                    
 -----------------------------------------------------------------------------*/

MEMORY
{
  ROM (rx)   : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE 
  RAM (rwx)  : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        Image$$VECTORS$$Base = .;
        * (RESET)
        KEEP(*(.isr_vector))
        Image$$VECTORS$$Limit = .;

        *(SVC_TABLE)
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        Image$$RO_DATA$$Base = .;
        *(.rodata*)
        Image$$RO_DATA$$Limit = .;

        KEEP(*(.eh_frame*))
    } > ROM

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > ROM

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > ROM
    __exidx_end = .;

    .copy.table :
    {
        . = ALIGN(4);
        __copy_table_start__ = .;
        LONG (__etext)
        LONG (__data_start__)
        LONG (__data_end__ - __data_start__)
        __copy_table_end__ = .;
    } > ROM

    .zero.table :
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG (__bss_end__ - __bss_start__)
        __zero_table_end__ = .;
    } > ROM

    __etext = .;

    .data : AT (__etext)
    {
        Image$$RW_DATA$$Base = .;
        __data_start__ = .;
        *(vtable)
        *(.data*)
        Image$$RW_DATA$$Limit = .;

        . = ALIGN(4);
        /* preinit data */
        PROVIDE (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > RAM

    .bss ALIGN(0x400):
    {
        Image$$ZI_DATA$$Base = .;
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
        Image$$ZI_DATA$$Limit = .;
        __end__ = .;
        end = __end__;
    } > RAM

#if defined(__HEAP_SIZE) && (__HEAP_SIZE > 0)    
    .heap (NOLOAD):
    {
        . = ALIGN(8);
        Image$$HEAP$$ZI$$Base = .;
        . += __HEAP_SIZE;
        Image$$HEAP$$ZI$$Limit = .;
        __HeapLimit = .;
    } > RAM  
#endif

    .stack (NOLOAD):
    {
        . = ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE - __FIQ_STACK_SIZE - __IRQ_STACK_SIZE - __SVC_STACK_SIZE - __ABT_STACK_SIZE - __UND_STACK_SIZE;
        . = ALIGN(8);
        
        __StackTop = .;
        Image$$SYS_STACK$$ZI$$Base = .;
        . += __STACK_SIZE;
        Image$$SYS_STACK$$ZI$$Limit = .;
        __stack = .;

        Image$$FIQ_STACK$$ZI$$Base = .;
        . += __FIQ_STACK_SIZE;
        Image$$FIQ_STACK$$ZI$$Limit = .;

        Image$$IRQ_STACK$$ZI$$Base = .;
        . += __IRQ_STACK_SIZE;
        Image$$IRQ_STACK$$ZI$$Limit = .;

        Image$$SVC_STACK$$ZI$$Base = .;
        . += __SVC_STACK_SIZE;
        Image$$SVC_STACK$$ZI$$Limit = .;

        Image$$ABT_STACK$$ZI$$Base = .;
        . += __ABT_STACK_SIZE;
        Image$$ABT_STACK$$ZI$$Limit = .;

        Image$$UND_STACK$$ZI$$Base = .;
        . += __UND_STACK_SIZE;
        Image$$UND_STACK$$ZI$$Limit = .;
    } > RAM
}
