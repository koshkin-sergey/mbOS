/*
 * Copyright (C) 2018-2019 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
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
 *
 * Project: EXTI Driver for STMicroelectronics STM32F4xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "EXTI_STM32F4xx.h"

#include <stddef.h>

#include "stm32f4xx.h"
#include "RCC_STM32F4xx.h"
#include "RTE_Device.h"

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct {
  EXTI_SignalEvent_t callback[EXTI_LINE_NUMBER];
} EXTI_Info_t;

typedef struct {
  IRQn_Type       irq_num[EXTI_LINE_NUMBER];  /* IRQ Number                   */
  EXTI_Info_t    *info;                       /* Run-Time information         */
} const EXTI_Resources_t;

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

static EXTI_Info_t EXTI_Info;

static EXTI_Resources_t exti = {
    {
        EXTI0_IRQn,
        EXTI1_IRQn,
        EXTI2_IRQn,
        EXTI3_IRQn,
        EXTI4_IRQn,
        EXTI9_5_IRQn,
        EXTI9_5_IRQn,
        EXTI9_5_IRQn,
        EXTI9_5_IRQn,
        EXTI9_5_IRQn,
        EXTI15_10_IRQn,
        EXTI15_10_IRQn,
        EXTI15_10_IRQn,
        EXTI15_10_IRQn,
        EXTI15_10_IRQn,
        EXTI15_10_IRQn,
        PVD_IRQn,
        RTC_Alarm_IRQn,
#if defined(STM32F401xC) || defined(STM32F401xE) ||                                                 \
    defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F411xE) ||                                                                         \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
        OTG_FS_WKUP_IRQn,
#else
        (IRQn_Type)0,
#endif
#if defined(STM32F407xx) || defined(STM32F417xx) ||                                                 \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
        ETH_WKUP_IRQn,
#else
        (IRQn_Type)0,
#endif
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
        OTG_HS_WKUP_IRQn,
#else
        (IRQn_Type)0,
#endif
        TAMP_STAMP_IRQn,
        RTC_WKUP_IRQn,
    },
    &EXTI_Info
};

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
void EXTI_IRQHandler(EXTI_Line_t line)
{
  EXTI_SignalEvent_t callback = exti.info->callback[line];

  EXTI->PR = (1UL << line);

  if (callback != NULL) {
    callback();
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          void EXTI_Initialize(EXTI_Line_t line, EXTI_Mode_t mode, EXTI_trigger_t trigger, EXTI_SignalEvent_t cb)
 * @brief
 * @param[in]   line
 * @param[in]   mode
 * @param[in]   trigger
 * @param[in]   cb
 */
void EXTI_Initialize(EXTI_Line_t line, EXTI_Mode_t mode, EXTI_trigger_t trigger, EXTI_SignalEvent_t cb)
{
  uint32_t exti_imr, exti_emr, exti_rtsr, exti_ftsr, mask;
  IRQn_Type irq_num;

  exti_imr = EXTI->IMR;
  exti_emr = EXTI->EMR;
  exti_rtsr = EXTI->RTSR;
  exti_ftsr = EXTI->FTSR;

  mask = (1UL << (uint32_t)line);

  switch (mode) {
    case EXTI_MODE_INTERRUPT:
      exti_imr |= mask;
      exti_emr &= ~mask;
      break;

    case EXTI_MODE_EVENT:
      exti_emr |= mask;
      exti_imr &= ~mask;
      break;

    case EXTI_MODE_INTERRUPT_EVENT:
      exti_imr |= mask;
      exti_emr |= mask;
      break;
  }

  switch (trigger) {
    case EXTI_TRIGGER_RISING:
      exti_rtsr |= mask;
      exti_ftsr &= ~mask;
      break;

    case EXTI_TRIGGER_FALLING:
      exti_ftsr |= mask;
      exti_rtsr &= ~mask;
      break;

    case EXTI_TRIGGER_RISING_FALLING:
      exti_rtsr |= mask;
      exti_ftsr |= mask;
      break;
  }

  exti.info->callback[line] = cb;

  EXTI->IMR = exti_imr;
  EXTI->EMR = exti_emr;
  EXTI->RTSR = exti_rtsr;
  EXTI->FTSR = exti_ftsr;

  if (mode == EXTI_MODE_INTERRUPT || mode == EXTI_MODE_INTERRUPT_EVENT) {
    irq_num = exti.irq_num[line];

    /* Clear and Enable EXTI IRQ */
    NVIC_ClearPendingIRQ(irq_num);
    NVIC_SetPriority(irq_num, RTE_EXTI_INT_PRIORITY);
    NVIC_EnableIRQ(irq_num);
  }
}

/**
 * @fn          void EXTI_Uninitialize(EXTI_Line_t line)
 * @brief
 * @param[in]   line
 */
void EXTI_Uninitialize(EXTI_Line_t line)
{
  uint32_t mask = (1UL << (uint32_t)line);

  /* Mask interrupt request */
  EXTI->IMR &= ~mask;
  /* Mask event request */
  EXTI->EMR &= ~mask;
  /* Disable rising trigger */
  EXTI->RTSR &= ~mask;
  /* Disable falling trigger */
  EXTI->FTSR &= ~mask;
  /* Clear pending bit */
  EXTI->PR = mask;

  exti.info->callback[line] = NULL;
}

/**
 * @fn          void EXTI_LineMapping(EXTI_Line_t line, EXTI_Port_t port)
 * @brief
 * @param[in]   line
 * @param[in]   port
 */
void EXTI_LineMapping(EXTI_Line_t line, EXTI_Port_t port)
{
  uint32_t value, reg_num, offset;

  if (line <= EXTI_LINE_15) {
    /* Enable SYSCFG clock */
    RCC_EnablePeriph(RCC_PERIPH_SYSCFG);

    reg_num = line >> 2U;
    offset = ((uint32_t)line & 3U) << 2U;

    /* Configure external line mapping */
    value = SYSCFG->EXTICR[reg_num] & ~(0x0F << offset);
    SYSCFG->EXTICR[reg_num] = value | (port << offset);
  }
}

/**
 * @fn          void EXTI_SoftwareRequest(EXTI_Line_t line)
 * @brief
 * @param[in]   line
 */
void EXTI_SoftwareRequest(EXTI_Line_t line)
{
  EXTI->SWIER |= (1UL << (uint32_t)line);
}

/*******************************************************************************
 *  Interrupt Handlers
 ******************************************************************************/

/**
 * @fn          void PVD_IRQHandler(void)
 * @brief       PVD through EXTI Line detection
 */
void PVD_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_PVD);
}

