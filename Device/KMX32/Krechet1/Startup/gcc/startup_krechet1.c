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

#define isr_prologue()            __ASM volatile(                  \
                                    "pushr  LC                  \n"\
                                    "pushr  SMC                 \n"\
                                    "pushr  CLR                 \n"\
                                    "pushr  PRW                 \n"\
                                    "push   DP2                 \n"\
                                    "push   DP1                 \n"\
                                    "mfprs  DP2, ILR_PC         \n"\
                                    "mfprs  DP1, ILR_PSW        \n"\
                                    "push   DP2                 \n"\
                                    "push   DP1                 \n"\
                                    "srfb   8                   \n"\
                                    "srfa   8                   \n"\
                                  )

#define isr_epilogue()            __ASM volatile(                  \
                                    "jsr    ContextSwitch       \n"\
                                    "rsfa   8                   \n"\
                                    "rsfb   8                   \n"\
                                    "pop    DP1                 \n"\
                                    "pop    DP2                 \n"\
                                    "mtprs  ILR_PSW, DP1        \n"\
                                    "mtprs  ILR_PC,  DP2        \n"\
                                    "pop    DP1                 \n"\
                                    "pop    DP2                 \n"\
                                    "popr   PRW                 \n"\
                                    "popr   CLR                 \n"\
                                    "popr   SMC                 \n"\
                                    "popr   LC                  \n"\
                                  )

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void ContextSwitch   (void);
void Default_Handler (void);
void Vectors         (void) __attribute__ ((naked, section(".vectors")));
void __do_reset      (void);

/*----------------------------------------------------------------------------
  Interrupt Handler
 *----------------------------------------------------------------------------*/
void SysErr_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void WDT_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_EV_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_ER_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIO_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SWI_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI0_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void UART2_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void UART3_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM0_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_CNT_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_CAP_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_CNT_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_CAP_Handler (void) __attribute__ ((weak, alias("Default_Handler")));


void _Reset_Handler    (void) __attribute__ ((fast_interrupt));
void _SysErr_Handler   (void) __attribute__ ((fast_interrupt));
void _WDT_Handler      (void) __attribute__ ((fast_interrupt));
void _DMA_EV_Handler   (void) __attribute__ ((fast_interrupt));
void _DMA_ER_Handler   (void) __attribute__ ((fast_interrupt));
void _GPIO_Handler     (void) __attribute__ ((fast_interrupt));
void _SWI_Handler      (void) __attribute__ ((fast_interrupt));
void _SPI0_Handler     (void) __attribute__ ((fast_interrupt));
void _SPI1_Handler     (void) __attribute__ ((fast_interrupt));
void _I2C0_Handler     (void) __attribute__ ((fast_interrupt));
void _I2C1_Handler     (void) __attribute__ ((fast_interrupt));
void _UART0_Handler    (void) __attribute__ ((fast_interrupt));
void _UART1_Handler    (void) __attribute__ ((fast_interrupt));
void _UART2_Handler    (void) __attribute__ ((fast_interrupt));
void _UART3_Handler    (void) __attribute__ ((fast_interrupt));
void _TIM0_Handler     (void) __attribute__ ((fast_interrupt));
void _TIM1_Handler     (void) __attribute__ ((fast_interrupt));
void _PWM0_CNT_Handler (void) __attribute__ ((fast_interrupt));
void _PWM0_CAP_Handler (void) __attribute__ ((fast_interrupt));
void _PWM1_CNT_Handler (void) __attribute__ ((fast_interrupt));
void _PWM1_CAP_Handler (void) __attribute__ ((fast_interrupt));

/*----------------------------------------------------------------------------
  Interrupt Vector Table
 *----------------------------------------------------------------------------*/
void Vectors(void)
{
  __ASM volatile(
      "jmp    _Reset_Handler                       \n"
      "jmp    _SysErr_Handler                      \n"
      "jmp    _WDT_Handler                         \n"
      "jmp    _DMA_EV_Handler                      \n"
      "jmp    _DMA_ER_Handler                      \n"
      "jmp    _GPIO_Handler                        \n"
      "jmp    _SWI_Handler                         \n"
      "jmp    _SPI0_Handler                        \n"
      "jmp    _SPI1_Handler                        \n"
      "jmp    _I2C0_Handler                        \n"
      "jmp    _I2C1_Handler                        \n"
      "jmp    _UART0_Handler                       \n"
      "jmp    _UART1_Handler                       \n"
      "jmp    _UART2_Handler                       \n"
      "jmp    _UART3_Handler                       \n"
      "jmp    _TIM0_Handler                        \n"
      "jmp    _TIM1_Handler                        \n"
      "jmp    _PWM0_CNT_Handler                    \n"
      "jmp    _PWM0_CAP_Handler                    \n"
      "jmp    _PWM1_CNT_Handler                    \n"
      "jmp    _PWM1_CAP_Handler                    \n"
  );
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void _Reset_Handler(void)
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
      "ldrzs  FA,     lo(__FA_base)                      \n"
      "ldrzs  FB,     lo(__FB_base)                      \n"
      "jmp    __do_reset                                 \n"
  );
}

void _SysErr_Handler(void)
{
  while(1U);
}

void _WDT_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr WDT_Handler");
  isr_epilogue();
}

void _DMA_EV_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr DMA_EV_Handler");
  isr_epilogue();
}

void _DMA_ER_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr DMA_ER_Handler");
  isr_epilogue();
}

void _GPIO_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr GPIO_Handler");
  isr_epilogue();
}

void _SWI_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr SWI_Handler");
  isr_epilogue();
}

void _SPI0_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr SPI0_Handler");
  isr_epilogue();
}

void _SPI1_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr SPI1_Handler");
  isr_epilogue();
}

void _I2C0_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr I2C0_Handler");
  isr_epilogue();
}

void _I2C1_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr I2C1_Handler");
  isr_epilogue();
}

void _UART0_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr UART0_Handler");
  isr_epilogue();
}

void _UART1_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr UART1_Handler");
  isr_epilogue();
}

void _UART2_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr UART2_Handler");
  isr_epilogue();
}

void _UART3_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr UART3_Handler");
  isr_epilogue();
}

void _TIM0_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr SysTick_Handler");
  isr_epilogue();
}

void _TIM1_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr TIM1_Handler");
  isr_epilogue();
}

void _PWM0_CNT_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr PWM0_CNT_Handler");
  isr_epilogue();
}

void _PWM0_CAP_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr PWM0_CAP_Handler");
  isr_epilogue();
}

void _PWM1_CNT_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr PWM1_CNT_Handler");
  isr_epilogue();
}

void _PWM1_CAP_Handler(void)
{
  isr_prologue();
  __ASM volatile("jsr PWM1_CAP_Handler");
  isr_epilogue();
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
