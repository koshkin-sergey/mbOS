/*
 * Copyright (C) 2017-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define SemaphoreTokenLimit   65535U ///< maximum number of tokens per semaphore

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

/**
 * @brief       Decrement Semaphore tokens.
 * @param[in]   sem  semaphore object.
 * @return      osOK - success, osErrorResource - failure.
 */
static osStatus_t SemaphoreTokenDecrement(osSemaphore_t *sem)
{
  osStatus_t status;

  BEGIN_CRITICAL_SECTION

  if (sem->count != 0U) {
    sem->count--;
    status = osOK;
  }
  else {
    status = osErrorResource;
  }

  END_CRITICAL_SECTION

  return (status);
}

/**
 * @brief       Increment Semaphore tokens.
 * @param[in]   sem  semaphore object.
 * @return      osOK - success, osErrorResource - failure.
 */
static osStatus_t SemaphoreTokenIncrement(osSemaphore_t *sem)
{
  osStatus_t status;

  BEGIN_CRITICAL_SECTION

  /* Try to release token */
  if (sem->count < sem->max_count) {
    sem->count++;
    status = osOK;
  }
  else {
    status = osErrorResource;
  }

  END_CRITICAL_SECTION

  return (status);
}

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static osSemaphoreId_t svcSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr)
{
  osSemaphore_t *sem;

  /* Check parameters */
  if ((attr == NULL)                          ||
      (attr->cb_mem == NULL)                  ||
      (((uint32_t)attr->cb_mem & 3U) != 0U)   ||
      (attr->cb_size < sizeof(osSemaphore_t)) ||
      (max_count == 0U)                       ||
      (max_count > SemaphoreTokenLimit)       ||
      (initial_count > max_count))
  {
    return (NULL);
  }

  sem = attr->cb_mem;

  /* Initialize control block */
  sem->id         = ID_SEMAPHORE;
  sem->flags      = 0U;
  sem->name       = attr->name;
  sem->count      = (uint16_t)initial_count;
  sem->max_count  = (uint16_t)max_count;

  QueueReset(&sem->wait_queue);
  QueueReset(&sem->post_queue);

  return (sem);
}

static const char *svcSemaphoreGetName(osSemaphoreId_t semaphore_id)
{
  osSemaphore_t *sem = semaphore_id;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE)) {
    return NULL;
  }

  return (sem->name);
}

static osStatus_t svcSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout)
{
  osSemaphore_t *sem = semaphore_id;
  osStatus_t status;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE)) {
    return (osErrorParameter);
  }

  /* Try to acquire token */
  status = SemaphoreTokenDecrement(sem);
  if ((status == osErrorResource) && (timeout != 0U)) {
    /* No token available */
    status = krnThreadWaitEnter(ThreadWaitingSemaphore, &sem->wait_queue, timeout);
  }

  return (status);
}

static osStatus_t svcSemaphoreRelease(osSemaphoreId_t semaphore_id)
{
  osSemaphore_t *sem = semaphore_id;
  osStatus_t status;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE)) {
    return (osErrorParameter);
  }

  /* Check if Thread is waiting for a token */
  if (!isQueueEmpty(&sem->wait_queue)) {
    /* Wakeup waiting Thread with highest Priority */
    krnThreadWaitExit(GetThreadByQueue(sem->wait_queue.next), (uint32_t)osOK, DISPATCH_YES);
    status = osOK;
  }
  else {
    /* Try to release token */
    status = SemaphoreTokenIncrement(sem);
  }

  return (status);
}

static uint32_t svcSemaphoreGetCount(osSemaphoreId_t semaphore_id)
{
  osSemaphore_t *sem = semaphore_id;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE)) {
    return (0U);
  }

  return (sem->count);
}

static osStatus_t svcSemaphoreDelete(osSemaphoreId_t semaphore_id)
{
  osSemaphore_t *sem = semaphore_id;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  krnThreadWaitDelete(&sem->wait_queue);
  /* Mark object as invalid */
  sem->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  ISR Calls
 ******************************************************************************/

__STATIC_INLINE
osStatus_t isrSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout)
{
  osSemaphore_t *sem = semaphore_id;
  osStatus_t status;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE) || (timeout != 0U)) {
    return (osErrorParameter);
  }

  /* Try to acquire token */
  status = SemaphoreTokenDecrement(sem);

  return (status);
}

