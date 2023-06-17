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
 * Project: SPI Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef SPI_STM32F4XX_H_
#define SPI_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#include "asm/stm32f4xx.h"
#include "asm/RCC_STM32F4xx.h"
#include "asm/GPIO_STM32F4xx.h"
#include "asm/DMA_STM32F4xx.h"

#include "Driver/Driver_SPI.h"

#include "device_config.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#if ((defined(RTE_Drivers_SPI1) || \
      defined(RTE_Drivers_SPI2) || \
      defined(RTE_Drivers_SPI3) || \
      defined(RTE_Drivers_SPI4) || \
      defined(RTE_Drivers_SPI5) || \
      defined(RTE_Drivers_SPI6))   \
      && (RTE_SPI1 == 0)            \
      && (RTE_SPI2 == 0)            \
      && (RTE_SPI3 == 0)            \
      && (RTE_SPI4 == 0)            \
      && (RTE_SPI5 == 0)            \
      && (RTE_SPI6 == 0))
#error "SPI not configured in RTE_Device.h!"
#endif

#define SPIx_EXPORT_DRIVER(x)                                                                                                                                               \
static int32_t        SPI##x##_Initialize      (ARM_SPI_SignalEvent_t pSignalEvent)                { return SPI_Initialize (pSignalEvent, &SPI##x##_Resources); }           \
static int32_t        SPI##x##_Uninitialize    (void)                                              { return SPI_Uninitialize (&SPI##x##_Resources); }                       \
static int32_t        SPI##x##_PowerControl    (ARM_POWER_STATE state)                             { return SPI_PowerControl (state, &SPI##x##_Resources); }                \
static int32_t        SPI##x##_Send            (const void *data, uint32_t num)                    { return SPI_Send (data, num, &SPI##x##_Resources); }                    \
static int32_t        SPI##x##_Receive         (void *data, uint32_t num)                          { return SPI_Receive (data, num, &SPI##x##_Resources); }                 \
static int32_t        SPI##x##_Transfer        (const void *data_out, void *data_in, uint32_t num) { return SPI_Transfer (data_out, data_in, num, &SPI##x##_Resources); }   \
static uint32_t       SPI##x##_GetDataCount    (void)                                              { return SPI_GetDataCount (&SPI##x##_Resources); }                       \
static int32_t        SPI##x##_Control         (uint32_t control, uint32_t arg)                    { return SPI_Control (control, arg, &SPI##x##_Resources); }              \
static ARM_SPI_STATUS SPI##x##_GetStatus       (void)                                              { return SPI_GetStatus (&SPI##x##_Resources); }                          \
       void           SPI##x##_IRQHandler      (void)                                              { SPI_IRQHandler(&SPI##x##_Resources); }                                 \
                                                                                                                                                                            \
ARM_DRIVER_SPI Driver_SPI##x = {        \
  SPIx_GetVersion,                      \
  SPIx_GetCapabilities,                 \
  SPI##x##_Initialize,                  \
  SPI##x##_Uninitialize,                \
  SPI##x##_PowerControl,                \
  SPI##x##_Send,                        \
  SPI##x##_Receive,                     \
  SPI##x##_Transfer,                    \
  SPI##x##_GetDataCount,                \
  SPI##x##_Control,                     \
  SPI##x##_GetStatus                    \
}                                       \


#define SPIx_TX_DMA_ALLOC(x)                                                                         \
void SPI##x##_TX_DMA_Handler  (void)           { DMA_IRQ_Handle(&SPI##x##_TX_DMA); }                 \
void SPI##x##_TX_DMA_Complete (uint32_t event) { SPI_TX_DMA_Complete(event, &SPI##x##_Resources); }  \

#define SPIx_RX_DMA_ALLOC(x)                                                                         \
void SPI##x##_RX_DMA_Handler  (void)           { DMA_IRQ_Handle(&SPI##x##_RX_DMA); }                 \
void SPI##x##_RX_DMA_Complete (uint32_t event) { SPI_RX_DMA_Complete(event, &SPI##x##_Resources); }  \


