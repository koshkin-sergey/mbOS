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
#include "asm/Driver_FLASH.h"

#if   defined ( __GNUC__ )
  #define __RAMFUNC                 __attribute__((section(".ramfunc")))
#elif defined ( __ICCARM__ )
  #define __RAMFUNC                 __ramfunc
#endif

__RAMFUNC void writeflash(uint32_t addr,uint16_t data)
{
  FLASH->ADR  = addr;            // set address
  FLASH->DAT  = data;            // set data value
  FLASH->MOD  = 0x08;
  FLASH->CON  = 0x02;            // write command

  while(!(FLASH->STA & 0x03));   // wait for command completion
}

