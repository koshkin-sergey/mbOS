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
#include <asm/gd32vf103xx.h>
#include <Core/Riscv/irq_riscv.h>

void Default_Handler(void);

/**
 * @brief Exception Entry
 */
void exc_entry(void)   __attribute__ ((weak, alias("Default_Handler")));

/**
 * @brief Exception Handlers
 */
void IAM_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void IAF_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void ILI_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void BKP_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void LAM_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void LAF_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SAM_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SAF_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void ECU_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void ECS_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void ECM_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void IPF_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void LPF_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SPF_Handler(void) __attribute__ ((weak, alias("Default_Handler")));

/**
 * @brief Exception Vector Table
 */
static const IRQHandler_t exc_vector[EXCn_MAX_NUM] = {
  IAM_Handler,    // Instruction address misaligned
  IAF_Handler,    // Instruction access fault
  ILI_Handler,    // Illegal instruction
  BKP_Handler,    // Breakpoint
  LAM_Handler,    // Load address misaligned
  LAF_Handler,    // Load access fault
  SAM_Handler,    // Store/AMO address misaligned
  SAF_Handler,    // Store/AMO access fault
  ECU_Handler,    // Environment call from U-mode
  ECS_Handler,    // Environment call from S-mode
  NULL,           // Reserved
  ECM_Handler,    // Environment call from M-mode
  IPF_Handler,    // Instruction page fault
  LPF_Handler,    // Load page fault
  NULL,           // Reserved
  SPF_Handler     // Store/AMO page fault
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Initialize interrupt controller.
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Initialize(void)
{
  CSR_WRITE(CSR_MSCRATCH, 0);
  CSR_WRITE(CSR_MTVEC, exc_entry);
  CSR_WRITE(CSR_MSTATUS, MSTATUS_MIE);

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

  return (0);
}

/**
 * @brief       Get the registered interrupt handler.
 * @param[in]   irqn   interrupt or exception ID number
 * @return      registered interrupt handler function address.
 */
IRQHandler_t IRQ_GetHandler(IRQn_ID_t irqn)
{
  IRQHandler_t handler = NULL;

  if ((irqn & MCAUSE_INT_Msk) == 0U) {
    handler = exc_vector[irqn & MCAUSE_CODE_Msk];
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
  (void) irqn;

  return (0);
}

/**
 * @brief       Disable interrupt.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_Disable(IRQn_ID_t irqn)
{
  (void) irqn;

  return (0);
}

/**
 * @brief       Get interrupt enable state.
 * @param[in]   irqn    interrupt ID number
 * @return      0 - interrupt is disabled, 1 - interrupt is enabled.
 */
uint32_t IRQ_GetEnableState(IRQn_ID_t irqn)
{
  (void) irqn;

  return (0U);
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
 * @brief       Set interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPending(IRQn_ID_t irqn)
{
  (void) irqn;

  return (0);
}

/**
 * @brief       Get interrupt pending flag.
 * @param[in]   irqn    interrupt ID number
 * @return      0 - interrupt is not pending, 1 - interrupt is pending.
 */
uint32_t IRQ_GetPending(IRQn_ID_t irqn)
{
  (void) irqn;

  return (0U);
}

/**
 * @brief       Set interrupt priority value.
 * @param[in]   irqn      interrupt ID number
 * @param[in]   priority  interrupt priority value
 * @return      0 on success, -1 on error.
 */
int32_t IRQ_SetPriority(IRQn_ID_t irqn, uint32_t priority)
{
  (void) irqn;
  (void) priority;

  return (-1);
}

/**
 * @brief       Get interrupt priority.
 * @param[in]   irqn      interrupt ID number
 * @return      current interrupt priority value with optional
 *              IRQ_PRIORITY_ERROR bit set.
 */
uint32_t IRQ_GetPriority(IRQn_ID_t irqn)
{
  (void) irqn;

  return (0U);
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
 * @brief       Default Handler for Exceptions / Interrupts.
 */
void Default_Handler(void)
{
  for (;;);
}
