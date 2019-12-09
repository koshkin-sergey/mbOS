/*
 * Copyright (C) 2018-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for STMicroelectronics STM32F4xx
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#if !defined(RTE_HSI)
  #define RTE_HSI         ((uint32_t)16000000)  /* Default value of the Internal oscillator in Hz */
#endif  // RTE_HSI
#if !defined(RTE_HSE)
  #define RTE_HSE         ((uint32_t)8000000)   /* Default value of the External oscillator in Hz */
#endif  // RTE_HSE

/* Interrupt Priority */
#define RTE_I2C_INT_PRIORITY            (1U)
#define RTE_I2C_DMA_INT_PRIORITY        (1U)
#define RTE_I2S_INT_PRIORITY            (1U)
#define RTE_I2S_DMA_INT_PRIORITY        (1U)
#define RTE_USART_INT_PRIORITY          (1U)
#define RTE_USART_DMA_INT_PRIORITY      (1U)
#define RTE_SPI_INT_PRIORITY            (1U)
#define RTE_SPI_DMA_INT_PRIORITY        (1U)
#define RTE_EXTI_INT_PRIORITY           (1U)

// <e> USART1 (Universal synchronous asynchronous receiver transmitter) [Driver_USART1]
// <i> Configuration settings for Driver_USART1 in component ::CMSIS Driver:USART
#define RTE_USART1                      0

//   <o> USART1_TX Pin <0=>Not Used <1=>PA9 <2=>PA15 <3=>PB6
#define   RTE_USART1_TX_ID              1
#if      (RTE_USART1_TX_ID == 0)
  #define RTE_USART1_TX                 0
#elif    (RTE_USART1_TX_ID == 1)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_A
  #define RTE_USART1_TX_PIN             GPIO_PIN_9
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART1_TX_ID == 2)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_A
  #define RTE_USART1_TX_PIN             GPIO_PIN_15
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART1_TX_ID == 3)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_B
  #define RTE_USART1_TX_PIN             GPIO_PIN_6
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_TX Pin Configuration!"
#endif

//   <o> USART1_RX Pin <0=>Not Used <1=>PA10 <2=>PB3 <3=>PB7
#define   RTE_USART1_RX_ID              1
#if      (RTE_USART1_RX_ID == 0)
  #define RTE_USART1_RX                 0
#elif    (RTE_USART1_RX_ID == 1)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_A
  #define RTE_USART1_RX_PIN             GPIO_PIN_10
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART1_RX_ID == 2)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_B
  #define RTE_USART1_RX_PIN             GPIO_PIN_3
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART1_RX_ID == 3)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_B
  #define RTE_USART1_RX_PIN             GPIO_PIN_7
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_RX Pin Configuration!"
#endif

//   <o> USART1_CK Pin <0=>Not Used <1=>PA8
#define   RTE_USART1_CK_ID              1
#if      (RTE_USART1_CK_ID == 0)
  #define RTE_USART1_CK                 0
#elif    (RTE_USART1_CK_ID == 1)
  #define RTE_USART1_CK                 1
  #define RTE_USART1_CK_PORT            GPIO_PORT_A
  #define RTE_USART1_CK_PIN             GPIO_PIN_8
  #define RTE_USART1_CK_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_CK Pin Configuration!"
#endif

//   <o> USART1_CTS Pin <0=>Not Used <1=>PA11
#define   RTE_USART1_CTS_ID             1
#if      (RTE_USART1_CTS_ID == 0)
  #define RTE_USART1_CTS                0
#elif    (RTE_USART1_CTS_ID == 1)
  #define RTE_USART1_CTS                1
  #define RTE_USART1_CTS_PORT           GPIO_PORT_A
  #define RTE_USART1_CTS_PIN            GPIO_PIN_11
  #define RTE_USART1_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_CTS Pin Configuration!"
#endif

//   <o> USART1_RTS Pin <0=>Not Used <1=>PA12
#define   RTE_USART1_RTS_ID             1
#if      (RTE_USART1_RTS_ID == 0)
  #define RTE_USART1_RTS                0
#elif    (RTE_USART1_RTS_ID == 1)
  #define RTE_USART1_RTS                1
  #define RTE_USART1_RTS_PORT           GPIO_PORT_A
  #define RTE_USART1_RTS_PIN            GPIO_PIN_12
  #define RTE_USART1_RTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <2=>2 <5=>5
//     <i>  Selects DMA Stream (only Stream 2 or 5 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART1_RX_DMA               0
#define RTE_USART1_RX_DMA_NUMBER        2
#define RTE_USART1_RX_DMA_STREAM        2
#define RTE_USART1_RX_DMA_CHANNEL       4
#define RTE_USART1_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART1_TX_DMA               0
#define RTE_USART1_TX_DMA_NUMBER        2
#define RTE_USART1_TX_DMA_STREAM        7
#define RTE_USART1_TX_DMA_CHANNEL       4
#define RTE_USART1_TX_DMA_PRIORITY      0

// </e> USART1 (Universal synchronous asynchronous receiver transmitter) [Driver_USART1]

// <e> USART2 (Universal synchronous asynchronous receiver transmitter) [Driver_USART2]
// <i> Configuration settings for Driver_USART2 in component ::CMSIS Driver:USART
#define RTE_USART2                      1

//   <o> USART2_TX Pin <0=>Not Used <1=>PA2 <2=>PD5
#define   RTE_USART2_TX_ID              1
#if      (RTE_USART2_TX_ID == 0)
  #define RTE_USART2_TX                 0
#elif    (RTE_USART2_TX_ID == 1)
  #define RTE_USART2_TX                 1
  #define RTE_USART2_TX_PORT            GPIO_PORT_A
  #define RTE_USART2_TX_PIN             GPIO_PIN_2
  #define RTE_USART2_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART2_TX_ID == 2)
  #define RTE_USART2_TX                 1
  #define RTE_USART2_TX_PORT            GPIO_PORT_D
  #define RTE_USART2_TX_PIN             GPIO_PIN_5
  #define RTE_USART2_TX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_TX Pin Configuration!"
#endif

//   <o> USART2_RX Pin <0=>Not Used <1=>PA3 <2=>PD6
#define   RTE_USART2_RX_ID              1
#if      (RTE_USART2_RX_ID == 0)
  #define RTE_USART2_RX                 0
#elif    (RTE_USART2_RX_ID == 1)
  #define RTE_USART2_RX                 1
  #define RTE_USART2_RX_PORT            GPIO_PORT_A
  #define RTE_USART2_RX_PIN             GPIO_PIN_3
  #define RTE_USART2_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART2_RX_ID == 2)
  #define RTE_USART2_RX                 1
  #define RTE_USART2_RX_PORT            GPIO_PORT_D
  #define RTE_USART2_RX_PIN             GPIO_PIN_6
  #define RTE_USART2_RX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_RX Pin Configuration!"
#endif

//   <o> USART2_CK Pin <0=>Not Used <1=>PA4 <2=>PD7
#define   RTE_USART2_CK_ID              0
#if      (RTE_USART2_CK_ID == 0)
  #define RTE_USART2_CK                 0
#elif    (RTE_USART2_CK_ID == 1)
  #define RTE_USART2_CK                 1
  #define RTE_USART2_CK_PORT            GPIO_PORT_A
  #define RTE_USART2_CK_PIN             GPIO_PIN_4
  #define RTE_USART2_CK_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART2_CK_ID == 2)
  #define RTE_USART2_CK                 1
  #define RTE_USART2_CK_PORT            GPIO_PORT_D
  #define RTE_USART2_CK_PIN             GPIO_PIN_7
  #define RTE_USART2_CK_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_CK Pin Configuration!"
#endif

//   <o> USART2_CTS Pin <0=>Not Used <1=>PA0 <2=>PD3
#define   RTE_USART2_CTS_ID             0
#if      (RTE_USART2_CTS_ID == 0)
  #define RTE_USART2_CTS                0
#elif    (RTE_USART2_CTS_ID == 1)
  #define RTE_USART2_CTS                1
  #define RTE_USART2_CTS_PORT           GPIO_PORT_A
  #define RTE_USART2_CTS_PIN            GPIO_PIN_0
  #define RTE_USART2_CTS_FUNC           GPIO_PIN_FUNC_7
#elif    (RTE_USART2_CTS_ID == 2)
  #define RTE_USART2_CTS                1
  #define RTE_USART2_CTS_PORT           GPIO_PORT_D
  #define RTE_USART2_CTS_PIN            GPIO_PIN_3
  #define RTE_USART2_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_CTS Pin Configuration!"
#endif

//   <o> USART2_RTS Pin <0=>Not Used <1=>PA1 <2=>PD4
#define   RTE_USART2_RTS_ID             0
#if      (RTE_USART2_RTS_ID == 0)
  #define RTE_USART2_RTS                0
#elif    (RTE_USART2_RTS_ID == 1)
  #define RTE_USART2_RTS                1
  #define RTE_USART2_RTS_PORT           GPIO_PORT_A
  #define RTE_USART2_RTS_PIN            GPIO_PIN_1
  #define RTE_USART2_RTS_FUNC           GPIO_PIN_FUNC_7
#elif    (RTE_USART2_RTS_ID == 2)
  #define RTE_USART2_RTS                1
  #define RTE_USART2_RTS_PORT           GPIO_PORT_D
  #define RTE_USART2_RTS_PIN            GPIO_PIN_4
  #define RTE_USART2_RTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <5=>5 <7=>7
//     <i>  Selects DMA Stream (only Stream 5 or 7 can be used)
//     <o3> Channel <4=>4 <6=>6
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART2_RX_DMA               0
#define RTE_USART2_RX_DMA_NUMBER        1
#define RTE_USART2_RX_DMA_STREAM        5
#define RTE_USART2_RX_DMA_CHANNEL       4
#define RTE_USART2_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <6=>6
//     <i>  Selects DMA Stream (only Stream 6 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART2_TX_DMA               0
#define RTE_USART2_TX_DMA_NUMBER        1
#define RTE_USART2_TX_DMA_STREAM        6
#define RTE_USART2_TX_DMA_CHANNEL       4
#define RTE_USART2_TX_DMA_PRIORITY      0

// </e> USART2 (Universal synchronous asynchronous receiver transmitter) [Driver_USART2]

// <e> USART3 (Universal synchronous asynchronous receiver transmitter) [Driver_USART3]
// <i> Configuration settings for Driver_USART3 in component ::CMSIS Driver:USART
#define RTE_USART3                      0

//   <o> USART3_TX Pin <0=>Not Used <1=>PB10 <2=>PC10 <3=>PD8
#define   RTE_USART3_TX_ID              0
#if      (RTE_USART3_TX_ID == 0)
  #define RTE_USART3_TX                 0
#elif    (RTE_USART3_TX_ID == 1)
  #define RTE_USART3_TX                 1
  #define RTE_USART3_TX_PORT            GPIO_PORT_B
  #define RTE_USART3_TX_PIN             GPIO_PIN_10
  #define RTE_USART3_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART3_TX_ID == 2)
  #define RTE_USART3_TX                 1
  #define RTE_USART3_TX_PORT            GPIO_PORT_C
  #define RTE_USART3_TX_PIN             GPIO_PIN_10
  #define RTE_USART3_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART3_TX_ID == 3)
  #define RTE_USART3_TX                 1
  #define RTE_USART3_TX_PORT            GPIO_PORT_D
  #define RTE_USART3_TX_PIN             GPIO_PIN_8
  #define RTE_USART3_TX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_TX Pin Configuration!"
#endif

//   <o> USART3_RX Pin <0=>Not Used <1=>PB11 <2=>PC11 <3=>PD9 <4=>PC5
#define   RTE_USART3_RX_ID              0
#if      (RTE_USART3_RX_ID == 0)
  #define RTE_USART3_RX                 0
