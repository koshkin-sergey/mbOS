/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: DMA Driver for STMicroelectronics STM32F7xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "DMA_STM32F7xx.h"
#include "device_config.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define DMA_FLAG_FEIF                 (1U << 0) ///< Stream FIFO error interrupt flag
#define DMA_FLAG_DMEIF                (1U << 2) ///< Stream direct mode error interrupt flag
#define DMA_FLAG_TEIF                 (1U << 3) ///< Stream transfer error interrupt flag
#define DMA_FLAG_HTIF                 (1U << 4) ///< Stream half transfer interrupt flag
#define DMA_FLAG_TCIF                 (1U << 5) ///< Stream transfer complete interrupt flag

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* lookup table for necessary bitshift of flags within status registers */
static const uint8_t flag_offset[] = {0U, 6U, 16U, 22U};

static DMA_Resources_t* dma_res[16];

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void DMA_Initialize(DMA_Resources_t *res)
 * @brief       Initialize DMA stream
 * @param[in]   res  Pointer to DMA resources
 */
void DMA_Initialize(DMA_Resources_t *res)
{
  if (res == NULL)
    return;

  uint32_t stream_number = (((uint32_t)res->stream & 0xFFU) - 16U) / 24U;
  uint32_t dma_reg_addr = ((uint32_t)res->stream & (uint32_t)(~0x3FF));

  if (dma_reg_addr == DMA1_BASE) {
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    res->handle->stream_number = stream_number;
  }
  else {
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    res->handle->stream_number = stream_number + 8U;
  }

  if (stream_number & 4U) {
    dma_reg_addr += 4U;
  }

  res->handle->bit_offset    = flag_offset[stream_number & 3U];
  res->handle->dma_reg       = (DMA_Base_Reg_t *)dma_reg_addr;

  /* Disable the peripheral */
  res->stream->CR &= ~DMA_SxCR_EN;

  /* Check if the DMA Stream is disabled */
  while (res->stream->CR & DMA_SxCR_EN);

  /* Clear all interrupt flags */
  res->handle->dma_reg->IFCR = 0x3D << res->handle->bit_offset;

  /* Enable IRQ */
  NVIC_ClearPendingIRQ(res->irq_num);
  NVIC_SetPriority(res->irq_num, res->cb_priority);
  NVIC_EnableIRQ(res->irq_num);

  res->handle->state = DMA_STATE_INITIALIZED;
}

/**
 * @fn          void DMA_Uninitialize(DMA_Resources_t res)
 * @brief       Uninitialize DMA stream
 * @param[in]   res  Pointer to DMA resources
 */
void DMA_Uninitialize(DMA_Resources_t *res)
{
  if (res == NULL)
    return;

  DMA_Stream_TypeDef *stream = res->stream;

  /* Disable IRQ */
  NVIC_DisableIRQ(res->irq_num);

  /* Reset DMA Stream */
  stream->CR = 0U;
  stream->NDTR = 0U;
  stream->PAR = 0U;
  stream->M0AR = 0U;
  stream->M1AR = 0U;
  stream->FCR = 0x21U;

  /* Clear all interrupt flags */
  res->handle->dma_reg->IFCR = 0x3D << res->handle->bit_offset;

  res->handle->state = DMA_STATE_RESET;
}

/**
 * @fn          void DMA_Config(const DMA_Resources_t *res)
 * @brief       Configure the DMA Stream
 * @param[in]   res  Pointer to DMA resources
 */
