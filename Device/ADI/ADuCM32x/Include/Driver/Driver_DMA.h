/*
 * Copyright (C) 2017-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef DRIVER_DMA_H_
#define DRIVER_DMA_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/Driver_Common.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* Current driver status flag definition */
#define DMA_INITIALIZED                 ((uint8_t)(1U))

/* DMA_Channel_Info status definition */
#define DMA_CHANNEL_CONFIGURED          ((uint8_t)(1U))
#define DMA_CHANNEL_BUSY                ((uint8_t)(1U << 1))

/* DMASTA definition */
#define DMASTA_MENABLE_Pos                0
#define DMASTA_MENABLE_Msk               (1 << DMASTA_MENABLE_Pos)
#define DMASTA_MENABLE_DISABLE           (0 << DMASTA_MENABLE_Pos)
#define DMASTA_MENABLE_ENABLE            (1 << DMASTA_MENABLE_Pos)

#define DMASTA_STATE_Pos                  4
#define DMASTA_STATE_Msk                 (0xF << DMASTA_STATE_Pos)
#define DMASTA_STATE_IDLE                (0x0 << DMASTA_STATE_Pos)
#define DMASTA_STATE_READ_CON_DATA       (0x1 << DMASTA_STATE_Pos)
#define DMASTA_STATE_READ_SRC_DATA_END   (0x2 << DMASTA_STATE_Pos)
#define DMASTA_STATE_READ_DEST_DATA_END  (0x3 << DMASTA_STATE_Pos)
#define DMASTA_STATE_READ_SRC_DATA       (0x4 << DMASTA_STATE_Pos)
#define DMASTA_STATE_WRITE_DST_DATA      (0x5 << DMASTA_STATE_Pos)
#define DMASTA_STATE_WRITE_REQ_CLR       (0x6 << DMASTA_STATE_Pos)
#define DMASTA_STATE_WRITE_CON_DATA      (0x7 << DMASTA_STATE_Pos)
#define DMASTA_STATE_STALLED             (0x8 << DMASTA_STATE_Pos)
#define DMASTA_STATE_DONE                (0x9 << DMASTA_STATE_Pos)

#define DMASTA_CHNLSM1_Pos                16
#define DMASTA_CHNLSM1_Msk               (0x1F << DMASTA_CHNLSM1_Pos)

/* DMACFG definition */
#define DMACFG_MENABLE_Pos                0
#define DMACFG_MENABLE_Msk               (1 << DMASTA_MENABLE_Pos)
#define DMACFG_MENABLE_DISABLE           (0 << DMASTA_MENABLE_Pos)
#define DMACFG_MENABLE_ENABLE            (1 << DMASTA_MENABLE_Pos)

/****** DMA Control Codes *****/
#define DMA_CHANNEL_CONFIGURE_PRI_SRC_ENDP  (0x01UL)  // arg1 = channel, arg2 = Source end pointer
#define DMA_CHANNEL_CONFIGURE_PRI_DEST_ENDP (0x02UL)  // arg1 = channel, arg2 = Destination end pointer
#define DMA_CHANNEL_CONFIGURE_PRI_CONTROL   (0x03UL)  // arg1 = channel, arg2 = Control

#define DMA_CHANNEL_CONFIGURE_ALT_SRC_ENDP  (0x04UL)  // arg1 = channel, arg2 = Source end pointer
#define DMA_CHANNEL_CONFIGURE_ALT_DEST_ENDP (0x05UL)  // arg1 = channel, arg2 = Destination end pointer
#define DMA_CHANNEL_CONFIGURE_ALT_CONTROL   (0x06UL)  // arg1 = channel, arg2 = Control

#define DMA_CHANNEL_REQ_ENABLE              (0x07UL)  // arg1 = channel
#define DMA_CHANNEL_REQ_DISABLE             (0x08UL)  // arg1 = channel

#define DMA_CHANNEL_PRI_SET                 (0x09UL)  // arg1 = channel
#define DMA_CHANNEL_ALT_SET                 (0x0AUL)  // arg1 = channel

#define DMA_CHANNEL_PRIORITY_NORMAL         (0x0BUL)  // arg1 = channel
#define DMA_CHANNEL_PRIORITY_HIGH           (0x0CUL)  // arg1 = channel