#elif    (RTE_USART3_RX_ID == 1)
  #define RTE_USART3_RX                 1
  #define RTE_USART3_RX_PORT            GPIO_PORT_B
  #define RTE_USART3_RX_PIN             GPIO_PIN_11
  #define RTE_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART3_RX_ID == 2)
  #define RTE_USART3_RX                 1
  #define RTE_USART3_RX_PORT            GPIO_PORT_C
  #define RTE_USART3_RX_PIN             GPIO_PIN_11
  #define RTE_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART3_RX_ID == 3)
  #define RTE_USART3_RX                 1
  #define RTE_USART3_RX_PORT            GPIO_PORT_D
  #define RTE_USART3_RX_PIN             GPIO_PIN_9
  #define RTE_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART3_RX_ID == 4)
  #define RTE_USART3_RX                 1
  #define RTE_USART3_RX_PORT            GPIO_PORT_C
  #define RTE_USART3_RX_PIN             GPIO_PIN_5
  #define RTE_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_RX Pin Configuration!"
#endif

//   <o> USART3_CK Pin <0=>Not Used <1=>PB12 <2=>PC12 <3=>PD10
#define   RTE_USART3_CK_ID              0
#if      (RTE_USART3_CK_ID == 0)
  #define RTE_USART3_CK                 0
#elif    (RTE_USART3_CK_ID == 1)
  #define RTE_USART3_CK                 1
  #define RTE_USART3_CK_PORT            GPIO_PORT_B
  #define RTE_USART3_CK_PIN             GPIO_PIN_12
  #if defined (STM32F413xx) || defined (STM32F423xx)
    #define RTE_USART3_CK_FUNC          GPIO_PIN_FUNC_8
  #else
    #define RTE_USART3_CK_FUNC          GPIO_PIN_FUNC_7
  #endif
#elif    (RTE_USART3_CK_ID == 2)
  #define RTE_USART3_CK                 1
  #define RTE_USART3_CK_PORT            GPIO_PORT_C
  #define RTE_USART3_CK_PIN             GPIO_PIN_12
  #define RTE_USART3_CK_FUNC            GPIO_PIN_FUNC_7
#elif    (RTE_USART3_CK_ID == 3)
  #define RTE_USART3_CK                 1
  #define RTE_USART3_CK_PORT            GPIO_PORT_D
  #define RTE_USART3_CK_PIN             GPIO_PIN_10
  #define RTE_USART3_CK_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_CK Pin Configuration!"
#endif

//   <o> USART3_CTS Pin <0=>Not Used <1=>PB13 <2=>PD11
#define   RTE_USART3_CTS_ID             0
#if      (RTE_USART3_CTS_ID == 0)
  #define RTE_USART3_CTS                0
#elif    (RTE_USART3_CTS_ID == 1)
  #define RTE_USART3_CTS                1
  #define RTE_USART3_CTS_PORT           GPIO_PORT_B
  #define RTE_USART3_CTS_PIN            GPIO_PIN_13
  #if defined (STM32F413xx) || defined (STM32F423xx)
    #define RTE_USART3_CTS_FUNC         GPIO_PIN_FUNC_8
  #else
    #define RTE_USART3_CTS_FUNC         GPIO_PIN_FUNC_7
  #endif
#elif    (RTE_USART3_CTS_ID == 2)
  #define RTE_USART3_CTS                1
  #define RTE_USART3_CTS_PORT           GPIO_PORT_D
  #define RTE_USART3_CTS_PIN            GPIO_PIN_11
  #define RTE_USART3_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_CTS Pin Configuration!"
#endif

//   <o> USART3_RTS Pin <0=>Not Used <1=>PB14 <2=>PD12
#define   RTE_USART3_RTS_ID             0
#if      (RTE_USART3_RTS_ID == 0)
  #define RTE_USART3_RTS                0
#elif    (RTE_USART3_RTS_ID == 1)
  #define RTE_USART3_RTS                1
  #define RTE_USART3_RTS_PORT           GPIO_PORT_B
  #define RTE_USART3_RTS_PIN            GPIO_PIN_14
  #define RTE_USART3_RTS_FUNC           GPIO_PIN_FUNC_7
#elif    (RTE_USART3_RTS_ID == 2)
  #define RTE_USART3_RTS                1
  #define RTE_USART3_RTS_PORT           GPIO_PORT_D
  #define RTE_USART3_RTS_PIN            GPIO_PIN_12
  #define RTE_USART3_RTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1 <4=>4
//     <i>  Selects DMA Stream (only Stream 1 or 4 can be used)
//     <o3> Channel <4=>4 <7=>7
//     <i>  Selects DMA Channel (only Channel 4 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART3_RX_DMA               0
#define RTE_USART3_RX_DMA_NUMBER        1
#define RTE_USART3_RX_DMA_STREAM        1
#define RTE_USART3_RX_DMA_CHANNEL       4
#define RTE_USART3_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3 <4=>4
//     <i>  Selects DMA Stream (only Stream 3 or 4 can be used)
//     <o3> Channel <4=>4 <7=>7
//     <i>  Selects DMA Channel (only Channel 4 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART3_TX_DMA               0
#define RTE_USART3_TX_DMA_NUMBER        1
#define RTE_USART3_TX_DMA_STREAM        3
#define RTE_USART3_TX_DMA_CHANNEL       4
#define RTE_USART3_TX_DMA_PRIORITY      0

// </e> USART3 (Universal synchronous asynchronous receiver transmitter) [Driver_USART3]

// <e> UART4 (Universal asynchronous receiver transmitter) [Driver_USART4]
// <i> Configuration settings for Driver_USART4 in component ::CMSIS Driver:USART
#define RTE_UART4                       0

//   <o> UART4_TX Pin <0=>Not Used <1=>PA0 <2=>PC10 <3=>PD10 <4=>PA12 <5=>PD1
#define   RTE_UART4_TX_ID               0
#if      (RTE_UART4_TX_ID == 0)
  #define RTE_UART4_TX                  0
#elif    (RTE_UART4_TX_ID == 1)
  #define RTE_UART4_TX                  1
  #define RTE_UART4_TX_PORT             GPIO_PORT_A
  #define RTE_UART4_TX_PIN              GPIO_PIN_0
  #define RTE_UART4_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART4_TX_ID == 2)
  #define RTE_UART4_TX                  1
  #define RTE_UART4_TX_PORT             GPIO_PORT_C
  #define RTE_UART4_TX_PIN              GPIO_PIN_10
  #define RTE_UART4_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART4_TX_ID == 3)
  #define RTE_UART4_TX                  1
  #define RTE_UART4_TX_PORT             GPIO_PORT_D
  #define RTE_UART4_TX_PIN              GPIO_PIN_10
  #define RTE_UART4_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART4_TX_ID == 4)
  #define RTE_UART4_TX                  1
  #define RTE_UART4_TX_PORT             GPIO_PORT_A
  #define RTE_UART4_TX_PIN              GPIO_PIN_12
  #define RTE_UART4_TX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART4_TX_ID == 5)
  #define RTE_UART4_TX                  1
  #define RTE_UART4_TX_PORT             GPIO_PORT_D
  #define RTE_UART4_TX_PIN              GPIO_PIN_1
  #define RTE_UART4_TX_FUNC             GPIO_PIN_FUNC_11
#else
  #error "Invalid UART4_TX Pin Configuration!"
#endif

//   <o> UART4_RX Pin <0=>Not Used <1=>PA1 <2=>PC11 <3=>PA11 <4=>PD0
#define   RTE_UART4_RX_ID               0
#if      (RTE_UART4_RX_ID == 0)
  #define RTE_UART4_RX                  0
#elif    (RTE_UART4_RX_ID == 1)
  #define RTE_UART4_RX                  1
  #define RTE_UART4_RX_PORT             GPIO_PORT_A
  #define RTE_UART4_RX_PIN              GPIO_PIN_1
  #define RTE_UART4_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART4_RX_ID == 2)
  #define RTE_UART4_RX                  1
  #define RTE_UART4_RX_PORT             GPIO_PORT_C
  #define RTE_UART4_RX_PIN              GPIO_PIN_11
  #define RTE_UART4_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART4_RX_ID == 3)
  #define RTE_UART4_RX                  1
  #define RTE_UART4_RX_PORT             GPIO_PORT_A
  #define RTE_UART4_RX_PIN              GPIO_PIN_11
  #define RTE_UART4_RX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART4_RX_ID == 4)
  #define RTE_UART4_RX                  1
  #define RTE_UART4_RX_PORT             GPIO_PORT_D
  #define RTE_UART4_RX_PIN              GPIO_PIN_0
  #define RTE_UART4_RX_FUNC             GPIO_PIN_FUNC_11
#else
  #error "Invalid UART4_RX Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <2=>2
//     <i>  Selects DMA Stream (only Stream 2 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART4_RX_DMA                0
#define RTE_UART4_RX_DMA_NUMBER         1
#define RTE_UART4_RX_DMA_STREAM         2
#define RTE_UART4_RX_DMA_CHANNEL        4
#define RTE_UART4_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <4=>4
//     <i>  Selects DMA Stream (only Stream 4 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART4_TX_DMA                0
#define RTE_UART4_TX_DMA_NUMBER         1
#define RTE_UART4_TX_DMA_STREAM         4
#define RTE_UART4_TX_DMA_CHANNEL        4
#define RTE_UART4_TX_DMA_PRIORITY       0

// </e> UART4 (Universal asynchronous receiver transmitter) [Driver_USART4]

// <e> UART5 (Universal asynchronous receiver transmitter) [Driver_USART5]
// <i> Configuration settings for Driver_USART5 in component ::CMSIS Driver:USART
#define RTE_UART5                       0

//   <o> UART5_TX Pin <0=>Not Used <1=>PC12 <2=>PB6 <3=>PB9 <4=>PB13
#define   RTE_UART5_TX_ID               0
#if      (RTE_UART5_TX_ID == 0)
  #define RTE_UART5_TX                  0
#elif    (RTE_UART5_TX_ID == 1)
  #define RTE_UART5_TX                  1
  #define RTE_UART5_TX_PORT             GPIO_PORT_C
  #define RTE_UART5_TX_PIN              GPIO_PIN_12
  #define RTE_UART5_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART5_TX_ID == 2)
  #define RTE_UART5_TX                  1
  #define RTE_UART5_TX_PORT             GPIO_PORT_B
  #define RTE_UART5_TX_PIN              GPIO_PIN_6
  #define RTE_UART5_TX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART5_TX_ID == 3)
  #define RTE_UART5_TX                  1
  #define RTE_UART5_TX_PORT             GPIO_PORT_B
  #define RTE_UART5_TX_PIN              GPIO_PIN_9
  #define RTE_UART5_TX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART5_TX_ID == 4)
  #define RTE_UART5_TX                  1
  #define RTE_UART5_TX_PORT             GPIO_PORT_B
  #define RTE_UART5_TX_PIN              GPIO_PIN_13
  #define RTE_UART5_TX_FUNC             GPIO_PIN_FUNC_11
#else
  #error "Invalid UART5_TX Pin Configuration!"
#endif

//   <o> UART5_RX Pin <0=>Not Used <1=>PD2 <2=>PB5 <3=>PB8 <4=>PB12
#define   RTE_UART5_RX_ID               0
#if      (RTE_UART5_RX_ID == 0)
  #define RTE_UART5_RX                  0
#elif    (RTE_UART5_RX_ID == 1)
  #define RTE_UART5_RX                  1
  #define RTE_UART5_RX_PORT             GPIO_PORT_D
  #define RTE_UART5_RX_PIN              GPIO_PIN_2
  #define RTE_UART5_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART5_RX_ID == 2)
  #define RTE_UART5_RX                  1
  #define RTE_UART5_RX_PORT             GPIO_PORT_B
  #define RTE_UART5_RX_PIN              GPIO_PIN_5
  #define RTE_UART5_RX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART5_RX_ID == 3)
  #define RTE_UART5_RX                  1
  #define RTE_UART5_RX_PORT             GPIO_PORT_B
  #define RTE_UART5_RX_PIN              GPIO_PIN_8
  #define RTE_UART5_RX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART5_RX_ID == 4)
  #define RTE_UART5_RX                  1
  #define RTE_UART5_RX_PORT             GPIO_PORT_B
  #define RTE_UART5_RX_PIN              GPIO_PIN_12
  #define RTE_UART5_RX_FUNC             GPIO_PIN_FUNC_11
