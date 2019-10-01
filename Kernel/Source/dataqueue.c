/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <string.h>
#include "kernel_lib.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

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

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static bool DataPut(osDataQueue_t *dq, const void *data_ptr)
{
  if (dq->data_count == dq->max_data_count) {
    return (false);
  }

  memcpy(&dq->dq_mem[dq->head], data_ptr, dq->data_size);
  dq->head += dq->data_size;
  if (dq->head >= dq->data_limit) {
    dq->head = 0U;
  }

  dq->data_count++;

  return (true);
}

static bool DataGet(osDataQueue_t *dq, void *data_ptr)
{
  if (dq->data_count == 0U) {
    return (false);
  }

  memcpy(data_ptr, &dq->dq_mem[dq->tail], dq->data_size);
  dq->data_count--;
  dq->tail += dq->data_size;
  if (dq->tail >= dq->data_limit) {
    dq->tail = 0U;
  }

  return (true);
}

static osDataQueueId_t DataQueueNew(uint32_t data_count, uint32_t data_size, const osDataQueueAttr_t *attr)
{
  osDataQueue_t *dq;
  void          *dq_mem;
  uint32_t       data_limit;

  /* Check parameters */
  if ((data_count == 0U) || (data_size  == 0U) || (attr == NULL)) {
    return (NULL);
  }

  dq         = attr->cb_mem;
  dq_mem     = attr->dq_mem;
  data_limit = data_count * data_size;

  /* Check parameters */
  if (((__CLZ(data_count) + __CLZ(data_size)) < 32U) ||
      (dq == NULL) || (((uint32_t)dq & 3U) != 0U) || (attr->cb_size < sizeof(osDataQueue_t)) ||
      (dq_mem == NULL) || (attr->dq_size < data_limit)) {
    return (NULL);
  }

  /* Initialize control block */
  dq->id             = ID_DATA_QUEUE;
  dq->flags          = 0U;
  dq->name           = attr->name;
  dq->max_data_count = data_count;
  dq->data_size      = data_size;
  dq->data_count     = 0U;
  dq->data_limit     = data_limit;
  dq->head           = 0U;
  dq->tail           = 0U;
  dq->dq_mem         = dq_mem;

  QueueReset(&dq->wait_put_queue);
  QueueReset(&dq->wait_get_queue);

  return (dq);
}

static const char *DataQueueGetName(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (NULL);
  }

  return (dq->name);
}

static osStatus_t DataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout)
{
  osDataQueue_t    *dq = dq_id;
  osThread_t       *thread;
  osStatus_t        status;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE) || (data_ptr == NULL)) {
    return (osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  /* Check if Thread is waiting to receive a data */
  if (!isQueueEmpty(&dq->wait_get_queue)) {
    /* Wakeup waiting Thread with highest Priority */
    thread = GetThreadByQueue(dq->wait_get_queue.next);
    libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_YES);
    memcpy((void *)thread->winfo.dataque.data_ptr, data_ptr, dq->data_size);
    status = osOK;
  }
  else {
    /* Try to put a data into Queue */
    if (DataPut(dq, data_ptr) != false) {
      status = osOK;
    }
    else {
      /* No memory available */
      if (timeout != 0U) {
        /* Suspend current Thread */
        thread = ThreadGetRunning();
        if (libThreadWaitEnter(thread, &dq->wait_put_queue, timeout)) {
          thread->winfo.dataque.data_ptr = (uint32_t)data_ptr;
          status = (osStatus_t)osThreadWait;
        }
        else {
          status = osErrorTimeout;
        }
      }
      else {
        status = osErrorResource;
      }
    }
  }

  END_CRITICAL_SECTION

  return (status);
}

