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
 * Project: DMA Driver Definitions for STMicroelectronics STM32F1xx
 */

#ifndef DMA_STM32F10X_H_
#define DMA_STM32F10X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define _DMAx_CHANNELy(x, y)              DMA##x##_Channel##y
#define  DMAx_CHANNELy(x, y)             _DMAx_CHANNELy(x, y)

#define _DMAx_CHANNELy_EVENT(x, y)        DMA##x##_Channel##y##_Event
#define  DMAx_CHANNELy_EVENT(x, y)       _DMAx_CHANNELy_EVENT(x, y)

#define _DMAx_CHANNELy_IRQn(x, y)         DMA##x##_Channel##y##_IRQn
#define  DMAx_CHANNELy_IRQn(x, y)        _DMAx_CHANNELy_IRQn(x, y)

#define DMA_PRIORITY(x)                   (((uint32_t)(x) << DMA_CCR_PL_Pos) & DMA_CCR_PL_Msk)

// DMA channel Interrupt Flags
#define DMA_CHANNEL_GLOBAL_INTERRUPT     (1UL<<0)
#define DMA_CHANNEL_TRANSFER_COMPLETE    (1UL<<1)
#define DMA_CHANNEL_HALF_TRANSFER        (1UL<<2)
#define DMA_CHANNEL_TRANSFER_ERROR       (1UL<<3)
#define DMA_CHANNEL_FLAGS                (DMA_CHANNEL_TRANSFER_ERROR    | \
                                          DMA_CHANNEL_HALF_TRANSFER     | \
                                          DMA_CHANNEL_TRANSFER_COMPLETE | \
                                          DMA_CHANNEL_GLOBAL_INTERRUPT)

// DMA channel Configuration Register definitions
#define DMA_TRANSFER_ERROR_INTERRUPT    DMA_CCR_TEIE
#define DMA_HALF_TRANSFER_INTERRUPT     DMA_CCR_HTIE
#define DMA_TRANSFER_COMPLETE_INTERRUPT DMA_CCR_TCIE
#define DMA_PERIPHERAL_TO_MEMORY        0
#define DMA_MEMORY_TO_PERIPHERAL        DMA_CCR_DIR
#define DMA_MEMORY_TO_MEMORY            DMA_CCR_MEM2MEM
#define DMA_CIRCULAR_MODE               DMA_CCR_CIRC
#define DMA_PERIPHERAL_INCREMENT        DMA_CCR_PINC
#define DMA_MEMORY_INCREMENT            DMA_CCR_MINC
#define DMA_PERIPHERAL_DATA_8BIT        0
#define DMA_PERIPHERAL_DATA_16BIT       DMA_CCR_PSIZE_0
#define DMA_PERIPHERAL_DATA_32BIT       DMA_CCR_PSIZE_1
#define DMA_MEMORY_DATA_8BIT            0
#define DMA_MEMORY_DATA_16BIT           DMA_CCR_MSIZE_0
#define DMA_MEMORY_DATA_32BIT           DMA_CCR_MSIZE_1

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* DMA Information definitions */
typedef struct _DMA_INFO {
  DMA_Channel_TypeDef *instance;        /* Channel registry interface */
  uint8_t              ch_num;          /* Channel number             */
  uint8_t              priority;        /* Channel priority           */
  IRQn_Type            irq_num;         /* DMA channel IRQ Number     */
} DMA_INFO;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn          void DMA_ChannelInitialize(DMA_INFO *info)
 * @brief       Initialize DMA Channel
 * @param[in]   info  DMA info
 */
void DMA_ChannelInitialize(DMA_INFO *info);

/**
 * @fn          void DMA_ChannelUninitialize(DMA_INFO *info)
 * @brief       Uninitialize DMA Channel
 * @param[in]   info  DMA info
 */
void DMA_ChannelUninitialize(DMA_INFO *info);

/**
 * @fn          void DMA_ChannelConfigure(DMA_Channel_TypeDef *DMA_Channel, uint32_t ccr, uint32_t cpar, uint32_t cmar, uint32_t cndtr)
 * @brief       Configure DMA channel for next transfer
 * @param[in]   DMA_Channel specifies pointer to DMA channel peripheral
 * @param[in]   cfg    Configuration register value
 * @param[in]   paddr  Peripheral address register value
 * @param[in]   maddr  Memory address register value
 * @param[in]   num    Number of data transfer register value (up to 65535)
 */
void DMA_ChannelConfigure(DMA_Channel_TypeDef *dma_cnl, uint32_t cfg, uint32_t paddr, uint32_t maddr, uint16_t num);

/**
  \fn          void DMA_ChannelEnable (DMA_Channel_TypeDef *DMA_Channel)
  \brief       Enable channel and/or start memory to memory transfer
  \param[in]   DMA_Channel  Pointer to DMA channel peripheral
*/
__STATIC_FORCEINLINE void DMA_ChannelEnable (DMA_Channel_TypeDef *DMA_Channel) {
  DMA_Channel->CCR |=  DMA_CCR_EN;
}

/**
  \fn          void DMA_ChannelDisable (DMA_Channel_TypeDef *DMA_Channel)
  \brief       Disable channel and/or stop memory to memory transfer
  \param[in]   DMA_Channel  Pointer to DMA channel peripheral
*/
__STATIC_FORCEINLINE void DMA_ChannelDisable (DMA_Channel_TypeDef *DMA_Channel) {
  DMA_Channel->CCR &= ~DMA_CCR_EN;
}

/**
  \fn          bool DMA_ChannelStatus (DMA_Channel_TypeDef *DMA_Channel)
  \brief       Check if channel is enabled or disabled
  \param[in]   DMA_Channel  Pointer to DMA channel peripheral
  \return      Channel Status
               - \b true Enabled
               - \b false Disabled
*/
__STATIC_FORCEINLINE bool DMA_ChannelStatus (DMA_Channel_TypeDef *DMA_Channel) {
  return (DMA_Channel->CCR & DMA_CCR_EN) ? true : false;
}

/**
  \fn          uint32_t DMA_ChannelTransferItemCount (DMA_Channel_TypeDef *DMA_Channel)
  \brief       Get number of data items to transfer
  \param[in]   DMA_channel  Pointer to DMA channel peripheral
  \return      Number of data items to transfer
*/
__STATIC_FORCEINLINE uint32_t DMA_ChannelTransferItemCount (DMA_Channel_TypeDef *DMA_Channel) {
  return DMA_Channel->CNDTR;
}

#endif /* DMA_STM32F10X_H_ */

/* ----------------------------- End of file ---------------------------------*/