#else
  #error "Invalid UART5_RX Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0
//     <i>  Selects DMA Stream (only Stream 0 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART5_RX_DMA                0
#define RTE_UART5_RX_DMA_NUMBER         1
#define RTE_UART5_RX_DMA_STREAM         0
#define RTE_UART5_RX_DMA_CHANNEL        4
#define RTE_UART5_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <4=>4 <8=>8
//     <i>  Selects DMA Channel (only Channel 4 or 8 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART5_TX_DMA                0
#define RTE_UART5_TX_DMA_NUMBER         1
#define RTE_UART5_TX_DMA_STREAM         7
#define RTE_UART5_TX_DMA_CHANNEL        4
#define RTE_UART5_TX_DMA_PRIORITY       0

// </e> UART5 (Universal asynchronous receiver transmitter) [Driver_USART5]

// <e> USART6 (Universal synchronous asynchronous receiver transmitter) [Driver_USART6]
// <i> Configuration settings for Driver_USART6 in component ::CMSIS Driver:USART
#define RTE_USART6                      0

//   <o> USART6_TX Pin <0=>Not Used <1=>PA11 <2=>PC6 <3=>PG14
#define   RTE_USART6_TX_ID              0
#if      (RTE_USART6_TX_ID == 0)
  #define RTE_USART6_TX                 0
#elif    (RTE_USART6_TX_ID == 1)
  #define RTE_USART6_TX                 1
  #define RTE_USART6_TX_PORT            GPIO_PORT_A
  #define RTE_USART6_TX_PIN             GPIO_PIN_11
  #define RTE_USART6_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (RTE_USART6_TX_ID == 2)
  #define RTE_USART6_TX                 1
  #define RTE_USART6_TX_PORT            GPIO_PORT_C
  #define RTE_USART6_TX_PIN             GPIO_PIN_6
  #define RTE_USART6_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (RTE_USART6_TX_ID == 3)
  #define RTE_USART6_TX                 1
  #define RTE_USART6_TX_PORT            GPIO_PORT_G
  #define RTE_USART6_TX_PIN             GPIO_PIN_14
  #define RTE_USART6_TX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_TX Pin Configuration!"
#endif

//   <o> USART6_RX Pin <0=>Not Used <1=>PA12 <2=>PC7 <3=>PG9
#define   RTE_USART6_RX_ID              0
#if      (RTE_USART6_RX_ID == 0)
  #define RTE_USART6_RX                 0
#elif    (RTE_USART6_RX_ID == 1)
  #define RTE_USART6_RX                 1
  #define RTE_USART6_RX_PORT            GPIO_PORT_A
  #define RTE_USART6_RX_PIN             GPIO_PIN_12
  #define RTE_USART6_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (RTE_USART6_RX_ID == 2)
  #define RTE_USART6_RX                 1
  #define RTE_USART6_RX_PORT            GPIO_PORT_C
  #define RTE_USART6_RX_PIN             GPIO_PIN_7
  #define RTE_USART6_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (RTE_USART6_RX_ID == 3)
  #define RTE_USART6_RX                 1
  #define RTE_USART6_RX_PORT            GPIO_PORT_G
  #define RTE_USART6_RX_PIN             GPIO_PIN_9
  #define RTE_USART6_RX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_RX Pin Configuration!"
#endif

//   <o> USART6_CK Pin <0=>Not Used <1=>PC8 <2=>PG7
#define   RTE_USART6_CK_ID              0
#if      (RTE_USART6_CK_ID == 0)
  #define RTE_USART6_CK                 0
#elif    (RTE_USART6_CK_ID == 1)
  #define RTE_USART6_CK                 1
  #define RTE_USART6_CK_PORT            GPIO_PORT_C
  #define RTE_USART6_CK_PIN             GPIO_PIN_8
  #define RTE_USART6_CK_FUNC            GPIO_PIN_FUNC_8
#elif    (RTE_USART6_CK_ID == 2)
  #define RTE_USART6_CK                 1
  #define RTE_USART6_CK_PORT            GPIO_PORT_G
  #define RTE_USART6_CK_PIN             GPIO_PIN_7
  #define RTE_USART6_CK_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_CK Pin Configuration!"
#endif

//   <o> USART6_CTS Pin <0=>Not Used <1=>PG13 <2=>PG15
#define   RTE_USART6_CTS_ID             0
#if      (RTE_USART6_CTS_ID == 0)
  #define RTE_USART6_CTS                0
#elif    (RTE_USART6_CTS_ID == 1)
  #define RTE_USART6_CTS                1
  #define RTE_USART6_CTS_PORT           GPIO_PORT_G
  #define RTE_USART6_CTS_PIN            GPIO_PIN_13
  #define RTE_USART6_CTS_FUNC           GPIO_PIN_FUNC_8
#elif    (RTE_USART6_CTS_ID == 2)
  #define RTE_USART6_CTS                1
  #define RTE_USART6_CTS_PORT           GPIO_PORT_G
  #define RTE_USART6_CTS_PIN            GPIO_PIN_15
  #define RTE_USART6_CTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_CTS Pin Configuration!"
#endif

//   <o> USART6_RTS Pin <0=>Not Used <1=>PG8 <2=>PG12
#define   RTE_USART6_RTS_ID             0
#if      (RTE_USART6_RTS_ID == 0)
  #define RTE_USART6_RTS                0
#elif    (RTE_USART6_RTS_ID == 1)
  #define RTE_USART6_RTS                1
  #define RTE_USART6_RTS_PORT           GPIO_PORT_G
  #define RTE_USART6_RTS_PIN            GPIO_PIN_8
  #define RTE_USART6_RTS_FUNC           GPIO_PIN_FUNC_8
#elif    (RTE_USART6_RTS_ID == 2)
  #define RTE_USART6_RTS                1
  #define RTE_USART6_RTS_PORT           GPIO_PORT_G
  #define RTE_USART6_RTS_PIN            GPIO_PIN_12
  #define RTE_USART6_RTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <1=>1 <2=>2
//     <i>  Selects DMA Stream (only Stream 1 or 2 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART6_RX_DMA               0
#define RTE_USART6_RX_DMA_NUMBER        2
#define RTE_USART6_RX_DMA_STREAM        1
#define RTE_USART6_RX_DMA_CHANNEL       5
#define RTE_USART6_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <6=>6 <7=>7
//     <i>  Selects DMA Stream (only Stream 6 or 7 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_USART6_TX_DMA               0
#define RTE_USART6_TX_DMA_NUMBER        2
#define RTE_USART6_TX_DMA_STREAM        6
#define RTE_USART6_TX_DMA_CHANNEL       5
#define RTE_USART6_TX_DMA_PRIORITY      0

// </e> USART6 (Universal synchronous asynchronous receiver transmitter) [Driver_USART6]

// <e> UART7 (Universal asynchronous receiver transmitter) [Driver_USART7]
// <i> Configuration settings for Driver_USART7 in component ::CMSIS Driver:USART
#define RTE_UART7                       0

//   <o> UART7_TX Pin <0=>Not Used <1=>PF7 <2=>PE8 <3=>PA15 <4=>PB4
#define   RTE_UART7_TX_ID               0
#if      (RTE_UART7_TX_ID == 0)
  #define RTE_UART7_TX                  0
#elif    (RTE_UART7_TX_ID == 1)
  #define RTE_UART7_TX                  1
  #define RTE_UART7_TX_PORT             GPIO_PORT_F
  #define RTE_UART7_TX_PIN              GPIO_PIN_7
  #define RTE_UART7_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART7_TX_ID == 2)
  #define RTE_UART7_TX                  1
  #define RTE_UART7_TX_PORT             GPIO_PORT_E
  #define RTE_UART7_TX_PIN              GPIO_PIN_8
  #define RTE_UART7_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART7_TX_ID == 3)
  #define RTE_UART7_TX                  1
  #define RTE_UART7_TX_PORT             GPIO_PORT_A
  #define RTE_UART7_TX_PIN              GPIO_PIN_15
  #define RTE_UART7_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART7_TX_ID == 4)
  #define RTE_UART7_TX                  1
  #define RTE_UART7_TX_PORT             GPIO_PORT_B
  #define RTE_UART7_TX_PIN              GPIO_PIN_4
  #define RTE_UART7_TX_FUNC             GPIO_PIN_FUNC_8
#else
  #error "Invalid UART7_TX Pin Configuration!"
#endif

//   <o> UART7_RX Pin <0=>Not Used <1=>PF6 <2=>PE7 <3=>PA8 <4=>PB3
#define   RTE_UART7_RX_ID               0
#if      (RTE_UART7_RX_ID == 0)
  #define RTE_UART7_RX                  0
#elif    (RTE_UART7_RX_ID == 1)
  #define RTE_UART7_RX                  1
  #define RTE_UART7_RX_PORT             GPIO_PORT_F
  #define RTE_UART7_RX_PIN              GPIO_PIN_6
  #define RTE_UART7_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART7_RX_ID == 2)
  #define RTE_UART7_RX                  1
  #define RTE_UART7_RX_PORT             GPIO_PORT_E
  #define RTE_UART7_RX_PIN              GPIO_PIN_7
  #define RTE_UART7_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART7_RX_ID == 3)
  #define RTE_UART7_RX                  1
  #define RTE_UART7_RX_PORT             GPIO_PORT_A
  #define RTE_UART7_RX_PIN              GPIO_PIN_8
  #define RTE_UART7_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART7_RX_ID == 4)
  #define RTE_UART7_RX                  1
  #define RTE_UART7_RX_PORT             GPIO_PORT_B
  #define RTE_UART7_RX_PIN              GPIO_PIN_3
  #define RTE_UART7_RX_FUNC             GPIO_PIN_FUNC_8
#else
  #error "Invalid UART7_RX Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3
//     <i>  Selects DMA Stream (only Stream 3 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART7_RX_DMA                0
#define RTE_UART7_RX_DMA_NUMBER         1
#define RTE_UART7_RX_DMA_STREAM         3
#define RTE_UART7_RX_DMA_CHANNEL        5
#define RTE_UART7_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1
//     <i>  Selects DMA Stream (only Stream 1 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART7_TX_DMA                0
#define RTE_UART7_TX_DMA_NUMBER         1
#define RTE_UART7_TX_DMA_STREAM         1
#define RTE_UART7_TX_DMA_CHANNEL        5
#define RTE_UART7_TX_DMA_PRIORITY       0

// </e> UART7 (Universal asynchronous receiver transmitter) [Driver_USART7]

// <e> UART8 (Universal asynchronous receiver transmitter) [Driver_USART8]
// <i> Configuration settings for Driver_USART8 in component ::CMSIS Driver:USART
#define RTE_UART8                       0

//   <o> UART8_TX Pin <0=>Not Used <1=>PE1 <2=>PF9
#define   RTE_UART8_TX_ID               0
#if      (RTE_UART8_TX_ID == 0)
  #define RTE_UART8_TX                  0
#elif    (RTE_UART8_TX_ID == 1)
  #define RTE_UART8_TX                  1
  #define RTE_UART8_TX_PORT             GPIO_PORT_E
  #define RTE_UART8_TX_PIN              GPIO_PIN_1
  #define RTE_UART8_TX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART8_TX_ID == 2)
  #define RTE_UART8_TX                  1
  #define RTE_UART8_TX_PORT             GPIO_PORT_F
  #define RTE_UART8_TX_PIN              GPIO_PIN_9
  #define RTE_UART8_TX_FUNC             GPIO_PIN_FUNC_8
