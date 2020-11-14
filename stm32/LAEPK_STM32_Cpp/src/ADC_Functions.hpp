/**
 ******************************************************************************
 * @file    ADC_Functions.hpp
 * @author  ZiTe (honmonoh@gmail.com)
 * @version V1.0
 * @date    14-November-2020
 * @brief   Header for ADC_Function.c module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#ifndef ADC_FUNCTIONS_H_
#define ADC_FUNCTIONS_H_

#include "GPIO_Functions.hpp"

/**
 * @brief  Get ADC converted value.
 * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
 * @param  ADC_Channel: the ADC channel to configure.
 * @param  Rank: The rank in the regular group sequencer. This parameter must be between 1 to 16.
 * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
 * @return Converted value
 */
uint16_t ADC_GetValue(ADC_TypeDef *ADCx,
                      uint8_t ADC_Channel,
                      uint8_t Rank,
                      uint8_t ADC_SampleTime);

class ADC
{
public:
  ADC(void);

  GPIO_PortPinTypeDef PortPin;
  ADC_TypeDef *ADCx;
  uint8_t ADC_Channel;
  uint8_t ADC_Rank;
  uint8_t ADC_SampleTime;

  void Init(void);

  void Enable(void);
  void Disable(void);

  /**
   * @brief Get the converted value of ADC.
   * @return Converted value.
   */
  uint16_t getValue(void);

  /**
   * @brief Get the converted value of ADC.
   * @param NewRank: The rank in the regular group sequencer. This parameter must be between 1 to 16.
   * @param NewSampleTime: The sample time value to be set for the selected channel.
   * @return Converted value.
   */
  uint16_t getValue(uint8_t NewRank, uint8_t NewSampleTime);
};

#endif /* ADC_FUNCTIONS_H_ */

/********************************END OF FILE***********************************/
