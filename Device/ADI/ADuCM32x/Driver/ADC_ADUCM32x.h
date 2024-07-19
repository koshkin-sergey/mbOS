/**
 * @authors Sergey Koshkin <skoshkin@neoros.ru>
 *          Pimonov Vladimir <vpimonov@neoros.ru>
 * @copyright (C) 2024 “Neoros” LLC <info@neoros.ru>
 * All rights reserved
 *
 * File Name  : ADC_ADUCM32x.c
 * Description: Драйвер АЦП микроконтроллеров ADuCM32x
 */

#ifndef ADC_ADUCM32X_H_
#define ADC_ADUCM32X_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include <asm/aducm32x.h>
#include <device_config.h>
#include <Driver/GPIO_ADUCM32x.h>
#include <Driver/Driver_ADC.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

/* ADC configuration definitions */
#if defined (DEV_ADC) && (DEV_ADC == 1)
  #define USE_ADC

  #if !defined(MMR_ADC)
    #error "ADC not available for selected device!"
    #undef USE_ADC
  #endif

  #if defined (DEV_ADC_IN8) && (DEV_ADC_IN8 == 1)
    #define USE_ADC_IN8
    #define ADC_IN8_GPIO_PIN        GPIO_PIN_2
  #endif

  #if defined (DEV_ADC_IN9) && (DEV_ADC_IN9 == 1)
    #define USE_ADC_IN9
    #define ADC_IN9_GPIO_PIN        GPIO_PIN_3
  #endif

  #if defined (DEV_ADC_IN12) && (DEV_ADC_IN12 == 1)
    #define USE_ADC_IN12
    #define ADC_IN12_GPIO_PIN       GPIO_PIN_4
  #endif

  #if defined (DEV_ADC_IN13) && (DEV_ADC_IN13 == 1)
    #define USE_ADC_IN13
    #define ADC_IN13_GPIO_PIN       GPIO_PIN_5
  #endif

  #if defined (DEV_ADC_IN14) && (DEV_ADC_IN14 == 1)
    #define USE_ADC_IN14
    #define ADC_IN14_GPIO_PIN       GPIO_PIN_6
  #endif

  #if defined (DEV_ADC_IN15) && (DEV_ADC_IN15 == 1)
    #define USE_ADC_IN15
    #define ADC_IN15_GPIO_PIN       GPIO_PIN_7
  #endif

  #define ADC_INT_PRIORITY          DEV_ADC_INT_PRIO
  #define USE_VREF2V5_OUT           DEV_VREF2V5_OUT
  #define ADC_VREF_SRC              DEV_ADC_VREF_SRC
  #define ADC_CONV_FREQ             DEV_ADC_CONV_FREQ
  #define ADC_ACT                   DEV_ADC_ACT
  #define ADC_SEC_INT               DEV_ADC_SEC_INT
#endif

/****** Current driver status flag definition *****/
#define ADC_FLAG_INITIALIZED        (1UL << 0)                                  ///< ADC initialized
#define ADC_FLAG_POWERED            (1UL << 1)                                  ///< ADC powered on
#define ADC_FLAG_CONFIGURED         (1UL << 2)                                  ///< ADC is configured
#define ADC_FLAG_ENABLE             (1UL << 3)                                  ///< ADC is enabled

/* Number of configurable ADC pins */
#define ADC_CFG_PIN_NUM             (6U)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/* ADC Pin */
typedef const struct ADC_Pin {
  GPIO_PIN_t            pin;                // IO pin
} ADC_Pin_t;

/* ADC Acquire Information (Run-Time) */
typedef struct _ADC_ACQ_INFO {
  uint32_t              num;                // Total number of data to be acquired
  uint32_t              cnt;                // Number of data acquired
  int32_t              *buf;                // Pointer to data buffer
} ADC_ACQ_INFO;

/* ADC Information (Run-Time) */
typedef struct _ADC_INFO {
  ADC_SignalEvent_t      cb_event;          // Event Callback
  uint32_t                  flags;          // Current ADC state flags
  uint32_t              data_bits;          // Number of Data bits
  uint32_t                   mode;          // Mode
  ADC_STATUS_t             status;          // Status flags
  ADC_ACQ_INFO           acq_info;          // Acquire information
} ADC_INFO;

/* ADC IRQ Configuration */
typedef const struct _ADC_IRQ {
  IRQ_Priority_t         priority;          // ADC interrupt priority
  IRQn_Type                   num;          // ADC IRQ Number
} ADC_IRQ;

/* ADC Resource Configuration */
typedef struct {
  MMR_ADC_t                  *reg;          // ADC peripheral register interface
  ADC_INFO                  *info;          // Run-Time information
  ADC_IRQ                     irq;          // ADC interrupt information
  Driver_GPIO_t             *gpio;          // Pointer to GPIO driver
  ADC_Pin_t *pin[ADC_CFG_PIN_NUM];          // ADC configurable pins
} const ADC_RESOURCES;

#endif /* ADC_ADUCM32X_H_ */
