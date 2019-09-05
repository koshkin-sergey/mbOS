/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for STMicroelectronics STM32F7xx
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __DEVICE_CONFIG_H
#define __DEVICE_CONFIG_H

// <h> Clock Configuration
//   <o> High-speed Internal Clock (Hz) <1-999999999>
#define HSI_CLK                         16000000
//   <o> High-speed External Clock (Hz) <1-999999999>
#define HSE_CLK                         8000000
//   <o> Low-speed Internal Clock (Hz) <1-999999999>
#define LSI_CLK                         32000
//   <o> Low-speed External Clock (Hz) <1-999999999>
#define LSE_CLK                         32768
// </h>

/* Interrupt Priority */
#define DEV_I2C_INT_PRIORITY           (1U)
#define DEV_I2S_INT_PRIORITY           (1U)
#define DEV_USART_INT_PRIORITY         (1U)
#define DEV_USART_DMA_INT_PRIORITY     (1U)
#define DEV_SPI_INT_PRIORITY           (1U)
#define DEV_SPI_DMA_INT_PRIORITY       (1U)
#define DEV_QSPI_INT_PRIORITY          (1U)
#define DEV_QSPI_DMA_INT_PRIORITY      (1U)
#define DEV_EXTI_INT_PRIORITY          (1U)
#define DEV_DAC_INT_PRIORITY           (1U)

// <e> USART1 (Universal synchronous asynchronous receiver transmitter) [Driver_USART1]
// <i> Configuration settings for Driver_USART1 in component ::CMSIS Driver:USART
#define DEV_USART1                      0

//   <o> USART1_TX Pin <0=>Not Used <1=>PA9 <2=>PB6 <3=>PB14
#define   DEV_USART1_TX_ID              1
#if      (DEV_USART1_TX_ID == 0)
  #define DEV_USART1_TX                 0
#elif    (DEV_USART1_TX_ID == 1)
  #define DEV_USART1_TX                 1
  #define DEV_USART1_TX_PORT            GPIO_PORT_A
  #define DEV_USART1_TX_PIN             GPIO_PIN_9
  #define DEV_USART1_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART1_TX_ID == 2)
  #define DEV_USART1_TX                 1
  #define DEV_USART1_TX_PORT            GPIO_PORT_B
  #define DEV_USART1_TX_PIN             GPIO_PIN_6
  #define DEV_USART1_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART1_TX_ID == 3)
  #define DEV_USART1_TX                 1
  #define DEV_USART1_TX_PORT            GPIO_PORT_B
  #define DEV_USART1_TX_PIN             GPIO_PIN_14
  #define DEV_USART1_TX_FUNC            GPIO_PIN_FUNC_4
#else
  #error "Invalid USART1_TX Pin Configuration!"
#endif

//   <o> USART1_RX Pin <0=>Not Used <1=>PA10 <2=>PB7 <3=>PB15
#define   DEV_USART1_RX_ID              1
#if      (DEV_USART1_RX_ID == 0)
  #define DEV_USART1_RX                 0
#elif    (DEV_USART1_RX_ID == 1)
  #define DEV_USART1_RX                 1
  #define DEV_USART1_RX_PORT            GPIO_PORT_A
  #define DEV_USART1_RX_PIN             GPIO_PIN_10
  #define DEV_USART1_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART1_RX_ID == 2)
  #define DEV_USART1_RX                 1
  #define DEV_USART1_RX_PORT            GPIO_PORT_B
  #define DEV_USART1_RX_PIN             GPIO_PIN_7
  #define DEV_USART1_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART1_RX_ID == 3)
  #define DEV_USART1_RX                 1
  #define DEV_USART1_RX_PORT            GPIO_PORT_B
  #define DEV_USART1_RX_PIN             GPIO_PIN_15
  #define DEV_USART1_RX_FUNC            GPIO_PIN_FUNC_4
#else
  #error "Invalid USART1_RX Pin Configuration!"
#endif

//   <o> USART1_CK Pin <0=>Not Used <1=>PA8
#define   DEV_USART1_CK_ID              0
#if      (DEV_USART1_CK_ID == 0)
  #define DEV_USART1_CK                 0
#elif    (DEV_USART1_CK_ID == 1)
  #define DEV_USART1_CK                 1
  #define DEV_USART1_CK_PORT            GPIO_PORT_A
  #define DEV_USART1_CK_PIN             GPIO_PIN_8
  #define DEV_USART1_CK_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_CK Pin Configuration!"
#endif

//   <o> USART1_CTS Pin <0=>Not Used <1=>PA11
#define   DEV_USART1_CTS_ID             0
#if      (DEV_USART1_CTS_ID == 0)
  #define DEV_USART1_CTS                0
#elif    (DEV_USART1_CTS_ID == 1)
  #define DEV_USART1_CTS                1
  #define DEV_USART1_CTS_PORT           GPIO_PORT_A
  #define DEV_USART1_CTS_PIN            GPIO_PIN_11
  #define DEV_USART1_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART1_CTS Pin Configuration!"
#endif

//   <o> USART1_RTS Pin <0=>Not Used <1=>PA12
#define   DEV_USART1_RTS_ID             0
#if      (DEV_USART1_RTS_ID == 0)
  #define DEV_USART1_RTS                0
#elif    (DEV_USART1_RTS_ID == 1)
  #define DEV_USART1_RTS                1
  #define DEV_USART1_RTS_PORT           GPIO_PORT_A
  #define DEV_USART1_RTS_PIN            GPIO_PIN_12
  #define DEV_USART1_RTS_FUNC           GPIO_PIN_FUNC_7
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
#define DEV_USART1_RX_DMA               1
#define DEV_USART1_RX_DMA_NUMBER        2
#define DEV_USART1_RX_DMA_STREAM        2
#define DEV_USART1_RX_DMA_CHANNEL       4
#define DEV_USART1_RX_DMA_PRIORITY      0

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
#define DEV_USART1_TX_DMA               1
#define DEV_USART1_TX_DMA_NUMBER        2
#define DEV_USART1_TX_DMA_STREAM        7
#define DEV_USART1_TX_DMA_CHANNEL       4
#define DEV_USART1_TX_DMA_PRIORITY      0

// </e> USART1 (Universal synchronous asynchronous receiver transmitter) [Driver_USART1]

// <e> USART2 (Universal synchronous asynchronous receiver transmitter) [Driver_USART2]
// <i> Configuration settings for Driver_USART2 in component ::CMSIS Driver:USART
#define DEV_USART2                      0

//   <o> USART2_TX Pin <0=>Not Used <1=>PA2 <2=>PD5
#define   DEV_USART2_TX_ID              0
#if      (DEV_USART2_TX_ID == 0)
  #define DEV_USART2_TX                 0
#elif    (DEV_USART2_TX_ID == 1)
  #define DEV_USART2_TX                 1
  #define DEV_USART2_TX_PORT            GPIO_PORT_A
  #define DEV_USART2_TX_PIN             GPIO_PIN_2
  #define DEV_USART2_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART2_TX_ID == 2)
  #define DEV_USART2_TX                 1
  #define DEV_USART2_TX_PORT            GPIO_PORT_D
  #define DEV_USART2_TX_PIN             GPIO_PIN_5
  #define DEV_USART2_TX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_TX Pin Configuration!"
#endif

//   <o> USART2_RX Pin <0=>Not Used <1=>PA3 <2=>PD6
#define   DEV_USART2_RX_ID              0
#if      (DEV_USART2_RX_ID == 0)
  #define DEV_USART2_RX                 0
#elif    (DEV_USART2_RX_ID == 1)
  #define DEV_USART2_RX                 1
  #define DEV_USART2_RX_PORT            GPIO_PORT_A
  #define DEV_USART2_RX_PIN             GPIO_PIN_3
  #define DEV_USART2_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART2_RX_ID == 2)
  #define DEV_USART2_RX                 1
  #define DEV_USART2_RX_PORT            GPIO_PORT_D
  #define DEV_USART2_RX_PIN             GPIO_PIN_6
  #define DEV_USART2_RX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_RX Pin Configuration!"
#endif

//   <o> USART2_CK Pin <0=>Not Used <1=>PA4 <2=>PD7
#define   DEV_USART2_CK_ID              0
#if      (DEV_USART2_CK_ID == 0)
  #define DEV_USART2_CK                 0
#elif    (DEV_USART2_CK_ID == 1)
  #define DEV_USART2_CK                 1
  #define DEV_USART2_CK_PORT            GPIO_PORT_A
  #define DEV_USART2_CK_PIN             GPIO_PIN_4
  #define DEV_USART2_CK_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART2_CK_ID == 2)
  #define DEV_USART2_CK                 1
  #define DEV_USART2_CK_PORT            GPIO_PORT_D
  #define DEV_USART2_CK_PIN             GPIO_PIN_7
  #define DEV_USART2_CK_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_CK Pin Configuration!"
#endif

//   <o> USART2_CTS Pin <0=>Not Used <1=>PA0 <2=>PD3
#define   DEV_USART2_CTS_ID             0
#if      (DEV_USART2_CTS_ID == 0)
  #define DEV_USART2_CTS                0
#elif    (DEV_USART2_CTS_ID == 1)
  #define DEV_USART2_CTS                1
  #define DEV_USART2_CTS_PORT           GPIO_PORT_A
  #define DEV_USART2_CTS_PIN            GPIO_PIN_0
  #define DEV_USART2_CTS_FUNC           GPIO_PIN_FUNC_7
#elif    (DEV_USART2_CTS_ID == 2)
  #define DEV_USART2_CTS                1
  #define DEV_USART2_CTS_PORT           GPIO_PORT_D
  #define DEV_USART2_CTS_PIN            GPIO_PIN_3
  #define DEV_USART2_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_CTS Pin Configuration!"
#endif

//   <o> USART2_RTS Pin <0=>Not Used <1=>PA1 <2=>PD4
#define   DEV_USART2_RTS_ID             0
#if      (DEV_USART2_RTS_ID == 0)
  #define DEV_USART2_RTS                0
#elif    (DEV_USART2_RTS_ID == 1)
  #define DEV_USART2_RTS                1
  #define DEV_USART2_RTS_PORT           GPIO_PORT_A
  #define DEV_USART2_RTS_PIN            GPIO_PIN_1
  #define DEV_USART2_RTS_FUNC           GPIO_PIN_FUNC_7
#elif    (DEV_USART2_RTS_ID == 2)
  #define DEV_USART2_RTS                1
  #define DEV_USART2_RTS_PORT           GPIO_PORT_D
  #define DEV_USART2_RTS_PIN            GPIO_PIN_4
  #define DEV_USART2_RTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART2_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <5=>5
//     <i>  Selects DMA Stream (only Stream 5 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_USART2_RX_DMA               0
#define DEV_USART2_RX_DMA_NUMBER        1
#define DEV_USART2_RX_DMA_STREAM        5
#define DEV_USART2_RX_DMA_CHANNEL       4
#define DEV_USART2_RX_DMA_PRIORITY      0

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
#define DEV_USART2_TX_DMA               0
#define DEV_USART2_TX_DMA_NUMBER        1
#define DEV_USART2_TX_DMA_STREAM        6
#define DEV_USART2_TX_DMA_CHANNEL       4
#define DEV_USART2_TX_DMA_PRIORITY      0

