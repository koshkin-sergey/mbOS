/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

OUTPUT_FORMAT("elf32-kmx32","elf32-kmx32","elf32-kmx32")
OUTPUT_ARCH(kmx32)

/*------------------------------------------------------------------------------
//            <<< Use Configuration Wizard in Context Menu >>>
 -----------------------------------------------------------------------------*/

/*----------------------- Flash Configuration ----------------------------------
//  <h> Flash Configuration
//    <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
//    <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
//  </h>
 -----------------------------------------------------------------------------*/
__ROM_BASE = 0x80001000;
__ROM_SIZE = 0x00010000;

/*------------------------ RAM Configuration -----------------------------------
//  <h> RAM Configuration
//    <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
//    <o1> RAM Total Size (in Bytes) <0x0-0xFFFFFFFF:8>
//    <h> Stack / Heap Configuration
//      <o2>  Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//      <o3>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
//    </h>
//  </h>
 -----------------------------------------------------------------------------*/
__RAM_BASE          = 0x00000000;
__RAM_SIZE          = 0x00008000;

__STACK_SIZE        = 0x00000100;
__HEAP_SIZE         = 0x00000000;

__IRQ_FA_STACK_SIZE = 0x00000020;
__IRQ_FB_STACK_SIZE = 0x00000020;
__SWI_FA_STACK_SIZE = 0x00000020;
__SWI_FB_STACK_SIZE = 0x00000020;

/*------------------------------------------------------------------------------
//                    <<< end of configuration section >>>
 -----------------------------------------------------------------------------*/

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x80001000, LENGTH = 0x00010000
  RAM   (rw)  : ORIGIN = 0x00000000, LENGTH = 0x00008000
}

ENTRY(Reset_Handler)

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors))
    *(.text)
    *(.text.*)

    KEEP(*(.init))
    KEEP(*(.fini))

    /* .ctors */
    . = ALIGN(4);
     __ctors_start = .;
     KEEP (*(SORT(.ctors.*)))
     KEEP (*(.ctors))
     __ctors_end = .;

     /* .dtors */
     __dtors_start = .;
     KEEP (*(SORT(.dtors.*)))
     KEEP (*(.dtors))
     __dtors_end = .;

    __flbr = .;
    *(.rodata*)
  } > FLASH

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;
    
    LONG (LOADADDR(.data))
    LONG (__data_start__)
    LONG ((__data_end__ - __data_start__) / 4)
    
    __copy_table_end__ = .;
  } > FLASH

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;

    LONG (__bss_start__)
    LONG ((__bss_end__ - __bss_start__) / 4)

    __zero_table_end__ = .;
  } > FLASH

  __etext = ALIGN (4);
  
  .data : AT(__etext)
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    /* All data end */
    __data_end__ = .;
  } > RAM

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    . = ALIGN(8);
    *(.bss.os.thread.stack)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    . = . + __HEAP_SIZE;
    . = ALIGN(8);
    __HeapLimit = .;
  } > RAM

  .stack (ORIGIN(RAM) + LENGTH(RAM) -  __STACK_SIZE -
          __IRQ_FA_STACK_SIZE - __IRQ_FB_STACK_SIZE -
          __SWI_FA_STACK_SIZE - __SWI_FB_STACK_SIZE) (NOLOAD) :
  {
    . = ALIGN(8);
    
    __StackLimit = .;
    . += __STACK_SIZE;
    __StackTop = .;
    
    __IRQ_FA_Base = .;
    . += __IRQ_FA_STACK_SIZE;
    __IRQ_FA_Limit = .;
    
    __IRQ_FB_Base = .;
    . += __IRQ_FB_STACK_SIZE;
    __IRQ_FB_Limit = .;
    
    __SWI_FA_Base = .;
    . += __SWI_FA_STACK_SIZE;
    __SWI_FA_Limit = .;
    
    __SWI_FB_Base = .;
    . += __SWI_FB_STACK_SIZE;
    __SWI_FB_Limit = .;
  } > RAM
  PROVIDE(__stack = __StackTop);

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
