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
 * Project: DMA Driver Definitions for STMicroelectronics STM32F4xx
 */

#ifndef DMA_STM32F4XX_H_
#define DMA_STM32F4XX_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include "stm32f4xx.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define _DMA_CHANNEL_x(x)               DMA_CHANNEL_##x
#define  DMA_CHANNEL_x(x)              _DMA_CHANNEL_x(x)

#define  DMA_PRIORITY(x)              ((x == 0) ? DMA_PRIORITY_LOW    : \
                                       (x == 1) ? DMA_PRIORITY_MEDIUM : \
                                       (x == 2) ? DMA_PRIORITY_HIGH   : \
                                                  DMA_PRIORITY_VERY_HIGH)

#define _DMAx_STREAMy(x, y)             DMA##x##_Stream##y
#define  DMAx_STREAMy(x, y)            _DMAx_STREAMy(x, y)

#define _DMAx_STREAMy_IRQ(x, y)         DMA##x##_Stream##y##_IRQHandler
#define  DMAx_STREAMy_IRQ(x, y)        _DMAx_STREAMy_IRQ(x, y)

#define _DMAx_STREAMy_IRQn(x, y)        DMA##x##_Stream##y##_IRQn
#define  DMAx_STREAMy_IRQn(x, y)       _DMAx_STREAMy_IRQn(x, y)

/****** DMA Event ******/
#define DMA_EVENT_TRANSFER_COMPLETE       (1U << 0) ///< DMA transfer complete
#define DMA_EVENT_HALF_TRANSFER_COMPLETE  (1U << 1) ///< DMA half-transfer complete
#define DMA_EVENT_TRANSFER_ABORT          (1U << 2) ///< DMA transfer abort
#define DMA_EVENT_TRANSFER_ERROR          (1U << 3) ///< DMA transfer error
#define DMA_EVENT_FIFO_ERROR              (1U << 4) ///< DMA FIFO underrun/overrun condition is detected
#define DMA_EVENT_DIRECT_MODE_ERROR       (1U << 5) ///< DMA direct mode error

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef void (*DMA_Callback_t)(uint32_t event);

/* DMA States */
typedef enum {
  DMA_STATE_RESET       = 0U,       /*!< DMA not yet initialized or disabled */
  DMA_STATE_INITIALIZED = 1U,       /*!< DMA initialized                     */
  DMA_STATE_READY       = 2U,       /*!< DMA initialized and ready for use   */
  DMA_STATE_BUSY        = 3U,       /*!< DMA process is ongoing              */
  DMA_STATE_ABORT       = 4U,       /*!< DMA Abort state                     */
  DMA_STATE_Reserved    = 0x7FFFFFFF
} DMA_STATE_t;

typedef enum {
  DMA_CHANNEL_0 = 0x00000000U,          /*!< DMA Channel 0 */
  DMA_CHANNEL_1 = 0x02000000U,          /*!< DMA Channel 1 */
  DMA_CHANNEL_2 = 0x04000000U,          /*!< DMA Channel 2 */
  DMA_CHANNEL_3 = 0x06000000U,          /*!< DMA Channel 3 */
  DMA_CHANNEL_4 = 0x08000000U,          /*!< DMA Channel 4 */
  DMA_CHANNEL_5 = 0x0A000000U,          /*!< DMA Channel 5 */
  DMA_CHANNEL_6 = 0x0C000000U,          /*!< DMA Channel 6 */
  DMA_CHANNEL_7 = 0x0E000000U,          /*!< DMA Channel 7 */
  DMA_CHANNEL_Reserved = 0x7FFFFFFFU
} DMA_Channel_t;

typedef enum {
  DMA_DIR_PER_TO_MEM = 0x00000000U,     /*!< Peripheral to memory direction */
  DMA_DIR_MEM_TO_PER = DMA_SxCR_DIR_0,  /*!< Memory to peripheral direction */
  DMA_DIR_MEM_TO_MEM = DMA_SxCR_DIR_1,  /*!< Memory to memory direction     */
  DMA_DIR_Reserved   = 0x7FFFFFFFU
} DMA_Dir_t;

typedef enum {
  DMA_PINC_DISABLE  = 0x00000000U,      /*!< Peripheral increment mode disable */
  DMA_PINC_ENABLE   = DMA_SxCR_PINC,    /*!< Peripheral increment mode enable  */
  DMA_PINC_Reserved = 0x7FFFFFFF
} DMA_PerInc_t;

