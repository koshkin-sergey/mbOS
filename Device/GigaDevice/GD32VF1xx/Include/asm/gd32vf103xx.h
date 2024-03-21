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

#ifndef GD32VF103_H
#define GD32VF103_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* ----------------------  Interrupt Number Definition  --------------------- */

typedef enum IRQn {
/* -------------------  Core Specific Interrupt Numbers  -------------------- */
  CLIC_INT_RESERVED     = 0,   /*!< RISC-V reserved                           */
  CLIC_INT_SFT          = 3,   /*!< Software interrupt                        */
  CLIC_INT_TMR          = 7,   /*!< CPU Timer interrupt                       */
  CLIC_INT_BWEI         = 17,  /*!< Bus Error interrupt                       */
  CLIC_INT_PMOVI        = 18,  /*!< Performance Monitor                       */

/* ----------------  GD32VF103 Specific Interrupt Numbers  _----------------- */
  WWDGT_IRQn            = 19,  /*!< window watchDog timer interrupt           */
  LVD_IRQn              = 20,  /*!< LVD through EXTI line detect interrupt    */
  TAMPER_IRQn           = 21,  /*!< tamper through EXTI line detect           */
  RTC_IRQn              = 22,  /*!< RTC alarm interrupt                       */
  FMC_IRQn              = 23,  /*!< FMC interrupt                             */
  RCU_CTC_IRQn          = 24,  /*!< RCU and CTC interrupt                     */
  EXTI0_IRQn            = 25,  /*!< EXTI line 0 interrupts                    */
  EXTI1_IRQn            = 26,  /*!< EXTI line 1 interrupts                    */
  EXTI2_IRQn            = 27,  /*!< EXTI line 2 interrupts                    */
  EXTI3_IRQn            = 28,  /*!< EXTI line 3 interrupts                    */
  EXTI4_IRQn            = 29,  /*!< EXTI line 4 interrupts                    */
  DMA0_Channel0_IRQn    = 30,  /*!< DMA0 channel0 interrupt                   */
  DMA0_Channel1_IRQn    = 31,  /*!< DMA0 channel1 interrupt                   */
  DMA0_Channel2_IRQn    = 32,  /*!< DMA0 channel2 interrupt                   */
  DMA0_Channel3_IRQn    = 33,  /*!< DMA0 channel3 interrupt                   */
  DMA0_Channel4_IRQn    = 34,  /*!< DMA0 channel4 interrupt                   */
  DMA0_Channel5_IRQn    = 35,  /*!< DMA0 channel5 interrupt                   */
  DMA0_Channel6_IRQn    = 36,  /*!< DMA0 channel6 interrupt                   */
  ADCx_IRQn             = 37,  /*!< ADC0 and ADC1 interrupt                   */
  CAN0_TX_IRQn          = 38,  /*!< CAN0 TX interrupts                        */
  CAN0_RX0_IRQn         = 39,  /*!< CAN0 RX0 interrupts                       */
  CAN0_RX1_IRQn         = 40,  /*!< CAN0 RX1 interrupts                       */
  CAN0_EWMC_IRQn        = 41,  /*!< CAN0 EWMC interrupts                      */
  EXTI5_9_IRQn          = 42,  /*!< EXTI[9:5] interrupts                      */
  TIMER0_BRK_IRQn       = 43,  /*!< TIMER0 break interrupts                   */
  TIMER0_UP_IRQn        = 44,  /*!< TIMER0 update interrupts                  */
  TIMER0_TRG_CMT_IRQn   = 45,  /*!< TIMER0 trigger and commutation interrupts */
  TIMER0_Channel_IRQn   = 46,  /*!< TIMER0 channel capture compare interrupts */
  TIMER1_IRQn           = 47,  /*!< TIMER1 interrupt                          */
  TIMER2_IRQn           = 48,  /*!< TIMER2 interrupt                          */
  TIMER3_IRQn           = 49,  /*!< TIMER3 interrupts                         */
  I2C0_EV_IRQn          = 50,  /*!< I2C0 event interrupt                      */
  I2C0_ER_IRQn          = 51,  /*!< I2C0 error interrupt                      */
  I2C1_EV_IRQn          = 52,  /*!< I2C1 event interrupt                      */
  I2C1_ER_IRQn          = 53,  /*!< I2C1 error interrupt                      */
  SPI0_IRQn             = 54,  /*!< SPI0 interrupt                            */
  SPI1_IRQn             = 55,  /*!< SPI1 interrupt                            */
  USART0_IRQn           = 56,  /*!< USART0 interrupt                          */
  USART1_IRQn           = 57,  /*!< USART1 interrupt                          */
  USART2_IRQn           = 58,  /*!< USART2 interrupt                          */
  EXTI10_15_IRQn        = 59,  /*!< EXTI[15:10] interrupts                    */
  RTC_ALARM_IRQn        = 60,  /*!< RTC alarm interrupt EXTI                  */
  USBFS_WKUP_IRQn       = 61,  /*!< USBFS wakeup interrupt                    */

  TIMER4_IRQn           = 69,  /*!< TIMER4 global interrupt                   */
  SPI2_IRQn             = 70,  /*!< SPI2 global interrupt                     */
  UART3_IRQn            = 71,  /*!< UART3 global interrupt                    */
  UART4_IRQn            = 72,  /*!< UART4 global interrupt                    */
  TIMER5_IRQn           = 73,  /*!< TIMER5 global interrupt                   */
  TIMER6_IRQn           = 74,  /*!< TIMER6 global interrupt                   */
  DMA1_Channel0_IRQn    = 75,  /*!< DMA1 channel0 global interrupt            */
  DMA1_Channel1_IRQn    = 76,  /*!< DMA1 channel1 global interrupt            */
  DMA1_Channel2_IRQn    = 77,  /*!< DMA1 channel2 global interrupt            */
  DMA1_Channel3_IRQn    = 78,  /*!< DMA1 channel3 global interrupt            */
  DMA1_Channel4_IRQn    = 79,  /*!< DMA1 channel3 global interrupt            */

  CAN1_TX_IRQn          = 82,  /*!< CAN1 TX interrupt                         */
  CAN1_RX0_IRQn         = 83,  /*!< CAN1 RX0 interrupt                        */
  CAN1_RX1_IRQn         = 84,  /*!< CAN1 RX1 interrupt                        */
  CAN1_EWMC_IRQn        = 85,  /*!< CAN1 EWMC interrupt                       */
  USBFS_IRQn            = 86,  /*!< USBFS global interrupt                    */

  IRQn_Reserved         = 0x7FFFFFFF
} IRQn_Type;

