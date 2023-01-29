/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#include <Driver/EXTI_ADUCM32x.h>

#include <stddef.h>
#include <asm/aducm32x.h>
#include <Driver/GPIO_ADUCM32x.h>
#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

/* EXTI configuration definitions */
#if defined (DEV_EXTI) && (DEV_EXTI == 1)
  #if defined (DEV_EXTI_IRQ0) && (DEV_EXTI_IRQ0 == 1)
    #define USE_EXTI0_IRQ
    #define EXTI0_IRQ_GPIO_PORT     DEV_EXTI_IRQ0_PORT
    #define EXTI0_IRQ_GPIO_PIN      DEV_EXTI_IRQ0_PIN
    #define EXTI0_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ0_PULL_UP
    #define EXTI0_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ0_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ1) && (DEV_EXTI_IRQ1 == 1)
    #define USE_EXTI1_IRQ
    #define EXTI1_IRQ_GPIO_PORT     DEV_EXTI_IRQ1_PORT
    #define EXTI1_IRQ_GPIO_PIN      DEV_EXTI_IRQ1_PIN
    #define EXTI1_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ1_PULL_UP
    #define EXTI1_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ1_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ2) && (DEV_EXTI_IRQ2 == 1)
    #define USE_EXTI2_IRQ
    #define EXTI2_IRQ_GPIO_PORT     DEV_EXTI_IRQ2_PORT
    #define EXTI2_IRQ_GPIO_PIN      DEV_EXTI_IRQ2_PIN
    #define EXTI2_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ2_PULL_UP
    #define EXTI2_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ2_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ4) && (DEV_EXTI_IRQ4 == 1)
    #define USE_EXTI4_IRQ
    #define EXTI4_IRQ_GPIO_PORT     DEV_EXTI_IRQ4_PORT
    #define EXTI4_IRQ_GPIO_PIN      DEV_EXTI_IRQ4_PIN
    #define EXTI4_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ4_PULL_UP
    #define EXTI4_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ4_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ5) && (DEV_EXTI_IRQ5 == 1)
    #define USE_EXTI5_IRQ
    #define EXTI5_IRQ_GPIO_PORT     DEV_EXTI_IRQ5_PORT
    #define EXTI5_IRQ_GPIO_PIN      DEV_EXTI_IRQ5_PIN
    #define EXTI5_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ5_PULL_UP
    #define EXTI5_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ5_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ7) && (DEV_EXTI_IRQ7 == 1)
    #define USE_EXTI7_IRQ
    #define EXTI7_IRQ_GPIO_PORT     DEV_EXTI_IRQ7_PORT
    #define EXTI7_IRQ_GPIO_PIN      DEV_EXTI_IRQ7_PIN
    #define EXTI7_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ7_PULL_UP
    #define EXTI7_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ7_INT_PRIO
  #endif

  #if defined (DEV_EXTI_IRQ8) && (DEV_EXTI_IRQ8 == 1)
    #define USE_EXTI8_IRQ
    #define EXTI8_IRQ_GPIO_PORT     DEV_EXTI_IRQ8_PORT
    #define EXTI8_IRQ_GPIO_PIN      DEV_EXTI_IRQ8_PIN
    #define EXTI8_IRQ_PULL_UP       (GPIO_PULL_t)DEV_EXTI_IRQ8_PULL_UP
    #define EXTI8_IRQ_INT_PRIO      (IRQ_Priority_t)DEV_EXTI_IRQ8_INT_PRIO
  #endif
#endif

#if defined(USE_EXTI0_IRQ) || defined(USE_EXTI1_IRQ) || \
    defined(USE_EXTI2_IRQ) || defined(USE_EXTI4_IRQ) || \
    defined(USE_EXTI5_IRQ) || defined(USE_EXTI7_IRQ) || \
    defined(USE_EXTI8_IRQ)

#define EXTIx_EXPORT_DRIVER(x)    \
static int32_t EXTI##x##_Initialize   (EXTI_SignalEvent_t cb_event)             { return (EXTI_Initialize   (cb_event, &EXTI##x##_Resources)); } \
static int32_t EXTI##x##_Uninitialize (void)                                    { return (EXTI_Uninitialize (          &EXTI##x##_Resources)); } \
static int32_t EXTI##x##_Control      (uint32_t control)                        { return (EXTI_Control      (control,  &EXTI##x##_Resources)); } \
\
Driver_EXTI_t Driver_EXTI##x = {  \
  EXTI##x##_Initialize,           \
  EXTI##x##_Uninitialize,         \
  EXTI##x##_Control,              \
}