#else
  #error "Invalid UART8_TX Pin Configuration!"
#endif

//   <o> UART8_RX Pin <0=>Not Used <1=>PE0 <2=>PF8
#define   RTE_UART8_RX_ID               0
#if      (RTE_UART8_RX_ID == 0)
  #define RTE_UART8_RX                  0
#elif    (RTE_UART8_RX_ID == 1)
  #define RTE_UART8_RX                  1
  #define RTE_UART8_RX_PORT             GPIO_PORT_E
  #define RTE_UART8_RX_PIN              GPIO_PIN_0
  #define RTE_UART8_RX_FUNC             GPIO_PIN_FUNC_8
#elif    (RTE_UART8_RX_ID == 2)
  #define RTE_UART8_RX                  1
  #define RTE_UART8_RX_PORT             GPIO_PORT_F
  #define RTE_UART8_RX_PIN              GPIO_PIN_8
  #define RTE_UART8_RX_FUNC             GPIO_PIN_FUNC_8
#else
  #error "Invalid UART8_RX Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <6=>6
//     <i>  Selects DMA Stream (only Stream 6 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART8_RX_DMA                0
#define RTE_UART8_RX_DMA_NUMBER         1
#define RTE_UART8_RX_DMA_STREAM         6
#define RTE_UART8_RX_DMA_CHANNEL        5
#define RTE_UART8_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0
//     <i>  Selects DMA Stream (only Stream 0 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART8_TX_DMA                0
#define RTE_UART8_TX_DMA_NUMBER         1
#define RTE_UART8_TX_DMA_STREAM         0
#define RTE_UART8_TX_DMA_CHANNEL        5
#define RTE_UART8_TX_DMA_PRIORITY       0

// </e> UART8 (Universal asynchronous receiver transmitter) [Driver_USART8]

// <e> UART9 (Universal asynchronous receiver transmitter) [Driver_USART9]
// <i> Configuration settings for Driver_USART9 in component ::CMSIS Driver:USART
#define RTE_UART9                       0

//   <o> UART9_TX Pin <0=>Not Used <1=>PD15 <2=>PG1
#define   RTE_UART9_TX_ID               0
#if      (RTE_UART9_TX_ID == 0)
  #define RTE_UART9_TX                  0
#elif    (RTE_UART9_TX_ID == 1)
  #define RTE_UART9_TX                  1
  #define RTE_UART9_TX_PORT             GPIO_PORT_D
  #define RTE_UART9_TX_PIN              GPIO_PIN_15
  #define RTE_UART9_TX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART9_TX_ID == 2)
  #define RTE_UART9_TX                  1
  #define RTE_UART9_TX_PORT             GPIO_PORT_G
  #define RTE_UART9_TX_PIN              GPIO_PIN_1
  #define RTE_UART9_TX_FUNC             GPIO_PIN_FUNC_11
#else
  #error "Invalid UART9_TX Pin Configuration!"
#endif

//   <o> UART9_RX Pin <0=>Not Used <1=>PD14 <2=>PG0
#define   RTE_UART9_RX_ID               0
#if      (RTE_UART9_RX_ID == 0)
  #define RTE_UART9_RX                  0
#elif    (RTE_UART9_RX_ID == 1)
  #define RTE_UART9_RX                  1
  #define RTE_UART9_RX_PORT             GPIO_PORT_D
  #define RTE_UART9_RX_PIN              GPIO_PIN_14
  #define RTE_UART9_RX_FUNC             GPIO_PIN_FUNC_11
#elif    (RTE_UART9_RX_ID == 2)
  #define RTE_UART9_RX                  1
  #define RTE_UART9_RX_PORT             GPIO_PORT_G
  #define RTE_UART9_RX_PIN              GPIO_PIN_0
  #define RTE_UART9_RX_FUNC             GPIO_PIN_FUNC_11
#else
  #error "Invalid UART9_RX Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART9_RX_DMA                0
#define RTE_UART9_RX_DMA_NUMBER         1
#define RTE_UART9_RX_DMA_STREAM         6
#define RTE_UART9_RX_DMA_CHANNEL        5
#define RTE_UART9_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0
//     <i>  Selects DMA Stream (only Stream 0 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART9_TX_DMA                0
#define RTE_UART9_TX_DMA_NUMBER         1
#define RTE_UART9_TX_DMA_STREAM         0
#define RTE_UART9_TX_DMA_CHANNEL        5
#define RTE_UART9_TX_DMA_PRIORITY       0

// </e> UART9 (Universal asynchronous receiver transmitter) [Driver_USART9]

// <e> UART10 (Universal asynchronous receiver transmitter) [Driver_USART10]
// <i> Configuration settings for Driver_USART10 in component ::CMSIS Driver:USART
#define RTE_UART10                      0

//   <o> UART10_TX Pin <0=>Not Used <1=>PE3 <2=>PG12
#define   RTE_UART10_TX_ID              0
#if      (RTE_UART10_TX_ID == 0)
  #define RTE_UART10_TX                 0
#elif    (RTE_UART10_TX_ID == 1)
  #define RTE_UART10_TX                 1
  #define RTE_UART10_TX_PORT            GPIO_PORT_E
  #define RTE_UART10_TX_PIN             GPIO_PIN_3
  #define RTE_UART10_TX_FUNC            GPIO_PIN_FUNC_11
#elif    (RTE_UART10_TX_ID == 2)
  #define RTE_UART10_TX                 1
  #define RTE_UART10_TX_PORT            GPIO_PORT_G
  #define RTE_UART10_TX_PIN             GPIO_PIN_12
  #define RTE_UART10_TX_FUNC            GPIO_PIN_FUNC_11
#else
  #error "Invalid UART10_TX Pin Configuration!"
#endif

//   <o> UART10_RX Pin <0=>Not Used <1=>PE2 <2=>PG11
#define   RTE_UART10_RX_ID              0
#if      (RTE_UART10_RX_ID == 0)
  #define RTE_UART10_RX                 0
#elif    (RTE_UART10_RX_ID == 1)
  #define RTE_UART10_RX                 1
  #define RTE_UART10_RX_PORT            GPIO_PORT_E
  #define RTE_UART10_RX_PIN             GPIO_PIN_2
  #define RTE_UART10_RX_FUNC            GPIO_PIN_FUNC_11
#elif    (RTE_UART10_RX_ID == 2)
  #define RTE_UART10_RX                 1
  #define RTE_UART10_RX_PORT            GPIO_PORT_G
  #define RTE_UART10_RX_PIN             GPIO_PIN_11
  #define RTE_UART10_RX_FUNC            GPIO_PIN_FUNC_11
#else
  #error "Invalid UART10_RX Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0 <3=>3
//     <i>  Selects DMA Stream (only Stream 0 or 3 can be used)
//     <o3> Channel <5=>5 <9=>9
//     <i>  Selects DMA Channel (only Channel 5 or 9 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART10_RX_DMA               0
#define RTE_UART10_RX_DMA_NUMBER        1
#define RTE_UART10_RX_DMA_STREAM        6
#define RTE_UART10_RX_DMA_CHANNEL       5
#define RTE_UART10_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <7=>7 <3=>5
//     <i>  Selects DMA Stream (only Stream 7 or 5 can be used)
//     <o3> Channel <6=>6 <9=>9
//     <i>  Selects DMA Channel (only Channel 6 or 9 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART10_TX_DMA               0
#define RTE_UART10_TX_DMA_NUMBER        1
#define RTE_UART10_TX_DMA_STREAM        0
#define RTE_UART10_TX_DMA_CHANNEL       5
#define RTE_UART10_TX_DMA_PRIORITY      0

// </e> UART10 (Universal asynchronous receiver transmitter) [Driver_USART10]

// <e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::Drivers:I2C
#define   RTE_I2C1                      1

//   <o> I2C1_SCL Pin <0=>PB6 <1=>PB8
#define   RTE_I2C1_SCL_PORT_ID          0
#if      (RTE_I2C1_SCL_PORT_ID == 0)
  #define RTE_I2C1_SCL_PORT             GPIO_PORT_B
  #define RTE_I2C1_SCL_PIN              GPIO_PIN_6
  #define RTE_I2C1_SCL_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C1_SCL_PORT_ID == 1)
  #define RTE_I2C1_SCL_PORT             GPIO_PORT_B
  #define RTE_I2C1_SCL_PIN              GPIO_PIN_8
  #define RTE_I2C1_SCL_FUNC             GPIO_PIN_FUNC_4
#else
  #error "Invalid I2C1_SCL Pin Configuration!"
#endif
//   <o> I2C1_SDA Pin <0=>PB7 <1=>PB9
#define   RTE_I2C1_SDA_PORT_ID          1
#if      (RTE_I2C1_SDA_PORT_ID == 0)
  #define RTE_I2C1_SDA_PORT             GPIO_PORT_B
  #define RTE_I2C1_SDA_PIN              GPIO_PIN_7
  #define RTE_I2C1_SDA_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C1_SDA_PORT_ID == 1)
  #define RTE_I2C1_SDA_PORT             GPIO_PORT_B
  #define RTE_I2C1_SDA_PIN              GPIO_PIN_9
  #define RTE_I2C1_SDA_FUNC             GPIO_PIN_FUNC_4
#else
  #error "Invalid I2C1_SDA Pin Configuration!"
#endif
// </e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]

// <e> I2C2 (Inter-integrated Circuit Interface 2) [Driver_I2C2]
// <i> Configuration settings for Driver_I2C2 in component ::Drivers:I2C
#define   RTE_I2C2                      0

//   <o> I2C2_SCL Pin <0=>PB10 <1=>PF1 <2=>PH4
#define   RTE_I2C2_SCL_PORT_ID          0
#if      (RTE_I2C2_SCL_PORT_ID == 0)
  #define RTE_I2C2_SCL_PORT             GPIO_PORT_B
  #define RTE_I2C2_SCL_PIN              GPIO_PIN_10
  #define RTE_I2C2_SCL_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C2_SCL_PORT_ID == 1)
  #define RTE_I2C2_SCL_PORT             GPIO_PORT_F
  #define RTE_I2C2_SCL_PIN              GPIO_PIN_1
  #define RTE_I2C2_SCL_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C2_SCL_PORT_ID == 2)
  #define RTE_I2C2_SCL_PORT             GPIO_PORT_H
  #define RTE_I2C2_SCL_PIN              GPIO_PIN_4
  #define RTE_I2C2_SCL_FUNC             GPIO_PIN_FUNC_4
#else
  #error "Invalid I2C2_SCL Pin Configuration!"
#endif
//   <o> I2C2_SDA Pin <0=>PB11 <1=>PF0 <2=>PH5
#define   RTE_I2C2_SDA_PORT_ID          0
#if      (RTE_I2C2_SDA_PORT_ID == 0)
  #define RTE_I2C2_SDA_PORT             GPIO_PORT_B
  #define RTE_I2C2_SDA_PIN              GPIO_PIN_11
  #define RTE_I2C2_SDA_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C2_SDA_PORT_ID == 1)
  #define RTE_I2C2_SDA_PORT             GPIO_PORT_F
  #define RTE_I2C2_SDA_PIN              GPIO_PIN_0
  #define RTE_I2C2_SDA_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C2_SDA_PORT_ID == 2)
  #define RTE_I2C2_SDA_PORT             GPIO_PORT_H
  #define RTE_I2C2_SDA_PIN              GPIO_PIN_5
  #define RTE_I2C2_SDA_FUNC             GPIO_PIN_FUNC_4
#else
  #error "Invalid I2C2_SDA Pin Configuration!"
#endif
// </e> I2C2 (Inter-integrated Circuit Interface 2) [Driver_I2C2]

// <e> I2C3 (Inter-integrated Circuit Interface 3) [Driver_I2C3]
// <i> Configuration settings for Driver_I2C3 in component ::Drivers:I2C
#define   RTE_I2C3                      0