// </e> USART2 (Universal synchronous asynchronous receiver transmitter) [Driver_USART2]

// <e> USART3 (Universal synchronous asynchronous receiver transmitter) [Driver_USART3]
// <i> Configuration settings for Driver_USART3 in component ::CMSIS Driver:USART
#define DEV_USART3                      0

//   <o> USART3_TX Pin <0=>Not Used <1=>PB10 <2=>PC10 <3=>PD8
#define   DEV_USART3_TX_ID              0
#if      (DEV_USART3_TX_ID == 0)
  #define DEV_USART3_TX                 0
#elif    (DEV_USART3_TX_ID == 1)
  #define DEV_USART3_TX                 1
  #define DEV_USART3_TX_PORT            GPIO_PORT_B
  #define DEV_USART3_TX_PIN             GPIO_PIN_10
  #define DEV_USART3_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART3_TX_ID == 2)
  #define DEV_USART3_TX                 1
  #define DEV_USART3_TX_PORT            GPIO_PORT_C
  #define DEV_USART3_TX_PIN             GPIO_PIN_10
  #define DEV_USART3_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART3_TX_ID == 3)
  #define DEV_USART3_TX                 1
  #define DEV_USART3_TX_PORT            GPIO_PORT_D
  #define DEV_USART3_TX_PIN             GPIO_PIN_8
  #define DEV_USART3_TX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_TX Pin Configuration!"
#endif

//   <o> USART3_RX Pin <0=>Not Used <1=>PB11 <2=>PC11 <3=>PD9
#define   DEV_USART3_RX_ID              0
#if      (DEV_USART3_RX_ID == 0)
  #define DEV_USART3_RX                 0
#elif    (DEV_USART3_RX_ID == 1)
  #define DEV_USART3_RX                 1
  #define DEV_USART3_RX_PORT            GPIO_PORT_B
  #define DEV_USART3_RX_PIN             GPIO_PIN_11
  #define DEV_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART3_RX_ID == 2)
  #define DEV_USART3_RX                 1
  #define DEV_USART3_RX_PORT            GPIO_PORT_C
  #define DEV_USART3_RX_PIN             GPIO_PIN_11
  #define DEV_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART3_RX_ID == 3)
  #define DEV_USART3_RX                 1
  #define DEV_USART3_RX_PORT            GPIO_PORT_D
  #define DEV_USART3_RX_PIN             GPIO_PIN_9
  #define DEV_USART3_RX_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_RX Pin Configuration!"
#endif

//   <o> USART3_CK Pin <0=>Not Used <1=>PB12 <2=>PC12 <3=>PD10
#define   DEV_USART3_CK_ID              0
#if      (DEV_USART3_CK_ID == 0)
  #define DEV_USART3_CK                 0
#elif    (DEV_USART3_CK_ID == 1)
  #define DEV_USART3_CK                 1
  #define DEV_USART3_CK_PORT            GPIO_PORT_B
  #define DEV_USART3_CK_PIN             GPIO_PIN_12
  #define DEV_USART3_CK_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART3_CK_ID == 2)
  #define DEV_USART3_CK                 1
  #define DEV_USART3_CK_PORT            GPIO_PORT_C
  #define DEV_USART3_CK_PIN             GPIO_PIN_12
  #define DEV_USART3_CK_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_USART3_CK_ID == 3)
  #define DEV_USART3_CK                 1
  #define DEV_USART3_CK_PORT            GPIO_PORT_D
  #define DEV_USART3_CK_PIN             GPIO_PIN_10
  #define DEV_USART3_CK_FUNC            GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_CK Pin Configuration!"
#endif

//   <o> USART3_CTS Pin <0=>Not Used <1=>PB13 <2=>PD11
#define   DEV_USART3_CTS_ID             0
#if      (DEV_USART3_CTS_ID == 0)
  #define DEV_USART3_CTS                0
#elif    (DEV_USART3_CTS_ID == 1)
  #define DEV_USART3_CTS                1
  #define DEV_USART3_CTS_PORT           GPIO_PORT_B
  #define DEV_USART3_CTS_PIN            GPIO_PIN_13
  #define DEV_USART3_CTS_FUNC           GPIO_PIN_FUNC_7
#elif    (DEV_USART3_CTS_ID == 2)
  #define DEV_USART3_CTS                1
  #define DEV_USART3_CTS_PORT           GPIO_PORT_D
  #define DEV_USART3_CTS_PIN            GPIO_PIN_11
  #define DEV_USART3_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_CTS Pin Configuration!"
#endif

//   <o> USART3_RTS Pin <0=>Not Used <1=>PB14 <2=>PD12
#define   DEV_USART3_RTS_ID             0
#if      (DEV_USART3_RTS_ID == 0)
  #define DEV_USART3_RTS                0
#elif    (DEV_USART3_RTS_ID == 1)
  #define DEV_USART3_RTS                1
  #define DEV_USART3_RTS_PORT           GPIO_PORT_B
  #define DEV_USART3_RTS_PIN            GPIO_PIN_14
  #define DEV_USART3_RTS_FUNC           GPIO_PIN_FUNC_7
#elif    (DEV_USART3_RTS_ID == 2)
  #define DEV_USART3_RTS                1
  #define DEV_USART3_RTS_PORT           GPIO_PORT_D
  #define DEV_USART3_RTS_PIN            GPIO_PIN_12
  #define DEV_USART3_RTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid USART3_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1
//     <i>  Selects DMA Stream (only Stream 1 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_USART3_RX_DMA               0
#define DEV_USART3_RX_DMA_NUMBER        1
#define DEV_USART3_RX_DMA_STREAM        1
#define DEV_USART3_RX_DMA_CHANNEL       4
#define DEV_USART3_RX_DMA_PRIORITY      0

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
#define DEV_USART3_TX_DMA               0
#define DEV_USART3_TX_DMA_NUMBER        1
#define DEV_USART3_TX_DMA_STREAM        3
#define DEV_USART3_TX_DMA_CHANNEL       4
#define DEV_USART3_TX_DMA_PRIORITY      0

// </e> USART3 (Universal synchronous asynchronous receiver transmitter) [Driver_USART3]

// <e> UART4 (Universal asynchronous receiver transmitter) [Driver_USART4]
// <i> Configuration settings for Driver_USART4 in component ::CMSIS Driver:USART
#define DEV_UART4                      0

//   <o> UART4_TX Pin <0=>Not Used <1=>PA0 <2=>PA12 <3=>PC10 <4=>PD1 <5=>PH13
#define   DEV_UART4_TX_ID              0
#if      (DEV_UART4_TX_ID == 0)
  #define DEV_UART4_TX                 0
#elif    (DEV_UART4_TX_ID == 1)
  #define DEV_UART4_TX                 1
  #define DEV_UART4_TX_PORT            GPIO_PORT_A
  #define DEV_UART4_TX_PIN             GPIO_PIN_0
  #define DEV_UART4_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_TX_ID == 2)
  #define DEV_UART4_TX                 1
  #define DEV_UART4_TX_PORT            GPIO_PORT_A
  #define DEV_UART4_TX_PIN             GPIO_PIN_12
  #define DEV_UART4_TX_FUNC            GPIO_PIN_FUNC_6
#elif    (DEV_UART4_TX_ID == 3)
  #define DEV_UART4_TX                 1
  #define DEV_UART4_TX_PORT            GPIO_PORT_C
  #define DEV_UART4_TX_PIN             GPIO_PIN_10
  #define DEV_UART4_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_TX_ID == 4)
  #define DEV_UART4_TX                 1
  #define DEV_UART4_TX_PORT            GPIO_PORT_D
  #define DEV_UART4_TX_PIN             GPIO_PIN_1
  #define DEV_UART4_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_TX_ID == 5)
  #define DEV_UART4_TX                 1
  #define DEV_UART4_TX_PORT            GPIO_PORT_H
  #define DEV_UART4_TX_PIN             GPIO_PIN_13
  #define DEV_UART4_TX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART4_TX Pin Configuration!"
#endif

//   <o> UART4_RX Pin <0=>Not Used <1=>PA1 <2=>PA11 <3=>PC11 <4=>PD0 <5=>PH14 <6=>PI9
#define   DEV_UART4_RX_ID              0
#if      (DEV_UART4_RX_ID == 0)
  #define DEV_UART4_RX                 0
#elif    (DEV_UART4_RX_ID == 1)
  #define DEV_UART4_RX                 1
  #define DEV_UART4_RX_PORT            GPIO_PORT_A
  #define DEV_UART4_RX_PIN             GPIO_PIN_1
  #define DEV_UART4_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_RX_ID == 2)
  #define DEV_UART4_RX                 1
  #define DEV_UART4_RX_PORT            GPIO_PORT_A
  #define DEV_UART4_RX_PIN             GPIO_PIN_11
  #define DEV_UART4_RX_FUNC            GPIO_PIN_FUNC_6
#elif    (DEV_UART4_RX_ID == 3)
  #define DEV_UART4_RX                 1
  #define DEV_UART4_RX_PORT            GPIO_PORT_C
  #define DEV_UART4_RX_PIN             GPIO_PIN_11
  #define DEV_UART4_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_RX_ID == 4)
  #define DEV_UART4_RX                 1
  #define DEV_UART4_RX_PORT            GPIO_PORT_D
  #define DEV_UART4_RX_PIN             GPIO_PIN_0
  #define DEV_UART4_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_RX_ID == 5)
  #define DEV_UART4_RX                 1
  #define DEV_UART4_RX_PORT            GPIO_PORT_H
  #define DEV_UART4_RX_PIN             GPIO_PIN_14
  #define DEV_UART4_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART4_RX_ID == 6)
  #define DEV_UART4_RX                 1
  #define DEV_UART4_RX_PORT            GPIO_PORT_I
  #define DEV_UART4_RX_PIN             GPIO_PIN_9
  #define DEV_UART4_RX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART4_RX Pin Configuration!"
#endif

//   <o> UART4_CTS Pin <0=>Not Used <1=>PB0 <2=>PB15
#define   DEV_UART4_CTS_ID             0
#if      (DEV_UART4_CTS_ID == 0)
  #define DEV_UART4_CTS                0
#elif    (DEV_UART4_CTS_ID == 1)
  #define DEV_UART4_CTS                1
  #define DEV_UART4_CTS_PORT           GPIO_PORT_B
  #define DEV_UART4_CTS_PIN            GPIO_PIN_0
  #define DEV_UART4_CTS_FUNC           GPIO_PIN_FUNC_8
#elif    (DEV_UART4_CTS_ID == 2)
  #define DEV_UART4_CTS                1
  #define DEV_UART4_CTS_PORT           GPIO_PORT_B
  #define DEV_UART4_CTS_PIN            GPIO_PIN_15
  #define DEV_UART4_CTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid UART4_CTS Pin Configuration!"
#endif

