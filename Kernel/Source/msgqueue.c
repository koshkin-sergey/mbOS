/*
 * Copyright (C) 2013-2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

static osMessage_t *MessagePut(osMessageQueue_t *mq, const void *msg_ptr, uint8_t msg_prio)
{
  queue_t     *que;
  osMessage_t *msg;

  /* Try to allocate memory */
  msg = krnMemoryPoolAlloc(&mq->mp_info);
  if (msg != NULL) {
    /* Copy Message */
    memcpy(&msg[1], msg_ptr, mq->msg_size);
    msg->id = ID_MESSAGE;
    msg->flags = 0U;
    msg->priority = msg_prio;
    /* Put Message into Queue */
    que = &mq->msg_queue;
    if (msg_prio != 0U) {
      for (que = que->next; que != &mq->msg_queue; que = que->next) {
        if (GetMessageByQueue(que)->priority < msg_prio) {
          break;
        }
      }
    }
    QueueAppend(que, &msg->msg_que);
    mq->msg_count++;
  }

  return (msg);
}

static osMessage_t *MessageGet(osMessageQueue_t *mq, void *msg_ptr, uint8_t *msg_prio)
{
  queue_t     *que;
  osMessage_t *msg;

  que = &mq->msg_queue;

  if (!isQueueEmpty(que)) {
    msg = GetMessageByQueue(QueueExtract(que));
    /* Copy Message */
    memcpy(msg_ptr, &msg[1], mq->msg_size);
    if (msg_prio != NULL) {
      *msg_prio = msg->priority;
    }
    /* Free memory */
    msg->id = ID_INVALID;
    krnMemoryPoolFree(&mq->mp_info, msg);
    mq->msg_count--;
  }
  else {
    msg = NULL;
  }

  return (msg);
}

/*******************************************************************************
 *  Service Calls
 ******************************************************************************/

static osMessageQueueId_t svcMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr)
{
  osMessageQueue_t *mq;
  void             *mq_mem;
  uint32_t          mq_size;
  uint32_t          block_size;

  /* Check parameters */
  if ((msg_count == 0U) || (msg_size  == 0U) || (attr == NULL)) {
    return (NULL);
  }

  mq      = attr->cb_mem;
  mq_mem  = attr->mq_mem;
  mq_size = attr->mq_size;
  block_size = ((msg_size + 3U) & ~3UL) + sizeof(osMessage_t);

  /* Check parameters */
  if (((__CLZ(msg_count) + __CLZ(block_size)) < 32U) ||
      (mq == NULL) || (((uint32_t)mq & 3U) != 0U) || (attr->cb_size < sizeof(osMessageQueue_t)) ||
      (mq_mem == NULL) || (((uint32_t)mq_mem & 3U) != 0U) || (mq_size < (msg_count * block_size))) {
    return (NULL);
  }

  /* Initialize control block */
  mq->id = ID_MESSAGE_QUEUE;
  mq->flags = 0U;
  mq->name = attr->name;
  mq->msg_size = msg_size;
  mq->msg_count = 0U;
  QueueReset(&mq->wait_put_queue);
  QueueReset(&mq->wait_get_queue);
  QueueReset(&mq->msg_queue);
  krnMemoryPoolInit(msg_count, block_size, mq_mem, &mq->mp_info);

  return (mq);
}

static const char *svcMessageQueueGetName(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (NULL);
  }

  return (mq->name);
}

