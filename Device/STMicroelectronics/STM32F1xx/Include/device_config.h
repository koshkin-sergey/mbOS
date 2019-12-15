/*
 * Copyright (C) 2018 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *
 * Project: RTE Device Configuration for STMicroelectronics STM32F1xx
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

// <h> Clock Configuration
//   <o> High-speed Internal Clock <1-999999999>
#define RTE_HSI                         8000000
//   <o> High-speed External Clock <1-999999999>
#define RTE_HSE                         8000000
// </h>

/* Interrupt Priority */
#define RTE_I2C_INT_PRIORITY            (1U)
#define RTE_I2S_INT_PRIORITY            (1U)
#define RTE_USART_INT_PRIORITY          (1U)
#define RTE_SPI_INT_PRIORITY            (1U)
#define RTE_DMA_INT_PRIORITY            (1U)
#define RTE_EXTI_INT_PRIORITY           (1U)
#define RTE_DAC_INT_PRIORITY            (1U)

// <e> USART1 (Universal synchronous asynchronous receiver transmitter)
// <i> Configuration settings for Driver_USART1 in component ::CMSIS Driver:USART
#define RTE_USART1                       0

//   <o> USART1_TX Pin <0=>Not Used <1=>PA9
#define RTE_USART1_TX_PORT_ID_DEF       1
#if    (RTE_USART1_TX_PORT_ID_DEF == 0)
#define RTE_USART1_TX_DEF               0
#elif  (RTE_USART1_TX_PORT_ID_DEF == 1)
#define RTE_USART1_TX_DEF               1
#define RTE_USART1_TX_PORT_DEF          GPIO_PORT_A
#define RTE_USART1_TX_BIT_DEF           GPIO_PIN_9
#else
#error "Invalid USART1_TX Pin Configuration!"
#endif

//   <o> USART1_RX Pin <0=>Not Used <1=>PA10
#define RTE_USART1_RX_PORT_ID_DEF       1
#if    (RTE_USART1_RX_PORT_ID_DEF == 0)
#define RTE_USART1_RX_DEF               0
#elif  (RTE_USART1_RX_PORT_ID_DEF == 1)
#define RTE_USART1_RX_DEF               1
#define RTE_USART1_RX_PORT_DEF          GPIO_PORT_A
#define RTE_USART1_RX_BIT_DEF           GPIO_PIN_10
#else
#error "Invalid USART1_RX Pin Configuration!"
#endif

//   <o> USART1_CK Pin <0=>Not Used <1=>PA8
#define RTE_USART1_CK_PORT_ID_DEF       1
#if    (RTE_USART1_CK_PORT_ID_DEF == 0)
#define RTE_USART1_CK                   0
#elif  (RTE_USART1_CK_PORT_ID_DEF == 1)
#define RTE_USART1_CK                   1
#define RTE_USART1_CK_PORT_DEF          GPIO_PORT_A
#define RTE_USART1_CK_BIT_DEF           GPIO_PIN_8
#else
#error "Invalid USART1_CK Pin Configuration!"
#endif

//   <o> USART1_CTS Pin <0=>Not Used <1=>PA11
#define RTE_USART1_CTS_PORT_ID_DEF      1
#if    (RTE_USART1_CTS_PORT_ID_DEF == 0)
#define RTE_USART1_CTS                  0
#elif  (RTE_USART1_CTS_PORT_ID_DEF == 1)
#define RTE_USART1_CTS                  1
#define RTE_USART1_CTS_PORT_DEF         GPIO_PORT_A
#define RTE_USART1_CTS_BIT_DEF          GPIO_PIN_11
#else
#error "Invalid USART1_CTS Pin Configuration!"
#endif

//   <o> USART1_RTS Pin <0=>Not Used <1=>PA12
#define RTE_USART1_RTS_PORT_ID_DEF      1
#if    (RTE_USART1_RTS_PORT_ID_DEF == 0)
#define RTE_USART1_RTS                  0
#elif  (RTE_USART1_RTS_PORT_ID_DEF == 1)
#define RTE_USART1_RTS                  1
#define RTE_USART1_RTS_PORT_DEF         GPIO_PORT_A
#define RTE_USART1_RTS_BIT_DEF          GPIO_PIN_12
#else
#error "Invalid USART1_RTS Pin Configuration!"
#endif

//   <e> USART1 Pin Remap
//   <i> Enable USART1 Pin Remapping
#define RTE_USART1_REMAP_FULL           0

//     <o> USART1_TX Pin <0=>Not Used <1=>PB6
#define RTE_USART1_TX_PORT_ID_FULL      0
#if    (RTE_USART1_TX_PORT_ID_FULL == 0)
#define RTE_USART1_TX_FULL              0
#elif  (RTE_USART1_TX_PORT_ID_FULL == 1)
#define RTE_USART1_TX_FULL              1
#define RTE_USART1_TX_PORT_FULL         GPIO_PORT_B
#define RTE_USART1_TX_BIT_FULL          GPIO_PIN_6
#else
#error "Invalid USART1_TX Pin Configuration!"
#endif

//     <o> USART1_RX Pin <0=>Not Used <1=>PB7
#define RTE_USART1_RX_PORT_ID_FULL      0
#if    (RTE_USART1_RX_PORT_ID_FULL == 0)
#define RTE_USART1_RX_FULL              0
#elif  (RTE_USART1_RX_PORT_ID_FULL == 1)
#define RTE_USART1_RX_FULL              1
#define RTE_USART1_RX_PORT_FULL         GPIO_PORT_B
#define RTE_USART1_RX_BIT_FULL          GPIO_PIN_7
#else
#error "Invalid USART1_RX Pin Configuration!"
#endif
//   </e>

#if    (RTE_USART1_REMAP_FULL)
#define RTE_USART1_AF_REMAP              AFIO_USART1_REMAP
#define RTE_USART1_TX                    RTE_USART1_TX_FULL
#define RTE_USART1_TX_PORT               RTE_USART1_TX_PORT_FULL
#define RTE_USART1_TX_BIT                RTE_USART1_TX_BIT_FULL
#define RTE_USART1_RX                    RTE_USART1_RX_FULL
#define RTE_USART1_RX_PORT               RTE_USART1_RX_PORT_FULL
#define RTE_USART1_RX_BIT                RTE_USART1_RX_BIT_FULL
#define RTE_USART1_CK_PORT               RTE_USART1_CK_PORT_DEF
#define RTE_USART1_CK_BIT                RTE_USART1_CK_BIT_DEF
#define RTE_USART1_CTS_PORT              RTE_USART1_CTS_PORT_DEF
#define RTE_USART1_CTS_BIT               RTE_USART1_CTS_BIT_DEF
#define RTE_USART1_RTS_PORT              RTE_USART1_RTS_PORT_DEF
#define RTE_USART1_RTS_BIT               RTE_USART1_RTS_BIT_DEF
#else
#define RTE_USART1_AF_REMAP              AFIO_USART1_NO_REMAP
#define RTE_USART1_TX                    RTE_USART1_TX_DEF
#define RTE_USART1_TX_PORT               RTE_USART1_TX_PORT_DEF
#define RTE_USART1_TX_BIT                RTE_USART1_TX_BIT_DEF
#define RTE_USART1_RX                    RTE_USART1_RX_DEF
#define RTE_USART1_RX_PORT               RTE_USART1_RX_PORT_DEF
#define RTE_USART1_RX_BIT                RTE_USART1_RX_BIT_DEF
#define RTE_USART1_CK_PORT               RTE_USART1_CK_PORT_DEF
#define RTE_USART1_CK_BIT                RTE_USART1_CK_BIT_DEF
#define RTE_USART1_CTS_PORT              RTE_USART1_CTS_PORT_DEF
#define RTE_USART1_CTS_BIT               RTE_USART1_CTS_BIT_DEF
#define RTE_USART1_RTS_PORT              RTE_USART1_RTS_PORT_DEF
#define RTE_USART1_RTS_BIT               RTE_USART1_RTS_BIT_DEF
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Set DMA Channel priority
//   </e>
#define RTE_USART1_RX_DMA               1
#define RTE_USART1_RX_DMA_NUMBER        1
#define RTE_USART1_RX_DMA_CHANNEL       5
#define RTE_USART1_RX_DMA_PRIORITY      0
//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Set DMA Channel priority
//   </e>
#define RTE_USART1_TX_DMA               1
#define RTE_USART1_TX_DMA_NUMBER        1
#define RTE_USART1_TX_DMA_CHANNEL       4
#define RTE_USART1_TX_DMA_PRIORITY      0
// </e>


// <e> USART2 (Universal synchronous asynchronous receiver transmitter)
// <i> Configuration settings for Driver_USART2 in component ::CMSIS Driver:USART
#define RTE_USART2                      0

//   <o> USART2_TX Pin <0=>Not Used <1=>PA2
#define RTE_USART2_TX_PORT_ID_DEF       1
#if    (RTE_USART2_TX_PORT_ID_DEF == 0)
#define RTE_USART2_TX_DEF               0
#elif  (RTE_USART2_TX_PORT_ID_DEF == 1)
#define RTE_USART2_TX_DEF               1
#define RTE_USART2_TX_PORT_DEF          GPIO_PORT_A
#define RTE_USART2_TX_BIT_DEF           GPIO_PIN_2
#else
#error "Invalid USART2_TX Pin Configuration!"
#endif

//   <o> USART2_RX Pin <0=>Not Used <1=>PA3
#define RTE_USART2_RX_PORT_ID_DEF       1
#if    (RTE_USART2_RX_PORT_ID_DEF == 0)
#define RTE_USART2_RX_DEF               0
#elif  (RTE_USART2_RX_PORT_ID_DEF == 1)
#define RTE_USART2_RX_DEF               1
#define RTE_USART2_RX_PORT_DEF          GPIO_PORT_A
#define RTE_USART2_RX_BIT_DEF           GPIO_PIN_3
#else
#error "Invalid USART2_RX Pin Configuration!"
#endif

//   <o> USART2_CK Pin <0=>Not Used <1=>PA4
#define RTE_USART2_CK_PORT_ID_DEF       1
#if    (RTE_USART2_CK_PORT_ID_DEF == 0)
#define RTE_USART2_CK_DEF               0
#elif  (RTE_USART2_CK_PORT_ID_DEF == 1)
#define RTE_USART2_CK_DEF               1
#define RTE_USART2_CK_PORT_DEF          GPIO_PORT_A
#define RTE_USART2_CK_BIT_DEF           GPIO_PIN_4
#else
#error "Invalid USART2_CK Pin Configuration!"
#endif

//   <o> USART2_CTS Pin <0=>Not Used <1=>PA0
#define RTE_USART2_CTS_PORT_ID_DEF      1
#if    (RTE_USART2_CTS_PORT_ID_DEF == 0)
#define RTE_USART2_CTS_DEF              0
#elif  (RTE_USART2_CTS_PORT_ID_DEF == 1)
#define RTE_USART2_CTS_DEF              1
#define RTE_USART2_CTS_PORT_DEF         GPIO_PORT_A
#define RTE_USART2_CTS_BIT_DEF          GPIO_PIN_0
#else
#error "Invalid USART2_CTS Pin Configuration!"
#endif

//   <o> USART2_RTS Pin <0=>Not Used <1=>PA1
#define RTE_USART2_RTS_PORT_ID_DEF      1
#if    (RTE_USART2_RTS_PORT_ID_DEF == 0)
#define RTE_USART2_RTS_DEF              0
#elif  (RTE_USART2_RTS_PORT_ID_DEF == 1)
#define RTE_USART2_RTS_DEF              1
#define RTE_USART2_RTS_PORT_DEF         GPIO_PORT_A
#define RTE_USART2_RTS_BIT_DEF          GPIO_PIN_1
#else
#error "Invalid USART2_RTS Pin Configuration!"
#endif

//   <e> USART2 Pin Remap
//   <i> Enable USART2 Pin Remapping
#define RTE_USART2_REMAP_FULL           0

//     <o> USART2_TX Pin <0=>Not Used <1=>PD5
#define RTE_USART2_TX_PORT_ID_FULL      0
#if    (RTE_USART2_TX_PORT_ID_FULL == 0)
#define RTE_USART2_TX_FULL              0
#elif  (RTE_USART2_TX_PORT_ID_FULL == 1)
#define RTE_USART2_TX_FULL              1
#define RTE_USART2_TX_PORT_FULL         GPIO_PORT_D
#define RTE_USART2_TX_BIT_FULL          GPIO_PIN_5
#else
#error "Invalid USART2_TX Pin Configuration!"
#endif

//     <o> USART2_RX Pin <0=>Not Used <1=>PD6
#define RTE_USART2_RX_PORT_ID_FULL      0
#if    (RTE_USART2_RX_PORT_ID_FULL == 0)
#define RTE_USART2_RX_FULL              0
#elif  (RTE_USART2_RX_PORT_ID_FULL == 1)
#define RTE_USART2_RX_FULL              1
#define RTE_USART2_RX_PORT_FULL         GPIO_PORT_D
#define RTE_USART2_RX_BIT_FULL          GPIO_PIN_6
#else
#error "Invalid USART2_RX Pin Configuration!"
#endif

//     <o> USART2_CK Pin <0=>Not Used <1=>PD7
#define RTE_USART2_CK_PORT_ID_FULL      0
#if    (RTE_USART2_CK_PORT_ID_FULL == 0)
#define RTE_USART2_CK_FULL              0
#elif  (RTE_USART2_CK_PORT_ID_FULL == 1)
#define RTE_USART2_CK_FULL              1
#define RTE_USART2_CK_PORT_FULL         GPIO_PORT_D
#define RTE_USART2_CK_BIT_FULL          GPIO_PIN_7
#else
#error "Invalid USART2_CK Pin Configuration!"
#endif

//     <o> USART2_CTS Pin <0=>Not Used <1=>PD3
#define RTE_USART2_CTS_PORT_ID_FULL     0
#if    (RTE_USART2_CTS_PORT_ID_FULL == 0)
#define RTE_USART2_CTS_FULL             0
#elif  (RTE_USART2_CTS_PORT_ID_FULL == 1)
#define RTE_USART2_CTS_FULL             1
#define RTE_USART2_CTS_PORT_FULL        GPIO_PORT_D
#define RTE_USART2_CTS_BIT_FULL         GPIO_PIN_3
#else
#error "Invalid USART2_CTS Pin Configuration!"
#endif

