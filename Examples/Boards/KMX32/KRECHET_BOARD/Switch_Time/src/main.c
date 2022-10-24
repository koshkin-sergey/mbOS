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

#define THREAD_STACK_SIZE             (256U)

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t thrd_a;
static osThread_t   thrd_a_cb;
static uint64_t     thrd_a_stack[THREAD_STACK_SIZE/8U] __attribute__((section(".bss.os.thread.stack")));
static const osThreadAttr_t thrd_a_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &thrd_a_cb,
    .cb_size    = sizeof(thrd_a_cb),
    .stack_mem  = &thrd_a_stack[0],
    .stack_size = sizeof(thrd_a_stack),
    .priority   = osPriorityNormal,
};

static osThreadId_t thrd_b;
static osThread_t   thrd_b_cb;
static uint64_t     thrd_b_stack[THREAD_STACK_SIZE/8U] __attribute__((section(".bss.os.thread.stack")));
static const osThreadAttr_t thrd_b_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &thrd_b_cb,
    .cb_size    = sizeof(thrd_b_cb),
    .stack_mem  = &thrd_b_stack[0],
    .stack_size = sizeof(thrd_b_stack),
    .priority   = osPriorityNormal,
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void GPIO_Init(void)
{
  __set_CpuReg(CPU_PRW_REG, PRW_ADSU);
  __set_PeriphReg(ADSU_GATE_REG, __get_PeriphReg(ADSU_GATE_REG) | 0x00010000);

  __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
  __set_PeriphReg(GPIO_DIR_REG, LED1_G);
}

static void thrd_a_func(void *argument)
{
  (void) argument;

  for (;;) {
    __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
    __set_PeriphReg(GPIO_OUT_REG, __get_PeriphReg(GPIO_OUT_REG) ^ LED1_G);
    osThreadYield();
  }
}

static void thrd_b_func(void *argument)
{
  (void) argument;

  for (;;) {
    __set_CpuReg(CPU_PRW_REG, PRW_GPIO);
    __set_PeriphReg(GPIO_OUT_REG, __get_PeriphReg(GPIO_OUT_REG) ^ LED1_G);
    osThreadYield();
  }
}

int main(void)
{
  osStatus_t status;

  SystemCoreClockUpdate();
  GPIO_Init();

  status = osKernelInitialize();
  if (status == osOK) {
    thrd_a = osThreadNew(thrd_a_func, NULL, &thrd_a_attr);
    if (thrd_a == NULL) {
      goto error;
    }

    thrd_b = osThreadNew(thrd_b_func, NULL, &thrd_b_attr);
    if (thrd_b == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}
