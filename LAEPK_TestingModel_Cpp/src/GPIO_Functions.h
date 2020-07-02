/**
 ******************************************************************************
 * @file    GPIO_Functions.h
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    08-October-2019
 * @brief   Header for GPIO_Function.c module
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
#include "stm32f10x.h"
#include "GPIO_mapping.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* -----Pin Mode and Speed----- */
#define OUT     (0)
#define IN      (1)

#define GPPP    (0)
#define GPOD    (1)
#define AFPP    (2)
#define AFOD    (3)

#define FL      (0)
#define AN      (1)
#define PD      (2)
#define PU      (3)

#define S2M     (2)
#define S10M    (10)
#define S50M    (50)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_Initialization(void);
void Pin_Mod(u8 PortPin, u8 INout, u8 Mode, u8 Speed);
void Pin_Set(u8 PortPin);
void Pin_Clr(u8 PortPin);
void Pin_Toggle(u8 PortPin);
void Pin_Write(u8 PortPin, u8 Value);
u8 Pin_ReadInput(u8 PortPin);
u8 Pin_ReadOutput(u8 PortPin);
char Port_Determine(u8 PortPin);

#endif /* __GPIO_FUNCTIONS_H */

/********************************END OF FILE***********************************/
