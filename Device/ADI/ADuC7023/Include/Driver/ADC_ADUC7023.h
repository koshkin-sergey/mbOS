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

#ifndef ADC_ADUC7023_H_
#define ADC_ADUC7023_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include <asm/aduc7023.h>
#include <device_config.h>
#include <Kernel/irq.h>
#include <Driver/GPIO_ADUC7023.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define ADC_RESOLUTION              (12U)
#define ADC_MAX_LSB                 ((1UL << ADC_RESOLUTION) - 1UL)

/* The number of ADC pins. */
#define ADC_PIN_NUM                 (8U)

/* ADC configuration definitions */
#if defined (DEV_ADC) && (DEV_ADC == 1)
  #define USE_ADC

  #if !defined(ADC)
    #error "ADC not available for selected device!"
    #undef USE_ADC
  #endif

  #if defined (DEV_ADC_IN4) && (DEV_ADC_IN4 == 1)
    #define USE_ADC_IN4
    #define ADC_IN4_GPIO_PORT       DEV_ADC_IN4_PORT
    #define ADC_IN4_GPIO_PIN        DEV_ADC_IN4_PIN
    #define ADC_IN4_GPIO_FUNC       DEV_ADC_IN4_FUNC
  #endif

  #if defined (DEV_ADC_IN5) && (DEV_ADC_IN5 == 1)
    #define USE_ADC_IN5
    #define ADC_IN5_GPIO_PORT       DEV_ADC_IN5_PORT
    #define ADC_IN5_GPIO_PIN        DEV_ADC_IN5_PIN
    #define ADC_IN5_GPIO_FUNC       DEV_ADC_IN5_FUNC
  #endif

  #if defined (DEV_ADC_IN6) && (DEV_ADC_IN6 == 1)
    #define USE_ADC_IN6
    #define ADC_IN6_GPIO_PORT       DEV_ADC_IN6_PORT
    #define ADC_IN6_GPIO_PIN        DEV_ADC_IN6_PIN
    #define ADC_IN6_GPIO_FUNC       DEV_ADC_IN6_FUNC
  #endif

  #if defined (DEV_ADC_IN7) && (DEV_ADC_IN7 == 1)
    #define USE_ADC_IN7
    #define ADC_IN7_GPIO_PORT       DEV_ADC_IN7_PORT
    #define ADC_IN7_GPIO_PIN        DEV_ADC_IN7_PIN
    #define ADC_IN7_GPIO_FUNC       DEV_ADC_IN7_FUNC
  #endif

  #if defined (DEV_ADC_IN8) && (DEV_ADC_IN8 == 1)
    #define USE_ADC_IN8
    #define ADC_IN8_GPIO_PORT       DEV_ADC_IN8_PORT
    #define ADC_IN8_GPIO_PIN        DEV_ADC_IN8_PIN
    #define ADC_IN8_GPIO_FUNC       DEV_ADC_IN8_FUNC
  #endif

  #if defined (DEV_ADC_IN9) && (DEV_ADC_IN9 == 1)
    #define USE_ADC_IN9
    #define ADC_IN9_GPIO_PORT       DEV_ADC_IN9_PORT
    #define ADC_IN9_GPIO_PIN        DEV_ADC_IN9_PIN
    #define ADC_IN9_GPIO_FUNC       DEV_ADC_IN9_FUNC
  #endif

  #if defined (DEV_ADC_IN10) && (DEV_ADC_IN10 == 1)
    #define USE_ADC_IN10
    #define ADC_IN10_GPIO_PORT      DEV_ADC_IN10_PORT
    #define ADC_IN10_GPIO_PIN       DEV_ADC_IN10_PIN
    #define ADC_IN10_GPIO_FUNC      DEV_ADC_IN10_FUNC
  #endif

  #if defined (DEV_ADC_IN12) && (DEV_ADC_IN12 == 1)
    #define USE_ADC_IN12
    #define ADC_IN12_GPIO_PORT      DEV_ADC_IN12_PORT
    #define ADC_IN12_GPIO_PIN       DEV_ADC_IN12_PIN
    #define ADC_IN12_GPIO_FUNC      DEV_ADC_IN12_FUNC
  #endif

  #define ADC_INT_PRIORITY          DEV_ADC_INT_PRIO
