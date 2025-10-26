/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : BSP.c
Purpose : BSP.c for Raspberry Pi Pico

*/

#include "BSP.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define LED_PIN                                   (25)

#define RESETS_BASE_ADDR                          (0x4000C000)
#define RESETS_RESET                              (*(volatile unsigned int*)(RESETS_BASE_ADDR + 0x00u))

#define RESETS_RESET_IO_BANK0_MASK                (1 << 5)
#define RESETS_RESET_IO_PADS_BANK0_MASK           (1 << 8)

#define GPIO_BASE_ADDR                            (0x40014000)
#define GPIOx_STATUS(x)                           (*(volatile unsigned int*)(GPIO_BASE_ADDR + (x * 8u) + 0x00u))
#define GPIOx_CTRL(x)                             (*(volatile unsigned int*)(GPIO_BASE_ADDR + (x * 8u) + 0x04u))

#define PAD_BASE_ADDR                             (0x4001C000)
#define PAD_GPIOx_CTRL(x)                         (*(volatile unsigned int*)(PAD_BASE_ADDR + 0x04u + (x * 4u)))

#define SIO_BASE_ADDR                             (0xD0000000)
#define SIO_GPIO_OUT                              (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x10u))
#define SIO_GPIO_OUT_SET                          (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x14u))
#define SIO_GPIO_OUT_CLR                          (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x18u))
#define SIO_GPIO_OUT_XOR                          (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x1Cu))
#define SIO_GPIO_OE                               (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x20u))
#define SIO_GPIO_OE_SET                           (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x24u))
#define SIO_GPIO_OE_CLR                           (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x28u))
#define SIO_GPIO_OE_XOR                           (*(volatile unsigned int*)(SIO_BASE_ADDR + 0x2Cu))

#define GPIO_IE_MASK                              (1 << 6)
#define GPIO_OD_MASK                              (1 << 7)
#define GPIO_CTRL_FSEL_F5                         (5u)

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       BSP_Init()
*/
void BSP_Init(void) {
  unsigned int v;
  //
  // Get pads and GPIO out of reset
  //
  v = RESETS_RESET;
  v &= ~(RESETS_RESET_IO_BANK0_MASK | RESETS_RESET_IO_PADS_BANK0_MASK);
  RESETS_RESET = v;
  //
  // Clear Output and Output enable
  //
  SIO_GPIO_OE_CLR  = (1 << LED_PIN);
  SIO_GPIO_OUT_CLR = (1 << LED_PIN);
  //
  // Set PAD config to input enable (optional for LED sample)
  //
  v = PAD_GPIOx_CTRL(LED_PIN);
  v &= ~(GPIO_IE_MASK | GPIO_OD_MASK);  // Maske OD and IE
  v |=  (GPIO_IE_MASK);  // Set IE
  PAD_GPIOx_CTRL(LED_PIN) = v;
  //
  //  Set GPIO Control to alt func SIO
  //
  v = 0;
  v |= (GPIO_CTRL_FSEL_F5);  // Alt func F5 (SIO)
  GPIOx_CTRL(LED_PIN) = v;
  //
  // Set pin to output direction and set output high after init
  //
  SIO_GPIO_OE_SET  = (0x1 << LED_PIN); // Set pin to output
  SIO_GPIO_OUT_SET = (0x1 << LED_PIN); // Set output high
}

/*********************************************************************
*
*       BSP_SetLED()
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    SIO_GPIO_OUT_SET = (0x1 << Index); // Set LED
  }
}

/*********************************************************************
*
*       BSP_ClrLED()
*/
void BSP_ClrLED(int Index) {
  if (Index == 0) {
    SIO_GPIO_OUT_CLR = (0x1 << Index); // Clear LED
  }
}

/*********************************************************************
*
*       BSP_ToggleLED()
*/
void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    SIO_GPIO_OUT_XOR = (0x1 << LED_PIN); // Toggle LED
  }
}

/****** End Of File *************************************************/
