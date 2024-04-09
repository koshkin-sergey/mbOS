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

#include <Core/Riscv/compiler.h>
#include <Core/Riscv/irq_riscv.h>
#include <asm/system_gd32vf1xx.h>

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/

void irq_vectors(void)        __attribute__((naked,    section(".text.vtable")));
void _enter(void)             __attribute__((noreturn, section(".text.init")));
void _exit(int code);
void Default_Handler(void);

/**
 * @brief Exception Handlers
 */
void IAM_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void IAF_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void ILI_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void BKP_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void LAM_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void LAF_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SAM_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SAF_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void ECU_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void ECS_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void IPF_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void LPF_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SPF_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));

/**
 * @brief Interrupt Handlers
 */
void WWDGT_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void LVD_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMPER_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void RCU_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_Channel6_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC0_1_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN0_TX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN0_RX0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN0_RX1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN0_EWMC_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI5_9_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_BRK_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_UP_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_TRG_CMT_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_Channel_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER2_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER3_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_EV_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_ER_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void USART0_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI10_15_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void USBFS_WKUP_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void EXMC_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER4_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART3_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER5_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER6_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_EWMC_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void USBFS_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));

/**
 * @brief Exception Vector Table
 */
extern const IRQHandler_t exc_vectors[];
       const IRQHandler_t exc_vectors[] = {
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
  0,              // Reserved
  SVC_Handler,    // Environment call from M-mode
  IPF_Handler,    // Instruction page fault
  LPF_Handler,    // Load page fault
  0,              // Reserved
  SPF_Handler     // Store/AMO page fault
};

