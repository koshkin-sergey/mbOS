/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stddef.h>
#include <asm/gd32vf103xx_eclic.h>
#include <asm/gd32vf103xx_systimer.h>
#include <Core/Riscv/irq_riscv.h>

extern const IRQHandler_t exc_vectors[];

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#ifndef __riscv_32e
/**
 * @brief       Macro for context save
 * @details     This macro save ABI defined caller saved registers in the stack.
 * @remarks     This Macro could use to save context when you enter to exception
 *              or interrupt
 */
#define SAVE_CONTEXT()                                                         \
  __ASM volatile (                                                             \
    "addi    sp, sp, -72            \n\t"                                      \
    "sw      a0,  0 * 4(sp)         \n\t"                                      \
    "sw      a1,  1 * 4(sp)         \n\t"                                      \
    "sw      a2,  2 * 4(sp)         \n\t"                                      \
    "sw      a3,  3 * 4(sp)         \n\t"                                      \
    "sw      a4,  4 * 4(sp)         \n\t"                                      \
    "sw      a5,  5 * 4(sp)         \n\t"                                      \
    "sw      t0,  6 * 4(sp)         \n\t"                                      \
    "sw      t1,  7 * 4(sp)         \n\t"                                      \
    "sw      t2,  8 * 4(sp)         \n\t"                                      \
    "sw      ra,  9 * 4(sp)         \n\t"                                      \
    "csrr    t0, mepc               \n\t"                                      \
    "sw      t0, 10 * 4(sp)         \n\t"                                      \
    "csrr    t0, mstatus            \n\t"                                      \
    "sw      t0, 11 * 4(sp)         \n\t"                                      \
    "sw      a6, 12 * 4(sp)         \n\t"                                      \
    "sw      a7, 13 * 4(sp)         \n\t"                                      \
    "sw      t3, 14 * 4(sp)         \n\t"                                      \
    "sw      t4, 15 * 4(sp)         \n\t"                                      \
    "sw      t5, 16 * 4(sp)         \n\t"                                      \
    "sw      t6, 17 * 4(sp)         \n\t"                                      \
  )

/**
 * @brief       Macro for restore caller registers
 * @details     This macro restore ABI defined caller saved registers from stack.
 * @remarks     You could use this macro to restore context before you want return
 *              from interrupt or exeception
 */
#define RESTORE_CONTEXT()                                                      \
  __ASM volatile (                                                             \
    "lw      t0, 11 * 4(sp)         \n\t"                                      \
    "csrw    mstatus, t0            \n\t"                                      \
    "lw      t0, 10 * 4(sp)         \n\t"                                      \
    "csrw    mepc, t0               \n\t"                                      \
    "lw      a0,  0 * 4(sp)         \n\t"                                      \
    "lw      a1,  1 * 4(sp)         \n\t"                                      \
    "lw      a2,  2 * 4(sp)         \n\t"                                      \
    "lw      a3,  3 * 4(sp)         \n\t"                                      \
    "lw      a4,  4 * 4(sp)         \n\t"                                      \
    "lw      a5,  5 * 4(sp)         \n\t"                                      \
    "lw      t0,  6 * 4(sp)         \n\t"                                      \
    "lw      t1,  7 * 4(sp)         \n\t"                                      \
    "lw      t2,  8 * 4(sp)         \n\t"                                      \
    "lw      ra,  9 * 4(sp)         \n\t"                                      \
    "lw      a6, 12 * 4(sp)         \n\t"                                      \
    "lw      a7, 13 * 4(sp)         \n\t"                                      \
    "lw      t3, 14 * 4(sp)         \n\t"                                      \
    "lw      t4, 15 * 4(sp)         \n\t"                                      \
    "lw      t5, 16 * 4(sp)         \n\t"                                      \
    "lw      t6, 17 * 4(sp)         \n\t"                                      \
    "addi    sp, sp, 72             \n\t"                                      \
    "mret                           \n\t"                                      \
  )