//   <o> I2C3_SCL Pin <0=>PA8 <1=>PH7
#define   RTE_I2C3_SCL_PORT_ID          0
#if      (RTE_I2C3_SCL_PORT_ID == 0)
  #define RTE_I2C3_SCL_PORT             GPIO_PORT_A
  #define RTE_I2C3_SCL_PIN              GPIO_PIN_8
  #define RTE_I2C3_SCL_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C3_SCL_PORT_ID == 1)
  #define RTE_I2C3_SCL_PORT             GPIO_PORT_H
  #define RTE_I2C3_SCL_PIN              GPIO_PIN_7
  #define RTE_I2C3_SCL_FUNC             GPIO_PIN_FUNC_4
#else
  #error "Invalid I2C3_SCL Pin Configuration!"
#endif
//   <o> I2C3_SDA Pin <0=>PC9 <1=>PH8
#define   RTE_I2C3_SDA_PORT_ID          0
#if      (RTE_I2C3_SDA_PORT_ID == 0)
  #define RTE_I2C3_SDA_PORT             GPIO_PORT_C
  #define RTE_I2C3_SDA_PIN              GPIO_PIN_9
  #define RTE_I2C3_SDA_FUNC             GPIO_PIN_FUNC_4
#elif    (RTE_I2C3_SDA_PORT_ID == 1)
  #define RTE_I2C3_SDA_PORT             GPIO_PORT_H
  #define RTE_I2C3_SDA_PIN              GPIO_PIN_8
  #define RTE_I2C3_SDA_FUNC             GPIO_PIN_FUNC_4
#else
  #error "Invalid I2C3_SDA Pin Configuration!"
#endif
// </e> I2C3 (Inter-integrated Circuit Interface 3) [Driver_I2C3]

// <e> I2S2 (Inter-IC Sound Interface 2) [Driver_SAI2]
// <i> Configuration settings for Driver_SAI2 in component ::Drivers:SAI
#define   RTE_I2S2                      0

//   <o> I2S2_MCLK Pin <0=>PC6
#define   RTE_I2S2_MCLK_PORT_ID         0
#if      (RTE_I2S2_MCLK_PORT_ID == 0)
  #define RTE_I2S2_MCLK_PORT            GPIO_PORT_C
  #define RTE_I2S2_MCLK_PIN             GPIO_PIN_6
  #define RTE_I2S2_MCLK_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid I2S2_MCLK Pin Configuration!"
#endif
//   <o> I2S2_BCLK Pin <0=>PB10 <1=>PB13 <2=>PI1
#define   RTE_I2S2_BCLK_PORT_ID         1
#if      (RTE_I2S2_BCLK_PORT_ID == 0)
  #define RTE_I2S2_BCLK_PORT            GPIO_PORT_B
  #define RTE_I2S2_BCLK_PIN             GPIO_PIN_10
  #define RTE_I2S2_BCLK_FUNC            GPIO_PIN_FUNC_5
#elif    (RTE_I2S2_BCLK_PORT_ID == 1)
  #define RTE_I2S2_BCLK_PORT            GPIO_PORT_B
  #define RTE_I2S2_BCLK_PIN             GPIO_PIN_13
  #define RTE_I2S2_BCLK_FUNC            GPIO_PIN_FUNC_5
#elif    (RTE_I2S2_BCLK_PORT_ID == 2)
  #define RTE_I2S2_BCLK_PORT            GPIO_PORT_I
  #define RTE_I2S2_BCLK_PIN             GPIO_PIN_1
  #define RTE_I2S2_BCLK_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid I2S2_BCLK Pin Configuration!"
#endif
//   <o> I2S2_WCLK Pin <0=>PB9 <1=>PB12 <2=>PI0
#define   RTE_I2S2_WCLK_PORT_ID         1
#if      (RTE_I2S2_WCLK_PORT_ID == 0)
  #define RTE_I2S2_WCLK_PORT            GPIO_PORT_B
  #define RTE_I2S2_WCLK_PIN             GPIO_PIN_9
  #define RTE_I2S2_WCLK_FUNC            GPIO_PIN_FUNC_5
#elif    (RTE_I2S2_WCLK_PORT_ID == 1)
  #define RTE_I2S2_WCLK_PORT            GPIO_PORT_B
  #define RTE_I2S2_WCLK_PIN             GPIO_PIN_12
  #define RTE_I2S2_WCLK_FUNC            GPIO_PIN_FUNC_5
#elif    (RTE_I2S2_WCLK_PORT_ID == 2)
  #define RTE_I2S2_WCLK_PORT            GPIO_PORT_I
  #define RTE_I2S2_WCLK_PIN             GPIO_PIN_0
  #define RTE_I2S2_WCLK_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid I2S2_WCLK Pin Configuration!"
#endif
//   <o> I2S2_DOUT Pin <0=>PB15 <1=>PC3 <2=>PI3
#define   RTE_I2S2_DOUT_PORT_ID         0
#if      (RTE_I2S2_DOUT_PORT_ID == 0)
  #define RTE_I2S2_DOUT_PORT            GPIO_PORT_B
  #define RTE_I2S2_DOUT_PIN             GPIO_PIN_15
  #define RTE_I2S2_DOUT_FUNC            GPIO_PIN_FUNC_5
#elif    (RTE_I2S2_DOUT_PORT_ID == 1)
  #define RTE_I2S2_DOUT_PORT            GPIO_PORT_C
  #define RTE_I2S2_DOUT_PIN             GPIO_PIN_3
  #define RTE_I2S2_DOUT_FUNC            GPIO_PIN_FUNC_5
#elif    (RTE_I2S2_DOUT_PORT_ID == 2)
  #define RTE_I2S2_DOUT_PORT            GPIO_PORT_I
  #define RTE_I2S2_DOUT_PIN             GPIO_PIN_3
  #define RTE_I2S2_DOUT_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid I2S2_DOUT Pin Configuration!"
#endif
//   <o> I2S2_DIN Pin <0=>PB14 <1=>PC2 <2=>PI2
#define   RTE_I2S2_DIN_PORT_ID          0
#if      (RTE_I2S2_DIN_PORT_ID == 0)
  #define RTE_I2S2_DIN_PORT             GPIO_PORT_B
  #define RTE_I2S2_DIN_PIN              GPIO_PIN_14
  #define RTE_I2S2_DIN_FUNC             GPIO_PIN_FUNC_6
#elif    (RTE_I2S2_DIN_PORT_ID == 1)
  #define RTE_I2S2_DIN_PORT             GPIO_PORT_C
  #define RTE_I2S2_DIN_PIN              GPIO_PIN_2
  #define RTE_I2S2_DIN_FUNC             GPIO_PIN_FUNC_6
#elif    (RTE_I2S2_DIN_PORT_ID == 2)
  #define RTE_I2S2_DIN_PORT             GPIO_PORT_I
  #define RTE_I2S2_DIN_PIN              GPIO_PIN_2
  #define RTE_I2S2_DIN_FUNC             GPIO_PIN_FUNC_6
#else
  #error "Invalid I2S2_DIN Pin Configuration!"
#endif
//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3
//     <i>  Selects DMA Stream (only Stream 3 can be used)
//     <o3> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2S2_RX_DMA                 0
#define RTE_I2S2_RX_DMA_NUMBER          1
#define RTE_I2S2_RX_DMA_STREAM          3
#define RTE_I2S2_RX_DMA_CHANNEL         3
#define RTE_I2S2_RX_DMA_PRIORITY        3

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <4=>4
//     <i>  Selects DMA Stream (only Stream 4 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2S2_TX_DMA                 0
#define RTE_I2S2_TX_DMA_NUMBER          1
#define RTE_I2S2_TX_DMA_STREAM          4
#define RTE_I2S2_TX_DMA_CHANNEL         0
#define RTE_I2S2_TX_DMA_PRIORITY        3

// </e> I2S2 (Inter-IC Sound Interface 2) [Driver_SAI2]

// <e> I2S3 (Inter-IC Sound Interface 3) [Driver_SAI3]
// <i> Configuration settings for Driver_SAI3 in component ::Drivers:SAI
#define   RTE_I2S3                      1

//   <o> I2S3_MCLK Pin <0=>PC7
#define   RTE_I2S3_MCLK_PORT_ID         0
#if      (RTE_I2S3_MCLK_PORT_ID == 0)
  #define RTE_I2S3_MCLK_PORT            GPIO_PORT_C
  #define RTE_I2S3_MCLK_PIN             GPIO_PIN_7
  #define RTE_I2S3_MCLK_FUNC            GPIO_PIN_FUNC_6
#else
  #error "Invalid I2S3_MCLK Pin Configuration!"
#endif
//   <o> I2S3_BCLK Pin <0=>PB3 <1=>PC10
#define   RTE_I2S3_BCLK_PORT_ID         1
#if      (RTE_I2S3_BCLK_PORT_ID == 0)
  #define RTE_I2S3_BCLK_PORT            GPIO_PORT_B
  #define RTE_I2S3_BCLK_PIN             GPIO_PIN_3
  #define RTE_I2S3_BCLK_FUNC            GPIO_PIN_FUNC_6
#elif    (RTE_I2S3_BCLK_PORT_ID == 1)
  #define RTE_I2S3_BCLK_PORT            GPIO_PORT_C
  #define RTE_I2S3_BCLK_PIN             GPIO_PIN_10
  #define RTE_I2S3_BCLK_FUNC            GPIO_PIN_FUNC_6
#else
  #error "Invalid I2S3_BCLK Pin Configuration!"
#endif
//   <o> I2S3_WCLK Pin <0=>PA4 <1=>PA15
#define   RTE_I2S3_WCLK_PORT_ID         0
#if      (RTE_I2S3_WCLK_PORT_ID == 0)
  #define RTE_I2S3_WCLK_PORT            GPIO_PORT_A
  #define RTE_I2S3_WCLK_PIN             GPIO_PIN_4
  #define RTE_I2S3_WCLK_FUNC            GPIO_PIN_FUNC_6
#elif    (RTE_I2S3_WCLK_PORT_ID == 1)
  #define RTE_I2S3_WCLK_PORT            GPIO_PORT_A
  #define RTE_I2S3_WCLK_PIN             GPIO_PIN_15
  #define RTE_I2S3_WCLK_FUNC            GPIO_PIN_FUNC_6
#else
  #error "Invalid I2S3_WCLK Pin Configuration!"
#endif
//   <o> I2S3_DOUT Pin <0=>PB5 <1=>PC12
#define   RTE_I2S3_DOUT_PORT_ID         1
#if      (RTE_I2S3_DOUT_PORT_ID == 0)
  #define RTE_I2S3_DOUT_PORT            GPIO_PORT_B
  #define RTE_I2S3_DOUT_PIN             GPIO_PIN_5
  #define RTE_I2S3_DOUT_FUNC            GPIO_PIN_FUNC_6
#elif    (RTE_I2S3_DOUT_PORT_ID == 1)
  #define RTE_I2S3_DOUT_PORT            GPIO_PORT_C
  #define RTE_I2S3_DOUT_PIN             GPIO_PIN_12
  #define RTE_I2S3_DOUT_FUNC            GPIO_PIN_FUNC_6
#else
  #error "Invalid I2S3_DOUT Pin Configuration!"
#endif
//   <o> I2S3_DIN Pin <0=>PB4 <1=>PC11
#define   RTE_I2S3_DIN_PORT_ID          1
#if      (RTE_I2S3_DIN_PORT_ID == 0)
  #define RTE_I2S3_DIN_PORT             GPIO_PORT_B
  #define RTE_I2S3_DIN_PIN              GPIO_PIN_4
  #define RTE_I2S3_DIN_FUNC             GPIO_PIN_FUNC_7
