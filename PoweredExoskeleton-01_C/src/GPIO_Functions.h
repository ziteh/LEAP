
/**
 ******************************************************************************
 * @file   		GPIO_Functions.h
 * @author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	08-October-2019
 * @brief   	Header for GPIO_Function.c module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_FUNCTIONS_H
#define __GPIO_FUNCTIONS_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "GPIO_mapping.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_Initialization(void);
void PinMod(u8 PortPin, u8 INout, u8 Mode, u8 Speed);
void PinSet(u8 PortPin);
void PinClr(u8 PortPin);
void PinToggle(u8 PortPin);
void PinWrite(u8 PortPin, u8 Value);
u8   PinRead(u8 PortPin);
char PortDetermine(u8 PortPin);

#endif /* __GPIO_FUNCTIONS_H */

/********************************END OF FILE***********************************/
