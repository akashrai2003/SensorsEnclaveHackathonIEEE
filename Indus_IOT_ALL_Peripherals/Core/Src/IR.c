/*
 **************************************************************************
 * @file 		IR.c
 * @brief 		IR and its operations [TX and RX]
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "IR.h"
uint8_t counter = 0;
uint8_t GPIO_int = 0;

/**************************************************************************
 * @brief GPIO Interrupt callback for IR data reception
 * @param Pin
 * @return None
 **************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
if(GPIO_Pin==GPIO_PIN_7){  
counter = 1;
}

if(GPIO_Pin==GPIO_PIN_2)
{
GPIO_int=1;
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==0)
		HAL_UART_Transmit(&huart1,"0",1,100);
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==1)
		HAL_UART_Transmit(&huart1,"1",1,100);
}
}

/**************************************************************************
 * @brief IR Execution after arrival of IR data
 * @param noen
 * @return void
 **************************************************************************/
void IR_Execute(){
		if(counter == 1){
counter = 0;
			HAL_UART_Transmit(&huart1,"\n\rButton Pressed",sizeof("\n\rButton Pressed"),100);
    HAL_TIM_OC_Start(&htim16,TIM_CHANNEL_1);
		HAL_TIM_OC_Start(&htim17,TIM_CHANNEL_1);
			HAL_Delay(1000);
			HAL_TIM_OC_Stop(&htim16,TIM_CHANNEL_1);
			HAL_TIM_OC_Stop(&htim17,TIM_CHANNEL_1);
		}
		if(GPIO_int == 1){
		GPIO_int = 0;
				HAL_TIM_OC_Stop(&htim16,TIM_CHANNEL_1);
			HAL_TIM_OC_Stop(&htim17,TIM_CHANNEL_1);
		}
}
