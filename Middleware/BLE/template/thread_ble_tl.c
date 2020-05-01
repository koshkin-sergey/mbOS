/******************************************************************************
 * @file    thread_ble_tl.c
 * @brief   Thread for BlueNRG-MS transport layer.
 * @author  Sergey Koshkin
 * @version V1.0.0
 ******************************************************************************/
/*
 * Copyright (C) 2020 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "app.h"
#include <string.h>
#include <asm/GPIO_STM32F7xx.h>
#include <asm/EXTI_STM32F7xx.h>
#include <CMSIS/Driver/Driver_SPI.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STK_SIZE               512U
#define DRIVER_SPI_NUM                1
#define HEADER_SIZE                   5U
#define BUFFER_SIZE                   128U
#define EVENT_POOL_CNT                5U

/* Event flags */
#define FLAG_RECEIVE                  (1UL << 0U)
#define FLAG_SEND                     (1UL << 1U)
#define FLAG_RESET                    (1UL << 2U)
#define FLAG_TRANSFER_COMPLETE        (1UL << 3U)
#define FLAG_TX_READY                 (1UL << 4U)

/* BlueNRG-MS Event line */
#define BLE_EXTI_PORT                 EXTI_PORT_C
#define BLE_EXTI_LINE                 EXTI_LINE_4

/* BlueNRG-MS Event pin */
#define BLE_EVENT_PORT                GPIO_PORT_C
#define BLE_EVENT_PIN                 GPIO_PIN_4

/* BlueNRG-MS Reset pin */
#define BLE_RESET_PORT                GPIO_PORT_C
#define BLE_RESET_PIN                 GPIO_PIN_5

/* BlueNRG-MS Control byte */
#define BLE_WRITE_OPER                0x0A
#define BLE_READ_OPER                 0x0B
#define BLE_READY                     0x02

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

extern ARM_DRIVER_SPI ARM_Driver_SPI_(DRIVER_SPI_NUM);

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct buffer_s {
  uint8_t data[BUFFER_SIZE];
  uint8_t size;
} buffer_t;

typedef __PACKED_STRUCT header_s {
  uint8_t ctrl;
  uint16_t wbuf_size;
  uint16_t rbuf_size;
} header_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

//static buffer_t buf_rx;
static buffer_t buf_tx;

static osThread_t           thread_cb;
static uint64_t             thread_stack[THREAD_STK_SIZE/8U];
static const osThreadAttr_t thread_attr = {
  .name       = NULL,
  .attr_bits  = 0U,
  .cb_mem     = &thread_cb,
  .cb_size    = sizeof(thread_cb),
  .stack_mem  = &thread_stack[0],
  .stack_size = sizeof(thread_stack),
  .priority   = osPriorityHigh,
};

static osEventFlagsId_t         ble_evt;
static osEventFlags_t           ble_evt_cb;
static const osEventFlagsAttr_t ble_evt_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &ble_evt_cb,
  .cb_size   = sizeof(ble_evt_cb)
};

static osMemoryPoolId_t         event_pool;
static osMemoryPool_t           event_pool_cb;
static uint8_t event_pool_mem[osMemoryPoolMemSize(EVENT_POOL_CNT, BUFFER_SIZE)];
static const osMemoryPoolAttr_t event_pool_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &event_pool_cb,
  .cb_size   = sizeof(event_pool_cb),
  .mp_mem    = &event_pool_mem[0],
  .mp_size   = osMemoryPoolMemSize(EVENT_POOL_CNT, BUFFER_SIZE),
};

static osDataQueueId_t         event_queue;
static osDataQueue_t           event_queue_cb;
static void* event_queue_mem[EVENT_POOL_CNT];
static const osDataQueueAttr_t event_queue_attr = {
  .name = NULL,
  .attr_bits = 0U,
  .cb_mem    = &event_queue_cb,
  .cb_size   = sizeof(event_queue_cb),
  .dq_mem    = &event_queue_mem[0],
  .dq_size   = sizeof(event_queue_mem),
};

static ARM_DRIVER_SPI *driver_spi = &ARM_Driver_SPI_(DRIVER_SPI_NUM);

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void SPI_Callback(uint32_t event)
{
  if (event & ARM_SPI_EVENT_TRANSFER_COMPLETE) {
    osEventFlagsSet(ble_evt, FLAG_TRANSFER_COMPLETE);
  }
}