#define DMA_CHANNEL_SW_REQ                  (0x0DUL)  // arg1 = channel
#define DMA_CHANNEL_ERR_CLR                 (0x0EUL)  // arg1 = channel

#define DMA_CHANNEL_BYTE_SWAP_ENABLE        (0x0FUL)  // arg1 = channel
#define DMA_CHANNEL_BYTE_SWAP_DISABLE       (0x10UL)  // arg1 = channel

/* CHNL_CFG definition */
#define DMA_CHNL_CFG_CYCLE_CTRL_Pos          0
#define DMA_CHNL_CFG_CYCLE_CTRL_Msk          (0x3 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_Size         3
#define DMA_CHNL_CFG_CYCLE_CTRL_STOP         (0 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_BASIC        (1 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_AUTOREQ      (2 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_PINGPONG     (3 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_MSGP         (4 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_MSGA         (5 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_PSGP         (6 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHNL_CFG_CYCLE_CTRL_PSGA         (7 << DMA_CHNL_CFG_CYCLE_CTRL_Pos)

#define DMA_CHNL_CFG_N_MINUS_1_Pos           4
#define DMA_CHNL_CFG_N_MINUS_1_Size          10

#define DMA_CHNL_CFG_R_POWER_Pos             14

#define DMA_CHNL_CFG_SRC_SIZE_Pos            24
#define DMA_CHNL_CFG_SRC_SIZE_Size           2
#define DMA_CHNL_CFG_SRC_SIZE_BYTE           (0 << DMA_CHNL_CFG_SRC_SIZE_Pos)
#define DMA_CHNL_CFG_SRC_SIZE_HALFWORD       (1 << DMA_CHNL_CFG_SRC_SIZE_Pos)
#define DMA_CHNL_CFG_SRC_SIZE_WORD           (2 << DMA_CHNL_CFG_SRC_SIZE_Pos)

#define DMA_CHNL_CFG_SRC_INC_Pos             26
#define DMA_CHNL_CFG_SRC_INC_Size            2
#define DMA_CHNL_CFG_SRC_INC_BYTE            (0 << DMA_CHNL_CFG_SRC_INC_Pos)
#define DMA_CHNL_CFG_SRC_INC_HALFWORD        (1 << DMA_CHNL_CFG_SRC_INC_Pos)
#define DMA_CHNL_CFG_SRC_INC_WORD            (2 << DMA_CHNL_CFG_SRC_INC_Pos)
#define DMA_CHNL_CFG_SRC_INC_NO_INC          (3 << DMA_CHNL_CFG_SRC_INC_Pos)

#define DMA_CHNL_CFG_DST_SIZE_Pos            28
#define DMA_CHNL_CFG_DST_SIZE_Size           2
#define DMA_CHNL_CFG_DST_SIZE_BYTE           (0 << DMA_CHNL_CFG_DST_SIZE_Pos)
#define DMA_CHNL_CFG_DST_SIZE_HALFWORD       (1 << DMA_CHNL_CFG_DST_SIZE_Pos)
#define DMA_CHNL_CFG_DST_SIZE_WORD           (2 << DMA_CHNL_CFG_DST_SIZE_Pos)

#define DMA_CHNL_CFG_DST_INC_Pos             30
#define DMA_CHNL_CFG_DST_INC_Size            2
#define DMA_CHNL_CFG_DST_INC_BYTE            (0 << DMA_CHNL_CFG_DST_INC_Pos)
#define DMA_CHNL_CFG_DST_INC_HALFWORD        (1 << DMA_CHNL_CFG_DST_INC_Pos)
#define DMA_CHNL_CFG_DST_INC_WORD            (2 << DMA_CHNL_CFG_DST_INC_Pos)
#define DMA_CHNL_CFG_DST_INC_NO_INC          (3 << DMA_CHNL_CFG_DST_INC_Pos)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @brief       Signal DMA Events.
 * @param[in]   event   DMA Event mask
 * @return      none
 */
typedef void (*DMA_SignalEvent_t)(uint32_t event);

/* -----------DMA Channel Configure Structure----------- */
typedef enum {
  DMA_DIR_PERIPH_DST,
  DMA_DIR_PERIPH_SRC,
} CFG_DMA_DIR;

typedef enum {
  DMA_INC_BYTE,
  DMA_INC_HALF_WORD,
  DMA_INC_WORD,
  DMA_INC_DISABLE,
} CFG_DMA_INC;

