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

#ifndef RP2040_SIO_H
#define RP2040_SIO_H

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

#define SIO                               ((SIO_t*) SIO_BASE)

#define SIO_GPIO_MASK(pin)                (1UL << pin)

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

/**
 * @brief Single-cycle IO block
 *        Provides core-local and inter-core hardware for the two processors,
 *        with single-cycle access. (SIO)
 */
typedef struct {                                /*!< SIO Structure                                                             */
  __IOM uint32_t  CPUID;                        /*!< Processor core identifier                                                 */
  __IOM uint32_t  GPIO_IN;                      /*!< Input value for GPIO pins                                                 */
  __IOM uint32_t  GPIO_HI_IN;                   /*!< Input value for QSPI pins                                                 */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  GPIO_OUT;                     /*!< GPIO output value                                                         */
  __IOM uint32_t  GPIO_OUT_SET;                 /*!< GPIO output value set                                                     */
  __IOM uint32_t  GPIO_OUT_CLR;                 /*!< GPIO output value clear                                                   */
  __IOM uint32_t  GPIO_OUT_XOR;                 /*!< GPIO output value XOR                                                     */
  __IOM uint32_t  GPIO_OE;                      /*!< GPIO output enable                                                        */
  __IOM uint32_t  GPIO_OE_SET;                  /*!< GPIO output enable set                                                    */
  __IOM uint32_t  GPIO_OE_CLR;                  /*!< GPIO output enable clear                                                  */
  __IOM uint32_t  GPIO_OE_XOR;                  /*!< GPIO output enable XOR                                                    */
  __IOM uint32_t  GPIO_HI_OUT;                  /*!< QSPI output value                                                         */
  __IOM uint32_t  GPIO_HI_OUT_SET;              /*!< QSPI output value set                                                     */
  __IOM uint32_t  GPIO_HI_OUT_CLR;              /*!< QSPI output value clear                                                   */
  __IOM uint32_t  GPIO_HI_OUT_XOR;              /*!< QSPI output value XOR                                                     */
  __IOM uint32_t  GPIO_HI_OE;                   /*!< QSPI output enable                                                        */
  __IOM uint32_t  GPIO_HI_OE_SET;               /*!< QSPI output enable set                                                    */
  __IOM uint32_t  GPIO_HI_OE_CLR;               /*!< QSPI output enable clear                                                  */
  __IOM uint32_t  GPIO_HI_OE_XOR;               /*!< QSPI output enable XOR                                                    */
  __IOM uint32_t  FIFO_ST;                      /*!< Status register for inter-core FIFOs (mailboxes). There is one
                                                     FIFO in the core 0 -> core 1 direction, and one core 1
                                                     -> core 0. Both are 32 bits wide and 8 words deep. Core
                                                     0 can see the read side of the 1->0 FIFO (RX), and the
                                                     write side of 0->1 FIFO (TX). Core 1 can see the read side
                                                     of the 0->1 FIFO (RX), and the write side of 1->0 FIFO
                                                     (TX). The SIO IRQ for each core is the logical OR of the
                                                     VLD, WOF and ROE fields of its FIFO_ST register.                          */
  __IOM uint32_t  FIFO_WR;                      /*!< Write access to this core's TX FIFO                                       */
  __IOM uint32_t  FIFO_RD;                      /*!< Read access to this core's RX FIFO                                        */
  __IOM uint32_t  SPINLOCK_ST;                  /*!< Spinlock state A bitmap containing the state of all 32 spinlocks
                                                     (1=locked). Mainly intended for debugging.                                */
  __IOM uint32_t  DIV_UDIVIDEND;                /*!< Divider unsigned dividend Write to the DIVIDEND operand of the
                                                     divider, i.e. the p in `p / q`. Any operand write starts
                                                     a new calculation. The results appear in QUOTIENT, REMAINDER.
                                                     UDIVIDEND/SDIVIDEND are aliases of the same internal register.
                                                     The U alias starts an unsigned calculation, and the S alias
                                                     starts a signed calculation.                                              */
  __IOM uint32_t  DIV_UDIVISOR;                 /*!< Divider unsigned divisor Write to the DIVISOR operand of the
                                                     divider, i.e. the q in `p / q`. Any operand write starts
                                                     a new calculation. The results appear in QUOTIENT, REMAINDER.
                                                     UDIVISOR/SDIVISOR are aliases of the same internal register.
                                                     The U alias starts an unsigned calculation, and the S alias
                                                     starts a signed calculation.                                              */
  __IOM uint32_t  DIV_SDIVIDEND;                /*!< Divider signed dividend The same as UDIVIDEND, but starts a
                                                     signed calculation, rather than unsigned.                                 */
  __IOM uint32_t  DIV_SDIVISOR;                 /*!< Divider signed divisor The same as UDIVISOR, but starts a signed
                                                     calculation, rather than unsigned.                                        */
  __IOM uint32_t  DIV_QUOTIENT;                 /*!< Divider result quotient The result of `DIVIDEND / DIVISOR` (division).
                                                     Contents undefined while CSR_READY is low. For signed calculations,
                                                     QUOTIENT is negative when the signs of DIVIDEND and DIVISOR
                                                     differ. This register can be written to directly, for context
                                                     save/restore purposes. This halts any in-progress calculation
                                                     and sets the CSR_READY and CSR_DIRTY flags. Reading from
                                                     QUOTIENT clears the CSR_DIRTY flag, so should read results
                                                     in the order REMAINDER, QUOTIENT if CSR_DIRTY is used.                    */
  __IOM uint32_t  DIV_REMAINDER;                /*!< Divider result remainder The result of `DIVIDEND % DIVISOR`
                                                     (modulo). Contents undefined while CSR_READY is low. For
                                                     signed calculations, REMAINDER is negative only when DIVIDEND
                                                     is negative. This register can be written to directly,
                                                     for context save/restore purposes. This halts any in-progress
                                                     calculation and sets the CSR_READY and CSR_DIRTY flags.                   */
  __IOM uint32_t  DIV_CSR;                      /*!< Control and status register for divider.                                  */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  INTERP0_ACCUM0;               /*!< Read/write access to accumulator 0                                        */
  __IOM uint32_t  INTERP0_ACCUM1;               /*!< Read/write access to accumulator 1                                        */
  __IOM uint32_t  INTERP0_BASE0;                /*!< Read/write access to BASE0 register.                                      */
  __IOM uint32_t  INTERP0_BASE1;                /*!< Read/write access to BASE1 register.                                      */
  __IOM uint32_t  INTERP0_BASE2;                /*!< Read/write access to BASE2 register.                                      */
  __IOM uint32_t  INTERP0_POP_LANE0;            /*!< Read LANE0 result, and simultaneously write lane results to
                                                     both accumulators (POP).                                                  */
  __IOM uint32_t  INTERP0_POP_LANE1;            /*!< Read LANE1 result, and simultaneously write lane results to
                                                     both accumulators (POP).                                                  */
  __IOM uint32_t  INTERP0_POP_FULL;             /*!< Read FULL result, and simultaneously write lane results to both
                                                     accumulators (POP).                                                       */
  __IOM uint32_t  INTERP0_PEEK_LANE0;           /*!< Read LANE0 result, without altering any internal state (PEEK).            */
  __IOM uint32_t  INTERP0_PEEK_LANE1;           /*!< Read LANE1 result, without altering any internal state (PEEK).            */
  __IOM uint32_t  INTERP0_PEEK_FULL;            /*!< Read FULL result, without altering any internal state (PEEK).             */
  __IOM uint32_t  INTERP0_CTRL_LANE0;           /*!< Control register for lane 0                                               */
  __IOM uint32_t  INTERP0_CTRL_LANE1;           /*!< Control register for lane 1                                               */
  __IOM uint32_t  INTERP0_ACCUM0_ADD;           /*!< Values written here are atomically added to ACCUM0 Reading yields
                                                     lane 0's raw shift and mask value (BASE0 not added).                      */
  __IOM uint32_t  INTERP0_ACCUM1_ADD;           /*!< Values written here are atomically added to ACCUM1 Reading yields
                                                     lane 1's raw shift and mask value (BASE1 not added).                      */
  __IOM uint32_t  INTERP0_BASE_1AND0;           /*!< On write, the lower 16 bits go to BASE0, upper bits to BASE1
                                                     simultaneously. Each half is sign-extended to 32 bits if
                                                     that lane's SIGNED flag is set.                                           */
  __IOM uint32_t  INTERP1_ACCUM0;               /*!< Read/write access to accumulator 0                                        */
  __IOM uint32_t  INTERP1_ACCUM1;               /*!< Read/write access to accumulator 1                                        */
  __IOM uint32_t  INTERP1_BASE0;                /*!< Read/write access to BASE0 register.                                      */
  __IOM uint32_t  INTERP1_BASE1;                /*!< Read/write access to BASE1 register.                                      */
  __IOM uint32_t  INTERP1_BASE2;                /*!< Read/write access to BASE2 register.                                      */
  __IOM uint32_t  INTERP1_POP_LANE0;            /*!< Read LANE0 result, and simultaneously write lane results to
                                                     both accumulators (POP).                                                  */
  __IOM uint32_t  INTERP1_POP_LANE1;            /*!< Read LANE1 result, and simultaneously write lane results to
                                                     both accumulators (POP).                                                  */
  __IOM uint32_t  INTERP1_POP_FULL;             /*!< Read FULL result, and simultaneously write lane results to both
                                                     accumulators (POP).                                                       */
  __IOM uint32_t  INTERP1_PEEK_LANE0;           /*!< Read LANE0 result, without altering any internal state (PEEK).            */
  __IOM uint32_t  INTERP1_PEEK_LANE1;           /*!< Read LANE1 result, without altering any internal state (PEEK).            */
  __IOM uint32_t  INTERP1_PEEK_FULL;            /*!< Read FULL result, without altering any internal state (PEEK).             */
  __IOM uint32_t  INTERP1_CTRL_LANE0;           /*!< Control register for lane 0                                               */
  __IOM uint32_t  INTERP1_CTRL_LANE1;           /*!< Control register for lane 1                                               */
  __IOM uint32_t  INTERP1_ACCUM0_ADD;           /*!< Values written here are atomically added to ACCUM0 Reading yields
                                                     lane 0's raw shift and mask value (BASE0 not added).                      */
  __IOM uint32_t  INTERP1_ACCUM1_ADD;           /*!< Values written here are atomically added to ACCUM1 Reading yields
                                                     lane 1's raw shift and mask value (BASE1 not added).                      */
  __IOM uint32_t  INTERP1_BASE_1AND0;           /*!< On write, the lower 16 bits go to BASE0, upper bits to BASE1
                                                     simultaneously. Each half is sign-extended to 32 bits if
                                                     that lane's SIGNED flag is set.                                           */
  __IOM uint32_t  SPINLOCK0;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK1;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK2;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK3;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK4;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK5;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK6;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK7;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK8;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK9;                    /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK10;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK11;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK12;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK13;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK14;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK15;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK16;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK17;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK18;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK19;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK20;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK21;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK22;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK23;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK24;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK25;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK26;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK27;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK28;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK29;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK30;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
  __IOM uint32_t  SPINLOCK31;                   /*!< Reading from a spinlock address will: - Return 0 if lock is
                                                     already locked - Otherwise return nonzero, and simultaneously
                                                     claim the lock Writing (any value) releases the lock. If
                                                     core 0 and core 1 attempt to claim the same lock simultaneously,
                                                     core 0 wins. The value returned on success is 0x1 << lock
                                                     number.                                                                   */
} SIO_t;                                        /*!< Size = 384 (0x180)                                                        */

#ifdef __cplusplus
}
#endif

#endif  /* RP2040_SIO_H */
