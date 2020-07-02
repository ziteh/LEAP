
/**
 ******************************************************************************
 * @file   		USART_Functions.h
 * @author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	14-October-2019
 * @brief  		Header for USART_Functions.c module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_FUNCTIONS_H
#define __USART_FUNCTIONS_H

/* Includes ------------------------------------------------------------------*/
//#include <iostream>
//#include <string>
//using namespace std;
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void USART_Initialization(void);
//void USART_Send(USART_TypeDef* USARTx, string Data);
//void USART_Send(USART_TypeDef* USARTx, std::string Data);
void USART_Send(USART_TypeDef* USARTx, uint8_t* Data);

#endif /* __USART_FUNCTIONS_H */

/********************************END OF FILE***********************************/

