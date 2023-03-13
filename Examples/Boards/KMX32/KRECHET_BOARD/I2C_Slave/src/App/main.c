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

#include <asm/krechet1.h>
#include <Kernel/kernel.h>
#include <CMSIS/Driver/Driver_I2C.h>
#include <Driver/ADSU_KRECHET1.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STACK_SIZE             (256U)

#define LED0_R                        (1UL << 24U)
#define LED0_G                        (1UL << 25U)
#define LED0_B                        (1UL << 26U)
#define LED1_R                        (1UL << 27U)
#define LED1_G                        (1UL << 28U)
#define LED1_B                        (1UL << 29U)
#define LED_TIMEOUT                   (500U)

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

static osThreadId_t main_id;
static osThread_t   main_cb;
static uint64_t     main_stack[THREAD_STACK_SIZE/8U] __attribute__((section(".bss.os.thread.stack")));
static const osThreadAttr_t main_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &main_cb,
    .cb_size    = sizeof(main_cb),
    .stack_mem  = &main_stack[0],
    .stack_size = sizeof(main_stack),
    .priority   = osPriorityNormal,
};

static osTimerId_t         timer_led;
static osTimer_t           timer_led_cb;
static const osTimerAttr_t timer_led_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer_led_cb,
    .cb_size   = sizeof(timer_led_cb)
};

extern Driver_ADSU_t Driver_ADSU;
static Driver_ADSU_t *adsu = &Driver_ADSU;

extern ARM_DRIVER_I2C Driver_I2C0;
static ARM_DRIVER_I2C *i2c = &Driver_I2C0;

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
  adsu->PeriphEnable(ADSU_Periph_GPIO);

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_DIR_REG, LED1_G);
}

static
void main_proc(void *param)
{
  (void) param;

  GPIO_Init();
  osTimerStart(timer_led, LED_TIMEOUT);

  /* Initialize I2C Driver */
  i2c->Initialize(I2C_Callback);
  /* Configure I2C Driver */
  i2c->PowerControl(ARM_POWER_FULL);
  i2c->Control(ARM_I2C_OWN_ADDRESS, SLAVE_ADDR);

  i2c->SlaveTransmit(&mem_page[offset], sizeof(mem_page));
}

static void timer_led_func(void *argument)
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
    main_id = osThreadNew(main_proc, NULL, &main_attr);
    if (main_id == NULL) {
      goto error;
    }

    timer_led = osTimerNew(timer_led_func, osTimerPeriodic, NULL, &timer_led_attr);
    if (timer_led == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
