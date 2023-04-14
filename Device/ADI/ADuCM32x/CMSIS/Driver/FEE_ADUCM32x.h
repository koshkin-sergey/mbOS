/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: Flash Driver Definitions for ADI ADuCM32x
 */

#ifndef FEE_ADUCM32X_H_
#define FEE_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/aducm32x.h>
#include <device_config.h>
#include <CMSIS/Driver/Driver_Flash.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* Flash Controller configuration definitions */
#if defined (DEV_FEE) && (DEV_FEE == 1)
  #define USE_FEE

  #if !defined(MMR_FEE)
    #error "FEE not available for selected device!"
    #undef USE_FEE
  #endif

  #define FEE_INT_PRIORITY          (IRQ_Priority_t)DEV_FEE_INT_PRIO
#endif

/* Flash driver flag definitions */
#define FEE_FLAG_INIT               (1UL << 0)    // Driver initialized
#define FEE_FLAG_POWER              (1UL << 1)    // Driver powered on

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef struct FlashXfer {
  const uint64_t *addr;
  const uint32_t *data;
  size_t          cnt;
} FlashXfer_t;

/**
 * @brief Flash driver runtime information
 */
typedef struct FlashInstance {
  ARM_Flash_SignalEvent_t   cb_event;
  ARM_FLASH_STATUS          status;
  FlashXfer_t               xfer;
  uint32_t volatile         flags;
} FlashInstance_t;

#endif /* FEE_ADUCM32X_H_ */
