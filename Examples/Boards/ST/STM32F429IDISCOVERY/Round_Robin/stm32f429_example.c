/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * File Name  :	stm32f429_example.c
 * Description:	Round Robin Example
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "asm/GPIO_STM32F4xx.h"
#include "asm/system_stm32f4xx.h"
#include "Kernel/kernel.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define THREAD_STACK_SIZE             (256U)

#define LED_PORT                      GPIO_PORT_G
#define LED_GREEN                     GPIO_PIN_13
#define LED_RED                       GPIO_PIN_14

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t         threadA;
static osThread_t           threadA_cb;
static uint64_t             threadA_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t threadA_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &threadA_cb,
    .cb_size    = sizeof(threadA_cb),
    .stack_mem  = &threadA_stack[0],
    .stack_size = sizeof(threadA_stack),
    .priority   = osPriorityNormal,
};

static osThreadId_t         threadB;
static osThread_t           threadB_cb;
static uint64_t             threadB_stack[THREAD_STACK_SIZE/8U];
static const osThreadAttr_t threadB_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &threadB_cb,
    .cb_size    = sizeof(threadB_cb),
    .stack_mem  = &threadB_stack[0],
    .stack_size = sizeof(threadB_stack),
    .priority   = osPriorityNormal,
};

static const GPIO_PIN_CFG_t LED_cfg = {
    GPIO_MODE_OUT_PP,
    GPIO_PULL_DISABLE,
    GPIO_SPEED_LOW
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

__NO_RETURN
static void threadA_func(void *param)
{
  (void) param;

  for (;;) {
    GPIO_PinWrite(LED_PORT, LED_GREEN, GPIO_PIN_OUT_HIGH);
    GPIO_PinWrite(LED_PORT, LED_RED,   GPIO_PIN_OUT_LOW);
  }
}

__NO_RETURN
static void threadB_func(void *param)
{
  (void) param;

  for (;;) {
    GPIO_PinWrite(LED_PORT, LED_GREEN, GPIO_PIN_OUT_LOW);
    GPIO_PinWrite(LED_PORT, LED_RED,   GPIO_PIN_OUT_HIGH);
  }
}

static void HardwareInit(void)
{
  SystemCoreClockUpdate();

  if (!GPIO_GetPortClockState(LED_PORT)) {
    GPIO_PortClock(LED_PORT, GPIO_PORT_CLK_ENABLE);
  }

  GPIO_PinConfig(LED_PORT, LED_GREEN, &LED_cfg);
  GPIO_PinConfig(LED_PORT, LED_RED,   &LED_cfg);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

int main(void)
{
  osStatus_t status;

  HardwareInit();

  status = osKernelInitialize();
  if (status == osOK) {
    threadA = osThreadNew(threadA_func, NULL, &threadA_attr);
    if (threadA == NULL) {
      goto error;
    }

    threadB = osThreadNew(threadB_func, NULL, &threadB_attr);
    if (threadB == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}

/* ----------------------------- End of file ---------------------------------*/
