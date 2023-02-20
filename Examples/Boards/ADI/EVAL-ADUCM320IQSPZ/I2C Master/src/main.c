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


#include <stddef.h>
#include <Kernel/kernel.h>
#include <asm/system_aducm32x.h>
#include <Driver/GPIO_ADUCM32x.h>
#include "CMSIS/Driver/Driver_I2C.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (256U)

#define LED_PIN                       (GPIO_PIN_4)

#define SLAVE_ADDR                    (0xA0 >> 1U)
#define I2C_TIMEOUT                   (50U)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t init_id;
static osThread_t   init_cb;
static uint64_t     init_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t init_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &init_cb,
    .cb_size    = sizeof(init_cb),
    .stack_mem  = &init_stack[0],
    .stack_size = sizeof(init_stack),
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

static uint8_t test_rd_buf[3];

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
int32_t Read_Reg_Event(uint8_t reg_num, uint8_t *buf, uint8_t size)
{
  uint32_t flags;

  i2c->MasterTransmit(SLAVE_ADDR, &reg_num, sizeof(reg_num), true);
  /* Wait until transfer completed */
  flags = osEventFlagsWait(evf_i2c,
                           ARM_I2C_EVENT_TRANSFER_DONE |
                           ARM_I2C_EVENT_TRANSFER_INCOMPLETE,
                           osFlagsWaitAny,
                           I2C_TIMEOUT);
  /* Check if all data transferred */
  if ((flags & ARM_I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
    return (-1);
  }

  i2c->MasterReceive(SLAVE_ADDR, buf, size, false);
  /* Wait until transfer completed */
  flags = osEventFlagsWait(evf_i2c,
                           ARM_I2C_EVENT_TRANSFER_DONE |
                           ARM_I2C_EVENT_TRANSFER_INCOMPLETE,
                           osFlagsWaitAny,
                           I2C_TIMEOUT);
  /* Check if all data transferred */
  if ((flags & ARM_I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
    return (-1);
  }

  return (0U);
}

static
int32_t Read_Reg_Pool(uint8_t reg_num, uint8_t *buf, uint8_t size)
{
  i2c->MasterTransmit(SLAVE_ADDR, &reg_num, sizeof(reg_num), true);
  /* Wait until transfer completed */
  while (i2c->GetStatus().busy != 0U);
  /* Check if all data transferred */
  if (i2c->GetDataCount() != sizeof(reg_num)) {
    return (-1);
  }

  i2c->MasterReceive(SLAVE_ADDR, buf, size, false);
  /* Wait until transfer completed */
  while (i2c->GetStatus().busy != 0U);
  /* Check if all data transferred */
  if (i2c->GetDataCount() != size) {
    return (-1);
  }

  return (0U);
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

__NO_RETURN static void main_proc(void *param)
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

  for (;;) {
    if (pooling == false) {
      Read_Reg_Event(0x00, &test_rd_buf[0], sizeof(test_rd_buf));
    }
    else {
      Read_Reg_Pool(0x00, &test_rd_buf[0], sizeof(test_rd_buf));
    }
    osDelay(10U);
  }
}

static void timer_func(void *argument)
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
    init_id = osThreadNew(main_proc, NULL, &init_attr);
    if (init_id == NULL) {
      goto error;
    }

    timer_id = osTimerNew(timer_func, osTimerPeriodic, NULL, &timer_attr);
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