//     <o> USART2_RTS Pin <0=>Not Used <1=>PD4
#define RTE_USART2_RTS_PORT_ID_FULL     0
#if    (RTE_USART2_RTS_PORT_ID_FULL == 0)
#define RTE_USART2_RTS_FULL             0
#elif  (RTE_USART2_RTS_PORT_ID_FULL == 1)
#define RTE_USART2_RTS_FULL             1
#define RTE_USART2_RTS_PORT_FULL        GPIO_PORT_D
#define RTE_USART2_RTS_BIT_FULL         GPIO_PIN_4
#else
#error "Invalid USART2_RTS Pin Configuration!"
#endif
//   </e>

#if    (RTE_USART2_REMAP_FULL)
#define RTE_USART2_AF_REMAP              AFIO_USART2_REMAP
#define RTE_USART2_TX                    RTE_USART2_TX_FULL
#define RTE_USART2_TX_PORT               RTE_USART2_TX_PORT_FULL
#define RTE_USART2_TX_BIT                RTE_USART2_TX_BIT_FULL
#define RTE_USART2_RX                    RTE_USART2_RX_FULL
#define RTE_USART2_RX_PORT               RTE_USART2_RX_PORT_FULL
#define RTE_USART2_RX_BIT                RTE_USART2_RX_BIT_FULL
#define RTE_USART2_CK                    RTE_USART2_CK_FULL
#define RTE_USART2_CK_PORT               RTE_USART2_CK_PORT_FULL
#define RTE_USART2_CK_BIT                RTE_USART2_CK_BIT_FULL
#define RTE_USART2_CTS                   RTE_USART2_CTS_FULL
#define RTE_USART2_CTS_PORT              RTE_USART2_CTS_PORT_FULL
#define RTE_USART2_CTS_BIT               RTE_USART2_CTS_BIT_FULL
#define RTE_USART2_RTS                   RTE_USART2_RTS_FULL
#define RTE_USART2_RTS_PORT              RTE_USART2_RTS_PORT_FULL
#define RTE_USART2_RTS_BIT               RTE_USART2_RTS_BIT_FULL
#else
#define RTE_USART2_AF_REMAP              AFIO_USART2_NO_REMAP
#define RTE_USART2_TX                    RTE_USART2_TX_DEF
#define RTE_USART2_TX_PORT               RTE_USART2_TX_PORT_DEF
#define RTE_USART2_TX_BIT                RTE_USART2_TX_BIT_DEF
#define RTE_USART2_RX                    RTE_USART2_RX_DEF
#define RTE_USART2_RX_PORT               RTE_USART2_RX_PORT_DEF
#define RTE_USART2_RX_BIT                RTE_USART2_RX_BIT_DEF
#define RTE_USART2_CK                    RTE_USART2_CK_DEF
#define RTE_USART2_CK_PORT               RTE_USART2_CK_PORT_DEF
#define RTE_USART2_CK_BIT                RTE_USART2_CK_BIT_DEF
#define RTE_USART2_CTS                   RTE_USART2_CTS_DEF
#define RTE_USART2_CTS_PORT              RTE_USART2_CTS_PORT_DEF
#define RTE_USART2_CTS_BIT               RTE_USART2_CTS_BIT_DEF
#define RTE_USART2_RTS                   RTE_USART2_RTS_DEF
#define RTE_USART2_RTS_PORT              RTE_USART2_RTS_PORT_DEF
#define RTE_USART2_RTS_BIT               RTE_USART2_RTS_BIT_DEF
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <6=>6
//     <i>  Selects DMA Channel (only Channel 6 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Set DMA Channel priority
//   </e>
#define RTE_USART2_RX_DMA               1
#define RTE_USART2_RX_DMA_NUMBER        1
#define RTE_USART2_RX_DMA_CHANNEL       6
#define RTE_USART2_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <7=>7
//     <i>  Selects DMA Channel (only Channel 7 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Set DMA Channel priority
//   </e>
#define RTE_USART2_TX_DMA               1
#define RTE_USART2_TX_DMA_NUMBER        1
#define RTE_USART2_TX_DMA_CHANNEL       7
#define RTE_USART2_TX_DMA_PRIORITY      0

// </e>


// <e> USART3 (Universal synchronous asynchronous receiver transmitter)
// <i> Configuration settings for Driver_USART3 in component ::CMSIS Driver:USART
#define RTE_USART3                      0

//   <o> USART3_TX Pin <0=>Not Used <1=>PB10
#define RTE_USART3_TX_PORT_ID_DEF       1
#if    (RTE_USART3_TX_PORT_ID_DEF == 0)
#define RTE_USART3_TX_DEF               0
#elif  (RTE_USART3_TX_PORT_ID_DEF == 1)
#define RTE_USART3_TX_DEF               1
#define RTE_USART3_TX_PORT_DEF          GPIO_PORT_B
#define RTE_USART3_TX_BIT_DEF           GPIO_PIN_10
#else
#error "Invalid USART3_TX Pin Configuration!"
#endif

//   <o> USART3_RX Pin <0=>Not Used <1=>PB11
#define RTE_USART3_RX_PORT_ID_DEF       1
#if    (RTE_USART3_RX_PORT_ID_DEF == 0)
#define RTE_USART3_RX_DEF               0
#elif  (RTE_USART3_RX_PORT_ID_DEF == 1)
#define RTE_USART3_RX_DEF               1
#define RTE_USART3_RX_PORT_DEF          GPIO_PORT_B
#define RTE_USART3_RX_BIT_DEF           GPIO_PIN_11
#else
#error "Invalid USART3_RX Pin Configuration!"
#endif

//   <o> USART3_CK Pin <0=>Not Used <1=>PB12
#define RTE_USART3_CK_PORT_ID_DEF       0
#if    (RTE_USART3_CK_PORT_ID_DEF == 0)
#define RTE_USART3_CK_DEF               0
#elif  (RTE_USART3_CK_PORT_ID_DEF == 1)
#define RTE_USART3_CK_DEF               1
#define RTE_USART3_CK_PORT_DEF          GPIO_PORT_B
#define RTE_USART3_CK_BIT_DEF           GPIO_PIN_12
#else
#error "Invalid USART3_CK Pin Configuration!"
#endif

//   <o> USART3_CTS Pin <0=>Not Used <1=>PB13
#define RTE_USART3_CTS_PORT_ID_DEF      0
#if    (RTE_USART3_CTS_PORT_ID_DEF == 0)
#define RTE_USART3_CTS_DEF              0
#elif  (RTE_USART3_CTS_PORT_ID_DEF == 1)
#define RTE_USART3_CTS_DEF              1
#define RTE_USART3_CTS_PORT_DEF         GPIO_PORT_B
#define RTE_USART3_CTS_BIT_DEF          GPIO_PIN_13
#else
#error "Invalid USART3_CTS Pin Configuration!"
#endif

//   <o> USART3_RTS Pin <0=>Not Used <1=>PB14
#define RTE_USART3_RTS_PORT_ID_DEF      0
#if    (RTE_USART3_RTS_PORT_ID_DEF == 0)
#define RTE_USART3_RTS_DEF              0
#elif  (RTE_USART3_RTS_PORT_ID_DEF == 1)
#define RTE_USART3_RTS_DEF              1
#define RTE_USART3_RTS_PORT_DEF         GPIO_PORT_B
#define RTE_USART3_RTS_BIT_DEF          GPIO_PIN_14
#else
#error "Invalid USART3_RTS Pin Configuration!"
#endif

//   <e> USART3 Partial Pin Remap
//   <i> Enable USART3 Partial Pin Remapping
#define RTE_USART3_REMAP_PARTIAL        1

//     <o> USART3_TX Pin <0=>Not Used <1=>PC10
#define RTE_USART3_TX_PORT_ID_PARTIAL   1
#if    (RTE_USART3_TX_PORT_ID_PARTIAL == 0)
#define RTE_USART3_TX_PARTIAL           0
#elif  (RTE_USART3_TX_PORT_ID_PARTIAL == 1)
#define RTE_USART3_TX_PARTIAL           1
#define RTE_USART3_TX_PORT_PARTIAL      GPIO_PORT_C
#define RTE_USART3_TX_BIT_PARTIAL       GPIO_PIN_10
#else
#error "Invalid USART3_TX Pin Configuration!"
#endif

//     <o> USART3_RX Pin <0=>Not Used <1=>PC11
#define RTE_USART3_RX_PORT_ID_PARTIAL   1
#if    (RTE_USART3_RX_PORT_ID_PARTIAL == 0)
#define RTE_USART3_RX_PARTIAL           0
#elif  (RTE_USART3_RX_PORT_ID_PARTIAL == 1)
#define RTE_USART3_RX_PARTIAL           1
#define RTE_USART3_RX_PORT_PARTIAL      GPIO_PORT_C
#define RTE_USART3_RX_BIT_PARTIAL       GPIO_PIN_11
#else
#error "Invalid USART3_RX Pin Configuration!"
#endif

//     <o> USART3_CK Pin <0=>Not Used <1=>PC12
#define RTE_USART3_CK_PORT_ID_PARTIAL   0
#if    (RTE_USART3_CK_PORT_ID_PARTIAL == 0)
#define RTE_USART3_CK_PARTIAL           0
#elif  (RTE_USART3_CK_PORT_ID_PARTIAL == 1)
#define RTE_USART3_CK_PARTIAL           1
#define RTE_USART3_CK_PORT_PARTIAL      GPIO_PORT_C
#define RTE_USART3_CK_BIT_PARTIAL       GPIO_PIN_12
#else
#error "Invalid USART3_CK Pin Configuration!"
#endif
//   </e>

//   <e> USART3 Full Pin Remap
//   <i> Enable USART3 Full Pin Remapping
#define RTE_USART3_REMAP_FULL           0

//     <o> USART3_TX Pin <0=>Not Used <1=>PD8
#define RTE_USART3_TX_PORT_ID_FULL      0
#if    (RTE_USART3_TX_PORT_ID_FULL == 0)
#define RTE_USART3_TX_FULL              0
#elif  (RTE_USART3_TX_PORT_ID_FULL == 1)
#define RTE_USART3_TX_FULL              1
#define RTE_USART3_TX_PORT_FULL         GPIO_PORT_D
#define RTE_USART3_TX_BIT_FULL          GPIO_PIN_8
#else
#error "Invalid USART3_TX Pin Configuration!"
#endif

//     <o> USART3_RX Pin <0=>Not Used <1=>PD9
#define RTE_USART3_RX_PORT_ID_FULL      0
#if    (RTE_USART3_RX_PORT_ID_FULL == 0)
#define RTE_USART3_RX_FULL              0
#elif  (RTE_USART3_RX_PORT_ID_FULL == 1)
#define RTE_USART3_RX_FULL              1
#define RTE_USART3_RX_PORT_FULL         GPIO_PORT_D
#define RTE_USART3_RX_BIT_FULL          GPIO_PIN_9
#else
#error "Invalid USART3_RX Pin Configuration!"
#endif

//     <o> USART3_CK Pin <0=>Not Used <1=>PD10
#define RTE_USART3_CK_PORT_ID_FULL      0
#if    (RTE_USART3_CK_PORT_ID_FULL == 0)
#define RTE_USART3_CK_FULL              0
#elif  (RTE_USART3_CK_PORT_ID_FULL == 1)
#define RTE_USART3_CK_FULL              1
#define RTE_USART3_CK_PORT_FULL         GPIO_PORT_D
#define RTE_USART3_CK_BIT_FULL          GPIO_PIN_10
#else
#error "Invalid USART3_CK Pin Configuration!"
#endif

//     <o> USART3_CTS Pin <0=>Not Used <1=>PD11
#define RTE_USART3_CTS_PORT_ID_FULL     0
#if    (RTE_USART3_CTS_PORT_ID_FULL == 0)
#define RTE_USART3_CTS_FULL             0
#elif  (RTE_USART3_CTS_PORT_ID_FULL == 1)
#define RTE_USART3_CTS_FULL             1
#define RTE_USART3_CTS_PORT_FULL        GPIO_PORT_D
#define RTE_USART3_CTS_BIT_FULL         GPIO_PIN_11
#else
#error "Invalid USART3_CTS Pin Configuration!"
#endif

//     <o> USART3_RTS Pin <0=>Not Used <1=>PD12
#define RTE_USART3_RTS_PORT_ID_FULL     0
#if    (RTE_USART3_RTS_PORT_ID_FULL == 0)
#define RTE_USART3_RTS_FULL             0
#elif  (RTE_USART3_RTS_PORT_ID_FULL == 1)
#define RTE_USART3_RTS_FULL             1
#define RTE_USART3_RTS_PORT_FULL        GPIO_PORT_D
#define RTE_USART3_RTS_BIT_FULL         GPIO_PIN_12
#else
#error "Invalid USART3_RTS Pin Configuration!"
#endif
//   </e>

#if ((RTE_USART3_REMAP_PARTIAL == 1) && (RTE_USART3_REMAP_FULL == 1))
#error "Invalid USART3 Pin Remap Configuration!"
#endif

