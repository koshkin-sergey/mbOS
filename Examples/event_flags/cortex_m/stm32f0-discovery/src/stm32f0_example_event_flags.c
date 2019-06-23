/*
 * Copyright (C) 2015-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * File Name  :	stm32f0_example_event_flags.c
 * Description:	stm32f0_example_event_flags
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
#include "RTOS_Config.h"
#include "ukernel.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TEST_FLAG           (1UL)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t         threadA;
static osThread_t           threadA_cb;
static uint64_t             threadA_stack[OS_STACK_SIZE/8U];
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
static uint64_t             threadB_stack[OS_STACK_SIZE/8U];
static const osThreadAttr_t threadB_attr = {
    .name       = NULL,
    .attr_bits  = 0U,
    .cb_mem     = &threadB_cb,
    .cb_size    = sizeof(threadB_cb),
    .stack_mem  = &threadB_stack[0],
    .stack_size = sizeof(threadB_stack),
    .priority   = osPriorityNormal,
};

static osEventFlagsId_t         event;
static osEventFlags_t           event_cb;
static const osEventFlagsAttr_t event_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &event_cb,
    .cb_size   = sizeof(event_cb)
};

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void threadA_func(void *param)
{
  uint32_t flags;

  for (;;) {
    flags = osEventFlagsWait(event, TEST_FLAG, osFlagsWaitAny, osWaitForever);
    if (flags == TEST_FLAG) {
      GPIOC->ODR ^= (1UL << 8U);
    }
  }
}

static void threadB_func(void *param)
{
  uint32_t flags;
  uint32_t tick;

  for (;;) {
    tick = osKernelGetTickCount() + 1000;
    flags = osEventFlagsSet(event, TEST_FLAG);
    if ((int32_t)flags >= 0) {
      GPIOC->ODR |= (1UL << 9U);
      osDelay(50);
      GPIOC->ODR &= ~(1UL << 9U);
    }
    osDelayUntil(tick);
  }
}

static void HardwareInit(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
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

    event = osEventFlagsNew(&event_attr);
    if (event == NULL) {
      goto error;
    }

    /* Start RTOS */
    osKernelStart();
  }

error:
  return (-1);
}

void osSysTickInit(uint32_t hz)
{
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/hz);
}

/* ----------------------------- End of file ---------------------------------*/
