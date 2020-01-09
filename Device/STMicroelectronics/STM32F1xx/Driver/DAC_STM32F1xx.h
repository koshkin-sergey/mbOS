/*
 * Copyright (C) 2018-2020 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: DAC Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef DAC_STM32F1XX_H_
#define DAC_STM32F1XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

#include "device_config.h"
#include "asm/stm32f1xx.h"
#include "asm/RCC_STM32F1xx.h"
#include "asm/GPIO_STM32F1xx.h"
#include "asm/DMA_STM32F1xx.h"
#include "asm/Driver_DAC.h"


#if defined(STM32F100xB) || defined(STM32F100xE) || \
    defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define _RCC_PERIPH_x(x)              RCC_PERIPH_TIM##x
#define  RCC_PERIPH_x(x)             _RCC_PERIPH_x(x)

#define _TIMx(x)                      TIM##x
#define  TIMx(x)                     _TIMx(x)

#define _TIMx_IRQn(x)                 TIM##x##_IRQn
#define  TIMx_IRQn(x)                _TIMx_IRQn(x)

#define DAC_TRIGGER_TIM6              (0UL << DAC_CR_TSEL1_Pos)
#define DAC_TRIGGER_TIM7              (2UL << DAC_CR_TSEL1_Pos)
#define DAC_TRIGGER_SOFTWARE          (7UL << DAC_CR_TSEL1_Pos)

/* DAC configuration definitions */
#if (DEV_DAC1 == 1)
  #define USE_DAC1

  #if (DEV_DAC1_CH1_DMA == 1)
    #define DAC1_CH1_DMA_Instance    DMAx_CHANNELy(DEV_DAC1_CH1_DMA_NUMBER, DEV_DAC1_CH1_DMA_CHANNEL)
    #define DAC1_CH1_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_DAC1_CH1_DMA_NUMBER, DEV_DAC1_CH1_DMA_CHANNEL)
    #define DAC1_CH1_DMA_Channel     DEV_DAC1_CH1_DMA_CHANNEL
    #define DAC1_CH1_DMA_Priority    DEV_DAC1_CH1_DMA_PRIORITY

    #define DAC1_CH1_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_DAC1_CH1_DMA_NUMBER, DEV_DAC1_CH1_DMA_CHANNEL)
  #endif

  #if (DEV_DAC1_CH2_DMA == 1)
    #define DAC1_CH2_DMA_Instance    DMAx_CHANNELy(DEV_DAC1_CH2_DMA_NUMBER, DEV_DAC1_CH2_DMA_CHANNEL)
    #define DAC1_CH2_DMA_IRQn        DMAx_CHANNELy_IRQn(DEV_DAC1_CH2_DMA_NUMBER, DEV_DAC1_CH2_DMA_CHANNEL)
    #define DAC1_CH2_DMA_Channel     DEV_DAC1_CH2_DMA_CHANNEL
    #define DAC1_CH2_DMA_Priority    DEV_DAC1_CH2_DMA_PRIORITY

    #define DAC1_CH2_DMA_Handler     DMAx_CHANNELy_EVENT(DEV_DAC1_CH2_DMA_NUMBER, DEV_DAC1_CH2_DMA_CHANNEL)
  #endif

  #if (DEV_DAC1_CH1_OUT == 1)
    #define USE_DAC1_CH1_OUT_Pin     1U
    #define DAC1_CH1_OUT_GPIOx       DEV_DAC1_CH1_OUT_PORT
    #define DAC1_CH1_OUT_GPIO_Pin    DEV_DAC1_CH1_OUT_BIT
  #endif

  #if (DEV_DAC1_CH2_OUT == 1)
    #define USE_DAC1_CH2_OUT_Pin     1U
    #define DAC1_CH2_OUT_GPIOx       DEV_DAC1_CH2_OUT_PORT
    #define DAC1_CH2_OUT_GPIO_Pin    DEV_DAC1_CH2_OUT_BIT
  #endif

  #if (DEV_DAC1_TRIGGER_HARDWARE == 1)
    #define DAC1_TRG_TIMER_Instance  TIMx(DEV_DAC1_TRIGGER_SELECT)
    #define DAC1_TRG_TIMER_Periph    RCC_PERIPH_x(DEV_DAC1_TRIGGER_SELECT)
    #define DAC1_TRG_TIMER_IRQn      TIMx_IRQn(DEV_DAC1_TRIGGER_SELECT)
  #endif
#endif

#if defined(USE_DAC1) && defined(DAC1_CH1_DMA_Instance)
#define __DAC_DMA_CH1
#endif

#if defined(USE_DAC1) && defined(DAC1_CH2_DMA_Instance)
#define __DAC_DMA_CH2
#endif

/* Current driver status flag definition */
#define DAC_INITIALIZED           ((uint8_t)(1U << 0U))   /* DAC initialized */
#define DAC_POWERED               ((uint8_t)(1U << 1U))   /* DAC powered on  */
#define DAC_CONFIGURED            ((uint8_t)(1U << 2U))   /* DAC configured  */

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* DAC Dma */
typedef const DMA_INFO DAC_DMA;

/* DAC pin */
typedef const struct _DAC_PIN {
  GPIO_PORT_t           port;           /* Port */
  GPIO_PIN_t            pin;            /* Pin  */
} DAC_PIN;

/* DAC Input/Output Configuration */
typedef const struct _DAC_IO {
  DAC_PIN              *ch1_out;        /* Pointer to channel 1 out pin configuration */
  DAC_PIN              *ch2_out;        /* Pointer to channel 2 out pin configuration */
} DAC_IO;

typedef struct DAC_Status_s {
  uint8_t busy;
} DAC_Status_t;

/* DAC Information (Run-time) */
typedef struct _DAC_INFO {
  DAC_SignalEvent_t     cb_event;       /* Event Callback    */
  DAC_Status_t          status;         /* Status flags      */
  uint8_t               state;          /* Current DAC state */
  uint32_t              mode;           /* Current DAC mode  */
} DAC_INFO;

/* DAC Transfer Information (Run-Time) */
typedef struct _DAC_TRANSFER_INFO {
  uint32_t              num;            /* Total number of transfers */
  uint32_t             *buf;            /* Pointer to data buffer    */
  uint32_t              cnt;            /* Number of data sent       */
} DAC_TRANSFER_INFO;

typedef const struct _DAC_TRIGGER {
  TIM_TypeDef          *reg;            /* Timer peripheral pointer */
  RCC_Periph_t          periph;         /* Timer peripheral         */
  IRQn_Type             irq_num;        /* Timer IRQ Number         */
} DAC_TRIGGER;

/* DAC Resources definition */
typedef struct _DAC_RESOURCES {
  DAC_TypeDef          *reg;            /* DAC peripheral pointer   */
  RCC_Periph_t          periph;         /* Peripheral               */
  DAC_TRIGGER          *trigger;        /* DAC Trigger              */
  DAC_IO                io;             /* DAC Output pins          */
  DAC_DMA              *ch1_dma;        /* Channel 1 DMA interface  */
  DAC_DMA              *ch2_dma;        /* Channel 2 DMA interface  */
  DAC_INFO             *info;           /* Run-Time Information     */
  DAC_TRANSFER_INFO    *xfer;           /* DAC transfer information */
} DAC_RESOURCES;

#endif

#endif /* DAC_STM32F10X_H_ */

/* ----------------------------- End of file ---------------------------------*/
