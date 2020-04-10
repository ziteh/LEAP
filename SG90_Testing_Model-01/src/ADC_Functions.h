
/**
 ******************************************************************************
 * @file   		ADC_Functions.h
 * @author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	09-April-2020
 * @brief   	Header for ADC_Function.c module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ADC_FUNCTIONS_H_
#define ADC_FUNCTIONS_H_

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Functions.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_Initialization(void);
uint16_t ADC_GetValue(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);

#endif /* ADC_FUNCTIONS_H_ */

/********************************END OF FILE***********************************/