#endif

/****** ADC error codes *****/
#define ADC_DRIVER_OK                 0         ///< Operation succeeded
#define ADC_DRIVER_ERROR             -1         ///< Unspecified error
#define ADC_DRIVER_ERROR_BUSY        -2         ///< Driver is busy
#define ADC_DRIVER_ERROR_TIMEOUT     -3         ///< Timeout occurred
#define ADC_DRIVER_ERROR_UNSUPPORTED -4         ///< Operation not supported
#define ADC_DRIVER_ERROR_PARAMETER   -5         ///< Parameter error

/****** ADC Event *****/
#define ADC_EVENT_ACQ_COMPLETE      (1UL << 0)  ///< Acquisition completed
#define ADC_EVENT_DATA_OVERFLOW     (1UL << 1)  ///< ADC data overflow

/****** Current driver status flag definition *****/
#define ADC_FLAG_INITIALIZED        (1UL << 0)  ///< ADC initialized
#define ADC_FLAG_POWERED            (1UL << 1)  ///< ADC powered on
#define ADC_FLAG_CONFIGURED         (1UL << 2)  ///< ADC is configured
#define ADC_FLAG_ENABLE             (1UL << 3)  ///< ADC is enabled

/****** ADC Control Codes *****/
#define ADC_CONTROL_Msk             (0xFFUL)
#define ADC_CONFIGURE               (0x01UL)                                    ///< Configure ADC;
#define ADC_CONTROL                 (0x02UL)                                    ///< Control ADC; arg provide additional configuration
#define ADC_CHANNEL_SELECT          (0x03UL)                                    ///< ADC channel select; arg provide additional configuration

/*----- ADC Control Codes: Configuration Parameters: Conversion Mode -----*/
#define ADC_MODE_Pos                 8
#define ADC_MODE_Msk                (1UL << ADC_MODE_Pos)
#define ADC_MODE_SINGLE_ENDED       (0UL << ADC_MODE_Pos)                       ///< Single-ended mode (default)
#define ADC_MODE_DIFFERENTIAL       (1UL << ADC_MODE_Pos)                       ///< Differential mode

/*----- ADC Control Codes: Configuration Parameters: Conversion Trigger Type -----*/
#define ADC_TRG_Pos                  9
#define ADC_TRG_Msk                 (7UL << ADC_TRG_Pos)
#define ADC_TRG_CS_PIN              (0UL << ADC_TRG_Pos)                       ///< CONVSTART pin as a conversion input (default)
#define ADC_TRG_TIMER1              (1UL << ADC_TRG_Pos)                       ///< Timer1 as a conversion input
#define ADC_TRG_TIMER0              (2UL << ADC_TRG_Pos)                       ///< Timer0 as a conversion input
#define ADC_TRG_PLA                 (5UL << ADC_TRG_Pos)                       ///< PLA conversion

/*----- ADC Control Codes: Configuration Parameters: Acquisition time -----*/
#define ADC_ACQ_TIME_Pos             12
#define ADC_ACQ_TIME_Msk            (3UL << ADC_ACQ_TIME_Pos)
#define ADC_ACQ_TIME_2C             (0UL << ADC_ACQ_TIME_Pos)                   ///< 2 clocks (default)
#define ADC_ACQ_TIME_4C             (1UL << ADC_ACQ_TIME_Pos)                   ///< 4 clocks
#define ADC_ACQ_TIME_8C             (2UL << ADC_ACQ_TIME_Pos)                   ///< 8 clocks
#define ADC_ACQ_TIME_16C            (3UL << ADC_ACQ_TIME_Pos)                   ///< 16 clocks

