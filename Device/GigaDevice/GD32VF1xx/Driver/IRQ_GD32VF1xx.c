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

/**
 * @brief
 */
static void exc_entry(void)
{
  uint32_t mcause_val = CSR_READ(CSR_MCAUSE);

  if ((mcause_val & MCAUSE_INT_Msk) == 0U) {
    IRQHandler_t handler = exc_vector[mcause_val & MCAUSE_CODE_Msk];
    if (handler != NULL) {
      handler();
    }
  }
  else {

  }
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
  CSR_WRITE(CSR_MTVEC, exc_entry);

  return (0);
}

/**
 * @brief       Default Handler for Exceptions / Interrupts.
 */
void Default_Handler(void)
{
  for (;;);
}
