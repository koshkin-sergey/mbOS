/*
 * Copyright (C) 2018-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: EXTI Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef EXTI_STM32F4XX_H_
#define EXTI_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef void (*EXTI_SignalEvent_t)(void);

typedef enum {
  EXTI_LINE_0             = 0,
  EXTI_LINE_1             = 1,
  EXTI_LINE_2             = 2,
  EXTI_LINE_3             = 3,
  EXTI_LINE_4             = 4,
  EXTI_LINE_5             = 5,
  EXTI_LINE_6             = 6,
  EXTI_LINE_7             = 7,
  EXTI_LINE_8             = 8,
  EXTI_LINE_9             = 9,
  EXTI_LINE_10            = 10,
  EXTI_LINE_11            = 11,
  EXTI_LINE_12            = 12,
  EXTI_LINE_13            = 13,
  EXTI_LINE_14            = 14,
  EXTI_LINE_15            = 15,
  EXTI_PVD                = 16,
  EXTI_RTC_ALARM          = 17,
#if defined(STM32F401xC) || defined(STM32F401xE) ||                                                 \
    defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F411xE) ||                                                                         \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_USB_OTG_FS_WAKEUP  = 18,
#endif
#if defined(STM32F407xx) || defined(STM32F417xx) ||                                                 \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_ETHERNET_WAKEUP    = 19,
#endif
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_USB_OTG_HS_WAKEUP  = 20,
#endif
  EXTI_RTC_TAMPER_STAMP   = 21,
  EXTI_RTC_WAKEUP         = 22,
  EXTI_LINE_NUMBER
} EXTI_Line_t;

typedef enum {
  EXTI_PORT_A = 0,
  EXTI_PORT_B = 1,
  EXTI_PORT_C = 2,
#if defined(STM32F401xC) || defined(STM32F401xE) ||                                                 \
    defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F411xE) ||                                                                         \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_PORT_D = 3,
  EXTI_PORT_E = 4,
#endif
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_PORT_F = 5,
  EXTI_PORT_G = 6,
#endif
  EXTI_PORT_H = 7,
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_PORT_I = 8,
#endif
#if defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  EXTI_PORT_J = 9,
  EXTI_PORT_K = 10,
#endif
} EXTI_Port_t;

typedef enum {
  EXTI_MODE_INTERRUPT,
  EXTI_MODE_EVENT,
  EXTI_MODE_INTERRUPT_EVENT,
} EXTI_Mode_t;

typedef enum {
  EXTI_TRIGGER_RISING,
  EXTI_TRIGGER_FALLING,
  EXTI_TRIGGER_RISING_FALLING,
} EXTI_trigger_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn          void EXTI_Initialize(EXTI_Line_t line, EXTI_Mode_t mode, EXTI_trigger_t trigger, EXTI_SignalEvent_t cb)
 * @brief
 * @param[in]   line
 * @param[in]   mode
 * @param[in]   trigger
 * @param[in]   cb
 */
void EXTI_Initialize(EXTI_Line_t line, EXTI_Mode_t mode, EXTI_trigger_t trigger, EXTI_SignalEvent_t cb);

/**
 * @fn          void EXTI_Uninitialize(EXTI_Line_t line)
 * @brief
 * @param[in]   line
 */
void EXTI_Uninitialize(EXTI_Line_t line);

/**
 * @fn          void EXTI_LineMapping(EXTI_Line_t line, EXTI_Port_t port)
 * @brief
 * @param[in]   line
 * @param[in]   port
 */
void EXTI_LineMapping(EXTI_Line_t line, EXTI_Port_t port);

/**
 * @fn          void EXTI_SoftwareRequest(EXTI_Line_t line)
 * @brief
 * @param[in]   line
 */
void EXTI_SoftwareRequest(EXTI_Line_t line);

#endif /* EXTI_STM32F4XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
