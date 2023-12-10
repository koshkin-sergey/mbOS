/*
 * Copyright (C) 2019-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: USART Driver Definitions for STMicroelectronics STM32F7xx
 */

#ifndef USART_STM32F7XX_H_
#define USART_STM32F7XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <asm/stm32f7xx.h>
#include <Driver/RCC_STM32F7xx.h>
#include <Driver/GPIO_STM32F7xx.h>
#include <Driver/DMA_STM32F7xx.h>

#include <Driver/Driver_USART.h>

#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* USART1 configuration definitions */
#if defined(DEV_USART1) && (DEV_USART1 == 1)
  #define USE_USART1

  #if !defined(USART1)
    #error "USART1 not available for selected device!"
    #undef USE_USART1
  #endif

  #if (DEV_USART1_RX_DMA == 1)
    #define USART1_RX_DMA_Stream      DMAx_STREAMy(DEV_USART1_RX_DMA_NUMBER, DEV_USART1_RX_DMA_STREAM)
    #define USART1_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART1_RX_DMA_NUMBER, DEV_USART1_RX_DMA_STREAM)
    #define USART1_RX_DMA_Channel     DMA_CHANNEL_x(DEV_USART1_RX_DMA_CHANNEL)
    #define USART1_RX_DMA_Priority    DMA_PRIORITY(DEV_USART1_RX_DMA_PRIORITY)
  #endif
  #if (DEV_USART1_TX_DMA == 1)
    #define USART1_TX_DMA_Stream      DMAx_STREAMy(DEV_USART1_TX_DMA_NUMBER, DEV_USART1_TX_DMA_STREAM)
    #define USART1_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART1_TX_DMA_NUMBER, DEV_USART1_TX_DMA_STREAM)
    #define USART1_TX_DMA_Channel     DMA_CHANNEL_x(DEV_USART1_TX_DMA_CHANNEL)
    #define USART1_TX_DMA_Priority    DMA_PRIORITY(DEV_USART1_TX_DMA_PRIORITY)
  #endif

  #if (DEV_USART1_TX == 1)
    #define USE_USART1_TX_Pin       1
    #define USART1_TX_GPIO_PORT     DEV_USART1_TX_PORT
    #define USART1_TX_GPIO_PIN      DEV_USART1_TX_PIN
    #define USART1_TX_GPIO_FUNC     DEV_USART1_TX_FUNC
  #endif

  #if (DEV_USART1_RX == 1)
    #define USE_USART1_RX_Pin       1
    #define USART1_RX_GPIO_PORT     DEV_USART1_RX_PORT
    #define USART1_RX_GPIO_PIN      DEV_USART1_RX_PIN
    #define USART1_RX_GPIO_FUNC     DEV_USART1_RX_FUNC
  #endif

  #if (DEV_USART1_CK == 1)
    #define USE_USART1_CK_Pin       1
    #define USART1_CK_GPIO_PORT     DEV_USART1_CK_PORT
    #define USART1_CK_GPIO_PIN      DEV_USART1_CK_PIN
    #define USART1_CK_GPIO_FUNC     DEV_USART1_CK_FUNC
  #endif

  #if (DEV_USART1_RTS == 1)
    #define USE_USART1_RTS_Pin      1
    #define USART1_RTS_GPIO_PORT    DEV_USART1_RTS_PORT
    #define USART1_RTS_GPIO_PIN     DEV_USART1_RTS_PIN
    #define USART1_RTS_GPIO_FUNC    DEV_USART1_RTS_FUNC
  #endif

  #if (DEV_USART1_CTS == 1)
    #define USE_USART1_CTS_Pin      1
    #define USART1_CTS_GPIO_PORT    DEV_USART1_CTS_PORT
    #define USART1_CTS_GPIO_PIN     DEV_USART1_CTS_PIN
    #define USART1_CTS_GPIO_FUNC    DEV_USART1_CTS_FUNC
  #endif
#endif

