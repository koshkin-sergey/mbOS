/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for ADI ADUC7023
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __DEVICE_CONFIG_H
#define __DEVICE_CONFIG_H

// <e> ADC (Analog-To-Digital Converter) [Driver_ADC]
// <i> Configuration settings for Driver_ADC
#define DEV_ADC                        0

//   <e> ADC4
//     <o1> Pin <0=>P1.2
//   </e>
#define DEV_ADC_IN4                    0
#define DEV_ADC_IN4_ID                 0
#if    (DEV_ADC_IN4_ID == 0)
  #define DEV_ADC_IN4_PORT             &DRIVER_GPIO1
  #define DEV_ADC_IN4_PIN              GPIO_PIN_2
  #define DEV_ADC_IN4_FUNC             GPIO_PIN_FUNC_1
#endif

//   <e> ADC5
//     <o1> Pin <0=>P1.3
//   </e>
#define DEV_ADC_IN5                    0
#define DEV_ADC_IN5_ID                 0
#if    (DEV_ADC_IN5_ID == 0)
  #define DEV_ADC_IN5_PORT             &DRIVER_GPIO1
  #define DEV_ADC_IN5_PIN              GPIO_PIN_3
  #define DEV_ADC_IN5_FUNC             GPIO_PIN_FUNC_1
#endif

//   <e> ADC6
//     <o1> Pin <0=>P1.5
//   </e>
#define DEV_ADC_IN6                    0
#define DEV_ADC_IN6_ID                 0
#if    (DEV_ADC_IN6_ID == 0)
  #define DEV_ADC_IN6_PORT             &DRIVER_GPIO1
  #define DEV_ADC_IN6_PIN              GPIO_PIN_5
  #define DEV_ADC_IN6_FUNC             GPIO_PIN_FUNC_1
#endif

//   <e> ADC7
//     <o1> Pin <0=>P2.2
//   </e>
#define DEV_ADC_IN7                    0
#define DEV_ADC_IN7_ID                 0
#if    (DEV_ADC_IN7_ID == 0)
  #define DEV_ADC_IN7_PORT             &DRIVER_GPIO2
  #define DEV_ADC_IN7_PIN              GPIO_PIN_2
  #define DEV_ADC_IN7_FUNC             GPIO_PIN_FUNC_1
#endif

//   <e> ADC8
//     <o1> Pin <0=>P2.3
//   </e>
#define DEV_ADC_IN8                    0
#define DEV_ADC_IN8_ID                 0
#if    (DEV_ADC_IN8_ID == 0)
  #define DEV_ADC_IN8_PORT             &DRIVER_GPIO2
  #define DEV_ADC_IN8_PIN              GPIO_PIN_3
  #define DEV_ADC_IN8_FUNC             GPIO_PIN_FUNC_1
#endif

//   <e> ADC9
//     <o1> Pin <0=>P2.4
//   </e>
#define DEV_ADC_IN9                    0
#define DEV_ADC_IN9_ID                 0
#if    (DEV_ADC_IN9_ID == 0)
  #define DEV_ADC_IN9_PORT             &DRIVER_GPIO2
  #define DEV_ADC_IN9_PIN              GPIO_PIN_4
  #define DEV_ADC_IN9_FUNC             GPIO_PIN_FUNC_1
#endif

//   <e> ADC10
//     <o1> Pin <0=>P1.4
//   </e>
#define DEV_ADC_IN10                   0
#define DEV_ADC_IN10_ID                0
#if    (DEV_ADC_IN10_ID == 0)
  #define DEV_ADC_IN10_PORT            &DRIVER_GPIO1
  #define DEV_ADC_IN10_PIN             GPIO_PIN_4
  #define DEV_ADC_IN10_FUNC            GPIO_PIN_FUNC_1
#endif

//   <e> ADC12
//     <o1> Pin <0=>P2.0
//   </e>
#define DEV_ADC_IN12                   0
#define DEV_ADC_IN12_ID                0
#if    (DEV_ADC_IN12_ID == 0)
  #define DEV_ADC_IN12_PORT            &DRIVER_GPIO2
  #define DEV_ADC_IN12_PIN             GPIO_PIN_0
  #define DEV_ADC_IN12_FUNC            GPIO_PIN_FUNC_1
#endif

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_ADC_INT_PRIO               4

// </e>

// <e> I2C0 (Inter-integrated Circuit Interface) [Driver_I2C0]
// <i> Configuration settings for Driver_I2C0 in component ::CMSIS Driver:I2C
#define DEV_I2C0                       0

//   <o> SCL Pin <0=>P0.4
#define   DEV_I2C0_SCL_PORT_ID         0
#if      (DEV_I2C0_SCL_PORT_ID == 0)
  #define DEV_I2C0_SCL_PORT            &DRIVER_GPIO0
  #define DEV_I2C0_SCL_PIN             GPIO_PIN_4
  #define DEV_I2C0_SCL_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C0 SCL Pin Configuration!"
