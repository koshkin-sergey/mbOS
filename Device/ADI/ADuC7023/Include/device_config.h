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

// <e> I2C0 (Inter-integrated Circuit Interface) [Driver_I2C0]
// <i> Configuration settings for Driver_I2C0 in component ::CMSIS Driver:I2C
#define DEV_I2C0                        1

//   <o> I2C0_SCL Pin <0=>P0.4
#define   DEV_I2C0_SCL_PORT_ID         0
#if      (DEV_I2C0_SCL_PORT_ID == 0)
  #define DEV_I2C0_SCL_PORT            &DRIVER_GPIO0
  #define DEV_I2C0_SCL_PIN             GPIO_PIN_4
  #define DEV_I2C0_SCL_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C0_SCL Pin Configuration!"
#endif

//   <o> I2C0_SDA Pin <0=>P0.5
#define   DEV_I2C0_SDA_PORT_ID         0
#if      (DEV_I2C0_SDA_PORT_ID == 0)
  #define DEV_I2C0_SDA_PORT            &DRIVER_GPIO0
  #define DEV_I2C0_SDA_PIN             GPIO_PIN_5
  #define DEV_I2C0_SDA_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C0_SDA Pin Configuration!"
#endif

// </e>

// <e> I2C1 (Inter-integrated Circuit Interface) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::CMSIS Driver:I2C
#define DEV_I2C1                        1

//   <o> I2C1_SCL Pin <0=>P0.6 <1=>P1.6
#define   DEV_I2C1_SCL_PORT_ID         0
#if      (DEV_I2C1_SCL_PORT_ID == 0)
  #define DEV_I2C1_SCL_PORT            &DRIVER_GPIO0
  #define DEV_I2C1_SCL_PIN             GPIO_PIN_6
  #define DEV_I2C1_SCL_FUNC            GPIO_PIN_FUNC_2
#elif    (DEV_I2C1_SCL_PORT_ID == 1)
  #define DEV_I2C1_SCL_PORT            &DRIVER_GPIO1
  #define DEV_I2C1_SCL_PIN             GPIO_PIN_6
  #define DEV_I2C1_SCL_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1_SCL Pin Configuration!"
#endif

//   <o> I2C1_SDA Pin <0=>P0.7 <1=>P1.7
#define   DEV_I2C1_SDA_PORT_ID         0
#if      (DEV_I2C1_SDA_PORT_ID == 0)
  #define DEV_I2C1_SDA_PORT            &DRIVER_GPIO0
  #define DEV_I2C1_SDA_PIN             GPIO_PIN_7
  #define DEV_I2C1_SDA_FUNC            GPIO_PIN_FUNC_2
#elif    (DEV_I2C1_SDA_PORT_ID == 1)
  #define DEV_I2C1_SDA_PORT            &DRIVER_GPIO1
  #define DEV_I2C1_SDA_PIN             GPIO_PIN_7
  #define DEV_I2C1_SDA_FUNC            GPIO_PIN_FUNC_1
#else
  #error "Invalid I2C1_SDA Pin Configuration!"
#endif

// </e>

#endif  /* __DEVICE_CONFIG_H */
