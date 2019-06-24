/*
 * Copyright (C) 2018 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: USART Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef USART_STM32F4XX_H_
#define USART_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#include "stm32f4xx.h"
#include "RCC_STM32F4xx.h"
#include "GPIO_STM32F4xx.h"

#include "Driver_USART.h"

#include "Config/RTE_Device.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

// USART1 configuration definitions
#if (RTE_USART1 == 1)
  #define USE_USART1

  #if (RTE_USART1_TX == 1)
    #if defined (STM32F410Tx)
      // USART1 TX available on pins: PA15, PB6
      #if ((RTE_USART1_TX_ID != 2) && (RTE_USART1_TX_ID != 3))
        #error "Only PA15 and PB6 can be configured as USART TX on selected device!"
      #endif
    #elif !defined (STM32F411xE)
      // PA15 as USART1 TX only available on STM32F411xx
      #if (RTE_USART1_TX_ID == 2)
        #error "PA15 can not be configured as USART1 TX on selected device!"
      #endif
    #endif

    #define USE_USART1_TX_Pin       1
    #define USART1_TX_GPIO_PORT     RTE_USART1_TX_PORT
    #define USART1_TX_GPIO_PIN      RTE_USART1_TX_PIN
    #define USART1_TX_GPIO_FUNC     RTE_USART1_TX_FUNC
  #endif

  #if (RTE_USART1_RX == 1)
    #if defined (STM32F410Tx)
      // USART1 RX available on pins: PB3, PB7
      #if ((RTE_USART1_RX_ID != 2) && (RTE_USART1_RX_ID != 3))
        #error "Only PB3 and PB7 can be configured as USART1 RX on selected device!"
      #endif
    #elif !defined (STM32F411xE)
      // PB3 as USART1 RX only available on STM32F411xx
      #if (RTE_USART1_RX_ID == 2)
        #error "PB3 can not be configured as USART1 RX on selected device!"
      #endif
    #endif

    #define USE_USART1_RX_Pin       1
    #define USART1_RX_GPIO_PORT     RTE_USART1_RX_PORT
    #define USART1_RX_GPIO_PIN      RTE_USART1_RX_PIN
    #define USART1_RX_GPIO_FUNC     RTE_USART1_RX_FUNC
  #endif

  #if (RTE_USART1_CK == 1)
    #define USE_USART1_CK_Pin       1
    #define USART1_CK_GPIO_PORT     RTE_USART1_CK_PORT
    #define USART1_CK_GPIO_PIN      RTE_USART1_CK_PIN
    #define USART1_CK_GPIO_FUNC     RTE_USART1_CK_FUNC
  #endif


  #if (RTE_USART1_RTS == 1)
    #define USE_USART1_RTS_Pin      1
    #define USART1_RTS_GPIO_PORT    RTE_USART1_RTS_PORT
    #define USART1_RTS_GPIO_PIN     RTE_USART1_RTS_PIN
    #define USART1_RTS_GPIO_FUNC    RTE_USART1_RTS_FUNC
  #endif

  #if (RTE_USART1_CTS == 1)
    #if defined (STM32F410Tx)
      // USART1 CTS pin is not available
      #error "USART1 CTS pin is not available on selected device!"
    #endif

    #define USE_USART1_CTS_Pin      1
    #define USART1_CTS_GPIO_PORT    RTE_USART1_CTS_PORT
    #define USART1_CTS_GPIO_PIN     RTE_USART1_CTS_PIN
    #define USART1_CTS_GPIO_FUNC    RTE_USART1_CTS_FUNC
  #endif
#endif

// USART2 configuration definitions
#if (RTE_USART2 == 1)
  #define USE_USART2

  #if (RTE_USART2_TX == 1)
    #if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
      // USART2 TX available on pin: PA2
      #if (RTE_USART2_TX_ID != 1)
        #error "Only PA2 can be configured as USART2 TX on selected device!"
      #endif
    #endif

    #define USE_USART2_TX_Pin       1
    #define USART2_TX_GPIO_PORT     RTE_USART2_TX_PORT
    #define USART2_TX_GPIO_PIN      RTE_USART2_TX_PIN
    #define USART2_TX_GPIO_FUNC     RTE_USART2_TX_FUNC
  #endif

  #if (RTE_USART2_RX == 1)
    #if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
      // USART2 RX available on pin: PA3
      #if (RTE_USART2_RX_ID != 1)
        #error "Only PA3 can be configured as USART2 RX on selected device!"
      #endif
    #endif

    #define USE_USART2_RX_Pin       1
    #define USART2_RX_GPIO_PORT     RTE_USART2_RX_PORT
    #define USART2_RX_GPIO_PIN      RTE_USART2_RX_PIN
    #define USART2_RX_GPIO_FUNC     RTE_USART2_RX_FUNC
  #endif

  #if (RTE_USART2_CK == 1)
    #if defined(STM32F410Tx)
      // USART2 CK is not available
      #error "USART2 CK pin is not available on selected device!"
    #elif defined(STM32F410Cx) || defined(STM32F410Rx)
      // USART2 CK available on pin: PA4
      #if ((RTE_USART2_CK_ID != 0) && (RTE_USART2_CK_ID != 1))
        #error "Only PA4 can be configured as USART2 CK on selected device!"
      #endif
    #endif

    #define USE_USART2_CK_Pin       1
    #define USART2_CK_GPIO_PORT     RTE_USART2_CK_PORT
    #define USART2_CK_GPIO_PIN      RTE_USART2_CK_PIN
    #define USART2_CK_GPIO_FUNC     RTE_USART2_CK_FUNC
  #endif


  #if (RTE_USART2_RTS == 1)
    #if defined(STM32F410Tx)
      // USART2 RTS is not available
      #error "USART2 RTS pin is not available on selected device!"
    #elif defined(STM32F410Cx) || defined(STM32F410Rx)
      // USART2 RTS available on pin: PA1
      #if ((RTE_USART2_RTS_ID != 0) && (RTE_USART2_RTS_ID != 1))
        #error "Only PA1 can be configured as USART2 RTS on selected device!"
      #endif
    #endif

    #define USE_USART2_RTS_Pin      1
    #define USART2_RTS_GPIO_PORT    RTE_USART2_RTS_PORT
    #define USART2_RTS_GPIO_PIN     RTE_USART2_RTS_PIN
    #define USART2_RTS_GPIO_FUNC    RTE_USART2_RTS_FUNC
  #endif

  #if (RTE_USART2_CTS == 1)
    #if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
      // USART2 CTS available on pin: PA0
      #if ((RTE_USART2_CTS_ID != 0) && (RTE_USART2_CTS_ID != 1))
        #error "Only PA0 can be configured as USART2 CTS on selected device!"
      #endif
    #endif

    #define USE_USART2_CTS_Pin      1
    #define USART2_CTS_GPIO_PORT    RTE_USART2_CTS_PORT
    #define USART2_CTS_GPIO_PIN     RTE_USART2_CTS_PIN
    #define USART2_CTS_GPIO_FUNC    RTE_USART2_CTS_FUNC
  #endif
#endif

// USART3 configuration definitions
#if (RTE_USART3 == 1)

  #ifndef USART3
    #error "USART3 not available for selected device!"
  #endif

  #define USE_USART3

  #if (RTE_USART3_TX == 1)
    #define USE_USART3_TX_Pin       1
    #define USART3_TX_GPIO_PORT     RTE_USART3_TX_PORT
    #define USART3_TX_GPIO_PIN      RTE_USART3_TX_PIN
    #define USART3_TX_GPIO_FUNC     RTE_USART3_TX_FUNC
  #endif

  #if (RTE_USART3_RX == 1)
    #define USE_USART3_RX_Pin       1
    #define USART3_RX_GPIO_PORT     RTE_USART3_RX_PORT
    #define USART3_RX_GPIO_PIN      RTE_USART3_RX_PIN
    #define USART3_RX_GPIO_FUNC     RTE_USART3_RX_FUNC
  #endif

  #if (RTE_USART3_CK == 1)
    #define USE_USART3_CK_Pin       1
    #define USART3_CK_GPIO_PORT     RTE_USART3_CK_PORT
    #define USART3_CK_GPIO_PIN      RTE_USART3_CK_PIN
    #define USART3_CK_GPIO_FUNC     RTE_USART3_CK_FUNC
  #endif

  #if (RTE_USART3_RTS == 1)
    #define USE_USART3_RTS_Pin      1
    #define USART3_RTS_GPIO_PORT    RTE_USART3_RTS_PORT
    #define USART3_RTS_GPIO_PIN     RTE_USART3_RTS_PIN
    #define USART3_RTS_GPIO_FUNC    RTE_USART3_RTS_FUNC
  #endif

  #if (RTE_USART3_CTS == 1)
    #define USE_USART3_CTS_Pin      1
    #define USART3_CTS_GPIO_PORT    RTE_USART3_CTS_PORT
    #define USART3_CTS_GPIO_PIN     RTE_USART3_CTS_PIN
    #define USART3_CTS_GPIO_FUNC    RTE_USART3_CTS_FUNC
  #endif
#endif

// UART4 configuration definitions
#if (RTE_UART4 == 1)

  #ifndef UART4
    #error "UART4 not available for selected device!"
  #endif

  #define USE_UART4

  #if (RTE_UART4_TX == 1)
    #if defined (STM32F413xx) || defined (STM32F423xx)
      // UART4 TX available on pins: PA0, PD10, PA12, PD1
      #if ((RTE_UART4_TX_ID == 2))
        #error "PC10 can not be configured as UART4 TX on selected device!"
      #endif
    #else
      // UART4 TX available on pins: PA0, PC10
      #if ((RTE_UART4_TX_ID != 1) && (RTE_UART4_TX_ID != 2))
        #error "PD10, PA12, PD1 can not be configured as UART4 TX on selected device!"
      #endif
    #endif

    #define USE_UART4_TX_Pin        1
    #define UART4_TX_GPIO_PORT      RTE_UART4_TX_PORT
    #define UART4_TX_GPIO_PIN       RTE_UART4_TX_PIN
    #define UART4_TX_GPIO_FUNC      RTE_UART4_TX_FUNC
  #endif

  #if (RTE_UART4_RX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART4 RX available on pins: PA1, PC11
      #if ((RTE_UART4_TX_ID != 1) && (RTE_UART4_TX_ID != 2))
        #error "PA11, PD0 can not be configured as UART4 RX on selected device!"
      #endif
    #endif

    #define USE_UART4_RX_Pin        1
    #define UART4_RX_GPIO_PORT      RTE_UART4_RX_PORT
    #define UART4_RX_GPIO_PIN       RTE_UART4_RX_PIN
    #define UART4_RX_GPIO_FUNC      RTE_UART4_RX_FUNC
  #endif
#endif

// UART5 configuration definitions
#if (RTE_UART5 == 1)

  #ifndef UART5
    #error "UART5 not available for selected device!"
  #endif

  #define USE_UART5

  #if (RTE_UART5_TX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART5 TX available on pins: PC12
      #if ((RTE_UART5_TX_ID != 1))
        #error "PB6, PB9, PB13 can not be configured as UART5 TX on selected device!"
      #endif
    #endif

    #define USE_UART5_TX_Pin        1
    #define UART5_TX_GPIO_PORT      RTE_UART5_TX_PORT
    #define UART5_TX_GPIO_PIN       RTE_UART5_TX_PIN
    #define UART5_TX_GPIO_FUNC      RTE_UART5_TX_FUNC
  #endif

  #if (RTE_UART5_RX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART5 RX available on pins: PD2
      #if ((RTE_UART5_RX_ID != 1))
        #error "PB5, PB8, PB12 can not be configured as UART5 RX on selected device!"
      #endif
    #endif

    #define USE_UART5_RX_Pin        1
    #define UART5_RX_GPIO_PORT      RTE_UART5_RX_PORT
    #define UART5_RX_GPIO_PIN       RTE_UART5_RX_PIN
    #define UART5_RX_GPIO_FUNC      RTE_UART5_RX_FUNC
  #endif
#endif

// USART6 configuration definitions
#if defined (STM32F410Tx) && defined (USART6)
  // USART6 not available on WLCSP36 package
  #undef USART6
#endif

#if (RTE_USART6 == 1)
  #define USE_USART6

  #ifndef USART6
    #error "USART6 not available for selected device!"
  #endif

  #if (RTE_USART6_TX == 1)
    #if defined (STM32F410Cx)
      // USART6 TX available on pin: PA11
      #if ((RTE_USART6_TX_ID != 1)
        #error "Only PA11 can be configured as USART6 TX on selected device!"
      #endif
    #elif defined (STM32F410Rx)
      // USART6 TX available on pins: PA11, PC6
      #if ((RTE_USART6_TX_ID != 1) && (RTE_USART6_TX_ID != 2))
        #error "Only PA11 and PC6 can be configured as USART6 TX on selected device!"
      #endif
    #elif defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F411xE)
      // PG14 as USART6 TX not available on STM32F401xx and STM32F411xx
      #if (RTE_USART6_TX_ID == 3)
        #error "PG14 can not be configured as USART6 TX on selected device!"
      #endif
    #elif defined (STM32F413xx) || defined (STM32F423xx)
      // USART6 TX available on pins: PA11, PC6, PG14
    #else
      // PA11 as USART6 TX only available on STM32F401xx and STM32F411xx
      #if (RTE_USART6_TX_ID == 1)
        #error "PA11 can not be configured as USART6 TX on selected device!"
      #endif
    #endif

    #define USE_USART6_TX_Pin       1
    #define USART6_TX_GPIO_PORT     RTE_USART6_TX_PORT
    #define USART6_TX_GPIO_PIN      RTE_USART6_TX_PIN
    #define USART6_TX_GPIO_FUNC     RTE_USART6_TX_FUNC
  #endif

  #if (RTE_USART6_RX == 1)
    #if defined (STM32F410Cx)
      // USART6 RX available on pin: PA12
      #if ((RTE_USART6_RX_ID != 1)
        #error "Only PA12 can be configured as USART6 RX on selected device!"
      #endif
    #elif defined (STM32F410Rx)
      // USART6 RX available on pins: PA12, PC7
      #if ((RTE_USART6_RX_ID != 1) && (RTE_USART6_RX_ID != 2))
        #error "Only PA12 and PC7 can be configured as USART6 RX on selected device!"
      #endif
    #elif defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F411xE)
      // PG9 as USART6 RX not available on STM32F401xx and STM32F411xx
      #if (RTE_USART6_RX_ID == 3)
        #error "PG9 can not be configured as USART6 RX on selected device!"
      #endif
    #elif defined (STM32F413xx) || defined (STM32F423xx)
      // USART6 RX available on pins: PA12, PC7, PG9
    #else
      // PA12 as USART6 RX only available on STM32F401xx and STM32F411xx
      #if (RTE_USART6_RX_ID == 1)
        #error "PA12 can not be configured as USART6 RX on selected device!"
      #endif
    #endif

    #define USE_USART6_RX_Pin       1
    #define USART6_RX_GPIO_PORT     RTE_USART6_RX_PORT
    #define USART6_RX_GPIO_PIN      RTE_USART6_RX_PIN
    #define USART6_RX_GPIO_FUNC     RTE_USART6_RX_FUNC
  #endif

  #if (RTE_USART6_CK == 1)
    #if defined (STM32F410Cx)
      // USART6 CK pin is not available
      #error "USART2 CK pin is not available on selected device!"
    #elif defined (STM32F410Rx)
      // USART6 CK available on pin: PC8
      #if ((RTE_USART6_CK_ID != 0) && (RTE_USART6_CK_ID != 1)
        #error "Only PC8 can be configured as USART6 CK on selected device!"
      #endif
    #elif defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F411xE)
      // PG7 as USART6 CK not available on STM32F401xx and STM32F411xx
      #if (RTE_USART6_CK_ID == 2)
        #error "PG7 can not be configured as USART6 CK on selected device!"
      #endif
    #endif

    #define USE_USART6_CK_Pin       1
    #define USART6_CK_GPIO_PORT     RTE_USART6_CK_PORT
    #define USART6_CK_GPIO_PIN      RTE_USART6_CK_PIN
    #define USART6_CK_GPIO_FUNC     RTE_USART6_CK_FUNC
  #endif

  #if (RTE_USART6_RTS == 1)
    #if defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F411xE) || \
        defined (STM32F410Cx) || defined (STM32F410Rx)
      #error "RTS line not available on selected device!"
    #endif

    #define USE_USART6_RTS_Pin      1
    #define USART6_RTS_GPIO_PORT     RTE_USART6_RTS_PORT
    #define USART6_RTS_GPIO_PIN      RTE_USART6_RTS_PIN
    #define USART6_RTS_GPIO_FUNC     RTE_USART6_RTS_FUNC
  #endif

  #if (RTE_USART6_CTS == 1)
    #if defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F411xE) || \
        defined (STM32F410Cx) || defined (STM32F410Rx)
      #error "CTS line not available on selected device!"
    #endif

    #define USE_USART6_CTS_Pin      1
    #define USART6_CTS_GPIO_PORT     RTE_USART6_CTS_PORT
    #define USART6_CTS_GPIO_PIN      RTE_USART6_CTS_PIN
    #define USART6_CTS_GPIO_FUNC     RTE_USART6_CTS_FUNC
  #endif
#endif

// UART7 configuration definitions
#if (RTE_UART7 == 1)

  #ifndef UART7
    #error "UART7 not available for selected device!"
  #endif

  #define USE_UART7

  #if (RTE_UART7_TX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART7 TX available on pins: PF7, PE8
      #if ((RTE_UART7_TX_ID == 3) || (RTE_UART7_TX_ID == 3))
        #error "PA15, PB4 can not be configured as UART7 TX on selected device!"
      #endif
    #endif

    #define USE_UART7_TX_Pin        1
    #define UART7_TX_GPIO_PORT      RTE_UART7_TX_PORT
    #define UART7_TX_GPIO_PIN       RTE_UART7_TX_PIN
    #define UART7_TX_GPIO_FUNC      RTE_UART7_TX_FUNC
  #endif

  #if (RTE_UART7_RX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART7 RX available on pins: PF6, PE7
      #if ((RTE_UART7_RX_ID == 3) || (RTE_UART7_RX_ID == 3))
        #error "PA8, PB3 can not be configured as UART7 RX on selected device!"
      #endif
    #endif

    #define USE_UART7_RX_Pin        1
    #define UART7_RX_GPIO_PORT      RTE_UART7_RX_PORT
    #define UART7_RX_GPIO_PIN       RTE_UART7_RX_PIN
    #define UART7_RX_GPIO_FUNC      RTE_UART7_RX_FUNC
  #endif
#endif

// UART8 configuration definitions
#if (RTE_UART8 == 1)

  #ifndef UART8
    #error "UART8 not available for selected device!"
  #endif

  #define USE_UART8

  #if (RTE_UART8_TX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART8 TX available on pins: PE1
      #if ((RTE_UART8_TX_ID == 2))
        #error "PF9 can not be configured as UART8 TX on selected device!"
      #endif
    #endif

    #define USE_UART8_TX_Pin        1
    #define UART8_TX_GPIO_PORT      RTE_UART8_TX_PORT
    #define UART8_TX_GPIO_PIN       RTE_UART8_TX_PIN
    #define UART8_TX_GPIO_FUNC      RTE_UART8_TX_FUNC
  #endif

  #if (RTE_UART8_RX == 1)
    #if !defined (STM32F413xx) && !defined (STM32F423xx)
      // UART8 RX available on pins: PE0
      #if ((RTE_UART8_RX_ID == 2))
        #error "PF8 can not be configured as UART8 RX on selected device!"
      #endif
    #endif

    #define USE_UART8_RX_Pin        1
    #define UART8_RX_GPIO_PORT      RTE_UART8_RX_PORT
    #define UART8_RX_GPIO_PIN       RTE_UART8_RX_PIN
    #define UART8_RX_GPIO_FUNC      RTE_UART8_RX_FUNC
  #endif
#endif

// UART9 configuration definitions
#if (!defined (STM32F413xx) && !defined (STM32F423xx)) && defined (USART9)
  // USART9 not available
  #undef USART9
#endif

#if (RTE_UART9 == 1)

  #ifndef UART9
    #error "UART9 not available for selected device!"
  #endif

  #define USE_UART9

  #if (RTE_UART9_TX == 1)
    #define USE_UART9_TX_Pin        1
    #define UART9_TX_GPIO_PORT      RTE_UART9_TX_PORT
    #define UART9_TX_GPIO_PIN       RTE_UART9_TX_PIN
    #define UART9_TX_GPIO_FUNC      RTE_UART9_TX_FUNC
  #endif

  #if (RTE_UART9_RX == 1)
    #define USE_UART9_RX_Pin        1
    #define UART9_RX_GPIO_PORT      RTE_UART9_RX_PORT
    #define UART9_RX_GPIO_PIN       RTE_UART9_RX_PIN
    #define UART9_RX_GPIO_FUNC      RTE_UART9_RX_FUNC
  #endif
#endif

// UART10 configuration definitions
#if (!defined (STM32F413xx) && !defined (STM32F423xx)) && defined (USART10)
  // USART10 not available
  #undef USART10
#endif

#if (RTE_UART10 == 1)

  #ifndef UART10
    #error "UART10 not available for selected device!"
  #endif

  #define USE_UART10

  #if (RTE_UART10_TX == 1)
    #define USE_UART10_TX_Pin       1
    #define UART10_TX_GPIO_PORT     RTE_UART10_TX_PORT
    #define UART10_TX_GPIO_PIN      RTE_UART10_TX_PIN
    #define UART10_TX_GPIO_FUNC     RTE_UART10_TX_FUNC
  #endif

  #if (RTE_UART10_RX == 1)
    #define USE_UART10_RX_Pin       1
    #define UART10_RX_GPIO_PORT     RTE_UART10_RX_PORT
    #define UART10_RX_GPIO_PIN      RTE_UART10_RX_PIN
    #define UART10_RX_GPIO_FUNC     RTE_UART10_RX_FUNC
  #endif
#endif

// USART BRR macro
#define USART_DIVIDER(_PCLK_, _BAUD_)           (((_PCLK_)*25)/(4*(_BAUD_)))
#define USART_DIVIDER_MANTISA(_PCLK_, _BAUD_)     (USART_DIVIDER((_PCLK_), (_BAUD_))/100)
#define USART_DIVIDER_FRACTION(_PCLK_, _BAUD_)  (((USART_DIVIDER((_PCLK_), (_BAUD_)) - (USART_DIVIDER_MANTISA((_PCLK_), (_BAUD_)) * 100)) * 16 + 50) / 100)
#define USART_BAUDRATE_DIVIDER(_PCLK_, _BAUD_)   ((USART_DIVIDER_MANTISA((_PCLK_), (_BAUD_)) << 4)|(USART_DIVIDER_FRACTION((_PCLK_), (_BAUD_)) & 0x0F))

// USART flags
#define USART_FLAG_INITIALIZED      ((uint8_t)(1U))
#define USART_FLAG_POWERED          ((uint8_t)(1U << 1))
#define USART_FLAG_CONFIGURED       ((uint8_t)(1U << 2))
#define USART_FLAG_TX_ENABLED       ((uint8_t)(1U << 3))
#define USART_FLAG_RX_ENABLED       ((uint8_t)(1U << 4))

// USART synchronous xfer modes
#define USART_SYNC_MODE_TX           ( 1UL )
#define USART_SYNC_MODE_RX           ( 2UL )
#define USART_SYNC_MODE_TX_RX        (USART_SYNC_MODE_TX | USART_SYNC_MODE_RX)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

// USART pin
typedef const struct _USART_PIN {
  GPIO_PORT_t           port;           // IO port
  GPIO_PIN_t            pin;            // IO pin
  GPIO_PIN_FUNC_t       func;           // AF pin configuration
} USART_PIN;

// USART Input/Output Configuration
typedef const struct _USART_IO {
  USART_PIN            *tx;             // TX  Pin identifier
  USART_PIN            *rx;             // RX  Pin identifier
  USART_PIN            *ck;             // CLK Pin identifier
  USART_PIN            *rts;            // RTS Pin identifier
  USART_PIN            *cts;            // CTS Pin identifier
} USART_IO;

// USART Transfer Information (Run-Time)
typedef struct _USART_TRANSFER_INFO {
  uint32_t              rx_num;         // Total number of receive data
  uint32_t              tx_num;         // Total number of transmit data
  uint8_t              *rx_buf;         // Pointer to in data buffer
  uint8_t              *tx_buf;         // Pointer to out data buffer
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              tx_cnt;         // Number of data sent
  uint16_t              dump_val;       // Variable for dumping DMA data
  uint16_t              def_val;        // Default transfer value
  uint32_t              sync_mode;      // Synchronous mode flag
  uint8_t               break_flag;     // Transmit break flag
  uint8_t               send_active;    // Send active flag
} USART_TRANSFER_INFO;

typedef struct _USART_STATUS {
  uint8_t tx_busy;                      // Transmitter busy flag
  uint8_t rx_busy;                      // Receiver busy flag
  uint8_t tx_underflow;                 // Transmit data underflow detected (cleared on start of next send operation)
  uint8_t rx_overflow;                  // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t rx_break;                     // Break detected on receive (cleared on start of next receive operation)
  uint8_t rx_framing_error;             // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t rx_parity_error;              // Parity error detected on receive (cleared on start of next receive operation)
} USART_STATUS;

// USART Information (Run-time)
typedef struct _USART_INFO {
  ARM_USART_SignalEvent_t cb_event;            // Event Callback
  USART_STATUS            status;              // Status flags
  uint8_t                 flags;               // Current USART flags
  uint32_t                mode;                // Current USART mode
  uint32_t                flow_control;        // Flow control
} USART_INFO;

// USART Resources definition
typedef struct USART_RESOURCES_s {
  ARM_USART_CAPABILITIES  capabilities;        // Capabilities
  USART_TypeDef          *reg;                 // USART peripheral pointer
  USART_IO                io;                  // USART Input/Output pins
  IRQn_Type               irq_num;             // USART IRQ Number
  RCC_Periph_t            rcc;                 // RCC Clock/Reset registers
  USART_INFO             *info;                // Run-Time Information
  USART_TRANSFER_INFO    *xfer;                // USART transfer information
} const USART_RESOURCES;

#endif /* USART_STM32F4XX_H */

/* ----------------------------- End of file ---------------------------------*/
