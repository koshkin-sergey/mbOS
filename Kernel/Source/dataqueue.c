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

#include <string.h>
#include "kernel_lib.h"

/*******************************************************************************
 *  Helper functions
 ******************************************************************************/

static bool DataPut(osDataQueue_t *dq, const void *data_ptr)
{
  bool status = false;

  BEGIN_CRITICAL_SECTION

  if (dq->data_count != dq->max_data_count) {
    memcpy(&dq->dq_mem[dq->head], data_ptr, dq->data_size);
    dq->head += dq->data_size;
    if (dq->head >= dq->data_limit) {
      dq->head = 0U;
    }

    dq->data_count++;
    status = true;
  }

  END_CRITICAL_SECTION

  return (status);
}

static bool DataGet(osDataQueue_t *dq, void *data_ptr)
{
  bool status = false;

  BEGIN_CRITICAL_SECTION

  if (dq->data_count != 0U) {
    memcpy(data_ptr, &dq->dq_mem[dq->tail], dq->data_size);
    dq->data_count--;
    dq->tail += dq->data_size;
    if (dq->tail >= dq->data_limit) {
      dq->tail = 0U;
    }
  }

  END_CRITICAL_SECTION

  return (status);
}

static void DataReset(osDataQueue_t *dq)
{
  BEGIN_CRITICAL_SECTION

  dq->data_count = 0U;
  dq->head       = 0U;
  dq->tail       = 0U;

  END_CRITICAL_SECTION
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osDataQueueId_t svcDataQueueNew(uint32_t data_count, uint32_t data_size, const osDataQueueAttr_t *attr)
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

static const char *svcDataQueueGetName(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (NULL);
  }

  return (dq->name);
}

static osStatus_t svcDataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout)
{
  osDataQueue_t    *dq = dq_id;
  osThread_t       *thread;
  osStatus_t        status;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE) || (data_ptr == NULL)) {
    return (osErrorParameter);
  }

  /* Check if Thread is waiting to receive a data */
  if (!isQueueEmpty(&dq->wait_get_queue)) {
    /* Wakeup waiting Thread with highest Priority */
    thread = GetThreadByQueue(dq->wait_get_queue.next);
    krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_YES);
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
        status = krnThreadWaitEnter(thread, &dq->wait_put_queue, timeout);
        if (status != osErrorTimeout) {
          thread->winfo.dataque.data_ptr = (uint32_t)data_ptr;
        }
      }
      else {
        status = osErrorResource;
      }
    }
  }

  return (status);
}

static osStatus_t svcDataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout)
{
  osDataQueue_t    *dq = dq_id;
  osThread_t       *thread;
  osStatus_t        status;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE) || (data_ptr == NULL)) {
    return (osErrorParameter);
  }

  /* Get Data from Queue */
  if (DataGet(dq, data_ptr) != false) {
    /* Check if Thread is waiting to send a data */
    if (!isQueueEmpty(&dq->wait_put_queue)) {
      /* Get waiting Thread with highest Priority */
      thread = GetThreadByQueue(dq->wait_put_queue.next);
      /* Try to put a data into Queue */
      if (DataPut(dq, (const void *)thread->winfo.dataque.data_ptr) != false) {
        /* Wakeup waiting Thread with highest Priority */
        krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_YES);
      }
    }
    status = osOK;
  }
  else {
    /* No Message available */
    if (timeout != 0U) {
      /* Suspend current Thread */
      thread = ThreadGetRunning();
      status = krnThreadWaitEnter(thread, &dq->wait_get_queue, timeout);
      if (status != osErrorTimeout) {
        thread->winfo.dataque.data_ptr = (uint32_t)data_ptr;
      }
    }
    else {
      status = osErrorResource;
    }
  }

  return (status);
}

static uint32_t svcDataQueueGetCapacity(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->max_data_count);
}

static uint32_t svcDataQueueGetDataSize(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->data_size);
}

static uint32_t svcDataQueueGetCount(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->data_count);
}

static uint32_t svcDataQueueGetSpace(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (0U);
  }

  return (dq->max_data_count - dq->data_count);
}

static osStatus_t svcDataQueueReset(osDataQueueId_t dq_id)
{
  osDataQueue_t    *dq = dq_id;
  osThread_t       *thread;
  winfo_dataque_t  *winfo;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (osErrorParameter);
  }

  /* Remove data from Queue */
  DataReset(dq);
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
      krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    } while(!isQueueEmpty(&dq->wait_put_queue));
    krnThreadDispatch(NULL);
  }

  return (osOK);
}

