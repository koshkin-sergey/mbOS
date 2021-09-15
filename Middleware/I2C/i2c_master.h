/**
 * Copyright (C) 2021 Sergey Koshkin <skoshkin@neoros.ru>
 * All rights reserved
 *
 * File Name  : i2c_master.h
 * Description: Definitions for I2CInterface
 */

#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
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
 *  typedefs and structures (scope: module-local)
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

int32_t I2C_OpenPort(uint32_t port_num);
int32_t I2C_ClosePort(uint32_t port_num);
int32_t I2C_CreateCom(uint32_t        port_num,
                      I2C_Com_t      *com,
                      I2C_BusSpeed_t  bus_speed,
                      uint32_t        slave_addr,
                      uint32_t        timeout);
int32_t I2C_Write(I2C_Com_t *com, uint8_t *buf, uint32_t buf_size);
int32_t I2C_Read(I2C_Com_t *com,
                 uint32_t   addr,
                 uint32_t   addr_size,
                 uint8_t   *buf,
                 uint32_t   buf_size);


#ifdef  __cplusplus
}
#endif

#endif /* I2C_MASTER_H_ */
