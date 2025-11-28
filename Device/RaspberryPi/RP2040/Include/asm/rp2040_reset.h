/*
 * Copyright (C) 2025 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef RP2040_RESET_H
#define RP2040_RESET_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <asm/rp2040.h>

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define RESETS                            ((RESETS_t*) RESETS_BASE)

/**
 * @brief Bit definition for RESET register
 */
#define RESETS_RESET_ADC_Pos              (0U)
#define RESETS_RESET_ADC_Msk              (1UL << RESETS_RESET_ADC_Pos)
#define RESETS_RESET_ADC                          RESETS_RESET_ADC_Msk

#define RESETS_RESET_BUSCTRL_Pos          (1U)
#define RESETS_RESET_BUSCTRL_Msk          (1UL << RESETS_RESET_BUSCTRL_Pos)
#define RESETS_RESET_BUSCTRL                      RESETS_RESET_BUSCTRL_Msk

#define RESETS_RESET_DMA_Pos              (2U)
#define RESETS_RESET_DMA_Msk              (1UL << RESETS_RESET_DMA_Pos)
#define RESETS_RESET_DMA                          RESETS_RESET_DMA_Msk

#define RESETS_RESET_I2C0_Pos             (3U)
#define RESETS_RESET_I2C0_Msk             (1UL << RESETS_RESET_I2C0_Pos)
#define RESETS_RESET_I2C0                         RESETS_RESET_I2C0_Msk

#define RESETS_RESET_I2C1_Pos             (4U)
#define RESETS_RESET_I2C1_Msk             (1UL << RESETS_RESET_I2C1_Pos)
#define RESETS_RESET_I2C1                         RESETS_RESET_I2C1_Msk

#define RESETS_RESET_IO_BANK0_Pos         (5U)
#define RESETS_RESET_IO_BANK0_Msk         (1UL << RESETS_RESET_IO_BANK0_Pos)
#define RESETS_RESET_IO_BANK0                     RESETS_RESET_IO_BANK0_Msk

#define RESETS_RESET_IO_QSPI_Pos          (6U)
#define RESETS_RESET_IO_QSPI_Msk          (1UL << RESETS_RESET_IO_QSPI_Pos)
#define RESETS_RESET_IO_QSPI                      RESETS_RESET_IO_QSPI_Msk

#define RESETS_RESET_JTAG_Pos             (7U)
#define RESETS_RESET_JTAG_Msk             (1UL << RESETS_RESET_JTAG_Pos)
#define RESETS_RESET_JTAG                         RESETS_RESET_JTAG_Msk

#define RESETS_RESET_PADS_BANK0_Pos       (8U)
#define RESETS_RESET_PADS_BANK0_Msk       (1UL << RESETS_RESET_PADS_BANK0_Pos)
#define RESETS_RESET_PADS_BANK0                   RESETS_RESET_PADS_BANK0_Msk

#define RESETS_RESET_PADS_QSPI_Pos        (9U)
#define RESETS_RESET_PADS_QSPI_Msk        (1UL << RESETS_RESET_PADS_QSPI_Pos)
#define RESETS_RESET_PADS_QSPI                    RESETS_RESET_PADS_QSPI_Msk

#define RESETS_RESET_PIO0_Pos             (10U)
#define RESETS_RESET_PIO0_Msk             (1UL << RESETS_RESET_PIO0_Pos)
#define RESETS_RESET_PIO0                         RESETS_RESET_PIO0_Msk

#define RESETS_RESET_PIO1_Pos             (11U)
#define RESETS_RESET_PIO1_Msk             (1UL << RESETS_RESET_PIO1_Pos)
#define RESETS_RESET_PIO1                         RESETS_RESET_PIO1_Msk

#define RESETS_RESET_PLL_SYS_Pos          (12U)
#define RESETS_RESET_PLL_SYS_Msk          (1UL << RESETS_RESET_PLL_SYS_Pos)
#define RESETS_RESET_PLL_SYS                      RESETS_RESET_PLL_SYS_Msk

