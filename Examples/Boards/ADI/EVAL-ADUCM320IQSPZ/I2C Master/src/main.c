/*
 * Copyright (C) 2023-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include <Driver/GPIO_ADUCM32x.h>
#include "Driver/Driver_I2C.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (384U)

#define LED_PIN                       (GPIO_PIN_4)

#define SLAVE_ADDR                    (0xA0 >> 1U)
#define I2C_TIMEOUT                   (50U)

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

static osEventFlagsId_t         evf_i2c;
static osEventFlags_t           evf_i2c_cb;
static const osEventFlagsAttr_t evf_i2c_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &evf_i2c_cb,
    .cb_size   = sizeof(evf_i2c_cb)
};

static Driver_GPIO_t *gpio = &Driver_GPIO2;

extern ARM_DRIVER_I2C Driver_I2C0;
static ARM_DRIVER_I2C *i2c = &Driver_I2C0;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void I2C_Callback(uint32_t event)
{
  osEventFlagsSet(evf_i2c, event);
}

static
int32_t WaitTransferEvent(void)
{
  uint32_t flags;

  flags = osEventFlagsWait(evf_i2c,
                           ARM_I2C_EVENT_TRANSFER_DONE       |
                           ARM_I2C_EVENT_TRANSFER_INCOMPLETE |
                           ARM_I2C_EVENT_ADDRESS_NACK        |
                           ARM_I2C_EVENT_ARBITRATION_LOST    |
                           ARM_I2C_EVENT_BUS_ERROR,
                           osFlagsWaitAny,
                           I2C_TIMEOUT);
  if ((flags & osFlagsError) != 0U) {
    if (flags == osFlagsErrorTimeout) {
      i2c->Control(ARM_I2C_BUS_CLEAR, 0U);
    }
    return (-1);
  }

  /* Check if all data transferred */
  if ((flags & ~ARM_I2C_EVENT_TRANSFER_DONE) != 0U) {
    return (-1);
  }

  return (0);
}

static
int32_t TestTransferEvent(uint8_t *wr_buf, uint8_t wr_size,
                          uint8_t *rd_buf, uint8_t rd_size)
{
  int32_t rc = 0;
  bool pend = (rd_buf != NULL && rd_size != 0U) ? true : false;

  if (wr_buf != NULL && wr_size != 0U) {
    rc = i2c->MasterTransmit(SLAVE_ADDR, wr_buf, wr_size, pend);
    if (rc == ARM_DRIVER_OK) {
      /* Wait until transfer completed */
      rc = WaitTransferEvent();
    }
  }

  if (rc == 0 && pend == true) {
    rc = i2c->MasterReceive(SLAVE_ADDR, rd_buf, rd_size, false);
    if (rc == ARM_DRIVER_OK) {
      /* Wait until transfer completed */
      rc = WaitTransferEvent();
    }
  }

  return (rc);
}

static
int32_t WaitTransferPool(void)
{
  uint32_t timeout;
  ARM_I2C_STATUS state;
  int32_t rc = 0;

  timeout = osKernelGetTickCount() + I2C_TIMEOUT;

  do {
    state = i2c->GetStatus();
    if (state.busy == 0U) {
      break;
    }
  } while (time_before(osKernelGetTickCount(), timeout));

  if (state.busy != 0U) {
    i2c->Control(ARM_I2C_BUS_CLEAR, 0U);
    rc = -1;
  }

  if (state.arbitration_lost != 0U || state.bus_error != 0U) {
    rc = -1;
  }

  return (rc);
}

static
int32_t TestTransferPool(uint8_t *wr_buf, uint8_t wr_size,
                         uint8_t *rd_buf, uint8_t rd_size)
{
  int32_t rc;
  bool pend = (rd_buf != NULL && rd_size != 0U) ? true : false;

  if (wr_buf != NULL && wr_size != 0U) {
    rc = i2c->MasterTransmit(SLAVE_ADDR, wr_buf, wr_size, pend);
    if (rc == ARM_DRIVER_OK) {
      /* Wait until transfer completed */
      rc = WaitTransferPool();
    }
  }

  /* Check if all data transferred */
  if (i2c->GetDataCount() != wr_size) {
    rc = -1;
  }

  if (rc == 0 && pend == true) {
    rc = i2c->MasterReceive(SLAVE_ADDR, rd_buf, rd_size, false);
    if (rc == ARM_DRIVER_OK) {
      /* Wait until transfer completed */
      rc = WaitTransferPool();
    }
  }

  /* Check if all data transferred */
  if (i2c->GetDataCount() != rd_size) {
    rc = -1;
  }

  return (rc);
}

static void GPIO_Init(void)
{
  const GPIO_PIN_CFG_t led_cfg = {
    .func = GPIO_PIN_FUNC_0,
    .mode = GPIO_MODE_OUT_PP,
    .pull = GPIO_PULL_DISABLE
  };

  gpio->PinConfig(LED_PIN, &led_cfg);
}

__NO_RETURN
static void main_proc(void *param)
{
  (void) param;
  bool pooling;

  GPIO_Init();
  osTimerStart(timer_id, TIMEOUT);

  pooling = false;

  /* Initialize I2C Driver */
  if (pooling == false) {
    i2c->Initialize(I2C_Callback);
  }
  else {
    i2c->Initialize(NULL);
  }
  /* Configure I2C Driver */
  i2c->PowerControl(ARM_POWER_FULL);
  i2c->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);

  uint8_t wr_buf[] = {0U};
  uint8_t rd_buf[16];

  for (;;) {
    if (pooling == false) {
      TestTransferEvent(&wr_buf[0], sizeof(wr_buf), &rd_buf[0], sizeof(rd_buf));
    }
    else {
      TestTransferPool(&wr_buf[0], sizeof(wr_buf), &rd_buf[0], sizeof(rd_buf));
    }
    osDelay(5U);
  }
}

static void timer_proc(void *argument)
{
  (void) argument;

  gpio->PinToggle(LED_PIN);
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

    evf_i2c = osEventFlagsNew(&evf_i2c_attr);
    if (evf_i2c == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