//   <o> UART4_RTS Pin <0=>Not Used <1=>PA15 <2=>PB14
#define   DEV_UART4_RTS_ID             0
#if      (DEV_UART4_RTS_ID == 0)
  #define DEV_UART4_RTS                0
#elif    (DEV_UART4_RTS_ID == 1)
  #define DEV_UART4_RTS                1
  #define DEV_UART4_RTS_PORT           GPIO_PORT_A
  #define DEV_UART4_RTS_PIN            GPIO_PIN_15
  #define DEV_UART4_RTS_FUNC           GPIO_PIN_FUNC_8
#elif    (DEV_UART4_RTS_ID == 2)
  #define DEV_UART4_RTS                1
  #define DEV_UART4_RTS_PORT           GPIO_PORT_B
  #define DEV_UART4_RTS_PIN            GPIO_PIN_14
  #define DEV_UART4_RTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid UART4_RTS Pin Configuration!"
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
#define DEV_UART4_RX_DMA               0
#define DEV_UART4_RX_DMA_NUMBER        1
#define DEV_UART4_RX_DMA_STREAM        2
#define DEV_UART4_RX_DMA_CHANNEL       4
#define DEV_UART4_RX_DMA_PRIORITY      0

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
#define DEV_UART4_TX_DMA               0
#define DEV_UART4_TX_DMA_NUMBER        1
#define DEV_UART4_TX_DMA_STREAM        4
#define DEV_UART4_TX_DMA_CHANNEL       4
#define DEV_UART4_TX_DMA_PRIORITY      0

// </e> UART4 (Universal asynchronous receiver transmitter) [Driver_USART4]

// <e> UART5 (Universal asynchronous receiver transmitter) [Driver_USART5]
// <i> Configuration settings for Driver_USART5 in component ::CMSIS Driver:USART
#define DEV_UART5                      0

//   <o> UART5_TX Pin <0=>Not Used <1=>PB6 <2=>PB9 <3=>PB13 <4=>PC12
#define   DEV_UART5_TX_ID              0
#if      (DEV_UART5_TX_ID == 0)
  #define DEV_UART5_TX                 0
#elif    (DEV_UART5_TX_ID == 1)
  #define DEV_UART5_TX                 1
  #define DEV_UART5_TX_PORT            GPIO_PORT_B
  #define DEV_UART5_TX_PIN             GPIO_PIN_6
  #define DEV_UART5_TX_FUNC            GPIO_PIN_FUNC_1
#elif    (DEV_UART5_TX_ID == 2)
  #define DEV_UART5_TX                 1
  #define DEV_UART5_TX_PORT            GPIO_PORT_B
  #define DEV_UART5_TX_PIN             GPIO_PIN_9
  #define DEV_UART5_TX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_UART5_TX_ID == 3)
  #define DEV_UART5_TX                 1
  #define DEV_UART5_TX_PORT            GPIO_PORT_B
  #define DEV_UART5_TX_PIN             GPIO_PIN_13
  #define DEV_UART5_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART5_TX_ID == 4)
  #define DEV_UART5_TX                 1
  #define DEV_UART5_TX_PORT            GPIO_PORT_C
  #define DEV_UART5_TX_PIN             GPIO_PIN_12
  #define DEV_UART5_TX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART5_TX Pin Configuration!"
#endif

//   <o> UART5_RX Pin <0=>Not Used <1=>PB5 <2=>PB8 <3=>PB12 <4=>PD2
#define   DEV_UART5_RX_ID              0
#if      (DEV_UART5_RX_ID == 0)
  #define DEV_UART5_RX                 0
#elif    (DEV_UART5_RX_ID == 1)
  #define DEV_UART5_RX                 1
  #define DEV_UART5_RX_PORT            GPIO_PORT_B
  #define DEV_UART5_RX_PIN             GPIO_PIN_5
  #define DEV_UART5_RX_FUNC            GPIO_PIN_FUNC_1
#elif    (DEV_UART5_RX_ID == 2)
  #define DEV_UART5_RX                 1
  #define DEV_UART5_RX_PORT            GPIO_PORT_B
  #define DEV_UART5_RX_PIN             GPIO_PIN_8
  #define DEV_UART5_RX_FUNC            GPIO_PIN_FUNC_7
#elif    (DEV_UART5_RX_ID == 3)
  #define DEV_UART5_RX                 1
  #define DEV_UART5_RX_PORT            GPIO_PORT_B
  #define DEV_UART5_RX_PIN             GPIO_PIN_12
  #define DEV_UART5_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART5_RX_ID == 4)
  #define DEV_UART5_RX                 1
  #define DEV_UART5_RX_PORT            GPIO_PORT_D
  #define DEV_UART5_RX_PIN             GPIO_PIN_2
  #define DEV_UART5_RX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART5_RX Pin Configuration!"
#endif

//   <o> UART5_CTS Pin <0=>Not Used <1=>PC9
#define   DEV_UART5_CTS_ID             0
#if      (DEV_UART5_CTS_ID == 0)
  #define DEV_UART5_CTS                0
#elif    (DEV_UART5_CTS_ID == 1)
  #define DEV_UART5_CTS                1
  #define DEV_UART5_CTS_PORT           GPIO_PORT_C
  #define DEV_UART5_CTS_PIN            GPIO_PIN_9
  #define DEV_UART5_CTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid UART5_CTS Pin Configuration!"
#endif

//   <o> UART5_RTS Pin <0=>Not Used <1=>PC8
#define   DEV_UART5_RTS_ID             0
#if      (DEV_UART5_RTS_ID == 0)
  #define DEV_UART5_RTS                0
#elif    (DEV_UART5_RTS_ID == 1)
  #define DEV_UART5_RTS                1
  #define DEV_UART5_RTS_PORT           GPIO_PORT_C
  #define DEV_UART5_RTS_PIN            GPIO_PIN_8
  #define DEV_UART5_RTS_FUNC           GPIO_PIN_FUNC_7
#else
  #error "Invalid UART5_RTS Pin Configuration!"
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
#define DEV_UART5_RX_DMA               0
#define DEV_UART5_RX_DMA_NUMBER        1
#define DEV_UART5_RX_DMA_STREAM        0
#define DEV_UART5_RX_DMA_CHANNEL       4
#define DEV_UART5_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_UART5_TX_DMA               0
#define DEV_UART5_TX_DMA_NUMBER        1
#define DEV_UART5_TX_DMA_STREAM        7
#define DEV_UART5_TX_DMA_CHANNEL       4
#define DEV_UART5_TX_DMA_PRIORITY      0

// </e> UART5 (Universal asynchronous receiver transmitter) [Driver_USART5]

// <e> USART6 (Universal synchronous asynchronous receiver transmitter) [Driver_USART6]
// <i> Configuration settings for Driver_USART6 in component ::CMSIS Driver:USART
#define DEV_USART6                      0

//   <o> USART6_TX Pin <0=>Not Used <1=>PC6 <2=>PG14
#define   DEV_USART6_TX_ID              0
#if      (DEV_USART6_TX_ID == 0)
  #define DEV_USART6_TX                 0
#elif    (DEV_USART6_TX_ID == 1)
  #define DEV_USART6_TX                 1
  #define DEV_USART6_TX_PORT            GPIO_PORT_C
  #define DEV_USART6_TX_PIN             GPIO_PIN_6
  #define DEV_USART6_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_USART6_TX_ID == 2)
  #define DEV_USART6_TX                 1
  #define DEV_USART6_TX_PORT            GPIO_PORT_G
  #define DEV_USART6_TX_PIN             GPIO_PIN_14
  #define DEV_USART6_TX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_TX Pin Configuration!"
#endif

//   <o> USART6_RX Pin <0=>Not Used <1=>PC7 <2=>PG9
#define   DEV_USART6_RX_ID              0
#if      (DEV_USART6_RX_ID == 0)
  #define DEV_USART6_RX                 0
#elif    (DEV_USART6_RX_ID == 1)
  #define DEV_USART6_RX                 1
  #define DEV_USART6_RX_PORT            GPIO_PORT_C
  #define DEV_USART6_RX_PIN             GPIO_PIN_7
  #define DEV_USART6_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_USART6_RX_ID == 2)
  #define DEV_USART6_RX                 1
  #define DEV_USART6_RX_PORT            GPIO_PORT_G
  #define DEV_USART6_RX_PIN             GPIO_PIN_9
  #define DEV_USART6_RX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_RX Pin Configuration!"
#endif

//   <o> USART6_CK Pin <0=>Not Used <1=>PC8 <2=>PG7
#define   DEV_USART6_CK_ID              0
#if      (DEV_USART6_CK_ID == 0)
  #define DEV_USART6_CK                 0
#elif    (DEV_USART6_CK_ID == 1)
  #define DEV_USART6_CK                 1
  #define DEV_USART6_CK_PORT            GPIO_PORT_C
  #define DEV_USART6_CK_PIN             GPIO_PIN_8
  #define DEV_USART6_CK_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_USART6_CK_ID == 2)
  #define DEV_USART6_CK                 1
  #define DEV_USART6_CK_PORT            GPIO_PORT_G
  #define DEV_USART6_CK_PIN             GPIO_PIN_7
  #define DEV_USART6_CK_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_CK Pin Configuration!"
#endif

//   <o> USART6_CTS Pin <0=>Not Used <1=>PG13 <2=>PG15
#define   DEV_USART6_CTS_ID             0
#if      (DEV_USART6_CTS_ID == 0)
  #define DEV_USART6_CTS                0
#elif    (DEV_USART6_CTS_ID == 1)
  #define DEV_USART6_CTS                1
  #define DEV_USART6_CTS_PORT           GPIO_PORT_G
  #define DEV_USART6_CTS_PIN            GPIO_PIN_13
  #define DEV_USART6_CTS_FUNC           GPIO_PIN_FUNC_8
#elif    (DEV_USART6_CTS_ID == 2)
  #define DEV_USART6_CTS                1
  #define DEV_USART6_CTS_PORT           GPIO_PORT_G
  #define DEV_USART6_CTS_PIN            GPIO_PIN_15
  #define DEV_USART6_CTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid USART6_CTS Pin Configuration!"
#endif

//   <o> USART6_RTS Pin <0=>Not Used <1=>PG8 <2=>PG12
#define   DEV_USART6_RTS_ID             0
#if      (DEV_USART6_RTS_ID == 0)
  #define DEV_USART6_RTS                0
#elif    (DEV_USART6_RTS_ID == 1)
  #define DEV_USART6_RTS                1
  #define DEV_USART6_RTS_PORT           GPIO_PORT_G
  #define DEV_USART6_RTS_PIN            GPIO_PIN_8
  #define DEV_USART6_RTS_FUNC           GPIO_PIN_FUNC_8
