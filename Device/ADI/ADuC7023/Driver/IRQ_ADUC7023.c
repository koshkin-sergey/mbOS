/*
 * Copyright (C) 2021-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <stddef.h>
#include <string.h>
#include "Core/Arm/irq_ctrl.h"
#include "asm/aduc7023.h"

#define RAM_INTVEC_SIZE   16U
#define RAM_INTVEC_ATTR   __attribute__((used, section(".vectors_ram")))
#define IRQ_TABLE_ATTR    __attribute__((used, aligned(128), section(".bss.irq_table")))

typedef struct IRQ_MODE_INFO_s {
  uint32_t type;      /* Type of interrupt (IRQ or FIQ) */
} IRQ_MODE_INFO_t;

static IRQ_MODE_INFO_t irq_mode;

/*------------------------------------------------------------------------------
 * Interrupt Vector table
 *----------------------------------------------------------------------------*/
#if defined (RAM_INTVEC)

static uint32_t ram_intvec[RAM_INTVEC_SIZE] RAM_INTVEC_ATTR;

#endif

static IRQHandler_t irq_table[IRQ_VECTOR_COUNT] IRQ_TABLE_ATTR = { 0U };

/**
 * @brief       Initialize interrupt controller.
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Initialize(void)
{
  uint32_t addr;

  addr = (uint32_t)&irq_table[0];
  if ((addr & ~(IRQ_BASER_Msk << 7U)) != 0U) {
    return (-1);
  }

  irq_mode.type = 0UL;

  /* Disable all interrupt sources */
  IRQ->CLR = IRQ_CLR_DEF_VALUE;
  FIQ->CLR = FIQ_CLR_DEF_VALUE;

  /* Set interrupt priorities to highest priority */
  IRQ->P[0] = IRQ_PRIO_DEF_VALUE;
  IRQ->P[1] = IRQ_PRIO_DEF_VALUE;
  IRQ->P[2] = IRQ_PRIO_DEF_VALUE;

#if defined (RAM_INTVEC)

  uint32_t *flash_ptr = (uint32_t *)FLASH_BASE;

  for (uint32_t i = 0; i < RAM_INTVEC_SIZE; ++i) {
    ram_intvec[i] = flash_ptr[i];
  }

  SYS->REMAP = SYS_REMAP_SRAM;

#endif

  /* Set to NULL all interrupt handlers */
  for (uint32_t i = 0; i < IRQ_VECTOR_COUNT; ++i) {
    irq_table[i] = (IRQHandler_t)NULL;
  }

  IRQ->BASE = addr >> 7U;

  /* Enable IRQ and FIQ signal lines */
  IRQ->CONN = IRQ_CONN_ENIRQN | IRQ_CONN_ENFIQN;

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
  int32_t status;

  if (irqn >= 0 && irqn < IRQ_VECTOR_COUNT && handler != NULL) {
    irq_table[irqn] = handler;
    status = 0;
  }
  else {
    status = -1;
  }

  return (status);
}

/**
 * @brief       Get the registered interrupt handler.
 * @param[in]   irqn    interrupt ID number
 * @return      registered interrupt handler function address.
 */
