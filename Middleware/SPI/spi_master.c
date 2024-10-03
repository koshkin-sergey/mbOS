/**
 * Copyright (C) 2024 Sergey Koshkin <skoshkin@neoros.ru>
 * All rights reserved
 *
 * File Name  : spi_master.c
 * Description: Реализация интерфейса SPI
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include "spi_master.h"
#include <device_config.h>

/*******************************************************************************
 *  defines and macros (scope: module-local)
 ******************************************************************************/

#define SPI_EVENT_ALL                 (SPI_EVENT_TRANSFER_COMPLETE | \
                                       SPI_EVENT_DATA_LOST         | \
                                       SPI_EVENT_MODE_FAULT          )

#define SPIx_RESOURCES(x)                                                      \
/* Information (Run-Time) */                                                   \
static PortInfo_t SPI##x##_PortInfo;                                           \
/* Event Callback */                                                           \
static void SPI##x##_SignalEvent(uint32_t event) {                             \
  osEventFlagsSet(&SPI##x##_PortInfo.event_flags, event);                      \
}                                                                              \
/* Driver */                                                                   \
extern DRIVER_SPI Driver_SPI_(x);                                              \
/* Resources */                                                                \
static PortResources_t SPI##x##_PortResources = {                              \
    &Driver_SPI_(x),                                                           \
    SPI##x##_SignalEvent,                                                      \
    &SPI##x##_PortInfo,                                                        \
}


/*******************************************************************************
 *  typedefs and structures (scope: module-local)
 ******************************************************************************/

typedef struct PortStatus {
  uint32_t open     : 1;          // Port: 0=Close, 1=Open
  uint32_t lock     : 1;          // Port: 0=Unlock, 1=Lock
  uint32_t reserved : 30;         // Reserved
} PortStatus_t;

typedef struct PortInfo {
  PortStatus_t    status;
  SPI_Com_t      *curr_com;
  osSemaphore_t   access_sem;
  osEventFlags_t  event_flags;
} PortInfo_t;

typedef struct PortResources {
  DRIVER_SPI        *driver;      // CMSIS Driver for SPI
  SPI_SignalEvent_t  cb_event;    // Driver Event Callback
  PortInfo_t        *info;        // Port Info
} const PortResources_t;

/*******************************************************************************
 *  global variable definitions (scope: module-local)
 ******************************************************************************/

#if defined (DEV_SPI0) && (DEV_SPI0 == 1)
  SPIx_RESOURCES(0);
#endif  /* defined (DEV_SPI0) */

#if defined (DEV_SPI1) && (DEV_SPI1 == 1)
  SPIx_RESOURCES(1);
#endif  /* defined (DEV_SPI1) */

static PortResources_t *ports[DEV_SPI_NUMBER] = {
#if defined (DEV_SPI0) && (DEV_SPI0 == 1)
    &SPI0_PortResources,
#else
    NULL,
#endif
#if defined (DEV_SPI1) && (DEV_SPI1 == 1)
    &SPI1_PortResources,
#else
    NULL,
#endif
};

/*******************************************************************************
 *  function implementations (scope: module-local)
 ******************************************************************************/

static PortResources_t* GetPort(uint32_t port_num)
{
  PortResources_t *port;

  if (port_num >= (sizeof(ports)/sizeof(ports[0]))) {
    return (NULL);
  }

  port = ports[port_num];

  return (port);
}

static
int32_t WaitOperation(PortResources_t *port, uint32_t timeout)
{
  uint32_t flags;
  int32_t  rc = SPI_OK;

  flags = osEventFlagsWait(&port->info->event_flags, SPI_EVENT_ALL,
                           osFlagsWaitAny, timeout);
  if ((flags & osFlagsError) != 0U) {
    if (flags == osFlagsErrorTimeout) {
      port->driver->Control(SPI_ABORT_TRANSFER, 0U);
      rc = SPI_ERROR_TIMEOUT;
    }
    else {
      rc = SPI_ERROR;
    }
  }
  else {
    /* Check if all data transferred */
    if ((flags & ~SPI_EVENT_TRANSFER_COMPLETE) != 0U) {
      port->driver->Control(SPI_ABORT_TRANSFER, 0U);
      rc = SPI_ERROR;
    }
  }

  return (rc);
}

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

