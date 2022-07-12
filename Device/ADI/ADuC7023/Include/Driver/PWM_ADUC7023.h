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

#ifndef PWM_ADUC7023_H_
#define PWM_ADUC7023_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

#include <asm/aduc7023.h>
#include <device_config.h>
#include <Driver/GPIO_ADUC7023.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* The number of PWM pins */
#define PWM_PIN_NUM                 (7U)

/* PWM configuration definitions */
#if defined (DEV_PWM) && (DEV_PWM == 1)
  #define USE_PWM

  #if !defined(PWM)
    #error "PWM not available for selected device!"
    #undef USE_PWM
  #endif

  #if defined (DEV_PWM_OUT0) && (DEV_PWM_OUT0 == 1)
    #define USE_PWM_OUT0
    #define PWM_OUT0_GPIO_PORT      DEV_PWM_OUT0_PORT
    #define PWM_OUT0_GPIO_PIN       DEV_PWM_OUT0_PIN
    #define PWM_OUT0_GPIO_FUNC      DEV_PWM_OUT0_FUNC
  #endif

  #if defined (DEV_PWM_OUT1) && (DEV_PWM_OUT1 == 1)
    #define USE_PWM_OUT1
    #define PWM_OUT1_GPIO_PORT      DEV_PWM_OUT1_PORT
    #define PWM_OUT1_GPIO_PIN       DEV_PWM_OUT1_PIN
    #define PWM_OUT1_GPIO_FUNC      DEV_PWM_OUT1_FUNC
  #endif

  #if defined (DEV_PWM_OUT2) && (DEV_PWM_OUT2 == 1)
    #define USE_PWM_OUT2
    #define PWM_OUT2_GPIO_PORT      DEV_PWM_OUT2_PORT
    #define PWM_OUT2_GPIO_PIN       DEV_PWM_OUT2_PIN
    #define PWM_OUT2_GPIO_FUNC      DEV_PWM_OUT2_FUNC
  #endif

  #if defined (DEV_PWM_OUT3) && (DEV_PWM_OUT3 == 1)
    #define USE_PWM_OUT3
    #define PWM_OUT3_GPIO_PORT      DEV_PWM_OUT3_PORT
    #define PWM_OUT3_GPIO_PIN       DEV_PWM_OUT3_PIN
    #define PWM_OUT3_GPIO_FUNC      DEV_PWM_OUT3_FUNC
  #endif

  #if defined (DEV_PWM_OUT4) && (DEV_PWM_OUT4 == 1)
    #define USE_PWM_OUT4
    #define PWM_OUT4_GPIO_PORT      DEV_PWM_OUT4_PORT
    #define PWM_OUT4_GPIO_PIN       DEV_PWM_OUT4_PIN
    #define PWM_OUT4_GPIO_FUNC      DEV_PWM_OUT4_FUNC
  #endif

  #if defined (DEV_PWM_TRIP) && (DEV_PWM_TRIP == 1)
    #define USE_PWM_TRIP
    #define PWM_TRIP_GPIO_PORT      DEV_PWM_TRIP_PORT
    #define PWM_TRIP_GPIO_PIN       DEV_PWM_TRIP_PIN
    #define PWM_TRIP_GPIO_FUNC      DEV_PWM_TRIP_FUNC
  #endif

  #if defined (DEV_PWM_SYNC) && (DEV_PWM_SYNC == 1)
    #define USE_PWM_SYNC
    #define PWM_SYNC_GPIO_PORT      DEV_PWM_SYNC_PORT
    #define PWM_SYNC_GPIO_PIN       DEV_PWM_SYNC_PIN
    #define PWM_SYNC_GPIO_FUNC      DEV_PWM_SYNC_FUNC
  #endif

  #if   (DEV_PWM_CLK_PSC == 0)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_2
  #elif (DEV_PWM_CLK_PSC == 1)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_4
  #elif (DEV_PWM_CLK_PSC == 2)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_8
  #elif (DEV_PWM_CLK_PSC == 3)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_16
  #elif (DEV_PWM_CLK_PSC == 4)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_32
  #elif (DEV_PWM_CLK_PSC == 5)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_64
  #elif (DEV_PWM_CLK_PSC == 6)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_128
  #elif (DEV_PWM_CLK_PSC == 7)
    #define PWM_CLK_PRESCALE          PWMCON1_PWMCP_DIV_256
  #else
    #error "PWM prescaler selection error!"
  #endif
#endif

/****** PWM error codes *****/
#define PWM_DRIVER_OK                  0                                        ///< Operation succeeded
#define PWM_DRIVER_ERROR              -1                                        ///< Unspecified error
#define PWM_DRIVER_ERROR_BUSY         -2                                        ///< Driver is busy
#define PWM_DRIVER_ERROR_TIMEOUT      -3                                        ///< Timeout occurred
#define PWM_DRIVER_ERROR_UNSUPPORTED  -4                                        ///< Operation not supported
#define PWM_DRIVER_ERROR_PARAMETER    -5                                        ///< Parameter error

/****** Current driver status flag definition *****/
#define PWM_FLAG_INITIALIZED          (1UL << 0)                                ///< PWM initialized
#define PWM_FLAG_POWERED              (1UL << 1)                                ///< PWM powered on
#define PWM_FLAG_CONFIGURED           (1UL << 2)                                ///< PWM is configured
#define PWM_FLAG_ENABLE               (1UL << 3)                                ///< PWM is enabled

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* PWM Pin */
typedef const struct _PWM_PIN {
  DRIVER_GPIO          *gpio;               // Pointer to GPIO driver
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
} PWM_PIN;

/* PWM Information (Run-Time) */
typedef struct _PWM_INFO {
  uint32_t              flags;              // Current state flags
} PWM_INFO;

/* PWM Resource Configuration */
typedef struct {
  PWM_t                 *reg;               // PWM peripheral register interface
  PWM_PIN  *pin[PWM_PIN_NUM];               // PWM pins
  PWM_INFO             *info;               // Run-Time information
} const PWM_RESOURCES;

/**
 * Function documentation
 *
 * @fn          int32_t PWM_Initialize(void)
 * @brief       Initialize Pulse-Width Modulator.
 * @return      Execution status
 *
 */

/**
 * @brief Access structure of the pwm Driver.
 */
typedef struct Driver_PWM {
  int32_t (*Initialize)   (void);
  int32_t (*Uninitialize) (void);
  int32_t (*Control)      (uint32_t control, uint32_t arg);
} const Driver_PWM_t;

#endif /* PWM_ADUC7023_H_ */
