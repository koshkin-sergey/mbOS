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

#include <asm/rp2350.h>

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
void MemManage_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));

void TIMER0_ALRM_0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_ALRM_1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_ALRM_2_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_ALRM_3_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_ALRM_0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_ALRM_1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_ALRM_2_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_ALRM_3_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO0_0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO0_1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO1_0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO1_1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO2_0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PIO2_1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void IO_BANK0_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void IO_BANK0_NS_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void IO_QSPI_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void IO_QSPI_NS_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_FIFO_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_BELL_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_FIFO_NS_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_BELL_NS_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void SIO_MTIMECMP_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void CLOCKS_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void OTP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TRNG_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PLL_SYS_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void PLL_USB_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void POWMAN_POW_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void POWMAN_TIMER_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));

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
  MemManage_Handler,                /* -12 MPU Fault Handler                  */
  BusFault_Handler,                 /* -11 Bus Fault Handler                  */
  UsageFault_Handler,               /* -10 Usage Fault Handler                */
  SecureFault_Handler,              /*  -9 Secure Fault Handler               */
  0,                                /*  -8 Reserved                           */
  0,                                /*  -7 Reserved                           */
  0,                                /*  -6 Reserved                           */
  SVC_Handler,                      /*  -5 SVCall Handler                     */
  DebugMon_Handler,                 /*  -4 Debug Monitor Handler              */
  0,                                /*  -3 Reserved                           */
  PendSV_Handler,                   /*  -2 PendSV Handler                     */
  SysTick_Handler,                  /*  -1 SysTick Handler                    */

  /* Interrupts */
  TIMER0_ALRM_0_IRQHandler,         /*  0 Timer0 Alarm 0 Interrupt            */
  TIMER0_ALRM_1_IRQHandler,         /*  1 Timer0 Alarm 1 Interrupt            */
  TIMER0_ALRM_2_IRQHandler,         /*  2 Timer0 Alarm 2 Interrupt            */
  TIMER0_ALRM_3_IRQHandler,         /*  3 Timer0 Alarm 3 Interrupt            */
  TIMER1_ALRM_0_IRQHandler,         /*  4 Timer1 Alarm 0 Interrupt            */
  TIMER1_ALRM_1_IRQHandler,         /*  5 Timer1 Alarm 1 Interrupt            */
  TIMER1_ALRM_2_IRQHandler,         /*  6 Timer1 Alarm 2 Interrupt            */
  TIMER1_ALRM_3_IRQHandler,         /*  7 Timer1 Alarm 3 Interrupt            */
  PWM0_IRQHandler,                  /*  8 PWM0 Interrupt                      */
  PWM1_IRQHandler,                  /*  9 PWM1 Interrupt                      */
  DMA0_IRQHandler,                  /* 10 DMA0 Interrupt                      */
  DMA1_IRQHandler,                  /* 11 DMA1 Interrupt                      */
  DMA2_IRQHandler,                  /* 12 DMA2 Interrupt                      */
  DMA3_IRQHandler,                  /* 13 DMA3 Interrupt                      */
  USB_IRQHandler,                   /* 14 USB Interrupt                       */
  PIO0_0_IRQHandler,                /* 15                                     */
  PIO0_1_IRQHandler,                /* 16                                     */
  PIO1_0_IRQHandler,                /* 17                                     */
  PIO1_1_IRQHandler,                /* 18                                     */
  PIO2_0_IRQHandler,                /* 19                                     */
  PIO2_1_IRQHandler,                /* 20                                     */
  IO_BANK0_IRQHandler,              /* 21                                     */
  IO_BANK0_NS_IRQHandler,           /* 22                                     */
  IO_QSPI_IRQHandler,               /* 23                                     */
  IO_QSPI_NS_IRQHandler,            /* 24                                     */
  SIO_FIFO_IRQHandler,              /* 25                                     */
  SIO_BELL_IRQHandler,              /* 26                                     */
  SIO_FIFO_NS_IRQHandler,           /* 27                                     */
  SIO_BELL_NS_IRQHandler,           /* 28                                     */
  SIO_MTIMECMP_IRQHandler,          /* 29                                     */
  CLOCKS_IRQHandler,                /* 30                                     */
  SPI0_IRQHandler,                  /* 31 SPI0 Interrupt                      */
  SPI1_IRQHandler,                  /* 32 SPI1 Interrupt                      */
  UART0_IRQHandler,                 /* 33 UART0 Interrupt                     */
  UART1_IRQHandler,                 /* 34 UART1 Interrupt                     */
  ADC_IRQHandler,                   /* 35 ADC Interrupt                       */
  I2C0_IRQHandler,                  /* 36 I2C0 Interrupt                      */
  I2C1_IRQHandler,                  /* 37 I2C1 Interrupt                      */
  OTP_IRQHandler,                   /* 38 RTC Interrupt                       */
  TRNG_IRQHandler,                  /* 39 TRNG Interrupt                      */
  0,                                /* 40 Reserved                            */
  0,                                /* 41 Reserved                            */
  PLL_SYS_IRQHandler,               /* 42                                     */
  PLL_USB_IRQHandler,               /* 43                                     */
  POWMAN_POW_IRQHandler,            /* 44                                     */
  POWMAN_TIMER_IRQHandler,          /* 45                                     */
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
