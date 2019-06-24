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

#include "GPIO_STM32F4xx.h"
#include "ukernel.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define TIMEOUT                       (250UL)
#define THREAD_STACK_SIZE             (256U)

#define LED_PORT                      GPIO_PORT_D
#define LED_GREEN                     GPIO_PIN_12
#define LED_ORANGE                    GPIO_PIN_13
#define LED_RED                       GPIO_PIN_14
#define LED_BLUE                      GPIO_PIN_15

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

static const GPIO_PIN_CFG_t LED_cfg = {
    GPIO_MODE_OUT_PP,
    GPIO_PULL_DISABLE,
    GPIO_SPEED_LOW
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
    GPIO_PinToggle(LED_PORT, LED_GREEN);
    osDelay(TIMEOUT/2UL);
  }
}

static void threadB_func(void *param)
{
  osDelay(TIMEOUT);
  osTimerStart(timer2, TIMEOUT);

  for (;;) {
    osDelay(TIMEOUT/2UL);
    GPIO_PinToggle(LED_PORT, LED_RED);
    osDelay(TIMEOUT/2UL);
  }
}

static void timer1_func(void *argument)
{
  GPIO_PinToggle(LED_PORT, LED_ORANGE);
}

static void timer2_func(void *argument)
{
  GPIO_PinToggle(LED_PORT, LED_BLUE);
}

static void HardwareInit(void)
{
  if (!GPIO_GetPortClockState(LED_PORT)) {
    GPIO_PortClock(LED_PORT, GPIO_PORT_CLK_ENABLE);
  }

  GPIO_PinConfig(LED_PORT, LED_GREEN,  &LED_cfg);
  GPIO_PinConfig(LED_PORT, LED_ORANGE, &LED_cfg);
  GPIO_PinConfig(LED_PORT, LED_RED,    &LED_cfg);
  GPIO_PinConfig(LED_PORT, LED_BLUE,   &LED_cfg);
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

/* ----------------------------- End of file ---------------------------------*/