/* includes */
#include <Core/Riscv/core_riscv.h>
#include "system_gd32vf1xx.h"

/* main flash and SRAM memory map */
#define FLASH_BASE      (0x08000000UL)        /*!< FLASH base address         */
#define SRAM_BASE       (0x20000000UL)        /*!< SRAM base address          */
#define OPT_BASE        (0x1FFFF800UL)        /*!< Option bytes base address  */
#define DBG_BASE        (0xE0042000UL)        /*!< DBG base address           */

/* Peripheral memory map */
#define APB1_BASE       (0x40000000UL)        /*!< APB1 base address          */
#define APB2_BASE       (0x40010000UL)        /*!< APB2 base address          */
#define AHB_BASE        (0x40018000UL)        /*!< AHB base address           */

/* Advanced Peripheral Bus 1 memory map */
#define TIMER1_BASE     (APB1_BASE + 0x00000000U)   /*!< TIMER1 base address  */
#define TIMER2_BASE     (APB1_BASE + 0x00000400U)   /*!< TIMER2 base address  */
#define TIMER3_BASE     (APB1_BASE + 0x00000800U)   /*!< TIMER3 base address  */
#define TIMER4_BASE     (APB1_BASE + 0x00000C00U)   /*!< TIMER4 base address  */
#define TIMER5_BASE     (APB1_BASE + 0x00001000U)   /*!< TIMER5 base address  */
#define TIMER6_BASE     (APB1_BASE + 0x00001400U)   /*!< TIMER6 base address  */
#define RTC_BASE        (APB1_BASE + 0x00002800U)   /*!< RTC base address     */
#define WWDGT_BASE      (APB1_BASE + 0x00002C00U)   /*!< WWDGT base address   */
#define FWDGT_BASE      (APB1_BASE + 0x00003000U)   /*!< FWDGT base address   */
#define SPI1_BASE       (APB1_BASE + 0x00003800U)   /*!< SPI1 base address    */
#define SPI2_BASE       (APB1_BASE + 0x00003C00U)   /*!< SPI2 base address    */
#define USART1_BASE     (APB1_BASE + 0x00004400U)   /*!< USART1 base address  */
#define USART2_BASE     (APB1_BASE + 0x00004800U)   /*!< USART2 base address  */
#define UART3_BASE      (APB1_BASE + 0x00004C00U)   /*!< UART3 base address   */
#define UART4_BASE      (APB1_BASE + 0x00005000U)   /*!< UART4 base address   */
#define I2C0_BASE       (APB1_BASE + 0x00005400U)   /*!< I2C0 base address    */
#define I2C1_BASE       (APB1_BASE + 0x00005800U)   /*!< I2C1 base address    */
#define USB_CAN_SRAM    (APB1_BASE + 0x00006000U)   /*!< USB/CAN SRAM address */
#define CAN0_BASE       (APB1_BASE + 0x00006400U)   /*!< CAN0 base address    */
#define CAN1_BASE       (APB1_BASE + 0x00006800U)   /*!< CAN1 base address    */
#define BKP_BASE        (APB1_BASE + 0x00006C00U)   /*!< BKP base address     */
#define PMU_BASE        (APB1_BASE + 0x00007000U)   /*!< PMU base address     */
#define DAC_BASE        (APB1_BASE + 0x00007400U)   /*!< DAC base address     */

