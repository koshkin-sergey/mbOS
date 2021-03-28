/**************************************************************************//**
 * @file     cmsis_armcc.h
 * @brief    CMSIS compiler specific macros, functions, instructions
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

#ifndef __CMSIS_ARMCC_H
#define __CMSIS_ARMCC_H

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 400677)
  #error "Please use Arm Compiler Toolchain V4.0.677 or later!"
#endif

/* CMSIS compiler control architecture macros */
#if (defined (__TARGET_ARCH_4T ) && (__TARGET_ARCH_4T  == 1))
  #define __ARM_ARCH_4T__           1
#endif

#if (defined (__TARGET_ARCH_5T ) && (__TARGET_ARCH_5T  == 1))
  #define __ARM_ARCH_5T__           1
#endif

/* CMSIS compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               __inline
#endif
#ifndef   __FORCEINLINE
  #define __FORCEINLINE                          __forceinline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static __inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   static __forceinline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __declspec(noreturn)
#endif
#ifndef   CMSIS_DEPRECATED
  #define CMSIS_DEPRECATED                       __attribute__((deprecated))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        __packed struct
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  #define __UNALIGNED_UINT16_WRITE(addr, val)    ((*((__packed uint16_t *)(addr))) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  #define __UNALIGNED_UINT16_READ(addr)          (*((const __packed uint16_t *)(addr)))
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  #define __UNALIGNED_UINT32_WRITE(addr, val)    ((*((__packed uint32_t *)(addr))) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #define __UNALIGNED_UINT32_READ(addr)          (*((const __packed uint32_t *)(addr)))
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed))
#endif
#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER()                   __memory_changed()
#endif

/* ##########################  Core Instruction Access  ######################### */
/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in unsigned integer value. For example, 0x12345678 becomes 0x78563412.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
#define __REV                             __rev

/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order within each halfword of a word. For example, 0x12345678 becomes 0x34127856.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
#if ((defined (__ARM_ARCH_4T__) && (__ARM_ARCH_4T__ == 1)) || \
     (defined (__ARM_ARCH_5T__) && (__ARM_ARCH_5T__ == 1))     )

#define __REV16(value) __ROR(__REV(value), 16)

#else

__attribute__((section(".rev16_text"))) __STATIC_INLINE __ASM uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}
#endif

/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in a 16-bit value and returns the signed 16-bit result. For example, 0x0080 becomes 0x8000.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
#if ((defined (__ARM_ARCH_4T__) && (__ARM_ARCH_4T__ == 1)) || \
     (defined (__ARM_ARCH_5T__) && (__ARM_ARCH_5T__ == 1))     )

#define __REVSH(value) (int16_t)__builtin_bswap16(value)

#else

__attribute__((section(".revsh_text"))) __STATIC_INLINE __ASM int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}
#endif

/**
  \brief   Rotate Right in unsigned value (32 bit)
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
#define __ROR                             __ror

/**
  \brief   Reverse bit order of value
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
#define __RBIT                            __rbit

/**
  \brief   Count leading zeros
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ                             __clz


/* ###########################  Core Function Access  ########################### */

/** \brief  Get CPSR (Current Program Status Register)
    \return               CPSR Register value
 */
__STATIC_INLINE uint32_t __get_CPSR(void)
{
  register uint32_t __regCPSR          __ASM("cpsr");
  return(__regCPSR);
}


/** \brief  Set CPSR (Current Program Status Register)
    \param [in]    cpsr  CPSR value to set
 */
__STATIC_INLINE void __set_CPSR(uint32_t cpsr)
{
  register uint32_t __regCPSR          __ASM("cpsr");
  __regCPSR = cpsr;
}

/** \brief  Get Mode
    \return                Processor Mode
 */
__STATIC_INLINE uint32_t __get_mode(void)
{
  return (__get_CPSR() & 0x1FU);
}

/** \brief  Set Mode
    \param [in]    mode  Mode value to set
 */
__STATIC_INLINE __ASM void __set_mode(uint32_t mode)
{
  MOV  r1, lr
  MSR  CPSR_C, r0
  BX   r1
}

/** \brief  Get Stack Pointer
    \return Stack Pointer
 */
__STATIC_INLINE __ASM uint32_t __get_SP(void)
{
  MOV  r0, sp
  BX   lr
}

/** \brief  Set Stack Pointer
    \param [in]    stack  Stack Pointer value to set
 */
__STATIC_INLINE __ASM void __set_SP(uint32_t stack)
{
  MOV  sp, r0
  BX   lr
}

#endif /* __CMSIS_ARMCC_H */
