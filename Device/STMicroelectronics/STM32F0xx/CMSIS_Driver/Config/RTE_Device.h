/*
 * Copyright (C) 2017 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: RTE Device Configuration for STMicroelectronics STM32F0xx
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef RTE_DEVICE_H_
#define RTE_DEVICE_H_

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

// <h> Clock Configuration
//   <o> High-speed Internal Clock <1-999999999>
#define RTE_HSI                         8000000
//   <o> High-speed External Clock <1-999999999>
#define RTE_HSE                         8000000
// </h>

#if !defined(RTE_HSI14)
  #define RTE_HSI14       ((uint32_t)14000000)  /* Default value of the HSI14 Internal oscillator in Hz */
#endif  // RTE_HSI14
#if !defined(RTE_HSI48)
  #define RTE_HSI48       ((uint32_t)48000000)  /* Default value of the HSI48 Internal oscillator in Hz */
#endif  // RTE_HSI48

/* Interrupt Priority */
#define RTE_I2C_INT_PRIORITY            (1U)
#define RTE_USART_INT_PRIORITY          (1U)


// <e> USART1 (Universal synchronous asynchronous receiver transmitter) [Driver_USART1]
// <i> Configuration settings for Driver_USART1 in component ::CMSIS Driver:USART
#define RTE_USART1                      1

//   <o> USART1_TX Pin <0=>Not Used <1=>PA2 <2=>PA9 <3=>PA14 <4=>PB6
#define   RTE_USART1_TX_ID              1
#if      (RTE_USART1_TX_ID == 0)
  #define RTE_USART1_TX                 0
#elif    (RTE_USART1_TX_ID == 1)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_A
  #define RTE_USART1_TX_PIN             GPIO_PIN_2
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_TX_ID == 2)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_A
  #define RTE_USART1_TX_PIN             GPIO_PIN_9
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_TX_ID == 3)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_A
  #define RTE_USART1_TX_PIN             GPIO_PIN_14
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_TX_ID == 4)
  #define RTE_USART1_TX                 1
  #define RTE_USART1_TX_PORT            GPIO_PORT_B
  #define RTE_USART1_TX_PIN             GPIO_PIN_6
  #define RTE_USART1_TX_FUNC            GPIO_PIN_FUNC_0
#else
  #error "Invalid USART1_TX Pin Configuration!"
#endif

//   <o> USART1_RX Pin <0=>Not Used <1=>PA3 <2=>PA10 <3=>PA15 <4=>PB7
#define   RTE_USART1_RX_ID              1
#if      (RTE_USART1_RX_ID == 0)
  #define RTE_USART1_RX                 0
#elif    (RTE_USART1_RX_ID == 1)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_A
  #define RTE_USART1_RX_PIN             GPIO_PIN_3
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_RX_ID == 2)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_A
  #define RTE_USART1_RX_PIN             GPIO_PIN_10
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_RX_ID == 3)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_A
  #define RTE_USART1_RX_PIN             GPIO_PIN_15
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_RX_ID == 4)
  #define RTE_USART1_RX                 1
  #define RTE_USART1_RX_PORT            GPIO_PORT_B
  #define RTE_USART1_RX_PIN             GPIO_PIN_7
  #define RTE_USART1_RX_FUNC            GPIO_PIN_FUNC_0
#else
  #error "Invalid USART1_RX Pin Configuration!"
#endif

//   <o> USART1_CK Pin <0=>Not Used <1=>PA4 <2=>PA8
#define   RTE_USART1_CK_ID              0
#if      (RTE_USART1_CK_ID == 0)
  #define RTE_USART1_CK                 0
#elif    (RTE_USART1_CK_ID == 1)
  #define RTE_USART1_CK                 1
  #define RTE_USART1_CK_PORT            GPIO_PORT_A
  #define RTE_USART1_CK_PIN             GPIO_PIN_4
  #define RTE_USART1_CK_FUNC            GPIO_PIN_FUNC_1
#elif    (RTE_USART1_CK_ID == 2)
  #define RTE_USART1_CK                 1
  #define RTE_USART1_CK_PORT            GPIO_PORT_A
  #define RTE_USART1_CK_PIN             GPIO_PIN_8
  #define RTE_USART1_CK_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid USART1_CK Pin Configuration!"
#endif

//   <o> USART1_CTS Pin <0=>Not Used <1=>PA0 <2=>PA11
#define   RTE_USART1_CTS_ID             0
#if      (RTE_USART1_CTS_ID == 0)
  #define RTE_USART1_CTS                0
#elif    (RTE_USART1_CTS_ID == 1)
  #define RTE_USART1_CTS                1
  #define RTE_USART1_CTS_PORT           GPIO_PORT_A
  #define RTE_USART1_CTS_PIN            GPIO_PIN_0
  #define RTE_USART1_CTS_FUNC           GPIO_PIN_FUNC_1
