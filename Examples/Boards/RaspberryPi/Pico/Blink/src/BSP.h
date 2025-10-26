/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : BSP.h
Purpose : Board support package header

*/

#ifndef BSP_H
#define BSP_H

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

//
// In order to avoid warnings for unused parameters
//
#ifndef BSP_USE_PARA
  #define BSP_USE_PARA(para)  (void) (para)
#endif

/*********************************************************************
*
*       Prototypes
*
**********************************************************************
*/

#ifdef __cplusplus
extern "C" {
#endif

void          BSP_Init        (void);
void          BSP_SetLED      (int Index);
void          BSP_ClrLED      (int Index);
void          BSP_ToggleLED   (int Index);
int           BSP_GetLEDState (int Index);
int           BSP_FPGA_Init   (void);

#ifdef __cplusplus
}
#endif

#endif  // BSP_H

/*************************** End of file ****************************/