static osStatus_t svcDataQueueDelete(osDataQueueId_t dq_id)
{
  osDataQueue_t *dq = dq_id;

  /* Check parameters */
  if ((dq == NULL) || (dq->id != ID_DATA_QUEUE)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  krnThreadWaitDelete(&dq->wait_put_queue);
  krnThreadWaitDelete(&dq->wait_get_queue);

  /* Mark object as invalid */
  dq->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  ISR Calls
 ******************************************************************************/

__STATIC_INLINE
osStatus_t isrDataQueuePut(osDataQueueId_t dq_id, const void *data_ptr, uint32_t timeout)
{
  osDataQueue_t    *dq = dq_id;
  osStatus_t        status;

  /* Check parameters */
  if ((dq       == NULL) || (dq->id  != ID_DATA_QUEUE) ||
      (data_ptr == NULL) || (timeout != 0U)) {
    return (osErrorParameter);
  }

  /* Try to put a data into Queue */
  if (DataPut(dq, data_ptr) != false) {
    /* Register post ISR processing */
    krnPostProcess((osObject_t *)dq);
    status = osOK;
  }
  else {
    /* No memory available */
    status = osErrorResource;
  }

  return (status);
}

__STATIC_INLINE
osStatus_t isrDataQueueGet(osDataQueueId_t dq_id, void *data_ptr, uint32_t timeout)
{
  osDataQueue_t    *dq = dq_id;
  osStatus_t        status;

  /* Check parameters */
  if ((dq       == NULL) || (dq->id  != ID_DATA_QUEUE) ||
      (data_ptr == NULL) || (timeout != 0U)) {
    return (osErrorParameter);
  }

  /* Get Data from Queue */
  if (DataGet(dq, data_ptr) != false) {
    /* Register post ISR processing */
    krnPostProcess((osObject_t *)dq);
    status = osOK;
  }
  else {
    /* No Data available */
    status = osErrorResource;
  }

  return (status);
}

/*******************************************************************************
 *  Post ISR processing
 ******************************************************************************/

/**
 * @brief       Data Queue post ISR processing.
 * @param[in]   dq  data queue object.
 */
void krnDataQueuePostProcess(osDataQueue_t *dq)
{
  osThread_t *thread;

  /* Check if Thread is waiting to receive a data */
  if (!isQueueEmpty(&dq->wait_get_queue)) {
    thread = GetThreadByQueue(dq->wait_get_queue.next);
    /* Try to get Data from Queue */
    if (DataGet(dq, (void *)thread->winfo.dataque.data_ptr) != false) {
      /* Wakeup waiting Thread with highest Priority */
      krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    }
  }
  /* Check if Thread is waiting to send a data */
  else if (!isQueueEmpty(&dq->wait_put_queue)) {
    /* Get waiting Thread with highest Priority */
    thread = GetThreadByQueue(dq->wait_put_queue.next);
    /* Try to put a data into Queue */
    if (DataPut(dq, (const void *)thread->winfo.dataque.data_ptr) != false) {
      /* Wakeup waiting Thread with highest Priority */
      krnThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    }
  }
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
    dq_id = (osDataQueueId_t)SVC_3(data_count, data_size, attr, svcDataQueueNew);
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
    name = (const char *)SVC_1(dq_id, svcDataQueueGetName);
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
    status = isrDataQueuePut(dq_id, data_ptr, timeout);
  }
  else {
    status = (osStatus_t)SVC_3(dq_id, data_ptr, timeout, svcDataQueuePut);
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
    status = isrDataQueueGet(dq_id, data_ptr, timeout);
  }
  else {
    status = (osStatus_t)SVC_3(dq_id, data_ptr, timeout, svcDataQueueGet);
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
    capacity = svcDataQueueGetCapacity(dq_id);
  }
  else {
    capacity = SVC_1(dq_id, svcDataQueueGetCapacity);
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
    data_size = svcDataQueueGetDataSize(dq_id);
  }
  else {
    data_size = SVC_1(dq_id, svcDataQueueGetDataSize);
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
    count = svcDataQueueGetCount(dq_id);
  }
  else {
    count = SVC_1(dq_id, svcDataQueueGetCount);
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
    space = svcDataQueueGetSpace(dq_id);
  }
  else {
    space = SVC_1(dq_id, svcDataQueueGetSpace);
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
    status = (osStatus_t)SVC_1(dq_id, svcDataQueueReset);
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
    status = (osStatus_t)SVC_1(dq_id, svcDataQueueDelete);
  }

  return (status);
}

/* ----------------------------- End of file ---------------------------------*/