static osStatus_t DataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout)
{
  osDataQueue_t    *dq = dq_id;
  osThread_t       *thread;
  osStatus_t        status;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE) || (data_ptr == NULL)) {
    return (osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  /* Get Data from Queue */
  if (DataGet(dq, data_ptr) != false) {
    /* Check if Thread is waiting to send a data */
    if (!isQueueEmpty(&dq->wait_put_queue)) {
      /* Get waiting Thread with highest Priority */
      thread = GetThreadByQueue(dq->wait_put_queue.next);
      /* Try to put a data into Queue */
      if (DataPut(dq, (const void *)thread->winfo.dataque.data_ptr) != false) {
        /* Wakeup waiting Thread with highest Priority */
        libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_YES);
      }
    }
    status = osOK;
  }
  else {
    /* No Message available */
    if (timeout != 0U) {
      /* Suspend current Thread */
      thread = ThreadGetRunning();
      if (libThreadWaitEnter(thread, &dq->wait_get_queue, timeout)) {
        thread->winfo.dataque.data_ptr = (uint32_t)data_ptr;
        status = (osStatus_t)osThreadWait;
      }
      else {
        status = osErrorTimeout;
      }
    }
    else {
      status = osErrorResource;
    }
  }

  END_CRITICAL_SECTION

  return (status);
}

static uint32_t DataQueueGetCapacity(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->max_data_count);
}

static uint32_t DataQueueGetMsgSize(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->data_size);
}

static uint32_t DataQueueGetCount(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->data_count);
}

static uint32_t DataQueueGetSpace(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->max_data_count - dq->data_count);
}

static osStatus_t DataQueueReset(osDataQueueId_t dq_id)
{
  osDataQueue_t    *dq = dq_id;
  osThread_t       *thread;
  winfo_dataque_t  *winfo;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  /* Remove data from Queue */
  dq->data_count = 0U;
  dq->head       = 0U;
  dq->tail       = 0U;

  /* Check if Threads are waiting to send a data */
  if (!isQueueEmpty(&dq->wait_put_queue)) {
    do {
      /* Get waiting Thread with highest Priority */
      thread = GetThreadByQueue(dq->wait_put_queue.next);
      winfo = &thread->winfo.dataque;
      /* Try to put a data into Queue */
      if (DataPut(dq, (const void *)winfo->data_ptr) == false) {
        break;
      }
      /* Wakeup waiting Thread with highest Priority */
      libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    } while(!isQueueEmpty(&dq->wait_put_queue));
    libThreadDispatch(NULL);
  }

  END_CRITICAL_SECTION

  return (osOK);
}

