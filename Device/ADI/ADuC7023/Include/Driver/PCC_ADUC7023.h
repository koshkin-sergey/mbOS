/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
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
 */

#ifndef DRIVER_PCC_H_
#define DRIVER_PCC_H_

#include <stdint.h>

#define PCC_PERIPH_I2C0             0x00000004UL
#define PCC_PERIPH_I2C1             0x00000020UL
#define PCC_PERIPH_SPI              0x00000100UL
#define PCC_PERIPH_PWM              0x00000800UL


typedef uint32_t PCC_Periph_t;

void PCC_ClkReset(void);
void PCC_EnablePeriph(PCC_Periph_t periph);
void PCC_DisablePeriph(PCC_Periph_t periph);

#endif /* DRIVER_PCC_H_ */
