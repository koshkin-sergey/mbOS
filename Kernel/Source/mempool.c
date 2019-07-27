/*
 * Copyright (C) 2017-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
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

static osMemoryPoolId_t MemoryPoolNew(uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr)
{
  osMemoryPool_t *mp;
  void           *mp_mem;
  uint32_t        mp_size;

  /* Check parameters */
  if ((block_count == 0U) || (block_size  == 0U) || ((__CLZ(block_count) + __CLZ(block_size)) < 32U) || (attr == NULL)) {
    return (NULL);
  }

  mp      = attr->cb_mem;
  mp_mem  = attr->mp_mem;
  mp_size = attr->mp_size;

  /* Check parameters */
  if ((mp == NULL) || (((uint32_t)mp & 3U) != 0U) || (attr->cb_size < sizeof(osMemoryPool_t)) ||
      (mp_mem == NULL) || (((uint32_t)mp_mem & 3U) != 0U) || (mp_size < (block_count * block_size))) {
    return (NULL);
  }

  /* Initialize control block */
  mp->id = ID_MEMORYPOOL;
  mp->flags = 0U;
  mp->name = attr->name;
  QueueReset(&mp->wait_queue);
  libMemoryPoolInit(block_count, block_size, mp_mem, &mp->info);

  return (mp);
}

static const char *MemoryPoolGetName(osMemoryPoolId_t mp_id)
{
  osMemoryPool_t *mp = mp_id;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (NULL);
  }

  return (mp->name);
}

static void *MemoryPoolAlloc(osMemoryPoolId_t mp_id, uint32_t timeout)
{
  osMemoryPool_t *mp = mp_id;
  void           *block;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (NULL);
  }

  BEGIN_CRITICAL_SECTION

  /* Allocate memory */
  block = libMemoryPoolAlloc(&mp->info);
  if (block == NULL && timeout != 0U) {
    if (libThreadWaitEnter(ThreadGetRunning(), &mp->wait_queue, timeout)) {
      block = (void *)osThreadWait;
    }
  }

  END_CRITICAL_SECTION

  return (block);
}

static osStatus_t MemoryPoolFree(osMemoryPoolId_t mp_id, void *block)
{
  osMemoryPool_t *mp = mp_id;
  osStatus_t      status;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (osErrorParameter);
  }

  BEGIN_CRITICAL_SECTION

  /* Check if Thread is waiting to allocate memory */
  if (!isQueueEmpty(&mp->wait_queue)) {
    /* Wakeup waiting Thread with highest Priority */
    libThreadWaitExit(GetThreadByQueue(mp->wait_queue.next), (uint32_t)block, DISPATCH_YES);
    status = osOK;
  }
  else {
    /* Free memory */
    status = libMemoryPoolFree(&mp->info, block);
  }

  END_CRITICAL_SECTION

  return (status);
}

static uint32_t MemoryPoolGetCapacity(osMemoryPoolId_t mp_id)
{
  osMemoryPool_t *mp = mp_id;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (0U);
  }

  return (mp->info.max_blocks);
}

static uint32_t MemoryPoolGetBlockSize(osMemoryPoolId_t mp_id)
{
  osMemoryPool_t *mp = mp_id;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (0U);
  }

  return (mp->info.block_size);
}

static uint32_t MemoryPoolGetCount(osMemoryPoolId_t mp_id)
{
  osMemoryPool_t *mp = mp_id;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (0U);
  }

  return (mp->info.used_blocks);
}

static uint32_t MemoryPoolGetSpace(osMemoryPoolId_t mp_id)
{
  osMemoryPool_t *mp = mp_id;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (0U);
  }

  return (mp->info.max_blocks - mp->info.used_blocks);
}

static osStatus_t MemoryPoolDelete(osMemoryPoolId_t mp_id)
{
  osMemoryPool_t *mp = mp_id;

  /* Check parameters */
  if ((mp == NULL) || (mp->id != ID_MEMORYPOOL)) {
    return (osErrorParameter);
  }

  /* Unblock waiting threads */
  libThreadWaitDelete(&mp->wait_queue);

  /* Mark object as invalid */
  mp->id = ID_INVALID;

  return (osOK);
}

/*******************************************************************************
 *  Library functions
 ******************************************************************************/

