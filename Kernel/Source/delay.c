/*
 * Copyright (C) 2019-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: mbOS real-time kernel
 */

/**
 * @file
 *
 * Kernel system routines.
 *
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "kernel_lib.h"

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static osStatus_t Delay(uint32_t ticks)
{
  if (ticks != 0U) {
    krnThreadWaitEnter(ThreadGetRunning(), NULL, ticks);
  }

  return (osOK);
}

static osStatus_t DelayUntil(uint32_t ticks)
{
  ticks -= osInfo.kernel.tick;

  if ((ticks == 0U) || (ticks > 0x7FFFFFFFU)) {
    return (osErrorParameter);
  }

  if (ticks != 0U) {
    krnThreadWaitEnter(ThreadGetRunning(), NULL, ticks);
  }

  return (osOK);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          osStatus_t osDelay(uint32_t ticks)
 * @brief       Wait for Timeout (Time Delay).
 * @param[in]   ticks   \ref CMSIS_RTOS_TimeOutValue "time ticks" value
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDelay(uint32_t ticks)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(ticks, Delay);
  }

  return (status);
}

/**
 * @fn          osStatus_t osDelayUntil(uint32_t ticks)
 * @brief       Wait until specified time.
 * @param[in]   ticks   absolute time in ticks
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDelayUntil(uint32_t ticks)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(ticks, DelayUntil);
  }

  return (status);
}

/*------------------------------ End of file ---------------------------------*/
