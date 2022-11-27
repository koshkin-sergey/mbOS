/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <asm/krechet1.h>
#include <Kernel/kernel.h>
#include <CMSIS/Driver/Driver_I2C.h>
#include <Driver/ADSU_KRECHET1.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define LED0_R                        (1UL << 24U)
#define LED0_G                        (1UL << 25U)
#define LED0_B                        (1UL << 26U)
#define LED1_R                        (1UL << 27U)
#define LED1_G                        (1UL << 28U)
#define LED1_B                        (1UL << 29U)

#define SLAVE_ADDR                    (0xA0 >> 1U)
#define I2C_TIMEOUT                   (50U)
#define LED_TIMEOUT                   (500U)
#define THREAD_STACK_SIZE             (256U)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

extern Driver_ADSU_t Driver_ADSU;
static Driver_ADSU_t *adsu = &Driver_ADSU;

extern ARM_DRIVER_I2C Driver_I2C0;
static ARM_DRIVER_I2C *i2c = &Driver_I2C0;

static osThreadId_t init_id;
static osThread_t   init_cb;
static uint64_t     init_stack[THREAD_STACK_SIZE/8U] __attribute__((section(".bss.os.thread.stack")));
static const osThreadAttr_t init_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &init_cb,
    .cb_size    = sizeof(init_cb),
    .stack_mem  = &init_stack[0],
    .stack_size = sizeof(init_stack),
    .priority   = osPriorityNormal,
};

static osTimerId_t         timer1;
static osTimer_t           timer1_cb;
static const osTimerAttr_t timer1_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer1_cb,
    .cb_size   = sizeof(timer1_cb)
};

static osEventFlagsId_t         evf_i2c;
static osEventFlags_t           evf_i2c_cb;
static const osEventFlagsAttr_t evf_i2c_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &evf_i2c_cb,
    .cb_size   = sizeof(evf_i2c_cb)
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void I2C_Callback(uint32_t event)
{
  osEventFlagsSet(evf_i2c, event);
}

static void GPIO_Init(void)
{
  adsu->PeriphEnable(ADSU_Periph_GPIO);

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_DIR_REG, LED1_G);
}

void i2c_write(const uint8_t *buf, size_t size, bool xfer_pending)
{
  int32_t ret;

  ret = i2c->MasterTransmit(SLAVE_ADDR, buf, size, xfer_pending);
  if (ret == ARM_DRIVER_OK) {
    osEventFlagsWait(
        evf_i2c,
        ARM_I2C_EVENT_TRANSFER_DONE       |
        ARM_I2C_EVENT_TRANSFER_INCOMPLETE |
        ARM_I2C_EVENT_ADDRESS_NACK        |
        ARM_I2C_EVENT_ARBITRATION_LOST    |
        ARM_I2C_EVENT_BUS_ERROR,
        osFlagsWaitAny,
        I2C_TIMEOUT);
  }
}

void i2c_read(uint8_t *buf, size_t size)
{
  int32_t ret;

  ret = i2c->MasterReceive(SLAVE_ADDR, buf, size, false);
  if (ret == ARM_DRIVER_OK) {
    osEventFlagsWait(
        evf_i2c,
        ARM_I2C_EVENT_TRANSFER_DONE       |
        ARM_I2C_EVENT_TRANSFER_INCOMPLETE |
        ARM_I2C_EVENT_ADDRESS_NACK        |
        ARM_I2C_EVENT_ARBITRATION_LOST    |
        ARM_I2C_EVENT_BUS_ERROR,
        osFlagsWaitAny,
        I2C_TIMEOUT);
  }
}

static void init_proc(void *param)
{
  (void) param;
  uint8_t addr[] = {0U};
  uint8_t buf[]  = {1U,2U,3U,4U};

  GPIO_Init();

  /* Initialize I2C Driver */
  i2c->Initialize(I2C_Callback);
  /* Configure I2C Driver */
  i2c->PowerControl(ARM_POWER_FULL);
  i2c->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);

  osTimerStart(timer1, LED_TIMEOUT);

  for (;;) {
    i2c_write(&addr[0], sizeof(addr), true);
    i2c_read(&buf[0], sizeof(buf));
    osDelay(2U);
  }
}

static void timer1_func(void *argument)
{
  (void) argument;

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_OUT_REG, __get_PeriphReg(GPIO_OUT_REG) ^ LED1_G);
}

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();

  status = osKernelInitialize();
  if (status == osOK) {
    init_id = osThreadNew(init_proc, NULL, &init_attr);
    if (init_id == NULL) {
        goto error;
    }

    timer1 = osTimerNew(timer1_func, osTimerPeriodic, NULL, &timer1_attr);
    if (timer1 == NULL) {
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