/*----- ADC Control Codes: Configuration Parameters: ADC clock divider -----*/
#define ADC_CLK_DIV_Pos              14
#define ADC_CLK_DIV_Msk             (7UL << ADC_CLK_DIV_Pos)
#define ADC_CLK_DIV_1               (0UL << ADC_CLK_DIV_Pos)                    ///< ADC Freq = UCLK/1 (default)
#define ADC_CLK_DIV_2               (1UL << ADC_CLK_DIV_Pos)                    ///< ADC Freq = UCLK/2
#define ADC_CLK_DIV_4               (2UL << ADC_CLK_DIV_Pos)                    ///< ADC Freq = UCLK/4
#define ADC_CLK_DIV_8               (3UL << ADC_CLK_DIV_Pos)                    ///< ADC Freq = UCLK/8
#define ADC_CLK_DIV_16              (4UL << ADC_CLK_DIV_Pos)                    ///< ADC Freq = UCLK/16
#define ADC_CLK_DIV_32              (5UL << ADC_CLK_DIV_Pos)                    ///< ADC Freq = UCLK/32

/*----- ADC Control Codes: Configuration Parameters: ADC positive channel selection -----*/
#define ADC_P_CNL_SEL_Pos            17
#define ADC_P_CNL_SEL_Msk           (0x1FUL << ADC_P_CNL_SEL_Pos)
#define ADC_P_CNL_SEL_IN0           (0x00UL << ADC_P_CNL_SEL_Pos)               ///< ADC0 (default)
#define ADC_P_CNL_SEL_IN1           (0x01UL << ADC_P_CNL_SEL_Pos)               ///< ADC1
#define ADC_P_CNL_SEL_IN2           (0x02UL << ADC_P_CNL_SEL_Pos)               ///< ADC2
#define ADC_P_CNL_SEL_IN3           (0x03UL << ADC_P_CNL_SEL_Pos)               ///< ADC3
#define ADC_P_CNL_SEL_IN4           (0x04UL << ADC_P_CNL_SEL_Pos)               ///< ADC4
#define ADC_P_CNL_SEL_IN5           (0x05UL << ADC_P_CNL_SEL_Pos)               ///< ADC5
#define ADC_P_CNL_SEL_IN6           (0x06UL << ADC_P_CNL_SEL_Pos)               ///< ADC6
#define ADC_P_CNL_SEL_IN7           (0x07UL << ADC_P_CNL_SEL_Pos)               ///< ADC7
#define ADC_P_CNL_SEL_IN8           (0x08UL << ADC_P_CNL_SEL_Pos)               ///< ADC8
#define ADC_P_CNL_SEL_IN9           (0x09UL << ADC_P_CNL_SEL_Pos)               ///< ADC9
#define ADC_P_CNL_SEL_IN10          (0x0AUL << ADC_P_CNL_SEL_Pos)               ///< ADC10
#define ADC_P_CNL_SEL_IN12          (0x0CUL << ADC_P_CNL_SEL_Pos)               ///< ADC12
#define ADC_P_CNL_SEL_DAC0          (0x0EUL << ADC_P_CNL_SEL_Pos)               ///< DAC0
#define ADC_P_CNL_SEL_DAC1          (0x0FUL << ADC_P_CNL_SEL_Pos)               ///< DAC1
#define ADC_P_CNL_SEL_TS            (0x10UL << ADC_P_CNL_SEL_Pos)               ///< Temperature sensor
#define ADC_P_CNL_SEL_AGND          (0x11UL << ADC_P_CNL_SEL_Pos)               ///< AGND (self-diagnostic feature)
#define ADC_P_CNL_SEL_IREF          (0x12UL << ADC_P_CNL_SEL_Pos)               ///< Internal reference (self-diagnostic feature)
#define ADC_P_CNL_SEL_AVDD          (0x13UL << ADC_P_CNL_SEL_Pos)               ///< AVDD/2

