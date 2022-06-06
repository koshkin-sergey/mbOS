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
 * Project: mbOS real-time kernel
 */

/**
 * @file
 *
 * Kernel system routines.
 *
 */

#include <string.h>
#include "kernel_lib.h"
#include "Kernel/tick.h"

KernelInfo_t osInfo;

static osStatus_t svcKernelInitialize(void)
{
  if (osInfo.kernel.state == osKernelReady) {
    return (osOK);
  }

  if (osInfo.kernel.state != osKernelInactive) {
    return (osError);
  }

  /* Initialize osInfo */
  memset(&osInfo, 0, sizeof(osInfo));

  for (uint32_t i = 0U; i < NUM_PRIORITY; i++) {
    QueueReset(&osInfo.ready_list[i]);
  }

  QueueReset(&osInfo.timer_queue);
  QueueReset(&osInfo.delay_queue);
  QueueReset(&osInfo.post_queue);

  osInfo.kernel.state = osKernelReady;

  return (osOK);
}

static osStatus_t svcKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size)
{
  if (version != NULL) {
    version->api    = osVersionAPI;
    version->kernel = osVersionKernel;
  }

  if ((id_buf != NULL) && (id_size != 0U)) {
    if (id_size > sizeof(osKernelId)) {
      id_size = sizeof(osKernelId);
    }
    memcpy(id_buf, osKernelId, id_size);
  }

  return (osOK);
}

static osKernelState_t svcKernelGetState(void)
{
  return (osInfo.kernel.state);
}

static osStatus_t svcKernelStart(void)
{
  if (osInfo.kernel.state != osKernelReady) {
    return (osError);
  }

  /* Thread startup (Idle and Timer Thread) */
  if (!krnThreadStartup()) {
    return (osError);
  }

  /* Setup SVC and PendSV System Service Calls */
  SystemIsrInit();

  /* Setup RTOS Tick */
  if (osTickSetup(osConfig.tick_freq, OS_TICK_HANDLER) != 0) {
    return (osError);
  }
  osInfo.tick_irqn = osTickGetIRQn();

  /* Enable RTOS Tick */
  osTickEnable();

  setPrivilegedMode(osConfig.flags & osConfigPrivilegedMode);

  osInfo.kernel.state = osKernelRunning;

  /* Switch to Ready Thread with highest Priority */
  SchedDispatch(NULL);

  return (osOK);
}

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#endif

static int32_t svcKernelLock(void)
{
  int32_t lock;

  switch (osInfo.kernel.state) {
    case osKernelRunning:
      osInfo.kernel.state = osKernelLocked;
      lock = 0;
      break;

    case osKernelLocked:
      lock = 1;
      break;

    default:
      lock = (int32_t)osError;
      break;
  }

  return (lock);
}

static int32_t svcKernelUnlock(void)
{
  int32_t lock;

  switch (osInfo.kernel.state) {
    case osKernelRunning:
      lock = 0;
      break;

    case osKernelLocked:
      osInfo.kernel.state = osKernelRunning;
      lock = 1;
      break;

    default:
      lock = (int32_t)osError;
      break;
  }

  return (lock);
}

static int32_t svcKernelRestoreLock(int32_t lock)
{
  int32_t lock_new;

  switch (osInfo.kernel.state) {
    case osKernelRunning:
    case osKernelLocked:
      switch (lock) {
        case 0:
          osInfo.kernel.state = osKernelRunning;
          lock_new = 0;
          break;

        case 1:
          osInfo.kernel.state = osKernelLocked;
          lock_new = 1;
          break;

        default:
          lock_new = (int32_t)osError;
          break;
      }
      break;

    default:
      lock_new = (int32_t)osError;
      break;
  }

  return (lock_new);
}

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

static uint32_t svcKernelGetTickCount(void)
{
  return (osInfo.kernel.tick);
}

static uint32_t svcKernelGetTickFreq(void)
{
  return (osConfig.tick_freq);
}

static uint32_t svcKernelGetSysTimerCount(void)
{
  uint32_t tick;
  uint32_t count;

  tick  = osInfo.kernel.tick;
  count = osTickGetCount();
  if (osTickGetOverflow() != 0U) {
    count = osTickGetCount();
    tick++;
  }
  count += tick * osTickGetInterval();

  return (count);
}

static uint32_t svcKernelGetSysTimerFreq(void)
{
  uint32_t freq = osTickGetClock();

  return (freq);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          osStatus_t osKernelInitialize(void)
 * @brief       Initialize the RTOS Kernel.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osKernelInitialize(void)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_0(svcKernelInitialize);
  }

  return (status);
}