/* USART2 configuration definitions */
#if defined(DEV_USART2) && (DEV_USART2 == 1)
  #define USE_USART2

  #if !defined(USART2)
    #error "USART2 not available for selected device!"
    #undef USE_USART2
  #endif

  #if (DEV_USART2_RX_DMA == 1)
    #define USART2_RX_DMA_Stream      DMAx_STREAMy(DEV_USART2_RX_DMA_NUMBER, DEV_USART2_RX_DMA_STREAM)
    #define USART2_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART2_RX_DMA_NUMBER, DEV_USART2_RX_DMA_STREAM)
    #define USART2_RX_DMA_Channel     DMA_CHANNEL_x(DEV_USART2_RX_DMA_CHANNEL)
    #define USART2_RX_DMA_Priority    DMA_PRIORITY(DEV_USART2_RX_DMA_PRIORITY)
  #endif
  #if (DEV_USART2_TX_DMA == 1)
    #define USART2_TX_DMA_Stream      DMAx_STREAMy(DEV_USART2_TX_DMA_NUMBER, DEV_USART2_TX_DMA_STREAM)
    #define USART2_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART2_TX_DMA_NUMBER, DEV_USART2_TX_DMA_STREAM)
    #define USART2_TX_DMA_Channel     DMA_CHANNEL_x(DEV_USART2_TX_DMA_CHANNEL)
    #define USART2_TX_DMA_Priority    DMA_PRIORITY(DEV_USART2_TX_DMA_PRIORITY)
  #endif

  #if (DEV_USART2_TX == 1)
    #define USE_USART2_TX_Pin       1
    #define USART2_TX_GPIO_PORT     DEV_USART2_TX_PORT
    #define USART2_TX_GPIO_PIN      DEV_USART2_TX_PIN
    #define USART2_TX_GPIO_FUNC     DEV_USART2_TX_FUNC
  #endif

  #if (DEV_USART2_RX == 1)
    #define USE_USART2_RX_Pin       1
    #define USART2_RX_GPIO_PORT     DEV_USART2_RX_PORT
    #define USART2_RX_GPIO_PIN      DEV_USART2_RX_PIN
    #define USART2_RX_GPIO_FUNC     DEV_USART2_RX_FUNC
  #endif

  #if (DEV_USART2_CK == 1)
    #define USE_USART2_CK_Pin       1
    #define USART2_CK_GPIO_PORT     DEV_USART2_CK_PORT
    #define USART2_CK_GPIO_PIN      DEV_USART2_CK_PIN
    #define USART2_CK_GPIO_FUNC     DEV_USART2_CK_FUNC
  #endif

  #if (DEV_USART2_RTS == 1)
    #define USE_USART2_RTS_Pin      1
    #define USART2_RTS_GPIO_PORT    DEV_USART2_RTS_PORT
    #define USART2_RTS_GPIO_PIN     DEV_USART2_RTS_PIN
    #define USART2_RTS_GPIO_FUNC    DEV_USART2_RTS_FUNC
  #endif

  #if (DEV_USART2_CTS == 1)
    #define USE_USART2_CTS_Pin      1
    #define USART2_CTS_GPIO_PORT    DEV_USART2_CTS_PORT
    #define USART2_CTS_GPIO_PIN     DEV_USART2_CTS_PIN
    #define USART2_CTS_GPIO_FUNC    DEV_USART2_CTS_FUNC
  #endif
#endif

/* USART3 configuration definitions */
#if defined(DEV_USART3) && (DEV_USART3 == 1)
  #define USE_USART3

  #if !defined(USART3)
    #error "USART3 not available for selected device!"
    #undef USE_USART3
  #endif

  #if (DEV_USART3_RX_DMA == 1)
    #define USART3_RX_DMA_Stream      DMAx_STREAMy(DEV_USART3_RX_DMA_NUMBER, DEV_USART3_RX_DMA_STREAM)
    #define USART3_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART3_RX_DMA_NUMBER, DEV_USART3_RX_DMA_STREAM)
    #define USART3_RX_DMA_Channel     DMA_CHANNEL_x(DEV_USART3_RX_DMA_CHANNEL)
    #define USART3_RX_DMA_Priority    DMA_PRIORITY(DEV_USART3_RX_DMA_PRIORITY)
  #endif
  #if (DEV_USART3_TX_DMA == 1)
    #define USART3_TX_DMA_Stream      DMAx_STREAMy(DEV_USART3_TX_DMA_NUMBER, DEV_USART3_TX_DMA_STREAM)
    #define USART3_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART3_TX_DMA_NUMBER, DEV_USART3_TX_DMA_STREAM)
    #define USART3_TX_DMA_Channel     DMA_CHANNEL_x(DEV_USART3_TX_DMA_CHANNEL)
    #define USART3_TX_DMA_Priority    DMA_PRIORITY(DEV_USART3_TX_DMA_PRIORITY)
  #endif

  #if (DEV_USART3_TX == 1)
    #define USE_USART3_TX_Pin         1
    #define USART3_TX_GPIO_PORT       DEV_USART3_TX_PORT
    #define USART3_TX_GPIO_PIN        DEV_USART3_TX_PIN
    #define USART3_TX_GPIO_FUNC       DEV_USART3_TX_FUNC
  #endif

  #if (DEV_USART3_RX == 1)
    #define USE_USART3_RX_Pin         1
    #define USART3_RX_GPIO_PORT       DEV_USART3_RX_PORT
    #define USART3_RX_GPIO_PIN        DEV_USART3_RX_PIN
    #define USART3_RX_GPIO_FUNC       DEV_USART3_RX_FUNC
  #endif

  #if (DEV_USART3_CK == 1)
    #define USE_USART3_CK_Pin         1
    #define USART3_CK_GPIO_PORT       DEV_USART3_CK_PORT
    #define USART3_CK_GPIO_PIN        DEV_USART3_CK_PIN
    #define USART3_CK_GPIO_FUNC       DEV_USART3_CK_FUNC
  #endif

  #if (DEV_USART3_RTS == 1)
    #define USE_USART3_RTS_Pin        1
    #define USART3_RTS_GPIO_PORT      DEV_USART3_RTS_PORT
    #define USART3_RTS_GPIO_PIN       DEV_USART3_RTS_PIN
    #define USART3_RTS_GPIO_FUNC      DEV_USART3_RTS_FUNC
  #endif

  #if (DEV_USART3_CTS == 1)
    #define USE_USART3_CTS_Pin        1
    #define USART3_CTS_GPIO_PORT      DEV_USART3_CTS_PORT
    #define USART3_CTS_GPIO_PIN       DEV_USART3_CTS_PIN
    #define USART3_CTS_GPIO_FUNC      DEV_USART3_CTS_FUNC
  #endif