#else
/**
 * @brief       Macro for context save
 * @details     This macro save ABI defined caller saved registers in the stack.
 * @remarks     This Macro could use to save context when you enter to exception
 *              or interrupt
 */
#define SAVE_CONTEXT()                                                         \
  __ASM volatile (                                                             \
    "addi    sp, sp, -48            \n\t"                                      \
    "sw      a0,  0 * 4(sp)         \n\t"                                      \
    "sw      a1,  1 * 4(sp)         \n\t"                                      \
    "sw      a2,  2 * 4(sp)         \n\t"                                      \
    "sw      a3,  3 * 4(sp)         \n\t"                                      \
    "sw      a4,  4 * 4(sp)         \n\t"                                      \
    "sw      a5,  5 * 4(sp)         \n\t"                                      \
    "sw      t0,  6 * 4(sp)         \n\t"                                      \
    "sw      t1,  7 * 4(sp)         \n\t"                                      \
    "sw      t2,  8 * 4(sp)         \n\t"                                      \
    "sw      ra,  9 * 4(sp)         \n\t"                                      \
    "csrr    t0, mepc               \n\t"                                      \
    "sw      t0, 10 * 4(sp)         \n\t"                                      \
    "csrr    t0, mstatus            \n\t"                                      \
    "sw      t0, 11 * 4(sp)         \n\t"                                      \
  )

/**
 * @brief       Macro for restore caller registers
 * @details     This macro restore ABI defined caller saved registers from stack.
 * @remarks     You could use this macro to restore context before you want return
 *              from interrupt or exeception
 */
#define RESTORE_CONTEXT()                                                      \
  __ASM volatile (                                                             \
    "lw      t0, 11 * 4(sp)         \n\t"                                      \
    "csrw    mstatus, t0            \n\t"                                      \
    "lw      t0, 10 * 4(sp)         \n\t"                                      \
    "csrw    mepc, t0               \n\t"                                      \
    "lw      a0,  0 * 4(sp)         \n\t"                                      \
    "lw      a1,  1 * 4(sp)         \n\t"                                      \
    "lw      a2,  2 * 4(sp)         \n\t"                                      \
    "lw      a3,  3 * 4(sp)         \n\t"                                      \
    "lw      a4,  4 * 4(sp)         \n\t"                                      \
    "lw      a5,  5 * 4(sp)         \n\t"                                      \
    "lw      t0,  6 * 4(sp)         \n\t"                                      \
    "lw      t1,  7 * 4(sp)         \n\t"                                      \
    "lw      t2,  8 * 4(sp)         \n\t"                                      \
    "lw      ra,  9 * 4(sp)         \n\t"                                      \
    "addi    sp, sp, 48             \n\t"                                      \
    "mret                           \n\t"                                      \
  )
#endif

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

uint32_t IRQ_NestLevel;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

void exc_entry(void) __attribute__ ((naked, aligned(64)));

/**
 * @brief       Exception Entry
 */
void exc_entry(void)
{
  SAVE_CONTEXT();

  __ASM volatile (
    "  lw    t0, IRQ_NestLevel      \n\t"
    "  addi  t0, t0, +1             \n\t"   // Increment IRQ nesting level
    "  sw    t0, IRQ_NestLevel, t1  \n\t"
    "  csrrw sp, mscratch, sp       \n\t"
    "  bnez  sp, 1f                 \n\t"
    "  csrr  sp, mscratch           \n\t"
    "1:                             \n\t"
    "  csrr  a0, mcause             \n\t"
    "  blt   a0, zero, 1f           \n\t"
    "  slli  a0, a0, 20             \n\t"
    "  srli  a0, a0, 18             \n\t"
    "  la    a5, exc_vectors        \n\t"
    "  add   a5, a5, a0             \n\t"
    "  lw    a0, 0(a5)              \n\t"
    "  csrs  mstatus, 0x8           \n\t"   // Re-enable interrupts
    "  jalr  a0                     \n\t"
    "  csrc  mstatus, 0x8           \n\t"   // Disable interrupts
    "1:                             \n\t"
    "  csrrw sp, mscratch, sp       \n\t"
    "  lw    t0, IRQ_NestLevel      \n\t"
    "  addi  t0, t0, -1             \n\t"   // Decrement IRQ nesting level
    "  sw    t0, IRQ_NestLevel, t1  \n\t"
  );

  RESTORE_CONTEXT();
}