/* External Interrupt Enable bit */
#define EXTI_IRQ_EN_Pos               (3U)
#define EXTI_IRQ_EN_Msk               (0x1U << EXTI_IRQ_EN_Pos)
#define EXTI_IRQ_DISABLE              (0x0U << EXTI_IRQ_EN_Pos)
#define EXTI_IRQ_ENABLE               (0x1U << EXTI_IRQ_EN_Pos)

/* External Interrupt Mode */
#define EXTI_IRQ_MODE_Pos             (0U)
#define EXTI_IRQ_MODE_Msk             (0x7U << EXTI_IRQ_MODE_Pos)

/****** Current driver status flag definition *****/
#define EXTI_FLAG_INITIALIZED         (1UL << 0)                                ///< EXTI initialized

/*******************************************************************************
 *  external declarations
 ******************************************************************************/

#if defined(USE_EXTI0_IRQ)
extern void EXTI0_IRQHandler(void);
#endif

#if defined(USE_EXTI1_IRQ)
extern void EXTI1_IRQHandler(void);
#endif

#if defined(USE_EXTI2_IRQ)
extern void EXTI2_IRQHandler(void);
#endif

#if defined(USE_EXTI4_IRQ)
extern void EXTI4_IRQHandler(void);
#endif

#if defined(USE_EXTI5_IRQ)
extern void EXTI5_IRQHandler(void);
#endif

#if defined(USE_EXTI7_IRQ)
extern void EXTI7_IRQHandler(void);
#endif

#if defined(USE_EXTI8_IRQ)
extern void EXTI8_IRQHandler(void);
#endif

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* EXTI Resource Configuration */
typedef struct EXTI_Resources {
  __IOM uint16_t              *reg;        // EXTI peripheral register
  struct pos {
    uint32_t               clr: 16;
    uint32_t               ctl: 16;
  } pos;
  struct pin {
    Driver_GPIO_t            *gpio;        // Pointer to GPIO driver
    GPIO_PIN_t                 pin;        // IO pin
    GPIO_PULL_t             pullup;        // Pin Pull Up
  } pin;
  struct irq {
    IRQn_Type                  num;        // EXTI IRQ Number
    IRQ_Priority_t        priority;        // EXTI interrupt priority
  } irq;
  struct info {
    EXTI_SignalEvent_t    cb_event;        // Event Callback
    uint32_t                 flags;        // Current state flags
  } *info;
} const EXTI_Resources_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

#if defined(USE_EXTI0_IRQ)
/* EXTI0 Information (Run-Time) */
static struct info EXTI0_Info;

/* EXTI0 Resources */
static EXTI_Resources_t EXTI0_Resources = {
  &MMR_EXTI->EI0CFG,
  {
    0U,
    0U
  },
  {
    EXTI0_IRQ_GPIO_PORT,
    EXTI0_IRQ_GPIO_PIN,
    EXTI0_IRQ_PULL_UP
  },
  {
    EXTI0_IRQn,
    EXTI0_IRQ_INT_PRIO
  },
  &EXTI0_Info
};
#endif  // defined(USE_EXTI0_IRQ)

#if defined(USE_EXTI1_IRQ)
/* EXTI1 Information (Run-Time) */
static struct info EXTI1_Info;

/* EXTI1 Resources */
static EXTI_Resources_t EXTI1_Resources = {
  &MMR_EXTI->EI0CFG,
  {
    1U,
    4U,
  },
  {
    EXTI1_IRQ_GPIO_PORT,
    EXTI1_IRQ_GPIO_PIN,
    EXTI1_IRQ_PULL_UP
  },
  {
    EXTI1_IRQn,
    EXTI1_IRQ_INT_PRIO
  },
  &EXTI1_Info
};
#endif  // defined(USE_EXTI1_IRQ)

#if defined(USE_EXTI2_IRQ)
/* EXTI2 Information (Run-Time) */
static struct info EXTI2_Info;

/* EXTI2 Resources */
static EXTI_Resources_t EXTI2_Resources = {
  &MMR_EXTI->EI0CFG,
  {
    2U,
    8U,
  },
  {
    EXTI2_IRQ_GPIO_PORT,
    EXTI2_IRQ_GPIO_PIN,
    EXTI2_IRQ_PULL_UP
  },
  {
    EXTI2_IRQn,
    EXTI2_IRQ_INT_PRIO
  },
  &EXTI2_Info
};
#endif  // defined(USE_EXTI2_IRQ)