#define RESETS_RESET_PLL_USB_Pos          (13U)
#define RESETS_RESET_PLL_USB_Msk          (1UL << RESETS_RESET_PLL_USB_Pos)
#define RESETS_RESET_PLL_USB                      RESETS_RESET_PLL_USB_Msk

#define RESETS_RESET_PWM_Pos              (14U)
#define RESETS_RESET_PWM_Msk              (1UL << RESETS_RESET_PWM_Pos)
#define RESETS_RESET_PWM                          RESETS_RESET_PWM_Msk

#define RESETS_RESET_RTC_Pos              (15U)
#define RESETS_RESET_RTC_Msk              (1UL << RESETS_RESET_RTC_Pos)
#define RESETS_RESET_RTC                          RESETS_RESET_RTC_Msk

#define RESETS_RESET_SPI0_Pos             (16U)
#define RESETS_RESET_SPI0_Msk             (1UL << RESETS_RESET_SPI0_Pos)
#define RESETS_RESET_SPI0                         RESETS_RESET_SPI0_Msk

#define RESETS_RESET_SPI1_Pos             (17U)
#define RESETS_RESET_SPI1_Msk             (1UL << RESETS_RESET_SPI1_Pos)
#define RESETS_RESET_SPI1                         RESETS_RESET_SPI1_Msk

#define RESETS_RESET_SYSCFG_Pos           (18U)
#define RESETS_RESET_SYSCFG_Msk           (1UL << RESETS_RESET_SYSCFG_Pos)
#define RESETS_RESET_SYSCFG                       RESETS_RESET_SYSCFG_Msk

#define RESETS_RESET_SYSINFO_Pos          (19U)
#define RESETS_RESET_SYSINFO_Msk          (1UL << RESETS_RESET_SYSINFO_Pos)
#define RESETS_RESET_SYSINFO                      RESETS_RESET_SYSINFO_Msk

#define RESETS_RESET_TBMAN_Pos            (20U)
#define RESETS_RESET_TBMAN_Msk            (1UL << RESETS_RESET_TBMAN_Pos)
#define RESETS_RESET_TBMAN                        RESETS_RESET_TBMAN_Msk

#define RESETS_RESET_TIMER_Pos            (21U)
#define RESETS_RESET_TIMER_Msk            (1UL << RESETS_RESET_TIMER_Pos)
#define RESETS_RESET_TIMER                        RESETS_RESET_TIMER_Msk

#define RESETS_RESET_UART0_Pos            (22U)
#define RESETS_RESET_UART0_Msk            (1UL << RESETS_RESET_UART0_Pos)
#define RESETS_RESET_UART0                        RESETS_RESET_UART0_Msk

#define RESETS_RESET_UART1_Pos            (23U)
#define RESETS_RESET_UART1_Msk            (1UL << RESETS_RESET_UART1_Pos)
#define RESETS_RESET_UART1                        RESETS_RESET_UART1_Msk

#define RESETS_RESET_USBCTRL_Pos          (24U)
#define RESETS_RESET_USBCTRL_Msk          (1UL << RESETS_RESET_USBCTRL_Pos)
#define RESETS_RESET_USBCTRL                      RESETS_RESET_USBCTRL_Msk

/**
 * @brief Bit definition for WDSEL register
 */
#define RESETS_WDSEL_ADC_Pos              (0U)
#define RESETS_WDSEL_ADC_Msk              (1UL << RESETS_RESET_ADC_Pos)
#define RESETS_WDSEL_ADC                          RESETS_RESET_ADC_Msk

#define RESETS_WDSEL_BUSCTRL_Pos          (1U)
#define RESETS_WDSEL_BUSCTRL_Msk          (1UL << RESETS_WDSEL_BUSCTRL_Pos)
#define RESETS_WDSEL_BUSCTRL                      RESETS_WDSEL_BUSCTRL_Msk