/* SPI1 configuration definitions */
#if (RTE_SPI1 == 1)

  #define USE_SPI1

  #if (RTE_SPI1_RX_DMA == 1)
    #define SPI1_RX_DMA_Stream      DMAx_STREAMy(RTE_SPI1_RX_DMA_NUMBER, RTE_SPI1_RX_DMA_STREAM)
    #define SPI1_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI1_RX_DMA_NUMBER, RTE_SPI1_RX_DMA_STREAM)
    #define SPI1_RX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI1_RX_DMA_CHANNEL)
    #define SPI1_RX_DMA_Priority    DMA_PRIORITY(RTE_SPI1_RX_DMA_PRIORITY)
    #define SPI1_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI1_RX_DMA_NUMBER, RTE_SPI1_RX_DMA_STREAM)
  #endif
  #if (RTE_SPI1_TX_DMA == 1)
    #define SPI1_TX_DMA_Stream      DMAx_STREAMy(RTE_SPI1_TX_DMA_NUMBER, RTE_SPI1_TX_DMA_STREAM)
    #define SPI1_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI1_TX_DMA_NUMBER, RTE_SPI1_TX_DMA_STREAM)
    #define SPI1_TX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI1_TX_DMA_CHANNEL)
    #define SPI1_TX_DMA_Priority    DMA_PRIORITY(RTE_SPI1_TX_DMA_PRIORITY)
    #define SPI1_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI1_TX_DMA_NUMBER, RTE_SPI1_TX_DMA_STREAM)
  #endif

  #if (RTE_SPI1_MISO == 1)
    #if defined (STM32F410Tx)
      // SPI1 MISO available on pin: PB4
      #if (RTE_SPI1_MISO_PORT_ID != 2)
        #error "Only PB4 can be configured as SPI1 MISO on selected device!"
      #endif
    #endif

    #define USE_SPI1_MISO_Pin       1U
    #define SPI1_MISO_GPIO_PORT     RTE_SPI1_MISO_PORT
    #define SPI1_MISO_GPIO_PIN      RTE_SPI1_MISO_PIN
    #define SPI1_MISO_GPIO_FUNC     RTE_SPI1_MISO_FUNC
  #endif

  #if (RTE_SPI1_MOSI == 1)
    #if defined (STM32F410Tx)
      // SPI1 MOSI available on pin: PB5
      #if (RTE_SPI1_MOSI_PORT_ID != 2)
        #error "Only PB5 can be configured as SPI1 MOSI on selected device!"
      #endif
    #endif

    #define USE_SPI1_MOSI_Pin       1U
    #define SPI1_MOSI_GPIO_PORT     RTE_SPI1_MOSI_PORT
    #define SPI1_MOSI_GPIO_PIN      RTE_SPI1_MOSI_PIN
    #define SPI1_MOSI_GPIO_FUNC     RTE_SPI1_MOSI_FUNC
  #endif

  #define USE_SPI1_SCK_Pin          1U
  #define SPI1_SCK_GPIO_PORT        RTE_SPI1_SCK_PORT
  #define SPI1_SCK_GPIO_PIN         RTE_SPI1_SCK_PIN
  #define SPI1_SCK_GPIO_FUNC        RTE_SPI1_SCK_FUNC

  #if (RTE_SPI1_NSS == 1)
    #if defined (STM32F410Tx)
      // SPI1 NSS available on pin: PA15
      #if ((RTE_SPI1_NSS_PORT_ID != 0) && (RTE_SPI1_NSS_PORT_ID != 2)
        #error "Only PA15 can be configured as SPI1 NSS on selected device!"
      #endif
    #endif

    #define USE_SPI1_NSS_Pin        1U
    #define SPI1_NSS_GPIO_PORT      RTE_SPI1_NSS_PORT
    #define SPI1_NSS_GPIO_PIN       RTE_SPI1_NSS_PIN
    #define SPI1_NSS_GPIO_FUNC      RTE_SPI1_NSS_FUNC
  #endif

#endif