#elif    (RTE_I2S3_DIN_PORT_ID == 1)
  #define RTE_I2S3_DIN_PORT             GPIO_PORT_C
  #define RTE_I2S3_DIN_PIN              GPIO_PIN_11
  #define RTE_I2S3_DIN_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid I2S3_DIN Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0 <2=>2
//     <i>  Selects DMA Stream (only Stream 0 or 2 can be used)
//     <o3> Channel <2=>2 <3=>3
//     <i>  Selects DMA Channel (only Channel 2 or 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2S3_RX_DMA                 0
#define RTE_I2S3_RX_DMA_NUMBER          1
#define RTE_I2S3_RX_DMA_STREAM          0
#define RTE_I2S3_RX_DMA_CHANNEL         2
#define RTE_I2S3_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <5=>5 <7=>7
//     <i>  Selects DMA Stream (only Stream 5 or 7 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_I2S3_TX_DMA                 1
#define RTE_I2S3_TX_DMA_NUMBER          1
#define RTE_I2S3_TX_DMA_STREAM          5
#define RTE_I2S3_TX_DMA_CHANNEL         0
#define RTE_I2S3_TX_DMA_PRIORITY        3

// </e> I2S3 (Inter-IC Sound Interface 3) [Driver_SAI3]

// <e> SPI1 (Serial Peripheral Interface 1) [Driver_SPI1]
// <i> Configuration settings for Driver_SPI1 in component ::CMSIS Driver:SPI
#define RTE_SPI1                        1

//   <o> SPI1_MISO Pin <0=>Not Used <1=>PA6 <2=>PB4
#define RTE_SPI1_MISO_PORT_ID           0
#if    (RTE_SPI1_MISO_PORT_ID == 0)
  #define RTE_SPI1_MISO                 0
#elif  (RTE_SPI1_MISO_PORT_ID == 1)
  #define RTE_SPI1_MISO                 1
  #define RTE_SPI1_MISO_PORT            GPIO_PORT_A
  #define RTE_SPI1_MISO_PIN             GPIO_PIN_6
  #define RTE_SPI1_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI1_MISO_PORT_ID == 2)
  #define RTE_SPI1_MISO                 1
  #define RTE_SPI1_MISO_PORT            GPIO_PORT_B
  #define RTE_SPI1_MISO_PIN             GPIO_PIN_4
  #define RTE_SPI1_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_MISO Pin Configuration!"
#endif

//   <o> SPI1_MOSI Pin <0=>Not Used <1=>PA7 <2=>PB5
#define RTE_SPI1_MOSI_PORT_ID           1
#if    (RTE_SPI1_MOSI_PORT_ID == 0)
  #define RTE_SPI1_MOSI                 0
#elif  (RTE_SPI1_MOSI_PORT_ID == 1)
  #define RTE_SPI1_MOSI                 1
  #define RTE_SPI1_MOSI_PORT            GPIO_PORT_A
  #define RTE_SPI1_MOSI_PIN             GPIO_PIN_7
  #define RTE_SPI1_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI1_MOSI_PORT_ID == 2)
  #define RTE_SPI1_MOSI                 1
  #define RTE_SPI1_MOSI_PORT            GPIO_PORT_B
  #define RTE_SPI1_MOSI_PIN             GPIO_PIN_5
  #define RTE_SPI1_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_MOSI Pin Configuration!"
#endif

//   <o> SPI1_SCK Pin <0=>PA5 <1=>PB3
#define RTE_SPI1_SCK_PORT_ID            0
#if    (RTE_SPI1_SCK_PORT_ID == 0)
  #define RTE_SPI1_SCK_PORT             GPIO_PORT_A
  #define RTE_SPI1_SCK_PIN              GPIO_PIN_5
  #define RTE_SPI1_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI1_SCK_PORT_ID == 1)
  #define RTE_SPI1_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI1_SCK_PIN              GPIO_PIN_3
  #define RTE_SPI1_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_SCK Pin Configuration!"
#endif

//   <o> SPI1_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15
#define RTE_SPI1_NSS_PORT_ID            2
#if    (RTE_SPI1_NSS_PORT_ID == 0)
  #define RTE_SPI1_NSS                  0
#elif  (RTE_SPI1_NSS_PORT_ID == 1)
  #define RTE_SPI1_NSS                  1
  #define RTE_SPI1_NSS_PORT             GPIO_PORT_A
  #define RTE_SPI1_NSS_PIN              GPIO_PIN_4
  #define RTE_SPI1_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI1_NSS_PORT_ID == 2)
  #define RTE_SPI1_NSS                  1
  #define RTE_SPI1_NSS_PORT             GPIO_PORT_A
  #define RTE_SPI1_NSS_PIN              GPIO_PIN_15
  #define RTE_SPI1_NSS_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0 <2=>2
//     <i>  Selects DMA Stream (only Stream 0 or 2 can be used)
//     <o3> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI1_RX_DMA                 1
#define RTE_SPI1_RX_DMA_NUMBER          2
#define RTE_SPI1_RX_DMA_STREAM          0
#define RTE_SPI1_RX_DMA_CHANNEL         3
#define RTE_SPI1_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <3=>3 <5=>5
//     <i>  Selects DMA Stream (only Stream 3 or 5 can be used)
//     <o3> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI1_TX_DMA                 1
#define RTE_SPI1_TX_DMA_NUMBER          2
#define RTE_SPI1_TX_DMA_STREAM          5
#define RTE_SPI1_TX_DMA_CHANNEL         3
#define RTE_SPI1_TX_DMA_PRIORITY        0

// </e>

// <e> SPI2 (Serial Peripheral Interface 2) [Driver_SPI2]
// <i> Configuration settings for Driver_SPI2 in component ::CMSIS Driver:SPI
#define RTE_SPI2                        0

//   <o> SPI2_MISO Pin <0=>Not Used <1=>PB14 <2=>PC2 <3=>PI2 <4=>PA12
#define RTE_SPI2_MISO_PORT_ID           0
#if    (RTE_SPI2_MISO_PORT_ID == 0)
  #define RTE_SPI2_MISO                 0
#elif  (RTE_SPI2_MISO_PORT_ID == 1)
  #define RTE_SPI2_MISO                 1
  #define RTE_SPI2_MISO_PORT            GPIO_PORT_B
  #define RTE_SPI2_MISO_PIN             GPIO_PIN_14
  #define RTE_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_MISO_PORT_ID == 2)
  #define RTE_SPI2_MISO                 1
  #define RTE_SPI2_MISO_PORT            GPIO_PORT_C
  #define RTE_SPI2_MISO_PIN             GPIO_PIN_2
  #define RTE_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_MISO_PORT_ID == 3)
  #define RTE_SPI2_MISO                 1
  #define RTE_SPI2_MISO_PORT            GPIO_PORT_I
  #define RTE_SPI2_MISO_PIN             GPIO_PIN_2
  #define RTE_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_MISO_PORT_ID == 4)
  #define RTE_SPI2_MISO                 1
  #define RTE_SPI2_MISO_PORT            GPIO_PORT_A
  #define RTE_SPI2_MISO_PIN             GPIO_PIN_12
  #define RTE_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_MISO Pin Configuration!"
#endif

//   <o> SPI2_MOSI Pin <0=>Not Used <1=>PB15 <2=>PC3 <3=>PI3 <4=>PA10
#define RTE_SPI2_MOSI_PORT_ID           0
#if    (RTE_SPI2_MOSI_PORT_ID == 0)
  #define RTE_SPI2_MOSI                 0
#elif  (RTE_SPI2_MOSI_PORT_ID == 1)
  #define RTE_SPI2_MOSI                 1
  #define RTE_SPI2_MOSI_PORT            GPIO_PORT_B
  #define RTE_SPI2_MOSI_PIN             GPIO_PIN_15
  #define RTE_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_MOSI_PORT_ID == 2)
  #define RTE_SPI2_MOSI                 1
  #define RTE_SPI2_MOSI_PORT            GPIO_PORT_C
  #define RTE_SPI2_MOSI_PIN             GPIO_PIN_3
  #define RTE_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_MOSI_PORT_ID == 3)
  #define RTE_SPI2_MOSI                 1
  #define RTE_SPI2_MOSI_PORT            GPIO_PORT_I
  #define RTE_SPI2_MOSI_PIN             GPIO_PIN_3
  #define RTE_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_MOSI_PORT_ID == 4)
  #define RTE_SPI2_MOSI                 1
  #define RTE_SPI2_MOSI_PORT            GPIO_PORT_A
  #define RTE_SPI2_MOSI_PIN             GPIO_PIN_10
  #define RTE_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_MOSI Pin Configuration!"
#endif

//   <o> SPI2_SCK Pin <0=>PB10 <1=>PB13 <2=>PC7 <3=>PD3 <4=>PI1 <5=>PA9
#define RTE_SPI2_SCK_PORT_ID            0
#if    (RTE_SPI2_SCK_PORT_ID == 0)
  #define RTE_SPI2_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI2_SCK_PIN              GPIO_PIN_10
  #define RTE_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_SCK_PORT_ID == 1)
  #define RTE_SPI2_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI2_SCK_PIN              GPIO_PIN_13
  #define RTE_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_SCK_PORT_ID == 2)
  #define RTE_SPI2_SCK_PORT             GPIO_PORT_C
  #define RTE_SPI2_SCK_PIN              GPIO_PIN_7
  #define RTE_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_SCK_PORT_ID == 3)
  #define RTE_SPI2_SCK_PORT             GPIO_PORT_D
  #define RTE_SPI2_SCK_PIN              GPIO_PIN_3
  #define RTE_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_SCK_PORT_ID == 4)
  #define RTE_SPI2_SCK_PORT             GPIO_PORT_I
  #define RTE_SPI2_SCK_PIN              GPIO_PIN_1
  #define RTE_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_SCK_PORT_ID == 5)
  #define RTE_SPI2_SCK_PORT             GPIO_PORT_A
  #define RTE_SPI2_SCK_PIN              GPIO_PIN_9
  #define RTE_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_SCK Pin Configuration!"
#endif

//   <o> SPI2_NSS Pin <0=>Not Used <1=>PB9 <2=>PB12 <3=>PI0 <4=>PA11
#define RTE_SPI2_NSS_PORT_ID            0
#if    (RTE_SPI2_NSS_PORT_ID == 0)
  #define RTE_SPI2_NSS                  0
#elif  (RTE_SPI2_NSS_PORT_ID == 1)
  #define RTE_SPI2_NSS                  1
  #define RTE_SPI2_NSS_PORT             GPIO_PORT_B
  #define RTE_SPI2_NSS_PIN              GPIO_PIN_9
  #define RTE_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_NSS_PORT_ID == 2)
  #define RTE_SPI2_NSS                  1
  #define RTE_SPI2_NSS_PORT             GPIO_PORT_B
  #define RTE_SPI2_NSS_PIN              GPIO_PIN_12
  #define RTE_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_NSS_PORT_ID == 3)
  #define RTE_SPI2_NSS                  1
  #define RTE_SPI2_NSS_PORT             GPIO_PORT_I
  #define RTE_SPI2_NSS_PIN              GPIO_PIN_0
  #define RTE_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI2_NSS_PORT_ID == 4)
  #define RTE_SPI2_NSS                  1
  #define RTE_SPI2_NSS_PORT             GPIO_PORT_A
  #define RTE_SPI2_NSS_PIN              GPIO_PIN_11
  #define RTE_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3
//     <i>  Selects DMA Stream (only Stream 3 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI2_RX_DMA                 0
#define RTE_SPI2_RX_DMA_NUMBER          1
#define RTE_SPI2_RX_DMA_STREAM          3
#define RTE_SPI2_RX_DMA_CHANNEL         0
#define RTE_SPI2_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <4=>4
//     <i>  Selects DMA Stream (only Stream 4 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI2_TX_DMA                 0
#define RTE_SPI2_TX_DMA_NUMBER          1
#define RTE_SPI2_TX_DMA_STREAM          4
#define RTE_SPI2_TX_DMA_CHANNEL         0
#define RTE_SPI2_TX_DMA_PRIORITY        0

