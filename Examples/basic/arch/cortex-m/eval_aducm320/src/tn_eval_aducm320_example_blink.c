/*
 * Copyright (C) 2016 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * File Name  :	tn_eval_aducm320_example_blink.c
 * Description:	tn_eval_aducm320_blink
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "tn.h"
#include "ADuCM320.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define SYSTICK_FREQ      1000
#define TASK_A_STK_SIZE   64
#define TASK_A_PRIORITY   1

#define LED_PIN           ((uint8_t)1 << 4)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static TN_TCB task_A;
tn_stack_t task_A_stack[TASK_A_STK_SIZE];

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

/**
 * @brief
 * @param
 * @return
 */
__attribute__((noreturn)) void task_A_func(void *param)
{
  pADI_GP2->GPOE |= LED_PIN;

  for (int i = 0; i < 50; ++i) {
    pADI_GP2->GPTGL = LED_PIN;
    tn_task_sleep(20);
  }

  for (;;) {
    pADI_GP2->GPTGL = LED_PIN;
    tn_task_sleep(500);
  }
}

/**
 * @brief
 * @param
 * @return
 */
void rtos_init(void)
{
  tn_task_create(&task_A, task_A_func, TASK_A_PRIORITY,
                 &(task_A_stack[TASK_A_STK_SIZE-1]), TASK_A_STK_SIZE,
                 NULL, TN_TASK_START_ON_CREATION);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief
 * @param
 * @return
 */
int32_t main(void)
{
  TN_OPTIONS tn_opt = {
    .app_init = rtos_init,
    .freq_timer = SYSTICK_FREQ
  };

  /* Disable interrupt in core Cortex-M3 */
  tn_disable_irq();

  /* Start RTOS */
  tn_start_system(&tn_opt);

  return -1;
}

/**
 * @brief
 * @param
 * @return
 */
void tn_systick_init(uint32_t hz)
{
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/hz);
}

/**
 * @brief
 * @param
 * @return
 */
void tn_idle_task_func(void *param)
{
  for (;;) {
    /* Reset WDT */
    pADI_WDT->T3CLRI = 0xCCCC;
    /* Wait for interrupt */
    __WFI();
  }
}

/**
 * @brief
 * @param
 * @return
 */
void SysTick_Handler(void)
{
  tn_timer();
}

/* ----------------------------- End of file ---------------------------------*/
