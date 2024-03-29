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
#include <BLE/ble.h>
#include <asm/GPIO_STM32F7xx.h>
#include <asm/EXTI_STM32F7xx.h>
#include <Driver/Driver_SPI.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STK_SIZE               512U
#define DRIVER_SPI_NUM                1
#define HEADER_SIZE                   5U

/* Event flags */
#define FLAG_RECEIVE                  (1UL << 0U)
#define FLAG_TRANSFER_COMPLETE        (1UL << 1U)

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

typedef __PACKED_STRUCT header_s {
  uint8_t ctrl;
  uint16_t wbuf_size;
  uint16_t rbuf_size;
} header_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t         thread;
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

static osSemaphoreId_t  sem_spi;
static osSemaphore_t    sem_spi_cb;
static const osSemaphoreAttr_t  sem_spi_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &sem_spi_cb,
  .cb_size   = sizeof(sem_spi_cb)
};

static osEventFlagsId_t         evt_flags;
static osEventFlags_t           evt_flags_cb;
static const osEventFlagsAttr_t evt_flags_attr = {
  .name      = NULL,
  .attr_bits = 0U,
  .cb_mem    = &evt_flags_cb,
  .cb_size   = sizeof(evt_flags_cb)
};

static ARM_DRIVER_SPI *driver_spi = &ARM_Driver_SPI_(DRIVER_SPI_NUM);

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void SPI_Callback(uint32_t event)
{
  if (event & ARM_SPI_EVENT_TRANSFER_COMPLETE) {
    osEventFlagsSet(evt_flags, FLAG_TRANSFER_COMPLETE);
  }
}

