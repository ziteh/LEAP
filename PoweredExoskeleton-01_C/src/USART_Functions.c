
/**
  ******************************************************************************
  * @file   	USART_Functions.c
  * @author  	Huang Tzu-Fu
  * 			National Formosa University
  * 			Department of Electronic Engineering
  * 			Intelligent Robot System Laboratory
  * @version 	V1.0.0
  * @date    	08-October-2019
  * @brief   	USART functions program
  ******************************************************************************
  * @attention
  *
  * None
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "USART_Functions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize USART.
  * @param  None
  * @retval None
  * @attention Please run "RCC_Initialization()" before this function.
  */
void USART_Initialization(void)
{
	USART_InitTypeDef USART_InitStructure;	// Structure Declarations

//	USART_DeInit(USART2);
	USART_StructInit(&USART_InitStructure);	// Fills each USART_InitStruct member with its default value

	/* Configure the USART */
	/**
	 * USART2 configured as follow:
	 * - BaudRate = 9600 baud
	 * - Word Length = 8 Bits
	 * - One Stop Bit
	 * - No parity
	 * - Hardware flow control disabled (RTS and CTS signals)
	 * - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* Enable "Receive Data register not empty" interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/*Enable USART*/
	USART_Cmd(USART1, ENABLE);

	/* Clear "Transmission Complete" flag, 否則第1位數據會丟失 */
	USART_ClearFlag(USART1, USART_FLAG_TC);
}

/**
  * @brief  USART send data.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   				This parameter can be one of the following values:
  *   				USART1, USART2, USART3, UART4 or UART5.
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_Send(USART_TypeDef* USARTx, uint8_t* Data)
{
	for (int i = 0; Data[i] != '\0'; i++)
	{
		/* Transmits single data through the USARTx peripheral */
		USART_SendData(USARTx, (uint16_t)Data[i]);

		/* Wait until transmission Complete, use TC or TXE flag */
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
		{/* Null */}
	}
}

/********************************END OF FILE***********************************/