#endif

/* UART4 configuration definitions */
#if defined(DEV_UART4) && (DEV_UART4 == 1)
  #define USE_UART4

  #if !defined(UART4)
    #error "UART4 not available for selected device!"
    #undef USE_UART4
  #endif

  #if (DEV_UART4_RX_DMA == 1)
    #define UART4_RX_DMA_Stream      DMAx_STREAMy(DEV_UART4_RX_DMA_NUMBER, DEV_UART4_RX_DMA_STREAM)
    #define UART4_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART4_RX_DMA_NUMBER, DEV_UART4_RX_DMA_STREAM)
    #define UART4_RX_DMA_Channel     DMA_CHANNEL_x(DEV_UART4_RX_DMA_CHANNEL)
    #define UART4_RX_DMA_Priority    DMA_PRIORITY(DEV_UART4_RX_DMA_PRIORITY)
  #endif
  #if (DEV_UART4_TX_DMA == 1)
    #define UART4_TX_DMA_Stream      DMAx_STREAMy(DEV_UART4_TX_DMA_NUMBER, DEV_UART4_TX_DMA_STREAM)
    #define UART4_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART4_TX_DMA_NUMBER, DEV_UART4_TX_DMA_STREAM)
    #define UART4_TX_DMA_Channel     DMA_CHANNEL_x(DEV_UART4_TX_DMA_CHANNEL)
    #define UART4_TX_DMA_Priority    DMA_PRIORITY(DEV_UART4_TX_DMA_PRIORITY)
  #endif

  #if (DEV_UART4_TX == 1)
    #define USE_UART4_TX_Pin         1
    #define UART4_TX_GPIO_PORT       DEV_UART4_TX_PORT
    #define UART4_TX_GPIO_PIN        DEV_UART4_TX_PIN
    #define UART4_TX_GPIO_FUNC       DEV_UART4_TX_FUNC
  #endif

  #if (DEV_UART4_RX == 1)
    #define USE_UART4_RX_Pin         1
    #define UART4_RX_GPIO_PORT       DEV_UART4_RX_PORT
    #define UART4_RX_GPIO_PIN        DEV_UART4_RX_PIN
    #define UART4_RX_GPIO_FUNC       DEV_UART4_RX_FUNC
  #endif

  #if (DEV_UART4_RTS == 1)
    #define USE_UART4_RTS_Pin        1
    #define UART4_RTS_GPIO_PORT      DEV_UART4_RTS_PORT
    #define UART4_RTS_GPIO_PIN       DEV_UART4_RTS_PIN
    #define UART4_RTS_GPIO_FUNC      DEV_UART4_RTS_FUNC
  #endif

  #if (DEV_UART4_CTS == 1)
    #define USE_UART4_CTS_Pin        1
    #define UART4_CTS_GPIO_PORT      DEV_UART4_CTS_PORT
    #define UART4_CTS_GPIO_PIN       DEV_UART4_CTS_PIN
    #define UART4_CTS_GPIO_FUNC      DEV_UART4_CTS_FUNC
  #endif
#endif

