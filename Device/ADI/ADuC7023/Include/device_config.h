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

// <e> DAC0 (Digital-To-Analog Converter) [Driver_DAC0]
// <i> Configuration settings for Driver_DAC0
#define DEV_DAC0                       0

//   <o> Output Range <0=>VREF <1=> AVDD
#define DEV_DAC0_OUTPUT_RANGE          0

// </e>

// <e> DAC1 (Digital-To-Analog Converter) [Driver_DAC1]
// <i> Configuration settings for Driver_DAC1
#define DEV_DAC1                       0

//   <o> Output Range <0=>VREF <1=> AVDD
#define DEV_DAC1_OUTPUT_RANGE          0

// </e>

// <e> DAC2 (Digital-To-Analog Converter) [Driver_DAC2]
// <i> Configuration settings for Driver_DAC2
#define DEV_DAC2                       0

//   <o> Output Range <0=>VREF <1=> AVDD
#define DEV_DAC2_OUTPUT_RANGE          0

// </e>

// <e> DAC3 (Digital-To-Analog Converter) [Driver_DAC3]
// <i> Configuration settings for Driver_DAC3
#define DEV_DAC3                       0

//   <o> Output Range <0=>VREF <1=> AVDD
#define DEV_DAC3_OUTPUT_RANGE          0

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
#define DEV_I2C1                       0

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
//     <o2> Internal Pull-Up Resistor <0=>Enable <1=>Disable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ0                0
#define   DEV_EXTI_IRQ0_ID             0
#define   DEV_EXTI_IRQ0_PULL_UP        0
#define   DEV_EXTI_IRQ0_INT_PRIO       4
#if      (DEV_EXTI_IRQ0_ID == 0)
  #define DEV_EXTI_IRQ0_PORT           &DRIVER_GPIO0
  #define DEV_EXTI_IRQ0_PIN            GPIO_PIN_4
  #define DEV_EXTI_IRQ0_FUNC           GPIO_PIN_FUNC_0
#endif

//   <e> IRQ1
//     <o1> Pin <0=>P1.1
//     <o2> Internal Pull-Up Resistor <0=>Enable <1=>Disable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ1                0
#define   DEV_EXTI_IRQ1_ID             0
#define   DEV_EXTI_IRQ1_PULL_UP        0
#define   DEV_EXTI_IRQ1_INT_PRIO       4
#if      (DEV_EXTI_IRQ1_ID == 0)
  #define DEV_EXTI_IRQ1_PORT           &DRIVER_GPIO1
  #define DEV_EXTI_IRQ1_PIN            GPIO_PIN_1
  #define DEV_EXTI_IRQ1_FUNC           GPIO_PIN_FUNC_0
#endif

//   <e> IRQ2
//     <o1> Pin <0=>P1.2
//     <o2> Internal Pull-Up Resistor <0=>Enable <1=>Disable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ2                0
#define   DEV_EXTI_IRQ2_ID             0
#define   DEV_EXTI_IRQ2_PULL_UP        0
#define   DEV_EXTI_IRQ2_INT_PRIO       4
#if      (DEV_EXTI_IRQ2_ID == 0)
  #define DEV_EXTI_IRQ2_PORT           &DRIVER_GPIO1
  #define DEV_EXTI_IRQ2_PIN            GPIO_PIN_2
  #define DEV_EXTI_IRQ2_FUNC           GPIO_PIN_FUNC_0
#endif

//   <e> IRQ3
//     <o1> Pin <0=>P1.3
//     <o2> Internal Pull-Up Resistor <0=>Enable <1=>Disable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ3                0
#define   DEV_EXTI_IRQ3_ID             0
#define   DEV_EXTI_IRQ3_PULL_UP        0
#define   DEV_EXTI_IRQ3_INT_PRIO       4
#if      (DEV_EXTI_IRQ3_ID == 0)
  #define DEV_EXTI_IRQ3_PORT           &DRIVER_GPIO1
  #define DEV_EXTI_IRQ3_PIN            GPIO_PIN_3
  #define DEV_EXTI_IRQ3_FUNC           GPIO_PIN_FUNC_0
#endif

// </e>


// <e> PWM (Pulse-Width Modulator) [Driver_PWM]
// <i> Configuration settings for Driver_PWM
#define DEV_PWM                        1