#elif    (DEV_USART6_RTS_ID == 2)
  #define DEV_USART6_RTS                1
  #define DEV_USART6_RTS_PORT           GPIO_PORT_G
  #define DEV_USART6_RTS_PIN            GPIO_PIN_12
  #define DEV_USART6_RTS_FUNC           GPIO_PIN_FUNC_8
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
#define DEV_USART6_RX_DMA               0
#define DEV_USART6_RX_DMA_NUMBER        2
#define DEV_USART6_RX_DMA_STREAM        1
#define DEV_USART6_RX_DMA_CHANNEL       5
#define DEV_USART6_RX_DMA_PRIORITY      0

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
#define DEV_USART6_TX_DMA               0
#define DEV_USART6_TX_DMA_NUMBER        2
#define DEV_USART6_TX_DMA_STREAM        6
#define DEV_USART6_TX_DMA_CHANNEL       5
#define DEV_USART6_TX_DMA_PRIORITY      0

// </e> USART6 (Universal synchronous asynchronous receiver transmitter) [Driver_USART6]

// <e> UART7 (Universal asynchronous receiver transmitter) [Driver_USART7]
// <i> Configuration settings for Driver_USART7 in component ::CMSIS Driver:USART
#define DEV_UART7                      0

//   <o> UART7_TX Pin <0=>Not Used <1=>PA15 <2=>PB4 <3=>PE8 <4=>PF7
#define   DEV_UART7_TX_ID              0
#if      (DEV_UART7_TX_ID == 0)
  #define DEV_UART7_TX                 0
#elif    (DEV_UART7_TX_ID == 1)
  #define DEV_UART7_TX                 1
  #define DEV_UART7_TX_PORT            GPIO_PORT_A
  #define DEV_UART7_TX_PIN             GPIO_PIN_15
  #define DEV_UART7_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART7_TX_ID == 2)
  #define DEV_UART7_TX                 1
  #define DEV_UART7_TX_PORT            GPIO_PORT_B
  #define DEV_UART7_TX_PIN             GPIO_PIN_4
  #define DEV_UART7_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART7_TX_ID == 3)
  #define DEV_UART7_TX                 1
  #define DEV_UART7_TX_PORT            GPIO_PORT_E
  #define DEV_UART7_TX_PIN             GPIO_PIN_8
  #define DEV_UART7_TX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART7_TX_ID == 4)
  #define DEV_UART7_TX                 1
  #define DEV_UART7_TX_PORT            GPIO_PORT_F
  #define DEV_UART7_TX_PIN             GPIO_PIN_7
  #define DEV_UART7_TX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART7_TX Pin Configuration!"
#endif

//   <o> UART7_RX Pin <0=>Not Used <1=>PA8 <2=>PB3 <3=>PE7 <4=>PF6
#define   DEV_UART7_RX_ID              0
#if      (DEV_UART7_RX_ID == 0)
  #define DEV_UART7_RX                 0
#elif    (DEV_UART7_RX_ID == 1)
  #define DEV_UART7_RX                 1
  #define DEV_UART7_RX_PORT            GPIO_PORT_A
  #define DEV_UART7_RX_PIN             GPIO_PIN_8
  #define DEV_UART7_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART7_RX_ID == 2)
  #define DEV_UART7_RX                 1
  #define DEV_UART7_RX_PORT            GPIO_PORT_B
  #define DEV_UART7_RX_PIN             GPIO_PIN_3
  #define DEV_UART7_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART7_RX_ID == 3)
  #define DEV_UART7_RX                 1
  #define DEV_UART7_RX_PORT            GPIO_PORT_E
  #define DEV_UART7_RX_PIN             GPIO_PIN_7
  #define DEV_UART7_RX_FUNC            GPIO_PIN_FUNC_8
#elif    (DEV_UART7_RX_ID == 4)
  #define DEV_UART7_RX                 1
  #define DEV_UART7_RX_PORT            GPIO_PORT_F
  #define DEV_UART7_RX_PIN             GPIO_PIN_6
  #define DEV_UART7_RX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART7_RX Pin Configuration!"
#endif

//   <o> UART7_CTS Pin <0=>Not Used <1=>PE10 <2=>PF9
#define   DEV_UART7_CTS_ID             0
#if      (DEV_UART7_CTS_ID == 0)
  #define DEV_UART7_CTS                0
#elif    (DEV_UART7_CTS_ID == 1)
  #define DEV_UART7_CTS                1
  #define DEV_UART7_CTS_PORT           GPIO_PORT_E
  #define DEV_UART7_CTS_PIN            GPIO_PIN_10
  #define DEV_UART7_CTS_FUNC           GPIO_PIN_FUNC_8
#elif    (DEV_UART7_CTS_ID == 2)
  #define DEV_UART7_CTS                1
  #define DEV_UART7_CTS_PORT           GPIO_PORT_F
  #define DEV_UART7_CTS_PIN            GPIO_PIN_9
  #define DEV_UART7_CTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid UART7_CTS Pin Configuration!"
#endif

//   <o> UART7_RTS Pin <0=>Not Used <1=>PE9 <2=>PF8
#define   DEV_UART7_RTS_ID             0
#if      (DEV_UART7_RTS_ID == 0)
  #define DEV_UART7_RTS                0
#elif    (DEV_UART7_RTS_ID == 1)
  #define DEV_UART7_RTS                1
  #define DEV_UART7_RTS_PORT           GPIO_PORT_E
  #define DEV_UART7_RTS_PIN            GPIO_PIN_9
  #define DEV_UART7_RTS_FUNC           GPIO_PIN_FUNC_8
#elif    (DEV_UART7_RTS_ID == 2)
  #define DEV_UART7_RTS                1
  #define DEV_UART7_RTS_PORT           GPIO_PORT_F
  #define DEV_UART7_RTS_PIN            GPIO_PIN_8
  #define DEV_UART7_RTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid UART7_RTS Pin Configuration!"
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
#define DEV_UART7_RX_DMA               0
#define DEV_UART7_RX_DMA_NUMBER        1
#define DEV_UART7_RX_DMA_STREAM        3
#define DEV_UART7_RX_DMA_CHANNEL       5
#define DEV_UART7_RX_DMA_PRIORITY      0

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
#define DEV_UART7_TX_DMA               0
#define DEV_UART7_TX_DMA_NUMBER        1
#define DEV_UART7_TX_DMA_STREAM        1
#define DEV_UART7_TX_DMA_CHANNEL       5
#define DEV_UART7_TX_DMA_PRIORITY      0

// </e> UART7 (Universal asynchronous receiver transmitter) [Driver_USART7]

// <e> UART8 (Universal asynchronous receiver transmitter) [Driver_USART8]
// <i> Configuration settings for Driver_USART8 in component ::CMSIS Driver:USART
#define DEV_UART8                      0

//   <o> UART8_TX Pin <0=>Not Used <1=>PE1
#define   DEV_UART8_TX_ID              0
#if      (DEV_UART8_TX_ID == 0)
  #define DEV_UART8_TX                 0
#elif    (DEV_UART8_TX_ID == 1)
  #define DEV_UART8_TX                 1
  #define DEV_UART8_TX_PORT            GPIO_PORT_E
  #define DEV_UART8_TX_PIN             GPIO_PIN_1
  #define DEV_UART8_TX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART8_TX Pin Configuration!"
#endif

//   <o> UART8_RX Pin <0=>Not Used <1=>PE0
#define   DEV_UART8_RX_ID              0
#if      (DEV_UART8_RX_ID == 0)
  #define DEV_UART8_RX                 0
#elif    (DEV_UART8_RX_ID == 1)
  #define DEV_UART8_RX                 1
  #define DEV_UART8_RX_PORT            GPIO_PORT_E
  #define DEV_UART8_RX_PIN             GPIO_PIN_0
  #define DEV_UART8_RX_FUNC            GPIO_PIN_FUNC_8
#else
  #error "Invalid UART8_RX Pin Configuration!"
#endif

//   <o> UART8_CTS Pin <0=>Not Used <1=>PD14
#define   DEV_UART8_CTS_ID             0
#if      (DEV_UART8_CTS_ID == 0)
  #define DEV_UART8_CTS                0
#elif    (DEV_UART8_CTS_ID == 1)
  #define DEV_UART8_CTS                1
  #define DEV_UART8_CTS_PORT           GPIO_PORT_D
  #define DEV_UART8_CTS_PIN            GPIO_PIN_14
  #define DEV_UART8_CTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid UART8_CTS Pin Configuration!"
#endif

//   <o> UART8_RTS Pin <0=>Not Used <1=>PD15
#define   DEV_UART8_RTS_ID             0
#if      (DEV_UART8_RTS_ID == 0)
  #define DEV_UART8_RTS                0
#elif    (DEV_UART8_RTS_ID == 1)
  #define DEV_UART8_RTS                1
  #define DEV_UART8_RTS_PORT           GPIO_PORT_D
  #define DEV_UART8_RTS_PIN            GPIO_PIN_15
  #define DEV_UART8_RTS_FUNC           GPIO_PIN_FUNC_8
#else
  #error "Invalid UART8_RTS Pin Configuration!"
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
#define DEV_UART8_RX_DMA               0
#define DEV_UART8_RX_DMA_NUMBER        1
#define DEV_UART8_RX_DMA_STREAM        6
#define DEV_UART8_RX_DMA_CHANNEL       5
#define DEV_UART8_RX_DMA_PRIORITY      0

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
#define DEV_UART8_TX_DMA               0
#define DEV_UART8_TX_DMA_NUMBER        1
#define DEV_UART8_TX_DMA_STREAM        0
#define DEV_UART8_TX_DMA_CHANNEL       5
#define DEV_UART8_TX_DMA_PRIORITY      0

// </e> UART8 (Universal asynchronous receiver transmitter) [Driver_USART8]


// <e> SPI1 (Serial Peripheral Interface 1) [Driver_SPI1]
// <i> Configuration settings for Driver_SPI1 in component ::CMSIS Driver:SPI
#define DEV_SPI1                        0

//   <o> SPI1_MISO Pin <0=>Not Used <1=>PA6 <2=>PB4 <3=>PG9
#define DEV_SPI1_MISO_PORT_ID           0
#if    (DEV_SPI1_MISO_PORT_ID == 0)
  #define DEV_SPI1_MISO                 0
#elif  (DEV_SPI1_MISO_PORT_ID == 1)
  #define DEV_SPI1_MISO                 1
  #define DEV_SPI1_MISO_PORT            GPIO_PORT_A
  #define DEV_SPI1_MISO_PIN             GPIO_PIN_6
  #define DEV_SPI1_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_MISO_PORT_ID == 2)
  #define DEV_SPI1_MISO                 1
  #define DEV_SPI1_MISO_PORT            GPIO_PORT_B
  #define DEV_SPI1_MISO_PIN             GPIO_PIN_4
  #define DEV_SPI1_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_MISO_PORT_ID == 3)
  #define DEV_SPI1_MISO                 1
  #define DEV_SPI1_MISO_PORT            GPIO_PORT_G
  #define DEV_SPI1_MISO_PIN             GPIO_PIN_9
  #define DEV_SPI1_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_MISO Pin Configuration!"
#endif

//   <o> SPI1_MOSI Pin <0=>Not Used <1=>PA7 <2=>PB5 <3=>PD7
#define DEV_SPI1_MOSI_PORT_ID           0
#if    (DEV_SPI1_MOSI_PORT_ID == 0)
  #define DEV_SPI1_MOSI                 0
