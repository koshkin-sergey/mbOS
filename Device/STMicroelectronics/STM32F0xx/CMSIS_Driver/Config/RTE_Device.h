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

#if !defined(RTE_HSI)
  #define RTE_HSI         ((uint32_t)8000000)   /* Default value of the Internal oscillator in Hz */
#endif  // RTE_HSI
#if !defined(RTE_HSE)
  #define RTE_HSE         ((uint32_t)8000000)   /* Default value of the External oscillator in Hz */
#endif  // RTE_HSE
#if !defined(RTE_HSI14)
  #define RTE_HSI14       ((uint32_t)14000000)  /* Default value of the HSI14 Internal oscillator in Hz */
#endif  // RTE_HSI14
#if !defined(RTE_HSI48)
  #define RTE_HSI48       ((uint32_t)48000000)  /* Default value of the HSI48 Internal oscillator in Hz */
#endif  // RTE_HSI48

// <e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::Drivers:I2C
#define   RTE_I2C1                      1

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