static void EXTI_Callback(EXTI_Line_t line)
{
  if (line == BLE_EXTI_LINE) {
    osEventFlagsSet(ble_evt, FLAG_RECEIVE);
  }
}

static void ResetPinConfig(void)
{
  static const GPIO_PIN_CFG_t reset_pin_cfg = {
      GPIO_MODE_OUT_PP,
      GPIO_PULL_DISABLE,
      GPIO_SPEED_LOW
  };

  if (!GPIO_GetPortClockState(BLE_RESET_PORT)) {
    GPIO_PortClock(BLE_RESET_PORT, GPIO_PORT_CLK_ENABLE);
  }

  GPIO_PinWrite(BLE_RESET_PORT, BLE_RESET_PIN, GPIO_PIN_OUT_HIGH);
  GPIO_PinConfig(BLE_RESET_PORT, BLE_RESET_PIN, &reset_pin_cfg);
}

static void EventPinConfig(void)
{
  static const GPIO_PIN_CFG_t event_pin_cfg = {
      GPIO_MODE_INPUT,
      GPIO_PULL_DOWN,
      GPIO_SPEED_LOW
  };

  if (!GPIO_GetPortClockState(BLE_EVENT_PORT)) {
    GPIO_PortClock(BLE_EVENT_PORT, GPIO_PORT_CLK_ENABLE);
  }

  GPIO_PinConfig(BLE_EVENT_PORT, BLE_EVENT_PIN, &event_pin_cfg);
}

int32_t TransferHeader(header_t *hdr)
{
  int32_t  ret;
  uint32_t flags;

  ret = driver_spi->Transfer(hdr, hdr, sizeof(header_t));
  if (ret != ARM_DRIVER_OK) {
    return (-1);
  }

  flags = osEventFlagsWait(ble_evt, FLAG_TRANSFER_COMPLETE, osFlagsWaitAny,
                           osWaitForever);
  if ((int32_t)flags < 0) {
    return (-2);
  }

  return (0);
}

uint32_t isEventAvailable(void)
{
  return GPIO_PinRead(BLE_EVENT_PORT, BLE_EVENT_PIN);
}

static void ReceiveEvent(void)
{
  int32_t   ret;
  header_t  hdr;
  void     *buf_rx;

  while(isEventAvailable()) {
    buf_rx = osMemoryPoolAlloc(event_pool, osWaitForever);
    if (buf_rx != NULL) {
      hdr.ctrl = BLE_READ_OPER;
      /* CS reset */
      driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
      /* Read header */
      ret = TransferHeader(&hdr);
      if ((ret == 0) && (hdr.ctrl == BLE_READY) && (hdr.rbuf_size > 0U)) {
        if (hdr.rbuf_size > BUFFER_SIZE) {
          hdr.rbuf_size = BUFFER_SIZE;
        }
        ret = driver_spi->Receive(buf_rx, hdr.rbuf_size);
        if (ret == ARM_DRIVER_OK) {
          osEventFlagsWait(ble_evt, FLAG_TRANSFER_COMPLETE, osFlagsWaitAny,
                           osWaitForever);
        }
      }
      else {
        ret = ARM_DRIVER_ERROR;
      }
      /* Release CS line */
      driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);

      if (ret == ARM_DRIVER_OK) {
        osDataQueuePut(event_queue, &buf_rx, osWaitForever);
      }
      else {
        osMemoryPoolFree(event_pool, buf_rx);
      }
    }
  };
}

static void SendData(buffer_t *buf)
{
  int32_t  ret, result;
  header_t hdr;
  uint32_t cnt = 0U;

  do {
    result = -1;
    ++cnt;
    hdr.ctrl = BLE_WRITE_OPER;
    /* CS reset */
    driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
    /* Read header */
    ret = TransferHeader(&hdr);
    if ((ret == 0) && (hdr.ctrl == BLE_READY)) {
      if (hdr.wbuf_size >= buf->size) {
        ret = driver_spi->Send(&buf->data[0], buf->size);
        if (ret == ARM_DRIVER_OK) {
          osEventFlagsWait(ble_evt, FLAG_TRANSFER_COMPLETE, osFlagsWaitAny,
                           osWaitForever);
          result = 0;
        }
      }
    }
    /* Release CS line */
    driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
    if (result != 0) {
      osDelay(1);
    }
  } while((result != 0) && (cnt < 10U));

  osEventFlagsSet(ble_evt, FLAG_TX_READY);
}