#elif  (DEV_SPI1_MOSI_PORT_ID == 1)
  #define DEV_SPI1_MOSI                 1
  #define DEV_SPI1_MOSI_PORT            GPIO_PORT_A
  #define DEV_SPI1_MOSI_PIN             GPIO_PIN_7
  #define DEV_SPI1_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_MOSI_PORT_ID == 2)
  #define DEV_SPI1_MOSI                 1
  #define DEV_SPI1_MOSI_PORT            GPIO_PORT_B
  #define DEV_SPI1_MOSI_PIN             GPIO_PIN_5
  #define DEV_SPI1_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_MOSI_PORT_ID == 3)
  #define DEV_SPI1_MOSI                 1
  #define DEV_SPI1_MOSI_PORT            GPIO_PORT_D
  #define DEV_SPI1_MOSI_PIN             GPIO_PIN_7
  #define DEV_SPI1_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_MOSI Pin Configuration!"
#endif

//   <o> SPI1_SCK Pin <0=>PA5 <1=>PB3 <2=>PG11
#define DEV_SPI1_SCK_PORT_ID            0
#if    (DEV_SPI1_SCK_PORT_ID == 0)
  #define DEV_SPI1_SCK_PORT             GPIO_PORT_A
  #define DEV_SPI1_SCK_PIN              GPIO_PIN_5
  #define DEV_SPI1_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_SCK_PORT_ID == 1)
  #define DEV_SPI1_SCK_PORT             GPIO_PORT_B
  #define DEV_SPI1_SCK_PIN              GPIO_PIN_3
  #define DEV_SPI1_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_SCK_PORT_ID == 2)
  #define DEV_SPI1_SCK_PORT             GPIO_PORT_G
  #define DEV_SPI1_SCK_PIN              GPIO_PIN_11
  #define DEV_SPI1_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI1_SCK Pin Configuration!"
#endif

//   <o> SPI1_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15 <3=>PG10
#define DEV_SPI1_NSS_PORT_ID            0
#if    (DEV_SPI1_NSS_PORT_ID == 0)
  #define DEV_SPI1_NSS                  0
#elif  (DEV_SPI1_NSS_PORT_ID == 1)
  #define DEV_SPI1_NSS                  1
  #define DEV_SPI1_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI1_NSS_PIN              GPIO_PIN_4
  #define DEV_SPI1_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_NSS_PORT_ID == 2)
  #define DEV_SPI1_NSS                  1
  #define DEV_SPI1_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI1_NSS_PIN              GPIO_PIN_15
  #define DEV_SPI1_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI1_NSS_PORT_ID == 3)
  #define DEV_SPI1_NSS                  1
  #define DEV_SPI1_NSS_PORT             GPIO_PORT_G
  #define DEV_SPI1_NSS_PIN              GPIO_PIN_10
  #define DEV_SPI1_NSS_FUNC             GPIO_PIN_FUNC_5
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
#define DEV_SPI1_RX_DMA                 0
#define DEV_SPI1_RX_DMA_NUMBER          2
#define DEV_SPI1_RX_DMA_STREAM          0
#define DEV_SPI1_RX_DMA_CHANNEL         3
#define DEV_SPI1_RX_DMA_PRIORITY        0

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
#define DEV_SPI1_TX_DMA                 0
#define DEV_SPI1_TX_DMA_NUMBER          2
#define DEV_SPI1_TX_DMA_STREAM          5
#define DEV_SPI1_TX_DMA_CHANNEL         3
#define DEV_SPI1_TX_DMA_PRIORITY        0

// </e>

// <e> SPI2 (Serial Peripheral Interface 1) [Driver_SPI2]
// <i> Configuration settings for Driver_SPI2 in component ::CMSIS Driver:SPI
#define DEV_SPI2                        0

//   <o> SPI2_MISO Pin <0=>Not Used <1=>PB14 <2=>PC2 <3=>PI2
#define DEV_SPI2_MISO_PORT_ID           0
#if    (DEV_SPI2_MISO_PORT_ID == 0)
  #define DEV_SPI2_MISO                 0
#elif  (DEV_SPI2_MISO_PORT_ID == 1)
  #define DEV_SPI2_MISO                 1
  #define DEV_SPI2_MISO_PORT            GPIO_PORT_B
  #define DEV_SPI2_MISO_PIN             GPIO_PIN_14
  #define DEV_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_MISO_PORT_ID == 2)
  #define DEV_SPI2_MISO                 1
  #define DEV_SPI2_MISO_PORT            GPIO_PORT_C
  #define DEV_SPI2_MISO_PIN             GPIO_PIN_2
  #define DEV_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_MISO_PORT_ID == 3)
  #define DEV_SPI2_MISO                 1
  #define DEV_SPI2_MISO_PORT            GPIO_PORT_I
  #define DEV_SPI2_MISO_PIN             GPIO_PIN_2
  #define DEV_SPI2_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_MISO Pin Configuration!"
#endif

//   <o> SPI2_MOSI Pin <0=>Not Used <1=>PB15 <2=>PC1 <3=>PC3 <4=>PI3
#define DEV_SPI2_MOSI_PORT_ID           0
#if    (DEV_SPI2_MOSI_PORT_ID == 0)
  #define DEV_SPI2_MOSI                 0
#elif  (DEV_SPI2_MOSI_PORT_ID == 1)
  #define DEV_SPI2_MOSI                 1
  #define DEV_SPI2_MOSI_PORT            GPIO_PORT_B
  #define DEV_SPI2_MOSI_PIN             GPIO_PIN_15
  #define DEV_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_MOSI_PORT_ID == 2)
  #define DEV_SPI2_MOSI                 1
  #define DEV_SPI2_MOSI_PORT            GPIO_PORT_C
  #define DEV_SPI2_MOSI_PIN             GPIO_PIN_1
  #define DEV_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_MOSI_PORT_ID == 3)
  #define DEV_SPI2_MOSI                 1
  #define DEV_SPI2_MOSI_PORT            GPIO_PORT_C
  #define DEV_SPI2_MOSI_PIN             GPIO_PIN_3
  #define DEV_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_MOSI_PORT_ID == 4)
  #define DEV_SPI2_MOSI                 1
  #define DEV_SPI2_MOSI_PORT            GPIO_PORT_I
  #define DEV_SPI2_MOSI_PIN             GPIO_PIN_3
  #define DEV_SPI2_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_MOSI Pin Configuration!"
#endif

//   <o> SPI2_SCK Pin <0=>PA9 <1=>PB10 <2=>PB13 <3=>PD3 <4=>PI1 <5=>PA12
#define DEV_SPI2_SCK_PORT_ID            0
#if    (DEV_SPI2_SCK_PORT_ID == 0)
  #define DEV_SPI2_SCK_PORT             GPIO_PORT_A
  #define DEV_SPI2_SCK_PIN              GPIO_PIN_9
  #define DEV_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_SCK_PORT_ID == 1)
  #define DEV_SPI2_SCK_PORT             GPIO_PORT_B
  #define DEV_SPI2_SCK_PIN              GPIO_PIN_10
  #define DEV_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_SCK_PORT_ID == 2)
  #define DEV_SPI2_SCK_PORT             GPIO_PORT_B
  #define DEV_SPI2_SCK_PIN              GPIO_PIN_13
  #define DEV_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_SCK_PORT_ID == 3)
  #define DEV_SPI2_SCK_PORT             GPIO_PORT_D
  #define DEV_SPI2_SCK_PIN              GPIO_PIN_3
  #define DEV_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_SCK_PORT_ID == 4)
  #define DEV_SPI2_SCK_PORT             GPIO_PORT_I
  #define DEV_SPI2_SCK_PIN              GPIO_PIN_1
  #define DEV_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_SCK_PORT_ID == 5)
  #define DEV_SPI2_SCK_PORT             GPIO_PORT_A
  #define DEV_SPI2_SCK_PIN              GPIO_PIN_12
  #define DEV_SPI2_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI2_SCK Pin Configuration!"
#endif

//   <o> SPI2_NSS Pin <0=>Not Used <1=>PB4 <2=>PB9 <3=>PB12 <4=>PI0 <5=>PA11
#define DEV_SPI2_NSS_PORT_ID            0
#if    (DEV_SPI2_NSS_PORT_ID == 0)
  #define DEV_SPI2_NSS                  0
#elif  (DEV_SPI2_NSS_PORT_ID == 1)
  #define DEV_SPI2_NSS                  1
  #define DEV_SPI2_NSS_PORT             GPIO_PORT_B
  #define DEV_SPI2_NSS_PIN              GPIO_PIN_4
  #define DEV_SPI2_NSS_FUNC             GPIO_PIN_FUNC_7
#elif  (DEV_SPI2_NSS_PORT_ID == 2)
  #define DEV_SPI2_NSS                  1
  #define DEV_SPI2_NSS_PORT             GPIO_PORT_B
  #define DEV_SPI2_NSS_PIN              GPIO_PIN_9
  #define DEV_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_NSS_PORT_ID == 3)
  #define DEV_SPI2_NSS                  1
  #define DEV_SPI2_NSS_PORT             GPIO_PORT_B
  #define DEV_SPI2_NSS_PIN              GPIO_PIN_12
  #define DEV_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_NSS_PORT_ID == 4)
  #define DEV_SPI2_NSS                  1
  #define DEV_SPI2_NSS_PORT             GPIO_PORT_I
  #define DEV_SPI2_NSS_PIN              GPIO_PIN_0
  #define DEV_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI2_NSS_PORT_ID == 5)
  #define DEV_SPI2_NSS                  1
  #define DEV_SPI2_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI2_NSS_PIN              GPIO_PIN_11
  #define DEV_SPI2_NSS_FUNC             GPIO_PIN_FUNC_5
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
#define DEV_SPI2_RX_DMA                 0
#define DEV_SPI2_RX_DMA_NUMBER          1
#define DEV_SPI2_RX_DMA_STREAM          3
#define DEV_SPI2_RX_DMA_CHANNEL         0
#define DEV_SPI2_RX_DMA_PRIORITY        0

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
#define DEV_SPI2_TX_DMA                 0
#define DEV_SPI2_TX_DMA_NUMBER          1
#define DEV_SPI2_TX_DMA_STREAM          4
#define DEV_SPI2_TX_DMA_CHANNEL         0
#define DEV_SPI2_TX_DMA_PRIORITY        0

// </e>

// <e> SPI3 (Serial Peripheral Interface 1) [Driver_SPI3]
// <i> Configuration settings for Driver_SPI3 in component ::CMSIS Driver:SPI
#define DEV_SPI3                        0

//   <o> SPI3_MISO Pin <0=>Not Used <1=>PB4 <2=>PC11
#define DEV_SPI3_MISO_PORT_ID           0
#if    (DEV_SPI3_MISO_PORT_ID == 0)
  #define DEV_SPI3_MISO                 0
#elif  (DEV_SPI3_MISO_PORT_ID == 1)
  #define DEV_SPI3_MISO                 1
  #define DEV_SPI3_MISO_PORT            GPIO_PORT_B
  #define DEV_SPI3_MISO_PIN             GPIO_PIN_4
  #define DEV_SPI3_MISO_FUNC            GPIO_PIN_FUNC_6