void DMA_Config(const DMA_Resources_t *res)
{
  if (res == NULL)
    return;

  uint32_t val;
  DMA_StreamConfig_t *cfg = &res->handle->config;
  DMA_Stream_TypeDef *stream = res->stream;

  /* Change DMA peripheral state */
  res->handle->state = DMA_STATE_BUSY;

  /* Disable the peripheral */
  stream->CR &= ~DMA_SxCR_EN;

  /* Check if the DMA Stream is disabled */
  while (stream->CR & DMA_SxCR_EN);

  /* Get the CR register value */
  val = (stream->CR & (DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE));

  /* Prepare the DMA Stream configuration */
  val |= (res->channel      | cfg->Direction    | cfg->PerInc | cfg->MemInc |
          cfg->PerDataAlign | cfg->MemDataAlign | cfg->Mode   | res->priority);

  /* The memory burst and peripheral burst are not used when the FIFO is disabled */
  if(cfg->FIFOMode == DMA_FIFOMODE_ENABLE) {
    /* Get memory burst and peripheral burst */
    val |= (cfg->MemBurst | cfg->PerBurst);
  }

  /* Write to DMA Stream CR register */
  stream->CR = val;

  /* Get the FCR register value */
  val = (stream->FCR & DMA_SxFCR_FEIE);

  /* Prepare the DMA Stream FIFO configuration */
  val |= cfg->FIFOMode;

  /* The FIFO threshold is not used when the FIFO mode is disabled */
  if (cfg->FIFOMode == DMA_FIFOMODE_ENABLE) {
    /* Get the FIFO threshold */
    val |= cfg->FIFOThreshold;
  }

  /* Write to DMA Stream FCR */
  stream->FCR = val;

  /* Change DMA peripheral state */
  res->handle->state = DMA_STATE_READY;
}

/**
 * @fn          void DMA_Start(DMA_Resources_t *res, uint32_t per_addr, uint32_t mem_addr, uint32_t num)
 * @brief       Enable stream and/or start memory to memory transfer
 * @param[in]   res  Pointer to DMA resources
 * @param[in]   per_addr
 * @param[in]   mem_addr
 * @param[in]   num
 */
void DMA_Start(DMA_Resources_t *res, uint32_t per_addr, uint32_t mem_addr, uint32_t num)
{
  if ((res == NULL) || (per_addr == 0U) || (mem_addr == 0U) || (num == 0U)) {
    return;
  }

  DMA_Stream_TypeDef *stream = res->stream;
  DMA_Handle_t *handle = res->handle;

  if (handle->state == DMA_STATE_READY) {
    /* Change DMA peripheral state */
    handle->state = DMA_STATE_BUSY;

    stream->NDTR = num;
    stream->PAR  = per_addr;
    stream->M0AR = mem_addr;
    stream->M1AR = 0U;

    /* Clear all interrupt flags */
    handle->dma_reg->IFCR = 0x3D << handle->bit_offset;
    dma_res[handle->stream_number] = res;

    stream->CR |= (DMA_SxCR_TCIE | DMA_SxCR_EN);
  }
}

/**
 * @fn          void DMA_Abort(DMA_Resources_t *res)
 * @brief       Disable stream and/or stop memory to memory transfer
 * @param[in]   res   Pointer to DMA resources
 */
void DMA_Abort(DMA_Resources_t *res)
{
  if ((res == NULL) || (res->handle->state != DMA_STATE_BUSY))
    return;

  res->handle->state = DMA_STATE_ABORT;

  /* Disable the peripheral */
  res->stream->CR &= ~DMA_SxCR_EN;
}

/**
 * @fn          void DMA_WaitAbort(DMA_Resources_t *res)
 * @brief       Waiting for stream transfer to complete
 * @param[in]   res   Pointer to DMA resources
 */
void DMA_WaitAbort(DMA_Resources_t *res)
{
  while (res->handle->state == DMA_STATE_ABORT) {
    __NOP();
  }
}

/**
 * @fn          void DMA_IRQ_Handle(DMA_Resources_t *res, const void *param)
 * @brief       DMA Interrupt Handle
 * @param[in]   res    Pointer to DMA resources
 */