/* SPI2 configuration definitions */
#if (RTE_SPI2 == 1)
  #ifndef SPI2
    #error "SPI2 not available for selected device!"
  #endif

  #define USE_SPI2

  #if (RTE_SPI2_RX_DMA == 1)
    #define SPI2_RX_DMA_Stream      DMAx_STREAMy(RTE_SPI2_RX_DMA_NUMBER, RTE_SPI2_RX_DMA_STREAM)
    #define SPI2_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI2_RX_DMA_NUMBER, RTE_SPI2_RX_DMA_STREAM)
    #define SPI2_RX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI2_RX_DMA_CHANNEL)
    #define SPI2_RX_DMA_Priority    DMA_PRIORITY(RTE_SPI2_RX_DMA_PRIORITY)
    #define SPI2_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI2_RX_DMA_NUMBER, RTE_SPI2_RX_DMA_STREAM)
  #endif
  #if (RTE_SPI2_TX_DMA == 1)
    #define SPI2_TX_DMA_Stream      DMAx_STREAMy(RTE_SPI2_TX_DMA_NUMBER, RTE_SPI2_TX_DMA_STREAM)
    #define SPI2_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI2_TX_DMA_NUMBER, RTE_SPI2_TX_DMA_STREAM)
    #define SPI2_TX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI2_TX_DMA_CHANNEL)
    #define SPI2_TX_DMA_Priority    DMA_PRIORITY(RTE_SPI2_TX_DMA_PRIORITY)
    #define SPI2_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI2_TX_DMA_NUMBER, RTE_SPI2_TX_DMA_STREAM)
  #endif

  #if (RTE_SPI2_MISO == 1)
    #if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
      // PI2 as SPI2 MISO not available on STM32F401xx, STM32F411xx and STM32F446xx
      #if (RTE_SPI2_MISO_PORT_ID == 3)
        #error "PI2 can not be configured as SPI2 MISO on selected device!"
      #endif
    #elif defined (STM32F410Cx)
      // SPI2 MISO available on pin: PB14
      #if (RTE_SPI2_MISO_PORT_ID != 1)
        #error "Only PB14 can be configured as SPI2 MISO on selected device!"
      #endif
    #elif defined (STM32F410Rx)
      // SPI2 MISO available on pins: PB14, PC2
      #if ((RTE_SPI2_MISO_PORT_ID != 1) && (RTE_SPI2_MISO_PORT_ID != 2))
        #error "Only PB14 and PC2 can be configured as SPI2 MISO on selected device!"
      #endif
    #elif defined (STM32F413xx) || defined (STM32F423xx)
      // SPI2 MISO available on pins: PB14, PC2, PA12
      #if ((RTE_SPI2_MISO_PORT_ID != 1) && (RTE_SPI2_MISO_PORT_ID != 2) && (RTE_SPI2_MISO_PORT_ID != 4))
        #error "Only PB14, PC2, PA12 can be configured as SPI2 MISO on selected device!"
      #endif
    #endif

    #define USE_SPI2_MISO_Pin       1U
    #define SPI2_MISO_GPIO_PORT     RTE_SPI2_MISO_PORT
    #define SPI2_MISO_GPIO_PIN      RTE_SPI2_MISO_PIN
    #define SPI2_MISO_GPIO_FUNC     RTE_SPI2_MISO_FUNC
  #endif

  #if (RTE_SPI2_MOSI == 1)
    #if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
      // PI3 as SPI2 MOSI not available on STM32F401xx, STM32F411xx and STM32F446xx
      #if (RTE_SPI2_MOSI_PORT_ID == 3)
        #error "PI3 can not be configured as SPI2 MOSI on selected device!"
      #endif
    #elif defined (STM32F410Cx)
      // SPI2 MOSI available on pin: PB15
      #if (RTE_SPI2_MOSI_PORT_ID != 1)
        #error "Only PB15 can be configured as SPI2 MOSI on selected device!"
      #endif
    #elif defined (STM32F410Rx)
      // SPI2 MOSI available on pins: PB15, PC3
      #if ((RTE_SPI2_MOSI_PORT_ID != 1) && (RTE_SPI2_MOSI_PORT_ID != 2))
        #error "Only PB15 and PC3 can be configured as SPI2 MOSI on selected device!"
      #endif
    #elif defined (STM32F413xx) || defined (STM32F423xx)
      // SPI2 MOSI available on pins: PB15, PC3, PA10
      #if ((RTE_SPI2_MOSI_PORT_ID != 1) && (RTE_SPI2_MOSI_PORT_ID != 2) && (RTE_SPI2_MOSI_PORT_ID != 4))
        #error "Only PB15, PC3, PA10 can be configured as SPI2 MOSI on selected device!"
      #endif
    #endif

    #define USE_SPI2_MOSI_Pin       1U
    #define SPI2_MOSI_GPIO_PORT     RTE_SPI2_MOSI_PORT
    #define SPI2_MOSI_GPIO_PIN      RTE_SPI2_MOSI_PIN
    #define SPI2_MOSI_GPIO_FUNC     RTE_SPI2_MOSI_FUNC
  #endif

  #if defined (STM32F410Cx)
    // SPI2 SCK available on pins: PB10, PB13
    #if (RTE_SPI2_SCK_PORT_ID > 1)
      #error "Only PB10 and PB13 can be configured as SPI2 SCK on selected device!"
    #endif
  #elif defined (STM32F410Rx)
    // SPI2 SCK available on pins: PB10, PB13, PC7
    #if (RTE_SPI2_SCK_PORT_ID > 2)
      #error "Only PB10, PB13 and PC7 can be configured as SPI2 SCK on selected device!"
    #endif
  #elif !defined(STM32F411xE) && !defined(STM32F446xx)
    // PC7 as SPI2 SCK only available on STM32F411xx and STM32F446xx
    #if (RTE_SPI2_SCK_PORT_ID == 2)
      #error "PC7 can not be configured as SPI2 SCK on selected device!"
    #endif
  #elif defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
    // PD3 as SPI2 SCK not available on STM32F405xx, STM32F407xx, STM32F415xx and STM32F417xx
    #if (RTE_SPI2_SCK_PORT_ID == 3)
      #error "PD3 can not be configured as SPI2 SCK on selected device!"
    #endif
  #elif defined(STM32F446xx)
    // PI1 as SPI2 SCK not available on STM32F446xx
    #if (RTE_SPI2_SCK_PORT_ID == 1)
      #error "PI1 can not be configured as SPI2 SCK on selected device!"
    #endif
  #elif defined (STM32F413xx) || defined (STM32F423xx)
    // PI1 as SPI2 SCK not available on STM32F413xx, STM32F423xx
    #if (RTE_SPI2_SCK_PORT_ID == 4)
      #error "PI1 can not be configured as SPI2 SCK on selected device!"
    #endif
  #endif

  #define USE_SPI2_SCK_Pin          1U
  #define SPI2_SCK_GPIO_PORT        RTE_SPI2_SCK_PORT
  #define SPI2_SCK_GPIO_PIN         RTE_SPI2_SCK_PIN
  #define SPI2_SCK_GPIO_FUNC        RTE_SPI2_SCK_FUNC

  #if (RTE_SPI2_NSS == 1)
    #if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
      // PI0 as SPI2 NSS not available on STM32F401xx, STM32F411xx and STM32F446xx
      #if (RTE_SPI2_NSS_PORT_ID == 3)
        #error "PI0 can not be configured as SPI2 NSS on selected device!"
      #endif
    #elif defined (STM32F410Cx) || defined (STM32F410Rx)
      // SPI2 NSS available on pins: PB9, PB12
      #if (RTE_SPI2_NSS_PORT_ID > 2)
        #error "Only PB9 and PB12 can be configured as SPI2 NSS on selected device!"
      #endif
    #elif defined (STM32F413xx) || defined (STM32F423xx)
      // PI0 as SPI2 NSS not available on STM32F413xx, STM32F423xx
      #if (RTE_SPI2_NSS_PORT_ID == 3)
        #error "PI0 can not be configured as SPI2 NSS on selected device!"
      #endif
    #endif

    #define USE_SPI2_NSS_Pin        1U
    #define SPI2_NSS_GPIO_PORT      RTE_SPI2_NSS_PORT
    #define SPI2_NSS_GPIO_PIN       RTE_SPI2_NSS_PIN
    #define SPI2_NSS_GPIO_FUNC      RTE_SPI2_NSS_FUNC
  #endif

