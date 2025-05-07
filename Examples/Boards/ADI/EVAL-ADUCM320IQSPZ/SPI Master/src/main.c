/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <stddef.h>
#include <Kernel/kernel.h>
#include <asm/system_aducm32x.h>
#include <Driver/Driver_GPIO.h>
#include <Driver/Driver_SPI.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (384U)

#define CS_PIN                        (GPIO_PIN_3)
#define LED_PIN                       (GPIO_PIN_4)

#define SPI_TIMEOUT                   (50U)
#define SPI_BUS_SPEED                 (10000000U)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t         thread_id;
static osThread_t           thread_cb;
static uint64_t             thread_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t thread_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &thread_cb,
    .cb_size    = sizeof(thread_cb),
    .stack_mem  = &thread_stack[0],
    .stack_size = sizeof(thread_stack),
    .priority   = osPriorityNormal,
};

static osTimerId_t         timer_id;
static osTimer_t           timer_cb;
static const osTimerAttr_t timer_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer_cb,
    .cb_size   = sizeof(timer_cb)
};

static osEventFlagsId_t         evf_spi;
static osEventFlags_t           evf_spi_cb;
static const osEventFlagsAttr_t evf_spi_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &evf_spi_cb,
    .cb_size   = sizeof(evf_spi_cb)
};

extern Driver_GPIO_t Driver_GPIO1;
static Driver_GPIO_t *gpio_cs = &Driver_GPIO1;

extern Driver_GPIO_t Driver_GPIO2;
static Driver_GPIO_t *gpio_led = &Driver_GPIO2;

extern DRIVER_SPI Driver_SPI1;
static DRIVER_SPI *spi = &Driver_SPI1;

static bool pooling;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void SPI_Callback(uint32_t event)
{
  if ((event & SPI_EVENT_DATA_LOST) != 0U) {
    spi->Control(SPI_ABORT_TRANSFER, 0U);
  }

  osEventFlagsSet(evf_spi, event);
}

static
int32_t WaitTransfer(uint32_t data_cnt)
{
  if (pooling == false) {
    uint32_t flags;

    flags = osEventFlagsWait(evf_spi,
                             SPI_EVENT_TRANSFER_COMPLETE |
                             SPI_EVENT_DATA_LOST         |
                             SPI_EVENT_MODE_FAULT,
                             osFlagsWaitAny,
                             SPI_TIMEOUT);
    if ((flags & osFlagsError) != 0U) {
      if (flags == osFlagsErrorTimeout) {
        spi->Control(SPI_ABORT_TRANSFER, 0U);
      }
      return (-1);
    }

    /* Check if all data transferred */
    if ((flags & ~SPI_EVENT_TRANSFER_COMPLETE) != 0U) {
      return (-1);
    }
  }
  else {
    uint32_t timeout;
    SPI_STATUS state;

    timeout = osKernelGetTickCount() + SPI_TIMEOUT;

    do {
      state = spi->GetStatus();
      if (state.busy == 0U) {
        break;
      }
    } while (time_before(osKernelGetTickCount(), timeout));

    if (state.busy != 0U) {
      spi->Control(SPI_ABORT_TRANSFER, 0U);
      return (-1);
    }

    if (state.data_lost != 0U || state.mode_fault != 0U) {
      return (-1);
    }

    /* Check if all data transferred */
    if (spi->GetDataCount() != data_cnt) {
      return (-1);
    }
  }

  return (0);
}

static
int32_t TestTransfer(uint8_t *wr_buf, uint8_t *rd_buf, uint32_t size)
{
  int32_t rc = 0;

  if (size > 0U) {
    /* Chip Select active */
    gpio_cs->PinWrite(CS_PIN, GPIO_PIN_OUT_LOW);

    if (wr_buf != NULL && rd_buf != NULL) {
      /* Transfer */
      spi->Transfer(wr_buf, rd_buf, size);
    }
    else if (wr_buf != NULL) {
      /* Send */
      spi->Send(wr_buf, size);
    }
    else if (rd_buf != NULL) {
      /* Receive */
      spi->Receive(rd_buf, size);
    }

    /* Wait until transfer completed */
    rc = WaitTransfer(size);

    /* Chip Select inactive */
    gpio_cs->PinWrite(CS_PIN, GPIO_PIN_OUT_HIGH);
  }

  return (rc);
}

static void GPIO_Init(void)
{
  const GPIO_PIN_CFG_t gpio_cfg = {
    .func = GPIO_PIN_FUNC_0,
    .mode = GPIO_MODE_OUT_PP,
    .pull = GPIO_PULL_DISABLE
  };

  gpio_cs->PinConfig(CS_PIN, &gpio_cfg);
  gpio_led->PinConfig(LED_PIN, &gpio_cfg);

  gpio_cs->PinWrite(CS_PIN, GPIO_PIN_OUT_HIGH);
}

static void SPI_Init(void)
{
  SPI_SignalEvent_t cb_event;

  cb_event = pooling == false ? SPI_Callback : NULL;

  /* Initialize SPI Driver */
  spi->Initialize(cb_event);
  /* Configure SPI Driver */
  spi->PowerControl(POWER_FULL);
  spi->Control(SPI_MODE_MASTER   |
               SPI_CPOL1_CPHA1   |
               SPI_DATA_BITS(8U) |
               SPI_MSB_LSB       |
               SPI_SS_MASTER_UNUSED,
               SPI_BUS_SPEED);
}

__NO_RETURN
static void main_proc(void *param)
{
  (void) param;

  pooling = false;

  GPIO_Init();
  SPI_Init();

  osTimerStart(timer_id, TIMEOUT);

  static uint8_t wr_buf[6] = {0x90U};
  static uint8_t rd_buf[sizeof(wr_buf)] = {0U};

  for (;;) {
    TestTransfer(&wr_buf[0], &rd_buf[0], sizeof(wr_buf));
    osDelay(1U);
  }
}

static void timer_proc(void *argument)
{
  (void) argument;

  gpio_led->PinToggle(LED_PIN);
}

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();

  status = osKernelInitialize();
  if (status == osOK) {
    thread_id = osThreadNew(main_proc, NULL, &thread_attr);
    if (thread_id == NULL) {
      goto error;
    }

    timer_id = osTimerNew(timer_proc, osTimerPeriodic, NULL, &timer_attr);
    if (timer_id == NULL) {
      goto error;
    }

    evf_spi = osEventFlagsNew(&evf_spi_attr);
    if (evf_spi == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
