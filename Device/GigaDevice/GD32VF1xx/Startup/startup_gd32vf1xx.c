/*
 * Copyright (C) 2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <Core/Riscv/compiler.h>
#include <asm/system_gd32vf1xx.h>

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/

void _enter(void) __attribute__ ((naked, section(".text.init")));
void _reset(void) __NO_RETURN;
void _exit(int code);
void early_exc_handler(void)  __attribute__((__noreturn__, aligned(16)));

void _enter(void)
{
  __ASM volatile  (
      ".option push                 \n"
      ".option norelax              \n"
      "la   gp, __global_pointer$   \n"
      ".option pop                  \n"
      "la   sp, _sp                 \n"
      "la   t0, early_exc_handler   \n"
      "csrw mtvec, t0               \n"
      "j    _reset                  \n"
  );
}

void _reset(void)
{
  SystemInit();
  __PROGRAM_START();
}

/**
 * @brief       On Release, call the hardware reset procedure.
 *              On Debug we just enter an infinite loop,
 *              to be used as landmark when halting the debugger.
 * @param[in]   code
 */
void _exit(int code __attribute__((unused)))
{
  for (;;);
}

void early_exc_handler(void)
{
  for (;;);
}
