/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef ADSU_KRECHET1_H_
#define ADSU_KRECHET1_H_

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define OSC_DISABLE                 (0U)
#define OSC_ENABLE                  (1U)

#define CLK_SRC_RC                  (0U)
#define CLK_SRC_XT                  (1U)
#define CLK_SRC_HRC                 (2U)

#define CLK_DIV_1                   (0U)
#define CLK_DIV_2                   (1U)
#define CLK_DIV_4                   (2U)
#define CLK_DIV_8                   (3U)
#define CLK_DIV_16                  (4U)

#define CLK_OUT_DISABLE             (0U)
#define CLK_OUT_ENABLE              (1U)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct ADSU_OscCfg {
  uint32_t RC_Enable  : 1;
  uint32_t XT_Enable  : 1;
  uint32_t HRC_Enable : 1;
  uint32_t Reserved   : 29;
} ADSU_OscCfg_t;

typedef struct ADSU_ClkCfg {
  uint32_t clk_src    : 2;
  uint32_t clk_div    : 3;
  uint32_t clk_out_en : 1;
  uint32_t Reserved   : 26;
} ADSU_ClkCfg_t;

typedef enum ADSU_Freq {
  ADSU_FREQ_RC,
  ADSU_FREQ_HRC,
  ADSU_FREQ_XT,
  ADSU_FREQ_OSC,
  ADSU_FREQ_SYS,
  ADSU_FREQ_Reserved = 0x7FFFFFFF
} ADSU_Freq_t;

typedef enum ADSU_Periph {
  ADSU_Periph_FMCU  = (1UL << 3U),
  ADSU_Periph_TMR0  = (1UL << 12U),
  ADSU_Periph_TMR1  = (1UL << 13U),
  ADSU_Periph_PWM0  = (1UL << 14U),
  ADSU_Periph_PWM1  = (1UL << 15U),
  ADSU_Periph_GPIO  = (1UL << 16U),
  ADSU_Periph_SPI0  = (1UL << 23U),
  ADSU_Periph_SPI1  = (1UL << 24U),
  ADSU_Periph_UART0 = (1UL << 25U),
  ADSU_Periph_UART1 = (1UL << 26U),
  ADSU_Periph_I2C0  = (1UL << 27U),
  ADSU_Periph_I2C1  = (1UL << 28U),
  ADSU_Periph_UART2 = (1UL << 29U),
  ADSU_Periph_UART3 = (1UL << 30U),
  ADSU_Periph_CHIN  = (1UL << 31U)
} ADSU_Periph_t;

/**
 * Function documentation
 *
 * @fn          void ADSU_ClkReset(void)
 * @brief       Setup the clock system. Initialize the default clock
 *              source.
 *
 * @fn          void ADSU_OscConfig(ADSU_OscCfg_t cfg)
 * @brief       Initializes the Oscillators according to the specified
 *              parameters in the cfg argument.
 * @param[in]   cfg   ADSU_OscCfg_t structure that contains the configuration
 *                    information for the Oscillators.
 *
 * @fn          void ADSU_ClkConfig(ADSU_ClkCfg_t cfg)
 * @brief       Initializes the CPU clock according to the specified
 *              parameters in the cfg argument.
 * @param[in]   cfg   ADSU_ClkCfg_t structure that contains the configuration
 *                    information for the clock system.
 *
 * @fn          uint32_t ADSU_GetFrequency(ADSU_Freq_t type)
 * @brief       Gets Clock Frequency.
 * @param[in]   type  ADSU_Freq_t.
 * @return      Returns clock frequency in Hz.
 *
 * @fn          void ADSU_PeriphEnable(ADSU_Periph_t periph)
 * @brief       Enables the peripheral specified by the periph argument.
 * @param[in]   periph  ADSU_Periph_t.
 *
 * @fn          void ADSU_PeriphDisable(ADSU_Periph_t periph)
 * @brief       Disables the peripheral specified by the periph argument.
 * @param[in]   periph  ADSU_Periph_t.
 *
 * @fn          uint32_t ADSU_GetStatePeriph(ADSU_Periph_t periph)
 * @brief       Gets the current state of the peripheral specified
 *              by the periph argument.
 * @param[in]   periph  ADSU_Periph_t.
 * @return      Returns state of the peripheral:
 *                0 - The peripheral is disabled;
 *                1 - The peripheral is enabled.
 *
 * @fn          void ADSU_PeriphReset(ADSU_Periph_t periph)
 * @brief       Resets the peripheral specified by the periph argument.
 * @param[in]   periph  ADSU_Periph_t.
 */

/**
 * @brief Access structure of the ADSU Driver.
 */
typedef struct Driver_ADSU {
  void     (*ClkReset)      (void);
  void     (*OscConfig)     (ADSU_OscCfg_t cfg);
  void     (*ClkConfig)     (ADSU_ClkCfg_t cfg);
  uint32_t (*GetFrequency)  (ADSU_Freq_t   type);
  void     (*PeriphEnable)  (ADSU_Periph_t periph);
  void     (*PeriphDisable) (ADSU_Periph_t periph);
  uint32_t (*GetStatePeriph)(ADSU_Periph_t periph);
  void     (*PeriphReset)   (ADSU_Periph_t periph);
} const Driver_ADSU_t;

#endif /* ADSU_KRECHET1_H_ */
