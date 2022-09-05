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

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define LED0_R                        (1UL << 24U)
#define LED0_G                        (1UL << 25U)
#define LED0_B                        (1UL << 26U)
#define LED1_R                        (1UL << 27U)
#define LED1_G                        (1UL << 28U)
#define LED1_B                        (1UL << 29U)

#define TIMEOUT                       (500UL)
#define THREAD_STACK_SIZE             (256U)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

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

static osTimerId_t         timer2;
static osTimer_t           timer2_cb;
static const osTimerAttr_t timer2_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer2_cb,
    .cb_size   = sizeof(timer2_cb)
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void GPIO_Init(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_GATE_REG, __get_PeriphReg(ADSU_GATE_REG) | 0x00010000);

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_DIR_REG, LED0_R | LED0_B | LED1_G);
  __set_PeriphReg(GPIO_OUT_REG, LED0_R);
}

static void init_proc(void *param)
{
  (void) param;

  GPIO_Init();

  osTimerStart(timer1, TIMEOUT);
  osTimerStart(timer2, TIMEOUT / 4U);
}

static void timer1_func(void *argument)
{
  (void) argument;

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_OUT_REG, __get_PeriphReg(GPIO_OUT_REG) ^ (LED0_R | LED0_B));
}

static void timer2_func(void *argument)
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

    timer2 = osTimerNew(timer2_func, osTimerPeriodic, NULL, &timer2_attr);
    if (timer2 == NULL) {
        goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
