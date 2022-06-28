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
void __do_reset      (void);

/*----------------------------------------------------------------------------
  Interrupt Handler
 *----------------------------------------------------------------------------*/
void Reset_Handler    (void) __attribute__ ((naked));
void SysErr_Handler   (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void WDT_Handler      (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void DMA_EV_Handler   (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void DMA_ER_Handler   (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void GPIO_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void SWI_Handler      (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void SPI0_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void SPI1_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void I2C0_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void I2C1_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void UART0_Handler    (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void UART1_Handler    (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void UART2_Handler    (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void UART3_Handler    (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void SysTick_Handler  (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void TIM1_Handler     (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void PWM0_CNT_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void PWM0_CAP_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void PWM1_CNT_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));
void PWM1_CAP_Handler (void) __attribute__ ((fast_interrupt, weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Interrupt Vector Table
 *----------------------------------------------------------------------------*/
void Vectors(void)
{
  __ASM volatile(
    "jmp    Reset_Handler     \n"
    "jmp    SysErr_Handler    \n"
    "jmp    WDT_Handler       \n"
    "jmp    DMA_EV_Handler    \n"
    "jmp    DMA_ER_Handler    \n"
    "jmp    GPIO_Handler      \n"
    "jmp    SWI_Handler       \n"
    "jmp    SPI0_Handler      \n"
    "jmp    SPI1_Handler      \n"
    "jmp    I2C0_Handler      \n"
    "jmp    I2C1_Handler      \n"
    "jmp    UART0_Handler     \n"
    "jmp    UART1_Handler     \n"
    "jmp    UART2_Handler     \n"
    "jmp    UART3_Handler     \n"
    "jmp    SysTick_Handler   \n"
    "jmp    TIM1_Handler      \n"
    "jmp    PWM0_CNT_Handler  \n"
    "jmp    PWM0_CAP_Handler  \n"
    "jmp    PWM1_CNT_Handler  \n"
    "jmp    PWM1_CAP_Handler  \n"
  );
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  __ASM volatile(
      "cst    0x10                                       \n"
      "ldrsl  PRW,    0                                  \n"
      "ldrl   CONF,   0x0061                             \n"
      "ldrh   CONF,   0x00F9                             \n"
      "reset                                             \n"
      "ldrl   r28,    lo(Vectors)                        \n"
      "ldrh   r28,    hi(Vectors)                        \n"
      "ldrsl  DP1ID,  0x0001                             \n"
      "ldrsl  DP2ID,  0x0001                             \n"
      "movl   c7,     lit(__stack)                       \n"
      "ldrzs  FA,     lo(__IRQ_FA_Base)                  \n"
      "ldrzs  FB,     lo(__IRQ_FB_Base)                  \n"
      "jmp    __do_reset                                 \n"
  );
}

/*----------------------------------------------------------------------------
  Default Handler for Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

void __do_reset(void)
{
  SystemInit();                      /* CMSIS System Initialization           */
  __PROGRAM_START();                 /* Enter PreMain (C library entry point) */
}
