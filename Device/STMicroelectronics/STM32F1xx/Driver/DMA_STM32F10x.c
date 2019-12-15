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
 * Project: DMA Driver for STMicroelectronics STM32F1xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "device_config.h"
#include "asm/DMA_STM32F10x.h"
#include "asm/RCC_STM32F10x.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#if defined(STM32F100xE) ||                         \
    defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
  /* DMA2 peripheral exists on HD, XL, HD_VL and CL devices */
  #define STM32F10X_ENABLE_DMA2
#endif

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/* DMA1 Channel Events */
__WEAK void DMA1_Channel1_Event(uint32_t event);
__WEAK void DMA1_Channel2_Event(uint32_t event);
__WEAK void DMA1_Channel3_Event(uint32_t event);
__WEAK void DMA1_Channel4_Event(uint32_t event);
__WEAK void DMA1_Channel5_Event(uint32_t event);
__WEAK void DMA1_Channel6_Event(uint32_t event);
__WEAK void DMA1_Channel7_Event(uint32_t event);

#if defined (STM32F10X_ENABLE_DMA2)
/* DMA2 Channel Events */
__WEAK void DMA2_Channel1_Event(uint32_t event);
__WEAK void DMA2_Channel2_Event(uint32_t event);
__WEAK void DMA2_Channel3_Event(uint32_t event);
__WEAK void DMA2_Channel4_Event(uint32_t event);
__WEAK void DMA2_Channel5_Event(uint32_t event);
#endif

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void DMA_ChannelInitialize(DMA_INFO *info)
 * @brief       Initialize DMA Channel
 * @param[in]   info  DMA info
 */
void DMA_ChannelInitialize(DMA_INFO *info)
{
  if (info == NULL)
    return;

  DMA_TypeDef *dma = (DMA_TypeDef *)((uint32_t)info->instance & ~0x3FFUL);
  uint32_t offset = (info->ch_num-1) << 2U;

  if (dma == DMA1) {
    RCC_EnablePeriph(RCC_PERIPH_DMA1);
  }
  else {
    RCC_EnablePeriph(RCC_PERIPH_DMA2);
  }

  /* Disable the peripheral */
  info->instance->CCR = 0U;
  /* Clear all flags */
  dma->IFCR = 0xFU << offset;
  /* Enable IRQ */
  NVIC_ClearPendingIRQ(info->irq_num);
  NVIC_SetPriority(info->irq_num, RTE_DMA_INT_PRIORITY);
  NVIC_EnableIRQ(info->irq_num);
}

/**
 * @fn          void DMA_ChannelUninitialize(DMA_INFO *info)
 * @brief       Uninitialize DMA Channel
 * @param[in]   info  DMA info
 */
void DMA_ChannelUninitialize(DMA_INFO *info)
{
  if (info == NULL)
    return;

  DMA_TypeDef *dma = (DMA_TypeDef *)((uint32_t)info->instance & ~0x3FFUL);
  uint32_t offset = (info->ch_num-1) << 2U;

  /* Disable IRQ */
  NVIC_EnableIRQ(info->irq_num);
  /* Disable the peripheral */
  info->instance->CCR = 0U;
  /* Clear all flags */
  dma->IFCR = 0xFU << offset;
}

/**
 * @fn          void DMA_ChannelConfigure(DMA_Channel_TypeDef *DMA_Channel, uint32_t ccr, uint32_t cpar, uint32_t cmar, uint32_t cndtr)
 * @brief       Configure DMA channel for next transfer
 * @param[in]   DMA_Channel specifies pointer to DMA channel peripheral
 * @param[in]   cfg    Configuration register value
 * @param[in]   paddr  Peripheral address register value
 * @param[in]   maddr  Memory address register value
 * @param[in]   num    Number of data transfer register value (up to 65535)
 */
void DMA_ChannelConfigure(DMA_Channel_TypeDef *dma_cnl, uint32_t cfg, uint32_t paddr, uint32_t maddr, uint16_t num)
{
  __IO uint32_t ccr = dma_cnl->CCR;

  /* If DMA channel is enable */
  if (ccr & DMA_CCR_EN_Msk) {
    /* Disable DMA channel */
    dma_cnl->CCR = ccr & ~DMA_CCR_EN_Msk;
  }

  /* Configure DMA channel */
  dma_cnl->CPAR  = paddr;
  dma_cnl->CMAR  = maddr;
  dma_cnl->CNDTR = num;
  dma_cnl->CCR   = cfg;
}

void DMA1_Channel1_Event(uint32_t event)
{
  __NOP();
}

void DMA1_Channel2_Event(uint32_t event)
{
  __NOP();
}

void DMA1_Channel3_Event(uint32_t event)
{
  __NOP();
}

void DMA1_Channel4_Event(uint32_t event)
{
  __NOP();
}

void DMA1_Channel5_Event(uint32_t event)
{
  __NOP();
}

void DMA1_Channel6_Event(uint32_t event)
{
  __NOP();
}

void DMA1_Channel7_Event(uint32_t event)
{
  __NOP();
}

#if defined(STM32F10X_ENABLE_DMA2)