extern void irq_vectors(void);
       void irq_vectors(void)
{
  __ASM volatile  (
    "j    _enter                      \n\t"
    ".word 0                          \n\t"        /* 1: Reserved */
    ".word 0                          \n\t"        /* 2: Reserved */
    ".word PendSV_Handler             \n\t"        /* 3: Machine software interrupt */
    ".word 0                          \n\t"        /* 4: Reserved */
    ".word 0                          \n\t"        /* 5: Reserved */
    ".word 0                          \n\t"        /* 6: Reserved */
    ".word SysTick_Handler            \n\t"        /* 7: Machine timer interrupt */
    ".word 0                          \n\t"        /* 8: Reserved */
    ".word 0                          \n\t"        /* 9: Reserved */
    ".word 0                          \n\t"        /* 10: Reserved */
    ".word 0                          \n\t"        /* 11: Reserved */
    ".word 0                          \n\t"        /* 12: Reserved */
    ".word 0                          \n\t"        /* 13: Reserved */
    ".word 0                          \n\t"        /* 14: Reserved */
    ".word 0                          \n\t"        /* 15: Reserved */
    ".word 0                          \n\t"        /* 16: Reserved */
    ".word 0                          \n\t"        /* 17: Bus Error interrupt */
    ".word 0                          \n\t"        /* 18: Performance Monitor */

    ".word WWDGT_IRQHandler           \n\t"
    ".word LVD_IRQHandler             \n\t"
    ".word TAMPER_IRQHandler          \n\t"
    ".word RTC_IRQHandler             \n\t"
    ".word FMC_IRQHandler             \n\t"
    ".word RCU_IRQHandler             \n\t"
    ".word EXTI0_IRQHandler           \n\t"
    ".word EXTI1_IRQHandler           \n\t"
    ".word EXTI2_IRQHandler           \n\t"
    ".word EXTI3_IRQHandler           \n\t"
    ".word EXTI4_IRQHandler           \n\t"
    ".word DMA0_Channel0_IRQHandler   \n\t"
    ".word DMA0_Channel1_IRQHandler   \n\t"
    ".word DMA0_Channel2_IRQHandler   \n\t"
    ".word DMA0_Channel3_IRQHandler   \n\t"
    ".word DMA0_Channel4_IRQHandler   \n\t"
    ".word DMA0_Channel5_IRQHandler   \n\t"
    ".word DMA0_Channel6_IRQHandler   \n\t"
    ".word ADC0_1_IRQHandler          \n\t"
    ".word CAN0_TX_IRQHandler         \n\t"
    ".word CAN0_RX0_IRQHandler        \n\t"
    ".word CAN0_RX1_IRQHandler        \n\t"
    ".word CAN0_EWMC_IRQHandler       \n\t"
    ".word EXTI5_9_IRQHandler         \n\t"
    ".word TIMER0_BRK_IRQHandler      \n\t"
    ".word TIMER0_UP_IRQHandler       \n\t"
    ".word TIMER0_TRG_CMT_IRQHandler  \n\t"
    ".word TIMER0_Channel_IRQHandler  \n\t"
    ".word TIMER1_IRQHandler          \n\t"
    ".word TIMER2_IRQHandler          \n\t"
    ".word TIMER3_IRQHandler          \n\t"
    ".word I2C0_EV_IRQHandler         \n\t"
    ".word I2C0_ER_IRQHandler         \n\t"
    ".word I2C1_EV_IRQHandler         \n\t"
    ".word I2C1_ER_IRQHandler         \n\t"
    ".word SPI0_IRQHandler            \n\t"
    ".word SPI1_IRQHandler            \n\t"
    ".word USART0_IRQHandler          \n\t"
    ".word USART1_IRQHandler          \n\t"
    ".word USART2_IRQHandler          \n\t"
    ".word EXTI10_15_IRQHandler       \n\t"
    ".word RTC_Alarm_IRQHandler       \n\t"
    ".word USBFS_WKUP_IRQHandler      \n\t"
    ".word 0                          \n\t"
    ".word 0                          \n\t"
    ".word 0                          \n\t"
    ".word 0                          \n\t"
    ".word 0                          \n\t"
    ".word EXMC_IRQHandler            \n\t"
    ".word 0                          \n\t"
    ".word TIMER4_IRQHandler          \n\t"
    ".word SPI2_IRQHandler            \n\t"
    ".word UART3_IRQHandler           \n\t"
    ".word UART4_IRQHandler           \n\t"
    ".word TIMER5_IRQHandler          \n\t"
    ".word TIMER6_IRQHandler          \n\t"
    ".word DMA1_Channel0_IRQHandler   \n\t"
    ".word DMA1_Channel1_IRQHandler   \n\t"
    ".word DMA1_Channel2_IRQHandler   \n\t"
    ".word DMA1_Channel3_IRQHandler   \n\t"
    ".word DMA1_Channel4_IRQHandler   \n\t"
    ".word 0                          \n\t"
    ".word 0                          \n\t"
    ".word CAN1_TX_IRQHandler         \n\t"
    ".word CAN1_RX0_IRQHandler        \n\t"
    ".word CAN1_RX1_IRQHandler        \n\t"
    ".word CAN1_EWMC_IRQHandler       \n\t"
    ".word USBFS_IRQHandler           \n\t"
  );
}

void _enter(void)
{
  __ASM volatile  (
    "csrc mstatus, 0x8                \n\t"
    "la      a0, _enter               \n\t"
    "li      a1, 1                    \n\t"
    "slli    a1, a1, 29               \n\t"
    "bleu    a1, a0, _start0800       \n\t"
    "srli    a1, a1, 2                \n\t"
    "bleu    a1, a0, _start0800       \n\t"
    "la      a0, _start0800           \n\t"
    "add     a0, a0, a1               \n\t"
    "jr      a0                       \n\t"
    "_start0800:                      \n\t"
    ".option push                     \n\t"
    ".option norelax                  \n\t"
    "la   gp, __global_pointer$       \n\t"
    ".option pop                      \n\t"
    "la   sp, _sp                     \n\t"
  );

  SystemInit();
  __PROGRAM_START();
}

/**
 * @brief       On Release, call the hardware reset procedure.
 *              On Debug we just enter an infinite loop,
 *              to be used as landmark when halting the debugger.
 * @param[in]   code
 */
void _exit(int code __attribute__((unused)))
{
  for (;;);
}

/**
 * @brief       Default Handler.
 */
void Default_Handler(void)
{
  for (;;);
}
