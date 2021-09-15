/**
 * Copyright (C) 2021 Sergey Koshkin <skoshkin@neoros.ru>
 * All rights reserved
 *
 * File Name  : i2c_master.c
 * Description: Definitions for I2C Interface
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Kernel/kernel.h>

#include "i2c_master.h"

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define I2C_EVENT_ALL                 (ARM_I2C_EVENT_TRANSFER_DONE       | \
                                       ARM_I2C_EVENT_TRANSFER_INCOMPLETE | \
                                       ARM_I2C_EVENT_ADDRESS_NACK        | \
                                       ARM_I2C_EVENT_ARBITRATION_LOST    | \
                                       ARM_I2C_EVENT_BUS_ERROR              )

#define I2C_ADDRESS_7BIT_MASK         (0x7FUL)
#define I2C_ADDRESS_10BIT_MASK        (0x3FFUL)

/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct I2C_PortStatus {
    uint32_t open     : 1;    // Port: 0=Close, 1=Open
    uint32_t reserved : 31;   // Reserved
} I2C_PortStatus_t;

typedef struct I2C_PortInfo {
    I2C_PortStatus_t  status;
    I2C_Com_t        *curr_com;
    osSemaphore_t     access_sem;
    osEventFlags_t    event_flags;
} I2C_PortInfo_t;

typedef struct I2C_PortResources {
    ARM_DRIVER_I2C        *driver;    // CMSIS Driver for I2C
    ARM_I2C_SignalEvent_t  cb_event;  // Driver Event Callback
    I2C_PortInfo_t        *info;      // I2C Port Info
} const I2C_PortResources_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

#if defined (USE_I2C0)

static void I2C0_SignalEvent(uint32_t event);

/* I2C0 Information (Run-Time) */
static I2C_PortInfo_t I2C0_PortInfo;

/* I2C Driver */
extern ARM_DRIVER_I2C ARM_Driver_I2C_(0);

/* I2C0 Resources */
static I2C_PortResources_t I2C0_PortResources = {
    &ARM_Driver_I2C_(0),
    I2C0_SignalEvent,
    &I2C0_PortInfo,
};

#endif  /* defined (USE_I2C0) */

#if defined (USE_I2C1)

static void I2C1_SignalEvent(uint32_t event);

/* I2C1 Information (Run-Time) */
static I2C_PortInfo_t I2C1_PortInfo;

/* I2C Driver */
extern ARM_DRIVER_I2C ARM_Driver_I2C_(1);

/* I2C1 Resources */
static I2C_PortResources_t I2C1_PortResources = {
    &ARM_Driver_I2C_(1),
    I2C1_SignalEvent,
    &I2C1_PortInfo,
};

#endif  /* defined (USE_I2C1) */