/*----- ADC Control Codes: Configuration Parameters: ADC negative channel selection -----*/
#define ADC_N_CNL_SEL_Pos            22
#define ADC_N_CNL_SEL_Msk           (0x1FUL << ADC_N_CNL_SEL_Pos)
#define ADC_N_CNL_SEL_IN0           (0x00UL << ADC_N_CNL_SEL_Pos)               ///< ADC0 (default)
#define ADC_N_CNL_SEL_IN1           (0x01UL << ADC_N_CNL_SEL_Pos)               ///< ADC1
#define ADC_N_CNL_SEL_IN2           (0x02UL << ADC_N_CNL_SEL_Pos)               ///< ADC2
#define ADC_N_CNL_SEL_IN3           (0x03UL << ADC_N_CNL_SEL_Pos)               ///< ADC3
#define ADC_N_CNL_SEL_IN4           (0x04UL << ADC_N_CNL_SEL_Pos)               ///< ADC4
#define ADC_N_CNL_SEL_IN5           (0x05UL << ADC_N_CNL_SEL_Pos)               ///< ADC5
#define ADC_N_CNL_SEL_IN6           (0x06UL << ADC_N_CNL_SEL_Pos)               ///< ADC6
#define ADC_N_CNL_SEL_IN7           (0x07UL << ADC_N_CNL_SEL_Pos)               ///< ADC7
#define ADC_N_CNL_SEL_IN8           (0x08UL << ADC_N_CNL_SEL_Pos)               ///< ADC8
#define ADC_N_CNL_SEL_IN9           (0x09UL << ADC_N_CNL_SEL_Pos)               ///< ADC9
#define ADC_N_CNL_SEL_IN10          (0x0AUL << ADC_N_CNL_SEL_Pos)               ///< ADC10
#define ADC_N_CNL_SEL_IN12          (0x0CUL << ADC_N_CNL_SEL_Pos)               ///< ADC12
#define ADC_N_CNL_SEL_DAC1          (0x0FUL << ADC_N_CNL_SEL_Pos)               ///< DAC1
#define ADC_N_CNL_SEL_TS            (0x10UL << ADC_N_CNL_SEL_Pos)               ///< Temperature sensor
#define ADC_N_CNL_SEL_AGND          (0x11UL << ADC_N_CNL_SEL_Pos)               ///< AGND (self-diagnostic feature)
#define ADC_N_CNL_SEL_IREF          (0x12UL << ADC_N_CNL_SEL_Pos)               ///< Internal reference (self-diagnostic feature)

/****** ADC Configuration (arg) *****/

/*----- ADC Configuration (arg): Conversion type -----*/
#define ADC_CONV_Pos                 0
#define ADC_CONV_Msk                (3UL << ADC_CONV_Pos)
#define ADC_CONV_STOP               (0UL << ADC_CONV_Pos)
#define ADC_CONV_TRIGGER            (1UL << ADC_CONV_Pos)
#define ADC_CONV_SOFT_SINGLE        (2UL << ADC_CONV_Pos)
#define ADC_CONV_SOFT_CONT          (3UL << ADC_CONV_Pos)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @fn          void ADC_SignalEvent(uint32_t event)
 * @brief       Signal ADC Events.
 * @param[in]   event  Notification mask
 */
typedef void (*ADC_SignalEvent_t)(uint32_t event);

/**
 * @brief General power states
 */
typedef enum _ADC_POWER_STATE {
  ADC_POWER_OFF,                        ///< Power off: no operation possible
  ADC_POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
  ADC_POWER_FULL                        ///< Power on: full operation at maximum performance
} ADC_POWER_STATE;

/**
 * @brief ADC Status
 */
typedef struct ADC_STATUS {
  uint32_t busy             : 1;            // ADC busy flag
  uint32_t overflow         : 1;            // Data overflow detected (cleared on start of next operation)
  uint32_t reserved         : 30;
} ADC_STATUS_t;