#endif

/* SPI3 configuration definitions */
#if (RTE_SPI3 == 1)
  #ifndef SPI3
    #error "SPI3 not available for selected device!"
  #endif

  #define USE_SPI3

  #if (RTE_SPI3_RX_DMA == 1)
    #define SPI3_RX_DMA_Stream      DMAx_STREAMy(RTE_SPI3_RX_DMA_NUMBER, RTE_SPI3_RX_DMA_STREAM)
    #define SPI3_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI3_RX_DMA_NUMBER, RTE_SPI3_RX_DMA_STREAM)
    #define SPI3_RX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI3_RX_DMA_CHANNEL)
    #define SPI3_RX_DMA_Priority    DMA_PRIORITY(RTE_SPI3_RX_DMA_PRIORITY)
    #define SPI3_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI3_RX_DMA_NUMBER, RTE_SPI3_RX_DMA_STREAM)
  #endif
  #if (RTE_SPI3_TX_DMA == 1)
    #define SPI3_TX_DMA_Stream      DMAx_STREAMy(RTE_SPI3_TX_DMA_NUMBER, RTE_SPI3_TX_DMA_STREAM)
    #define SPI3_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI3_TX_DMA_NUMBER, RTE_SPI3_TX_DMA_STREAM)
    #define SPI3_TX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI3_TX_DMA_CHANNEL)
    #define SPI3_TX_DMA_Priority    DMA_PRIORITY(RTE_SPI3_TX_DMA_PRIORITY)
    #define SPI3_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI3_TX_DMA_NUMBER, RTE_SPI3_TX_DMA_STREAM)
  #endif

  #if (RTE_SPI3_MISO == 1)
    #define USE_SPI3_MISO_Pin       1U
    #define SPI3_MISO_GPIO_PORT     RTE_SPI3_MISO_PORT
    #define SPI3_MISO_GPIO_PIN      RTE_SPI3_MISO_PIN
    #define SPI3_MISO_GPIO_FUNC     RTE_SPI3_MISO_FUNC
  #endif

  #if (RTE_SPI3_MOSI == 1)
    #if defined(STM32F405xx) || defined(STM32F407xx) || \
        defined(STM32F415xx) || defined(STM32F417xx)
      // PD6 as SPI3 MOSI not available on STM32F405xx, STM32F407xx, STM32F415xx and STM32F417xx
      #if (RTE_SPI3_MOSI_PORT_ID == 3)
        #error "PD6 can not be configured as SPI3 MOSI on selected device!"
      #endif
    #endif

    #define USE_SPI3_MOSI_Pin       1U
    #define SPI3_MOSI_GPIO_PORT     RTE_SPI3_MOSI_PORT
    #define SPI3_MOSI_GPIO_PIN      RTE_SPI3_MOSI_PIN
    #define SPI3_MOSI_GPIO_FUNC     RTE_SPI3_MOSI_FUNC
  #endif

  #ifndef STM32F411xE
    // PB12 as SPI3 SCK only available on STM32F411xx
    #if (RTE_SPI3_SCK_PORT_ID == 1)
      #error "PB12 can not be configured as SPI3 SCK on selected device!"
    #endif
  #endif

  #define USE_SPI3_SCK_Pin          1U
  #define SPI3_SCK_GPIO_PORT        RTE_SPI3_SCK_PORT
  #define SPI3_SCK_GPIO_PIN         RTE_SPI3_SCK_PIN
  #define SPI3_SCK_GPIO_FUNC        RTE_SPI3_SCK_FUNC

  #if (RTE_SPI3_NSS == 1)
    #define USE_SPI3_NSS_Pin        1U
    #define SPI3_NSS_GPIO_PORT      RTE_SPI3_NSS_PORT
    #define SPI3_NSS_GPIO_PIN       RTE_SPI3_NSS_PIN
    #define SPI3_NSS_GPIO_FUNC      RTE_SPI3_NSS_FUNC
  #endif

#endif