static I2C_PortResources_t *ports[] = {
#if defined (USE_I2C0)
    &I2C0_PortResources,
#else
    NULL,
#endif
#if defined (USE_I2C1)
    &I2C1_PortResources,
#else
    NULL,
#endif
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

#if defined (USE_I2C0)

static void I2C0_SignalEvent(uint32_t event)
{
  osEventFlagsSet(&I2C0_PortInfo.event_flags, event);
}

#endif

#if defined (USE_I2C0)

static void I2C1_SignalEvent(uint32_t event)
{
  osEventFlagsSet(&I2C1_PortInfo.event_flags, event);
}

#endif

static I2C_PortResources_t* GetPort(uint32_t port_num)
{
  I2C_PortResources_t *port;

  if (port_num >= (sizeof(ports)/sizeof(ports[0]))) {
    return (NULL);
  }

  port = ports[port_num];

  return (port);
}

static
int32_t WaitOperation(I2C_PortResources_t *port, int32_t err, uint32_t timeout)
{
  uint32_t flags;
   int32_t rc = I2C_ERROR_RESOURCE;

  if (err == ARM_DRIVER_OK) {
    flags = osEventFlagsWait(&port->info->event_flags, I2C_EVENT_ALL,
                             osFlagsWaitAny, timeout);
    if ((flags & osFlagsError) != 0U && flags == osFlagsErrorTimeout) {
        rc = I2C_ERROR_TIMEOUT;
    }
    else if (flags & ARM_I2C_EVENT_TRANSFER_DONE) {
      if (flags & ARM_I2C_EVENT_ADDRESS_NACK) {
        rc = I2C_ERROR_ADDRESS_NACK;
      }
      else {
        rc = port->driver->GetDataCount();
      }
    }
  }
  else if (err == ARM_DRIVER_ERROR_BUSY) {
    rc = I2C_ERROR_TIMEOUT;
  }

  return (rc);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

int32_t I2C_OpenPort(uint32_t port_num)
{
  osSemaphoreAttr_t    sem_attr;
  osEventFlagsAttr_t   evf_attr;
  I2C_PortResources_t *port;

  port = GetPort(port_num);
  if (port == NULL) {
    return (I2C_ERROR_PARAMETER);
  }

  /* Check if port was already open */
  if (port->info->status.open == 1U) {
    return (I2C_OK);
  }

  /* Create Access Semaphore */
  sem_attr.name      = NULL;
  sem_attr.attr_bits = 0U;
  sem_attr.cb_mem    = &port->info->access_sem;
  sem_attr.cb_size   = sizeof(port->info->access_sem);
  if (osSemaphoreNew(1U, 0U, &sem_attr) == NULL) {
    return (I2C_ERROR_RESOURCE);
  }

  /* Create Event Flags */
  evf_attr.name      = NULL;
  evf_attr.attr_bits = 0U;
  evf_attr.cb_mem    = &port->info->event_flags;
  evf_attr.cb_size   = sizeof(port->info->event_flags);
  if (osEventFlagsNew(&evf_attr) == NULL) {
    return (I2C_ERROR_RESOURCE);
  }

  port->driver->Initialize(port->cb_event);
  port->driver->PowerControl(ARM_POWER_FULL);

  port->info->curr_com    = NULL;
  port->info->status.open = 1U;
  osSemaphoreRelease(&port->info->access_sem);

  return (I2C_OK);
}

int32_t I2C_ClosePort(uint32_t port_num)
{
  I2C_PortResources_t *port;

  port = GetPort(port_num);
  if (port == NULL) {
    return (I2C_ERROR_PARAMETER);
  }

  /* Check if port was already closed */
  if (port->info->status.open == 0U) {
    return (I2C_OK);
  }

  port->driver->PowerControl(ARM_POWER_OFF);
  port->driver->Uninitialize();

  osEventFlagsDelete(&port->info->event_flags);
  osSemaphoreDelete(&port->info->access_sem);
  port->info->status.open = 0U;

  return (I2C_OK);
}

int32_t I2C_CreateCom(uint32_t        port_num,
                      I2C_Com_t      *com,
                      I2C_BusSpeed_t  bus_speed,
                      uint32_t        slave_addr,
                      uint32_t        timeout)
{
  I2C_PortResources_t *port;
  int32_t              rc = I2C_OK;

  port = GetPort(port_num);
  if (port == NULL) {
    return (I2C_ERROR_PARAMETER);
  }

  /* Check if port was open */
  if (port->info->status.open == 0U) {
    return (I2C_ERROR);
  }

  if (osSemaphoreAcquire(&port->info->access_sem, osWaitForever) != osOK) {
    return (I2C_ERROR_RESOURCE);
  }

  /* Create Access Semaphore */
  osSemaphoreAttr_t sem_attr = {
      .name      = NULL,
      .attr_bits = 0U,
      .cb_mem    = &com->access_sem,
      .cb_size   = sizeof(com->access_sem),
  };

  if (osSemaphoreNew(1U, 0U, &sem_attr) != NULL) {
    com->port_num   = port_num;
    com->bus_speed  = bus_speed;
    com->timeout    = timeout;

    if ((slave_addr & I2C_ADDRESS_8BIT_FORMAT) != 0U) {
      com->slave_addr = (slave_addr >> 1U) & I2C_ADDRESS_7BIT_MASK;
    }
    else if ((slave_addr & I2C_ADDRESS_10BIT_FORMAT) != 0U) {
      com->slave_addr = slave_addr & I2C_ADDRESS_10BIT_MASK;
    }
    else {
      com->slave_addr = slave_addr & I2C_ADDRESS_7BIT_MASK;
    }


    osSemaphoreRelease(&com->access_sem);
  }
  else {
    rc = I2C_ERROR_RESOURCE;
  }

  osSemaphoreRelease(&port->info->access_sem);

  return (rc);
}

int32_t I2C_Write(I2C_Com_t *com, uint8_t *buf, uint32_t buf_size)
{
   int32_t rc;
   int32_t err;
  uint32_t timeout;

  if (com == NULL || buf == NULL || buf_size == 0U) {
    return (I2C_ERROR_PARAMETER);
  }

  if (osSemaphoreAcquire(&com->access_sem, osWaitForever) != osOK) {
    return (I2C_ERROR_RESOURCE);
  }

  I2C_PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (I2C_ERROR_RESOURCE);
  }

  if (osSemaphoreAcquire(&port->info->access_sem, osWaitForever) == osOK) {
    if (port->info->curr_com != com) {
      port->driver->Control(ARM_I2C_BUS_SPEED, com->bus_speed);
      port->info->curr_com = com;
    }

    timeout = osKernelGetTickCount() + com->timeout;

    do {
      err = port->driver->MasterTransmit(com->slave_addr, buf, buf_size, false);
      rc = WaitOperation(port, err, com->timeout);
      if (rc == I2C_ERROR_TIMEOUT) {
        osDelay(1U);
      }
      else {
        break;
      }
    } while (time_after(timeout, osKernelGetTickCount()));

    if (rc == I2C_ERROR_TIMEOUT) {
      port->driver->Control(ARM_I2C_ABORT_TRANSFER, 0U);
    }

    osSemaphoreRelease(&port->info->access_sem);
  }
  else {
    rc = I2C_ERROR_RESOURCE;
  }

  osSemaphoreRelease(&com->access_sem);

  return (rc);
}

int32_t I2C_Read(I2C_Com_t *com,
                 uint32_t   addr,
                 uint32_t   addr_size,
                 uint8_t   *buf,
                 uint32_t   buf_size)
{
   int32_t rc;
   int32_t err;
  uint32_t timeout;


  if (com == NULL || buf == NULL || buf_size == 0U || addr_size > 4U) {
    return (I2C_ERROR_PARAMETER);
  }

  if (osSemaphoreAcquire(&com->access_sem, osWaitForever) != osOK) {
    return (I2C_ERROR);
  }

  I2C_PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (I2C_ERROR);
  }

  if (osSemaphoreAcquire(&port->info->access_sem, osWaitForever) == osOK) {
    if (port->info->curr_com != com) {
      port->driver->Control(ARM_I2C_BUS_SPEED, com->bus_speed);
      port->info->curr_com = com;
    }

    timeout = osKernelGetTickCount() + com->timeout;

    do {
      if (addr_size != 0U) {
        err = port->driver->MasterTransmit(com->slave_addr, (uint8_t *)&addr,
                                           addr_size, true);
        rc = WaitOperation(port, err, com->timeout);
        if (rc == I2C_ERROR_TIMEOUT) {
          osDelay(1U);
          continue;
        }

        if (rc != addr_size) {
          break;
        }
      }

      err = port->driver->MasterReceive(com->slave_addr, buf, buf_size, false);
      rc = WaitOperation(port, err, com->timeout);
      if (rc == I2C_ERROR_TIMEOUT) {
        osDelay(1U);
      }
      else {
        break;
      }
    } while (time_after(timeout, osKernelGetTickCount()));

    if (rc == I2C_ERROR_TIMEOUT) {
      port->driver->Control(ARM_I2C_ABORT_TRANSFER, 0U);
    }

    osSemaphoreRelease(&port->info->access_sem);
  }
  else {
    rc = I2C_ERROR;
  }

  osSemaphoreRelease(&com->access_sem);

  return (rc);
}
