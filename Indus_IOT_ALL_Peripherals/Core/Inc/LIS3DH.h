#ifndef _lis3dh_H_
#define _lis3dh_H_

/*
 **************************************************************************
 * @file 		LIS3DH.h
 * @brief 		Accelerometer and its Operations related to 3 axis data acquisition .
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "stm32g4xx_hal.h"
#include "main.h"
#include "stdbool.h"

/**************************************************************************
Handlers
 **************************************************************************/
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart1;

/**************************************************************************
Private Defines
 **************************************************************************/
#define X_THRESHOLD 600
#define Y_THRESHOLD -0.078
#define Z_THRESHOLD .60

//List of Defines
#define DIV_ADDRESS 0x30               
#define WHO_AM_I_ADDR                0x0F
#define CTRL_REG1_ADDR               0x20
#define CTRL_REG2_ADDR               0x21
#define CTRL_REG3_ADDR               0x22
#define CTRL_REG4_ADDR               0x23              
#define CTRL_REG5_ADDR               0x24
#define CTRL_REG6_ADDR               0x25

#define STATUS_ADDR                  0x27

#define OUT_X_L_ADDR                 0x28
#define OUT_X_H_ADDR                 0x29
#define OUT_Y_L_ADDR                 0x2A
#define OUT_Y_H_ADDR                 0x2B
#define OUT_Z_L_ADDR                 0x2C
#define OUT_Z_H_ADDR                 0x2D


//Data rate
#define DATARATE_POWERDOWN           ((uint8_t)0x00)  /* Power Down Mode*/
#define DATARATE_1                   ((uint8_t)0x10)  /* 3.125 Hz Normal Mode */
#define DATARATE_10                  ((uint8_t)0x20)  /* 6.25  Hz Normal Mode */
#define DATARATE_25                  ((uint8_t)0x30)  /* 12.5  Hz Normal Mode */
#define DATARATE_50                  ((uint8_t)0x40)  /* 25    Hz Normal Mode */
#define DATARATE_100                 ((uint8_t)0x50)  /* 50    Hz Normal Mode */
#define DATARATE_200                 ((uint8_t)0x60)  /* 100   Hz Normal Mode */
#define DATARATE_400                 ((uint8_t)0x70)  /* 400   Hz Normal Mode */
#define DATARATE_1600                ((uint8_t)0x80)  /* 800   Hz Normal Mode */
#define DATARATE_5376                ((uint8_t)0x90)  /* 1600  Hz Normal Mode */

//Full scale
#define FULLSCALE_2                  ((uint8_t)0x00)  /* 2 g  */
#define FULLSCALE_4                  ((uint8_t)0x08)  /* 4 g  */
#define FULLSCALE_6                  ((uint8_t)0x10)  /* 6 g  */
#define FULLSCALE_8                  ((uint8_t)0x18)  /* 8 g  */
#define FULLSCALE_16                 ((uint8_t)0x20)  /* 16 g */

// Anti-Aliasing Bandwidth
#define FILTER_BW_800                ((uint8_t)0x00)  /* 800 Hz */
#define FILTER_BW_400                ((uint8_t)0x80)  /* 400 Hz  */
#define FILTER_BW_200                ((uint8_t)0x40)  /* 200 Hz */
#define FILTER_BW_50                 ((uint8_t)0xC0)  /* 50 Hz  */

//Enabled axis 
#define X_ENABLE                     ((uint8_t)0x01)
#define Y_ENABLE                     ((uint8_t)0x02)
#define Z_ENABLE                     ((uint8_t)0x04)
#define XYZ_ENABLE                   ((uint8_t)0x67)

//Sensitivity values (Based on Full-Scale)
#define SENSITIVITY_0_06G            0.06  /* 0.06 mg/digit*/
#define SENSITIVITY_0_12G            0.12  /* 0.12 mg/digit*/
#define SENSITIVITY_0_18G            0.18  /* 0.18 mg/digit*/
#define SENSITIVITY_0_24G            0.24  /* 0.24 mg/digit*/
#define SENSITIVITY_0_73G            0.73  /* 0.73 mg/digit*/

//Typedefs
//1. Accelerometer Configuration struct
typedef struct 
{
	uint8_t dataRate;
	uint8_t fullScale;
	uint8_t antiAliasingBW;
	uint8_t enableAxes;
	bool interruptEnable;
}InitTypeDef;

//2. Accelerometer raw data
typedef struct 
{
	int16_t x;
	int16_t y;
	int16_t z;
}DataRaw;

//3. Accelerometer mg data (scaled data)
typedef struct
{
	float x;
	float y;
	float z;
}DataScaled;

/**************************************************************************
Wrapper Functions
 **************************************************************************/
//Private functions
//1. Write IO
void WriteIO(uint8_t reg, uint8_t *dataW, uint8_t size);
//2. Read IO
void ReadIO(uint8_t reg, uint8_t *dataR, uint8_t size);


//1. Accelerometer initialise function
void Init(I2C_HandleTypeDef *accSPI, InitTypeDef *accInitDef);
//2. Get Accelerometer raw data
DataRaw GetDataRaw(void);
//3. Get Accelerometer mg data
DataScaled GetDataScaled(void);
//4. Poll for Data Ready
bool PollDRDY(uint32_t msTimeout);

//** Calibration functions **//
//1. Set X-Axis calibrate
void X_calibrate(float x_min, float x_max);
//2. Set Y-Axis calibrate
void Y_calibrate(float y_min, float y_max);
//3. Set Z-Axis calibrate
void Z_calibrate(float z_min, float z_max);

//Padometer Functions
int16_t Pitching(void);
int16_t Rolling(void);
uint8_t steps_fw_bw(void);
#endif