/* UART5 configuration definitions */
#if defined(DEV_UART5) && (DEV_UART5 == 1)
  #define USE_UART5

  #if !defined(UART5)
    #error "UART5 not available for selected device!"
    #undef USE_UART5
  #endif

  #if (DEV_UART5_RX_DMA == 1)
    #define UART5_RX_DMA_Stream      DMAx_STREAMy(DEV_UART5_RX_DMA_NUMBER, DEV_UART5_RX_DMA_STREAM)
    #define UART5_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART5_RX_DMA_NUMBER, DEV_UART5_RX_DMA_STREAM)
    #define UART5_RX_DMA_Channel     DMA_CHANNEL_x(DEV_UART5_RX_DMA_CHANNEL)
    #define UART5_RX_DMA_Priority    DMA_PRIORITY(DEV_UART5_RX_DMA_PRIORITY)
  #endif
  #if (DEV_UART5_TX_DMA == 1)
    #define UART5_TX_DMA_Stream      DMAx_STREAMy(DEV_UART5_TX_DMA_NUMBER, DEV_UART5_TX_DMA_STREAM)
    #define UART5_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART5_TX_DMA_NUMBER, DEV_UART5_TX_DMA_STREAM)
    #define UART5_TX_DMA_Channel     DMA_CHANNEL_x(DEV_UART5_TX_DMA_CHANNEL)
    #define UART5_TX_DMA_Priority    DMA_PRIORITY(DEV_UART5_TX_DMA_PRIORITY)
  #endif

  #if (DEV_UART5_TX == 1)
    #define USE_UART5_TX_Pin         1
    #define UART5_TX_GPIO_PORT       DEV_UART5_TX_PORT
    #define UART5_TX_GPIO_PIN        DEV_UART5_TX_PIN
    #define UART5_TX_GPIO_FUNC       DEV_UART5_TX_FUNC
  #endif

  #if (DEV_UART5_RX == 1)
    #define USE_UART5_RX_Pin         1
    #define UART5_RX_GPIO_PORT       DEV_UART5_RX_PORT
    #define UART5_RX_GPIO_PIN        DEV_UART5_RX_PIN
    #define UART5_RX_GPIO_FUNC       DEV_UART5_RX_FUNC
  #endif

  #if (DEV_UART5_RTS == 1)
    #define USE_UART5_RTS_Pin        1
    #define UART5_RTS_GPIO_PORT      DEV_UART5_RTS_PORT
    #define UART5_RTS_GPIO_PIN       DEV_UART5_RTS_PIN
    #define UART5_RTS_GPIO_FUNC      DEV_UART5_RTS_FUNC
  #endif

  #if (DEV_UART5_CTS == 1)
    #define USE_UART5_CTS_Pin        1
    #define UART5_CTS_GPIO_PORT      DEV_UART5_CTS_PORT
    #define UART5_CTS_GPIO_PIN       DEV_UART5_CTS_PIN
    #define UART5_CTS_GPIO_FUNC      DEV_UART5_CTS_FUNC
  #endif
#endif

/* USART6 configuration definitions */
#if defined(DEV_USART6) && (DEV_USART6 == 1)
  #define USE_USART6

  #if !defined(USART6)
    #error "USART6 not available for selected device!"
    #undef USE_USART6
  #endif

  #if (DEV_USART6_RX_DMA == 1)
    #define USART6_RX_DMA_Stream      DMAx_STREAMy(DEV_USART6_RX_DMA_NUMBER, DEV_USART6_RX_DMA_STREAM)
    #define USART6_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART6_RX_DMA_NUMBER, DEV_USART6_RX_DMA_STREAM)
    #define USART6_RX_DMA_Channel     DMA_CHANNEL_x(DEV_USART6_RX_DMA_CHANNEL)
    #define USART6_RX_DMA_Priority    DMA_PRIORITY(DEV_USART6_RX_DMA_PRIORITY)
  #endif
  #if (DEV_USART6_TX_DMA == 1)
    #define USART6_TX_DMA_Stream      DMAx_STREAMy(DEV_USART6_TX_DMA_NUMBER, DEV_USART6_TX_DMA_STREAM)
    #define USART6_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_USART6_TX_DMA_NUMBER, DEV_USART6_TX_DMA_STREAM)
    #define USART6_TX_DMA_Channel     DMA_CHANNEL_x(DEV_USART6_TX_DMA_CHANNEL)
    #define USART6_TX_DMA_Priority    DMA_PRIORITY(DEV_USART6_TX_DMA_PRIORITY)
  #endif

  #if (DEV_USART6_TX == 1)
    #define USE_USART6_TX_Pin         1
    #define USART6_TX_GPIO_PORT       DEV_USART6_TX_PORT
    #define USART6_TX_GPIO_PIN        DEV_USART6_TX_PIN
    #define USART6_TX_GPIO_FUNC       DEV_USART6_TX_FUNC
  #endif

  #if (DEV_USART6_RX == 1)
    #define USE_USART6_RX_Pin         1
    #define USART6_RX_GPIO_PORT       DEV_USART6_RX_PORT
    #define USART6_RX_GPIO_PIN        DEV_USART6_RX_PIN
    #define USART6_RX_GPIO_FUNC       DEV_USART6_RX_FUNC
  #endif

  #if (DEV_USART6_CK == 1)
    #define USE_USART6_CK_Pin         1
    #define USART6_CK_GPIO_PORT       DEV_USART6_CK_PORT
    #define USART6_CK_GPIO_PIN        DEV_USART6_CK_PIN
    #define USART6_CK_GPIO_FUNC       DEV_USART6_CK_FUNC
  #endif

  #if (DEV_USART6_RTS == 1)
    #define USE_USART6_RTS_Pin        1
    #define USART6_RTS_GPIO_PORT      DEV_USART6_RTS_PORT
    #define USART6_RTS_GPIO_PIN       DEV_USART6_RTS_PIN
    #define USART6_RTS_GPIO_FUNC      DEV_USART6_RTS_FUNC
  #endif

  #if (DEV_USART6_CTS == 1)
    #define USE_USART6_CTS_Pin        1
    #define USART6_CTS_GPIO_PORT      DEV_USART6_CTS_PORT
    #define USART6_CTS_GPIO_PIN       DEV_USART6_CTS_PIN
    #define USART6_CTS_GPIO_FUNC      DEV_USART6_CTS_FUNC
  #endif
