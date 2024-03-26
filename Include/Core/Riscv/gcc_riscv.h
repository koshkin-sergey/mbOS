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

#ifndef __GCC_RISCV_H
#define __GCC_RISCV_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* NMSIS compiler specific defines */
/** \brief Pass information from the compiler to the assembler. */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif

/** \brief Recommend that function should be inlined by the compiler. */
#ifndef   __INLINE
  #define __INLINE                               inline
#endif

/** \brief Define a static function that may be inlined by the compiler. */
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif

/** \brief Define a static function that should be always inlined by the compiler. */
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif

/** \brief Inform the compiler that a function does not return. */
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif

/** \brief Inform that a variable shall be retained in executable image. */
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif

/** \brief restrict pointer qualifier to enable additional optimizations. */
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif

/** \brief specified the vector size of the variable, measured in bytes */
#ifndef   __VECTOR_SIZE
  #define __VECTOR_SIZE(x)                       __attribute__((vector_size(x)))
#endif

/** \brief Request smallest possible alignment. */
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif

/** \brief Request smallest possible alignment for a structure. */
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif

/** \brief Request smallest possible alignment for a union. */
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif

#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint16_t write access */
  __PACKED_STRUCT T_UINT16_WRITE {
      uint16_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned write of a uint16_t variable. */
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif

#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint16_t read access */
  __PACKED_STRUCT T_UINT16_READ {
      uint16_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned read of a uint16_t variable. */
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif

#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint32_t write access */
  __PACKED_STRUCT T_UINT32_WRITE {
      uint32_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned write of a uint32_t variable. */
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif

#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint32_t read access */
  __PACKED_STRUCT T_UINT32_READ {
      uint32_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned read of a uint32_t variable. */
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif

/** \brief Minimum `x` bytes alignment for a variable. */
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif

/** \brief restrict pointer qualifier to enable additional optimizations. */
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif

/** \brief Barrier to prevent compiler from reordering instructions. */
#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER()                   __ASM volatile("":::"memory")
#endif

/** \brief provide the compiler with branch prediction information, the branch is usually true */
#ifndef   __USUALLY
  #define __USUALLY(exp)                         __builtin_expect((exp), 1)
#endif

/** \brief provide the compiler with branch prediction information, the branch is rarely true */
#ifndef   __RARELY
  #define __RARELY(exp)                          __builtin_expect((exp), 0)
#endif

/** \brief Use this attribute to indicate that the specified function is an interrupt handler run in Machine Mode. */
#ifndef   __INTERRUPT
  #define __INTERRUPT                            __attribute__((interrupt))
#endif

/** \brief Use this attribute to indicate that the specified function is an interrupt handler run in Machine Mode. */
#ifndef   __MACHINE_INTERRUPT
  #define __MACHINE_INTERRUPT                    __attribute__ ((interrupt ("machine")))
#endif

/** \brief Use this attribute to indicate that the specified function is an interrupt handler run in Supervisor Mode. */
#ifndef   __SUPERVISOR_INTERRUPT
  #define __SUPERVISOR_INTERRUPT                 __attribute__ ((interrupt ("supervisor")))
#endif

/** \brief Use this attribute to indicate that the specified function is an interrupt handler run in User Mode. */
#ifndef   __USER_INTERRUPT
  #define __USER_INTERRUPT                       __attribute__ ((interrupt ("user")))
#endif


/* #######################  Startup and Lowlevel Init  ###################### */

#ifndef __PROGRAM_START

extern void _start(void) __NO_RETURN;

/**
 * @brief   Initializes data and bss sections
 * @details This default implementations initialized all data and additional bss
 *          sections relying on .copy.table and .zero.table specified properly
 *          in the used linker script.
 */
__STATIC_FORCEINLINE __NO_RETURN
void __riscv_start(void)
{
  typedef struct {
      uint32_t const *src;
      uint32_t       *dest;
      uint32_t        wlen;
  } __copy_table_t;

  typedef struct {
      uint32_t *dest;
      uint32_t  wlen;
  } __zero_table_t;

  extern const __copy_table_t __copy_table_start__;
  extern const __copy_table_t __copy_table_end__;
  extern const __zero_table_t __zero_table_start__;
  extern const __zero_table_t __zero_table_end__;

  for (__copy_table_t const* pTable = &__copy_table_start__; pTable < &__copy_table_end__; ++pTable) {
    for (uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = pTable->src[i];
    }
  }

  for (__zero_table_t const* pTable = &__zero_table_start__; pTable < &__zero_table_end__; ++pTable) {
    for (uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = 0u;
    }
  }

  _start();
}

#define __PROGRAM_START           __riscv_start
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

#define __STR(s)                                 #s
#define STRINGIFY(s)                             __STR(s)

/**
 * @brief       CSR operation Macro for csrr instruction.
 * @details     Read the content of csr register and return it
 * @param       csr  CSR macro definition
 * @return      CSR register value
 */
#define CSR_READ(csr)                                                          \
({                                                                             \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrr %0, " STRINGIFY(csr)                                   \
                : "=r"(__tmp)                                                  \
                :                                                              \
                : "memory");                                                   \
  __tmp;                                                                       \
})

/**
 * @brief       CSR operation Macro for csrw instruction.
 * @details     Write the content of val to csr register
 * @param       csr  CSR macro definition
 * @param       val  value to store into the CSR register
 */
#define CSR_WRITE(csr, val)                                                    \
({                                                                             \
  __ASM volatile ("csrw " STRINGIFY(csr) ", %0"                                \
                :                                                              \
                : "Kr"(val)                                                    \
                : "memory");                                                   \
})

/**
 * @brief       CSR operation Macro for csrrw instruction.
 * @details     Read the content of csr register to __tmp,
 *              then write content of val into csr register,
 *              then return __tmp
 * @param       csr  CSR macro definition
 * @param       val  value to store into the CSR register
 * @return      CSR register value before written
 */
#define CSR_SWAP(csr, val)                                                     \
({                                                                             \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrrw %0, " STRINGIFY(csr) ", %1"                           \
                : "=r"(__tmp)                                                  \
                : "Kr"(val)                                                    \
                : "memory");                                                   \
  __tmp;                                                                       \
})

/**
 * @brief       CSR operation Macro for csrs instruction.
 * @details     Set csr register to be csr_content | val
 * @param       csr  CSR macro definition
 * @param       val  Mask value to be used wih csrs instruction
 */
#define CSR_SET(csr, val)                                                      \
({                                                                             \
  __ASM volatile ("csrs " STRINGIFY(csr) ", %0"                                \
                :                                                              \
                : "Kr"(val)                                                    \
                : "memory");                                                   \
})

/**
 * @brief       CSR operation Macro for csrrs instruction.
 * @details     Read the content of csr register to __tmp,
 *              then set csr register to be csr_content | val,
 *              then return __tmp
 * @param       csr  CSR macro definition
 * @param       val  Mask value to be used wih csrrs instruction
 * @return      CSR register value before written
 */
#define CSR_READ_SET(csr, val)                                                 \
({                                                                             \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrrs %0, " STRINGIFY(csr) ", %1"                           \
                : "=r"(__tmp)                                                  \
                : "Kr"(val)                                                    \
                : "memory");                                                   \
  __tmp;                                                                       \
})

/**
 * @brief       CSR operation Macro for csrc instruction.
 * @details     Set csr register to be csr_content & ~val
 * @param       csr  CSR macro definition
 * @param       val  Mask value to be used wih csrc instruction
 */
#define CSR_CLEAR(csr, val)                                                    \
({                                                                             \
  __ASM volatile ("csrc " STRINGIFY(csr) ", %0"                                \
                :                                                              \
                : "Kr"(val)                                                    \
                : "memory");                                                   \
})

/**
 * @brief       CSR operation Macro for csrrc instruction.
 * @details     Read the content of csr register to __tmp,
 *              then set csr register to be csr_content & ~val,
 *              then return __tmp
 * @param       csr  CSR macro definition
 * @param       val  Mask value to be used wih csrrc instruction
 * @return      CSR register value before written
 */
#define CSR_READ_CLEAR(csr, val)                                               \
({                                                                             \
  uint32_t __tmp;                                                              \
  __ASM volatile ("csrrc %0, " STRINGIFY(csr) ", %1"                           \
                : "=r"(__tmp)                                                  \
                : "Kr"(val)                                                    \
                : "memory");                                                   \
  __tmp;                                                                       \
})

#ifdef __cplusplus
}
#endif

#endif /* __GCC_RISCV_H */
