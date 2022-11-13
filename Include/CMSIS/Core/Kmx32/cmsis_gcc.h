/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

/* ignore some GCC warnings */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* Fallback for __has_builtin */
#ifndef __has_builtin
  #define __has_builtin(x) (0)
#endif

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
#ifndef   __INTERRUPT
  #define __INTERRUPT                            __attribute__((interrupt))
#endif
#ifndef   __FAST_INTERRUPT
  #define __FAST_INTERRUPT                       __attribute__((fast_interrupt))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
/*lint -esym(9058, T_UINT16_WRITE)*/ /* disable MISRA 2012 Rule 2.4 for T_UINT16_WRITE */
  __PACKED_STRUCT T_UINT16_WRITE { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
/*lint -esym(9058, T_UINT16_READ)*/ /* disable MISRA 2012 Rule 2.4 for T_UINT16_READ */
  __PACKED_STRUCT T_UINT16_READ { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
/*lint -esym(9058, T_UINT32_WRITE)*/ /* disable MISRA 2012 Rule 2.4 for T_UINT32_WRITE */
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif
#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER()                   __ASM volatile("":::"memory")
#endif


/************************  Core Function Access  ******************************/

/**
 * @brief     Enable IRQ Interrupts
 * @details   Enables IRQ interrupts by setting the IE-bit in the PSW.
 */
__STATIC_FORCEINLINE void __enable_irq(void)
{
  __ASM volatile ("sst 0x10" : : : "memory");
}


/**
 * @brief     Disable IRQ Interrupts
 * @details   Disables IRQ interrupts by clearing the IE-bit in the PSW.
 */
__STATIC_FORCEINLINE void __disable_irq(void)
{
  __ASM volatile ("cst 0x10" : : : "memory");
}

/**
 * @brief       Push Unprotected CPU Register onto the stack.
 * @param[in]   addr  CPU Register address
 */
#define __push_CpuReg(addr)                                                    \
  __ASM volatile ("pushr r%0" : : "n" (addr))

/**
 * @brief       Pop Unprotected CPU Register from the stack.
 * @param[in]   addr  CPU Register address
 */
#define __pop_CpuReg(addr)                                                    \
  __ASM volatile ("popr r%0" : : "n" (addr))

/**
 * @brief       Get CPU Register
 * @details     Returns the content of the CPU Register.
 * @param[in]   addr  CPU Register address
 * @return      CPU Register value
 */
#define __get_CpuReg(addr)                                                     \
__extension__ (                                                                \
{                                                                              \
  uint32_t result;                                                             \
  __ASM volatile ("mfprs %0, r%1" : "=r" (result) : "n" (addr));               \
  result;                                                                      \
})

/**
 * @brief       Set CPU Register
 * @details     Writes the given value to the CPU Register.
 * @param[in]   addr  CPU Register address
 * @param[in]   data  CPU Register value to set
 */
#define __set_CpuReg(addr, data)                                               \
  __ASM volatile ("mtprs r%0, %1" : : "n" (addr), "r" (data))

/**
 * @brief       Get Peripheral Register
 * @details     Returns the content of the Peripheral Register.
 * @param[in]   addr  Peripheral Register address
 * @return      Peripheral Register value
 */
#define __get_PeriphReg(addr)                                                  \
__extension__ (                                                                \
{                                                                              \
  uint32_t result;                                                             \
  __ASM volatile ("mfpr %0, r%1" : "=r" (result) : "n" (addr));                \
  result;                                                                      \
})

/**
 * @brief       Set Peripheral Register
 * @details     Writes the given value to the Peripheral Register.
 * @param[in]   addr  Peripheral Register address
 * @param[in]   data  Peripheral Register value to set
 */
#define __set_PeriphReg(addr, data)                                            \
  __ASM volatile ("mtpr r%0, %1" : : "n" (addr), "r" (data))


/************************  Core Instruction Access  ***************************/

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
#define __NOP()                             __ASM volatile ("nop")

/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in unsigned integer value. For example, 0x12345678 becomes 0x78563412.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE  uint32_t __REV(uint32_t value)
{
  return (__builtin_bswap32(value));
}

/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__STATIC_FORCEINLINE  uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U) {
    return (op1);
  }
  return ((op1 >> op2) | (op1 << (32U - op2)));
}

