/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *
 * Description: This file provides Debug interface.
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include "Debug/debug.h"
#include "Kernel/kernel.h"
#include "CMSIS/Driver/Driver_USART.h"

#if defined(DEBUG)

#ifndef DRIVER_USART_DEBUG_NUM
#define DRIVER_USART_DEBUG_NUM        5
#endif

#ifndef DRIVER_USART_DEBUG_BAUDRATE
#define DRIVER_USART_DEBUG_BAUDRATE   9600
#endif

/* USART Driver */
#define _USART_Driver(n)              Driver_USART##n
#define  USART_Driver(n)              _USART_Driver(n)

extern ARM_DRIVER_USART USART_Driver(DRIVER_USART_DEBUG_NUM);

#define EVENT_SEND_COMPLETE           (1U << 0)
#define DEBUG_MSG_BUF_SIZE            256U

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct UsartInfo_s {
  ARM_DRIVER_USART  *driver;
  uint32_t         baudrate;
  uint32_t          c_cflag;
} const UsartInfo_t;

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osEventFlagsId_t         ef;
static osEventFlags_t           ef_cb;
static const osEventFlagsAttr_t ef_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &ef_cb,
    .cb_size   = sizeof(ef_cb)
};

static osSemaphoreId_t         sem;
static osSemaphore_t           sem_cb;
static const osSemaphoreAttr_t sem_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &sem_cb,
    .cb_size   = sizeof(sem_cb),
};

static UsartInfo_t usart = {
    .driver   = &USART_Driver(DRIVER_USART_DEBUG_NUM),
    .baudrate = DRIVER_USART_DEBUG_BAUDRATE,
    .c_cflag  = ARM_USART_MODE_ASYNCHRONOUS |
                ARM_USART_DATA_BITS_8       |
                ARM_USART_PARITY_NONE       |
                ARM_USART_STOP_BITS_1       |
                ARM_USART_FLOW_CONTROL_NONE,
};

static char debug_buf[DEBUG_MSG_BUF_SIZE];

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void USART_Callback(uint32_t event)
{
  if (event & ARM_USART_EVENT_SEND_COMPLETE) {
    osEventFlagsSet(ef, EVENT_SEND_COMPLETE);
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

static void lock(void)
{
  osSemaphoreAcquire(sem, osWaitForever);
}

static void unlock(void)
{
  osSemaphoreRelease(sem);
}

static uint32_t Initialize(void)
{
  ARM_DRIVER_USART *driver;

  ef = osEventFlagsNew(&ef_attr);
  if (ef == NULL) {
    return (DEBUG_ERROR);
  }

  sem = osSemaphoreNew(1U, 1U, &sem_attr);
  if (sem == NULL) {
    return (DEBUG_ERROR);
  }

  driver = usart.driver;

  driver->Initialize(USART_Callback);
  driver->PowerControl(ARM_POWER_FULL);
  driver->Control(usart.c_cflag, usart.baudrate);
  driver->Control(ARM_USART_CONTROL_TX, 1U);

  return (DEBUG_OK);
}

static uint32_t Uninitialize(void)
{
  ARM_DRIVER_USART *driver = usart.driver;

  driver->PowerControl(ARM_POWER_OFF);
  driver->Uninitialize();

  osSemaphoreDelete(sem);
  osEventFlagsDelete(ef);

  return (DEBUG_OK);
}

static int32_t dprintf(const char *template, ...)
{
  va_list ap;
  int32_t cnt;

  lock();

  va_start(ap, template);
  cnt = vsnprintf(debug_buf, DEBUG_MSG_BUF_SIZE, template, ap);
  va_end(ap);

  if (cnt >= (int32_t)DEBUG_MSG_BUF_SIZE) {
    if (debug_buf[DEBUG_MSG_BUF_SIZE-2] != '\r') {
      debug_buf[DEBUG_MSG_BUF_SIZE-2] = '*';
    }
    debug_buf[DEBUG_MSG_BUF_SIZE-1] = '\n';
    cnt = DEBUG_MSG_BUF_SIZE;
  }

  if (cnt > 0) {
    if (usart.driver->Send(debug_buf, cnt) == ARM_DRIVER_OK) {
      osEventFlagsWait(ef, EVENT_SEND_COMPLETE, osFlagsWaitAny, osWaitForever);
    }
  }

  unlock();

  return (cnt);
}

Debug_t Debug = {
    Initialize,
    Uninitialize,
    dprintf,
};

#endif  /* defined(DEBUG) */

/* ----------------------------- End of file ---------------------------------*/