/* SPI4 configuration definitions */
#if (RTE_SPI4 == 1)
  #ifndef SPI4
    #error "SPI4 not available for selected device!"
  #endif

  #define USE_SPI4

  #if (RTE_SPI4_RX_DMA == 1)
    #define SPI4_RX_DMA_Stream      DMAx_STREAMy(RTE_SPI4_RX_DMA_NUMBER, RTE_SPI4_RX_DMA_STREAM)
    #define SPI4_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI4_RX_DMA_NUMBER, RTE_SPI4_RX_DMA_STREAM)
    #define SPI4_RX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI4_RX_DMA_CHANNEL)
    #define SPI4_RX_DMA_Priority    DMA_PRIORITY(RTE_SPI4_RX_DMA_PRIORITY)
    #define SPI4_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI4_RX_DMA_NUMBER, RTE_SPI4_RX_DMA_STREAM)
  #endif
  #if (RTE_SPI4_TX_DMA == 1)
    #define SPI4_TX_DMA_Stream      DMAx_STREAMy(RTE_SPI4_TX_DMA_NUMBER, RTE_SPI4_TX_DMA_STREAM)
    #define SPI4_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI4_TX_DMA_NUMBER, RTE_SPI4_TX_DMA_STREAM)
    #define SPI4_TX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI4_TX_DMA_CHANNEL)
    #define SPI4_TX_DMA_Priority    DMA_PRIORITY(RTE_SPI4_TX_DMA_PRIORITY)
    #define SPI4_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI4_TX_DMA_NUMBER, RTE_SPI4_TX_DMA_STREAM)
  #endif

  #if (RTE_SPI4_MISO == 1)
    #ifndef STM32F411xE
      // PA11 as SPI4 MISO only available on STM32F411xx
      #if (RTE_SPI4_MISO_PORT_ID == 1)
        #error "PA11 can not be configured as SPI4 MISO on selected device!"
      #endif
    #endif

    #define USE_SPI4_MISO_Pin       1U
    #define SPI4_MISO_GPIO_PORT     RTE_SPI4_MISO_PORT
    #define SPI4_MISO_GPIO_PIN      RTE_SPI4_MISO_PIN
    #define SPI4_MISO_GPIO_FUNC     RTE_SPI4_MISO_FUNC
  #endif

  #if (RTE_SPI4_MOSI == 1)
    #ifndef STM32F411xE
      // PA1 as SPI4 MOSI only available on STM32F411xx
      #if (RTE_SPI4_MOSI_PORT_ID == 1)
        #error "PA1 can not be configured as SPI4 MOSI on selected device!"
      #endif
    #endif

    #define USE_SPI4_MOSI_Pin       1U
    #define SPI4_MOSI_GPIO_PORT     RTE_SPI4_MOSI_PORT
    #define SPI4_MOSI_GPIO_PIN      RTE_SPI4_MOSI_PIN
    #define SPI4_MOSI_GPIO_FUNC     RTE_SPI4_MOSI_FUNC
  #endif

  #ifndef STM32F411xE
    // PB13 as SPI4 SCK only available on STM32F411xx
    #if (RTE_SPI4_SCK_PORT_ID == 0)
      #error "PB13 can not be configured as SPI4 SCK on selected device!"
    #endif
  #endif

  #define USE_SPI4_SCK_Pin          1U
  #define SPI4_SCK_GPIO_PORT        RTE_SPI4_SCK_PORT
  #define SPI4_SCK_GPIO_PIN         RTE_SPI4_SCK_PIN
  #define SPI4_SCK_GPIO_FUNC        RTE_SPI4_SCK_FUNC

  #if (RTE_SPI4_NSS == 1)
    #ifndef STM32F411xE
      // PB12 as SPI4 NSS only available on STM32F411xx
      #if (RTE_SPI4_NSS_PORT_ID == 1)
        #error "PB12 can not be configured as SPI4 NSS on selected device!"
      #endif
    #endif

    #define USE_SPI4_NSS_Pin        1U
    #define SPI4_NSS_GPIO_PORT      RTE_SPI4_NSS_PORT
    #define SPI4_NSS_GPIO_PIN       RTE_SPI4_NSS_PIN
    #define SPI4_NSS_GPIO_FUNC      RTE_SPI4_NSS_FUNC
  #endif

#endif

