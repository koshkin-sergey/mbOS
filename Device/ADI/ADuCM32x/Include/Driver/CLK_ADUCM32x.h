/*
 * Copyright (C) 2017-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Clock Driver Definitions for ADI ADuCM32x
 */

#ifndef CLK_ADUCM32X_H_
#define CLK_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef enum {
  CLK_PERIPH_SPI0 = (1U << 0),
  CLK_PERIPH_SPI1 = (1U << 1),
  CLK_PERIPH_I2C0 = (1U << 3),
  CLK_PERIPH_I2C1 = (1U << 4),
  CLK_PERIPH_UART = (1U << 5),
  CLK_PERIPH_D2D  = (1U << 6),
} CLK_PERIPH;

typedef enum {
  CLOCK_OFF,
  CLOCK_ON,
} CLK_MODE;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

extern
void CLK_SourceHFXTAL(void);
extern
uint32_t CLK_GetFreqHCLK(void);
extern
uint32_t CLK_GetFreqPCLK(void);
extern
uint32_t CLK_GetFreqD2DCLK(void);
extern
void CLK_PeriphGateControl(CLK_PERIPH clk, CLK_MODE mode);

#endif /* CLK_ADUCM32X_H_ */

/* ----------------------------- End of file ---------------------------------*/