#endif

/* UART7 configuration definitions */
#if defined(DEV_UART7) && (DEV_UART7 == 1)
  #define USE_UART7

  #if !defined(UART7)
    #error "UART7 not available for selected device!"
    #undef USE_UART7
  #endif

  #if (DEV_UART7_RX_DMA == 1)
    #define UART7_RX_DMA_Stream      DMAx_STREAMy(DEV_UART7_RX_DMA_NUMBER, DEV_UART7_RX_DMA_STREAM)
    #define UART7_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART7_RX_DMA_NUMBER, DEV_UART7_RX_DMA_STREAM)
    #define UART7_RX_DMA_Channel     DMA_CHANNEL_x(DEV_UART7_RX_DMA_CHANNEL)
    #define UART7_RX_DMA_Priority    DMA_PRIORITY(DEV_UART7_RX_DMA_PRIORITY)
  #endif
  #if (DEV_UART7_TX_DMA == 1)
    #define UART7_TX_DMA_Stream      DMAx_STREAMy(DEV_UART7_TX_DMA_NUMBER, DEV_UART7_TX_DMA_STREAM)
    #define UART7_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART7_TX_DMA_NUMBER, DEV_UART7_TX_DMA_STREAM)
    #define UART7_TX_DMA_Channel     DMA_CHANNEL_x(DEV_UART7_TX_DMA_CHANNEL)
    #define UART7_TX_DMA_Priority    DMA_PRIORITY(DEV_UART7_TX_DMA_PRIORITY)
  #endif

  #if (DEV_UART7_TX == 1)
    #define USE_UART7_TX_Pin         1
    #define UART7_TX_GPIO_PORT       DEV_UART7_TX_PORT
    #define UART7_TX_GPIO_PIN        DEV_UART7_TX_PIN
    #define UART7_TX_GPIO_FUNC       DEV_UART7_TX_FUNC
  #endif

  #if (DEV_UART7_RX == 1)
    #define USE_UART7_RX_Pin         1
    #define UART7_RX_GPIO_PORT       DEV_UART7_RX_PORT
    #define UART7_RX_GPIO_PIN        DEV_UART7_RX_PIN
    #define UART7_RX_GPIO_FUNC       DEV_UART7_RX_FUNC
  #endif

  #if (DEV_UART7_RTS == 1)
    #define USE_UART7_RTS_Pin        1
    #define UART7_RTS_GPIO_PORT      DEV_UART7_RTS_PORT
    #define UART7_RTS_GPIO_PIN       DEV_UART7_RTS_PIN
    #define UART7_RTS_GPIO_FUNC      DEV_UART7_RTS_FUNC
  #endif

  #if (DEV_UART7_CTS == 1)
    #define USE_UART7_CTS_Pin        1
    #define UART7_CTS_GPIO_PORT      DEV_UART7_CTS_PORT
    #define UART7_CTS_GPIO_PIN       DEV_UART7_CTS_PIN
    #define UART7_CTS_GPIO_FUNC      DEV_UART7_CTS_FUNC
  #endif
#endif