static osStatus_t DataQueueDelete(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  libThreadWaitDelete(&dq->wait_put_queue);
  libThreadWaitDelete(&dq->wait_get_queue);

  /* Mark object as invalid */
  dq->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osDataQueueId_t osDataQueueNew(uint32_t data_count, uint32_t data_size, const osDataQueueAttr_t *attr)
 * @brief       Create and Initialize a Data Queue object.
 * @param[in]   data_count  maximum number of data in queue.
 * @param[in]   data_size   maximum data size in bytes.
 * @param[in]   attr        data queue attributes.
 * @return      data queue ID for reference by other functions or NULL in case of error.
 */
osDataQueueId_t osDataQueueNew(uint32_t data_count, uint32_t data_size, const osDataQueueAttr_t *attr)
{
  osDataQueueId_t dq_id;

  if (IsIrqMode() || IsIrqMasked()) {
    dq_id = NULL;
  }
  else {
    dq_id = (osDataQueueId_t)SVC_3(data_count, data_size, attr, DataQueueNew);
  }

  return (dq_id);
}

/**
 * @fn          const char *osDataQueueGetName(osDataQueueId_t dq_id)
 * @brief       Get name of a Data Queue object.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osDataQueueGetName(osDataQueueId_t dq_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(dq_id, DataQueueGetName);
  }

  return (name);
}

/**
 * @fn          osStatus_t osDataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout)
 * @brief       Put a Data into a Queue or timeout if Queue is full.
 * @param[in]   dq_id     data queue ID obtained by \ref osDataQueueNew.
 * @param[in]   data_ptr  pointer to buffer with data to put into a queue.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    if (timeout != 0U) {
      status = osErrorParameter;
    }
    else {
      status = DataQueuePut(dq_id, data_ptr, timeout);
    }
  }
  else {
    status = (osStatus_t)SVC_3(dq_id, data_ptr, timeout, DataQueuePut);
    if (status == osThreadWait) {
      status = (osStatus_t)ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (status);
}

/**
 * @fn          osStatus_t osDataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout)
 * @brief       Get a Data from a Queue or timeout if Queue is empty.
 * @param[in]   dq_id     data queue ID obtained by \ref osDataQueueNew.
 * @param[out]  data_ptr  pointer to buffer for data to get from a queue.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    if (timeout != 0U) {
      status = osErrorParameter;
    }
    else {
      status = DataQueueGet(dq_id, data_ptr, timeout);
    }
  }
  else {
    status = (osStatus_t)SVC_3(dq_id, data_ptr, timeout, DataQueueGet);
    if (status == osThreadWait) {
      status = (osStatus_t)ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (status);
}

/**
 * @fn          uint32_t osDataQueueGetCapacity(osDataQueueId_t dq_id)
 * @brief       Get maximum number of data in a Data Queue.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      maximum number of data or 0 in case of an error.
 */
uint32_t osDataQueueGetCapacity(osDataQueueId_t dq_id)
{
  uint32_t capacity;

  if (IsIrqMode() || IsIrqMasked()) {
    capacity = DataQueueGetCapacity(dq_id);
  }
  else {
    capacity = SVC_1(dq_id, DataQueueGetCapacity);
  }

  return (capacity);
}

/**
 * @fn          uint32_t osDataQueueGetDataSize(osDataQueueId_t dq_id)
 * @brief       Get maximum data size in bytes.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      maximum data size in bytes or 0 in case of an error.
 */
uint32_t osDataQueueGetDataSize(osDataQueueId_t dq_id)
{
  uint32_t data_size;

  if (IsIrqMode() || IsIrqMasked()) {
    data_size = DataQueueGetMsgSize(dq_id);
  }
  else {
    data_size = SVC_1(dq_id, DataQueueGetMsgSize);
  }

  return (data_size);
}

/**
 * @fn          uint32_t osDataQueueGetCount(osDataQueueId_t dq_id)
 * @brief       Get number of queued data in a Data Queue.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      number of queued data or 0 in case of an error.
 */
uint32_t osDataQueueGetCount(osDataQueueId_t dq_id)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = DataQueueGetCount(dq_id);
  }
  else {
    count = SVC_1(dq_id, DataQueueGetCount);
  }

  return (count);
}

/**
 * @fn          uint32_t osDataQueueGetSpace(osDataQueueId_t dq_id)
 * @brief       Get number of available slots for data in a Data Queue.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      number of available slots for data or 0 in case of an error.
 */
uint32_t osDataQueueGetSpace(osDataQueueId_t dq_id)
{
  uint32_t space;

  if (IsIrqMode() || IsIrqMasked()) {
    space = DataQueueGetSpace(dq_id);
  }
  else {
    space = SVC_1(dq_id, DataQueueGetSpace);
  }

  return (space);
}

/**
 * @fn          osStatus_t osDataQueueReset(osDataQueueId_t dq_id)
 * @brief       Reset a Data Queue to initial empty state.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueueReset(osDataQueueId_t dq_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(dq_id, DataQueueReset);
  }

  return (status);
}

/**
 * @fn          osStatus_t osDataQueueDelete(osDataQueueId_t dq_id)
 * @brief       Delete a Data Queue object.
 * @param[in]   dq_id   data queue ID obtained by \ref osDataQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osDataQueueDelete(osDataQueueId_t dq_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(dq_id, DataQueueDelete);
  }

  return (status);
}

/* ----------------------------- End of file ---------------------------------*/