/* SPI5 configuration definitions */
#if (RTE_SPI5 == 1)
  #ifndef SPI5
    #error "SPI5 not available for selected device!"
  #endif

  #define USE_SPI5

  #if (RTE_SPI5_RX_DMA == 1)
    #define SPI5_RX_DMA_Stream      DMAx_STREAMy(RTE_SPI5_RX_DMA_NUMBER, RTE_SPI5_RX_DMA_STREAM)
    #define SPI5_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI5_RX_DMA_NUMBER, RTE_SPI5_RX_DMA_STREAM)
    #define SPI5_RX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI5_RX_DMA_CHANNEL)
    #define SPI5_RX_DMA_Priority    DMA_PRIORITY(RTE_SPI5_RX_DMA_PRIORITY)
    #define SPI5_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI5_RX_DMA_NUMBER, RTE_SPI5_RX_DMA_STREAM)
  #endif
  #if (RTE_SPI5_TX_DMA == 1)
    #define SPI5_TX_DMA_Stream      DMAx_STREAMy(RTE_SPI5_TX_DMA_NUMBER, RTE_SPI5_TX_DMA_STREAM)
    #define SPI5_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI5_TX_DMA_NUMBER, RTE_SPI5_TX_DMA_STREAM)
    #define SPI5_TX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI5_TX_DMA_CHANNEL)
    #define SPI5_TX_DMA_Priority    DMA_PRIORITY(RTE_SPI5_TX_DMA_PRIORITY)
    #define SPI5_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI5_TX_DMA_NUMBER, RTE_SPI5_TX_DMA_STREAM)
  #endif

  #if (RTE_SPI5_MISO == 1)
    #if defined (STM32F410Cx) || defined (STM32F410Rx)
      // SPI5 MISO available on pin: PA12
      #if (RTE_SPI5_MISO_PORT_ID != 1)
        #error "Only PA12 can be configured as SPI5 MISO on selected device!"
      #endif
    #elif !defined (STM32F411xE)
      // PA12 as SPI5 MISO only available on STM32F411xx
      #if (RTE_SPI5_MISO_PORT_ID == 1)
        #error "PA12 can not be configured as SPI5 MISO on selected device!"
      #endif

      // PE5 as SPI5 MISO only available on STM32F411xx
      #if (RTE_SPI5_MISO_PORT_ID == 2)
        #error "PE5 can not be configured as SPI5 MISO on selected device!"
      #endif

      // PE13 as SPI5 MISO only available on STM32F411xx
      #if (RTE_SPI5_MISO_PORT_ID == 3)
        #error "PE13 can not be configured as SPI5 MISO on selected device!"
      #endif
    #else
      // PF8 as SPI5 MISO only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
      #if (RTE_SPI5_MISO_PORT_ID == 4)
        #error "PF8 can not be configured as SPI5 MISO on selected device!"
      #endif

      // PH7 as SPI5 MISO only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
      #if (RTE_SPI5_MISO_PORT_ID == 5)
        #error "PH7 can not be configured as SPI5 MISO on selected device!"
      #endif
    #endif

    #define USE_SPI5_MISO_Pin       1U
    #define SPI5_MISO_GPIO_PORT     RTE_SPI5_MISO_PORT
    #define SPI5_MISO_GPIO_PIN      RTE_SPI5_MISO_PIN
    #define SPI5_MISO_GPIO_FUNC     RTE_SPI5_MISO_FUNC
  #endif

  #if (RTE_SPI5_MOSI == 1)
    #if defined (STM32F410Cx) || defined (STM32F410Rx)
      // SPI5 MOSI available on pins: PA10, PB8
      #if ((RTE_SPI5_MOSI_PORT_ID != 1) && (RTE_SPI5_MOSI_PORT_ID != 2))
        #error "Only PA10 and PB8 can be configured as SPI5 MOSI on selected device!"
      #endif
    #elif !defined (STM32F411xE)
      // PA10 as SPI5 MOSI only available on STM32F411xx
      #if (RTE_SPI5_MOSI_PORT_ID == 1)
        #error "PA10 can not be configured as SPI5 MOSI on selected device!"
      #endif

      // PB8 as SPI5 MOSI only available on STM32F411xx
      #if (RTE_SPI5_MOSI_PORT_ID == 2)
        #error "PB8 can not be configured as SPI5 MOSI on selected device!"
      #endif

      // PE6 as SPI5 MOSI only available on STM32F411xx
      #if (RTE_SPI5_MOSI_PORT_ID == 3)
        #error "PE6 can not be configured as SPI5 MOSI on selected device!"
      #endif

      // PE14 as SPI5 MOSI only available on STM32F411xx
      #if (RTE_SPI5_MOSI_PORT_ID == 4)
        #error "PE14 can not be configured as SPI5 MOSI on selected device!"
      #endif
    #else
      // PF9 as SPI5 MOSI only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
      #if (RTE_SPI5_MOSI_PORT_ID == 5)
        #error "PF9 can not be configured as SPI5 MOSI on selected device!"
      #endif

      // PF11 as SPI5 MOSI only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
      #if (RTE_SPI5_MOSI_PORT_ID == 6)
        #error "PF11 can not be configured as SPI5 MOSI on selected device!"
      #endif
    #endif

    #define USE_SPI5_MOSI_Pin       1U
    #define SPI5_MOSI_GPIO_PORT     RTE_SPI5_MOSI_PORT
    #define SPI5_MOSI_GPIO_PIN      RTE_SPI5_MOSI_PIN
    #define SPI5_MOSI_GPIO_FUNC     RTE_SPI5_MOSI_FUNC
  #endif

  #if defined (STM32F410Cx) || defined (STM32F410Rx)
    // SPI5 SCK available on pin: PB0
    #if (RTE_SPI5_SCK_PORT_ID != 0)
      #error "Only PB0 can be configured as SPI5 SCK on selected device!"
    #endif
  #elif !defined (STM32F411xE)
    // PB0 as SPI5 SCK only available on STM32F411xx
    #if (RTE_SPI5_SCK_PORT_ID == 0)
      #error "PB0 can not be configured as SPI5 SCK on selected device!"
    #endif

    // PE2 as SPI5 SCK only available on STM32F411xx
    #if (RTE_SPI5_SCK_PORT_ID == 1)
      #error "PE2 can not be configured as SPI5 SCK on selected device!"
    #endif

    // PE12 as SPI5 SCK only available on STM32F411xx
    #if (RTE_SPI5_SCK_PORT_ID == 2)
      #error "PE12 can not be configured as SPI5 SCK on selected device!"
    #endif
  #else
    // PF7 as SPI5 SCK only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
    #if (RTE_SPI5_SCK_PORT_ID == 3)
      #error "PF7 can not be configured as SPI5 SCK on selected device!"
    #endif

    // PH6 as SPI5 SCK only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
    #if (RTE_SPI5_SCK_PORT_ID == 4)
      #error "PH6 can not be configured as SPI5 SCK on selected device!"
    #endif
  #endif

  #define USE_SPI5_SCK_Pin          1U
  #define SPI5_SCK_GPIO_PORT        RTE_SPI5_SCK_PORT
  #define SPI5_SCK_GPIO_PIN         RTE_SPI5_SCK_PIN
  #define SPI5_SCK_GPIO_FUNC        RTE_SPI5_SCK_FUNC

  #if (RTE_SPI5_NSS == 1)
    #if defined (STM32F410Cx) || defined (STM32F410Rx)
      // SPI5 NSS available on pin: PB1
      #if ((RTE_SPI5_NSS_PORT_ID != 0) && (RTE_SPI5_NSS_PORT_ID != 1))
        #error "Only PB1 can be configured as SPI5 NSS on selected device!"
      #endif
    #elif !defined (STM32F411xE)
      // PB1 as SPI5 NSS only available on STM32F411xx
      #if (RTE_SPI5_NSS_PORT_ID == 0)
        #error "PB1 can not be configured as SPI5 NSS on selected device!"
      #endif

      // PE4 as SPI5 NSS only available on STM32F411xx
      #if (RTE_SPI5_NSS_PORT_ID == 1)
        #error "PE4 can not be configured as SPI5 NSS on selected device!"
      #endif

      // PE11 as SPI5 NSS only available on STM32F411xx
      #if (RTE_SPI5_NSS_PORT_ID == 2)
        #error "PE11 can not be configured as SPI5 NSS on selected device!"
      #endif
    #else
      // PF6 as SPI5 NSS only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
      #if (RTE_SPI5_NSS_PORT_ID == 3)
        #error "PF6 can not be configured as SPI5 NSS on selected device!"
      #endif

      // PH5 as SPI5 NSS only available on STM32F427xx, STM32F429xx, STM32F437xx and STM32F439xx
      #if (RTE_SPI5_NSS_PORT_ID == 4)
        #error "PH5 can not be configured as SPI5 NSS on selected device!"
      #endif
    #endif

    #define USE_SPI5_NSS_Pin        1U
    #define SPI5_NSS_GPIO_PORT      RTE_SPI5_NSS_PORT
    #define SPI5_NSS_GPIO_PIN       RTE_SPI5_NSS_PIN
    #define SPI5_NSS_GPIO_FUNC      RTE_SPI5_NSS_FUNC
  #endif