IRQHandler_t IRQ_GetHandler(IRQn_ID_t irqn)
{
  IRQHandler_t handler;

  if (irqn >= 0 && irqn < IRQ_VECTOR_COUNT) {
    handler = irq_table[irqn];
  }
  else {
    handler = NULL;
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
   int32_t status;
  uint32_t irq_msk;

  if (irqn >= 0 && irqn < IRQ_VECTOR_COUNT) {
    irq_msk = 1UL << irqn;

    if ((irq_mode.type & irq_msk) == 0UL) {
      IRQ->EN = irq_msk;
    }
    else {
      FIQ->EN = irq_msk;
    }

    status = 0;
  }
  else {
    status = -1;
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
   int32_t status;
  uint32_t irq_msk;

  if (irqn >= 0 && irqn < IRQ_VECTOR_COUNT) {
    irq_msk = 1UL << irqn;

    if ((irq_mode.type & irq_msk) == 0UL) {
      IRQ->CLR = irq_msk;
    }
    else {
      FIQ->CLR = irq_msk;
    }

    status = 0;
  }
  else {
    status = -1;
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
  uint32_t irq;
  uint32_t fiq;
  uint32_t enable;

  if ((irqn >= 0) && (irqn < IRQ_VECTOR_COUNT)) {
    irq = IRQ->EN >> irqn;
    fiq = FIQ->EN >> irqn;
    enable = (irq | fiq) & 1U;
  }
  else {
    enable = 0U;
  }

  return (enable);
}

/**
 * @brief       Configure interrupt request mode.
 * @param[in]   irqn    interrupt ID number
 * @param[in]   mode    mode configuration
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetMode(IRQn_ID_t irqn, uint32_t mode)
{
  uint32_t mask;

  if ((irqn < 0) || (irqn >= IRQ_VECTOR_COUNT)) {
    return (-1);
  }

  mask = 1UL << irqn;
  switch (mode & IRQ_MODE_TYPE_Msk) {
    case IRQ_MODE_TYPE_IRQ:
      irq_mode.type &= ~mask;
      break;

    case IRQ_MODE_TYPE_FIQ:
      irq_mode.type |= mask;
      break;
  }

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
  uint32_t mode;

  if ((irqn < 0) || (irqn >= IRQ_VECTOR_COUNT)) {
    return (IRQ_MODE_ERROR);
  }

  if ((irq_mode.type & (1UL << irqn)) == 0UL) {
    mode = IRQ_MODE_TYPE_IRQ;
  }
  else {
    mode = IRQ_MODE_TYPE_FIQ;
  }

  return (mode);
}

/**
 * @brief       Get ID number of current interrupt request (IRQ).
 * @return      interrupt ID number.
 */
IRQn_ID_t IRQ_GetActiveIRQ(void)
{
  uint32_t irqn = (IRQ->VEC & IRQ_VEC_ID_Msk) >> IRQ_VEC_ID_Pos;

  return ((IRQn_ID_t)irqn);
}

/**
 * @brief       Get ID number of current fast interrupt request (FIQ).
 * @return      interrupt ID number.
 */
IRQn_ID_t IRQ_GetActiveFIQ(void)
{
  uint32_t fiqn = (FIQ->VEC & FIQ_VEC_ID_Msk) >> FIQ_VEC_ID_Pos;

  return ((IRQn_ID_t)fiqn);
}

/**
 * @brief       Signal end of interrupt processing.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_EndOfInterrupt(IRQn_ID_t irqn)
{
  (void) irqn;

  IRQ->STAN = 0xFF;

  return (0);
}

/**
 * @brief       Set interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPending(IRQn_ID_t irqn)
{
  if (irqn < 0 || irqn >= IRQ_VECTOR_COUNT) {
    return (-1);
  }

  return (0);
}

/**
 * @brief       Get interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 - interrupt is not pending, 1 - interrupt is pending.
 */
uint32_t IRQ_GetPending(IRQn_ID_t irqn)
{
  uint32_t sig;

  if (irqn < 0 || irqn >= IRQ_VECTOR_COUNT) {
    return (0U);
  }

  if ((irq_mode.type & (1UL << irqn)) == 0UL) {
    sig = IRQ->SIG;
  }
  else {
    sig = FIQ->SIG;
  }

  return ((sig >> irqn) & 1UL);
}

/**
 * @brief       Clear interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_ClearPending(IRQn_ID_t irqn)
{
  (void) irqn;

  return (-1);
}

/**
 * @brief       Set interrupt priority value.
 * @param[in]   irqn      interrupt ID number
 * @param[in]   priority  interrupt priority value
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriority(IRQn_ID_t irqn, uint32_t priority)
{
  uint32_t idx;
  uint32_t offset;
  uint32_t prior;

  if (irqn == 0 || irqn >= IRQ_VECTOR_COUNT) {
    return (-1);
  }

  idx    = IRQ_PRIORITY_IDX(irqn);
  offset = IRQ_PRIORITY_OFS(irqn);

  prior = IRQ->P[idx] & ~(IRQ_PRIORITY_BIT_Msk << offset);
  IRQ->P[idx] = prior | (priority << offset);

  return (0);
}

/**
 * @brief       Get interrupt priority.
 * @param[in]   irqn      interrupt ID number
 * @return      current interrupt priority value with optional
 *              IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriority(IRQn_ID_t irqn)
{
  uint32_t priority;
  uint32_t idx;
  uint32_t offset;

  if ((irqn >= 0) && (irqn < IRQ_VECTOR_COUNT)) {
    idx    = IRQ_PRIORITY_IDX(irqn);
    offset = IRQ_PRIORITY_OFS(irqn);
    priority = (IRQ->P[idx] >> offset) & IRQ_PRIORITY_BIT_Msk;
  }
  else {
    priority = IRQ_PRIORITY_ERROR;
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
