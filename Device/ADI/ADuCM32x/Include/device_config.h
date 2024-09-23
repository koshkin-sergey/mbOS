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
 *  includes
 ******************************************************************************/

#include <Driver/Driver_GPIO.h>

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern Driver_GPIO_t Driver_GPIO0;
extern Driver_GPIO_t Driver_GPIO1;
extern Driver_GPIO_t Driver_GPIO2;
extern Driver_GPIO_t Driver_GPIO3;
extern Driver_GPIO_t Driver_GPIO4;
extern Driver_GPIO_t Driver_GPIO5;

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

// <e> ADC (Analog-To-Digital Converter) [Driver_ADC]
// <i> Configuration settings for Driver_ADC
#define DEV_ADC                         1

//   <e> AIN8
//     <o1> Pin <0=>P4.2
//   </e>
#define DEV_ADC_IN8                     0
#define DEV_ADC_IN8_ID                  0

//   <e> AIN9
//     <o1> Pin <0=>P4.3
//   </e>
#define DEV_ADC_IN9                     0
#define DEV_ADC_IN9_ID                  0

//   <e> AIN12
//     <o1> Pin <0=>P4.4
//   </e>
#define DEV_ADC_IN12                    0
#define DEV_ADC_IN12_ID                 0

//   <e> AIN13
//     <o1> Pin <0=>P4.5
//   </e>
#define DEV_ADC_IN13                    0
#define DEV_ADC_IN13_ID                 0

//   <e> AIN14
//     <o1> Pin <0=>P4.6
//   </e>
#define DEV_ADC_IN14                    0
#define DEV_ADC_IN14_ID                 0

//   <e> AIN15
//     <o1> Pin <0=>P4.7
//   </e>
#define DEV_ADC_IN15                    0
#define DEV_ADC_IN15_ID                 0

//   <e> VREF2V5 OUT (AIN11)
//   <i> Power up 2.5V reference output driving AIN11/BUF_VREF2V5 pin
//     <o1> Source <0=>Internal <1=>External
//     <i> Select reference source for output bufer
//   </e>
#define DEV_VREF2V5_OUT                 0
#define DEV_VREF2V5_OUT_SRC             0

//   <o> Interrupt Priority <0=>Realtime <1=>Above High <2=>High <3=>Above Normal <4=>Normal <5=>Below Normal <6=>Above Low <7=>Low
#define DEV_ADC_INT_PRIO                4

//   <e> DMA
//     <o1> Priority <0=>Normal <1=>High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_ADC_DMA                     0
#define DEV_ADC_DMA_PRIORITY            0

// </e>

// <e> DAC0 (Digital-To-Analog Converter) [Driver_DAC0]
// <i> Configuration settings for Driver_DAC0
#define DEV_DAC0                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC0_OUTPUT_RANGE           0
// </e>

// <e> DAC1 (Digital-To-Analog Converter) [Driver_DAC1]
// <i> Configuration settings for Driver_DAC1
#define DEV_DAC1                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC1_OUTPUT_RANGE           0
// </e>

// <e> DAC2 (Digital-To-Analog Converter) [Driver_DAC2]
// <i> Configuration settings for Driver_DAC2
#define DEV_DAC2                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC2_OUTPUT_RANGE           0
// </e>

// <e> DAC3 (Digital-To-Analog Converter) [Driver_DAC3]
// <i> Configuration settings for Driver_DAC3
#define DEV_DAC3                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC3_OUTPUT_RANGE           0
// </e>

// <e> DAC4 (Digital-To-Analog Converter) [Driver_DAC4]
// <i> Configuration settings for Driver_DAC4
#define DEV_DAC4                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC4_OUTPUT_RANGE           0
// </e>

// <e> DAC5 (Digital-To-Analog Converter) [Driver_DAC5]
// <i> Configuration settings for Driver_DAC5
#define DEV_DAC5                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC5_OUTPUT_RANGE           0
// </e>

// <e> DAC6 (Digital-To-Analog Converter) [Driver_DAC6]
// <i> Configuration settings for Driver_DAC6
#define DEV_DAC6                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC6_OUTPUT_RANGE           0
// </e>

// <e> DAC7 (Digital-To-Analog Converter) [Driver_DAC7]
// <i> Configuration settings for Driver_DAC7
#define DEV_DAC7                        1

//   <o> Output Range <0=>VREF <1=>AVDD
#define DEV_DAC7_OUTPUT_RANGE           0
// </e>

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

//   <e> DMA Rx
//     <o1> Priority <0=>Default <1=>High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_SPI0_RX_DMA                0
#define DEV_SPI0_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Priority <0=>Default <1=>High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_SPI0_TX_DMA                0
#define DEV_SPI0_TX_DMA_PRIORITY       0

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
#define   DEV_SPI1_MISO_PORT_ID        1
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
#define   DEV_SPI1_MOSI_PORT_ID        1
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

//   <e> DMA Rx
//     <o1> Priority <0=>Default <1=>High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_SPI1_RX_DMA                0
#define DEV_SPI1_RX_DMA_PRIORITY       0

//   <e> DMA Tx
//     <o1> Priority <0=>Default <1=>High
//     <i>  Selects DMA Priority
//   </e>
#define DEV_SPI1_TX_DMA                0
#define DEV_SPI1_TX_DMA_PRIORITY       0

// </e>

#endif  /* __DEVICE_CONFIG_H */