/* UART8 configuration definitions */
#if defined(DEV_UART8) && (DEV_UART8 == 1)
  #define USE_UART8

  #if !defined(UART8)
    #error "UART8 not available for selected device!"
    #undef USE_UART8
  #endif

  #if (DEV_UART8_RX_DMA == 1)
    #define UART8_RX_DMA_Stream      DMAx_STREAMy(DEV_UART8_RX_DMA_NUMBER, DEV_UART8_RX_DMA_STREAM)
    #define UART8_RX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART8_RX_DMA_NUMBER, DEV_UART8_RX_DMA_STREAM)
    #define UART8_RX_DMA_Channel     DMA_CHANNEL_x(DEV_UART8_RX_DMA_CHANNEL)
    #define UART8_RX_DMA_Priority    DMA_PRIORITY(DEV_UART8_RX_DMA_PRIORITY)
  #endif
  #if (DEV_UART8_TX_DMA == 1)
    #define UART8_TX_DMA_Stream      DMAx_STREAMy(DEV_UART8_TX_DMA_NUMBER, DEV_UART8_TX_DMA_STREAM)
    #define UART8_TX_DMA_IRQn        DMAx_STREAMy_IRQn(DEV_UART8_TX_DMA_NUMBER, DEV_UART8_TX_DMA_STREAM)
    #define UART8_TX_DMA_Channel     DMA_CHANNEL_x(DEV_UART8_TX_DMA_CHANNEL)
    #define UART8_TX_DMA_Priority    DMA_PRIORITY(DEV_UART8_TX_DMA_PRIORITY)
  #endif

  #if (DEV_UART8_TX == 1)
    #define USE_UART8_TX_Pin         1
    #define UART8_TX_GPIO_PORT       DEV_UART8_TX_PORT
    #define UART8_TX_GPIO_PIN        DEV_UART8_TX_PIN
    #define UART8_TX_GPIO_FUNC       DEV_UART8_TX_FUNC
  #endif

  #if (DEV_UART8_RX == 1)
    #define USE_UART8_RX_Pin         1
    #define UART8_RX_GPIO_PORT       DEV_UART8_RX_PORT
    #define UART8_RX_GPIO_PIN        DEV_UART8_RX_PIN
    #define UART8_RX_GPIO_FUNC       DEV_UART8_RX_FUNC
  #endif

  #if (DEV_UART8_RTS == 1)
    #define USE_UART8_RTS_Pin        1
    #define UART8_RTS_GPIO_PORT      DEV_UART8_RTS_PORT
    #define UART8_RTS_GPIO_PIN       DEV_UART8_RTS_PIN
    #define UART8_RTS_GPIO_FUNC      DEV_UART8_RTS_FUNC
  #endif

  #if (DEV_UART8_CTS == 1)
    #define USE_UART8_CTS_Pin        1
    #define UART8_CTS_GPIO_PORT      DEV_UART8_CTS_PORT
    #define UART8_CTS_GPIO_PIN       DEV_UART8_CTS_PIN
    #define UART8_CTS_GPIO_FUNC      DEV_UART8_CTS_FUNC
  #endif
#endif

#if (defined(USART1_RX_DMA_Stream) || \
     defined(USART2_RX_DMA_Stream) || \
     defined(USART3_RX_DMA_Stream) || \
     defined( UART4_RX_DMA_Stream) || \
     defined( UART5_RX_DMA_Stream) || \
     defined(USART6_RX_DMA_Stream) || \
     defined( UART7_TX_DMA_Stream) || \
     defined( UART8_TX_DMA_Stream))
#define __USART_DMA_RX
#endif
#if (defined(USART1_TX_DMA_Stream) || \
     defined(USART2_TX_DMA_Stream) || \
     defined(USART3_TX_DMA_Stream) || \
     defined( UART4_TX_DMA_Stream) || \
     defined( UART5_TX_DMA_Stream) || \
     defined(USART6_RX_DMA_Stream) || \
     defined( UART7_TX_DMA_Stream) || \
     defined( UART8_TX_DMA_Stream))
#define __USART_DMA_TX
#endif
#if (defined(__USART_DMA_RX) && defined(__USART_DMA_TX))
#define __USART_DMA
#endif

