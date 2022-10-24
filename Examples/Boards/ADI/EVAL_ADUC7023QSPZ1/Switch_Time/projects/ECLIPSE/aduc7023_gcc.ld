/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
__ROM_BASE = 0x00080000;
__ROM_SIZE = 0x0000F800;

/*--------------------- RAM Configuration -----------------------------------
// <h> RAM Configuration
//   <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
//   <o1> RAM Total Size (in Bytes) <0x0-0xFFFFFFFF:8>
//   <h> Stack / Heap Configuration
//     <o2>  Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//     <o3>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
//     <h> Exceptional Modes
//       <o4> UND Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o5> ABT Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o6> SVC Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o7> IRQ Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//       <o8> FIQ Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//     </h>
//   </h>
// </h>
 *----------------------------------------------------------------------------*/
__RAM_BASE       = 0x00010000;
__RAM_SIZE       = 0x00002000;

__STACK_SIZE     = 0x00000100;
__HEAP_SIZE      = 0x00000000;

__UND_STACK_SIZE = 0x00000000;
__ABT_STACK_SIZE = 0x00000000;
__SVC_STACK_SIZE = 0x00000100;
__IRQ_STACK_SIZE = 0x00000000;
__FIQ_STACK_SIZE = 0x00000000;

/*-----------------------------------------------------------------------------
//                   <<< end of configuration section >>>                    
 -----------------------------------------------------------------------------*/

MEMORY
{
  FLASH (rx)  : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  RAM   (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors))
    *(EXCLUDE_FILE(*irq_arm.o) .text*)

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

    *(.rodata*)

    KEEP(*(.eh_frame*))
  } > FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH

  .ARM.exidx :
  {
    __exidx_start = .;
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    __exidx_end = .;
  } > FLASH

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;
    
    LONG (LOADADDR(.fastcode))
    LONG (__fastcode_start__)
    LONG ((__fastcode_end__ - __fastcode_start__) / 4)
    
    LONG (LOADADDR(.data))
    LONG (__data_start__)
    LONG ((__data_end__ - __data_start__) / 4)
    
    __copy_table_end__ = .;
  } > FLASH

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    __zero_table_end__ = .;
  } > FLASH
  
  /**
   * Location counter can end up 2byte aligned with narrow Thumb code but
   * __etext is assumed by startup code to be the LMA of a section in RAM
   * which must be 4byte aligned 
   */
  __etext = ALIGN (4);

  .vectors_ram (NOLOAD) :
  {
    KEEP(*(.vectors_ram))
  } > RAM

  .fastcode :
  {
    . = ALIGN(4);
    __fastcode_start__ = .;
    *irq_arm.o(.text.os.handlers)
    *(.fastcode)
    . = ALIGN(4);
    __fastcode_end__ = .;
  } > RAM AT > FLASH

  .data :
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(vtable)
    *(.data)
    *(.data.*)

    . = ALIGN(4);
    /* preinit data */
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    . = ALIGN(4);
    /* init data */
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    . = ALIGN(4);
    /* finit data */
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);

    KEEP(*(.jcr*))
    . = ALIGN(4);
    /* All data end */
    __data_end__ = .;

  } > RAM AT > FLASH

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss.irq_table)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM AT > RAM

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    . = . + __HEAP_SIZE;
    . = ALIGN(8);
    __HeapLimit = .;
  } > RAM

  .stack (ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE - __FIQ_STACK_SIZE - __IRQ_STACK_SIZE - __SVC_STACK_SIZE - __ABT_STACK_SIZE - __UND_STACK_SIZE) (NOLOAD):
  {
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
