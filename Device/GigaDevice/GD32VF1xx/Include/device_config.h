/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for GigaDevice GD32VF103xx
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
#define CLK_LO_INT_VALUE                40000

//   <o> Low-Frequency External Clock (Hz)  <1-999999999>
//   <i> Low-Frequency External Clock
#define CLK_LO_EXT_VALUE                32768

//   <o> High-Frequency Internal Clock (Hz) <1-999999999>
//   <i> High-Frequency Internal Clock
#define CLK_HI_INT_VALUE                8000000

//   <o> High-Frequency External Clock (Hz) <1-999999999>
//   <i> High-Frequency External Clock
#define CLK_HI_EXT_VALUE                25000000
// </h>


#endif  /* __DEVICE_CONFIG_H */