/**
 * @brief       Open SPI Port
 * @param[in]   port_num  port number (hardware specific)
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_RESOURCE  - Resource error
 *              SPI_ERROR_PARAMETER - Parameter error
 */
int32_t SPI_PortOpen(uint32_t port_num)
{
  PortResources_t *port;

  port = GetPort(port_num);
  if (port == NULL) {
    return (SPI_ERROR_PARAMETER);
  }

  /* Check if port was already open */
  if (port->info->status.open == 1U) {
    return (SPI_OK);
  }

  /* Create Access Semaphore */
  osSemaphoreAttr_t sem_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &port->info->access_sem,
    .cb_size   = sizeof(port->info->access_sem),
  };
  if (osSemaphoreNew(1U, 0U, &sem_attr) == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  /* Create Event Flags */
  osEventFlagsAttr_t evf_attr = {
    .name      = NULL,
    .attr_bits = 0U,
    .cb_mem    = &port->info->event_flags,
    .cb_size   = sizeof(port->info->event_flags),
  };
  if (osEventFlagsNew(&evf_attr) == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  port->driver->Initialize(port->cb_event);
  port->driver->PowerControl(POWER_FULL);

  port->info->curr_com    = NULL;
  port->info->status.open = 1U;

  osSemaphoreRelease(&port->info->access_sem);

  return (SPI_OK);
}

/**
 * @brief       Close SPI Port
 * @param[in]   port_num  port number (hardware specific)
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_PARAMETER - Parameter error
 */
int32_t SPI_PortClose(uint32_t port_num)
{
  PortResources_t *port;

  port = GetPort(port_num);
  if (port == NULL) {
    return (SPI_ERROR_PARAMETER);
  }

  /* Check if port was already closed */
  if (port->info->status.open == 0U) {
    return (SPI_OK);
  }

  port->driver->PowerControl(POWER_OFF);
  port->driver->Uninitialize();

  osEventFlagsDelete(&port->info->event_flags);
  osSemaphoreDelete(&port->info->access_sem);
  port->info->status.open = 0U;

  return (SPI_OK);
}

/**
 * @brief       Create Communication on SPI port
 * @param[in]   com         COM handle pointer
 * @param[in]   port_num    Port number (hardware specific)
 * @param[in]   cfg         Communication Config
 * @param[in]   hooks       Pre/Post Callback functions
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR           - Unspecified error
 *              SPI_ERROR_RESOURCE  - Resource error
 *              SPI_ERROR_PARAMETER - Parameter error
 */
int32_t SPI_ComCreate(SPI_Com_t           *com,
                      uint32_t             port_num,
                      const SPI_Com_Cfg_t *cfg,
                      const SPI_Hooks_t   *hooks)
{
  PortResources_t *port;

  port = GetPort(port_num);
  if (port == NULL || com == NULL || cfg == NULL) {
    return (SPI_ERROR_PARAMETER);
  }

  /* Check if port was open */
  if (port->info->status.open == 0U) {
    return (SPI_ERROR);
  }

  if (osSemaphoreAcquire(&port->info->access_sem, osWaitForever) != osOK) {
    return (SPI_ERROR_RESOURCE);
  }

  com->port_num = port_num;
  com->com_cfg  = cfg;
  com->hooks    = hooks;

  osSemaphoreRelease(&port->info->access_sem);

  return (SPI_OK);
}

/**
 * @brief       Lock Communication on SPI port
 * @param[in]   com   COM handle pointer
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_RESOURCE  - Resource error
 */
int32_t SPI_ComLock(SPI_Com_t *com)
{
  int32_t rc = SPI_OK;

  PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  /* Check if port was open */
  if (port->info->status.open == 0U) {
    return (SPI_ERROR);
  }

  /* Check if port lock */
  if (port->info->status.lock != 0U) {
    return (SPI_OK);
  }

  if (osSemaphoreAcquire(&port->info->access_sem, osWaitForever) == osOK) {
    if (port->info->curr_com != com) {
      const SPI_Com_Cfg_t *cfg = com->com_cfg;
      port->driver->Control(cfg->drv_cfg, cfg->bus_speed);
      port->info->curr_com = com;
    }

    if (com->hooks != NULL && com->hooks->pre_callback != NULL) {
      com->hooks->pre_callback(com->hooks->pre_param);
    }

    port->info->status.lock = 1U;
  }
  else {
    rc = SPI_ERROR_RESOURCE;
  }

  return (rc);
}

/**
 * @brief       Unlock Communication on SPI port
 * @param[in]   com   COM handle pointer
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_RESOURCE  - Resource error
 */
int32_t SPI_ComUnLock(SPI_Com_t *com)
{
  int32_t rc = SPI_OK;

  PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  /* Check if port was open */
  if (port->info->status.open == 0U) {
    return (SPI_ERROR);
  }

  /* Check if port lock */
  if (port->info->status.lock == 0U) {
    return (SPI_OK);
  }

  port->info->status.lock = 0U;

  if (com->hooks != NULL && com->hooks->post_callback != NULL) {
    com->hooks->post_callback(com->hooks->post_param);
  }

  if (osSemaphoreRelease(&port->info->access_sem) != osOK) {
    rc = SPI_ERROR_RESOURCE;
  }

  return (rc);
}

/**
 * @brief       Send data to SPI COM
 * @param[in]   com       COM handle pointer
 * @param[in]   buf       Pointer to buffer with data to send to SPI COM
 * @param[in]   num       Number of data items to send
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR           - Unspecified error
 *              SPI_ERROR_RESOURCE  - Resource error
 *              SPI_ERROR_PARAMETER - Parameter error
 *              SPI_ERROR_TIMEOUT   - Timeout occurred
 */
int32_t SPI_ComSend(SPI_Com_t *com, const void *buf, uint32_t num)
{
  int32_t rc;

  if (com == NULL || buf == NULL || num == 0U) {
    return (SPI_ERROR_PARAMETER);
  }

  PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  /* Check if port lock */
  if (port->info->status.lock == 0U) {
    return (SPI_ERROR);
  }

  rc = port->driver->Send(buf, num);
  if (rc == DRIVER_OK) {
    rc = WaitOperation(port, com->timeout);
  }
  else {
    rc = SPI_ERROR;
  }

  return (rc);
}

/**
 * @brief       Receive data from SPI COM
 * @param[in]   com         COM handle pointer
 * @param[out]  buf         Pointer to buffer for data to receive from SPI COM
 * @param[in]   num         Number of data items to receive
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR           - Unspecified error
 *              SPI_ERROR_RESOURCE  - Resource error
 *              SPI_ERROR_PARAMETER - Parameter error
 *              SPI_ERROR_TIMEOUT   - Timeout occurred
 */
int32_t SPI_ComReceive(SPI_Com_t *com, void *buf, uint32_t num)
{
  int32_t rc;

  if (com == NULL || buf == NULL || num == 0U) {
    return (SPI_ERROR_PARAMETER);
  }

  PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  /* Check if port lock */
  if (port->info->status.lock == 0U) {
    return (SPI_ERROR);
  }

  rc = port->driver->Receive(buf, num);
  if (rc == DRIVER_OK) {
    rc = WaitOperation(port, com->timeout);
  }
  else {
    rc = SPI_ERROR;
  }

  return (rc);
}

/**
 * @brief       Send/Receive data to/from SPI COM
 * @param[in]   com         COM handle pointer
 * @param[in]   buf_out     Pointer to buffer with data to send to SPI COM
 * @param[out]  buf_in      Pointer to buffer for data to receive from SPI COM
 * @param[in]   num         Number of data items to transfer
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR           - Unspecified error
 *              SPI_ERROR_RESOURCE  - Resource error
 *              SPI_ERROR_PARAMETER - Parameter error
 *              SPI_ERROR_TIMEOUT   - Timeout occurred
 */
int32_t SPI_ComTransfer(SPI_Com_t *com, const void *buf_out, void *buf_in, uint32_t num)
{
  int32_t rc;

  if (com == NULL || buf_out == NULL || buf_in == NULL || num == 0U) {
    return (SPI_ERROR_PARAMETER);
  }

  PortResources_t *port = GetPort(com->port_num);
  if (port == NULL) {
    return (SPI_ERROR_RESOURCE);
  }

  /* Check if port lock */
  if (port->info->status.lock == 0U) {
    return (SPI_ERROR);
  }

  rc = port->driver->Transfer(buf_out, buf_in, num);
  if (rc == DRIVER_OK) {
    rc = WaitOperation(port, com->timeout);
  }
  else {
    rc = SPI_ERROR;
  }

  return (rc);
}
