/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Device Configuration for STMicroelectronics STM32F7xx
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __DEVICE_CONFIG_H
#define __DEVICE_CONFIG_H

// <h> Clock Configuration
//   <o> High-speed Internal Clock <1-999999999>
#define HSI_CLK                         16000000
//   <o> High-speed External Clock <1-999999999>
#define HSE_CLK                         8000000
// </h>

/* Interrupt Priority */
#define I2C_INT_PRIORITY                (1U)
#define I2S_INT_PRIORITY                (1U)
#define USART_INT_PRIORITY              (1U)
#define SPI_INT_PRIORITY                (1U)
#define DMA_INT_PRIORITY                (1U)
#define EXTI_INT_PRIORITY               (1U)
#define DAC_INT_PRIORITY                (1U)

#endif  /* __DEVICE_CONFIG_H */

/* ----------------------------- End of file ---------------------------------*/
