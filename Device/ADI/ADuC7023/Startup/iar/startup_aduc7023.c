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

#include "asm/aduc7023.h"

extern uint32_t SVC_STACK$$Limit;
extern uint32_t ABT_STACK$$Limit;
extern uint32_t UND_STACK$$Limit;

__arm void __iar_init_core(void)
{
  // Setup Stack for exceptional mode
  __ASM volatile(
      "MSR    CPSR_c, #0xD3                            \n"
      "LDR    SP, =SVC_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xD7                            \n"
      "LDR    SP, =ABT_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xDB                            \n"
      "LDR    SP, =UND_STACK$$Limit                    \n"
      "MSR    CPSR_c, #0xD0                            \n"
      "LDR    R0, =SystemInit                          \n"
      "MOV    LR, PC                                   \n"
      "BX     R0                                       \n"
      :
      :
      : "cc", "r0", "lr"
  );
}
