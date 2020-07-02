/**
 ******************************************************************************
 * @file    USART_Functions.h
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    14-October-2019
 * @brief   Header for USART_Functions.c module
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

#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

#ifdef __cplusplus
} /* extern "C" { */
#endif
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void USART_Initialization(void);
void USART_Send(USART_TypeDef* USARTx, uint8_t *Data);
void USART_Send(USART_TypeDef* USARTx, std::string Data);

#endif /* __USART_FUNCTIONS_H */

/********************************END OF FILE***********************************/