/**
 * @brief       Initialize Memory Pool.
 * @param[in]   block_count   maximum number of memory blocks in memory pool.
 * @param[in]   block_size    size of a memory block in bytes.
 * @param[in]   block_mem     pointer to memory for block storage.
 * @param[in]   mp_info       memory pool info.
 */
void libMemoryPoolInit(uint32_t block_count, uint32_t block_size, void *block_mem, osMemoryPoolInfo_t *mp_info)
{
  // Initialize information structure
  mp_info->max_blocks  = block_count;
  mp_info->used_blocks = 0U;
  mp_info->block_size  = block_size;
  mp_info->block_base  = block_mem;
  mp_info->block_free  = block_mem;
  mp_info->block_lim   = &(((uint8_t *)block_mem)[block_count * block_size]);

  /* Reset Memory Pool */
  libMemoryPoolReset(mp_info);
}

/**
 * @brief       Reset Memory Pool.
 * @param[in]   mp_info       memory pool info.
 */
void libMemoryPoolReset(osMemoryPoolInfo_t *mp_info)
{
  void *mem;
  void *block;
  uint32_t block_count;

  /* Link all free blocks */
  mem = mp_info->block_base;
  block_count = mp_info->max_blocks;

  while (--block_count != 0U) {
    block = &((uint8_t *)mem)[mp_info->block_size];
    *((void **)mem) = block;
    mem = block;
  }
  *((void **)mem) = NULL;
}

/**
 * @brief       Allocate a memory block from a Memory Pool.
 * @param[in]   mp_info   memory pool info.
 * @return      address of the allocated memory block or NULL in case of no memory is available.
 */
void *libMemoryPoolAlloc(osMemoryPoolInfo_t *mp_info)
{
  void *block;

  if (mp_info == NULL) {
    return (NULL);
  }

  block = mp_info->block_free;
  if (block != NULL) {
    mp_info->block_free = *((void **)block);
    mp_info->used_blocks++;
  }

  return (block);
}

/**
 * @brief       Return an allocated memory block back to a Memory Pool.
 * @param[in]   mp_info   memory pool info.
 * @param[in]   block     address of the allocated memory block to be returned to the memory pool.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t libMemoryPoolFree(osMemoryPoolInfo_t *mp_info, void *block)
{
  if ((mp_info == NULL) || (block < mp_info->block_base) || (block >= mp_info->block_lim)) {
    return (osErrorParameter);
  }

  *((void **)block) = mp_info->block_free;
  mp_info->block_free = block;
  mp_info->used_blocks--;

  return (osOK);
}

/*******************************************************************************
 *  Public API
 ******************************************************************************/

/**
 * @fn          osMemoryPoolId_t osMemoryPoolNew(uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr)
 * @brief       Create and Initialize a Memory Pool object.
 * @param[in]   block_count   maximum number of memory blocks in memory pool.
 * @param[in]   block_size    memory block size in bytes.
 * @param[in]   attr          memory pool attributes.
 * @return      memory pool ID for reference by other functions or NULL in case of error.
 */
osMemoryPoolId_t osMemoryPoolNew(uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr)
{
  osMemoryPoolId_t mp_id;

  if (IsIrqMode() || IsIrqMasked()) {
    mp_id = NULL;
  }
  else {
    mp_id = (osMemoryPoolId_t)svc_3(block_count, block_size, (uint32_t)attr, (uint32_t)MemoryPoolNew);
  }

  return (mp_id);
}

/**
 * @fn          const char *osMemoryPoolGetName(osMemoryPoolId_t mp_id)
 * @brief       Get name of a Memory Pool object.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      name as null-terminated string or NULL in case of an error.
 */
const char *osMemoryPoolGetName(osMemoryPoolId_t mp_id)
{
  const char *name;

  if (IsIrqMode() || IsIrqMasked()) {
    name = NULL;
  }
  else {
    name = (const char *)svc_1((uint32_t)mp_id, (uint32_t)MemoryPoolGetName);
  }

  return (name);
}

/**
 * @fn          void *osMemoryPoolAlloc(osMemoryPoolId_t mp_id, uint32_t timeout)
 * @brief       Allocate a memory block from a Memory Pool.
 * @param[in]   mp_id     memory pool ID obtained by \ref osMemoryPoolNew.
 * @param[in]   timeout   \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return      address of the allocated memory block or NULL in case of no memory is available.
 */
