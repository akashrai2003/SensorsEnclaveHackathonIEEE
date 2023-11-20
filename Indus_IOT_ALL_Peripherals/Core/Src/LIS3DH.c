/*
 **************************************************************************
 * @file 		LIS3DH.c
 * @brief 		Calculating Forward backward steps using 3 axis data of Accelerometer.
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "LIS3DH.h"
#include "math.h"

/**************************************************************************
Required Variables
 **************************************************************************/
//2. Sensitivity value
static float Sensitivity = SENSITIVITY_0_06G;
//3. bias variables
static float X_Bias = 0.0f;
static float Y_Bias = 0.0f;
static float Z_Bias = 0.0f;
//4. scaling variables
static float X_Scale = 1.0f;
static float Y_Scale = 1.0f;
static float Z_Scale = 1.0f;
int flag = 0;
int forward_steps=0;
int backward_steps=0;
char buffer_steps[16];
char buffer_rolling[23];
char buffer_pitching[24];
int16_t pitching =0;
int16_t rolling=0;
int flag1=0;
int flag2=0;
DataScaled myAxisData;

/**************************************************************************
 * @brief Read content of WHO_AM_I Reg
 * @param none
 * @return register data
 **************************************************************************/
uint8_t Read_WHO_AM_I_Reg(){
uint8_t data[1]= {0};
HAL_I2C_Mem_Read(&hi2c2, DIV_ADDRESS, WHO_AM_I_ADDR, 1,  (uint8_t *)data, 1, 100);
return data[0];
}

/**************************************************************************
 * @brief Writing to Accelerometer sensor using HAL APIs
 * @param register
 * @param data buffer
 * @param size
 * @return register data
 **************************************************************************/
void WriteIO(uint8_t reg, uint8_t *dataW, uint8_t size)
{
	uint8_t Reg = reg;
	//set register value
	HAL_I2C_Master_Transmit(&hi2c2,DIV_ADDRESS, &Reg, 1, 10);
	//Transmit data
	HAL_I2C_Master_Transmit(&hi2c2,DIV_ADDRESS, dataW, size, 10);
}
/**************************************************************************
 * @brief Reading from Accelerometer sensor using HAL APIs
 * @param register
 * @param data buffer
 * @param size
 * @return register data
 **************************************************************************/
void ReadIO(uint8_t reg, uint8_t *dataR, uint8_t size)
{
	uint8_t Buf[4];
	Buf[0] = reg | 0x80;
	//set register value
	HAL_I2C_Master_Transmit(&hi2c2,DIV_ADDRESS, Buf, 1, 10);
	//Transmit data
	HAL_I2C_Master_Receive(&hi2c2,DIV_ADDRESS, Buf, size, 10);
	for(uint8_t i=0; i<(size&0x3); i++)
	{
		dataR[i] = Buf[i];
	}
}


/**************************************************************************
 * @brief Accelerometer sensor initialization using HAL APIs
 * @param Handler
 * @param Initialization parameters
 * @return register data
 **************************************************************************/
void Init(I2C_HandleTypeDef *acc, InitTypeDef *accInitDef)
{
		uint8_t Command[3];
	Command[0]=XYZ_ENABLE;
	Command[1]=FULLSCALE_8;
//WriteIO(CTRL_REG4_ADDR, &Command[1], 1);
//	WriteIO(CTRL_REG1_ADDR, &Command[0], 1);
HAL_I2C_Mem_Write(&hi2c2, DIV_ADDRESS, CTRL_REG4_ADDR, 1, &Command[1], 1, 100);    
HAL_I2C_Mem_Write(&hi2c2, DIV_ADDRESS, CTRL_REG1_ADDR, 1, &Command[0], 1, 100); 
	uint8_t Data = 0;
	
	memcpy(&hi2c2, acc, sizeof(*acc));
	//** 1. Enable Axes and Output Data Rate **//
	//Set CTRL REG4 settings value
	Data |= (accInitDef->enableAxes & 0x07);		//Enable Axes
	Data |= (accInitDef->dataRate & 0xF0);			//Output Data Rate
	//Write to accelerometer
	WriteIO(CTRL_REG1_ADDR, &Data, 1);
	
	//** 2. Full-Scale selection, Anti-aliasing BW, self test**//
	Data = 0;
	Data |= (accInitDef->antiAliasingBW & 0xC0);		//Anti-aliasing BW
	Data |= (accInitDef->fullScale & 0x38);				//Full-Scale
	//Write to accelerometer
	WriteIO(CTRL_REG5_ADDR, &Data, 1);
	
	//** 3. Interrupt Configuration **//
	if(accInitDef->interruptEnable)
	{
		Data = 0x88;
		//Write to accelerometer
		WriteIO(CTRL_REG4_ADDR, &Data, 1);
	}
	
	//Assign sensor sensitivity (based on Full-Scale)
	switch(accInitDef->fullScale)
	{
		case FULLSCALE_2:
			Sensitivity = SENSITIVITY_0_06G;
			break;
		
		case FULLSCALE_4:
			Sensitivity = SENSITIVITY_0_12G;
			break;
		
		case FULLSCALE_6:
			Sensitivity =SENSITIVITY_0_18G;
			break;
		
		case FULLSCALE_8:
			Sensitivity = SENSITIVITY_0_24G;
			break;
		
		case FULLSCALE_16:
		  Sensitivity = SENSITIVITY_0_73G;
			break;
	}
}
/**************************************************************************
 * @brief Get sensors raw data
 * @param void
 * @return register raw data
 **************************************************************************/
