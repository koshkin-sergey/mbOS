/*
 * Copyright (C) 2023-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef __GCC_H
#define __GCC_H

/* CMSIS compiler specific defines */

#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __FORCEINLINE
  #define __FORCEINLINE                          __attribute__((always_inline))
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_WRITE { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_READ { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif
#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER()                   __ASM volatile("":::"memory")
#endif
/**
 *  @brief Use this attribute to indicate that the specified function is an interrupt handler.
 */
#ifndef   __INTERRUPT
  #define __INTERRUPT                            __attribute__((interrupt))
#endif


/* ########################  Core Instruction Access  ####################### */

/**
 * @brief   No Operation
 * @details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
#define __NOP()                             __ASM volatile ("nop")

/**
 * @brief   Wait For Interrupt
 * @details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
#define __WFI()                             __ASM volatile ("wfi":::"memory")

/**
 * @brief   Reverse byte order (32 bit)
 * @details Reverses the byte order in unsigned integer value. For example, 0x12345678 becomes 0x78563412.
 * @param [in]    value  Value to reverse
 * @return               Reversed value
 */
__STATIC_FORCEINLINE
uint32_t __REV(uint32_t value)
{
  return (__builtin_bswap32(value));
}

/**
 * @brief   Reverse byte order (16 bit)
 * @details Reverses the byte order in a 16-bit value and returns the signed 16-bit result. For example, 0x0080 becomes 0x8000.
 * @param [in]    value  Value to reverse
 * @return               Reversed value
 */
__STATIC_FORCEINLINE
int16_t __REVSH(int16_t value)
{
  return ((int16_t)__builtin_bswap16(value));
}

/**
 * @brief   Rotate Right in unsigned value (32 bit)
 * @details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
 * @param [in]    op1  Value to rotate
 * @param [in]    op2  Number of Bits to rotate
 * @return               Rotated value
 */
__STATIC_FORCEINLINE
uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U) {
    return (op1);
  }
  return ((op1 >> op2) | (op1 << (32U - op2)));
}

/**
 * @brief   Reverse bit order of value
 * @details Reverses the bit order of the given value.
 * @param [in]    value  Value to reverse
 * @return               Reversed value
 */
__STATIC_FORCEINLINE
uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  int32_t s = (sizeof(value) * 8U) - 1U; /* extra shift needed at end */

  result = value;                      /* r will be reversed bits of v; first get LSB of v */
  for (value >>= 1U; value; value >>= 1U) {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                        /* shift when v's highest bits are zero */

  return (result);
}

/**
 * @brief       Reverse bit order of value
 * @details     Reverses the bit order of the given value.
 * @param[in]   value  Value to reverse
 * @return      Reversed value
 */
__STATIC_FORCEINLINE uint16_t __RBIT16(uint16_t value)
{
  uint16_t result;
  int32_t s = (sizeof(value) * 8U) - 1U; /* extra shift needed at end */

  result = value;                      /* r will be reversed bits of v; first get LSB of v */
  for (value >>= 1U; value; value >>= 1U) {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                        /* shift when v's highest bits are zero */

  return (result);
}

/**
 * @brief   Count leading zeros
 * @param [in]  value  Value to count the leading zeros
 * @return             number of leading zeros in value
 */
__STATIC_FORCEINLINE
uint8_t __CLZ(uint32_t value)
{
  /* Even though __builtin_clz produces a CLZ instruction on ARM, formally
     __builtin_clz(0) is undefined behavior, so handle this case specially.
     This guarantees ARM-compatible results if happening to compile on a non-ARM
     target, and ensures the compiler doesn't decide to activate any
     optimizations using the logic "value was passed to __builtin_clz, so it
     is non-zero".
     ARM GCC 7.3 and possibly earlier will optimize this test away, leaving a
     single CLZ instruction.
   */
  if (value == 0U) {
    return (32U);
  }
  return (__builtin_clz(value));
}


/* #########################  Core Function Access  ######################### */

#define read_csr(reg) (                                                        \
{                                                                              \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrr %0, " #reg : "=r"(__tmp));                             \
  __tmp;                                                                       \
})

#define write_csr(reg, val)                                                    \
  __ASM volatile ("csrw " #reg ", %0" :: "Kr"(val))

#define swap_csr(reg, val) (                                                   \
{                                                                              \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "Kr"(val));         \
  __tmp;                                                                       \
})

#define set_csr(reg, bit) (                                                    \
{                                                                              \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "Kr"(bit));         \
  __tmp;                                                                       \
})

#define clear_csr(reg, bit) (                                                  \
{                                                                              \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "Kr"(bit));         \
  __tmp;                                                                       \
})

#endif /* __GCC_H */