static void EXTI_Callback(EXTI_Line_t line)
{
  if (line == BLE_EXTI_LINE) {
    osEventFlagsSet(evt_flags, FLAG_RECEIVE);
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

  EXTI_Initialize(EXTI_Callback);
  EXTI_SetConfigLine(BLE_EXTI_LINE, BLE_EXTI_PORT, EXTI_MODE_INTERRUPT,
                     EXTI_TRIGGER_RISING);
}

static int32_t TransferHeader(header_t *hdr)
{
  int32_t  ret;
  uint32_t flags;

  ret = driver_spi->Transfer(hdr, hdr, sizeof(header_t));
  if (ret != ARM_DRIVER_OK) {
    return (-1);
  }

  flags = osEventFlagsWait(evt_flags, FLAG_TRANSFER_COMPLETE, osFlagsWaitAny,
                           osWaitForever);
  if ((int32_t)flags < 0) {
    return (-2);
  }

  return (0);
}

static void CS_Active(void)
{
  osSemaphoreAcquire(sem_spi, osWaitForever);
  driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
}

static void CS_Inactive(void)
{
  driver_spi->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
  osSemaphoreRelease(sem_spi);
}

static uint32_t isEventAvailable(void)
{
  return GPIO_PinRead(BLE_EVENT_PORT, BLE_EVENT_PIN);
}

__NO_RETURN static
void thread_ble_tl(void *param)
{
  int32_t       ret;
  uint32_t      flags;
  header_t      hdr;
  hci_packet_t *packet;
  HCI_TL_InitConf_t *cfg = (HCI_TL_InitConf_t *)param;

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

  for(;;) {
    flags = osEventFlagsWait(evt_flags, FLAG_RECEIVE, osFlagsWaitAny, osWaitForever);
    if ((int32_t)flags < 0) {
      DEBUG_LOG("Error of event wait %d", (int32_t)flags);
      continue;
    }

    while(isEventAvailable()) {
      packet = cfg->MemoryAlloc();
      if (packet != NULL) {
        hdr.ctrl = BLE_READ_OPER;
        /* CS reset */
        CS_Active();
        /* Read header */
        ret = TransferHeader(&hdr);
        if ((ret == 0) && (hdr.ctrl == BLE_READY) && (hdr.rbuf_size > 0U)) {
          if (hdr.rbuf_size > cfg->hci_packet_size) {
            hdr.rbuf_size = cfg->hci_packet_size;
          }
          ret = driver_spi->Receive(packet, hdr.rbuf_size);
          if (ret == ARM_DRIVER_OK) {
            osEventFlagsWait(evt_flags, FLAG_TRANSFER_COMPLETE, osFlagsWaitAny,
                osWaitForever);
          }
        }
        else {
          ret = ARM_DRIVER_ERROR;
        }
        /* Release CS line */
        CS_Inactive();

        if (ret == ARM_DRIVER_OK) {
          cfg->EvtRxCallback(packet);
        }
        else {
          cfg->MemoryFree(packet);
        }
      }
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
 * @return      Execution Status
 */
int32_t BLE_InitTransportLayer(const void* pConf)
{
  int32_t status;

  /* Initialize reset pin */
  ResetPinConfig();
  /* Initialize event pin */
  EventPinConfig();
  /* Create Event Flag */
  evt_flags = osEventFlagsNew(&evt_flags_attr);
  /* Create Semaphore */
  sem_spi = osSemaphoreNew(1U, 1U, &sem_spi_attr);
  /* Create Thread */
  thread = osThreadNew(thread_ble_tl, (void*)pConf, &thread_attr);

  if ((evt_flags == NULL) || (sem_spi == NULL) || (thread == NULL)) {
    BLE_DeInit();
    status = BLE_TL_ERROR;
    DEBUG_LOG("Error creating thread for BLE transport layer\r\n");
  }
  else {
    status = BLE_TL_OK;
  }

  return (status);
}

/**
 * @fn          int32_t BLE_DeInit(void)
 * @brief       DeInitializes the peripherals communication with the Bluetooth
                module (via SPI, I2C, USART, ...)
 *
 * @return      Execution Status
 */
int32_t BLE_DeInit(void)
{
  /* Delete Thread */
  if (thread != NULL) {
    osThreadTerminate(thread);
  }
  /* Delete Event Flag */
  if (evt_flags != NULL) {
    osEventFlagsDelete(evt_flags);
  }
  /* Delete Semaphore */
  if (sem_spi != NULL) {
    osSemaphoreDelete(sem_spi);
  }

  return (BLE_TL_OK);
}

/**
 * @fn          int32_t BLE_Reset(void)
 * @brief       Reset BlueNRG module.
 *
 * @return      0
 */
int32_t BLE_Reset(void)
{
  GPIO_PinWrite(BLE_RESET_PORT, BLE_RESET_PIN, GPIO_PIN_OUT_LOW);
  osDelay(100);
  GPIO_PinWrite(BLE_RESET_PORT, BLE_RESET_PIN, GPIO_PIN_OUT_HIGH);
  osDelay(5);

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
  int32_t  ret, result, sent = 0U;
  header_t hdr;
  uint32_t cnt = 0U;

  do {
    result = -1;
    ++cnt;
    hdr.ctrl = BLE_WRITE_OPER;
    /* CS reset */
    CS_Active();
    /* Read header */
    ret = TransferHeader(&hdr);
    if ((ret == 0) && (hdr.ctrl == BLE_READY)) {
      if (hdr.wbuf_size >= size) {
        ret = driver_spi->Send(buf, size);
        if (ret == ARM_DRIVER_OK) {
          osEventFlagsWait(evt_flags, FLAG_TRANSFER_COMPLETE, osFlagsWaitAny,
                           osWaitForever);
          sent = driver_spi->GetDataCount();
          result = 0;
        }
      }
    }
    /* Release CS line */
    CS_Inactive();
    if (result != 0) {
      osDelay(1);
    }
  } while((result != 0) && (cnt < 10U));

  return (sent);
}
#if 0
/**
 * @fn          int32_t HCI_GetEvent(hci_event_t*, opcode_t)
 * @brief       Get HCI Event.
 *
 * @param[out]  event   Pointer to Event buffer.
 * @param[in]   opcode
 * @return      Execution Status
 */
int32_t HCI_GetEvent(hci_event_t *event, opcode_t opcode)
{
  hci_packet_t *packet;
  osStatus_t    status;

  (void)opcode;

  if (event == NULL) {
    return (BLE_TL_ERROR);
  }

  status = osDataQueueGet(que_event, &packet, osWaitForever);
  if (status != osOK) {
    return (BLE_TL_ERROR);
  }

  memcpy(event, &packet->event, sizeof(hci_event_t));
  osMemoryPoolFree(event_pool, packet);

  return (BLE_TL_OK);
}

/**
 * @fn          int32_t HCI_GetCmdEvent(hci_event_t*, opcode_t)
 * @brief       Get HCI Command Event.
 *
 * @param[out]  event   Pointer to Event buffer.
 * @param[in]   opcode
 * @return      Execution Status
 */
int32_t HCI_GetCmdEvent(hci_event_t *event, opcode_t opcode)
{
  hci_packet_t *packet;
  osStatus_t    status;

  (void)opcode;

  if (event == NULL) {
    return (BLE_TL_ERROR);
  }

  status = osDataQueueGet(que_cmd_event, &packet, osWaitForever);
  if (status != osOK) {
    return (BLE_TL_ERROR);
  }

  memcpy(event, &packet->event, sizeof(hci_event_t));
  osMemoryPoolFree(event_pool, packet);

  return (BLE_TL_OK);
}
#endif
/* ----------------------------- End of file ---------------------------------*/
