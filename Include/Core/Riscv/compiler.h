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

/* IO definitions (access restrictions to peripheral registers) */
/**
 * @brief      Defines 'read only' permissions
 */
#ifdef __cplusplus
  #define   __I                       volatile
#else
  #define   __I                       volatile const
#endif
/**
 * @brief       Defines 'write only' permissions
 */
#define     __O                       volatile
/**
 * @brief       Defines 'read / write' permissions
 */
#define     __IO                      volatile

/* following defines should be used for structure members */
/**
 * @brief       Defines 'read only' structure member permissions
 */
#define     __IM                      volatile const
/**
 * @brief       Defines 'write only' structure member permissions
 */
#define     __OM                      volatile
/**
 * @brief       Defines 'read / write' structure member permissions
 */
#define     __IOM                     volatile
/**
 * @brief       Placeholder struct members used for "reserved" areas
 */
#define     RESERVED(N, T)            T RESERVED##N

/**
  \brief     Mask and shift a bit field value for use in a register bit range.
  \param [in] field  Name of the register bit field.
  \param [in] value  Value of the bit field. This parameter is interpreted as an uint32_t type.
  \return           Masked and shifted value.
*/
#define _VAL2FLD(field, value)    (((uint32_t)(value) << field ## _Pos) & field ## _Msk)

/**
  \brief     Mask and shift a register value to extract a bit filed value.
  \param [in] field  Name of the register bit field.
  \param [in] value  Value of register. This parameter is interpreted as an uint32_t type.
  \return           Masked and shifted bit field value.
*/
#define _FLD2VAL(field, value)    (((uint32_t)(value) & field ## _Msk) >> field ## _Pos)

#endif /* __COMPILER_H */
