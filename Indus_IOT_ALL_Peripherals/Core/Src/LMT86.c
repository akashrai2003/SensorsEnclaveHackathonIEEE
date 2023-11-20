/*
 **************************************************************************
 * @file 		lmt86.c
 * @brief 		Reading ADC data from LMT86
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "LMT86.h"
#include "math.h"

/**************************************************************************
 * @brief Start ADC and get ADC data after conversion
 * @param none
 * @return adc data
 **************************************************************************/
uint16_t Get_ADC_Value(){
	uint16_t Raw_Data=0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,100);
	Raw_Data = HAL_ADC_GetValue(&hadc1);
	return Raw_Data;
}

/**************************************************************************
 * @brief Get Calibrated Temprature Data
 * @param data buffer
 * @return temp data
 **************************************************************************/
uint8_t Get_Temprature_data(uint16_t data){
uint8_t Temp = (10.888 - sqrt(((-10.888)*(-10.888)) + 4 * 0.00347 * (1777.3 - data))) / (2 * (-0.00347))+30;;
	return Temp;
}
