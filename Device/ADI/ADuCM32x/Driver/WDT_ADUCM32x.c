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

#include <asm/aducm32x.h>

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static struct info {
  WDT_SignalEvent_t cb_event;
} WDT_Info;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static int32_t WDT_SetSignalEvent(WDT_SignalEvent_t cb_event)
{
  WDT_Info.cb_event = cb_event;

  return (WDT_DRIVER_OK);
}

static int32_t WDT_Control(uint32_t control, uint32_t arg)
{
  (void) control;
  (void) arg;

  return (WDT_DRIVER_OK);
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

}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

Driver_WDT_t Driver_WDT = {
  WDT_SetSignalEvent,
  WDT_Control,
  WDT_Reload,
};
