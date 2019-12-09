/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "asm/stm32f401xe.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void __NO_RETURN Default_Handler(void);
void __NO_RETURN Reset_Handler  (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));

void WWDG_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI5_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));

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
  Reset_Handler,                    /*     Reset Handler                      */
  NMI_Handler,                      /* -14 NMI Handler                        */
  HardFault_Handler,                /* -13 Hard Fault Handler                 */
  MemManage_Handler,                /* -12 MPU Fault Handler                  */
  BusFault_Handler,                 /* -11 Bus Fault Handler                  */
  UsageFault_Handler,               /* -10 Usage Fault Handler                */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  SVC_Handler,                      /*  -5 SVCall Handler                     */
  DebugMon_Handler,                 /*  -4 Debug Monitor Handler              */
  0,                                /*     Reserved                           */
  PendSV_Handler,                   /*  -2 PendSV Handler                     */
  SysTick_Handler,                  /*  -1 SysTick Handler                    */

  /* Interrupts */
  WWDG_IRQHandler,                  /* Window WatchDog                        */
  PVD_IRQHandler,                   /* PVD through EXTI Line detection        */
  TAMP_STAMP_IRQHandler,            /* Tamper and TimeStamps through the EXTI line */
  RTC_WKUP_IRQHandler,              /* RTC Wakeup through the EXTI line       */
  RCC_IRQHandler,                   /* RCC                                    */
  FLASH_IRQHandler,                 /* FLASH                                  */
  EXTI0_IRQHandler,                 /* EXTI Line0                             */
  EXTI1_IRQHandler,                 /* EXTI Line1                             */
  EXTI2_IRQHandler,                 /* EXTI Line2                             */
  EXTI3_IRQHandler,                 /* EXTI Line3                             */
  EXTI4_IRQHandler,                 /* EXTI Line4                             */
  DMA1_Stream0_IRQHandler,          /* DMA1 Stream 0                          */
  DMA1_Stream1_IRQHandler,          /* DMA1 Stream 1                          */
  DMA1_Stream2_IRQHandler,          /* DMA1 Stream 2                          */
  DMA1_Stream3_IRQHandler,          /* DMA1 Stream 3                          */
  DMA1_Stream4_IRQHandler,          /* DMA1 Stream 4                          */
  DMA1_Stream5_IRQHandler,          /* DMA1 Stream 5                          */
  DMA1_Stream6_IRQHandler,          /* DMA1 Stream 6                          */
  ADC_IRQHandler,                   /* ADC1, ADC2 and ADC3s                   */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  EXTI9_5_IRQHandler,               /* External Line[9:5]s                    */
  TIM1_BRK_TIM9_IRQHandler,         /* TIM1 Break and TIM9                    */
  TIM1_UP_TIM10_IRQHandler,         /* TIM1 Update and TIM10                  */
  TIM1_TRG_COM_TIM11_IRQHandler,    /* TIM1 Trigger and Commutation and TIM11 */
  TIM1_CC_IRQHandler,               /* TIM1 Capture Compare                   */
  TIM2_IRQHandler,                  /* TIM2                                   */
  TIM3_IRQHandler,                  /* TIM3                                   */
  TIM4_IRQHandler,                  /* TIM4                                   */
  I2C1_EV_IRQHandler,               /* I2C1 Event                             */
  I2C1_ER_IRQHandler,               /* I2C1 Error                             */
  I2C2_EV_IRQHandler,               /* I2C2 Event                             */
  I2C2_ER_IRQHandler,               /* I2C2 Error                             */
  SPI1_IRQHandler,                  /* SPI1                                   */
  SPI2_IRQHandler,                  /* SPI2                                   */
  USART1_IRQHandler,                /* USART1                                 */
  USART2_IRQHandler,                /* USART2                                 */
  0,                                /* Reserved                               */
  EXTI15_10_IRQHandler,             /* External Line[15:10]s                  */
  RTC_Alarm_IRQHandler,             /* RTC Alarm (A and B) through EXTI Line  */
  OTG_FS_WKUP_IRQHandler,           /* USB OTG FS Wakeup through EXTI line    */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  DMA1_Stream7_IRQHandler,          /* DMA1 Stream7                           */
  0,                                /* Reserved                               */
  SDIO_IRQHandler,                  /* SDIO                                   */
  TIM5_IRQHandler,                  /* TIM5                                   */
  SPI3_IRQHandler,                  /* SPI3                                   */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  DMA2_Stream0_IRQHandler,          /* DMA2 Stream 0                          */
  DMA2_Stream1_IRQHandler,          /* DMA2 Stream 1                          */
  DMA2_Stream2_IRQHandler,          /* DMA2 Stream 2                          */
  DMA2_Stream3_IRQHandler,          /* DMA2 Stream 3                          */
  DMA2_Stream4_IRQHandler,          /* DMA2 Stream 4                          */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  OTG_FS_IRQHandler,                /* USB OTG FS                             */
  DMA2_Stream5_IRQHandler,          /* DMA2 Stream 5                          */
  DMA2_Stream6_IRQHandler,          /* DMA2 Stream 6                          */
  DMA2_Stream7_IRQHandler,          /* DMA2 Stream 7                          */
  USART6_IRQHandler,                /* USART6                                 */
  I2C3_EV_IRQHandler,               /* I2C3 event                             */
  I2C3_ER_IRQHandler,               /* I2C3 error                             */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  FPU_IRQHandler,                   /* FPU                                    */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  SPI4_IRQHandler,                  /* SPI4                                   */
  SPI5_IRQHandler,                  /* SPI5                                   */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  SystemInit();                      /* CMSIS System Initialization           */
  __PROGRAM_START();                 /* Enter PreMain (C library entry point) */
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}