static osStatus_t svcMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
  osMessageQueue_t *mq = mq_id;
  osMessage_t      *msg;
  osThread_t       *thread;
  winfo_msgque_t   *winfo;
  osStatus_t        status;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE) || (msg_ptr == NULL)) {
    return (osErrorParameter);
  }

  /* Check if Thread is waiting to receive a Message */
  if (!isQueueEmpty(&mq->wait_get_queue)) {
    /* Wakeup waiting Thread with highest Priority */
    thread = GetThreadByQueue(mq->wait_get_queue.next);
    libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_YES);
    winfo = &thread->winfo.msgque;
    memcpy((void *)winfo->msg, msg_ptr, mq->msg_size);
    if ((uint8_t *)winfo->msg_prio != NULL) {
      *((uint8_t *)winfo->msg_prio) = msg_prio;
    }
    status = osOK;
  }
  else {
    /* Try to put Message into Queue */
    msg = MessagePut(mq, msg_ptr, msg_prio);
    if (msg != NULL) {
      status = osOK;
    }
    else {
      /* No memory available */
      if (timeout != 0U) {
        /* Suspend current Thread */
        thread = ThreadGetRunning();
        if (libThreadWaitEnter(thread, &mq->wait_put_queue, timeout)) {
          winfo = &thread->winfo.msgque;
          winfo->msg      = (void *)msg_ptr;
          winfo->msg_prio = (uint32_t)msg_prio;
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

  return (status);
}

static osStatus_t svcMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
  osMessageQueue_t *mq = mq_id;
  osMessage_t      *msg;
  osThread_t       *thread;
  winfo_msgque_t   *winfo;
  osStatus_t        status;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE) || (msg_ptr == NULL)) {
    return (osErrorParameter);
  }

  /* Get Message from Queue */
  msg = MessageGet(mq, msg_ptr, msg_prio);

  if (msg != NULL) {
    /* Check if Thread is waiting to send a Message */
    if (!isQueueEmpty(&mq->wait_put_queue)) {
      /* Get waiting Thread with highest Priority */
      thread = GetThreadByQueue(mq->wait_put_queue.next);
      winfo = &thread->winfo.msgque;
      /* Try to put Message into Queue */
      msg = MessagePut(mq, (const void *)winfo->msg, (uint8_t)winfo->msg_prio);
      if (msg != NULL) {
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
      if (libThreadWaitEnter(thread, &mq->wait_get_queue, timeout)) {
        winfo = &thread->winfo.msgque;
        winfo->msg      = msg_ptr;
        winfo->msg_prio = (uint32_t)msg_prio;
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

  return (status);
}

static uint32_t svcMessageQueueGetCapacity(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (0U);
  }

  return (mq->mp_info.max_blocks);
}

static uint32_t svcMessageQueueGetMsgSize(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (0U);
  }

  return (mq->msg_size);
}

static uint32_t svcMessageQueueGetCount(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (0U);
  }

  return (mq->msg_count);
}

static uint32_t svcMessageQueueGetSpace(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (0U);
  }

  return (mq->mp_info.max_blocks - mq->msg_count);
}

static osStatus_t svcMessageQueueReset(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;
  osMessage_t      *msg;
  osThread_t       *thread;
  winfo_msgque_t   *winfo;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (osErrorParameter);
  }

  /* Remove Messages from Queue */
  mq->msg_count = 0U;
  QueueReset(&mq->msg_queue);
  krnMemoryPoolReset(&mq->mp_info);

  /* Check if Threads are waiting to send Messages */
  if (!isQueueEmpty(&mq->wait_put_queue)) {
    do {
      /* Get waiting Thread with highest Priority */
      thread = GetThreadByQueue(mq->wait_put_queue.next);
      winfo = &thread->winfo.msgque;
      /* Try to put Message into Queue */
      msg = MessagePut(mq, (const void *)winfo->msg, (uint8_t)winfo->msg_prio);
      if (msg == NULL) {
        break;
      }
      /* Wakeup waiting Thread with highest Priority */
      libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    } while (!isQueueEmpty(&mq->wait_put_queue));
    libThreadDispatch(NULL);
  }

  return (osOK);
}

