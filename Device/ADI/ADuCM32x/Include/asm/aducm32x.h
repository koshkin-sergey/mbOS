/*
 * Copyright (C) 2015 Analog Devices Inc.
 * Copyright (C) 2022-2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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
 */

/** @addtogroup Analog Devices Inc.
  * @{
  */

/** @addtogroup ADUCM32x
  * @{
  */

#ifndef ADUCM32X_H_
#define ADUCM32X_H_

#if !defined (ADUCM320) && !defined (ADUCM320I) && \
    !defined (ADUCM322) && !defined (ADUCM322I)
  #error "Please select first the target ADUCM32x device used in your application (in aducm32x.h file)"
#endif


#ifdef __cplusplus
extern "C" {
#endif 


/* ----------------------  Interrupt Number Definition  --------------------- */

typedef enum {
/* ----------------  Cortex-M3 Processor Exceptions Numbers  ---------------- */
  NonMaskableInt_IRQn       = -14,  /* Non Maskable Interrupt                 */
  HardFault_IRQn            = -13,  /* Hard Fault Interrupt                   */
  MemoryManagement_IRQn     = -12,  /* Memory Management Interrupt            */
  BusFault_IRQn             = -11,  /* Bus Fault Interrupt                    */
  UsageFault_IRQn           = -10,  /* Usage Fault Interrupt                  */
  SVCall_IRQn               = -5,   /* SV Call Interrupt via SVC instruction  */
  DebugMonitor_IRQn         = -4,   /* Debug Monitor Interrupt                */
  PendSV_IRQn               = -2,   /* Pend SV Interrupt                      */
  SysTick_IRQn              = -1,   /* System Tick Timer Interrupt            */
/* -----------------  ADUCM32x Specific Interrupt Numbers  _----------------- */
  WKUP_IRQn                 = 0,    /* Wakeup Timer Interrupt                 */
  EXTI0_IRQn                = 1,    /* External Interrupt 0                   */
  EXTI1_IRQn                = 2,    /* External Interrupt 1                   */
  EXTI2_IRQn                = 3,    /* External Interrupt 2                   */
  EXTI4_IRQn                = 5,    /* External Interrupt 4                   */
  EXTI5_IRQn                = 6,    /* External Interrupt 5                   */
  EXTI7_IRQn                = 8,    /* External Interrupt 7                   */
  EXTI8_IRQn                = 9,    /* External Interrupt 8                   */
  WDT_IRQn                  = 10,   /* Watchdog Timer Interrupt               */
  LVD0_IRQn                 = 13,   /* Low Voltage Die Interrupt 0            */
  MDIO_IRQn                 = 14,   /* MDIO Interrupt                         */
  TIM0_IRQn                 = 15,   /* Timer0 Interrupt                       */
  TIM1_IRQn                 = 16,   /* Timer1 Interrupt                       */
  FLASH_IRQn                = 17,   /* Flash Memory Interrupt                 */
  UART0_IRQn                = 18,   /* UART Interrupt                         */
  SPI0_IRQn                 = 19,   /* SPI0 Interrupt                         */
  SPI1_IRQn                 = 20,   /* SPI1 Interrupt                         */
  I2C0_Slave_IRQn           = 21,   /* I2C0 Slave Interrupt                   */
  I2C0_Master_IRQn          = 22,   /* I2C0 Master Interrupt                  */
  PLA0_IRQn                 = 23,   /* PLA0 Interrupt                         */
  PLA1_IRQn                 = 24,   /* PLA1 Interrupt                         */
  DMA_ERR_IRQn              = 25,   /* DMA Error Interrupt                    */
  DMA_SPI0_TX_IRQn          = 26,   /* DMA SPI0 TX Interrupt                  */
  DMA_SPI0_RX_IRQn          = 27,   /* DMA SPI0 RX Interrupt                  */
  DMA_SPI1_TX_IRQn          = 28,   /* DMA SPI1 TX Interrupt                  */
  DMA_SPI1_RX_IRQn          = 29,   /* DMA SPI1 RX Interrupt                  */
  DMA_UART0_TX_IRQn         = 30,   /* DMA UART TX Interrupt                  */
  DMA_UART0_RX_IRQn         = 31,   /* DMA UART RX Interrupt                  */
  DMA_I2C0_STX_IRQn         = 32,   /* DMA I2C0 Slave TX Interrupt            */
  DMA_I2C0_SRX_IRQn         = 33,   /* DMA I2C0 Slave RX Interrupt            */
  DMA_I2C0_M_IRQn           = 34,   /* DMA I2C0 Master Interrupt              */
  DMA_I2C1_STX_IRQn         = 35,   /* DMA I2C1 Slave TX Interrupt            */
  DMA_I2C1_SRX_IRQn         = 36,   /* DMA I2C1 Slave RX Interrupt            */
  DMA_I2C1_M_IRQn           = 37,   /* DMA I2C1 Master Interrupt              */
  DMA_ADC_IRQn              = 38,   /* DMA ADC Interrupt                      */
  DMA_FLASH_IRQn            = 39,   /* DMA Flash Interrupt                    */
  I2C1_Slave_IRQn           = 44,   /* I2C1 Slave Interrupt                   */
  I2C1_Master_IRQn          = 45,   /* I2C1 Master Interrupt                  */
  PLA2_IRQn                 = 46,   /* PLA2 Interrupt                         */
  PLA3_IRQn                 = 47,   /* PLA3 Interrupt                         */
  TIM2_IRQn                 = 48,   /* Timer2 Interrupt                       */
  LVD1_IRQn                 = 49,   /* Low Voltage Die Interrupt 1            */
  PWMT_IRQn                 = 50,   /* PWM TRIP Interrupt                     */
  PWM0_IRQn                 = 51,   /* PWM Channel Pair 0 interrupt           */
  PWM1_IRQn                 = 52,   /* PWM Channel Pair 1 interrupt           */
  PWM2_IRQn                 = 53,   /* PWM Channel Pair 2 interrupt           */
  PWM3_IRQn                 = 54    /* PWM Channel Pair 3 interrupt           */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the cm3 Processor and Core Peripherals---------------- */

#define __CM3_REV              0x0200       /*!< Cortex-M3 Core Revision          */
#define __MPU_PRESENT             0         /*!< MPU present or not                    */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
/** @} */ /* End of group Configuration_of_CMSIS */


#include <CMSIS/Core/Cortex/core_cm3.h>
#include "system_aducm32x.h"
#include <stdint.h>


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif




/* TLD[LOAD] - Load value */
#define TLD_LOAD_MSK                   (0xFFFF << 0  )

/* TVAL[VAL] - Current count */
#define TVAL_VAL_MSK                   (0xFFFF << 0  )

/* TCON[EVENTEN] - Event select */
#define TCON_EVENTEN_MSK               (0x1   << 12 )
#define TCON_EVENTEN                   (0x1   << 12 )
#define TCON_EVENTEN_DIS               (0x0   << 12 ) /* Events will not be captured */
#define TCON_EVENTEN_EN                (0x1   << 12 ) /* Events will be captured  */

/* TCON[EVENT] - Event select range */
#define TCON_EVENT_MSK                 (0xF   << 8  )

/* TCON[RLD] - Reload control */
#define TCON_RLD_MSK                   (0x1   << 7  )
#define TCON_RLD                       (0x1   << 7  )
#define TCON_RLD_EN                    (0x1   << 7  ) /* Resets the up/down counter when TCLRI[0] is set */
#define TCON_RLD_DIS                   (0x0   << 7  ) /* Up/Down counter is only reset on a timeout event */

/* TCON[CLK] - Clock select */
#define TCON_CLK_MSK                   (0x3   << 5  )
#define TCON_CLK_PCLK                  (0x0   << 5  ) /* PCLK.                    */
#define TCON_CLK_HCLK                  (0x1   << 5  ) /* HCLK.                    */
#define TCON_CLK_LFOSC                 (0x2   << 5  ) /* LFOSC. 32 KHz OSC        */
#define TCON_CLK_HFXTAL                (0x3   << 5  ) /* HFXTAL. 16 MHz OSC or XTAL (Dependent on CLKCON0.11) */

/* TCON[ENABLE] - Timer enable */
#define TCON_ENABLE_MSK                (0x1   << 4  )
#define TCON_ENABLE                    (0x1   << 4  )
#define TCON_ENABLE_DIS                (0x0   << 4  ) /* DIS. Timer is disabled (default) */
#define TCON_ENABLE_EN                 (0x1   << 4  ) /* EN. Timer is enabled     */

/* TCON[MOD] - Timer mode */
#define TCON_MOD_MSK                   (0x1   << 3  )
#define TCON_MOD                       (0x1   << 3  )
#define TCON_MOD_FREERUN               (0x0   << 3  ) /* FREERUN.Timer runs in free running mode */
#define TCON_MOD_PERIODIC              (0x1   << 3  ) /* PERIODIC. Timer runs in periodic mode (default) */

/* TCON[UP] - Count up */
#define TCON_UP_MSK                    (0x1   << 2  )
#define TCON_UP                        (0x1   << 2  )
#define TCON_UP_DIS                    (0x0   << 2  ) /* DIS. Timer is set to count down (default) */
#define TCON_UP_EN                     (0x1   << 2  ) /* EN. Timer is set to count up */

/* TCON[PRE] - Prescaler */
#define TCON_PRE_MSK                   (0x3   << 0  )
#define TCON_PRE_DIV1                  (0x0   << 0  ) /* source_clock / [1 or 4]  */
#define TCON_PRE_DIV16                 (0x1   << 0  ) /* source_clock / 16        */
#define TCON_PRE_DIV256                (0x2   << 0  ) /* source_clock / 256       */
#define TCON_PRE_DIV32768              (0x3   << 0  ) /* source_clock / 32,768    */

/* TCLRI[CAP] - Clear captured event interrupt */
#define TCLRI_CAP_MSK                  (0x1   << 1  )
#define TCLRI_CAP                      (0x1   << 1  )
#define TCLRI_CAP_CLR                  (0x1   << 1  ) /* Clear the capture event interrupt */

/* TCLRI[TMOUT] - Clear timeout interrupt */
#define TCLRI_TMOUT_MSK                (0x1   << 0  )
#define TCLRI_TMOUT                    (0x1   << 0  )
#define TCLRI_TMOUT_CLR                (0x1   << 0  ) /* Clears the timeout interrupt */

/* TCAP[CAP] - 16-bit captured value */
#define TCAP_CAP_MSK                   (0xFFFF << 0  )

/* TSTA[PDOK] - TCLRI synchronization */
#define TSTA_PDOK_MSK                  (0x1   << 7  )
#define TSTA_PDOK                      (0x1   << 7  )
#define TSTA_PDOK_CLR                  (0x0   << 7  ) /* CLR. The interrupt is cleared in the timer clock domain */
#define TSTA_PDOK_SET                  (0x1   << 7  ) /* SET. TCLRI[0] is being updated in the timer clock domain */

/* TSTA[BUSY] - Timer Busy */
#define TSTA_BUSY_MSK                  (0x1   << 6  )
#define TSTA_BUSY                      (0x1   << 6  )
#define TSTA_BUSY_CLR                  (0x0   << 6  ) /* CLR. Timer ready to receive commands to TCON */
#define TSTA_BUSY_SET                  (0x1   << 6  ) /* SET. Timer not ready to receive commands to TCON */

/* TSTA[CAP] - Capture event pending */
#define TSTA_CAP_MSK                   (0x1   << 1  )
#define TSTA_CAP                       (0x1   << 1  )
#define TSTA_CAP_CLR                   (0x0   << 1  ) /* CLR. No capture event is pending */
#define TSTA_CAP_SET                   (0x1   << 1  ) /* SET. A capture event is pending */

/* TSTA[TMOUT] - Timeout event occurred */
#define TSTA_TMOUT_MSK                 (0x1   << 0  )
#define TSTA_TMOUT                     (0x1   << 0  )
#define TSTA_TMOUT_CLR                 (0x0   << 0  ) /* CLR. No timeout event has occurred */
#define TSTA_TMOUT_SET                 (0x1   << 0  ) /* SET. A timeout event has occurred */

/* SPISTA[CSRSG] - Detected a rising edge on CS, in CONT mode */
#define SPISTA_CSRSG_MSK               (0x1   << 14 )
#define SPISTA_CSRSG                   (0x1   << 14 )
#define SPISTA_CSRSG_CLR               (0x0   << 14 ) /* Cleared to 0 when the Status register is read. */
#define SPISTA_CSRSG_SET               (0x1   << 14 ) /* Set to 1 when there was a rising edge in CS line, when the device was in master mode, continuous transfer, High Frequency mode and CSIRQ_EN was asserted. */

/* SPISTA[CSFLG] - Detected a falling edge on CS, in CONT mode */
#define SPISTA_CSFLG_MSK               (0x1   << 13 )
#define SPISTA_CSFLG                   (0x1   << 13 )
#define SPISTA_CSFLG_CLR               (0x0   << 13 ) /* Cleared to 0 when the Status register is read. */
#define SPISTA_CSFLG_SET               (0x1   << 13 ) /* Set to 1 when there was a falling edge in CS line, when the device was in master mode, continuous transfer, High Frequency mode and CSIRQ_EN was asserted */

/* SPISTA[CSERR] - Detected a CS error condition */
#define SPISTA_CSERR_MSK               (0x1   << 12 )
#define SPISTA_CSERR                   (0x1   << 12 )
#define SPISTA_CSERR_CLR               (0x0   << 12 ) /* Cleared to 0 when the Status register is read. */
#define SPISTA_CSERR_SET               (0x1   << 12 ) /* Set to 1 when the CS line was de-asserted abruptly, even before the full-byte of data was transmitted completely. This bit will cause an interrupt. */

/* SPISTA[RXS] - SPI Rx FIFO excess bytes present */
#define SPISTA_RXS_MSK                 (0x1   << 11 )
#define SPISTA_RXS                     (0x1   << 11 )
#define SPISTA_RXS_CLR                 (0x0   << 11 ) /* This bit is cleared when the number of bytes in the FIFO is equal or less than the number in SPI0CON[15:14]. */
#define SPISTA_RXS_SET                 (0x1   << 11 ) /* This bit is set when there are more bytes in the Rx FIFO than indicated in the MOD bits in SPI0CON. */

/* SPISTA[RXFSTA] - SPI Rx FIFO status */
#define SPISTA_RXFSTA_MSK              (0x7   << 8  )
#define SPISTA_RXFSTA_EMPTY            (0x0   << 8  ) /* Rx FIFO empty            */
#define SPISTA_RXFSTA_ONEBYTE          (0x1   << 8  ) /* 1 valid byte in FIFO     */
#define SPISTA_RXFSTA_TWOBYTES         (0x2   << 8  ) /* 2 valid bytes in the FIFO */
#define SPISTA_RXFSTA_THREEBYTES       (0x3   << 8  ) /* 3 valid bytes in the FIFO */
#define SPISTA_RXFSTA_FOURBYTES        (0x4   << 8  ) /* 4 valid bytes in the FIFO */

/* SPISTA[RXOF] - SPI Rx FIFO overflow */
#define SPISTA_RXOF_MSK                (0x1   << 7  )
#define SPISTA_RXOF                    (0x1   << 7  )
#define SPISTA_RXOF_CLR                (0x0   << 7  ) /* Cleared when the SPISTA register is read. */
#define SPISTA_RXOF_SET                (0x1   << 7  ) /* Set when the Rx FIFO was already full when new data was loaded to the FIFO. This bit generates an interrupt except when RFLUSH is set in SPI0CON. */

/* SPISTA[RX] - SPI Rx IRQ */
#define SPISTA_RX_MSK                  (0x1   << 6  )
#define SPISTA_RX                      (0x1   << 6  )
#define SPISTA_RX_CLR                  (0x0   << 6  ) /* Cleared when the SPI0STA register is read. */
#define SPISTA_RX_SET                  (0x1   << 6  ) /* Set when a receive interrupt occurs. This bit is set when TIM in SPI0CON is cleared and the required number of bytes have been received. */

/* SPISTA[TX] - SPI Tx IRQ */
#define SPISTA_TX_MSK                  (0x1   << 5  )
#define SPISTA_TX                      (0x1   << 5  )
#define SPISTA_TX_CLR                  (0x0   << 5  ) /* CLR. Cleared to 0 when the SPI0STA register is read. */
#define SPISTA_TX_SET                  (0x1   << 5  ) /* SET. Set to 1 when a transmit interrupt occurs. This bit is set when TIM in SPI0CON is set and the required number of bytes have been transmitted. */

/* SPISTA[TXUR] - SPI Tx FIFO underflow */
#define SPISTA_TXUR_MSK                (0x1   << 4  )
#define SPISTA_TXUR                    (0x1   << 4  )
#define SPISTA_TXUR_CLR                (0x0   << 4  ) /* Cleared to 0 when the SPI0STA register is read. */
#define SPISTA_TXUR_SET                (0x1   << 4  ) /* Set  to 1 when a transmit is initiated without any valid data in the Tx FIFO. This bit generates an interrupt except when TFLUSH is set in SPI0CON. */

/* SPISTA[TXFSTA] - SPI Tx FIFO status */
#define SPISTA_TXFSTA_MSK              (0x7   << 1  )
#define SPISTA_TXFSTA_EMPTY            (0x0   << 1  ) /* Tx FIFO empty            */
#define SPISTA_TXFSTA_ONEBYTE          (0x1   << 1  ) /* 1 valid byte in FIFO     */
#define SPISTA_TXFSTA_TWOBYTES         (0x2   << 1  ) /* 2 valid bytes in FIFO    */
#define SPISTA_TXFSTA_THREEBYTES       (0x3   << 1  ) /* 3 valid bytes in FIFO    */
#define SPISTA_TXFSTA_FOURBYTES        (0x4   << 1  ) /* 4 valid bytes in FIFO    */

/* SPISTA[IRQ] - SPI Interrupt status */
#define SPISTA_IRQ_MSK                 (0x1   << 0  )
#define SPISTA_IRQ                     (0x1   << 0  )
#define SPISTA_IRQ_CLR                 (0x0   << 0  ) /* Cleared to 0 after reading SPI0STA. */
#define SPISTA_IRQ_SET                 (0x1   << 0  ) /* Set to 1 when an SPI based interrupt occurs. */

/* SPIRX[DMA_DATA_BYTE_2] - 8-bit receive buffer */
#define SPIRX_DMA_DATA_BYTE_2_MSK      (0xFF  << 8  )

/* SPIRX[DATA_BYTE_1] - 8-bit receive buffer */
#define SPIRX_DATA_BYTE_1_MSK          (0xFF  << 0  )

/* SPITX[DMA_DATA_BYTE_2] - 8-bit transmit buffer */
#define SPITX_DMA_DATA_BYTE_2_MSK      (0xFF  << 8  )

/* SPITX[DATA_BYTE_1] - 8-bit transmit buffer */
#define SPITX_DATA_BYTE_1_MSK          (0xFF  << 0  )

/* SPIDIV[CSIRQ_EN] - Enable interrupt on every CS edge in CONT mode */
#define SPIDIV_CSIRQ_EN_MSK            (0x1   << 8  )
#define SPIDIV_CSIRQ_EN                (0x1   << 8  )
#define SPIDIV_CSIRQ_EN_DIS            (0x0   << 8  )
#define SPIDIV_CSIRQ_EN_EN             (0x1   << 8  )

/* SPIDIV[BCRST] - Reset Mode for CSERR */
#define SPIDIV_BCRST_MSK               (0x1   << 7  )
#define SPIDIV_BCRST                   (0x1   << 7  )
#define SPIDIV_BCRST_DIS               (0x0   << 7  )
#define SPIDIV_BCRST_EN                (0x1   << 7  )

/* SPIDIV[HFM] - High Frequency Mode */
#define SPIDIV_HFM_MSK                 (0x1   << 6  )
#define SPIDIV_HFM                     (0x1   << 6  )
#define SPIDIV_HFM_DIS                 (0x0   << 6  )
#define SPIDIV_HFM_EN                  (0x1   << 6  )

/* SPIDIV[DIV] - SPI clock divider */
#define SPIDIV_DIV_MSK                 (0x3F  << 0  )

/* SPICON[MOD] - SPI IRQ mode bits */
#define SPICON_MOD_MSK                 (0x3   << 14 )
#define SPICON_MOD_TX1RX1              (0x0   << 14 ) /* Tx interrupt occurs when 1 byte has been transferred. Rx interrupt occurs when 1 or more bytes have been received into the FIFO. */
#define SPICON_MOD_TX2RX2              (0x1   << 14 ) /* Tx interrupt occurs when 2 bytes has been transferred.  Rx interrupt occurs when 2 or more bytes have been received into the FIFO. */
#define SPICON_MOD_TX3RX3              (0x2   << 14 ) /* Tx interrupt occurs when 3 bytes has been transferred.  Rx interrupt occurs when 3 or more bytes have been received into the FIFO. */
#define SPICON_MOD_TX4RX4              (0x3   << 14 ) /* Tx interrupt occurs when 4 bytes has been transferred.  Rx interrupt occurs when the Rx FIFO is full, or 4 bytes present. */

/* SPICON[TFLUSH] - SPI Tx FIFO Flush enable */
#define SPICON_TFLUSH_MSK              (0x1   << 13 )
#define SPICON_TFLUSH                  (0x1   << 13 )
#define SPICON_TFLUSH_DIS              (0x0   << 13 ) /* Clear this bit to disable Tx FIFO flushing. */
#define SPICON_TFLUSH_EN               (0x1   << 13 ) /* Set this bit to flush the Tx FIFO. This bit does not clear itself and should be toggled if a single flush is required. If this bit is left high, then either the last transmitted value or "0x00" is transmitted depending on the ZEN bit. Any writes to the Tx FIFO are ignored while this bit is set. */

/* SPICON[RFLUSH] - SPI Rx FIFO Flush enable */
#define SPICON_RFLUSH_MSK              (0x1   << 12 )
#define SPICON_RFLUSH                  (0x1   << 12 )
#define SPICON_RFLUSH_DIS              (0x0   << 12 ) /* Clear this bit to disable Rx FIFO flushing. */
#define SPICON_RFLUSH_EN               (0x1   << 12 ) /* Set this bit to flush the Rx FIFO. This bit does not clear itself and should be toggled if a single flush is required. If this bit is set all incoming data is ignored and no interrupts are generated. If set and TIM = 0, a read of the Rx FIFO will initiate a transfer. */

/* SPICON[CON] - Continuous transfer enable */
#define SPICON_CON_MSK                 (0x1   << 11 )
#define SPICON_CON                     (0x1   << 11 )
#define SPICON_CON_DIS                 (0x0   << 11 ) /* DIS. Cleared by user to disable continuous transfer. Each transfer consists of a single 8-bit serial transfer. If valid data exists in the SPI0TX register, then a new transfer is initiated after a stall period of 1 serial clock cycle. */
#define SPICON_CON_EN                  (0x1   << 11 ) /* EN. Set by user to enable continuous transfer. In master mode, the transfer continues until no valid data is available in the Tx register. CS is asserted and remains asserted for the duration of each 8-bit serial transfer until Tx is empty. */

/* SPICON[LOOPBACK] - Loopback enable */
#define SPICON_LOOPBACK_MSK            (0x1   << 10 )
#define SPICON_LOOPBACK                (0x1   << 10 )
#define SPICON_LOOPBACK_DIS            (0x0   << 10 ) /* Cleared by user to be in normal mode. */
#define SPICON_LOOPBACK_EN             (0x1   << 10 ) /* Set by user to connect MISO to MOSI and test software. */

/* SPICON[OEN] - Slave MISO output enable */
#define SPICON_OEN_MSK                 (0x1   << 9  )
#define SPICON_OEN                     (0x1   << 9  )
#define SPICON_OEN_DIS                 (0x0   << 9  ) /* Clear this bit to disable the output driver on the MISO pin. The MISO pin will be Open-Circuit when this bit is clear. */
#define SPICON_OEN_EN                  (0x1   << 9  ) /* Set this bit for MISO to operate as normal. */

/* SPICON[RXOF] - SPIRX overflow overwrite enable */
#define SPICON_RXOF_MSK                (0x1   << 8  )
#define SPICON_RXOF                    (0x1   << 8  )
#define SPICON_RXOF_DIS                (0x0   << 8  ) /* Cleared by user, the new serial byte received is discarded. */
#define SPICON_RXOF_EN                 (0x1   << 8  ) /* Set by user, the valid data in the Rx register is overwritten by the new serial byte received. */

/* SPICON[ZEN] - Transmit zeros enable */
#define SPICON_ZEN_MSK                 (0x1   << 7  )
#define SPICON_ZEN                     (0x1   << 7  )
#define SPICON_ZEN_DIS                 (0x0   << 7  ) /* Clear this bit to transmit the last transmitted value when there is no valid data in the Tx FIFO. */
#define SPICON_ZEN_EN                  (0x1   << 7  ) /* Set this bit to transmit "0x00" when there is no valid data in the Tx FIFO. */

/* SPICON[TIM] - SPI transfer and interrupt mode */
#define SPICON_TIM_MSK                 (0x1   << 6  )
#define SPICON_TIM                     (0x1   << 6  )
#define SPICON_TIM_RXRD                (0x0   << 6  ) /* Cleared by user to initiate transfer with a read of the SPI0RX register. Interrupt only occurs when Rx is full. */
#define SPICON_TIM_TXWR                (0x1   << 6  ) /* Set by user to initiate transfer with a write to the SPI0TX register. Interrupt only occurs when Tx is empty. */

/* SPICON[LSB] - LSB first transfer enable */
#define SPICON_LSB_MSK                 (0x1   << 5  )
#define SPICON_LSB                     (0x1   << 5  )
#define SPICON_LSB_DIS                 (0x0   << 5  ) /* MSB transmitted first    */
#define SPICON_LSB_EN                  (0x1   << 5  ) /* LSB transmitted first    */

/* SPICON[WOM] - SPI Wired Or mode */
#define SPICON_WOM_MSK                 (0x1   << 4  )
#define SPICON_WOM                     (0x1   << 4  )
#define SPICON_WOM_EN                  (0x1   << 4  ) /* Enables open circuit data output enable. External pull-ups required on data out pins */
#define SPICON_WOM_DIS                 (0x0   << 4  ) /* Normal output levels     */

/* SPICON[CPOL] - Serial Clock Polarity */
#define SPICON_CPOL_MSK                (0x1   << 3  )
#define SPICON_CPOL                    (0x1   << 3  )
#define SPICON_CPOL_LOW                (0x0   << 3  ) /* Serial clock idles low   */
#define SPICON_CPOL_HIGH               (0x1   << 3  ) /* Serial clock idles high  */

/* SPICON[CPHA] - Serial clock phase mode */
#define SPICON_CPHA_MSK                (0x1   << 2  )
#define SPICON_CPHA                    (0x1   << 2  )
#define SPICON_CPHA_SAMPLETRAILING     (0x1   << 2  ) /* Serial clock pulses at the beginning of each serial bit transfer */
#define SPICON_CPHA_SAMPLELEADING      (0x0   << 2  ) /* Serial clock pulses at the end of each serial bit transfer */

/* SPICON[MASEN] - Master mode enable */
#define SPICON_MASEN_MSK               (0x1   << 1  )
#define SPICON_MASEN                   (0x1   << 1  )
#define SPICON_MASEN_DIS               (0x0   << 1  ) /* Enable slave mode        */
#define SPICON_MASEN_EN                (0x1   << 1  ) /* Enable master mode       */

/* SPICON[ENABLE] - SPI enable */
#define SPICON_ENABLE_MSK              (0x1   << 0  )
#define SPICON_ENABLE                  (0x1   << 0  )
#define SPICON_ENABLE_DIS              (0x0   << 0  ) /* Disable the SPI          */
#define SPICON_ENABLE_EN               (0x1   << 0  ) /* Enable the SPI           */

/* SPIDMA[IENRXDMA] - Enable receive DMA request */
#define SPIDMA_IENRXDMA_MSK            (0x1   << 2  )
#define SPIDMA_IENRXDMA                (0x1   << 2  )
#define SPIDMA_IENRXDMA_DIS            (0x0   << 2  ) /* Disable RX DMA Interrupt */
#define SPIDMA_IENRXDMA_EN             (0x1   << 2  ) /* Enable RX DMA Interrupt  */

/* SPIDMA[IENTXDMA] - Enable transmit DMA request */
#define SPIDMA_IENTXDMA_MSK            (0x1   << 1  )
#define SPIDMA_IENTXDMA                (0x1   << 1  )
#define SPIDMA_IENTXDMA_DIS            (0x0   << 1  ) /* Disable TX DMA Interrupt */
#define SPIDMA_IENTXDMA_EN             (0x1   << 1  ) /* Enable TX DMA Interrupt  */

/* SPIDMA[ENABLE] - Enable DMA for data transfer */
#define SPIDMA_ENABLE_MSK              (0x1   << 0  )
#define SPIDMA_ENABLE                  (0x1   << 0  )
#define SPIDMA_ENABLE_DIS              (0x0   << 0  )
#define SPIDMA_ENABLE_EN               (0x1   << 0  )

/* SPICNT[COUNT] - Transfer byte count */
#define SPICNT_COUNT_MSK               (0xFF  << 0  )

/* I2CMCON[PRESTOP_BUS_CLR] - Prestop Bus-Clear */
#define I2CMCON_PRESTOP_BUS_CLR_MSK    (0x1   << 13 )
#define I2CMCON_PRESTOP_BUS_CLR        (0x1   << 13 )
#define I2CMCON_PRESTOP_BUS_CLR_DIS    (0x0   << 13 )
#define I2CMCON_PRESTOP_BUS_CLR_EN     (0x1   << 13 )

/* I2CMCON[BUS_CLR_EN] - Bus-Clear Enable */
#define I2CMCON_BUS_CLR_EN_MSK         (0x1   << 12 )
#define I2CMCON_BUS_CLR_EN             (0x1   << 12 )
#define I2CMCON_BUS_CLR_EN_DIS         (0x0   << 12 )
#define I2CMCON_BUS_CLR_EN_EN          (0x1   << 12 )

/* I2CMCON[MTXDMA] - Enable master Tx DMA request */
#define I2CMCON_MTXDMA_MSK             (0x1   << 11 )
#define I2CMCON_MTXDMA                 (0x1   << 11 )
#define I2CMCON_MTXDMA_DIS             (0x0   << 11 ) /* Disable DMA mode         */
#define I2CMCON_MTXDMA_EN              (0x1   << 11 ) /* Enable I2C master DMA Tx requests. */

/* I2CMCON[MRXDMA] - Enable master Rx DMA request */
#define I2CMCON_MRXDMA_MSK             (0x1   << 10 )
#define I2CMCON_MRXDMA                 (0x1   << 10 )
#define I2CMCON_MRXDMA_DIS             (0x0   << 10 ) /* Disable DMA mode         */
#define I2CMCON_MRXDMA_EN              (0x1   << 10 ) /* Enable I2C master DMA Rx requests. */

/* I2CMCON[MXMITDEC] - Decrement master TX FIFO status when a byte has been transmitted */
#define I2CMCON_MXMITDEC_MSK           (0x1   << 9  )
#define I2CMCON_MXMITDEC               (0x1   << 9  )
#define I2CMCON_MXMITDEC_DIS           (0x0   << 9  )
#define I2CMCON_MXMITDEC_EN            (0x1   << 9  )

/* I2CMCON[IENCMP] - Transaction completed (or stop detected) interrupt enable */
#define I2CMCON_IENCMP_MSK             (0x1   << 8  )
#define I2CMCON_IENCMP                 (0x1   << 8  )
#define I2CMCON_IENCMP_DIS             (0x0   << 8  ) /* An interrupt is not generated when a STOP is detected. */
#define I2CMCON_IENCMP_EN              (0x1   << 8  ) /* An interrupt is generated when a STOP is detected. */

/* I2CMCON[IENACK] - ACK not received interrupt enable */
#define I2CMCON_IENACK_MSK             (0x1   << 7  )
#define I2CMCON_IENACK                 (0x1   << 7  )
#define I2CMCON_IENACK_DIS             (0x0   << 7  ) /* ACK not received interrupt disable */
#define I2CMCON_IENACK_EN              (0x1   << 7  ) /* ACK not received interrupt enable */

/* I2CMCON[IENALOST] - Arbitration lost interrupt enable */
#define I2CMCON_IENALOST_MSK           (0x1   << 6  )
#define I2CMCON_IENALOST               (0x1   << 6  )
#define I2CMCON_IENALOST_DIS           (0x0   << 6  ) /* Arbitration lost interrupt disable */
#define I2CMCON_IENALOST_EN            (0x1   << 6  ) /* Arbitration lost interrupt enable */

/* I2CMCON[IENMTX] - Transmit request interrupt enable */
#define I2CMCON_IENMTX_MSK             (0x1   << 5  )
#define I2CMCON_IENMTX                 (0x1   << 5  )
#define I2CMCON_IENMTX_DIS             (0x0   << 5  ) /* Transmit request interrupt disable */
#define I2CMCON_IENMTX_EN              (0x1   << 5  ) /* Transmit request interrupt enable */

/* I2CMCON[IENMRX] - Receive request interrupt enable */
#define I2CMCON_IENMRX_MSK             (0x1   << 4  )
#define I2CMCON_IENMRX                 (0x1   << 4  )
#define I2CMCON_IENMRX_DIS             (0x0   << 4  ) /* Receive request interrupt disable */
#define I2CMCON_IENMRX_EN              (0x1   << 4  ) /* Receive request interrupt enable */

/* I2CMCON[STRETCH] - Stretch SCL enable */
#define I2CMCON_STRETCH_MSK            (0x1   << 3  )
#define I2CMCON_STRETCH                (0x1   << 3  )
#define I2CMCON_STRETCH_DIS            (0x0   << 3  ) /* Disable Clock stretching */
#define I2CMCON_STRETCH_EN             (0x1   << 3  ) /* Setting this bit tells the device if SCL is 0 hold it at 0;. Or if SCL is 1 then when it next goes to 0 hold it at 0. */

/* I2CMCON[LOOPBACK] - Internal loopback enable */
#define I2CMCON_LOOPBACK_MSK           (0x1   << 2  )
#define I2CMCON_LOOPBACK               (0x1   << 2  )
#define I2CMCON_LOOPBACK_DIS           (0x0   << 2  ) /* SCL and SDA out of the device are not muxed onto their corresponding inputs. */
#define I2CMCON_LOOPBACK_EN            (0x1   << 2  ) /* SCL and SDA out of the device are muxed onto their corresponding inputs. */

/* I2CMCON[COMPETE] - Start back-off disable */
#define I2CMCON_COMPETE_MSK            (0x1   << 1  )
#define I2CMCON_COMPETE                (0x1   << 1  )
#define I2CMCON_COMPETE_DIS            (0x0   << 1  )
#define I2CMCON_COMPETE_EN             (0x1   << 1  )

/* I2CMCON[MASEN] - Master enable */
#define I2CMCON_MASEN_MSK              (0x1   << 0  )
#define I2CMCON_MASEN                  (0x1   << 0  )
#define I2CMCON_MASEN_DIS              (0x0   << 0  ) /* Master is disabled       */
#define I2CMCON_MASEN_EN               (0x1   << 0  ) /* Master is enabled        */

/* I2CMSTA[SCL_FILTERED] - State of SCL Line */
#define I2CMSTA_SCL_FILTERED_MSK       (0x1   << 14 )
#define I2CMSTA_SCL_FILTERED           (0x1   << 14 )
#define I2CMSTA_SCL_FILTERED_CLR       (0x0   << 14 )
#define I2CMSTA_SCL_FILTERED_SET       (0x1   << 14 )

/* I2CMSTA[SDA_FILTERED] - State of SDA Line */
#define I2CMSTA_SDA_FILTERED_MSK       (0x1   << 13 )
#define I2CMSTA_SDA_FILTERED           (0x1   << 13 )
#define I2CMSTA_SDA_FILTERED_CLR       (0x0   << 13 )
#define I2CMSTA_SDA_FILTERED_SET       (0x1   << 13 )

/* I2CMSTA[MTXUFLOW] - Master Transmit Underflow */
#define I2CMSTA_MTXUFLOW_MSK           (0x1   << 12 )
#define I2CMSTA_MTXUFLOW               (0x1   << 12 )
#define I2CMSTA_MTXUFLOW_CLR           (0x0   << 12 )
#define I2CMSTA_MTXUFLOW_SET           (0x1   << 12 )

/* I2CMSTA[MSTOP] - STOP driven by this I2C Master */
#define I2CMSTA_MSTOP_MSK              (0x1   << 11 )
#define I2CMSTA_MSTOP                  (0x1   << 11 )
#define I2CMSTA_MSTOP_CLR              (0x0   << 11 )
#define I2CMSTA_MSTOP_SET              (0x1   << 11 )

/* I2CMSTA[LINEBUSY] - Line is busy */
#define I2CMSTA_LINEBUSY_MSK           (0x1   << 10 )
#define I2CMSTA_LINEBUSY               (0x1   << 10 )
#define I2CMSTA_LINEBUSY_CLR           (0x0   << 10 )
#define I2CMSTA_LINEBUSY_SET           (0x1   << 10 )

/* I2CMSTA[MRXOF] - Master Receive FIFO overflow */
#define I2CMSTA_MRXOF_MSK              (0x1   << 9  )
#define I2CMSTA_MRXOF                  (0x1   << 9  )
#define I2CMSTA_MRXOF_CLR              (0x0   << 9  )
#define I2CMSTA_MRXOF_SET              (0x1   << 9  )

/* I2CMSTA[TCOMP] - Transaction complete or stop detected */
#define I2CMSTA_TCOMP_MSK              (0x1   << 8  )
#define I2CMSTA_TCOMP                  (0x1   << 8  )
#define I2CMSTA_TCOMP_CLR              (0x0   << 8  )
#define I2CMSTA_TCOMP_SET              (0x1   << 8  )

/* I2CMSTA[NACKDATA] - ACK not received in response to data write */
#define I2CMSTA_NACKDATA_MSK           (0x1   << 7  )
#define I2CMSTA_NACKDATA               (0x1   << 7  )
#define I2CMSTA_NACKDATA_CLR           (0x0   << 7  )
#define I2CMSTA_NACKDATA_SET           (0x1   << 7  )

/* I2CMSTA[MBUSY] - Master busy */
#define I2CMSTA_MBUSY_MSK              (0x1   << 6  )
#define I2CMSTA_MBUSY                  (0x1   << 6  )
#define I2CMSTA_MBUSY_CLR              (0x0   << 6  )
#define I2CMSTA_MBUSY_SET              (0x1   << 6  )

/* I2CMSTA[ALOST] - Arbitration lost */
#define I2CMSTA_ALOST_MSK              (0x1   << 5  )
#define I2CMSTA_ALOST                  (0x1   << 5  )
#define I2CMSTA_ALOST_CLR              (0x0   << 5  )
#define I2CMSTA_ALOST_SET              (0x1   << 5  )

/* I2CMSTA[NACKADDR] - ACK not received in response to an address */
#define I2CMSTA_NACKADDR_MSK           (0x1   << 4  )
#define I2CMSTA_NACKADDR               (0x1   << 4  )
#define I2CMSTA_NACKADDR_CLR           (0x0   << 4  )
#define I2CMSTA_NACKADDR_SET           (0x1   << 4  )

/* I2CMSTA[MRXREQ] - Master Receive request */
#define I2CMSTA_MRXREQ_MSK             (0x1   << 3  )
#define I2CMSTA_MRXREQ                 (0x1   << 3  )
#define I2CMSTA_MRXREQ_CLR             (0x0   << 3  )
#define I2CMSTA_MRXREQ_SET             (0x1   << 3  )

/* I2CMSTA[MTXREQ] - Master Transmit request */
#define I2CMSTA_MTXREQ_MSK             (0x1   << 2  )
#define I2CMSTA_MTXREQ                 (0x1   << 2  )
#define I2CMSTA_MTXREQ_CLR             (0x0   << 2  )
#define I2CMSTA_MTXREQ_SET             (0x1   << 2  )

/* I2CMSTA[MTXFSTA] - Master Transmit FIFO status */
#define I2CMSTA_MTXFSTA_MSK            (0x3   << 0  )

/* I2CMRX[ICMRX] - Master receive register */
#define I2CMRX_ICMRX_MSK               (0xFF  << 0  )

/* I2CMTX[I2CMTX] - Master transmit register */
#define I2CMTX_I2CMTX_MSK              (0xFF  << 0  )

/* I2CMRXCNT[EXTEND] - Extended read */
#define I2CMRXCNT_EXTEND_MSK           (0x1   << 8  )
#define I2CMRXCNT_EXTEND               (0x1   << 8  )
#define I2CMRXCNT_EXTEND_DIS           (0x0   << 8  )
#define I2CMRXCNT_EXTEND_EN            (0x1   << 8  )

/* I2CMRXCNT[COUNT] - Receive count */
#define I2CMRXCNT_COUNT_MSK            (0xFF  << 0  )

/* I2CMCRXCNT[COUNT] - Current receive count */
#define I2CMCRXCNT_COUNT_MSK           (0xFF  << 0  )

/* I2CADR0[ADR0] - Address byte 0 */
#define I2CADR0_ADR0_MSK               (0xFF  << 0  )

/* I2CADR1[ADR1] - Address byte 1 */
#define I2CADR1_ADR1_MSK               (0xFF  << 0  )

/* I2CDIV[HIGH] - Serial clock high time */
#define I2CDIV_HIGH_MSK                (0xFF  << 8  )

/* I2CDIV[LOW] - Serial clock low time */
#define I2CDIV_LOW_MSK                 (0xFF  << 0  )

/* I2CSCON[STXDMA] - Enable slave Tx DMA request */
#define I2CSCON_STXDMA_MSK             (0x1   << 14 )
#define I2CSCON_STXDMA                 (0x1   << 14 )
#define I2CSCON_STXDMA_DIS             (0x0   << 14 )
#define I2CSCON_STXDMA_EN              (0x1   << 14 )

/* I2CSCON[SRXDMA] - Enable slave Rx DMA request */
#define I2CSCON_SRXDMA_MSK             (0x1   << 13 )
#define I2CSCON_SRXDMA                 (0x1   << 13 )
#define I2CSCON_SRXDMA_DIS             (0x0   << 13 )
#define I2CSCON_SRXDMA_EN              (0x1   << 13 )

/* I2CSCON[IENREPST] - Repeated start interrupt enable */
#define I2CSCON_IENREPST_MSK           (0x1   << 12 )
#define I2CSCON_IENREPST               (0x1   << 12 )
#define I2CSCON_IENREPST_DIS           (0x0   << 12 )
#define I2CSCON_IENREPST_EN            (0x1   << 12 )

/* I2CSCON[SXMITDEC] - Decrement Slave Tx FIFO status when a byte has been transmitted */
#define I2CSCON_SXMITDEC_MSK           (0x1   << 11 )
#define I2CSCON_SXMITDEC               (0x1   << 11 )
#define I2CSCON_SXMITDEC_DIS           (0x0   << 11 )
#define I2CSCON_SXMITDEC_EN            (0x1   << 11 )

/* I2CSCON[IENSTX] - Slave Transmit request interrupt enable */
#define I2CSCON_IENSTX_MSK             (0x1   << 10 )
#define I2CSCON_IENSTX                 (0x1   << 10 )
#define I2CSCON_IENSTX_DIS             (0x0   << 10 )
#define I2CSCON_IENSTX_EN              (0x1   << 10 )

/* I2CSCON[IENSRX] - Slave Receive request interrupt enable */
#define I2CSCON_IENSRX_MSK             (0x1   << 9  )
#define I2CSCON_IENSRX                 (0x1   << 9  )
#define I2CSCON_IENSRX_DIS             (0x0   << 9  )
#define I2CSCON_IENSRX_EN              (0x1   << 9  )

/* I2CSCON[IENSTOP] - Stop condition detected interrupt enable */
#define I2CSCON_IENSTOP_MSK            (0x1   << 8  )
#define I2CSCON_IENSTOP                (0x1   << 8  )
#define I2CSCON_IENSTOP_DIS            (0x0   << 8  )
#define I2CSCON_IENSTOP_EN             (0x1   << 8  )

/* I2CSCON[NACK] - NACK next communication */
#define I2CSCON_NACK_MSK               (0x1   << 7  )
#define I2CSCON_NACK                   (0x1   << 7  )
#define I2CSCON_NACK_DIS               (0x0   << 7  )
#define I2CSCON_NACK_EN                (0x1   << 7  )

/* I2CSCON[STRETCHSCL] - Stretch SCL enable */
#define I2CSCON_STRETCHSCL_MSK         (0x1   << 6  )
#define I2CSCON_STRETCHSCL             (0x1   << 6  )
#define I2CSCON_STRETCHSCL_DIS         (0x0   << 6  )
#define I2CSCON_STRETCHSCL_EN          (0x1   << 6  )

/* I2CSCON[EARLYTXR] - Early transmit request mode */
#define I2CSCON_EARLYTXR_MSK           (0x1   << 5  )
#define I2CSCON_EARLYTXR               (0x1   << 5  )
#define I2CSCON_EARLYTXR_DIS           (0x0   << 5  )
#define I2CSCON_EARLYTXR_EN            (0x1   << 5  )

/* I2CSCON[GCSBCLR] - General call status bit clear */
#define I2CSCON_GCSBCLR_MSK            (0x1   << 4  )
#define I2CSCON_GCSBCLR                (0x1   << 4  )
#define I2CSCON_GCSBCLR_DIS            (0x0   << 4  )
#define I2CSCON_GCSBCLR_EN             (0x1   << 4  )

/* I2CSCON[HGCEN] - Hardware general call enable */
#define I2CSCON_HGCEN_MSK              (0x1   << 3  )
#define I2CSCON_HGCEN                  (0x1   << 3  )
#define I2CSCON_HGCEN_DIS              (0x0   << 3  )
#define I2CSCON_HGCEN_EN               (0x1   << 3  )

/* I2CSCON[GCEN] - General call enable */
#define I2CSCON_GCEN_MSK               (0x1   << 2  )
#define I2CSCON_GCEN                   (0x1   << 2  )
#define I2CSCON_GCEN_DIS               (0x0   << 2  )
#define I2CSCON_GCEN_EN                (0x1   << 2  )

/* I2CSCON[ADR10EN] - Enabled 10-bit addressing */
#define I2CSCON_ADR10EN_MSK            (0x1   << 1  )
#define I2CSCON_ADR10EN                (0x1   << 1  )
#define I2CSCON_ADR10EN_DIS            (0x0   << 1  )
#define I2CSCON_ADR10EN_EN             (0x1   << 1  )

/* I2CSCON[SLVEN] - Slave enable */
#define I2CSCON_SLVEN_MSK              (0x1   << 0  )
#define I2CSCON_SLVEN                  (0x1   << 0  )
#define I2CSCON_SLVEN_DIS              (0x0   << 0  )
#define I2CSCON_SLVEN_EN               (0x1   << 0  )

/* I2CSSTA[START] - Start and matching address */
#define I2CSSTA_START_MSK              (0x1   << 14 )
#define I2CSSTA_START                  (0x1   << 14 )
#define I2CSSTA_START_CLR              (0x0   << 14 )
#define I2CSSTA_START_SET              (0x1   << 14 )

/* I2CSSTA[REPSTART] - Repeated start and matching address */
#define I2CSSTA_REPSTART_MSK           (0x1   << 13 )
#define I2CSSTA_REPSTART               (0x1   << 13 )
#define I2CSSTA_REPSTART_CLR           (0x0   << 13 )
#define I2CSSTA_REPSTART_SET           (0x1   << 13 )

/* I2CSSTA[IDMAT] - Device ID matched */
#define I2CSSTA_IDMAT_MSK              (0x3   << 11 )

/* I2CSSTA[STOP] - Stop after start and matching address */
#define I2CSSTA_STOP_MSK               (0x1   << 10 )
#define I2CSSTA_STOP                   (0x1   << 10 )
#define I2CSSTA_STOP_CLR               (0x0   << 10 )
#define I2CSSTA_STOP_SET               (0x1   << 10 )

/* I2CSSTA[GCID] - General ID */
#define I2CSSTA_GCID_MSK               (0x3   << 8  )

/* I2CSSTA[GCINT] - General call interrupt */
#define I2CSSTA_GCINT_MSK              (0x1   << 7  )
#define I2CSSTA_GCINT                  (0x1   << 7  )
#define I2CSSTA_GCINT_CLR              (0x0   << 7  )
#define I2CSSTA_GCINT_SET              (0x1   << 7  )

/* I2CSSTA[SBUSY] - Slave busy */
#define I2CSSTA_SBUSY_MSK              (0x1   << 6  )
#define I2CSSTA_SBUSY                  (0x1   << 6  )
#define I2CSSTA_SBUSY_CLR              (0x0   << 6  )
#define I2CSSTA_SBUSY_SET              (0x1   << 6  )

/* I2CSSTA[NOACK] - Ack not generated by the slave */
#define I2CSSTA_NOACK_MSK              (0x1   << 5  )
#define I2CSSTA_NOACK                  (0x1   << 5  )
#define I2CSSTA_NOACK_CLR              (0x0   << 5  )
#define I2CSSTA_NOACK_SET              (0x1   << 5  )

/* I2CSSTA[SRXOF] - Slave Receive FIFO overflow */
#define I2CSSTA_SRXOF_MSK              (0x1   << 4  )
#define I2CSSTA_SRXOF                  (0x1   << 4  )
#define I2CSSTA_SRXOF_CLR              (0x0   << 4  )
#define I2CSSTA_SRXOF_SET              (0x1   << 4  )

/* I2CSSTA[SRXREQ] - Slave Receive request */
#define I2CSSTA_SRXREQ_MSK             (0x1   << 3  )
#define I2CSSTA_SRXREQ                 (0x1   << 3  )
#define I2CSSTA_SRXREQ_CLR             (0x0   << 3  )
#define I2CSSTA_SRXREQ_SET             (0x1   << 3  )

/* I2CSSTA[STXREQ] - Slave Transmit request */
#define I2CSSTA_STXREQ_MSK             (0x1   << 2  )
#define I2CSSTA_STXREQ                 (0x1   << 2  )
#define I2CSSTA_STXREQ_CLR             (0x0   << 2  )
#define I2CSSTA_STXREQ_SET             (0x1   << 2  )

/* I2CSSTA[STXUR] - Slave Transmit FIFO underflow */
#define I2CSSTA_STXUR_MSK              (0x1   << 1  )
#define I2CSSTA_STXUR                  (0x1   << 1  )
#define I2CSSTA_STXUR_CLR              (0x0   << 1  )
#define I2CSSTA_STXUR_SET              (0x1   << 1  )

/* I2CSSTA[STXFSEREQ] - Slave Tx FIFO Status or early request */
#define I2CSSTA_STXFSEREQ_MSK          (0x1   << 0  )
#define I2CSSTA_STXFSEREQ              (0x1   << 0  )
#define I2CSSTA_STXFSEREQ_CLR          (0x0   << 0  )
#define I2CSSTA_STXFSEREQ_SET          (0x1   << 0  )

/* I2CSRX[I2CSRX] - Slave receive register */
#define I2CSRX_I2CSRX_MSK              (0xFF  << 0  )

/* I2CSTX[I2CSTX] - Slave transmit register */
#define I2CSTX_I2CSTX_MSK              (0xFF  << 0  )

/* I2CALT[ALT] - Slave Alt */
#define I2CALT_ALT_MSK                 (0xFF  << 0  )

/* I2CID0[ID0] - Slave device ID 0 */
#define I2CID0_ID0_MSK                 (0xFF  << 0  )

/* I2CID1[ID1] - Slave device ID 1 */
#define I2CID1_ID1_MSK                 (0xFF  << 0  )

/* I2CID2[ID2] - Slave device ID 2 */
#define I2CID2_ID2_MSK                 (0xFF  << 0  )

/* I2CID3[ID3] - Slave device ID 3 */
#define I2CID3_ID3_MSK                 (0xFF  << 0  )

/* I2CFSTA[MFLUSH] - Flush the master transmit FIFO */
#define I2CFSTA_MFLUSH_MSK             (0x1   << 9  )
#define I2CFSTA_MFLUSH                 (0x1   << 9  )
#define I2CFSTA_MFLUSH_DIS             (0x0   << 9  ) /* Clearing to 0 has no effect. */
#define I2CFSTA_MFLUSH_EN              (0x1   << 9  ) /* Set to 1 to flush the master transmit FIFO. The master transmit FIFO will have to flushed if arbitration is lost or a slave responds with a NACK. */

/* I2CFSTA[SFLUSH] - Flush the slave transmit FIFO */
#define I2CFSTA_SFLUSH_MSK             (0x1   << 8  )
#define I2CFSTA_SFLUSH                 (0x1   << 8  )
#define I2CFSTA_SFLUSH_DIS             (0x0   << 8  ) /* Clearing to 0 has no effect. */
#define I2CFSTA_SFLUSH_EN              (0x1   << 8  ) /* Set to 1 to flush the slave transmit FIFO. */

/* I2CFSTA[MRXFSTA] - Master receive FIFO status */
#define I2CFSTA_MRXFSTA_MSK            (0x3   << 6  )
#define I2CFSTA_MRXFSTA_EMPTY          (0x0   << 6  ) /* FIFO empty               */
#define I2CFSTA_MRXFSTA_ONEBYTE        (0x1   << 6  ) /* 1 bytes in the FIFO      */
#define I2CFSTA_MRXFSTA_TWOBYTES       (0x2   << 6  ) /* 2 bytes in the FIFO      */

/* I2CFSTA[MTXFSTA] - Master transmit FIFO status */
#define I2CFSTA_MTXFSTA_MSK            (0x3   << 4  )
#define I2CFSTA_MTXFSTA_EMPTY          (0x0   << 4  ) /* FIFO empty               */
#define I2CFSTA_MTXFSTA_ONEBYTE        (0x1   << 4  ) /* 1 bytes in the FIFO      */
#define I2CFSTA_MTXFSTA_TWOBYTES       (0x2   << 4  ) /* 2 bytes in the FIFO      */

/* I2CFSTA[SRXFSTA] - Slave receive FIFO status */
#define I2CFSTA_SRXFSTA_MSK            (0x3   << 2  )
#define I2CFSTA_SRXFSTA_EMPTY          (0x0   << 2  ) /* FIFO empty               */
#define I2CFSTA_SRXFSTA_ONEBYTE        (0x1   << 2  ) /* 1 bytes in the FIFO      */
#define I2CFSTA_SRXFSTA_TWOBYTES       (0x2   << 2  ) /* 2 bytes in the FIFO      */

/* I2CFSTA[STXFSTA] - Slave transmit FIFO status */
#define I2CFSTA_STXFSTA_MSK            (0x3   << 0  )
#define I2CFSTA_STXFSTA_EMPTY          (0x0   << 0  ) /* FIFO empty               */
#define I2CFSTA_STXFSTA_ONEBYTE        (0x1   << 0  ) /* 1 bytes in the FIFO      */
#define I2CFSTA_STXFSTA_TWOBYTES       (0x2   << 0  ) /* 2 bytes in the FIFO      */

/* I2CSHCON[RESET] - Reset START STOP detect circuit */
#define I2CSHCON_RESET_MSK             (0x1   << 0  )
#define I2CSHCON_RESET                 (0x1   << 0  )
#define I2CSHCON_RESET_DIS             (0x0   << 0  )
#define I2CSHCON_RESET_EN              (0x1   << 0  )

#if defined(ADUCM320I) | defined(ADUCM322) | defined(ADUCM322I)

/* I2CASSCL[SSRTSTA] - stretch timeout for slave */
#define I2CASSCL_SSRTSTA_MSK           (0x1   << 9  )
#define I2CASSCL_SSRTSTA               (0x1   << 9  )
#define I2CASSCL_SSRTSTA_DIS           (0x0   << 9  )
#define I2CASSCL_SSRTSTA_EN            (0x1   << 9  )

/* I2CASSCL[MSRTSTA] - stretch timeout for master */
#define I2CASSCL_MSRTSTA_MSK           (0x1   << 8  )
#define I2CASSCL_MSRTSTA               (0x1   << 8  )
#define I2CASSCL_MSRTSTA_DIS           (0x0   << 8  )
#define I2CASSCL_MSRTSTA_EN            (0x1   << 8  )

/* I2CASSCL[SSTRCON] - automatic stretch mode for slave */
#define I2CASSCL_SSTRCON_MSK           (0xF   << 4  )

/* I2CASSCL[MSTRCON] - automatic stretch mode for master */
#define I2CASSCL_MSTRCON_MSK           (0xF   << 0  )

#endif

/* DACCON[PD] - DAC0 power down */
#define DACCON_PD_MSK                  (0x1   << 8  )
#define DACCON_PD                      (0x1   << 8  )

/* DACCON[EN] - DAC0 enable */
#define DACCON_EN_MSK                  (0x1   << 4  )
#define DACCON_EN                      (0x1   << 4  )

/* DACCON[RN] - DAC0 reference selection */
#define DACCON_RN_MSK                  (0x3   << 0  )

/* DACDAT[DAT] - DAC0 data */
#define DACDAT_DAT_MSK                 (0xFFF << 16 )

#if defined(ADUCM320) | defined(ADUCM320I)

/* IDACCON[CLRB] - IDAC0 Clear bit */
#define IDACCON_CLRB_MSK               (0x1   << 7  )
#define IDACCON_CLRB                   (0x1   << 7  )

/* IDACCON[SHT_EN] - IDAC0 shutdown enable */
#define IDACCON_SHT_EN_MSK             (0x1   << 6  )
#define IDACCON_SHT_EN                 (0x1   << 6  )

/* IDACCON[BW] - IDAC0 bandwidth */
#define IDACCON_BW_MSK                 (0xF   << 2  )

/* IDACCON[PUL] - IDAC0 pull down */
#define IDACCON_PUL_MSK                (0x1   << 1  )
#define IDACCON_PUL                    (0x1   << 1  )

/* IDACCON[PD] - IDAC0 power down */
#define IDACCON_PD_MSK                 (0x1   << 0  )
#define IDACCON_PD                     (0x1   << 0  )
#define IDACCON_PD_ON                  (0x0   << 0  ) /* Powers IDAC0 up          */
#define IDACCON_PD_OFF                 (0x1   << 0  ) /* Powers IDAC0 down        */

/* IDACDAT[DATH] - IDAC0 high data */
#define IDACDAT_DATH_MSK               (0x7FF << 17 )

/* IDACDAT[DATL] - IDAC0 low data */
#define IDACDAT_DATL_MSK               (0x1F  << 12 )

/* IDACDAT[SYNC] - IDAC0 sync bits */
#define IDACDAT_SYNC_MSK               (0x3F  << 0  )

#endif


// -----------------------------------------------------------------------------
// -----                             TIMER                                 -----
// -----------------------------------------------------------------------------

/**
  * @brief TIMER (MMR_TIMER)
  */

typedef struct MMR_TIMER {                  /*!< MMR_TIMER Structure                   */
  __IO uint16_t  TLD;                       /*!< 16-bit load value register            */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  TVAL;                      /*!< 16-bit timer value register           */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  TCON;                      /*!< Control register                      */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  TCLRI;                     /*!< Clear interrupt register              */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  TCAP;                      /*!< Capture register                      */
  __I  uint16_t  RESERVED4[5];
  __IO uint16_t  TSTA;                      /*!< Status register                       */
} MMR_TIMER_t;

/* Reset Value for T0LD*/
#define T0LD_RVAL                      0x0 

/* T0LD[LOAD] - Load value */
#define T0LD_LOAD_MSK                  (0xFFFF << 0  )

/* Reset Value for T0VAL*/
#define T0VAL_RVAL                     0x0 

/* T0VAL[VAL] - Current count */
#define T0VAL_VAL_MSK                  (0xFFFF << 0  )

/* Reset Value for T0CON*/
#define T0CON_RVAL                     0xA 

/* T0CON[EVENTEN] - Event select */
#define T0CON_EVENTEN_BBA              (*(volatile unsigned long *) 0x42000130)
#define T0CON_EVENTEN_MSK              (0x1   << 12 )
#define T0CON_EVENTEN                  (0x1   << 12 )
#define T0CON_EVENTEN_DIS              (0x0   << 12 ) /* Events will not be captured */
#define T0CON_EVENTEN_EN               (0x1   << 12 ) /* Events will be captured  */

/* T0CON[EVENT] - Event select range */
#define T0CON_EVENT_MSK                (0xF   << 8  )

/* T0CON[RLD] - Reload control */
#define T0CON_RLD_BBA                  (*(volatile unsigned long *) 0x4200011C)
#define T0CON_RLD_MSK                  (0x1   << 7  )
#define T0CON_RLD                      (0x1   << 7  )
#define T0CON_RLD_EN                   (0x1   << 7  ) /* Resets the up/down counter when TCLRI[0] is set */
#define T0CON_RLD_DIS                  (0x0   << 7  ) /* Up/Down counter is only reset on a timeout event */

/* T0CON[CLK] - Clock select */
#define T0CON_CLK_MSK                  (0x3   << 5  )
#define T0CON_CLK_PCLK                 (0x0   << 5  ) /* PCLK.                    */
#define T0CON_CLK_HCLK                 (0x1   << 5  ) /* HCLK.                    */
#define T0CON_CLK_LFOSC                (0x2   << 5  ) /* LFOSC. 32 KHz OSC        */
#define T0CON_CLK_HFXTAL               (0x3   << 5  ) /* HFXTAL. 16 MHz OSC or XTAL (Dependent on CLKCON0.11) */

/* T0CON[ENABLE] - Timer enable */
#define T0CON_ENABLE_BBA               (*(volatile unsigned long *) 0x42000110)
#define T0CON_ENABLE_MSK               (0x1   << 4  )
#define T0CON_ENABLE                   (0x1   << 4  )
#define T0CON_ENABLE_DIS               (0x0   << 4  ) /* DIS. Timer is disabled (default) */
#define T0CON_ENABLE_EN                (0x1   << 4  ) /* EN. Timer is enabled     */

/* T0CON[MOD] - Timer mode */
#define T0CON_MOD_BBA                  (*(volatile unsigned long *) 0x4200010C)
#define T0CON_MOD_MSK                  (0x1   << 3  )
#define T0CON_MOD                      (0x1   << 3  )
#define T0CON_MOD_FREERUN              (0x0   << 3  ) /* FREERUN.Timer runs in free running mode */
#define T0CON_MOD_PERIODIC             (0x1   << 3  ) /* PERIODIC. Timer runs in periodic mode (default) */

/* T0CON[UP] - Count up */
#define T0CON_UP_BBA                   (*(volatile unsigned long *) 0x42000108)
#define T0CON_UP_MSK                   (0x1   << 2  )
#define T0CON_UP                       (0x1   << 2  )
#define T0CON_UP_DIS                   (0x0   << 2  ) /* DIS. Timer is set to count down (default) */
#define T0CON_UP_EN                    (0x1   << 2  ) /* EN. Timer is set to count up */

/* T0CON[PRE] - Prescaler */
#define T0CON_PRE_MSK                  (0x3   << 0  )
#define T0CON_PRE_DIV1                 (0x0   << 0  ) /* source_clock / [1 or 4]  */
#define T0CON_PRE_DIV16                (0x1   << 0  ) /* source_clock / 16        */
#define T0CON_PRE_DIV256               (0x2   << 0  ) /* source_clock / 256       */
#define T0CON_PRE_DIV32768             (0x3   << 0  ) /* source_clock / 32,768    */

/* Reset Value for T0CLRI*/
#define T0CLRI_RVAL                    0x0 

/* T0CLRI[CAP] - Clear captured event interrupt */
#define T0CLRI_CAP_BBA                 (*(volatile unsigned long *) 0x42000184)
#define T0CLRI_CAP_MSK                 (0x1   << 1  )
#define T0CLRI_CAP                     (0x1   << 1  )
#define T0CLRI_CAP_CLR                 (0x1   << 1  ) /* Clear the capture event interrupt */

/* T0CLRI[TMOUT] - Clear timeout interrupt */
#define T0CLRI_TMOUT_BBA               (*(volatile unsigned long *) 0x42000180)
#define T0CLRI_TMOUT_MSK               (0x1   << 0  )
#define T0CLRI_TMOUT                   (0x1   << 0  )
#define T0CLRI_TMOUT_CLR               (0x1   << 0  ) /* Clears the timeout interrupt */

/* Reset Value for T0CAP*/
#define T0CAP_RVAL                     0x0 

/* T0CAP[CAP] - 16-bit captured value */
#define T0CAP_CAP_MSK                  (0xFFFF << 0  )

/* Reset Value for T0STA*/
#define T0STA_RVAL                     0x0 

/* T0STA[PDOK] - TCLRI synchronization */
#define T0STA_PDOK_BBA                 (*(volatile unsigned long *) 0x4200039C)
#define T0STA_PDOK_MSK                 (0x1   << 7  )
#define T0STA_PDOK                     (0x1   << 7  )
#define T0STA_PDOK_CLR                 (0x0   << 7  ) /* CLR. The interrupt is cleared in the timer clock domain */
#define T0STA_PDOK_SET                 (0x1   << 7  ) /* SET. TCLRI[0] is being updated in the timer clock domain */

/* T0STA[BUSY] - Timer Busy */
#define T0STA_BUSY_BBA                 (*(volatile unsigned long *) 0x42000398)
#define T0STA_BUSY_MSK                 (0x1   << 6  )
#define T0STA_BUSY                     (0x1   << 6  )
#define T0STA_BUSY_CLR                 (0x0   << 6  ) /* CLR. Timer ready to receive commands to TCON */
#define T0STA_BUSY_SET                 (0x1   << 6  ) /* SET. Timer not ready to receive commands to TCON */

/* T0STA[CAP] - Capture event pending */
#define T0STA_CAP_BBA                  (*(volatile unsigned long *) 0x42000384)
#define T0STA_CAP_MSK                  (0x1   << 1  )
#define T0STA_CAP                      (0x1   << 1  )
#define T0STA_CAP_CLR                  (0x0   << 1  ) /* CLR. No capture event is pending */
#define T0STA_CAP_SET                  (0x1   << 1  ) /* SET. A capture event is pending */

/* T0STA[TMOUT] - Timeout event occurred */
#define T0STA_TMOUT_BBA                (*(volatile unsigned long *) 0x42000380)
#define T0STA_TMOUT_MSK                (0x1   << 0  )
#define T0STA_TMOUT                    (0x1   << 0  )
#define T0STA_TMOUT_CLR                (0x0   << 0  ) /* CLR. No timeout event has occurred */
#define T0STA_TMOUT_SET                (0x1   << 0  ) /* SET. A timeout event has occurred */

/* Reset Value for T1LD*/
#define T1LD_RVAL                      0x0 

/* T1LD[LOAD] - Load value */
#define T1LD_LOAD_MSK                  (0xFFFF << 0  )

/* Reset Value for T1VAL*/
#define T1VAL_RVAL                     0x0 

/* T1VAL[VAL] - Current count */
#define T1VAL_VAL_MSK                  (0xFFFF << 0  )

/* Reset Value for T1CON*/
#define T1CON_RVAL                     0xA 

/* T1CON[EVENTEN] - Event select */
#define T1CON_EVENTEN_BBA              (*(volatile unsigned long *) 0x42008130)
#define T1CON_EVENTEN_MSK              (0x1   << 12 )
#define T1CON_EVENTEN                  (0x1   << 12 )
#define T1CON_EVENTEN_DIS              (0x0   << 12 ) /* Events will not be captured */
#define T1CON_EVENTEN_EN               (0x1   << 12 ) /* Events will be captured  */

/* T1CON[EVENT] - Event select range */
#define T1CON_EVENT_MSK                (0xF   << 8  )

/* T1CON[RLD] - Reload control */
#define T1CON_RLD_BBA                  (*(volatile unsigned long *) 0x4200811C)
#define T1CON_RLD_MSK                  (0x1   << 7  )
#define T1CON_RLD                      (0x1   << 7  )
#define T1CON_RLD_EN                   (0x1   << 7  ) /* Resets the up/down counter when TCLRI[0] is set */
#define T1CON_RLD_DIS                  (0x0   << 7  ) /* Up/Down counter is only reset on a timeout event */

/* T1CON[CLK] - Clock select */
#define T1CON_CLK_MSK                  (0x3   << 5  )
#define T1CON_CLK_PCLK                 (0x0   << 5  ) /* PCLK.                    */
#define T1CON_CLK_HCLK                 (0x1   << 5  ) /* HCLK.                    */
#define T1CON_CLK_LFOSC                (0x2   << 5  ) /* LFOSC. 32 KHz OSC        */
#define T1CON_CLK_HFXTAL               (0x3   << 5  ) /* HFXTAL. 16 MHz OSC or XTAL (Dependent on CLKCON0.11) */

/* T1CON[ENABLE] - Timer enable */
#define T1CON_ENABLE_BBA               (*(volatile unsigned long *) 0x42008110)
#define T1CON_ENABLE_MSK               (0x1   << 4  )
#define T1CON_ENABLE                   (0x1   << 4  )
#define T1CON_ENABLE_DIS               (0x0   << 4  ) /* DIS. Timer is disabled (default) */
#define T1CON_ENABLE_EN                (0x1   << 4  ) /* EN. Timer is enabled     */

/* T1CON[MOD] - Timer mode */
#define T1CON_MOD_BBA                  (*(volatile unsigned long *) 0x4200810C)
#define T1CON_MOD_MSK                  (0x1   << 3  )
#define T1CON_MOD                      (0x1   << 3  )
#define T1CON_MOD_FREERUN              (0x0   << 3  ) /* FREERUN. Timer runs in free running mode */
#define T1CON_MOD_PERIODIC             (0x1   << 3  ) /* PERIODIC. Timer runs in periodic mode (default) */

/* T1CON[UP] - Count up */
#define T1CON_UP_BBA                   (*(volatile unsigned long *) 0x42008108)
#define T1CON_UP_MSK                   (0x1   << 2  )
#define T1CON_UP                       (0x1   << 2  )
#define T1CON_UP_DIS                   (0x0   << 2  ) /* DIS. Timer is set to count down (default) */
#define T1CON_UP_EN                    (0x1   << 2  ) /* EN. Timer is set to count up */

/* T1CON[PRE] - Prescaler */
#define T1CON_PRE_MSK                  (0x3   << 0  )
#define T1CON_PRE_DIV1                 (0x0   << 0  ) /* source_clock / [1 or 4]  */
#define T1CON_PRE_DIV16                (0x1   << 0  ) /* source_clock / 16        */
#define T1CON_PRE_DIV256               (0x2   << 0  ) /* source_clock / 256       */
#define T1CON_PRE_DIV32768             (0x3   << 0  ) /* source_clock / 32,768    */

/* Reset Value for T1CLRI*/
#define T1CLRI_RVAL                    0x0 

/* T1CLRI[CAP] - Clear captured event interrupt */
#define T1CLRI_CAP_BBA                 (*(volatile unsigned long *) 0x42008184)
#define T1CLRI_CAP_MSK                 (0x1   << 1  )
#define T1CLRI_CAP                     (0x1   << 1  )
#define T1CLRI_CAP_CLR                 (0x1   << 1  ) /* Clear the capture event interrupt */

/* T1CLRI[TMOUT] - Clear timeout interrupt */
#define T1CLRI_TMOUT_BBA               (*(volatile unsigned long *) 0x42008180)
#define T1CLRI_TMOUT_MSK               (0x1   << 0  )
#define T1CLRI_TMOUT                   (0x1   << 0  )
#define T1CLRI_TMOUT_CLR               (0x1   << 0  ) /* Clears the timeout interrupt */

/* Reset Value for T1CAP*/
#define T1CAP_RVAL                     0x0 

/* T1CAP[CAP] - 16-bit captured value */
#define T1CAP_CAP_MSK                  (0xFFFF << 0  )

/* Reset Value for T1STA*/
#define T1STA_RVAL                     0x0 

/* T1STA[PDOK] - TCLRI synchronization */
#define T1STA_PDOK_BBA                 (*(volatile unsigned long *) 0x4200839C)
#define T1STA_PDOK_MSK                 (0x1   << 7  )
#define T1STA_PDOK                     (0x1   << 7  )
#define T1STA_PDOK_CLR                 (0x0   << 7  ) /* CLR. The interrupt is cleared in the timer clock domain */
#define T1STA_PDOK_SET                 (0x1   << 7  ) /* SET. TCLRI[0] is being updated in the timer clock domain */

/* T1STA[BUSY] - Timer Busy */
#define T1STA_BUSY_BBA                 (*(volatile unsigned long *) 0x42008398)
#define T1STA_BUSY_MSK                 (0x1   << 6  )
#define T1STA_BUSY                     (0x1   << 6  )
#define T1STA_BUSY_CLR                 (0x0   << 6  ) /* CLR. Timer ready to receive commands to TCON */
#define T1STA_BUSY_SET                 (0x1   << 6  ) /* SET. Timer not ready to receive commands to TCON */

/* T1STA[CAP] - Capture event pending */
#define T1STA_CAP_BBA                  (*(volatile unsigned long *) 0x42008384)
#define T1STA_CAP_MSK                  (0x1   << 1  )
#define T1STA_CAP                      (0x1   << 1  )
#define T1STA_CAP_CLR                  (0x0   << 1  ) /* CLR. No capture event is pending */
#define T1STA_CAP_SET                  (0x1   << 1  ) /* SET. A capture event is pending */

/* T1STA[TMOUT] - Timeout event occurred */
#define T1STA_TMOUT_BBA                (*(volatile unsigned long *) 0x42008380)
#define T1STA_TMOUT_MSK                (0x1   << 0  )
#define T1STA_TMOUT                    (0x1   << 0  )
#define T1STA_TMOUT_CLR                (0x0   << 0  ) /* CLR. No timeout event has occurred */
#define T1STA_TMOUT_SET                (0x1   << 0  ) /* SET. A timeout event has occurred */

/* Reset Value for T2LD*/
#define T2LD_RVAL                      0x0 

/* T2LD[LOAD] - Load value */
#define T2LD_LOAD_MSK                  (0xFFFF << 0  )

/* Reset Value for T2VAL*/
#define T2VAL_RVAL                     0x0 

/* T2VAL[VAL] - Current count */
#define T2VAL_VAL_MSK                  (0xFFFF << 0  )

/* Reset Value for T2CON*/
#define T2CON_RVAL                     0xA 

/* T2CON[EVENTEN] - Event select */
#define T2CON_EVENTEN_BBA              (*(volatile unsigned long *) 0x42010130)
#define T2CON_EVENTEN_MSK              (0x1   << 12 )
#define T2CON_EVENTEN                  (0x1   << 12 )
#define T2CON_EVENTEN_DIS              (0x0   << 12 ) /* Events will not be captured */
#define T2CON_EVENTEN_EN               (0x1   << 12 ) /* Events will be captured  */

/* T2CON[EVENT] - Event select range */
#define T2CON_EVENT_MSK                (0xF   << 8  )

/* T2CON[RLD] - Reload control */
#define T2CON_RLD_BBA                  (*(volatile unsigned long *) 0x4201011C)
#define T2CON_RLD_MSK                  (0x1   << 7  )
#define T2CON_RLD                      (0x1   << 7  )
#define T2CON_RLD_EN                   (0x1   << 7  ) /* Resets the up/down counter when TCLRI[0] is set */
#define T2CON_RLD_DIS                  (0x0   << 7  ) /* Up/Down counter is only reset on a timeout event */

/* T2CON[CLK] - Clock select */
#define T2CON_CLK_MSK                  (0x3   << 5  )
#define T2CON_CLK_PCLK                 (0x0   << 5  ) /* PCLK                     */
#define T2CON_CLK_HCLK                 (0x1   << 5  ) /* HCLK                     */
#define T2CON_CLK_LFOSC                (0x2   << 5  ) /* LFOSC. 32 KHz OSC        */
#define T2CON_CLK_HFXTAL               (0x3   << 5  ) /* HFXTAL. 16 MHz OSC or XTAL (Dependent on CLKCON0.11) */

/* T2CON[ENABLE] - Timer enable */
#define T2CON_ENABLE_BBA               (*(volatile unsigned long *) 0x42010110)
#define T2CON_ENABLE_MSK               (0x1   << 4  )
#define T2CON_ENABLE                   (0x1   << 4  )
#define T2CON_ENABLE_DIS               (0x0   << 4  ) /* DIS. Timer is disabled (default) */
#define T2CON_ENABLE_EN                (0x1   << 4  ) /* EN. Timer is enabled     */

/* T2CON[MOD] - Timer mode */
#define T2CON_MOD_BBA                  (*(volatile unsigned long *) 0x4201010C)
#define T2CON_MOD_MSK                  (0x1   << 3  )
#define T2CON_MOD                      (0x1   << 3  )
#define T2CON_MOD_FREERUN              (0x0   << 3  ) /* FREERUN. Timer runs in free running mode */
#define T2CON_MOD_PERIODIC             (0x1   << 3  ) /* PERIODIC. Timer runs in periodic mode (default) */

/* T2CON[UP] - Count up */
#define T2CON_UP_BBA                   (*(volatile unsigned long *) 0x42010108)
#define T2CON_UP_MSK                   (0x1   << 2  )
#define T2CON_UP                       (0x1   << 2  )
#define T2CON_UP_DIS                   (0x0   << 2  ) /* DIS. Timer is set to count down (default) */
#define T2CON_UP_EN                    (0x1   << 2  ) /* EN. Timer is set to count up */

/* T2CON[PRE] - Prescaler */
#define T2CON_PRE_MSK                  (0x3   << 0  )
#define T2CON_PRE_DIV1                 (0x0   << 0  ) /* source_clock / [1 or 4]  */
#define T2CON_PRE_DIV16                (0x1   << 0  ) /* source_clock / 16        */
#define T2CON_PRE_DIV256               (0x2   << 0  ) /* source_clock / 256       */
#define T2CON_PRE_DIV32768             (0x3   << 0  ) /* source_clock / 32,768    */

/* Reset Value for T2CLRI*/
#define T2CLRI_RVAL                    0x0 

/* T2CLRI[CAP] - Clear captured event interrupt */
#define T2CLRI_CAP_BBA                 (*(volatile unsigned long *) 0x42010184)
#define T2CLRI_CAP_MSK                 (0x1   << 1  )
#define T2CLRI_CAP                     (0x1   << 1  )
#define T2CLRI_CAP_CLR                 (0x1   << 1  ) /* Clear the capture event interrupt */

/* T2CLRI[TMOUT] - Clear timeout interrupt */
#define T2CLRI_TMOUT_BBA               (*(volatile unsigned long *) 0x42010180)
#define T2CLRI_TMOUT_MSK               (0x1   << 0  )
#define T2CLRI_TMOUT                   (0x1   << 0  )
#define T2CLRI_TMOUT_CLR               (0x1   << 0  ) /* Clears the timeout interrupt */

/* Reset Value for T2CAP*/
#define T2CAP_RVAL                     0x0 

/* T2CAP[CAP] - 16-bit captured value */
#define T2CAP_CAP_MSK                  (0xFFFF << 0  )

/* Reset Value for T2STA*/
#define T2STA_RVAL                     0x0 

/* T2STA[PDOK] - TCLRI synchronization */
#define T2STA_PDOK_BBA                 (*(volatile unsigned long *) 0x4201039C)
#define T2STA_PDOK_MSK                 (0x1   << 7  )
#define T2STA_PDOK                     (0x1   << 7  )
#define T2STA_PDOK_CLR                 (0x0   << 7  ) /* CLR. The interrupt is cleared in the timer clock domain */
#define T2STA_PDOK_SET                 (0x1   << 7  ) /* SET. TCLRI[0] is being updated in the timer clock domain */

/* T2STA[BUSY] - Timer Busy */
#define T2STA_BUSY_BBA                 (*(volatile unsigned long *) 0x42010398)
#define T2STA_BUSY_MSK                 (0x1   << 6  )
#define T2STA_BUSY                     (0x1   << 6  )
#define T2STA_BUSY_CLR                 (0x0   << 6  ) /* CLR. Timer ready to receive commands to TCON */
#define T2STA_BUSY_SET                 (0x1   << 6  ) /* SET. Timer not ready to receive commands to TCON */

/* T2STA[CAP] - Capture event pending */
#define T2STA_CAP_BBA                  (*(volatile unsigned long *) 0x42010384)
#define T2STA_CAP_MSK                  (0x1   << 1  )
#define T2STA_CAP                      (0x1   << 1  )
#define T2STA_CAP_CLR                  (0x0   << 1  ) /* CLR. No capture event is pending */
#define T2STA_CAP_SET                  (0x1   << 1  ) /* SET. A capture event is pending */

/* T2STA[TMOUT] - Timeout event occurred */
#define T2STA_TMOUT_BBA                (*(volatile unsigned long *) 0x42010380)
#define T2STA_TMOUT_MSK                (0x1   << 0  )
#define T2STA_TMOUT                    (0x1   << 0  )
#define T2STA_TMOUT_CLR                (0x0   << 0  ) /* CLR. No timeout event has occurred */
#define T2STA_TMOUT_SET                (0x1   << 0  ) /* SET. A timeout event has occurred */
// ------------------------------------------------------------------------------------------------
// -----                                        ID                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief misc16 (MMR_ID)
  */

typedef struct MMR_ID {                     /*!< MMR_ID Structure                      */
  __IO uint16_t  CHIPID;                    /*!< Digital die ID                        */
} MMR_ID_t;

/* Reset Value for CHIPID*/
#define CHIPID_RVAL                    0x561 

/* CHIPID[PARTID] - Part Identifier */
#define CHIPID_PARTID_MSK              (0xFFF << 4  )

/* CHIPID[REV] - Silicon Revision Number */
#define CHIPID_REV_MSK                 (0xF   << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        PWRCTL                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief always_on (MMR_PWRCTL)
  */

typedef struct MMR_PWRCTL {                 /*!< MMR_PWRCTL Structure                  */
  __IO uint16_t  PWRMOD;                    /*!< Power modes                           */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  PWRKEY;                    /*!< Key protection for PWRMOD             */
} MMR_PWRCTL_t;

/* Reset Value for PWRMOD*/
#define PWRMOD_RVAL                    0x0 

/* PWRMOD[WICENACK] - WIC Acknowledgment for SLEEPDEEP */
#define PWRMOD_WICENACK_BBA            (*(volatile unsigned long *) 0x4204800C)
#define PWRMOD_WICENACK_MSK            (0x1   << 3  )
#define PWRMOD_WICENACK                (0x1   << 3  )
#define PWRMOD_WICENACK_DIS            (0x0   << 3  )
#define PWRMOD_WICENACK_EN             (0x1   << 3  )

/* PWRMOD[PWRMOD] - Power modes control bits */
#define PWRMOD_PWRMOD_MSK              (0x3   << 0  )
#define PWRMOD_PWRMOD_FULLACTIVE       (0x0   << 0  ) /* Active Mode              */
#define PWRMOD_PWRMOD_CORESLEEP        (0x1   << 0  ) /* CORE_SLEEP Mode          */
#define PWRMOD_PWRMOD_SYSSLEEP         (0x2   << 0  ) /* SYS_SLEEP Mode           */
#define PWRMOD_PWRMOD_HIBERNATE        (0x3   << 0  ) /* Hibernate Mode           */

/* Reset Value for PWRKEY*/
#define PWRKEY_RVAL                    0x0 

/* PWRKEY[PWRKEY] - Power control key register */
#define PWRKEY_PWRKEY_MSK              (0xFFFF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        RESET                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief always_on (MMR_RESET)
  */

typedef struct MMR_RESET {                  /*!< MMR_RESET Structure                   */
  __IO uint16_t  RSTCFG;                    /*!< Reset configuration                   */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  RSTKEY;                    /*!< Key protection for RSTCFG             */
  __I  uint16_t  RESERVED1[25];
  __IO uint16_t  RSTSTA;                    /*!< Reset status                          */
} MMR_RESET_t;

/* Reset Value for RSTCFG*/
#define RSTCFG_RVAL                    0x0 

/* RSTCFG[GPIO_PLA_RETAIN] - GPIO/PLA retain their status after WDT and software reset */
#define RSTCFG_GPIO_PLA_RETAIN_BBA     (*(volatile unsigned long *) 0x42048100)
#define RSTCFG_GPIO_PLA_RETAIN_MSK     (0x1   << 0  )
#define RSTCFG_GPIO_PLA_RETAIN         (0x1   << 0  )
#define RSTCFG_GPIO_PLA_RETAIN_DIS     (0x1   << 0  ) /* GPIO/PLA don't retain status after watchdog or software reset. */
#define RSTCFG_GPIO_PLA_RETAIN_EN      (0x0   << 0  ) /* GPIO/PLA retain status after watchdog or software reset */

/* Reset Value for RSTKEY*/
#define RSTKEY_RVAL                    0x0 

/* RSTKEY[RSTKEY] - Reset configuration key register */
#define RSTKEY_RSTKEY_MSK              (0xFFFF << 0  )

/* Reset Value for RSTSTA*/
#define RSTSTA_RVAL                    0x0 

/* RSTSTA[SWRST] - Software reset */
#define RSTSTA_SWRST_BBA               (*(volatile unsigned long *) 0x4204880C)
#define RSTSTA_SWRST_MSK               (0x1   << 3  )
#define RSTSTA_SWRST                   (0x1   << 3  )
#define RSTSTA_SWRST_DIS               (0x0   << 3  )
#define RSTSTA_SWRST_EN                (0x1   << 3  )

/* RSTSTA[WDRST] - Watchdog timeout */
#define RSTSTA_WDRST_BBA               (*(volatile unsigned long *) 0x42048808)
#define RSTSTA_WDRST_MSK               (0x1   << 2  )
#define RSTSTA_WDRST                   (0x1   << 2  )
#define RSTSTA_WDRST_DIS               (0x0   << 2  )
#define RSTSTA_WDRST_EN                (0x1   << 2  )

/* RSTSTA[EXTRST] - External reset */
#define RSTSTA_EXTRST_BBA              (*(volatile unsigned long *) 0x42048804)
#define RSTSTA_EXTRST_MSK              (0x1   << 1  )
#define RSTSTA_EXTRST                  (0x1   << 1  )
#define RSTSTA_EXTRST_DIS              (0x0   << 1  )
#define RSTSTA_EXTRST_EN               (0x1   << 1  )

/* RSTSTA[POR] - Power-on reset */
#define RSTSTA_POR_BBA                 (*(volatile unsigned long *) 0x42048800)
#define RSTSTA_POR_MSK                 (0x1   << 0  )
#define RSTSTA_POR                     (0x1   << 0  )
#define RSTSTA_POR_DIS                 (0x0   << 0  )
#define RSTSTA_POR_EN                  (0x1   << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        INTERRUPT                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief always_on (MMR_INTERRUPT)
  */

typedef struct MMR_INTERRUPT {              /*!< MMR_INTERRUPT Structure               */
  __IO uint16_t  EI0CFG;                    /*!< External Interrupt configuration 0    */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  EI1CFG;                    /*!< External Interrupt configuration 1    */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  EI2CFG;                    /*!< External Interrupt configuration 2    */
  __I  uint16_t  RESERVED2[3];
  __IO uint16_t  EICLR;                     /*!< External Interrupt clear              */
} MMR_INTERRUPT_t;

/* Reset Value for EI0CFG*/
#define EI0CFG_RVAL                    0x0 

/* EI0CFG[IRQ3EN] - External Interrupt 3 enable bit */
#define EI0CFG_IRQ3EN_BBA              (*(volatile unsigned long *) 0x4204843C)
#define EI0CFG_IRQ3EN_MSK              (0x1   << 15 )
#define EI0CFG_IRQ3EN                  (0x1   << 15 )
#define EI0CFG_IRQ3EN_DIS              (0x0   << 15 ) /* External Interrupt 3 disabled */
#define EI0CFG_IRQ3EN_EN               (0x1   << 15 ) /* External Interrupt 3 enabled */

/* EI0CFG[IRQ3MDE] - External Interrupt 3 Mode registers */
#define EI0CFG_IRQ3MDE_MSK             (0x7   << 12 )
#define EI0CFG_IRQ3MDE_RISE            (0x0   << 12 ) /* Rising edge              */
#define EI0CFG_IRQ3MDE_FALL            (0x1   << 12 ) /* Falling edge             */
#define EI0CFG_IRQ3MDE_RISEORFALL      (0x2   << 12 ) /* Rising or falling edge   */
#define EI0CFG_IRQ3MDE_HIGHLEVEL       (0x3   << 12 ) /* High level               */
#define EI0CFG_IRQ3MDE_LOWLEVEL        (0x4   << 12 ) /* Low level                */

/* EI0CFG[IRQ2EN] - External Interrupt 2 Enable bit */
#define EI0CFG_IRQ2EN_BBA              (*(volatile unsigned long *) 0x4204842C)
#define EI0CFG_IRQ2EN_MSK              (0x1   << 11 )
#define EI0CFG_IRQ2EN                  (0x1   << 11 )
#define EI0CFG_IRQ2EN_DIS              (0x0   << 11 ) /* External Interrupt 2 disabled */
#define EI0CFG_IRQ2EN_EN               (0x1   << 11 ) /* External Interrupt 2 enabled */

/* EI0CFG[IRQ2MDE] - External Interrupt 2 Mode registers */
#define EI0CFG_IRQ2MDE_MSK             (0x7   << 8  )
#define EI0CFG_IRQ2MDE_RISE            (0x0   << 8  ) /* Rising edge              */
#define EI0CFG_IRQ2MDE_FALL            (0x1   << 8  ) /* Falling edge             */
#define EI0CFG_IRQ2MDE_RISEORFALL      (0x2   << 8  ) /* Rising or falling edge   */
#define EI0CFG_IRQ2MDE_HIGHLEVEL       (0x3   << 8  ) /* High level               */
#define EI0CFG_IRQ2MDE_LOWLEVEL        (0x4   << 8  ) /* Low level                */

/* EI0CFG[IRQ1EN] - External Interrupt 1 Enable bit */
#define EI0CFG_IRQ1EN_BBA              (*(volatile unsigned long *) 0x4204841C)
#define EI0CFG_IRQ1EN_MSK              (0x1   << 7  )
#define EI0CFG_IRQ1EN                  (0x1   << 7  )
#define EI0CFG_IRQ1EN_DIS              (0x0   << 7  ) /* External Interrupt 0 disabled */
#define EI0CFG_IRQ1EN_EN               (0x1   << 7  ) /* External Interrupt 0 enabled */

/* EI0CFG[IRQ1MDE] - External Interrupt 1 Mode registers */
#define EI0CFG_IRQ1MDE_MSK             (0x7   << 4  )
#define EI0CFG_IRQ1MDE_RISE            (0x0   << 4  ) /* Rising edge              */
#define EI0CFG_IRQ1MDE_FALL            (0x1   << 4  ) /* Falling edge             */
#define EI0CFG_IRQ1MDE_RISEORFALL      (0x2   << 4  ) /* Rising or falling edge   */
#define EI0CFG_IRQ1MDE_HIGHLEVEL       (0x3   << 4  ) /* High level               */
#define EI0CFG_IRQ1MDE_LOWLEVEL        (0x4   << 4  ) /* Low level                */

/* EI0CFG[IRQ0EN] - External Interrupt 0 Enable bit */
#define EI0CFG_IRQ0EN_BBA              (*(volatile unsigned long *) 0x4204840C)
#define EI0CFG_IRQ0EN_MSK              (0x1   << 3  )
#define EI0CFG_IRQ0EN                  (0x1   << 3  )
#define EI0CFG_IRQ0EN_DIS              (0x0   << 3  ) /* External Interrupt 0 disabled */
#define EI0CFG_IRQ0EN_EN               (0x1   << 3  ) /* External Interrupt 0 enabled */

/* EI0CFG[IRQ0MDE] - External Interrupt 0 Mode registers */
#define EI0CFG_IRQ0MDE_MSK             (0x7   << 0  )
#define EI0CFG_IRQ0MDE_RISE            (0x0   << 0  ) /* Rising edge              */
#define EI0CFG_IRQ0MDE_FALL            (0x1   << 0  ) /* Falling edge             */
#define EI0CFG_IRQ0MDE_RISEORFALL      (0x2   << 0  ) /* Rising or falling edge   */
#define EI0CFG_IRQ0MDE_HIGHLEVEL       (0x3   << 0  ) /* High level               */
#define EI0CFG_IRQ0MDE_LOWLEVEL        (0x4   << 0  ) /* Low level                */

/* Reset Value for EI1CFG*/
#define EI1CFG_RVAL                    0x0 

/* EI1CFG[IRQ7EN] - External Interrupt 7 enable bit */
#define EI1CFG_IRQ7EN_BBA              (*(volatile unsigned long *) 0x420484BC)
#define EI1CFG_IRQ7EN_MSK              (0x1   << 15 )
#define EI1CFG_IRQ7EN                  (0x1   << 15 )
#define EI1CFG_IRQ7EN_DIS              (0x0   << 15 ) /* External Interrupt 7 disabled */
#define EI1CFG_IRQ7EN_EN               (0x1   << 15 ) /* External Interrupt 7 enabled */

/* EI1CFG[IRQ7MDE] - External Interrupt 7 Mode registers */
#define EI1CFG_IRQ7MDE_MSK             (0x7   << 12 )
#define EI1CFG_IRQ7MDE_RISE            (0x0   << 12 ) /* Rising edge              */
#define EI1CFG_IRQ7MDE_FALL            (0x1   << 12 ) /* Falling edge             */
#define EI1CFG_IRQ7MDE_RISEORFALL      (0x2   << 12 ) /* Rising or falling edge   */
#define EI1CFG_IRQ7MDE_HIGHLEVEL       (0x3   << 12 ) /* High level               */
#define EI1CFG_IRQ7MDE_LOWLEVEL        (0x4   << 12 ) /* Low level                */

/* EI1CFG[IRQ6EN] - External Interrupt 6 Enable bit */
#define EI1CFG_IRQ6EN_BBA              (*(volatile unsigned long *) 0x420484AC)
#define EI1CFG_IRQ6EN_MSK              (0x1   << 11 )
#define EI1CFG_IRQ6EN                  (0x1   << 11 )
#define EI1CFG_IRQ6EN_DIS              (0x0   << 11 ) /* External Interrupt 6 disabled */
#define EI1CFG_IRQ6EN_EN               (0x1   << 11 ) /* External Interrupt 6 enabled */

/* EI1CFG[IRQ6MDE] - External Interrupt 6 Mode registers */
#define EI1CFG_IRQ6MDE_MSK             (0x7   << 8  )
#define EI1CFG_IRQ6MDE_RISE            (0x0   << 8  ) /* Rising edge              */
#define EI1CFG_IRQ6MDE_FALL            (0x1   << 8  ) /* Falling edge             */
#define EI1CFG_IRQ6MDE_RISEORFALL      (0x2   << 8  ) /* Rising or falling edge   */
#define EI1CFG_IRQ6MDE_HIGHLEVEL       (0x3   << 8  ) /* High level               */
#define EI1CFG_IRQ6MDE_LOWLEVEL        (0x4   << 8  ) /* Low level                */

/* EI1CFG[IRQ5EN] - External Interrupt 5 Enable bit */
#define EI1CFG_IRQ5EN_BBA              (*(volatile unsigned long *) 0x4204849C)
#define EI1CFG_IRQ5EN_MSK              (0x1   << 7  )
#define EI1CFG_IRQ5EN                  (0x1   << 7  )
#define EI1CFG_IRQ5EN_DIS              (0x0   << 7  ) /* External Interrupt 5 disabled */
#define EI1CFG_IRQ5EN_EN               (0x1   << 7  ) /* External Interrupt 5 enabled */

/* EI1CFG[IRQ5MDE] - External Interrupt 5 Mode registers */
#define EI1CFG_IRQ5MDE_MSK             (0x7   << 4  )
#define EI1CFG_IRQ5MDE_RISING          (0x0   << 4  ) /* Rising edge              */
#define EI1CFG_IRQ5MDE_FALLING         (0x1   << 4  ) /* Falling edge             */
#define EI1CFG_IRQ5MDE_RISEORFALL      (0x2   << 4  ) /* Rising or falling edge   */
#define EI1CFG_IRQ5MDE_HIGHLEVEL       (0x3   << 4  ) /* High level               */
#define EI1CFG_IRQ5MDE_LOWLEVEL        (0x4   << 4  ) /* Low level                */

/* EI1CFG[IRQ4EN] - External Interrupt 4 Enable bit */
#define EI1CFG_IRQ4EN_BBA              (*(volatile unsigned long *) 0x4204848C)
#define EI1CFG_IRQ4EN_MSK              (0x1   << 3  )
#define EI1CFG_IRQ4EN                  (0x1   << 3  )
#define EI1CFG_IRQ4EN_DIS              (0x0   << 3  ) /* External Interrupt 4 disabled */
#define EI1CFG_IRQ4EN_EN               (0x1   << 3  ) /* External Interrupt 4 enabled */

/* EI1CFG[IRQ4MDE] - External Interrupt 4 Mode registers */
#define EI1CFG_IRQ4MDE_MSK             (0x7   << 0  )
#define EI1CFG_IRQ4MDE_RISE            (0x0   << 0  ) /* Rising edge              */
#define EI1CFG_IRQ4MDE_FALL            (0x1   << 0  ) /* Falling edge             */
#define EI1CFG_IRQ4MDE_RISEORFALL      (0x2   << 0  ) /* Rising or falling edge   */
#define EI1CFG_IRQ4MDE_HIGHLEVEL       (0x3   << 0  ) /* High level               */
#define EI1CFG_IRQ4MDE_LOWLEVEL        (0x4   << 0  ) /* Low level                */

/* Reset Value for EI2CFG*/
#define EI2CFG_RVAL                    0x0 

/* EI2CFG[IRQ8EN] - External Interrupt 8 Enable bit */
#define EI2CFG_IRQ8EN_BBA              (*(volatile unsigned long *) 0x4204850C)
#define EI2CFG_IRQ8EN_MSK              (0x1   << 3  )
#define EI2CFG_IRQ8EN                  (0x1   << 3  )
#define EI2CFG_IRQ8EN_DIS              (0x0   << 3  ) /* External Interrupt 8 disabled */
#define EI2CFG_IRQ8EN_EN               (0x1   << 3  ) /* External Interrupt 8 enabled */

/* EI2CFG[IRQ8MDE] - External Interrupt 8 Mode registers */
#define EI2CFG_IRQ8MDE_MSK             (0x7   << 0  )
#define EI2CFG_IRQ8MDE_RISE            (0x0   << 0  ) /* Rising edge              */
#define EI2CFG_IRQ8MDE_FALL            (0x1   << 0  ) /* Falling edge             */
#define EI2CFG_IRQ8MDE_RISEORFALL      (0x2   << 0  ) /* Rising or falling edge   */
#define EI2CFG_IRQ8MDE_HIGHLEVEL       (0x3   << 0  ) /* High level               */
#define EI2CFG_IRQ8MDE_LOWLEVEL        (0x4   << 0  ) /* Low level                */

/* Reset Value for EICLR*/
#define EICLR_RVAL                     0x0 

/* EICLR[IRQ8] - External interrupt 8 */
#define EICLR_IRQ8_BBA                 (*(volatile unsigned long *) 0x42048620)
#define EICLR_IRQ8_MSK                 (0x1   << 8  )
#define EICLR_IRQ8                     (0x1   << 8  )
#define EICLR_IRQ8_DIS                 (0x0   << 8  )
#define EICLR_IRQ8_EN                  (0x1   << 8  )

/* EICLR[IRQ7] - External interrupt 7 */
#define EICLR_IRQ7_BBA                 (*(volatile unsigned long *) 0x4204861C)
#define EICLR_IRQ7_MSK                 (0x1   << 7  )
#define EICLR_IRQ7                     (0x1   << 7  )
#define EICLR_IRQ7_DIS                 (0x0   << 7  )
#define EICLR_IRQ7_EN                  (0x1   << 7  )

/* EICLR[IRQ6] - External interrupt 6 */
#define EICLR_IRQ6_BBA                 (*(volatile unsigned long *) 0x42048618)
#define EICLR_IRQ6_MSK                 (0x1   << 6  )
#define EICLR_IRQ6                     (0x1   << 6  )
#define EICLR_IRQ6_DIS                 (0x0   << 6  )
#define EICLR_IRQ6_EN                  (0x1   << 6  )

/* EICLR[IRQ5] - External interrupt 5 */
#define EICLR_IRQ5_BBA                 (*(volatile unsigned long *) 0x42048614)
#define EICLR_IRQ5_MSK                 (0x1   << 5  )
#define EICLR_IRQ5                     (0x1   << 5  )
#define EICLR_IRQ5_DIS                 (0x0   << 5  )
#define EICLR_IRQ5_EN                  (0x1   << 5  )

/* EICLR[IRQ4] - External interrupt 4 */
#define EICLR_IRQ4_BBA                 (*(volatile unsigned long *) 0x42048610)
#define EICLR_IRQ4_MSK                 (0x1   << 4  )
#define EICLR_IRQ4                     (0x1   << 4  )
#define EICLR_IRQ4_DIS                 (0x0   << 4  )
#define EICLR_IRQ4_EN                  (0x1   << 4  )

/* EICLR[IRQ3] - External interrupt 3 */
#define EICLR_IRQ3_BBA                 (*(volatile unsigned long *) 0x4204860C)
#define EICLR_IRQ3_MSK                 (0x1   << 3  )
#define EICLR_IRQ3                     (0x1   << 3  )
#define EICLR_IRQ3_DIS                 (0x0   << 3  )
#define EICLR_IRQ3_EN                  (0x1   << 3  )

/* EICLR[IRQ2] - External interrupt 2 */
#define EICLR_IRQ2_BBA                 (*(volatile unsigned long *) 0x42048608)
#define EICLR_IRQ2_MSK                 (0x1   << 2  )
#define EICLR_IRQ2                     (0x1   << 2  )
#define EICLR_IRQ2_DIS                 (0x0   << 2  )
#define EICLR_IRQ2_EN                  (0x1   << 2  )

/* EICLR[IRQ1] - External interrupt 1 */
#define EICLR_IRQ1_BBA                 (*(volatile unsigned long *) 0x42048604)
#define EICLR_IRQ1_MSK                 (0x1   << 1  )
#define EICLR_IRQ1                     (0x1   << 1  )
#define EICLR_IRQ1_DIS                 (0x0   << 1  )
#define EICLR_IRQ1_EN                  (0x1   << 1  )

/* EICLR[IRQ0] - External interrupt 0 */
#define EICLR_IRQ0_BBA                 (*(volatile unsigned long *) 0x42048600)
#define EICLR_IRQ0_MSK                 (0x1   << 0  )
#define EICLR_IRQ0                     (0x1   << 0  )
#define EICLR_IRQ0_DIS                 (0x0   << 0  )
#define EICLR_IRQ0_EN                  (0x1   << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        wdt                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief wdt (MMR_WDT)
  */

typedef struct MMR_WDT {                    /*!< MMR_WDT Structure                     */
  __IO uint16_t  T3LD;                      /*!< Load value register                   */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  T3VAL;                     /*!< Current count value register          */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  T3CON;                     /*!< Control register                      */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  T3CLRI;                    /*!< Clear interrupt register              */
  __I  uint16_t  RESERVED3[5];
  __IO uint16_t  T3STA;                     /*!< Status register                       */
} MMR_WDT_t;

/* Reset Value for T3LD*/
#define T3LD_RVAL                      0x1000 

/* T3LD[LOAD] - Load value */
#define T3LD_LOAD_MSK                  (0xFFFF << 0  )

/* Reset Value for T3VAL*/
#define T3VAL_RVAL                     0x1000 

/* T3VAL[CCOUNT] - Current count value */
#define T3VAL_CCOUNT_MSK               (0xFFFF << 0  )

/* Reset Value for T3CON*/
#define T3CON_RVAL                     0xE9 

/* T3CON[MOD] - Timer mode */
#define T3CON_MOD_BBA                  (*(volatile unsigned long *) 0x4204B118)
#define T3CON_MOD_MSK                  (0x1   << 6  )
#define T3CON_MOD                      (0x1   << 6  )
#define T3CON_MOD_FREERUN              (0x0   << 6  ) /* FREERUN. Cleared by user to operate in free running mode. */
#define T3CON_MOD_PERIODIC             (0x1   << 6  ) /* PERIODIC. Set by user to operate in periodic mode (default). */

/* T3CON[ENABLE] - Timer enable */
#define T3CON_ENABLE_BBA               (*(volatile unsigned long *) 0x4204B114)
#define T3CON_ENABLE_MSK               (0x1   << 5  )
#define T3CON_ENABLE                   (0x1   << 5  )
#define T3CON_ENABLE_DIS               (0x0   << 5  ) /* DIS. Cleared by user to disable the timer. */
#define T3CON_ENABLE_EN                (0x1   << 5  ) /* EN. Set by user to enable the timer (default). */

/* T3CON[PRE] - Prescaler */
#define T3CON_PRE_MSK                  (0x3   << 2  )
#define T3CON_PRE_DIV1                 (0x0   << 2  ) /* DIV1.Source clock/1.     */
#define T3CON_PRE_DIV16                (0x1   << 2  ) /* DIV16. Source clock/16.  */
#define T3CON_PRE_DIV256               (0x2   << 2  ) /* DIV256. Source clock/256 (default). */
#define T3CON_PRE_DIV4096              (0x3   << 2  ) /* DIV4096. Source clock/4096 */

/* T3CON[IRQ] - Timer interrupt */
#define T3CON_IRQ_BBA                  (*(volatile unsigned long *) 0x4204B104)
#define T3CON_IRQ_MSK                  (0x1   << 1  )
#define T3CON_IRQ                      (0x1   << 1  )
#define T3CON_IRQ_DIS                  (0x0   << 1  ) /* DIS.Cleared by user to generate a reset on a time out (default). */
#define T3CON_IRQ_EN                   (0x1   << 1  ) /* EN.Set by user to generate an interrupt when the timer times out. This feature is provided for debug purposes and is only available in ACTIVE mode. */

/* T3CON[PMD] - Power Mode Disable */
#define T3CON_PMD_BBA                  (*(volatile unsigned long *) 0x4204B100)
#define T3CON_PMD_MSK                  (0x1   << 0  )
#define T3CON_PMD                      (0x1   << 0  )
#define T3CON_PMD_DIS                  (0x0   << 0  ) /* DIS. The watchdog timer will continue its count down while in hibernate mode. */
#define T3CON_PMD_EN                   (0x1   << 0  ) /* EN. When hibernate mode is entered, the watchdog counter will suspend its count down. As hibernate mode is exited, the count down will resume from its current count value (the count will not be reset). */

/* Reset Value for T3CLRI*/
#define T3CLRI_RVAL                    0x0 

/* T3CLRI[CLRWDG] - Clear watchdog */
#define T3CLRI_CLRWDG_MSK              (0xFFFF << 0  )

/* Reset Value for T3STA*/
#define T3STA_RVAL                     0x0 

/* T3STA[LOCK] - Lock status bit */
#define T3STA_LOCK_BBA                 (*(volatile unsigned long *) 0x4204B310)
#define T3STA_LOCK_MSK                 (0x1   << 4  )
#define T3STA_LOCK                     (0x1   << 4  )
#define T3STA_LOCK_CLR                 (0x0   << 4  )
#define T3STA_LOCK_SET                 (0x1   << 4  )

/* T3STA[CON] - T3CON write sync in progress */
#define T3STA_CON_BBA                  (*(volatile unsigned long *) 0x4204B30C)
#define T3STA_CON_MSK                  (0x1   << 3  )
#define T3STA_CON                      (0x1   << 3  )
#define T3STA_CON_CLR                  (0x0   << 3  ) /* APB and T3 clock domains T3CON configuration values match */
#define T3STA_CON_SET                  (0x1   << 3  ) /* APB T3CON register values are being synchronized to T3 clock domain */

/* T3STA[LD] - T3LD write sync in progress */
#define T3STA_LD_BBA                   (*(volatile unsigned long *) 0x4204B308)
#define T3STA_LD_MSK                   (0x1   << 2  )
#define T3STA_LD                       (0x1   << 2  )
#define T3STA_LD_CLR                   (0x0   << 2  ) /* APB and T3 clock domains T3LD values match */
#define T3STA_LD_SET                   (0x1   << 2  ) /* APB T3LD value is being synchronized to T3 clock domain */

/* T3STA[CLRI] - T3CLRI write sync in progress */
#define T3STA_CLRI_BBA                 (*(volatile unsigned long *) 0x4204B304)
#define T3STA_CLRI_MSK                 (0x1   << 1  )
#define T3STA_CLRI                     (0x1   << 1  )
#define T3STA_CLRI_CLR                 (0x0   << 1  ) /* APB T3CLRI write sync not done/ */
#define T3STA_CLRI_SET                 (0x1   << 1  ) /* APB T3CLRI write is being synced to T3 clock domain. T3 will be restarted (if 0xCCCC was written) once sync is complete */
// ------------------------------------------------------------------------------------------------
// -----                                        wut                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief wut (MMR_WUT)
  */

typedef struct MMR_WUT {                    /*!< MMR_WUT Structure                     */
  __IO uint16_t  T4VAL0;                    /*!< Current count value - LS 16 bits      */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  T4VAL1;                    /*!< Current count value - MS 16 bits      */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  T4CON;                     /*!< Control register                      */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  T4INC;                     /*!< 12-bit interval for wakeup field A    */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  T4WUFB0;                   /*!< Wakeup field B - LS 16 bits           */
  __I  uint16_t  RESERVED4;
  __IO uint16_t  T4WUFB1;                   /*!< Wakeup field B - MS 16 bits           */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  T4WUFC0;                   /*!< Wakeup field C - LS 16 bits           */
  __I  uint16_t  RESERVED6;
  __IO uint16_t  T4WUFC1;                   /*!< Wakeup field C - MS 16 bits           */
  __I  uint16_t  RESERVED7;
  __IO uint16_t  T4WUFD0;                   /*!< Wakeup field D - LS 16 bits           */
  __I  uint16_t  RESERVED8;
  __IO uint16_t  T4WUFD1;                   /*!< Wakeup field D - MS 16 bits           */
  __I  uint16_t  RESERVED9;
  __IO uint16_t  T4IEN;                     /*!< Interrupt enable register             */
  __I  uint16_t  RESERVED10;
  __IO uint16_t  T4STA;                     /*!< Status register                       */
  __I  uint16_t  RESERVED11;
  __IO uint16_t  T4CLRI;                    /*!< Clear interrupt register              */
  __I  uint16_t  RESERVED12[5];
  __IO uint16_t  T4WUFA0;                   /*!< Wakeup field A - LS 16 bits           */
  __I  uint16_t  RESERVED13;
  __IO uint16_t  T4WUFA1;                   /*!< Wakeup field A - MS 16 bits           */
} MMR_WUT_t;

/* Reset Value for T4VAL0*/
#define T4VAL0_RVAL                    0x0 

/* T4VAL0[T4VALL] - Current count Low */
#define T4VAL0_T4VALL_MSK              (0xFFFF << 0  )

/* Reset Value for T4VAL1*/
#define T4VAL1_RVAL                    0x0 

/* T4VAL1[T4VALH] - Current count high */
#define T4VAL1_T4VALH_MSK              (0xFFFF << 0  )

/* Reset Value for T4CON*/
#define T4CON_RVAL                     0x40 

/* T4CON[STOP_WUFA] - Disables updating field A register T4WUFA */
#define T4CON_STOP_WUFA_BBA            (*(volatile unsigned long *) 0x4204A12C)
#define T4CON_STOP_WUFA_MSK            (0x1   << 11 )
#define T4CON_STOP_WUFA                (0x1   << 11 )
#define T4CON_STOP_WUFA_DIS            (0x0   << 11 )
#define T4CON_STOP_WUFA_EN             (0x1   << 11 )

/* T4CON[CLK] - Clock select */
#define T4CON_CLK_MSK                  (0x3   << 9  )
#define T4CON_CLK_PCLK                 (0x0   << 9  ) /* PCLK: PCLK (default)     */
#define T4CON_CLK_LFOSC                (0x1   << 9  ) /* LFOSC: 32 kHz internal oscillator */
#define T4CON_CLK_ECLKIN               (0x3   << 9  ) /* ECLKIN: External clock from P1.0 */

/* T4CON[WUEN] - Wakeup enable */
#define T4CON_WUEN_BBA                 (*(volatile unsigned long *) 0x4204A120)
#define T4CON_WUEN_MSK                 (0x1   << 8  )
#define T4CON_WUEN                     (0x1   << 8  )
#define T4CON_WUEN_DIS                 (0x0   << 8  ) /* DIS: Cleared by user to disable the wake up timer when the core clock is off */
#define T4CON_WUEN_EN                  (0x1   << 8  ) /* EN: Set by user to enable the wake up timer even when the core clock is off. */

/* T4CON[ENABLE] - Timer enable */
#define T4CON_ENABLE_BBA               (*(volatile unsigned long *) 0x4204A11C)
#define T4CON_ENABLE_MSK               (0x1   << 7  )
#define T4CON_ENABLE                   (0x1   << 7  )
#define T4CON_ENABLE_DIS               (0x0   << 7  ) /* DIS: Disable the timer (default). */
#define T4CON_ENABLE_EN                (0x1   << 7  ) /* EN: Enable the timer.    */

/* T4CON[MOD] - Timer mode */
#define T4CON_MOD_BBA                  (*(volatile unsigned long *) 0x4204A118)
#define T4CON_MOD_MSK                  (0x1   << 6  )
#define T4CON_MOD                      (0x1   << 6  )
#define T4CON_MOD_PERIODIC             (0x0   << 6  ) /* PERIODIC: Cleared by user to operate in periodic mode. In this mode, the timer counts up to T4WUFD */
#define T4CON_MOD_FREERUN              (0x1   << 6  ) /* FREERUN: Set by user to operate in free running mode (default). */

/* T4CON[FREEZE] - Freeze enable */
#define T4CON_FREEZE_BBA               (*(volatile unsigned long *) 0x4204A10C)
#define T4CON_FREEZE_MSK               (0x1   << 3  )
#define T4CON_FREEZE                   (0x1   << 3  )
#define T4CON_FREEZE_DIS               (0x0   << 3  ) /* DIS: Cleared by user to disable this feature (default). */
#define T4CON_FREEZE_EN                (0x1   << 3  ) /* EN: Set by user to enable the freeze of the high 16-bits after the lower bits have been read from T4VAL0. This ensures that the software will read an atomic shot of the timer. T4VAL1 unfreezes after it has been read. */

/* T4CON[PRE] - Prescaler */
#define T4CON_PRE_MSK                  (0x3   << 0  )
#define T4CON_PRE_PREDIV1              (0x0   << 0  ) /* PREDIV1: source clock/1 (default). If the selected clock source is PCLK, then this setting results in a prescaler of 4. */
#define T4CON_PRE_PREDIV16             (0x1   << 0  ) /* PREDIV16: source clock/16 */
#define T4CON_PRE_PREDIV256            (0x2   << 0  ) /* PREDIV256: source clock/256 */
#define T4CON_PRE_PREDIV32768          (0x3   << 0  ) /* PREDIV32768: source clock/32,768 */

/* Reset Value for T4INC*/
#define T4INC_RVAL                     0xC8 

/* T4INC[INTERVAL] - Interval for wakeup field A */
#define T4INC_INTERVAL_MSK             (0xFFF << 0  )

/* Reset Value for T4WUFB0*/
#define T4WUFB0_RVAL                   0x1FFF 

/* T4WUFB0[T4WUFBL] - Wakeup field B low */
#define T4WUFB0_T4WUFBL_MSK            (0xFFFF << 0  )

/* Reset Value for T4WUFB1*/
#define T4WUFB1_RVAL                   0x0 

/* T4WUFB1[T4WUFBH] - Wakeup field B High */
#define T4WUFB1_T4WUFBH_MSK            (0xFFFF << 0  )

/* Reset Value for T4WUFC0*/
#define T4WUFC0_RVAL                   0x2FFF 

/* T4WUFC0[T4WUFCL] - Wakeup field C Low */
#define T4WUFC0_T4WUFCL_MSK            (0xFFFF << 0  )

/* Reset Value for T4WUFC1*/
#define T4WUFC1_RVAL                   0x0 

/* T4WUFC1[T4WUFCH] - Wakeup field C High */
#define T4WUFC1_T4WUFCH_MSK            (0xFFFF << 0  )

/* Reset Value for T4WUFD0*/
#define T4WUFD0_RVAL                   0x3FFF 

/* T4WUFD0[T4WUFD0] - Wakeup field D Low */
#define T4WUFD0_T4WUFD0_MSK            (0xFFFF << 0  )

/* Reset Value for T4WUFD1*/
#define T4WUFD1_RVAL                   0x0 

/* T4WUFD1[T4WUFDH] - Wakeup field D high */
#define T4WUFD1_T4WUFDH_MSK            (0xFFFF << 0  )

/* Reset Value for T4IEN*/
#define T4IEN_RVAL                     0x0 

/* T4IEN[ROLL] - Rollover interrupt enable */
#define T4IEN_ROLL_BBA                 (*(volatile unsigned long *) 0x4204A510)
#define T4IEN_ROLL_MSK                 (0x1   << 4  )
#define T4IEN_ROLL                     (0x1   << 4  )
#define T4IEN_ROLL_DIS                 (0x0   << 4  )
#define T4IEN_ROLL_EN                  (0x1   << 4  )

/* T4IEN[WUFD] - T4WUFD interrupt enable */
#define T4IEN_WUFD_BBA                 (*(volatile unsigned long *) 0x4204A50C)
#define T4IEN_WUFD_MSK                 (0x1   << 3  )
#define T4IEN_WUFD                     (0x1   << 3  )
#define T4IEN_WUFD_DIS                 (0x0   << 3  )
#define T4IEN_WUFD_EN                  (0x1   << 3  )

/* T4IEN[WUFC] - T4WUFC interrupt enable */
#define T4IEN_WUFC_BBA                 (*(volatile unsigned long *) 0x4204A508)
#define T4IEN_WUFC_MSK                 (0x1   << 2  )
#define T4IEN_WUFC                     (0x1   << 2  )
#define T4IEN_WUFC_DIS                 (0x0   << 2  )
#define T4IEN_WUFC_EN                  (0x1   << 2  )

/* T4IEN[WUFB] - T4WUFB interrupt enable */
#define T4IEN_WUFB_BBA                 (*(volatile unsigned long *) 0x4204A504)
#define T4IEN_WUFB_MSK                 (0x1   << 1  )
#define T4IEN_WUFB                     (0x1   << 1  )
#define T4IEN_WUFB_DIS                 (0x0   << 1  )
#define T4IEN_WUFB_EN                  (0x1   << 1  )

/* T4IEN[WUFA] - T4WUFA interrupt enable */
#define T4IEN_WUFA_BBA                 (*(volatile unsigned long *) 0x4204A500)
#define T4IEN_WUFA_MSK                 (0x1   << 0  )
#define T4IEN_WUFA                     (0x1   << 0  )
#define T4IEN_WUFA_DIS                 (0x0   << 0  )
#define T4IEN_WUFA_EN                  (0x1   << 0  )

/* Reset Value for T4STA*/
#define T4STA_RVAL                     0x0 

/* T4STA[PDOK] - Enable bit synchronized */
#define T4STA_PDOK_BBA                 (*(volatile unsigned long *) 0x4204A5A0)
#define T4STA_PDOK_MSK                 (0x1   << 8  )
#define T4STA_PDOK                     (0x1   << 8  )
#define T4STA_PDOK_CLR                 (0x0   << 8  )
#define T4STA_PDOK_SET                 (0x1   << 8  )

/* T4STA[FREEZE] - Timer value freeze */
#define T4STA_FREEZE_BBA               (*(volatile unsigned long *) 0x4204A59C)
#define T4STA_FREEZE_MSK               (0x1   << 7  )
#define T4STA_FREEZE                   (0x1   << 7  )
#define T4STA_FREEZE_CLR               (0x0   << 7  )
#define T4STA_FREEZE_SET               (0x1   << 7  )

/* T4STA[IRQCRY] - Wakeup status to powerdown */
#define T4STA_IRQCRY_BBA               (*(volatile unsigned long *) 0x4204A598)
#define T4STA_IRQCRY_MSK               (0x1   << 6  )
#define T4STA_IRQCRY                   (0x1   << 6  )
#define T4STA_IRQCRY_CLR               (0x0   << 6  )
#define T4STA_IRQCRY_SET               (0x1   << 6  )

/* T4STA[ROLL] - Rollover interrupt flag */
#define T4STA_ROLL_BBA                 (*(volatile unsigned long *) 0x4204A590)
#define T4STA_ROLL_MSK                 (0x1   << 4  )
#define T4STA_ROLL                     (0x1   << 4  )
#define T4STA_ROLL_CLR                 (0x0   << 4  )
#define T4STA_ROLL_SET                 (0x1   << 4  )

/* T4STA[WUFD] - T4WUFD interrupt flag */
#define T4STA_WUFD_BBA                 (*(volatile unsigned long *) 0x4204A58C)
#define T4STA_WUFD_MSK                 (0x1   << 3  )
#define T4STA_WUFD                     (0x1   << 3  )
#define T4STA_WUFD_CLR                 (0x0   << 3  )
#define T4STA_WUFD_SET                 (0x1   << 3  )

/* T4STA[WUFC] - T4WUFC interrupt flag */
#define T4STA_WUFC_BBA                 (*(volatile unsigned long *) 0x4204A588)
#define T4STA_WUFC_MSK                 (0x1   << 2  )
#define T4STA_WUFC                     (0x1   << 2  )
#define T4STA_WUFC_CLR                 (0x0   << 2  )
#define T4STA_WUFC_SET                 (0x1   << 2  )

/* T4STA[WUFB] - T4WUFB interrupt flag */
#define T4STA_WUFB_BBA                 (*(volatile unsigned long *) 0x4204A584)
#define T4STA_WUFB_MSK                 (0x1   << 1  )
#define T4STA_WUFB                     (0x1   << 1  )
#define T4STA_WUFB_CLR                 (0x0   << 1  )
#define T4STA_WUFB_SET                 (0x1   << 1  )

/* T4STA[WUFA] - T4WUFA interrupt flag */
#define T4STA_WUFA_BBA                 (*(volatile unsigned long *) 0x4204A580)
#define T4STA_WUFA_MSK                 (0x1   << 0  )
#define T4STA_WUFA                     (0x1   << 0  )
#define T4STA_WUFA_CLR                 (0x0   << 0  )
#define T4STA_WUFA_SET                 (0x1   << 0  )

/* Reset Value for T4CLRI*/
#define T4CLRI_RVAL                    0x0 

/* T4CLRI[ROLL] - Rollover interrupt clear */
#define T4CLRI_ROLL_BBA                (*(volatile unsigned long *) 0x4204A610)
#define T4CLRI_ROLL_MSK                (0x1   << 4  )
#define T4CLRI_ROLL                    (0x1   << 4  )
#define T4CLRI_ROLL_DIS                (0x0   << 4  )
#define T4CLRI_ROLL_EN                 (0x1   << 4  )

/* T4CLRI[WUFD] - T4WUFD interrupt clear */
#define T4CLRI_WUFD_BBA                (*(volatile unsigned long *) 0x4204A60C)
#define T4CLRI_WUFD_MSK                (0x1   << 3  )
#define T4CLRI_WUFD                    (0x1   << 3  )
#define T4CLRI_WUFD_DIS                (0x0   << 3  )
#define T4CLRI_WUFD_EN                 (0x1   << 3  )

/* T4CLRI[WUFC] - T4WUFC interrupt clear */
#define T4CLRI_WUFC_BBA                (*(volatile unsigned long *) 0x4204A608)
#define T4CLRI_WUFC_MSK                (0x1   << 2  )
#define T4CLRI_WUFC                    (0x1   << 2  )
#define T4CLRI_WUFC_DIS                (0x0   << 2  )
#define T4CLRI_WUFC_EN                 (0x1   << 2  )

/* T4CLRI[WUFB] - T4WUFB interrupt clear */
#define T4CLRI_WUFB_BBA                (*(volatile unsigned long *) 0x4204A604)
#define T4CLRI_WUFB_MSK                (0x1   << 1  )
#define T4CLRI_WUFB                    (0x1   << 1  )
#define T4CLRI_WUFB_DIS                (0x0   << 1  )
#define T4CLRI_WUFB_EN                 (0x1   << 1  )

/* T4CLRI[WUFA] - T4WUFA interrupt clear */
#define T4CLRI_WUFA_BBA                (*(volatile unsigned long *) 0x4204A600)
#define T4CLRI_WUFA_MSK                (0x1   << 0  )
#define T4CLRI_WUFA                    (0x1   << 0  )
#define T4CLRI_WUFA_DIS                (0x0   << 0  )
#define T4CLRI_WUFA_EN                 (0x1   << 0  )

/* Reset Value for T4WUFA0*/
#define T4WUFA0_RVAL                   0x1900 

/* T4WUFA0[T4WUFAL] - Wakeup field A Low */
#define T4WUFA0_T4WUFAL_MSK            (0xFFFF << 0  )

/* Reset Value for T4WUFA1*/
#define T4WUFA1_RVAL                   0x0 

/* T4WUFA1[T4WUFAH] - Wakeup field A High */
#define T4WUFA1_T4WUFAH_MSK            (0xFFFF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        I2C                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief i2cms (MMR_I2C0)
  */

typedef struct MMR_I2C {                    /*!< MMR_I2C0 Structure                    */
  __IO uint16_t  I2CMCON;                   /*!< Master control register               */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  I2CMSTA;                   /*!< Master status register                */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  I2CMRX;                    /*!< Master receive data register          */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  I2CMTX;                    /*!< Master transmit data register         */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  I2CMRXCNT;                 /*!< Master receive data count register    */
  __I  uint16_t  RESERVED4;
  __IO uint16_t  I2CMCRXCNT;                /*!< Master current receive data count register */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  I2CADR0;                   /*!< 1st master address byte register      */
  __I  uint16_t  RESERVED6;
  __IO uint16_t  I2CADR1;                   /*!< 2nd master address byte register      */
  __I  uint16_t  RESERVED7[3];
  __IO uint16_t  I2CDIV;                    /*!< Serial clock period divisor register  */
  __I  uint16_t  RESERVED8;
  __IO uint16_t  I2CSCON;                   /*!< Slave control register                */
  __I  uint16_t  RESERVED9;
  __IO uint16_t  I2CSSTA;                   /*!< Slave I2C Status/Error/IRQ register   */
  __I  uint16_t  RESERVED10;
  __IO uint16_t  I2CSRX;                    /*!< Slave receive register                */
  __I  uint16_t  RESERVED11;
  __IO uint16_t  I2CSTX;                    /*!< Slave transmit register               */
  __I  uint16_t  RESERVED12;
  __IO uint16_t  I2CALT;                    /*!< Hardware general call ID register     */
  __I  uint16_t  RESERVED13;
  __IO uint16_t  I2CID0;                    /*!< 1st slave address device ID register  */
  __I  uint16_t  RESERVED14;
  __IO uint16_t  I2CID1;                    /*!< 2nd slave address device ID register  */
  __I  uint16_t  RESERVED15;
  __IO uint16_t  I2CID2;                    /*!< 3rd slave address device ID register  */
  __I  uint16_t  RESERVED16;
  __IO uint16_t  I2CID3;                    /*!< 4th slave address device ID register  */
  __I  uint16_t  RESERVED17;
  __IO uint16_t  I2CFSTA;                   /*!< Master and slave FIFO status register */
  __I  uint16_t  RESERVED18;
  __IO uint16_t  I2CSHCON;                  /*!< Shared control register               */
  __I  uint16_t  RESERVED19;
#if defined(ADUCM320I) | defined(ADUCM322) | defined(ADUCM322I)
  __I  uint32_t  RESERVED20;
  __IO uint16_t  I2CASSCL;                  /*!< Automatic Stretch control register    */
  __I  uint16_t  RESERVED21;
#endif
} MMR_I2C_t;

/* Reset Value for I2C0MCON*/
#define I2C0MCON_RVAL                  0x0 

/* I2C0MCON[PRESTOP_BUS_CLR] - Prestop Bus-Clear */
#define I2C0MCON_PRESTOP_BUS_CLR_BBA   (*(volatile unsigned long *) 0x42060034)
#define I2C0MCON_PRESTOP_BUS_CLR_MSK   (0x1   << 13 )
#define I2C0MCON_PRESTOP_BUS_CLR       (0x1   << 13 )
#define I2C0MCON_PRESTOP_BUS_CLR_DIS   (0x0   << 13 )
#define I2C0MCON_PRESTOP_BUS_CLR_EN    (0x1   << 13 )

/* I2C0MCON[BUS_CLR_EN] - Bus-Clear Enable */
#define I2C0MCON_BUS_CLR_EN_BBA        (*(volatile unsigned long *) 0x42060030)
#define I2C0MCON_BUS_CLR_EN_MSK        (0x1   << 12 )
#define I2C0MCON_BUS_CLR_EN            (0x1   << 12 )
#define I2C0MCON_BUS_CLR_EN_DIS        (0x0   << 12 )
#define I2C0MCON_BUS_CLR_EN_EN         (0x1   << 12 )

/* I2C0MCON[MTXDMA] - Enable master Tx DMA request */
#define I2C0MCON_MTXDMA_BBA            (*(volatile unsigned long *) 0x4206002C)
#define I2C0MCON_MTXDMA_MSK            (0x1   << 11 )
#define I2C0MCON_MTXDMA                (0x1   << 11 )
#define I2C0MCON_MTXDMA_DIS            (0x0   << 11 ) /* Disable DMA mode         */
#define I2C0MCON_MTXDMA_EN             (0x1   << 11 ) /* Enable I2C master DMA Tx requests. */

/* I2C0MCON[MRXDMA] - Enable master Rx DMA request */
#define I2C0MCON_MRXDMA_BBA            (*(volatile unsigned long *) 0x42060028)
#define I2C0MCON_MRXDMA_MSK            (0x1   << 10 )
#define I2C0MCON_MRXDMA                (0x1   << 10 )
#define I2C0MCON_MRXDMA_DIS            (0x0   << 10 ) /* Disable DMA mode         */
#define I2C0MCON_MRXDMA_EN             (0x1   << 10 ) /* Enable I2C master DMA Rx requests. */

/* I2C0MCON[MXMITDEC] - Decrement master TX FIFO status when a byte has been transmitted */
#define I2C0MCON_MXMITDEC_BBA          (*(volatile unsigned long *) 0x42060024)
#define I2C0MCON_MXMITDEC_MSK          (0x1   << 9  )
#define I2C0MCON_MXMITDEC              (0x1   << 9  )
#define I2C0MCON_MXMITDEC_DIS          (0x0   << 9  )
#define I2C0MCON_MXMITDEC_EN           (0x1   << 9  )

/* I2C0MCON[IENCMP] - Transaction completed (or stop detected) interrupt enable */
#define I2C0MCON_IENCMP_BBA            (*(volatile unsigned long *) 0x42060020)
#define I2C0MCON_IENCMP_MSK            (0x1   << 8  )
#define I2C0MCON_IENCMP                (0x1   << 8  )
#define I2C0MCON_IENCMP_DIS            (0x0   << 8  ) /* An interrupt is not generated when a STOP is detected. */
#define I2C0MCON_IENCMP_EN             (0x1   << 8  ) /* An interrupt is generated when a STOP is detected. */

/* I2C0MCON[IENACK] - ACK not received interrupt enable */
#define I2C0MCON_IENACK_BBA            (*(volatile unsigned long *) 0x4206001C)
#define I2C0MCON_IENACK_MSK            (0x1   << 7  )
#define I2C0MCON_IENACK                (0x1   << 7  )
#define I2C0MCON_IENACK_DIS            (0x0   << 7  ) /* ACK not received interrupt disable */
#define I2C0MCON_IENACK_EN             (0x1   << 7  ) /* ACK not received interrupt enable */

/* I2C0MCON[IENALOST] - Arbitration lost interrupt enable */
#define I2C0MCON_IENALOST_BBA          (*(volatile unsigned long *) 0x42060018)
#define I2C0MCON_IENALOST_MSK          (0x1   << 6  )
#define I2C0MCON_IENALOST              (0x1   << 6  )
#define I2C0MCON_IENALOST_DIS          (0x0   << 6  ) /* Arbitration lost interrupt disable */
#define I2C0MCON_IENALOST_EN           (0x1   << 6  ) /* Arbitration lost interrupt enable */

/* I2C0MCON[IENMTX] - Transmit request interrupt enable */
#define I2C0MCON_IENMTX_BBA            (*(volatile unsigned long *) 0x42060014)
#define I2C0MCON_IENMTX_MSK            (0x1   << 5  )
#define I2C0MCON_IENMTX                (0x1   << 5  )
#define I2C0MCON_IENMTX_DIS            (0x0   << 5  ) /* Transmit request interrupt disable */
#define I2C0MCON_IENMTX_EN             (0x1   << 5  ) /* Transmit request interrupt enable */

/* I2C0MCON[IENMRX] - Receive request interrupt enable */
#define I2C0MCON_IENMRX_BBA            (*(volatile unsigned long *) 0x42060010)
#define I2C0MCON_IENMRX_MSK            (0x1   << 4  )
#define I2C0MCON_IENMRX                (0x1   << 4  )
#define I2C0MCON_IENMRX_DIS            (0x0   << 4  ) /* Receive request interrupt disable */
#define I2C0MCON_IENMRX_EN             (0x1   << 4  ) /* Receive request interrupt enable */

/* I2C0MCON[STRETCH] - Stretch SCL enable */
#define I2C0MCON_STRETCH_BBA           (*(volatile unsigned long *) 0x4206000C)
#define I2C0MCON_STRETCH_MSK           (0x1   << 3  )
#define I2C0MCON_STRETCH               (0x1   << 3  )
#define I2C0MCON_STRETCH_DIS           (0x0   << 3  ) /* Disable Clock stretching */
#define I2C0MCON_STRETCH_EN            (0x1   << 3  ) /* Setting this bit tells the device if SCL is 0 hold it at 0;. Or if SCL is 1 then when it next goes to 0 hold it at 0. */

/* I2C0MCON[LOOPBACK] - Internal loopback enable */
#define I2C0MCON_LOOPBACK_BBA          (*(volatile unsigned long *) 0x42060008)
#define I2C0MCON_LOOPBACK_MSK          (0x1   << 2  )
#define I2C0MCON_LOOPBACK              (0x1   << 2  )
#define I2C0MCON_LOOPBACK_DIS          (0x0   << 2  ) /* SCL and SDA out of the device are not muxed onto their corresponding inputs. */
#define I2C0MCON_LOOPBACK_EN           (0x1   << 2  ) /* SCL and SDA out of the device are muxed onto their corresponding inputs. */

/* I2C0MCON[COMPETE] - Start back-off disable */
#define I2C0MCON_COMPETE_BBA           (*(volatile unsigned long *) 0x42060004)
#define I2C0MCON_COMPETE_MSK           (0x1   << 1  )
#define I2C0MCON_COMPETE               (0x1   << 1  )
#define I2C0MCON_COMPETE_DIS           (0x0   << 1  )
#define I2C0MCON_COMPETE_EN            (0x1   << 1  )

/* I2C0MCON[MASEN] - Master enable */
#define I2C0MCON_MASEN_BBA             (*(volatile unsigned long *) 0x42060000)
#define I2C0MCON_MASEN_MSK             (0x1   << 0  )
#define I2C0MCON_MASEN                 (0x1   << 0  )
#define I2C0MCON_MASEN_DIS             (0x0   << 0  ) /* Master is disabled       */
#define I2C0MCON_MASEN_EN              (0x1   << 0  ) /* Master is enabled        */

/* Reset Value for I2C0MSTA*/
#define I2C0MSTA_RVAL                  0x6000 

/* I2C0MSTA[SCL_FILTERED] - State of SCL Line */
#define I2C0MSTA_SCL_FILTERED_BBA      (*(volatile unsigned long *) 0x420600B8)
#define I2C0MSTA_SCL_FILTERED_MSK      (0x1   << 14 )
#define I2C0MSTA_SCL_FILTERED          (0x1   << 14 )
#define I2C0MSTA_SCL_FILTERED_CLR      (0x0   << 14 )
#define I2C0MSTA_SCL_FILTERED_SET      (0x1   << 14 )

/* I2C0MSTA[SDA_FILTERED] - State of SDA Line */
#define I2C0MSTA_SDA_FILTERED_BBA      (*(volatile unsigned long *) 0x420600B4)
#define I2C0MSTA_SDA_FILTERED_MSK      (0x1   << 13 )
#define I2C0MSTA_SDA_FILTERED          (0x1   << 13 )
#define I2C0MSTA_SDA_FILTERED_CLR      (0x0   << 13 )
#define I2C0MSTA_SDA_FILTERED_SET      (0x1   << 13 )

/* I2C0MSTA[MTXUFLOW] - Master Transmit Underflow */
#define I2C0MSTA_MTXUFLOW_BBA          (*(volatile unsigned long *) 0x420600B0)
#define I2C0MSTA_MTXUFLOW_MSK          (0x1   << 12 )
#define I2C0MSTA_MTXUFLOW              (0x1   << 12 )
#define I2C0MSTA_MTXUFLOW_CLR          (0x0   << 12 )
#define I2C0MSTA_MTXUFLOW_SET          (0x1   << 12 )

/* I2C0MSTA[MSTOP] - STOP driven by this I2C Master */
#define I2C0MSTA_MSTOP_BBA             (*(volatile unsigned long *) 0x420600AC)
#define I2C0MSTA_MSTOP_MSK             (0x1   << 11 )
#define I2C0MSTA_MSTOP                 (0x1   << 11 )
#define I2C0MSTA_MSTOP_CLR             (0x0   << 11 )
#define I2C0MSTA_MSTOP_SET             (0x1   << 11 )

/* I2C0MSTA[LINEBUSY] - Line is busy */
#define I2C0MSTA_LINEBUSY_BBA          (*(volatile unsigned long *) 0x420600A8)
#define I2C0MSTA_LINEBUSY_MSK          (0x1   << 10 )
#define I2C0MSTA_LINEBUSY              (0x1   << 10 )
#define I2C0MSTA_LINEBUSY_CLR          (0x0   << 10 )
#define I2C0MSTA_LINEBUSY_SET          (0x1   << 10 )

/* I2C0MSTA[MRXOF] - Master Receive FIFO overflow */
#define I2C0MSTA_MRXOF_BBA             (*(volatile unsigned long *) 0x420600A4)
#define I2C0MSTA_MRXOF_MSK             (0x1   << 9  )
#define I2C0MSTA_MRXOF                 (0x1   << 9  )
#define I2C0MSTA_MRXOF_CLR             (0x0   << 9  )
#define I2C0MSTA_MRXOF_SET             (0x1   << 9  )

/* I2C0MSTA[TCOMP] - Transaction complete or stop detected */
#define I2C0MSTA_TCOMP_BBA             (*(volatile unsigned long *) 0x420600A0)
#define I2C0MSTA_TCOMP_MSK             (0x1   << 8  )
#define I2C0MSTA_TCOMP                 (0x1   << 8  )
#define I2C0MSTA_TCOMP_CLR             (0x0   << 8  )
#define I2C0MSTA_TCOMP_SET             (0x1   << 8  )

/* I2C0MSTA[NACKDATA] - ACK not received in response to data write */
#define I2C0MSTA_NACKDATA_BBA          (*(volatile unsigned long *) 0x4206009C)
#define I2C0MSTA_NACKDATA_MSK          (0x1   << 7  )
#define I2C0MSTA_NACKDATA              (0x1   << 7  )
#define I2C0MSTA_NACKDATA_CLR          (0x0   << 7  )
#define I2C0MSTA_NACKDATA_SET          (0x1   << 7  )

/* I2C0MSTA[MBUSY] - Master busy */
#define I2C0MSTA_MBUSY_BBA             (*(volatile unsigned long *) 0x42060098)
#define I2C0MSTA_MBUSY_MSK             (0x1   << 6  )
#define I2C0MSTA_MBUSY                 (0x1   << 6  )
#define I2C0MSTA_MBUSY_CLR             (0x0   << 6  )
#define I2C0MSTA_MBUSY_SET             (0x1   << 6  )

/* I2C0MSTA[ALOST] - Arbitration lost */
#define I2C0MSTA_ALOST_BBA             (*(volatile unsigned long *) 0x42060094)
#define I2C0MSTA_ALOST_MSK             (0x1   << 5  )
#define I2C0MSTA_ALOST                 (0x1   << 5  )
#define I2C0MSTA_ALOST_CLR             (0x0   << 5  )
#define I2C0MSTA_ALOST_SET             (0x1   << 5  )

/* I2C0MSTA[NACKADDR] - ACK not received in response to an address */
#define I2C0MSTA_NACKADDR_BBA          (*(volatile unsigned long *) 0x42060090)
#define I2C0MSTA_NACKADDR_MSK          (0x1   << 4  )
#define I2C0MSTA_NACKADDR              (0x1   << 4  )
#define I2C0MSTA_NACKADDR_CLR          (0x0   << 4  )
#define I2C0MSTA_NACKADDR_SET          (0x1   << 4  )

/* I2C0MSTA[MRXREQ] - Master Receive request */
#define I2C0MSTA_MRXREQ_BBA            (*(volatile unsigned long *) 0x4206008C)
#define I2C0MSTA_MRXREQ_MSK            (0x1   << 3  )
#define I2C0MSTA_MRXREQ                (0x1   << 3  )
#define I2C0MSTA_MRXREQ_CLR            (0x0   << 3  )
#define I2C0MSTA_MRXREQ_SET            (0x1   << 3  )

/* I2C0MSTA[MTXREQ] - Master Transmit request */
#define I2C0MSTA_MTXREQ_BBA            (*(volatile unsigned long *) 0x42060088)
#define I2C0MSTA_MTXREQ_MSK            (0x1   << 2  )
#define I2C0MSTA_MTXREQ                (0x1   << 2  )
#define I2C0MSTA_MTXREQ_CLR            (0x0   << 2  )
#define I2C0MSTA_MTXREQ_SET            (0x1   << 2  )

/* I2C0MSTA[MTXFSTA] - Master Transmit FIFO status */
#define I2C0MSTA_MTXFSTA_MSK           (0x3   << 0  )

/* Reset Value for I2C0MRX*/
#define I2C0MRX_RVAL                   0x0 

/* I2C0MRX[ICMRX] - Master receive register */
#define I2C0MRX_ICMRX_MSK              (0xFF  << 0  )

/* Reset Value for I2C0MTX*/
#define I2C0MTX_RVAL                   0x0 

/* I2C0MTX[I2CMTX] - Master transmit register */
#define I2C0MTX_I2CMTX_MSK             (0xFF  << 0  )

/* Reset Value for I2C0MRXCNT*/
#define I2C0MRXCNT_RVAL                0x0 

/* I2C0MRXCNT[EXTEND] - Extended read */
#define I2C0MRXCNT_EXTEND_BBA          (*(volatile unsigned long *) 0x42060220)
#define I2C0MRXCNT_EXTEND_MSK          (0x1   << 8  )
#define I2C0MRXCNT_EXTEND              (0x1   << 8  )
#define I2C0MRXCNT_EXTEND_DIS          (0x0   << 8  )
#define I2C0MRXCNT_EXTEND_EN           (0x1   << 8  )

/* I2C0MRXCNT[COUNT] - Receive count */
#define I2C0MRXCNT_COUNT_MSK           (0xFF  << 0  )

/* Reset Value for I2C0MCRXCNT*/
#define I2C0MCRXCNT_RVAL               0x0 

/* I2C0MCRXCNT[COUNT] - Current receive count */
#define I2C0MCRXCNT_COUNT_MSK          (0xFF  << 0  )

/* Reset Value for I2C0ADR0*/
#define I2C0ADR0_RVAL                  0x0 

/* I2C0ADR0[ADR0] - Address byte 0 */
#define I2C0ADR0_ADR0_MSK              (0xFF  << 0  )

/* Reset Value for I2C0ADR1*/
#define I2C0ADR1_RVAL                  0x0 

/* I2C0ADR1[ADR1] - Address byte 1 */
#define I2C0ADR1_ADR1_MSK              (0xFF  << 0  )

/* Reset Value for I2C0DIV*/
#define I2C0DIV_RVAL                   0x1F1F 

/* I2C0DIV[HIGH] - Serial clock high time */
#define I2C0DIV_HIGH_MSK               (0xFF  << 8  )

/* I2C0DIV[LOW] - Serial clock low time */
#define I2C0DIV_LOW_MSK                (0xFF  << 0  )

/* Reset Value for I2C0SCON*/
#define I2C0SCON_RVAL                  0x0 

/* I2C0SCON[STXDMA] - Enable slave Tx DMA request */
#define I2C0SCON_STXDMA_BBA            (*(volatile unsigned long *) 0x42060538)
#define I2C0SCON_STXDMA_MSK            (0x1   << 14 )
#define I2C0SCON_STXDMA                (0x1   << 14 )
#define I2C0SCON_STXDMA_DIS            (0x0   << 14 )
#define I2C0SCON_STXDMA_EN             (0x1   << 14 )

/* I2C0SCON[SRXDMA] - Enable slave Rx DMA request */
#define I2C0SCON_SRXDMA_BBA            (*(volatile unsigned long *) 0x42060534)
#define I2C0SCON_SRXDMA_MSK            (0x1   << 13 )
#define I2C0SCON_SRXDMA                (0x1   << 13 )
#define I2C0SCON_SRXDMA_DIS            (0x0   << 13 )
#define I2C0SCON_SRXDMA_EN             (0x1   << 13 )

/* I2C0SCON[IENREPST] - Repeated start interrupt enable */
#define I2C0SCON_IENREPST_BBA          (*(volatile unsigned long *) 0x42060530)
#define I2C0SCON_IENREPST_MSK          (0x1   << 12 )
#define I2C0SCON_IENREPST              (0x1   << 12 )
#define I2C0SCON_IENREPST_DIS          (0x0   << 12 )
#define I2C0SCON_IENREPST_EN           (0x1   << 12 )

/* I2C0SCON[SXMITDEC] - Decrement Slave Tx FIFO status when a byte has been transmitted */
#define I2C0SCON_SXMITDEC_BBA          (*(volatile unsigned long *) 0x4206052C)
#define I2C0SCON_SXMITDEC_MSK          (0x1   << 11 )
#define I2C0SCON_SXMITDEC              (0x1   << 11 )
#define I2C0SCON_SXMITDEC_DIS          (0x0   << 11 )
#define I2C0SCON_SXMITDEC_EN           (0x1   << 11 )

/* I2C0SCON[IENSTX] - Slave Transmit request interrupt enable */
#define I2C0SCON_IENSTX_BBA            (*(volatile unsigned long *) 0x42060528)
#define I2C0SCON_IENSTX_MSK            (0x1   << 10 )
#define I2C0SCON_IENSTX                (0x1   << 10 )
#define I2C0SCON_IENSTX_DIS            (0x0   << 10 )
#define I2C0SCON_IENSTX_EN             (0x1   << 10 )

/* I2C0SCON[IENSRX] - Slave Receive request interrupt enable */
#define I2C0SCON_IENSRX_BBA            (*(volatile unsigned long *) 0x42060524)
#define I2C0SCON_IENSRX_MSK            (0x1   << 9  )
#define I2C0SCON_IENSRX                (0x1   << 9  )
#define I2C0SCON_IENSRX_DIS            (0x0   << 9  )
#define I2C0SCON_IENSRX_EN             (0x1   << 9  )

/* I2C0SCON[IENSTOP] - Stop condition detected interrupt enable */
#define I2C0SCON_IENSTOP_BBA           (*(volatile unsigned long *) 0x42060520)
#define I2C0SCON_IENSTOP_MSK           (0x1   << 8  )
#define I2C0SCON_IENSTOP               (0x1   << 8  )
#define I2C0SCON_IENSTOP_DIS           (0x0   << 8  )
#define I2C0SCON_IENSTOP_EN            (0x1   << 8  )

/* I2C0SCON[NACK] - NACK next communication */
#define I2C0SCON_NACK_BBA              (*(volatile unsigned long *) 0x4206051C)
#define I2C0SCON_NACK_MSK              (0x1   << 7  )
#define I2C0SCON_NACK                  (0x1   << 7  )
#define I2C0SCON_NACK_DIS              (0x0   << 7  )
#define I2C0SCON_NACK_EN               (0x1   << 7  )

/* I2C0SCON[STRETCHSCL] - Stretch SCL enable */
#define I2C0SCON_STRETCHSCL_BBA        (*(volatile unsigned long *) 0x42060518)
#define I2C0SCON_STRETCHSCL_MSK        (0x1   << 6  )
#define I2C0SCON_STRETCHSCL            (0x1   << 6  )
#define I2C0SCON_STRETCHSCL_DIS        (0x0   << 6  )
#define I2C0SCON_STRETCHSCL_EN         (0x1   << 6  )

/* I2C0SCON[EARLYTXR] - Early transmit request mode */
#define I2C0SCON_EARLYTXR_BBA          (*(volatile unsigned long *) 0x42060514)
#define I2C0SCON_EARLYTXR_MSK          (0x1   << 5  )
#define I2C0SCON_EARLYTXR              (0x1   << 5  )
#define I2C0SCON_EARLYTXR_DIS          (0x0   << 5  )
#define I2C0SCON_EARLYTXR_EN           (0x1   << 5  )

/* I2C0SCON[GCSBCLR] - General call status bit clear */
#define I2C0SCON_GCSBCLR_BBA           (*(volatile unsigned long *) 0x42060510)
#define I2C0SCON_GCSBCLR_MSK           (0x1   << 4  )
#define I2C0SCON_GCSBCLR               (0x1   << 4  )
#define I2C0SCON_GCSBCLR_DIS           (0x0   << 4  )
#define I2C0SCON_GCSBCLR_EN            (0x1   << 4  )

/* I2C0SCON[HGCEN] - Hardware general call enable */
#define I2C0SCON_HGCEN_BBA             (*(volatile unsigned long *) 0x4206050C)
#define I2C0SCON_HGCEN_MSK             (0x1   << 3  )
#define I2C0SCON_HGCEN                 (0x1   << 3  )
#define I2C0SCON_HGCEN_DIS             (0x0   << 3  )
#define I2C0SCON_HGCEN_EN              (0x1   << 3  )

/* I2C0SCON[GCEN] - General call enable */
#define I2C0SCON_GCEN_BBA              (*(volatile unsigned long *) 0x42060508)
#define I2C0SCON_GCEN_MSK              (0x1   << 2  )
#define I2C0SCON_GCEN                  (0x1   << 2  )
#define I2C0SCON_GCEN_DIS              (0x0   << 2  )
#define I2C0SCON_GCEN_EN               (0x1   << 2  )

/* I2C0SCON[ADR10EN] - Enabled 10-bit addressing */
#define I2C0SCON_ADR10EN_BBA           (*(volatile unsigned long *) 0x42060504)
#define I2C0SCON_ADR10EN_MSK           (0x1   << 1  )
#define I2C0SCON_ADR10EN               (0x1   << 1  )
#define I2C0SCON_ADR10EN_DIS           (0x0   << 1  )
#define I2C0SCON_ADR10EN_EN            (0x1   << 1  )

/* I2C0SCON[SLVEN] - Slave enable */
#define I2C0SCON_SLVEN_BBA             (*(volatile unsigned long *) 0x42060500)
#define I2C0SCON_SLVEN_MSK             (0x1   << 0  )
#define I2C0SCON_SLVEN                 (0x1   << 0  )
#define I2C0SCON_SLVEN_DIS             (0x0   << 0  )
#define I2C0SCON_SLVEN_EN              (0x1   << 0  )

/* Reset Value for I2C0SSTA*/
#define I2C0SSTA_RVAL                  0x1 

/* I2C0SSTA[START] - Start and matching address */
#define I2C0SSTA_START_BBA             (*(volatile unsigned long *) 0x420605B8)
#define I2C0SSTA_START_MSK             (0x1   << 14 )
#define I2C0SSTA_START                 (0x1   << 14 )
#define I2C0SSTA_START_CLR             (0x0   << 14 )
#define I2C0SSTA_START_SET             (0x1   << 14 )

/* I2C0SSTA[REPSTART] - Repeated start and matching address */
#define I2C0SSTA_REPSTART_BBA          (*(volatile unsigned long *) 0x420605B4)
#define I2C0SSTA_REPSTART_MSK          (0x1   << 13 )
#define I2C0SSTA_REPSTART              (0x1   << 13 )
#define I2C0SSTA_REPSTART_CLR          (0x0   << 13 )
#define I2C0SSTA_REPSTART_SET          (0x1   << 13 )

/* I2C0SSTA[IDMAT] - Device ID matched */
#define I2C0SSTA_IDMAT_MSK             (0x3   << 11 )

/* I2C0SSTA[STOP] - Stop after start and matching address */
#define I2C0SSTA_STOP_BBA              (*(volatile unsigned long *) 0x420605A8)
#define I2C0SSTA_STOP_MSK              (0x1   << 10 )
#define I2C0SSTA_STOP                  (0x1   << 10 )
#define I2C0SSTA_STOP_CLR              (0x0   << 10 )
#define I2C0SSTA_STOP_SET              (0x1   << 10 )

/* I2C0SSTA[GCID] - General ID */
#define I2C0SSTA_GCID_MSK              (0x3   << 8  )

/* I2C0SSTA[GCINT] - General call interrupt */
#define I2C0SSTA_GCINT_BBA             (*(volatile unsigned long *) 0x4206059C)
#define I2C0SSTA_GCINT_MSK             (0x1   << 7  )
#define I2C0SSTA_GCINT                 (0x1   << 7  )
#define I2C0SSTA_GCINT_CLR             (0x0   << 7  )
#define I2C0SSTA_GCINT_SET             (0x1   << 7  )

/* I2C0SSTA[SBUSY] - Slave busy */
#define I2C0SSTA_SBUSY_BBA             (*(volatile unsigned long *) 0x42060598)
#define I2C0SSTA_SBUSY_MSK             (0x1   << 6  )
#define I2C0SSTA_SBUSY                 (0x1   << 6  )
#define I2C0SSTA_SBUSY_CLR             (0x0   << 6  )
#define I2C0SSTA_SBUSY_SET             (0x1   << 6  )

/* I2C0SSTA[NOACK] - Ack not generated by the slave */
#define I2C0SSTA_NOACK_BBA             (*(volatile unsigned long *) 0x42060594)
#define I2C0SSTA_NOACK_MSK             (0x1   << 5  )
#define I2C0SSTA_NOACK                 (0x1   << 5  )
#define I2C0SSTA_NOACK_CLR             (0x0   << 5  )
#define I2C0SSTA_NOACK_SET             (0x1   << 5  )

/* I2C0SSTA[SRXOF] - Slave Receive FIFO overflow */
#define I2C0SSTA_SRXOF_BBA             (*(volatile unsigned long *) 0x42060590)
#define I2C0SSTA_SRXOF_MSK             (0x1   << 4  )
#define I2C0SSTA_SRXOF                 (0x1   << 4  )
#define I2C0SSTA_SRXOF_CLR             (0x0   << 4  )
#define I2C0SSTA_SRXOF_SET             (0x1   << 4  )

/* I2C0SSTA[SRXREQ] - Slave Receive request */
#define I2C0SSTA_SRXREQ_BBA            (*(volatile unsigned long *) 0x4206058C)
#define I2C0SSTA_SRXREQ_MSK            (0x1   << 3  )
#define I2C0SSTA_SRXREQ                (0x1   << 3  )
#define I2C0SSTA_SRXREQ_CLR            (0x0   << 3  )
#define I2C0SSTA_SRXREQ_SET            (0x1   << 3  )

/* I2C0SSTA[STXREQ] - Slave Transmit request */
#define I2C0SSTA_STXREQ_BBA            (*(volatile unsigned long *) 0x42060588)
#define I2C0SSTA_STXREQ_MSK            (0x1   << 2  )
#define I2C0SSTA_STXREQ                (0x1   << 2  )
#define I2C0SSTA_STXREQ_CLR            (0x0   << 2  )
#define I2C0SSTA_STXREQ_SET            (0x1   << 2  )

/* I2C0SSTA[STXUR] - Slave Transmit FIFO underflow */
#define I2C0SSTA_STXUR_BBA             (*(volatile unsigned long *) 0x42060584)
#define I2C0SSTA_STXUR_MSK             (0x1   << 1  )
#define I2C0SSTA_STXUR                 (0x1   << 1  )
#define I2C0SSTA_STXUR_CLR             (0x0   << 1  )
#define I2C0SSTA_STXUR_SET             (0x1   << 1  )

/* I2C0SSTA[STXFSEREQ] - Slave Tx FIFO Status or early request */
#define I2C0SSTA_STXFSEREQ_BBA         (*(volatile unsigned long *) 0x42060580)
#define I2C0SSTA_STXFSEREQ_MSK         (0x1   << 0  )
#define I2C0SSTA_STXFSEREQ             (0x1   << 0  )
#define I2C0SSTA_STXFSEREQ_CLR         (0x0   << 0  )
#define I2C0SSTA_STXFSEREQ_SET         (0x1   << 0  )

/* Reset Value for I2C0SRX*/
#define I2C0SRX_RVAL                   0x0 

/* I2C0SRX[I2CSRX] - Slave receive register */
#define I2C0SRX_I2CSRX_MSK             (0xFF  << 0  )

/* Reset Value for I2C0STX*/
#define I2C0STX_RVAL                   0x0 

/* I2C0STX[I2CSTX] - Slave transmit register */
#define I2C0STX_I2CSTX_MSK             (0xFF  << 0  )

/* Reset Value for I2C0ALT*/
#define I2C0ALT_RVAL                   0x0 

/* I2C0ALT[ALT] - Slave Alt */
#define I2C0ALT_ALT_MSK                (0xFF  << 0  )

/* Reset Value for I2C0ID0*/
#define I2C0ID0_RVAL                   0x0 

/* I2C0ID0[ID0] - Slave device ID 0 */
#define I2C0ID0_ID0_MSK                (0xFF  << 0  )

/* Reset Value for I2C0ID1*/
#define I2C0ID1_RVAL                   0x0 

/* I2C0ID1[ID1] - Slave device ID 1 */
#define I2C0ID1_ID1_MSK                (0xFF  << 0  )

/* Reset Value for I2C0ID2*/
#define I2C0ID2_RVAL                   0x0 

/* I2C0ID2[ID2] - Slave device ID 2 */
#define I2C0ID2_ID2_MSK                (0xFF  << 0  )

/* Reset Value for I2C0ID3*/
#define I2C0ID3_RVAL                   0x0 

/* I2C0ID3[ID3] - Slave device ID 3 */
#define I2C0ID3_ID3_MSK                (0xFF  << 0  )

/* Reset Value for I2C0FSTA*/
#define I2C0FSTA_RVAL                  0x0 

/* I2C0FSTA[MFLUSH] - Flush the master transmit FIFO */
#define I2C0FSTA_MFLUSH_BBA            (*(volatile unsigned long *) 0x420609A4)
#define I2C0FSTA_MFLUSH_MSK            (0x1   << 9  )
#define I2C0FSTA_MFLUSH                (0x1   << 9  )
#define I2C0FSTA_MFLUSH_DIS            (0x0   << 9  ) /* Clearing to 0 has no effect. */
#define I2C0FSTA_MFLUSH_EN             (0x1   << 9  ) /* Set to 1 to flush the master transmit FIFO. The master transmit FIFO will have to flushed if arbitration is lost or a slave responds with a NACK. */

/* I2C0FSTA[SFLUSH] - Flush the slave transmit FIFO */
#define I2C0FSTA_SFLUSH_BBA            (*(volatile unsigned long *) 0x420609A0)
#define I2C0FSTA_SFLUSH_MSK            (0x1   << 8  )
#define I2C0FSTA_SFLUSH                (0x1   << 8  )
#define I2C0FSTA_SFLUSH_DIS            (0x0   << 8  ) /* Clearing to 0 has no effect. */
#define I2C0FSTA_SFLUSH_EN             (0x1   << 8  ) /* Set to 1 to flush the slave transmit FIFO. */

/* I2C0FSTA[MRXFSTA] - Master receive FIFO status */
#define I2C0FSTA_MRXFSTA_MSK           (0x3   << 6  )
#define I2C0FSTA_MRXFSTA_EMPTY         (0x0   << 6  ) /* FIFO empty               */
#define I2C0FSTA_MRXFSTA_ONEBYTE       (0x1   << 6  ) /* 1 bytes in the FIFO      */
#define I2C0FSTA_MRXFSTA_TWOBYTES      (0x2   << 6  ) /* 2 bytes in the FIFO      */

/* I2C0FSTA[MTXFSTA] - Master transmit FIFO status */
#define I2C0FSTA_MTXFSTA_MSK           (0x3   << 4  )
#define I2C0FSTA_MTXFSTA_EMPTY         (0x0   << 4  ) /* FIFO empty               */
#define I2C0FSTA_MTXFSTA_ONEBYTE       (0x1   << 4  ) /* 1 bytes in the FIFO      */
#define I2C0FSTA_MTXFSTA_TWOBYTES      (0x2   << 4  ) /* 2 bytes in the FIFO      */

/* I2C0FSTA[SRXFSTA] - Slave receive FIFO status */
#define I2C0FSTA_SRXFSTA_MSK           (0x3   << 2  )
#define I2C0FSTA_SRXFSTA_EMPTY         (0x0   << 2  ) /* FIFO empty               */
#define I2C0FSTA_SRXFSTA_ONEBYTE       (0x1   << 2  ) /* 1 bytes in the FIFO      */
#define I2C0FSTA_SRXFSTA_TWOBYTES      (0x2   << 2  ) /* 2 bytes in the FIFO      */

/* I2C0FSTA[STXFSTA] - Slave transmit FIFO status */
#define I2C0FSTA_STXFSTA_MSK           (0x3   << 0  )
#define I2C0FSTA_STXFSTA_EMPTY         (0x0   << 0  ) /* FIFO empty               */
#define I2C0FSTA_STXFSTA_ONEBYTE       (0x1   << 0  ) /* 1 bytes in the FIFO      */
#define I2C0FSTA_STXFSTA_TWOBYTES      (0x2   << 0  ) /* 2 bytes in the FIFO      */

/* Reset Value for I2C0SHCON*/
#define I2C0SHCON_RVAL                 0x0 

/* I2C0SHCON[RESET] - Reset START STOP detect circuit */
#define I2C0SHCON_RESET_BBA            (*(volatile unsigned long *) 0x42060A00)
#define I2C0SHCON_RESET_MSK            (0x1   << 0  )
#define I2C0SHCON_RESET                (0x1   << 0  )
#define I2C0SHCON_RESET_DIS            (0x0   << 0  )
#define I2C0SHCON_RESET_EN             (0x1   << 0  )

/* Reset Value for I2C0ASSCL*/
#define I2C0ASSCL_RVAL                 0x0 

/* I2C0ASSCL[SSRTSTA] - stretch timeout for slave */
#define I2C0ASSCL_SSRTSTA_BBA          (*(volatile unsigned long *) 0x42060B24)
#define I2C0ASSCL_SSRTSTA_MSK          (0x1   << 9  )
#define I2C0ASSCL_SSRTSTA              (0x1   << 9  )
#define I2C0ASSCL_SSRTSTA_DIS          (0x0   << 9  )
#define I2C0ASSCL_SSRTSTA_EN           (0x1   << 9  )

/* I2C0ASSCL[MSRTSTA] - stretch timeout for master */
#define I2C0ASSCL_MSRTSTA_BBA          (*(volatile unsigned long *) 0x42060B20)
#define I2C0ASSCL_MSRTSTA_MSK          (0x1   << 8  )
#define I2C0ASSCL_MSRTSTA              (0x1   << 8  )
#define I2C0ASSCL_MSRTSTA_DIS          (0x0   << 8  )
#define I2C0ASSCL_MSRTSTA_EN           (0x1   << 8  )

/* I2C0ASSCL[SSTRCON] - automatic stretch mode for slave */
#define I2C0ASSCL_SSTRCON_MSK          (0xF   << 4  )

/* I2C0ASSCL[MSTRCON] - automatic stretch mode for master */
#define I2C0ASSCL_MSTRCON_MSK          (0xF   << 0  )

/* Reset Value for I2C1MCON*/
#define I2C1MCON_RVAL                  0x0 

/* I2C1MCON[PRESTOP_BUS_CLR] - Prestop Bus-Clear */
#define I2C1MCON_PRESTOP_BUS_CLR_BBA   (*(volatile unsigned long *) 0x42068034)
#define I2C1MCON_PRESTOP_BUS_CLR_MSK   (0x1   << 13 )
#define I2C1MCON_PRESTOP_BUS_CLR       (0x1   << 13 )
#define I2C1MCON_PRESTOP_BUS_CLR_DIS   (0x0   << 13 )
#define I2C1MCON_PRESTOP_BUS_CLR_EN    (0x1   << 13 )

/* I2C1MCON[BUS_CLR_EN] - Bus-Clear Enable */
#define I2C1MCON_BUS_CLR_EN_BBA        (*(volatile unsigned long *) 0x42068030)
#define I2C1MCON_BUS_CLR_EN_MSK        (0x1   << 12 )
#define I2C1MCON_BUS_CLR_EN            (0x1   << 12 )
#define I2C1MCON_BUS_CLR_EN_DIS        (0x0   << 12 )
#define I2C1MCON_BUS_CLR_EN_EN         (0x1   << 12 )

/* I2C1MCON[MTXDMA] - Enable master Tx DMA request */
#define I2C1MCON_MTXDMA_BBA            (*(volatile unsigned long *) 0x4206802C)
#define I2C1MCON_MTXDMA_MSK            (0x1   << 11 )
#define I2C1MCON_MTXDMA                (0x1   << 11 )
#define I2C1MCON_MTXDMA_DIS            (0x0   << 11 ) /* Disable DMA mode         */
#define I2C1MCON_MTXDMA_EN             (0x1   << 11 ) /* Enable I2C master DMA Tx requests. */

/* I2C1MCON[MRXDMA] - Enable master Rx DMA request */
#define I2C1MCON_MRXDMA_BBA            (*(volatile unsigned long *) 0x42068028)
#define I2C1MCON_MRXDMA_MSK            (0x1   << 10 )
#define I2C1MCON_MRXDMA                (0x1   << 10 )
#define I2C1MCON_MRXDMA_DIS            (0x0   << 10 ) /* Disable DMA mode         */
#define I2C1MCON_MRXDMA_EN             (0x1   << 10 ) /* Enable I2C master DMA Rx requests. */

/* I2C1MCON[MXMITDEC] - Decrement master TX FIFO status when a byte has been transmitted */
#define I2C1MCON_MXMITDEC_BBA          (*(volatile unsigned long *) 0x42068024)
#define I2C1MCON_MXMITDEC_MSK          (0x1   << 9  )
#define I2C1MCON_MXMITDEC              (0x1   << 9  )
#define I2C1MCON_MXMITDEC_DIS          (0x0   << 9  )
#define I2C1MCON_MXMITDEC_EN           (0x1   << 9  )

/* I2C1MCON[IENCMP] - Transaction completed (or stop detected) interrupt enable */
#define I2C1MCON_IENCMP_BBA            (*(volatile unsigned long *) 0x42068020)
#define I2C1MCON_IENCMP_MSK            (0x1   << 8  )
#define I2C1MCON_IENCMP                (0x1   << 8  )
#define I2C1MCON_IENCMP_DIS            (0x0   << 8  ) /* An interrupt is not generated when a STOP is detected. */
#define I2C1MCON_IENCMP_EN             (0x1   << 8  ) /* An interrupt is generated when a STOP is detected. */

/* I2C1MCON[IENACK] - ACK not received interrupt enable */
#define I2C1MCON_IENACK_BBA            (*(volatile unsigned long *) 0x4206801C)
#define I2C1MCON_IENACK_MSK            (0x1   << 7  )
#define I2C1MCON_IENACK                (0x1   << 7  )
#define I2C1MCON_IENACK_DIS            (0x0   << 7  ) /* ACK not received interrupt disable */
#define I2C1MCON_IENACK_EN             (0x1   << 7  ) /* ACK not received interrupt enable */

/* I2C1MCON[IENALOST] - Arbitration lost interrupt enable */
#define I2C1MCON_IENALOST_BBA          (*(volatile unsigned long *) 0x42068018)
#define I2C1MCON_IENALOST_MSK          (0x1   << 6  )
#define I2C1MCON_IENALOST              (0x1   << 6  )
#define I2C1MCON_IENALOST_DIS          (0x0   << 6  ) /* Arbitration lost interrupt disable */
#define I2C1MCON_IENALOST_EN           (0x1   << 6  ) /* Arbitration lost interrupt enable */

/* I2C1MCON[IENMTX] - Transmit request interrupt enable. */
#define I2C1MCON_IENMTX_BBA            (*(volatile unsigned long *) 0x42068014)
#define I2C1MCON_IENMTX_MSK            (0x1   << 5  )
#define I2C1MCON_IENMTX                (0x1   << 5  )
#define I2C1MCON_IENMTX_DIS            (0x0   << 5  ) /* Transmit request interrupt disable */
#define I2C1MCON_IENMTX_EN             (0x1   << 5  ) /* Transmit request interrupt enable */

/* I2C1MCON[IENMRX] - Receive request interrupt enable */
#define I2C1MCON_IENMRX_BBA            (*(volatile unsigned long *) 0x42068010)
#define I2C1MCON_IENMRX_MSK            (0x1   << 4  )
#define I2C1MCON_IENMRX                (0x1   << 4  )
#define I2C1MCON_IENMRX_DIS            (0x0   << 4  ) /* Receive request interrupt disable */
#define I2C1MCON_IENMRX_EN             (0x1   << 4  ) /* Receive request interrupt enable */

/* I2C1MCON[STRETCH] - Stretch SCL enable */
#define I2C1MCON_STRETCH_BBA           (*(volatile unsigned long *) 0x4206800C)
#define I2C1MCON_STRETCH_MSK           (0x1   << 3  )
#define I2C1MCON_STRETCH               (0x1   << 3  )
#define I2C1MCON_STRETCH_DIS           (0x0   << 3  ) /* Disable Clock stretching */
#define I2C1MCON_STRETCH_EN            (0x1   << 3  ) /* Setting this bit tells the device if SCL is 0 hold it at 0;. Or if SCL is 1 then when it next goes to 0 hold it at 0. */

/* I2C1MCON[LOOPBACK] - Internal loopback enable */
#define I2C1MCON_LOOPBACK_BBA          (*(volatile unsigned long *) 0x42068008)
#define I2C1MCON_LOOPBACK_MSK          (0x1   << 2  )
#define I2C1MCON_LOOPBACK              (0x1   << 2  )
#define I2C1MCON_LOOPBACK_DIS          (0x0   << 2  ) /* SCL and SDA out of the device are not muxed onto their corresponding inputs. */
#define I2C1MCON_LOOPBACK_EN           (0x1   << 2  ) /* SCL and SDA out of the device are muxed onto their corresponding inputs. */

/* I2C1MCON[COMPETE] - Start back-off disable */
#define I2C1MCON_COMPETE_BBA           (*(volatile unsigned long *) 0x42068004)
#define I2C1MCON_COMPETE_MSK           (0x1   << 1  )
#define I2C1MCON_COMPETE               (0x1   << 1  )
#define I2C1MCON_COMPETE_DIS           (0x0   << 1  )
#define I2C1MCON_COMPETE_EN            (0x1   << 1  )

/* I2C1MCON[MASEN] - Master enable */
#define I2C1MCON_MASEN_BBA             (*(volatile unsigned long *) 0x42068000)
#define I2C1MCON_MASEN_MSK             (0x1   << 0  )
#define I2C1MCON_MASEN                 (0x1   << 0  )
#define I2C1MCON_MASEN_DIS             (0x0   << 0  ) /* Master is disabled       */
#define I2C1MCON_MASEN_EN              (0x1   << 0  ) /* Master is enabled        */

/* Reset Value for I2C1MSTA*/
#define I2C1MSTA_RVAL                  0x6000 

/* I2C1MSTA[SCL_FILTERED] - State of SCL Line */
#define I2C1MSTA_SCL_FILTERED_BBA      (*(volatile unsigned long *) 0x420680B8)
#define I2C1MSTA_SCL_FILTERED_MSK      (0x1   << 14 )
#define I2C1MSTA_SCL_FILTERED          (0x1   << 14 )
#define I2C1MSTA_SCL_FILTERED_CLR      (0x0   << 14 )
#define I2C1MSTA_SCL_FILTERED_SET      (0x1   << 14 )

/* I2C1MSTA[SDA_FILTERED] - State of SDA Line */
#define I2C1MSTA_SDA_FILTERED_BBA      (*(volatile unsigned long *) 0x420680B4)
#define I2C1MSTA_SDA_FILTERED_MSK      (0x1   << 13 )
#define I2C1MSTA_SDA_FILTERED          (0x1   << 13 )
#define I2C1MSTA_SDA_FILTERED_CLR      (0x0   << 13 )
#define I2C1MSTA_SDA_FILTERED_SET      (0x1   << 13 )

/* I2C1MSTA[MTXUFLOW] - Master Transmit Underflow */
#define I2C1MSTA_MTXUFLOW_BBA          (*(volatile unsigned long *) 0x420680B0)
#define I2C1MSTA_MTXUFLOW_MSK          (0x1   << 12 )
#define I2C1MSTA_MTXUFLOW              (0x1   << 12 )
#define I2C1MSTA_MTXUFLOW_CLR          (0x0   << 12 )
#define I2C1MSTA_MTXUFLOW_SET          (0x1   << 12 )

/* I2C1MSTA[MSTOP] - STOP driven by this I2C Master */
#define I2C1MSTA_MSTOP_BBA             (*(volatile unsigned long *) 0x420680AC)
#define I2C1MSTA_MSTOP_MSK             (0x1   << 11 )
#define I2C1MSTA_MSTOP                 (0x1   << 11 )
#define I2C1MSTA_MSTOP_CLR             (0x0   << 11 )
#define I2C1MSTA_MSTOP_SET             (0x1   << 11 )

/* I2C1MSTA[LINEBUSY] - Line is busy */
#define I2C1MSTA_LINEBUSY_BBA          (*(volatile unsigned long *) 0x420680A8)
#define I2C1MSTA_LINEBUSY_MSK          (0x1   << 10 )
#define I2C1MSTA_LINEBUSY              (0x1   << 10 )
#define I2C1MSTA_LINEBUSY_CLR          (0x0   << 10 )
#define I2C1MSTA_LINEBUSY_SET          (0x1   << 10 )

/* I2C1MSTA[MRXOF] - Master Receive FIFO overflow */
#define I2C1MSTA_MRXOF_BBA             (*(volatile unsigned long *) 0x420680A4)
#define I2C1MSTA_MRXOF_MSK             (0x1   << 9  )
#define I2C1MSTA_MRXOF                 (0x1   << 9  )
#define I2C1MSTA_MRXOF_CLR             (0x0   << 9  )
#define I2C1MSTA_MRXOF_SET             (0x1   << 9  )

/* I2C1MSTA[TCOMP] - Transaction complete or stop detected */
#define I2C1MSTA_TCOMP_BBA             (*(volatile unsigned long *) 0x420680A0)
#define I2C1MSTA_TCOMP_MSK             (0x1   << 8  )
#define I2C1MSTA_TCOMP                 (0x1   << 8  )
#define I2C1MSTA_TCOMP_CLR             (0x0   << 8  )
#define I2C1MSTA_TCOMP_SET             (0x1   << 8  )

/* I2C1MSTA[NACKDATA] - ACK not received in response to data write */
#define I2C1MSTA_NACKDATA_BBA          (*(volatile unsigned long *) 0x4206809C)
#define I2C1MSTA_NACKDATA_MSK          (0x1   << 7  )
#define I2C1MSTA_NACKDATA              (0x1   << 7  )
#define I2C1MSTA_NACKDATA_CLR          (0x0   << 7  )
#define I2C1MSTA_NACKDATA_SET          (0x1   << 7  )

/* I2C1MSTA[MBUSY] - Master busy */
#define I2C1MSTA_MBUSY_BBA             (*(volatile unsigned long *) 0x42068098)
#define I2C1MSTA_MBUSY_MSK             (0x1   << 6  )
#define I2C1MSTA_MBUSY                 (0x1   << 6  )
#define I2C1MSTA_MBUSY_CLR             (0x0   << 6  )
#define I2C1MSTA_MBUSY_SET             (0x1   << 6  )

/* I2C1MSTA[ALOST] - Arbitration lost */
#define I2C1MSTA_ALOST_BBA             (*(volatile unsigned long *) 0x42068094)
#define I2C1MSTA_ALOST_MSK             (0x1   << 5  )
#define I2C1MSTA_ALOST                 (0x1   << 5  )
#define I2C1MSTA_ALOST_CLR             (0x0   << 5  )
#define I2C1MSTA_ALOST_SET             (0x1   << 5  )

/* I2C1MSTA[NACKADDR] - ACK not received in response to an address */
#define I2C1MSTA_NACKADDR_BBA          (*(volatile unsigned long *) 0x42068090)
#define I2C1MSTA_NACKADDR_MSK          (0x1   << 4  )
#define I2C1MSTA_NACKADDR              (0x1   << 4  )
#define I2C1MSTA_NACKADDR_CLR          (0x0   << 4  )
#define I2C1MSTA_NACKADDR_SET          (0x1   << 4  )

/* I2C1MSTA[MRXREQ] - Master Receive request */
#define I2C1MSTA_MRXREQ_BBA            (*(volatile unsigned long *) 0x4206808C)
#define I2C1MSTA_MRXREQ_MSK            (0x1   << 3  )
#define I2C1MSTA_MRXREQ                (0x1   << 3  )
#define I2C1MSTA_MRXREQ_CLR            (0x0   << 3  )
#define I2C1MSTA_MRXREQ_SET            (0x1   << 3  )

/* I2C1MSTA[MTXREQ] - Master Transmit request */
#define I2C1MSTA_MTXREQ_BBA            (*(volatile unsigned long *) 0x42068088)
#define I2C1MSTA_MTXREQ_MSK            (0x1   << 2  )
#define I2C1MSTA_MTXREQ                (0x1   << 2  )
#define I2C1MSTA_MTXREQ_CLR            (0x0   << 2  )
#define I2C1MSTA_MTXREQ_SET            (0x1   << 2  )

/* I2C1MSTA[MTXFSTA] - Master Transmit FIFO status */
#define I2C1MSTA_MTXFSTA_MSK           (0x3   << 0  )

/* Reset Value for I2C1MRX*/
#define I2C1MRX_RVAL                   0x0 

/* I2C1MRX[ICMRX] - Master receive register */
#define I2C1MRX_ICMRX_MSK              (0xFF  << 0  )

/* Reset Value for I2C1MTX*/
#define I2C1MTX_RVAL                   0x0 

/* I2C1MTX[I2CMTX] - Master transmit register */
#define I2C1MTX_I2CMTX_MSK             (0xFF  << 0  )

/* Reset Value for I2C1MRXCNT*/
#define I2C1MRXCNT_RVAL                0x0 

/* I2C1MRXCNT[EXTEND] - Extended read */
#define I2C1MRXCNT_EXTEND_BBA          (*(volatile unsigned long *) 0x42068220)
#define I2C1MRXCNT_EXTEND_MSK          (0x1   << 8  )
#define I2C1MRXCNT_EXTEND              (0x1   << 8  )
#define I2C1MRXCNT_EXTEND_DIS          (0x0   << 8  )
#define I2C1MRXCNT_EXTEND_EN           (0x1   << 8  )

/* I2C1MRXCNT[COUNT] - Receive count */
#define I2C1MRXCNT_COUNT_MSK           (0xFF  << 0  )

/* Reset Value for I2C1MCRXCNT*/
#define I2C1MCRXCNT_RVAL               0x0 

/* I2C1MCRXCNT[COUNT] - Current receive count */
#define I2C1MCRXCNT_COUNT_MSK          (0xFF  << 0  )

/* Reset Value for I2C1ADR0*/
#define I2C1ADR0_RVAL                  0x0 

/* I2C1ADR0[ADR0] - Address byte 0 */
#define I2C1ADR0_ADR0_MSK              (0xFF  << 0  )

/* Reset Value for I2C1ADR1*/
#define I2C1ADR1_RVAL                  0x0 

/* I2C1ADR1[ADR1] - Address byte 1 */
#define I2C1ADR1_ADR1_MSK              (0xFF  << 0  )

/* Reset Value for I2C1DIV*/
#define I2C1DIV_RVAL                   0x1F1F 

/* I2C1DIV[HIGH] - Serial clock high time */
#define I2C1DIV_HIGH_MSK               (0xFF  << 8  )

/* I2C1DIV[LOW] - Serial clock low time */
#define I2C1DIV_LOW_MSK                (0xFF  << 0  )

/* Reset Value for I2C1SCON*/
#define I2C1SCON_RVAL                  0x0 

/* I2C1SCON[STXDMA] - Enable slave Tx DMA request */
#define I2C1SCON_STXDMA_BBA            (*(volatile unsigned long *) 0x42068538)
#define I2C1SCON_STXDMA_MSK            (0x1   << 14 )
#define I2C1SCON_STXDMA                (0x1   << 14 )
#define I2C1SCON_STXDMA_DIS            (0x0   << 14 )
#define I2C1SCON_STXDMA_EN             (0x1   << 14 )

/* I2C1SCON[SRXDMA] - Enable slave Rx DMA request */
#define I2C1SCON_SRXDMA_BBA            (*(volatile unsigned long *) 0x42068534)
#define I2C1SCON_SRXDMA_MSK            (0x1   << 13 )
#define I2C1SCON_SRXDMA                (0x1   << 13 )
#define I2C1SCON_SRXDMA_DIS            (0x0   << 13 )
#define I2C1SCON_SRXDMA_EN             (0x1   << 13 )

/* I2C1SCON[IENREPST] - Repeated start interrupt enable */
#define I2C1SCON_IENREPST_BBA          (*(volatile unsigned long *) 0x42068530)
#define I2C1SCON_IENREPST_MSK          (0x1   << 12 )
#define I2C1SCON_IENREPST              (0x1   << 12 )
#define I2C1SCON_IENREPST_DIS          (0x0   << 12 )
#define I2C1SCON_IENREPST_EN           (0x1   << 12 )

/* I2C1SCON[SXMITDEC] - Decrement Slave Tx FIFO status when a byte has been transmitted */
#define I2C1SCON_SXMITDEC_BBA          (*(volatile unsigned long *) 0x4206852C)
#define I2C1SCON_SXMITDEC_MSK          (0x1   << 11 )
#define I2C1SCON_SXMITDEC              (0x1   << 11 )
#define I2C1SCON_SXMITDEC_DIS          (0x0   << 11 )
#define I2C1SCON_SXMITDEC_EN           (0x1   << 11 )

/* I2C1SCON[IENSTX] - Slave Transmit request interrupt enable */
#define I2C1SCON_IENSTX_BBA            (*(volatile unsigned long *) 0x42068528)
#define I2C1SCON_IENSTX_MSK            (0x1   << 10 )
#define I2C1SCON_IENSTX                (0x1   << 10 )
#define I2C1SCON_IENSTX_DIS            (0x0   << 10 )
#define I2C1SCON_IENSTX_EN             (0x1   << 10 )

/* I2C1SCON[IENSRX] - Slave Receive request interrupt enable */
#define I2C1SCON_IENSRX_BBA            (*(volatile unsigned long *) 0x42068524)
#define I2C1SCON_IENSRX_MSK            (0x1   << 9  )
#define I2C1SCON_IENSRX                (0x1   << 9  )
#define I2C1SCON_IENSRX_DIS            (0x0   << 9  )
#define I2C1SCON_IENSRX_EN             (0x1   << 9  )

/* I2C1SCON[IENSTOP] - Stop condition detected interrupt enable */
#define I2C1SCON_IENSTOP_BBA           (*(volatile unsigned long *) 0x42068520)
#define I2C1SCON_IENSTOP_MSK           (0x1   << 8  )
#define I2C1SCON_IENSTOP               (0x1   << 8  )
#define I2C1SCON_IENSTOP_DIS           (0x0   << 8  )
#define I2C1SCON_IENSTOP_EN            (0x1   << 8  )

/* I2C1SCON[NACK] - NACK next communication */
#define I2C1SCON_NACK_BBA              (*(volatile unsigned long *) 0x4206851C)
#define I2C1SCON_NACK_MSK              (0x1   << 7  )
#define I2C1SCON_NACK                  (0x1   << 7  )
#define I2C1SCON_NACK_DIS              (0x0   << 7  )
#define I2C1SCON_NACK_EN               (0x1   << 7  )

/* I2C1SCON[STRETCHSCL] - Stretch SCL enable */
#define I2C1SCON_STRETCHSCL_BBA        (*(volatile unsigned long *) 0x42068518)
#define I2C1SCON_STRETCHSCL_MSK        (0x1   << 6  )
#define I2C1SCON_STRETCHSCL            (0x1   << 6  )
#define I2C1SCON_STRETCHSCL_DIS        (0x0   << 6  )
#define I2C1SCON_STRETCHSCL_EN         (0x1   << 6  )

/* I2C1SCON[EARLYTXR] - Early transmit request mode */
#define I2C1SCON_EARLYTXR_BBA          (*(volatile unsigned long *) 0x42068514)
#define I2C1SCON_EARLYTXR_MSK          (0x1   << 5  )
#define I2C1SCON_EARLYTXR              (0x1   << 5  )
#define I2C1SCON_EARLYTXR_DIS          (0x0   << 5  )
#define I2C1SCON_EARLYTXR_EN           (0x1   << 5  )

/* I2C1SCON[GCSBCLR] - General call status bit clear */
#define I2C1SCON_GCSBCLR_BBA           (*(volatile unsigned long *) 0x42068510)
#define I2C1SCON_GCSBCLR_MSK           (0x1   << 4  )
#define I2C1SCON_GCSBCLR               (0x1   << 4  )
#define I2C1SCON_GCSBCLR_DIS           (0x0   << 4  )
#define I2C1SCON_GCSBCLR_EN            (0x1   << 4  )

/* I2C1SCON[HGCEN] - Hardware general call enable */
#define I2C1SCON_HGCEN_BBA             (*(volatile unsigned long *) 0x4206850C)
#define I2C1SCON_HGCEN_MSK             (0x1   << 3  )
#define I2C1SCON_HGCEN                 (0x1   << 3  )
#define I2C1SCON_HGCEN_DIS             (0x0   << 3  )
#define I2C1SCON_HGCEN_EN              (0x1   << 3  )

/* I2C1SCON[GCEN] - General call enable */
#define I2C1SCON_GCEN_BBA              (*(volatile unsigned long *) 0x42068508)
#define I2C1SCON_GCEN_MSK              (0x1   << 2  )
#define I2C1SCON_GCEN                  (0x1   << 2  )
#define I2C1SCON_GCEN_DIS              (0x0   << 2  )
#define I2C1SCON_GCEN_EN               (0x1   << 2  )

/* I2C1SCON[ADR10EN] - Enabled 10-bit addressing */
#define I2C1SCON_ADR10EN_BBA           (*(volatile unsigned long *) 0x42068504)
#define I2C1SCON_ADR10EN_MSK           (0x1   << 1  )
#define I2C1SCON_ADR10EN               (0x1   << 1  )
#define I2C1SCON_ADR10EN_DIS           (0x0   << 1  )
#define I2C1SCON_ADR10EN_EN            (0x1   << 1  )

/* I2C1SCON[SLVEN] - Slave enable */
#define I2C1SCON_SLVEN_BBA             (*(volatile unsigned long *) 0x42068500)
#define I2C1SCON_SLVEN_MSK             (0x1   << 0  )
#define I2C1SCON_SLVEN                 (0x1   << 0  )
#define I2C1SCON_SLVEN_DIS             (0x0   << 0  )
#define I2C1SCON_SLVEN_EN              (0x1   << 0  )

/* Reset Value for I2C1SSTA*/
#define I2C1SSTA_RVAL                  0x1 

/* I2C1SSTA[START] - Start and matching address */
#define I2C1SSTA_START_BBA             (*(volatile unsigned long *) 0x420685B8)
#define I2C1SSTA_START_MSK             (0x1   << 14 )
#define I2C1SSTA_START                 (0x1   << 14 )
#define I2C1SSTA_START_CLR             (0x0   << 14 )
#define I2C1SSTA_START_SET             (0x1   << 14 )

/* I2C1SSTA[REPSTART] - Repeated start and matching address */
#define I2C1SSTA_REPSTART_BBA          (*(volatile unsigned long *) 0x420685B4)
#define I2C1SSTA_REPSTART_MSK          (0x1   << 13 )
#define I2C1SSTA_REPSTART              (0x1   << 13 )
#define I2C1SSTA_REPSTART_CLR          (0x0   << 13 )
#define I2C1SSTA_REPSTART_SET          (0x1   << 13 )

/* I2C1SSTA[IDMAT] - Device ID matched */
#define I2C1SSTA_IDMAT_MSK             (0x3   << 11 )

/* I2C1SSTA[STOP] - Stop after start and matching address */
#define I2C1SSTA_STOP_BBA              (*(volatile unsigned long *) 0x420685A8)
#define I2C1SSTA_STOP_MSK              (0x1   << 10 )
#define I2C1SSTA_STOP                  (0x1   << 10 )
#define I2C1SSTA_STOP_CLR              (0x0   << 10 )
#define I2C1SSTA_STOP_SET              (0x1   << 10 )

/* I2C1SSTA[GCID] - General ID */
#define I2C1SSTA_GCID_MSK              (0x3   << 8  )

/* I2C1SSTA[GCINT] - General call interrupt */
#define I2C1SSTA_GCINT_BBA             (*(volatile unsigned long *) 0x4206859C)
#define I2C1SSTA_GCINT_MSK             (0x1   << 7  )
#define I2C1SSTA_GCINT                 (0x1   << 7  )
#define I2C1SSTA_GCINT_CLR             (0x0   << 7  )
#define I2C1SSTA_GCINT_SET             (0x1   << 7  )

/* I2C1SSTA[SBUSY] - Slave busy */
#define I2C1SSTA_SBUSY_BBA             (*(volatile unsigned long *) 0x42068598)
#define I2C1SSTA_SBUSY_MSK             (0x1   << 6  )
#define I2C1SSTA_SBUSY                 (0x1   << 6  )
#define I2C1SSTA_SBUSY_CLR             (0x0   << 6  )
#define I2C1SSTA_SBUSY_SET             (0x1   << 6  )

/* I2C1SSTA[NOACK] - Ack not generated by the slave */
#define I2C1SSTA_NOACK_BBA             (*(volatile unsigned long *) 0x42068594)
#define I2C1SSTA_NOACK_MSK             (0x1   << 5  )
#define I2C1SSTA_NOACK                 (0x1   << 5  )
#define I2C1SSTA_NOACK_CLR             (0x0   << 5  )
#define I2C1SSTA_NOACK_SET             (0x1   << 5  )

/* I2C1SSTA[SRXOF] - Slave Receive FIFO overflow */
#define I2C1SSTA_SRXOF_BBA             (*(volatile unsigned long *) 0x42068590)
#define I2C1SSTA_SRXOF_MSK             (0x1   << 4  )
#define I2C1SSTA_SRXOF                 (0x1   << 4  )
#define I2C1SSTA_SRXOF_CLR             (0x0   << 4  )
#define I2C1SSTA_SRXOF_SET             (0x1   << 4  )

/* I2C1SSTA[SRXREQ] - Slave Receive request */
#define I2C1SSTA_SRXREQ_BBA            (*(volatile unsigned long *) 0x4206858C)
#define I2C1SSTA_SRXREQ_MSK            (0x1   << 3  )
#define I2C1SSTA_SRXREQ                (0x1   << 3  )
#define I2C1SSTA_SRXREQ_CLR            (0x0   << 3  )
#define I2C1SSTA_SRXREQ_SET            (0x1   << 3  )

/* I2C1SSTA[STXREQ] - Slave Transmit request */
#define I2C1SSTA_STXREQ_BBA            (*(volatile unsigned long *) 0x42068588)
#define I2C1SSTA_STXREQ_MSK            (0x1   << 2  )
#define I2C1SSTA_STXREQ                (0x1   << 2  )
#define I2C1SSTA_STXREQ_CLR            (0x0   << 2  )
#define I2C1SSTA_STXREQ_SET            (0x1   << 2  )

/* I2C1SSTA[STXUR] - Slave Transmit FIFO underflow */
#define I2C1SSTA_STXUR_BBA             (*(volatile unsigned long *) 0x42068584)
#define I2C1SSTA_STXUR_MSK             (0x1   << 1  )
#define I2C1SSTA_STXUR                 (0x1   << 1  )
#define I2C1SSTA_STXUR_CLR             (0x0   << 1  )
#define I2C1SSTA_STXUR_SET             (0x1   << 1  )

/* I2C1SSTA[STXFSEREQ] - Slave Tx FIFO Status or early request */
#define I2C1SSTA_STXFSEREQ_BBA         (*(volatile unsigned long *) 0x42068580)
#define I2C1SSTA_STXFSEREQ_MSK         (0x1   << 0  )
#define I2C1SSTA_STXFSEREQ             (0x1   << 0  )
#define I2C1SSTA_STXFSEREQ_CLR         (0x0   << 0  )
#define I2C1SSTA_STXFSEREQ_SET         (0x1   << 0  )

/* Reset Value for I2C1SRX*/
#define I2C1SRX_RVAL                   0x0 

/* I2C1SRX[I2CSRX] - Slave receive register */
#define I2C1SRX_I2CSRX_MSK             (0xFF  << 0  )

/* Reset Value for I2C1STX*/
#define I2C1STX_RVAL                   0x0 

/* I2C1STX[I2CSTX] - Slave transmit register */
#define I2C1STX_I2CSTX_MSK             (0xFF  << 0  )

/* Reset Value for I2C1ALT*/
#define I2C1ALT_RVAL                   0x0 

/* I2C1ALT[ALT] - Slave Alt */
#define I2C1ALT_ALT_MSK                (0xFF  << 0  )

/* Reset Value for I2C1ID0*/
#define I2C1ID0_RVAL                   0x0 

/* I2C1ID0[ID0] - Slave device ID 0 */
#define I2C1ID0_ID0_MSK                (0xFF  << 0  )

/* Reset Value for I2C1ID1*/
#define I2C1ID1_RVAL                   0x0 

/* I2C1ID1[ID1] - Slave device ID 1 */
#define I2C1ID1_ID1_MSK                (0xFF  << 0  )

/* Reset Value for I2C1ID2*/
#define I2C1ID2_RVAL                   0x0 

/* I2C1ID2[ID2] - Slave device ID 2 */
#define I2C1ID2_ID2_MSK                (0xFF  << 0  )

/* Reset Value for I2C1ID3*/
#define I2C1ID3_RVAL                   0x0 

/* I2C1ID3[ID3] - Slave device ID 3 */
#define I2C1ID3_ID3_MSK                (0xFF  << 0  )

/* Reset Value for I2C1FSTA*/
#define I2C1FSTA_RVAL                  0x0 

/* I2C1FSTA[MFLUSH] - Flush the master transmit FIFO */
#define I2C1FSTA_MFLUSH_BBA            (*(volatile unsigned long *) 0x420689A4)
#define I2C1FSTA_MFLUSH_MSK            (0x1   << 9  )
#define I2C1FSTA_MFLUSH                (0x1   << 9  )
#define I2C1FSTA_MFLUSH_DIS            (0x0   << 9  ) /* Clearing to 0 has no effect. */
#define I2C1FSTA_MFLUSH_EN             (0x1   << 9  ) /* Set to 1 to flush the master transmit FIFO. The master transmit FIFO will have to flushed if arbitration is lost or a slave responds with a NACK. */

/* I2C1FSTA[SFLUSH] - Flush the slave transmit FIFO */
#define I2C1FSTA_SFLUSH_BBA            (*(volatile unsigned long *) 0x420689A0)
#define I2C1FSTA_SFLUSH_MSK            (0x1   << 8  )
#define I2C1FSTA_SFLUSH                (0x1   << 8  )
#define I2C1FSTA_SFLUSH_DIS            (0x0   << 8  ) /* Clearing to 0 has no effect. */
#define I2C1FSTA_SFLUSH_EN             (0x1   << 8  ) /* Set to 1 to flush the slave transmit FIFO. */

/* I2C1FSTA[MRXFSTA] - Master receive FIFO status */
#define I2C1FSTA_MRXFSTA_MSK           (0x3   << 6  )
#define I2C1FSTA_MRXFSTA_EMPTY         (0x0   << 6  ) /* FIFO empty               */
#define I2C1FSTA_MRXFSTA_ONEBYTE       (0x1   << 6  ) /* 1 bytes in the FIFO      */
#define I2C1FSTA_MRXFSTA_TWOBYTES      (0x2   << 6  ) /* 2 bytes in the FIFO      */

/* I2C1FSTA[MTXFSTA] - Master transmit FIFO status */
#define I2C1FSTA_MTXFSTA_MSK           (0x3   << 4  )
#define I2C1FSTA_MTXFSTA_EMPTY         (0x0   << 4  ) /* FIFO empty               */
#define I2C1FSTA_MTXFSTA_ONEBYTE       (0x1   << 4  ) /* 1 bytes in the FIFO      */
#define I2C1FSTA_MTXFSTA_TWOBYTES      (0x2   << 4  ) /* 2 bytes in the FIFO      */

/* I2C1FSTA[SRXFSTA] - Slave receive FIFO status */
#define I2C1FSTA_SRXFSTA_MSK           (0x3   << 2  )
#define I2C1FSTA_SRXFSTA_EMPTY         (0x0   << 2  ) /* FIFO empty               */
#define I2C1FSTA_SRXFSTA_ONEBYTE       (0x1   << 2  ) /* 1 bytes in the FIFO      */
#define I2C1FSTA_SRXFSTA_TWOBYTES      (0x2   << 2  ) /* 2 bytes in the FIFO      */

/* I2C1FSTA[STXFSTA] - Slave transmit FIFO status */
#define I2C1FSTA_STXFSTA_MSK           (0x3   << 0  )
#define I2C1FSTA_STXFSTA_EMPTY         (0x0   << 0  ) /* FIFO empty               */
#define I2C1FSTA_STXFSTA_ONEBYTE       (0x1   << 0  ) /* 1 bytes in the FIFO      */
#define I2C1FSTA_STXFSTA_TWOBYTES      (0x2   << 0  ) /* 2 bytes in the FIFO      */

/* Reset Value for I2C1SHCON*/
#define I2C1SHCON_RVAL                 0x0 

/* I2C1SHCON[RESET] - Reset START STOP detect circuit */
#define I2C1SHCON_RESET_BBA            (*(volatile unsigned long *) 0x42068A00)
#define I2C1SHCON_RESET_MSK            (0x1   << 0  )
#define I2C1SHCON_RESET                (0x1   << 0  )
#define I2C1SHCON_RESET_DIS            (0x0   << 0  )
#define I2C1SHCON_RESET_EN             (0x1   << 0  )

#if defined(ADUCM320I) | defined(ADUCM322) | defined(ADUCM322I)

/* Reset Value for I2C1ASSCL*/
#define I2C1ASSCL_RVAL                 0x0 

/* I2C1ASSCL[SSRTSTA] - stretch timeout for slave */
#define I2C1ASSCL_SSRTSTA_BBA          (*(volatile unsigned long *) 0x42068B24)
#define I2C1ASSCL_SSRTSTA_MSK          (0x1   << 9  )
#define I2C1ASSCL_SSRTSTA              (0x1   << 9  )
#define I2C1ASSCL_SSRTSTA_DIS          (0x0   << 9  )
#define I2C1ASSCL_SSRTSTA_EN           (0x1   << 9  )

/* I2C1ASSCL[MSRTSTA] - stretch timeout for master */
#define I2C1ASSCL_MSRTSTA_BBA          (*(volatile unsigned long *) 0x42068B20)
#define I2C1ASSCL_MSRTSTA_MSK          (0x1   << 8  )
#define I2C1ASSCL_MSRTSTA              (0x1   << 8  )
#define I2C1ASSCL_MSRTSTA_DIS          (0x0   << 8  )
#define I2C1ASSCL_MSRTSTA_EN           (0x1   << 8  )

/* I2C1ASSCL[SSTRCON] - automatic stretch mode for slave */
#define I2C1ASSCL_SSTRCON_MSK          (0xF   << 4  )

/* I2C1ASSCL[MSTRCON] - automatic stretch mode for master */
#define I2C1ASSCL_MSTRCON_MSK          (0xF   << 0  )

#endif


// ------------------------------------------------------------------------------------------------
// -----                                        uart0                                        -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief UART (MMR_UART)
  */
typedef struct MMR_UART {                   /*!< MMR_UART Structure                    */
  __IO uint16_t  COMDAT;                    /*!< Transmit holding register & Receive buffer register */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  COMIEN;                    /*!< Interrupt enable register             */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  COMIIR;                    /*!< Interrupt identification register     */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  COMLCR;                    /*!< Line control register                 */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  COMMCR;                    /*!< Modem control register                */
  __I  uint16_t  RESERVED4;
  __IO uint16_t  COMLSR;                    /*!< Line status register                  */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  COMMSR;                    /*!< Modem status register                 */
  __I  uint16_t  RESERVED6;
  __IO uint16_t  COMSCR;                    /*!< Scratch buffer register               */
  __I  uint16_t  RESERVED7[3];
  __IO uint16_t  COMFBR;                    /*!< Fractional baud rate register         */
  __I  uint16_t  RESERVED8;
  __IO uint16_t  COMDIV;                    /*!< Baud rate divider register            */
} MMR_UART_t;

/* Reset Value for COMTX*/
#define COMTX_RVAL                     0x0 

/* COMTX[THR] - Transmit Holding Register */
#define COMTX_THR_MSK                  (0xFF  << 0  )

/* Reset Value for COMRX*/
#define COMRX_RVAL                     0x0 

/* COMRX[RBR] - Receive Buffer Register */
#define COMRX_RBR_MSK                  (0xFF  << 0  )

/* Reset Value for COMIEN*/
#define COMIEN_RVAL                    0x0 

/* COMIEN[EDMAR] - DMA requests in receive mode */
#define COMIEN_EDMAR_BBA               (*(volatile unsigned long *) 0x420A0094)
#define COMIEN_EDMAR_MSK               (0x1   << 5  )
#define COMIEN_EDMAR                   (0x1   << 5  )
#define COMIEN_EDMAR_DIS               (0x0   << 5  ) /* DMA requests disabled    */
#define COMIEN_EDMAR_EN                (0x1   << 5  ) /* DMA requests enabled     */

/* COMIEN[EDMAT] - DMA requests in transmit mode */
#define COMIEN_EDMAT_BBA               (*(volatile unsigned long *) 0x420A0090)
#define COMIEN_EDMAT_MSK               (0x1   << 4  )
#define COMIEN_EDMAT                   (0x1   << 4  )
#define COMIEN_EDMAT_DIS               (0x0   << 4  ) /* DMA requests are disabled */
#define COMIEN_EDMAT_EN                (0x1   << 4  ) /* DMA requests are enabled */

/* COMIEN[EDSSI] - Modem status interrupt */
#define COMIEN_EDSSI_BBA               (*(volatile unsigned long *) 0x420A008C)
#define COMIEN_EDSSI_MSK               (0x1   << 3  )
#define COMIEN_EDSSI                   (0x1   << 3  )
#define COMIEN_EDSSI_DIS               (0x0   << 3  ) /* Interrupt disabled       */
#define COMIEN_EDSSI_EN                (0x1   << 3  ) /* Interrupt enabled        */

/* COMIEN[ELSI] - Rx status interrupt */
#define COMIEN_ELSI_BBA                (*(volatile unsigned long *) 0x420A0088)
#define COMIEN_ELSI_MSK                (0x1   << 2  )
#define COMIEN_ELSI                    (0x1   << 2  )
#define COMIEN_ELSI_DIS                (0x0   << 2  ) /* Interrupt disabled       */
#define COMIEN_ELSI_EN                 (0x1   << 2  ) /* Interrupt enabled        */

/* COMIEN[ETBEI] - Transmit buffer empty interrupt */
#define COMIEN_ETBEI_BBA               (*(volatile unsigned long *) 0x420A0084)
#define COMIEN_ETBEI_MSK               (0x1   << 1  )
#define COMIEN_ETBEI                   (0x1   << 1  )
#define COMIEN_ETBEI_DIS               (0x0   << 1  ) /* Interrupt disabled       */
#define COMIEN_ETBEI_EN                (0x1   << 1  ) /* Interrupt enabled        */

/* COMIEN[ERBFI] - Receive buffer full interrupt */
#define COMIEN_ERBFI_BBA               (*(volatile unsigned long *) 0x420A0080)
#define COMIEN_ERBFI_MSK               (0x1   << 0  )
#define COMIEN_ERBFI                   (0x1   << 0  )
#define COMIEN_ERBFI_DIS               (0x0   << 0  ) /* Interrupt disabled       */
#define COMIEN_ERBFI_EN                (0x1   << 0  ) /* Interrupt enabled        */

/* Reset Value for COMIIR*/
#define COMIIR_RVAL                    0x1 

/* COMIIR[STA] - Interrupt status */
#define COMIIR_STA_MSK                 (0x3   << 1  )
#define COMIIR_STA_MODEMSTATUS         (0x0   << 1  ) /* Modem status interrupt (Read COMMSR to clear) */
#define COMIIR_STA_TXBUFEMPTY          (0x1   << 1  ) /* Transmit buffer empty interrupt (Write to COMTX or read COMIIR to clear) */
#define COMIIR_STA_RXBUFFULL           (0x2   << 1  ) /* Receive buffer full interrupt (Read COMRX to clear) */
#define COMIIR_STA_RXLINESTATUS        (0x3   << 1  ) /* Receive line status interrupt (Read COMLSR to clear) */

/* COMIIR[NIRQ] - Interrupt flag */
#define COMIIR_NIRQ_BBA                (*(volatile unsigned long *) 0x420A0100)
#define COMIIR_NIRQ_MSK                (0x1   << 0  )
#define COMIIR_NIRQ                    (0x1   << 0  )
#define COMIIR_NIRQ_CLR                (0x0   << 0  ) /* Interrupt occurred. Source of interrupt indicated in the STA bits. */
#define COMIIR_NIRQ_SET                (0x1   << 0  ) /* No interrupt occurred.   */

/* Reset Value for COMLCR*/
#define COMLCR_RVAL                    0x0 

/* COMLCR[BRK] - Set Break */
#define COMLCR_BRK_BBA                 (*(volatile unsigned long *) 0x420A0198)
#define COMLCR_BRK_MSK                 (0x1   << 6  )
#define COMLCR_BRK                     (0x1   << 6  )
#define COMLCR_BRK_DIS                 (0x0   << 6  ) /* Force TxD to 0           */
#define COMLCR_BRK_EN                  (0x1   << 6  ) /* Normal TxD operation     */

/* COMLCR[SP] - Stick Parity */
#define COMLCR_SP_BBA                  (*(volatile unsigned long *) 0x420A0194)
#define COMLCR_SP_MSK                  (0x1   << 5  )
#define COMLCR_SP                      (0x1   << 5  )
#define COMLCR_SP_DIS                  (0x0   << 5  ) /* Parity will not be forced based on EPS and PEN */
#define COMLCR_SP_EN                   (0x1   << 5  ) /* Parity forced based on EPS and PEN */

/* COMLCR[EPS] - Parity Select */
#define COMLCR_EPS_BBA                 (*(volatile unsigned long *) 0x420A0190)
#define COMLCR_EPS_MSK                 (0x1   << 4  )
#define COMLCR_EPS                     (0x1   << 4  )
#define COMLCR_EPS_ODD                 (0x0   << 4  ) /* Odd parity will be transmitted and checked */
#define COMLCR_EPS_EVEN                (0x1   << 4  ) /* Even parity will be transmitted and checked */

/* COMLCR[PEN] - Parity Enable */
#define COMLCR_PEN_BBA                 (*(volatile unsigned long *) 0x420A018C)
#define COMLCR_PEN_MSK                 (0x1   << 3  )
#define COMLCR_PEN                     (0x1   << 3  )
#define COMLCR_PEN_DIS                 (0x0   << 3  ) /* Parity will not be transmitted or checked */
#define COMLCR_PEN_EN                  (0x1   << 3  ) /* Parity will be transmitted and checked */

/* COMLCR[STOP] - Stop Bit */
#define COMLCR_STOP_BBA                (*(volatile unsigned long *) 0x420A0188)
#define COMLCR_STOP_MSK                (0x1   << 2  )
#define COMLCR_STOP                    (0x1   << 2  )
#define COMLCR_STOP_DIS                (0x0   << 2  ) /* Send 1 stop bit regardless of the word length (WLS). */
#define COMLCR_STOP_EN                 (0x1   << 2  ) /* Send a number of stop bits based on the word length. Transmit 1.5 stop bits if the word length is 5 bits (WLS = 00), or 2 stop bits if the word length is 6 (WLS = 01), 7 (WLS = 10), or 8 bits (WLS = 11). */

/* COMLCR[WLS] - Word Length Select */
#define COMLCR_WLS_MSK                 (0x3   << 0  )
#define COMLCR_WLS_FIVEBITS            (0x0   << 0  ) /* 5 bits                   */
#define COMLCR_WLS_SIXBITS             (0x1   << 0  ) /* 6 bits                   */
#define COMLCR_WLS_SEVENBITS           (0x2   << 0  ) /* 7 bits                   */
#define COMLCR_WLS_EIGHTBITS           (0x3   << 0  ) /* 8 bits                   */

/* Reset Value for COMMCR*/
#define COMMCR_RVAL                    0x0 

/* COMMCR[LOOPBACK] - Loopback mode */
#define COMMCR_LOOPBACK_BBA            (*(volatile unsigned long *) 0x420A0210)
#define COMMCR_LOOPBACK_MSK            (0x1   << 4  )
#define COMMCR_LOOPBACK                (0x1   << 4  )
#define COMMCR_LOOPBACK_DIS            (0x0   << 4  ) /* Normal operation - loopback disabled */
#define COMMCR_LOOPBACK_EN             (0x1   << 4  ) /* Loopback enabled         */

/* COMMCR[OUT2] - Output 2 */
#define COMMCR_OUT2_BBA                (*(volatile unsigned long *) 0x420A020C)
#define COMMCR_OUT2_MSK                (0x1   << 3  )
#define COMMCR_OUT2                    (0x1   << 3  )
#define COMMCR_OUT2_HIGH               (0x0   << 3  ) /* Force OUT2 to a logic 1  */
#define COMMCR_OUT2_LOW                (0x1   << 3  ) /* Force OUT2 to a logic 0  */

/* COMMCR[OUT1] - Output 1 */
#define COMMCR_OUT1_BBA                (*(volatile unsigned long *) 0x420A0208)
#define COMMCR_OUT1_MSK                (0x1   << 2  )
#define COMMCR_OUT1                    (0x1   << 2  )
#define COMMCR_OUT1_HIGH               (0x0   << 2  ) /* Force OUT1 to a logic 1  */
#define COMMCR_OUT1_LOW                (0x1   << 2  ) /* Force OUT1 to a logic 0  */

/* COMMCR[RTS] - Request to send */
#define COMMCR_RTS_BBA                 (*(volatile unsigned long *) 0x420A0204)
#define COMMCR_RTS_MSK                 (0x1   << 1  )
#define COMMCR_RTS                     (0x1   << 1  )
#define COMMCR_RTS_HIGH                (0x0   << 1  ) /* Force RTS to a logic 1   */
#define COMMCR_RTS_LOW                 (0x1   << 1  ) /* Force RTS to a logic 0   */

/* COMMCR[DTR] - Data Terminal Ready */
#define COMMCR_DTR_BBA                 (*(volatile unsigned long *) 0x420A0200)
#define COMMCR_DTR_MSK                 (0x1   << 0  )
#define COMMCR_DTR                     (0x1   << 0  )
#define COMMCR_DTR_HIGH                (0x0   << 0  ) /* Force DTR to a logic 1   */
#define COMMCR_DTR_LOW                 (0x1   << 0  ) /* Force DTR to a logic 0   */

/* Reset Value for COMLSR*/
#define COMLSR_RVAL                    0x60 

/* COMLSR[TEMT] - COMTX and shift register empty status */
#define COMLSR_TEMT_BBA                (*(volatile unsigned long *) 0x420A0298)
#define COMLSR_TEMT_MSK                (0x1   << 6  )
#define COMLSR_TEMT                    (0x1   << 6  )
#define COMLSR_TEMT_CLR                (0x0   << 6  ) /* COMTX has been written to and contains data to be transmitted. Care should be taken not to overwrite its value. */
#define COMLSR_TEMT_SET                (0x1   << 6  ) /* COMTX and the transmit shift register are empty and it is safe to write new data to COMTX. Data has been transmitted. */

/* COMLSR[THRE] - COMTX empty */
#define COMLSR_THRE_BBA                (*(volatile unsigned long *) 0x420A0294)
#define COMLSR_THRE_MSK                (0x1   << 5  )
#define COMLSR_THRE                    (0x1   << 5  )
#define COMLSR_THRE_CLR                (0x0   << 5  ) /* COMTX has been written to and contains data to be transmitted. Care should be taken not to overwrite its value. */
#define COMLSR_THRE_SET                (0x1   << 5  ) /* COMTX is empty and it is safe to write new data to COMTX. The previous data may not have been transmitted yet and can still be present in the shift register. */

/* COMLSR[BI] - Break indicator */
#define COMLSR_BI_BBA                  (*(volatile unsigned long *) 0x420A0290)
#define COMLSR_BI_MSK                  (0x1   << 4  )
#define COMLSR_BI                      (0x1   << 4  )
#define COMLSR_BI_CLR                  (0x0   << 4  ) /* SIN was not detected to be longer than the maximum word length. */
#define COMLSR_BI_SET                  (0x1   << 4  ) /* SIN was held low for more than the maximum word length. */

/* COMLSR[FE] - Framing error */
#define COMLSR_FE_BBA                  (*(volatile unsigned long *) 0x420A028C)
#define COMLSR_FE_MSK                  (0x1   << 3  )
#define COMLSR_FE                      (0x1   << 3  )
#define COMLSR_FE_CLR                  (0x0   << 3  ) /* No invalid Stop bit was detected. */
#define COMLSR_FE_SET                  (0x1   << 3  ) /* An invalid Stop bit was detected on a received word. */

/* COMLSR[PE] - Parity error */
#define COMLSR_PE_BBA                  (*(volatile unsigned long *) 0x420A0288)
#define COMLSR_PE_MSK                  (0x1   << 2  )
#define COMLSR_PE                      (0x1   << 2  )
#define COMLSR_PE_CLR                  (0x0   << 2  ) /* No parity error was detected */
#define COMLSR_PE_SET                  (0x1   << 2  ) /* A parity error occurred on a received word. */

/* COMLSR[OE] - Overrun error */
#define COMLSR_OE_BBA                  (*(volatile unsigned long *) 0x420A0284)
#define COMLSR_OE_MSK                  (0x1   << 1  )
#define COMLSR_OE                      (0x1   << 1  )
#define COMLSR_OE_CLR                  (0x0   << 1  ) /* Receive data has not been overwritten */
#define COMLSR_OE_SET                  (0x1   << 1  ) /* Receive data was overwritten by new data before COMRX was read. */

/* COMLSR[DR] - Data ready */
#define COMLSR_DR_BBA                  (*(volatile unsigned long *) 0x420A0280)
#define COMLSR_DR_MSK                  (0x1   << 0  )
#define COMLSR_DR                      (0x1   << 0  )
#define COMLSR_DR_CLR                  (0x0   << 0  ) /* COMRX does not contain new receive data. */
#define COMLSR_DR_SET                  (0x1   << 0  ) /* COMRX contains receive data that should be read. */

/* Reset Value for COMMSR*/
#define COMMSR_RVAL                    0x0 

/* COMMSR[DCD] - Data Carrier Detect */
#define COMMSR_DCD_BBA                 (*(volatile unsigned long *) 0x420A031C)
#define COMMSR_DCD_MSK                 (0x1   << 7  )
#define COMMSR_DCD                     (0x1   << 7  )
#define COMMSR_DCD_DIS                 (0x0   << 7  ) /* DCD is currently logic high */
#define COMMSR_DCD_EN                  (0x1   << 7  ) /* DCD is currently logic low */

/* COMMSR[RI] - Ring Indicator */
#define COMMSR_RI_BBA                  (*(volatile unsigned long *) 0x420A0318)
#define COMMSR_RI_MSK                  (0x1   << 6  )
#define COMMSR_RI                      (0x1   << 6  )
#define COMMSR_RI_DIS                  (0x0   << 6  ) /* RI is currently logic high */
#define COMMSR_RI_EN                   (0x1   << 6  ) /* RI is currently logic low */

/* COMMSR[DSR] - Data Set Ready */
#define COMMSR_DSR_BBA                 (*(volatile unsigned long *) 0x420A0314)
#define COMMSR_DSR_MSK                 (0x1   << 5  )
#define COMMSR_DSR                     (0x1   << 5  )
#define COMMSR_DSR_DIS                 (0x0   << 5  ) /* DSR is currently logic high */
#define COMMSR_DSR_EN                  (0x1   << 5  ) /* DSR is currently logic low */

/* COMMSR[CTS] - Clear To Send */
#define COMMSR_CTS_BBA                 (*(volatile unsigned long *) 0x420A0310)
#define COMMSR_CTS_MSK                 (0x1   << 4  )
#define COMMSR_CTS                     (0x1   << 4  )
#define COMMSR_CTS_DIS                 (0x0   << 4  ) /* CTS is currently logic high */
#define COMMSR_CTS_EN                  (0x1   << 4  ) /* CTS is currently logic low */

/* COMMSR[DDCD] - Delta DCD */
#define COMMSR_DDCD_BBA                (*(volatile unsigned long *) 0x420A030C)
#define COMMSR_DDCD_MSK                (0x1   << 3  )
#define COMMSR_DDCD                    (0x1   << 3  )
#define COMMSR_DDCD_DIS                (0x0   << 3  ) /* DCD has not changed state since COMMSR was last read */
#define COMMSR_DDCD_EN                 (0x1   << 3  ) /* DCD changed state since COMMSR last read */

/* COMMSR[TERI] - Trailing Edge RI */
#define COMMSR_TERI_BBA                (*(volatile unsigned long *) 0x420A0308)
#define COMMSR_TERI_MSK                (0x1   << 2  )
#define COMMSR_TERI                    (0x1   << 2  )
#define COMMSR_TERI_DIS                (0x0   << 2  ) /* RI has not changed from 0 to 1 since COMMSR last read */
#define COMMSR_TERI_EN                 (0x1   << 2  ) /* RI changed from 0 to 1 since COMMSR last read */

/* COMMSR[DDSR] - Delta DSR */
#define COMMSR_DDSR_BBA                (*(volatile unsigned long *) 0x420A0304)
#define COMMSR_DDSR_MSK                (0x1   << 1  )
#define COMMSR_DDSR                    (0x1   << 1  )
#define COMMSR_DDSR_DIS                (0x0   << 1  ) /* DSR has not changed state since COMMSR was last read */
#define COMMSR_DDSR_EN                 (0x1   << 1  ) /* DSR changed state since COMMSR last read */

/* COMMSR[DCTS] - Delta CTS */
#define COMMSR_DCTS_BBA                (*(volatile unsigned long *) 0x420A0300)
#define COMMSR_DCTS_MSK                (0x1   << 0  )
#define COMMSR_DCTS                    (0x1   << 0  )
#define COMMSR_DCTS_DIS                (0x0   << 0  ) /* CTS has not changed state since COMMSR was last read */
#define COMMSR_DCTS_EN                 (0x1   << 0  ) /* CTS changed state since COMMSR last read */

/* Reset Value for COMSCR*/
#define COMSCR_RVAL                    0x0 

/* COMSCR[SCR] - Scratch */
#define COMSCR_SCR_MSK                 (0xFF  << 0  )

/* Reset Value for COMFBR*/
#define COMFBR_RVAL                    0x0 

/* COMFBR[FBEN] - Fractional baud rate generator enable */
#define COMFBR_FBEN_BBA                (*(volatile unsigned long *) 0x420A04BC)
#define COMFBR_FBEN_MSK                (0x1   << 15 )
#define COMFBR_FBEN                    (0x1   << 15 )
#define COMFBR_FBEN_DIS                (0x0   << 15 )
#define COMFBR_FBEN_EN                 (0x1   << 15 )

/* COMFBR[DIVM] - Fractional baud rate M divide bits 1 to 3 */
#define COMFBR_DIVM_MSK                (0x3   << 11 )

/* COMFBR[DIVN] - Fractional baud rate N divide bits 0 to 2047. */
#define COMFBR_DIVN_MSK                (0x7FF << 0  )

/* Reset Value for COMDIV*/
#define COMDIV_RVAL                    0x1 

/* COMDIV[DIV] - Baud rate divider */
#define COMDIV_DIV_MSK                 (0xFFFF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        MDIO                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief MDIO (MMR_MDIO)
  */

typedef struct MMR_MDIO {                   /*!< MMR_MDIO Structure                    */
  __IO uint16_t  MDCON;                     /*!< MDIO block control                    */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  MDFRM;                     /*!< MDIO received frame control information */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  MDRXD;                     /*!< MDIO received data                    */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  MDADR;                     /*!< MDIO received address                 */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  MDTXD;                     /*!< MDIO data for transmission            */
  __I  uint16_t  RESERVED4;
  __IO uint16_t  MDPHY;                     /*!< MDIO PHYADDR software values and selection and DEVADD */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  MDSTA;                     /*!< MDIO progress signaling through frame */
  __I  uint16_t  RESERVED6;
  __IO uint16_t  MDIEN;                     /*!< MDIO interrupt enables                */
  __I  uint16_t  RESERVED7;
  __IO uint16_t  MDPIN;                     /*!< MDIO read PHYADDR pins                */
} MMR_MDIO_t;

/* Reset Value for MDCON*/
#define MDCON_RVAL                     0x0 

/* MDCON[MD_DRV] -  */
#define MDCON_MD_DRV_BBA               (*(volatile unsigned long *) 0x420B8008)
#define MDCON_MD_DRV_MSK               (0x1   << 2  )
#define MDCON_MD_DRV                   (0x1   << 2  )
#define MDCON_MD_DRV_MD_DRV_OD         (0x0   << 2  ) /* MDIO drive open drain.   */
#define MDCON_MD_DRV_MD_DRV_PP         (0x1   << 2  ) /* MDIO drive push-pull.    */

/* MDCON[MD_PHM] -  */
#define MDCON_MD_PHM_BBA               (*(volatile unsigned long *) 0x420B8004)
#define MDCON_MD_PHM_MSK               (0x1   << 1  )
#define MDCON_MD_PHM                   (0x1   << 1  )

/* MDCON[MD_RST] -  */
#define MDCON_MD_RST_BBA               (*(volatile unsigned long *) 0x420B8000)
#define MDCON_MD_RST_MSK               (0x1   << 0  )
#define MDCON_MD_RST                   (0x1   << 0  )
#define MDCON_MD_RST_DIS               (0x0   << 0  )
#define MDCON_MD_RST_EN                (0x1   << 0  )

/* Reset Value for MDFRM*/
#define MDFRM_RVAL                     0x0 

/* MDFRM[MD_DEV] -  */
#define MDFRM_MD_DEV_MSK               (0x1F  << 7  )

/* MDFRM[MD_PHY] -  */
#define MDFRM_MD_PHY_MSK               (0x1F  << 2  )

/* MDFRM[MD_OP] -  */
#define MDFRM_MD_OP_MSK                (0x3   << 0  )
#define MDFRM_MD_OP_MD_OP_ADF          (0x0   << 0  ) /* Address frame.           */
#define MDFRM_MD_OP_MD_OP_WRF          (0x1   << 0  ) /* Write frame.             */
#define MDFRM_MD_OP_MD_OP_INCF         (0x2   << 0  ) /* PostReadIncAdd frame.    */
#define MDFRM_MD_OP_MD_OP_RDF          (0x3   << 0  ) /* Read frame.              */

/* Reset Value for MDRXD*/
#define MDRXD_RVAL                     0x0 

/* MDRXD[MD_RXD] -  */
#define MDRXD_MD_RXD_MSK               (0xFFFF << 0  )

/* Reset Value for MDADR*/
#define MDADR_RVAL                     0x0 

/* MDADR[MD_ADR] -  */
#define MDADR_MD_ADR_MSK               (0xFFFF << 0  )

/* Reset Value for MDTXD*/
#define MDTXD_RVAL                     0x0 

/* MDTXD[MD_TXD] -  */
#define MDTXD_MD_TXD_MSK               (0xFFFF << 0  )

/* Reset Value for MDPHY*/
#define MDPHY_RVAL                     0x400 

/* MDPHY[MD_DEVADD] -  */
#define MDPHY_MD_DEVADD_MSK            (0x1F  << 10 )

/* MDPHY[MD_PHYSEL] -  */
#define MDPHY_MD_PHYSEL_MSK            (0x1F  << 5  )

/* MDPHY[MD_PHYSW] -  */
#define MDPHY_MD_PHYSW_MSK             (0x1F  << 0  )

/* Reset Value for MDSTA*/
#define MDSTA_RVAL                     0x0 

/* MDSTA[MD_PHYN] -  */
#define MDSTA_MD_PHYN_BBA              (*(volatile unsigned long *) 0x420B831C)
#define MDSTA_MD_PHYN_MSK              (0x1   << 7  )
#define MDSTA_MD_PHYN                  (0x1   << 7  )
#define MDSTA_MD_PHYN_DIS              (0x0   << 7  )
#define MDSTA_MD_PHYN_EN               (0x1   << 7  )

/* MDSTA[MD_PHYM] -  */
#define MDSTA_MD_PHYM_BBA              (*(volatile unsigned long *) 0x420B8318)
#define MDSTA_MD_PHYM_MSK              (0x1   << 6  )
#define MDSTA_MD_PHYM                  (0x1   << 6  )
#define MDSTA_MD_PHYM_DIS              (0x0   << 6  )
#define MDSTA_MD_PHYM_EN               (0x1   << 6  )

/* MDSTA[MD_DEVN] -  */
#define MDSTA_MD_DEVN_BBA              (*(volatile unsigned long *) 0x420B8314)
#define MDSTA_MD_DEVN_MSK              (0x1   << 5  )
#define MDSTA_MD_DEVN                  (0x1   << 5  )
#define MDSTA_MD_DEVN_DIS              (0x0   << 5  )
#define MDSTA_MD_DEVN_EN               (0x1   << 5  )

/* MDSTA[MD_DEVM] -  */
#define MDSTA_MD_DEVM_BBA              (*(volatile unsigned long *) 0x420B8310)
#define MDSTA_MD_DEVM_MSK              (0x1   << 4  )
#define MDSTA_MD_DEVM                  (0x1   << 4  )
#define MDSTA_MD_DEVM_DIS              (0x0   << 4  )
#define MDSTA_MD_DEVM_EN               (0x1   << 4  )

/* MDSTA[MD_RDF] -  */
#define MDSTA_MD_RDF_BBA               (*(volatile unsigned long *) 0x420B830C)
#define MDSTA_MD_RDF_MSK               (0x1   << 3  )
#define MDSTA_MD_RDF                   (0x1   << 3  )
#define MDSTA_MD_RDF_DIS               (0x0   << 3  )
#define MDSTA_MD_RDF_EN                (0x1   << 3  )

/* MDSTA[MD_INCF] -  */
#define MDSTA_MD_INCF_BBA              (*(volatile unsigned long *) 0x420B8308)
#define MDSTA_MD_INCF_MSK              (0x1   << 2  )
#define MDSTA_MD_INCF                  (0x1   << 2  )
#define MDSTA_MD_INCF_DIS              (0x0   << 2  )
#define MDSTA_MD_INCF_EN               (0x1   << 2  )

/* MDSTA[MD_ADRF] -  */
#define MDSTA_MD_ADRF_BBA              (*(volatile unsigned long *) 0x420B8304)
#define MDSTA_MD_ADRF_MSK              (0x1   << 1  )
#define MDSTA_MD_ADRF                  (0x1   << 1  )
#define MDSTA_MD_ADRF_DIS              (0x0   << 1  )
#define MDSTA_MD_ADRF_EN               (0x1   << 1  )

/* MDSTA[MD_WRF] -  */
#define MDSTA_MD_WRF_BBA               (*(volatile unsigned long *) 0x420B8300)
#define MDSTA_MD_WRF_MSK               (0x1   << 0  )
#define MDSTA_MD_WRF                   (0x1   << 0  )
#define MDSTA_MD_WRF_DIS               (0x0   << 0  )
#define MDSTA_MD_WRF_EN                (0x1   << 0  )

/* Reset Value for MDIEN*/
#define MDIEN_RVAL                     0x0 

/* MDIEN[MD_PHYNI] -  */
#define MDIEN_MD_PHYNI_BBA             (*(volatile unsigned long *) 0x420B839C)
#define MDIEN_MD_PHYNI_MSK             (0x1   << 7  )
#define MDIEN_MD_PHYNI                 (0x1   << 7  )
#define MDIEN_MD_PHYNI_DIS             (0x0   << 7  )
#define MDIEN_MD_PHYNI_EN              (0x1   << 7  )

/* MDIEN[MD_PHYMI] -  */
#define MDIEN_MD_PHYMI_BBA             (*(volatile unsigned long *) 0x420B8398)
#define MDIEN_MD_PHYMI_MSK             (0x1   << 6  )
#define MDIEN_MD_PHYMI                 (0x1   << 6  )
#define MDIEN_MD_PHYMI_DIS             (0x0   << 6  )
#define MDIEN_MD_PHYMI_EN              (0x1   << 6  )

/* MDIEN[MD_DEVNI] -  */
#define MDIEN_MD_DEVNI_BBA             (*(volatile unsigned long *) 0x420B8394)
#define MDIEN_MD_DEVNI_MSK             (0x1   << 5  )
#define MDIEN_MD_DEVNI                 (0x1   << 5  )
#define MDIEN_MD_DEVNI_DIS             (0x0   << 5  )
#define MDIEN_MD_DEVNI_EN              (0x1   << 5  )

/* MDIEN[MD_DEVMI] -  */
#define MDIEN_MD_DEVMI_BBA             (*(volatile unsigned long *) 0x420B8390)
#define MDIEN_MD_DEVMI_MSK             (0x1   << 4  )
#define MDIEN_MD_DEVMI                 (0x1   << 4  )
#define MDIEN_MD_DEVMI_DIS             (0x0   << 4  )
#define MDIEN_MD_DEVMI_EN              (0x1   << 4  )

/* MDIEN[MD_RDFI] -  */
#define MDIEN_MD_RDFI_BBA              (*(volatile unsigned long *) 0x420B838C)
#define MDIEN_MD_RDFI_MSK              (0x1   << 3  )
#define MDIEN_MD_RDFI                  (0x1   << 3  )
#define MDIEN_MD_RDFI_DIS              (0x0   << 3  )
#define MDIEN_MD_RDFI_EN               (0x1   << 3  )

/* MDIEN[MD_INCFI] -  */
#define MDIEN_MD_INCFI_BBA             (*(volatile unsigned long *) 0x420B8388)
#define MDIEN_MD_INCFI_MSK             (0x1   << 2  )
#define MDIEN_MD_INCFI                 (0x1   << 2  )
#define MDIEN_MD_INCFI_DIS             (0x0   << 2  )
#define MDIEN_MD_INCFI_EN              (0x1   << 2  )

/* MDIEN[MD_ADRI] -  */
#define MDIEN_MD_ADRI_BBA              (*(volatile unsigned long *) 0x420B8384)
#define MDIEN_MD_ADRI_MSK              (0x1   << 1  )
#define MDIEN_MD_ADRI                  (0x1   << 1  )
#define MDIEN_MD_ADRI_DIS              (0x0   << 1  )
#define MDIEN_MD_ADRI_EN               (0x1   << 1  )

/* MDIEN[MD_WRFI] -  */
#define MDIEN_MD_WRFI_BBA              (*(volatile unsigned long *) 0x420B8380)
#define MDIEN_MD_WRFI_MSK              (0x1   << 0  )
#define MDIEN_MD_WRFI                  (0x1   << 0  )
#define MDIEN_MD_WRFI_DIS              (0x0   << 0  )
#define MDIEN_MD_WRFI_EN               (0x1   << 0  )

/* Reset Value for MDPIN*/
#define MDPIN_RVAL                     0x0 

/* MDPIN[MD_PIN] -  */
#define MDPIN_MD_PIN_MSK               (0x1F  << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        PLA                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief PLA (MMR_PLA)
  */

typedef struct MMR_PLA {                    /*!< MMR_PLA Structure                     */
  __IO uint32_t  PLA_ELEM[32];              /*!< ELEMx Configuration Register          */
  __IO uint16_t  PLA_CLK;                   /*!< PLA Clock Select                      */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  PLA_IRQ0;                  /*!< Interrupt Register for Block 0 and 1  */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  PLA_IRQ1;                  /*!< Interrupt Register for Block 2 and 3  */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  PLA_ADC;                   /*!< ADC Configuration Register            */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  PLA_DIN0;                  /*!< AMBA Bus Data Input for Block 0 and 1 */
  __I  uint16_t  RESERVED4[3];
  __IO uint16_t  PLA_DOUT0;                 /*!< AMBA Bus Data Output for Block 0 and 1 */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  PLA_DOUT1;                 /*!< AMBA Bus Data Output for Block 2 and 3 */
  __I  uint16_t  RESERVED6;
  __IO uint16_t  PLA_LCK;                   /*!< Write lock Register. Can only be set once every reset */
  __I  uint16_t  RESERVED7;
#if defined(ADUCM320I) | defined(ADUCM322) | defined(ADUCM322I)
  __IO uint16_t  PLA_PROBE_I2C;             /*!< PLA GPIO INPUT can be switched to probe I2C SCL/SDA */
  __I  uint16_t  RESERVED8;
#endif
} MMR_PLA_t;

/* Reset Value for PLA_ELEM*/
#define PLA_ELEM_RVAL                  0x0 

/* PLA_ELEM[MUX0] - Even element feedback selection (in respective block) */
#define PLA_ELEM_MUX0_MSK              (0x3   << 9  )
#define PLA_ELEM_MUX0_ELEM0            (0x0   << 9  ) /* Feedback from Element 0 (all except Element 0) / Input from other block (Element 0 only) */
#define PLA_ELEM_MUX0_ELEM2            (0x1   << 9  ) /* Feedback from Element 2  */
#define PLA_ELEM_MUX0_ELEM4            (0x2   << 9  ) /* Feedback from Element 4  */
#define PLA_ELEM_MUX0_ELEM6            (0x3   << 9  ) /* Feedback from Element 6  */

/* PLA_ELEM[MUX1] - Odd element feedback selection (in respective block) */
#define PLA_ELEM_MUX1_MSK              (0x3   << 7  )
#define PLA_ELEM_MUX1_ELEM1            (0x0   << 7  ) /* Feedback from Element 1  */
#define PLA_ELEM_MUX1_ELEM3            (0x1   << 7  ) /* Feedback from Element 3  */
#define PLA_ELEM_MUX1_ELEM5            (0x2   << 7  ) /* Feedback from Element 5  */
#define PLA_ELEM_MUX1_ELEM7            (0x3   << 7  ) /* Feedback from Element 7  */

/* PLA_ELEM[MUX2] - Select between correspondng bit from PLA_DINx register or even feedback mux */
#define PLA_ELEM_MUX2_BBA              (*(volatile unsigned long *) 0x420B0018)
#define PLA_ELEM_MUX2_MSK              (0x1   << 6  )
#define PLA_ELEM_MUX2                  (0x1   << 6  )
#define PLA_ELEM_MUX2_MMR              (0x0   << 6  ) /* PLA_DINx input           */
#define PLA_ELEM_MUX2_EVEN             (0x1   << 6  ) /* Even feedback mux        */

/* PLA_ELEM[MUX3] - Select between GPIO Bus input or odd feedback input (for Elements 16-31 odd feedback is always selected) */
#define PLA_ELEM_MUX3_BBA              (*(volatile unsigned long *) 0x420B0014)
#define PLA_ELEM_MUX3_MSK              (0x1   << 5  )
#define PLA_ELEM_MUX3                  (0x1   << 5  )
#define PLA_ELEM_MUX3_ODD              (0x0   << 5  ) /* odd feedback mux         */
#define PLA_ELEM_MUX3_GPIO             (0x1   << 5  ) /* GPIO input               */

/* PLA_ELEM[TBL] - bit 4,3,2,1 configures output for {mux2_out, mux3_out} = 11,10,01,00 respectively */
#define PLA_ELEM_TBL_MSK               (0xF   << 1  )
#define PLA_ELEM_TBL_LOW               (0x0   << 1  ) /* 0.                       */
#define PLA_ELEM_TBL_NOR               (0x1   << 1  ) /* NOR.                     */
#define PLA_ELEM_TBL_BANDNOTA          (0x2   << 1  ) /* B and not A.             */
#define PLA_ELEM_TBL_NOTA              (0x3   << 1  ) /* NOT A.                   */
#define PLA_ELEM_TBL_AANDNOTB          (0x4   << 1  ) /* A and not B.             */
#define PLA_ELEM_TBL_NOTB              (0x5   << 1  ) /* Not B.                   */
#define PLA_ELEM_TBL_EXOR              (0x6   << 1  ) /* EXOR.                    */
#define PLA_ELEM_TBL_NAND              (0x7   << 1  ) /* NAND.                    */
#define PLA_ELEM_TBL_AND               (0x8   << 1  ) /* AND.                     */
#define PLA_ELEM_TBL_EXNOR             (0x9   << 1  ) /* EXNOR.                   */
#define PLA_ELEM_TBL_B                 (0xA   << 1  ) /* B.                       */
#define PLA_ELEM_TBL_BORNOTA           (0xB   << 1  ) /* B or not A.              */
#define PLA_ELEM_TBL_A                 (0xC   << 1  ) /* A.                       */
#define PLA_ELEM_TBL_AORNOTB           (0xD   << 1  ) /* A or not B.              */
#define PLA_ELEM_TBL_OR                (0xE   << 1  ) /* OR                       */
#define PLA_ELEM_TBL_HIGH              (0xF   << 1  ) /* 1.                       */

/* PLA_ELEM[MUX4] - Select or bypass flip-flop output */
#define PLA_ELEM_MUX4_BBA              (*(volatile unsigned long *) 0x420B0000)
#define PLA_ELEM_MUX4_MSK              (0x1   << 0  )
#define PLA_ELEM_MUX4                  (0x1   << 0  )
#define PLA_ELEM_MUX4_FF               (0x0   << 0  ) /* FF output                */
#define PLA_ELEM_MUX4_BYPASS           (0x1   << 0  ) /* Bypass output            */

/* Reset Value for PLA_CLK*/
#define PLA_CLK_RVAL                   0x0 

/* PLA_CLK[BLOCK3] - Clock select for Block 3 */
#define PLA_CLK_BLOCK3_MSK             (0x7   << 12 )
#define PLA_CLK_BLOCK3_P03             (0x0   << 12 ) /* GPIO clock on P0.3       */
#define PLA_CLK_BLOCK3_P11             (0x1   << 12 ) /* GPIO clock on P1.1       */
#define PLA_CLK_BLOCK3_P20             (0x2   << 12 ) /* GPIO clock on P2.0       */
#define PLA_CLK_BLOCK3_HCLK            (0x3   << 12 ) /* HCLK                     */
#define PLA_CLK_BLOCK3_MOSC            (0x4   << 12 ) /* MOSC (16 MHz)            */
#define PLA_CLK_BLOCK3_T0              (0x5   << 12 ) /* Timer 0                  */
#define PLA_CLK_BLOCK3_T2              (0x6   << 12 ) /* Timer 2                  */
#define PLA_CLK_BLOCK3_KOSC            (0x7   << 12 ) /* KOSC (32 kHz)            */

/* PLA_CLK[BLOCK2] - Clock select for Block 2 */
#define PLA_CLK_BLOCK2_MSK             (0x7   << 8  )
#define PLA_CLK_BLOCK2_P03             (0x0   << 8  ) /* GPIO clock on P0.3       */
#define PLA_CLK_BLOCK2_P11             (0x1   << 8  ) /* GPIO clock on P1.1       */
#define PLA_CLK_BLOCK2_P20             (0x2   << 8  ) /* GPIO clock on P2.0       */
#define PLA_CLK_BLOCK2_HCLK            (0x3   << 8  ) /* HCLK                     */
#define PLA_CLK_BLOCK2_MOSC            (0x4   << 8  ) /* MOSC (16 MHz)            */
#define PLA_CLK_BLOCK2_T0              (0x5   << 8  ) /* Timer 0                  */
#define PLA_CLK_BLOCK2_T2              (0x6   << 8  ) /* Timer 2                  */
#define PLA_CLK_BLOCK2_KOSC            (0x7   << 8  ) /* KOSC (32 kHz)            */

/* PLA_CLK[BLOCK1] - Clock select for Block 1 */
#define PLA_CLK_BLOCK1_MSK             (0x7   << 4  )
#define PLA_CLK_BLOCK1_P03             (0x0   << 4  ) /* GPIO clock on P0.3       */
#define PLA_CLK_BLOCK1_P11             (0x1   << 4  ) /* GPIO clock on P1.1       */
#define PLA_CLK_BLOCK1_P20             (0x2   << 4  ) /* GPIO clock on P2.0       */
#define PLA_CLK_BLOCK1_HCLK            (0x3   << 4  ) /* HCLK                     */
#define PLA_CLK_BLOCK1_MOSC            (0x4   << 4  ) /* MOSC (16 MHz)            */
#define PLA_CLK_BLOCK1_T0              (0x5   << 4  ) /* Timer 0                  */
#define PLA_CLK_BLOCK1_T2              (0x6   << 4  ) /* Timer 2                  */
#define PLA_CLK_BLOCK1_KOSC            (0x7   << 4  ) /* KOSC (32 kHz)            */

/* PLA_CLK[BLOCK0] - Clock select for Block 0 */
#define PLA_CLK_BLOCK0_MSK             (0x7   << 0  )
#define PLA_CLK_BLOCK0_P03             (0x0   << 0  ) /* GPIO clock on P0.3       */
#define PLA_CLK_BLOCK0_P11             (0x1   << 0  ) /* GPIO clock on P1.1       */
#define PLA_CLK_BLOCK0_P20             (0x2   << 0  ) /* GPIO clock on P2.0       */
#define PLA_CLK_BLOCK0_HCLK            (0x3   << 0  ) /* HCLK                     */
#define PLA_CLK_BLOCK0_MOSC            (0x4   << 0  ) /* MOSC (16 MHz)            */
#define PLA_CLK_BLOCK0_T0              (0x5   << 0  ) /* Timer 0                  */
#define PLA_CLK_BLOCK0_T2              (0x6   << 0  ) /* Timer 2                  */
#define PLA_CLK_BLOCK0_KOSC            (0x7   << 0  ) /* KOSC (32 kHz)            */

/* Reset Value for PLA_IRQ0*/
#define PLA_IRQ0_RVAL                  0x0 

/* PLA_IRQ0[irq1_en] - IRQ1 enable */
#define PLA_IRQ0_irq1_en_BBA           (*(volatile unsigned long *) 0x420B10B0)
#define PLA_IRQ0_irq1_en_MSK           (0x1   << 12 )
#define PLA_IRQ0_irq1_en               (0x1   << 12 )
#define PLA_IRQ0_irq1_en_DIS           (0x0   << 12 ) /* disable IRQ1 interrupt   */
#define PLA_IRQ0_irq1_en_EN            (0x1   << 12 ) /* enable IRQ1 interrupt    */

/* PLA_IRQ0[irq1_src] - IRQ1 source select (Elements 0-15). 4-bit value corresponds to element number (e.g. 1011 selects Element 11). */
#define PLA_IRQ0_irq1_src_MSK          (0xF   << 8  )

/* PLA_IRQ0[irq0_en] - IRQ0 enable */
#define PLA_IRQ0_irq0_en_BBA           (*(volatile unsigned long *) 0x420B1090)
#define PLA_IRQ0_irq0_en_MSK           (0x1   << 4  )
#define PLA_IRQ0_irq0_en               (0x1   << 4  )
#define PLA_IRQ0_irq0_en_DIS           (0x0   << 4  ) /* disable IRQ0 interrupt   */
#define PLA_IRQ0_irq0_en_EN            (0x1   << 4  ) /* enable IRQ0 interrupt    */

/* PLA_IRQ0[irq0_src] - IRQ0 source select (Elements 0-15). 4-bit value corresponds to element number (e.g. 1011 selects Element 11). */
#define PLA_IRQ0_irq0_src_MSK          (0xF   << 0  )

/* Reset Value for PLA_IRQ1*/
#define PLA_IRQ1_RVAL                  0x0 

/* PLA_IRQ1[irq3_en] - IRQ3 enable */
#define PLA_IRQ1_irq3_en_BBA           (*(volatile unsigned long *) 0x420B1130)
#define PLA_IRQ1_irq3_en_MSK           (0x1   << 12 )
#define PLA_IRQ1_irq3_en               (0x1   << 12 )
#define PLA_IRQ1_irq3_en_DIS           (0x0   << 12 ) /* disable IRQ3 interrupt   */
#define PLA_IRQ1_irq3_en_EN            (0x1   << 12 ) /* enable IRQ3 interrupt    */

/* PLA_IRQ1[irq3_src] - IRQ3 source select (Elements 16-31) Element number corresponds to 4-bit value + 16 (e.g. 1011 selects Element 27). */
#define PLA_IRQ1_irq3_src_MSK          (0xF   << 8  )

/* PLA_IRQ1[irq2_en] - IRQ2 enable */
#define PLA_IRQ1_irq2_en_BBA           (*(volatile unsigned long *) 0x420B1110)
#define PLA_IRQ1_irq2_en_MSK           (0x1   << 4  )
#define PLA_IRQ1_irq2_en               (0x1   << 4  )
#define PLA_IRQ1_irq2_en_DIS           (0x0   << 4  ) /* disable IRQ2 interrupt   */
#define PLA_IRQ1_irq2_en_EN            (0x1   << 4  ) /* enable IRQ2 interrupt    */

/* PLA_IRQ1[irq2_src] - IRQ2 source select (Elements 16-31). Element number corresponds to 4-bit value + 16 (e.g. 1011 selects Element 27). */
#define PLA_IRQ1_irq2_src_MSK          (0xF   << 0  )

/* Reset Value for PLA_ADC*/
#define PLA_ADC_RVAL                   0x0 

/* PLA_ADC[convst_en] - Bit to enable ADC start convert from PLA */
#define PLA_ADC_convst_en_BBA          (*(volatile unsigned long *) 0x420B1194)
#define PLA_ADC_convst_en_MSK          (0x1   << 5  )
#define PLA_ADC_convst_en              (0x1   << 5  )

/* PLA_ADC[convst_src] - Element for ADC start convert source. The binary value corresponds to the element number. For example Element 23 is 10111 */
#define PLA_ADC_convst_src_MSK         (0x1F  << 0  )

/* Reset Value for PLA_DIN0*/
#define PLA_DIN0_RVAL                  0x0 

/* PLA_DIN0[DIN] -  */
#define PLA_DIN0_DIN_MSK               (0xFFFF << 0  )

/* Reset Value for PLA_DOUT0*/
#define PLA_DOUT0_RVAL                 0x0 

/* PLA_DOUT0[E15] - Output bit from Element 15 */
#define PLA_DOUT0_E15_BBA              (*(volatile unsigned long *) 0x420B133C)
#define PLA_DOUT0_E15_MSK              (0x1   << 15 )
#define PLA_DOUT0_E15                  (0x1   << 15 )
#define PLA_DOUT0_E15_CLR              (0x0   << 15 )
#define PLA_DOUT0_E15_SET              (0x1   << 15 )

/* PLA_DOUT0[E14] - Output bit from Element 14 */
#define PLA_DOUT0_E14_BBA              (*(volatile unsigned long *) 0x420B1338)
#define PLA_DOUT0_E14_MSK              (0x1   << 14 )
#define PLA_DOUT0_E14                  (0x1   << 14 )
#define PLA_DOUT0_E14_CLR              (0x0   << 14 )
#define PLA_DOUT0_E14_SET              (0x1   << 14 )

/* PLA_DOUT0[E13] - Output bit from Element 13 */
#define PLA_DOUT0_E13_BBA              (*(volatile unsigned long *) 0x420B1334)
#define PLA_DOUT0_E13_MSK              (0x1   << 13 )
#define PLA_DOUT0_E13                  (0x1   << 13 )
#define PLA_DOUT0_E13_CLR              (0x0   << 13 )
#define PLA_DOUT0_E13_SET              (0x1   << 13 )

/* PLA_DOUT0[E12] - Output bit from Element 12 */
#define PLA_DOUT0_E12_BBA              (*(volatile unsigned long *) 0x420B1330)
#define PLA_DOUT0_E12_MSK              (0x1   << 12 )
#define PLA_DOUT0_E12                  (0x1   << 12 )
#define PLA_DOUT0_E12_CLR              (0x0   << 12 )
#define PLA_DOUT0_E12_SET              (0x1   << 12 )

/* PLA_DOUT0[E11] - Output bit from Element 11 */
#define PLA_DOUT0_E11_BBA              (*(volatile unsigned long *) 0x420B132C)
#define PLA_DOUT0_E11_MSK              (0x1   << 11 )
#define PLA_DOUT0_E11                  (0x1   << 11 )
#define PLA_DOUT0_E11_CLR              (0x0   << 11 )
#define PLA_DOUT0_E11_SET              (0x1   << 11 )

/* PLA_DOUT0[E10] - Output bit from Element 10 */
#define PLA_DOUT0_E10_BBA              (*(volatile unsigned long *) 0x420B1328)
#define PLA_DOUT0_E10_MSK              (0x1   << 10 )
#define PLA_DOUT0_E10                  (0x1   << 10 )
#define PLA_DOUT0_E10_CLR              (0x0   << 10 )
#define PLA_DOUT0_E10_SET              (0x1   << 10 )

/* PLA_DOUT0[E9] - Output bit from Element 9 */
#define PLA_DOUT0_E9_BBA               (*(volatile unsigned long *) 0x420B1324)
#define PLA_DOUT0_E9_MSK               (0x1   << 9  )
#define PLA_DOUT0_E9                   (0x1   << 9  )
#define PLA_DOUT0_E9_CLR               (0x0   << 9  )
#define PLA_DOUT0_E9_SET               (0x1   << 9  )

/* PLA_DOUT0[E8] - Output bit from Element 8 */
#define PLA_DOUT0_E8_BBA               (*(volatile unsigned long *) 0x420B1320)
#define PLA_DOUT0_E8_MSK               (0x1   << 8  )
#define PLA_DOUT0_E8                   (0x1   << 8  )
#define PLA_DOUT0_E8_CLR               (0x0   << 8  )
#define PLA_DOUT0_E8_SET               (0x1   << 8  )

/* PLA_DOUT0[E7] - Output bit from Element 7 */
#define PLA_DOUT0_E7_BBA               (*(volatile unsigned long *) 0x420B131C)
#define PLA_DOUT0_E7_MSK               (0x1   << 7  )
#define PLA_DOUT0_E7                   (0x1   << 7  )
#define PLA_DOUT0_E7_CLR               (0x0   << 7  )
#define PLA_DOUT0_E7_SET               (0x1   << 7  )

/* PLA_DOUT0[E6] - Output bit from Element 6 */
#define PLA_DOUT0_E6_BBA               (*(volatile unsigned long *) 0x420B1318)
#define PLA_DOUT0_E6_MSK               (0x1   << 6  )
#define PLA_DOUT0_E6                   (0x1   << 6  )
#define PLA_DOUT0_E6_CLR               (0x0   << 6  )
#define PLA_DOUT0_E6_SET               (0x1   << 6  )

/* PLA_DOUT0[E5] - Output bit from Element 5 */
#define PLA_DOUT0_E5_BBA               (*(volatile unsigned long *) 0x420B1314)
#define PLA_DOUT0_E5_MSK               (0x1   << 5  )
#define PLA_DOUT0_E5                   (0x1   << 5  )
#define PLA_DOUT0_E5_CLR               (0x0   << 5  )
#define PLA_DOUT0_E5_SET               (0x1   << 5  )

/* PLA_DOUT0[E4] - Output bit from Element 4 */
#define PLA_DOUT0_E4_BBA               (*(volatile unsigned long *) 0x420B1310)
#define PLA_DOUT0_E4_MSK               (0x1   << 4  )
#define PLA_DOUT0_E4                   (0x1   << 4  )
#define PLA_DOUT0_E4_CLR               (0x0   << 4  )
#define PLA_DOUT0_E4_SET               (0x1   << 4  )

/* PLA_DOUT0[E3] - Output bit from Element 3 */
#define PLA_DOUT0_E3_BBA               (*(volatile unsigned long *) 0x420B130C)
#define PLA_DOUT0_E3_MSK               (0x1   << 3  )
#define PLA_DOUT0_E3                   (0x1   << 3  )
#define PLA_DOUT0_E3_CLR               (0x0   << 3  )
#define PLA_DOUT0_E3_SET               (0x1   << 3  )

/* PLA_DOUT0[E2] - Output bit from Element 2 */
#define PLA_DOUT0_E2_BBA               (*(volatile unsigned long *) 0x420B1308)
#define PLA_DOUT0_E2_MSK               (0x1   << 2  )
#define PLA_DOUT0_E2                   (0x1   << 2  )
#define PLA_DOUT0_E2_CLR               (0x0   << 2  )
#define PLA_DOUT0_E2_SET               (0x1   << 2  )

/* PLA_DOUT0[E1] - Output bit from Element 1 */
#define PLA_DOUT0_E1_BBA               (*(volatile unsigned long *) 0x420B1304)
#define PLA_DOUT0_E1_MSK               (0x1   << 1  )
#define PLA_DOUT0_E1                   (0x1   << 1  )
#define PLA_DOUT0_E1_CLR               (0x0   << 1  )
#define PLA_DOUT0_E1_SET               (0x1   << 1  )

/* PLA_DOUT0[E0] - Output bit from Element 0 */
#define PLA_DOUT0_E0_BBA               (*(volatile unsigned long *) 0x420B1300)
#define PLA_DOUT0_E0_MSK               (0x1   << 0  )
#define PLA_DOUT0_E0                   (0x1   << 0  )
#define PLA_DOUT0_E0_CLR               (0x0   << 0  )
#define PLA_DOUT0_E0_SET               (0x1   << 0  )

/* Reset Value for PLA_DOUT1*/
#define PLA_DOUT1_RVAL                 0x0 

/* PLA_DOUT1[E31] - Output bit from Element 31 */
#define PLA_DOUT1_E31_BBA              (*(volatile unsigned long *) 0x420B13BC)
#define PLA_DOUT1_E31_MSK              (0x1   << 15 )
#define PLA_DOUT1_E31                  (0x1   << 15 )
#define PLA_DOUT1_E31_CLR              (0x0   << 15 )
#define PLA_DOUT1_E31_SET              (0x1   << 15 )

/* PLA_DOUT1[E30] - Output bit from Element 30 */
#define PLA_DOUT1_E30_BBA              (*(volatile unsigned long *) 0x420B13B8)
#define PLA_DOUT1_E30_MSK              (0x1   << 14 )
#define PLA_DOUT1_E30                  (0x1   << 14 )
#define PLA_DOUT1_E30_CLR              (0x0   << 14 )
#define PLA_DOUT1_E30_SET              (0x1   << 14 )

/* PLA_DOUT1[E29] - Output bit from Element 29 */
#define PLA_DOUT1_E29_BBA              (*(volatile unsigned long *) 0x420B13B4)
#define PLA_DOUT1_E29_MSK              (0x1   << 13 )
#define PLA_DOUT1_E29                  (0x1   << 13 )
#define PLA_DOUT1_E29_CLR              (0x0   << 13 )
#define PLA_DOUT1_E29_SET              (0x1   << 13 )

/* PLA_DOUT1[E28] - Output bit from Element 28 */
#define PLA_DOUT1_E28_BBA              (*(volatile unsigned long *) 0x420B13B0)
#define PLA_DOUT1_E28_MSK              (0x1   << 12 )
#define PLA_DOUT1_E28                  (0x1   << 12 )
#define PLA_DOUT1_E28_CLR              (0x0   << 12 )
#define PLA_DOUT1_E28_SET              (0x1   << 12 )

/* PLA_DOUT1[E27] - Output bit from Element 27 */
#define PLA_DOUT1_E27_BBA              (*(volatile unsigned long *) 0x420B13AC)
#define PLA_DOUT1_E27_MSK              (0x1   << 11 )
#define PLA_DOUT1_E27                  (0x1   << 11 )
#define PLA_DOUT1_E27_CLR              (0x0   << 11 )
#define PLA_DOUT1_E27_SET              (0x1   << 11 )

/* PLA_DOUT1[E26] - Output bit from Element 26 */
#define PLA_DOUT1_E26_BBA              (*(volatile unsigned long *) 0x420B13A8)
#define PLA_DOUT1_E26_MSK              (0x1   << 10 )
#define PLA_DOUT1_E26                  (0x1   << 10 )
#define PLA_DOUT1_E26_CLR              (0x0   << 10 )
#define PLA_DOUT1_E26_SET              (0x1   << 10 )

/* PLA_DOUT1[E25] - Output bit from Element 25 */
#define PLA_DOUT1_E25_BBA              (*(volatile unsigned long *) 0x420B13A4)
#define PLA_DOUT1_E25_MSK              (0x1   << 9  )
#define PLA_DOUT1_E25                  (0x1   << 9  )
#define PLA_DOUT1_E25_CLR              (0x0   << 9  )
#define PLA_DOUT1_E25_SET              (0x1   << 9  )

/* PLA_DOUT1[E24] - Output bit from Element 24 */
#define PLA_DOUT1_E24_BBA              (*(volatile unsigned long *) 0x420B13A0)
#define PLA_DOUT1_E24_MSK              (0x1   << 8  )
#define PLA_DOUT1_E24                  (0x1   << 8  )
#define PLA_DOUT1_E24_CLR              (0x0   << 8  )
#define PLA_DOUT1_E24_SET              (0x1   << 8  )

/* PLA_DOUT1[E23] - Output bit from Element 23 */
#define PLA_DOUT1_E23_BBA              (*(volatile unsigned long *) 0x420B139C)
#define PLA_DOUT1_E23_MSK              (0x1   << 7  )
#define PLA_DOUT1_E23                  (0x1   << 7  )
#define PLA_DOUT1_E23_CLR              (0x0   << 7  )
#define PLA_DOUT1_E23_SET              (0x1   << 7  )

/* PLA_DOUT1[E22] - Output bit from Element 22 */
#define PLA_DOUT1_E22_BBA              (*(volatile unsigned long *) 0x420B1398)
#define PLA_DOUT1_E22_MSK              (0x1   << 6  )
#define PLA_DOUT1_E22                  (0x1   << 6  )
#define PLA_DOUT1_E22_CLR              (0x0   << 6  )
#define PLA_DOUT1_E22_SET              (0x1   << 6  )

/* PLA_DOUT1[E21] - Output bit from Element 21 */
#define PLA_DOUT1_E21_BBA              (*(volatile unsigned long *) 0x420B1394)
#define PLA_DOUT1_E21_MSK              (0x1   << 5  )
#define PLA_DOUT1_E21                  (0x1   << 5  )
#define PLA_DOUT1_E21_CLR              (0x0   << 5  )
#define PLA_DOUT1_E21_SET              (0x1   << 5  )

/* PLA_DOUT1[E20] - Output bit from Element 20 */
#define PLA_DOUT1_E20_BBA              (*(volatile unsigned long *) 0x420B1390)
#define PLA_DOUT1_E20_MSK              (0x1   << 4  )
#define PLA_DOUT1_E20                  (0x1   << 4  )
#define PLA_DOUT1_E20_CLR              (0x0   << 4  )
#define PLA_DOUT1_E20_SET              (0x1   << 4  )

/* PLA_DOUT1[E19] - Output bit from Element 19 */
#define PLA_DOUT1_E19_BBA              (*(volatile unsigned long *) 0x420B138C)
#define PLA_DOUT1_E19_MSK              (0x1   << 3  )
#define PLA_DOUT1_E19                  (0x1   << 3  )
#define PLA_DOUT1_E19_CLR              (0x0   << 3  )
#define PLA_DOUT1_E19_SET              (0x1   << 3  )

/* PLA_DOUT1[E18] - Output bit from Element 18 */
#define PLA_DOUT1_E18_BBA              (*(volatile unsigned long *) 0x420B1388)
#define PLA_DOUT1_E18_MSK              (0x1   << 2  )
#define PLA_DOUT1_E18                  (0x1   << 2  )
#define PLA_DOUT1_E18_CLR              (0x0   << 2  )
#define PLA_DOUT1_E18_SET              (0x1   << 2  )

/* PLA_DOUT1[E17] - Output bit from Element 17 */
#define PLA_DOUT1_E17_BBA              (*(volatile unsigned long *) 0x420B1384)
#define PLA_DOUT1_E17_MSK              (0x1   << 1  )
#define PLA_DOUT1_E17                  (0x1   << 1  )
#define PLA_DOUT1_E17_CLR              (0x0   << 1  )
#define PLA_DOUT1_E17_SET              (0x1   << 1  )

/* PLA_DOUT1[E16] - Output bit from Element 16 */
#define PLA_DOUT1_E16_BBA              (*(volatile unsigned long *) 0x420B1380)
#define PLA_DOUT1_E16_MSK              (0x1   << 0  )
#define PLA_DOUT1_E16                  (0x1   << 0  )
#define PLA_DOUT1_E16_CLR              (0x0   << 0  )
#define PLA_DOUT1_E16_SET              (0x1   << 0  )

/* Reset Value for PLA_LCK*/
#define PLA_LCK_RVAL                   0x0 

/* PLA_LCK[LOCK] - Set to disable writing to registers */
#define PLA_LCK_LOCK_BBA               (*(volatile unsigned long *) 0x420B1400)
#define PLA_LCK_LOCK_MSK               (0x1   << 0  )
#define PLA_LCK_LOCK                   (0x1   << 0  )
#define PLA_LCK_LOCK_DIS               (0x0   << 0  ) /* Writing to registers allowed */
#define PLA_LCK_LOCK_EN                (0x1   << 0  ) /* Writing to registers disabled */

#if defined(ADUCM320I) | defined(ADUCM322) | defined(ADUCM322I)

/* Reset Value for PLA_PROBE_I2C*/
#define PLA_PROBE_I2C_RVAL             0x0 

/* PLA_PROBE_I2C[ELEM3] - Connects either GPIO or I2C as the GPIO input to BLOCK 0 element 3 */
#define PLA_PROBE_I2C_ELEM3_BBA        (*(volatile unsigned long *) 0x420B148C)
#define PLA_PROBE_I2C_ELEM3_MSK        (0x1   << 3  )
#define PLA_PROBE_I2C_ELEM3            (0x1   << 3  )
#define PLA_PROBE_I2C_ELEM3_P0_3       (0x0   << 3  ) /* PLA PROBE GPIO P0.3      */
#define PLA_PROBE_I2C_ELEM3_I2C1_SDA   (0x1   << 3  ) /* PLA PROBE I2C1_SDA       */

/* PLA_PROBE_I2C[ELEM2] - Connects either GPIO or I2C as the GPIO input to BLOCK 0 element 2 */
#define PLA_PROBE_I2C_ELEM2_BBA        (*(volatile unsigned long *) 0x420B1488)
#define PLA_PROBE_I2C_ELEM2_MSK        (0x1   << 2  )
#define PLA_PROBE_I2C_ELEM2            (0x1   << 2  )
#define PLA_PROBE_I2C_ELEM2_P0_2       (0x0   << 2  ) /* PLA PROBE GPIO P0.2      */
#define PLA_PROBE_I2C_ELEM2_I2C1_SCL   (0x1   << 2  ) /* PLA PROBE I2C1_SCL       */

/* PLA_PROBE_I2C[ELEM1] - Connects either GPIO or I2C as the GPIO input to BLOCK 0 element 1 */
#define PLA_PROBE_I2C_ELEM1_BBA        (*(volatile unsigned long *) 0x420B1484)
#define PLA_PROBE_I2C_ELEM1_MSK        (0x1   << 1  )
#define PLA_PROBE_I2C_ELEM1            (0x1   << 1  )
#define PLA_PROBE_I2C_ELEM1_P0_1       (0x0   << 1  ) /* PLA PROBE GPIO P0.1      */
#define PLA_PROBE_I2C_ELEM1_I2C0_SDA   (0x1   << 1  ) /* PLA PROBE I2C0_SDA       */

/* PLA_PROBE_I2C[ELEM0] - Connects either GPIO or I2C as the GPIO input to BLOCK 0 element 0 */
#define PLA_PROBE_I2C_ELEM0_BBA        (*(volatile unsigned long *) 0x420B1480)
#define PLA_PROBE_I2C_ELEM0_MSK        (0x1   << 0  )
#define PLA_PROBE_I2C_ELEM0            (0x1   << 0  )
#define PLA_PROBE_I2C_ELEM0_P0_0       (0x0   << 0  ) /* PLA PROBE GPIO P0.0      */
#define PLA_PROBE_I2C_ELEM0_I2C0_SCL   (0x1   << 0  ) /* PLA PROBE I2C0_SCL       */

#endif


// ------------------------------------------------------------------------------------------------
// -----                                        dma                                        -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief DMA (MMR_DMA)
  */

typedef struct MMR_DMA {                    /*!< MMR_DMA Structure                     */
  __IO uint32_t  DMASTA;                    /*!< DMA Status                            */
  __IO uint32_t  DMACFG;                    /*!< DMA Configuration                     */
  __IO uint32_t  DMAPDBPTR;                 /*!< DMA channel primary control data base pointer */
  __IO uint32_t  DMAADBPTR;                 /*!< DMA channel alternate control data base pointer */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  DMASWREQ;                  /*!< DMA channel software request          */
  __I  uint32_t  RESERVED1[2];
  __IO uint32_t  DMARMSKSET;                /*!< DMA channel request mask set          */
  __IO uint32_t  DMARMSKCLR;                /*!< DMA channel request mask clear        */
  __IO uint32_t  DMAENSET;                  /*!< DMA channel enable set                */
  __IO uint32_t  DMAENCLR;                  /*!< DMA channel enable clear              */
  __IO uint32_t  DMAALTSET;                 /*!< DMA channel primary-alternate set     */
  __IO uint32_t  DMAALTCLR;                 /*!< DMA channel primary-alternate clear   */
  __IO uint32_t  DMAPRISET;                 /*!< DMA channel priority set              */
  __IO uint32_t  DMAPRICLR;                 /*!< DMA channel priority clear            */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  DMAERRCLR;                 /*!< DMA Per Channel Bus Error             */
  __I  uint32_t  RESERVED3[492];
  __IO uint32_t  DMABSSET;                  /*!< DMA channel bytes swap enable set     */
  __IO uint32_t  DMABSCLR;                  /*!< DMA channel bytes swap enable clear   */
} MMR_DMA_t;

/* Reset Value for DMASTA*/
#define DMASTA_RVAL                    0xF0000 

/* DMASTA[CHNLSM1] - Number of available DMA channels minus 1 */
#define DMASTA_CHNLSM1_MSK             (0x1F  << 16 )

/* DMASTA[STATE] - Current state of DMA controller */
#define DMASTA_STATE_MSK               (0xF   << 4  )

/* DMASTA[MENABLE] - Enable status of the controller */
#define DMASTA_MENABLE_BBA             (*(volatile unsigned long *) 0x42200000)
#define DMASTA_MENABLE_MSK             (0x1   << 0  )
#define DMASTA_MENABLE                 (0x1   << 0  )

/* Reset Value for DMACFG*/
#define DMACFG_RVAL                    0x0 

/* DMACFG[MENABLE] - Controller enable */
#define DMACFG_MENABLE_BBA             (*(volatile unsigned long *) 0x42200080)
#define DMACFG_MENABLE_MSK             (0x1   << 0  )
#define DMACFG_MENABLE                 (0x1   << 0  )

/* Reset Value for DMAPDBPTR*/
#define DMAPDBPTR_RVAL                 0x0 

/* DMAPDBPTR[CTRLBASEPTR] - Pointer to the base address of the primary data structure */
#define DMAPDBPTR_CTRLBASEPTR_MSK      (0xFFFFFFFF << 0  )

/* Reset Value for DMAADBPTR*/
#define DMAADBPTR_RVAL                 0x100 

/* DMAADBPTR[ALTCBPTR] - Base address of the alternate data structure */
#define DMAADBPTR_ALTCBPTR_MSK         (0xFFFFFFFF << 0  )

/* Reset Value for DMASWREQ*/
#define DMASWREQ_RVAL                  0x0 

/* DMASWREQ[CHSWREQ] - Generate software request */
#define DMASWREQ_CHSWREQ_MSK           (0x3FFF << 0  )

/* Reset Value for DMARMSKSET*/
#define DMARMSKSET_RVAL                0x0 

/* DMARMSKSET[CHREQMSET] - Mask requests from DMA channels */
#define DMARMSKSET_CHREQMSET_MSK       (0x3FFF << 0  )

/* Reset Value for DMARMSKCLR*/
#define DMARMSKCLR_RVAL                0x0 

/* DMARMSKCLR[CHREQMCLR] - Clear REQ_MASK_SET bits in DMARMSKSET */
#define DMARMSKCLR_CHREQMCLR_MSK       (0x3FFF << 0  )

/* Reset Value for DMAENSET*/
#define DMAENSET_RVAL                  0x0 

/* DMAENSET[CHENSET] - Enable DMA channels */
#define DMAENSET_CHENSET_MSK           (0x3FFF << 0  )

/* Reset Value for DMAENCLR*/
#define DMAENCLR_RVAL                  0x0 

/* DMAENCLR[CHENCLR] - Disable DMA channels */
#define DMAENCLR_CHENCLR_MSK           (0x3FFF << 0  )

/* Reset Value for DMAALTSET*/
#define DMAALTSET_RVAL                 0x0 

/* DMAALTSET[CHPRIALTSET] - Control struct status / select alt struct */
#define DMAALTSET_CHPRIALTSET_MSK      (0x3FFF << 0  )

/* Reset Value for DMAALTCLR*/
#define DMAALTCLR_RVAL                 0x0 

/* DMAALTCLR[CHPRIALTCLR] - Select primary data struct */
#define DMAALTCLR_CHPRIALTCLR_MSK      (0x3FFF << 0  )

/* Reset Value for DMAPRISET*/
#define DMAPRISET_RVAL                 0x0 

/* DMAPRISET[CHPRISET] - Configure channel for high priority */
#define DMAPRISET_CHPRISET_MSK         (0x3FFF << 0  )

/* Reset Value for DMAPRICLR*/
#define DMAPRICLR_RVAL                 0x0 

/* DMAPRICLR[CHPRICLR] - Configure channel for default priority level */
#define DMAPRICLR_CHPRICLR_MSK         (0x3FFF << 0  )

/* Reset Value for DMAERRCLR*/
#define DMAERRCLR_RVAL                 0x0 

/* DMAERRCLR[ERRCLR] - Bus error status */
#define DMAERRCLR_ERRCLR_MSK           (0x3FFF << 0  )

/* Reset Value for DMABSSET*/
#define DMABSSET_RVAL                  0x0 

/* DMABSSET[CHBSWAPSET] - Byte swap status */
#define DMABSSET_CHBSWAPSET_MSK        (0x3FFF << 0  )

/* Reset Value for DMABSCLR*/
#define DMABSCLR_RVAL                  0x0 

/* DMABSCLR[CHBSWAPCLR] - Disable byte swap */
#define DMABSCLR_CHBSWAPCLR_MSK        (0x3FFF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        FEE                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief FEE (MMR_FEE)
  */

typedef struct MMR_FEE {                    /*!< MMR_FEE Structure                     */
  __IO uint32_t  FEESTA;                    /*!< Status register                       */
  __IO uint32_t  FEECON0;                   /*!< Command Control register: interrupt enable register */
  __IO uint32_t  FEECMD;                    /*!< Command register                      */
  __IO uint32_t  FEEFLADR;                  /*!< Flash address key - hole register     */
  __IO uint32_t  FEEFLDATA0;                /*!< Flash Data register: key-hole interface lower 32 bits */
  __IO uint32_t  FEEFLDATA1;                /*!< Flash Data register: key-hole interface upper 32 bits */
  __IO uint32_t  FEEADR0;                   /*!< Lower page address register           */
  __IO uint32_t  FEEADR1;                   /*!< Upper page address register           */
  __IO uint32_t  FEEKEY;                    /*!< Flash Key register.                   */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  FEEPRO0;                   /*!< write protection register for flash0  */
  __IO uint32_t  FEEPRO1;                   /*!< write protection register for flash1  */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  FEESIG;                    /*!< Flash Signature                       */
  __IO uint32_t  FEECON1;                   /*!< User Setup register                   */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  FEEWRADDRA;                /*!< write abort address register          */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  FEEAEN0;                   /*!< Interrupt abort enable register. Interrupt 31 to Interrupt 0. */
  __IO uint32_t  FEEAEN1;                   /*!< Interrupt abort enable register. Interrupt 54 to Interrupt 32. */
  __I  uint32_t  RESERVED4[5];
  __IO uint32_t  FEEECCCONFIG;              /*!< Configurable ECC enable/disable, error response */
  __I  uint32_t  RESERVED5[3];
  __IO uint32_t  FEEECCADDR0;               /*!< Flash 0 ECC Error Address             */
  __IO uint32_t  FEEECCADDR1;               /*!< Flash 1 ECC Error Address             */
  __I  uint32_t  RESERVED6[17];
  __IO uint32_t  CACHESTAT;                 /*!< Cache Status register                 */
  __IO uint32_t  CACHESETUP;                /*!< Cache Setup register                  */
  __IO uint32_t  CACHEKEY;                  /*!< Cache Key register                    */
} MMR_FEE_t;

/* Reset Value for FEESTA*/
#define FEESTA_RVAL                    0x0 

/* FEESTA[INIT] - Initialization upload in progress. */
#define FEESTA_INIT_BBA                (*(volatile unsigned long *) 0x42300038)
#define FEESTA_INIT_MSK                (0x1   << 14 )
#define FEESTA_INIT                    (0x1   << 14 )
#define FEESTA_INIT_CLR                (0x0   << 14 )
#define FEESTA_INIT_SET                (0x1   << 14 )

/* FEESTA[SIGNERR] - Information space signature check on reset error. */
#define FEESTA_SIGNERR_BBA             (*(volatile unsigned long *) 0x42300034)
#define FEESTA_SIGNERR_MSK             (0x1   << 13 )
#define FEESTA_SIGNERR                 (0x1   << 13 )
#define FEESTA_SIGNERR_CLR             (0x0   << 13 )
#define FEESTA_SIGNERR_SET             (0x1   << 13 )

/* FEESTA[CMDRES] - These two bits indicate the status of a command on completion or the status of a write. */
#define FEESTA_CMDRES_MSK              (0x3   << 4  )
#define FEESTA_CMDRES_SUCCESS          (0x0   << 4  ) /* Successful completion of a command or a write */
#define FEESTA_CMDRES_IGNORED          (0x1   << 4  ) /* Attempted signcheck, write or erase of a protected location. */
#define FEESTA_CMDRES_READERROR        (0x2   << 4  ) /* Read verify error. After an erase the controller reads the corresponding word(s) to verify that the transaction completed successfully. If data read is not all 'F's this is the resulting status.If the Sign command is executed and the resulting signature does not match the data in the upper 4 bytes of the upper page in a block then this is the resulting status. */
#define FEESTA_CMDRES_ABORTED          (0x3   << 4  ) /* Indicates that a command or a write was aborted by an abort command or a system interrupt has caused an abort */

/* FEESTA[WRALMOSTDONE] - Write almost Complete - key-hole registers open for access. This bit flags the earliest point at which the flash controller data and address may be updated for the next command without affecting an active flash command operation. */
#define FEESTA_WRALMOSTDONE_BBA        (*(volatile unsigned long *) 0x4230000C)
#define FEESTA_WRALMOSTDONE_MSK        (0x1   << 3  )
#define FEESTA_WRALMOSTDONE            (0x1   << 3  )
#define FEESTA_WRALMOSTDONE_CLR        (0x0   << 3  ) /* Cleared to 0 when read   */
#define FEESTA_WRALMOSTDONE_SET        (0x1   << 3  ) /* Set to 1 when a write completes */

/* FEESTA[CMDDONE] - This bit asserts when a command completes. */
#define FEESTA_CMDDONE_BBA             (*(volatile unsigned long *) 0x42300008)
#define FEESTA_CMDDONE_MSK             (0x1   << 2  )
#define FEESTA_CMDDONE                 (0x1   << 2  )
#define FEESTA_CMDDONE_CLR             (0x0   << 2  ) /* Cleared to 0 when read   */
#define FEESTA_CMDDONE_SET             (0x1   << 2  ) /* Set to 1 when a command completes */

/* FEESTA[WRCLOSE] - This bit is asserted when the user has written all key-hole registers for flash write and the controller has started the write. */
#define FEESTA_WRCLOSE_BBA             (*(volatile unsigned long *) 0x42300004)
#define FEESTA_WRCLOSE_MSK             (0x1   << 1  )
#define FEESTA_WRCLOSE                 (0x1   << 1  )
#define FEESTA_WRCLOSE_CLR             (0x0   << 1  )
#define FEESTA_WRCLOSE_SET             (0x1   << 1  )

/* FEESTA[CMDBUSY] - Command busy. */
#define FEESTA_CMDBUSY_BBA             (*(volatile unsigned long *) 0x42300000)
#define FEESTA_CMDBUSY_MSK             (0x1   << 0  )
#define FEESTA_CMDBUSY                 (0x1   << 0  )
#define FEESTA_CMDBUSY_CLR             (0x0   << 0  )
#define FEESTA_CMDBUSY_SET             (0x1   << 0  )

/* Reset Value for FEECON0*/
#define FEECON0_RVAL                   0x0 

/* FEECON0[IENERR] - Command fail interrupt enable */
#define FEECON0_IENERR_BBA             (*(volatile unsigned long *) 0x42300088)
#define FEECON0_IENERR_MSK             (0x1   << 2  )
#define FEECON0_IENERR                 (0x1   << 2  )
#define FEECON0_IENERR_DIS             (0x0   << 2  ) /* Disable                  */
#define FEECON0_IENERR_EN              (0x1   << 2  ) /* Enable                   */

/* FEECON0[IWRALCOMP] - Write almost complete interrupt enable */
#define FEECON0_IWRALCOMP_BBA          (*(volatile unsigned long *) 0x42300084)
#define FEECON0_IWRALCOMP_MSK          (0x1   << 1  )
#define FEECON0_IWRALCOMP              (0x1   << 1  )
#define FEECON0_IWRALCOMP_DIS          (0x0   << 1  ) /* Disable                  */
#define FEECON0_IWRALCOMP_EN           (0x1   << 1  ) /* Enable                   */

/* FEECON0[IENCMD] - Command complete interrupt enable */
#define FEECON0_IENCMD_BBA             (*(volatile unsigned long *) 0x42300080)
#define FEECON0_IENCMD_MSK             (0x1   << 0  )
#define FEECON0_IENCMD                 (0x1   << 0  )
#define FEECON0_IENCMD_DIS             (0x0   << 0  ) /* Disable                  */
#define FEECON0_IENCMD_EN              (0x1   << 0  ) /* Enable                   */

/* Reset Value for FEECMD*/
#define FEECMD_RVAL                    0x0 

/* FEECMD[CMD] - Commands */
#define FEECMD_CMD_MSK                 (0x1F  << 0  )
#define FEECMD_CMD_IDLE                (0x0   << 0  ) /* IDLE. No command executed. */
#define FEECMD_CMD_PAGEERASE           (0x1   << 0  ) /* PAGEERASE. Write the address of the page to be erased to the FEEADR0 register, then write this code to the FEECMD and the flash will erase the page. When the erase has completed the flash will read every location in the page to verify all words in the page are erased.  If there is a read verify error this will be indicated in the Status register.  To erase multiple pages wait until a previous page erase has completed - check the status then issue a command to start the next page erase.  Before entering this command  0xF123F456 must first be written to the FEEKEY register. */
#define FEECMD_CMD_SIGN                (0x2   << 0  ) /* SIGN. Use this command to generate a signature for a block of data.  The signature is generated on a page by page basis.  To generate a signature the address of the first page of the block is entered in the FEEADR0 register, the address of the last page is written to the FEEADR1 register, then write this code to the FEECMD register.  When the command has completed the signature is available for reading in the Sign register.  The last 4 bytes of the last page in a block is reserved for storing the signature. Before entering this command 0xF123F456 must first be written to the FEEKEY register. */
#define FEECMD_CMD_WRITE               (0x4   << 0  ) /* WRITE. Use this command to write to flash locations. This command needs a UserKey for writing into write protection location and userfaakey location. No key is required for other flash locations. This command takes the address, data from FEEADR, FEEFLDATA key-hole registers. */
#define FEECMD_CMD_MASSERASE0          (0x5   << 0  ) /* MASSERASE0. Erase all of flash0 user space. To enable this operation 0xF123F456 must first be written to the FEEKEY register (this is to prevent accidental erases).  When the mass erase has completed the controller will read every location to verify that all locations are 0xFFFFFFFFFFFFFFFF.  If there is a read verify error this will be indicated in the Status register. */
#define FEECMD_CMD_MASSERASE1          (0x6   << 0  ) /* MASSERASE1. Erase all of flash1 user space. To enable this operation 0xF123F456 must first be written to the FEEKEY register (this is to prevent accidental erases).  When the mass erase has completed the controller will read every location to verify that all locations are 0xFFFFFFFFFFFFFFFF.  If there is a read verify error this will be indicated in the Status register. */
#define FEECMD_CMD_ABORT               (0x8   << 0  ) /* ABORT. If this command is issued then any command currently in progress will be stopped.  The status will indicate command completed with an error status (FEESTA[5:4] = 0x3).  Note that this is the only command that can be issued while another command is already in progress.  This command can also be used to stop a write that may be in progress. If a write or erase is aborted then the flash timing will be violated and it is not possible to determine if the write or erase completed successfully.  To enable this operation 0xF123F456 must first be written to the FEEKEY register (this is to prevent accidental aborts). */

/* Reset Value for FEEFLADR*/
#define FEEFLADR_RVAL                  0x0 

/* FEEFLADR[FLAddr] - Memory mapped address for the flash location */
#define FEEFLADR_FLAddr_MSK            (0xFFFF << 3  )

/* Reset Value for FEEFLDATA0*/
#define FEEFLDATA0_RVAL                0x0 

/* FEEFLDATA0[FLDATA0] - FLDATA0 forms the lower 32 bit of 64 bit data to be written to flash */
#define FEEFLDATA0_FLDATA0_MSK         (0xFFFFFFFF << 0  )

/* Reset Value for FEEFLDATA1*/
#define FEEFLDATA1_RVAL                0x0 

/* FEEFLDATA1[FLDATA1] - FLDATA1 forms the upper 32 bit of 64 bit data to be written to flash */
#define FEEFLDATA1_FLDATA1_MSK         (0xFFFFFFFF << 0  )

/* Reset Value for FEEADR0*/
#define FEEADR0_RVAL                   0x0 

/* FEEADR0[PageAddr0] - Used by SIGN and PAGEERASE commands for specifying page address. See the description of these commands in FEECMD */
#define FEEADR0_PageAddr0_MSK          (0xFF  << 11 )

/* Reset Value for FEEADR1*/
#define FEEADR1_RVAL                   0x0 

/* FEEADR1[PageAddr1] - Used by SIGN command for specifying the end page address. See description of this command in FEECMD */
#define FEEADR1_PageAddr1_MSK          (0xFF  << 11 )

/* Reset Value for FEEKEY*/
#define FEEKEY_RVAL                    0x0 

/* FEEKEY[KEY] - Enter 0xF123F456 to allow key protected operations. Returns 0x0 if read. */
#define FEEKEY_KEY_MSK                 (0xFFFFFFFF << 0  )

/* Reset Value for FEEPRO0*/
#define FEEPRO0_RVAL                   0xFFFFFFFF 

/* FEEPRO0[WrProt0] - Write protection for flash0 - 32 bits. */
#define FEEPRO0_WrProt0_MSK            (0xFFFFFFFF << 0  )

/* Reset Value for FEEPRO1*/
#define FEEPRO1_RVAL                   0xFFFFFFFF 

/* FEEPRO1[WrProt1] - Write protection for flash1 - 32 bits. */
#define FEEPRO1_WrProt1_MSK            (0xFFFFFFFF << 0  )

/* Reset Value for FEESIG*/
#define FEESIG_RVAL                    0x0 

/* FEESIG[SIGN] - 24 bit signature. */
#define FEESIG_SIGN_MSK                (0xFFFFFF << 0  )

/* Reset Value for FEECON1*/
#define FEECON1_RVAL                   0x1 

/* FEECON1[MDIO] - MDIO mode */
#define FEECON1_MDIO_BBA               (*(volatile unsigned long *) 0x42300710)
#define FEECON1_MDIO_MSK               (0x1   << 4  )
#define FEECON1_MDIO                   (0x1   << 4  )
#define FEECON1_MDIO_DIS               (0x0   << 4  )
#define FEECON1_MDIO_EN                (0x1   << 4  )

/* FEECON1[SWAP] - Swap program code for MDIO mode. */
#define FEECON1_SWAP_BBA               (*(volatile unsigned long *) 0x4230070C)
#define FEECON1_SWAP_MSK               (0x1   << 3  )
#define FEECON1_SWAP                   (0x1   << 3  )
#define FEECON1_SWAP_DIS               (0x0   << 3  )
#define FEECON1_SWAP_EN                (0x1   << 3  )

/* FEECON1[INCR] - Auto increment FEEFLAADR for non DMA operation. */
#define FEECON1_INCR_BBA               (*(volatile unsigned long *) 0x42300708)
#define FEECON1_INCR_MSK               (0x1   << 2  )
#define FEECON1_INCR                   (0x1   << 2  )
#define FEECON1_INCR_DIS               (0x0   << 2  ) /* Disable auto address increment */
#define FEECON1_INCR_EN                (0x1   << 2  ) /* Enable auto address increment */

/* FEECON1[KHDMA] - Key-hole DMA enable. */
#define FEECON1_KHDMA_BBA              (*(volatile unsigned long *) 0x42300704)
#define FEECON1_KHDMA_MSK              (0x1   << 1  )
#define FEECON1_KHDMA                  (0x1   << 1  )
#define FEECON1_KHDMA_DIS              (0x0   << 1  ) /* Disable DMA mode         */
#define FEECON1_KHDMA_EN               (0x1   << 1  ) /* Enable DMA mode          */

/* FEECON1[DBG] - JTAG debug enable */
#define FEECON1_DBG_BBA                (*(volatile unsigned long *) 0x42300700)
#define FEECON1_DBG_MSK                (0x1   << 0  )
#define FEECON1_DBG                    (0x1   << 0  )
#define FEECON1_DBG_DIS                (0x0   << 0  ) /* Disable JTAG access      */
#define FEECON1_DBG_EN                 (0x1   << 0  ) /* Enable JTAG access       */

/* Reset Value for FEEWRADDRA*/
#define FEEWRADDRA_RVAL                0x0 

/* FEEWRADDRA[WrAbortAddr] - If a write is aborted then this will contain the address of the location been written when the write was aborted. This register has appropriate value if command abort happened. This has to be read after the command is aborted. And this has to be read before any other command is given. After reset the value will be random. */
#define FEEWRADDRA_WrAbortAddr_MSK     (0xFFFFFFFF << 0  )

/* Reset Value for FEEAEN0*/
#define FEEAEN0_RVAL                   0x0 

/* FEEAEN0[SysIrqAbortEn] - Lower 32 bits of System Interrupt Abort Enable. To allow a system interrupt to abort a command (write, erase, sign or mass verify) then write a '1' to the appropriate bit in this register. */
#define FEEAEN0_SysIrqAbortEn_MSK      (0xFFFFFFFF << 0  )

/* Reset Value for FEEAEN1*/
#define FEEAEN1_RVAL                   0x0 

/* FEEAEN1[SysIrqAbortEn] - Upper 23 bits of System Interrupt Abort Enable. To allow a system interrupt to abort a command (write, erase, sign or mass verify) then write a '1' to the appropriate bit in this register. */
#define FEEAEN1_SysIrqAbortEn_MSK      (0x7FFFFF << 0  )

/* Reset Value for FEEECCCONFIG*/
#define FEEECCCONFIG_RVAL              0x0 

/* FEEECCCONFIG[INT] - Interrupt enable when a ECC error happens during an AHB read from program or data flash. */
#define FEEECCCONFIG_INT_MSK           (0x3   << 3  )

/* FEEECCCONFIG[FAULT] - Signifies when to generate AHB error (HRESP = 1) when an ECC error happens - 1 bit error or 2 bit error. */
#define FEEECCCONFIG_FAULT_MSK         (0x3   << 1  )

/* FEEECCCONFIG[DIS] - ECC Disable bit. */
#define FEEECCCONFIG_DIS_BBA           (*(volatile unsigned long *) 0x42300C80)
#define FEEECCCONFIG_DIS_MSK           (0x1   << 0  )
#define FEEECCCONFIG_DIS               (0x1   << 0  )
#define FEEECCCONFIG_DIS_DIS           (0x0   << 0  )
#define FEEECCCONFIG_DIS_EN            (0x1   << 0  )

/* Reset Value for FEEECCADDR0*/
#define FEEECCADDR0_RVAL               0x0 

/* FEEECCADDR0[ADDR0] - This register has the address of flash0 for which ECC error is detected. */
#define FEEECCADDR0_ADDR0_MSK          (0x7FFFF << 0  )

/* Reset Value for FEEECCADDR1*/
#define FEEECCADDR1_RVAL               0x0 

/* FEEECCADDR1[ADDR1] - This register has the address of flash1 for which ECC error is detected. */
#define FEEECCADDR1_ADDR1_MSK          (0x7FFFF << 0  )

/* Reset Value for CACHESTAT*/
#define CACHESTAT_RVAL                 0x2 

/* CACHESTAT[DLOCK] - This bit is set when D-Cache is locked and cleared when D-cache is unlocked. */
#define CACHESTAT_DLOCK_BBA            (*(volatile unsigned long *) 0x42301848)
#define CACHESTAT_DLOCK_MSK            (0x1   << 18 )
#define CACHESTAT_DLOCK                (0x1   << 18 )
#define CACHESTAT_DLOCK_CLR            (0x0   << 18 )
#define CACHESTAT_DLOCK_SET            (0x1   << 18 )

/* CACHESTAT[DEN] - If this bit is set then D-Cache is enabled and when cleared D-Cache is disabled. This is also cleared when CACHESTAT[16] is set. */
#define CACHESTAT_DEN_BBA              (*(volatile unsigned long *) 0x42301844)
#define CACHESTAT_DEN_MSK              (0x1   << 17 )
#define CACHESTAT_DEN                  (0x1   << 17 )
#define CACHESTAT_DEN_CLR              (0x0   << 17 )
#define CACHESTAT_DEN_SET              (0x1   << 17 )

/* CACHESTAT[DINIT] - It is set when D-cache memory initialization starts and clears when initialization is done. D-Cache is disabled when this bit is set. */
#define CACHESTAT_DINIT_BBA            (*(volatile unsigned long *) 0x42301840)
#define CACHESTAT_DINIT_MSK            (0x1   << 16 )
#define CACHESTAT_DINIT                (0x1   << 16 )
#define CACHESTAT_DINIT_CLR            (0x0   << 16 )
#define CACHESTAT_DINIT_SET            (0x1   << 16 )

/* CACHESTAT[ILOCK] - This bit is set when I-Cache is locked and cleared when I-cache is unlocked. */
#define CACHESTAT_ILOCK_BBA            (*(volatile unsigned long *) 0x42301808)
#define CACHESTAT_ILOCK_MSK            (0x1   << 2  )
#define CACHESTAT_ILOCK                (0x1   << 2  )
#define CACHESTAT_ILOCK_CLR            (0x0   << 2  )
#define CACHESTAT_ILOCK_SET            (0x1   << 2  )

/* CACHESTAT[IEN] - If this bit is set then I-Cache is enabled and when cleared I-Cache is disabled. This is also cleared when CACHESTAT[0] is set. */
#define CACHESTAT_IEN_BBA              (*(volatile unsigned long *) 0x42301804)
#define CACHESTAT_IEN_MSK              (0x1   << 1  )
#define CACHESTAT_IEN                  (0x1   << 1  )
#define CACHESTAT_IEN_CLR              (0x0   << 1  )
#define CACHESTAT_IEN_SET              (0x1   << 1  )

/* CACHESTAT[IINIT] - It is set when I-cache memory initialization starts and clears when initialization is done. I-Cache is disabled when this bit is set. */
#define CACHESTAT_IINIT_BBA            (*(volatile unsigned long *) 0x42301800)
#define CACHESTAT_IINIT_MSK            (0x1   << 0  )
#define CACHESTAT_IINIT                (0x1   << 0  )
#define CACHESTAT_IINIT_CLR            (0x0   << 0  )
#define CACHESTAT_IINIT_SET            (0x1   << 0  )

/* Reset Value for CACHESETUP*/
#define CACHESETUP_RVAL                0x2 

/* CACHESETUP[DWRBUF] - If this bit is set, then for every AHB access, hit from WrBuffer is not checked. */
#define CACHESETUP_DWRBUF_BBA          (*(volatile unsigned long *) 0x423018CC)
#define CACHESETUP_DWRBUF_MSK          (0x1   << 19 )
#define CACHESETUP_DWRBUF              (0x1   << 19 )
#define CACHESETUP_DWRBUF_EN           (0x0   << 19 )
#define CACHESETUP_DWRBUF_DIS          (0x1   << 19 )

/* CACHESETUP[DLOCK] - If this bit is set, then D-cache contents are locked. Any new misses will not be replaced in D-Cache. This bit is cleared when CACHESETUP[16] is set. */
#define CACHESETUP_DLOCK_BBA           (*(volatile unsigned long *) 0x423018C8)
#define CACHESETUP_DLOCK_MSK           (0x1   << 18 )
#define CACHESETUP_DLOCK               (0x1   << 18 )
#define CACHESETUP_DLOCK_DIS           (0x0   << 18 )
#define CACHESETUP_DLOCK_EN            (0x1   << 18 )

/* CACHESETUP[DEN] - If this bit set, then D-Cache is enabled for AHB accesses. If 0, then D-cache is disabled, and all AHB accesses will be via Flash memory. This bit is cleared when CACHESETUP[16] is set. */
#define CACHESETUP_DEN_BBA             (*(volatile unsigned long *) 0x423018C4)
#define CACHESETUP_DEN_MSK             (0x1   << 17 )
#define CACHESETUP_DEN                 (0x1   << 17 )
#define CACHESETUP_DEN_DIS             (0x0   << 17 )
#define CACHESETUP_DEN_EN              (0x1   << 17 )

/* CACHESETUP[DINIT] - If this bit is set then the D-cache contents are initialized to all zeros. This bit will be cleared once the initialization starts. */
#define CACHESETUP_DINIT_BBA           (*(volatile unsigned long *) 0x423018C0)
#define CACHESETUP_DINIT_MSK           (0x1   << 16 )
#define CACHESETUP_DINIT               (0x1   << 16 )
#define CACHESETUP_DINIT_DIS           (0x0   << 16 )
#define CACHESETUP_DINIT_EN            (0x1   << 16 )

/* CACHESETUP[IRDBUF] - If this bit is set, then for every AHB access, hit from Read Buffer is not checked. */
#define CACHESETUP_IRDBUF_BBA          (*(volatile unsigned long *) 0x42301890)
#define CACHESETUP_IRDBUF_MSK          (0x1   << 4  )
#define CACHESETUP_IRDBUF              (0x1   << 4  )
#define CACHESETUP_IRDBUF_EN           (0x0   << 4  )
#define CACHESETUP_IRDBUF_DIS          (0x1   << 4  )

/* CACHESETUP[IWRBUF] - If this bit is set, then for every AHB access, hit from Write Buffer is not checked. */
#define CACHESETUP_IWRBUF_BBA          (*(volatile unsigned long *) 0x4230188C)
#define CACHESETUP_IWRBUF_MSK          (0x1   << 3  )
#define CACHESETUP_IWRBUF              (0x1   << 3  )
#define CACHESETUP_IWRBUF_EN           (0x0   << 3  )
#define CACHESETUP_IWRBUF_DIS          (0x1   << 3  )

/* CACHESETUP[ILOCK] - If this bit is set, then I-cache contents are locked. Any new misses won�t be replaced in I-Cache. This bit is cleared when CACHESETUP[0] is set. */
#define CACHESETUP_ILOCK_BBA           (*(volatile unsigned long *) 0x42301888)
#define CACHESETUP_ILOCK_MSK           (0x1   << 2  )
#define CACHESETUP_ILOCK               (0x1   << 2  )
#define CACHESETUP_ILOCK_DIS           (0x0   << 2  )
#define CACHESETUP_ILOCK_EN            (0x1   << 2  )

/* CACHESETUP[IEN] - If this bit set, then I-Cache is enabled for AHB accesses. If 0, then I-cache is disabled, and all AHB accesses will be via Flash memory. This bit is cleared when CACHESETUP[0] is set. */
#define CACHESETUP_IEN_BBA             (*(volatile unsigned long *) 0x42301884)
#define CACHESETUP_IEN_MSK             (0x1   << 1  )
#define CACHESETUP_IEN                 (0x1   << 1  )
#define CACHESETUP_IEN_DIS             (0x0   << 1  )
#define CACHESETUP_IEN_EN              (0x1   << 1  )

/* CACHESETUP[IINIT] - If this bit is set then the I-cache contents are initialized to all zeros. This bit will be cleared once the initialization starts. */
#define CACHESETUP_IINIT_BBA           (*(volatile unsigned long *) 0x42301880)
#define CACHESETUP_IINIT_MSK           (0x1   << 0  )
#define CACHESETUP_IINIT               (0x1   << 0  )
#define CACHESETUP_IINIT_DIS           (0x0   << 0  )
#define CACHESETUP_IINIT_EN            (0x1   << 0  )

/* Reset Value for CACHEKEY*/
#define CACHEKEY_RVAL                  0x0 

/* CACHEKEY[Key] - Cache Key register */
#define CACHEKEY_Key_MSK               (0xFFFFFFFF << 0  )


/*------------------------------------------------------------------------------
 *                                  GPIO
 *----------------------------------------------------------------------------*/

/**
 * @brief GPIO (MMR_GPIO)
 */

typedef struct {                            /*!< MMR_GPIO Structure                     */
  __IOM uint16_t  GPCON;                    /*!< GPIO Port configuration             */
  __IM  uint16_t  RESERVED0;
  __IOM uint8_t   GPOE;                     /*!< GPIO Port output enable             */
  __IM  uint8_t   RESERVED1[3];
  __IOM uint8_t   GPPUL;                    /*!< GPIO Port pullup enable             */
  __IM  uint8_t   RESERVED2[3];
  __IOM uint8_t   GPIE;                     /*!< GPIO Port input path enable         */
  __IM  uint8_t   RESERVED3[3];
  __IOM uint8_t   GPIN;                     /*!< GPIO Port registered data input     */
  __IM  uint8_t   RESERVED4[3];
  __IOM uint8_t   GPOUT;                    /*!< GPIO Port data output               */
  __IM  uint8_t   RESERVED5[3];
  __IOM uint8_t   GPSET;                    /*!< GPIO Port data out set              */
  __IM  uint8_t   RESERVED6[3];
  __IOM uint8_t   GPCLR;                    /*!< GPIO Port data out clear            */
  __IM  uint8_t   RESERVED7[3];
  __IOM uint8_t   GPTGL;                    /*!< GPIO Port pin toggle                */
  __IM  uint8_t   RESERVED8[3];
  __IOM uint8_t   GPODE;                    /*!< GPIO Port open drain enable         */
  __IM  uint8_t   RESERVED9[3];
} MMR_GPIO_t;

/********************  Reset Value for registers  *****************************/
#define GPIO_CON_RVAL             (0U)
#define GPIO_OE_RVAL              (0U)
#define GPIO_PUL_RVAL             (0U)
#define GPIO_IE_RVAL              (0U)
#define GPIO_IN_RVAL              (0U)
#define GPIO_OUT_RVAL             (0U)
#define GPIO_SET_RVAL             (0U)
#define GPIO_CLR_RVAL             (0U)
#define GPIO_TGL_RVAL             (0U)
#define GPIO_ODE_RVAL             (0U)

/********************  Bit definition for GPCON register  *********************/
#define GPIO_CON(af, pin)         ((uint16_t)(((af) & 3U) << ((pin) << 1U)))

/********************  Bit definition for GPOE register  **********************/
#define GPIO_OE(mode, pin)        ((uint8_t)(((mode) & 1U) << (pin)))

/********************  Bit definition for GPPUL register  *********************/
#define GPIO_PUL(mode, pin)       ((uint8_t)(((mode) & 1U) << (pin)))

/********************  Bit definition for GPIE register  **********************/
#define GPIO_IE(mode, pin)        ((uint8_t)(((mode) & 1U) << (pin)))

/********************  Bit definition for GPSET register  *********************/
#define GPIO_SET(pin)             ((uint8_t)(1U << (pin)))

/********************  Bit definition for GPCLR register  *********************/
#define GPIO_CLR(pin)             ((uint8_t)(1U << (pin)))

/********************  Bit definition for GPTGL register  *********************/
#define GPIO_TGL(pin)             ((uint8_t)(1U << (pin)))

/********************  Bit definition for GPODE register  *********************/
#define GPIO_ODE(mode, pin)       ((uint8_t)(((mode) & 1U) << (pin)))


// ------------------------------------------------------------------------------------------------
// -----                                        PWM                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief PWM (MMR_PWM)
  */

typedef struct MMR_PWM {                    /*!< MMR_PWM Structure                     */
  __IO uint16_t  PWMCON0;                   /*!< PWM control register                  */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  PWMCON1;                   /*!< ADC conversion start and trip control register */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  PWMICLR;                   /*!< Hardware trip configuration register  */
  __I  uint16_t  RESERVED2[3];
  __IO uint16_t  PWM0COM0;                  /*!< Compare Register 0 for PWM0 and PWM1  */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  PWM0COM1;                  /*!< Compare Register 1 for PWM0 and PWM1  */
  __I  uint16_t  RESERVED4;
  __IO uint16_t  PWM0COM2;                  /*!< Compare Register 2 for PWM0 and PWM1  */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  PWM0LEN;                   /*!< Period value register for PWM0 and PWM1 */
  __I  uint16_t  RESERVED6;
  __IO uint16_t  PWM1COM0;                  /*!< Compare Register 0 for PWM2 and PWM3  */
  __I  uint16_t  RESERVED7;
  __IO uint16_t  PWM1COM1;                  /*!< Compare Register 1 for PWM2 and PWM3  */
  __I  uint16_t  RESERVED8;
  __IO uint16_t  PWM1COM2;                  /*!< Compare Register 2 for PWM2 and PWM3  */
  __I  uint16_t  RESERVED9;
  __IO uint16_t  PWM1LEN;                   /*!< Period value register for PWM2 and PWM3 */
  __I  uint16_t  RESERVED10;
  __IO uint16_t  PWM2COM0;                  /*!< Compare Register 0 for PWM4 and PWM5  */
  __I  uint16_t  RESERVED11;
  __IO uint16_t  PWM2COM1;                  /*!< Compare Register 1 for PWM4 and PWM5  */
  __I  uint16_t  RESERVED12;
  __IO uint16_t  PWM2COM2;                  /*!< Compare Register 2 for PWM4 and PWM5  */
  __I  uint16_t  RESERVED13;
  __IO uint16_t  PWM2LEN;                   /*!< Period value register for PWM4 and PWM5 */
  __I  uint16_t  RESERVED14;
  __IO uint16_t  PWM3COM0;                  /*!< Compare Register 0 for PWM6 and PWM7  */
  __I  uint16_t  RESERVED15;
  __IO uint16_t  PWM3COM1;                  /*!< Compare Register 1 for PWM6 and PWM7  */
  __I  uint16_t  RESERVED16;
  __IO uint16_t  PWM3COM2;                  /*!< Compare Register 2 for PWM6 and PWM7  */
  __I  uint16_t  RESERVED17;
  __IO uint16_t  PWM3LEN;                   /*!< Period value register for PWM6 and PWM7 */
} MMR_PWM_t;

/* Reset Value for PWMCON0*/
#define PWMCON0_RVAL                   0x12 

/* PWMCON0[SYNC] - Set to enable PWM synchronization from the SYNC pin of the PWM */
#define PWMCON0_SYNC_BBA               (*(volatile unsigned long *) 0x4248003C)
#define PWMCON0_SYNC_MSK               (0x1   << 15 )
#define PWMCON0_SYNC                   (0x1   << 15 )
#define PWMCON0_SYNC_DIS               (0x0   << 15 ) /* Ignore transition from the SYNC pin */
#define PWMCON0_SYNC_EN                (0x1   << 15 ) /* All PWM counters are reset on the next clock cycle after detection of a falling edge from SYNC pin */

/* PWMCON0[PWM7INV] - Set to invert PWM7 output */
#define PWMCON0_PWM7INV_BBA            (*(volatile unsigned long *) 0x42480038)
#define PWMCON0_PWM7INV_MSK            (0x1   << 14 )
#define PWMCON0_PWM7INV                (0x1   << 14 )
#define PWMCON0_PWM7INV_DIS            (0x0   << 14 )
#define PWMCON0_PWM7INV_EN             (0x1   << 14 )

/* PWMCON0[PWM5INV] - Set to invert PWM5 output */
#define PWMCON0_PWM5INV_BBA            (*(volatile unsigned long *) 0x42480034)
#define PWMCON0_PWM5INV_MSK            (0x1   << 13 )
#define PWMCON0_PWM5INV                (0x1   << 13 )
#define PWMCON0_PWM5INV_DIS            (0x0   << 13 )
#define PWMCON0_PWM5INV_EN             (0x1   << 13 )

/* PWMCON0[PWM3INV] - Set to invert PWM3 output */
#define PWMCON0_PWM3INV_BBA            (*(volatile unsigned long *) 0x42480030)
#define PWMCON0_PWM3INV_MSK            (0x1   << 12 )
#define PWMCON0_PWM3INV                (0x1   << 12 )
#define PWMCON0_PWM3INV_DIS            (0x0   << 12 )
#define PWMCON0_PWM3INV_EN             (0x1   << 12 )

/* PWMCON0[PWM1INV] - Set to invert PWM1 output */
#define PWMCON0_PWM1INV_BBA            (*(volatile unsigned long *) 0x4248002C)
#define PWMCON0_PWM1INV_MSK            (0x1   << 11 )
#define PWMCON0_PWM1INV                (0x1   << 11 )
#define PWMCON0_PWM1INV_DIS            (0x0   << 11 )
#define PWMCON0_PWM1INV_EN             (0x1   << 11 )

/* PWMCON0[PWMIEN] - Set to enable interrupts for PWM */
#define PWMCON0_PWMIEN_BBA             (*(volatile unsigned long *) 0x42480028)
#define PWMCON0_PWMIEN_MSK             (0x1   << 10 )
#define PWMCON0_PWMIEN                 (0x1   << 10 )
#define PWMCON0_PWMIEN_DIS             (0x0   << 10 )
#define PWMCON0_PWMIEN_EN              (0x1   << 10 )

/* PWMCON0[ENA] - When HOFF=0 and HMODE=1 this serves as enable for Pair 0 and 1 */
#define PWMCON0_ENA_BBA                (*(volatile unsigned long *) 0x42480024)
#define PWMCON0_ENA_MSK                (0x1   << 9  )
#define PWMCON0_ENA                    (0x1   << 9  )
#define PWMCON0_ENA_DIS                (0x0   << 9  ) /* Disable Pair 0 and 1     */
#define PWMCON0_ENA_EN                 (0x1   << 9  ) /* Enable Pair 0 and 1      */

/* PWMCON0[PWMCMP] - PWM Clock prescaler. Sets HCLK divider. */
#define PWMCON0_PWMCMP_MSK             (0x7   << 6  )
#define PWMCON0_PWMCMP_DIV2            (0x0   << 6  ) /* HCLK/2                   */
#define PWMCON0_PWMCMP_DIV4            (0x1   << 6  ) /* HCLK/4                   */
#define PWMCON0_PWMCMP_DIV8            (0x2   << 6  ) /* HCLK/8                   */
#define PWMCON0_PWMCMP_DIV16           (0x3   << 6  ) /* HCLK/16                  */
#define PWMCON0_PWMCMP_DIV32           (0x4   << 6  ) /* HCLK/32                  */
#define PWMCON0_PWMCMP_DIV64           (0x5   << 6  ) /* HCLK/64                  */
#define PWMCON0_PWMCMP_DIV128          (0x6   << 6  ) /* HCLK/128                 */
#define PWMCON0_PWMCMP_DIV256          (0x7   << 6  ) /* HCLK/256                 */

/* PWMCON0[POINV] - Set to invert PWM outputs for Pair 0 and 1 when PWM is in H-bridge mode */
#define PWMCON0_POINV_BBA              (*(volatile unsigned long *) 0x42480014)
#define PWMCON0_POINV_MSK              (0x1   << 5  )
#define PWMCON0_POINV                  (0x1   << 5  )
#define PWMCON0_POINV_DIS              (0x0   << 5  )
#define PWMCON0_POINV_EN               (0x1   << 5  )

/* PWMCON0[HOFF] - Set to turn off the high-side for Pair 0 and 1 when PWM is in H-bridge mode */
#define PWMCON0_HOFF_BBA               (*(volatile unsigned long *) 0x42480010)
#define PWMCON0_HOFF_MSK               (0x1   << 4  )
#define PWMCON0_HOFF                   (0x1   << 4  )
#define PWMCON0_HOFF_DIS               (0x0   << 4  )
#define PWMCON0_HOFF_EN                (0x1   << 4  )

/* PWMCON0[LCOMP] - Signal to load a new set of compare register values. In standard mode, this bit is cleared when the new values are loaded in the compare registers for all the channels. In H-bridge mode this bit does not get cleared, but the user must write a value of 1 to this bit in order for the compare registers to be loaded */
#define PWMCON0_LCOMP_BBA              (*(volatile unsigned long *) 0x4248000C)
#define PWMCON0_LCOMP_MSK              (0x1   << 3  )
#define PWMCON0_LCOMP                  (0x1   << 3  )
#define PWMCON0_LCOMP_DIS              (0x0   << 3  ) /* Use the values previously store in the compare and length registers */
#define PWMCON0_LCOMP_EN               (0x1   << 3  ) /* Load the internal compare registers with values stored in the PWMxCOMx and PWMxLEN registers */

/* PWMCON0[DIR] - Direction control when PWM is in H-bridge mode */
#define PWMCON0_DIR_BBA                (*(volatile unsigned long *) 0x42480008)
#define PWMCON0_DIR_MSK                (0x1   << 2  )
#define PWMCON0_DIR                    (0x1   << 2  )
#define PWMCON0_DIR_DIS                (0x0   << 2  ) /* PWM2 and PWM3 act as output signals while PWM0 and PWM1 are held low */
#define PWMCON0_DIR_EN                 (0x1   << 2  ) /* PWM0 and PWM1 act as output signals while PWM2 and PWM3 are held low */

/* PWMCON0[HMODE] - Set to enable H-bridge mode */
#define PWMCON0_HMODE_BBA              (*(volatile unsigned long *) 0x42480004)
#define PWMCON0_HMODE_MSK              (0x1   << 1  )
#define PWMCON0_HMODE                  (0x1   << 1  )
#define PWMCON0_HMODE_DIS              (0x0   << 1  )
#define PWMCON0_HMODE_EN               (0x1   << 1  )

/* PWMCON0[PWMEN] - Master enable for PWM */
#define PWMCON0_PWMEN_BBA              (*(volatile unsigned long *) 0x42480000)
#define PWMCON0_PWMEN_MSK              (0x1   << 0  )
#define PWMCON0_PWMEN                  (0x1   << 0  )
#define PWMCON0_PWMEN_DIS              (0x0   << 0  ) /* Disable all PWM outputs  */
#define PWMCON0_PWMEN_EN               (0x1   << 0  ) /* Enable all PWM outputs   */

/* Reset Value for PWMCON1*/
#define PWMCON1_RVAL                   0x0 

/* PWMCON1[TRIP_EN] - Set to enable PWM Trip functionality */
#define PWMCON1_TRIP_EN_BBA            (*(volatile unsigned long *) 0x42480098)
#define PWMCON1_TRIP_EN_MSK            (0x1   << 6  )
#define PWMCON1_TRIP_EN                (0x1   << 6  )
#define PWMCON1_TRIP_EN_DIS            (0x0   << 6  )
#define PWMCON1_TRIP_EN_EN             (0x1   << 6  )

/* Reset Value for PWMICLR*/
#define PWMICLR_RVAL                   0x0 

/* PWMICLR[TRIP] - Write a 1 to clear latched IRQPWMTrip interrupt. Returns 0 on reads. */
#define PWMICLR_TRIP_BBA               (*(volatile unsigned long *) 0x42480110)
#define PWMICLR_TRIP_MSK               (0x1   << 4  )
#define PWMICLR_TRIP                   (0x1   << 4  )
#define PWMICLR_TRIP_DIS               (0x0   << 4  )
#define PWMICLR_TRIP_EN                (0x1   << 4  )

/* PWMICLR[PWM3] - Write a 1 to clear latched IRQPWM3 interrupt. Returns 0 on reads. */
#define PWMICLR_PWM3_BBA               (*(volatile unsigned long *) 0x4248010C)
#define PWMICLR_PWM3_MSK               (0x1   << 3  )
#define PWMICLR_PWM3                   (0x1   << 3  )
#define PWMICLR_PWM3_DIS               (0x0   << 3  )
#define PWMICLR_PWM3_EN                (0x1   << 3  )

/* PWMICLR[PWM2] - Write a 1 to clear latched IRQPWM2 interrupt. Returns 0 on reads. */
#define PWMICLR_PWM2_BBA               (*(volatile unsigned long *) 0x42480108)
#define PWMICLR_PWM2_MSK               (0x1   << 2  )
#define PWMICLR_PWM2                   (0x1   << 2  )
#define PWMICLR_PWM2_DIS               (0x0   << 2  )
#define PWMICLR_PWM2_EN                (0x1   << 2  )

/* PWMICLR[PWM1] - Write a 1 to clear latched IRQPWM1 interrupt. Returns 0 on reads. */
#define PWMICLR_PWM1_BBA               (*(volatile unsigned long *) 0x42480104)
#define PWMICLR_PWM1_MSK               (0x1   << 1  )
#define PWMICLR_PWM1                   (0x1   << 1  )
#define PWMICLR_PWM1_DIS               (0x0   << 1  )
#define PWMICLR_PWM1_EN                (0x1   << 1  )

/* PWMICLR[PWM0] - Write a 1 to clear latched IRQPWM0 interrupt. Returns 0 on reads. */
#define PWMICLR_PWM0_BBA               (*(volatile unsigned long *) 0x42480100)
#define PWMICLR_PWM0_MSK               (0x1   << 0  )
#define PWMICLR_PWM0                   (0x1   << 0  )
#define PWMICLR_PWM0_DIS               (0x0   << 0  )
#define PWMICLR_PWM0_EN                (0x1   << 0  )

/* Reset Value for PWM0COM0*/
#define PWM0COM0_RVAL                  0x0 

/* PWM0COM0[COM0] - Compare register 0 data */
#define PWM0COM0_COM0_MSK              (0xFFFF << 0  )

/* Reset Value for PWM0COM1*/
#define PWM0COM1_RVAL                  0x0 

/* PWM0COM1[COM1] - Compare register 1 data */
#define PWM0COM1_COM1_MSK              (0xFFFF << 0  )

/* Reset Value for PWM0COM2*/
#define PWM0COM2_RVAL                  0x0 

/* PWM0COM2[COM2] - Compare register 2 data */
#define PWM0COM2_COM2_MSK              (0xFFFF << 0  )

/* Reset Value for PWM0LEN*/
#define PWM0LEN_RVAL                   0x0 

/* PWM0LEN[LEN] - Period value */
#define PWM0LEN_LEN_MSK                (0xFFFF << 0  )

/* Reset Value for PWM1COM0*/
#define PWM1COM0_RVAL                  0x0 

/* PWM1COM0[COM0] - Compare register 0 data */
#define PWM1COM0_COM0_MSK              (0xFFFF << 0  )

/* Reset Value for PWM1COM1*/
#define PWM1COM1_RVAL                  0x0 

/* PWM1COM1[COM1] - Compare register 1 data */
#define PWM1COM1_COM1_MSK              (0xFFFF << 0  )

/* Reset Value for PWM1COM2*/
#define PWM1COM2_RVAL                  0x0 

/* PWM1COM2[COM2] - Compare register 2 data */
#define PWM1COM2_COM2_MSK              (0xFFFF << 0  )

/* Reset Value for PWM1LEN*/
#define PWM1LEN_RVAL                   0x0 

/* PWM1LEN[LEN] - Period value */
#define PWM1LEN_LEN_MSK                (0xFFFF << 0  )

/* Reset Value for PWM2COM0*/
#define PWM2COM0_RVAL                  0x0 

/* PWM2COM0[COM0] - Compare register 0 data */
#define PWM2COM0_COM0_MSK              (0xFFFF << 0  )

/* Reset Value for PWM2COM1*/
#define PWM2COM1_RVAL                  0x0 

/* PWM2COM1[COM1] - Compare register 1 data */
#define PWM2COM1_COM1_MSK              (0xFFFF << 0  )

/* Reset Value for PWM2COM2*/
#define PWM2COM2_RVAL                  0x0 

/* PWM2COM2[COM2] - Compare register 2 data */
#define PWM2COM2_COM2_MSK              (0xFFFF << 0  )

/* Reset Value for PWM2LEN*/
#define PWM2LEN_RVAL                   0x0 

/* PWM2LEN[LEN] - Period value */
#define PWM2LEN_LEN_MSK                (0xFFFF << 0  )

/* Reset Value for PWM3COM0*/
#define PWM3COM0_RVAL                  0x0 

/* PWM3COM0[COM0] - Compare register 0 data */
#define PWM3COM0_COM0_MSK              (0xFFFF << 0  )

/* Reset Value for PWM3COM1*/
#define PWM3COM1_RVAL                  0x0 

/* PWM3COM1[COM1] - Compare register 1 data */
#define PWM3COM1_COM1_MSK              (0xFFFF << 0  )

/* Reset Value for PWM3COM2*/
#define PWM3COM2_RVAL                  0x0 

/* PWM3COM2[COM2] - Compare register 2 data */
#define PWM3COM2_COM2_MSK              (0xFFFF << 0  )

/* Reset Value for PWM3LEN*/
#define PWM3LEN_RVAL                   0x0 

/* PWM3LEN[LEN] - Period value */
#define PWM3LEN_LEN_MSK                (0xFFFF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        CLKCTL                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief clocking (MMR_CLKCTL)
  */

typedef struct MMR_CLKCTL{                  /*!< MMR_CLKCTL Structure                  */
  __IO uint16_t  CLKCON0;                   /*!< Misc clock settings register          */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  CLKCON1;                   /*!< Clock dividers register               */
  __I  uint16_t  RESERVED1[7];
  __IO uint16_t  CLKCON5;                   /*!< User clock gating control register    */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  CLKSTAT0;                  /*!< Clocking status                       */
} MMR_CLKCTL_t;

/* Reset Value for CLKCON0*/
#define CLKCON0_RVAL                   0x0 

/* CLKCON0[HFXTALIE] - High frequency crystal interrupt enable */
#define CLKCON0_HFXTALIE_BBA           (*(volatile unsigned long *) 0x4250003C)
#define CLKCON0_HFXTALIE_MSK           (0x1   << 15 )
#define CLKCON0_HFXTALIE               (0x1   << 15 )
#define CLKCON0_HFXTALIE_DIS           (0x0   << 15 ) /* An interrupt to the core will not be generated on a HFXTAL ok or HFXTAL nok */
#define CLKCON0_HFXTALIE_EN            (0x1   << 15 ) /* An interrupt to the core will be generated on a HFXTAL ok or HFXTAL nok */

/* CLKCON0[SPLLIE] - SPLL Interrupt enable */
#define CLKCON0_SPLLIE_BBA             (*(volatile unsigned long *) 0x42500034)
#define CLKCON0_SPLLIE_MSK             (0x1   << 13 )
#define CLKCON0_SPLLIE                 (0x1   << 13 )
#define CLKCON0_SPLLIE_DIS             (0x0   << 13 ) /* System PLL interrupt will not be generated */
#define CLKCON0_SPLLIE_EN              (0x1   << 13 ) /* System PLL interrupt will be generated */

/* CLKCON0[PLLMUX] - PLL source selection */
#define CLKCON0_PLLMUX_BBA             (*(volatile unsigned long *) 0x4250002C)
#define CLKCON0_PLLMUX_MSK             (0x1   << 11 )
#define CLKCON0_PLLMUX                 (0x1   << 11 )
#define CLKCON0_PLLMUX_HFOSC           (0x0   << 11 ) /* Internal oscillator is selected (HFOSC) */
#define CLKCON0_PLLMUX_HFXTAL          (0x1   << 11 ) /* External oscillator is selected (HFXTAL) */

/* CLKCON0[CLKOUT] - GPIO clk out select */
#define CLKCON0_CLKOUT_MSK             (0xF   << 4  )
#define CLKCON0_CLKOUT_ROOT            (0x0   << 4  ) /* Root Clock               */
#define CLKCON0_CLKOUT_LFOSC           (0x1   << 4  ) /* LFOSC (32 kHz)           */
#define CLKCON0_CLKOUT_HFOSC           (0x2   << 4  ) /* HFOSC (16 MHz)           */
#define CLKCON0_CLKOUT_CORE            (0x4   << 4  ) /* Core Clock               */
#define CLKCON0_CLKOUT_PCLK            (0x5   << 4  ) /* PCLK                     */
#define CLKCON0_CLKOUT_T0              (0xB   << 4  ) /* Timer 0 Clock            */
#define CLKCON0_CLKOUT_WUT             (0xC   << 4  ) /* Wake up Timer Clock      */
#define CLKCON0_CLKOUT_HFXTAL          (0xE   << 4  ) /* HFXTAL                   */

/* CLKCON0[CLKMUX] - Clock mux select */
#define CLKCON0_CLKMUX_MSK             (0x3   << 0  )
#define CLKCON0_CLKMUX_HFOSC           (0x0   << 0  ) /* High frequency internal oscillator (HFOSC) */
#define CLKCON0_CLKMUX_SPLL            (0x1   << 0  ) /* System PLL is selected (80 MHz) */
#define CLKCON0_CLKMUX_UPLL            (0x2   << 0  ) /* UPLL is selected (60 MHz) */
#define CLKCON0_CLKMUX_EXTCLK          (0x3   << 0  ) /* External GPIO port is selected (ECLKIN) */

/* Reset Value for CLKCON1*/
#define CLKCON1_RVAL                   0xA82 

/* CLKCON1[CDD2DCLK] - D2DCLK divide bits */
#define CLKCON1_CDD2DCLK_BBA           (*(volatile unsigned long *) 0x425000AC)
#define CLKCON1_CDD2DCLK_MSK           (0x1   << 11 )
#define CLKCON1_CDD2DCLK               (0x1   << 11 )
#define CLKCON1_CDD2DCLK_DIV1          (0x0   << 11 ) /* D2D_CLK frequency = HCLK frequency */
#define CLKCON1_CDD2DCLK_DIV2          (0x1   << 11 ) /* D2D_CLK frequency = half of HCLK frequency */

/* CLKCON1[CDPCLK] - PCLK divide bits */
#define CLKCON1_CDPCLK_MSK             (0x7   << 8  )
#define CLKCON1_CDPCLK_DIV1            (0x0   << 8  ) /* DIV1. Divide by 1 (PCLK is equal to root clock) */
#define CLKCON1_CDPCLK_DIV2            (0x1   << 8  ) /* DIV2. Divide by 2 (PCLK is half the frequency of root clock) */
#define CLKCON1_CDPCLK_DIV4            (0x2   << 8  ) /* DIV4. Divide by 4 (PCLK is quarter the frequency of root clock, 20 MHz) */
#define CLKCON1_CDPCLK_DIV8            (0x3   << 8  ) /* DIV8. Divide by 8        */
#define CLKCON1_CDPCLK_DIV16           (0x4   << 8  ) /* DIV16. Divide by 16      */
#define CLKCON1_CDPCLK_DIV32           (0x5   << 8  ) /* DIV32. Divide by 32      */
#define CLKCON1_CDPCLK_DIV64           (0x6   << 8  ) /* DIV64. Divide by 164     */
#define CLKCON1_CDPCLK_DIV128          (0x7   << 8  ) /* DIV128. Divide by 128    */

/* CLKCON1[CDHCLK] - HCLK divide bits */
#define CLKCON1_CDHCLK_MSK             (0x7   << 0  )
#define CLKCON1_CDHCLK_DIV1            (0x0   << 0  ) /* DIV1. Divide by 1 (HCLK is equal to root clock) */
#define CLKCON1_CDHCLK_DIV2            (0x1   << 0  ) /* DIV2. Divide by 2 (HCLK is half the frequency of root clock) */
#define CLKCON1_CDHCLK_DIV4            (0x2   << 0  ) /* DIV4. Divide by 4 (HCLK is quarter the frequency of root clock) */
#define CLKCON1_CDHCLK_DIV8            (0x3   << 0  ) /* DIV8. Divide by 8        */
#define CLKCON1_CDHCLK_DIV16           (0x4   << 0  ) /* DIV16.Divide by 16       */
#define CLKCON1_CDHCLK_DIV32           (0x5   << 0  ) /* DIV32.Divide by 32       */
#define CLKCON1_CDHCLK_DIV64           (0x6   << 0  ) /* DIV64.Divide by 64       */
#define CLKCON1_CDHCLK_DIV128          (0x7   << 0  ) /* DIV128. Divide by 128    */

/* Reset Value for CLKCON5*/
#define CLKCON5_RVAL                   0x0 

/* CLKCON5[D2DCLKOFF] - D2D clock user control */
#define CLKCON5_D2DCLKOFF_BBA          (*(volatile unsigned long *) 0x42500298)
#define CLKCON5_D2DCLKOFF_MSK          (0x1   << 6  )
#define CLKCON5_D2DCLKOFF              (0x1   << 6  )
#define CLKCON5_D2DCLKOFF_ON           (0x0   << 6  ) /* Clock on                 */
#define CLKCON5_D2DCLKOFF_OFF          (0x1   << 6  ) /* Clock off                */

/* CLKCON5[UCLKUARTOFF] - UART clock user control */
#define CLKCON5_UCLKUARTOFF_BBA        (*(volatile unsigned long *) 0x42500294)
#define CLKCON5_UCLKUARTOFF_MSK        (0x1   << 5  )
#define CLKCON5_UCLKUARTOFF            (0x1   << 5  )
#define CLKCON5_UCLKUARTOFF_ON         (0x0   << 5  ) /* Clock on                 */
#define CLKCON5_UCLKUARTOFF_OFF        (0x1   << 5  ) /* Clock off                */

/* CLKCON5[UCLKI2C1OFF] - I2C1 clock user control */
#define CLKCON5_UCLKI2C1OFF_BBA        (*(volatile unsigned long *) 0x42500290)
#define CLKCON5_UCLKI2C1OFF_MSK        (0x1   << 4  )
#define CLKCON5_UCLKI2C1OFF            (0x1   << 4  )
#define CLKCON5_UCLKI2C1OFF_ON         (0x0   << 4  ) /* Clock on                 */
#define CLKCON5_UCLKI2C1OFF_OFF        (0x1   << 4  ) /* Clock off                */

/* CLKCON5[UCLKI2C0OFF] - I2C0 clock user control */
#define CLKCON5_UCLKI2C0OFF_BBA        (*(volatile unsigned long *) 0x4250028C)
#define CLKCON5_UCLKI2C0OFF_MSK        (0x1   << 3  )
#define CLKCON5_UCLKI2C0OFF            (0x1   << 3  )
#define CLKCON5_UCLKI2C0OFF_ON         (0x0   << 3  ) /* Clock on                 */
#define CLKCON5_UCLKI2C0OFF_OFF        (0x1   << 3  ) /* Clock off                */

/* CLKCON5[UCLKSPI1OFF] - SPI1 clock user control */
#define CLKCON5_UCLKSPI1OFF_BBA        (*(volatile unsigned long *) 0x42500284)
#define CLKCON5_UCLKSPI1OFF_MSK        (0x1   << 1  )
#define CLKCON5_UCLKSPI1OFF            (0x1   << 1  )
#define CLKCON5_UCLKSPI1OFF_ON         (0x0   << 1  ) /* Clock on                 */
#define CLKCON5_UCLKSPI1OFF_OFF        (0x1   << 1  ) /* Clock off                */

/* CLKCON5[UCLKSPI0OFF] - SPI0 clock user control */
#define CLKCON5_UCLKSPI0OFF_BBA        (*(volatile unsigned long *) 0x42500280)
#define CLKCON5_UCLKSPI0OFF_MSK        (0x1   << 0  )
#define CLKCON5_UCLKSPI0OFF            (0x1   << 0  )
#define CLKCON5_UCLKSPI0OFF_ON         (0x0   << 0  ) /* Clock on                 */
#define CLKCON5_UCLKSPI0OFF_OFF        (0x1   << 0  ) /* Clock off                */

/* Reset Value for CLKSTAT0*/
#define CLKSTAT0_RVAL                  0x0 

/* CLKSTAT0[HFXTALNOK] - HF crystal not stable */
#define CLKSTAT0_HFXTALNOK_BBA         (*(volatile unsigned long *) 0x42500338)
#define CLKSTAT0_HFXTALNOK_MSK         (0x1   << 14 )
#define CLKSTAT0_HFXTALNOK             (0x1   << 14 )

/* CLKSTAT0[HFXTALOK] - HF crystal stable */
#define CLKSTAT0_HFXTALOK_BBA          (*(volatile unsigned long *) 0x42500334)
#define CLKSTAT0_HFXTALOK_MSK          (0x1   << 13 )
#define CLKSTAT0_HFXTALOK              (0x1   << 13 )

/* CLKSTAT0[HFXTALSTATUS] - HF crystal status */
#define CLKSTAT0_HFXTALSTATUS_BBA      (*(volatile unsigned long *) 0x42500330)
#define CLKSTAT0_HFXTALSTATUS_MSK      (0x1   << 12 )
#define CLKSTAT0_HFXTALSTATUS          (0x1   << 12 )

/* CLKSTAT0[SPLLUNLOCK] - System PLL unlock */
#define CLKSTAT0_SPLLUNLOCK_BBA        (*(volatile unsigned long *) 0x42500308)
#define CLKSTAT0_SPLLUNLOCK_MSK        (0x1   << 2  )
#define CLKSTAT0_SPLLUNLOCK            (0x1   << 2  )

/* CLKSTAT0[SPLLLOCK] - System PLL lock */
#define CLKSTAT0_SPLLLOCK_BBA          (*(volatile unsigned long *) 0x42500304)
#define CLKSTAT0_SPLLLOCK_MSK          (0x1   << 1  )
#define CLKSTAT0_SPLLLOCK              (0x1   << 1  )

/* CLKSTAT0[SPLLSTATUS] - System PLL status */
#define CLKSTAT0_SPLLSTATUS_BBA        (*(volatile unsigned long *) 0x42500300)
#define CLKSTAT0_SPLLSTATUS_MSK        (0x1   << 0  )
#define CLKSTAT0_SPLLSTATUS            (0x1   << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        dma_ctl                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief DMACTL (MMR_DMACTL)
  */

typedef struct MMR_DMACTL {                 /*!< MMR_DMACTL Structure                  */
  __IO uint16_t  GPFDMACTL;                 /*!< DMA Channel Control                   */
  __I  uint16_t  RESERVED0;
  __IO uint32_t  L1SRAMCTL;                 /*!< L1SRAMCTL                             */
} MMR_DMACTL_t;

/* Reset Value for GPFDMACTL*/
#define GPFDMACTL_RVAL                 0x0 

/* GPFDMACTL[GPFlash] - DMA Channel 13 Control */
#define GPFDMACTL_GPFlash_BBA          (*(volatile unsigned long *) 0x42502000)
#define GPFDMACTL_GPFlash_MSK          (0x1   << 0  )
#define GPFDMACTL_GPFlash              (0x1   << 0  )

/* Reset Value for L1SRAMCTL*/
#define L1SRAMCTL_RVAL                 0x0 

/* L1SRAMCTL[L1SRAMCTL] -  */
#define L1SRAMCTL_L1SRAMCTL_BBA        (*(volatile unsigned long *) 0x42502080)
#define L1SRAMCTL_L1SRAMCTL_MSK        (0x1   << 0  )
#define L1SRAMCTL_L1SRAMCTL            (0x1   << 0  )
#define L1SRAMCTL_L1SRAMCTL_DIS        (0x0   << 0  )
#define L1SRAMCTL_L1SRAMCTL_EN         (0x1   << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        SPI                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief SPI (MMR_SPI)
  */

typedef struct MMR_SPI {                    /*!< MMR_SPI Structure                    */
  __IO uint16_t  SPISTA;                    /*!< Status register                       */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  SPIRX;                     /*!< Receive register                      */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  SPITX;                     /*!< Transmit register                     */
  __I  uint16_t  RESERVED2;
  __IO uint16_t  SPIDIV;                    /*!< Baud rate selection register          */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  SPICON;                    /*!< SPI configuration register            */
  __I  uint16_t  RESERVED4;
  __IO uint16_t  SPIDMA;                    /*!< SPI DMA enable register               */
  __I  uint16_t  RESERVED5;
  __IO uint16_t  SPICNT;                    /*!< Transfer byte count register          */
} MMR_SPI_t;

/* Reset Value for SPI0STA*/
#define SPI0STA_RVAL                   0x0 

/* SPI0STA[CSRSG] - Detected a rising edge on CS, in CONT mode */
#define SPI0STA_CSRSG_BBA              (*(volatile unsigned long *) 0x42580038)
#define SPI0STA_CSRSG_MSK              (0x1   << 14 )
#define SPI0STA_CSRSG                  (0x1   << 14 )
#define SPI0STA_CSRSG_CLR              (0x0   << 14 ) /* Cleared to 0 when the Status register is read. */
#define SPI0STA_CSRSG_SET              (0x1   << 14 ) /* Set to 1 when there was a rising edge in CS line, when the device was in master mode, continuous transfer, High Frequency mode and CSIRQ_EN was asserted. */

/* SPI0STA[CSFLG] - Detected a falling edge on CS, in CONT mode */
#define SPI0STA_CSFLG_BBA              (*(volatile unsigned long *) 0x42580034)
#define SPI0STA_CSFLG_MSK              (0x1   << 13 )
#define SPI0STA_CSFLG                  (0x1   << 13 )
#define SPI0STA_CSFLG_CLR              (0x0   << 13 ) /* Cleared to 0 when the Status register is read. */
#define SPI0STA_CSFLG_SET              (0x1   << 13 ) /* Set to 1 when there was a falling edge in CS line, when the device was in master mode, continuous transfer, High Frequency mode and CSIRQ_EN was asserted */

/* SPI0STA[CSERR] - Detected a CS error condition */
#define SPI0STA_CSERR_BBA              (*(volatile unsigned long *) 0x42580030)
#define SPI0STA_CSERR_MSK              (0x1   << 12 )
#define SPI0STA_CSERR                  (0x1   << 12 )
#define SPI0STA_CSERR_CLR              (0x0   << 12 ) /* Cleared to 0 when the Status register is read. */
#define SPI0STA_CSERR_SET              (0x1   << 12 ) /* Set to 1 when the CS line was de-asserted abruptly, even before the full-byte of data was transmitted completely. This bit will cause an interrupt. */

/* SPI0STA[RXS] - SPI Rx FIFO excess bytes present */
#define SPI0STA_RXS_BBA                (*(volatile unsigned long *) 0x4258002C)
#define SPI0STA_RXS_MSK                (0x1   << 11 )
#define SPI0STA_RXS                    (0x1   << 11 )
#define SPI0STA_RXS_CLR                (0x0   << 11 ) /* This bit is cleared when the number of bytes in the FIFO is equal or less than the number in SPI0CON[15:14]. */
#define SPI0STA_RXS_SET                (0x1   << 11 ) /* This bit is set when there are more bytes in the Rx FIFO than indicated in the MOD bits in SPI0CON. */

/* SPI0STA[RXFSTA] - SPI Rx FIFO status */
#define SPI0STA_RXFSTA_MSK             (0x7   << 8  )
#define SPI0STA_RXFSTA_EMPTY           (0x0   << 8  ) /* Rx FIFO empty            */
#define SPI0STA_RXFSTA_ONEBYTE         (0x1   << 8  ) /* 1 valid byte in FIFO     */
#define SPI0STA_RXFSTA_TWOBYTES        (0x2   << 8  ) /* 2 valid bytes in the FIFO */
#define SPI0STA_RXFSTA_THREEBYTES      (0x3   << 8  ) /* 3 valid bytes in the FIFO */
#define SPI0STA_RXFSTA_FOURBYTES       (0x4   << 8  ) /* 4 valid bytes in the FIFO */

/* SPI0STA[RXOF] - SPI Rx FIFO overflow */
#define SPI0STA_RXOF_BBA               (*(volatile unsigned long *) 0x4258001C)
#define SPI0STA_RXOF_MSK               (0x1   << 7  )
#define SPI0STA_RXOF                   (0x1   << 7  )
#define SPI0STA_RXOF_CLR               (0x0   << 7  ) /* Cleared when the SPISTA register is read. */
#define SPI0STA_RXOF_SET               (0x1   << 7  ) /* Set when the Rx FIFO was already full when new data was loaded to the FIFO. This bit generates an interrupt except when RFLUSH is set in SPI0CON. */

/* SPI0STA[RX] - SPI Rx IRQ */
#define SPI0STA_RX_BBA                 (*(volatile unsigned long *) 0x42580018)
#define SPI0STA_RX_MSK                 (0x1   << 6  )
#define SPI0STA_RX                     (0x1   << 6  )
#define SPI0STA_RX_CLR                 (0x0   << 6  ) /* Cleared when the SPI0STA register is read. */
#define SPI0STA_RX_SET                 (0x1   << 6  ) /* Set when a receive interrupt occurs. This bit is set when TIM in SPI0CON is cleared and the required number of bytes have been received. */

/* SPI0STA[TX] - SPI Tx IRQ */
#define SPI0STA_TX_BBA                 (*(volatile unsigned long *) 0x42580014)
#define SPI0STA_TX_MSK                 (0x1   << 5  )
#define SPI0STA_TX                     (0x1   << 5  )
#define SPI0STA_TX_CLR                 (0x0   << 5  ) /* CLR. Cleared to 0 when the SPI0STA register is read. */
#define SPI0STA_TX_SET                 (0x1   << 5  ) /* SET. Set to 1 when a transmit interrupt occurs. This bit is set when TIM in SPI0CON is set and the required number of bytes have been transmitted. */

/* SPI0STA[TXUR] - SPI Tx FIFO underflow */
#define SPI0STA_TXUR_BBA               (*(volatile unsigned long *) 0x42580010)
#define SPI0STA_TXUR_MSK               (0x1   << 4  )
#define SPI0STA_TXUR                   (0x1   << 4  )
#define SPI0STA_TXUR_CLR               (0x0   << 4  ) /* Cleared to 0 when the SPI0STA register is read. */
#define SPI0STA_TXUR_SET               (0x1   << 4  ) /* Set  to 1 when a transmit is initiated without any valid data in the Tx FIFO. This bit generates an interrupt except when TFLUSH is set in SPI0CON. */

/* SPI0STA[TXFSTA] - SPI Tx FIFO status */
#define SPI0STA_TXFSTA_MSK             (0x7   << 1  )
#define SPI0STA_TXFSTA_EMPTY           (0x0   << 1  ) /* Tx FIFO empty            */
#define SPI0STA_TXFSTA_ONEBYTE         (0x1   << 1  ) /* 1 valid byte in FIFO     */
#define SPI0STA_TXFSTA_TWOBYTES        (0x2   << 1  ) /* 2 valid bytes in FIFO    */
#define SPI0STA_TXFSTA_THREEBYTES      (0x3   << 1  ) /* 3 valid bytes in FIFO    */
#define SPI0STA_TXFSTA_FOURBYTES       (0x4   << 1  ) /* 4 valid bytes in FIFO    */

/* SPI0STA[IRQ] - SPI Interrupt status */
#define SPI0STA_IRQ_BBA                (*(volatile unsigned long *) 0x42580000)
#define SPI0STA_IRQ_MSK                (0x1   << 0  )
#define SPI0STA_IRQ                    (0x1   << 0  )
#define SPI0STA_IRQ_CLR                (0x0   << 0  ) /* Cleared to 0 after reading SPI0STA. */
#define SPI0STA_IRQ_SET                (0x1   << 0  ) /* Set to 1 when an SPI based interrupt occurs. */

/* Reset Value for SPI0RX*/
#define SPI0RX_RVAL                    0x0 

/* SPI0RX[DMA_DATA_BYTE_2] - 8-bit receive buffer */
#define SPI0RX_DMA_DATA_BYTE_2_MSK     (0xFF  << 8  )

/* SPI0RX[DATA_BYTE_1] - 8-bit receive buffer */
#define SPI0RX_DATA_BYTE_1_MSK         (0xFF  << 0  )

/* Reset Value for SPI0TX*/
#define SPI0TX_RVAL                    0x0 

/* SPI0TX[DMA_DATA_BYTE_2] - 8-bit transmit buffer */
#define SPI0TX_DMA_DATA_BYTE_2_MSK     (0xFF  << 8  )

/* SPI0TX[DATA_BYTE_1] - 8-bit transmit buffer */
#define SPI0TX_DATA_BYTE_1_MSK         (0xFF  << 0  )

/* Reset Value for SPI0DIV*/
#define SPI0DIV_RVAL                   0x0 

/* SPI0DIV[CSIRQ_EN] - Enable interrupt on every CS edge in CONT mode */
#define SPI0DIV_CSIRQ_EN_BBA           (*(volatile unsigned long *) 0x425801A0)
#define SPI0DIV_CSIRQ_EN_MSK           (0x1   << 8  )
#define SPI0DIV_CSIRQ_EN               (0x1   << 8  )
#define SPI0DIV_CSIRQ_EN_DIS           (0x0   << 8  )
#define SPI0DIV_CSIRQ_EN_EN            (0x1   << 8  )

/* SPI0DIV[BCRST] - Reset Mode for CSERR */
#define SPI0DIV_BCRST_BBA              (*(volatile unsigned long *) 0x4258019C)
#define SPI0DIV_BCRST_MSK              (0x1   << 7  )
#define SPI0DIV_BCRST                  (0x1   << 7  )
#define SPI0DIV_BCRST_DIS              (0x0   << 7  )
#define SPI0DIV_BCRST_EN               (0x1   << 7  )

/* SPI0DIV[HFM] - High Frequency Mode */
#define SPI0DIV_HFM_BBA                (*(volatile unsigned long *) 0x42580198)
#define SPI0DIV_HFM_MSK                (0x1   << 6  )
#define SPI0DIV_HFM                    (0x1   << 6  )
#define SPI0DIV_HFM_DIS                (0x0   << 6  )
#define SPI0DIV_HFM_EN                 (0x1   << 6  )

/* SPI0DIV[DIV] - SPI clock divider */
#define SPI0DIV_DIV_MSK                (0x3F  << 0  )

/* Reset Value for SPI0CON*/
#define SPI0CON_RVAL                   0x0 

/* SPI0CON[MOD] - SPI IRQ mode bits */
#define SPI0CON_MOD_MSK                (0x3   << 14 )
#define SPI0CON_MOD_TX1RX1             (0x0   << 14 ) /* Tx interrupt occurs when 1 byte has been transferred. Rx interrupt occurs when 1 or more bytes have been received into the FIFO. */
#define SPI0CON_MOD_TX2RX2             (0x1   << 14 ) /* Tx interrupt occurs when 2 bytes has been transferred.  Rx interrupt occurs when 2 or more bytes have been received into the FIFO. */
#define SPI0CON_MOD_TX3RX3             (0x2   << 14 ) /* Tx interrupt occurs when 3 bytes has been transferred.  Rx interrupt occurs when 3 or more bytes have been received into the FIFO. */
#define SPI0CON_MOD_TX4RX4             (0x3   << 14 ) /* Tx interrupt occurs when 4 bytes has been transferred.  Rx interrupt occurs when the Rx FIFO is full, or 4 bytes present. */

/* SPI0CON[TFLUSH] - SPI Tx FIFO Flush enable */
#define SPI0CON_TFLUSH_BBA             (*(volatile unsigned long *) 0x42580234)
#define SPI0CON_TFLUSH_MSK             (0x1   << 13 )
#define SPI0CON_TFLUSH                 (0x1   << 13 )
#define SPI0CON_TFLUSH_DIS             (0x0   << 13 ) /* Clear this bit to disable Tx FIFO flushing. */
#define SPI0CON_TFLUSH_EN              (0x1   << 13 ) /* Set this bit to flush the Tx FIFO. This bit does not clear itself and should be toggled if a single flush is required. If this bit is left high, then either the last transmitted value or "0x00" is transmitted depending on the ZEN bit. Any writes to the Tx FIFO are ignored while this bit is set. */

/* SPI0CON[RFLUSH] - SPI Rx FIFO Flush enable */
#define SPI0CON_RFLUSH_BBA             (*(volatile unsigned long *) 0x42580230)
#define SPI0CON_RFLUSH_MSK             (0x1   << 12 )
#define SPI0CON_RFLUSH                 (0x1   << 12 )
#define SPI0CON_RFLUSH_DIS             (0x0   << 12 ) /* Clear this bit to disable Rx FIFO flushing. */
#define SPI0CON_RFLUSH_EN              (0x1   << 12 ) /* Set this bit to flush the Rx FIFO. This bit does not clear itself and should be toggled if a single flush is required. If this bit is set all incoming data is ignored and no interrupts are generated. If set and TIM = 0, a read of the Rx FIFO will initiate a transfer. */

/* SPI0CON[CON] - Continuous transfer enable */
#define SPI0CON_CON_BBA                (*(volatile unsigned long *) 0x4258022C)
#define SPI0CON_CON_MSK                (0x1   << 11 )
#define SPI0CON_CON                    (0x1   << 11 )
#define SPI0CON_CON_DIS                (0x0   << 11 ) /* DIS. Cleared by user to disable continuous transfer. Each transfer consists of a single 8-bit serial transfer. If valid data exists in the SPI0TX register, then a new transfer is initiated after a stall period of 1 serial clock cycle. */
#define SPI0CON_CON_EN                 (0x1   << 11 ) /* EN. Set by user to enable continuous transfer. In master mode, the transfer continues until no valid data is available in the Tx register. CS is asserted and remains asserted for the duration of each 8-bit serial transfer until Tx is empty. */

/* SPI0CON[LOOPBACK] - Loopback enable */
#define SPI0CON_LOOPBACK_BBA           (*(volatile unsigned long *) 0x42580228)
#define SPI0CON_LOOPBACK_MSK           (0x1   << 10 )
#define SPI0CON_LOOPBACK               (0x1   << 10 )
#define SPI0CON_LOOPBACK_DIS           (0x0   << 10 ) /* Cleared by user to be in normal mode. */
#define SPI0CON_LOOPBACK_EN            (0x1   << 10 ) /* Set by user to connect MISO to MOSI and test software. */

/* SPI0CON[OEN] - Slave MISO output enable */
#define SPI0CON_OEN_BBA                (*(volatile unsigned long *) 0x42580224)
#define SPI0CON_OEN_MSK                (0x1   << 9  )
#define SPI0CON_OEN                    (0x1   << 9  )
#define SPI0CON_OEN_DIS                (0x0   << 9  ) /* Clear this bit to disable the output driver on the MISO pin. The MISO pin will be Open-Circuit when this bit is clear. */
#define SPI0CON_OEN_EN                 (0x1   << 9  ) /* Set this bit for MISO to operate as normal. */

/* SPI0CON[RXOF] - SPIRX overflow overwrite enable */
#define SPI0CON_RXOF_BBA               (*(volatile unsigned long *) 0x42580220)
#define SPI0CON_RXOF_MSK               (0x1   << 8  )
#define SPI0CON_RXOF                   (0x1   << 8  )
#define SPI0CON_RXOF_DIS               (0x0   << 8  ) /* Cleared by user, the new serial byte received is discarded. */
#define SPI0CON_RXOF_EN                (0x1   << 8  ) /* Set by user, the valid data in the Rx register is overwritten by the new serial byte received. */

/* SPI0CON[ZEN] - Transmit zeros enable */
#define SPI0CON_ZEN_BBA                (*(volatile unsigned long *) 0x4258021C)
#define SPI0CON_ZEN_MSK                (0x1   << 7  )
#define SPI0CON_ZEN                    (0x1   << 7  )
#define SPI0CON_ZEN_DIS                (0x0   << 7  ) /* Clear this bit to transmit the last transmitted value when there is no valid data in the Tx FIFO. */
#define SPI0CON_ZEN_EN                 (0x1   << 7  ) /* Set this bit to transmit "0x00" when there is no valid data in the Tx FIFO. */

/* SPI0CON[TIM] - SPI transfer and interrupt mode */
#define SPI0CON_TIM_BBA                (*(volatile unsigned long *) 0x42580218)
#define SPI0CON_TIM_MSK                (0x1   << 6  )
#define SPI0CON_TIM                    (0x1   << 6  )
#define SPI0CON_TIM_RXRD               (0x0   << 6  ) /* Cleared by user to initiate transfer with a read of the SPI0RX register. Interrupt only occurs when Rx is full. */
#define SPI0CON_TIM_TXWR               (0x1   << 6  ) /* Set by user to initiate transfer with a write to the SPI0TX register. Interrupt only occurs when Tx is empty. */

/* SPI0CON[LSB] - LSB first transfer enable */
#define SPI0CON_LSB_BBA                (*(volatile unsigned long *) 0x42580214)
#define SPI0CON_LSB_MSK                (0x1   << 5  )
#define SPI0CON_LSB                    (0x1   << 5  )
#define SPI0CON_LSB_DIS                (0x0   << 5  ) /* MSB transmitted first    */
#define SPI0CON_LSB_EN                 (0x1   << 5  ) /* LSB transmitted first    */

/* SPI0CON[WOM] - SPI Wired Or mode */
#define SPI0CON_WOM_BBA                (*(volatile unsigned long *) 0x42580210)
#define SPI0CON_WOM_MSK                (0x1   << 4  )
#define SPI0CON_WOM                    (0x1   << 4  )
#define SPI0CON_WOM_EN                 (0x1   << 4  ) /* Enables open circuit data output enable. External pull-ups required on data out pins */
#define SPI0CON_WOM_DIS                (0x0   << 4  ) /* Normal output levels     */

/* SPI0CON[CPOL] - Serial Clock Polarity */
#define SPI0CON_CPOL_BBA               (*(volatile unsigned long *) 0x4258020C)
#define SPI0CON_CPOL_MSK               (0x1   << 3  )
#define SPI0CON_CPOL                   (0x1   << 3  )
#define SPI0CON_CPOL_LOW               (0x0   << 3  ) /* Serial clock idles low   */
#define SPI0CON_CPOL_HIGH              (0x1   << 3  ) /* Serial clock idles high  */

/* SPI0CON[CPHA] - Serial clock phase mode */
#define SPI0CON_CPHA_BBA               (*(volatile unsigned long *) 0x42580208)
#define SPI0CON_CPHA_MSK               (0x1   << 2  )
#define SPI0CON_CPHA                   (0x1   << 2  )
#define SPI0CON_CPHA_SAMPLETRAILING    (0x1   << 2  ) /* Serial clock pulses at the beginning of each serial bit transfer */
#define SPI0CON_CPHA_SAMPLELEADING     (0x0   << 2  ) /* Serial clock pulses at the end of each serial bit transfer */

/* SPI0CON[MASEN] - Master mode enable */
#define SPI0CON_MASEN_BBA              (*(volatile unsigned long *) 0x42580204)
#define SPI0CON_MASEN_MSK              (0x1   << 1  )
#define SPI0CON_MASEN                  (0x1   << 1  )
#define SPI0CON_MASEN_DIS              (0x0   << 1  ) /* Enable slave mode        */
#define SPI0CON_MASEN_EN               (0x1   << 1  ) /* Enable master mode       */

/* SPI0CON[ENABLE] - SPI enable */
#define SPI0CON_ENABLE_BBA             (*(volatile unsigned long *) 0x42580200)
#define SPI0CON_ENABLE_MSK             (0x1   << 0  )
#define SPI0CON_ENABLE                 (0x1   << 0  )
#define SPI0CON_ENABLE_DIS             (0x0   << 0  ) /* Disable the SPI          */
#define SPI0CON_ENABLE_EN              (0x1   << 0  ) /* Enable the SPI           */

/* Reset Value for SPI0DMA*/
#define SPI0DMA_RVAL                   0x0 

/* SPI0DMA[IENRXDMA] - Enable receive DMA request */
#define SPI0DMA_IENRXDMA_BBA           (*(volatile unsigned long *) 0x42580288)
#define SPI0DMA_IENRXDMA_MSK           (0x1   << 2  )
#define SPI0DMA_IENRXDMA               (0x1   << 2  )
#define SPI0DMA_IENRXDMA_DIS           (0x0   << 2  ) /* Disable RX DMA Interrupt */
#define SPI0DMA_IENRXDMA_EN            (0x1   << 2  ) /* Enable RX DMA Interrupt  */

/* SPI0DMA[IENTXDMA] - Enable transmit DMA request */
#define SPI0DMA_IENTXDMA_BBA           (*(volatile unsigned long *) 0x42580284)
#define SPI0DMA_IENTXDMA_MSK           (0x1   << 1  )
#define SPI0DMA_IENTXDMA               (0x1   << 1  )
#define SPI0DMA_IENTXDMA_DIS           (0x0   << 1  ) /* Disable TX DMA Interrupt */
#define SPI0DMA_IENTXDMA_EN            (0x1   << 1  ) /* Enable TX DMA Interrupt  */

/* SPI0DMA[ENABLE] - Enable DMA for data transfer */
#define SPI0DMA_ENABLE_BBA             (*(volatile unsigned long *) 0x42580280)
#define SPI0DMA_ENABLE_MSK             (0x1   << 0  )
#define SPI0DMA_ENABLE                 (0x1   << 0  )
#define SPI0DMA_ENABLE_DIS             (0x0   << 0  )
#define SPI0DMA_ENABLE_EN              (0x1   << 0  )

/* Reset Value for SPI0CNT*/
#define SPI0CNT_RVAL                   0x0 

/* SPI0CNT[COUNT] - Transfer byte count */
#define SPI0CNT_COUNT_MSK              (0xFF  << 0  )

/* Reset Value for SPI1STA*/
#define SPI1STA_RVAL                   0x0 

/* SPI1STA[CSRSG] - Detected a rising edge on CS, in CONT mode */
#define SPI1STA_CSRSG_BBA              (*(volatile unsigned long *) 0x42600038)
#define SPI1STA_CSRSG_MSK              (0x1   << 14 )
#define SPI1STA_CSRSG                  (0x1   << 14 )
#define SPI1STA_CSRSG_CLR              (0x0   << 14 ) /* Cleared to 0 when the Status register is read */
#define SPI1STA_CSRSG_SET              (0x1   << 14 ) /* Set to 1 when there was a rising edge in CS line, when the device was in master mode, continuous transfer, High Frequency mode and CSIRQ_EN was asserted. */

/* SPI1STA[CSFLG] - Detected a falling edge on CS, in CONT mode */
#define SPI1STA_CSFLG_BBA              (*(volatile unsigned long *) 0x42600034)
#define SPI1STA_CSFLG_MSK              (0x1   << 13 )
#define SPI1STA_CSFLG                  (0x1   << 13 )
#define SPI1STA_CSFLG_CLR              (0x0   << 13 ) /* Cleared to 0 when the Status register is read. */
#define SPI1STA_CSFLG_SET              (0x1   << 13 ) /* Set to 1 when there was a falling edge in CS line, when the device was in master mode, continuous transfer, High Frequency mode and CSIRQ_EN was asserted. */

/* SPI1STA[CSERR] - Detected a CS error condition */
#define SPI1STA_CSERR_BBA              (*(volatile unsigned long *) 0x42600030)
#define SPI1STA_CSERR_MSK              (0x1   << 12 )
#define SPI1STA_CSERR                  (0x1   << 12 )
#define SPI1STA_CSERR_CLR              (0x0   << 12 ) /* Cleared to 0 when the Status register is read. */
#define SPI1STA_CSERR_SET              (0x1   << 12 ) /* Set to 1 when the CS line was de-asserted abruptly, even before the full-byte of data was transmitted completely. This bit will cause an interrupt. */

/* SPI1STA[RXS] - SPI Rx FIFO excess bytes present */
#define SPI1STA_RXS_BBA                (*(volatile unsigned long *) 0x4260002C)
#define SPI1STA_RXS_MSK                (0x1   << 11 )
#define SPI1STA_RXS                    (0x1   << 11 )
#define SPI1STA_RXS_CLR                (0x0   << 11 ) /* Cleared to 0 when the number of bytes in the FIFO is equal or less than the number in SPI1CON[15:14]. */
#define SPI1STA_RXS_SET                (0x1   << 11 ) /* Set to 1 when there are more bytes in the Rx FIFO than indicated in the MOD bits in SPI1CON. */

/* SPI1STA[RXFSTA] - SPI Rx FIFO status */
#define SPI1STA_RXFSTA_MSK             (0x7   << 8  )
#define SPI1STA_RXFSTA_EMPTY           (0x0   << 8  ) /* Rx FIFO empty            */
#define SPI1STA_RXFSTA_ONEBYTE         (0x1   << 8  ) /* 1 valid byte in FIFO     */
#define SPI1STA_RXFSTA_TWOBYTES        (0x2   << 8  ) /* 2 valid bytes in the FIFO */
#define SPI1STA_RXFSTA_THREEBYTES      (0x3   << 8  ) /* 3 valid bytes in the FIFO */
#define SPI1STA_RXFSTA_FOURBYTES       (0x4   << 8  ) /* 4 valid bytes in the FIFO */

/* SPI1STA[RXOF] - SPI Rx FIFO overflow */
#define SPI1STA_RXOF_BBA               (*(volatile unsigned long *) 0x4260001C)
#define SPI1STA_RXOF_MSK               (0x1   << 7  )
#define SPI1STA_RXOF                   (0x1   << 7  )
#define SPI1STA_RXOF_CLR               (0x0   << 7  ) /* Cleared to 0 when the SPI1STA register is read. */
#define SPI1STA_RXOF_SET               (0x1   << 7  ) /* Set to 1 when the Rx FIFO was already full when new data was loaded to the FIFO. This bit generates an interrupt except when RFLUSH is set in SPI1CON. */

/* SPI1STA[RX] - SPI Rx IRQ */
#define SPI1STA_RX_BBA                 (*(volatile unsigned long *) 0x42600018)
#define SPI1STA_RX_MSK                 (0x1   << 6  )
#define SPI1STA_RX                     (0x1   << 6  )
#define SPI1STA_RX_CLR                 (0x0   << 6  ) /* Cleared to 0 when the SPI1STA register is read. */
#define SPI1STA_RX_SET                 (0x1   << 6  ) /* Set to 1 when TIM in SPI1CON is cleared and the required number of bytes have been received. */

/* SPI1STA[TX] - SPI Tx IRQ */
#define SPI1STA_TX_BBA                 (*(volatile unsigned long *) 0x42600014)
#define SPI1STA_TX_MSK                 (0x1   << 5  )
#define SPI1STA_TX                     (0x1   << 5  )
#define SPI1STA_TX_CLR                 (0x0   << 5  ) /* CLR. Cleared to 0 when the SPI1STA register is read. */
#define SPI1STA_TX_SET                 (0x1   << 5  ) /* SET. Set to 1 when a transmit interrupt occurs. This bit is set when TIM in SPI1CON is set and the required number of bytes have been transmitted. */

/* SPI1STA[TXUR] - SPI Tx FIFO underflow */
#define SPI1STA_TXUR_BBA               (*(volatile unsigned long *) 0x42600010)
#define SPI1STA_TXUR_MSK               (0x1   << 4  )
#define SPI1STA_TXUR                   (0x1   << 4  )
#define SPI1STA_TXUR_CLR               (0x0   << 4  ) /* Cleared to 0 when the SPI1STA register is read. */
#define SPI1STA_TXUR_SET               (0x1   << 4  ) /* Set to 1 when a transmit is initiated without any valid data in the Tx FIFO. This bit generates an interrupt except when TFLUSH is set in SPI1CON. */

/* SPI1STA[TXFSTA] - SPI Tx FIFO status */
#define SPI1STA_TXFSTA_MSK             (0x7   << 1  )
#define SPI1STA_TXFSTA_EMPTY           (0x0   << 1  ) /* Tx FIFO empty            */
#define SPI1STA_TXFSTA_ONEBYTE         (0x1   << 1  ) /* 1 valid byte in FIFO     */
#define SPI1STA_TXFSTA_TWOBYTES        (0x2   << 1  ) /* 2 valid bytes in FIFO    */
#define SPI1STA_TXFSTA_THREEBYTES      (0x3   << 1  ) /* 3 valid bytes in FIFO    */
#define SPI1STA_TXFSTA_FOURBYTES       (0x4   << 1  ) /* 4 valid bytes in FIFO    */

/* SPI1STA[IRQ] - SPI Interrupt status */
#define SPI1STA_IRQ_BBA                (*(volatile unsigned long *) 0x42600000)
#define SPI1STA_IRQ_MSK                (0x1   << 0  )
#define SPI1STA_IRQ                    (0x1   << 0  )
#define SPI1STA_IRQ_CLR                (0x0   << 0  ) /* Cleared to 0 after reading SPI1STA. */
#define SPI1STA_IRQ_SET                (0x1   << 0  ) /* Set to 1 when an SPI based interrupt occurs. */

/* Reset Value for SPI1RX*/
#define SPI1RX_RVAL                    0x0 

/* SPI1RX[DMA_DATA_BYTE_2] - 8-bit receive buffer */
#define SPI1RX_DMA_DATA_BYTE_2_MSK     (0xFF  << 8  )

/* SPI1RX[DATA_BYTE_1] - 8-bit receive buffer */
#define SPI1RX_DATA_BYTE_1_MSK         (0xFF  << 0  )

/* Reset Value for SPI1TX*/
#define SPI1TX_RVAL                    0x0 

/* SPI1TX[DMA_DATA_BYTE_2] - 8-bit transmit buffer */
#define SPI1TX_DMA_DATA_BYTE_2_MSK     (0xFF  << 8  )

/* SPI1TX[DATA_BYTE_1] - 8-bit transmit buffer */
#define SPI1TX_DATA_BYTE_1_MSK         (0xFF  << 0  )

/* Reset Value for SPI1DIV*/
#define SPI1DIV_RVAL                   0x0 

/* SPI1DIV[CSIRQ_EN] - Enable interrupt on every CS edge in CONT mode */
#define SPI1DIV_CSIRQ_EN_BBA           (*(volatile unsigned long *) 0x426001A0)
#define SPI1DIV_CSIRQ_EN_MSK           (0x1   << 8  )
#define SPI1DIV_CSIRQ_EN               (0x1   << 8  )
#define SPI1DIV_CSIRQ_EN_DIS           (0x0   << 8  )
#define SPI1DIV_CSIRQ_EN_EN            (0x1   << 8  )

/* SPI1DIV[BCRST] - Reset Mode for CSERR */
#define SPI1DIV_BCRST_BBA              (*(volatile unsigned long *) 0x4260019C)
#define SPI1DIV_BCRST_MSK              (0x1   << 7  )
#define SPI1DIV_BCRST                  (0x1   << 7  )
#define SPI1DIV_BCRST_DIS              (0x0   << 7  )
#define SPI1DIV_BCRST_EN               (0x1   << 7  )

/* SPI1DIV[HFM] - High Frequency Mode */
#define SPI1DIV_HFM_BBA                (*(volatile unsigned long *) 0x42600198)
#define SPI1DIV_HFM_MSK                (0x1   << 6  )
#define SPI1DIV_HFM                    (0x1   << 6  )
#define SPI1DIV_HFM_DIS                (0x0   << 6  )
#define SPI1DIV_HFM_EN                 (0x1   << 6  )

/* SPI1DIV[DIV] - SPI clock divider */
#define SPI1DIV_DIV_MSK                (0x3F  << 0  )

/* Reset Value for SPI1CON*/
#define SPI1CON_RVAL                   0x0 

/* SPI1CON[MOD] - SPI IRQ mode bits */
#define SPI1CON_MOD_MSK                (0x3   << 14 )
#define SPI1CON_MOD_TX1RX1             (0x0   << 14 ) /* Tx interrupt occurs when 1 byte has been transferred. Rx interrupt occurs when 1 or more bytes have been received into the FIFO. */
#define SPI1CON_MOD_TX2RX2             (0x1   << 14 ) /* Tx interrupt occurs when 2 bytes has been transferred.  Rx interrupt occurs when 2 or more bytes have been received into the FIFO. */
#define SPI1CON_MOD_TX3RX3             (0x2   << 14 ) /* Tx interrupt occurs when 3 bytes has been transferred.  Rx interrupt occurs when 3 or more bytes have been received into the FIFO. */
#define SPI1CON_MOD_TX4RX4             (0x3   << 14 ) /* Tx interrupt occurs when 4 bytes has been transferred.  Rx interrupt occurs when the Rx FIFO is full, or 4 bytes present. */

/* SPI1CON[TFLUSH] - SPI Tx FIFO Flush enable */
#define SPI1CON_TFLUSH_BBA             (*(volatile unsigned long *) 0x42600234)
#define SPI1CON_TFLUSH_MSK             (0x1   << 13 )
#define SPI1CON_TFLUSH                 (0x1   << 13 )
#define SPI1CON_TFLUSH_DIS             (0x0   << 13 ) /* Clear this bit to disable Tx FIFO flushing. */
#define SPI1CON_TFLUSH_EN              (0x1   << 13 ) /* Set this bit to flush the Tx FIFO. This bit does not clear itself and should be toggled if a single flush is required. If this bit is left high, then either the last transmitted value or "0x00" is transmitted depending on the ZEN bit. Any writes to the Tx FIFO are ignored while this bit is set. */

/* SPI1CON[RFLUSH] - SPI Rx FIFO Flush enable */
#define SPI1CON_RFLUSH_BBA             (*(volatile unsigned long *) 0x42600230)
#define SPI1CON_RFLUSH_MSK             (0x1   << 12 )
#define SPI1CON_RFLUSH                 (0x1   << 12 )
#define SPI1CON_RFLUSH_DIS             (0x0   << 12 ) /* Clear this bit to disable Rx FIFO flushing. */
#define SPI1CON_RFLUSH_EN              (0x1   << 12 ) /* Set this bit to flush the Rx FIFO. This bit does not clear itself and should be toggled if a single flush is required. If this bit is set all incoming data is ignored and no interrupts are generated. If set and TIM = 0, a read of the Rx FIFO will initiate a transfer. */

/* SPI1CON[CON] - Continuous transfer enable */
#define SPI1CON_CON_BBA                (*(volatile unsigned long *) 0x4260022C)
#define SPI1CON_CON_MSK                (0x1   << 11 )
#define SPI1CON_CON                    (0x1   << 11 )
#define SPI1CON_CON_DIS                (0x0   << 11 ) /* DIS. Cleared by user to disable continuous transfer. Each transfer consists of a single 8-bit serial transfer. If valid data exists in the SPI1TX register, then a new transfer is initiated after a stall period of 1 serial clock cycle. */
#define SPI1CON_CON_EN                 (0x1   << 11 ) /* EN. Set by user to enable continuous transfer. In master mode, the transfer continues until no valid data is available in the Tx register. CS is asserted and remains asserted for the duration of each 8-bit serial transfer until Tx is empty. */

/* SPI1CON[LOOPBACK] - Loopback enable */
#define SPI1CON_LOOPBACK_BBA           (*(volatile unsigned long *) 0x42600228)
#define SPI1CON_LOOPBACK_MSK           (0x1   << 10 )
#define SPI1CON_LOOPBACK               (0x1   << 10 )
#define SPI1CON_LOOPBACK_DIS           (0x0   << 10 ) /* Cleared by user to be in normal mode. */
#define SPI1CON_LOOPBACK_EN            (0x1   << 10 ) /* Set by user to connect MISO to MOSI and test software. */

/* SPI1CON[OEN] - Slave MISO output enable */
#define SPI1CON_OEN_BBA                (*(volatile unsigned long *) 0x42600224)
#define SPI1CON_OEN_MSK                (0x1   << 9  )
#define SPI1CON_OEN                    (0x1   << 9  )
#define SPI1CON_OEN_DIS                (0x0   << 9  ) /* Clear this bit to disable the output driver on the MISO pin. The MISO pin will be Open-Circuit when this bit is clear. */
#define SPI1CON_OEN_EN                 (0x1   << 9  ) /* Set this bit for MISO to operate as normal. */

/* SPI1CON[RXOF] - SPIRX overflow overwrite enable */
#define SPI1CON_RXOF_BBA               (*(volatile unsigned long *) 0x42600220)
#define SPI1CON_RXOF_MSK               (0x1   << 8  )
#define SPI1CON_RXOF                   (0x1   << 8  )
#define SPI1CON_RXOF_DIS               (0x0   << 8  ) /* Cleared by user, the new serial byte received is discarded. */
#define SPI1CON_RXOF_EN                (0x1   << 8  ) /* Set by user, the valid data in the Rx register is overwritten by the new serial byte received. */

/* SPI1CON[ZEN] - Transmit zeros enable */
#define SPI1CON_ZEN_BBA                (*(volatile unsigned long *) 0x4260021C)
#define SPI1CON_ZEN_MSK                (0x1   << 7  )
#define SPI1CON_ZEN                    (0x1   << 7  )
#define SPI1CON_ZEN_DIS                (0x0   << 7  ) /* Clear this bit to transmit the last transmitted value when there is no valid data in the Tx FIFO. */
#define SPI1CON_ZEN_EN                 (0x1   << 7  ) /* Set this bit to transmit "0x00" when there is no valid data in the Tx FIFO. */

/* SPI1CON[TIM] - SPI transfer and interrupt mode */
#define SPI1CON_TIM_BBA                (*(volatile unsigned long *) 0x42600218)
#define SPI1CON_TIM_MSK                (0x1   << 6  )
#define SPI1CON_TIM                    (0x1   << 6  )
#define SPI1CON_TIM_RXRD               (0x0   << 6  ) /* Cleared by user to initiate transfer with a read of the SPIRX register. Interrupt only occurs when Rx is full. */
#define SPI1CON_TIM_TXWR               (0x1   << 6  ) /* Set by user to initiate transfer with a write to the SPITX register. Interrupt only occurs when Tx is empty. */

/* SPI1CON[LSB] - LSB first transfer enable */
#define SPI1CON_LSB_BBA                (*(volatile unsigned long *) 0x42600214)
#define SPI1CON_LSB_MSK                (0x1   << 5  )
#define SPI1CON_LSB                    (0x1   << 5  )
#define SPI1CON_LSB_DIS                (0x0   << 5  ) /* MSB transmitted first    */
#define SPI1CON_LSB_EN                 (0x1   << 5  ) /* LSB transmitted first    */

/* SPI1CON[WOM] - SPI Wired Or mode */
#define SPI1CON_WOM_BBA                (*(volatile unsigned long *) 0x42600210)
#define SPI1CON_WOM_MSK                (0x1   << 4  )
#define SPI1CON_WOM                    (0x1   << 4  )
#define SPI1CON_WOM_DIS                (0x0   << 4  ) /* Normal output levels     */
#define SPI1CON_WOM_EN                 (0x1   << 4  ) /* Enables open circuit data output enable. External pull-ups required on data out pins */

/* SPI1CON[CPOL] - Serial Clock Polarity */
#define SPI1CON_CPOL_BBA               (*(volatile unsigned long *) 0x4260020C)
#define SPI1CON_CPOL_MSK               (0x1   << 3  )
#define SPI1CON_CPOL                   (0x1   << 3  )
#define SPI1CON_CPOL_LOW               (0x0   << 3  ) /* Serial clock idles low   */
#define SPI1CON_CPOL_HIGH              (0x1   << 3  ) /* Serial clock idles high  */

/* SPI1CON[CPHA] - Serial clock phase mode */
#define SPI1CON_CPHA_BBA               (*(volatile unsigned long *) 0x42600208)
#define SPI1CON_CPHA_MSK               (0x1   << 2  )
#define SPI1CON_CPHA                   (0x1   << 2  )
#define SPI1CON_CPHA_SAMPLELEADING     (0x0   << 2  ) /* Serial clock pulses at the end of each serial bit transfer */
#define SPI1CON_CPHA_SAMPLETRAILING    (0x1   << 2  ) /* Serial clock pulses at the beginning of each serial bit transfer */

/* SPI1CON[MASEN] - Master mode enable */
#define SPI1CON_MASEN_BBA              (*(volatile unsigned long *) 0x42600204)
#define SPI1CON_MASEN_MSK              (0x1   << 1  )
#define SPI1CON_MASEN                  (0x1   << 1  )
#define SPI1CON_MASEN_DIS              (0x0   << 1  ) /* Enable slave mode        */
#define SPI1CON_MASEN_EN               (0x1   << 1  ) /* Enable master mode       */

/* SPI1CON[ENABLE] - SPI enable */
#define SPI1CON_ENABLE_BBA             (*(volatile unsigned long *) 0x42600200)
#define SPI1CON_ENABLE_MSK             (0x1   << 0  )
#define SPI1CON_ENABLE                 (0x1   << 0  )
#define SPI1CON_ENABLE_DIS             (0x0   << 0  ) /* Disable the SPI          */
#define SPI1CON_ENABLE_EN              (0x1   << 0  ) /* Enable the SPI           */

/* Reset Value for SPI1DMA*/
#define SPI1DMA_RVAL                   0x0 

/* SPI1DMA[IENRXDMA] - Enable receive DMA request */
#define SPI1DMA_IENRXDMA_BBA           (*(volatile unsigned long *) 0x42600288)
#define SPI1DMA_IENRXDMA_MSK           (0x1   << 2  )
#define SPI1DMA_IENRXDMA               (0x1   << 2  )
#define SPI1DMA_IENRXDMA_DIS           (0x0   << 2  ) /* Disable RX DMA Interrupt */
#define SPI1DMA_IENRXDMA_EN            (0x1   << 2  ) /* Enable RX DMA Interrupt  */

/* SPI1DMA[IENTXDMA] - Enable transmit DMA request */
#define SPI1DMA_IENTXDMA_BBA           (*(volatile unsigned long *) 0x42600284)
#define SPI1DMA_IENTXDMA_MSK           (0x1   << 1  )
#define SPI1DMA_IENTXDMA               (0x1   << 1  )
#define SPI1DMA_IENTXDMA_DIS           (0x0   << 1  ) /* Disable TX DMA Interrupt */
#define SPI1DMA_IENTXDMA_EN            (0x1   << 1  ) /* Enable TX DMA Interrupt  */

/* SPI1DMA[ENABLE] - Enable DMA for data transfer */
#define SPI1DMA_ENABLE_BBA             (*(volatile unsigned long *) 0x42600280)
#define SPI1DMA_ENABLE_MSK             (0x1   << 0  )
#define SPI1DMA_ENABLE                 (0x1   << 0  )
#define SPI1DMA_ENABLE_DIS             (0x0   << 0  )
#define SPI1DMA_ENABLE_EN              (0x1   << 0  )

/* Reset Value for SPI1CNT*/
#define SPI1CNT_RVAL                   0x0 

/* SPI1CNT[COUNT] - Transfer byte count */
#define SPI1CNT_COUNT_MSK              (0xFF  << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        ADC_CORE                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief ADC (MMR_ADC)
  */

typedef struct MMR_ADC {                    /*!< MMR_ADC Structure                     */
  __IO uint16_t  ADCCON;                    /*!< ADC Configuration                     */
  __I  uint16_t  RESERVED0[8005];
  __IO uint32_t  ADCDAT[28];                /*!< ADCx Data and flags                   */
  __I  uint32_t  RESERVED1[4];
  __IO uint16_t  ADCCHA;                    /*!< ADC Channel Select                    */
  __I  uint16_t  RESERVED2[3];
  __IO uint32_t  ADCSEQ;                    /*!< ADC Sequencer Control                 */
  __IO uint32_t  ADCSEQC;                   /*!< ADC Sequencer Configuration           */
  __IO uint16_t  ADCGN;                     /*!< User gain adjust                      */
  __I  uint16_t  RESERVED3;
  __IO uint16_t  ADCOF;                     /*!< User offset adjust                    */
  __I  uint16_t  RESERVED4;
  __IO uint32_t  ADCCMP;                    /*!< Digital comparator configuration      */
  __IO uint32_t  ADCCNVC;                   /*!< ADC conversion  configuration         */
} MMR_ADC_t;

/* Reset Value for ADCCON*/
#define ADCCON_RVAL                    0x280 

/* ADCCON[SOFT_RESET] - software reset ADC */
#define ADCCON_SOFT_RESET_MSK          (0x3F  << 10 )

/* ADCCON[PUP] - ADC power up */
#define ADCCON_PUP_BBA                 (*(volatile unsigned long *) 0x43042EA4)
#define ADCCON_PUP_MSK                 (0x1   << 9  )
#define ADCCON_PUP                     (0x1   << 9  )

/* ADCCON[REFB_PUP] - ADC reference buffer power up */
#define ADCCON_REFB_PUP_BBA            (*(volatile unsigned long *) 0x43042E9C)
#define ADCCON_REFB_PUP_MSK            (0x1   << 7  )
#define ADCCON_REFB_PUP                (0x1   << 7  )

/* ADCCON[Restart_ADC] - Restart ADC, reset Analog Part of ADC */
#define ADCCON_Restart_ADC_BBA         (*(volatile unsigned long *) 0x43042E98)
#define ADCCON_Restart_ADC_MSK         (0x1   << 6  )
#define ADCCON_Restart_ADC             (0x1   << 6  )

/* ADCCON[SEQ_DMA] - DMA request enable for ADC sequence conversion */
#define ADCCON_SEQ_DMA_BBA             (*(volatile unsigned long *) 0x43042E90)
#define ADCCON_SEQ_DMA_MSK             (0x1   << 4  )
#define ADCCON_SEQ_DMA                 (0x1   << 4  )

/* ADCCON[CNV_DMA] - DMA request enable for ADC non-sequence conversion */
#define ADCCON_CNV_DMA_BBA             (*(volatile unsigned long *) 0x43042E8C)
#define ADCCON_CNV_DMA_MSK             (0x1   << 3  )
#define ADCCON_CNV_DMA                 (0x1   << 3  )

/* ADCCON[C_TYPE] - ADC conversion type */
#define ADCCON_C_TYPE_MSK              (0x7   << 0  )
#define ADCCON_C_TYPE_NO               (0x0   << 0  ) /* No conversion            */
#define ADCCON_C_TYPE_DIO              (0x1   << 0  ) /* DIO pin starts conversion (P2.4) */
#define ADCCON_C_TYPE_SINGLE           (0x2   << 0  ) /* Single conversion        */
#define ADCCON_C_TYPE_CONT             (0x3   << 0  ) /* Continuous conversion (use this mode for the sequencer) */
#define ADCCON_C_TYPE_PLA              (0x4   << 0  ) /* PLA conversion           */

/* Reset Value for ADCDAT*/
#define ADCDAT_RVAL                    0x0 

/* ADCDAT[DAT] - ADCx data */
#define ADCDAT_DAT_MSK                 (0xFFFFFFF << 4  )

/* ADCDAT[VALID] - Flag indicating if data is valid. */
#define ADCDAT_VALID_BBA               (*(volatile unsigned long *) 0x430C000C)
#define ADCDAT_VALID_MSK               (0x1   << 3  )
#define ADCDAT_VALID                   (0x1   << 3  )
#define ADCDAT_VALID_CLR               (0x0   << 3  ) /* Data is Invalid          */
#define ADCDAT_VALID_SET               (0x1   << 3  ) /* Data is Valid            */

/* ADCDAT[OLD] - Flag data has already been read. */
#define ADCDAT_OLD_BBA                 (*(volatile unsigned long *) 0x430C0008)
#define ADCDAT_OLD_MSK                 (0x1   << 2  )
#define ADCDAT_OLD                     (0x1   << 2  )
#define ADCDAT_OLD_CLR                 (0x0   << 2  ) /* Last data has not been read */
#define ADCDAT_OLD_SET                 (0x1   << 2  ) /* Last data already read   */

/* Reset Value for ADCCHA*/
#define ADCCHA_RVAL                    0x111F 

/* ADCCHA[ADCCN] - Selects channel for ADC negative input */
#define ADCCHA_ADCCN_MSK               (0x1F  << 8  )
#define ADCCHA_ADCCN_AIN0              (0x0   << 8  ) /* AIN0                     */
#define ADCCHA_ADCCN_AIN1              (0x1   << 8  ) /* AIN1                     */
#define ADCCHA_ADCCN_AIN2              (0x2   << 8  ) /* AIN2                     */
#define ADCCHA_ADCCN_AIN3              (0x3   << 8  ) /* AIN3                     */
#define ADCCHA_ADCCN_AIN4              (0x4   << 8  ) /* AIN4                     */
#define ADCCHA_ADCCN_AIN5              (0x5   << 8  ) /* AIN5                     */
#define ADCCHA_ADCCN_AIN6              (0x6   << 8  ) /* AIN6                     */
#define ADCCHA_ADCCN_AIN7              (0x7   << 8  ) /* AIN7                     */
#define ADCCHA_ADCCN_AIN8              (0x8   << 8  ) /* AIN8                     */
#define ADCCHA_ADCCN_AIN9              (0x9   << 8  ) /* AIN9                     */
#define ADCCHA_ADCCN_AIN10             (0xA   << 8  ) /* AIN10                    */
#define ADCCHA_ADCCN_AIN11             (0xB   << 8  ) /* AIN11                    */
#define ADCCHA_ADCCN_AIN12             (0xC   << 8  ) /* AIN12                    */
#define ADCCHA_ADCCN_AIN13             (0xD   << 8  ) /* AIN13                    */
#define ADCCHA_ADCCN_AIN14             (0xE   << 8  ) /* AIN14                    */
#define ADCCHA_ADCCN_AIN15             (0xF   << 8  ) /* AIN15                    */
#define ADCCHA_ADCCN_VREFP_NADC        (0x10  << 8  ) /* VREFP_NADC: Connect ADC_REFP to negative input. */
#define ADCCHA_ADCCN_VREFN_NADC        (0x11  << 8  ) /* VREFN_NADC: Connect ADC_REFN to negative input. Use This setting for single ended measurements. */
#define ADCCHA_ADCCN_AGND              (0x12  << 8  ) /* AGND                     */
#define ADCCHA_ADCCN_PGND              (0x13  << 8  ) /* PGND                     */

/* ADCCHA[ADCCP] - Select ADC channel */
#define ADCCHA_ADCCP_MSK               (0x1F  << 0  )
#define ADCCHA_ADCCP_AIN0              (0x0   << 0  ) /* AIN0                     */
#define ADCCHA_ADCCP_AIN1              (0x1   << 0  ) /* AIN1                     */
#define ADCCHA_ADCCP_AIN2              (0x2   << 0  ) /* AIN2                     */
#define ADCCHA_ADCCP_AIN3              (0x3   << 0  ) /* AIN3                     */
#define ADCCHA_ADCCP_AIN4              (0x4   << 0  ) /* AIN4                     */
#define ADCCHA_ADCCP_AIN5              (0x5   << 0  ) /* AIN5                     */
#define ADCCHA_ADCCP_AIN6              (0x6   << 0  ) /* AIN6                     */
#define ADCCHA_ADCCP_AIN7              (0x7   << 0  ) /* AIN7                     */
#define ADCCHA_ADCCP_AIN8              (0x8   << 0  ) /* AIN8                     */
#define ADCCHA_ADCCP_AIN9              (0x9   << 0  ) /* AIN9                     */
#define ADCCHA_ADCCP_AIN10             (0xA   << 0  ) /* AIN10                    */
#define ADCCHA_ADCCP_AIN11             (0xB   << 0  ) /* AIN11                    */
#define ADCCHA_ADCCP_AIN12             (0xC   << 0  ) /* AIN12                    */
#define ADCCHA_ADCCP_AIN13             (0xD   << 0  ) /* AIN13                    */
#define ADCCHA_ADCCP_AIN14             (0xE   << 0  ) /* AIN14                    */
#define ADCCHA_ADCCP_AIN15             (0xF   << 0  ) /* AIN15                    */
#define ADCCHA_ADCCP_TEMP_SENSOR       (0x16  << 0  ) /* TEMP_SENSOR              */
#define ADCCHA_ADCCP_VREFP_PADC        (0x17  << 0  ) /* VREFP_PADC: Connect ADC_REFP to positive input. Note: This pin should not be measured relative to AGND. This selection is intended for measuring the differential voltage between the negative input and ADC_REFP. */
#define ADCCHA_ADCCP_PVDD_IDAC2        (0x18  << 0  ) /* PVDD_IDAC2: Use this to measure the PVDD supply voltage for IDAC2 */
#define ADCCHA_ADCCP_IOVDD_2           (0x19  << 0  ) /* IOVDD_2: Use this to measure half of the IOVDD supply voltage */
#define ADCCHA_ADCCP_AVDD_2            (0x1A  << 0  ) /* AVDD_2: Use this to measure half of the AVDD supply voltage. */
#define ADCCHA_ADCCP_VREFN_PADC        (0x1B  << 0  ) /* VREFN_PADC: Connect ADC_REFN to positive input. */

/* Reset Value for ADCSEQ*/
#define ADCSEQ_RVAL                    0x0 

/* ADCSEQ[ST] - Sequence restart, used to force sequence to start at first channel when sequence is working */
#define ADCSEQ_ST_BBA                  (*(volatile unsigned long *) 0x430C117C)
#define ADCSEQ_ST_MSK                  (0x1   << 31 )
#define ADCSEQ_ST                      (0x1   << 31 )

/* ADCSEQ[EN] - Sequence enable */
#define ADCSEQ_EN_BBA                  (*(volatile unsigned long *) 0x430C1178)
#define ADCSEQ_EN_MSK                  (0x1   << 30 )
#define ADCSEQ_EN                      (0x1   << 30 )

/* ADCSEQ[CH] - Select channels included in sequence operation. */
#define ADCSEQ_CH_MSK                  (0x1FFFFFFF << 0  )

/* Reset Value for ADCSEQC*/
#define ADCSEQC_RVAL                   0x8C631 

/* ADCSEQC[T] - Define programmable delay of 0 to 254 between sequences. A delay 255 will cause a halt after one sequence. */
#define ADCSEQC_T_MSK                  (0xFF  << 20 )

/* ADCSEQC[DIF6] - Selects differential mode negative input for AIN6 in the sequence. */
#define ADCSEQC_DIF6_MSK               (0x1F  << 15 )

/* ADCSEQC[DIF4] - Selects differential mode negative input for AIN4 in the sequence. */
#define ADCSEQC_DIF4_MSK               (0x1F  << 10 )

/* ADCSEQC[DIF2] - Selects differential mode negative input for AIN2 in the sequence. */
#define ADCSEQC_DIF2_MSK               (0x1F  << 5  )

/* ADCSEQC[DIF0] - Selects differential mode negative input for AIN0 in the sequence. */
#define ADCSEQC_DIF0_MSK               (0x1F  << 0  )

/* Reset Value for ADCGN*/
#define ADCGN_RVAL                     0x2000 

/* ADCGN[GN] - User gain register */
#define ADCGN_GN_MSK                   (0x3FFF << 0  )

/* Reset Value for ADCOF*/
#define ADCOF_RVAL                     0x2000 

/* ADCOF[OF] - User offset register */
#define ADCOF_OF_MSK                   (0x3FFF << 0  )

/* Reset Value for ADCCMP*/
#define ADCCMP_RVAL                    0x0 

/* ADCCMP[THR] - Digital compare threshold */
#define ADCCMP_THR_MSK                 (0xFFFF << 2  )

/* ADCCMP[DIR] - Select digital comparator direction */
#define ADCCMP_DIR_BBA                 (*(volatile unsigned long *) 0x430C1304)
#define ADCCMP_DIR_MSK                 (0x1   << 1  )
#define ADCCMP_DIR                     (0x1   << 1  )
#define ADCCMP_DIR_DIS                 (0x0   << 1  ) /* ADCTH less than channel 4 data */
#define ADCCMP_DIR_EN                  (0x1   << 1  ) /* ADCTH larger than channel 4 data */

/* ADCCMP[EN] - Digital comparator enable */
#define ADCCMP_EN_BBA                  (*(volatile unsigned long *) 0x430C1300)
#define ADCCMP_EN_MSK                  (0x1   << 0  )
#define ADCCMP_EN                      (0x1   << 0  )
#define ADCCMP_EN_DIS                  (0x0   << 0  ) /* Disable                  */
#define ADCCMP_EN_EN                   (0x1   << 0  ) /* Enable                   */

/* Reset Value for ADCCNVC*/
#define ADCCNVC_RVAL                   0xA00C8 

/* ADCCNVC[CNVD] - Configure ADC Acquisition time and sampling time */
#define ADCCNVC_CNVD_MSK               (0x3FF << 16 )

/* ADCCNVC[CNVC] - Configure Conversion frequency */
#define ADCCNVC_CNVC_MSK               (0x3FF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        VDAC                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief VDAC (MMR_VDAC)
  */

typedef struct MMR_VDAC {                   /*!< MMR_VDAC Structure           */
  __IO uint16_t  DACCON;                    /*!< DAC control register         */
  __I  uint16_t  RESERVED0[8193];
  __IO uint32_t  DACDAT;                    /*!< DAC data register            */
} MMR_VDAC_t;

/* Reset Value for DAC0CON*/
#define DAC0CON_RVAL                   0x100 

/* DAC0CON[PD] - DAC0 power down */
#define DAC0CON_PD_BBA                 (*(volatile unsigned long *) 0x43048020)
#define DAC0CON_PD_MSK                 (0x1   << 8  )
#define DAC0CON_PD                     (0x1   << 8  )

/* DAC0CON[EN] - DAC0 enable */
#define DAC0CON_EN_BBA                 (*(volatile unsigned long *) 0x43048010)
#define DAC0CON_EN_MSK                 (0x1   << 4  )
#define DAC0CON_EN                     (0x1   << 4  )

/* DAC0CON[RN] - DAC0 reference selection */
#define DAC0CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC0DAT*/
#define DAC0DAT_RVAL                   0x0 

/* DAC0DAT[DAT] - DAC0 data */
#define DAC0DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC1CON*/
#define DAC1CON_RVAL                   0x100 

/* DAC1CON[PD] - DAC1 power down */
#define DAC1CON_PD_BBA                 (*(volatile unsigned long *) 0x430480A0)
#define DAC1CON_PD_MSK                 (0x1   << 8  )
#define DAC1CON_PD                     (0x1   << 8  )

/* DAC1CON[EN] - DAC1 enable */
#define DAC1CON_EN_BBA                 (*(volatile unsigned long *) 0x43048090)
#define DAC1CON_EN_MSK                 (0x1   << 4  )
#define DAC1CON_EN                     (0x1   << 4  )

/* DAC1CON[RN] - DAC1 reference selection */
#define DAC1CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC1DAT*/
#define DAC1DAT_RVAL                   0x0 

/* DAC1DAT[DAT] - DAC1 data */
#define DAC1DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC2CON*/
#define DAC2CON_RVAL                   0x100 

/* DAC2CON[PD] - DAC2 power down */
#define DAC2CON_PD_BBA                 (*(volatile unsigned long *) 0x43048120)
#define DAC2CON_PD_MSK                 (0x1   << 8  )
#define DAC2CON_PD                     (0x1   << 8  )

/* DAC2CON[EN] - DAC2 enable */
#define DAC2CON_EN_BBA                 (*(volatile unsigned long *) 0x43048110)
#define DAC2CON_EN_MSK                 (0x1   << 4  )
#define DAC2CON_EN                     (0x1   << 4  )

/* DAC2CON[RN] - DAC2 reference selection */
#define DAC2CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC2DAT*/
#define DAC2DAT_RVAL                   0x0 

/* DAC2DAT[DAT] - DAC2 data */
#define DAC2DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC3CON*/
#define DAC3CON_RVAL                   0x100 

/* DAC3CON[PD] - DAC3 power down */
#define DAC3CON_PD_BBA                 (*(volatile unsigned long *) 0x430481A0)
#define DAC3CON_PD_MSK                 (0x1   << 8  )
#define DAC3CON_PD                     (0x1   << 8  )

/* DAC3CON[EN] - DAC3 enable */
#define DAC3CON_EN_BBA                 (*(volatile unsigned long *) 0x43048190)
#define DAC3CON_EN_MSK                 (0x1   << 4  )
#define DAC3CON_EN                     (0x1   << 4  )

/* DAC3CON[RN] - DAC3 reference selection */
#define DAC3CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC3DAT*/
#define DAC3DAT_RVAL                   0x0 

/* DAC3DAT[DAT] - DAC3 data */
#define DAC3DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC4CON*/
#define DAC4CON_RVAL                   0x100 

/* DAC4CON[PD] - DAC4 power down */
#define DAC4CON_PD_BBA                 (*(volatile unsigned long *) 0x43048220)
#define DAC4CON_PD_MSK                 (0x1   << 8  )
#define DAC4CON_PD                     (0x1   << 8  )

/* DAC4CON[EN] - DAC4 enable */
#define DAC4CON_EN_BBA                 (*(volatile unsigned long *) 0x43048210)
#define DAC4CON_EN_MSK                 (0x1   << 4  )
#define DAC4CON_EN                     (0x1   << 4  )

/* DAC4CON[RN] - DAC4 reference selection */
#define DAC4CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC4DAT*/
#define DAC4DAT_RVAL                   0x0 

/* DAC4DAT[DAT] - DAC4 data */
#define DAC4DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC5CON*/
#define DAC5CON_RVAL                   0x100 

/* DAC5CON[PD] - DAC5 power down */
#define DAC5CON_PD_BBA                 (*(volatile unsigned long *) 0x430482A0)
#define DAC5CON_PD_MSK                 (0x1   << 8  )
#define DAC5CON_PD                     (0x1   << 8  )

/* DAC5CON[EN] - DAC5 enable */
#define DAC5CON_EN_BBA                 (*(volatile unsigned long *) 0x43048290)
#define DAC5CON_EN_MSK                 (0x1   << 4  )
#define DAC5CON_EN                     (0x1   << 4  )

/* DAC5CON[RN] - DAC5 reference selection */
#define DAC5CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC5DAT*/
#define DAC5DAT_RVAL                   0x0 

/* DAC5DAT[DAT] - DAC5 data */
#define DAC5DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC6CON*/
#define DAC6CON_RVAL                   0x100 

/* DAC6CON[PD] - DAC6 power down */
#define DAC6CON_PD_BBA                 (*(volatile unsigned long *) 0x43048320)
#define DAC6CON_PD_MSK                 (0x1   << 8  )
#define DAC6CON_PD                     (0x1   << 8  )

/* DAC6CON[EN] - DAC6 enable */
#define DAC6CON_EN_BBA                 (*(volatile unsigned long *) 0x43048310)
#define DAC6CON_EN_MSK                 (0x1   << 4  )
#define DAC6CON_EN                     (0x1   << 4  )

/* DAC6CON[RN] - DAC6 reference selection */
#define DAC6CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC6DAT*/
#define DAC6DAT_RVAL                   0x0 

/* DAC6DAT[DAT] - DAC6 data */
#define DAC6DAT_DAT_MSK                (0xFFF << 16 )

/* Reset Value for DAC7CON*/
#define DAC7CON_RVAL                   0x100 

/* DAC7CON[PD] - DAC7 power down */
#define DAC7CON_PD_BBA                 (*(volatile unsigned long *) 0x430483A0)
#define DAC7CON_PD_MSK                 (0x1   << 8  )
#define DAC7CON_PD                     (0x1   << 8  )

/* DAC7CON[EN] - DAC7 enable */
#define DAC7CON_EN_BBA                 (*(volatile unsigned long *) 0x43048390)
#define DAC7CON_EN_MSK                 (0x1   << 4  )
#define DAC7CON_EN                     (0x1   << 4  )

/* DAC7CON[RN] - DAC7 reference selection */
#define DAC7CON_RN_MSK                 (0x3   << 0  )

/* Reset Value for DAC7DAT*/
#define DAC7DAT_RVAL                   0x0 

/* DAC7DAT[DAT] - DAC7 data */
#define DAC7DAT_DAT_MSK                (0xFFF << 16 )
// ------------------------------------------------------------------------------------------------
// -----                                        InBuf                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief InBuf (MMR_InBuf)
  */

typedef struct MMR_INBUF {                  /*!< MMR_InBuf Structure                   */
  __IO uint16_t  IBUFCON;                   /*!< InBuf control register                */
} MMR_INBUF_t;

/* Reset Value for IBUFCON*/
#define IBUFCON_RVAL                   0xF 

/* IBUFCON[IBUF_CHOP] - CHOPINBUF enable the chop per InBuf separately */
#define IBUFCON_IBUF_CHOP_MSK          (0x3   << 4  )
#define IBUFCON_IBUF_CHOP_OFF          (0x0   << 4  ) /* Chopping disabled on both buffers. */
#define IBUFCON_IBUF_CHOP_NSIDE        (0x1   << 4  ) /* Chopping enabled on N-side only. P-side Disabled. */
#define IBUFCON_IBUF_CHOP_PSIDE        (0x2   << 4  ) /* Chopping enabled on P-side only. N-side Disabled. */
#define IBUFCON_IBUF_CHOP_BOTH         (0x3   << 4  ) /* Chopping enabled on both buffers. */

/* IBUFCON[IBUF_PD] - Power down P/N InBuf separately */
#define IBUFCON_IBUF_PD_MSK            (0x3   << 2  )
#define IBUFCON_IBUF_PD_NONE           (0x0   << 2  ) /* Both sides powered on    */
#define IBUFCON_IBUF_PD_NSIDE          (0x1   << 2  ) /* only N side powered down */
#define IBUFCON_IBUF_PD_PSIDE          (0x2   << 2  ) /* only P side powered down */
#define IBUFCON_IBUF_PD_BOTH           (0x3   << 2  ) /* Both sides powered down  */

/* IBUFCON[IBUF_BYP] - Bypass P/N InBuf seperately */
#define IBUFCON_IBUF_BYP_MSK           (0x3   << 0  )
#define IBUFCON_IBUF_BYP_NONE          (0x0   << 0  ) /* Bypass none sided        */
#define IBUFCON_IBUF_BYP_NSIDE         (0x1   << 0  ) /* N side bypassed          */
#define IBUFCON_IBUF_BYP_PSIDE         (0x2   << 0  ) /* P side bypassed          */
#define IBUFCON_IBUF_BYP_BOTH          (0x3   << 0  ) /* Bypass both              */
// ------------------------------------------------------------------------------------------------
// -----                                        LV                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief LV_MISC (MMR_LV)
  */

typedef struct MMR_LV {                     /*!< MMR_LV Structure                      */
  __IO uint16_t  LVID;                      /*!< Low voltage die ID                    */
} MMR_LV_t;

/* Reset Value for LVID*/
#define LVID_RVAL                      0x71 

/* LVID[LVID] - LVID comes from hardware coded logic */
#define LVID_LVID_MSK                  (0xFFFF << 0  )
// ------------------------------------------------------------------------------------------------
// -----                                        LV_RST                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief LV_MISC (MMR_LV_RST)
  */

typedef struct MMR_LV_RST {                 /*!< MMR_LV_RST Structure                  */
  __IO uint16_t  LVRST;                     /*!< LV die reset configuration            */
} MMR_LV_RST_t;

/* Reset Value for LVRST*/
#define LVRST_RVAL                     0x0 

/* LVRST[RETAIN] - LV retains status after WDT and software reset */
#define LVRST_RETAIN_BBA               (*(volatile unsigned long *) 0x43058680)
#define LVRST_RETAIN_MSK               (0x1   << 0  )
#define LVRST_RETAIN                   (0x1   << 0  )
#define LVRST_RETAIN_EN                (0x0   << 0  ) /* LV die retains status after watchdog or software reset. */
#define LVRST_RETAIN_DIS               (0x1   << 0  ) /* LV die does not retain status after watchdog or software reset. */
// ------------------------------------------------------------------------------------------------
// -----                                        LV_INT                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief LV_INT (MMR_LV_INT)
  */

typedef struct MMR_LV_INT {                 /*!< MMR_LV_INT Structure                  */
  __IO uint16_t  INTCLR;                    /*!< Interrupt clear register              */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  INTSEL;                    /*!< Interrupt mask register               */
  __I  uint16_t  RESERVED1;
  __IO uint16_t  INTSTA;                    /*!< Interrupt status register             */
} MMR_LV_INT_t;

/* Reset Value for INTCLR*/
#define INTCLR_RVAL                    0x0 

/* INTCLR[CLR_WRECC_ERR] - Write 1 to this bit to clear the write ECC error interrupt flag */
#define INTCLR_CLR_WRECC_ERR_BBA       (*(volatile unsigned long *) 0x4306009C)
#define INTCLR_CLR_WRECC_ERR_MSK       (0x1   << 7  )
#define INTCLR_CLR_WRECC_ERR           (0x1   << 7  )
#define INTCLR_CLR_WRECC_ERR_DIS       (0x0   << 7  )
#define INTCLR_CLR_WRECC_ERR_EN        (0x1   << 7  )

/* INTCLR[CLR_RDECC_ERR] - Write 1 to this bit to clear the read ECC error interrupt flag */
#define INTCLR_CLR_RDECC_ERR_BBA       (*(volatile unsigned long *) 0x43060098)
#define INTCLR_CLR_RDECC_ERR_MSK       (0x1   << 6  )
#define INTCLR_CLR_RDECC_ERR           (0x1   << 6  )
#define INTCLR_CLR_RDECC_ERR_DIS       (0x0   << 6  )
#define INTCLR_CLR_RDECC_ERR_EN        (0x1   << 6  )

#if defined(ADUCM320) | defined(ADUCM320I)

/* INTCLR[CLR_IDAC_EXTRESLOW] - Write 1 to this bit to clear the IDAC EXTRESLOW interrupt flag */
#define INTCLR_CLR_IDAC_EXTRESLOW_BBA  (*(volatile unsigned long *) 0x43060094)
#define INTCLR_CLR_IDAC_EXTRESLOW_MSK  (0x1   << 5  )
#define INTCLR_CLR_IDAC_EXTRESLOW      (0x1   << 5  )
#define INTCLR_CLR_IDAC_EXTRESLOW_DIS  (0x0   << 5  )
#define INTCLR_CLR_IDAC_EXTRESLOW_EN   (0x1   << 5  )

/* INTCLR[CLR_IDAC_TSHUT] - Write 1 to this bit to clear the IDAC TSHUT interrupt flag */
#define INTCLR_CLR_IDAC_TSHUT_BBA      (*(volatile unsigned long *) 0x43060090)
#define INTCLR_CLR_IDAC_TSHUT_MSK      (0x1   << 4  )
#define INTCLR_CLR_IDAC_TSHUT          (0x1   << 4  )
#define INTCLR_CLR_IDAC_TSHUT_DIS      (0x0   << 4  )
#define INTCLR_CLR_IDAC_TSHUT_EN       (0x1   << 4  )

#endif

/* INTCLR[CLR_ACOMP] - Write 1 to this bit to clear the analog compare interrupt flag */
#define INTCLR_CLR_ACOMP_BBA           (*(volatile unsigned long *) 0x4306008C)
#define INTCLR_CLR_ACOMP_MSK           (0x1   << 3  )
#define INTCLR_CLR_ACOMP               (0x1   << 3  )
#define INTCLR_CLR_ACOMP_DIS           (0x0   << 3  )
#define INTCLR_CLR_ACOMP_EN            (0x1   << 3  )

/* INTCLR[CLR_DCOMP] - Write 1 to this bit to clear the digital compare interrupt flag */
#define INTCLR_CLR_DCOMP_BBA           (*(volatile unsigned long *) 0x43060088)
#define INTCLR_CLR_DCOMP_MSK           (0x1   << 2  )
#define INTCLR_CLR_DCOMP               (0x1   << 2  )
#define INTCLR_CLR_DCOMP_DIS           (0x0   << 2  )
#define INTCLR_CLR_DCOMP_EN            (0x1   << 2  )

/* INTCLR[CLR_ADC_SEQ] - Write 1 to this bit to clear the ADC sequence conversion interrupt flag */
#define INTCLR_CLR_ADC_SEQ_BBA         (*(volatile unsigned long *) 0x43060084)
#define INTCLR_CLR_ADC_SEQ_MSK         (0x1   << 1  )
#define INTCLR_CLR_ADC_SEQ             (0x1   << 1  )
#define INTCLR_CLR_ADC_SEQ_DIS         (0x0   << 1  )
#define INTCLR_CLR_ADC_SEQ_EN          (0x1   << 1  )

/* INTCLR[CLR_ADC_SOFTCONV] - Write 1 to this bit to clear the ADC software conversion interrupt flag */
#define INTCLR_CLR_ADC_SOFTCONV_BBA    (*(volatile unsigned long *) 0x43060080)
#define INTCLR_CLR_ADC_SOFTCONV_MSK    (0x1   << 0  )
#define INTCLR_CLR_ADC_SOFTCONV        (0x1   << 0  )
#define INTCLR_CLR_ADC_SOFTCONV_DIS    (0x0   << 0  )
#define INTCLR_CLR_ADC_SOFTCONV_EN     (0x1   << 0  )

/* Reset Value for INTSEL*/
#define INTSEL_RVAL                    0x0 

/* INTSEL[SEL_WRECC_ERR_0] - Write 1 to this bit to enable write ECC error interrupt for interrupt pin 0 */
#define INTSEL_SEL_WRECC_ERR_0_BBA     (*(volatile unsigned long *) 0x4306013C)
#define INTSEL_SEL_WRECC_ERR_0_MSK     (0x1   << 15 )
#define INTSEL_SEL_WRECC_ERR_0         (0x1   << 15 )
#define INTSEL_SEL_WRECC_ERR_0_DIS     (0x0   << 15 )
#define INTSEL_SEL_WRECC_ERR_0_EN      (0x1   << 15 )

/* INTSEL[SEL_RDECC_ERR_0] - Write 1 to this bit to enable read ECC error interrupt for interrupt pin 0 */
#define INTSEL_SEL_RDECC_ERR_0_BBA     (*(volatile unsigned long *) 0x43060138)
#define INTSEL_SEL_RDECC_ERR_0_MSK     (0x1   << 14 )
#define INTSEL_SEL_RDECC_ERR_0         (0x1   << 14 )
#define INTSEL_SEL_RDECC_ERR_0_DIS     (0x0   << 14 )
#define INTSEL_SEL_RDECC_ERR_0_EN      (0x1   << 14 )

#if defined(ADUCM320) | defined(ADUCM320I)

/* INTSEL[SLE_IDAC_EXTRESLOW_0] - Write 1 to this bit to enable IDAC EXTRESLOW interrupt for interrupt pin 0 */
#define INTSEL_SLE_IDAC_EXTRESLOW_0_BBA (*(volatile unsigned long *) 0x43060134)
#define INTSEL_SLE_IDAC_EXTRESLOW_0_MSK (0x1   << 13 )
#define INTSEL_SLE_IDAC_EXTRESLOW_0    (0x1   << 13 )
#define INTSEL_SLE_IDAC_EXTRESLOW_0_DIS (0x0   << 13 )
#define INTSEL_SLE_IDAC_EXTRESLOW_0_EN (0x1   << 13 )

/* INTSEL[SEL_IDAC_TSHUT_0] - Write 1 to this bit to enable IDAC TSHUT interrupt for interrupt pin 0 */
#define INTSEL_SEL_IDAC_TSHUT_0_BBA    (*(volatile unsigned long *) 0x43060130)
#define INTSEL_SEL_IDAC_TSHUT_0_MSK    (0x1   << 12 )
#define INTSEL_SEL_IDAC_TSHUT_0        (0x1   << 12 )
#define INTSEL_SEL_IDAC_TSHUT_0_DIS    (0x0   << 12 )
#define INTSEL_SEL_IDAC_TSHUT_0_EN     (0x1   << 12 )

#endif

/* INTSEL[SEL_ACOMP_0] - Write 1 to this bit to enable analog comparator interrupt for interrupt pin 0 */
#define INTSEL_SEL_ACOMP_0_BBA         (*(volatile unsigned long *) 0x4306012C)
#define INTSEL_SEL_ACOMP_0_MSK         (0x1   << 11 )
#define INTSEL_SEL_ACOMP_0             (0x1   << 11 )
#define INTSEL_SEL_ACOMP_0_DIS         (0x0   << 11 )
#define INTSEL_SEL_ACOMP_0_EN          (0x1   << 11 )

/* INTSEL[SEL_DCOMP_0] - Write 1 to this bit to enable digital comparator interrupt for interrupt pin 0 */
#define INTSEL_SEL_DCOMP_0_BBA         (*(volatile unsigned long *) 0x43060128)
#define INTSEL_SEL_DCOMP_0_MSK         (0x1   << 10 )
#define INTSEL_SEL_DCOMP_0             (0x1   << 10 )
#define INTSEL_SEL_DCOMP_0_DIS         (0x0   << 10 )
#define INTSEL_SEL_DCOMP_0_EN          (0x1   << 10 )

/* INTSEL[SEL_ADC_SEQ_0] - Write 1 to this bit to enable ADC sequence conversion interrupt for interrupt pin 0 */
#define INTSEL_SEL_ADC_SEQ_0_BBA       (*(volatile unsigned long *) 0x43060124)
#define INTSEL_SEL_ADC_SEQ_0_MSK       (0x1   << 9  )
#define INTSEL_SEL_ADC_SEQ_0           (0x1   << 9  )
#define INTSEL_SEL_ADC_SEQ_0_DIS       (0x0   << 9  )
#define INTSEL_SEL_ADC_SEQ_0_EN        (0x1   << 9  )

/* INTSEL[SEL_ADC_SOFTCONV_0] - Write 1 to this bit to enable ADC software conversion interrupt for interrupt pin 0 */
#define INTSEL_SEL_ADC_SOFTCONV_0_BBA  (*(volatile unsigned long *) 0x43060120)
#define INTSEL_SEL_ADC_SOFTCONV_0_MSK  (0x1   << 8  )
#define INTSEL_SEL_ADC_SOFTCONV_0      (0x1   << 8  )
#define INTSEL_SEL_ADC_SOFTCONV_0_DIS  (0x0   << 8  )
#define INTSEL_SEL_ADC_SOFTCONV_0_EN   (0x1   << 8  )

/* INTSEL[SEL_WRECC_ERR_1] - Write 1 to this bit to enable write ECC error interrupt for interrupt pin 1 */
#define INTSEL_SEL_WRECC_ERR_1_BBA     (*(volatile unsigned long *) 0x4306011C)
#define INTSEL_SEL_WRECC_ERR_1_MSK     (0x1   << 7  )
#define INTSEL_SEL_WRECC_ERR_1         (0x1   << 7  )
#define INTSEL_SEL_WRECC_ERR_1_DIS     (0x0   << 7  )
#define INTSEL_SEL_WRECC_ERR_1_EN      (0x1   << 7  )

/* INTSEL[SEL_RDECC_ERR_1] - Write 1 to this bit to enable read ECC error interrupt for interrupt pin 1 */
#define INTSEL_SEL_RDECC_ERR_1_BBA     (*(volatile unsigned long *) 0x43060118)
#define INTSEL_SEL_RDECC_ERR_1_MSK     (0x1   << 6  )
#define INTSEL_SEL_RDECC_ERR_1         (0x1   << 6  )
#define INTSEL_SEL_RDECC_ERR_1_DIS     (0x0   << 6  )
#define INTSEL_SEL_RDECC_ERR_1_EN      (0x1   << 6  )

#if defined(ADUCM320) | defined(ADUCM320I)

/* INTSEL[SLE_IDAC_EXTRESLOW_1] - Write 1 to this bit to enable IDAC EXTRESLOW interrupt for interrupt pin 1 */
#define INTSEL_SLE_IDAC_EXTRESLOW_1_BBA (*(volatile unsigned long *) 0x43060114)
#define INTSEL_SLE_IDAC_EXTRESLOW_1_MSK (0x1   << 5  )
#define INTSEL_SLE_IDAC_EXTRESLOW_1    (0x1   << 5  )
#define INTSEL_SLE_IDAC_EXTRESLOW_1_DIS (0x0   << 5  )
#define INTSEL_SLE_IDAC_EXTRESLOW_1_EN (0x1   << 5  )

/* INTSEL[SEL_IDAC_TSHUT_1] - Write 1 to this bit to enable IDAC TSHUT interrupt for interrupt pin 1 */
#define INTSEL_SEL_IDAC_TSHUT_1_BBA    (*(volatile unsigned long *) 0x43060110)
#define INTSEL_SEL_IDAC_TSHUT_1_MSK    (0x1   << 4  )
#define INTSEL_SEL_IDAC_TSHUT_1        (0x1   << 4  )
#define INTSEL_SEL_IDAC_TSHUT_1_DIS    (0x0   << 4  )
#define INTSEL_SEL_IDAC_TSHUT_1_EN     (0x1   << 4  )

#endif

/* INTSEL[SEL_ACOMP_1] - Write 1 to this bit to enable analog comparator interrupt for interrupt pin 1 */
#define INTSEL_SEL_ACOMP_1_BBA         (*(volatile unsigned long *) 0x4306010C)
#define INTSEL_SEL_ACOMP_1_MSK         (0x1   << 3  )
#define INTSEL_SEL_ACOMP_1             (0x1   << 3  )
#define INTSEL_SEL_ACOMP_1_DIS         (0x0   << 3  )
#define INTSEL_SEL_ACOMP_1_EN          (0x1   << 3  )

/* INTSEL[SEL_DCOMP_1] - Write 1 to this bit to enable digital comparator interrupt for interrupt pin 1 */
#define INTSEL_SEL_DCOMP_1_BBA         (*(volatile unsigned long *) 0x43060108)
#define INTSEL_SEL_DCOMP_1_MSK         (0x1   << 2  )
#define INTSEL_SEL_DCOMP_1             (0x1   << 2  )
#define INTSEL_SEL_DCOMP_1_DIS         (0x0   << 2  )
#define INTSEL_SEL_DCOMP_1_EN          (0x1   << 2  )

/* INTSEL[SEL_ADC_SEQ_1] - Write 1 to this bit to enable ADC sequence conversion interrupt for interrupt pin 1 */
#define INTSEL_SEL_ADC_SEQ_1_BBA       (*(volatile unsigned long *) 0x43060104)
#define INTSEL_SEL_ADC_SEQ_1_MSK       (0x1   << 1  )
#define INTSEL_SEL_ADC_SEQ_1           (0x1   << 1  )
#define INTSEL_SEL_ADC_SEQ_1_DIS       (0x0   << 1  )
#define INTSEL_SEL_ADC_SEQ_1_EN        (0x1   << 1  )

/* INTSEL[SEL_ADC_SOFTCONV_1] - Write 1 to this bit to enable ADC software conversion interrupt for interrupt pin 1 */
#define INTSEL_SEL_ADC_SOFTCONV_1_BBA  (*(volatile unsigned long *) 0x43060100)
#define INTSEL_SEL_ADC_SOFTCONV_1_MSK  (0x1   << 0  )
#define INTSEL_SEL_ADC_SOFTCONV_1      (0x1   << 0  )
#define INTSEL_SEL_ADC_SOFTCONV_1_DIS  (0x0   << 0  )
#define INTSEL_SEL_ADC_SOFTCONV_1_EN   (0x1   << 0  )

/* Reset Value for INTSTA*/
#define INTSTA_RVAL                    0x0 

/* INTSTA[WRECC_ERR] - Write data ECC error interrupt status */
#define INTSTA_WRECC_ERR_BBA           (*(volatile unsigned long *) 0x4306019C)
#define INTSTA_WRECC_ERR_MSK           (0x1   << 7  )
#define INTSTA_WRECC_ERR               (0x1   << 7  )
#define INTSTA_WRECC_ERR_CLR           (0x0   << 7  )
#define INTSTA_WRECC_ERR_SET           (0x1   << 7  )

/* INTSTA[RDECC_ERR] - Read data ECC error interrupt status */
#define INTSTA_RDECC_ERR_BBA           (*(volatile unsigned long *) 0x43060198)
#define INTSTA_RDECC_ERR_MSK           (0x1   << 6  )
#define INTSTA_RDECC_ERR               (0x1   << 6  )
#define INTSTA_RDECC_ERR_CLR           (0x0   << 6  )
#define INTSTA_RDECC_ERR_SET           (0x1   << 6  )

#if defined(ADUCM320) | defined(ADUCM320I)

/* INTSTA[IDAC_EXTRESLOW] - IDAC EXTRESLOW interrupt status */
#define INTSTA_IDAC_EXTRESLOW_BBA      (*(volatile unsigned long *) 0x43060194)
#define INTSTA_IDAC_EXTRESLOW_MSK      (0x1   << 5  )
#define INTSTA_IDAC_EXTRESLOW          (0x1   << 5  )
#define INTSTA_IDAC_EXTRESLOW_CLR      (0x0   << 5  )
#define INTSTA_IDAC_EXTRESLOW_SET      (0x1   << 5  )

/* INTSTA[IDAC_TSHUT] - IDAC temperature TSHT interrupt status */
#define INTSTA_IDAC_TSHUT_BBA          (*(volatile unsigned long *) 0x43060190)
#define INTSTA_IDAC_TSHUT_MSK          (0x1   << 4  )
#define INTSTA_IDAC_TSHUT              (0x1   << 4  )
#define INTSTA_IDAC_TSHUT_CLR          (0x0   << 4  )
#define INTSTA_IDAC_TSHUT_SET          (0x1   << 4  )

#endif

/* INTSTA[ACOMP] - Analog comparator interrupt status */
#define INTSTA_ACOMP_BBA               (*(volatile unsigned long *) 0x4306018C)
#define INTSTA_ACOMP_MSK               (0x1   << 3  )
#define INTSTA_ACOMP                   (0x1   << 3  )
#define INTSTA_ACOMP_CLR               (0x0   << 3  )
#define INTSTA_ACOMP_SET               (0x1   << 3  )

/* INTSTA[DCOMP] - Digital comparator interrupt status */
#define INTSTA_DCOMP_BBA               (*(volatile unsigned long *) 0x43060188)
#define INTSTA_DCOMP_MSK               (0x1   << 2  )
#define INTSTA_DCOMP                   (0x1   << 2  )
#define INTSTA_DCOMP_CLR               (0x0   << 2  )
#define INTSTA_DCOMP_SET               (0x1   << 2  )

/* INTSTA[ADC_SEQ] - ADC sequence interrupt status */
#define INTSTA_ADC_SEQ_BBA             (*(volatile unsigned long *) 0x43060184)
#define INTSTA_ADC_SEQ_MSK             (0x1   << 1  )
#define INTSTA_ADC_SEQ                 (0x1   << 1  )
#define INTSTA_ADC_SEQ_CLR             (0x0   << 1  )
#define INTSTA_ADC_SEQ_SET             (0x1   << 1  )

/* INTSTA[ADC_SOFTCONV] - ADC software conversion  interrupt status */
#define INTSTA_ADC_SOFTCONV_BBA        (*(volatile unsigned long *) 0x43060180)
#define INTSTA_ADC_SOFTCONV_MSK        (0x1   << 0  )
#define INTSTA_ADC_SOFTCONV            (0x1   << 0  )
#define INTSTA_ADC_SOFTCONV_CLR        (0x0   << 0  )
#define INTSTA_ADC_SOFTCONV_SET        (0x1   << 0  )


#if defined(ADUCM320) | defined(ADUCM320I)

// ------------------------------------------------------------------------------------------------
// -----                                        IDAC                                        -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief IDAC (MMR_IDAC)
  */

typedef struct MMR_IDAC {                   /*!< MMR_IDAC Structure                   */
  __IO uint32_t  IDACDAT;                   /*!< IDAC data register                   */
  __IO uint8_t   IDACCON;                   /*!< IDAC control register                */
} MMR_IDAC_t;

/* Reset Value for IDAC0DAT*/
#define IDAC0DAT_RVAL                  0x0 

/* IDAC0DAT[DATH] - IDAC0 high data */
#define IDAC0DAT_DATH_MSK              (0x7FF << 17 )

/* IDAC0DAT[DATL] - IDAC0 low data */
#define IDAC0DAT_DATL_MSK              (0x1F  << 12 )

/* IDAC0DAT[SYNC] - IDAC0 sync bits */
#define IDAC0DAT_SYNC_MSK              (0x3F  << 0  )

/* Reset Value for IDAC0CON*/
#define IDAC0CON_RVAL                  0x1 

/* IDAC0CON[CLRB] - IDAC0 Clear bit */
#define IDAC0CON_CLRB_BBA              (*(volatile unsigned long *) 0x430D009C)
#define IDAC0CON_CLRB_MSK              (0x1   << 7  )
#define IDAC0CON_CLRB                  (0x1   << 7  )

/* IDAC0CON[SHT_EN] - IDAC0 shutdown enable */
#define IDAC0CON_SHT_EN_BBA            (*(volatile unsigned long *) 0x430D0098)
#define IDAC0CON_SHT_EN_MSK            (0x1   << 6  )
#define IDAC0CON_SHT_EN                (0x1   << 6  )

/* IDAC0CON[BW] - IDAC0 bandwidth */
#define IDAC0CON_BW_MSK                (0xF   << 2  )

/* IDAC0CON[PUL] - IDAC0 pull down */
#define IDAC0CON_PUL_BBA               (*(volatile unsigned long *) 0x430D0084)
#define IDAC0CON_PUL_MSK               (0x1   << 1  )
#define IDAC0CON_PUL                   (0x1   << 1  )

/* IDAC0CON[PD] - IDAC0 power down */
#define IDAC0CON_PD_BBA                (*(volatile unsigned long *) 0x430D0080)
#define IDAC0CON_PD_MSK                (0x1   << 0  )
#define IDAC0CON_PD                    (0x1   << 0  )
#define IDAC0CON_PD_ON                 (0x0   << 0  ) /* Powers IDAC0 up          */
#define IDAC0CON_PD_OFF                (0x1   << 0  ) /* Powers IDAC0 down        */

/* Reset Value for IDAC1DAT*/
#define IDAC1DAT_RVAL                  0x0 

/* IDAC1DAT[DATH] - IDAC1 high data */
#define IDAC1DAT_DATH_MSK              (0x7FF << 17 )

/* IDAC1DAT[DATL] - IDAC1 low data */
#define IDAC1DAT_DATL_MSK              (0x1F  << 12 )

/* IDAC1DAT[SYNC] - IDAC1 sync bits */
#define IDAC1DAT_SYNC_MSK              (0x3F  << 0  )

/* Reset Value for IDAC1CON*/
#define IDAC1CON_RVAL                  0x1 

/* IDAC1CON[CLRB] - IDAC1 Clear bit */
#define IDAC1CON_CLRB_BBA              (*(volatile unsigned long *) 0x430D019C)
#define IDAC1CON_CLRB_MSK              (0x1   << 7  )
#define IDAC1CON_CLRB                  (0x1   << 7  )

/* IDAC1CON[SHT_EN] - IDAC1 shutdown enable */
#define IDAC1CON_SHT_EN_BBA            (*(volatile unsigned long *) 0x430D0198)
#define IDAC1CON_SHT_EN_MSK            (0x1   << 6  )
#define IDAC1CON_SHT_EN                (0x1   << 6  )

/* IDAC1CON[BW] - IDAC1 bandwidth */
#define IDAC1CON_BW_MSK                (0xF   << 2  )

/* IDAC1CON[PUL] - IDAC1 pull down */
#define IDAC1CON_PUL_BBA               (*(volatile unsigned long *) 0x430D0184)
#define IDAC1CON_PUL_MSK               (0x1   << 1  )
#define IDAC1CON_PUL                   (0x1   << 1  )

/* IDAC1CON[PD] - IDAC1 power down */
#define IDAC1CON_PD_BBA                (*(volatile unsigned long *) 0x430D0180)
#define IDAC1CON_PD_MSK                (0x1   << 0  )
#define IDAC1CON_PD                    (0x1   << 0  )
#define IDAC1CON_PD_OFF                (0x0   << 0  ) /* Powers IDAC1 up          */
#define IDAC1CON_PD_ON                 (0x1   << 0  ) /* Powers IDAC1 down        */

/* Reset Value for IDAC2DAT*/
#define IDAC2DAT_RVAL                  0x0 

/* IDAC2DAT[DATH] - IDAC2 high data */
#define IDAC2DAT_DATH_MSK              (0x7FF << 17 )

/* IDAC2DAT[DATL] - IDAC2 low data */
#define IDAC2DAT_DATL_MSK              (0x1F  << 12 )

/* IDAC2DAT[SYNC] - IDAC2 sync bits */
#define IDAC2DAT_SYNC_MSK              (0x3F  << 0  )

/* Reset Value for IDAC2CON*/
#define IDAC2CON_RVAL                  0x1 

/* IDAC2CON[CLR] - IDAC2 Clear bit */
#define IDAC2CON_CLR_BBA               (*(volatile unsigned long *) 0x430D029C)
#define IDAC2CON_CLR_MSK               (0x1   << 7  )
#define IDAC2CON_CLR                   (0x1   << 7  )

/* IDAC2CON[SHT_EN] - IDAC2 shutdown enable */
#define IDAC2CON_SHT_EN_BBA            (*(volatile unsigned long *) 0x430D0298)
#define IDAC2CON_SHT_EN_MSK            (0x1   << 6  )
#define IDAC2CON_SHT_EN                (0x1   << 6  )

/* IDAC2CON[BW] - IDAC2 bandwidth */
#define IDAC2CON_BW_MSK                (0xF   << 2  )

/* IDAC2CON[PUL] - IDAC2 pull down */
#define IDAC2CON_PUL_BBA               (*(volatile unsigned long *) 0x430D0284)
#define IDAC2CON_PUL_MSK               (0x1   << 1  )
#define IDAC2CON_PUL                   (0x1   << 1  )

/* IDAC2CON[PD] - IDAC2 power down */
#define IDAC2CON_PD_BBA                (*(volatile unsigned long *) 0x430D0280)
#define IDAC2CON_PD_MSK                (0x1   << 0  )
#define IDAC2CON_PD                    (0x1   << 0  )
#define IDAC2CON_PD_OFF                (0x0   << 0  ) /* Powers IDAC2 up          */
#define IDAC2CON_PD_ON                 (0x1   << 0  ) /* Powers IDAC2 down        */

/* Reset Value for IDAC3DAT*/
#define IDAC3DAT_RVAL                  0x0 

/* IDAC3DAT[DATH] - IDAC3 high data */
#define IDAC3DAT_DATH_MSK              (0x7FF << 17 )

/* IDAC3DAT[DATL] - IDAC3 low data */
#define IDAC3DAT_DATL_MSK              (0x1F  << 12 )

/* IDAC3DAT[SYNC] - IDAC3 sync bits */
#define IDAC3DAT_SYNC_MSK              (0x3F  << 0  )

/* Reset Value for IDAC3CON*/
#define IDAC3CON_RVAL                  0x1 

/* IDAC3CON[CLR] - IDAC3 Clear bit */
#define IDAC3CON_CLR_BBA               (*(volatile unsigned long *) 0x430D039C)
#define IDAC3CON_CLR_MSK               (0x1   << 7  )
#define IDAC3CON_CLR                   (0x1   << 7  )

/* IDAC3CON[SHT_EN] - IDAC3 shutdown enable */
#define IDAC3CON_SHT_EN_BBA            (*(volatile unsigned long *) 0x430D0398)
#define IDAC3CON_SHT_EN_MSK            (0x1   << 6  )
#define IDAC3CON_SHT_EN                (0x1   << 6  )

/* IDAC3CON[BW] - IDAC3 bandwidth */
#define IDAC3CON_BW_MSK                (0xF   << 2  )

/* IDAC3CON[PUL] - IDAC3 pull down */
#define IDAC3CON_PUL_BBA               (*(volatile unsigned long *) 0x430D0384)
#define IDAC3CON_PUL_MSK               (0x1   << 1  )
#define IDAC3CON_PUL                   (0x1   << 1  )

/* IDAC3CON[PD] - IDAC3 power down */
#define IDAC3CON_PD_BBA                (*(volatile unsigned long *) 0x430D0380)
#define IDAC3CON_PD_MSK                (0x1   << 0  )
#define IDAC3CON_PD                    (0x1   << 0  )
#define IDAC3CON_PD_OFF                (0x0   << 0  ) /* Powers IDAC3 up          */
#define IDAC3CON_PD_ON                 (0x1   << 0  ) /* Powers IDAC3 down        */

#endif


// ------------------------------------------------------------------------------------------------
// -----                                        AFE                                        -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief comp_ldo_por_reftop_temp (MMR_AFE)
  */

typedef struct MMR_AFE {                    /*!< MMR_AFE Structure                     */
  __IO uint8_t   AFETEMPC;                  /*!< Temp sensor configuration register    */
  __I  uint8_t   RESERVED0[3];
  __IO uint8_t   AFEREFC;                   /*!< Reference configuration register      */
  __I  uint8_t   RESERVED1[3];
  __IO uint16_t  AFECOMP;                   /*!< Analog comparator configuration register */
} MMR_AFE_t;

/* Reset Value for AFETEMPC*/
#define AFETEMPC_RVAL                  0x0 

/* AFETEMPC[CHOP] - Temperature sensor chopping enable. */
#define AFETEMPC_CHOP_BBA              (*(volatile unsigned long *) 0x430F0604)
#define AFETEMPC_CHOP_MSK              (0x1   << 1  )
#define AFETEMPC_CHOP                  (0x1   << 1  )
#define AFETEMPC_CHOP_DIS              (0x0   << 1  ) /* Disable chopping mode    */
#define AFETEMPC_CHOP_EN               (0x1   << 1  ) /* Enable chopping mode     */

/* AFETEMPC[PD] - Temperature sensor power down. */
#define AFETEMPC_PD_BBA                (*(volatile unsigned long *) 0x430F0600)
#define AFETEMPC_PD_MSK                (0x1   << 0  )
#define AFETEMPC_PD                    (0x1   << 0  )
#define AFETEMPC_PD_DIS                (0x0   << 0  ) /* Power up temp sensor     */
#define AFETEMPC_PD_EN                 (0x1   << 0  ) /* Power down temp sensor   */

/* Reset Value for AFEREFC*/
#define AFEREFC_RVAL                   0x0 

/* AFEREFC[B2MA_PDA] - Power down the reference 2mA output driving buffer A. */
#define AFEREFC_B2MA_PDA_BBA           (*(volatile unsigned long *) 0x430F0698)
#define AFEREFC_B2MA_PDA_MSK           (0x1   << 6  )
#define AFEREFC_B2MA_PDA               (0x1   << 6  )
#define AFEREFC_B2MA_PDA_DIS           (0x0   << 6  ) /* Power up 2.5 V reference output driving buffer A */
#define AFEREFC_B2MA_PDA_EN            (0x1   << 6  ) /* Power down 2.5 V reference output driving buffer A */

/* AFEREFC[REF] - bypass the internal reference, and select the external reference. */
#define AFEREFC_REF_BBA                (*(volatile unsigned long *) 0x430F068C)
#define AFEREFC_REF_MSK                (0x1   << 3  )
#define AFEREFC_REF                    (0x1   << 3  )
#define AFEREFC_REF_INT                (0x0   << 3  ) /* Select internal 2.5v reference */
#define AFEREFC_REF_EXT                (0x1   << 3  ) /* Select external 2.5v reference */

/* AFEREFC[B2MA_PDB] - Power down the reference 2mA output driving buffer B. */
#define AFEREFC_B2MA_PDB_BBA           (*(volatile unsigned long *) 0x430F0688)
#define AFEREFC_B2MA_PDB_MSK           (0x1   << 2  )
#define AFEREFC_B2MA_PDB               (0x1   << 2  )
#define AFEREFC_B2MA_PDB_DIS           (0x0   << 2  ) /* Power up 2.5 V reference output driving buffer B */
#define AFEREFC_B2MA_PDB_EN            (0x1   << 2  ) /* Power down 2.5 V reference output driving buffer B */

/* AFEREFC[B2V5R_PD] - 2.5v reference buffer power down */
#define AFEREFC_B2V5R_PD_BBA           (*(volatile unsigned long *) 0x430F0684)
#define AFEREFC_B2V5R_PD_MSK           (0x1   << 1  )
#define AFEREFC_B2V5R_PD               (0x1   << 1  )
#define AFEREFC_B2V5R_PD_DIS           (0x0   << 1  ) /* Power up 2.5 V reference buffer */
#define AFEREFC_B2V5R_PD_EN            (0x1   << 1  ) /* Power down 2.5 V reference buffer */

/* AFEREFC[BG_PD] - Bandgap power down */
#define AFEREFC_BG_PD_BBA              (*(volatile unsigned long *) 0x430F0680)
#define AFEREFC_BG_PD_MSK              (0x1   << 0  )
#define AFEREFC_BG_PD                  (0x1   << 0  )
#define AFEREFC_BG_PD_DIS              (0x0   << 0  ) /* Power up 1.2 V bandgap   */
#define AFEREFC_BG_PD_EN               (0x1   << 0  ) /* Power down 1.2 V bandgap */

/* Reset Value for AFECOMP*/
#define AFECOMP_RVAL                   0x0 

/* AFECOMP[EN] - Powers up and enables comparator */
#define AFECOMP_EN_BBA                 (*(volatile unsigned long *) 0x430F0720)
#define AFECOMP_EN_MSK                 (0x1   << 8  )
#define AFECOMP_EN                     (0x1   << 8  )
#define AFECOMP_EN_DIS                 (0x0   << 8  ) /* Power down and disable comparator */
#define AFECOMP_EN_EN                  (0x1   << 8  ) /* Power up and enable comparator */

/* AFECOMP[INNEG] - Selects comparator negative input signal. */
#define AFECOMP_INNEG_MSK              (0x3   << 6  )
#define AFECOMP_INNEG_AVDD2            (0x0   << 6  ) /* AVDD/2                   */
#define AFECOMP_INNEG_AIN5             (0x1   << 6  ) /* AIN5                     */
#define AFECOMP_INNEG_DAC7             (0x2   << 6  ) /* DAC7                     */

/* AFECOMP[OUT] - Connects comparator output to interrupt logic. */
#define AFECOMP_OUT_MSK                (0x3   << 4  )
#define AFECOMP_OUT_DIS                (0x0   << 4  ) /* Do not connect output    */
#define AFECOMP_OUT_EN                 (0x1   << 4  ) /* Connect output to interrupt logic */

/* AFECOMP[INV] - Selects output logic state. */
#define AFECOMP_INV_BBA                (*(volatile unsigned long *) 0x430F070C)
#define AFECOMP_INV_MSK                (0x1   << 3  )
#define AFECOMP_INV                    (0x1   << 3  )
#define AFECOMP_INV_NO                 (0x0   << 3  ) /* Output will be high if +ve input is above -ve input. */
#define AFECOMP_INV_YES                (0x1   << 3  ) /* Output will be high if +ve input is below -ve input. */

/* AFECOMP[SPEED] - Selects comparator speed. */
#define AFECOMP_SPEED_MSK              (0x3   << 1  )
#define AFECOMP_SPEED_SPEED6           (0x0   << 1  ) /* 6.00us                   */
#define AFECOMP_SPEED_SPEED3           (0x1   << 1  ) /* 3.25us                   */
#define AFECOMP_SPEED_SPEED2           (0x2   << 1  ) /* 1.75us                   */
#define AFECOMP_SPEED_SPEED1           (0x3   << 1  ) /* 1.00us                   */

/* AFECOMP[HYS] - Enables comparator hysteresis */
#define AFECOMP_HYS_BBA                (*(volatile unsigned long *) 0x430F0700)
#define AFECOMP_HYS_MSK                (0x1   << 0  )
#define AFECOMP_HYS                    (0x1   << 0  )
#define AFECOMP_HYS_DIS                (0x0   << 0  ) /* Disable hysteresis       */
#define AFECOMP_HYS_EN                 (0x1   << 0  ) /* Enable  hysteresis       */

/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif


/* ========================================================================== */
/* =============              Peripheral memory map             ============= */
/* ========================================================================== */

#define MMR_TMR0_ADDR                            0x40000000UL
#define MMR_TMR1_ADDR                            0x40000400UL
#define MMR_TMR2_ADDR                            0x40000800UL
#define MMR_ID_ADDR                              0x40002024UL
#define MMR_PWRCTL_ADDR                          0x40002400UL
#define MMR_RESET_ADDR                           0x40002408UL
#define MMR_INTERRUPT_ADDR                       0x40002420UL
#define MMR_WDT_ADDR                             0x40002580UL
#define MMR_WUT_ADDR                             0x40002500UL
#define MMR_I2C0_ADDR                            0x40003000UL
#define MMR_I2C1_ADDR                            0x40003400UL
#define MMR_UART_ADDR                            0x40005000UL
#define MMR_MDIO_ADDR                            0x40005C00UL
#define MMR_PLA_ADDR                             0x40005800UL
#define MMR_DMA_ADDR                             0x40010000UL
#define MMR_FEE_ADDR                             0x40018000UL
#define MMR_GPIO0_ADDR                           0x40020000UL
#define MMR_GPIO1_ADDR                           0x40020040UL
#define MMR_GPIO2_ADDR                           0x40020080UL
#define MMR_GPIO3_ADDR                           0x400200C0UL
#define MMR_GPIO4_ADDR                           0x40020100UL
#define MMR_GPIO5_ADDR                           0x40020240UL
#define MMR_PWM_ADDR                             0x40024000UL
#define MMR_CLKCTL_ADDR                          0x40028000UL
#define MMR_DMACTL_ADDR                          0x40028100UL
#define MMR_SPI0_ADDR                            0x4002C000UL
#define MMR_SPI1_ADDR                            0x40030000UL
#define MMR_ADC_ADDR                             0x40082174UL
#define MMR_VDAC0_ADDR                           0x40082400UL
#define MMR_VDAC1_ADDR                           0x40082404UL
#define MMR_VDAC2_ADDR                           0x40082408UL
#define MMR_VDAC3_ADDR                           0x4008240CUL
#define MMR_VDAC4_ADDR                           0x40082410UL
#define MMR_VDAC5_ADDR                           0x40082414UL
#define MMR_VDAC6_ADDR                           0x40082418UL
#define MMR_VDAC7_ADDR                           0x4008241CUL
#define MMR_INBUF_ADDR                           0x40081400UL
#define MMR_LV_ADDR                              0x40082C30UL
#define MMR_LV_RST_ADDR                          0x40082C34UL
#define MMR_LV_INT_ADDR                          0x40083004UL
#if defined(ADUCM320) | defined(ADUCM320I)
#define MMR_IDAC0_ADDR                           0x40086800UL
#define MMR_IDAC1_ADDR                           0x40086808UL
#define MMR_IDAC2_ADDR                           0x40086810UL
#define MMR_IDAC3_ADDR                           0x40086818UL
#endif
#define MMR_AFE_ADDR                             0x40087830UL


/* ========================================================================== */
/* =============             Peripheral declaration             ============= */
/* ========================================================================== */

#define MMR_TMR0                  ((MMR_TIMER_t     *)MMR_TMR0_ADDR)
#define MMR_TMR1                  ((MMR_TIMER_t     *)MMR_TMR1_ADDR)
#define MMR_TMR2                  ((MMR_TIMER_t     *)MMR_TMR2_ADDR)
#define MMR_ID                    ((MMR_ID_t        *)MMR_ID_ADDR)
#define MMR_PWRCTL                ((MMR_PWRCTL_t    *)MMR_PWRCTL_ADDR)
#define MMR_RESET                 ((MMR_RESET_t     *)MMR_RESET_ADDR)
#define MMR_INTERRUPT             ((MMR_INTERRUPT_t *)MMR_INTERRUPT_ADDR)
#define MMR_WDT                   ((MMR_WDT_t       *)MMR_WDT_ADDR)
#define MMR_WUT                   ((MMR_WUT_t       *)MMR_WUT_ADDR)
#define MMR_I2C0                  ((MMR_I2C_t       *)MMR_I2C0_ADDR)
#define MMR_I2C1                  ((MMR_I2C_t       *)MMR_I2C1_ADDR)
#define MMR_UART                  ((MMR_UART_t      *)MMR_UART_ADDR)
#define MMR_MDIO                  ((MMR_MDIO_t      *)MMR_MDIO_ADDR)
#define MMR_PLA                   ((MMR_PLA_t       *)MMR_PLA_ADDR)
#define MMR_DMA                   ((MMR_DMA_t       *)MMR_DMA_ADDR)
#define MMR_FEE                   ((MMR_FEE_t       *)MMR_FEE_ADDR)
#define MMR_GPIO0                 ((MMR_GPIO_t      *)MMR_GPIO0_ADDR)
#define MMR_GPIO1                 ((MMR_GPIO_t      *)MMR_GPIO1_ADDR)
#define MMR_GPIO2                 ((MMR_GPIO_t      *)MMR_GPIO2_ADDR)
#define MMR_GPIO3                 ((MMR_GPIO_t      *)MMR_GPIO3_ADDR)
#define MMR_GPIO4                 ((MMR_GPIO_t      *)MMR_GPIO4_ADDR)
#define MMR_GPIO5                 ((MMR_GPIO_t      *)MMR_GPIO5_ADDR)
#define MMR_PWM                   ((MMR_PWM_t       *)MMR_PWM_ADDR)
#define MMR_CLKCTL                ((MMR_CLKCTL_t    *)MMR_CLKCTL_ADDR)
#define MMR_dma_ctl               ((MMR_DMACTL_t    *)MMR_DMACTL_ADDR)
#define MMR_SPI0                  ((MMR_SPI_t       *)MMR_SPI0_ADDR)
#define MMR_SPI1                  ((MMR_SPI_t       *)MMR_SPI1_ADDR)
#define MMR_ADC                   ((MMR_ADC_t       *)MMR_ADC_ADDR)
#define MMR_VDAC0                 ((MMR_VDAC_t      *)MMR_VDAC0_ADDR)
#define MMR_VDAC1                 ((MMR_VDAC_t      *)MMR_VDAC1_ADDR)
#define MMR_VDAC2                 ((MMR_VDAC_t      *)MMR_VDAC2_ADDR)
#define MMR_VDAC3                 ((MMR_VDAC_t      *)MMR_VDAC3_ADDR)
#define MMR_VDAC4                 ((MMR_VDAC_t      *)MMR_VDAC4_ADDR)
#define MMR_VDAC5                 ((MMR_VDAC_t      *)MMR_VDAC5_ADDR)
#define MMR_VDAC6                 ((MMR_VDAC_t      *)MMR_VDAC6_ADDR)
#define MMR_VDAC7                 ((MMR_VDAC_t      *)MMR_VDAC7_ADDR)
#define MMR_InBuf                 ((MMR_INBUF_t     *)MMR_INBUF_ADDR)
#define MMR_LV                    ((MMR_LV_t        *)MMR_LV_ADDR)
#define MMR_LV_RST                ((MMR_LV_RST_t    *)MMR_LV_RST_ADDR)
#define MMR_LV_INT                ((MMR_LV_INT_t    *)MMR_LV_INT_ADDR)
#if defined(ADUCM320) | defined(ADUCM320I)
#define MMR_IDAC0                 ((MMR_IDAC_t      *)MMR_IDAC0_ADDR)
#define MMR_IDAC1                 ((MMR_IDAC_t      *)MMR_IDAC1_ADDR)
#define MMR_IDAC2                 ((MMR_IDAC_t      *)MMR_IDAC2_ADDR)
#define MMR_IDAC3                 ((MMR_IDAC_t      *)MMR_IDAC3_ADDR)
#endif
#define MMR_AFE                   ((MMR_AFE_t       *)MMR_AFE_ADDR)

/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group ADUCM32x */
/** @} */ /* End of group CMSIS */

#ifdef __cplusplus
}
#endif 


#endif  // ADUCM32x_H_
