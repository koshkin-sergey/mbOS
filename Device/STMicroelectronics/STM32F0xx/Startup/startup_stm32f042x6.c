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

#include "stm32f042x6.h"

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
void SVC_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));

void WWDG_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_VDDIO2_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TSC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_5_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM14_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM16_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM17_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CEC_CAN_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));

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
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  SVC_Handler,                      /*  -5 SVCall Handler                     */
  0,                                /*     Reserved                           */
  0,                                /*     Reserved                           */
  PendSV_Handler,                   /*  -2 PendSV Handler                     */
  SysTick_Handler,                  /*  -1 SysTick Handler                    */

  /* Interrupts */
  WWDG_IRQHandler,                  /* Window WatchDog                        */
  PVD_VDDIO2_IRQHandler,            /* PVD and VDDIO2 through EXTI Line detect */
  RTC_IRQHandler,                   /* RTC through the EXTI line              */
  FLASH_IRQHandler,                 /* FLASH                                  */
  RCC_CRS_IRQHandler,               /* RCC and CRS                            */
  EXTI0_1_IRQHandler,               /* EXTI Line 0 and 1                      */
  EXTI2_3_IRQHandler,               /* EXTI Line 2 and 3                      */
  EXTI4_15_IRQHandler,              /* EXTI Line 4 to 15                      */
  TSC_IRQHandler,                   /* TSC                                    */
  DMA1_Channel1_IRQHandler,         /* DMA1 Channel 1                         */
  DMA1_Channel2_3_IRQHandler,       /* DMA1 Channel 2 and Channel 3           */
  DMA1_Channel4_5_IRQHandler,       /* DMA1 Channel 4 and Channel 5           */
  ADC1_IRQHandler,                  /* ADC1                                   */
  TIM1_BRK_UP_TRG_COM_IRQHandler,   /* TIM1 Break, Update, Trigger and Commutation */
  TIM1_CC_IRQHandler,               /* TIM1 Capture Compare                   */
  TIM2_IRQHandler,                  /* TIM2                                   */
  TIM3_IRQHandler,                  /* TIM3                                   */
  0,                                /* Reserved                               */
  0,                                /* Reserved                               */
  TIM14_IRQHandler,                 /* TIM14                                  */
  0,                                /* Reserved                               */
  TIM16_IRQHandler,                 /* TIM16                                  */
  TIM17_IRQHandler,                 /* TIM17                                  */
  I2C1_IRQHandler,                  /* I2C1                                   */
  0,                                /* Reserved                               */
  SPI1_IRQHandler,                  /* SPI1                                   */
  SPI2_IRQHandler,                  /* SPI2                                   */
  USART1_IRQHandler,                /* USART1                                 */
  USART2_IRQHandler,                /* USART2                                 */
  0,                                /* Reserved                               */
  CEC_CAN_IRQHandler,               /* CEC and CAN                            */
  USB_IRQHandler,                   /* USB                                    */
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
