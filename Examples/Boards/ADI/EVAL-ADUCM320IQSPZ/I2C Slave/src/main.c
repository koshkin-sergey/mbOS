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

#include <Kernel/kernel.h>
#include <asm/system_aducm32x.h>
#include <Driver/GPIO_ADUCM32x.h>
#include "CMSIS/Driver/Driver_I2C.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STACK_SIZE             (256U)

#define LED_PIN                       (GPIO_PIN_4)
#define LED_TIMEOUT                   (500UL)

#define SLAVE_ADDR                    (0xA0 >> 1U)

#define I2C_XFER_TRANSMIT             (0U)
#define I2C_XFER_RECEIVE              (1U)

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

static Driver_GPIO_t *gpio = &Driver_GPIO2;

extern ARM_DRIVER_I2C Driver_I2C0;
static ARM_DRIVER_I2C *i2c = &Driver_I2C0;

static uint8_t mem_page[128] = {0U};
static uint8_t offset;
static uint8_t rd_buf[4] = {0U};
static uint32_t last_xfer;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void I2C_Callback(uint32_t event)
{
  if ((event & ARM_I2C_EVENT_SLAVE_RECEIVE) != 0U) {
    uint8_t *buf_ptr;
    uint32_t buf_size;

    if (last_xfer == I2C_XFER_TRANSMIT) {
      buf_ptr = &offset;
      buf_size = sizeof(offset);
    }
    else {
      buf_ptr = &rd_buf[0];
      buf_size = sizeof(rd_buf);
    }
    i2c->SlaveReceive(buf_ptr, buf_size);
  }
  else if ((event & ARM_I2C_EVENT_TRANSFER_DONE) != 0U) {
    int32_t count = i2c->GetDataCount();
    ARM_I2C_STATUS status = i2c->GetStatus();

    if (last_xfer == I2C_XFER_RECEIVE && status.direction == I2C_XFER_RECEIVE) {
      last_xfer = I2C_XFER_TRANSMIT;
      for (int32_t i = 0; i < count; ++i) {
        mem_page[(offset + (uint8_t)i) & 0x7FU] = rd_buf[i];
      }
    }
    else {
      last_xfer = status.direction;
    }

    if (last_xfer == I2C_XFER_TRANSMIT) {
      offset += (uint8_t)count;
    }
    offset &= 0x7FU;

    i2c->SlaveTransmit(&mem_page[offset], sizeof(mem_page) - offset);
  }
}

static void GPIO_Init(void)
{
  static const GPIO_PIN_CFG_t led_cfg = {
    .func = GPIO_PIN_FUNC_0,
    .mode = GPIO_MODE_OUT_PP,
    .pull = GPIO_PULL_DISABLE
  };

  gpio->PinConfig(LED_PIN, &led_cfg);
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

  last_xfer = I2C_XFER_TRANSMIT;
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