/**
 * @fn          void TAMP_STAMP_IRQHandler(void)
 * @brief       Tamper and TimeStamps through the EXTI line
 */
void TAMP_STAMP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_RTC_TAMPER_STAMP);
}

/**
 * @fn          void RTC_WKUP_IRQHandler(void)
 * @brief       RTC Wakeup through the EXTI line
 */
void RTC_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_RTC_WAKEUP);
}

/**
 * @fn          void RTC_Alarm_IRQHandler(void)
 * @brief       RTC Alarm (A and B) through EXTI Line
 */
void RTC_Alarm_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_RTC_ALARM);
}

#if defined(STM32F401xC) || defined(STM32F401xE) ||                                                 \
    defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F411xE) ||                                                                         \
    defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || \
    defined(STM32F413xx) ||                                                                         \
    defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

/**
 * @fn          void OTG_FS_WKUP_IRQHandler(void)
 * @brief       USB OTG FS Wakeup through EXTI line
 */
void OTG_FS_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_USB_OTG_FS_WAKEUP);
}

#endif

#if defined(STM32F407xx) || defined(STM32F417xx) ||                                                 \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

/**
 * @fn          void ETH_WKUP_IRQHandler(void)
 * @brief       Ethernet Wakeup through EXTI line
 */
void ETH_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_ETHERNET_WAKEUP);
}

#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) ||                         \
    defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

/**
 * @fn          void OTG_HS_WKUP_IRQHandler(void)
 * @brief       USB OTG HS Wakeup through EXTI
 */
void OTG_HS_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_USB_OTG_HS_WAKEUP);
}

#endif

/**
 * @fn          void EXTI0_IRQHandler(void)
 * @brief       EXTI Line0
 */
void EXTI0_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_LINE_0);
}

/**
 * @fn          void EXTI1_IRQHandler(void)
 * @brief       EXTI Line1
 */
void EXTI1_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_LINE_1);
}

/**
 * @fn          void EXTI2_IRQHandler(void)
 * @brief       EXTI Line2
 */
void EXTI2_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_LINE_2);
}

/**
 * @fn          void EXTI3_IRQHandler(void)
 * @brief       EXTI Line3
 */
void EXTI3_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_LINE_3);
}

/**
 * @fn          void EXTI4_IRQHandler(void)
 * @brief       EXTI Line4
 */
void EXTI4_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_LINE_4);
}

/**
 * @fn          void EXTI9_5_IRQHandler(void)
 * @brief       External Line[9:5]s
 */
void EXTI9_5_IRQHandler(void)
{
  EXTI_Line_t line = EXTI_LINE_5;
  uint32_t pr = (EXTI->PR & (EXTI_PR_PR5 | EXTI_PR_PR6 | EXTI_PR_PR7 | EXTI_PR_PR8 | EXTI_PR_PR9)) >> line;

  while (pr != 0U) {
    if (pr & 1U) {
      EXTI_IRQHandler(line);
    }
    ++line;
    pr >>= 1U;
  }
}

/**
 * @fn          void EXTI15_10_IRQHandler(void)
 * @brief       External Line[15:10]s
 */
void EXTI15_10_IRQHandler(void)
{
  EXTI_Line_t line = EXTI_LINE_10;
  uint32_t pr = (EXTI->PR & (EXTI_PR_PR10 | EXTI_PR_PR11 | EXTI_PR_PR12 | EXTI_PR_PR13 | EXTI_PR_PR14 | EXTI_PR_PR15)) >> line;

  while (pr != 0U) {
    if (pr & 1U) {
      EXTI_IRQHandler(line);
    }
    ++line;
    pr >>= 1U;
  }
}

/* ----------------------------- End of file ---------------------------------*/
