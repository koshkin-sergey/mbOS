/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include "Driver/EXTI_ADUC7023.h"

#if defined(USE_EXTI_IRQ0) || defined(USE_EXTI_IRQ1) || \
    defined(USE_EXTI_IRQ2) || defined(USE_EXTI_IRQ3)

/*******************************************************************************
 *  function prototypes (scope: module-local)
 ******************************************************************************/

#if defined(USE_EXTI_IRQ0)
static void EXT_IRQ0Handler(void);
#endif

#if defined(USE_EXTI_IRQ1)
static void EXT_IRQ1Handler(void);
#endif

#if defined(USE_EXTI_IRQ2)
static void EXT_IRQ2Handler(void);
#endif

#if defined(USE_EXTI_IRQ3)
static void EXT_IRQ3Handler(void);
#endif

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* EXTI Information (Run-Time) */
static EXTI_INFO EXTI_Info;

/* EXTI Resources */
static EXTI_RESOURCES EXTI_Resources = {
  &IRQ->EXT_IRQ,
  /* Pin Configuration */
  {
#if defined(USE_EXTI_IRQ0)
    &(EXTI_PIN){EXTI_IRQ0_GPIO_PORT, EXTI_IRQ0_GPIO_PIN, EXTI_IRQ0_GPIO_FUNC, EXTI_IRQ0_PULL_UP},
#else
    NULL,
#endif
#if defined(USE_EXTI_IRQ1)
    &(EXTI_PIN){EXTI_IRQ1_GPIO_PORT, EXTI_IRQ1_GPIO_PIN, EXTI_IRQ1_GPIO_FUNC, EXTI_IRQ1_PULL_UP},
#else
    NULL,
#endif
#if defined(USE_EXTI_IRQ2)
    &(EXTI_PIN){EXTI_IRQ2_GPIO_PORT, EXTI_IRQ2_GPIO_PIN, EXTI_IRQ2_GPIO_FUNC, EXTI_IRQ2_PULL_UP},
#else
    NULL,
#endif
#if defined(USE_EXTI_IRQ3)
    &(EXTI_PIN){EXTI_IRQ3_GPIO_PORT, EXTI_IRQ3_GPIO_PIN, EXTI_IRQ3_GPIO_FUNC, EXTI_IRQ3_PULL_UP},
#else
    NULL,
#endif
  },
  /* IRQ Configuration */
  {
#if defined(USE_EXTI_IRQ0)
    &(EXTI_IRQ){EXTI_IRQ0_INT_PRIO, EXT_IRQ0_IRQn, EXT_IRQ0Handler},
#else
    NULL,
#endif
#if defined(USE_EXTI_IRQ1)
    &(EXTI_IRQ){EXTI_IRQ1_INT_PRIO, EXT_IRQ1_IRQn, EXT_IRQ1Handler},
#else
    NULL,
#endif
#if defined(USE_EXTI_IRQ2)
    &(EXTI_IRQ){EXTI_IRQ2_INT_PRIO, EXT_IRQ2_IRQn, EXT_IRQ2Handler},
#else
    NULL,
#endif
#if defined(USE_EXTI_IRQ3)
    &(EXTI_IRQ){EXTI_IRQ3_INT_PRIO, EXT_IRQ3_IRQn, EXT_IRQ3Handler},
#else
    NULL,
#endif
  },
  &EXTI_Info,
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static int32_t EXTI_Initialize(EXTI_SignalEvent_t cb_event)
{
  EXTI_PIN  *exti_pin;
  EXTI_IRQ  *exti_irq;
  EXTI_INFO *info = EXTI_Resources.info;

  if ((info->flags & EXTI_FLAG_INITIALIZED) != 0U) {
    return (EXTI_DRIVER_OK);
  }

  /* Configure EXTI Pins */
  GPIO_PIN_CFG_t pin_cfg = {
    .mode      = GPIO_MODE_INPUT,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  for (uint32_t i = 0U; i < EXT_IRQ_NUM; ++i) {
    if (EXTI_Resources.pin[i] != NULL) {
      exti_pin = EXTI_Resources.pin[i];
      pin_cfg.func = exti_pin->func;
      pin_cfg.pull_mode = exti_pin->pullup;
      exti_pin->gpio->PinConfig(exti_pin->pin, &pin_cfg);
    }

    if (EXTI_Resources.irq[i] != NULL) {
      exti_irq = EXTI_Resources.irq[i];
      IRQ_SetPriority(exti_irq->num, exti_irq->priority);
      IRQ_SetHandler(exti_irq->num, exti_irq->handler);
      IRQ_SetMode(exti_irq->num, IRQ_MODE_TYPE_IRQ);
    }
  }

  info->cb_event = cb_event;
  info->flags    = EXTI_FLAG_INITIALIZED;

  return (EXTI_DRIVER_OK);
}

static int32_t EXTI_Uninitialize(void)
{
  EXTI_PIN  *exti_pin;
  EXTI_INFO *info = EXTI_Resources.info;

  /* Configure EXTI Pins */
  GPIO_PIN_CFG_t pin_cfg = {
    .func      = GPIO_PIN_FUNC_0,
    .mode      = GPIO_MODE_INPUT,
    .pull_mode = GPIO_PULL_UP,
    .strength  = GPIO_STRENGTH_MEDIUM,
  };

  for (uint32_t i = 0U; i < EXT_IRQ_NUM; ++i) {
    if (EXTI_Resources.pin[i] != NULL) {
      exti_pin = EXTI_Resources.pin[i];
      exti_pin->gpio->PinConfig(exti_pin->pin, &pin_cfg);
    }
  }

  info->cb_event = NULL;
  info->flags    = 0U;

  return (EXTI_DRIVER_OK);
}

static int32_t EXTI_Control(uint32_t control, uint32_t arg)
{
  uint32_t        irqcone_reg;
  uint32_t        value;
  EXTI_INFO      *info = EXTI_Resources.info;
  struct EXT_IRQ *reg  = EXTI_Resources.reg;

  if ((info->flags & EXTI_FLAG_INITIALIZED) == 0U) {
    /* EXTI not initialized */
    return (EXTI_DRIVER_ERROR);
  }

  if (arg >= EXT_IRQ_NUM || EXTI_Resources.pin[arg] == NULL) {
    return (EXTI_DRIVER_ERROR_PARAMETER);
  }

  irqcone_reg = reg->CONE;

  switch (control & EXTI_CONTROL_Msk) {
    case EXTI_MODE_INACTIVE:
      /* Disable EXTI IRQ */
      IRQ_Disable(EXTI_Resources.irq[arg]->num);
      break;

    case EXTI_MODE_ACTIVE:
      /* Configure EXTI Mode */
      value = (control & EXTI_TRG_Msk) >> EXTI_TRG_Pos;

      switch (arg) {
        case EXT_IRQ0:
          MODIFY_REG(irqcone_reg, IRQ_CONE_IRQ0SRC_Msk, value << IRQ_CONE_IRQ0SRC_Pos);
          break;

        case EXT_IRQ1:
          MODIFY_REG(irqcone_reg, IRQ_CONE_IRQ1SRC_Msk, value << IRQ_CONE_IRQ1SRC_Pos);
          break;

        case EXT_IRQ2:
          MODIFY_REG(irqcone_reg, IRQ_CONE_IRQ2SRC_Msk, value << IRQ_CONE_IRQ2SRC_Pos);
          break;

        case EXT_IRQ3:
          MODIFY_REG(irqcone_reg, IRQ_CONE_IRQ3SRC_Msk, value << IRQ_CONE_IRQ3SRC_Pos);
          break;
      }

      reg->CONE = irqcone_reg;
      /* Enable EXTI IRQ */
      IRQ_Enable(EXTI_Resources.irq[arg]->num);
      break;

    default:
      return (EXTI_DRIVER_ERROR_UNSUPPORTED);
  }

  return (EXTI_DRIVER_OK);
}

/**
 * @brief       EXT IRQ Interrupt handler.
 */
static void EXT_IRQHandler(EXT_IRQn_t irqn, EXTI_EVENT_t event)
{
  EXTI_INFO *info = EXTI_Resources.info;

  if (info->cb_event != NULL) {
    info->cb_event(irqn, event);
  }
}

#if defined(USE_EXTI_IRQ0)
/**
 * @brief       EXT IRQ0 Interrupt handler.
 */
static void EXT_IRQ0Handler(void)
{
  EXTI_EVENT_t    event;
  struct EXT_IRQ *reg;

  reg   = EXTI_Resources.reg;
  event = (reg->CONE & IRQ_CONE_IRQ0SRC_Msk) >> IRQ_CONE_IRQ0SRC_Pos;

  if ((event & 2U) != 0U) {
    reg->CLRE = IRQ_CLRE_IRQ0CLRI;
  }

  EXT_IRQHandler(EXT_IRQ0, event);
}
#endif

#if defined(USE_EXTI_IRQ1)
/**
 * @brief       EXT IRQ1 Interrupt handler.
 */
static void EXT_IRQ1Handler(void)
{
  EXTI_EVENT_t    event;
  struct EXT_IRQ *reg;

  reg   = EXTI_Resources.reg;
  event = (reg->CONE & IRQ_CONE_IRQ1SRC_Msk) >> IRQ_CONE_IRQ1SRC_Pos;

  if ((event & 2U) != 0U) {
    reg->CLRE = IRQ_CLRE_IRQ1CLRI;
  }

  EXT_IRQHandler(EXT_IRQ1, event);
}
#endif

#if defined(USE_EXTI_IRQ2)
/**
 * @brief       EXT IRQ2 Interrupt handler.
 */
static void EXT_IRQ2Handler(void)
{
  EXTI_EVENT_t    event;
  struct EXT_IRQ *reg;

  reg   = EXTI_Resources.reg;
  event = (reg->CONE & IRQ_CONE_IRQ2SRC_Msk) >> IRQ_CONE_IRQ2SRC_Pos;

  if ((event & 2U) != 0U) {
    reg->CLRE = IRQ_CLRE_IRQ2CLRI;
  }

  EXT_IRQHandler(EXT_IRQ2, event);
}
#endif

#if defined(USE_EXTI_IRQ3)
/**
 * @brief       EXT IRQ3 Interrupt handler.
 */
static void EXT_IRQ3Handler(void)
{
  EXTI_EVENT_t    event;
  struct EXT_IRQ *reg;

  reg   = EXTI_Resources.reg;
  event = (reg->CONE & IRQ_CONE_IRQ3SRC_Msk) >> IRQ_CONE_IRQ3SRC_Pos;

  if ((event & 2U) != 0U) {
    reg->CLRE = IRQ_CLRE_IRQ3CLRI;
  }

  EXT_IRQHandler(EXT_IRQ3, event);
}
#endif

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

Driver_EXTI_t Driver_EXTI = {
  EXTI_Initialize,
  EXTI_Uninitialize,
  EXTI_Control,
};

#endif // defined(USE_EXTI_IRQ0)...
