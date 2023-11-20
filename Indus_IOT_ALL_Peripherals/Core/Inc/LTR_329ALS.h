#ifndef _ltr329als_H_
#define _ltr329als_H_

/*
 **************************************************************************
 * @file 		LTR_329ALS.h
 * @brief 		Light Sensor and its data acquisition
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "stm32g4xx_hal.h"
#include "main.h"

/**************************************************************************
Private Defines
 **************************************************************************/
#define Div_Address      0x52
#define ALS_CONTR        0x80
#define ALS_MEAS_RATE    0x85
#define PART_ID          0x86
#define MANUFAC_ID       0x87
#define ALS_DATA_CH1_0   0x88
#define ALS_DATA_CH1_1   0x89
#define ALS_DATA_CH0_0   0x8A
#define ALS_DATA_CH0_1   0x8B
#define ALS_STATUS       0x8C

/**************************************************************************
Handlers
 **************************************************************************/
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef hlpuart1; 

/**************************************************************************
Wrapper Functions
 **************************************************************************/
void LTR_329ALS_Init(void);
uint8_t Get_Gain(void);
float Get_Int_Factor(void);
uint16_t Get_Raw_CH_1_Data();
uint16_t Get_Raw_CH_0_Data();
float Get_Calibrated_Lux_Value(uint16_t Ch1_raw_data,uint16_t Ch0_raw_data,float Int_factor_data,uint8_t Gain_data);
#endif
