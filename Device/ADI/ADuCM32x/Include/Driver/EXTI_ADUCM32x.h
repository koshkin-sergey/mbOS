/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef EXTI_ADUCM32X_H_
#define EXTI_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/****** EXTI Event *****/
#define EXTI_EVENT_RISING_EDGE        (0U)
#define EXTI_EVENT_FALLING_EDGE       (1U)
#define EXTI_EVENT_RISE_OR_FALL_EDGE  (2U)
#define EXTI_EVENT_HIGH_LEVEL         (3U)
#define EXTI_EVENT_LOW_LEVEL          (4U)

/****** EXTI error codes *****/
#define EXTI_DRIVER_OK                 0                                        ///< Operation succeeded
#define EXTI_DRIVER_ERROR             -1                                        ///< Unspecified error
#define EXTI_DRIVER_ERROR_UNSUPPORTED -2                                        ///< Operation not supported

/****** EXTI Control Codes *****/
#define EXTI_CONTROL_Pos               0
#define EXTI_CONTROL_Msk              (0xFFUL)
#define EXTI_MODE_INACTIVE            (0x00UL << EXTI_CONTROL_Pos)              ///< Disable EXTI
#define EXTI_MODE_ACTIVE              (0x01UL << EXTI_CONTROL_Pos)              ///< Enable and configure EXTI

/*----- EXTI Control Codes: Configuration Parameters: Trigger Mode -----------*/
#define EXTI_TRG_Pos                   8
#define EXTI_TRG_Msk                  (7UL << EXTI_TRG_Pos)
#define EXTI_TRG_RISING_EDGE          (0UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on rising edge (default)
#define EXTI_TRG_FALLING_EDGE         (1UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on falling edge
#define EXTI_TRG_RISE_OR_FALL_EDGE    (2UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on rising or falling edge
#define EXTI_TRG_HIGH_LEVEL           (3UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on high level
#define EXTI_TRG_LOW_LEVEL            (4UL << EXTI_TRG_Pos)                     ///< External IRQ triggers on low level

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @fn          void EXTI_SignalEvent(uint32_t event)
 * @brief       Signal External Interrupt Events.
 * @param[in]   event  Notification mask
 */
typedef void (*EXTI_SignalEvent_t)(uint32_t event);

/**
 * Function documentation
 *
 * @fn          int32_t EXTI_Initialize(EXTI_SignalEvent_t cb_event)
 * @brief       Initialize External Interrupt Interface.
 * @param[in]   cb_event  External Interrupt event hadler.
 * @return      status code that indicates the execution status of the function.
 *
 * @fn          int32_t EXTI_Uninitialize(void)
 * @brief       De-initialize External Interrupt Interface.
 * @return      status code that indicates the execution status of the function.
 *
 * @fn          int32_t EXTI_Control(uint32_t control)
 * @brief       Control External Interrupt Interface.
 * @param[in]   control   Operation.
 * @return      status code that indicates the execution status of the function.
 */

/**
 * @brief Access structure of the EXTI Driver.
 */
typedef struct Driver_EXTI {
  int32_t       (*Initialize)   (EXTI_SignalEvent_t cb_event);
  int32_t       (*Uninitialize) (void);
  int32_t       (*Control)      (uint32_t control);
} const Driver_EXTI_t;

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern Driver_EXTI_t Driver_EXTI0;
extern Driver_EXTI_t Driver_EXTI1;
extern Driver_EXTI_t Driver_EXTI2;
extern Driver_EXTI_t Driver_EXTI4;
extern Driver_EXTI_t Driver_EXTI5;
extern Driver_EXTI_t Driver_EXTI7;
extern Driver_EXTI_t Driver_EXTI8;

#endif /* EXTI_ADUCM32X_H_ */
