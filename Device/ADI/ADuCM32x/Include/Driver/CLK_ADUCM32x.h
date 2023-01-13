/*
 * Copyright (C) 2017-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#define CLK_SPLL_SRC_HFOSC            (0U)
#define CLK_SPLL_SRC_HFXTAL           (1U)

#define CLK_UCLK_SRC_HFOSC            (0U)
#define CLK_UCLK_SRC_SPLL             (1U)
#define CLK_UCLK_SRC_ECLKIN           (3U)

#define CLK_HCLK_DIV_1                (0U)
#define CLK_HCLK_DIV_2                (1U)
#define CLK_HCLK_DIV_4                (2U)
#define CLK_HCLK_DIV_8                (3U)
#define CLK_HCLK_DIV_16               (4U)
#define CLK_HCLK_DIV_32               (5U)
#define CLK_HCLK_DIV_64               (6U)
#define CLK_HCLK_DIV_128              (7U)

#define CLK_PCLK_DIV_4                (2U)
#define CLK_PCLK_DIV_8                (3U)
#define CLK_PCLK_DIV_16               (4U)
#define CLK_PCLK_DIV_32               (5U)
#define CLK_PCLK_DIV_64               (6U)
#define CLK_PCLK_DIV_128              (7U)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef enum CLK_Freq {
  CLK_FREQ_HCLK = 0U,
  CLK_FREQ_PCLK = 1U,
  CLK_FREQ_ACLK = 2U
} CLK_Freq_t;

typedef enum CLK_Periph {
  CLK_PERIPH_SPI0 = (1U << 0U),
  CLK_PERIPH_SPI1 = (1U << 1U),
  CLK_PERIPH_I2C0 = (1U << 3U),
  CLK_PERIPH_I2C1 = (1U << 4U),
  CLK_PERIPH_UART = (1U << 5U)
} CLK_Periph_t;

typedef struct CLK_Cfg {
  uint32_t SPLL_src;
  uint32_t UCLK_src;
  uint32_t HCLK_div;
  uint32_t PCLK_div;
} CLK_Cfg_t;

/**
 * Function documentation
 *
 * @fn          void ClkReset(void)
 * @brief       Setup the clock system. Initialize the default clock
 *              source.
 *
 * @fn          void ClkConfig(const CLK_Cfg_t *cfg)
 * @brief       Initializes the CPU clock according to the specified
 *              parameters in the cfg argument.
 * @param[in]   cfg   CLK_Cfg_t structure that contains the configuration
 *                    information for the clock system.
 *
 * @fn          uint32_t GetFrequency(CLK_Freq_t type)
 * @brief       Gets Clock Frequency.
 * @param[in]   type  CLK_Freq_t.
 * @return      Returns clock frequency in Hz.
 *
 * @fn          void PeriphEnable(CLK_Periph_t periph)
 * @brief       Enables the peripheral specified by the periph argument.
 * @param[in]   periph  CLK_Periph_t.
 *
 * @fn          void PeriphDisable(CLK_Periph_t periph)
 * @brief       Disables the peripheral specified by the periph argument.
 * @param[in]   periph  CLK_Periph_t.
 *
 * @fn          uint32_t GetStatePeriph(CLK_Periph_t periph)
 * @brief       Gets the current state of the peripheral specified
 *              by the periph argument.
 * @param[in]   periph  CLK_Periph_t.
 * @return      Returns state of the peripheral:
 *                0 - The peripheral is disabled;
 *                1 - The peripheral is enabled.
 */

/**
 * @brief Access structure of the CLK Driver.
 */
typedef struct Driver_CLK {
  void     (*ClkReset)      (void);
  void     (*ClkConfig)     (const CLK_Cfg_t *cfg);
  uint32_t (*GetFrequency)  (CLK_Freq_t   type);
  void     (*PeriphEnable)  (CLK_Periph_t periph);
  void     (*PeriphDisable) (CLK_Periph_t periph);
  uint32_t (*GetStatePeriph)(CLK_Periph_t periph);
} const Driver_CLK_t;

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern Driver_CLK_t Driver_CLK;

#endif /* CLK_ADUCM32X_H_ */
