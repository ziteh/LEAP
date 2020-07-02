/**
 ******************************************************************************
 * @file    USART_Functions.c
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    08-October-2019
 * @brief   USART functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
//#include <string>
#include "USART_Functions.hpp"

extern "C"
{
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
}

using namespace std;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
//void USART_Send(USART_TypeDef* USARTx, string Data[]);
//void USART_Send(USART_TypeDef* USARTx, string* Data);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief       Initialize USART.
 * @param       None
 * @retval      None
 * @attention   Please run "RCC_Initialization()" before this function.
 */
void USART_Initialization(void)
{
  /* Structure Declarations */
  USART_InitTypeDef USART_InitStructure;

//    USART_DeInit(USART2);

  /* Fills each USART_InitStruct member with its default value */
  USART_StructInit(&USART_InitStructure);

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
  USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);

  /* Enable "Receive data register not empty" interrupt */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  /* Enable USART */
  USART_Cmd(USART2, ENABLE);

  /* Clear "Transmission Complete" flag, 否則第1位數據會丟失 */
  USART_ClearFlag(USART2, USART_FLAG_TC);
}

/**
 * @brief   USART send data.
 * @param   USARTx: Select the USART or the UART peripheral.
 *                  This parameter can be one of the following values:
 *                   USART1, USART2, USART3, UART4 or UART5.
 * @param   Data: the data to transmit.
 * @retval  None
 */
void USART_Send(USART_TypeDef* USARTx, uint8_t *Data)
{
  for (int i = 0; Data[i] != '\0'; i++)
  {
    /* Transmits single data through the USARTx peripheral */
    USART_SendData(USARTx, (uint16_t) Data[i]);

    /* Wait until transmission complete, use TC or TXE flag */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
    {
    }
  }
}
void USART_Send(USART_TypeDef* USARTx, string Data)
{
  for (int i = 0; Data[i] != '\0'; i++)
  {
    /* Transmits single data through the USARTx peripheral */
    USART_SendData(USARTx, (uint16_t) Data[i]);

    /* Wait until transmission complete, use TC or TXE flag */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
    {
    }
  }
}

/* stm32f1xx_it.c */
///**
//  * @brief  This function handles USARTx_IRQHandler Handler.
//  * @param  None
//  * @retval None
//  */
//void USARTx_IRQHandler(void)
//{
//    if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET) // 注意不是USART_FLAG_RXNE
//    {
//        /* Interrupt function */
//
//        /* NO need to clears the USARTx's interrupt pending bits */
//        /* USART_ClearITPendingBit(USARTx,USART_IT_RXNE); */
//    }
//}
/********************************END OF FILE***********************************/