#if    (RTE_USART3_REMAP_FULL)
#define RTE_USART3_AF_REMAP              AFIO_USART3_REMAP_FULL
#define RTE_USART3_TX                    RTE_USART3_TX_FULL
#define RTE_USART3_TX_PORT               RTE_USART3_TX_PORT_FULL
#define RTE_USART3_TX_BIT                RTE_USART3_TX_BIT_FULL
#define RTE_USART3_RX                    RTE_USART3_RX_FULL
#define RTE_USART3_RX_PORT               RTE_USART3_RX_PORT_FULL
#define RTE_USART3_RX_BIT                RTE_USART3_RX_BIT_FULL
#define RTE_USART3_CK                    RTE_USART3_CK_FULL
#define RTE_USART3_CK_PORT               RTE_USART3_CK_PORT_FULL
#define RTE_USART3_CK_BIT                RTE_USART3_CK_BIT_FULL
#define RTE_USART3_CTS                   RTE_USART3_CTS_FULL
#define RTE_USART3_CTS_PORT              RTE_USART3_CTS_PORT_FULL
#define RTE_USART3_CTS_BIT               RTE_USART3_CTS_BIT_FULL
#define RTE_USART3_RTS                   RTE_USART3_RTS_FULL
#define RTE_USART3_RTS_PORT              RTE_USART3_RTS_PORT_FULL
#define RTE_USART3_RTS_BIT               RTE_USART3_RTS_BIT_FULL
#elif  (RTE_USART3_REMAP_PARTIAL)
#define RTE_USART3_AF_REMAP              AFIO_USART3_REMAP_PARTIAL
#define RTE_USART3_TX                    RTE_USART3_TX_PARTIAL
#define RTE_USART3_TX_PORT               RTE_USART3_TX_PORT_PARTIAL
#define RTE_USART3_TX_BIT                RTE_USART3_TX_BIT_PARTIAL
#define RTE_USART3_RX                    RTE_USART3_RX_PARTIAL
#define RTE_USART3_RX_PORT               RTE_USART3_RX_PORT_PARTIAL
#define RTE_USART3_RX_BIT                RTE_USART3_RX_BIT_PARTIAL
#define RTE_USART3_CK                    RTE_USART3_CK_PARTIAL
#define RTE_USART3_CK_PORT               RTE_USART3_CK_PORT_PARTIAL
#define RTE_USART3_CK_BIT                RTE_USART3_CK_BIT_PARTIAL
#define RTE_USART3_CTS                   RTE_USART3_CTS_DEF
#define RTE_USART3_CTS_PORT              RTE_USART3_CTS_PORT_DEF
#define RTE_USART3_CTS_BIT               RTE_USART3_CTS_BIT_DEF
#define RTE_USART3_RTS                   RTE_USART3_RTS_DEF
#define RTE_USART3_RTS_PORT              RTE_USART3_RTS_PORT_DEF
#define RTE_USART3_RTS_BIT               RTE_USART3_RTS_BIT_DEF
#else
#define RTE_USART3_AF_REMAP              AFIO_USART3_NO_REMAP
#define RTE_USART3_TX                    RTE_USART3_TX_DEF
#define RTE_USART3_TX_PORT               RTE_USART3_TX_PORT_DEF
#define RTE_USART3_TX_BIT                RTE_USART3_TX_BIT_DEF
#define RTE_USART3_RX                    RTE_USART3_RX_DEF
#define RTE_USART3_RX_PORT               RTE_USART3_RX_PORT_DEF
#define RTE_USART3_RX_BIT                RTE_USART3_RX_BIT_DEF
#define RTE_USART3_CK                    RTE_USART3_CK_DEF
#define RTE_USART3_CK_PORT               RTE_USART3_CK_PORT_DEF
#define RTE_USART3_CK_BIT                RTE_USART3_CK_BIT_DEF
#define RTE_USART3_CTS                   RTE_USART3_CTS_DEF
#define RTE_USART3_CTS_PORT              RTE_USART3_CTS_PORT_DEF
#define RTE_USART3_CTS_BIT               RTE_USART3_CTS_BIT_DEF
#define RTE_USART3_RTS                   RTE_USART3_RTS_DEF
#define RTE_USART3_RTS_PORT              RTE_USART3_RTS_PORT_DEF
#define RTE_USART3_RTS_BIT               RTE_USART3_RTS_BIT_DEF
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//   </e>
#define RTE_USART3_RX_DMA               1
#define RTE_USART3_RX_DMA_NUMBER        1
#define RTE_USART3_RX_DMA_CHANNEL       3
#define RTE_USART3_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <2=>2
//     <i>  Selects DMA Channel (only Channel 2 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//   </e>
#define RTE_USART3_TX_DMA               1
#define RTE_USART3_TX_DMA_NUMBER        1
#define RTE_USART3_TX_DMA_CHANNEL       2
#define RTE_USART3_TX_DMA_PRIORITY      0

// </e>


// <e> UART4 (Universal asynchronous receiver transmitter)
// <i> Configuration settings for Driver_USART4 in component ::CMSIS Driver:USART
#define RTE_UART4                       0
#define RTE_UART4_AF_REMAP              AFIO_UNAVAILABLE_REMAP

//   <o> UART4_TX Pin <0=>Not Used <1=>PC10
#define RTE_UART4_TX_ID                 1
#if    (RTE_UART4_TX_ID == 0)
#define RTE_UART4_TX                    0
#elif  (RTE_UART4_TX_ID == 1)
#define RTE_UART4_TX                    1
#define RTE_UART4_TX_PORT               GPIO_PORT_C
#define RTE_UART4_TX_BIT                GPIO_PIN_10
#else
#error "Invalid UART4_TX Pin Configuration!"
#endif

//   <o> UART4_RX Pin <0=>Not Used <1=>PC11
#define RTE_UART4_RX_ID                 1
#if    (RTE_UART4_RX_ID == 0)
#define RTE_UART4_RX                    0
#elif  (RTE_UART4_RX_ID == 1)
#define RTE_UART4_RX                    1
#define RTE_UART4_RX_PORT               GPIO_PORT_C
#define RTE_UART4_RX_BIT                GPIO_PIN_11
#else
#error "Invalid UART4_RX Pin Configuration!"
#endif


//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//   </e>
#define RTE_UART4_RX_DMA                1
#define RTE_UART4_RX_DMA_NUMBER         2
#define RTE_UART4_RX_DMA_CHANNEL        3
#define RTE_UART4_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//   </e>
#define RTE_UART4_TX_DMA                1
#define RTE_UART4_TX_DMA_NUMBER         2
#define RTE_UART4_TX_DMA_CHANNEL        5
#define RTE_UART4_TX_DMA_PRIORITY       0

// </e>


// <e> UART5 (Universal asynchronous receiver transmitter)
// <i> Configuration settings for Driver_USART5 in component ::CMSIS Driver:USART
#define RTE_UART5                       0
#define RTE_UART5_AF_REMAP              AFIO_UNAVAILABLE_REMAP

//   <o> UART5_TX Pin <0=>Not Used <1=>PC12
#define RTE_UART5_TX_ID                 1
#if    (RTE_UART5_TX_ID == 0)
#define RTE_UART5_TX                    0
#elif  (RTE_UART5_TX_ID == 1)
#define RTE_UART5_TX                    1
#define RTE_UART5_TX_PORT               GPIO_PORT_C
#define RTE_UART5_TX_BIT                GPIO_PIN_12
#else
#error "Invalid UART5_TX Pin Configuration!"
#endif

//   <o> UART5_RX Pin <0=>Not Used <1=>PD2
#define RTE_UART5_RX_ID                 1
#if    (RTE_UART5_RX_ID == 0)
#define RTE_UART5_RX                    0
#elif  (RTE_UART5_RX_ID == 1)
#define RTE_UART5_RX                    1
#define RTE_UART5_RX_PORT               GPIO_PORT_D
#define RTE_UART5_RX_BIT                GPIO_PIN_2
#else
#error "Invalid UART5_RX Pin Configuration!"
#endif

#if defined(STM32F100xB) || defined(STM32F100xE)

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//   </e>
#define RTE_UART5_RX_DMA                1
#define RTE_UART5_RX_DMA_NUMBER         2
#define RTE_UART5_RX_DMA_CHANNEL        4
#define RTE_UART5_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//   </e>
#define RTE_UART5_TX_DMA                1
#define RTE_UART5_TX_DMA_NUMBER         2
#define RTE_UART5_TX_DMA_CHANNEL        1
#define RTE_UART5_TX_DMA_PRIORITY       0

#endif
// </e>


// <e> I2C1 (Inter-integrated Circuit Interface 1)
// <i> Configuration settings for Driver_I2C1 in component ::CMSIS Driver:I2C
#define RTE_I2C1                        0

//   <o> I2C1_SCL Pin <0=>PB6
#define RTE_I2C1_SCL_PORT_ID_DEF        0
#if    (RTE_I2C1_SCL_PORT_ID_DEF == 0)
#define RTE_I2C1_SCL_PORT_DEF           GPIO_PORT_B
#define RTE_I2C1_SCL_BIT_DEF            GPIO_PIN_6
#else
#error "Invalid I2C1_SCL Pin Configuration!"
#endif

//   <o> I2C1_SDA Pin <0=>PB7
#define RTE_I2C1_SDA_PORT_ID_DEF        0
#if    (RTE_I2C1_SDA_PORT_ID_DEF == 0)
#define RTE_I2C1_SDA_PORT_DEF           GPIO_PORT_B
#define RTE_I2C1_SDA_BIT_DEF            GPIO_PIN_7
#else
#error "Invalid I2C1_SCL Pin Configuration!"
#endif

//   <e> I2C1 Pin Remap
//   <i> Enable I2C1 Pin Remapping
#define RTE_I2C1_REMAP_FULL             0

//   <o> I2C1_SCL Pin <0=>PB8
#define RTE_I2C1_SCL_PORT_ID_FULL       0
#if    (RTE_I2C1_SCL_PORT_ID_FULL == 0)
#define RTE_I2C1_SCL_PORT_FULL          GPIO_PORT_B
#define RTE_I2C1_SCL_BIT_FULL           GPIO_PIN_8
#else
#error "Invalid I2C1_SCL Pin Configuration!"
#endif

//   <o> I2C1_SDA Pin <0=>PB9
#define RTE_I2C1_SDA_PORT_ID_FULL       0
#if    (RTE_I2C1_SDA_PORT_ID_FULL == 0)
#define RTE_I2C1_SDA_PORT_FULL          GPIO_PORT_B
#define RTE_I2C1_SDA_BIT_FULL           GPIO_PIN_9
#else
#error "Invalid I2C1_SCL Pin Configuration!"
#endif

//   </e>

#if    (RTE_I2C1_REMAP_FULL)
#define RTE_I2C1_AF_REMAP               AFIO_I2C1_REMAP
#define RTE_I2C1_SCL_PORT               RTE_I2C1_SCL_PORT_FULL
#define RTE_I2C1_SCL_BIT                RTE_I2C1_SCL_BIT_FULL
#define RTE_I2C1_SDA_PORT               RTE_I2C1_SDA_PORT_FULL
#define RTE_I2C1_SDA_BIT                RTE_I2C1_SDA_BIT_FULL
#else
#define RTE_I2C1_AF_REMAP               AFIO_I2C1_NO_REMAP
#define RTE_I2C1_SCL_PORT               RTE_I2C1_SCL_PORT_DEF
#define RTE_I2C1_SCL_BIT                RTE_I2C1_SCL_BIT_DEF
#define RTE_I2C1_SDA_PORT               RTE_I2C1_SDA_PORT_DEF
#define RTE_I2C1_SDA_BIT                RTE_I2C1_SDA_BIT_DEF
#endif


//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <7=>7
//     <i>  Selects DMA Channel (only Channel 7 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2C1_RX_DMA                 0
#define RTE_I2C1_RX_DMA_NUMBER          1
#define RTE_I2C1_RX_DMA_CHANNEL         7
#define RTE_I2C1_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <6=>6
//     <i>  Selects DMA Channel (only Channel 6 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2C1_TX_DMA                 0
#define RTE_I2C1_TX_DMA_NUMBER          1
#define RTE_I2C1_TX_DMA_CHANNEL         6
#define RTE_I2C1_TX_DMA_PRIORITY        0

// </e>


// <e> I2C2 (Inter-integrated Circuit Interface 2)
// <i> Configuration settings for Driver_I2C2 in component ::CMSIS Driver:I2C
#define RTE_I2C2                        0
#define RTE_I2C2_AF_REMAP               AFIO_UNAVAILABLE_REMAP

//   <o> I2C2_SCL Pin <0=>PB10
#define RTE_I2C2_SCL_PORT_ID            0
#if    (RTE_I2C2_SCL_PORT_ID == 0)
#define RTE_I2C2_SCL_PORT               GPIO_PORT_B
#define RTE_I2C2_SCL_BIT                GPIO_PIN_10
#else
#error "Invalid I2C2_SCL Pin Configuration!"
#endif

//   <o> I2C2_SDA Pin <0=>PB11
#define RTE_I2C2_SDA_PORT_ID            0
#if    (RTE_I2C2_SDA_PORT_ID == 0)
#define RTE_I2C2_SDA_PORT               GPIO_PORT_B
#define RTE_I2C2_SDA_BIT                GPIO_PIN_11
#else
#error "Invalid I2C2_SCL Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2C2_RX_DMA                 1
#define RTE_I2C2_RX_DMA_NUMBER          1
#define RTE_I2C2_RX_DMA_CHANNEL         5
#define RTE_I2C2_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2C2_TX_DMA                 1
#define RTE_I2C2_TX_DMA_NUMBER          1
#define RTE_I2C2_TX_DMA_CHANNEL         4
#define RTE_I2C2_TX_DMA_PRIORITY        0

// </e>


// <e> SPI1 (Serial Peripheral Interface 1) [Driver_SPI1]
// <i> Configuration settings for Driver_SPI1 in component ::CMSIS Driver:SPI
#define RTE_SPI1                        0

//   <o> SPI1_SCK Pin <0=>PA5
#define RTE_SPI1_SCK_PORT_ID_DEF        0
#if    (RTE_SPI1_SCK_PORT_ID_DEF == 0)
#define RTE_SPI1_SCK_PORT_DEF           GPIO_PORT_A
#define RTE_SPI1_SCK_BIT_DEF            GPIO_PIN_5
#else
#error "Invalid SPI1_SCK Pin Configuration!"
#endif

//   <o> SPI1_MISO Pin <0=>Not Used <1=>PA6
#define RTE_SPI1_MISO_PORT_ID_DEF       1
#if    (RTE_SPI1_MISO_PORT_ID_DEF == 0)
#define RTE_SPI1_MISO_DEF               0
#elif   (RTE_SPI1_MISO_PORT_ID_DEF == 1)
#define RTE_SPI1_MISO_DEF               1
#define RTE_SPI1_MISO_PORT_DEF          GPIO_PORT_A
#define RTE_SPI1_MISO_BIT_DEF           GPIO_PIN_6
#else
#error "Invalid SPI1_MISO Pin Configuration!"
#endif

//   <o> SPI1_MOSI Pin <0=>Not Used <1=>PA7
#define RTE_SPI1_MOSI_PORT_ID_DEF       1
#if    (RTE_SPI1_MOSI_PORT_ID_DEF == 0)
#define RTE_SPI1_MOSI_DEF               0
#elif  (RTE_SPI1_MOSI_PORT_ID_DEF == 1)
#define RTE_SPI1_MOSI_DEF               1
#define RTE_SPI1_MOSI_PORT_DEF          GPIO_PORT_A
#define RTE_SPI1_MOSI_BIT_DEF           GPIO_PIN_7
#else
#error "Invalid SPI1_MISO Pin Configuration!"
#endif

//   <o> SPI1_NSS Pin <0=>Not Used <1=>PA4
#define RTE_SPI1_NSS_PORT_ID_DEF        1
#if    (RTE_SPI1_NSS_PORT_ID_DEF == 0)
#define RTE_SPI1_NSS_DEF                0
#elif  (RTE_SPI1_NSS_PORT_ID_DEF == 1)
#define RTE_SPI1_NSS_DEF                1
#define RTE_SPI1_NSS_PORT_DEF           GPIO_PORT_A
#define RTE_SPI1_NSS_BIT_DEF            GPIO_PIN_4
#else
#error "Invalid SPI1_NSS Pin Configuration!"
#endif