void *osMemoryPoolAlloc(osMemoryPoolId_t mp_id, uint32_t timeout)
{
  void *memory;

  if (IsIrqMode() || IsIrqMasked()) {
    if (timeout != 0U) {
      memory = NULL;
    }
    else {
      memory = MemoryPoolAlloc(mp_id, timeout);
    }
  }
  else {
    memory = (void *)svc_2((uint32_t)mp_id, timeout, (uint32_t)MemoryPoolAlloc);
    if ((int32_t)memory == osThreadWait) {
      memory = (void *)ThreadGetRunning()->winfo.ret_val;
      if ((osStatus_t)memory == osErrorTimeout) {
        memory = NULL;
      }
    }
  }

  return (memory);
}

/**
 * @fn          osStatus_t osMemoryPoolFree(osMemoryPoolId_t mp_id, void *block)
 * @brief       Return an allocated memory block back to a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @param[in]   block   address of the allocated memory block to be returned to the memory pool.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMemoryPoolFree(osMemoryPoolId_t mp_id, void *block)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = MemoryPoolFree(mp_id, block);
  }
  else {
    status = (osStatus_t)svc_2((uint32_t)mp_id, (uint32_t)block, (uint32_t)MemoryPoolFree);
  }

  return (status);
}

/**
 * @fn          uint32_t osMemoryPoolGetCapacity(osMemoryPoolId_t mp_id)
 * @brief       Get maximum number of memory blocks in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      maximum number of memory blocks or 0 in case of an error.
 */
uint32_t osMemoryPoolGetCapacity(osMemoryPoolId_t mp_id)
{
  uint32_t capacity;

  if (IsIrqMode() || IsIrqMasked()) {
    capacity = MemoryPoolGetCapacity(mp_id);
  }
  else {
    capacity = svc_1((uint32_t)mp_id, (uint32_t)MemoryPoolGetCapacity);
  }

  return (capacity);
}

/**
 * @fn          uint32_t osMemoryPoolGetBlockSize(osMemoryPoolId_t mp_id)
 * @brief       Get memory block size in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      memory block size in bytes or 0 in case of an error.
 */
uint32_t osMemoryPoolGetBlockSize(osMemoryPoolId_t mp_id)
{
  uint32_t block_size;

  if (IsIrqMode() || IsIrqMasked()) {
    block_size = MemoryPoolGetBlockSize(mp_id);
  }
  else {
    block_size = svc_1((uint32_t)mp_id, (uint32_t)MemoryPoolGetBlockSize);
  }

  return (block_size);
}

/**
 * @fn          uint32_t osMemoryPoolGetCount(osMemoryPoolId_t mp_id)
 * @brief       Get number of memory blocks used in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      number of memory blocks used or 0 in case of an error.
 */
uint32_t osMemoryPoolGetCount(osMemoryPoolId_t mp_id)
{
  uint32_t count;

  if (IsIrqMode() || IsIrqMasked()) {
    count = MemoryPoolGetCount(mp_id);
  }
  else {
    count = svc_1((uint32_t)mp_id, (uint32_t)MemoryPoolGetCount);
  }

  return (count);
}

/**
 * @fn          uint32_t osMemoryPoolGetSpace(osMemoryPoolId_t mp_id)
 * @brief       Get number of memory blocks available in a Memory Pool.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      number of memory blocks available or 0 in case of an error.
 */
uint32_t osMemoryPoolGetSpace(osMemoryPoolId_t mp_id)
{
  uint32_t space;

  if (IsIrqMode() || IsIrqMasked()) {
    space = MemoryPoolGetSpace(mp_id);
  }
  else {
    space = svc_1((uint32_t)mp_id, (uint32_t)MemoryPoolGetSpace);
  }

  return (space);
}

/**
 * @fn          osStatus_t osMemoryPoolDelete(osMemoryPoolId_t mp_id)
 * @brief       Delete a Memory Pool object.
 * @param[in]   mp_id   memory pool ID obtained by \ref osMemoryPoolNew.
 * @return      status code that indicates the execution status of the function.
 */
osStatus_t osMemoryPoolDelete(osMemoryPoolId_t mp_id)
{
  osStatus_t status;

  if (IsIrqMode() || IsIrqMasked()) {
    status = osErrorISR;
  }
  else {
    status = (osStatus_t)svc_1((uint32_t)mp_id, (uint32_t)MemoryPoolDelete);
  }

  return (status);
}

/*------------------------------ End of file ---------------------------------*/
