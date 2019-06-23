/** 
@file     system_ADUCM320.c
@brief:   CMSIS Device System Source File for
          Analog Devices ADUCM320
@version  v0.1
@date     June 6th 2014
 
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

#include "ADUCM320.h"


/*----------------------------------------------------------------------------
  DEFINES
 *---------------------------------------------------------------------------*/

/* Extract the Clock Divider */
#define __CCLK_DIV (1 << (pADI_CLKCTL->CLKCON1 & CLKCON1_CDHCLK_MSK) )

/* define the clock multiplexer input frequencies */
#define __HFOSC    16000000
#define __SPLL     80000000

/*----------------------------------------------------------------------------
  Internal Clock Variables
 *---------------------------------------------------------------------------*/
static uint32_t uClk = 0;    /* Undivided System Clock Frequency (UCLK)   */

/* Frequency of the external clock source connected to P0.5 */
static uint32_t SystemExtClock = 0;
uint32_t SystemCoreClock = __SPLL;/*!< System Clock Frequency (Core Clock)*/


/*----------------------------------------------------------------------------
  Clock functions
 *---------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency     */
{
/* pre-processor verification that clock mux mask and allowed values agree   */
#if ((CLKCON0_CLKMUX_HFOSC   \
    | CLKCON0_CLKMUX_SPLL  \
    | CLKCON0_CLKMUX_EXTCLK) \
    == CLKCON0_CLKMUX_MSK)

    /* update the system core clock according the the current clock mux setting */
    switch (pADI_CLKCTL->CLKCON0 & CLKCON0_CLKMUX_MSK ) {

        case CLKCON0_CLKMUX_HFOSC:
            uClk = __HFOSC;
            break;
        case CLKCON0_CLKMUX_SPLL:
            uClk = __SPLL;
            break;
        case CLKCON0_CLKMUX_EXTCLK:
            uClk = SystemExtClock;
            break;
        /* no need to catch default case due to pre-processor test */
    }

    /* update the divided system clock */
    SystemCoreClock = uClk / __CCLK_DIV;

#else
#error "Clock mux mask and allowed value mismatch!"
#endif
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemFrequency variable.
 */
void SystemInit (void)
{
   /* compute internal clocks */
   SystemCoreClockUpdate();
}

/**
 * @brief  Sets the system external clock frequency
 *
 * @param  ExtClkFreq   External clock frequency in Hz
 * @return none
 *
 * Sets the clock frequency of the source connected to P1.0 clock input source
 */
void SetSystemExtClkFreq (uint32_t ExtClkFreq)
{
    SystemExtClock = ExtClkFreq;
}

/**
 * @brief  Gets the system external clock frequency
 *
 * @return External Clock frequency
 *
 * Gets the clock frequency of the source connected to P1.0 clock input source
 */
uint32_t GetSystemExtClkFreq (void)
{
    return  SystemExtClock;
}



