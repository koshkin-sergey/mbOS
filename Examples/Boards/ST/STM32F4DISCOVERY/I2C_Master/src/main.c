/*
 * Copyright (C) 2021-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <Driver/GPIO_STM32F4xx.h>
#include <Driver/RCC_STM32F4xx.h>
#include <asm/system_stm32f4xx.h>
#include <Kernel/kernel.h>
#include <Driver/Driver_I2C.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (512U)

#define LED_PORT                      GPIO_PORT_D
#define LED_GREEN                     GPIO_PIN_12
#define LED_RED                       GPIO_PIN_14

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

extern ARM_DRIVER_I2C Driver_I2C1;
static ARM_DRIVER_I2C *i2c = &Driver_I2C1;

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void I2C_Callback(uint32_t event)
{
  osEventFlagsSet(evf_i2c, event);
}

static
int32_t TestTransferEvent(uint8_t *wr_buf, uint8_t wr_size,
                          uint8_t *rd_buf, uint8_t rd_size)
{
  uint32_t flags;

  i2c->MasterTransmit(SLAVE_ADDR, wr_buf, wr_size, true);
  /* Wait until transfer completed */
  flags = osEventFlagsWait(evf_i2c,
                           ARM_I2C_EVENT_TRANSFER_DONE |
                           ARM_I2C_EVENT_TRANSFER_INCOMPLETE,
                           osFlagsWaitAny,
                           I2C_TIMEOUT);
  /* Check if all data transferred */
  if ((flags & (ARM_I2C_EVENT_TRANSFER_INCOMPLETE | osFlagsError)) != 0U) {
    return (-1);
  }

  i2c->MasterReceive(SLAVE_ADDR, rd_buf, rd_size, false);
  /* Wait until transfer completed */
  flags = osEventFlagsWait(evf_i2c,
                           ARM_I2C_EVENT_TRANSFER_DONE |
                           ARM_I2C_EVENT_TRANSFER_INCOMPLETE,
                           osFlagsWaitAny,
                           I2C_TIMEOUT);
  /* Check if all data transferred */
  if ((flags & (ARM_I2C_EVENT_TRANSFER_INCOMPLETE | osFlagsError)) != 0U) {
    return (-1);
  }

  return (0U);
}

static
int32_t TestTransferPool(uint8_t *wr_buf, uint8_t wr_size,
                         uint8_t *rd_buf, uint8_t rd_size)
{
  i2c->MasterTransmit(SLAVE_ADDR, wr_buf, wr_size, true);
  /* Wait until transfer completed */
  while (i2c->GetStatus().busy != 0U);
  /* Check if all data transferred */
  if (i2c->GetDataCount() != wr_size) {
    return (-1);
  }

  i2c->MasterReceive(SLAVE_ADDR, rd_buf, rd_size, false);
  /* Wait until transfer completed */
  while (i2c->GetStatus().busy != 0U);
  /* Check if all data transferred */
  if (i2c->GetDataCount() != rd_size) {
    return (-1);
  }

  return (0U);
}

__NO_RETURN
static void main_proc(void *param)
{
  (void) param;
  bool pooling;

  osTimerStart(timer_id, TIMEOUT);

  pooling = true;

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
    osDelay(10U);
  }
}

static void timer_func(void *argument)
{
  (void) argument;

  GPIO_PinToggle(LED_PORT, LED_GREEN);
}

static void HardwareInit(void)
{
  RCC_OscInit_t osc_init;
  RCC_ClkInit_t clk_init;

  osc_init.OSC_Type = RCC_OSC_TYPE_HSE;
  osc_init.HSE_State = RCC_HSE_ON;
  osc_init.PLL.state = RCC_PLL_ON;
  osc_init.PLL.source = RCC_PLL_SRC_HSE;
  osc_init.PLL.m = 8U;
  osc_init.PLL.n = 192U;
  osc_init.PLL.p = 8U;
  osc_init.PLL.q = 4U;

  RCC_OscInit(&osc_init);

  clk_init.type = (RCC_CLK_TYPE_SYSCLK | RCC_CLK_TYPE_HCLK | RCC_CLK_TYPE_PCLK1 | RCC_CLK_TYPE_PCLK2);
  clk_init.sys_clk_src = RCC_SYSCLK_SRC_PLLCLK;
  clk_init.AHB_clk_div = RCC_SYSCLK_DIV1;
  clk_init.APB1_clk_div = RCC_HCLK_DIV4;
  clk_init.APB2_clk_div = RCC_HCLK_DIV2;

  RCC_ClkInit(&clk_init, FLASH_LATENCY_0);

  SystemCoreClockUpdate();

  if (!GPIO_GetPortClockState(LED_PORT)) {
    GPIO_PortClock(LED_PORT, GPIO_PORT_CLK_ENABLE);
  }

  static const GPIO_PIN_CFG_t LED_cfg = {
    GPIO_MODE_OUT_PP,
    GPIO_PULL_DISABLE,
    GPIO_SPEED_LOW
  };

  GPIO_PinConfig(LED_PORT, LED_GREEN, &LED_cfg);
  GPIO_PinConfig(LED_PORT, LED_RED,   &LED_cfg);
}

int main(void)
{
  osStatus_t status;

  HardwareInit();

  status = osKernelInitialize();
  if (status == osOK) {
    thread_id = osThreadNew(main_proc, NULL, &thread_attr);
    if (thread_id == NULL) {
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
