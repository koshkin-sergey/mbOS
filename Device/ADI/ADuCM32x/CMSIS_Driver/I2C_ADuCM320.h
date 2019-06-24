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
 * Project: I2C Driver Definitions for ADI ADuCM32x
 */

#ifndef I2C_ADUCM320_H_
#define I2C_ADUCM320_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "RTE_Device.h"
#include "CLK_ADuCM320.h"
#include "GPIO_ADuCM320.h"
#include "Driver_I2C.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#if ((defined(RTE_Drivers_I2C0) || \
      defined(RTE_Drivers_I2C1))   \
     && (RTE_I2C0 == 0)            \
     && (RTE_I2C1 == 0))
  #error "I2C not configured in RTE_Device.h!"
#endif

/* I2C0 configuration definitions */
#if defined (RTE_I2C0) && (RTE_I2C0 == 1)
  #define USE_I2C0

  #define I2C0_SCL_GPIO_PORT        RTE_I2C0_SCL_PORT
  #define I2C0_SCL_GPIO_PIN         RTE_I2C0_SCL_PIN
  #define I2C0_SCL_GPIO_FUNC        RTE_I2C0_SCL_FUNC
  #define I2C0_SDA_GPIO_PORT        RTE_I2C0_SDA_PORT
  #define I2C0_SDA_GPIO_PIN         RTE_I2C0_SDA_PIN
  #define I2C0_SDA_GPIO_FUNC        RTE_I2C0_SDA_FUNC
#endif

/* I2C1 configuration definitions */
#if defined (RTE_I2C1) && (RTE_I2C1 == 1)

  #if !defined(pADI_I2C1)
    #error "I2C1 not available for selected device!"
  #endif

  #define USE_I2C1

  #define I2C1_SCL_GPIO_PORT        RTE_I2C1_SCL_PORT
  #define I2C1_SCL_GPIO_PIN         RTE_I2C1_SCL_PIN
  #define I2C1_SCL_GPIO_FUNC        RTE_I2C1_SCL_FUNC
  #define I2C1_SDA_GPIO_PORT        RTE_I2C1_SDA_PORT
  #define I2C1_SDA_GPIO_PIN         RTE_I2C1_SDA_PIN
  #define I2C1_SDA_GPIO_FUNC        RTE_I2C1_SDA_FUNC
#endif

/* I2C Driver state flags */
#define I2C_FLAG_INIT             (1UL << 0)    // Driver initialized
#define I2C_FLAG_POWER            (1UL << 1)    // Driver power on
#define I2C_FLAG_SETUP            (1UL << 2)    // Master configured, clock set
#define I2C_FLAG_SLAVE_RX         (1UL << 3)    // Slave receive registered
#define I2C_FLAG_SLAVE_ADDR       (1UL << 4)    // Addressed Slave
#define I2C_FLAG_TX_RESTART       (1UL << 5)
#define I2C_FLAG_RX_RESTART       (1UL << 6)
#define I2C_FLAG_ADDRESS_NACK     (1UL << 7)
#define I2C_FLAG_SLAVE_BUF_EMPTY  (1UL << 8)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

/* I2C Pin Configuration */
typedef const struct _I2C_PINS {
  const GPIO_PIN_ID_t  *scl;                // SCL Pin identifier
  const GPIO_PIN_ID_t  *sda;                // SDA Pin identifier
} I2C_PIN;

/* I2C Control Information */
typedef struct {
  ARM_I2C_SignalEvent_t cb_event;           // Event callback
  ARM_I2C_STATUS        status;             // Status flags
  uint32_t              flags;              // Control and state flags
  uint8_t              *data;               // Data to transfer
  int32_t               num;                // Number of bytes to transfer
  int32_t               cnt;                // Data transfer counter
  int32_t               data_cnt;
} I2C_CTRL;

/* I2C Resource Configuration */
typedef struct {
  ADI_I2C_TypeDef      *reg;                // I2C register interface
  I2C_PIN               pin;                // I2C pin configuration
  IRQn_Type             i2c_master_irq;     // I2C Master Event IRQ Number
  IRQn_Type             i2c_slave_irq;      // I2C Slave Event IRQ Number
  CLK_PERIPH            clk_periph;         // I2C clock user control
  I2C_CTRL             *ctrl;               // Run-Time control information
} const I2C_RESOURCES;

/*******************************************************************************
 *  exported variables
 ******************************************************************************/

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

#endif /* I2C_ADUCM320_H_ */

/* ----------------------------- End of file ---------------------------------*/