typedef enum {
  DMA_DATA_SIZE_BYTE,
  DMA_DATA_SIZE_HALF_WORD,
  DMA_DATA_SIZE_WORD,
} CFG_DMA_DATA_SIZE;

typedef enum {
  DMA_MODE_STOP,
  DMA_MODE_BASIC,
  DMA_MODE_AUTO,
  DMA_MODE_PINGPONG,
  DMA_MODE_MEMORY_SG_PRI,
  DMA_MODE_MEMORY_SG_ALT,
  DMA_MODE_PERIPH_SG_PRI,
  DMA_MODE_PERIPH_SG_ALT,
} CFG_DMA_MODE;

typedef enum {
  DMA_PRIORITY_DEFAULT,
  DMA_PRIORITY_HIGH,
} CFG_DMA_PRIORITY;

typedef struct DMA_CHNL_CFG {
  uint32_t          periph_addr;
  uint32_t          memory_addr;
  CFG_DMA_DIR       dir;
  uint32_t          buffer_size;
  CFG_DMA_INC       periph_inc;
  CFG_DMA_INC       memory_inc;
  CFG_DMA_DATA_SIZE periph_data_size;
  CFG_DMA_DATA_SIZE memory_data_size;
  CFG_DMA_MODE      mode;
  CFG_DMA_PRIORITY  priority;
} DMA_CHNL_CFG_t;

/* -----------DMA Channel Structure----------- */
typedef struct CHAN_DESC {
  uint32_t SRC_END_PTR;
  uint32_t DST_END_PTR;
  uint32_t CHNL_CFG;
  uint32_t Reserved;
} CHAN_DESC_t;

typedef struct DMA_CHAN_DESC {
  CHAN_DESC_t Channel_0;
  CHAN_DESC_t Channel_1;
  CHAN_DESC_t Channel_2;
  CHAN_DESC_t Channel_3;
  CHAN_DESC_t Channel_4;
  CHAN_DESC_t Channel_5;
  CHAN_DESC_t Channel_6;
  CHAN_DESC_t Channel_7;
  CHAN_DESC_t Channel_8;
  CHAN_DESC_t Channel_9;
  CHAN_DESC_t Channel_10;
  CHAN_DESC_t Channel_11;
  CHAN_DESC_t Channel_12;
  CHAN_DESC_t Channel_13;
  CHAN_DESC_t Channel_14;
  CHAN_DESC_t Channel_15;
} DMA_CHAN_DESC_t;

typedef struct DMA_STR_DESC {
  DMA_CHAN_DESC_t DMA_Primary_Structure;
  DMA_CHAN_DESC_t DMA_Alternate_Structure;
} DMA_STR_DESC_t;

typedef struct DMA_INFO {
  uint32_t dma_status;
  uint32_t channel_busy;
} DMA_INFO_t;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

#if defined (USE_DMA) && (DEV_USE_DMA == 1)
extern DMA_STR_DESC_t DMA_Structure;
#endif

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Initialize DMA peripheral
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */

/**
 * @brief       De-initialize DMA peripheral
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
/**
 * @brief       Enable DMA channel
 * @param[in]   ch    Channel number (0..7)
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
/**
 * @brief       Disable DMA channel
 * @param[in]   ch    Channel number (0..7)
 * @returns     -  0: function succeeded
 *              - -1: function failed
 */
/**
 * @brief       Check if DMA channel status
 * @param[in]   ch    Channel number (0..7)
 * @returns     Channel status
 */
/**
 * @brief       Check if DMA status
 * @returns     DMA status register
 */

/**
 * @brief Access structure of the DMA Driver.
 */
typedef struct Driver_DMA{
  int32_t         (*Initialize)         (void);
  int32_t         (*Uninitialize)       (void);
  int32_t         (*ChannelConfig)      (uint8_t ch, DMA_CHNL_CFG_t *cfg);
  int32_t         (*ChannelEnable)      (uint8_t ch);
  int32_t         (*ChannelDisable)     (uint8_t ch);
  uint32_t        (*GetChannelStatus)   (uint8_t ch);
  uint32_t        (*GetStatus)          (void);
} const Driver_DMA_t;

#endif /* DRIVER_DMA_H_ */