#endif

/* SPI6 configuration definitions */
#if (defined (STM32F413xx) && defined (STM32F423xx)) && defined (SPI6)
  // SPI6 not available
  #undef SPI6
#endif

#if (RTE_SPI6 == 1)
  #ifndef SPI6
    #error "SPI6 not available for selected device!"
  #endif

  #define USE_SPI6

  #if (RTE_SPI6_RX_DMA == 1)
    #define SPI6_RX_DMA_Stream      DMAx_STREAMy(RTE_SPI6_RX_DMA_NUMBER, RTE_SPI6_RX_DMA_STREAM)
    #define SPI6_RX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI6_RX_DMA_NUMBER, RTE_SPI6_RX_DMA_STREAM)
    #define SPI6_RX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI6_RX_DMA_CHANNEL)
    #define SPI6_RX_DMA_Priority    DMA_PRIORITY(RTE_SPI6_RX_DMA_PRIORITY)
    #define SPI6_RX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI6_RX_DMA_NUMBER, RTE_SPI6_RX_DMA_STREAM)
  #endif
  #if (RTE_SPI6_TX_DMA == 1)
    #define SPI6_TX_DMA_Stream      DMAx_STREAMy(RTE_SPI6_TX_DMA_NUMBER, RTE_SPI6_TX_DMA_STREAM)
    #define SPI6_TX_DMA_IRQn        DMAx_STREAMy_IRQn(RTE_SPI6_TX_DMA_NUMBER, RTE_SPI6_TX_DMA_STREAM)
    #define SPI6_TX_DMA_Channel     DMA_CHANNEL_x(RTE_SPI6_TX_DMA_CHANNEL)
    #define SPI6_TX_DMA_Priority    DMA_PRIORITY(RTE_SPI6_TX_DMA_PRIORITY)
    #define SPI6_TX_DMA_Handler     DMAx_STREAMy_IRQ(RTE_SPI6_TX_DMA_NUMBER, RTE_SPI6_TX_DMA_STREAM)
  #endif

  #if (RTE_SPI6_MISO == 1)
    #define USE_SPI6_MISO_Pin       1U
    #define SPI6_MISO_GPIO_PORT     RTE_SPI6_MISO_PORT
    #define SPI6_MISO_GPIO_PIN      RTE_SPI6_MISO_PIN
    #define SPI6_MISO_GPIO_FUNC     RTE_SPI6_MISO_FUNC
  #endif

  #if (RTE_SPI6_MOSI == 1)
    #define USE_SPI6_MOSI_Pin       1U
    #define SPI6_MOSI_GPIO_PORT     RTE_SPI6_MOSI_PORT
    #define SPI6_MOSI_GPIO_PIN      RTE_SPI6_MOSI_PIN
    #define SPI6_MOSI_GPIO_FUNC     RTE_SPI6_MOSI_FUNC
  #endif

  #define USE_SPI6_SCK_Pin          1U
  #define SPI6_SCK_GPIO_PORT        RTE_SPI6_SCK_PORT
  #define SPI6_SCK_GPIO_PIN         RTE_SPI6_SCK_PIN
  #define SPI6_SCK_GPIO_FUNC        RTE_SPI6_SCK_FUNC

  #if (RTE_SPI6_NSS == 1)
    #define USE_SPI6_NSS_Pin        1U
    #define SPI6_NSS_GPIO_PORT      RTE_SPI6_NSS_PORT
    #define SPI6_NSS_GPIO_PIN       RTE_SPI6_NSS_PIN
    #define SPI6_NSS_GPIO_FUNC      RTE_SPI6_NSS_FUNC
  #endif

