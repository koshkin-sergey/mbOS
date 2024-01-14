/*
 * Copyright (C) 2022-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern uint32_t osKernelGetSysTimerFreq(void);
extern uint32_t osKernelGetSysTimerCount(void);

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define GetSysTimerFreq()                 osKernelGetSysTimerFreq()
#define GetSysTimerCount()                osKernelGetSysTimerCount()
#define MicroSecToSysTimerCount(microsec) (uint32_t)(((uint64_t)microsec * GetSysTimerFreq()) / 1000000)


//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h> Clock Configuration
// <i> Configuration settings for Clock
//   <o> Low-Frequency Internal Clock (Hz)  <1-999999999>
//   <i> Low-Frequency Internal Clock
#define LF_CLK_VALUE                    32768
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


// <e> FEE (Flash Controller) [Driver_Flash]
// <i> Configuration settings for Driver_Flash
#define DEV_FEE                        1

// <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_FEE_INT_PRIO               4

// </e>


// <e> WDT (Watchdog Timer) [Driver_WDT]
// <i> Configuration settings for Driver_WDT
#define DEV_WDT                        1

// <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_WDT_INT_PRIO               4

// </e>


// <e> I2C0 (Inter-integrated Circuit Interface) [Driver_I2C0]
// <i> Configuration settings for Driver_I2C0 in component ::CMSIS Driver:I2C
#define DEV_I2C0                       1

//   <o> SCL Pin <0=>P0.4
#define   DEV_I2C0_SCL_PORT_ID         0
#if      (DEV_I2C0_SCL_PORT_ID == 0)
  #define DEV_I2C0_SCL_PORT            &Driver_GPIO0
  #define DEV_I2C0_SCL_PIN             GPIO_PIN_4
  #define DEV_I2C0_SCL_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C0 SCL Pin Configuration!"
#endif

//   <o> SDA Pin <0=>P0.5
#define   DEV_I2C0_SDA_PORT_ID         0
#if      (DEV_I2C0_SDA_PORT_ID == 0)
  #define DEV_I2C0_SDA_PORT            &Driver_GPIO0
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
#define DEV_I2C1                       1

//   <o> SCL Pin <0=>P0.6
#define   DEV_I2C1_SCL_PORT_ID         0
#if      (DEV_I2C1_SCL_PORT_ID == 0)
  #define DEV_I2C1_SCL_PORT            &Driver_GPIO0
  #define DEV_I2C1_SCL_PIN             GPIO_PIN_6
  #define DEV_I2C1_SCL_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1 SCL Pin Configuration!"
#endif

//   <o> SDA Pin <0=>P0.7
#define   DEV_I2C1_SDA_PORT_ID         0
#if      (DEV_I2C1_SDA_PORT_ID == 0)
  #define DEV_I2C1_SDA_PORT            &Driver_GPIO0
  #define DEV_I2C1_SDA_PIN             GPIO_PIN_7
  #define DEV_I2C1_SDA_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1 SDA Pin Configuration!"
#endif

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_I2C1_INT_PRIO              4

// </e>


// <e> SPI0 (Serial Peripheral Interface 0) [Driver_SPI0]
// <i> Configuration settings for Driver_SPI0 in component ::CMSIS Driver:SPI
#define DEV_SPI0                       1

//   <o> SCLK Pin <0=>P0.0
#define   DEV_SPI0_SCLK_PORT_ID        0
#if      (DEV_SPI0_SCLK_PORT_ID == 0)
  #define DEV_SPI0_SCLK_PORT           &Driver_GPIO0
  #define DEV_SPI0_SCLK_PIN            GPIO_PIN_0
  #define DEV_SPI0_SCLK_FUNC           GPIO_PIN_FUNC_1
#else
  #error "Invalid SPI0 SCLK Pin Configuration!"
#endif

//   <o> MISO Pin <0=>Not Used <1=>P0.1
#define   DEV_SPI0_MISO_PORT_ID        0
#if      (DEV_SPI0_MISO_PORT_ID == 0)
  #define DEV_SPI0_MISO                0
#elif    (DEV_SPI0_MISO_PORT_ID == 1)
  #define DEV_SPI0_MISO                1
  #define DEV_SPI0_MISO_PORT           &Driver_GPIO0
  #define DEV_SPI0_MISO_PIN            GPIO_PIN_1
  #define DEV_SPI0_MISO_FUNC           GPIO_PIN_FUNC_1
#else
  #error "Invalid SPI0 MISO Pin Configuration!"
#endif

//   <o> MOSI Pin <0=>Not Used <1=>P0.2
#define   DEV_SPI0_MOSI_PORT_ID        0
#if      (DEV_SPI0_MOSI_PORT_ID == 0)
  #define DEV_SPI0_MOSI                0
#elif    (DEV_SPI0_MOSI_PORT_ID == 1)
  #define DEV_SPI0_MOSI                1
  #define DEV_SPI0_MOSI_PORT           &Driver_GPIO0
  #define DEV_SPI0_MOSI_PIN            GPIO_PIN_2
  #define DEV_SPI0_MOSI_FUNC           GPIO_PIN_FUNC_1
#else
  #error "Invalid SPI0 MOSI Pin Configuration!"
#endif

//   <o> CS Pin <0=>Not Used <1=>P0.3
#define   DEV_SPI0_CS_PORT_ID          0
#if      (DEV_SPI0_CS_PORT_ID == 0)
  #define DEV_SPI0_CS                  0
#elif    (DEV_SPI0_CS_PORT_ID == 1)
  #define DEV_SPI0_CS                  1
  #define DEV_SPI0_CS_PORT             &Driver_GPIO0
  #define DEV_SPI0_CS_PIN              GPIO_PIN_3
  #define DEV_SPI0_CS_FUNC             GPIO_PIN_FUNC_1
#else
  #error "Invalid SPI0 CS Pin Configuration!"
#endif

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_SPI0_INT_PRIO              4

// </e>


// <e> SPI1 (Serial Peripheral Interface 1) [Driver_SPI1]
// <i> Configuration settings for Driver_SPI1 in component ::CMSIS Driver:SPI
#define DEV_SPI1                       1

//   <o> SCLK Pin <0=>P1.4
#define   DEV_SPI1_SCLK_PORT_ID        0
#if      (DEV_SPI1_SCLK_PORT_ID == 0)
  #define DEV_SPI1_SCLK_PORT           &Driver_GPIO1
  #define DEV_SPI1_SCLK_PIN            GPIO_PIN_4
  #define DEV_SPI1_SCLK_FUNC           GPIO_PIN_FUNC_2
#else
  #error "Invalid SPI1 SCLK Pin Configuration!"
#endif

//   <o> MISO Pin <0=>Not Used <1=>P1.5
#define   DEV_SPI1_MISO_PORT_ID        0
#if      (DEV_SPI1_MISO_PORT_ID == 0)
  #define DEV_SPI1_MISO                0
#elif    (DEV_SPI1_MISO_PORT_ID == 1)
  #define DEV_SPI1_MISO                1
  #define DEV_SPI1_MISO_PORT           &Driver_GPIO1
  #define DEV_SPI1_MISO_PIN            GPIO_PIN_5
  #define DEV_SPI1_MISO_FUNC           GPIO_PIN_FUNC_2
#else
  #error "Invalid SPI1 MISO Pin Configuration!"
#endif

//   <o> MOSI Pin <0=>Not Used <1=>P1.6
#define   DEV_SPI1_MOSI_PORT_ID        0
#if      (DEV_SPI1_MOSI_PORT_ID == 0)
  #define DEV_SPI1_MOSI                0
#elif    (DEV_SPI1_MOSI_PORT_ID == 1)
  #define DEV_SPI1_MOSI                1
  #define DEV_SPI1_MOSI_PORT           &Driver_GPIO1
  #define DEV_SPI1_MOSI_PIN            GPIO_PIN_6
  #define DEV_SPI1_MOSI_FUNC           GPIO_PIN_FUNC_2
#else
  #error "Invalid SPI1 MOSI Pin Configuration!"
#endif

//   <o> CS Pin <0=>Not Used <1=>P1.7
#define   DEV_SPI1_CS_PORT_ID          0
#if      (DEV_SPI1_CS_PORT_ID == 0)
  #define DEV_SPI1_CS                  0
#elif    (DEV_SPI1_CS_PORT_ID == 1)
  #define DEV_SPI1_CS                  1
  #define DEV_SPI1_CS_PORT             &Driver_GPIO1
  #define DEV_SPI1_CS_PIN              GPIO_PIN_7
  #define DEV_SPI1_CS_FUNC             GPIO_PIN_FUNC_2
#else
  #error "Invalid SPI1 CS Pin Configuration!"
#endif

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_SPI1_INT_PRIO              4

// </e>

#endif  /* __DEVICE_CONFIG_H */