typedef enum {
  DMA_MINC_DISABLE  = 0x00000000U,      /*!< Memory increment mode disable */
  DMA_MINC_ENABLE   = DMA_SxCR_MINC,    /*!< Memory increment mode enable  */
  DMA_MINC_Reserved = 0x7FFFFFFF
} DMA_MemInc_t;

typedef enum {
  DMA_PDATAALIGN_BYTE     = 0x00000000U,      /*!< Peripheral data alignment: Byte     */
  DMA_PDATAALIGN_HALFWORD = DMA_SxCR_PSIZE_0, /*!< Peripheral data alignment: HalfWord */
  DMA_PDATAALIGN_WORD     = DMA_SxCR_PSIZE_1, /*!< Peripheral data alignment: Word     */
  DMA_PDATAALIGN_Reserved = 0x7FFFFFFF
} DMA_PerDataAlign_t;

typedef enum {
  DMA_MDATAALIGN_BYTE     = 0x00000000U,      /*!< Memory data alignment: Byte     */
  DMA_MDATAALIGN_HALFWORD = DMA_SxCR_MSIZE_0, /*!< Memory data alignment: HalfWord */
  DMA_MDATAALIGN_WORD     = DMA_SxCR_MSIZE_1, /*!< Memory data alignment: Word     */
  DMA_MDATAALIGN_Reserved = 0x7FFFFFFF
} DMA_MemDataAlign_t;

typedef enum {
  DMA_MODE_NORMAL   = 0x00000000U,            /*!< Normal mode                  */
  DMA_MODE_CIRCULAR = DMA_SxCR_CIRC,          /*!< Circular mode                */
  DMA_MODE_PFCTRL   = DMA_SxCR_PFCTRL,        /*!< Peripheral flow control mode */
  DMA_MODE_Reserved = 0x7FFFFFFF
} DMA_Mode_t;

typedef enum {
  DMA_PRIORITY_LOW       = 0x00000000U,       /*!< Priority level: Low       */
  DMA_PRIORITY_MEDIUM    = DMA_SxCR_PL_0,     /*!< Priority level: Medium    */
  DMA_PRIORITY_HIGH      = DMA_SxCR_PL_1,     /*!< Priority level: High      */
  DMA_PRIORITY_VERY_HIGH = DMA_SxCR_PL,       /*!< Priority level: Very High */
  DMA_PRIORITY_Reserved  = 0x7FFFFFFF
} DMA_Priority_t;

typedef enum {
  DMA_FIFOMODE_DISABLE  = 0x00000000U,        /*!< FIFO mode disable */
  DMA_FIFOMODE_ENABLE   = DMA_SxFCR_DMDIS,    /*!< FIFO mode enable  */
  DMA_FIFOMODE_Reserved = 0x7FFFFFFF
} DMA_FIFOMode_t;

typedef enum {
  DMA_FIFO_THRESHOLD_1QUARTERFULL  = 0x00000000U,     /*!< FIFO threshold 1 quart full configuration  */
  DMA_FIFO_THRESHOLD_HALFFULL      = DMA_SxFCR_FTH_0, /*!< FIFO threshold half full configuration     */
  DMA_FIFO_THRESHOLD_3QUARTERSFULL = DMA_SxFCR_FTH_1, /*!< FIFO threshold 3 quarts full configuration */
  DMA_FIFO_THRESHOLD_FULL          = DMA_SxFCR_FTH,   /*!< FIFO threshold full configuration          */
  DMA_FIFO_THRESHOLD_Reserved
} DMA_FIFOThrhld_t;

typedef enum {
  DMA_MBURST_SINGLE   = 0x00000000U,
  DMA_MBURST_INC4     = DMA_SxCR_MBURST_0,
  DMA_MBURST_INC8     = DMA_SxCR_MBURST_1,
  DMA_MBURST_INC16    = DMA_SxCR_MBURST,
  DMA_MBURST_Reserved = 0x7FFFFFFF
} DMA_MemBurst_t;

typedef enum {
  DMA_PBURST_SINGLE   = 0x00000000U,
  DMA_PBURST_INC4     = DMA_SxCR_PBURST_0,
  DMA_PBURST_INC8     = DMA_SxCR_PBURST_1,
  DMA_PBURST_INC16    = DMA_SxCR_PBURST,
  DMA_PBURST_Reserved = 0x7FFFFFFF
} DMA_PerBurst_t;