#elif  (DEV_SPI3_MISO_PORT_ID == 2)
  #define DEV_SPI3_MISO                 1
  #define DEV_SPI3_MISO_PORT            GPIO_PORT_C
  #define DEV_SPI3_MISO_PIN             GPIO_PIN_11
  #define DEV_SPI3_MISO_FUNC            GPIO_PIN_FUNC_6
#else
  #error "Invalid SPI3_MISO Pin Configuration!"
#endif

//   <o> SPI3_MOSI Pin <0=>Not Used <1=>PB2 <2=>PB5 <3=>PC12 <4=>PD6
#define DEV_SPI3_MOSI_PORT_ID           0
#if    (DEV_SPI3_MOSI_PORT_ID == 0)
  #define DEV_SPI3_MOSI                 0
#elif  (DEV_SPI3_MOSI_PORT_ID == 1)
  #define DEV_SPI3_MOSI                 1
  #define DEV_SPI3_MOSI_PORT            GPIO_PORT_B
  #define DEV_SPI3_MOSI_PIN             GPIO_PIN_2
  #define DEV_SPI3_MOSI_FUNC            GPIO_PIN_FUNC_7
#elif  (DEV_SPI3_MOSI_PORT_ID == 2)
  #define DEV_SPI3_MOSI                 1
  #define DEV_SPI3_MOSI_PORT            GPIO_PORT_B
  #define DEV_SPI3_MOSI_PIN             GPIO_PIN_5
  #define DEV_SPI3_MOSI_FUNC            GPIO_PIN_FUNC_6
#elif  (DEV_SPI3_MOSI_PORT_ID == 3)
  #define DEV_SPI3_MOSI                 1
  #define DEV_SPI3_MOSI_PORT            GPIO_PORT_C
  #define DEV_SPI3_MOSI_PIN             GPIO_PIN_12
  #define DEV_SPI3_MOSI_FUNC            GPIO_PIN_FUNC_6
#elif  (DEV_SPI3_MOSI_PORT_ID == 4)
  #define DEV_SPI3_MOSI                 1
  #define DEV_SPI3_MOSI_PORT            GPIO_PORT_D
  #define DEV_SPI3_MOSI_PIN             GPIO_PIN_6
  #define DEV_SPI3_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI3_MOSI Pin Configuration!"
#endif

//   <o> SPI3_SCK Pin <0=>PB3 <1=>PC10
#define DEV_SPI3_SCK_PORT_ID            0
#if    (DEV_SPI3_SCK_PORT_ID == 0)
  #define DEV_SPI3_SCK_PORT             GPIO_PORT_B
  #define DEV_SPI3_SCK_PIN              GPIO_PIN_3
  #define DEV_SPI3_SCK_FUNC             GPIO_PIN_FUNC_6
#elif  (DEV_SPI3_SCK_PORT_ID == 1)
  #define DEV_SPI3_SCK_PORT             GPIO_PORT_C
  #define DEV_SPI3_SCK_PIN              GPIO_PIN_10
  #define DEV_SPI3_SCK_FUNC             GPIO_PIN_FUNC_6
#else
  #error "Invalid SPI3_SCK Pin Configuration!"
#endif

//   <o> SPI3_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15
#define DEV_SPI3_NSS_PORT_ID            0
#if    (DEV_SPI3_NSS_PORT_ID == 0)
  #define DEV_SPI3_NSS                  0
#elif  (DEV_SPI3_NSS_PORT_ID == 1)
  #define DEV_SPI3_NSS                  1
  #define DEV_SPI3_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI3_NSS_PIN              GPIO_PIN_4
  #define DEV_SPI3_NSS_FUNC             GPIO_PIN_FUNC_6
#elif  (DEV_SPI3_NSS_PORT_ID == 2)
  #define DEV_SPI3_NSS                  1
  #define DEV_SPI3_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI3_NSS_PIN              GPIO_PIN_15
  #define DEV_SPI3_NSS_FUNC             GPIO_PIN_FUNC_6
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
#define DEV_SPI3_RX_DMA                 0
#define DEV_SPI3_RX_DMA_NUMBER          1
#define DEV_SPI3_RX_DMA_STREAM          0
#define DEV_SPI3_RX_DMA_CHANNEL         0
#define DEV_SPI3_RX_DMA_PRIORITY        0

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
#define DEV_SPI3_TX_DMA                 0
#define DEV_SPI3_TX_DMA_NUMBER          1
#define DEV_SPI3_TX_DMA_STREAM          5
#define DEV_SPI3_TX_DMA_CHANNEL         0
#define DEV_SPI3_TX_DMA_PRIORITY        0

// </e>

// <e> SPI4 (Serial Peripheral Interface 1) [Driver_SPI4]
// <i> Configuration settings for Driver_SPI4 in component ::CMSIS Driver:SPI
#define DEV_SPI4                        0

//   <o> SPI4_MISO Pin <0=>Not Used <1=>PE5 <2=>PE13
#define DEV_SPI4_MISO_PORT_ID           0
#if    (DEV_SPI4_MISO_PORT_ID == 0)
  #define DEV_SPI4_MISO                 0
#elif  (DEV_SPI4_MISO_PORT_ID == 1)
  #define DEV_SPI4_MISO                 1
  #define DEV_SPI4_MISO_PORT            GPIO_PORT_E
  #define DEV_SPI4_MISO_PIN             GPIO_PIN_5
  #define DEV_SPI4_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI4_MISO_PORT_ID == 2)
  #define DEV_SPI4_MISO                 1
  #define DEV_SPI4_MISO_PORT            GPIO_PORT_E
  #define DEV_SPI4_MISO_PIN             GPIO_PIN_13
  #define DEV_SPI4_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_MISO Pin Configuration!"
#endif

//   <o> SPI4_MOSI Pin <0=>Not Used <1=>PE6 <2=>PE14
#define DEV_SPI4_MOSI_PORT_ID           0
#if    (DEV_SPI4_MOSI_PORT_ID == 0)
  #define DEV_SPI4_MOSI                 0
#elif  (DEV_SPI4_MOSI_PORT_ID == 1)
  #define DEV_SPI4_MOSI                 1
  #define DEV_SPI4_MOSI_PORT            GPIO_PORT_E
  #define DEV_SPI4_MOSI_PIN             GPIO_PIN_6
  #define DEV_SPI4_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI4_MOSI_PORT_ID == 2)
  #define DEV_SPI4_MOSI                 1
  #define DEV_SPI4_MOSI_PORT            GPIO_PORT_E
  #define DEV_SPI4_MOSI_PIN             GPIO_PIN_14
  #define DEV_SPI4_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_MOSI Pin Configuration!"
#endif

//   <o> SPI4_SCK Pin <0=>PE2 <1=>PE12
#define DEV_SPI4_SCK_PORT_ID            0
#if    (DEV_SPI4_SCK_PORT_ID == 0)
  #define DEV_SPI4_SCK_PORT             GPIO_PORT_E
  #define DEV_SPI4_SCK_PIN              GPIO_PIN_2
  #define DEV_SPI4_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI4_SCK_PORT_ID == 1)
  #define DEV_SPI4_SCK_PORT             GPIO_PORT_E
  #define DEV_SPI4_SCK_PIN              GPIO_PIN_12
  #define DEV_SPI4_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_SCK Pin Configuration!"
#endif

//   <o> SPI4_NSS Pin <0=>Not Used <1=>PE4 <2=>PE11
#define DEV_SPI4_NSS_PORT_ID            0
#if    (DEV_SPI4_NSS_PORT_ID == 0)
  #define DEV_SPI4_NSS                  0
#elif  (DEV_SPI4_NSS_PORT_ID == 1)
  #define DEV_SPI4_NSS                  1
  #define DEV_SPI4_NSS_PORT             GPIO_PORT_E
  #define DEV_SPI4_NSS_PIN              GPIO_PIN_4
  #define DEV_SPI4_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI4_NSS_PORT_ID == 2)
  #define DEV_SPI4_NSS                  1
  #define DEV_SPI4_NSS_PORT             GPIO_PORT_E
  #define DEV_SPI4_NSS_PIN              GPIO_PIN_11
  #define DEV_SPI4_NSS_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI4_NSS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0 <3=>3
//     <i>  Selects DMA Stream (only Stream 0 or 3 can be used)
//     <o3> Channel <4=>4 <5=>5
//     <i>  Selects DMA Channel (only Channel 4 or 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_SPI4_RX_DMA                 0
#define DEV_SPI4_RX_DMA_NUMBER          2
#define DEV_SPI4_RX_DMA_STREAM          0
#define DEV_SPI4_RX_DMA_CHANNEL         4
#define DEV_SPI4_RX_DMA_PRIORITY        0

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
#define DEV_SPI4_TX_DMA                 0
#define DEV_SPI4_TX_DMA_NUMBER          2
#define DEV_SPI4_TX_DMA_STREAM          1
#define DEV_SPI4_TX_DMA_CHANNEL         4
#define DEV_SPI4_TX_DMA_PRIORITY        0

// </e>

// <e> SPI5 (Serial Peripheral Interface 1) [Driver_SPI5]
// <i> Configuration settings for Driver_SPI5 in component ::CMSIS Driver:SPI
#define DEV_SPI5                        0

//   <o> SPI5_MISO Pin <0=>Not Used <1=>PF8 <2=>PH7
#define DEV_SPI5_MISO_PORT_ID           0
#if    (DEV_SPI5_MISO_PORT_ID == 0)
  #define DEV_SPI5_MISO                 0
#elif  (DEV_SPI5_MISO_PORT_ID == 1)
  #define DEV_SPI5_MISO                 1
  #define DEV_SPI5_MISO_PORT            GPIO_PORT_F
  #define DEV_SPI5_MISO_PIN             GPIO_PIN_8
  #define DEV_SPI5_MISO_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI5_MISO_PORT_ID == 2)
  #define DEV_SPI5_MISO                 1
  #define DEV_SPI5_MISO_PORT            GPIO_PORT_H
  #define DEV_SPI5_MISO_PIN             GPIO_PIN_7
  #define DEV_SPI5_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI5_MISO Pin Configuration!"
#endif

//   <o> SPI5_MOSI Pin <0=>Not Used <1=>PF9 <2=>PF11
#define DEV_SPI5_MOSI_PORT_ID           0
#if    (DEV_SPI5_MOSI_PORT_ID == 0)
  #define DEV_SPI5_MOSI                 0
#elif  (DEV_SPI5_MOSI_PORT_ID == 1)
  #define DEV_SPI5_MOSI                 1
  #define DEV_SPI5_MOSI_PORT            GPIO_PORT_F
  #define DEV_SPI5_MOSI_PIN             GPIO_PIN_9
  #define DEV_SPI5_MOSI_FUNC            GPIO_PIN_FUNC_5
#elif  (DEV_SPI5_MOSI_PORT_ID == 2)
  #define DEV_SPI5_MOSI                 1
  #define DEV_SPI5_MOSI_PORT            GPIO_PORT_F
  #define DEV_SPI5_MOSI_PIN             GPIO_PIN_11
  #define DEV_SPI5_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI5_MOSI Pin Configuration!"