#elif    (RTE_USART1_CTS_ID == 2)
  #define RTE_USART1_CTS                1
  #define RTE_USART1_CTS_PORT           GPIO_PORT_A
  #define RTE_USART1_CTS_PIN            GPIO_PIN_11
  #define RTE_USART1_CTS_FUNC           GPIO_PIN_FUNC_1
#else
  #error "Invalid USART1_CTS Pin Configuration!"
#endif

//   <o> USART1_RTS Pin <0=>Not Used <1=>PA1 <2=>PA12
#define   RTE_USART1_RTS_ID             0
#if      (RTE_USART1_RTS_ID == 0)
  #define RTE_USART1_RTS                0
#elif    (RTE_USART1_RTS_ID == 1)
  #define RTE_USART1_RTS                1
  #define RTE_USART1_RTS_PORT           GPIO_PORT_A
  #define RTE_USART1_RTS_PIN            GPIO_PIN_1
  #define RTE_USART1_RTS_FUNC           GPIO_PIN_FUNC_1
#elif    (RTE_USART1_RTS_ID == 2)
  #define RTE_USART1_RTS                1
  #define RTE_USART1_RTS_PORT           GPIO_PORT_A
  #define RTE_USART1_RTS_PIN            GPIO_PIN_12
  #define RTE_USART1_RTS_FUNC           GPIO_PIN_FUNC_1
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

// <e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::Drivers:I2C
#define   RTE_I2C1                      0

//   <o> I2C1_SCL Pin <0=>PB6 <1=>PB8
#define   RTE_I2C1_SCL_PORT_ID          0
#if      (RTE_I2C1_SCL_PORT_ID == 0)
  #define RTE_I2C1_SCL_PORT             GPIO_PORT_B
  #define RTE_I2C1_SCL_PIN              GPIO_PIN_6
  #define RTE_I2C1_SCL_FUNC             GPIO_PIN_FUNC_1
#elif    (RTE_I2C1_SCL_PORT_ID == 1)
  #define RTE_I2C1_SCL_PORT             GPIO_PORT_B
  #define RTE_I2C1_SCL_PIN              GPIO_PIN_8
  #define RTE_I2C1_SCL_FUNC             GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1_SCL Pin Configuration!"
#endif
//   <o> I2C1_SDA Pin <0=>PB7 <1=>PB9
#define   RTE_I2C1_SDA_PORT_ID          0
#if      (RTE_I2C1_SDA_PORT_ID == 0)
  #define RTE_I2C1_SDA_PORT             GPIO_PORT_B
  #define RTE_I2C1_SDA_PIN              GPIO_PIN_7
  #define RTE_I2C1_SDA_FUNC             GPIO_PIN_FUNC_1
#elif    (RTE_I2C1_SDA_PORT_ID == 1)
  #define RTE_I2C1_SDA_PORT             GPIO_PORT_B
  #define RTE_I2C1_SDA_PIN              GPIO_PIN_9
  #define RTE_I2C1_SDA_FUNC             GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1_SDA Pin Configuration!"
#endif
// </e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]

// <e> I2C2 (Inter-integrated Circuit Interface 2) [Driver_I2C2]
// <i> Configuration settings for Driver_I2C2 in component ::Drivers:I2C
#define   RTE_I2C2                      0

//   <o> I2C2_SCL Pin <0=>PB10 <1=>PF6
#define   RTE_I2C2_SCL_PORT_ID          0
#if      (RTE_I2C2_SCL_PORT_ID == 0)
  #define RTE_I2C2_SCL_PORT             GPIO_PORT_B
  #define RTE_I2C2_SCL_PIN              GPIO_PIN_10
  #define RTE_I2C2_SCL_FUNC             GPIO_PIN_FUNC_1
#elif    (RTE_I2C2_SCL_PORT_ID == 1)
  #define RTE_I2C2_SCL_PORT             GPIO_PORT_F
  #define RTE_I2C2_SCL_PIN              GPIO_PIN_6
  #define RTE_I2C2_SCL_FUNC             GPIO_PIN_FUNC_0
#else
  #error "Invalid I2C2_SCL Pin Configuration!"
#endif
//   <o> I2C2_SDA Pin <0=>PB11 <1=>PF7
#define   RTE_I2C2_SDA_PORT_ID          0
#if      (RTE_I2C2_SDA_PORT_ID == 0)
  #define RTE_I2C2_SDA_PORT             GPIO_PORT_B
  #define RTE_I2C2_SDA_PIN              GPIO_PIN_11
  #define RTE_I2C2_SDA_FUNC             GPIO_PIN_FUNC_1
#elif    (RTE_I2C2_SDA_PORT_ID == 1)
  #define RTE_I2C2_SDA_PORT             GPIO_PORT_F
  #define RTE_I2C2_SDA_PIN              GPIO_PIN_7
  #define RTE_I2C2_SDA_FUNC             GPIO_PIN_FUNC_0
#else
  #error "Invalid I2C2_SDA Pin Configuration!"
#endif
// </e> I2C2 (Inter-integrated Circuit Interface 2) [Driver_I2C2]

#endif /* RTE_DEVICE_H_ */

/* ----------------------------- End of file ---------------------------------*/