#define USARTx_EXPORT_DRIVER(x)                                                                                                                                                            \
static ARM_USART_CAPABILITIES  USART##x##_GetCapabilities (void)                                                { return USART_GetCapabilities (&USART##x##_Resources);                  } \
static int32_t                 USART##x##_Initialize      (ARM_USART_SignalEvent_t cb_event)                    { return USART_Initialize (cb_event, &USART##x##_Resources);             } \
static int32_t                 USART##x##_Uninitialize    (void)                                                { return USART_Uninitialize (&USART##x##_Resources);                     } \
static int32_t                 USART##x##_PowerControl    (ARM_POWER_STATE state)                               { return USART_PowerControl (state, &USART##x##_Resources);              } \
static int32_t                 USART##x##_Send            (const void *data, uint32_t num)                      { return USART_Send (data, num, &USART##x##_Resources);                  } \
static int32_t                 USART##x##_Receive         (void *data, uint32_t num)                            { return USART_Receive (data, num, &USART##x##_Resources);               } \
static int32_t                 USART##x##_Transfer        (const void *data_out, void *data_in, uint32_t num)   { return USART_Transfer (data_out, data_in, num, &USART##x##_Resources); } \
static uint32_t                USART##x##_GetTxCount      (void)                                                { return USART_GetTxCount (&USART##x##_Resources);                       } \
static uint32_t                USART##x##_GetRxCount      (void)                                                { return USART_GetRxCount (&USART##x##_Resources);                       } \
static int32_t                 USART##x##_Control         (uint32_t control, uint32_t arg)                      { return USART_Control (control, arg, &USART##x##_Resources);            } \
static ARM_USART_STATUS        USART##x##_GetStatus       (void)                                                { return USART_GetStatus (&USART##x##_Resources);                        } \
static int32_t                 USART##x##_SetModemControl (ARM_USART_MODEM_CONTROL control)                     { return USART_SetModemControl (control, &USART##x##_Resources);         } \
static ARM_USART_MODEM_STATUS  USART##x##_GetModemStatus  (void)                                                { return USART_GetModemStatus (&USART##x##_Resources);                   } \
       void                    USART##x##_IRQHandler      (void)                                                {        USART_IRQHandler (&USART##x##_Resources);                       } \
                                                                                                                                                                                           \
ARM_DRIVER_USART Driver_USART##x = {                                                                                                                                                       \
    USARTx_GetVersion,                                                                                                                                                                     \
    USART##x##_GetCapabilities,                                                                                                                                                            \
    USART##x##_Initialize,                                                                                                                                                                 \
    USART##x##_Uninitialize,                                                                                                                                                               \
    USART##x##_PowerControl,                                                                                                                                                               \
    USART##x##_Send,                                                                                                                                                                       \
    USART##x##_Receive,                                                                                                                                                                    \
    USART##x##_Transfer,                                                                                                                                                                   \
    USART##x##_GetTxCount,                                                                                                                                                                 \
    USART##x##_GetRxCount,                                                                                                                                                                 \
    USART##x##_Control,                                                                                                                                                                    \
    USART##x##_GetStatus,                                                                                                                                                                  \
    USART##x##_SetModemControl,                                                                                                                                                            \
    USART##x##_GetModemStatus                                                                                                                                                              \
};

#define UARTx_EXPORT_DRIVER(x)                                                                                                                                                             \
static ARM_USART_CAPABILITIES  USART##x##_GetCapabilities (void)                                                { return USART_GetCapabilities (&UART##x##_Resources);                   } \
static int32_t                 USART##x##_Initialize      (ARM_USART_SignalEvent_t cb_event)                    { return USART_Initialize (cb_event, &UART##x##_Resources);              } \
static int32_t                 USART##x##_Uninitialize    (void)                                                { return USART_Uninitialize (&UART##x##_Resources);                      } \
static int32_t                 USART##x##_PowerControl    (ARM_POWER_STATE state)                               { return USART_PowerControl (state, &UART##x##_Resources);               } \
static int32_t                 USART##x##_Send            (const void *data, uint32_t num)                      { return USART_Send (data, num, &UART##x##_Resources);                   } \
static int32_t                 USART##x##_Receive         (void *data, uint32_t num)                            { return USART_Receive (data, num, &UART##x##_Resources);                } \
static int32_t                 USART##x##_Transfer        (const void *data_out, void *data_in, uint32_t num)   { return USART_Transfer (data_out, data_in, num, &UART##x##_Resources);  } \
static uint32_t                USART##x##_GetTxCount      (void)                                                { return USART_GetTxCount (&UART##x##_Resources);                        } \
static uint32_t                USART##x##_GetRxCount      (void)                                                { return USART_GetRxCount (&UART##x##_Resources);                        } \
static int32_t                 USART##x##_Control         (uint32_t control, uint32_t arg)                      { return USART_Control (control, arg, &UART##x##_Resources);             } \
static ARM_USART_STATUS        USART##x##_GetStatus       (void)                                                { return USART_GetStatus (&UART##x##_Resources);                         } \
static int32_t                 USART##x##_SetModemControl (ARM_USART_MODEM_CONTROL control)                     { return USART_SetModemControl (control, &UART##x##_Resources);          } \
static ARM_USART_MODEM_STATUS  USART##x##_GetModemStatus  (void)                                                { return USART_GetModemStatus (&UART##x##_Resources);                    } \
       void                    UART##x##_IRQHandler       (void)                                                {        USART_IRQHandler (&UART##x##_Resources);                        } \
                                                                                                                                                                                           \
