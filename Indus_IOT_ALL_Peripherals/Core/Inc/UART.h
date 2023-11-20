#ifndef _uart_H_
#define _uart_H_

/*
 **************************************************************************
 * @file 		UART.h
 * @brief 		UART and its operations
 **************************************************************************
 *
 */
/**************************************************************************
 * @brief Required Includes
 **************************************************************************/
#include "stm32g4xx_hal.h"
#include "main.h"
#include "stdio.h"

/**************************************************************************
 * @brief Required Defines
 **************************************************************************/
#define Integer 22
#define String "IOT"
#define Float 2.2
#define TxData "Indus Board"
#define PRINTF "Printf is in use"

/**************************************************************************
 * @brief Required Handlers
 **************************************************************************/
extern UART_HandleTypeDef huart1;


uint8_t RxDataCallback[1];
uint8_t RxData[4]={0};
//uint8_t Data[10]={0};



/**************************************************************************
 * @brief Wrapper Function
 **************************************************************************/
void UART_Transmit(UART_HandleTypeDef *UART);
void UART_Receive(UART_HandleTypeDef *UART);
void UART_Receive_Interrupt_CallBack(UART_HandleTypeDef *UART);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void Printf_Function(UART_HandleTypeDef *UART);
void UART_Different_Datatypes(UART_HandleTypeDef *UART);
void UART_TRANSMIT(UART_HandleTypeDef *UART,char Data[],uint16_t size,uint32_t TimeOut);
#endif
