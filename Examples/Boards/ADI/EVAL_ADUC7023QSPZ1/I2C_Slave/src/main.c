/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
#include <asm/system_aduc7023.h>
#include <Driver/GPIO_ADUC7023.h>
#include "Driver/Driver_I2C.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STACK_SIZE             (256U)

#define LED_PIN                       (GPIO_PIN_7)
#define LED_TIMEOUT                   (500UL)

#define SLAVE_ADDR                    (0xA0 >> 1U)

#define I2C_XFER_TRANSMIT             (0U)
#define I2C_XFER_RECEIVE              (1U)

/* RX Buffer Size */
#define RX_BUF_SIZE                   (128)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef enum XferMode {
  XferModeNone = 0,
  XferModeAddr = 1,
  XferModeReserved = 0x7FFFFFFF
} XferMode_t;

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

static DRIVER_GPIO *gpio = &DRIVER_GPIO0;

extern ARM_DRIVER_I2C Driver_I2C1;
static ARM_DRIVER_I2C *i2c = &Driver_I2C1;

static uint8_t offset = 0U;
static uint8_t mem_page[128] = {0U};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void I2C_Callback(uint32_t event)
{
  static XferMode_t xfer_mode = XferModeNone;
  static uint8_t rd_buf[RX_BUF_SIZE] = {0U};

  if ((event & ARM_I2C_EVENT_SLAVE_RECEIVE) != 0U) {
    uint32_t size;

    i2c->Control(ARM_I2C_ABORT_TRANSFER, 0U);

    if (xfer_mode == XferModeNone) {
      size = sizeof(rd_buf[0]);
      xfer_mode = XferModeAddr;
    }
    else {
      size = RX_BUF_SIZE;
      xfer_mode = XferModeNone;
    }
    i2c->SlaveReceive(&rd_buf[0], size);
  }
  else if ((event & ARM_I2C_EVENT_TRANSFER_DONE) != 0U) {
    int32_t count = i2c->GetDataCount();
    ARM_I2C_STATUS status = i2c->GetStatus();

    if (count > 0) {
      if (status.direction == I2C_XFER_RECEIVE) {
        if (xfer_mode == XferModeAddr) {
          /* Received address from host */
          offset = rd_buf[0] & 0x7FU;
        }
        else {
          /* Received data from host */
          for (int32_t i = 0; i < count; ++i) {
            mem_page[offset] = rd_buf[i];
            offset = (offset + 1U) & 0x7FU;
          }
        }
      }
      else {
        /* Transmitted data to host */
        offset = (uint8_t)(offset + count) & 0x7FU;
        xfer_mode = XferModeNone;
      }
    }

    i2c->SlaveTransmit(&mem_page[offset], sizeof(mem_page) - offset);
  }
}

static void GPIO_Init(void)
{
  static const GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_OUTPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  gpio->PinConfig(LED_PIN, &pin_cfg);
}

static
void main_proc(void *param)
{
  (void) param;

  GPIO_Init();
  osTimerStart(timer_id, LED_TIMEOUT);

  /* Initialize I2C Driver */
  i2c->Initialize(I2C_Callback);
  /* Configure I2C Driver */
  i2c->PowerControl(ARM_POWER_FULL);
  i2c->Control(ARM_I2C_OWN_ADDRESS, SLAVE_ADDR);

  i2c->SlaveTransmit(&mem_page[offset], sizeof(mem_page));
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

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
