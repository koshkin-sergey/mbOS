/*
 * Copyright (C) 2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * File Name  :	stm32f4_example_timers.c
 * Description:	stm32f4_example_timers
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
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
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void threadA_func(void *param)
{
  osTimerStart(timer1, TIMEOUT);

  for (;;) {
    osDelay(TIMEOUT/2UL);
    GPIOD->ODR ^= (1UL << 12U);
    osDelay(TIMEOUT/2UL);
  }
}

static void threadB_func(void *param)
{
  osDelay(TIMEOUT);
  osTimerStart(timer2, TIMEOUT);

  for (;;) {
    osDelay(TIMEOUT/2UL);
    GPIOD->ODR ^= (1UL << 14U);
    osDelay(TIMEOUT/2UL);
  }
}

static void timer1_func(void *argument)
{
  GPIOD->ODR ^= (1UL << 13U);
}

static void timer2_func(void *argument)
{
  GPIOD->ODR ^= (1UL << 15U);
}

static void HardwareInit(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
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

void osSysTickInit(uint32_t hz)
{
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/hz);
}

/* ----------------------------- End of file ---------------------------------*/
