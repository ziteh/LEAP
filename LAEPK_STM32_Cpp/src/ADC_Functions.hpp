/**
 ******************************************************************************
 * @file    ADC_Functions.hpp
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    09-April-2020
 * @brief   Header for ADC_Function.c module
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
#include "GPIO_Functions.hpp"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t ADC_GetValue(  ADC_TypeDef* ADCx,
                        uint8_t ADC_Channel,
                        uint8_t Rank,
                        uint8_t ADC_SampleTime);

class ADC
{
public:
  ADC(void);
  ADC(ADC_TypeDef* NewADCx,
      uint8_t NewADC_Channel,
      GPIO_PortPinTypeDef NewPortPinOfADC);

  void setADCChannel(ADC_TypeDef* NewADCx, uint8_t NewADC_Channel);
  void setPortPin(GPIO_PortPinTypeDef NewPortPinOfADC);

  void setEnable(void);
  void setDisable(void);
  uint16_t getValue(void);

private:
  GPIO GPIO_ADC;
  ADC_TypeDef* ADCx;
  uint8_t ADC_Channel;
  ADC_InitTypeDef ADC_InitStruct;

  void setInit(ADC_InitTypeDef& ADC_InitStruct);
  void setDefault(void);
};

#endif /* ADC_FUNCTIONS_H_ */

/********************************END OF FILE***********************************/
