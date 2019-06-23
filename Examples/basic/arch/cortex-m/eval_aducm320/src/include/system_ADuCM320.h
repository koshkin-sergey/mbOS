/** 
@file     system_ADUCM320.h
@brief:   CMSIS Cortex-M3 Device Peripheral Access Layer Header File
          for the ADuCM320
@version  v0.1
@date     February 18th 2013 
 
@section disclaimer Disclaimer
THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES INC. ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT, ARE
DISCLAIMED. IN NO EVENT SHALL ANALOG DEVICES INC. BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

YOU ASSUME ANY AND ALL RISK FROM THE USE OF THIS CODE OR SUPPORT FILE.

IT IS THE RESPONSIBILITY OF THE PERSON INTEGRATING THIS CODE INTO AN APPLICATION
TO ENSURE THAT THE RESULTING APPLICATION PERFORMS AS REQUIRED AND IS SAFE.

**/


/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup aducM320_system
  * @{
  */  

#ifndef __SYSTEM_ADUCM320_H__
#define __SYSTEM_ADUCM320_H__

#ifdef __cplusplus
 extern "C" {
#endif

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
 * @brief  Initialize the system
 *
 * @param  none
 * @return none
 *
 * Setup the microcontroller system.
 * Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * @brief  Update internal SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * Updates the internal SystemCoreClock with current core
 * Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);


/**
 * @brief  Sets the system external clock frequency
 *
 * @param  ExtClkFreq   External clock frequency in Hz
 * @return none
 *
 * Sets the clock frequency of the source connected to Px.x clock input source
 */
extern void SetSystemExtClkFreq (uint32_t ExtClkFreq);


/**
 * @brief  Gets the system external clock frequency
 *
 * @return External Clock frequency
 *
 * Gets the clock frequency of the source connected to Px.x clock input source
 */
extern uint32_t GetSystemExtClkFreq (void);


#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_ADUCM320_H__ */

/**
  * @}
  */
  
/**
  * @}
  */  