//   <e> Output 0
//     <o1> Pin <0=>P1.0
//   </e>
#define   DEV_PWM_OUT0                 1
#define   DEV_PWM_OUT0_ID              0
#if      (DEV_PWM_OUT0_ID == 0)
  #define DEV_PWM_OUT0_PORT            &DRIVER_GPIO1
  #define DEV_PWM_OUT0_PIN             GPIO_PIN_0
  #define DEV_PWM_OUT0_FUNC            GPIO_PIN_FUNC_2
#endif

//   <e> Output 1
//     <o1> Pin <0=>P1.1
//   </e>
#define   DEV_PWM_OUT1                 0
#define   DEV_PWM_OUT1_ID              0
#if      (DEV_PWM_OUT1_ID == 0)
  #define DEV_PWM_OUT1_PORT            &DRIVER_GPIO1
  #define DEV_PWM_OUT1_PIN             GPIO_PIN_1
  #define DEV_PWM_OUT1_FUNC            GPIO_PIN_FUNC_2
#endif

//   <e> Output 2
//     <o1> Pin <0=>P1.6
//   </e>
#define   DEV_PWM_OUT2                 0
#define   DEV_PWM_OUT2_ID              0
#if      (DEV_PWM_OUT2_ID == 0)
  #define DEV_PWM_OUT2_PORT            &DRIVER_GPIO1
  #define DEV_PWM_OUT2_PIN             GPIO_PIN_6
  #define DEV_PWM_OUT2_FUNC            GPIO_PIN_FUNC_2
#endif

//   <e> Output 3
//     <o1> Pin <0=>P1.7
//   </e>
#define   DEV_PWM_OUT3                 0
#define   DEV_PWM_OUT3_ID              0
#if      (DEV_PWM_OUT3_ID == 0)
  #define DEV_PWM_OUT3_PORT            &DRIVER_GPIO1
  #define DEV_PWM_OUT3_PIN             GPIO_PIN_7
  #define DEV_PWM_OUT3_FUNC            GPIO_PIN_FUNC_2
#endif

//   <e> Output 4
//     <o1> Pin <0=>P2.0
//   </e>
#define   DEV_PWM_OUT4                 0
#define   DEV_PWM_OUT4_ID              0
#if      (DEV_PWM_OUT4_ID == 0)
  #define DEV_PWM_OUT4_PORT            &DRIVER_GPIO2
  #define DEV_PWM_OUT4_PIN             GPIO_PIN_0
  #define DEV_PWM_OUT4_FUNC            GPIO_PIN_FUNC_2
#endif

//   <e> Trip Input
//     <o1> Pin <0=>P1.5
//   </e>
#define   DEV_PWM_TRIP                 0
#define   DEV_PWM_TRIP_ID              0
#if      (DEV_PWM_TRIP_ID == 0)
  #define DEV_PWM_TRIP_PORT            &DRIVER_GPIO1
  #define DEV_PWM_TRIP_PIN             GPIO_PIN_5
  #define DEV_PWM_TRIP_FUNC            GPIO_PIN_FUNC_2
#endif

//   <e> Sync Input
//     <o1> Pin <0=>P2.2
//   </e>
#define   DEV_PWM_SYNC                 0
#define   DEV_PWM_SYNC_ID              0
#if      (DEV_PWM_SYNC_ID == 0)
  #define DEV_PWM_SYNC_PORT            &DRIVER_GPIO2
  #define DEV_PWM_SYNC_PIN             GPIO_PIN_2
  #define DEV_PWM_SYNC_FUNC            GPIO_PIN_FUNC_2
#endif

//   <o> Clock Prescaler <0=>UCLK/2 <1=>UCLK/4 <2=>UCLK/8 <3=>UCLK/16 <4=>UCLK/32 <5=>UCLK/64 <6=>UCLK/128 <7=>UCLK/256
#define DEV_PWM_CLK_PSC                0

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_PWM_INT_PRIO               4

// </e>


// <e> WDG (Watchdog Timer) [Driver_WDG]
// <i> Configuration settings for Driver_WDG
#define DEV_WDG                        0

//   <o> Timer Clock, Hz <0=>32768 <1=>2048 <2=>128
#define DEV_WDG_CLK                    0

// </e>

#endif  /* __DEVICE_CONFIG_H */