#endif

//   <o> SDA Pin <0=>P0.5
#define   DEV_I2C0_SDA_PORT_ID         0
#if      (DEV_I2C0_SDA_PORT_ID == 0)
  #define DEV_I2C0_SDA_PORT            &DRIVER_GPIO0
  #define DEV_I2C0_SDA_PIN             GPIO_PIN_5
  #define DEV_I2C0_SDA_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C0 SDA Pin Configuration!"
#endif

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_I2C0_INT_PRIO              4

// </e>

// <e> I2C1 (Inter-integrated Circuit Interface) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::CMSIS Driver:I2C
#define DEV_I2C1                        0

//   <o> SCL Pin <0=>P0.6 <1=>P1.6
#define   DEV_I2C1_SCL_PORT_ID         1
#if      (DEV_I2C1_SCL_PORT_ID == 0)
  #define DEV_I2C1_SCL_PORT            &DRIVER_GPIO0
  #define DEV_I2C1_SCL_PIN             GPIO_PIN_6
  #define DEV_I2C1_SCL_FUNC            GPIO_PIN_FUNC_2
#elif    (DEV_I2C1_SCL_PORT_ID == 1)
  #define DEV_I2C1_SCL_PORT            &DRIVER_GPIO1
  #define DEV_I2C1_SCL_PIN             GPIO_PIN_6
  #define DEV_I2C1_SCL_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1 SCL Pin Configuration!"
#endif

//   <o> SDA Pin <0=>P0.7 <1=>P1.7
#define   DEV_I2C1_SDA_PORT_ID         1
#if      (DEV_I2C1_SDA_PORT_ID == 0)
  #define DEV_I2C1_SDA_PORT            &DRIVER_GPIO0
  #define DEV_I2C1_SDA_PIN             GPIO_PIN_7
  #define DEV_I2C1_SDA_FUNC            GPIO_PIN_FUNC_2
#elif    (DEV_I2C1_SDA_PORT_ID == 1)
  #define DEV_I2C1_SDA_PORT            &DRIVER_GPIO1
  #define DEV_I2C1_SDA_PIN             GPIO_PIN_7
  #define DEV_I2C1_SDA_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1 SDA Pin Configuration!"
#endif

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_I2C1_INT_PRIO              4

// </e>

// <e> EXTI (External Interrupts) [Driver_EXTI]
// <i> Configuration settings for Driver_EXTI
#define DEV_EXTI                       0

//   <e> IRQ0
//     <o1> Pin <0=>P0.4
//     <o2> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ0                0
#define   DEV_EXTI_IRQ0_ID             0
#define   DEV_EXTI_IRQ0_INT_PRIO       4
#if      (DEV_EXTI_IRQ0_ID == 0)
  #define DEV_EXTI_IRQ0_PORT           &DRIVER_GPIO0
  #define DEV_EXTI_IRQ0_PIN            GPIO_PIN_4
  #define DEV_EXTI_IRQ0_FUNC           GPIO_PIN_FUNC_0
#endif

//   <e> IRQ1
//     <o1> Pin <0=>P1.1
//     <o2> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ1                0
#define   DEV_EXTI_IRQ1_ID             0
#define   DEV_EXTI_IRQ1_INT_PRIO       4
#if      (DEV_EXTI_IRQ1_ID == 0)
  #define DEV_EXTI_IRQ1_PORT           &DRIVER_GPIO1
  #define DEV_EXTI_IRQ1_PIN            GPIO_PIN_1
  #define DEV_EXTI_IRQ1_FUNC           GPIO_PIN_FUNC_0
#endif

//   <e> IRQ2
//     <o1> Pin <0=>P1.2
//     <o2> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ2                0
#define   DEV_EXTI_IRQ2_ID             0
#define   DEV_EXTI_IRQ2_INT_PRIO       4
#if      (DEV_EXTI_IRQ2_ID == 0)
  #define DEV_EXTI_IRQ2_PORT           &DRIVER_GPIO1
  #define DEV_EXTI_IRQ2_PIN            GPIO_PIN_2
  #define DEV_EXTI_IRQ2_FUNC           GPIO_PIN_FUNC_0
#endif

//   <e> IRQ3
//     <o1> Pin <0=>P1.3
//     <o2> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ3                0
#define   DEV_EXTI_IRQ3_ID             0
#define   DEV_EXTI_IRQ3_INT_PRIO       4
#if      (DEV_EXTI_IRQ3_ID == 0)
  #define DEV_EXTI_IRQ3_PORT           &DRIVER_GPIO1
  #define DEV_EXTI_IRQ3_PIN            GPIO_PIN_3
  #define DEV_EXTI_IRQ3_FUNC           GPIO_PIN_FUNC_0
#endif

// </e>

#endif  /* __DEVICE_CONFIG_H */
