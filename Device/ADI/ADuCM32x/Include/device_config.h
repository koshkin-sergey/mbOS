/*
 * Copyright (C) 2022-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for Analog Devices ADuCM32x
 */

#ifndef __DEVICE_CONFIG_H
#define __DEVICE_CONFIG_H

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h> Clock Configuration
// <i> Configuration settings for Clock
//   <o> Low-Frequency Internal Clock (Hz)  <1-999999999>
//   <i> Low-Frequency Internal Clock
#define LF_CLK_VALUE                    32000
//   <o> High-Frequency Internal Clock (Hz) <1-999999999>
//   <i> High-Frequency Internal Clock
#define HF_CLK_VALUE                    16000000
//   <o> External Clock (Hz)            <1-999999999>
//   <i> Frequency of the external clock source connected to P1.0
#define XT_CLK_VALUE                    16000000
// </h>


// <e> EXTI (External Interrupts) [Driver_EXTI]
// <i> Configuration settings for Driver_EXTI
#define DEV_EXTI                       1

//   <e> IRQ0
//     <o1> Pin <0=>P0.3
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ0                1
#define   DEV_EXTI_IRQ0_ID             0
#define   DEV_EXTI_IRQ0_PULL_UP        1
#define   DEV_EXTI_IRQ0_INT_PRIO       4
#if      (DEV_EXTI_IRQ0_ID == 0)
  #define DEV_EXTI_IRQ0_PORT           &Driver_GPIO0
  #define DEV_EXTI_IRQ0_PIN            GPIO_PIN_3
#endif

//   <e> IRQ1
//     <o1> Pin <0=>P1.7
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ1                0
#define   DEV_EXTI_IRQ1_ID             0
#define   DEV_EXTI_IRQ1_PULL_UP        0
#define   DEV_EXTI_IRQ1_INT_PRIO       4
#if      (DEV_EXTI_IRQ1_ID == 0)
  #define DEV_EXTI_IRQ1_PORT           &Driver_GPIO1
  #define DEV_EXTI_IRQ1_PIN            GPIO_PIN_7
#endif

//   <e> IRQ2
//     <o1> Pin <0=>P2.0
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ2                0
#define   DEV_EXTI_IRQ2_ID             0
#define   DEV_EXTI_IRQ2_PULL_UP        0
#define   DEV_EXTI_IRQ2_INT_PRIO       4
#if      (DEV_EXTI_IRQ2_ID == 0)
  #define DEV_EXTI_IRQ2_PORT           &Driver_GPIO2
  #define DEV_EXTI_IRQ2_PIN            GPIO_PIN_0
#endif

//   <e> IRQ4
//     <o1> Pin <0=>P2.2
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ4                0
#define   DEV_EXTI_IRQ4_ID             0
#define   DEV_EXTI_IRQ4_PULL_UP        0
#define   DEV_EXTI_IRQ4_INT_PRIO       4
#if      (DEV_EXTI_IRQ4_ID == 0)
  #define DEV_EXTI_IRQ4_PORT           &Driver_GPIO2
  #define DEV_EXTI_IRQ4_PIN            GPIO_PIN_2
#endif

//   <e> IRQ5
//     <o1> Pin <0=>P2.4
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ5                0
#define   DEV_EXTI_IRQ5_ID             0
#define   DEV_EXTI_IRQ5_PULL_UP        0
#define   DEV_EXTI_IRQ5_INT_PRIO       4
#if      (DEV_EXTI_IRQ5_ID == 0)
  #define DEV_EXTI_IRQ5_PORT           &Driver_GPIO2
  #define DEV_EXTI_IRQ5_PIN            GPIO_PIN_4
#endif

//   <e> IRQ7
//     <o1> Pin <0=>P2.6
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ7                0
#define   DEV_EXTI_IRQ7_ID             0
#define   DEV_EXTI_IRQ7_PULL_UP        0
#define   DEV_EXTI_IRQ7_INT_PRIO       4
#if      (DEV_EXTI_IRQ7_ID == 0)
  #define DEV_EXTI_IRQ7_PORT           &Driver_GPIO2
  #define DEV_EXTI_IRQ7_PIN            GPIO_PIN_6
#endif

//   <e> IRQ8
//     <o1> Pin <0=>P2.7
//     <o2> Internal Pull-Up Resistor <0=>Disable <1=>Enable
//     <o3> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
//   </e>
#define   DEV_EXTI_IRQ8                0
#define   DEV_EXTI_IRQ8_ID             0
#define   DEV_EXTI_IRQ8_PULL_UP        0
#define   DEV_EXTI_IRQ8_INT_PRIO       4
#if      (DEV_EXTI_IRQ8_ID == 0)
  #define DEV_EXTI_IRQ8_PORT           &Driver_GPIO2
  #define DEV_EXTI_IRQ8_PIN            GPIO_PIN_7
#endif

// </e>


#endif  /* __DEVICE_CONFIG_H */
