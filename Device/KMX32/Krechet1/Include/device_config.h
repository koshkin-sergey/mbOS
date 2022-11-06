/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for KM211 Krechet1
 */

#ifndef __DEVICE_CONFIG_H
#define __DEVICE_CONFIG_H

#define _Interruptx_Handler(x)    Interrupt##x##_Handler
#define  Interruptx_Handler(x)    _Interruptx_Handler(x)

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h> Clock Configuration
//   <o> Low-speed Internal Clock (Hz)  <1-999999999>
#define RC_CLK_VALUE                    11000000
//   <o> High-speed Internal Clock (Hz) <1-999999999>
#define HRC_CLK_VALUE                   40000000
//   <o> External Clock (Hz)            <1-999999999>
#define XT_CLK_VALUE                    24000000
// </h>


// <e> I2C0 (Inter-integrated Circuit Interface) [Driver_I2C0]
// <i> Configuration settings for Driver_I2C0 in component ::CMSIS Driver:I2C
#define DEV_I2C0                       1

//   <o> Interrupt Priority <3=>3 High <4=>4 Above_Normal_3 <5=>5 Above_Normal_2 <6=>6 Above_Normal_1
//                          <7=>7 Above_Normal <8=>8 Normal_4 <9=>9 Normal_3 <10=>10 Normal_2
//                          <11=>11 Normal_1 <12=>12 Normal <13=>13 Below_Normal_4 <14=>14 Below_Normal_3
//                          <15=>15 Below_Normal_2 <16=>16 Below_Normal_1 <17=>17 Below_Normal <18=>18 Low_3
//                          <19=>19 Low_2 <20=>20 Low_1 <21=>21 Low
#define DEV_I2C0_INT_PRIO              9
// </e>

// <e> I2C1 (Inter-integrated Circuit Interface) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::CMSIS Driver:I2C
#define DEV_I2C1                       1

//   <o> Interrupt Priority <3=>3 High <4=>4 Above_Normal_3 <5=>5 Above_Normal_2 <6=>6 Above_Normal_1
//                          <7=>7 Above_Normal <8=>8 Normal_4 <9=>9 Normal_3 <10=>10 Normal_2
//                          <11=>11 Normal_1 <12=>12 Normal <13=>13 Below_Normal_4 <14=>14 Below_Normal_3
//                          <15=>15 Below_Normal_2 <16=>16 Below_Normal_1 <17=>17 Below_Normal <18=>18 Low_3
//                          <19=>19 Low_2 <20=>20 Low_1 <21=>21 Low
#define DEV_I2C1_INT_PRIO              10
// </e>

#endif  /* __DEVICE_CONFIG_H */

/* ----------------------------- End of file ---------------------------------*/