void DMA2_Channel1_Event (uint32_t event)
{
  __NOP();
}
void DMA2_Channel2_Event (uint32_t event)
{
  __NOP();
}
void DMA2_Channel3_Event (uint32_t event)
{
  __NOP();
}
void DMA2_Channel4_Event (uint32_t event)
{
  __NOP();
}
void DMA2_Channel5_Event (uint32_t event)
{
  __NOP();
}

#endif  /* STM32F10X_ENABLE_DMA2 */

/*******************************************************************************
 *  Interrupt Handlers
 ******************************************************************************/

/**
 \fn          void DMA1_Channel1_IRQHandler (void)
 \brief       DMA1 Channel1 interrupt handler
 */
void DMA1_Channel1_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 0) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 0;
  DMA1_Channel1_Event(events);
}

/**
 \fn          void DMA1_Channel2_IRQHandler (void)
 \brief       DMA1 Channel2 interrupt handler
 */
void DMA1_Channel2_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 4) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 4;
  DMA1_Channel2_Event(events);
}

/**
 \fn          void DMA1_Channel3_IRQHandler (void)
 \brief       DMA1 Channel3 interrupt handler
 */
void DMA1_Channel3_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 8) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 8;
  DMA1_Channel3_Event(events);
}

/**
 \fn          void DMA1_Channel4_IRQHandler (void)
 \brief       DMA1 Channel4 interrupt handler
 */
void DMA1_Channel4_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 12) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 12;
  DMA1_Channel4_Event(events);
}

/**
 \fn          void DMA1_Channel5_IRQHandler (void)
 \brief       DMA1 Channel5 interrupt handler
 */
void DMA1_Channel5_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 16) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 16;
  DMA1_Channel5_Event(events);
}

/**
 \fn          void DMA1_Channel6_IRQHandler (void)
 \brief       DMA1 Channel6 interrupt handler
 */
void DMA1_Channel6_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 20) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 20;
  DMA1_Channel6_Event(events);
}

/**
 \fn          void DMA1_Channel7_IRQHandler (void)
 \brief       DMA1 Channel7 interrupt handler
 */
void DMA1_Channel7_IRQHandler(void)
{
  uint32_t events;

  events = (DMA1->ISR >> 24) & DMA_CHANNEL_FLAGS;
  DMA1->IFCR = events << 24;
  DMA1_Channel7_Event(events);
}

#if defined (STM32F10X_ENABLE_DMA2)
/**
 \fn          void DMA2_Channel1_IRQHandler (void)
 \brief       DMA2 Channel1 interrupt handler
 */
void DMA2_Channel1_IRQHandler(void)
{
  uint32_t events;

  events = (DMA2->ISR >> 0) & DMA_CHANNEL_FLAGS;
  DMA2->IFCR = events << 0;
  DMA2_Channel1_Event(events);
}

/**
 \fn          void DMA2_Channel2_IRQHandler (void)
 \brief       DMA2 Channel2 interrupt handler
 */
void DMA2_Channel2_IRQHandler(void)
{
  uint32_t events;

  events = (DMA2->ISR >> 4) & DMA_CHANNEL_FLAGS;
  DMA2->IFCR = events << 4;
  DMA2_Channel2_Event(events);
}

/**
 \fn          void DMA2_Channel3_IRQHandler (void)
 \brief       DMA2 Channel3 interrupt handler
 */
void DMA2_Channel3_IRQHandler(void)
{
  uint32_t events;

  events = (DMA2->ISR >> 8) & DMA_CHANNEL_FLAGS;
  DMA2->IFCR = events << 8;
  DMA2_Channel3_Event(events);
}

#if defined (STM32F105xC) || defined (STM32F107xC)
/**
 \fn          void DMA2_Channel4_IRQHandler (void)
 \brief       DMA2 Channel4 interrupt handler
 */
void DMA2_Channel4_IRQHandler (void) {
  uint32_t events;

  events = (DMA2->ISR >> 12) & DMA_CHANNEL_FLAGS;
  DMA2->IFCR = events << 12;
  DMA2_Channel4_Event(events);
}

/**
 \fn          void DMA2_Channel5_IRQHandler (void)
 \brief       DMA2 Channel5 interrupt handler
 */
void DMA2_Channel5_IRQHandler (void) {
  uint32_t events;

  events = (DMA2->ISR >> 16) & DMA_CHANNEL_FLAGS;
  DMA2->IFCR = events << 16;
  DMA2_Channel5_Event(events);
}

#else

/**
 \fn          void DMA2_Channel4_5_IRQHandler (void)
 \brief       DMA2 Channel 4 and 5 interrupt handler
 */
void DMA2_Channel4_5_IRQHandler(void)
{
  uint32_t events;

  events = (DMA2->ISR >> 12) & DMA_CHANNEL_FLAGS;
  if (events) {
    /* Channel 4 events */
    DMA2->IFCR = events << 12;
    DMA2_Channel4_Event(events);
  }

  events = (DMA2->ISR >> 16) & DMA_CHANNEL_FLAGS;
  if (events) {
    /* Channel 5 events */
    DMA2->IFCR = events << 16;
    DMA2_Channel5_Event(events);
  }
}
#endif

#endif /* STM32F10X_ENABLE_DMA2 */

/* ----------------------------- End of file ---------------------------------*/