/* ADC Pin */
typedef const struct _ADC_PIN {
  DRIVER_GPIO          *gpio;               // Pointer to GPIO driver
  GPIO_PIN_t            pin;                // IO pin
  GPIO_PIN_FUNC_t       func;               // AF pin configuration
} ADC_PIN;

/* ADC Input/Output Configuration */
typedef const struct _ADC_IO {
  ADC_PIN              *pin[ADC_PIN_NUM];  // ADC Input pins
} ADC_IO;

/* ADC Acquire Information (Run-Time) */
typedef struct _ADC_ACQ_INFO {
  uint32_t              num;                // Total number of data to be acquired
  uint32_t              cnt;                // Number of data acquired
   int16_t             *buf;                // Pointer to data buffer
} ADC_ACQ_INFO;

/* ADC Information (Run-Time) */
typedef struct _ADC_INFO {
  ADC_SignalEvent_t     cb_event;           // Event Callback
  uint32_t              flags;              // Current ADC state flags
  ADC_STATUS_t          status;             // Status flags
  ADC_ACQ_INFO          acq_info;           // Acquire information
} ADC_INFO;

/* ADC IRQ Configuration */
typedef const struct _ADC_IRQ {
  IRQ_Priority_t        priority;           // ADC interrupt priority
  IRQn_t                num;                // ADC IRQ Number
  IRQHandler_t          handler;            // ADC IRQ handler
} ADC_IRQ;

/* ADC Resource Configuration */
typedef struct {
  ADC_t                *reg;                // ADC peripheral register interface
  ADC_IO                io;                 // ADC Input pins
  ADC_INFO             *info;               // Run-Time information
  ADC_IRQ               irq;                // ADC interrupt information
} const ADC_RESOURCES;

/**
 * Function documentation
 *
 * @fn          int32_t ADC_Initialize(ADC_SignalEvent_t cb_event)
 * @brief       Initialize ADC Interface.
 * @param[in]   cb_event  Pointer to ADC_SignalEvent
 * @return      Execution status
 *
 * @fn          int32_t ADC_Uninitialize(void)
 * @brief       De-initialize ADC Interface.
 * @return      Execution status
 *
 * @fn          int32_t ADC_PowerControl(ADC_POWER_STATE state)
 * @brief       Control ADC Interface Power.
 * @param[in]   state  Power state
 * @return      Execution status
 *
 * @fn          int32_t ADC_Control(uint32_t control, uint32_t arg)
 * @brief       Control ADC Interface.
 * @param[in]   control  Operation
 * @param[in]   arg      Argument of operation (optional)
 * @return      Common execution status and driver specific execution status
 *
 * @fn          int32_t ADC_GetData(int16_t *data, uint32_t num)
 * @brief       Start acquisition data.
 * @param[out]  data  Pointer to buffer for data
 * @param[in]   num   Number of data items to acquire
 * @return      Execution status
 *
 * @fn          uint32_t ADC_GetCount(void)
 * @brief       Get acquired data count.
 * @return      Number of data items acquired
 *
 * @fn          ADC_STATUS_t ADC_GetStatus(void)
 * @brief       Get ADC status.
 * @return      ADC status
 */

/**
 * @brief Access structure of the ADC Driver.
 */
typedef struct Driver_ADC {
  int32_t       (*Initialize)   (ADC_SignalEvent_t cb_event);
  int32_t       (*Uninitialize) (void);
  int32_t       (*PowerControl) (ADC_POWER_STATE state);
  int32_t       (*Control)      (uint32_t control, uint32_t arg);
  int32_t       (*GetData)      (int16_t *data, uint32_t num);
  uint32_t      (*GetCount)     (void);
  ADC_STATUS_t  (*GetStatus)    (void);
} const Driver_ADC_t;

#endif /* ADC_ADUC7023_H_ */