typedef struct DMA_StreamConfig_s {
  DMA_Dir_t Direction;              /*!< Specifies the data transfer direction.                                           */
  DMA_PerInc_t PerInc;              /*!< Specifies whether the Peripheral address register should be incremented or not.  */
  DMA_MemInc_t MemInc;              /*!< Specifies whether the memory address register should be incremented or not.      */
  DMA_PerDataAlign_t PerDataAlign;  /*!< Specifies the Peripheral data width.                                             */
  DMA_MemDataAlign_t MemDataAlign;  /*!< Specifies the Memory data width.                                                 */
  DMA_Mode_t Mode;                  /*!< Specifies the operation mode.                                                    */
  DMA_FIFOMode_t FIFOMode;          /*!< Specifies if the FIFO mode or Direct mode will be used for the specified stream. */
  DMA_FIFOThrhld_t FIFOThreshold;   /*!< Specifies the FIFO threshold level.                                              */
  DMA_MemBurst_t MemBurst;          /*!< Specifies the Burst transfer configuration for the memory transfers.             */
  DMA_PerBurst_t PerBurst;          /*!< Specifies the Burst transfer configuration for the peripheral transfers.         */
} DMA_StreamConfig_t;

typedef struct DMA_Base_Reg_s {
  __IO uint32_t ISR;   /* DMA interrupt status register */
  __IO uint32_t Reserved;
  __IO uint32_t IFCR;  /* DMA interrupt flag clear register */
} DMA_Base_Reg_t;

typedef struct DMA_Handle_s {
  uint32_t bit_offset;
  DMA_Base_Reg_t *dma_reg;
  DMA_STATE_t state;
  DMA_StreamConfig_t config;
} DMA_Handle_t;

typedef const struct DMA_Resources_s {
  DMA_Handle_t         *handle;             // DMA Handle
  DMA_Stream_TypeDef   *stream;             // DMA Stream
  DMA_Channel_t         channel;            // DMA channel
  DMA_Priority_t        priority;           // DMA stream priority
  DMA_Callback_t        cb_event;           // Callback event
  uint32_t              cb_priority;        // Callback event priority
  IRQn_Type             irq_num;            // DMA stream IRQ Number
  uint8_t               reserved[3];        // Reserved
} DMA_Resources_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @fn          void DMA_Initialize(DMA_Resources_t *res)
 * @brief       Initialize DMA stream
 * @param[in]   res  Pointer to DMA resources
 */
void DMA_Initialize(DMA_Resources_t *res);

/**
 * @fn          void DMA_Uninitialize(DMA_Resources_t res)
 * @brief       Uninitialize DMA stream
 * @param[in]   res  Pointer to DMA resources
 */
void DMA_Uninitialize(DMA_Resources_t *res);

/**
 * @fn          void DMA_StreamConfig(const DMA_Resources_t *res)
 * @brief       Configure the DMA Stream
 * @param[in]   res  Pointer to DMA resources
 */
void DMA_StreamConfig(const DMA_Resources_t *res);

/**
 * @fn          void DMA_StreamEnable(DMA_Resources_t *res, uint32_t per_addr, uint32_t mem_addr, uint32_t num)
 * @brief       Enable stream and/or start memory to memory transfer
 * @param[in]   res  Pointer to DMA resources
 * @param[in]   per_addr
 * @param[in]   mem_addr
 * @param[in]   num
 */
void DMA_StreamEnable(DMA_Resources_t *res, uint32_t per_addr, uint32_t mem_addr, uint32_t num);

/**
 * @fn          void DMA_StreamDisable(DMA_Resources_t *res)
 * @brief       Disable stream and/or stop memory to memory transfer
 * @param[in]   res   Pointer to DMA resources
 */
void DMA_StreamDisable(DMA_Resources_t *res);

/**
 * @fn          void DMA_IRQ_Handle(DMA_Resources_t *res)
 * @brief       DMA Interrupt Handle
 * @param[in]   res   Pointer to DMA resources
 */
void DMA_IRQ_Handle(DMA_Resources_t *res);

#endif /* DMA_STM32F4XX_H_ */

/* ----------------------------- End of file ---------------------------------*/