/**
 * @fn          osStatus_t osKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size)
 * @brief       Get RTOS Kernel Information.
 * @param[out]  version   pointer to buffer for retrieving version information.
 * @param[out]  id_buf    pointer to buffer for retrieving kernel identification string.
 * @param[in]   id_size   size of buffer for kernel identification string.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked() || IsPrivileged()) {
    status = svcKernelGetInfo(version, id_buf, id_size);
  }
  else {
    status = (osStatus_t)SVC_3(version, id_buf, id_size, svcKernelGetInfo);
  }

  return (status);
}

/**
 * @fn          osKernelState_t osKernelGetState(void)
 * @brief       Get the current RTOS Kernel state.
 * @return      current RTOS Kernel state.
 */
osKernelState_t osKernelGetState(void)
{
  osKernelState_t state;

  if (IsIrqMode() || IsIrqMasked() || IsPrivileged()) {
    state = svcKernelGetState();
  }
  else {
    state = (osKernelState_t)SVC_0(svcKernelGetState);
  }

  return (state);
}

/**
 * @fn          osStatus_t osKernelStart(void)
 * @brief       Start the RTOS Kernel scheduler.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osKernelStart(void)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_0(svcKernelStart);
  }

  return (status);
}

/**
 * @fn          int32_t osKernelLock(void)
 * @brief       Lock the RTOS Kernel scheduler.
 * @return      previous lock state (1 - locked, 0 - not locked, error code if negative).
 */
int32_t osKernelLock(void)
{
  int32_t lock;

  if (IsIrqMode() || IsIrqMasked()) {
    lock = (int32_t)osErrorISR;
  }
  else {
    lock = (int32_t)SVC_0(svcKernelLock);
  }

  return (lock);
}

/**
 * @fn          int32_t osKernelUnlock(void)
 * @brief       Unlock the RTOS Kernel scheduler.
 * @return      previous lock state (1 - locked, 0 - not locked, error code if negative).
 */
int32_t osKernelUnlock(void)
{
  int32_t lock;

  if (IsIrqMode() || IsIrqMasked()) {
    lock = (int32_t)osErrorISR;
  }
  else {
    lock = (int32_t)SVC_0(svcKernelUnlock);
  }

  return (lock);
}

/**
 * @fn          int32_t osKernelRestoreLock(int32_t lock)
 * @brief       Restore the RTOS Kernel scheduler lock state.
 * @param[in]   lock  lock state obtained by \ref osKernelLock or \ref osKernelUnlock.
 * @return      new lock state (1 - locked, 0 - not locked, error code if negative).
 */
int32_t osKernelRestoreLock(int32_t lock)
{
  int32_t lock_new;

  if (IsIrqMode() || IsIrqMasked()) {
    lock_new = (int32_t)osErrorISR;
  }
  else {
    lock_new = (int32_t)SVC_1(lock, svcKernelRestoreLock);
  }

  return (lock_new);
}

/**
 * @fn          uint32_t osKernelGetTickCount(void)
 * @brief       Get the RTOS kernel tick count.
 * @return      RTOS kernel current tick count.
 */
uint32_t osKernelGetTickCount(void)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = svcKernelGetTickCount();
  }
  else {
    count = SVC_0(svcKernelGetTickCount);
  }

  return (count);
}

/**
 * @fn          uint32_t osKernelGetTickFreq(void)
 * @brief       Get the RTOS kernel tick frequency.
 * @return      frequency of the kernel tick in hertz, i.e. kernel ticks per second.
 */
uint32_t osKernelGetTickFreq(void)
{
  uint32_t freq;

  if (IsIrqMode() || IsIrqMasked()) {
    freq = svcKernelGetTickFreq();
  }
  else {
    freq = SVC_0(svcKernelGetTickFreq);
  }

  return (freq);
}

/**
 * @fn          uint32_t osKernelGetSysTimerCount(void)
 * @brief       Get the RTOS kernel system timer count.
 * @return      RTOS kernel current system timer count as 32-bit value.
 */
uint32_t osKernelGetSysTimerCount(void)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = svcKernelGetSysTimerCount();
  } else {
    count = SVC_0(svcKernelGetSysTimerCount);
  }

  return (count);
}

/**
 * @fn          uint32_t osKernelGetSysTimerFreq(void)
 * @brief       Get the RTOS kernel system timer frequency.
 * @return      frequency of the system timer in hertz, i.e. timer ticks per second.
 */
uint32_t osKernelGetSysTimerFreq(void)
{
  uint32_t freq;

  if (IsIrqMode() || IsIrqMasked()) {
    freq = svcKernelGetSysTimerFreq();
  } else {
    freq =  SVC_0(svcKernelGetSysTimerFreq);
  }

  return (freq);
}