#endif

#if ((defined(USE_SPI1) && defined(SPI1_RX_DMA_Handler)) || \
     (defined(USE_SPI2) && defined(SPI2_RX_DMA_Handler)) || \
     (defined(USE_SPI3) && defined(SPI3_RX_DMA_Handler)) || \
     (defined(USE_SPI4) && defined(SPI4_RX_DMA_Handler)) || \
     (defined(USE_SPI5) && defined(SPI5_RX_DMA_Handler)) || \
     (defined(USE_SPI6) && defined(SPI6_RX_DMA_Handler)))
  #define SPI_DMA_RX
#endif

#if ((defined(USE_SPI1) && defined(SPI1_TX_DMA_Handler)) || \
     (defined(USE_SPI2) && defined(SPI2_TX_DMA_Handler)) || \
     (defined(USE_SPI3) && defined(SPI3_TX_DMA_Handler)) || \
     (defined(USE_SPI4) && defined(SPI4_TX_DMA_Handler)) || \
     (defined(USE_SPI5) && defined(SPI5_TX_DMA_Handler)) || \
     (defined(USE_SPI6) && defined(SPI6_TX_DMA_Handler)))
  #define SPI_DMA_TX
#endif

#if (defined(SPI_DMA_RX) && defined(SPI_DMA_TX))
  #define SPI_DMA
#endif

/* Current driver status flag definition */
#define SPI_INITIALIZED           ((uint8_t)(1U))          // SPI initialized
#define SPI_POWERED               ((uint8_t)(1U << 1))     // SPI powered on
#define SPI_CONFIGURED            ((uint8_t)(1U << 2))     // SPI configured
#define SPI_DATA_LOST             ((uint8_t)(1U << 3))     // SPI data lost occurred
#define SPI_MODE_FAULT            ((uint8_t)(1U << 4))     // SPI mode fault occurred

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* SPI Pin */
typedef const struct _SPI_PIN {
  GPIO_PORT_t           port;               // IO port
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
} SPI_PIN;

/* SPI Input/Output Configuration */
typedef const struct _SPI_IO {
  SPI_PIN               *miso;              // Pointer to MISO pin configuration
  SPI_PIN               *mosi;              // Pointer to MOSI pin configuration
  SPI_PIN               *sck;               // Pointer to SCK pin configuration
  SPI_PIN               *nss;               // Pointer to NSS pin configuration
} SPI_IO;

typedef struct _SPI_STATUS {
  uint8_t               busy;               // Transmitter/Receiver busy flag
  uint8_t               data_lost;          // Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint8_t               mode_fault;         // Mode fault detected; optional (cleared on start of transfer operation)
} SPI_STATUS;

/* SPI Information (Run-Time) */
typedef struct _SPI_INFO {
  ARM_SPI_SignalEvent_t cb_event;           // Event Callback
  SPI_STATUS            status;             // Status flags
  uint8_t               state;              // Current SPI state
  uint32_t              mode;               // Current SPI mode
} SPI_INFO;

/* SPI Transfer Information (Run-Time) */
typedef struct _SPI_TRANSFER_INFO {
  uint32_t              num;                // Total number of transfers
  uint8_t              *rx_buf;             // Pointer to in data buffer
  uint8_t              *tx_buf;             // Pointer to out data buffer
  uint32_t              rx_cnt;             // Number of data received
  uint32_t              tx_cnt;             // Number of data sent
  uint32_t              dump_val;           // Variable for dumping DMA data
  uint16_t              def_val;            // Default transfer value
  uint16_t              reserved;           // Reserved
} SPI_TRANSFER_INFO;

/* SPI Resource Configuration */
typedef struct _SPI_RESOURSES {
  SPI_TypeDef          *reg;                // SPI peripheral register interface
  SPI_IO                io;                 // SPI Input/Output pins
  RCC_Periph_t          rcc;                // RCC registers
  DMA_Resources_t      *tx_dma;             // Transmit stream register interface
  DMA_Resources_t      *rx_dma;             // Receive stream register interface
  SPI_INFO             *info;               // Run-Time information
  SPI_TRANSFER_INFO    *xfer;               // SPI transfer information
  IRQn_Type             irq_num;            // SPI IRQ Number
  uint8_t               reserved[3];        // Reserved
} const SPI_RESOURCES;

#endif /* SPI_STM32F4XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
