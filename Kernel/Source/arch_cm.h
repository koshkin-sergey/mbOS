/*
 * Copyright (C) 2021-2022 Sergey Koshkin <koshkin.sergey@gmail.com>
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

#ifndef ARCH_CM_H_
#define ARCH_CM_H_

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <stdbool.h>
#include "Core/Cortex/cmsis_compiler.h"

/*******************************************************************************
 *  defines and macros
 ******************************************************************************/

#define INIT_EXC_RETURN     0xFFFFFFFDUL
#define OS_TICK_HANDLER     SysTick_Handler

/* following defines should be used for structure members */
#define __IM                volatile const      /*! Defines 'read only' structure member permissions */
#define __OM                volatile            /*! Defines 'write only' structure member permissions */
#define __IOM               volatile            /*! Defines 'read / write' structure member permissions */

/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000UL)          /*!< System Control Space Base Address */
#define SCB_BASE            (SCS_BASE + 0x0D00UL)   /*!< System Control Block Base Address */
#define SysTick_BASE        (SCS_BASE + 0x0010UL)   /*!< SysTick Base Address */

#define SCB                 ((SCB_Type *)SCB_BASE)  /*!< SCB configuration struct */
#define SysTick             ((SysTick_Type *)SysTick_BASE)  /*!< SysTick configuration struct */

#if   ((defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) ||       \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) ||       \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))

  #if defined(__CC_ARM)
    #define SVC_INDIRECT_REG          r12
  #elif defined(__ICCARM__)
    #define SVC_FUNC(f)               __asm (                                  \
                                        "mov r12,%0\n"                         \
                                        :: "r"(f): "r12"                       \
                                      )
  #else
    #define SVC_INDIRECT_REG          "r12"
  #endif

#elif ((defined(__ARM_ARCH_6M__)      && (__ARM_ARCH_6M__      != 0)) ||       \
       (defined(__ARM_ARCH_8M_BASE__) && (__ARM_ARCH_8M_BASE__ != 0)))

  #if defined(__CC_ARM)
    #define SVC_INDIRECT_REG          r7
  #elif defined(__ICCARM__)
    #define SVC_FUNC(f)               __asm (                                  \
                                        "mov r7,%0\n"                          \
                                        :: "r"(f): "r7"                        \
                                      )
  #else
    #define SVC_INDIRECT_REG          "r7"
  #endif

#endif

#define BEGIN_CRITICAL_SECTION        uint32_t primask = __get_PRIMASK(); \
                                      __disable_irq();
#define END_CRITICAL_SECTION          __set_PRIMASK(primask);

/*******************************************************************************
 *  typedefs and structures
 ******************************************************************************/

#if   ((defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) ||       \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) ||       \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))
/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

#define SCB_MEMMANAGE_PRIO      0U
#define SCB_BUSFAULT_PRIO       1U
#define SCB_USAGEFAULT_PRIO     2U
#define SCB_SVCALL_PRIO         7U
#define SCB_PENDSV_PRIO        10U
#define SCB_SYSTICK_PRIO       11U

#elif ((defined(__ARM_ARCH_6M__)      && (__ARM_ARCH_6M__      != 0)) || \
       (defined(__ARM_ARCH_8M_BASE__) && (__ARM_ARCH_8M_BASE__ != 0)))
/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
        uint32_t RESERVED0;
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
        uint32_t RESERVED1;
  __IOM uint32_t SHP[2U];                /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
} SCB_Type;

#endif

#define SCB_ICSR_PENDSTCLR_Pos             25U                                  /*!< SCB ICSR: PENDSTCLR Position */
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)      /*!< SCB ICSR: PENDSTCLR Mask */

#define SCB_ICSR_PENDSTSET_Pos             26U                                  /*!< SCB ICSR: PENDSTSET Position */
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)      /*!< SCB ICSR: PENDSTSET Mask */

#define SCB_ICSR_PENDSVSET_Pos             28U                                  /*!< SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)      /*!< SCB ICSR: PENDSVSET Mask */

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

/*******************************************************************************
 *  exported functions
 ******************************************************************************/

/**
 * @fn          bool IsPrivileged(void)
 * @brief       Check if running Privileged
 *
 * @return      true=privileged, false=unprivileged
 */
__STATIC_INLINE
bool IsPrivileged(void)
{
  return ((__get_CONTROL() & 1U) == 0U);
}

/**
 * @fn          bool IsIrqMode(void)
 * @brief       Check if in IRQ Mode
 * @return      true=IRQ, false=thread
 */
__STATIC_INLINE
bool IsIrqMode(void)
{
  return (__get_IPSR() != 0U);
}

/**
 * @fn          bool IsIrqMasked(void)
 * @brief       Check if IRQ is Masked
 * @return      true=masked, false=not masked
 */
__STATIC_INLINE
bool IsIrqMasked(void)
{
#if   ((defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) || \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) || \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))
  return ((__get_PRIMASK() != 0U) || (__get_BASEPRI() != 0U));
#else
  return (__get_PRIMASK() != 0U);
#endif
}