#if defined(USE_EXTI4_IRQ)
/* EXTI4 Information (Run-Time) */
static struct info EXTI4_Info;

/* EXTI4 Resources */
static EXTI_Resources_t EXTI4_Resources = {
  &MMR_EXTI->EI1CFG,
  {
    4U,
    0U,
  },
  {
    EXTI4_IRQ_GPIO_PORT,
    EXTI4_IRQ_GPIO_PIN,
    EXTI4_IRQ_PULL_UP
  },
  {
    EXTI4_IRQn,
    EXTI4_IRQ_INT_PRIO
  },
  &EXTI4_Info
};
#endif  // defined(USE_EXTI4_IRQ)

#if defined(USE_EXTI5_IRQ)
/* EXTI5 Information (Run-Time) */
static struct info EXTI5_Info;

/* EXTI5 Resources */
static EXTI_Resources_t EXTI5_Resources = {
  &MMR_EXTI->EI1CFG,
  {
    5U,
    4U,
  },
  {
    EXTI5_IRQ_GPIO_PORT,
    EXTI5_IRQ_GPIO_PIN,
    EXTI5_IRQ_PULL_UP
  },
  {
    EXTI5_IRQn,
    EXTI5_IRQ_INT_PRIO
  },
  &EXTI5_Info
};
#endif  // defined(USE_EXTI5_IRQ)

#if defined(USE_EXTI7_IRQ)
/* EXTI7 Information (Run-Time) */
static struct info EXTI7_Info;

/* EXTI7 Resources */
static EXTI_Resources_t EXTI7_Resources = {
  &MMR_EXTI->EI1CFG,
  {
    7U,
    12U,
  },
  {
    EXTI7_IRQ_GPIO_PORT,
    EXTI7_IRQ_GPIO_PIN,
    EXTI7_IRQ_PULL_UP
  },
  {
    EXTI7_IRQn,
    EXTI7_IRQ_INT_PRIO
  },
  &EXTI7_Info
};
#endif  // defined(USE_EXTI7_IRQ)

#if defined(USE_EXTI8_IRQ)
/* EXTI8 Information (Run-Time) */
static struct info EXTI8_Info;

/* EXTI8 Resources */
static EXTI_Resources_t EXTI8_Resources = {
  &MMR_EXTI->EI2CFG,
  {
    8U,
    0U,
  },
  {
    EXTI8_IRQ_GPIO_PORT,
    EXTI8_IRQ_GPIO_PIN,
    EXTI8_IRQ_PULL_UP
  },
  {
    EXTI8_IRQn,
    EXTI8_IRQ_INT_PRIO
  },
  &EXTI8_Info
};
#endif  // defined(USE_EXTI8_IRQ)

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static int32_t EXTI_Initialize(EXTI_SignalEvent_t cb_event, EXTI_Resources_t *exti)
{
  struct info *info = exti->info;

  if ((info->flags & EXTI_FLAG_INITIALIZED) != 0U) {
    return (EXTI_DRIVER_OK);
  }

  /* Configure EXTI Pins */
  const GPIO_PIN_CFG_t pin_cfg = {
    .mode = GPIO_MODE_INPUT,
    .func = GPIO_PIN_FUNC_0,
    .pull = exti->pin.pullup
  };
  exti->pin.gpio->PinConfig(exti->pin.pin, &pin_cfg);

  /* Clear and Enable EXTI IRQ */
  NVIC_ClearPendingIRQ(exti->irq.num);
  NVIC_SetPriority(exti->irq.num, exti->irq.priority);
  NVIC_EnableIRQ(exti->irq.num);

  info->cb_event = cb_event;
  info->flags    = EXTI_FLAG_INITIALIZED;

  return (EXTI_DRIVER_OK);
}

static int32_t EXTI_Uninitialize(EXTI_Resources_t *exti)
{
  struct info *info = exti->info;

  /* Disable External Interrupt */
  *exti->reg &= (uint16_t)~(EXTI_IRQ_ENABLE << exti->pos.ctl);

  /* Configure EXTI Pins */
  const GPIO_PIN_CFG_t pin_cfg = {
    .mode = GPIO_MODE_ANALOG,
    .func = GPIO_PIN_FUNC_0,
    .pull = GPIO_PULL_DISABLE
  };
  exti->pin.gpio->PinConfig(exti->pin.pin, &pin_cfg);

  /* Clear and Disable EXTI IRQ */
  NVIC_DisableIRQ(exti->irq.num);
  NVIC_ClearPendingIRQ(exti->irq.num);

  info->cb_event = NULL;
  info->flags    = 0U;

  return (EXTI_DRIVER_OK);
}