static osStatus_t svcMessageQueueDelete(osMessageQueueId_t mq_id)
{
  osMessageQueue_t *mq = mq_id;

  /* Check parameters */
  if ((mq == NULL) || (mq->id != ID_MESSAGE_QUEUE)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  libThreadWaitDelete(&mq->wait_put_queue);
  libThreadWaitDelete(&mq->wait_get_queue);

  /* Mark object as invalid */
  mq->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  ISR Calls
 ******************************************************************************/

__STATIC_INLINE
osStatus_t isrMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
  osMessageQueue_t *mq = mq_id;
  osMessage_t      *msg;
  osStatus_t        status;

  /* Check parameters */
  if ((mq      == NULL) || (mq->id  != ID_MESSAGE_QUEUE) ||
      (msg_ptr == NULL) || (timeout != 0U)) {
    return (osErrorParameter);
  }

  /* Try to put Message into Queue */
  msg = MessagePut(mq, msg_ptr, msg_prio);
  if (msg != NULL) {
    /* Register post ISR processing */
    krnPostProcess((osObject_t *)mq);
    status = osOK;
  }
  else {
    /* No memory available */
    status = osErrorResource;
  }

  return (status);
}

__STATIC_INLINE
osStatus_t isrMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
  osMessageQueue_t *mq = mq_id;
  osMessage_t      *msg;
  osStatus_t        status;

  /* Check parameters */
  if ((mq      == NULL) || (mq->id  != ID_MESSAGE_QUEUE) ||
      (msg_ptr == NULL) || (timeout != 0U)) {
    return (osErrorParameter);
  }

  /* Get Message from Queue */
  msg = MessageGet(mq, msg_ptr, msg_prio);
  if (msg != NULL) {
    /* Register post ISR processing */
    krnPostProcess((osObject_t *)mq);
    status = osOK;
  }
  else {
    /* No Message available */
    status = osErrorResource;
  }

  return (status);
}

/*******************************************************************************
 *  Post ISR processing
 ******************************************************************************/

/**
 * @brief       Message Queue post ISR processing.
 * @param[in]   mq  message queue object.
 */
void krnMessageQueuePostProcess(osMessageQueue_t *mq)
{
  osMessage_t    *msg;
  osThread_t     *thread;
  winfo_msgque_t *winfo;

  /* Check if Thread is waiting to receive a Message */
  if (!isQueueEmpty(&mq->wait_get_queue)) {
    /* Get waiting Thread with highest Priority */
    thread = GetThreadByQueue(mq->wait_get_queue.next);
    winfo = &thread->winfo.msgque;
    /* Try to get Message from Queue */
    msg = MessageGet(mq, winfo->msg, (uint8_t *)winfo->msg_prio);
    if (msg != NULL) {
      /* Wakeup waiting Thread */
      libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    }
  }
  else if (!isQueueEmpty(&mq->wait_put_queue)) {
    /* Get waiting Thread with highest Priority */
    thread = GetThreadByQueue(mq->wait_put_queue.next);
    winfo = &thread->winfo.msgque;
    /* Try to put Message into Queue */
    msg = MessagePut(mq, (const void *)winfo->msg, (uint8_t)winfo->msg_prio);
    if (msg != NULL) {
      /* Wakeup waiting Thread */
      libThreadWaitExit(thread, (uint32_t)osOK, DISPATCH_NO);
    }
  }
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr)
 * @brief       Create and Initialize a Message Queue object.
 * @param[in]   msg_count   maximum number of messages in queue.
 * @param[in]   msg_size    maximum message size in bytes.
 * @param[in]   attr        message queue attributes.
 * @return      message queue ID for reference by other functions or NULL in case of error.
 */
osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr)
{
  osMessageQueueId_t mq_id;

  if (IsIrqMode() || IsIrqMasked()) {
    mq_id = NULL;
  }
  else {
    mq_id = (osMessageQueueId_t)SVC_3(msg_count, msg_size, attr, svcMessageQueueNew);
  }

  return (mq_id);
}

