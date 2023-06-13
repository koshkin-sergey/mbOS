/**************************************************************************//**
 * @file     compiler.h
 * @brief    RISC-V compiler specific macros, functions, instructions
 * @version  V1.0.0
 * @date     12. June 2023
 ******************************************************************************/
/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef __COMPILER_H
#define __COMPILER_H

#include <stdint.h>

/*
 * GNU Compiler
 */
#if   defined ( __GNUC__ )
  #include "gcc.h"


/*
 * IAR Compiler
 */
#elif defined ( __ICCRISCV__ )
  #include "iccriscv.h"


#else
  #error Unknown compiler.
#endif


#endif /* __COMPILER_H */