void irq_entry(void) __attribute__ ((naked, aligned(4)));

/**
 * @brief       Interrupt Entry
 */
void irq_entry(void)
{
  SAVE_CONTEXT();

  __ASM volatile (
    "  lw    t0, IRQ_NestLevel      \n\t"
    "  bnez  t0, 1f                 \n\t"
    "  csrrw sp, mscratch, sp       \n\t"
    "1:                             \n\t"
    "  addi  t0, t0, +1             \n\t"   // Increment IRQ nesting level
    "  sw    t0, IRQ_NestLevel, t1  \n\t"
    "  csrrw ra, 0x7ED, ra          \n\t"
    "  csrc  mstatus, 0x8           \n\t"   // Disable interrupts
    "  lw    t0, IRQ_NestLevel      \n\t"
    "  addi  t0, t0, -1             \n\t"   // Decrement IRQ nesting level
    "  sw    t0, IRQ_NestLevel, t1  \n\t"
    "  bnez  t0, 1f                 \n\t"
    "  csrrw sp, mscratch, sp       \n\t"
    "1:                             \n\t"
  );

  RESTORE_CONTEXT();
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Initialize interrupt controller.
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Initialize(void)
{
  uint32_t addr;
  extern void irq_vectors(void);

  CSR_WRITE(CSR_MSCRATCH, 0);
  CSR_SET(CSR_MMISC_CTL, 1UL << 9);

  addr = ((uint32_t)exc_entry & ~0x3FUL) | 0x3UL;
  CSR_WRITE(CSR_MTVEC, addr);

  addr = (uint32_t)irq_vectors;
  CSR_WRITE(CSR_MTVT, addr);

  addr = ((uint32_t)irq_entry & ~0x3UL) | 0x1UL;
  CSR_WRITE(CSR_MTVT2, addr);

  uint32_t irq_cnt = ECLIC->info & CLIC_CLICINFO_NUM_Msk;
  for (uint32_t i = 0U; i < irq_cnt; ++i) {
    ECLIC->ctrl[i].intie = 0U;
    ECLIC->ctrl[i].intip = 0U;
  }

  SysTimer->msip = 0U;
  ECLIC->ctrl[CLIC_INT_SFT].intie = CLIC_INTIE_IE_Msk;

  return (0);
}

/**
 * @brief       Register interrupt handler.
 * @param[in]   irqn      interrupt ID number
 * @param[in]   handler   interrupt handler function address
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetHandler(IRQn_ID_t irqn, IRQHandler_t handler)
{
  (void) irqn;
  (void) handler;

  return (-1);
}

/**
 * @brief       Get the registered interrupt handler.
 * @param[in]   irqn   interrupt or exception ID number
 * @return      registered interrupt handler function address.
 */
IRQHandler_t IRQ_GetHandler(IRQn_ID_t irqn)
{
  IRQHandler_t handler = NULL;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    IRQHandler_t *irq_vtable = (IRQHandler_t *)CSR_READ(CSR_MTVT);
    handler = irq_vtable[irqn];
  }

  return (handler);
}

/**
 * @brief       Enable interrupt.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Enable(IRQn_ID_t irqn)
{
  int32_t status = -1;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    ECLIC->ctrl[irqn].intie = 1U;
    status = 0;
  }

  return (status);
}

/**
 * @brief       Disable interrupt.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Disable(IRQn_ID_t irqn)
{
  int32_t status = -1;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    ECLIC->ctrl[irqn].intie = 0U;
    status = 0;
  }

  return (status);
}

/**
 * @brief       Get interrupt enable state.
 * @param[in]   irqn    interrupt ID number
 * @return      0 - interrupt is disabled, 1 - interrupt is enabled.
 */
