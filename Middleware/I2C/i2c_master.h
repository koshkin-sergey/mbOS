/*
 * Copyright (C) 2021 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <Kernel/kernel.h>
#include <CMSIS/Driver/Driver_I2C.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define USE_I2C0
#define USE_I2C1

/* I2C return codes */
#define I2C_OK                        0
#define I2C_ERROR                    -1
#define I2C_ERROR_TIMEOUT            -2
#define I2C_ERROR_RESOURCE           -3
#define I2C_ERROR_PARAMETER          -4
#define I2C_ERROR_ADDRESS_NACK       -5

/* I2C Address Flags */
#define I2C_ADDRESS_7BIT_FORMAT       (0x0000UL)  // 7-bit address flag
#define I2C_ADDRESS_8BIT_FORMAT       (0x0400UL)  // 8-bit address flag
#define I2C_ADDRESS_10BIT_FORMAT      (0x0800UL)  // 10-bit address flag

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef enum I2C_BusSpeed {
  I2C_BUS_SPEED_STANDARD  = ARM_I2C_BUS_SPEED_STANDARD,
  I2C_BUS_SPEED_FAST      = ARM_I2C_BUS_SPEED_FAST,
  I2C_BUS_SPEED_FAST_PLUS = ARM_I2C_BUS_SPEED_FAST_PLUS,
  I2C_BUS_SPEED_HIGH      = ARM_I2C_BUS_SPEED_HIGH,
} I2C_BusSpeed_t;

typedef struct i2c_com {
    uint32_t       port_num;
    uint32_t       slave_addr;
    uint32_t       timeout;
    I2C_BusSpeed_t bus_speed;
    osSemaphore_t  access_sem;
} I2C_Com_t;

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Open I2C Port
 * @param[in]   port_num  port number (hardware specific)
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR_RESOURCE  - Resource error
 *              I2C_ERROR_PARAMETER - Parameter error
 */
int32_t I2C_PortOpen(uint32_t port_num);

/**
 * @brief       Close I2C Port
 * @param[in]   port_num  port number (hardware specific)
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR_PARAMETER - Parameter error
 */
int32_t I2C_PortClose(uint32_t port_num);

/**
 * @brief       Create Communication on I2C port
 * @param[in]   com         COM handle pointer
 * @param[in]   port_num    Port number (hardware specific)
 * @param[in]   bus_speed   Bus Speed
 * @param[in]   slave_addr  Slave address
 * @param[in]   timeout     Timeout for performing an operation in OS ticks
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR           - Unspecified error
 *              I2C_ERROR_RESOURCE  - Resource error
 *              I2C_ERROR_PARAMETER - Parameter error
 */
int32_t I2C_ComCreate(I2C_Com_t      *com,
                      uint32_t        port_num,
                      I2C_BusSpeed_t  bus_speed,
                      uint32_t        slave_addr,
                      uint32_t        timeout);

/**
 * @brief       Lock Communication on I2C port
 * @param[in]   com   COM handle pointer
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR_RESOURCE  - Resource error
 */
int32_t I2C_ComLock(I2C_Com_t *com);

/**
 * @brief       Unlock Communication on I2C port
 * @param[in]   com   COM handle pointer
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR_RESOURCE  - Resource error
 */
int32_t I2C_ComUnLock(I2C_Com_t *com);

/**
 * @brief       Write buffer on I2C COM
 * @param[in]   com       COM handle pointer
 * @param[in]   buf       Pointer to buffer to write
 * @param[in]   buf_size  Bytes to write
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR           - Unspecified error
 *              I2C_ERROR_RESOURCE  - Resource error
 *              I2C_ERROR_PARAMETER - Parameter error
 *              I2C_ERROR_TIMEOUT   - Timeout occurred
 */
int32_t I2C_Write(I2C_Com_t *com, const uint8_t *buf, uint32_t buf_size);

/**
 * @brief       Read buffer on I2C COM
 * @param[in]   com         COM handle pointer
 * @param[in]   addr        Peripheral start address
 * @param[in]   addr_size   Number of bytes of start address
 * @param[out]  buf         Pointer to buffer to fill
 * @param[out   buf_size    Bytes to receive
 * @return      I2C_OK              - Operation succeeded
 *              I2C_ERROR           - Unspecified error
 *              I2C_ERROR_RESOURCE  - Resource error
 *              I2C_ERROR_PARAMETER - Parameter error
 *              I2C_ERROR_TIMEOUT   - Timeout occurred
 */
int32_t I2C_Read(I2C_Com_t *com,
                 uint32_t   addr,
                 uint32_t   addr_size,
                 uint8_t   *buf,
                 uint32_t   buf_size);


#ifdef  __cplusplus
}
#endif

#endif /* I2C_MASTER_H_ */
