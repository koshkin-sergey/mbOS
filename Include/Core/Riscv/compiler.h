/*
 * Copyright (C) 2023-2024 Sergey Koshkin <koshkin.sergey@gmail.com>
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
  #include "gcc_riscv.h"


/*
 * IAR Compiler
 */
#elif defined ( __ICCRISCV__ )
  #include "icc_riscv.h"


#else
  #error Unknown compiler.
#endif


#endif /* __COMPILER_H */
