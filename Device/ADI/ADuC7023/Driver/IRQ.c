/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include "Kernel/irq.h"
#include "asm/aduc7023.h"

#define VECTOR_TABLE_ATTRIBUTE  __attribute__((aligned(128), section(".bss.isr_vector")))

static uint32_t fiq_mode;

/*------------------------------------------------------------------------------
 * Interrupt Vector table
 *----------------------------------------------------------------------------*/
static IRQHandler_t isr_vector[VECTOR_NUMBER] VECTOR_TABLE_ATTRIBUTE = { 0U };

/**
 * @brief       Initialize interrupt controller.
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Initialize(void)
{
  uint32_t addr;

  addr = (uint32_t)&isr_vector[0];
  if ((addr & ~(IRQ_BASER_Msk << 7U)) != 0U) {
    return (-1);
  }

  for (uint32_t i = 0; i < VECTOR_NUMBER; ++i) {
    isr_vector[i] = NULL;
  }

  fiq_mode = 0UL;
  IRQ->BASE = addr >> 7U;
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
  if (irqn < 0 || irqn >= VECTOR_NUMBER || handler == NULL) {
    return (-1);
  }

  isr_vector[irqn] = handler;

  return (0);
}

/**
 * @brief       Get the registered interrupt handler.
 * @param[in]   irqn    interrupt ID number
 * @return      registered interrupt handler function address.
 */
IRQHandler_t IRQ_GetHandler(IRQn_ID_t irqn)
{
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
    return (NULL);
  }

  return (isr_vector[irqn]);
}

/**
 * @brief       Enable interrupt.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Enable(IRQn_ID_t irqn)
{
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
    return (-1);
  }

  if ((fiq_mode & (1UL << irqn)) == 0UL) {
    IRQ->EN = (1UL << irqn);
  }
  else {
    FIQ->EN = (1UL << irqn);
  }

  return (0);
}

/**
 * @brief       Disable interrupt.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Disable(IRQn_ID_t irqn)
{
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
    return (-1);
  }

  if ((fiq_mode & (1UL << irqn)) == 0UL) {
    IRQ->CLR = (1UL << irqn);
  }
  else {
    FIQ->CLR = (1UL << irqn);
  }

  return (0);
}

/**
 * @brief       Get interrupt enable state.
 * @param[in]   irqn    interrupt ID number
 * @return      0 - interrupt is disabled, 1 - interrupt is enabled.
 */
uint32_t IRQ_GetEnableState(IRQn_ID_t irqn)
{
  uint32_t state;

  if ((fiq_mode & (1UL << irqn)) == 0UL) {
    state = (IRQ->EN & (1UL << irqn)) >> irqn;
  }
  else {
    state = (FIQ->EN & (1UL << irqn)) >> irqn;
  }

  return (state);
}

/**
 * @brief       Configure interrupt request mode.
 * @param[in]   irqn    interrupt ID number
 * @param[in]   mode    mode configuration
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetMode(IRQn_ID_t irqn, uint32_t mode)
{
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
  return (0U);
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
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
    return (-1);
  }

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
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
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
  return (0U);
}

/**
 * @brief       Clear interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_ClearPending(IRQn_ID_t irqn)
{
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
    return (-1);
  }

  return (0);
}

/**
 * @brief       Set interrupt priority value.
 * @param[in]   irqn      interrupt ID number
 * @param[in]   priority  interrupt priority value
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriority(IRQn_ID_t irqn, uint32_t priority)
{
  if (irqn < 0 || irqn >= VECTOR_NUMBER) {
    return (-1);
  }

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
  return (0U);
}

/**
 * @brief       Set priority masking threshold.
 * @param[in]   priority  priority masking threshold value
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriorityMask(uint32_t priority)
{
  return (0);
}

/**
 * @brief       Get priority masking threshold
 * @return      current priority masking threshold value with optional
 *              IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriorityMask(void)
{
  return (0U);
}

/// Set priority grouping field split point
/// \param[in]     bits          number of MSB bits included in the group priority field comparison
/// \return 0 on success, -1 on error.
/**
 * @brief       Set priority grouping field split point
 * @param[in]   bits    number of MSB bits included in the group priority field
 *                      comparison
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriorityGroupBits(uint32_t bits)
{
  return (0);
}

/**
 * @brief       Get priority grouping field split point
 * @return      current number of MSB bits included in the group priority field
 *              comparison with optional IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriorityGroupBits(void)
{
  return (0U);
}
