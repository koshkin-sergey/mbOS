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

#include <asm/krechet1.h>

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Default_Handler (void) __attribute__ ((fast_interrupt));
void Vectors         (void) __attribute__ ((naked, section(".vectors")));
void __start         (void);

/*----------------------------------------------------------------------------
  Interrupt Handler
 *----------------------------------------------------------------------------*/
void Reset_Handler       (void) __attribute__ ((naked));
void SysErr_Handler      (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void WDT_Handler         (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt3_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt4_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt5_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt6_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt7_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt8_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt9_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt10_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt11_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt12_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt13_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt14_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt15_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt16_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt17_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt18_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt19_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt20_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void Interrupt21_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void SysTick_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void SWI_Handler         (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Interrupt Vector Table
 *----------------------------------------------------------------------------*/
void Vectors(void)
{
  __ASM volatile(
    "jmp    Reset_Handler                                                    \n"
    "jmp    SysErr_Handler                                                   \n"
    "jmp    WDT_Handler                                                      \n"
    "jmp    Interrupt3_Handler                                               \n"
    "jmp    Interrupt4_Handler                                               \n"
    "jmp    Interrupt5_Handler                                               \n"
    "jmp    Interrupt6_Handler                                               \n"
    "jmp    Interrupt7_Handler                                               \n"
    "jmp    Interrupt8_Handler                                               \n"
    "jmp    Interrupt9_Handler                                               \n"
    "jmp    Interrupt10_Handler                                              \n"
    "jmp    Interrupt11_Handler                                              \n"
    "jmp    Interrupt12_Handler                                              \n"
    "jmp    Interrupt13_Handler                                              \n"
    "jmp    Interrupt14_Handler                                              \n"
    "jmp    Interrupt15_Handler                                              \n"
    "jmp    Interrupt16_Handler                                              \n"
    "jmp    Interrupt17_Handler                                              \n"
    "jmp    Interrupt18_Handler                                              \n"
    "jmp    Interrupt19_Handler                                              \n"
    "jmp    Interrupt20_Handler                                              \n"
    "jmp    Interrupt21_Handler                                              \n"
    "jmp    SysTick_Handler                                                  \n"
    "jmp    SWI_Handler                                                      \n"
  );
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  __ASM volatile(
    "cst    0x10                                                             \n"
    "ldrsl  PRW,    0                                                        \n"
    "ldrl   CONF,   0x017B                                                   \n"
    "ldrh   CONF,   0x0000                                                   \n"
    "reset                                                                   \n"
    "ldrl   r28,    lo(Vectors)                                              \n"
    "ldrh   r28,    hi(Vectors)                                              \n"
    "ldrsl  DP1ID,  0x0001                                                   \n"
    "ldrsl  DP2ID,  0x0001                                                   \n"
    "movl   c7,     lit(__stack)                                             \n"
    "subl   c7,     0x20                                                     \n"
    "mtprs  FB,     c7                                                       \n"
    "subl   c7,     0x20                                                     \n"
    "mtprs  FA,     c7                                                       \n"
    "jsr    SystemInit                                                       \n"
    "jmp    __start                                                          \n"
  );
}

/**
 * @brief   Initializes data and bss sections
 * @details This default implementations initialized all data and additional bss
 *          sections relying on .copy.table and .zero.table specified properly
 *          in the used linker script.
 */
void __start(void)
{
  extern int main(void);

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

  main();
}

/*----------------------------------------------------------------------------
  Default Handler for Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}
