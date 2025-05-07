/**************************************************************************//**
 * @file     cmsis_iccarm.h
 * @brief    CMSIS compiler ICCARM (IAR Compiler for Arm) header file
 * @version  V1.0.0
 * @date     18. January 2021
 ******************************************************************************/
/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
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

#ifndef __CMSIS_ICCARM_H__
#define __CMSIS_ICCARM_H__

#ifndef __ICCARM__
  #error This file should only be compiled by ICCARM
#endif

#pragma system_include

#define __IAR_FT _Pragma("inline=forced") __intrinsic

#if (__VER__ >= 8000000)
  #define __ICCARM_V8 1
#else
  #define __ICCARM_V8 0
#endif

#pragma language=extended

#ifndef __ALIGNED
  #if __ICCARM_V8
    #define __ALIGNED(x) __attribute__((aligned(x)))
  #elif (__VER__ >= 7080000)
    /* Needs IAR language extensions */
    #define __ALIGNED(x) __attribute__((aligned(x)))
  #else
    #warning No compiler specific solution for __ALIGNED.__ALIGNED is ignored.
    #define __ALIGNED(x)
  #endif
#endif


/* Define compiler macros for CPU architecture, used in CMSIS 5.
 */
#if __ARM_ARCH_4T__
/* Macro already defined */
#else
  #if defined(__ARM4TM__)
    #define __ARM_ARCH_4T__ 1
  #endif
#endif

#ifndef __ASM
  #define __ASM __asm
#endif

#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER() __ASM volatile("":::"memory")
#endif

#ifndef __INLINE
  #define __INLINE inline
#endif

#ifndef   __NO_RETURN
  #if __ICCARM_V8
    #define __NO_RETURN __attribute__((__noreturn__))
  #else
    #define __NO_RETURN _Pragma("object_attribute=__noreturn")
  #endif
#endif

#ifndef   __PACKED
  /* Needs IAR language extensions */
  #if __ICCARM_V8
    #define __PACKED __attribute__((packed, aligned(1)))
  #else
    #define __PACKED __packed
  #endif
#endif

#ifndef   __PACKED_STRUCT
  /* Needs IAR language extensions */
  #if __ICCARM_V8
    #define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
  #else
    #define __PACKED_STRUCT __packed struct
  #endif
#endif

#ifndef   __PACKED_UNION
  /* Needs IAR language extensions */
  #if __ICCARM_V8
    #define __PACKED_UNION union __attribute__((packed, aligned(1)))
  #else
    #define __PACKED_UNION __packed union
  #endif
#endif

#ifndef   __RESTRICT
  #if __ICCARM_V8
    #define __RESTRICT            __restrict
  #else
    /* Needs IAR language extensions */
    #define __RESTRICT            restrict
  #endif
#endif

#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE       static inline
#endif

#ifndef   __FORCEINLINE
  #define __FORCEINLINE         _Pragma("inline=forced")
#endif

#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE  __FORCEINLINE __STATIC_INLINE
#endif

#ifndef   CMSIS_DEPRECATED
  #define CMSIS_DEPRECATED      __attribute__((deprecated))
#endif

#ifndef __UNALIGNED_UINT16_READ
  #pragma language=save
  #pragma language=extended
  __IAR_FT uint16_t __iar_uint16_read(void const *ptr)
  {
    return *(__packed uint16_t*)(ptr);
  }
  #pragma language=restore
  #define __UNALIGNED_UINT16_READ(PTR) __iar_uint16_read(PTR)
#endif


#ifndef __UNALIGNED_UINT16_WRITE
  #pragma language=save
  #pragma language=extended
  __IAR_FT void __iar_uint16_write(void const *ptr, uint16_t val)
  {
    *(__packed uint16_t*)(ptr) = val;;
  }
  #pragma language=restore
  #define __UNALIGNED_UINT16_WRITE(PTR,VAL) __iar_uint16_write(PTR,VAL)
#endif

