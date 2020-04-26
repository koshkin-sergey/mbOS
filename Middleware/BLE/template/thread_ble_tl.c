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
#include <asm/EXTI_STM32F7xx.h>
#include <CMSIS/Driver/Driver_SPI.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STK_SIZE               512U
#define DRIVER_SPI_NUM                1
#define HEADER_SIZE                   5U
#define BUFFER_SIZE                   128U

/* Event flags */
#define BLE_EVENT_RECEIVE             (1UL << 0U)
#define BLE_EVENT_SEND                (1UL << 1U)
#define BLE_EVENT_TRANSFER_COMPLETE   (1UL << 2U)
#define BLE_EVENT_DATA_LOST           (1UL << 3U)

/* Event line */
#define BLE_EVENT_PORT                EXTI_PORT_C
#define BLE_EVENT_LINE                EXTI_LINE_4

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

static buffer_t buf_rx;
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
  .priority   = osPriorityNormal,
};

static osEventFlagsId_t         ble_evt;
static osEventFlags_t           ble_evt_cb;
static const osEventFlagsAttr_t ble_evt_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &ble_evt_cb,
    .cb_size   = sizeof(ble_evt_cb)
};

static ARM_DRIVER_SPI *driver_spi = &ARM_Driver_SPI_(DRIVER_SPI_NUM);

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void SPI_Callback(uint32_t event)
{
  uint32_t flag;

  switch (event) {
    case ARM_SPI_EVENT_TRANSFER_COMPLETE:
      flag = BLE_EVENT_TRANSFER_COMPLETE;
      break;

    case ARM_SPI_EVENT_DATA_LOST:
      flag = BLE_EVENT_DATA_LOST;
      break;

    default:
      flag = 0UL;
      break;
  }

  osEventFlagsSet(ble_evt, flag);
}

static void EXTI_Callback(EXTI_Line_t line)
{
  if (line == BLE_EVENT_LINE) {
    osEventFlagsSet(ble_evt, BLE_EVENT_RECEIVE);
  }
}

int32_t TransferHeader(header_t *hdr)
{
  int32_t  ret;
  uint32_t flags;

  ret = driver_spi->Transfer(hdr, hdr, sizeof(hdr));
  if (ret != ARM_DRIVER_OK) {
    return (-1);
  }

  flags = osEventFlagsWait(ble_evt,
                           BLE_EVENT_TRANSFER_COMPLETE | BLE_EVENT_DATA_LOST,
                           osFlagsWaitAny, osWaitForever);
  if (((int32_t)flags < 0) || (flags & BLE_EVENT_DATA_LOST)) {
    return (-2);
  }

  return (0);
}

static void ReceiveEvent(buffer_t *buf)
{
  int32_t  ret;
  header_t hdr;

  hdr.ctrl = BLE_READ_OPER;
  /* CS reset */
  driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
  /* Read header */
  ret = TransferHeader(&hdr);
  if ((ret == 0) && (hdr.ctrl == BLE_READY)) {
    if (hdr.rbuf_size > HEADER_SIZE) {
      hdr.rbuf_size = HEADER_SIZE;
    }
    ret = driver_spi->Receive(&buf->data[0], hdr.rbuf_size);
    if (ret == ARM_DRIVER_OK) {
      osEventFlagsWait(ble_evt, BLE_EVENT_TRANSFER_COMPLETE | BLE_EVENT_DATA_LOST,
                       osFlagsWaitAny, osWaitForever);
      buf->size = driver_spi->GetDataCount();
    }
  }
  /* Release CS line */
  driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
}

static void SendData(buffer_t *buf)
{
  int32_t  ret, result;
  header_t hdr;

  do {
    result = -1;
    hdr.ctrl = BLE_WRITE_OPER;
    /* CS reset */
    driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
    /* Read header */
    ret = TransferHeader(&hdr);
    if ((ret == 0) && (hdr.ctrl == BLE_READY)) {
      if (hdr.wbuf_size >= buf->size) {
        ret = driver_spi->Send(&buf->data[0], buf->size);
        if (ret == ARM_DRIVER_OK) {
          osEventFlagsWait(ble_evt, BLE_EVENT_TRANSFER_COMPLETE | BLE_EVENT_DATA_LOST,
              osFlagsWaitAny, osWaitForever);
          result = 0;
        }
      }
    }
    /* Release CS line */
    driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
  } while(result < 0);
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
  EXTI_SetConfigLine(BLE_EVENT_LINE, BLE_EVENT_PORT, EXTI_MODE_INTERRUPT,
                     EXTI_TRIGGER_RISING);

  for(;;) {
    flags = osEventFlagsWait(ble_evt, BLE_EVENT_RECEIVE | BLE_EVENT_SEND,
                             osFlagsWaitAny, osWaitForever);
    if ((int32_t)flags < 0) {
      DEBUG_LOG("Error of event wait %d", (int32_t)flags);
      continue;
    }

    if (flags & BLE_EVENT_RECEIVE) {
      ReceiveEvent(&buf_rx);
    }
    else if (flags & BLE_EVENT_SEND) {
      SendData(&buf_tx);
    }
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void CreateThreadBleTransportLayer(const void*)
 * @brief       Create BLE transport layer thread.
 *
 * @param[in]   pConf  Pointer to configuration struct
 */
void CreateThreadBleTransportLayer(const void* pConf)
{
  ble_evt = osEventFlagsNew(&ble_evt_attr);
  if (ble_evt != NULL) {
    osThreadNew(thread_ble_tl, (void*)pConf, &thread_attr);
  }
}

/* ----------------------------- End of file ---------------------------------*/