//   <e> SPI1 Pin Remap
//   <i> Enable SPI1 Pin Remapping.
#define RTE_SPI1_REMAP                  1

//   <o> SPI1_SCK Pin <0=>PB3
#define RTE_SPI1_SCK_PORT_ID_FULL       0
#if    (RTE_SPI1_SCK_PORT_ID_FULL == 0)
#define RTE_SPI1_SCK_PORT_FULL          GPIO_PORT_B
#define RTE_SPI1_SCK_BIT_FULL           GPIO_PIN_3
#else
#error "Invalid SPI1_SCK Pin Configuration!"
#endif

//   <o> SPI1_MISO Pin <0=>Not Used <1=>PB4
#define RTE_SPI1_MISO_PORT_ID_FULL      1
#if    (RTE_SPI1_MISO_PORT_ID_FULL == 0)
#define RTE_SPI1_MISO_FULL              0
#elif  (RTE_SPI1_MISO_PORT_ID_FULL == 1)
#define RTE_SPI1_MISO_FULL              1
#define RTE_SPI1_MISO_PORT_FULL         GPIO_PORT_B
#define RTE_SPI1_MISO_BIT_FULL          GPIO_PIN_4
#else
#error "Invalid SPI1_MISO Pin Configuration!"
#endif

//   <o> SPI1_MOSI Pin <0=>Not Used <1=>PB5
#define RTE_SPI1_MOSI_PORT_ID_FULL      1
#if    (RTE_SPI1_MOSI_PORT_ID_FULL == 0)
#define RTE_SPI1_MOSI_FULL              0
#elif  (RTE_SPI1_MOSI_PORT_ID_FULL == 1)
#define RTE_SPI1_MOSI_FULL              1
#define RTE_SPI1_MOSI_PORT_FULL         GPIO_PORT_B
#define RTE_SPI1_MOSI_BIT_FULL          GPIO_PIN_5
#else
#error "Invalid SPI1_MOSI Pin Configuration!"
#endif

//   <o> SPI1_NSS Pin <0=>Not Used <1=>PA15
#define RTE_SPI1_NSS_PORT_ID_FULL       1
#if    (RTE_SPI1_NSS_PORT_ID_FULL == 0)
#define RTE_SPI1_NSS_FULL               0
#elif  (RTE_SPI1_NSS_PORT_ID_FULL == 1)
#define RTE_SPI1_NSS_FULL               1
#define RTE_SPI1_NSS_PORT_FULL          GPIO_PORT_A
#define RTE_SPI1_NSS_BIT_FULL           GPIO_PIN_15
#else
#error "Invalid SPI1_NSS Pin Configuration!"
#endif

//   </e>

#if    (RTE_SPI1_REMAP)
#define RTE_SPI1_AF_REMAP               AFIO_SPI1_REMAP
#define RTE_SPI1_SCK_PORT               RTE_SPI1_SCK_PORT_FULL
#define RTE_SPI1_SCK_BIT                RTE_SPI1_SCK_BIT_FULL
#define RTE_SPI1_MISO                   RTE_SPI1_MISO_FULL
#define RTE_SPI1_MISO_PORT              RTE_SPI1_MISO_PORT_FULL
#define RTE_SPI1_MISO_BIT               RTE_SPI1_MISO_BIT_FULL
#define RTE_SPI1_MOSI                   RTE_SPI1_MOSI_FULL
#define RTE_SPI1_MOSI_PORT              RTE_SPI1_MOSI_PORT_FULL
#define RTE_SPI1_MOSI_BIT               RTE_SPI1_MOSI_BIT_FULL
#define RTE_SPI1_NSS                    RTE_SPI1_NSS_FULL
#define RTE_SPI1_NSS_PORT               RTE_SPI1_NSS_PORT_FULL
#define RTE_SPI1_NSS_BIT                RTE_SPI1_NSS_BIT_FULL
#else
#define RTE_SPI1_AF_REMAP               AFIO_SPI1_NO_REMAP
#define RTE_SPI1_SCK_PORT               RTE_SPI1_SCK_PORT_DEF
#define RTE_SPI1_SCK_BIT                RTE_SPI1_SCK_BIT_DEF
#define RTE_SPI1_MISO                   RTE_SPI1_MISO_DEF
#define RTE_SPI1_MISO_PORT              RTE_SPI1_MISO_PORT_DEF
#define RTE_SPI1_MISO_BIT               RTE_SPI1_MISO_BIT_DEF
#define RTE_SPI1_MOSI                   RTE_SPI1_MOSI_DEF
#define RTE_SPI1_MOSI_PORT              RTE_SPI1_MOSI_PORT_DEF
#define RTE_SPI1_MOSI_BIT               RTE_SPI1_MOSI_BIT_DEF
#define RTE_SPI1_NSS                    RTE_SPI1_NSS_DEF
#define RTE_SPI1_NSS_PORT               RTE_SPI1_NSS_PORT_DEF
#define RTE_SPI1_NSS_BIT                RTE_SPI1_NSS_BIT_DEF
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <2=>2
//     <i>  Selects DMA Channel (only Channel 2 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI1_RX_DMA                 0
#define RTE_SPI1_RX_DMA_NUMBER          1
#define RTE_SPI1_RX_DMA_CHANNEL         2
#define RTE_SPI1_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI1_TX_DMA                 0
#define RTE_SPI1_TX_DMA_NUMBER          1
#define RTE_SPI1_TX_DMA_CHANNEL         3
#define RTE_SPI1_TX_DMA_PRIORITY        0

// </e>


// <e> SPI2 (Serial Peripheral Interface 2) [Driver_SPI2]
// <i> Configuration settings for Driver_SPI2 in component ::CMSIS Driver:SPI
#define RTE_SPI2                        0

//   <o> SPI2_SCK Pin <0=>PB13
#define RTE_SPI2_SCK_PORT_ID            0
#if    (RTE_SPI2_SCK_PORT_ID == 0)
#define RTE_SPI2_SCK_PORT               GPIO_PORT_B
#define RTE_SPI2_SCK_BIT                GPIO_PIN_13
#else
#error "Invalid SPI2_SCK Pin Configuration!"
#endif

//   <o> SPI2_MISO Pin <0=>Not Used <1=>PB14
#define RTE_SPI2_MISO_PORT_ID           1
#if    (RTE_SPI2_MISO_PORT_ID == 0)
#define RTE_SPI2_MISO                   0
#elif  (RTE_SPI2_MISO_PORT_ID == 1)
#define RTE_SPI2_MISO                   1
#define RTE_SPI2_MISO_PORT              GPIO_PORT_B
#define RTE_SPI2_MISO_BIT               GPIO_PIN_14
#else
#error "Invalid SPI2_MISO Pin Configuration!"
#endif

//   <o> SPI2_MOSI Pin <0=>Not Used <1=>PB15
#define RTE_SPI2_MOSI_PORT_ID           1
#if    (RTE_SPI2_MOSI_PORT_ID == 0)
#define RTE_SPI2_MOSI                   0
#elif  (RTE_SPI2_MOSI_PORT_ID == 1)
#define RTE_SPI2_MOSI                   1
#define RTE_SPI2_MOSI_PORT              GPIO_PORT_B
#define RTE_SPI2_MOSI_BIT               GPIO_PIN_15
#else
#error "Invalid SPI2_MISO Pin Configuration!"
#endif

//   <o> SPI2_NSS Pin <0=>Not Used <1=>PB12
#define RTE_SPI2_NSS_PORT_ID            1
#if    (RTE_SPI2_NSS_PORT_ID == 0)
#define RTE_SPI2_NSS                    0
#elif  (RTE_SPI2_NSS_PORT_ID == 1)
#define RTE_SPI2_NSS                    1
#define RTE_SPI2_NSS_PORT               GPIO_PORT_B
#define RTE_SPI2_NSS_BIT                GPIO_PIN_12
#else
#error "Invalid SPI2_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI2_RX_DMA                 1
#define RTE_SPI2_RX_DMA_NUMBER          1
#define RTE_SPI2_RX_DMA_CHANNEL         4
#define RTE_SPI2_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI2_TX_DMA                 1
#define RTE_SPI2_TX_DMA_NUMBER          1
#define RTE_SPI2_TX_DMA_CHANNEL         5
#define RTE_SPI2_TX_DMA_PRIORITY        0

// </e>


// <e> SPI3 (Serial Peripheral Interface 3) [Driver_SPI3]
// <i> Configuration settings for Driver_SPI3 in component ::CMSIS Driver:SPI
#define RTE_SPI3                        0

//   <o> SPI3_SCK Pin <0=>PB3
#define RTE_SPI3_SCK_PORT_ID_DEF        0
#if    (RTE_SPI3_SCK_PORT_ID_DEF == 0)
#define RTE_SPI3_SCK_PORT_DEF           GPIO_PORT_B
#define RTE_SPI3_SCK_BIT_DEF            GPIO_PIN_3
#else
#error "Invalid SPI3_SCK Pin Configuration!"
#endif

//   <o> SPI3_MISO Pin <0=>Not Used <1=>PB4
#define RTE_SPI3_MISO_PORT_ID_DEF       1
#if    (RTE_SPI3_MISO_PORT_ID_DEF == 0)
#define RTE_SPI3_MISO_DEF               0
#elif  (RTE_SPI3_MISO_PORT_ID_DEF == 1)
#define RTE_SPI3_MISO_DEF               1
#define RTE_SPI3_MISO_PORT_DEF          GPIO_PORT_B
#define RTE_SPI3_MISO_BIT_DEF           GPIO_PIN_4
#else
#error "Invalid SPI3_MISO Pin Configuration!"
#endif

//   <o> SPI3_MOSI Pin <0=>Not Used <1=>PB5
#define RTE_SPI3_MOSI_PORT_ID_DEF       1
#if    (RTE_SPI3_MOSI_PORT_ID_DEF == 0)
#define RTE_SPI3_MOSI_DEF               0
#elif  (RTE_SPI3_MOSI_PORT_ID_DEF == 1)
#define RTE_SPI3_MOSI_DEF               1
#define RTE_SPI3_MOSI_PORT_DEF          GPIO_PORT_B
#define RTE_SPI3_MOSI_BIT_DEF           GPIO_PIN_5
#else
#error "Invalid SPI3_MOSI Pin Configuration!"
#endif

//   <o> SPI3_NSS Pin <0=>Not Used <1=>PA15
#define RTE_SPI3_NSS_PORT_ID_DEF        1
#if    (RTE_SPI3_NSS_PORT_ID_DEF == 0)
#define RTE_SPI3_NSS_DEF                0
#elif  (RTE_SPI3_NSS_PORT_ID_DEF == 1)
#define RTE_SPI3_NSS_DEF                1
#define RTE_SPI3_NSS_PORT_DEF           GPIO_PORT_A
#define RTE_SPI3_NSS_BIT_DEF            GPIO_PIN_15
#else
#error "Invalid SPI3_NSS Pin Configuration!"
#endif

//   <e> SPI3 Pin Remap
//   <i> Enable SPI3 Pin Remapping.
//   <i> SPI 3 Pin Remapping is available only in connectivity line devices!
#define RTE_SPI3_REMAP                  0

//   <o> SPI3_SCK Pin <0=>PC10
#define RTE_SPI3_SCK_PORT_ID_FULL       0
#if    (RTE_SPI3_SCK_PORT_ID_FULL == 0)
#define RTE_SPI3_SCK_PORT_FULL          GPIO_PORT_C
#define RTE_SPI3_SCK_BIT_FULL           GPIO_PIN_10
#else
#error "Invalid SPI3_SCK Pin Configuration!"
#endif

//   <o> SPI3_MISO Pin <0=>Not Used <1=>PC11
#define RTE_SPI3_MISO_PORT_ID_FULL      1
#if    (RTE_SPI3_MISO_PORT_ID_FULL == 0)
#define RTE_SPI3_MISO_FULL              0
#elif  (RTE_SPI3_MISO_PORT_ID_FULL == 1)
#define RTE_SPI3_MISO_FULL              1
#define RTE_SPI3_MISO_PORT_FULL         GPIO_PORT_C
#define RTE_SPI3_MISO_BIT_FULL          GPIO_PIN_11
#else
#error "Invalid SPI3_MISO Pin Configuration!"
#endif

//   <o> SPI3_MOSI Pin <0=>Not Used <1=>PC12
#define RTE_SPI3_MOSI_PORT_ID_FULL      1
#if    (RTE_SPI3_MOSI_PORT_ID_FULL == 0)
#define RTE_SPI3_MOSI_FULL              0
#elif  (RTE_SPI3_MOSI_PORT_ID_FULL == 1)
#define RTE_SPI3_MOSI_FULL              1
#define RTE_SPI3_MOSI_PORT_FULL         GPIO_PORT_C
#define RTE_SPI3_MOSI_BIT_FULL          GPIO_PIN_12
#else
#error "Invalid SPI3_MOSI Pin Configuration!"
#endif

//   <o> SPI3_NSS Pin <0=>Not Used <1=>PA4
#define RTE_SPI3_NSS_PORT_ID_FULL       1
#if    (RTE_SPI3_NSS_PORT_ID_FULL == 0)
#define RTE_SPI3_NSS_FULL               0
#elif  (RTE_SPI3_NSS_PORT_ID_FULL == 1)
#define RTE_SPI3_NSS_FULL               1
#define RTE_SPI3_NSS_PORT_FULL          GPIO_PORT_A
#define RTE_SPI3_NSS_BIT_FULL           GPIO_PIN_4
#else
#error "Invalid SPI3_NSS Pin Configuration!"
#endif

//   </e>