// </e>

// <e> SPI3 (Serial Peripheral Interface 3) [Driver_SPI3]
// <i> Configuration settings for Driver_SPI3 in component ::CMSIS Driver:SPI
#define RTE_SPI3                        0

//   <o> SPI3_MISO Pin <0=>Not Used <1=>PB4 <2=>PC11
#define RTE_SPI3_MISO_PORT_ID           0
#if    (RTE_SPI3_MISO_PORT_ID == 0)
  #define RTE_SPI3_MISO                 0
#elif  (RTE_SPI3_MISO_PORT_ID == 1)
  #define RTE_SPI3_MISO                 1
  #define RTE_SPI3_MISO_PORT            GPIO_PORT_B
  #define RTE_SPI3_MISO_PIN             GPIO_PIN_4
  #define RTE_SPI3_MISO_FUNC            GPIO_PIN_FUNC_6
#elif  (RTE_SPI3_MISO_PORT_ID == 2)
  #define RTE_SPI3_MISO                 1
  #define RTE_SPI3_MISO_PORT            GPIO_PORT_C
  #define RTE_SPI3_MISO_PIN             GPIO_PIN_11
  #define RTE_SPI3_MISO_FUNC            GPIO_PIN_FUNC_6
#else
  #error "Invalid SPI3_MISO Pin Configuration!"
#endif

//   <o> SPI3_MOSI Pin <0=>Not Used <1=>PB5 <2=>PC12 <3=>PD6
#define RTE_SPI3_MOSI_PORT_ID           0
#if    (RTE_SPI3_MOSI_PORT_ID == 0)
  #define RTE_SPI3_MOSI                 0
#elif  (RTE_SPI3_MOSI_PORT_ID == 1)
  #define RTE_SPI3_MOSI                 1
  #define RTE_SPI3_MOSI_PORT            GPIO_PORT_B
  #define RTE_SPI3_MOSI_PIN             GPIO_PIN_5
  #define RTE_SPI3_MOSI_FUNC            GPIO_PIN_FUNC_6
#elif  (RTE_SPI3_MOSI_PORT_ID == 2)
  #define RTE_SPI3_MOSI                 1
  #define RTE_SPI3_MOSI_PORT            GPIO_PORT_C
  #define RTE_SPI3_MOSI_PIN             GPIO_PIN_12
  #define RTE_SPI3_MOSI_FUNC            GPIO_PIN_FUNC_6
#elif  (RTE_SPI3_MOSI_PORT_ID == 3)
  #define RTE_SPI3_MOSI                 1
  #define RTE_SPI3_MOSI_PORT            GPIO_PORT_D
  #define RTE_SPI3_MOSI_PIN             GPIO_PIN_6

  #if (defined (STM32F413xx) || defined (STM32F423xx))
    #define RTE_SPI3_MOSI_FUNC          GPIO_PIN_FUNC_5
  #else
    #define RTE_SPI3_MOSI_FUNC          GPIO_PIN_FUNC_6
  #endif

#else
  #error "Invalid SPI3_MOSI Pin Configuration!"
#endif

//   <o> SPI3_SCK Pin <0=>PB3 <1=>PB12 <2=>PC10
#define RTE_SPI3_SCK_PORT_ID            0
#if    (RTE_SPI3_SCK_PORT_ID == 0)
  #define RTE_SPI3_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI3_SCK_PIN              GPIO_PIN_3
  #define RTE_SPI3_SCK_FUNC             GPIO_PIN_FUNC_6
#elif  (RTE_SPI3_SCK_PORT_ID == 1)
  #define RTE_SPI3_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI3_SCK_PIN              GPIO_PIN_12

  #if (defined (STM32F413xx) || defined (STM32F423xx))
    #define RTE_SPI3_SCK_FUNC           GPIO_PIN_FUNC_7
  #else
    #define RTE_SPI3_SCK_FUNC           GPIO_PIN_FUNC_6
  #endif

#elif  (RTE_SPI3_SCK_PORT_ID == 2)
  #define RTE_SPI3_SCK_PORT             GPIO_PORT_C
  #define RTE_SPI3_SCK_PIN              GPIO_PIN_10
  #define RTE_SPI3_SCK_FUNC             GPIO_PIN_FUNC_6
#else
  #error "Invalid SPI3_SCK Pin Configuration!"
#endif

//   <o> SPI3_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15
#define RTE_SPI3_NSS_PORT_ID            0
#if    (RTE_SPI3_NSS_PORT_ID == 0)
  #define RTE_SPI3_NSS                  0
#elif  (RTE_SPI3_NSS_PORT_ID == 1)
  #define RTE_SPI3_NSS                  1
  #define RTE_SPI3_NSS_PORT             GPIO_PORT_A
  #define RTE_SPI3_NSS_PIN              GPIO_PIN_4
  #define RTE_SPI3_NSS_FUNC             GPIO_PIN_FUNC_6
#elif  (RTE_SPI3_NSS_PORT_ID == 2)
  #define RTE_SPI3_NSS                  1
  #define RTE_SPI3_NSS_PORT             GPIO_PORT_A
  #define RTE_SPI3_NSS_PIN              GPIO_PIN_15
  #define RTE_SPI3_NSS_FUNC             GPIO_PIN_FUNC_6
#else
  #error "Invalid SPI3_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0 <2=>2
//     <i>  Selects DMA Stream (only Stream 0 or 2 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI3_RX_DMA                 0
#define RTE_SPI3_RX_DMA_NUMBER          1
#define RTE_SPI3_RX_DMA_STREAM          0
#define RTE_SPI3_RX_DMA_CHANNEL         0
#define RTE_SPI3_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <5=>5 <7=>7
//     <i>  Selects DMA Stream (only Stream 5 or 7 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI3_TX_DMA                 0
#define RTE_SPI3_TX_DMA_NUMBER          1
#define RTE_SPI3_TX_DMA_STREAM          5
#define RTE_SPI3_TX_DMA_CHANNEL         0
#define RTE_SPI3_TX_DMA_PRIORITY        0

// </e>

// <e> SPI4 (Serial Peripheral Interface 4) [Driver_SPI4]
// <i> Configuration settings for Driver_SPI4 in component ::CMSIS Driver:SPI
#define RTE_SPI4                        0

//   <o> SPI4_MISO Pin <0=>Not Used <1=>PA11 <2=>PE5 <3=>PE13
#define RTE_SPI4_MISO_PORT_ID           0
#if    (RTE_SPI4_MISO_PORT_ID == 0)
  #define RTE_SPI4_MISO                 0
#elif  (RTE_SPI4_MISO_PORT_ID == 1)
  #define RTE_SPI4_MISO                 1
  #define RTE_SPI4_MISO_PORT            GPIO_PORT_A
  #define RTE_SPI4_MISO_PIN             GPIO_PIN_11

  #if (defined (STM32F413xx) || defined (STM32F423xx))
    #define RTE_SPI3_MISO_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI3_MISO_FUNC          GPIO_PIN_FUNC_5
  #endif

#elif  (RTE_SPI4_MISO_PORT_ID == 2)
  #define RTE_SPI4_MISO                 1
  #define RTE_SPI4_MISO_PORT            GPIO_PORT_E
  #define RTE_SPI4_MISO_PIN             GPIO_PIN_5
  #define RTE_SPI4_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI4_MISO_PORT_ID == 3)
  #define RTE_SPI4_MISO                 1
  #define RTE_SPI4_MISO_PORT            GPIO_PORT_E
  #define RTE_SPI4_MISO_PIN             GPIO_PIN_13
  #define RTE_SPI4_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_MISO Pin Configuration!"
#endif

//   <o> SPI4_MOSI Pin <0=>Not Used <1=>PA1 <2=>PE6 <3=>PE14
#define RTE_SPI4_MOSI_PORT_ID           0
#if    (RTE_SPI4_MOSI_PORT_ID == 0)
  #define RTE_SPI4_MOSI                 0
#elif  (RTE_SPI4_MOSI_PORT_ID == 1)
  #define RTE_SPI4_MOSI                 1
  #define RTE_SPI4_MOSI_PORT            GPIO_PORT_A
  #define RTE_SPI4_MOSI_PIN             GPIO_PIN_1
  #define RTE_SPI4_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI4_MOSI_PORT_ID == 2)
  #define RTE_SPI4_MOSI                 1
  #define RTE_SPI4_MOSI_PORT            GPIO_PORT_E
  #define RTE_SPI4_MOSI_PIN             GPIO_PIN_6
  #define RTE_SPI4_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (RTE_SPI4_MOSI_PORT_ID == 3)
  #define RTE_SPI4_MOSI                 1
  #define RTE_SPI4_MOSI_PORT            GPIO_PORT_E
  #define RTE_SPI4_MOSI_PIN             GPIO_PIN_14
  #define RTE_SPI4_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_MOSI Pin Configuration!"
#endif

//   <o> SPI4_SCK Pin <0=>PB13 <1=>PE2 <2=>PE12
#define RTE_SPI4_SCK_PORT_ID            0
#if    (RTE_SPI4_SCK_PORT_ID == 0)
  #define RTE_SPI4_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI4_SCK_PIN              GPIO_PIN_13

  #if (defined (STM32F413xx) || defined (STM32F423xx))
    #define RTE_SPI4_SCK_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI4_SCK_FUNC           GPIO_PIN_FUNC_5
  #endif

#elif  (RTE_SPI4_SCK_PORT_ID == 1)
  #define RTE_SPI4_SCK_PORT             GPIO_PORT_E
  #define RTE_SPI4_SCK_PIN              GPIO_PIN_2
  #define RTE_SPI4_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI4_SCK_PORT_ID == 2)
  #define RTE_SPI4_SCK_PORT             GPIO_PORT_E
  #define RTE_SPI4_SCK_PIN              GPIO_PIN_12
  #define RTE_SPI4_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_SCK Pin Configuration!"
#endif

//   <o> SPI4_NSS Pin <0=>Not Used <1=>PB12 <2=>PE4 <3=>PE11
#define RTE_SPI4_NSS_PORT_ID            0
#if    (RTE_SPI4_NSS_PORT_ID == 0)
  #define RTE_SPI4_NSS                  0
#elif  (RTE_SPI4_NSS_PORT_ID == 1)
  #define RTE_SPI4_NSS                  1
  #define RTE_SPI4_NSS_PORT             GPIO_PORT_B
  #define RTE_SPI4_NSS_PIN              GPIO_PIN_12

  #if (defined (STM32F413xx) || defined (STM32F423xx))
    #define RTE_SPI4_NSS_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI4_NSS_FUNC           GPIO_PIN_FUNC_5
  #endif

#elif  (RTE_SPI4_NSS_PORT_ID == 2)
  #define RTE_SPI4_NSS                  1
  #define RTE_SPI4_NSS_PORT             GPIO_PORT_E
  #define RTE_SPI4_NSS_PIN              GPIO_PIN_4
  #define RTE_SPI4_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (RTE_SPI4_NSS_PORT_ID == 3)
  #define RTE_SPI4_NSS                  1
  #define RTE_SPI4_NSS_PORT             GPIO_PORT_E
  #define RTE_SPI4_NSS_PIN              GPIO_PIN_11
  #define RTE_SPI4_NSS_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0 <3=>3 <4=>4
//     <i>  Selects DMA Stream (only Stream 0 or 3 can be used)
//     <o3> Channel <4=>4 <5=>5
//     <i>  Selects DMA Channel (only Channel 4 or 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI4_RX_DMA                 0
#define RTE_SPI4_RX_DMA_NUMBER          1
#define RTE_SPI4_RX_DMA_STREAM          0
#define RTE_SPI4_RX_DMA_CHANNEL         0
#define RTE_SPI4_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <1=>1 <4=>4
//     <i>  Selects DMA Stream (only Stream 1 or 4 can be used)
//     <o3> Channel <4=>4 <5=>5
//     <i>  Selects DMA Channel (only Channel 4 or 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI4_TX_DMA                 0
#define RTE_SPI4_TX_DMA_NUMBER          1
#define RTE_SPI4_TX_DMA_STREAM          5
#define RTE_SPI4_TX_DMA_CHANNEL         0
#define RTE_SPI4_TX_DMA_PRIORITY        0

