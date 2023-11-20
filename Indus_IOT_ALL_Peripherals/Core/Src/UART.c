/*
 **************************************************************************
 * @file 		UART.c
 * @brief 		UART and its operations
 **************************************************************************
 *
 */

/**************************************************************************
Include Files
 **************************************************************************/
#include "UART.h"


/**************************************************************************
 * @brief UART Function for display of information
 * @param UART Handler
 * @return None
 **************************************************************************/

void UART_TRANSMIT(UART_HandleTypeDef *UART,char Data[],uint16_t size,uint32_t TimeOut)
{
	HAL_UART_Transmit (UART, (uint8_t *)Data, size, TimeOut);


}

/**************************************************************************
 * @brief UART Function Using HAL api inside wrapper to receive data over UART.
 * @param UART Handler
 * @return None
 **************************************************************************/
void UART_Receive(UART_HandleTypeDef *UART){
HAL_UART_Receive(&huart1,RxData,sizeof(RxData),2000); 
HAL_Delay(50);
}

/**************************************************************************
 * @brief UART Interrupt function inside wrapper gets called when we receive data.
 * @param UART Handler
 * @return None
 **************************************************************************/
void UART_Receive_Interrupt_CallBack(UART_HandleTypeDef *UART){
HAL_UART_Receive_IT(UART,RxDataCallback,sizeof(RxDataCallback));
}

/**************************************************************************
 * @brief UART Callback fuction modified to transmit data over UART
 * @param UART Handler
 * @return None
 **************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
	HAL_UART_Transmit(huart,RxDataCallback,sizeof(RxDataCallback),1);
}

/**************************************************************************
 * @brief Using printf() function inside wrapper to transmit data over UART.
 * @param UART Handler
 * @return None
 **************************************************************************/
void Printf_Function(UART_HandleTypeDef *UART){
#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
printf("\n\rPrintf Output=%s\n",PRINTF);
	HAL_Delay(500);
}

/**************************************************************************
 * @brief //Modified Function Prototype for Printf
 * @param none
 * @return None
 **************************************************************************/
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

/**************************************************************************
 * @brief Transmitting data of different datatype over UART.
 * @param UART Handler
 * @return None
 **************************************************************************/
void UART_Different_Datatypes(UART_HandleTypeDef *UART){
	char Buffer[64];
	printf("\n\rDiffrent Datatypes:");
	sprintf(Buffer,"\n\rInteger=%d\t\n\rOctal=%o\t\n\rHex=%x\t\n\rFloat=%f\t\n\rString=%s\n",Integer,Integer,Integer,Float,String);
	HAL_UART_Transmit(UART,(uint8_t *)Buffer,sizeof(Buffer),100);
}
