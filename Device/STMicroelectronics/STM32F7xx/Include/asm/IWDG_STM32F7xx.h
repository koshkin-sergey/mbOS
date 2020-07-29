/******************************************************************************
 * @file    IWDG_STM32F7xx.h
 * @brief   This file provides IWDG driver for STMicroelectronics STM32F7xx.
 * @author  Sergey Koshkin
 * @version V1.0.0
 ******************************************************************************/
/*
 * Copyright (C) 2020 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

#ifndef IWDG_STM32F7XX_H_
#define IWDG_STM32F7XX_H_

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* Return codes */
#define IWDG_DRIVER_OK                  0     ///< Operation succeeded
#define IWDG_DRIVER_ERROR              -1     ///< Unspecified error
#define IWDG_DRIVER_ERROR_PARAMETER    -2     ///< Parameter error

/**
 * @brief  IWDG Key Register BitMask
 */
#define IWDG_KEY_RELOAD                 0x0000AAAAUL  /*!< IWDG Reload Counter Enable   */
#define IWDG_KEY_ENABLE                 0x0000CCCCUL  /*!< IWDG Peripheral Enable       */
#define IWDG_KEY_WRITE_ACCESS_ENABLE    0x00005555UL  /*!< IWDG KR Write Access Enable  */
#define IWDG_KEY_WRITE_ACCESS_DISABLE   0x00000000UL  /*!< IWDG KR Write Access Disable */

/**
 * @brief  IWDG Prescaler
 */
#define IWDG_PRESCALER_4                0x00000000u                                     /*!< IWDG prescaler set to 4   */
#define IWDG_PRESCALER_8                IWDG_PR_PR_0                                    /*!< IWDG prescaler set to 8   */
#define IWDG_PRESCALER_16               IWDG_PR_PR_1                                    /*!< IWDG prescaler set to 16  */
#define IWDG_PRESCALER_32               (IWDG_PR_PR_1 | IWDG_PR_PR_0)                   /*!< IWDG prescaler set to 32  */
#define IWDG_PRESCALER_64               IWDG_PR_PR_2                                    /*!< IWDG prescaler set to 64  */
#define IWDG_PRESCALER_128              (IWDG_PR_PR_2 | IWDG_PR_PR_0)                   /*!< IWDG prescaler set to 128 */
#define IWDG_PRESCALER_256              (IWDG_PR_PR_2 | IWDG_PR_PR_1)                   /*!< IWDG prescaler set to 256 */

/**
 * @brief  IWDG Window option
 */
#define IWDG_WINDOW_DISABLE             IWDG_WINR_WIN

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @struct IWDG_Init_s
 * @brief  IWDG Init structure definition
 */
typedef struct IWDG_Init_s {
  uint32_t Prescaler;  /*!< Select the prescaler of the IWDG.
                            This parameter can be a value of @ref IWDG_Prescaler */
  uint32_t Reload;     /*!< Specifies the IWDG down-counter reload value.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
  uint32_t Window;     /*!< Specifies the window value to be compared to the down-counter.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
} IWDG_Init_t;

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn          int32_t IWDG_Initialize(IWDG_Init_t*)
 * @brief       Initialize the IWDG according to the specified parameters in the
 *              IWDG_Init_t and start watchdog.
 *
 * @param[in]   init  Pointer to a IWDG_Init_t structure that contains
 *                    the configuration information.
 * @return      Execution status
 */
int32_t IWDG_Initialize(const IWDG_Init_t *init);

/**
 * @fn          int32_t IWDG_Reload(void)
 * @brief       Reload the IWDG.
 *
 * @return      Execution status
 */
int32_t IWDG_Reload(void);

#endif /* IWDG_STM32F7XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