__STATIC_INLINE
osStatus_t isrSemaphoreRelease(osSemaphoreId_t semaphore_id)
{
  osSemaphore_t *sem = semaphore_id;
  osStatus_t status;

  /* Check parameters */
  if ((sem == NULL) || (sem->id != ID_SEMAPHORE)) {
    return (osErrorParameter);
  }

  /* Try to release token */
  status = SemaphoreTokenIncrement(sem);
  if (status == osOK) {
    /* Register post ISR processing */
    krnPostProcess((osObject_t *)sem);
  }

  return (status);
}

/*******************************************************************************
 *  Post ISR processing
 ******************************************************************************/

/**
 * @fn          void krnSemaphorePostProcess(osSemaphore_t*)
 * @brief       Semaphore post ISR processing.
 * @param[in]   sem  semaphore object.
 */
void krnSemaphorePostProcess(osSemaphore_t *sem)
{
  osStatus_t status;

  /* Check if Thread is waiting for a token */
  if (!isQueueEmpty(&sem->wait_queue)) {
    /* Try to acquire token */
    status = SemaphoreTokenDecrement(sem);
    if (status == osOK) {
      /* Wakeup waiting Thread with highest Priority */
      krnThreadWaitExit(GetThreadByQueue(sem->wait_queue.next), (uint32_t)osOK, DISPATCH_NO);
    }
  }
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osSemaphoreId_t osSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr)
 * @brief       Create and Initialize a Semaphore object.
 * @param[in]   max_count       maximum number of available tokens.
 * @param[in]   initial_count   initial number of available tokens.
 * @param[in]   attr            semaphore attributes.
 * @return      semaphore ID for reference by other functions or NULL in case of error.
 */
osSemaphoreId_t osSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr)
{
  osSemaphoreId_t semaphore_id;

  if (IsIrqMode() || IsIrqMasked()) {
    semaphore_id = NULL;
  }
  else {
    semaphore_id = (osSemaphoreId_t)SVC_3(max_count, initial_count, attr, svcSemaphoreNew);
  }

  return (semaphore_id);
}

/**
 * @fn          const char *osSemaphoreGetName(osSemaphoreId_t semaphore_id)
 * @brief       Get name of a Semaphore object.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osSemaphoreGetName(osSemaphoreId_t semaphore_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(semaphore_id, svcSemaphoreGetName);
  }

  return (name);
}

/**
 * @fn          osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout)
 * @brief       Acquire a Semaphore token or timeout if no tokens are available.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @param[in]   timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = isrSemaphoreAcquire(semaphore_id, timeout);
  }
  else {
    status = (osStatus_t)SVC_2(semaphore_id, timeout, svcSemaphoreAcquire);
    if (status == osThreadWait) {
      status = (osStatus_t)ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (status);
}

/**
 * @fn          osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id)
 * @brief       Release a Semaphore token that was acquired by osSemaphoreAcquire.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = isrSemaphoreRelease(semaphore_id);
  }
  else {
    status = (osStatus_t)SVC_1(semaphore_id, svcSemaphoreRelease);
  }

  return (status);
}

/**
 * @fn          uint32_t osSemaphoreGetCount(osSemaphoreId_t semaphore_id)
 * @brief       Get current Semaphore token count.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      number of tokens available or 0 in case of an error.
 */
uint32_t osSemaphoreGetCount(osSemaphoreId_t semaphore_id)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = svcSemaphoreGetCount(semaphore_id);
  }
  else {
    count = SVC_1(semaphore_id, svcSemaphoreGetCount);
  }

  return (count);
}

/**
 * @fn          osStatus_t osSemaphoreDelete(osSemaphoreId_t semaphore_id)
 * @brief       Delete a Semaphore object.
 * @param[in]   semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreDelete(osSemaphoreId_t semaphore_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(semaphore_id, svcSemaphoreDelete);
  }

  return (status);
}

/*------------------------------ End of file ---------------------------------*/