#if    (RTE_SPI3_REMAP)
#define RTE_SPI3_AF_REMAP               AFIO_SPI3_REMAP
#define RTE_SPI3_SCK_PORT               RTE_SPI3_SCK_PORT_FULL
#define RTE_SPI3_SCK_BIT                RTE_SPI3_SCK_BIT_FULL
#define RTE_SPI3_MISO                   RTE_SPI3_MISO_FULL
#define RTE_SPI3_MISO_PORT              RTE_SPI3_MISO_PORT_FULL
#define RTE_SPI3_MISO_BIT               RTE_SPI3_MISO_BIT_FULL
#define RTE_SPI3_MOSI                   RTE_SPI3_MOSI_FULL
#define RTE_SPI3_MOSI_PORT              RTE_SPI3_MOSI_PORT_FULL
#define RTE_SPI3_MOSI_BIT               RTE_SPI3_MOSI_BIT_FULL
#define RTE_SPI3_NSS                    RTE_SPI3_NSS_FULL
#define RTE_SPI3_NSS_PORT               RTE_SPI3_NSS_PORT_FULL
#define RTE_SPI3_NSS_BIT                RTE_SPI3_NSS_BIT_FULL
#else
#define RTE_SPI3_AF_REMAP               AFIO_SPI3_NO_REMAP
#define RTE_SPI3_SCK_PORT               RTE_SPI3_SCK_PORT_DEF
#define RTE_SPI3_SCK_BIT                RTE_SPI3_SCK_BIT_DEF
#define RTE_SPI3_MISO                   RTE_SPI3_MISO_DEF
#define RTE_SPI3_MISO_PORT              RTE_SPI3_MISO_PORT_DEF
#define RTE_SPI3_MISO_BIT               RTE_SPI3_MISO_BIT_DEF
#define RTE_SPI3_MOSI                   RTE_SPI3_MOSI_DEF
#define RTE_SPI3_MOSI_PORT              RTE_SPI3_MOSI_PORT_DEF
#define RTE_SPI3_MOSI_BIT               RTE_SPI3_MOSI_BIT_DEF
#define RTE_SPI3_NSS                    RTE_SPI3_NSS_DEF
#define RTE_SPI3_NSS_PORT               RTE_SPI3_NSS_PORT_DEF
#define RTE_SPI3_NSS_BIT                RTE_SPI3_NSS_BIT_DEF
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI3_RX_DMA                 0
#define RTE_SPI3_RX_DMA_NUMBER          2
#define RTE_SPI3_RX_DMA_CHANNEL         1
#define RTE_SPI3_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <2=>2
//     <i>  Selects DMA Channel (only Channel 2 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI3_TX_DMA                 0
#define RTE_SPI3_TX_DMA_NUMBER          2
#define RTE_SPI3_TX_DMA_CHANNEL         2
#define RTE_SPI3_TX_DMA_PRIORITY        0

// </e>

// <e> DAC1 (Digital to Analog Converter 1) [Driver_DAC1]
// <i> Configuration settings for Driver_DAC1
#define RTE_DAC1                        0

//   <o> CH1_OUT Pin <0=>Not Used <1=>PA4
#define RTE_DAC1_CH1_OUT_PORT_ID_DEF    1
#if    (RTE_DAC1_CH1_OUT_PORT_ID_DEF == 0)
#define RTE_DAC1_CH1_OUT                0
#elif  (RTE_DAC1_CH1_OUT_PORT_ID_DEF == 1)
#define RTE_DAC1_CH1_OUT                1
#define RTE_DAC1_CH1_OUT_PORT           GPIO_PORT_A
#define RTE_DAC1_CH1_OUT_BIT            GPIO_PIN_4
#else
#error "Invalid CH1_OUT Pin Configuration!"
#endif

//   <o> CH2_OUT Pin <0=>Not Used <1=>PA5
#define RTE_DAC1_CH2_OUT_PORT_ID_DEF    1
#if    (RTE_DAC1_CH2_OUT_PORT_ID_DEF == 0)
#define RTE_DAC1_CH2_OUT                0
#elif  (RTE_DAC1_CH2_OUT_PORT_ID_DEF == 1)
#define RTE_DAC1_CH2_OUT                1
#define RTE_DAC1_CH2_OUT_PORT           GPIO_PORT_A
#define RTE_DAC1_CH2_OUT_BIT            GPIO_PIN_5
#else
#error "Invalid CH2_OUT Pin Configuration!"
#endif

//   <o> Trigger <0=>Not Used <1=>Timer 6 <2=>Timer 7
#define RTE_DAC1_TRIGGER_SELECTION_DEF    0
#if    (RTE_DAC1_TRIGGER_SELECTION_DEF == 0)
#define RTE_DAC1_TRIGGER_HARDWARE         0
#elif  (RTE_DAC1_TRIGGER_SELECTION_DEF == 1)
#define RTE_DAC1_TRIGGER_HARDWARE         1
#define RTE_DAC1_TRIGGER_SELECT           6
#elif  (RTE_DAC1_TRIGGER_SELECTION_DEF == 2)
#define RTE_DAC1_TRIGGER_HARDWARE         1
#define RTE_DAC1_TRIGGER_SELECT           7
#else
#error "Invalid RTE_DAC1_TRIGGER_SELECTION_DEF Configuration!"
#endif

//   <e> DMA DAC1_CH1
//     <o1> Number <1=>1 <2=>2
//     <i>  Selects DMA Number
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_DAC1_CH1_DMA                 0
#define RTE_DAC1_CH1_DMA_NUMBER          2
#define RTE_DAC1_CH1_DMA_CHANNEL         3
#define RTE_DAC1_CH1_DMA_PRIORITY        0

//   <e> DMA DAC1_CH2
//     <o1> Number <1=>1 <2=>2
//     <i>  Selects DMA Number
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_DAC1_CH2_DMA                 0
#define RTE_DAC1_CH2_DMA_NUMBER          2
#define RTE_DAC1_CH2_DMA_CHANNEL         4
#define RTE_DAC1_CH2_DMA_PRIORITY        0

// </e>


// <e> ADC1 (Analog to Digital Converter 1) [Driver_ADC1]
// <i> Configuration settings for Driver_ADC1
#define RTE_ADC1                        0

//   <o> IN0 Pin <0=>Not Used <1=>PA0
#define RTE_ADC1_IN0_PORT_ID            1
#if    (RTE_ADC1_IN0_PORT_ID == 0)
#define RTE_ADC1_IN0                    0
#elif  (RTE_ADC1_IN0_PORT_ID == 1)
#define RTE_ADC1_IN0                    1
#define RTE_ADC123_IN0_PORT             GPIO_PORT_A
#define RTE_ADC123_IN0_BIT              GPIO_PIN_0
#else
#error "Invalid IN0 Pin Configuration!"
#endif

//   <o> IN1 Pin <0=>Not Used <1=>PA1
#define RTE_ADC1_IN1_PORT_ID            0
#if    (RTE_ADC1_IN1_PORT_ID == 0)
#define RTE_ADC1_IN1                    0
#elif  (RTE_ADC1_IN1_PORT_ID == 1)
#define RTE_ADC1_IN1                    1
#define RTE_ADC123_IN1_PORT             GPIO_PORT_A
#define RTE_ADC123_IN1_BIT              GPIO_PIN_1
#else
#error "Invalid IN1 Pin Configuration!"
#endif

//   <o> IN2 Pin <0=>Not Used <1=>PA2
#define RTE_ADC1_IN2_PORT_ID            0
#if    (RTE_ADC1_IN2_PORT_ID == 0)
#define RTE_ADC1_IN2                    0
#elif  (RTE_ADC1_IN2_PORT_ID == 1)
#define RTE_ADC1_IN2                    1
#define RTE_ADC123_IN2_PORT             GPIO_PORT_A
#define RTE_ADC123_IN2_BIT              GPIO_PIN_2
#else
#error "Invalid IN2 Pin Configuration!"
#endif

//   <o> IN3 Pin <0=>Not Used <1=>PA3
#define RTE_ADC1_IN3_PORT_ID            0
#if    (RTE_ADC1_IN3_PORT_ID == 0)
#define RTE_ADC1_IN3                    0
#elif  (RTE_ADC1_IN3_PORT_ID == 1)
#define RTE_ADC1_IN3                    1
#define RTE_ADC123_IN3_PORT             GPIO_PORT_A
#define RTE_ADC123_IN3_BIT              GPIO_PIN_3
#else
#error "Invalid IN3 Pin Configuration!"
#endif

//   <o> IN4 Pin <0=>Not Used <1=>PA4
#define RTE_ADC1_IN4_PORT_ID            0
#if    (RTE_ADC1_IN4_PORT_ID == 0)
#define RTE_ADC1_IN4                    0
#elif  (RTE_ADC1_IN4_PORT_ID == 1)
#define RTE_ADC1_IN4                    1
#define RTE_ADC12_IN4_PORT              GPIO_PORT_A
#define RTE_ADC12_IN4_BIT               GPIO_PIN_4
#else
#error "Invalid IN4 Pin Configuration!"
#endif

//   <o> IN5 Pin <0=>Not Used <1=>PA5
#define RTE_ADC1_IN5_PORT_ID            0
#if    (RTE_ADC1_IN5_PORT_ID == 0)
#define RTE_ADC1_IN5                    0
#elif  (RTE_ADC1_IN5_PORT_ID == 1)
#define RTE_ADC1_IN5                    1
#define RTE_ADC12_IN5_PORT              GPIO_PORT_A
#define RTE_ADC12_IN5_BIT               GPIO_PIN_5
#else
#error "Invalid IN5 Pin Configuration!"
#endif

//   <o> IN6 Pin <0=>Not Used <1=>PA6
#define RTE_ADC1_IN6_PORT_ID            0
#if    (RTE_ADC1_IN6_PORT_ID == 0)
#define RTE_ADC1_IN6                    0
#elif  (RTE_ADC1_IN6_PORT_ID == 1)
#define RTE_ADC1_IN6                    1
#define RTE_ADC12_IN6_PORT              GPIO_PORT_A
#define RTE_ADC12_IN6_BIT               GPIO_PIN_6
#else
#error "Invalid IN6 Pin Configuration!"
#endif

//   <o> IN7 Pin <0=>Not Used <1=>PA7
#define RTE_ADC1_IN7_PORT_ID            0
#if    (RTE_ADC1_IN7_PORT_ID == 0)
#define RTE_ADC1_IN7                    0
#elif  (RTE_ADC1_IN7_PORT_ID == 1)
#define RTE_ADC1_IN7                    1
#define RTE_ADC12_IN7_PORT              GPIO_PORT_A
#define RTE_ADC12_IN7_BIT               GPIO_PIN_7
#else
#error "Invalid IN7 Pin Configuration!"
#endif

//   <o> IN8 Pin <0=>Not Used <1=>PB0
#define RTE_ADC1_IN8_PORT_ID            0
#if    (RTE_ADC1_IN8_PORT_ID == 0)
#define RTE_ADC1_IN8                    0
#elif  (RTE_ADC1_IN8_PORT_ID == 1)
#define RTE_ADC1_IN8                    1
#define RTE_ADC12_IN8_PORT              GPIO_PORT_B
#define RTE_ADC12_IN8_BIT               GPIO_PIN_0
#else
#error "Invalid IN8 Pin Configuration!"
#endif

//   <o> IN9 Pin <0=>Not Used <1=>PB1
#define RTE_ADC1_IN9_PORT_ID            0
#if    (RTE_ADC1_IN9_PORT_ID == 0)
#define RTE_ADC1_IN9                    0
#elif  (RTE_ADC1_IN9_PORT_ID == 1)
#define RTE_ADC1_IN9                    1
#define RTE_ADC12_IN9_PORT              GPIO_PORT_B
#define RTE_ADC12_IN9_BIT               GPIO_PIN_1
#else
#error "Invalid IN9 Pin Configuration!"
#endif

//   <o> IN10 Pin <0=>Not Used <1=>PC0
#define RTE_ADC1_IN10_PORT_ID           0
#if    (RTE_ADC1_IN10_PORT_ID == 0)
#define RTE_ADC1_IN10                   0
#elif  (RTE_ADC1_IN10_PORT_ID == 1)
#define RTE_ADC1_IN10                   1
#define RTE_ADC123_IN10_PORT            GPIO_PORT_C
#define RTE_ADC123_IN10_BIT             GPIO_PIN_0
#else
#error "Invalid IN10 Pin Configuration!"
#endif

//   <o> IN11 Pin <0=>Not Used <1=>PC1
#define RTE_ADC1_IN11_PORT_ID           0
#if    (RTE_ADC1_IN11_PORT_ID == 0)
#define RTE_ADC1_IN11                   0
#elif  (RTE_ADC1_IN11_PORT_ID == 1)
#define RTE_ADC1_IN11                   1
#define RTE_ADC123_IN11_PORT            GPIO_PORT_C
#define RTE_ADC123_IN11_BIT             GPIO_PIN_1
#else
#error "Invalid IN11 Pin Configuration!"
#endif

//   <o> IN12 Pin <0=>Not Used <1=>PC2
#define RTE_ADC1_IN12_PORT_ID           1
#if    (RTE_ADC1_IN12_PORT_ID == 0)
#define RTE_ADC1_IN12                   0
#elif  (RTE_ADC1_IN12_PORT_ID == 1)
#define RTE_ADC1_IN12                   1
#define RTE_ADC123_IN12_PORT            GPIO_PORT_C
#define RTE_ADC123_IN12_BIT             GPIO_PIN_2
#else
#error "Invalid IN12 Pin Configuration!"
#endif

//   <o> IN13 Pin <0=>Not Used <1=>PC3
#define RTE_ADC1_IN13_PORT_ID           1
#if    (RTE_ADC1_IN13_PORT_ID == 0)
#define RTE_ADC1_IN13                   0
#elif  (RTE_ADC1_IN13_PORT_ID == 1)
#define RTE_ADC1_IN13                   1
#define RTE_ADC123_IN13_PORT            GPIO_PORT_C
#define RTE_ADC123_IN13_BIT             GPIO_PIN_3
#else
#error "Invalid IN13 Pin Configuration!"
#endif

//   <o> IN14 Pin <0=>Not Used <1=>PC4
#define RTE_ADC1_IN14_PORT_ID           0
#if    (RTE_ADC1_IN14_PORT_ID == 0)
#define RTE_ADC1_IN14                   0
#elif  (RTE_ADC1_IN14_PORT_ID == 1)
#define RTE_ADC1_IN14                   1
#define RTE_ADC12_IN14_PORT             GPIO_PORT_C
#define RTE_ADC12_IN14_BIT              GPIO_PIN_4
#else
#error "Invalid IN14 Pin Configuration!"
#endif

//   <o> IN15 Pin <0=>Not Used <1=>PC5
#define RTE_ADC1_IN15_PORT_ID           0
#if    (RTE_ADC1_IN15_PORT_ID == 0)
#define RTE_ADC1_IN15                   0
#elif  (RTE_ADC1_IN15_PORT_ID == 1)
#define RTE_ADC1_IN15                   1
#define RTE_ADC12_IN15_PORT             GPIO_PORT_C
#define RTE_ADC12_IN15_BIT              GPIO_PIN_5
#else
#error "Invalid IN15 Pin Configuration!"
#endif