/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE  uint32_t __RBIT(uint32_t value)
{
  uint32_t result;

  int32_t s = (4U /*sizeof(v)*/ * 8U) - 1U; /* extra shift needed at end */

  result = value;                      /* r will be reversed bits of v; first get LSB of v */
  for (value >>= 1U; value; value >>= 1U)
  {
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
  for (value >>= 1U; value; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                        /* shift when v's highest bits are zero */

  return (result);
}

/**
  \brief   Count leading zeros
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
__STATIC_FORCEINLINE uint8_t __CLZ(uint32_t value)
{
  /* Even though __builtin_clz produces a CLZ instruction on ARM, formally
     __builtin_clz(0) is undefined behaviour, so handle this case specially.
     This guarantees ARM-compatible results if happening to compile on a non-ARM
     target, and ensures the compiler doesn't decide to activate any
     optimisations using the logic "value was passed to __builtin_clz, so it
     is non-zero".
     ARM GCC 7.3 and possibly earlier will optimise this test away, leaving a
     single CLZ instruction.
   */
  if (value == 0U)
  {
    return (32U);
  }
  return (__builtin_clz(value));
}

__STATIC_FORCEINLINE void __isr_prologue(void)
{
  __ASM volatile (
    "pushr  LC                    \n\t"
    "pushr  SMC                   \n\t"
    "pushr  CLR                   \n\t"
    "pushr  PRW                   \n\t"
    "push   DP2                   \n\t"
    "push   DP1                   \n\t"
    "mfprs  DP1, ILR_PC           \n\t"
    "mfprs  DP2, ILR_PSW          \n\t"
    "push   DP1                   \n\t"
    "push   DP2                   \n\t"
    "pushr  FB                    \n\t"
    "pushr  FA                    \n\t"

    /* Increment IRQ nesting level   */
    "lda    dp1, IRQ_NestLevel    \n\t"
    "bne    1$                    \n\t"
    "mtprs  USP, c7               \n\t"
    "lda    c7, MSP               \n\t"
    "1$:                          \n\t"
    "addl   dp1, 1                \n\t"
    "sta    IRQ_NestLevel, dp1    \n\t"

    "srfa   8                     \n\t"

    /* Re-enable interrupts          */
    "sst    0x10                  \n\t"
  );
}

__STATIC_FORCEINLINE void __isr_epilogue(void)
{
  __ASM volatile(
    /* Disable interrupts            */
    "cst    0x10                  \n\t"

    /* Continue in context switcher  */
    "jsr    ContextSwitch         \n\t"

    "rsfa   8                     \n\t"

    /* Decrement IRQ nesting level   */
    "lda    dp1, IRQ_NestLevel    \n\t"
    "subl   dp1, 1                \n\t"
    "bne    2$                    \n\t"
    "sta    MSP, c7               \n\t"
    "mfprs  c7, USP               \n\t"
    "2$:                          \n\t"
    "sta    IRQ_NestLevel, dp1    \n\t"

    "popr   FA                    \n\t"
    "popr   FB                    \n\t"
    "pop    DP1                   \n\t"
    "pop    DP2                   \n\t"
    "mtprs  ILR_PSW, DP1          \n\t"
    "mtprs  ILR_PC,  DP2          \n\t"
    "pop    DP1                   \n\t"
    "pop    DP2                   \n\t"
    "popr   PRW                   \n\t"
    "popr   CLR                   \n\t"
    "popr   SMC                   \n\t"
    "popr   LC                    \n\t"
  );
}

#pragma GCC diagnostic pop

#endif /* __CMSIS_GCC_H */
