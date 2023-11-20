
/*
 **************************************************************************
 * @file 		UART.c
 * @brief 		DAC and its operations
 **************************************************************************
 *
 */
#include "DAC.h"

/**************************************************************************
 * @brief Start channel 1 and 2 of same DAC.
 * @param UART Handler
 * @return None
 **************************************************************************/
void Start_Channel(){
HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
//HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);
}

/**************************************************************************
 * @brief Configure Channel 2 for 12bit output mode with right data aligned.
 * @param none
 * @return void
 **************************************************************************/
void DAC_Output_CH_2(){
uint16_t data=1000;
		while(data<4000){
		HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_2,DAC_ALIGN_12B_R,data);
		HAL_Delay(1);
			data+=5;
		}
		while(data>2000){
		HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_2,DAC_ALIGN_12B_R,data);
		HAL_Delay(1);
			data-=5;
		}
}

/**************************************************************************
 * @brief Configure Channel 1 for 12bit output mode with right data aligned.
 * @param none
 * @return void
 **************************************************************************/
void DAC_Output_CH_1(){
uint16_t data=1000;
		while(data<4000){
		HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1,DAC_ALIGN_12B_R,data);
		HAL_Delay(1);
			data+=5;
		}
		while(data>2000){
		HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1,DAC_ALIGN_12B_R,data);
		HAL_Delay(1);
			data-=5;
		}
}