/**
 * @fn          const char *osMessageQueueGetName(osMessageQueueId_t mq_id)
 * @brief       Get name of a Message Queue object.
 * @param[in]   mq_id   message queue ID obtained by \ref osMessageQueueNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osMessageQueueGetName(osMessageQueueId_t mq_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)SVC_1(mq_id, svcMessageQueueGetName);
  }

  return (name);
}

/**
 * @fn          osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
 * @brief       Put a Message into a Queue or timeout if Queue is full.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @param[in]   msg_ptr   pointer to buffer with message to put into a queue.
 * @param[in]   msg_prio  message priority.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = isrMessageQueuePut(mq_id, msg_ptr, msg_prio, timeout);
  }
  else {
    status = (osStatus_t)SVC_4(mq_id, msg_ptr, msg_prio, timeout, svcMessageQueuePut);
    if (status == osThreadWait) {
      status = (osStatus_t)ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (status);
}

/**
 * @fn          osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
 * @brief       Get a Message from a Queue or timeout if Queue is empty.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @param[out]  msg_ptr   pointer to buffer for message to get from a queue.
 * @param[out]  msg_prio  pointer to buffer for message priority or NULL.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = isrMessageQueueGet(mq_id, msg_ptr, msg_prio, timeout);
  }
  else {
    status = (osStatus_t)SVC_4(mq_id, msg_ptr, msg_prio, timeout, svcMessageQueueGet);
    if (status == osThreadWait) {
      status = (osStatus_t)ThreadGetRunning()->winfo.ret_val;
    }
  }

  return (status);
}

/**
 * @fn          uint32_t osMessageQueueGetCapacity(osMessageQueueId_t mq_id)
 * @brief       Get maximum number of messages in a Message Queue.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      maximum number of messages or 0 in case of an error.
 */
uint32_t osMessageQueueGetCapacity(osMessageQueueId_t mq_id)
{
  uint32_t capacity;

  if (IsIrqMode() || IsIrqMasked()) {
    capacity = svcMessageQueueGetCapacity(mq_id);
  }
  else {
    capacity = SVC_1(mq_id, svcMessageQueueGetCapacity);
  }

  return (capacity);
}

/**
 * @fn          uint32_t osMessageQueueGetMsgSize(osMessageQueueId_t mq_id)
 * @brief       Get maximum message size in bytes.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      maximum message size in bytes or 0 in case of an error.
 */
uint32_t osMessageQueueGetMsgSize(osMessageQueueId_t mq_id)
{
  uint32_t msg_size;

  if (IsIrqMode() || IsIrqMasked()) {
    msg_size = svcMessageQueueGetMsgSize(mq_id);
  }
  else {
    msg_size = SVC_1(mq_id, svcMessageQueueGetMsgSize);
  }

  return (msg_size);
}

/**
 * @fn          uint32_t osMessageQueueGetCount(osMessageQueueId_t mq_id)
 * @brief       Get number of queued messages in a Message Queue.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      number of queued messages or 0 in case of an error.
 */
uint32_t osMessageQueueGetCount(osMessageQueueId_t mq_id)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = svcMessageQueueGetCount(mq_id);
  }
  else {
    count = SVC_1(mq_id, svcMessageQueueGetCount);
  }

  return (count);
}

/**
 * @fn          uint32_t osMessageQueueGetSpace(osMessageQueueId_t mq_id)
 * @brief       Get number of available slots for messages in a Message Queue.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      number of available slots for messages or 0 in case of an error.
 */
uint32_t osMessageQueueGetSpace(osMessageQueueId_t mq_id)
{
  uint32_t space;

  if (IsIrqMode() || IsIrqMasked()) {
    space = svcMessageQueueGetSpace(mq_id);
  }
  else {
    space = SVC_1(mq_id, svcMessageQueueGetSpace);
  }

  return (space);
}

/**
 * @fn          osStatus_t osMessageQueueReset(osMessageQueueId_t mq_id)
 * @brief       Reset a Message Queue to initial empty state.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueReset(osMessageQueueId_t mq_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(mq_id, svcMessageQueueReset);
  }

  return (status);
}

/**
 * @fn          osStatus_t osMessageQueueDelete(osMessageQueueId_t mq_id)
 * @brief       Delete a Message Queue object.
 * @param[in]   mq_id     message queue ID obtained by \ref osMessageQueueNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueDelete(osMessageQueueId_t mq_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)SVC_1(mq_id, svcMessageQueueDelete);
  }

  return (status);
}

/* ----------------------------- End of file ---------------------------------*/