#ifndef __UNALIGNED_UINT32_READ
  #pragma language=save
  #pragma language=extended
  __IAR_FT uint32_t __iar_uint32_read(void const *ptr)
  {
    return *(__packed uint32_t*)(ptr);
  }
  #pragma language=restore
  #define __UNALIGNED_UINT32_READ(PTR) __iar_uint32_read(PTR)
#endif

#ifndef __UNALIGNED_UINT32_WRITE
  #pragma language=save
  #pragma language=extended
  __IAR_FT void __iar_uint32_write(void const *ptr, uint32_t val)
  {
    *(__packed uint32_t*)(ptr) = val;;
  }
  #pragma language=restore
  #define __UNALIGNED_UINT32_WRITE(PTR,VAL) __iar_uint32_write(PTR,VAL)
#endif

#if 0
#ifndef __UNALIGNED_UINT32   /* deprecated */
  #pragma language=save
  #pragma language=extended
  __packed struct  __iar_u32 { uint32_t v; };
  #pragma language=restore
  #define __UNALIGNED_UINT32(PTR) (((struct __iar_u32 *)(PTR))->v)
#endif
#endif

#ifndef   __USED
  #if __ICCARM_V8
    #define __USED __attribute__((used))
  #else
    #define __USED _Pragma("__root")
  #endif
#endif

#ifndef   __WEAK
  #if __ICCARM_V8
    #define __WEAK __attribute__((weak))
  #else
    #define __WEAK _Pragma("__weak")
  #endif
#endif


#ifndef __ICCARM_INTRINSICS_VERSION__
  #define __ICCARM_INTRINSICS_VERSION__  0
#endif

#if __ICCARM_INTRINSICS_VERSION__ == 2

  #if defined(__CLZ)
    #undef __CLZ
  #endif
  #if defined(__REVSH)
    #undef __REVSH
  #endif
  #if defined(__RBIT)
    #undef __RBIT
  #endif
  #if defined(__SSAT)
    #undef __SSAT
  #endif
  #if defined(__USAT)
    #undef __USAT
  #endif

  #include "iccarm_builtin.h"

  #define __get_CPSR()                (__arm_rsr("CPSR"))
  #define __get_mode()                (__get_CPSR() & 0x1FU)

  #define __set_CPSR(VALUE)           (__arm_wsr("CPSR", (VALUE)))
  #define __set_mode(VALUE)           (__arm_wsr("CPSR_c", (VALUE)))

  #define __CLZ     __iar_builtin_CLZ

  #define __RBIT    __iar_builtin_RBIT
  #define __REV     __iar_builtin_REV
  #define __REV16   __iar_builtin_REV16

  __IAR_FT int16_t __REVSH(int16_t val)
  {
    return (int16_t) __iar_builtin_REVSH(val);
  }

  #define __ROR     __iar_builtin_ROR
  #define __NOP     __iar_builtin_no_operation

#else /* __ICCARM_INTRINSICS_VERSION__ == 2 */

  #ifdef __INTRINSICS_INCLUDED
  #error intrinsics.h is already included previously!
  #endif

  #include <intrinsics.h>

  #pragma diag_suppress=Pe940
  #pragma diag_suppress=Pe177

  #define __NOP           __no_operation

  __IAR_FT void __set_mode(uint32_t mode)
  {
    __ASM volatile("MSR  cpsr_c, %0" : : "r" (mode) : "memory");
  }

  __IAR_FT uint32_t __ROR(uint32_t op1, uint32_t op2)
  {
    return (op1 >> op2) | (op1 << ((sizeof(op1)*8)-op2));
  }

#endif   /* __ICCARM_INTRINSICS_VERSION__ == 2 */

#define __get_mode()                (__get_CPSR() & 0x1FU)


#undef __IAR_FT
#undef __ICCARM_V8

#pragma diag_default=Pe940
#pragma diag_default=Pe177

#endif /* __CMSIS_ICCARM_H__ */