static int32_t EXTI_Control(uint32_t control, EXTI_Resources_t *exti)
{
  uint32_t mode;
  uint32_t reg;

  if ((exti->info->flags & EXTI_FLAG_INITIALIZED) == 0U) {
    /* EXTI not initialized */
    return (EXTI_DRIVER_ERROR);
  }

  switch (control & EXTI_CONTROL_Msk) {
    case EXTI_MODE_INACTIVE:
      /* Disable External Interrupt */
      *exti->reg &= (uint16_t)~(EXTI_IRQ_ENABLE << exti->pos.ctl);
      break;

    case EXTI_MODE_ACTIVE:
      /* Configure EXTI Mode */
      mode = (control & EXTI_TRG_Msk) >> EXTI_TRG_Pos;
      /* Enable EXTI IRQ */
      reg = *exti->reg & ~((EXTI_IRQ_EN_Msk | EXTI_IRQ_MODE_Msk) << exti->pos.ctl);
      *exti->reg = (uint16_t)(reg | ((EXTI_IRQ_ENABLE | mode) << exti->pos.ctl));
      break;

    default:
      return (EXTI_DRIVER_ERROR_UNSUPPORTED);
  }

  return (EXTI_DRIVER_OK);
}

static void EXTI_IRQHandler(EXTI_Resources_t *exti)
{
  if (exti->info->cb_event != NULL) {
    uint32_t mode = (*exti->reg >> exti->pos.ctl) & EXTI_IRQ_MODE_Msk;
    exti->info->cb_event(mode);
  }

  MMR_EXTI->EICLR = (uint16_t)(EICLR_IRQ0_CLR << exti->pos.clr);
}

/*******************************************************************************
 *  function implementations (scope: module-export)
 ******************************************************************************/

#if defined(USE_EXTI0_IRQ)
/**
 * @brief       EXT IRQ0 Interrupt handler.
 */
void EXTI0_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI0_Resources);
}
#endif

#if defined(USE_EXTI1_IRQ)
/**
 * @brief       EXT IRQ1 Interrupt handler.
 */
void EXTI1_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI1_Resources);
}
#endif

#if defined(USE_EXTI2_IRQ)
/**
 * @brief       EXT IRQ2 Interrupt handler.
 */
void EXTI2_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI2_Resources);
}
#endif

#if defined(USE_EXTI4_IRQ)
/**
 * @brief       EXT IRQ4 Interrupt handler.
 */
void EXTI4_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI4_Resources);
}
#endif

#if defined(USE_EXTI5_IRQ)
/**
 * @brief       EXT IRQ5 Interrupt handler.
 */
void EXTI5_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI5_Resources);
}
#endif

#if defined(USE_EXTI7_IRQ)
/**
 * @brief       EXT IRQ7 Interrupt handler.
 */
void EXTI7_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI7_Resources);
}
#endif

#if defined(USE_EXTI8_IRQ)
/**
 * @brief       EXT IRQ8 Interrupt handler.
 */
void EXTI8_IRQHandler(void)
{
  EXTI_IRQHandler(&EXTI8_Resources);
}
#endif

/*******************************************************************************
 *  global variable definitions (scope: module-exported)
 ******************************************************************************/

#if defined(USE_EXTI0_IRQ)
EXTIx_EXPORT_DRIVER(0);
#endif

#if defined(USE_EXTI1_IRQ)
EXTIx_EXPORT_DRIVER(1);
#endif

#if defined(USE_EXTI2_IRQ)
EXTIx_EXPORT_DRIVER(2);
#endif

#if defined(USE_EXTI4_IRQ)
EXTIx_EXPORT_DRIVER(4);
#endif

#if defined(USE_EXTI5_IRQ)
EXTIx_EXPORT_DRIVER(5);
#endif

#if defined(USE_EXTI7_IRQ)
EXTIx_EXPORT_DRIVER(7);
#endif

#if defined(USE_EXTI8_IRQ)
EXTIx_EXPORT_DRIVER(8);
#endif

#endif // defined(USE_EXTI0_IRQ)...
