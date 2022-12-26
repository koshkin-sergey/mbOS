/*
 * Copyright (C) 2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup ADUCM32x
  * @{
  */
    
#ifndef ADUCM32X_H_
#define ADUCM32X_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
   
/* Uncomment the line below according to the target ADUCM32x device used in your
 * application.
 */
#if !defined (ADUCM320) && !defined (ADUCM320I) && \
    !defined (ADUCM322) && !defined (ADUCM322I)
  /* #define ADUCM320  */
  /* #define ADUCM320I */
  /* #define ADUCM322  */
  /* #define ADUCM322I */
#endif
   
/*  Tip: To avoid modifying this file each time you need to switch between these
 *       devices, you can define the device in your toolchain compiler preprocessor.
 */

/** @addtogroup Device_Included
  * @{
  */

#if defined(ADUCM320)
  #include "aducm320.h"
#elif defined(ADUCM320I)
  #include "aducm320i.h"
#elif defined(ADUCM322)
  #include "aducm322.h"
#elif defined(ADUCM322I)
  #include "aducm322i.h"
#else
 #error "Please select first the target ADUCM32x device used in your application (in aducm32x.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_macro
  * @{
  */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ADUCM32X_H_ */

/**
 * @}
 */

/**
 * @}
 */