#endif

//   <o> SPI5_SCK Pin <0=>PF7 <1=>PH6
#define DEV_SPI5_SCK_PORT_ID            0
#if    (DEV_SPI5_SCK_PORT_ID == 0)
  #define DEV_SPI5_SCK_PORT             GPIO_PORT_F
  #define DEV_SPI5_SCK_PIN              GPIO_PIN_7
  #define DEV_SPI5_SCK_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI5_SCK_PORT_ID == 1)
  #define DEV_SPI5_SCK_PORT             GPIO_PORT_H
  #define DEV_SPI5_SCK_PIN              GPIO_PIN_6
  #define DEV_SPI5_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI5_SCK Pin Configuration!"
#endif

//   <o> SPI5_NSS Pin <0=>Not Used <1=>PF6 <2=>PH5
#define DEV_SPI5_NSS_PORT_ID            0
#if    (DEV_SPI5_NSS_PORT_ID == 0)
  #define DEV_SPI5_NSS                  0
#elif  (DEV_SPI5_NSS_PORT_ID == 1)
  #define DEV_SPI5_NSS                  1
  #define DEV_SPI5_NSS_PORT             GPIO_PORT_F
  #define DEV_SPI5_NSS_PIN              GPIO_PIN_6
  #define DEV_SPI5_NSS_FUNC             GPIO_PIN_FUNC_5
#elif  (DEV_SPI5_NSS_PORT_ID == 2)
  #define DEV_SPI5_NSS                  1
  #define DEV_SPI5_NSS_PORT             GPIO_PORT_H
  #define DEV_SPI5_NSS_PIN              GPIO_PIN_5
  #define DEV_SPI5_NSS_FUNC             GPIO_PIN_FUNC_5
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
#define DEV_SPI5_RX_DMA                 0
#define DEV_SPI5_RX_DMA_NUMBER          2
#define DEV_SPI5_RX_DMA_STREAM          3
#define DEV_SPI5_RX_DMA_CHANNEL         2
#define DEV_SPI5_RX_DMA_PRIORITY        0

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <4=>4 <6=>6
//     <i>  Selects DMA Stream (only Stream 4 or 6 can be used)
//     <o3> Channel <2=>2 <7=>7
//     <i>  Selects DMA Channel (only Channel 2 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_SPI5_TX_DMA                 0
#define DEV_SPI5_TX_DMA_NUMBER          2
#define DEV_SPI5_TX_DMA_STREAM          4
#define DEV_SPI5_TX_DMA_CHANNEL         2
#define DEV_SPI5_TX_DMA_PRIORITY        0

// </e>

// <e> SPI6 (Serial Peripheral Interface 1) [Driver_SPI6]
// <i> Configuration settings for Driver_SPI6 in component ::CMSIS Driver:SPI
#define DEV_SPI6                        0

//   <o> SPI6_MISO Pin <0=>Not Used <1=>PA6 <2=>PB4 <3=>PG12
#define DEV_SPI6_MISO_PORT_ID           0
#if    (DEV_SPI6_MISO_PORT_ID == 0)
  #define DEV_SPI6_MISO                 0
#elif  (DEV_SPI6_MISO_PORT_ID == 1)
  #define DEV_SPI6_MISO                 1
  #define DEV_SPI6_MISO_PORT            GPIO_PORT_A
  #define DEV_SPI6_MISO_PIN             GPIO_PIN_6
  #define DEV_SPI6_MISO_FUNC            GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_MISO_PORT_ID == 2)
  #define DEV_SPI6_MISO                 1
  #define DEV_SPI6_MISO_PORT            GPIO_PORT_B
  #define DEV_SPI6_MISO_PIN             GPIO_PIN_4
  #define DEV_SPI6_MISO_FUNC            GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_MISO_PORT_ID == 3)
  #define DEV_SPI6_MISO                 1
  #define DEV_SPI6_MISO_PORT            GPIO_PORT_G
  #define DEV_SPI6_MISO_PIN             GPIO_PIN_12
  #define DEV_SPI6_MISO_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_MISO Pin Configuration!"
#endif

//   <o> SPI6_MOSI Pin <0=>Not Used <1=>PA7 <2=>PB5 <3=>PG14
#define DEV_SPI6_MOSI_PORT_ID           0
#if    (DEV_SPI6_MOSI_PORT_ID == 0)
  #define DEV_SPI6_MOSI                 0
#elif  (DEV_SPI6_MOSI_PORT_ID == 1)
  #define DEV_SPI6_MOSI                 1
  #define DEV_SPI6_MOSI_PORT            GPIO_PORT_A
  #define DEV_SPI6_MOSI_PIN             GPIO_PIN_7
  #define DEV_SPI6_MOSI_FUNC            GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_MOSI_PORT_ID == 2)
  #define DEV_SPI6_MOSI                 1
  #define DEV_SPI6_MOSI_PORT            GPIO_PORT_B
  #define DEV_SPI6_MOSI_PIN             GPIO_PIN_5
  #define DEV_SPI6_MOSI_FUNC            GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_MOSI_PORT_ID == 3)
  #define DEV_SPI6_MOSI                 1
  #define DEV_SPI6_MOSI_PORT            GPIO_PORT_G
  #define DEV_SPI6_MOSI_PIN             GPIO_PIN_14
  #define DEV_SPI6_MOSI_FUNC            GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_MOSI Pin Configuration!"
#endif

//   <o> SPI6_SCK Pin <0=>PA5 <1=>PB3 <2=>PG13
#define DEV_SPI6_SCK_PORT_ID            0
#if    (DEV_SPI6_SCK_PORT_ID == 0)
  #define DEV_SPI6_SCK_PORT             GPIO_PORT_A
  #define DEV_SPI6_SCK_PIN              GPIO_PIN_5
  #define DEV_SPI6_SCK_FUNC             GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_SCK_PORT_ID == 1)
  #define DEV_SPI6_SCK_PORT             GPIO_PORT_B
  #define DEV_SPI6_SCK_PIN              GPIO_PIN_3
  #define DEV_SPI6_SCK_FUNC             GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_SCK_PORT_ID == 2)
  #define DEV_SPI6_SCK_PORT             GPIO_PORT_G
  #define DEV_SPI6_SCK_PIN              GPIO_PIN_13
  #define DEV_SPI6_SCK_FUNC             GPIO_PIN_FUNC_5
#else
  #error "Invalid SPI6_SCK Pin Configuration!"
#endif

//   <o> SPI6_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15 <3=>PG8
#define DEV_SPI6_NSS_PORT_ID            0
#if    (DEV_SPI6_NSS_PORT_ID == 0)
  #define DEV_SPI6_NSS                  0
#elif  (DEV_SPI6_NSS_PORT_ID == 1)
  #define DEV_SPI6_NSS                  1
  #define DEV_SPI6_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI6_NSS_PIN              GPIO_PIN_4
  #define DEV_SPI6_NSS_FUNC             GPIO_PIN_FUNC_8
#elif  (DEV_SPI6_NSS_PORT_ID == 2)
  #define DEV_SPI6_NSS                  1
  #define DEV_SPI6_NSS_PORT             GPIO_PORT_A
  #define DEV_SPI6_NSS_PIN              GPIO_PIN_15
  #define DEV_SPI6_NSS_FUNC             GPIO_PIN_FUNC_7
#elif  (DEV_SPI6_NSS_PORT_ID == 3)
  #define DEV_SPI6_NSS                  1
  #define DEV_SPI6_NSS_PORT             GPIO_PORT_G
  #define DEV_SPI6_NSS_PIN              GPIO_PIN_8
  #define DEV_SPI6_NSS_FUNC             GPIO_PIN_FUNC_5
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
#define DEV_SPI6_RX_DMA                 0
#define DEV_SPI6_RX_DMA_NUMBER          2
#define DEV_SPI6_RX_DMA_STREAM          6
#define DEV_SPI6_RX_DMA_CHANNEL         1
#define DEV_SPI6_RX_DMA_PRIORITY        0

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
#define DEV_SPI6_TX_DMA                 0
#define DEV_SPI6_TX_DMA_NUMBER          2
#define DEV_SPI6_TX_DMA_STREAM          5
#define DEV_SPI6_TX_DMA_CHANNEL         1
#define DEV_SPI6_TX_DMA_PRIORITY        0

// </e>

// <e> QSPI0 (Quad Serial Peripheral Interface 0) [Driver_QSPI0]
// <i> Configuration settings for Driver_QSPI0 in component ::CMSIS Driver:QSPI
#define DEV_QSPI0                      0

//   <o> QSPI0_BK1_IO0 Pin <0=>Not Used <1=>PC9 <2=>PD11 <3=>PF8
#define   DEV_QSPI0_BK1_IO0_PORT_ID    0
#if      (DEV_QSPI0_BK1_IO0_PORT_ID == 0)
  #define DEV_QSPI0_BK1_IO0            0
#elif    (DEV_QSPI0_BK1_IO0_PORT_ID == 1)
  #define DEV_QSPI0_BK1_IO0            1
  #define DEV_QSPI0_BK1_IO0_PORT       GPIO_PORT_C
  #define DEV_QSPI0_BK1_IO0_PIN        GPIO_PIN_9
  #define DEV_QSPI0_BK1_IO0_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO0_PORT_ID == 2)
  #define DEV_QSPI0_BK1_IO0            1
  #define DEV_QSPI0_BK1_IO0_PORT       GPIO_PORT_D
  #define DEV_QSPI0_BK1_IO0_PIN        GPIO_PIN_11
  #define DEV_QSPI0_BK1_IO0_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO0_PORT_ID == 3)
  #define DEV_QSPI0_BK1_IO0            1
  #define DEV_QSPI0_BK1_IO0_PORT       GPIO_PORT_F
  #define DEV_QSPI0_BK1_IO0_PIN        GPIO_PIN_8
  #define DEV_QSPI0_BK1_IO0_FUNC       GPIO_PIN_FUNC_10
#else
  #error "Invalid QSPI0_BK1_IO0 Pin Configuration!"
#endif

//   <o> QSPI0_BK1_IO1 Pin <0=>Not Used <1=>PC10 <2=>PD12 <3=>PF9
#define   DEV_QSPI0_BK1_IO1_PORT_ID    0
#if      (DEV_QSPI0_BK1_IO1_PORT_ID == 0)
  #define DEV_QSPI0_BK1_IO1            0
#elif    (DEV_QSPI0_BK1_IO1_PORT_ID == 1)
  #define DEV_QSPI0_BK1_IO1            1
  #define DEV_QSPI0_BK1_IO1_PORT       GPIO_PORT_C
  #define DEV_QSPI0_BK1_IO1_PIN        GPIO_PIN_10
  #define DEV_QSPI0_BK1_IO1_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO1_PORT_ID == 2)
  #define DEV_QSPI0_BK1_IO1            1
  #define DEV_QSPI0_BK1_IO1_PORT       GPIO_PORT_D
  #define DEV_QSPI0_BK1_IO1_PIN        GPIO_PIN_12
  #define DEV_QSPI0_BK1_IO1_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO1_PORT_ID == 3)
  #define DEV_QSPI0_BK1_IO1            1
  #define DEV_QSPI0_BK1_IO1_PORT       GPIO_PORT_F
  #define DEV_QSPI0_BK1_IO1_PIN        GPIO_PIN_9
  #define DEV_QSPI0_BK1_IO1_FUNC       GPIO_PIN_FUNC_10
