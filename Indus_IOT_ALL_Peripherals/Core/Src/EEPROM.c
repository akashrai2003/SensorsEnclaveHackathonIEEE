/*
 **************************************************************************
 * @file 		EEPROM.c
 * @brief 		Writing and reading data from EEPROM with interrupt
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "EEPROM.h"

static SPI_HandleTypeDef  *EEPROM_SPI;

/**************************************************************************
 * @brief Initialize EEPROM
 * @param SPI Handler
 * @return Status
 **************************************************************************/
ORET_STATUS Init_EEPROM (SPI_HandleTypeDef *hspi){
	EEPROM_SPI = &hspi2;
	HAL_GPIO_WritePin(WP_GPIO_Port, WP_Pin, 1);
	HAL_GPIO_WritePin(HOLD_GPIO_Port, HOLD_Pin, 1);
}

/**************************************************************************
 * @brief EEPROM Function to write data to eeprom
 * @param Data Buffer
 * @param address
 * @param Number of Bytes
 * @return status
 **************************************************************************/
ORET_STATUS WritePage(uint8_t* pTxBuffer, uint16_t pAddr, uint16_t NumOfBytes)
{
	while (EEPROM_SPI->State != HAL_SPI_STATE_READY)
		{
				HAL_Delay(1);
		}
	HAL_StatusTypeDef EEPROM_STATUS = HAL_TIMEOUT;
	uint8_t command[3];
	WriteEnable ();
	command[0] = EEPROM_WRITE;
	command[1] = pAddr >> 8;
	command[2] = pAddr;
		
		EEPROM_CS_LOW();
	
		EEPROM_SendInstruction(command, 3);
		do
		{
			EEPROM_STATUS = HAL_SPI_Transmit (EEPROM_SPI, pTxBuffer, NumOfBytes, 100);
		}
		while (EEPROM_STATUS == HAL_BUSY || EEPROM_STATUS == HAL_ERROR || EEPROM_STATUS == HAL_TIMEOUT);
		HAL_UART_Transmit (&huart1, "\n\rWriteData:", sizeof("\n\rWriteData:"), 100);
		HAL_UART_Transmit (&huart1, pTxBuffer, NumOfBytes, 100);
		
		EEPROM_CS_HIGH();
		EEPROM_SPI_WaitStandbyState();
		WriteDisable();
		
		if (EEPROM_STATUS == HAL_ERROR)
		{
			HAL_UART_Transmit (&huart1, "\n\rError", sizeof("\n\rError"), 100);
			return FAIL;
		}
		else 
		{
			return SUCCESS_EEPROM;
		}			
}

/**************************************************************************
 * @brief EEPROM Function to read dat from eeprom
 * @param data buffer
 * @param address
 * @number of bytes
 * @return data
 **************************************************************************/
uint8_t ReadPage(uint8_t* pRxBuffer, uint16_t rAddr, uint16_t NumOfBytes)
	{
		while (EEPROM_SPI->State != HAL_SPI_STATE_READY)
		{
			HAL_Delay(1);
			HAL_UART_Transmit (&huart1, "\n\rSPI is busy", sizeof("\n\rSPI is busy"), 100);

		}
		HAL_StatusTypeDef EEPROM_STATUS;
		uint8_t command[3];
		
		command[0] = EEPROM_READ;
		command[1] = rAddr >> 8;
		command[2] = rAddr;
		
		EEPROM_CS_LOW();
	
		EEPROM_SendInstruction(command, 3);
		while (HAL_SPI_Receive(EEPROM_SPI, pRxBuffer, NumOfBytes, 100) == HAL_BUSY)
		{
			HAL_Delay(1);
		}
		EEPROM_CS_HIGH();
		return SUCCESS_EEPROM;
	}
	
/**************************************************************************
 * @brief EEPROM Write Enable by making CS low
 * @param void
 * @return void
 **************************************************************************/
void WriteEnable(void)
	{
		uint8_t command[1] = {EEPROM_WREN};
			EEPROM_CS_LOW();
		EEPROM_SendInstruction((uint8_t*)command, 1);
			EEPROM_CS_HIGH();
	}
	
/**************************************************************************
 * @brief EEPROM Write Disble by making CS High
 * @param void
 * @return void
 **************************************************************************/
void WriteDisable(void)
	{
		uint8_t command[1] = {EEPROM_WRDI};
			EEPROM_CS_HIGH();
		EEPROM_SendInstruction((uint8_t*)command, 1);
	}

/**************************************************************************
 * @brief EEPROM is in it wait/standby state
 * @param none
 * @return return status
 **************************************************************************/
uint8_t EEPROM_SPI_WaitStandbyState()
	{
		uint8_t EEstatus [1] = {0x00};
		uint8_t command [1] = {EEPROM_RDSR};
		
		EEPROM_CS_LOW();
		EEPROM_SendInstruction((uint8_t*)command, 1);
		do
		{
			while (HAL_SPI_Receive(EEPROM_SPI, (uint8_t*)EEstatus, 1, 200) == HAL_BUSY)
			{
				HAL_Delay(1);
			};
			HAL_Delay(1);
		}
		while ((EEstatus [0] & EEPROM_WIP_FLAG) == SET);
		EEPROM_CS_HIGH();
		return 0;
  }

/**************************************************************************
 * @brief Send instruction to eeprom
 * @param pointer to instruction
 * @param size
 * @return void
 **************************************************************************/
void EEPROM_SendInstruction(uint8_t *instruction, uint8_t size)
	{
		while (EEPROM_SPI->State == HAL_SPI_STATE_RESET)
		{
			HAL_Delay(1);
		}
		if  (HAL_SPI_Transmit(EEPROM_SPI, (uint8_t *)instruction, (uint8_t)size, 100) != HAL_OK)
		{
			Error_Handler();
		}
	}

/**************************************************************************
 * @brief Delay function using hal api in it
 * @param void
 * @return void
 **************************************************************************/
void  delay(int delay)
{
HAL_Delay(delay);
}

	