ARM_DRIVER_USART Driver_USART##x = {                                                                                                                                                       \
    USARTx_GetVersion,                                                                                                                                                                     \
    USART##x##_GetCapabilities,                                                                                                                                                            \
    USART##x##_Initialize,                                                                                                                                                                 \
    USART##x##_Uninitialize,                                                                                                                                                               \
    USART##x##_PowerControl,                                                                                                                                                               \
    USART##x##_Send,                                                                                                                                                                       \
    USART##x##_Receive,                                                                                                                                                                    \
    USART##x##_Transfer,                                                                                                                                                                   \
    USART##x##_GetTxCount,                                                                                                                                                                 \
    USART##x##_GetRxCount,                                                                                                                                                                 \
    USART##x##_Control,                                                                                                                                                                    \
    USART##x##_GetStatus,                                                                                                                                                                  \
    USART##x##_SetModemControl,                                                                                                                                                            \
    USART##x##_GetModemStatus                                                                                                                                                              \
}

#define USART_BAUDRATE_DIVIDER(_PCLK_, _BAUD_)  (((_PCLK_) + ((_BAUD_)/2U)) / (_BAUD_))

/* USART flags */
#define USART_FLAG_INITIALIZED      ((uint8_t)(1U << 0U))
#define USART_FLAG_POWERED          ((uint8_t)(1U << 1U))
#define USART_FLAG_CONFIGURED       ((uint8_t)(1U << 2U))
#define USART_FLAG_TX_ENABLED       ((uint8_t)(1U << 3U))
#define USART_FLAG_RX_ENABLED       ((uint8_t)(1U << 4U))

/* USART synchronous transfer modes */
#define USART_SYNC_MODE_TX           (1UL)
#define USART_SYNC_MODE_RX           (2UL)
#define USART_SYNC_MODE_TX_RX        (USART_SYNC_MODE_TX | USART_SYNC_MODE_RX)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* USART DMA */
typedef const DMA_Resources_t USART_DMA;

/* USART pin */
typedef const struct _USART_PIN {
  GPIO_PORT_t                  port;    // Port
  GPIO_PIN_t                    pin;    // Pin
  GPIO_PIN_FUNC_t              func;    // AF pin configuration
} USART_PIN;

/* USART Input/Output Configuration */
typedef const struct _USART_IO {
  USART_PIN                     *tx;    // TX  Pin identifier
  USART_PIN                     *rx;    // RX  Pin identifier
  USART_PIN                     *ck;    // CLK Pin identifier
  USART_PIN                    *rts;    // RTS Pin identifier
  USART_PIN                    *cts;    // CTS Pin identifier
} USART_IO;

// USART Transfer Information (Run-Time)
typedef struct _USART_TRANSFER_INFO {
  uint32_t                   rx_num;    // Total number of receive data
  uint32_t                   tx_num;    // Total number of transmit data
  uint8_t                   *rx_buf;    // Pointer to in data buffer
  const uint8_t             *tx_buf;    // Pointer to out data buffer
  uint32_t                   rx_cnt;    // Number of data received
  uint32_t                   tx_cnt;    // Number of data sent
  uint16_t                 dump_val;    // Variable for dumping DMA data
  uint16_t                  def_val;    // Default transfer value
  uint32_t                sync_mode;    // Synchronous mode flag
  uint8_t                break_flag;    // Transmit break flag
  uint8_t               send_active;    // Send active flag
  uint16_t                 reserved;    // Reserved
} USART_TRANSFER_INFO;

typedef struct _USART_STATUS {
  uint8_t                   tx_busy;    // Transmitter busy flag
  uint8_t                   rx_busy;    // Receiver busy flag
  uint8_t              tx_underflow;    // Transmit data underflow detected (cleared on start of next send operation)
  uint8_t               rx_overflow;    // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t                  rx_break;    // Break detected on receive (cleared on start of next receive operation)
  uint8_t          rx_framing_error;    // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t           rx_parity_error;    // Parity error detected on receive (cleared on start of next receive operation)
} USART_STATUS;

// USART Information (Run-time)
typedef struct _USART_INFO {
  ARM_USART_SignalEvent_t     cb_event; // Event Callback
  USART_STATUS                  status; // Status flags
  uint8_t                        flags; // Current USART flags
  uint32_t                        mode; // Current USART mode
  uint32_t                flow_control; // Flow control
} USART_INFO;

// USART Resources definition
typedef const struct {
  ARM_USART_CAPABILITIES  capabilities; // Capabilities
  USART_TypeDef                   *reg; // USART peripheral pointer
  RCC_Periph_t                  periph; // Peripheral
  USART_IO                          io; // USART Input/Output pins
  IRQn_Type                    irq_num; // USART IRQ Number
  USART_DMA                    *dma_tx; // Transmit stream register interface
  USART_DMA                    *dma_rx; // Receive stream register interface
  USART_INFO                     *info; // Run-Time Information
  USART_TRANSFER_INFO            *xfer; // USART transfer information
} USART_RESOURCES;

#endif /* USART_STM32F7XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
