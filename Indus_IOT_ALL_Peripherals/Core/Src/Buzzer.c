/*
 **************************************************************************
 * @file 		Buzzer.c
 * @brief 		Buzzer and its tone related operations
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "Buzzer.h"


/**************************************************************************
 * @brief Staring timer by using HAL api
 * @param none
 * @return void
 **************************************************************************/

void TIM_Start()
{
HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
}


/**************************************************************************
 * @brief Buzzer logical api for tone change
 * @param 0 to 3 diffrent tone input
 * @return void
 **************************************************************************/

void Buzzer_T1(uint8_t Data)
{
	switch(Data)
		{
	case 0x30:
		while(CH2_DC < 100)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC += 10;
    HAL_Delay(1);
}
while(CH2_DC > 0)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC -= 10;
    HAL_Delay(1);
}
		 break;
	case 0x31:
			while(CH2_DC < 1000)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC += 50;
    HAL_Delay(1);
}
while(CH2_DC > 0)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC -= 50;
    HAL_Delay(1);
}
			break;
	case 0x32:
			while(CH2_DC < 10000)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC += 100;
    HAL_Delay(1);
}
while(CH2_DC > 0)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC -= 100;
    HAL_Delay(1);
}
			break;
	case 0x33:
				 while(CH2_DC < 20000)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC += 500;
    HAL_Delay(1);
}
while(CH2_DC > 0)
{
    TIM1->CCR2 = CH2_DC;
    CH2_DC -= 500;
    HAL_Delay(1);
}
				 break;
}
			
	
}
