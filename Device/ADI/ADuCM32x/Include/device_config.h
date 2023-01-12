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


#endif  /* __DEVICE_CONFIG_H */

/* ----------------------------- End of file ---------------------------------*/
