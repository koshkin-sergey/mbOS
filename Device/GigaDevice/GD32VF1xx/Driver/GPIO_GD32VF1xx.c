/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: GPIO Driver for GigaDevice GD32VF1xx
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Driver/GPIO_GD32VF1xx.h>
#include <asm/gd32vf103xx_gpio.h>
#include <asm/gd32vf103xx_rcu.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define GPIOx_EXPORT_DRIVER(x)                                                 \
static int32_t  GPIO##x##_Initialize(void)                                      {return (GPIO_Initialize   (&GPIO##x##_Resources));            } \
static int32_t  GPIO##x##_Uninitialize(void)                                    {return (GPIO_Uninitialize (&GPIO##x##_Resources));            } \
static int32_t  GPIO##x##_PinConfig(GPIO_Pin_t pin, uint32_t cfg)               {return (GPIO_PinConfig    (pin, cfg, &GPIO##x##_Resources));  } \
static uint32_t GPIO##x##_PortRead(void)                                        {return (GPIO_PortRead     (&GPIO##x##_Resources));            } \
static void     GPIO##x##_PortWrite(uint32_t value)                             {        GPIO_PortWrite    (value, &GPIO##x##_Resources);      } \
static uint32_t GPIO##x##_PinRead(GPIO_Pin_t pin)                               {return (GPIO_PinRead      (pin, &GPIO##x##_Resources));       } \
static void     GPIO##x##_PinWrite(GPIO_Pin_t pin, GPIO_PinOut_t value)         {        GPIO_PinWrite     (pin, value, &GPIO##x##_Resources); } \
static void     GPIO##x##_PinToggle(GPIO_Pin_t pin)                             {        GPIO_PinToggle    (pin, &GPIO##x##_Resources);        } \
                                                                               \
Driver_GPIO_t Driver_GPIO##x = {                                               \
  GPIO##x##_Initialize,                                                        \
  GPIO##x##_Uninitialize,                                                      \
  GPIO##x##_PinConfig,                                                         \
  GPIO##x##_PortRead,                                                          \
  GPIO##x##_PortWrite,                                                         \
  GPIO##x##_PinRead,                                                           \
  GPIO##x##_PinWrite,                                                          \
  GPIO##x##_PinToggle                                                          \
}

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* GPIO Resource Configuration */
typedef struct GPIO_Resources {
  GPIO_t      *mmr;
  uint32_t  rcu_en;
} const GPIO_Resources_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

/* GPIOA Resources */
static GPIO_Resources_t GPIOA_Resources = {
  GPIOA,
  APB2EN_PAEN,
};

/* GPIOB Resources */
static GPIO_Resources_t GPIOB_Resources = {
  GPIOB,
  APB2EN_PBEN,
};

/* GPIOC Resources */
static GPIO_Resources_t GPIOC_Resources = {
  GPIOC,
  APB2EN_PCEN,
};

/* GPIOD Resources */
static GPIO_Resources_t GPIOD_Resources = {
  GPIOD,
  APB2EN_PDEN,
};

/* GPIOE Resources */
static GPIO_Resources_t GPIOE_Resources = {
  GPIOE,
  APB2EN_PEEN,
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static
int32_t GPIO_Initialize(GPIO_Resources_t *rs)
{
  RCU->APB2EN |= rs->rcu_en;

  return (GPIO_DRIVER_OK);
}

static
int32_t GPIO_Uninitialize(GPIO_Resources_t *rs)
{
  RCU->APB2EN &= ~rs->rcu_en;

  return (GPIO_DRIVER_OK);
}

static
int32_t GPIO_PinConfig(GPIO_Pin_t pin, uint32_t cfg, GPIO_Resources_t *rs)
{
  __O uint32_t *reg;
  uint32_t val;
  uint32_t offset;
  GPIO_t *mmr = rs->mmr;

  offset = (pin & 0x7) * 4;
  reg = pin < 8 ? &mmr->CTL0 : &mmr->CTL1;
  val = *reg & ~(0xFUL << offset);

  *reg = val | (0x1UL << offset);

  return (GPIO_DRIVER_OK);
}

static
uint32_t GPIO_PortRead(GPIO_Resources_t *rs)
{
  return (rs->mmr->ISTAT & ISTAT_ISTAT_Msk);
}

static
void GPIO_PortWrite(uint32_t value, GPIO_Resources_t *rs)
{
  rs->mmr->OCTL = value & OCTL_OCTL_Msk;
}

static
uint32_t GPIO_PinRead(GPIO_Pin_t pin, GPIO_Resources_t *rs)
{
  return ((rs->mmr->ISTAT >> pin) & 0x1UL);
}

static
void GPIO_PinWrite(GPIO_Pin_t pin, GPIO_PinOut_t value, GPIO_Resources_t *rs)
{
  __O uint32_t *reg;
  GPIO_t *mmr = rs->mmr;

  reg = value == 0 ? &mmr->BC : &mmr->BOP;
  *reg = 1UL << pin;
}

static
void GPIO_PinToggle(GPIO_Pin_t pin, GPIO_Resources_t *rs)
{
  rs->mmr->OCTL ^= (1UL << pin);
}

/*******************************************************************************
 *  global variable definitions  (scope: module-exported)
 ******************************************************************************/

GPIOx_EXPORT_DRIVER(A);
GPIOx_EXPORT_DRIVER(B);
GPIOx_EXPORT_DRIVER(C);
GPIOx_EXPORT_DRIVER(D);
GPIOx_EXPORT_DRIVER(E);
