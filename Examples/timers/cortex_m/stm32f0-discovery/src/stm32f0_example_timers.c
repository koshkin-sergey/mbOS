/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * File Name  :	stm32f0_example_timers.c
 * Description:	stm32f0_example_timers
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

#define TIMEOUT             (250UL)

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

static osTimerId_t         timer1;
static osTimer_t           timer1_cb;
static const osTimerAttr_t timer1_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &timer1_cb,
    .cb_size   = sizeof(timer1_cb)
};

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void threadA_func(void *param)
{
  osTimerStart(timer1, TIMEOUT/2UL);

  for (;;) {
    GPIOC->ODR ^= (1UL << 9U);
    osDelay(TIMEOUT);
  }
}

static void timer1_func(void *argument)
{
  GPIOC->ODR ^= (1UL << 8U);
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

    timer1 = osTimerNew(timer1_func, osTimerPeriodic, NULL, &timer1_attr);
    if (timer1 == NULL) {
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