//   <e> DMA
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_ADC1_DMA                    1
#define RTE_ADC1_DMA_NUMBER             1
#define RTE_ADC1_DMA_CHANNEL            1
#define RTE_ADC1_DMA_PRIORITY           0

// </e>


// <e> ADC2 (Analog to Digital Converter 2) [Driver_ADC2]
// <i> Configuration settings for Driver_ADC2
#define RTE_ADC2                        0

//   <o> IN0 Pin <0=>Not Used <1=>PA0
#define RTE_ADC2_IN0_PORT_ID            1
#if    (RTE_ADC2_IN0_PORT_ID == 0)
#define RTE_ADC2_IN0                    0
#elif  (RTE_ADC2_IN0_PORT_ID == 1)
#define RTE_ADC2_IN0                    1
#define RTE_ADC123_IN0_PORT             GPIO_PORT_A
#define RTE_ADC123_IN0_BIT              GPIO_PIN_0
#else
#error "Invalid IN0 Pin Configuration!"
#endif

//   <o> IN1 Pin <0=>Not Used <1=>PA1
#define RTE_ADC2_IN1_PORT_ID            0
#if    (RTE_ADC2_IN1_PORT_ID == 0)
#define RTE_ADC2_IN1                    0
#elif  (RTE_ADC2_IN1_PORT_ID == 1)
#define RTE_ADC2_IN1                    1
#define RTE_ADC123_IN1_PORT             GPIO_PORT_A
#define RTE_ADC123_IN1_BIT              GPIO_PIN_1
#else
#error "Invalid IN1 Pin Configuration!"
#endif

//   <o> IN2 Pin <0=>Not Used <1=>PA2
#define RTE_ADC2_IN2_PORT_ID            0
#if    (RTE_ADC2_IN2_PORT_ID == 0)
#define RTE_ADC2_IN2                    0
#elif  (RTE_ADC2_IN2_PORT_ID == 1)
#define RTE_ADC2_IN2                    1
#define RTE_ADC123_IN2_PORT             GPIO_PORT_A
#define RTE_ADC123_IN2_BIT              GPIO_PIN_2
#else
#error "Invalid IN2 Pin Configuration!"
#endif

//   <o> IN3 Pin <0=>Not Used <1=>PA3
#define RTE_ADC2_IN3_PORT_ID            0
#if    (RTE_ADC2_IN3_PORT_ID == 0)
#define RTE_ADC2_IN3                    0
#elif  (RTE_ADC2_IN3_PORT_ID == 1)
#define RTE_ADC2_IN3                    1
#define RTE_ADC123_IN3_PORT             GPIO_PORT_A
#define RTE_ADC123_IN3_BIT              GPIO_PIN_3
#else
#error "Invalid IN3 Pin Configuration!"
#endif

//   <o> IN4 Pin <0=>Not Used <1=>PA4
#define RTE_ADC2_IN4_PORT_ID            0
#if    (RTE_ADC2_IN4_PORT_ID == 0)
#define RTE_ADC2_IN4                    0
#elif  (RTE_ADC2_IN4_PORT_ID == 1)
#define RTE_ADC2_IN4                    1
#define RTE_ADC12_IN4_PORT              GPIO_PORT_A
#define RTE_ADC12_IN4_BIT               GPIO_PIN_4
#else
#error "Invalid IN4 Pin Configuration!"
#endif

//   <o> IN5 Pin <0=>Not Used <1=>PA5
#define RTE_ADC2_IN5_PORT_ID            0
#if    (RTE_ADC2_IN5_PORT_ID == 0)
#define RTE_ADC2_IN5                    0
#elif  (RTE_ADC2_IN5_PORT_ID == 1)
#define RTE_ADC2_IN5                    1
#define RTE_ADC12_IN5_PORT              GPIO_PORT_A
#define RTE_ADC12_IN5_BIT               GPIO_PIN_5
#else
#error "Invalid IN5 Pin Configuration!"
#endif

//   <o> IN6 Pin <0=>Not Used <1=>PA6
#define RTE_ADC2_IN6_PORT_ID            0
#if    (RTE_ADC2_IN6_PORT_ID == 0)
#define RTE_ADC2_IN6                    0
#elif  (RTE_ADC2_IN6_PORT_ID == 1)
#define RTE_ADC2_IN6                    1
#define RTE_ADC12_IN6_PORT              GPIO_PORT_A
#define RTE_ADC12_IN6_BIT               GPIO_PIN_6
#else
#error "Invalid IN6 Pin Configuration!"
#endif

//   <o> IN7 Pin <0=>Not Used <1=>PA7
#define RTE_ADC2_IN7_PORT_ID            0
#if    (RTE_ADC2_IN7_PORT_ID == 0)
#define RTE_ADC2_IN7                    0
#elif  (RTE_ADC2_IN7_PORT_ID == 1)
#define RTE_ADC2_IN7                    1
#define RTE_ADC12_IN7_PORT              GPIO_PORT_A
#define RTE_ADC12_IN7_BIT               GPIO_PIN_7
#else
#error "Invalid IN7 Pin Configuration!"
#endif

//   <o> IN8 Pin <0=>Not Used <1=>PB0
#define RTE_ADC2_IN8_PORT_ID            0
#if    (RTE_ADC2_IN8_PORT_ID == 0)
#define RTE_ADC2_IN8                    0
#elif  (RTE_ADC2_IN8_PORT_ID == 1)
#define RTE_ADC2_IN8                    1
#define RTE_ADC12_IN8_PORT              GPIO_PORT_B
#define RTE_ADC12_IN8_BIT               GPIO_PIN_0
#else
#error "Invalid IN8 Pin Configuration!"
#endif

//   <o> IN9 Pin <0=>Not Used <1=>PB1
#define RTE_ADC2_IN9_PORT_ID            0
#if    (RTE_ADC2_IN9_PORT_ID == 0)
#define RTE_ADC2_IN9                    0
#elif  (RTE_ADC2_IN9_PORT_ID == 1)
#define RTE_ADC2_IN9                    1
#define RTE_ADC12_IN9_PORT              GPIO_PORT_B
#define RTE_ADC12_IN9_BIT               GPIO_PIN_1
#else
#error "Invalid IN9 Pin Configuration!"
#endif

//   <o> IN10 Pin <0=>Not Used <1=>PC0
#define RTE_ADC2_IN10_PORT_ID           0
#if    (RTE_ADC2_IN10_PORT_ID == 0)
#define RTE_ADC2_IN10                   0
#elif  (RTE_ADC2_IN10_PORT_ID == 1)
#define RTE_ADC2_IN10                   1
#define RTE_ADC123_IN10_PORT            GPIO_PORT_C
#define RTE_ADC123_IN10_BIT             GPIO_PIN_0
#else
#error "Invalid IN10 Pin Configuration!"
#endif

//   <o> IN11 Pin <0=>Not Used <1=>PC1
#define RTE_ADC2_IN11_PORT_ID           0
#if    (RTE_ADC2_IN11_PORT_ID == 0)
#define RTE_ADC2_IN11                   0
#elif  (RTE_ADC2_IN11_PORT_ID == 1)
#define RTE_ADC2_IN11                   1
#define RTE_ADC123_IN11_PORT            GPIO_PORT_C
#define RTE_ADC123_IN11_BIT             GPIO_PIN_1
#else
#error "Invalid IN11 Pin Configuration!"
#endif

//   <o> IN12 Pin <0=>Not Used <1=>PC2
#define RTE_ADC2_IN12_PORT_ID           0
#if    (RTE_ADC2_IN12_PORT_ID == 0)
#define RTE_ADC2_IN12                   0
#elif  (RTE_ADC2_IN12_PORT_ID == 1)
#define RTE_ADC2_IN12                   1
#define RTE_ADC123_IN12_PORT            GPIO_PORT_C
#define RTE_ADC123_IN12_BIT             GPIO_PIN_2
#else
#error "Invalid IN12 Pin Configuration!"
#endif

//   <o> IN13 Pin <0=>Not Used <1=>PC3
#define RTE_ADC2_IN13_PORT_ID           0
#if    (RTE_ADC2_IN13_PORT_ID == 0)
#define RTE_ADC2_IN13                   0
#elif  (RTE_ADC2_IN13_PORT_ID == 1)
#define RTE_ADC2_IN13                   1
#define RTE_ADC123_IN13_PORT            GPIO_PORT_C
#define RTE_ADC123_IN13_BIT             GPIO_PIN_3
#else
#error "Invalid IN13 Pin Configuration!"
#endif

//   <o> IN14 Pin <0=>Not Used <1=>PC4
#define RTE_ADC2_IN14_PORT_ID           0
#if    (RTE_ADC2_IN14_PORT_ID == 0)
#define RTE_ADC2_IN14                   0
#elif  (RTE_ADC2_IN14_PORT_ID == 1)
#define RTE_ADC2_IN14                   1
#define RTE_ADC12_IN14_PORT             GPIO_PORT_C
#define RTE_ADC12_IN14_BIT              GPIO_PIN_4
#else
#error "Invalid IN14 Pin Configuration!"
#endif

//   <o> IN15 Pin <0=>Not Used <1=>PC5
#define RTE_ADC2_IN15_PORT_ID           0
#if    (RTE_ADC2_IN15_PORT_ID == 0)
#define RTE_ADC2_IN15                   0
#elif  (RTE_ADC2_IN15_PORT_ID == 1)
#define RTE_ADC2_IN15                   1
#define RTE_ADC12_IN15_PORT             GPIO_PORT_C
#define RTE_ADC12_IN15_BIT              GPIO_PIN_5
#else
#error "Invalid IN15 Pin Configuration!"
#endif

// </e>


// <e> ADC3 (Analog to Digital Converter 3) [Driver_ADC3]
// <i> Configuration settings for Driver_ADC3
#define RTE_ADC3                        0

//   <o> IN0 Pin <0=>Not Used <1=>PA0
#define RTE_ADC3_IN0_PORT_ID            0
#if    (RTE_ADC3_IN0_PORT_ID == 0)
#define RTE_ADC3_IN0                    0
#elif  (RTE_ADC3_IN0_PORT_ID == 1)
#define RTE_ADC3_IN0                    1
#define RTE_ADC123_IN0_PORT             GPIO_PORT_A
#define RTE_ADC123_IN0_BIT              GPIO_PIN_0
#else
#error "Invalid IN0 Pin Configuration!"
#endif

//   <o> IN1 Pin <0=>Not Used <1=>PA1
#define RTE_ADC3_IN1_PORT_ID            0
#if    (RTE_ADC3_IN1_PORT_ID == 0)
#define RTE_ADC3_IN1                    0
#elif  (RTE_ADC3_IN1_PORT_ID == 1)
#define RTE_ADC3_IN1                    1
#define RTE_ADC123_IN1_PORT             GPIO_PORT_A
#define RTE_ADC123_IN1_BIT              GPIO_PIN_1
#else
#error "Invalid IN1 Pin Configuration!"
#endif

//   <o> IN2 Pin <0=>Not Used <1=>PA2
#define RTE_ADC3_IN2_PORT_ID            0
#if    (RTE_ADC3_IN2_PORT_ID == 0)
#define RTE_ADC3_IN2                    0
#elif  (RTE_ADC3_IN2_PORT_ID == 1)
#define RTE_ADC3_IN2                    1
#define RTE_ADC123_IN2_PORT             GPIO_PORT_A
#define RTE_ADC123_IN2_BIT              GPIO_PIN_2
#else
#error "Invalid IN2 Pin Configuration!"
#endif

//   <o> IN3 Pin <0=>Not Used <1=>PA3
#define RTE_ADC3_IN3_PORT_ID            0
#if    (RTE_ADC3_IN3_PORT_ID == 0)
#define RTE_ADC3_IN3                    0
#elif  (RTE_ADC3_IN3_PORT_ID == 1)
#define RTE_ADC3_IN3                    1
#define RTE_ADC123_IN3_PORT             GPIO_PORT_A
#define RTE_ADC123_IN3_BIT              GPIO_PIN_3
#else
#error "Invalid IN3 Pin Configuration!"
#endif

//   <o> IN4 Pin <0=>Not Used <1=>PF6
#define RTE_ADC3_IN4_PORT_ID            0
#if    (RTE_ADC3_IN4_PORT_ID == 0)
#define RTE_ADC3_IN4                    0
#elif  (RTE_ADC3_IN4_PORT_ID == 1)
#define RTE_ADC3_IN4                    1
#define RTE_ADC3_IN4_PORT               GPIO_PORT_F
#define RTE_ADC3_IN4_BIT                GPIO_PIN_6
#else
#error "Invalid IN4 Pin Configuration!"
#endif

//   <o> IN5 Pin <0=>Not Used <1=>PF7
#define RTE_ADC3_IN5_PORT_ID            0
#if    (RTE_ADC3_IN5_PORT_ID == 0)
#define RTE_ADC3_IN5                    0
#elif  (RTE_ADC3_IN5_PORT_ID == 1)
#define RTE_ADC3_IN5                    1
#define RTE_ADC3_IN5_PORT               GPIO_PORT_F
#define RTE_ADC3_IN5_BIT                GPIO_PIN_7
#else
#error "Invalid IN5 Pin Configuration!"
#endif

//   <o> IN6 Pin <0=>Not Used <1=>PF8
#define RTE_ADC3_IN6_PORT_ID            0
#if    (RTE_ADC3_IN6_PORT_ID == 0)
#define RTE_ADC3_IN6                    0
#elif  (RTE_ADC3_IN6_PORT_ID == 1)
#define RTE_ADC3_IN6                    1
#define RTE_ADC3_IN6_PORT               GPIO_PORT_F
#define RTE_ADC3_IN6_BIT                GPIO_PIN_8
#else
#error "Invalid IN6 Pin Configuration!"
#endif

//   <o> IN7 Pin <0=>Not Used <1=>PF9
#define RTE_ADC3_IN7_PORT_ID            0
#if    (RTE_ADC3_IN7_PORT_ID == 0)
#define RTE_ADC3_IN7                    0
#elif  (RTE_ADC3_IN7_PORT_ID == 1)
#define RTE_ADC3_IN7                    1
#define RTE_ADC3_IN7_PORT               GPIO_PORT_F
#define RTE_ADC3_IN7_BIT                GPIO_PIN_9
#else
#error "Invalid IN7 Pin Configuration!"
#endif

//   <o> IN8 Pin <0=>Not Used <1=>PF10
#define RTE_ADC3_IN8_PORT_ID            0
#if    (RTE_ADC3_IN8_PORT_ID == 0)
#define RTE_ADC3_IN8                    0
#elif  (RTE_ADC3_IN8_PORT_ID == 1)
#define RTE_ADC3_IN8                    1
#define RTE_ADC3_IN8_PORT               GPIO_PORT_F
#define RTE_ADC3_IN8_BIT                GPIO_PIN_10
#else
#error "Invalid IN8 Pin Configuration!"
#endif

