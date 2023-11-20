#ifndef EEPROM_H
#define EEPROM_H
#include "main.h"

/*
 **************************************************************************
 * @file 		EEPROM.c
 * @brief 		Writing and reading data from EEPROM with interrupt
 **************************************************************************
 *
 */

/**************************************************************************
Private Define
 **************************************************************************/
#define DATA_IN "Indus"
#define SPI_CS_Pin GPIO_PIN_8
#define SPI_CS_GPIO_Port GPIOD
#define WP_Pin GPIO_PIN_9
#define WP_GPIO_Port GPIOD
#define HOLD_Pin GPIO_PIN_10
#define HOLD_GPIO_Port GPIOD

typedef enum{
	SUCCESS_EEPROM = 0,
	FAIL = 1,
	TIMEOUT = 2,
	BUSY = 3
}ORET_STATUS;

//Function for CS Control
#define EEPROM_CS_HIGH(); HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
#define EEPROM_CS_LOW();	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

//Commands
#define EEPROM_WREN  	0x06
#define EEPROM_WRDI		0x04
#define EEPROM_RDSR  	0x05
#define EEPROM_WRSR		0x01
#define EEPROM_READ  	0x03
#define EEPROM_WRITE	0x02
#define EEPROM_WIP_FLAG 0x01

#define STARTMEM 0x000
#define ENDMEM 0xFFF


/**************************************************************************
Handlers
 **************************************************************************/
extern UART_HandleTypeDef huart1;

extern SPI_HandleTypeDef hspi2;

/**************************************************************************
 * Wrapper Functions
 **************************************************************************/
ORET_STATUS Init_EEPROM (SPI_HandleTypeDef *hspi);
ORET_STATUS WritePage(uint8_t* pTxBuffer, uint16_t pAddr, uint16_t NumOfBytes);
uint8_t ReadPage(uint8_t* rTxBuffer, uint16_t rAddr, uint16_t NumOfBytes);
void WriteEnable (void);
void WriteDisable (void);
uint8_t EEPROM_SPI_WaitStandbyState(void);
void EEPROM_SendInstruction(uint8_t *instruction, uint8_t size);

#endif