#else
  #error "Invalid QSPI0_BK1_IO1 Pin Configuration!"
#endif

//   <o> QSPI0_BK1_IO2 Pin <0=>Not Used <1=>PE2 <2=>PF7
#define   DEV_QSPI0_BK1_IO2_PORT_ID    0
#if      (DEV_QSPI0_BK1_IO2_PORT_ID == 0)
  #define DEV_QSPI0_BK1_IO2            0
#elif    (DEV_QSPI0_BK1_IO2_PORT_ID == 1)
  #define DEV_QSPI0_BK1_IO2            1
  #define DEV_QSPI0_BK1_IO2_PORT       GPIO_PORT_E
  #define DEV_QSPI0_BK1_IO2_PIN        GPIO_PIN_2
  #define DEV_QSPI0_BK1_IO2_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO2_PORT_ID == 2)
  #define DEV_QSPI0_BK1_IO2            1
  #define DEV_QSPI0_BK1_IO2_PORT       GPIO_PORT_F
  #define DEV_QSPI0_BK1_IO2_PIN        GPIO_PIN_7
  #define DEV_QSPI0_BK1_IO2_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK1_IO2 Pin Configuration!"
#endif

//   <o> QSPI0_BK1_IO3 Pin <0=>Not Used <1=>PA1 <2=>PD13 <3=>PF6
#define   DEV_QSPI0_BK1_IO3_PORT_ID    0
#if      (DEV_QSPI0_BK1_IO3_PORT_ID == 0)
  #define DEV_QSPI0_BK1_IO3            0
#elif    (DEV_QSPI0_BK1_IO3_PORT_ID == 1)
  #define DEV_QSPI0_BK1_IO3            1
  #define DEV_QSPI0_BK1_IO3_PORT       GPIO_PORT_A
  #define DEV_QSPI0_BK1_IO3_PIN        GPIO_PIN_1
  #define DEV_QSPI0_BK1_IO3_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO3_PORT_ID == 2)
  #define DEV_QSPI0_BK1_IO3            1
  #define DEV_QSPI0_BK1_IO3_PORT       GPIO_PORT_D
  #define DEV_QSPI0_BK1_IO3_PIN        GPIO_PIN_13
  #define DEV_QSPI0_BK1_IO3_FUNC       GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_BK1_IO3_PORT_ID == 3)
  #define DEV_QSPI0_BK1_IO3            1
  #define DEV_QSPI0_BK1_IO3_PORT       GPIO_PORT_F
  #define DEV_QSPI0_BK1_IO3_PIN        GPIO_PIN_6
  #define DEV_QSPI0_BK1_IO3_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK1_IO3 Pin Configuration!"
#endif

//   <o> QSPI0_BK1_NCS Pin <0=>Not Used <1=>PB6 <2=>PB10
#define   DEV_QSPI0_BK1_NCS_PORT_ID    0
#if      (DEV_QSPI0_BK1_NCS_PORT_ID == 0)
  #define DEV_QSPI0_BK1_NCS            0
#elif    (DEV_QSPI0_BK1_NCS_PORT_ID == 1)
  #define DEV_QSPI0_BK1_NCS            1
  #define DEV_QSPI0_BK1_NCS_PORT       GPIO_PORT_B
  #define DEV_QSPI0_BK1_NCS_PIN        GPIO_PIN_6
  #define DEV_QSPI0_BK1_NCS_FUNC       GPIO_PIN_FUNC_10
#elif    (DEV_QSPI0_BK1_NCS_PORT_ID == 2)
  #define DEV_QSPI0_BK1_NCS            1
  #define DEV_QSPI0_BK1_NCS_PORT       GPIO_PORT_B
  #define DEV_QSPI0_BK1_NCS_PIN        GPIO_PIN_10
  #define DEV_QSPI0_BK1_NCS_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK1_NCS Pin Configuration!"
#endif

//   <o> QSPI0_BK2_IO0 Pin <0=>Not Used <1=>PE7 <2=>PH2
#define   DEV_QSPI0_BK2_IO0_PORT_ID    0
#if      (DEV_QSPI0_BK2_IO0_PORT_ID == 0)
  #define DEV_QSPI0_BK2_IO0            0
#elif    (DEV_QSPI0_BK2_IO0_PORT_ID == 1)
  #define DEV_QSPI0_BK2_IO0            1
  #define DEV_QSPI0_BK2_IO0_PORT       GPIO_PORT_E
  #define DEV_QSPI0_BK2_IO0_PIN        GPIO_PIN_7
  #define DEV_QSPI0_BK2_IO0_FUNC       GPIO_PIN_FUNC_10
#elif    (DEV_QSPI0_BK2_IO0_PORT_ID == 2)
  #define DEV_QSPI0_BK2_IO0            1
  #define DEV_QSPI0_BK2_IO0_PORT       GPIO_PORT_H
  #define DEV_QSPI0_BK2_IO0_PIN        GPIO_PIN_2
  #define DEV_QSPI0_BK2_IO0_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK2_IO0 Pin Configuration!"
#endif

//   <o> QSPI0_BK2_IO1 Pin <0=>Not Used <1=>PE8 <2=>PH3
#define   DEV_QSPI0_BK2_IO1_PORT_ID    0
#if      (DEV_QSPI0_BK2_IO1_PORT_ID == 0)
  #define DEV_QSPI0_BK2_IO1            0
#elif    (DEV_QSPI0_BK2_IO1_PORT_ID == 1)
  #define DEV_QSPI0_BK2_IO1            1
  #define DEV_QSPI0_BK2_IO1_PORT       GPIO_PORT_E
  #define DEV_QSPI0_BK2_IO1_PIN        GPIO_PIN_8
  #define DEV_QSPI0_BK2_IO1_FUNC       GPIO_PIN_FUNC_10
#elif    (DEV_QSPI0_BK2_IO1_PORT_ID == 2)
  #define DEV_QSPI0_BK2_IO1            1
  #define DEV_QSPI0_BK2_IO1_PORT       GPIO_PORT_H
  #define DEV_QSPI0_BK2_IO1_PIN        GPIO_PIN_3
  #define DEV_QSPI0_BK2_IO1_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK2_IO1 Pin Configuration!"
#endif

//   <o> QSPI0_BK2_IO2 Pin <0=>Not Used <1=>PE9 <2=>PG9
#define   DEV_QSPI0_BK2_IO2_PORT_ID    0
#if      (DEV_QSPI0_BK2_IO2_PORT_ID == 0)
  #define DEV_QSPI0_BK2_IO2            0
#elif    (DEV_QSPI0_BK2_IO2_PORT_ID == 1)
  #define DEV_QSPI0_BK2_IO2            1
  #define DEV_QSPI0_BK2_IO2_PORT       GPIO_PORT_E
  #define DEV_QSPI0_BK2_IO2_PIN        GPIO_PIN_9
  #define DEV_QSPI0_BK2_IO2_FUNC       GPIO_PIN_FUNC_10
#elif    (DEV_QSPI0_BK2_IO2_PORT_ID == 2)
  #define DEV_QSPI0_BK2_IO2            1
  #define DEV_QSPI0_BK2_IO2_PORT       GPIO_PORT_G
  #define DEV_QSPI0_BK2_IO2_PIN        GPIO_PIN_9
  #define DEV_QSPI0_BK2_IO2_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK2_IO2 Pin Configuration!"
#endif

//   <o> QSPI0_BK2_IO3 Pin <0=>Not Used <1=>PE10 <2=>PG14
#define   DEV_QSPI0_BK2_IO3_PORT_ID    0
#if      (DEV_QSPI0_BK2_IO3_PORT_ID == 0)
  #define DEV_QSPI0_BK2_IO3            0
#elif    (DEV_QSPI0_BK2_IO3_PORT_ID == 1)
  #define DEV_QSPI0_BK2_IO3            1
  #define DEV_QSPI0_BK2_IO3_PORT       GPIO_PORT_E
  #define DEV_QSPI0_BK2_IO3_PIN        GPIO_PIN_10
  #define DEV_QSPI0_BK2_IO3_FUNC       GPIO_PIN_FUNC_10
#elif    (DEV_QSPI0_BK2_IO3_PORT_ID == 2)
  #define DEV_QSPI0_BK2_IO3            1
  #define DEV_QSPI0_BK2_IO3_PORT       GPIO_PORT_G
  #define DEV_QSPI0_BK2_IO3_PIN        GPIO_PIN_14
  #define DEV_QSPI0_BK2_IO3_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK2_IO3 Pin Configuration!"
#endif

//   <o> QSPI0_BK2_NCS Pin <0=>Not Used <1=>PC11
#define   DEV_QSPI0_BK2_NCS_PORT_ID    0
#if      (DEV_QSPI0_BK2_NCS_PORT_ID == 0)
  #define DEV_QSPI0_BK2_NCS            0
#elif    (DEV_QSPI0_BK2_NCS_PORT_ID == 1)
  #define DEV_QSPI0_BK2_NCS            1
  #define DEV_QSPI0_BK2_NCS_PORT       GPIO_PORT_C
  #define DEV_QSPI0_BK2_NCS_PIN        GPIO_PIN_11
  #define DEV_QSPI0_BK2_NCS_FUNC       GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_BK2_NCS Pin Configuration!"
#endif

//   <o> QSPI0_CLK Pin <0=>PB2 <1=>PF10
#define   DEV_QSPI0_CLK_PORT_ID        0
#if      (DEV_QSPI0_CLK_PORT_ID == 0)
  #define DEV_QSPI0_CLK_PORT           GPIO_PORT_B
  #define DEV_QSPI0_CLK_PIN            GPIO_PIN_2
  #define DEV_QSPI0_CLK_FUNC           GPIO_PIN_FUNC_9
#elif    (DEV_QSPI0_CLK_PORT_ID == 1)
  #define DEV_QSPI0_CLK_PORT           GPIO_PORT_F
  #define DEV_QSPI0_CLK_PIN            GPIO_PIN_10
  #define DEV_QSPI0_CLK_FUNC           GPIO_PIN_FUNC_9
#else
  #error "Invalid QSPI0_CLK Pin Configuration!"
#endif

//   <e> DMA
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <7=>7 <2=>2
//     <i>  Selects DMA Stream (only Stream 7 or 2 can be used)
//     <o3> Channel <3=>3 <11=>11
//     <i>  Selects DMA Channel (only Channel 3 or 11 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_QSPI0_DMA                  0
#define DEV_QSPI0_DMA_NUMBER           2
#define DEV_QSPI0_DMA_STREAM           7
#define DEV_QSPI0_DMA_CHANNEL          3
#define DEV_QSPI0_DMA_PRIORITY         0

// </e>

#endif  /* __DEVICE_CONFIG_H */

/* ----------------------------- End of file ---------------------------------*/
