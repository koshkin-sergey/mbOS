/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * File Name  :	stm32f429_example_timers.c
 * Description:	stm32f429_example_timers
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

#define TIMEOUT                       (250UL)
#define THREAD_STACK_SIZE             (256U)

#define LED_PORT                      GPIO_PORT_G
#define LED_GREEN                     GPIO_PIN_13
#define LED_RED                       GPIO_PIN_14

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static osThreadId_t         init_id;
static osThread_t           init_cb;
static uint64_t             init_stack[THREAD_STACK_SIZE/8U];
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

static const GPIO_PIN_CFG_t LED_cfg = {
    GPIO_MODE_OUT_PP,
    GPIO_PULL_DISABLE,
    GPIO_SPEED_LOW
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static void init_proc(void *param)
{
  (void) param;

  osTimerStart(timer1, TIMEOUT);
  osDelay(TIMEOUT);
  osTimerStart(timer2, TIMEOUT);
}

static void timer1_func(void *argument)
{
  (void) argument;

  GPIO_PinToggle(LED_PORT, LED_GREEN);
}

static void timer2_func(void *argument)
{
  (void) argument;

  GPIO_PinToggle(LED_PORT, LED_RED);
}

static void HardwareInit(void)
{
  SystemCoreClockUpdate();

  if (!GPIO_GetPortClockState(LED_PORT)) {
    GPIO_PortClock(LED_PORT, GPIO_PORT_CLK_ENABLE);
  }

  GPIO_PinConfig(LED_PORT, LED_GREEN,  &LED_cfg);
  GPIO_PinConfig(LED_PORT, LED_RED,    &LED_cfg);
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

/* ----------------------------- End of file ---------------------------------*/