//   <o> IN10 Pin <0=>Not Used <1=>PC0
#define RTE_ADC3_IN10_PORT_ID           0
#if    (RTE_ADC3_IN10_PORT_ID == 0)
#define RTE_ADC3_IN10                   0
#elif  (RTE_ADC3_IN10_PORT_ID == 1)
#define RTE_ADC3_IN10                   1
#define RTE_ADC123_IN10_PORT            GPIO_PORT_C
#define RTE_ADC123_IN10_BIT             GPIO_PIN_0
#else
#error "Invalid IN10 Pin Configuration!"
#endif

//   <o> IN11 Pin <0=>Not Used <1=>PC1
#define RTE_ADC3_IN11_PORT_ID           0
#if    (RTE_ADC3_IN11_PORT_ID == 0)
#define RTE_ADC3_IN11                   0
#elif  (RTE_ADC3_IN11_PORT_ID == 1)
#define RTE_ADC3_IN11                   1
#define RTE_ADC123_IN11_PORT            GPIO_PORT_C
#define RTE_ADC123_IN11_BIT             GPIO_PIN_1
#else
#error "Invalid IN11 Pin Configuration!"
#endif

//   <o> IN12 Pin <0=>Not Used <1=>PC2
#define RTE_ADC3_IN12_PORT_ID           0
#if    (RTE_ADC3_IN12_PORT_ID == 0)
#define RTE_ADC3_IN12                   0
#elif  (RTE_ADC3_IN12_PORT_ID == 1)
#define RTE_ADC3_IN12                   1
#define RTE_ADC123_IN12_PORT            GPIO_PORT_C
#define RTE_ADC123_IN12_BIT             GPIO_PIN_2
#else
#error "Invalid IN12 Pin Configuration!"
#endif

//   <o> IN13 Pin <0=>Not Used <1=>PC3
#define RTE_ADC3_IN13_PORT_ID           0
#if    (RTE_ADC3_IN13_PORT_ID == 0)
#define RTE_ADC3_IN13                   0
#elif  (RTE_ADC3_IN13_PORT_ID == 1)
#define RTE_ADC3_IN13                   1
#define RTE_ADC123_IN13_PORT            GPIO_PORT_C
#define RTE_ADC123_IN13_BIT             GPIO_PIN_3
#else
#error "Invalid IN13 Pin Configuration!"
#endif

//   <e> DMA
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_ADC3_DMA                    1
#define RTE_ADC3_DMA_NUMBER             2
#define RTE_ADC3_DMA_CHANNEL            5
#define RTE_ADC3_DMA_PRIORITY           0

// </e>


// <e> SDIO (Secure Digital Input/Output) [Driver_MCI0]
// <i> Configuration settings for Driver_MCI0 in component ::CMSIS Driver:MCI
#define RTE_SDIO                        0

//   <h> SDIO Peripheral Bus
//     <o> SDIO_CK Pin <0=>PC12
#define   RTE_SDIO_CK_PORT_ID           0
#if      (RTE_SDIO_CK_PORT_ID == 0)
  #define RTE_SDIO_CK_PORT              GPIO_PORT_C
  #define RTE_SDIO_CK_PIN               GPIO_PIN_12
#else
  #error "Invalid SDIO_CLK Pin Configuration!"
#endif
//     <o> SDIO_CMD Pin <0=>PD2
#define   RTE_SDIO_CMD_PORT_ID          0
#if      (RTE_SDIO_CMD_PORT_ID == 0)
  #define RTE_SDIO_CMD_PORT             GPIO_PORT_D
  #define RTE_SDIO_CMD_PIN              GPIO_PIN_2
#else
  #error "Invalid SDIO_CMD Pin Configuration!"
#endif
//     <o> SDIO_D0 Pin <0=>PC8
#define   RTE_SDIO_D0_PORT_ID           0
#if      (RTE_SDIO_D0_PORT_ID == 0)
  #define RTE_SDIO_D0_PORT              GPIO_PORT_C
  #define RTE_SDIO_D0_PIN               GPIO_PIN_8
#else
  #error "Invalid SDIO_DAT0 Pin Configuration!"
#endif
//     <e> SDIO_D[1 .. 3]
#define   RTE_SDIO_BUS_WIDTH_4          1
//       <o> SDIO_D1 Pin <0=>PC9
#define   RTE_SDIO_D1_PORT_ID           0
#if      (RTE_SDIO_D1_PORT_ID == 0)
  #define RTE_SDIO_D1_PORT              GPIO_PORT_C
  #define RTE_SDIO_D1_PIN               GPIO_PIN_9
#else
  #error "Invalid SDIO_D1 Pin Configuration!"
#endif
//       <o> SDIO_D2 Pin <0=>PC10
#define   RTE_SDIO_D2_PORT_ID           0
#if      (RTE_SDIO_D2_PORT_ID == 0)
  #define RTE_SDIO_D2_PORT              GPIO_PORT_C
  #define RTE_SDIO_D2_PIN               GPIO_PIN_10
#else
  #error "Invalid SDIO_D2 Pin Configuration!"
#endif
//       <o> SDIO_D3 Pin <0=>PC11
#define   RTE_SDIO_D3_PORT_ID           0
#if      (RTE_SDIO_D3_PORT_ID == 0)
  #define RTE_SDIO_D3_PORT              GPIO_PORT_C
  #define RTE_SDIO_D3_PIN               GPIO_PIN_11
#else
  #error "Invalid SDIO_D3 Pin Configuration!"
#endif
//     </e> SDIO_D[1 .. 3]
//     <e> SDIO_D[4 .. 7]
#define   RTE_SDIO_BUS_WIDTH_8          0
//       <o> SDIO_D4 Pin <0=>PB8
#define   RTE_SDIO_D4_PORT_ID           0
#if      (RTE_SDIO_D4_PORT_ID == 0)
  #define RTE_SDIO_D4_PORT              GPIO_PORT_B
  #define RTE_SDIO_D4_PIN               GPIO_PIN_8
#else
  #error "Invalid SDIO_D4 Pin Configuration!"
#endif
//       <o> SDIO_D5 Pin <0=>PB9
#define   RTE_SDIO_D5_PORT_ID           0
#if      (RTE_SDIO_D5_PORT_ID == 0)
  #define RTE_SDIO_D5_PORT              GPIO_PORT_B
  #define RTE_SDIO_D5_PIN               GPIO_PIN_9
#else
  #error "Invalid SDIO_D5 Pin Configuration!"
#endif
//       <o> SDIO_D6 Pin <0=>PC6
#define   RTE_SDIO_D6_PORT_ID           0
#if      (RTE_SDIO_D6_PORT_ID == 0)
  #define RTE_SDIO_D6_PORT              GPIO_PORT_C
  #define RTE_SDIO_D6_PIN               GPIO_PIN_6
#else
  #error "Invalid SDIO_D6 Pin Configuration!"
#endif
//       <o> SDIO_D7 Pin <0=>PC7
#define   RTE_SDIO_D7_PORT_ID           0
#if      (RTE_SDIO_D7_PORT_ID == 0)
  #define RTE_SDIO_D7_PORT              GPIO_PORT_C
  #define RTE_SDIO_D7_PIN               GPIO_PIN_7
#else
  #error "Invalid SDIO_D7 Pin Configuration!"
#endif
//     </e> SDIO_D[4 .. 7]
//   </h> SDIO Peripheral Bus

//   <e> Card Detect Pin
//   <i> Configure Pin if exists
//   <i> GPIO Pxy (x = A..H, y = 0..15) or (x = I, y = 0..11)
//     <o1> Active State <0=>Low <1=>High
//     <i>  Selects Active State Logical Level
//     <o2> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD
//               <4=>GPIOE <5=>GPIOF <6=>GPIOG
//     <i>  Selects Port Name
//     <o3> Bit <0-15>
//     <i>  Selects Port Bit
//   </e>
#define RTE_SDIO_CD_EN                  1
#define RTE_SDIO_CD_ACTIVE              0
#define RTE_SDIO_CD_PORT                GPIO_PORT(5)
#define RTE_SDIO_CD_PIN                 GPIO_PIN_11

//   <e> Write Protect Pin
//   <i> Configure Pin if exists
//   <i> GPIO Pxy (x = A..H, y = 0..15) or (x = I, y = 0..11)
//     <o1> Active State <0=>Low <1=>High
//     <i>  Selects Active State Logical Level
//     <o2> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD
//               <4=>GPIOE <5=>GPIOF <6=>GPIOG
//     <i>  Selects Port Name
//     <o3> Bit <0-15>
//     <i>  Selects Port Bit
//   </e>
#define RTE_SDIO_WP_EN                  0
#define RTE_SDIO_WP_ACTIVE              1
#define RTE_SDIO_WP_PORT                GPIO_PORT(0)
#define RTE_SDIO_WP_PIN                 GPIO_PIN_10

//   <h> DMA
//     <o0> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o1> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o2> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </h>
#define RTE_SDIO_DMA_NUMBER             2
#define RTE_SDIO_DMA_CHANNEL            4
#define RTE_SDIO_DMA_PRIORITY           0

// </e>


// <e> CAN1 (Controller Area Network 1) [Driver_CAN1]
// <i> Configuration settings for Driver_CAN1 in component ::CMSIS Driver:CAN
#define RTE_CAN1                        0

//   <o> CAN1_RX Pin <0=>PA11 <1=>PB8 <2=>PD0
#define RTE_CAN1_RX_PORT_ID             0
#if    (RTE_CAN1_RX_PORT_ID == 0)
#define RTE_CAN1_RX_PORT                GPIO_PORT_A
#define RTE_CAN1_RX_BIT                 GPIO_PIN_11
#elif  (RTE_CAN1_RX_PORT_ID == 1)
#define RTE_CAN1_RX_PORT                GPIO_PORT_B
#define RTE_CAN1_RX_BIT                 GPIO_PIN_8
#elif  (RTE_CAN1_RX_PORT_ID == 2)
#define RTE_CAN1_RX_PORT                GPIO_PORT_D
#define RTE_CAN1_RX_BIT                 GPIO_PIN_0
#else
#error "Invalid CAN1_RX Pin Configuration!"
#endif

//   <o> CAN1_TX Pin <0=>PA12 <1=>PB9 <2=>PD1
#define RTE_CAN1_TX_PORT_ID             0
#if    (RTE_CAN1_TX_PORT_ID == 0)
#define RTE_CAN1_TX_PORT                GPIO_PORT_A
#define RTE_CAN1_TX_BIT                 GPIO_PIN_12
#elif  (RTE_CAN1_TX_PORT_ID == 1)
#define RTE_CAN1_TX_PORT                GPIO_PORT_B
#define RTE_CAN1_TX_BIT                 GPIO_PIN_9
#elif  (RTE_CAN1_TX_PORT_ID == 2)
#define RTE_CAN1_TX_PORT                GPIO_PORT_D
#define RTE_CAN1_TX_BIT                 GPIO_PIN_1
#else
#error "Invalid CAN1_TX Pin Configuration!"
#endif

// </e>


// <e> CAN2 (Controller Area Network 2) [Driver_CAN2]
// <i> Configuration settings for Driver_CAN2 in component ::CMSIS Driver:CAN
#define RTE_CAN2                        0

//   <o> CAN2_RX Pin <0=>PB5 <1=>PB12
#define RTE_CAN2_RX_PORT_ID             0
#if    (RTE_CAN2_RX_PORT_ID == 0)
#define RTE_CAN2_RX_PORT                GPIO_PORT_B
#define RTE_CAN2_RX_BIT                 GPIO_PIN_5
#elif  (RTE_CAN2_RX_PORT_ID == 1)
#define RTE_CAN2_RX_PORT                GPIO_PORT_B
#define RTE_CAN2_RX_BIT                 GPIO_PIN_12
#else
#error "Invalid CAN2_RX Pin Configuration!"
#endif

//   <o> CAN2_TX Pin <0=>PB6 <1=>PB13
#define RTE_CAN2_TX_PORT_ID             0
#if    (RTE_CAN2_TX_PORT_ID == 0)
#define RTE_CAN2_TX_PORT                GPIO_PORT_B
#define RTE_CAN2_TX_BIT                 GPIO_PIN_6
#elif  (RTE_CAN2_TX_PORT_ID == 1)
#define RTE_CAN2_TX_PORT                GPIO_PORT_B
#define RTE_CAN2_TX_BIT                 GPIO_PIN_13
#else
#error "Invalid CAN2_TX Pin Configuration!"
#endif

// </e>


// <e> ETH (Ethernet Interface) [Driver_ETH_MAC0]
// <i> Configuration settings for Driver_ETH_MAC0 in component ::CMSIS Driver:Ethernet MAC
#define RTE_ETH                         0

//   <e> MII (Media Independent Interface)
//   <i> Enable Media Independent Interface pin configuration
#define RTE_ETH_MII                     0

