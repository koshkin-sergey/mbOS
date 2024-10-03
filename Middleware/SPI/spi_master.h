/**
 * Copyright (C) 2024 Sergey Koshkin <skoshkin@neoros.ru>
 * All rights reserved
 *
 * File Name  : spi_master.h
 * Description: Реализация интерфейса SPI
 */

#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <Kernel/kernel.h>
#include <Driver/Driver_SPI.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* SPI return codes */
#define SPI_OK                        0
#define SPI_ERROR                    -1
#define SPI_ERROR_TIMEOUT            -2
#define SPI_ERROR_RESOURCE           -3
#define SPI_ERROR_PARAMETER          -4

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

typedef void (*SPI_Hook_t)(void *);

typedef struct SPI_Hooks {
  SPI_Hook_t  pre_callback;
  void       *pre_param;
  SPI_Hook_t  post_callback;
  void       *post_param;
} SPI_Hooks_t;

typedef struct SPI_Com_Cfg {
  uint32_t  drv_cfg;      // Driver Config
  uint32_t  bus_speed;    // Bus Speed in bps
} SPI_Com_Cfg_t;

typedef struct SPI_Com {
  uint32_t             port_num;
  const SPI_Com_Cfg_t *com_cfg;
  const SPI_Hooks_t   *hooks;
  uint32_t             timeout;     // Timeout for performing an operation in OS ticks
} SPI_Com_t;

/*******************************************************************************
 *  exported function prototypes
 ******************************************************************************/

/**
 * @brief       Open SPI Port
 * @param[in]   port_num  port number (hardware specific)
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_RESOURCE  - Resource error
 *              SPI_ERROR_PARAMETER - Parameter error
 */
int32_t SPI_PortOpen(uint32_t port_num);

/**
 * @brief       Close SPI Port
 * @param[in]   port_num  port number (hardware specific)
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_PARAMETER - Parameter error
 */
int32_t SPI_PortClose(uint32_t port_num);

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
                      const SPI_Hooks_t   *hooks);

/**
 * @brief       Lock Communication on SPI port
 * @param[in]   com   COM handle pointer
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_RESOURCE  - Resource error
 */
int32_t SPI_ComLock(SPI_Com_t *com);

/**
 * @brief       Unlock Communication on SPI port
 * @param[in]   com   COM handle pointer
 * @return      SPI_OK              - Operation succeeded
 *              SPI_ERROR_RESOURCE  - Resource error
 */
int32_t SPI_ComUnLock(SPI_Com_t *com);

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
int32_t SPI_ComSend(SPI_Com_t *com, const void *buf, uint32_t num);

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
int32_t SPI_ComReceive(SPI_Com_t *com, void *buf, uint32_t num);

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
int32_t SPI_ComTransfer(SPI_Com_t *com, const void *buf_out, void *buf_in, uint32_t num);

#ifdef  __cplusplus
}
#endif

#endif /* SPI_MASTER_H_ */