#define RESETS_WDSEL_DMA_Pos              (2U)
#define RESETS_WDSEL_DMA_Msk              (1UL << RESETS_WDSEL_DMA_Pos)
#define RESETS_WDSEL_DMA                          RESETS_WDSEL_DMA_Msk

#define RESETS_WDSEL_I2C0_Pos             (3U)
#define RESETS_WDSEL_I2C0_Msk             (1UL << RESETS_WDSEL_I2C0_Pos)
#define RESETS_WDSEL_I2C0                         RESETS_WDSEL_I2C0_Msk

#define RESETS_WDSEL_I2C1_Pos             (4U)
#define RESETS_WDSEL_I2C1_Msk             (1UL << RESETS_WDSEL_I2C1_Pos)
#define RESETS_WDSEL_I2C1                         RESETS_WDSEL_I2C1_Msk

#define RESETS_WDSEL_IO_BANK0_Pos         (5U)
#define RESETS_WDSEL_IO_BANK0_Msk         (1UL << RESETS_WDSEL_IO_BANK0_Pos)
#define RESETS_WDSEL_IO_BANK0                     RESETS_WDSEL_IO_BANK0_Msk

#define RESETS_WDSEL_IO_QSPI_Pos          (6U)
#define RESETS_WDSEL_IO_QSPI_Msk          (1UL << RESETS_WDSEL_IO_QSPI_Pos)
#define RESETS_WDSEL_IO_QSPI                      RESETS_WDSEL_IO_QSPI_Msk

#define RESETS_WDSEL_JTAG_Pos             (7U)
#define RESETS_WDSEL_JTAG_Msk             (1UL << RESETS_WDSEL_JTAG_Pos)
#define RESETS_WDSEL_JTAG                         RESETS_WDSEL_JTAG_Msk

#define RESETS_WDSEL_PADS_BANK0_Pos       (8U)
#define RESETS_WDSEL_PADS_BANK0_Msk       (1UL << RESETS_WDSEL_PADS_BANK0_Pos)
#define RESETS_WDSEL_PADS_BANK0                   RESETS_WDSEL_PADS_BANK0_Msk

#define RESETS_WDSEL_PADS_QSPI_Pos        (9U)
#define RESETS_WDSEL_PADS_QSPI_Msk        (1UL << RESETS_WDSEL_PADS_QSPI_Pos)
#define RESETS_WDSEL_PADS_QSPI                    RESETS_WDSEL_PADS_QSPI_Msk

#define RESETS_WDSEL_PIO0_Pos             (10U)
#define RESETS_WDSEL_PIO0_Msk             (1UL << RESETS_WDSEL_PIO0_Pos)
#define RESETS_WDSEL_PIO0                         RESETS_WDSEL_PIO0_Msk

#define RESETS_WDSEL_PIO1_Pos             (11U)
#define RESETS_WDSEL_PIO1_Msk             (1UL << RESETS_WDSEL_PIO1_Pos)
#define RESETS_WDSEL_PIO1                         RESETS_WDSEL_PIO1_Msk

#define RESETS_WDSEL_PLL_SYS_Pos          (12U)
#define RESETS_WDSEL_PLL_SYS_Msk          (1UL << RESETS_WDSEL_PLL_SYS_Pos)
#define RESETS_WDSEL_PLL_SYS                      RESETS_WDSEL_PLL_SYS_Msk

#define RESETS_WDSEL_PLL_USB_Pos          (13U)
#define RESETS_WDSEL_PLL_USB_Msk          (1UL << RESETS_WDSEL_PLL_USB_Pos)
#define RESETS_WDSEL_PLL_USB                      RESETS_WDSEL_PLL_USB_Msk

#define RESETS_WDSEL_PWM_Pos              (14U)
#define RESETS_WDSEL_PWM_Msk              (1UL << RESETS_WDSEL_PWM_Pos)
#define RESETS_WDSEL_PWM                          RESETS_WDSEL_PWM_Msk