//     <o> ETH_MII_TX_CLK Pin <0=>PC3
#define RTE_ETH_MII_TX_CLK_PORT_ID      0
#if    (RTE_ETH_MII_TX_CLK_PORT_ID == 0)
#define RTE_ETH_MII_TX_CLK_PORT         GPIO_PORT_C
#define RTE_ETH_MII_TX_CLK_PIN          GPIO_PIN_3
#else
#error "Invalid ETH_MII_TX_CLK Pin Configuration!"
#endif
//     <o> ETH_MII_TXD0 Pin <0=>PB12
#define RTE_ETH_MII_TXD0_PORT_ID        0
#if    (RTE_ETH_MII_TXD0_PORT_ID == 0)
#define RTE_ETH_MII_TXD0_PORT           GPIO_PORT_B
#define RTE_ETH_MII_TXD0_PIN            GPIO_PIN_12
#else
#error "Invalid ETH_MII_TXD0 Pin Configuration!"
#endif
//     <o> ETH_MII_TXD1 Pin <0=>PB13
#define RTE_ETH_MII_TXD1_PORT_ID        0
#if    (RTE_ETH_MII_TXD1_PORT_ID == 0)
#define RTE_ETH_MII_TXD1_PORT           GPIO_PORT_B
#define RTE_ETH_MII_TXD1_PIN            GPIO_PIN_13
#else
#error "Invalid ETH_MII_TXD1 Pin Configuration!"
#endif
//     <o> ETH_MII_TXD2 Pin <0=>PC2
#define RTE_ETH_MII_TXD2_PORT_ID        0
#if    (RTE_ETH_MII_TXD2_PORT_ID == 0)
#define RTE_ETH_MII_TXD2_PORT           GPIO_PORT_C
#define RTE_ETH_MII_TXD2_PIN            GPIO_PIN_2
#else
#error "Invalid ETH_MII_TXD2 Pin Configuration!"
#endif
//     <o> ETH_MII_TXD3 Pin <0=>PB8
#define RTE_ETH_MII_TXD3_PORT_ID        0
#if    (RTE_ETH_MII_TXD3_PORT_ID == 0)
#define RTE_ETH_MII_TXD3_PORT           GPIO_PORT_B
#define RTE_ETH_MII_TXD3_PIN            GPIO_PIN_8
#else
#error "Invalid ETH_MII_TXD3 Pin Configuration!"
#endif
//     <o> ETH_MII_TX_EN Pin <0=>PB11
#define RTE_ETH_MII_TX_EN_PORT_ID       0
#if    (RTE_ETH_MII_TX_EN_PORT_ID == 0)
#define RTE_ETH_MII_TX_EN_PORT          GPIO_PORT_B
#define RTE_ETH_MII_TX_EN_PIN           GPIO_PIN_11
#else
#error "Invalid ETH_MII_TX_EN Pin Configuration!"
#endif
//     <o> ETH_MII_RX_CLK Pin <0=>PA1
#define RTE_ETH_MII_RX_CLK_PORT_ID        0
#if    (RTE_ETH_MII_RX_CLK_PORT_ID == 0)
#define RTE_ETH_MII_RX_CLK_PORT         GPIO_PORT_A
#define RTE_ETH_MII_RX_CLK_PIN          GPIO_PIN_1
#else
#error "Invalid ETH_MII_RX_CLK Pin Configuration!"
#endif
//     <o> ETH_MII_RXD0 Pin <0=>PC4
#define RTE_ETH_MII_RXD0_DEF            0

//     <o> ETH_MII_RXD1 Pin <0=>PC5
#define RTE_ETH_MII_RXD1_DEF            0

//     <o> ETH_MII_RXD2 Pin <0=>PB0
#define RTE_ETH_MII_RXD2_DEF            0

//     <o> ETH_MII_RXD3 Pin <0=>PB1 <1=>PD12
#define RTE_ETH_MII_RXD3_DEF            0

//     <o> ETH_MII_RX_DV Pin <0=>PA7
#define RTE_ETH_MII_RX_DV_DEF           0

//     <o> ETH_MII_RX_ER Pin <0=>PB10
#define RTE_ETH_MII_RX_ER_PORT_ID       0
#if    (RTE_ETH_MII_RX_ER_PORT_ID == 0)
#define RTE_ETH_MII_RX_ER_PORT          GPIO_PORT_B
#define RTE_ETH_MII_RX_ER_PIN           GPIO_PIN_10
#else
#error "Invalid ETH_MII_RX_ER Pin Configuration!"
#endif
//     <o> ETH_MII_CRS Pin <0=>PA0
#define RTE_ETH_MII_CRS_PORT_ID       0
#if    (RTE_ETH_MII_CRS_PORT_ID == 0)
#define RTE_ETH_MII_CRS_PORT            GPIO_PORT_A
#define RTE_ETH_MII_CRS_PIN             GPIO_PIN_0
#else
#error "Invalid ETH_MII_CRS Pin Configuration!"
#endif
//     <o> ETH_MII_COL Pin <0=>PA3
#define RTE_ETH_MII_COL_PORT_ID       0
#if    (RTE_ETH_MII_COL_PORT_ID == 0)
#define RTE_ETH_MII_COL_PORT            GPIO_PORT_A
#define RTE_ETH_MII_COL_PIN             GPIO_PIN_3
#else
#error "Invalid ETH_MII_COL Pin Configuration!"
#endif

//     <e> Ethernet MAC I/O remapping
//     <i> Remap Ethernet pins
#define RTE_ETH_MII_REMAP               0

//     <o> ETH_MII_RXD0 Pin <1=>PD9
#define RTE_ETH_MII_RXD0_REMAP          1

//     <o> ETH_MII_RXD1 Pin <1=>PD10
#define RTE_ETH_MII_RXD1_REMAP          1

//     <o> ETH_MII_RXD2 Pin <1=>PD11
#define RTE_ETH_MII_RXD2_REMAP          1

//       <o> ETH_MII_RXD3 Pin <1=>PD12
#define RTE_ETH_MII_RXD3_REMAP          1

//       <o> ETH_MII_RX_DV Pin <1=>PD8
#define RTE_ETH_MII_RX_DV_REMAP         1
//     </e>

//   </e>

#if    ((RTE_ETH_MII_REMAP == 0) && (RTE_ETH_MII_RXD0_DEF == 0))
#define RTE_ETH_MII_RXD0_PORT           GPIO_PORT_C
#define RTE_ETH_MII_RXD0_PIN            GPIO_PIN_4
#elif  ((RTE_ETH_MII_REMAP == 1) && (RTE_ETH_MII_RXD0_REMAP == 1))
#define RTE_ETH_MII_RXD0_PORT           GPIO_PORT_D
#define RTE_ETH_MII_RXD0_PIN            GPIO_PIN_9
#else
#error "Invalid ETH_MII_RXD0 Pin Configuration!"
#endif

#if   ((RTE_ETH_MII_REMAP == 0) && (RTE_ETH_MII_RXD1_DEF == 0))
#define RTE_ETH_MII_RXD1_PORT           GPIO_PORT_C
#define RTE_ETH_MII_RXD1_PIN            GPIO_PIN_5
#elif ((RTE_ETH_MII_REMAP == 1) && (RTE_ETH_MII_RXD1_REMAP == 1))
#define RTE_ETH_MII_RXD1_PORT           GPIO_PORT_D
#define RTE_ETH_MII_RXD1_PIN            GPIO_PIN_10
#else
#error "Invalid ETH_MII_RXD1 Pin Configuration!"
#endif

#if   ((RTE_ETH_MII_REMAP == 0) && (RTE_ETH_MII_RXD2_DEF == 0))
#define RTE_ETH_MII_RXD2_PORT           GPIO_PORT_B
#define RTE_ETH_MII_RXD2_PIN            GPIO_PIN_0
#elif ((RTE_ETH_MII_REMAP == 1) && (RTE_ETH_MII_RXD2_REMAP == 1))
#define RTE_ETH_MII_RXD2_PORT           GPIO_PORT_D
#define RTE_ETH_MII_RXD2_PIN            GPIO_PIN_11
#else
#error "Invalid ETH_MII_RXD2 Pin Configuration!"
#endif

#if   ((RTE_ETH_MII_REMAP == 0) && (RTE_ETH_MII_RXD3_DEF == 0))
#define RTE_ETH_MII_RXD3_PORT           GPIO_PORT_B
#define RTE_ETH_MII_RXD3_PIN            GPIO_PIN_1
#elif ((RTE_ETH_MII_REMAP == 1) && (RTE_ETH_MII_RXD3_REMAP == 1))
#define RTE_ETH_MII_RXD3_PORT           GPIO_PORT_D
#define RTE_ETH_MII_RXD3_PIN            GPIO_PIN_12
#else
#error "Invalid ETH_MII_RXD3 Pin Configuration!"
#endif

#if   ((RTE_ETH_MII_REMAP == 0) && (RTE_ETH_MII_RX_DV_DEF == 0))
#define RTE_ETH_MII_RX_DV_PORT          GPIO_PORT_A
#define RTE_ETH_MII_RX_DV_PIN           GPIO_PIN_7
#elif ((RTE_ETH_MII_REMAP == 1) && (RTE_ETH_MII_RX_DV_REMAP == 1))
#define RTE_ETH_MII_RX_DV_PORT          GPIO_PORT_D
#define RTE_ETH_MII_RX_DV_PIN           GPIO_PIN_8
#else
#error "Invalid ETH_MII_RX_DV Pin Configuration!"
#endif

//   <e> RMII (Reduced Media Independent Interface)
#define RTE_ETH_RMII                    0

//     <o> ETH_RMII_TXD0 Pin <0=>PB12
#define RTE_ETH_RMII_TXD0_PORT_ID       0
#if    (RTE_ETH_RMII_TXD0_PORT_ID == 0)
#define RTE_ETH_RMII_TXD0_PORT          GPIO_PORT_B
#define RTE_ETH_RMII_TXD0_PIN           GPIO_PIN_12
#else
#error "Invalid ETH_RMII_TXD0 Pin Configuration!"
#endif
//     <o> ETH_RMII_TXD1 Pin <0=>PB13
#define RTE_ETH_RMII_TXD1_PORT_ID       0
#if    (RTE_ETH_RMII_TXD1_PORT_ID == 0)
#define RTE_ETH_RMII_TXD1_PORT          GPIO_PORT_B
#define RTE_ETH_RMII_TXD1_PIN           GPIO_PIN_13
#else
#error "Invalid ETH_RMII_TXD1 Pin Configuration!"
#endif
//     <o> ETH_RMII_TX_EN Pin <0=>PB11
#define RTE_ETH_RMII_TX_EN_PORT_ID      0
#if    (RTE_ETH_RMII_TX_EN_PORT_ID == 0)
#define RTE_ETH_RMII_TX_EN_PORT         GPIO_PORT_B
#define RTE_ETH_RMII_TX_EN_PIN          GPIO_PIN_11
#else
#error "Invalid ETH_RMII_TX_EN Pin Configuration!"
#endif
//     <o> ETH_RMII_RXD0 Pin <0=>PC4
#define RTE_ETH_RMII_RXD0_DEF           0

//     <o> ETH_RMII_RXD1 Pin <0=>PC5
#define RTE_ETH_RMII_RXD1_DEF           0

//     <o> ETH_RMII_REF_CLK Pin <0=>PA1
#define RTE_ETH_RMII_REF_CLK_PORT_ID    0
#if    (RTE_ETH_RMII_REF_CLK_PORT_ID == 0)
#define RTE_ETH_RMII_REF_CLK_PORT       GPIO_PORT_A
#define RTE_ETH_RMII_REF_CLK_PIN        GPIO_PIN_1
#else
#error "Invalid ETH_RMII_REF_CLK Pin Configuration!"
#endif
//     <o> ETH_RMII_CRS_DV Pin <0=>PA7
#define RTE_ETH_RMII_CRS_DV_DEF     0

//   <e> Ethernet MAC I/O remapping
//   <i> Remap Ethernet pins
#define RTE_ETH_RMII_REMAP              0
//     <o> ETH_RMII_RXD0 Pin <1=>PD9
#define RTE_ETH_RMII_RXD0_REMAP         1

//     <o> ETH_RMII_RXD1 Pin <1=>PD10
#define RTE_ETH_RMII_RXD1_REMAP         1

//     <o> ETH_RMII_CRS_DV Pin <1=>PD8
#define RTE_ETH_RMII_CRS_DV_REMAP       1
//   </e>

#if    ((RTE_ETH_RMII_REMAP == 0) && (RTE_ETH_RMII_RXD0_DEF == 0))
#define RTE_ETH_RMII_RXD0_PORT          GPIO_PORT_C
#define RTE_ETH_RMII_RXD0_PIN           GPIO_PIN_4
#elif  ((RTE_ETH_RMII_REMAP == 1) && (RTE_ETH_RMII_RXD0_REMAP == 1))
#define RTE_ETH_RMII_RXD0_PORT          GPIO_PORT_D
#define RTE_ETH_RMII_RXD0_PIN           GPIO_PIN_9
#else
#error "Invalid ETH_RMII_RXD0 Pin Configuration!"
#endif

#if    ((RTE_ETH_RMII_REMAP == 0) && (RTE_ETH_RMII_RXD1_DEF == 0))
#define RTE_ETH_RMII_RXD1_PORT          GPIO_PORT_C
#define RTE_ETH_RMII_RXD1_PIN           GPIO_PIN_5
#elif  ((RTE_ETH_RMII_REMAP == 1) && (RTE_ETH_RMII_RXD1_REMAP == 1))
#define RTE_ETH_RMII_RXD1_PORT          GPIO_PORT_D
#define RTE_ETH_RMII_RXD1_PIN           GPIO_PIN_10
#else
#error "Invalid ETH_RMII_RXD1 Pin Configuration!"
#endif

#if    ((RTE_ETH_RMII_REMAP == 0) && (RTE_ETH_RMII_CRS_DV_DEF == 0))
#define RTE_ETH_RMII_CRS_DV_PORT        GPIO_PORT_A
#define RTE_ETH_RMII_CRS_DV_PIN         GPIO_PIN_7
#elif  ((RTE_ETH_RMII_REMAP == 1) && (RTE_ETH_RMII_CRS_DV_REMAP == 1))
#define RTE_ETH_RMII_CRS_DV_PORT        GPIO_PORT_D
#define RTE_ETH_RMII_CRS_DV_PIN         GPIO_PIN_8
#else
#error "Invalid ETH_RMII_CRS_DV Pin Configuration!"
#endif

//   </e>

//   <h> Management Data Interface
//     <o> ETH_MDC Pin <0=>PC1
#define RTE_ETH_MDI_MDC_PORT_ID         0
#if    (RTE_ETH_MDI_MDC_PORT_ID == 0)
#define RTE_ETH_MDI_MDC_PORT            GPIO_PORT_C
#define RTE_ETH_MDI_MDC_PIN             GPIO_PIN_1
#else
#error "Invalid ETH_MDC Pin Configuration!"
#endif
//     <o> ETH_MDIO Pin <0=>PA2
#define RTE_ETH_MDI_MDIO_PORT_ID        0
#if    (RTE_ETH_MDI_MDIO_PORT_ID == 0)
#define RTE_ETH_MDI_MDIO_PORT           GPIO_PORT_A
#define RTE_ETH_MDI_MDIO_PIN            GPIO_PIN_2
#else
#error "Invalid ETH_MDIO Pin Configuration!"
#endif
//   </h>

//   <o> Reference 25MHz Clock generation on MCO pin <0=>Disabled <1=>Enabled
#define RTE_ETH_REF_CLOCK_ID            0
#if    (RTE_ETH_REF_CLOCK_ID == 0)
#define RTE_ETH_REF_CLOCK               0
#elif  (RTE_ETH_REF_CLOCK_ID == 1)
#define RTE_ETH_REF_CLOCK               1
#else
#error "Invalid MCO Ethernet Reference Clock Configuration!"
#endif
// </e>

#endif  /* __RTE_DEVICE_H */

/* ----------------------------- End of file ---------------------------------*/
