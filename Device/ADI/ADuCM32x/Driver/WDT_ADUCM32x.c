/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
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
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/WDT_ADUCM32x.h>

#include <stddef.h>
#include <asm/aducm32x.h>
#include <device_config.h>

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static struct info {
  WDT_SignalEvent_t cb_event;
} WDT_Info;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static int32_t WDT_Setup(uint32_t interval, WDT_SignalEvent_t cb_event)
{
  uint32_t load;
  uint32_t pre;
  int32_t ret = WDT_DRIVER_ERROR;

  if (interval == 0U || interval > 8000000U) {
    return (ARM_DRIVER_ERROR_PARAMETER);
  }

  if ((MMR_WDT->T3STA & (T3STA_LOCK_Msk | T3STA_CON_Msk | T3STA_LD_Msk)) == 0U) {
    pre  = 0U;
    load = LF_CLK_VALUE / 1000U * interval;

    while ((load & ~0xFFFFU) != 0U && (pre & ~0x3U) == 0U) {
      ++pre;
      load >>= 4U;
    };

    if ((pre & ~0x3U) == 0U) {
      MMR_WDT->T3LD  = (uint16_t)load;
      MMR_WDT->T3CON = (uint16_t)((MMR_WDT->T3CON & ~T3CON_PRE_Msk) | (pre << T3CON_PRE_Pos));

      if (cb_event != NULL) {
        MMR_WDT->T3CON |= T3CON_IRQ_EN;
      }

      WDT_Info.cb_event = cb_event;
      ret = WDT_DRIVER_OK;
    }
  }

  return (ret);
}

static int32_t WDT_Enable(void)
{
  int32_t ret = WDT_DRIVER_ERROR;

  if ((MMR_WDT->T3STA & (T3STA_LOCK_Msk | T3STA_CON_Msk)) == 0U) {
    MMR_WDT->T3CON |= (uint16_t)T3CON_ENABLE;
    ret = WDT_DRIVER_OK;
  }

  return (ret);
}

static int32_t WDT_Disable(void)
{
  int32_t ret = WDT_DRIVER_ERROR;

  if ((MMR_WDT->T3STA & (T3STA_LOCK_Msk | T3STA_CON_Msk)) == 0U) {
    MMR_WDT->T3CON &= (uint16_t)~T3CON_ENABLE;
    ret = WDT_DRIVER_OK;
  }

  return (ret);
}

static uint32_t WDT_GetInterval(void)
{
  return (MMR_WDT->T3LD * 1000U / LF_CLK_VALUE);
}

static uint32_t WDT_GetCount(void)
{
  return (MMR_WDT->T3LD - MMR_WDT->T3VAL);
}

static int32_t WDT_Reload(void)
{
  int32_t ret = WDT_DRIVER_ERROR;

  if ((MMR_WDT->T3STA & T3STA_CLRI_Msk) == T3STA_CLRI_CLR) {
    MMR_WDT->T3CLRI = T3CLRI_CLRWDG_VALUE;
    ret = WDT_DRIVER_OK;
  }

  return (ret);
}

/*******************************************************************************
 *  function implementations (scope: module-export)
 ******************************************************************************/

extern void WDT_IRQHandler(void);

void WDT_IRQHandler(void)
{
  if (WDT_Info.cb_event != NULL) {
    WDT_Info.cb_event();
  }
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

Driver_WDT_t Driver_WDT = {
  WDT_Setup,
  WDT_Enable,
  WDT_Disable,
  WDT_GetInterval,
  WDT_GetCount,
  WDT_Reload,
};
