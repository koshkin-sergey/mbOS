/*
 * Copyright (C) 2019-2020 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: EXTI Driver for STMicroelectronics STM32F7xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include "asm/stm32f7xx.h"
#include "asm/EXTI_STM32F7xx.h"
#include "asm/RCC_STM32F7xx.h"

#if (DEV_EXTI == 1)

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define NONE_IRQn                   (IRQn_Type)-128
#define EXTI9_5_MASK                0x000003E0UL
#define EXTI15_10_MASK              0x0000FC00UL

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct {
  EXTI_SignalEvent_t  cb_event;
  uint32_t            state;
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
        OTG_FS_WKUP_IRQn,
        ETH_WKUP_IRQn,
        OTG_HS_WKUP_IRQn,
        TAMP_STAMP_IRQn,
        RTC_WKUP_IRQn,
        LPTIM1_IRQn,
#if defined(STM32F765xx) || defined(STM32F767xx) || defined(STM32F769xx) || \
    defined(STM32F777xx) || defined(STM32F779xx)
        MDIOS_IRQn,
#else
        NONE_IRQn,
#endif
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
void EnableIRQ(IRQn_Type irq_num)
{
  if (irq_num < (IRQn_Type)0) {
    return;
  }

  if (NVIC_GetEnableIRQ(irq_num) == 0U) {
    NVIC_ClearPendingIRQ(irq_num);
    NVIC_SetPriority(irq_num, DEV_EXTI_INT_PRIORITY);
    NVIC_EnableIRQ(irq_num);
  }
}

static
void DisableIRQ(IRQn_Type irq_num, uint32_t int_mask)
{
  bool disable = false;

  if (irq_num < (IRQn_Type)0) {
    return;
  }

  switch (irq_num) {
    case EXTI9_5_IRQn:
      if ((int_mask & EXTI9_5_MASK) == 0U) {
        disable = true;
      }
      break;

    case EXTI15_10_IRQn:
      if ((int_mask & EXTI15_10_MASK) == 0U) {
        disable = true;
      }
      break;

    default:
      disable = true;
      break;
  }

  if (disable) {
    NVIC_DisableIRQ(irq_num);
  }
}

static
void EXTI_IRQHandler(EXTI_Line_t line)
{
  EXTI_SignalEvent_t cb_event = exti.info->cb_event;

  EXTI->PR = (1UL << line);

  if (cb_event != NULL) {
    cb_event(line);
  }
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @fn          int32_t EXTI_Initialize(EXTI_SignalEvent_t cb_event)
 * @brief       Initialize EXTI Interface.
 * @param[in]   cb_event  Pointer to EXTI_SignalEvent_t
 * @return      Execution status
 */
int32_t EXTI_Initialize(EXTI_SignalEvent_t cb_event)
{
  EXTI_Info_t *info = exti.info;

  if (info->state == EXTI_INITIALIZED) {
    return (EXTI_DRIVER_OK);
  }

  /* Initialize EXTI Run-Time Resources */
  info->cb_event = cb_event;
  info->state    = EXTI_INITIALIZED;
  /* Enable System configuration controller */
  RCC_EnablePeriph(RCC_PERIPH_SYSCFG);
  /* Initialize EXTI Hardware Resources */
  EXTI->IMR  = 0x00000000U;
  EXTI->EMR  = 0x00000000U;
  EXTI->RTSR = 0x00000000U;
  EXTI->FTSR = 0x00000000U;
  EXTI->PR   = 0x01FFFFFFU;

  return (EXTI_DRIVER_OK);
}

/**
 * @fn          int32_t EXTI_Uninitialize(void)
 * @brief       De-initialize EXTI Interface.
 * @return      Execution status
 */
int32_t EXTI_Uninitialize(void)
{
  EXTI_Info_t *info = exti.info;

  /* Initialize EXTI Hardware Resources */
  EXTI->IMR  = 0x00000000U;
  EXTI->EMR  = 0x00000000U;
  EXTI->RTSR = 0x00000000U;
  EXTI->FTSR = 0x00000000U;
  EXTI->PR   = 0x01FFFFFFU;
  /* Uninitialize EXTI Run-Time Resources */
  info->cb_event = NULL;
  info->state    = 0U;

  return (EXTI_DRIVER_OK);
}

/**
 * @fn          int32_t EXTI_SetConfigLine(EXTI_Line_t line, EXTI_Port_t port, EXTI_Mode_t mode, EXTI_trigger_t trigger)
 * @brief
 * @param[in]   line
 * @param[in]   port
 * @param[in]   mode
 * @param[in]   trigger
 * @return      Execution status
 */
