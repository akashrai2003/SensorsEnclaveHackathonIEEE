/*
 **************************************************************************
 * @file 		LED.c
 * @brief 		Blinking LEDs
 **************************************************************************
 *
 */
#include "LED.h"
/*
==========================================================================
						#### How to use this driver
==========================================================================
(#)Initialize GPIO pins for INDUS Board [Already initialized in main.c]
(#)Include LED.c an LED.h into your project to OFF and ON LEDs respectively.
(#)Use LED_OFF(), LED_ON() APIs with respective parameters.
*/

/*************************************************************************
 *@brief This function power OFF the  LED
 *@param LED Pin
 *@retval NULL
 *
 *************************************************************************/

void LED_OFF(uint16_t Pin)
{
	HAL_GPIO_WritePin(GPIOB,Pin,1);

}


/*************************************************************************
 *@brief This function power ON the LED
 *@param LED Pin
 *@retval NULL
 *
 **************************************************************************/

void LED_ON(uint16_t Pin)
{
	HAL_GPIO_WritePin(GPIOB,Pin,0);

}

/*************************************************************************
 *@brief This function power OFF and ON the LED
 *@param LED Pin
 *@retval NULL
 *
 *************************************************************************/

void LED_Toggle(uint16_t Pin)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);

}



