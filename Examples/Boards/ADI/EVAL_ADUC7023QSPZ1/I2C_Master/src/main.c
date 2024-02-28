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
#include <asm/system_aduc7023.h>
#include <Driver/GPIO_ADUC7023.h>
#include <Driver/Driver_I2C.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (384U)

#define LED_PIN                       (GPIO_PIN_7)

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

static DRIVER_GPIO *gpio = &DRIVER_GPIO0;

extern ARM_DRIVER_I2C Driver_I2C1;
static ARM_DRIVER_I2C *i2c = &Driver_I2C1;

static bool pooling;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void I2C_Callback(uint32_t event)
{
  osEventFlagsSet(evf_i2c, event);
}

static
int32_t WaitTransfer(uint32_t data_cnt)
{
  if (pooling == false) {
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
  }
  else {
    uint32_t timeout;
    ARM_I2C_STATUS state;

    timeout = osKernelGetTickCount() + I2C_TIMEOUT;

    do {
      state = i2c->GetStatus();
      if (state.busy == 0U) {
        break;
      }
    } while (time_before(osKernelGetTickCount(), timeout));

    if (state.busy != 0U) {
      i2c->Control(ARM_I2C_BUS_CLEAR, 0U);
      return (-1);
    }

    if (state.arbitration_lost != 0U || state.bus_error != 0U) {
      return (-1);
    }

    /* Check if all data transferred */
    if (i2c->GetDataCount() != (int32_t)data_cnt) {
      return (-1);
    }
  }

  return (0);
}

static
int32_t TestTransfer(uint8_t *wr_buf, uint8_t wr_size,
                     uint8_t *rd_buf, uint8_t rd_size)
{
  int32_t rc = 0;
  bool pend = (rd_buf != NULL && rd_size != 0U) ? true : false;

  if (wr_buf != NULL && wr_size != 0U) {
    rc = i2c->MasterTransmit(SLAVE_ADDR, wr_buf, wr_size, pend);
    if (rc == ARM_DRIVER_OK) {
      /* Wait until transfer completed */
      rc = WaitTransfer(wr_size);
    }
  }

  if (rc == 0 && pend == true) {
    rc = i2c->MasterReceive(SLAVE_ADDR, rd_buf, rd_size, false);
    if (rc == ARM_DRIVER_OK) {
      /* Wait until transfer completed */
      rc = WaitTransfer(rd_size);
    }
  }

  return (rc);
}

static void GPIO_Init(void)
{
  const GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_OUTPUT,
    .pull_mode = GPIO_PULL_DISABLE,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  gpio->PinConfig(LED_PIN, &pin_cfg);
}

static void I2C_Init(void)
{
  ARM_I2C_SignalEvent_t cb_event;

  cb_event = pooling == false ? I2C_Callback : NULL;

  /* Initialize I2C Driver */
  i2c->Initialize(cb_event);
  /* Configure I2C Driver */
  i2c->PowerControl(ARM_POWER_FULL);
  i2c->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);
}

__NO_RETURN
static void main_proc(void *param)
{
  (void) param;

  pooling = false;

  GPIO_Init();
  I2C_Init();

  osTimerStart(timer_id, TIMEOUT);

  uint8_t wr_buf[] = {0U};
  uint8_t rd_buf[16];

  for (;;) {
    TestTransfer(&wr_buf[0], sizeof(wr_buf), &rd_buf[0], sizeof(rd_buf));
    osDelay(5U);
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