int32_t EXTI_SetConfigLine(EXTI_Line_t line, EXTI_Port_t port, EXTI_Mode_t mode, EXTI_trigger_t trigger)
{
  uint32_t exti_imr, exti_emr, exti_rtsr, exti_ftsr, mask;
  uint32_t value, reg_num, offset;

  if (line >= EXTI_LINE_NUMBER) {
    return (EXTI_DRIVER_ERROR_PARAMETER);
  }

  if (exti.info->state != EXTI_INITIALIZED) {
    return (EXTI_DRIVER_ERROR);
  }

  exti_imr  = EXTI->IMR;
  exti_emr  = EXTI->EMR;
  exti_rtsr = EXTI->RTSR;
  exti_ftsr = EXTI->FTSR;

  mask = (1UL << (uint32_t)line);

  switch (mode) {
    case EXTI_MODE_INTERRUPT:
      exti_emr &= ~mask;
      exti_imr |= mask;
      break;

    case EXTI_MODE_EVENT:
      exti_imr &= ~mask;
      exti_emr |= mask;
      break;

    case EXTI_MODE_INTERRUPT_EVENT:
      exti_imr |= mask;
      exti_emr |= mask;
      break;

    default:
      return (EXTI_DRIVER_ERROR_PARAMETER);
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

    default:
      return (EXTI_DRIVER_ERROR_PARAMETER);
  }

  if (line <= EXTI_LINE_15) {
    if (port == EXTI_PORT_INTERNAL) {
      return (EXTI_DRIVER_ERROR_PARAMETER);
    }

    reg_num = line >> 2U;
    offset = ((uint32_t)line & 3U) << 2U;
    /* Configure external line mapping */
    value = SYSCFG->EXTICR[reg_num] & ~(0x0F << offset);
    SYSCFG->EXTICR[reg_num] = value | (port << offset);
  }

  EXTI->IMR  = exti_imr;
  EXTI->EMR  = exti_emr;
  EXTI->RTSR = exti_rtsr;
  EXTI->FTSR = exti_ftsr;

  if (mode == EXTI_MODE_EVENT) {
    /* Disable EXTI IRQ */
    DisableIRQ(exti.irq_num[line], exti_imr);
  }
  else {
    /* Enable EXTI IRQ */
    EnableIRQ(exti.irq_num[line]);
  }

  return (EXTI_DRIVER_OK);
}

/**
 * @fn          int32_t EXTI_ClearConfigLine(EXTI_Line_t line)
 * @brief
 * @param[in]   line
 * @return      Execution status
 */
int32_t EXTI_ClearConfigLine(EXTI_Line_t line)
{
  uint32_t  exti_imr, exti_emr, mask;

  if (exti.info->state != EXTI_INITIALIZED) {
    return (EXTI_DRIVER_ERROR);
  }

  if (line >= EXTI_LINE_NUMBER) {
    return (EXTI_DRIVER_ERROR_PARAMETER);
  }

  exti_imr = EXTI->IMR;
  exti_emr = EXTI->EMR;

  mask = (1UL << (uint32_t)line);

  if (exti_emr & mask) {
    EXTI->EMR &= ~mask;
  }

  if (exti_imr & mask) {
    exti_imr &= ~mask;
    EXTI->IMR = exti_imr;
    /* Disable EXTI IRQ */
    DisableIRQ(exti.irq_num[line], exti_imr);
  }

  return (EXTI_DRIVER_OK);
}

/**
 * @fn          int32_t EXTI_SoftwareRequest(EXTI_Line_t line)
 * @brief
 * @param[in]   line
 * @return      Execution status
 */
int32_t EXTI_SoftwareRequest(EXTI_Line_t line)
{
  if (exti.info->state != EXTI_INITIALIZED) {
    return (EXTI_DRIVER_ERROR);
  }

  if (line >= EXTI_LINE_NUMBER) {
    return (EXTI_DRIVER_ERROR_PARAMETER);
  }

  EXTI->SWIER |= (1UL << (uint32_t)line);

  return (EXTI_DRIVER_OK);
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

/**
 * @fn          void OTG_FS_WKUP_IRQHandler(void)
 * @brief       USB OTG FS Wakeup through EXTI line
 */
void OTG_FS_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_USB_OTG_FS_WAKEUP);
}

/**
 * @fn          void ETH_WKUP_IRQHandler(void)
 * @brief       Ethernet Wakeup through EXTI line
 */
void ETH_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_ETHERNET_WAKEUP);
}

/**
 * @fn          void OTG_HS_WKUP_IRQHandler(void)
 * @brief       USB OTG HS Wakeup through EXTI
 */
void OTG_HS_WKUP_IRQHandler(void)
{
  EXTI_IRQHandler(EXTI_USB_OTG_HS_WAKEUP);
}

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
  EXTI_Line_t line = (EXTI_Line_t) __CLZ(__RBIT(EXTI->PR));
  EXTI_IRQHandler(line);
}

/**
 * @fn          void EXTI15_10_IRQHandler(void)
 * @brief       External Line[15:10]s
 */
void EXTI15_10_IRQHandler(void)
{
  EXTI_Line_t line = (EXTI_Line_t) __CLZ(__RBIT(EXTI->PR));
  EXTI_IRQHandler(line);
}

#endif

/* ----------------------------- End of file ---------------------------------*/