__STATIC_INLINE
void SystemIsrInit(void)
{
  uint32_t n;

#if   ((defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) ||       \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) ||       \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))

  uint32_t p;

  SCB->SHP[SCB_PENDSV_PRIO] = 0xFFU;
  n = 32U - (uint32_t)__CLZ(~(SCB->SHP[10] | 0xFFFFFF00U));
  p = ((SCB->AIRCR >> 8) & 0x07U);
  if (p >= n) {
    n = p + 1U;
  }
  SCB->SHP[SCB_SVCALL_PRIO] = (uint8_t)(0xFEU << n);

#elif ((defined(__ARM_ARCH_6M__)      && (__ARM_ARCH_6M__      != 0)) || \
       (defined(__ARM_ARCH_8M_BASE__) && (__ARM_ARCH_8M_BASE__ != 0)))

  SCB->SHP[1] |= 0x00FF0000U;
  n = SCB->SHP[1];
  SCB->SHP[0] |= (n << (8+1)) & 0xFC000000U;

#endif
}

/**
 * @fn          void setPrivilegedMode(uint32_t)
 * @brief
 *
 * @param       flag
 */
__STATIC_INLINE
void setPrivilegedMode(uint32_t flag)
{
  if (flag != 0U) {
    /* Privileged Thread mode & PSP */
    __set_CONTROL(0x02U);
  } else {
    /* Unprivileged Thread mode & PSP */
    __set_CONTROL(0x03U);
  }
}

/**
 * @fn          void PendServCallReq(void)
 * @brief       Set Pending SV (Service Call) Flag.
 */
__STATIC_FORCEINLINE
void PendServCallReq(void)
{
  SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}

__STATIC_INLINE
uint32_t StackInit(StackAttr_t *attr, bool privileged)
{
  (void) privileged;

  uint32_t *stk = (uint32_t *)(attr->stk_mem + attr->stk_size);

  *(--stk) = 0x01000000L;                       //-- xPSR
  *(--stk) = attr->func_addr;                   //-- Entry Point
  *(--stk) = attr->func_exit;                   //-- R14 (LR)
  *(--stk) = 0x12121212L;                       //-- R12
  *(--stk) = 0x03030303L;                       //-- R3
  *(--stk) = 0x02020202L;                       //-- R2
  *(--stk) = 0x01010101L;                       //-- R1
  *(--stk) = attr->func_param;                  //-- R0 - thread's function argument
  *(--stk) = 0x11111111L;                       //-- R11
  *(--stk) = 0x10101010L;                       //-- R10
  *(--stk) = 0x09090909L;                       //-- R9
  *(--stk) = 0x08080808L;                       //-- R8
  *(--stk) = 0x07070707L;                       //-- R7
  *(--stk) = 0x06060606L;                       //-- R6
  *(--stk) = 0x05050505L;                       //-- R5
  *(--stk) = 0x04040404L;                       //-- R4

  return ((uint32_t)stk);
}

__STATIC_FORCEINLINE
uint32_t svc_0(uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_0(void);

  SVC_FUNC(func);

  return __svc_0();

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0");

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_1(uint32_t param1, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_1(uint32_t);

  SVC_FUNC(func);

  return __svc_1(param1);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_2(uint32_t param1, uint32_t param2, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1, r1=param2}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_2(uint32_t, uint32_t);

  SVC_FUNC(func);

  return __svc_2(param1, param2);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;
  register uint32_t __r1 __ASM("r1") = param2;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_3(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1, r1=param2, r2=param3}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_3(uint32_t, uint32_t, uint32_t);

  SVC_FUNC(func);

  return __svc_3(param1, param2, param3);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;
  register uint32_t __r1 __ASM("r1") = param2;
  register uint32_t __r2 __ASM("r2") = param3;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2)
  );

  return (__r0);

#endif
}

__STATIC_FORCEINLINE
uint32_t svc_4(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t func)
{
#if defined(__CC_ARM)

  register uint32_t __r0 __ASM("r0");

  __ASM {
    SVC 0, {SVC_INDIRECT_REG=func, r0=param1, r1=param2, r2=param3, r3=param4}, {__r0=r0}
  }

  return (__r0);

#elif defined(__ICCARM__)

  _Pragma("swi_number = 0") __swi uint32_t __svc_4(uint32_t, uint32_t, uint32_t, uint32_t);

  SVC_FUNC(func);

  return __svc_4(param1, param2, param3, param4);

#else   // !(defined(__CC_ARM) || defined(__ICCARM__))

  register uint32_t __rf __ASM(SVC_INDIRECT_REG) = func;
  register uint32_t __r0 __ASM("r0") = param1;
  register uint32_t __r1 __ASM("r1") = param2;
  register uint32_t __r2 __ASM("r2") = param3;
  register uint32_t __r3 __ASM("r3") = param4;

  __ASM volatile ("svc 0\n"
                 :"=r"(__r0)
                 :"r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2),"r"(__r3)
  );

  return (__r0);

#endif
}

#endif /* ARCH_CM_H_ */