#define RESETS_WDSEL_RTC_Pos              (15U)
#define RESETS_WDSEL_RTC_Msk              (1UL << RESETS_WDSEL_RTC_Pos)
#define RESETS_WDSEL_RTC                          RESETS_WDSEL_RTC_Msk

#define RESETS_WDSEL_SPI0_Pos             (16U)
#define RESETS_WDSEL_SPI0_Msk             (1UL << RESETS_WDSEL_SPI0_Pos)
#define RESETS_WDSEL_SPI0                         RESETS_WDSEL_SPI0_Msk

#define RESETS_WDSEL_SPI1_Pos             (17U)
#define RESETS_WDSEL_SPI1_Msk             (1UL << RESETS_WDSEL_SPI1_Pos)
#define RESETS_WDSEL_SPI1                         RESETS_WDSEL_SPI1_Msk

#define RESETS_WDSEL_SYSCFG_Pos           (18U)
#define RESETS_WDSEL_SYSCFG_Msk           (1UL << RESETS_WDSEL_SYSCFG_Pos)
#define RESETS_WDSEL_SYSCFG                       RESETS_WDSEL_SYSCFG_Msk

#define RESETS_WDSEL_SYSINFO_Pos          (19U)
#define RESETS_WDSEL_SYSINFO_Msk          (1UL << RESETS_WDSEL_SYSINFO_Pos)
#define RESETS_WDSEL_SYSINFO                      RESETS_WDSEL_SYSINFO_Msk

#define RESETS_WDSEL_TBMAN_Pos            (20U)
#define RESETS_WDSEL_TBMAN_Msk            (1UL << RESETS_WDSEL_TBMAN_Pos)
#define RESETS_WDSEL_TBMAN                        RESETS_WDSEL_TBMAN_Msk

#define RESETS_WDSEL_TIMER_Pos            (21U)
#define RESETS_WDSEL_TIMER_Msk            (1UL << RESETS_WDSEL_TIMER_Pos)
#define RESETS_WDSEL_TIMER                        RESETS_WDSEL_TIMER_Msk

#define RESETS_WDSEL_UART0_Pos            (22U)
#define RESETS_WDSEL_UART0_Msk            (1UL << RESETS_WDSEL_UART0_Pos)
#define RESETS_WDSEL_UART0                        RESETS_WDSEL_UART0_Msk

#define RESETS_WDSEL_UART1_Pos            (23U)
#define RESETS_WDSEL_UART1_Msk            (1UL << RESETS_WDSEL_UART1_Pos)
#define RESETS_WDSEL_UART1                        RESETS_WDSEL_UART1_Msk

#define RESETS_WDSEL_USBCTRL_Pos          (24U)
#define RESETS_WDSEL_USBCTRL_Msk          (1UL << RESETS_WDSEL_USBCTRL_Pos)
#define RESETS_WDSEL_USBCTRL                      RESETS_WDSEL_USBCTRL_Msk

/**
 * @brief Bit definition for WDSEL register
 */
#define RESETS_RESET_DONE_ADC_Pos         (0U)
#define RESETS_RESET_DONE_ADC_Msk         (1UL << RESETS_RESET_ADC_Pos)
#define RESETS_RESET_DONE_ADC                     RESETS_RESET_ADC_Msk

#define RESETS_RESET_DONE_BUSCTRL_Pos     (1U)
#define RESETS_RESET_DONE_BUSCTRL_Msk     (1UL << RESETS_RESET_DONE_BUSCTRL_Pos)
#define RESETS_RESET_DONE_BUSCTRL                 RESETS_RESET_DONE_BUSCTRL_Msk

#define RESETS_RESET_DONE_DMA_Pos         (2U)
#define RESETS_RESET_DONE_DMA_Msk         (1UL << RESETS_RESET_DONE_DMA_Pos)
#define RESETS_RESET_DONE_DMA                     RESETS_RESET_DONE_DMA_Msk

