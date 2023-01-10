/*
 * Copyright (C) 2022-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <asm/aducm32x.h>

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
void SVC_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));

void WKUP_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI5_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI7_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI8_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void WDT_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void LVD0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void MDIO_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_Slave_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_Master_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PLA0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PLA1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_ERR_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_SPI0_TX_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_SPI0_RX_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_SPI1_TX_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_SPI1_RX_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_UART0_TX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_UART0_RX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_I2C0_STX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_I2C0_SRX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_I2C0_M_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_I2C1_STX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_I2C1_SRX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_I2C1_M_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_ADC_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_FLASH_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_Slave_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_Master_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PLA2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PLA3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void LVD1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PWMT_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));

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
  WKUP_IRQHandler,                  /* Wakeup Timer Interrupt        [ 0]     */
  EXTI0_IRQHandler,                 /* External Interrupt 0          [ 1]     */
  EXTI1_IRQHandler,                 /* External Interrupt 1          [ 2]     */
  EXTI2_IRQHandler,                 /* External Interrupt 2          [ 3]     */
  0,                                /* Reserved                      [ 4]     */
  EXTI4_IRQHandler,                 /* External Interrupt 4          [ 5]     */
  EXTI5_IRQHandler,                 /* External Interrupt 5          [ 6]     */
  0,                                /* Reserved                      [ 7]     */
  EXTI7_IRQHandler,                 /* External Interrupt 7          [ 8]     */
  EXTI8_IRQHandler,                 /* External Interrupt 8          [ 9]     */
  WDT_IRQHandler,                   /* Watchdog Timer Interrupt      [10]     */
  0,                                /* Reserved                      [11]     */
  0,                                /* Reserved                      [12]     */
  LVD0_IRQHandler,                  /* Low Voltage Die Interrupt 0   [13]     */
  MDIO_IRQHandler,                  /* MDIO Interrupt                [14]     */
  TIM0_IRQHandler,                  /* Timer0 Interrupt              [15]     */
  TIM1_IRQHandler,                  /* Timer1 Interrupt              [16]     */
  FLASH_IRQHandler,                 /* Flash Memory Interrupt        [17]     */
  UART0_IRQHandler,                 /* UART Interrupt                [18]     */
  SPI0_IRQHandler,                  /* SPI0 Interrupt                [19]     */
  SPI1_IRQHandler,                  /* SPI1 Interrupt                [20]     */
  I2C0_Slave_IRQHandler,            /* I2C0 Slave Interrupt          [21]     */
  I2C0_Master_IRQHandler,           /* I2C0 Master Interrupt         [22]     */
  PLA0_IRQHandler,                  /* PLA0 Interrupt                [23]     */
  PLA1_IRQHandler,                  /* PLA1 Interrupt                [24]     */
  DMA_ERR_IRQHandler,               /* DMA Error Interrupt           [25]     */
  DMA_SPI0_TX_IRQHandler,           /* DMA SPI0 TX Interrupt         [26]     */
  DMA_SPI0_RX_IRQHandler,           /* DMA SPI0 RX Interrupt         [27]     */
  DMA_SPI1_TX_IRQHandler,           /* DMA SPI1 TX Interrupt         [28]     */
  DMA_SPI1_RX_IRQHandler,           /* DMA SPI1 RX Interrupt         [29]     */
  DMA_UART0_TX_IRQHandler,          /* DMA UART TX Interrupt         [30]     */
  DMA_UART0_RX_IRQHandler,          /* DMA UART RX Interrupt         [31]     */
  DMA_I2C0_STX_IRQHandler,          /* DMA I2C0 Slave TX Interrupt   [32]     */
  DMA_I2C0_SRX_IRQHandler,          /* DMA I2C0 Slave RX Interrupt   [33]     */
  DMA_I2C0_M_IRQHandler,            /* DMA I2C0 Master Interrupt     [34]     */
  DMA_I2C1_STX_IRQHandler,          /* DMA I2C1 Slave TX Interrupt   [35]     */
  DMA_I2C1_SRX_IRQHandler,          /* DMA I2C1 Slave RX Interrupt   [36]     */
  DMA_I2C1_M_IRQHandler,            /* DMA I2C1 Master Interrupt     [37]     */
  DMA_ADC_IRQHandler,               /* DMA ADC Interrupt             [38]     */
  DMA_FLASH_IRQHandler,             /* DMA Flash Interrupt           [39]     */
  0,                                /* Reserved                      [40]     */
  0,                                /* Reserved                      [41]     */
  0,                                /* Reserved                      [42]     */
  0,                                /* Reserved                      [43]     */
  I2C1_Slave_IRQHandler,            /* I2C1 Slave Interrupt          [44]     */
  I2C1_Master_IRQHandler,           /* I2C1 Master Interrupt         [45]     */
  PLA2_IRQHandler,                  /* PLA2 Interrupt                [46]     */
  PLA3_IRQHandler,                  /* PLA3 Interrupt                [47]     */
  TIM2_IRQHandler,                  /* Timer2 Interrupt              [48]     */
  LVD1_IRQHandler,                  /* Low Voltage Die Interrupt 1   [49]     */
  PWMT_IRQHandler,                  /* PWM TRIP Interrupt            [50]     */
  PWM0_IRQHandler,                  /* PWM Channel Pair 0 interrupt  [51]     */
  PWM1_IRQHandler,                  /* PWM Channel Pair 1 interrupt  [52]     */
  PWM2_IRQHandler,                  /* PWM Channel Pair 2 interrupt  [53]     */
  PWM3_IRQHandler,                  /* PWM Channel Pair 3 interrupt  [54]     */
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
  __NOP();
  
  SystemInit();                      /* CMSIS System Initialization           */
  __PROGRAM_START();                 /* Enter PreMain (C library entry point) */
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif
