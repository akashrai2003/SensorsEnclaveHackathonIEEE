/*
 **************************************************************************
 * @file 		shtc3temperature.c
 * @brief 		shtc3 temperature sensor and its operations
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "shtc3temperature.h"

/**************************************************************************
 * @brief I2C function to get slave acknowledgment
 * @param none
 * @return void
 **************************************************************************/
//void GetSlaveAcknowledgment(){
//	char buffer10[32];
//		if (HAL_OK == Device_check())
//  {
//    	  sprintf(buffer10,"\n\rSHTC3 Device Ready");
//    	  HAL_UART_Transmit(&huart1, (uint8_t *)buffer10, 20, 100);
//    }
//    else{
//    	  sprintf(buffer10,"\n\rSHTC3 Device Not Ready");
//    	  HAL_UART_Transmit(&huart1,(uint8_t *) buffer10, 20, 100);
//    }
//}
//
///**************************************************************************
// * @brief I2C function to get device id
// * @param none
// * @return void
// **************************************************************************/
//void GetDeviceIDSht21(){
//char buffer8[32]={0};
//	uint16_t buffer7=0;
//buffer7 = Read_Device_Id();
//	  sprintf(buffer8,"\n\rID-%x",buffer7);
//		HAL_UART_Transmit(&huart1,(uint8_t *)buffer8,11,100);
//	  HAL_Delay(500);
//}

/**************************************************************************
 * @brief I2C function to get temperature data
 * @param none
 * @return void
 **************************************************************************/
//void GetTempratureSht21(){
//char buffer8[27]={0};
//	uint16_t buffer7 = 0;
//buffer7 = Read_Temprature();
//	buffer7 = 175 * (float)buffer7 / 65536.0f - 45.0f;
//	  sprintf(buffer8,"\n\rTemp->%d",buffer7);
//		HAL_UART_Transmit(&huart1,(uint8_t *)buffer8,11,100);
//	  HAL_Delay(500);
//}
//
///**************************************************************************
// * @brief I2C function to get device id
// * @param none
// * @return device id
// **************************************************************************/
//uint16_t Read_Device_Id(void){
//		uint8_t command1[2];
//			uint8_t Rx_buf[2];
//    uint16_t data=0;
//	command1[0]=CMD19;
//	command1[1]=CMD20;
//HAL_I2C_Master_Transmit(&hi2c2,SLAVEADDERESS,&command1[0],2,100);
//HAL_Delay(100);
//	HAL_I2C_Master_Receive(&hi2c2,SLAVEADDERESS,Rx_buf,2,100);                 //HAL API fro i2c master Rx
//		data = ((Rx_buf[0]<<8)|Rx_buf[1]);
//		return data;
//}
///**************************************************************************
// * @brief I2C function to get temperature data
// * @param none
// * @return temperarature data
// **************************************************************************/
//uint16_t Read_Temprature(){
//		uint8_t command2[2];
//			uint8_t Rx_buf1[2];
//    uint16_t data=0;
//	command2[0]=CMD21;
//	command2[1]=CMD22;
//HAL_I2C_Master_Transmit(&hi2c2,SLAVEADDERESS,&command2[0],2,100);
//HAL_Delay(100);
//	HAL_I2C_Master_Receive(&hi2c2,SLAVEADDERESS,Rx_buf1,2,100);                 //HAL API fro i2c master Rx
//		data = ((Rx_buf1[0]<<8)|Rx_buf1[1]);
//		return data;
//}
//
///**************************************************************************
// * @brief I2C function to get Humidity data
// * @param none
// * @return humidity data
// **************************************************************************/
//uint16_t Read_Humidity(){
//uint8_t command3[2];
//			uint8_t Rx_buf2[2];
//    uint16_t data=0;
//	command3[0]=CMD23;
//	command3[1]=CMD24;
//HAL_I2C_Master_Transmit(&hi2c2,SLAVEADDERESS,&command3[0],2,100);
//HAL_Delay(100);
//	HAL_I2C_Master_Receive(&hi2c2,SLAVEADDERESS,Rx_buf2,2,100);                 //HAL API fro i2c master Rx
//		data = ((Rx_buf2[0]<<8)|Rx_buf2[1]);
//		return data;
//}
//
///**************************************************************************
// * @brief I2C function to check device
// * @param none
// * @return device check status
// **************************************************************************/
//uint8_t Device_check(void){
//	uint8_t DeviceAddress1=SLAVEADDERESS;
//    if (HAL_OK == HAL_I2C_IsDeviceReady(&hi2c2, DeviceAddress1, 1, 100))
//    {
//    	  return 0;
//    }
//    else{
//	      return 1;
//        }
//}
//
//
