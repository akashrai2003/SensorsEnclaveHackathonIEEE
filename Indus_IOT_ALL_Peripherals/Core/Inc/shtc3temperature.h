
#ifndef _shtc3temprature_H_
#define _shtc3temprature_H_

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
#include "main.h"
#include "stm32g4xx_hal.h"

/**************************************************************************
Handlers
 **************************************************************************/
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart1;


#define CMD19    0xEF                 //ID Reg
#define CMD20    0xC8
#define CMD21    0x7C
#define CMD22    0xA2
#define CMD23    0x5C
#define CMD24    0x24

//Address of the Slave
#define SLAVEADDERESS 0xE0

/**************************************************************************
Wrapper Functions
 **************************************************************************/
uint16_t Read_Device_Id();
uint16_t Read_Temprature();
uint16_t Read_Humidity();
uint8_t Device_check(void);

#endif