DataRaw GetDataRaw(void)
{
	uint8_t Buf[2];
	DataRaw tempDataRaw;
	//Read X data
	ReadIO(OUT_X_L_ADDR, Buf, 2);
	tempDataRaw.x = ((Buf[1] << 8) + Buf[0]);
	
	//Read Y data
ReadIO(OUT_Y_L_ADDR, Buf, 2);
	tempDataRaw.y = ((Buf[1] << 8) + Buf[0]);
	
	//Read Z data
	ReadIO(OUT_Z_L_ADDR, Buf, 2);
	tempDataRaw.z = ((Buf[1] << 8) + Buf[0]);
	
	return tempDataRaw;
	
}
/**************************************************************************
 * @brief Get scaled data from raw data
 * @param void
 * @return scaled data
 **************************************************************************/
DataScaled GetDataScaled(void)
{
	//Read raw data
	DataRaw tempRawData = GetDataRaw();;
	//Scale data and return 
	DataScaled tempScaledData;
	tempScaledData.x = (tempRawData.x * Sensitivity * X_Scale) + 0.0f - X_Bias;
	tempScaledData.y = (tempRawData.y * Sensitivity * Y_Scale) + 0.0f - Y_Bias;
	tempScaledData.z = (tempRawData.z * Sensitivity * Z_Scale) + 0.0f - Z_Bias;
	
	return tempScaledData;
}
/**************************************************************************
 * @brief Pol for data ready
 * @param timeout
 * @return status
 **************************************************************************/
bool PollDRDY(uint32_t msTimeout)
{
	uint8_t Acc_status;
	uint32_t startTick = HAL_GetTick();
	do
	{
		//Read status register with a timeout
		ReadIO(0x27, &Acc_status, 1);
		if(Acc_status & 0x07)break;
		
	}while((Acc_status & 0x07)==0 && (HAL_GetTick() - startTick) < msTimeout);
	if(Acc_status & 0x07)
	{
		return true;
	}
	return false;
	
}

/**************************************************************************
 * @brief X axis calibration API
 * @param x min
 * @param X max
 * @return void
 **************************************************************************/
void X_calibrate(float x_min, float x_max)
{
	X_Bias = (x_max+x_min)/2.0f;
	X_Scale = (2*1000)/(x_max - x_min);
}
/**************************************************************************
 * @brief Y axis calibration API
 * @param Y min
 * @param Y max
 * @return void
 **************************************************************************/
void Y_calibrate(float y_min, float y_max)
{
	Y_Bias = (y_max+y_min)/2.0f;
	Y_Scale = (2*1000)/(y_max - y_min);
}
/**************************************************************************
 * @brief Z axis calibration API
 * @param Z min
 * @param Z max
 * @return void
 **************************************************************************/
void Z_calibrate(float z_min, float z_max)
{
	Z_Bias = (z_max+z_min)/2.0f;
	Z_Scale = (2*1000)/(z_max - z_min);
}

/**************************************************************************
 * @brief Calculate Rolling Angle
 * @param void
 * @return angle data
 **************************************************************************/
int16_t Rolling(void){
	DataScaled Newdata;
	Newdata =GetDataScaled();
	float x_axis = Newdata.x;
	float y_axis = Newdata.y;
	float z_axis = Newdata.z;
	rolling = atan(1 * x_axis / sqrt(pow(y_axis, 2) + pow(z_axis, 2))) * 180 / 3.14;
  sprintf(buffer_rolling,"\n\rRolling=%d degree",rolling);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_rolling,23,100);
	return rolling;
}

/**************************************************************************
 * @brief Calculate Pitching Angle
 * @param void
 * @return angle data
 **************************************************************************/
int16_t Pitching(void){
		DataScaled Newdata;
	Newdata =GetDataScaled();
	float x_axis =  Newdata.x;
	float y_axis =  Newdata.y;
	float z_axis =  Newdata.z;
  pitching = atan(1 * y_axis / sqrt(pow(x_axis, 2) + pow(z_axis, 2))) * 180 / 3.14;
 sprintf(buffer_pitching,"\n\rPitching=%d degree",pitching);                           
	HAL_UART_Transmit(&huart1,(uint8_t *)buffer_pitching,24,100);
	return pitching;
}

/**************************************************************************
 * @brief Calculate Forward and Backward steps using Angle
 * @param void
 * @return none
 **************************************************************************/
uint8_t steps_fw_bw(void){
if((pitching < 60)&& flag1==0){
	forward_steps+=1;
	flag1=1;
	 sprintf(buffer_steps,"\n\rForward Steps=%d",forward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,18,100);
}
else if((pitching < 60)&&(flag1==1)){
sprintf(buffer_steps,"\n\rForward Steps=%d",forward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,18,100);
}
else{
sprintf(buffer_steps,"\n\rForward Steps=%d",forward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,18,100);
}
if((pitching > 60)&&(flag1==1)){
	flag1=0;
	sprintf(buffer_steps,"\n\rForward Steps=%d",forward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,18,100);
}

if((pitching > -60)&& flag2==0){
	backward_steps+=1;
	flag2=1;
	 sprintf(buffer_steps,"\n\rBackward Steps=%d",backward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,19,100);
}
else if((pitching > -60)&&(flag2==1)){
sprintf(buffer_steps,"\n\rBackward Steps=%d",backward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,19,100);
}
else{
sprintf(buffer_steps,"\n\rBackward Steps=%d",backward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,19,100);
}
if((pitching < -60)&&(flag2==1)){
	flag2=0;
	sprintf(buffer_steps,"\n\rBackward Steps=%d",backward_steps);                           
		HAL_UART_Transmit(&huart1,(uint8_t *)buffer_steps,19,100);
}
}

///**************************************************************************
// * @brief Delay function using hal APi inside
// * @param delay
// * @return void
// **************************************************************************/
//void delay(uint8_t delay)
//{
//	HAL_Delay(delay);
//
//}