#define RESETS_RESET_DONE_I2C0_Pos        (3U)
#define RESETS_RESET_DONE_I2C0_Msk        (1UL << RESETS_RESET_DONE_I2C0_Pos)
#define RESETS_RESET_DONE_I2C0                    RESETS_RESET_DONE_I2C0_Msk

#define RESETS_RESET_DONE_I2C1_Pos        (4U)
#define RESETS_RESET_DONE_I2C1_Msk        (1UL << RESETS_RESET_DONE_I2C1_Pos)
#define RESETS_RESET_DONE_I2C1                    RESETS_RESET_DONE_I2C1_Msk

#define RESETS_RESET_DONE_IO_BANK0_Pos    (5U)
#define RESETS_RESET_DONE_IO_BANK0_Msk    (1UL << RESETS_RESET_DONE_IO_BANK0_Pos)
#define RESETS_RESET_DONE_IO_BANK0                RESETS_RESET_DONE_IO_BANK0_Msk

#define RESETS_RESET_DONE_IO_QSPI_Pos     (6U)
#define RESETS_RESET_DONE_IO_QSPI_Msk     (1UL << RESETS_RESET_DONE_IO_QSPI_Pos)
#define RESETS_RESET_DONE_IO_QSPI                 RESETS_RESET_DONE_IO_QSPI_Msk

#define RESETS_RESET_DONE_JTAG_Pos        (7U)
#define RESETS_RESET_DONE_JTAG_Msk        (1UL << RESETS_RESET_DONE_JTAG_Pos)
#define RESETS_RESET_DONE_JTAG                    RESETS_RESET_DONE_JTAG_Msk

#define RESETS_RESET_DONE_PADS_BANK0_Pos  (8U)
#define RESETS_RESET_DONE_PADS_BANK0_Msk  (1UL << RESETS_RESET_DONE_PADS_BANK0_Pos)
#define RESETS_RESET_DONE_PADS_BANK0              RESETS_RESET_DONE_PADS_BANK0_Msk

#define RESETS_RESET_DONE_PADS_QSPI_Pos   (9U)
#define RESETS_RESET_DONE_PADS_QSPI_Msk   (1UL << RESETS_RESET_DONE_PADS_QSPI_Pos)
#define RESETS_RESET_DONE_PADS_QSPI               RESETS_RESET_DONE_PADS_QSPI_Msk

#define RESETS_RESET_DONE_PIO0_Pos        (10U)
#define RESETS_RESET_DONE_PIO0_Msk        (1UL << RESETS_RESET_DONE_PIO0_Pos)
#define RESETS_RESET_DONE_PIO0                    RESETS_RESET_DONE_PIO0_Msk

#define RESETS_RESET_DONE_PIO1_Pos        (11U)
#define RESETS_RESET_DONE_PIO1_Msk        (1UL << RESETS_RESET_DONE_PIO1_Pos)
#define RESETS_RESET_DONE_PIO1                    RESETS_RESET_DONE_PIO1_Msk

#define RESETS_RESET_DONE_PLL_SYS_Pos     (12U)
#define RESETS_RESET_DONE_PLL_SYS_Msk     (1UL << RESETS_RESET_DONE_PLL_SYS_Pos)
#define RESETS_RESET_DONE_PLL_SYS                 RESETS_RESET_DONE_PLL_SYS_Msk

#define RESETS_RESET_DONE_PLL_USB_Pos     (13U)
#define RESETS_RESET_DONE_PLL_USB_Msk     (1UL << RESETS_RESET_DONE_PLL_USB_Pos)
#define RESETS_RESET_DONE_PLL_USB                 RESETS_RESET_DONE_PLL_USB_Msk

#define RESETS_RESET_DONE_PWM_Pos         (14U)
#define RESETS_RESET_DONE_PWM_Msk         (1UL << RESETS_RESET_DONE_PWM_Pos)
#define RESETS_RESET_DONE_PWM                     RESETS_RESET_DONE_PWM_Msk

