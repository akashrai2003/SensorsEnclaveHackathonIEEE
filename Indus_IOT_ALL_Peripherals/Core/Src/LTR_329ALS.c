/*
 **************************************************************************
 * @file 		LTR_329ALS.c
 * @brief 		Light Sensor and its data acquisition
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "LTR_329ALS.h"

uint8_t Gain=0,Int_Time=0;
float Int_factor=0,ratio,Lux_value;
uint16_t Ch1_data, Ch0_data;

/**************************************************************************
 * @brief Initialize sensor
 * @param none
 * @return void
 **************************************************************************/
void LTR_329ALS_Init(void){
uint8_t Wbuffer[2]={0};
uint8_t Rbuffer[1]={0};
HAL_Delay(100);                                             //initial startup time
Wbuffer[0]=ALS_CONTR;
Wbuffer[1]=0x01;
HAL_I2C_Master_Transmit(&hi2c2,Div_Address,Wbuffer,2,100);  //set the sensor to active mode
HAL_Delay(1000);                                              //wakeup time from standby
}

/**************************************************************************
 * @brief Iget gain from Sensor
 * @param none
 * @return void
 **************************************************************************/
uint8_t Get_Gain(void){
uint8_t Wbuffer[2]={0};
uint8_t Rbuffer[1]={0};
Wbuffer[0]=ALS_CONTR;
Wbuffer[1]=0x01;
HAL_I2C_Master_Transmit(&hi2c2,Div_Address,Wbuffer,1,100);
HAL_I2C_Master_Receive(&hi2c2,Div_Address,Rbuffer,1,100);

Gain = (Rbuffer[0]>>2)&0x07;
switch(Gain){
	case 0: Gain = 1; break;
	case 1: Gain = 2; break;
	case 2: Gain = 4; break;
	case 3: Gain = 8; break;
	case 6: Gain = 48; break;
	case 7: Gain = 96; break;
  }
return Gain;
}

/**************************************************************************
 * @brief Get Integration time factor from sensor. Required for Lux Conversion.
 * @param none
 * @return void
 **************************************************************************/
float Get_Int_Factor(void){
uint8_t Wbuffer1[1]={0};
uint8_t Wbuffer2[1]={0};
uint8_t Rbuffer2[1]={0};
Wbuffer1[0]= ALS_MEAS_RATE;
HAL_I2C_Master_Transmit(&hi2c2,Div_Address,Wbuffer2,1,100);
HAL_I2C_Master_Receive(&hi2c2,Div_Address,Rbuffer2,1,100);
Int_Time = (Rbuffer2[0]>>3)&0x07;
switch(Int_Time){
	case 0: Int_factor = 1; break;
	case 1: Int_factor = 0.5; break;
	case 2: Int_factor = 2; break;
	case 3: Int_factor = 2; break;
	case 4: Int_factor = 1.5; break;
	case 5: Int_factor = 2.5; break;
	case 6: Int_factor = 3; break;
	case 7: Int_factor = 3.5; break;
  }
return Int_factor;
}

/**************************************************************************
 * @brief Get raw data from channel 1. Required for Lux Conversion.
 * @param none
 * @return Raw sensor data
 **************************************************************************/

uint16_t Get_Raw_CH_1_Data(){
uint8_t Wbuffer3[1]={0};
uint8_t Rbuffer3[4]={0};
Wbuffer3[0]=ALS_DATA_CH1_0;
HAL_I2C_Master_Transmit(&hi2c2,Div_Address,Wbuffer3,1,100);
HAL_Delay(200);
HAL_I2C_Master_Receive(&hi2c2,Div_Address,Rbuffer3,4,100);
Ch1_data = (Rbuffer3[1]<<8)+(Rbuffer3[0]);
return Ch1_data;
}

/**************************************************************************
 * @brief Get raw data from channel 0. Required for Lux Conversion.
 * @param none
 * @return Raw sensor data
 **************************************************************************/
uint16_t Get_Raw_CH_0_Data(){
uint8_t Wbuffer3[1]={0};
uint8_t Rbuffer3[4]={0};
Wbuffer3[0]=ALS_DATA_CH1_0;
HAL_I2C_Master_Transmit(&hi2c2,Div_Address,Wbuffer3,1,100);
HAL_Delay(200);
HAL_I2C_Master_Receive(&hi2c2,Div_Address,Rbuffer3,4,100);
Ch0_data = (Rbuffer3[3]<<8)+(Rbuffer3[2]);
return Ch0_data;
}

/**************************************************************************
 * @brief Get calculated Lux Values by using the formulae mensioned in the datasheet "LTR-329ALS Appendix A"
 * @param Raw data from CH1
 * @param Raw data from CH0
 * @param Int factor
 * @param Gain DATA
 * @return Calibrated sensor data
 **************************************************************************/

float Get_Calibrated_Lux_Value(uint16_t Ch1_raw_data,uint16_t Ch0_raw_data,float Int_factor_data,uint8_t Gain_data)
{
ratio = Ch1_raw_data/(Ch1_raw_data + Ch0_raw_data);
if(ratio < 0.45)
Lux_value = ((1.7743 * Ch0_raw_data)+(1.1059 * Ch1_raw_data))/Gain_data/Int_factor_data;
else if(ratio < 0.64 && ratio >= 0.45)
Lux_value = ((4.2785 * Ch0_raw_data)-(1.9548 * Ch1_raw_data))/Gain_data/Int_factor_data;
else if(ratio < 0.85 && ratio >= 0.64)
Lux_value = ((0.5926 * Ch0_raw_data)+(0.1185 * Ch1_raw_data))/Gain_data/Int_factor_data;
else
Lux_value = 0;
return Lux_value;
}