static void DMA_IRQ_Handle(DMA_Resources_t *res)
{
  uint32_t event = 0U, isr, cr;
  DMA_Handle_t *handle = res->handle;
  DMA_Base_Reg_t *dma = handle->dma_reg;
  DMA_Stream_TypeDef *stream = res->stream;

  cr = stream->CR;
  isr = dma->ISR >> handle->bit_offset;

  if (isr & (DMA_FLAG_FEIF | DMA_FLAG_DMEIF | DMA_FLAG_TEIF)) {
    /* FIFO Error Interrupt management */
    if (isr & DMA_FLAG_FEIF) {
      /* Clear FIFO Error Interrupt flag */
      dma->IFCR = DMA_FLAG_FEIF << handle->bit_offset;
      event |= DMA_EVENT_FIFO_ERROR;
    }

    /* Direct Mode Error Interrupt management */
    if (isr & DMA_FLAG_DMEIF) {
      /* Clear Direct Mode Error Interrupt flag */
      dma->IFCR = DMA_FLAG_DMEIF << handle->bit_offset;
      event |= DMA_EVENT_DIRECT_MODE_ERROR;
    }

    /* Transfer Error Interrupt management */
    if (isr & DMA_FLAG_TEIF) {
      /* Clear Transfer Error Interrupt flag */
      dma->IFCR = DMA_FLAG_TEIF << handle->bit_offset;
      event |= DMA_EVENT_TRANSFER_ERROR;
    }
  }

  /* Half Transfer Complete Interrupt management */
  if ((cr & DMA_SxCR_HTIE) && (isr & DMA_FLAG_HTIF)) {
    /* Clear Half Transfer Complete Interrupt flag */
    dma->IFCR = DMA_FLAG_HTIF << handle->bit_offset;

    if (!(cr & DMA_SxCR_CIRC))
      stream->CR &= ~DMA_SxCR_HTIE;

    event |= DMA_EVENT_HALF_TRANSFER_COMPLETE;
  }

  /* Transfer Complete Interrupt management */
  if ((cr & DMA_SxCR_TCIE) && (isr & DMA_FLAG_TCIF)) {
    if (handle->state == DMA_STATE_ABORT) {
      /* Disable all the transfer interrupts */
      stream->CR &= ~(DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE);
      stream->FCR &= ~DMA_SxFCR_FEIE;

      /* Clear all interrupt flags */
      handle->dma_reg->IFCR = 0x3D << handle->bit_offset;
      /* Change the DMA state */
      handle->state = DMA_STATE_READY;

      event |= DMA_EVENT_TRANSFER_ABORT;
    }
    else {
      /* Clear Transfer Complete Interrupt flag */
      dma->IFCR = DMA_FLAG_TCIF << handle->bit_offset;

      if (!(cr & DMA_SxCR_CIRC))
        stream->CR &= ~DMA_SxCR_TCIE;

      /* Change the DMA state */
      handle->state = DMA_STATE_READY;

      event |= DMA_EVENT_TRANSFER_COMPLETE;
    }
  }

  if (res->cb_event) {
    res->cb_event(event, res->cb_param);
  }
}

void DMA1_Stream0_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[0]);
}

void DMA1_Stream1_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[1]);
}

void DMA1_Stream2_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[2]);
}

void DMA1_Stream3_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[3]);
}

void DMA1_Stream4_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[4]);
}

void DMA1_Stream5_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[5]);
}

void DMA1_Stream6_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[6]);
}

void DMA1_Stream7_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[7]);
}

void DMA2_Stream0_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[8]);
}

void DMA2_Stream1_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[9]);
}

void DMA2_Stream2_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[10]);
}

void DMA2_Stream3_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[11]);
}

void DMA2_Stream4_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[12]);
}

void DMA2_Stream5_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[13]);
}

void DMA2_Stream6_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[14]);
}

void DMA2_Stream7_IRQHandler(void)
{
  DMA_IRQ_Handle(dma_res[15]);
}

/* ----------------------------- End of file ---------------------------------*/