uint32_t IRQ_GetEnableState(IRQn_ID_t irqn)
{
  uint32_t status = 0U;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    status = ECLIC->ctrl[irqn].intie;
  }

  return (status);
}

/**
 * @brief       Configure interrupt request mode.
 * @param[in]   irqn    interrupt ID number
 * @param[in]   mode    mode configuration
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetMode(IRQn_ID_t irqn, uint32_t mode)
{
  (void) irqn;
  (void) mode;

  return (0);
}

/**
 * @brief       Get interrupt mode configuration.
 * @param[in]   irqn    interrupt ID number
 * @return      current interrupt mode configuration with optional
 *              IRQ_MODE_ERROR bit set.
 */
uint32_t IRQ_GetMode(IRQn_ID_t irqn)
{
  (void) irqn;

  return (0U);
}

/**
 * @brief       Signal end of interrupt processing.
 * @param[in]   irqn   interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_EndOfInterrupt(IRQn_ID_t irqn)
{
  (void) irqn;

  return (-1);
}



/**
 * @brief       Set interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPending(IRQn_ID_t irqn)
{
  int32_t status = -1;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    ECLIC->ctrl[irqn].intip = 1U;
    status = 0;
  }

  return (status);
}

/**
 * @brief       Get interrupt pending flag.
 * @param[in]   irqn   interrupt ID number
 * @return      0 - interrupt is not pending, 1 - interrupt is pending.
 */
uint32_t IRQ_GetPending(IRQn_ID_t irqn)
{
  uint32_t status = 0U;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    status = ECLIC->ctrl[irqn].intip;
  }

  return (status);
}

/**
 * @brief       Clear interrupt pending flag.
 * @param[in]   irqn   interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_ClearPending(IRQn_ID_t irqn)
{
  int32_t status = -1;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    ECLIC->ctrl[irqn].intip = 0U;
    status = 0;
  }

  return (status);
}

/**
 * @brief       Set interrupt priority value.
 * @param[in]   irqn      interrupt ID number
 * @param[in]   priority  interrupt priority value
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriority(IRQn_ID_t irqn, uint32_t priority)
{
  int32_t status = -1;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    ECLIC->ctrl[irqn].intctrl = (uint8_t)priority;
    status = 0;
  }

  return (status);
}

/**
 * @brief       Get interrupt priority.
 * @param[in]   irqn      interrupt ID number
 * @return      current interrupt priority value with optional
 *              IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriority(IRQn_ID_t irqn)
{
  uint32_t priority = IRQ_PRIORITY_ERROR;

  if (irqn > 0 && irqn < IRQn_MAX_NUM) {
    priority = ECLIC->ctrl[irqn].intctrl;
  }

  return (priority);
}

/**
 * @brief       Set priority masking threshold.
 * @param[in]   priority  priority masking threshold value
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriorityMask(uint32_t priority)
{
  (void) priority;

  return (-1);
}

/**
 * @brief       Get priority masking threshold
 * @return      current priority masking threshold value with optional
 *              IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriorityMask(void)
{
  return (IRQ_PRIORITY_ERROR);
}

/**
 * @brief       Set priority grouping field split point
 * @param[in]   bits    number of MSB bits included in the group priority field
 *                      comparison
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriorityGroupBits(uint32_t bits)
{
  (void) bits;

  return (-1);
}

/**
 * @brief       Get priority grouping field split point
 * @return      current number of MSB bits included in the group priority field
 *              comparison with optional IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriorityGroupBits(void)
{
  return (IRQ_PRIORITY_ERROR);
}

/**
 * @brief       Generate the software interrupt by writing 1 to the msip register
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetSWI(void)
{
  SysTimer->msip = 1U;

  return (0);
}

/**
 * @brief       Clear the software interrupt by writing 0 to the msip register
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_ClearSWI(void)
{
  SysTimer->msip = 0U;

  return (0);
}