#define RESETS_RESET_DONE_RTC_Pos         (15U)
#define RESETS_RESET_DONE_RTC_Msk         (1UL << RESETS_RESET_DONE_RTC_Pos)
#define RESETS_RESET_DONE_RTC                     RESETS_RESET_DONE_RTC_Msk

#define RESETS_RESET_DONE_SPI0_Pos        (16U)
#define RESETS_RESET_DONE_SPI0_Msk        (1UL << RESETS_RESET_DONE_SPI0_Pos)
#define RESETS_RESET_DONE_SPI0                    RESETS_RESET_DONE_SPI0_Msk

#define RESETS_RESET_DONE_SPI1_Pos        (17U)
#define RESETS_RESET_DONE_SPI1_Msk        (1UL << RESETS_RESET_DONE_SPI1_Pos)
#define RESETS_RESET_DONE_SPI1                    RESETS_RESET_DONE_SPI1_Msk

#define RESETS_RESET_DONE_SYSCFG_Pos      (18U)
#define RESETS_RESET_DONE_SYSCFG_Msk      (1UL << RESETS_RESET_DONE_SYSCFG_Pos)
#define RESETS_RESET_DONE_SYSCFG                  RESETS_RESET_DONE_SYSCFG_Msk

#define RESETS_RESET_DONE_SYSINFO_Pos     (19U)
#define RESETS_RESET_DONE_SYSINFO_Msk     (1UL << RESETS_RESET_DONE_SYSINFO_Pos)
#define RESETS_RESET_DONE_SYSINFO                 RESETS_RESET_DONE_SYSINFO_Msk

#define RESETS_RESET_DONE_TBMAN_Pos       (20U)
#define RESETS_RESET_DONE_TBMAN_Msk       (1UL << RESETS_RESET_DONE_TBMAN_Pos)
#define RESETS_RESET_DONE_TBMAN                   RESETS_RESET_DONE_TBMAN_Msk

#define RESETS_RESET_DONE_TIMER_Pos       (21U)
#define RESETS_RESET_DONE_TIMER_Msk       (1UL << RESETS_RESET_DONE_TIMER_Pos)
#define RESETS_RESET_DONE_TIMER                   RESETS_RESET_DONE_TIMER_Msk

#define RESETS_RESET_DONE_UART0_Pos       (22U)
#define RESETS_RESET_DONE_UART0_Msk       (1UL << RESETS_RESET_DONE_UART0_Pos)
#define RESETS_RESET_DONE_UART0                   RESETS_RESET_DONE_UART0_Msk

#define RESETS_RESET_DONE_UART1_Pos       (23U)
#define RESETS_RESET_DONE_UART1_Msk       (1UL << RESETS_RESET_DONE_UART1_Pos)
#define RESETS_RESET_DONE_UART1                   RESETS_RESET_DONE_UART1_Msk

#define RESETS_RESET_DONE_USBCTRL_Pos     (24U)
#define RESETS_RESET_DONE_USBCTRL_Msk     (1UL << RESETS_RESET_DONE_USBCTRL_Pos)
#define RESETS_RESET_DONE_USBCTRL                 RESETS_RESET_DONE_USBCTRL_Msk

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
  * @brief RESETS (RESETS)
  */
typedef struct {                                /*!< RESETS Structure                                                          */
  __IOM uint32_t  RESET;                        /*!< Reset control. If a bit is set it means the peripheral is in
                                                     reset. 0 means the peripheral's reset is deasserted.                      */
  __IOM uint32_t  WDSEL;                        /*!< Watchdog select. If a bit is set then the watchdog will reset
                                                     this peripheral when the watchdog fires.                                  */
  __IOM uint32_t  RESET_DONE;                   /*!< Reset done. If a bit is set then a reset done signal has been
                                                     returned by the peripheral. This indicates that the peripheral's
                                                     registers are ready to be accessed.                                       */
} RESETS_t;                                     /*!< Size = 12 (0xc)                                                           */

#ifdef __cplusplus
}
#endif

#endif  /* RP2040_RESET_H */
