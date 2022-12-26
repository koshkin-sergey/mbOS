/*
 * Copyright (C) 2017-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: DMA Driver Definitions for ADI ADuCM32x
 */

#ifndef DMA_ADUCM32X_H_
#define DMA_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @brief       Signal DMA Events.
 * @param[in]   event   DMA Event mask
 * @return      none
 */
typedef void (*DMA_SignalEvent_t)(uint32_t event);

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Initialize DMA peripheral
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
extern
int32_t DMA_Initialize(void);

/**
 * @brief       De-initialize DMA peripheral
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
extern
int32_t DMA_Uninitialize(void);

/**
 * @brief       Selects DMA requests
 * @param[in]   peri  DMA peripheral (0..13)
 * @param[in]   sel   Selects the DMA request for DMA input (0..3)
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
extern
int32_t DMA_PeripheralSelect(uint8_t peri, uint8_t sel);

/**
 * @brief       Configure DMA channel for next transfer
 * @param[in]   ch        Channel number (0..7)
 * @param[in]   src_addr  Source address
 * @param[in]   dest_addr Destination address
 * @param[in]   size      Amount of data to transfer
 * @param[in]   control   Channel control
 * @param[in]   config    Channel configuration
 * @param[in]   cb_event  Channel callback pointer
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
extern
int32_t DMA_ChannelConfigure(uint8_t ch, uint32_t src_addr, uint32_t dest_addr,
    uint32_t size, uint32_t control, uint32_t config, DMA_SignalEvent_t cb_event);

/**
 * @brief       Enable DMA channel
 * @param[in]   ch    Channel number (0..7)
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
extern
int32_t DMA_ChannelEnable(uint8_t ch);

/**
 * @brief       Disable DMA channel
 * @param[in]   ch    Channel number (0..7)
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
extern
int32_t DMA_ChannelDisable(uint8_t ch);

/**
 * @brief       Check if DMA channel is enabled or disabled
 * @param[in]   ch    Channel number (0..7)
 * @returns     Channel status
 *              - 1: channel enabled
 *              - 0: channel disabled
 */
extern
uint32_t DMA_ChannelGetStatus(uint8_t ch);

/**
 * @brief       Get number of transferred data
 * @param[in]   ch    Channel number (0..7)
 * @returns     Number of transferred data
 */
extern
uint32_t DMA_ChannelGetCount(uint8_t ch);

#endif /* DMA_ADUCM32X_H_ */

/* ----------------------------- End of file ---------------------------------*/
