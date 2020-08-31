/**
 ******************************************************************************
 * @file    ADC_Functions.c
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    26-March-2020
 * @brief   ADC functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "ADC_Functions.hpp"

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
                      uint8_t ADC_SampleTime)
{
  ADC_RegularChannelConfig(ADCx, ADC_Channel, Rank, ADC_SampleTime); // ADC Config
  ADC_SoftwareStartConvCmd(ADCx, ENABLE);                            // Software start convert

  // Wait until convert complete
  while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == 0)
  {
  }
  return (uint16_t)ADC_GetConversionValue(ADCx); // Get conversion value
}

ADC::ADC(void)
{
  this->setDefault();
}

ADC::ADC(ADC_TypeDef *NewADCx,
         uint8_t NewADC_Channel,
         GPIO_PortPinTypeDef NewPortPinOfADC)
{
  this->setADCChannel(NewADCx, NewADC_Channel);
  this->setPortPin(NewPortPinOfADC);

  this->setDefault();
}

void ADC::setADCChannel(ADC_TypeDef *NewADCx, uint8_t NewADC_Channel)
{
  ADCx = NewADCx;
  ADC_Channel = NewADC_Channel;
}
void ADC::setPortPin(GPIO_PortPinTypeDef NewPortPinOfADC)
{
  GPIO_ADC.setPortPin(NewPortPinOfADC);
}
void ADC::setEnable(void)
{
  this->setInit(ADC_InitStruct);

  ADC_Cmd(ADCx, ENABLE);

  /* ADC Calibration */
  ADC_ResetCalibration(ADCx); // Reset calibration
  while (ADC_GetResetCalibrationStatus(ADCx) == 1)
  {
    // Wait until reset calibration complete
  }
  ADC_StartCalibration(ADCx); // Start calibration
  while (ADC_GetCalibrationStatus(ADCx) == 1)
  {
    // Wait until calibration complete
  }
}

void ADC::setDisable(void)
{
  ADC_Cmd(ADCx, DISABLE);
}

uint16_t ADC::getValue(void)
{
  ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // ADC Config
  ADC_SoftwareStartConvCmd(ADCx, ENABLE);                                   // Software start convert
  while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == 0)
  {
    // Wait until convert complete
  }
  return (uint16_t)ADC_GetConversionValue(ADCx); // Get conversion value
}

void ADC::setInit(ADC_InitTypeDef &ADC_InitStruct)
{
  ADC_Init(ADCx, &ADC_InitStruct);
}

void ADC::setDefault(void)
{
  RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ADC's clock con't over 14MHz

  //  ADC_DeInit(ADCx);

  ADC_StructInit(&ADC_InitStruct);

  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_NbrOfChannel = 1;

  GPIO_ADC.setMode(GPIO_Mode_AIN);
}

/********************************END OF FILE***********************************/
