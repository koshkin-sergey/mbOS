/*
 * Copyright (C) 2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/rp2040.h>

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);
extern             void _exit(int code);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler  (void);
            void Default_Handler(void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));

void TIMER_ALRM_0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER_ALRM_1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER_ALRM_2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER_ALRM_3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void XIP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO0_0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO0_1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO1_0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO1_1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void IO_BANK0_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void IO_QSPI_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_PROC0_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_PROC1_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void CLOCKS_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const pFunc __VECTOR_TABLE[];
       const pFunc __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {
  (pFunc)(&__INITIAL_SP),           /*     Initial Stack Pointer              */
  Reset_Handler,                    /* -15 Reset Handler                      */
  NMI_Handler,                      /* -14 NMI Handler                        */
  HardFault_Handler,                /* -13 Hard Fault Handler                 */
  0,                                /* -12 Reserved                           */
  0,                                /* -11 Reserved                           */
  0,                                /* -10 Reserved                           */
  0,                                /*  -9 Reserved                           */
  0,                                /*  -8 Reserved                           */
  0,                                /*  -7 Reserved                           */
  0,                                /*  -6 Reserved                           */
  SVC_Handler,                      /*  -5 SVCall Handler                     */
  0,                                /*  -4 Reserved                           */
  0,                                /*  -3 Reserved                           */
  PendSV_Handler,                   /*  -2 PendSV Handler                     */
  SysTick_Handler,                  /*  -1 SysTick Handler                    */

  /* Interrupts */
  TIMER_ALRM_0_IRQHandler,          /*  0 Timer Alarm 0 Interrupt             */
  TIMER_ALRM_1_IRQHandler,          /*  1 Timer Alarm 1 Interrupt             */
  TIMER_ALRM_2_IRQHandler,          /*  2 Timer Alarm 2 Interrupt             */
  TIMER_ALRM_3_IRQHandler,          /*  3 Timer Alarm 3 Interrupt             */
  PWM_IRQHandler,                   /*  4 PWM Interrupt                       */
  USB_IRQHandler,                   /*  5 USB Interrupt                       */
  XIP_IRQHandler,                   /*  6 XIP Interrupt                       */
  PIO0_0_IRQHandler,                /*  7                                     */
  PIO0_1_IRQHandler,                /*  8                                     */
  PIO1_0_IRQHandler,                /*  9                                     */
  PIO1_1_IRQHandler,                /* 10                                     */
  DMA0_IRQHandler,                  /* 11 DMA0 Interrupt                      */
  DMA1_IRQHandler,                  /* 12 DMA1 Interrupt                      */
  IO_BANK0_IRQHandler,              /* 13                                     */
  IO_QSPI_IRQHandler,               /* 14                                     */
  SIO_PROC0_IRQHandler,             /* 15                                     */
  SIO_PROC1_IRQHandler,             /* 16                                     */
  CLOCKS_IRQHandler,                /* 17                                     */
  SPI0_IRQHandler,                  /* 18 SPI0 Interrupt                      */
  SPI1_IRQHandler,                  /* 19 SPI1 Interrupt                      */
  UART0_IRQHandler,                 /* 20 UART0 Interrupt                     */
  UART1_IRQHandler,                 /* 21 UART1 Interrupt                     */
  ADC_IRQHandler,                   /* 22 ADC Interrupt                       */
  I2C0_IRQHandler,                  /* 23 I2C0 Interrupt                      */
  I2C1_IRQHandler,                  /* 24 I2C1 Interrupt                      */
  RTC_IRQHandler,                   /* 25 RTC Interrupt                       */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN
void Reset_Handler(void)
{
  SystemInit();                      /* CMSIS System Initialization           */
  __PROGRAM_START();                 /* Enter PreMain (C library entry point) */
}

/**
 * @brief       Default Handler for Exceptions / Interrupts.
 */
void Default_Handler(void)
{
  for (;;);
}

/**
 * @brief       On Release, call the hardware reset procedure.
 *              On Debug we just enter an infinite loop,
 *              to be used as landmark when halting the debugger.
 * @param[in]   code
 */
void _exit(int code __attribute__((unused)))
{
#if !defined (DEBUG)
  NVIC_SystemReset();
#endif

  for (;;);
}