// </e>

// <e> SPI5 (Serial Peripheral Interface 5) [Driver_SPI5]
// <i> Configuration settings for Driver_SPI5 in component ::CMSIS Driver:SPI
#define RTE_SPI5                        0

//   <o> SPI5_MISO Pin <0=>Not Used <1=>PA12 <2=>PE5 <3=>PE13 <4=>PF8 <5=>PH7
#define RTE_SPI5_MISO_PORT_ID           0
#if    (RTE_SPI5_MISO_PORT_ID == 0)
  #define RTE_SPI5_MISO                 0
#elif  (RTE_SPI5_MISO_PORT_ID == 1)
  #define RTE_SPI5_MISO                 1
  #define RTE_SPI5_MISO_PORT            GPIO_PORT_A
  #define RTE_SPI5_MISO_PIN             GPIO_PIN_12

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MISO_PORT_ID == 2)
  #define RTE_SPI5_MISO                 1
  #define RTE_SPI5_MISO_PORT            GPIO_PORT_E
  #define RTE_SPI5_MISO_PIN             GPIO_PIN_5

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MISO_PORT_ID == 3)
  #define RTE_SPI5_MISO                 1
  #define RTE_SPI5_MISO_PORT            GPIO_PORT_E
  #define RTE_SPI5_MISO_PIN             GPIO_PIN_13

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MISO_PORT_ID == 4)
  #define RTE_SPI5_MISO                 1
  #define RTE_SPI5_MISO_PORT            GPIO_PORT_F
  #define RTE_SPI5_MISO_PIN             GPIO_PIN_8

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MISO_PORT_ID == 5)
  #define RTE_SPI5_MISO                 1
  #define RTE_SPI5_MISO_PORT            GPIO_PORT_H
  #define RTE_SPI5_MISO_PIN             GPIO_PIN_7

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MISO_FUNC          GPIO_PIN_FUNC_5
  #endif
#else
  #error "Invalid SPI5_MISO Pin Configuration!"
#endif

//   <o> SPI5_MOSI Pin <0=>Not Used <1=>PA10 <2=>PB8 <3=>PE6 <4=>PE14 <5=>PF9 <6=>PF11
#define RTE_SPI5_MOSI_PORT_ID           0
#if    (RTE_SPI5_MOSI_PORT_ID == 0)
  #define RTE_SPI5_MOSI                 0
#elif  (RTE_SPI5_MOSI_PORT_ID == 1)
  #define RTE_SPI5_MOSI                 1
  #define RTE_SPI5_MOSI_PORT            GPIO_PORT_A
  #define RTE_SPI5_MOSI_PIN             GPIO_PIN_10

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MOSI_PORT_ID == 2)
  #define RTE_SPI5_MOSI                 1
  #define RTE_SPI5_MOSI_PORT            GPIO_PORT_B
  #define RTE_SPI5_MOSI_PIN             GPIO_PIN_8

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MOSI_PORT_ID == 3)
  #define RTE_SPI5_MOSI                 1
  #define RTE_SPI5_MOSI_PORT            GPIO_PORT_E
  #define RTE_SPI5_MOSI_PIN             GPIO_PIN_6

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MOSI_PORT_ID == 4)
  #define RTE_SPI5_MOSI                 1
  #define RTE_SPI5_MOSI_PORT            GPIO_PORT_E
  #define RTE_SPI5_MOSI_PIN             GPIO_PIN_14

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MOSI_PORT_ID == 5)
  #define RTE_SPI5_MOSI                 1
  #define RTE_SPI5_MOSI_PORT            GPIO_PORT_F
  #define RTE_SPI5_MOSI_PIN             GPIO_PIN_9

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_MOSI_PORT_ID == 6)
  #define RTE_SPI5_MOSI                 1
  #define RTE_SPI5_MOSI_PORT            GPIO_PORT_F
  #define RTE_SPI5_MOSI_PIN             GPIO_PIN_11

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_MOSI_FUNC          GPIO_PIN_FUNC_5
  #endif
#else
  #error "Invalid SPI5_MOSI Pin Configuration!"
#endif

//   <o> SPI5_SCK Pin <0=>PB0 <1=>PE2 <2=>PE12 <3=>PF7 <4=>PH6
#define RTE_SPI5_SCK_PORT_ID            0
#if    (RTE_SPI5_SCK_PORT_ID == 0)
  #define RTE_SPI5_SCK_PORT             GPIO_PORT_B
  #define RTE_SPI5_SCK_PIN              GPIO_PIN_0

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_SCK_PORT_ID == 1)
  #define RTE_SPI5_SCK_PORT             GPIO_PORT_E
  #define RTE_SPI5_SCK_PIN              GPIO_PIN_2

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_SCK_PORT_ID == 2)
  #define RTE_SPI5_SCK_PORT             GPIO_PORT_E
  #define RTE_SPI5_SCK_PIN              GPIO_PIN_12

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_SCK_PORT_ID == 3)
  #define RTE_SPI5_SCK_PORT             GPIO_PORT_F
  #define RTE_SPI5_SCK_PIN              GPIO_PIN_7

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_SCK_PORT_ID == 4)
  #define RTE_SPI5_SCK_PORT             GPIO_PORT_H
  #define RTE_SPI5_SCK_PIN              GPIO_PIN_6

  #if (defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_SCK_FUNC           GPIO_PIN_FUNC_5
  #endif
#else
  #error "Invalid SPI5_SCK Pin Configuration!"
#endif

//   <o> SPI5_NSS Pin <0=>Not Used <1=>PB1 <2=>PE4 <3=>PE11 <4=>PF6 <5=>PH5
#define RTE_SPI5_NSS_PORT_ID            0
#if    (RTE_SPI5_NSS_PORT_ID == 0)
  #define RTE_SPI5_NSS                  0
#elif  (RTE_SPI5_NSS_PORT_ID == 1)
  #define RTE_SPI5_NSS                  1
  #define RTE_SPI5_NSS_PORT             GPIO_PORT_B
  #define RTE_SPI5_NSS_PIN              GPIO_PIN_1

  #if (defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_NSS_PORT_ID == 2)
  #define RTE_SPI5_NSS                  1
  #define RTE_SPI5_NSS_PORT             GPIO_PORT_E
  #define RTE_SPI5_NSS_PIN              GPIO_PIN_4

  #if (defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_NSS_PORT_ID == 3)
  #define RTE_SPI5_NSS                  1
  #define RTE_SPI5_NSS_PORT             GPIO_PORT_E
  #define RTE_SPI5_NSS_PIN              GPIO_PIN_11

  #if (defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_NSS_PORT_ID == 4)
  #define RTE_SPI5_NSS                  1
  #define RTE_SPI5_NSS_PORT             GPIO_PORT_F
  #define RTE_SPI5_NSS_PIN              GPIO_PIN_6

  #if (defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_5
  #endif
#elif  (RTE_SPI5_NSS_PORT_ID == 5)
  #define RTE_SPI5_NSS                  1
  #define RTE_SPI5_NSS_PORT             GPIO_PORT_H
  #define RTE_SPI5_NSS_PIN              GPIO_PIN_5

  #if (defined(STM32F413xx) || defined(STM32F423xx))
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_6
  #else
    #define RTE_SPI5_NSS_FUNC           GPIO_PIN_FUNC_5
  #endif
#else
  #error "Invalid SPI5_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <3=>3 <5=>5
//     <i>  Selects DMA Stream (only Stream 3 or 5 can be used)
//     <o3> Channel <2=>2 <7=>7
//     <i>  Selects DMA Channel (only Channel 2 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI5_RX_DMA                 0
#define RTE_SPI5_RX_DMA_NUMBER          2
#define RTE_SPI5_RX_DMA_STREAM          3
#define RTE_SPI5_RX_DMA_CHANNEL         2
#define RTE_SPI5_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <4=>4 <5=>5 <6=>6
//     <i>  Selects DMA Stream (only Stream 4 or 6 can be used)
//     <o3> Channel <2=>2 <5=>5 <7=>7
//     <i>  Selects DMA Channel (only Channel 2 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI5_TX_DMA                 0
#define RTE_SPI5_TX_DMA_NUMBER          2
#define RTE_SPI5_TX_DMA_STREAM          4
#define RTE_SPI5_TX_DMA_CHANNEL         2
#define RTE_SPI5_TX_DMA_PRIORITY        0

// </e>

// <e> SPI6 (Serial Peripheral Interface 6) [Driver_SPI6]
// <i> Configuration settings for Driver_SPI6 in component ::CMSIS Driver:SPI
#define RTE_SPI6                        0

//   <o> SPI6_MISO Pin <0=>Not Used <1=>PG12
#define RTE_SPI6_MISO_PORT_ID           0
#if    (RTE_SPI6_MISO_PORT_ID == 0)
  #define RTE_SPI6_MISO                 0
#elif  (RTE_SPI6_MISO_PORT_ID == 1)
  #define RTE_SPI6_MISO                 1
  #define RTE_SPI6_MISO_PORT            GPIO_PORT_G
  #define RTE_SPI6_MISO_PIN             GPIO_PIN_12
  #define RTE_SPI6_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_MISO Pin Configuration!"
#endif

//   <o> SPI6_MOSI Pin <0=>Not Used <1=>PG14
#define RTE_SPI6_MOSI_PORT_ID           0
#if    (RTE_SPI6_MOSI_PORT_ID == 0)
  #define RTE_SPI6_MOSI                 0
#elif  (RTE_SPI6_MOSI_PORT_ID == 1)
  #define RTE_SPI6_MOSI                 1
  #define RTE_SPI6_MOSI_PORT            GPIO_PORT_G
  #define RTE_SPI6_MOSI_PIN             GPIO_PIN_14
  #define RTE_SPI6_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_MOSI Pin Configuration!"
#endif

//   <o> SPI6_SCK Pin <0=>PG13
#define RTE_SPI6_SCK_PORT_ID            0
#if    (RTE_SPI6_SCK_PORT_ID == 0)
  #define RTE_SPI6_SCK_PORT             GPIO_PORT_G
  #define RTE_SPI6_SCK_PIN              GPIO_PIN_13
  #define RTE_SPI6_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_SCK Pin Configuration!"
#endif

//   <o> SPI6_NSS Pin <0=>Not Used <1=>PG8
#define RTE_SPI6_NSS_PORT_ID            0
#if    (RTE_SPI6_NSS_PORT_ID == 0)
  #define RTE_SPI6_NSS                  0
#elif  (RTE_SPI6_NSS_PORT_ID == 1)
  #define RTE_SPI6_NSS                  1
  #define RTE_SPI6_NSS_PORT             GPIO_PORT_G
  #define RTE_SPI6_NSS_PIN              GPIO_PIN_8
  #define RTE_SPI6_NSS_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <6=>6
//     <i>  Selects DMA Stream (only Stream 6 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI6_RX_DMA                 0
#define RTE_SPI6_RX_DMA_NUMBER          2
#define RTE_SPI6_RX_DMA_STREAM          6
#define RTE_SPI6_RX_DMA_CHANNEL         1
#define RTE_SPI6_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <5=>5
//     <i>  Selects DMA Stream (only Stream 5 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define RTE_SPI6_TX_DMA                 0
#define RTE_SPI6_TX_DMA_NUMBER          2
#define RTE_SPI6_TX_DMA_STREAM          5
#define RTE_SPI6_TX_DMA_CHANNEL         1
#define RTE_SPI6_TX_DMA_PRIORITY        0

// </e>

#endif /* DEVICE_CONFIG_H_ */

/* ----------------------------- End of file ---------------------------------*/