void ResetModule(void)
{
  GPIO_PinWrite(BLE_RESET_PORT, BLE_RESET_PIN, GPIO_PIN_OUT_LOW);
  osDelay(100);
  GPIO_PinWrite(BLE_RESET_PORT, BLE_RESET_PIN, GPIO_PIN_OUT_HIGH);
  osDelay(5);
}

__NO_RETURN static
void thread_ble_tl(void *param)
{
  (void) param;
  int32_t ret;
  uint32_t flags;

  DEBUG_LOG("Created thread for BLE transport layer\r\n");

  driver_spi->Initialize(SPI_Callback);
  driver_spi->PowerControl(ARM_POWER_FULL);
  ret = driver_spi->Control(ARM_SPI_MODE_MASTER  |
                            ARM_SPI_CPOL0_CPHA0  |
                            ARM_SPI_SS_MASTER_SW |
                            ARM_SPI_DATA_BITS(8), 8000000);
  if (ret != ARM_DRIVER_OK) {
    DEBUG_LOG("Error SPI interface configuration %d\r\n", ret);
    osThreadExit();
  }
  ret = driver_spi->Control(ARM_SPI_GET_BUS_SPEED, 0U);
  DEBUG_LOG("BLE module SPI interface clock = %d Hz\r\n", ret);

  EXTI_Initialize(EXTI_Callback);
  EXTI_SetConfigLine(BLE_EXTI_LINE, BLE_EXTI_PORT, EXTI_MODE_INTERRUPT,
                     EXTI_TRIGGER_RISING);

  osEventFlagsSet(ble_evt, FLAG_TX_READY);

  for(;;) {
    flags = osEventFlagsWait(ble_evt, FLAG_RECEIVE | FLAG_SEND | FLAG_RESET,
                             osFlagsWaitAny, osWaitForever);
    if ((int32_t)flags < 0) {
      DEBUG_LOG("Error of event wait %d", (int32_t)flags);
      continue;
    }

    if (flags & FLAG_RECEIVE) {
      ReceiveEvent();
    }

    if (flags & FLAG_SEND) {
      SendData(&buf_tx);
    }

    if (flags & FLAG_RESET) {
      ResetModule();
    }
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          int32_t BLE_InitTransportLayer(const void*)
 * @brief       Create BLE transport layer thread.
 *
 * @param[in]   pConf  Pointer to configuration struct
 * @return      0
 */
int32_t BLE_InitTransportLayer(const void* pConf)
{
  /* Initialize reset pin */
  ResetPinConfig();
  /* Initialize event pin */
  EventPinConfig();
  /* Create Event Pool */
  event_pool = osMemoryPoolNew(EVENT_POOL_CNT, BUFFER_SIZE, &event_pool_attr);
  /* Create Event Queue */
  event_queue = osDataQueueNew(EVENT_POOL_CNT, sizeof(void*), &event_queue_attr);
  /* Create Event Flag */
  ble_evt = osEventFlagsNew(&ble_evt_attr);
  if (ble_evt != NULL) {
    /* Create Thread */
    osThreadNew(thread_ble_tl, (void*)pConf, &thread_attr);
  }

  return (0);
}

/**
 * @fn          int32_t BLE_Reset(void)
 * @brief       Reset BlueNRG module.
 *
 * @return      0
 */
int32_t BLE_Reset(void)
{
  osEventFlagsSet(ble_evt, FLAG_RESET);

  return (0);
}

/**
 * @fn          int32_t BLE_Send(const uint8_t*, uint16_t)
 * @brief       Writes data from local buffer to Bluetooth module.
 *
 * @param[in]   buf   Data buffer to be written
 * @param[in]   size  Size of the data buffer
 * @return      Number of bytes are written
 */
int32_t BLE_Send(const uint8_t* buf, uint16_t size)
{
  uint32_t flags;

  if ((buf == NULL) || (size > BUFFER_SIZE)) {
    return (0);
  }

  flags = osEventFlagsWait(ble_evt, FLAG_TX_READY, osFlagsWaitAny, 10);
  if ((int32_t)flags < 0) {
    return (0);
  }

  memcpy(&buf_tx.data[0], buf, size);
  buf_tx.size = size;

  osEventFlagsSet(ble_evt, FLAG_SEND);

  return (size);
}

/* ----------------------------- End of file ---------------------------------*/