/* Advanced Peripheral Bus 2 memory map */
#define AFIO_BASE       (APB2_BASE + 0x00000000U)   /*!< AFIO base address    */
#define EXTI_BASE       (APB2_BASE + 0x00000400U)   /*!< EXTI base address    */
#define GPIOA_BASE      (APB2_BASE + 0x00000800U)   /*!< GPIOA base address   */
#define GPIOB_BASE      (APB2_BASE + 0x00000C00U)   /*!< GPIOB base address   */
#define GPIOC_BASE      (APB2_BASE + 0x00001000U)   /*!< GPIOC base address   */
#define GPIOD_BASE      (APB2_BASE + 0x00001400U)   /*!< GPIOD base address   */
#define GPIOE_BASE      (APB2_BASE + 0x00001800U)   /*!< GPIOE base address   */
#define ADC0_BASE       (APB2_BASE + 0x00002400U)   /*!< ADC0 base address    */
#define ADC1_BASE       (APB2_BASE + 0x00002800U)   /*!< ADC1 base address    */
#define TIMER0_BASE     (APB2_BASE + 0x00002C00U)   /*!< TIMER0 base address  */
#define SPI0_BASE       (APB2_BASE + 0x00003000U)   /*!< SPI0 base address    */
#define USART0_BASE     (APB2_BASE + 0x00003800U)   /*!< USART0 base address  */

/* Advanced High performance Bus memory map */
#define DMA0_BASE       (AHB_BASE + 0x00008000U)    /*!< DMA0 base address    */
#define DMA1_BASE       (AHB_BASE + 0x00008400U)    /*!< DMA1 base address    */
#define RCU_BASE        (AHB_BASE + 0x00009000U)    /*!< RCU base address     */
#define FMC_BASE        (AHB_BASE + 0x0000A000U)    /*!< FMC base address     */
#define CRC_BASE        (AHB_BASE + 0x0000B000U)    /*!< CRC base address     */
#define USBFS_BASE      (AHB_BASE + 0x0FFE8000U)    /*!< USBFS base address   */
#define EXT_RAM         (AHB_BASE + 0x1FFE8000U)    /*!< External RAM address */
#define EXMC_BASE       (AHB_BASE + 0x5FFE8000U)    /*!< EXMC reg address     */

#ifdef __cplusplus
}
#endif

#endif 
