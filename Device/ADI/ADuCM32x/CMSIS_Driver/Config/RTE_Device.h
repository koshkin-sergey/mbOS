/*
 * Copyright (C) 2017 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 * Project: RTE Device Configuration for ADI ADuCM32x
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef HAL_CONFIG_H_
#define HAL_CONFIG_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "ADuCM320.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/*- Interrupt Priority -------------------------------------------------------*/
#define HAL_ADC_INT_PRIO                1U
#define HAL_PWM_INT_PRIO                1U
#define HAL_SPI_INT_PRIO                1U
#define HAL_USART_INT_PRIO              1U
#define HAL_I2C_INT_PRIO                1U
#define HAL_TMR_INT_PRIO                0U

// <e> USART0 (Universal synchronous asynchronous receiver transmitter) [Driver_USART0]
// </e> USART0 (Universal synchronous asynchronous receiver transmitter) [Driver_USART0]
#define RTE_USART0                      0

// USART0_TX Pin P1.1
#define RTE_USART0_TX_PORT              GPIO_PORT_1
#define RTE_USART0_TX_PIN               GPIO_PIN_1
#define RTE_USART0_TX_FUNC              GPIO_PIN_FUNC_1
// USART0_RX Pin P1.0
#define RTE_USART0_RX_PORT              GPIO_PORT_1
#define RTE_USART0_RX_PIN               GPIO_PIN_0
#define RTE_USART0_RX_FUNC              GPIO_PIN_FUNC_1

// <e> I2C0 (Inter-integrated Circuit Interface 0) [Driver_I2C0]
// <i> Configuration settings for Driver_I2C0 in component ::Drivers:I2C
// </e> I2C0 (Inter-integrated Circuit Interface 0) [Driver_I2C0]
#define RTE_I2C0                        0

// I2C0_SCL Pin P0.4
#define RTE_I2C0_SCL_PORT               GPIO_PORT_0
#define RTE_I2C0_SCL_PIN                GPIO_PIN_4
#define RTE_I2C0_SCL_FUNC               GPIO_PIN_FUNC_1
// I2C0_SDA Pin P0.5
#define RTE_I2C0_SDA_PORT               GPIO_PORT_0
#define RTE_I2C0_SDA_PIN                GPIO_PIN_5
#define RTE_I2C0_SDA_FUNC               GPIO_PIN_FUNC_1

// <e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::Drivers:I2C
// </e> I2C1 (Inter-integrated Circuit Interface 1) [Driver_I2C1]
#define RTE_I2C1                        0

// I2C1_SCL Pin P0.6
#define RTE_I2C1_SCL_PORT               GPIO_PORT_0
#define RTE_I2C1_SCL_PIN                GPIO_PIN_6
#define RTE_I2C1_SCL_FUNC               GPIO_PIN_FUNC_1
// I2C1_SDA Pin P0.7
#define RTE_I2C1_SDA_PORT               GPIO_PORT_0
#define RTE_I2C1_SDA_PIN                GPIO_PIN_7
#define RTE_I2C1_SDA_FUNC               GPIO_PIN_FUNC_1

//------------- <<< end of configuration section >>> ---------------------------

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

__STATIC_INLINE
void NVIC_Enable_IRQ(IRQn_Type IRQn, uint32_t priority)
{
  NVIC_SetPriority(IRQn, priority);
  NVIC_EnableIRQ(IRQn);
}

__STATIC_INLINE
void NVIC_Disable_IRQ(IRQn_Type IRQn)
{
  NVIC_DisableIRQ(IRQn);
}

#endif /* HAL_CONFIG_H_ */

/* ----------------------------- End of file ---------------------------------*/
