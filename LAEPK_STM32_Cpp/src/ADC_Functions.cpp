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

uint16_t ADC_GetValue(ADC_TypeDef *ADCx,
                      uint8_t ADC_Channel,
                      uint8_t Rank = 1,
                      uint8_t ADC_SampleTime = ADC_SampleTime_55Cycles5)
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
  /* ADC's clock con't over than 14MHz. */
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  this->ADC_Rank = 1;
  this->ADC_SampleTime = ADC_SampleTime_55Cycles5;
}

void ADC::Init(void)
{
  GPIO ADC_GPIO;
  ADC_GPIO.PortPin = this->PortPin;
  ADC_GPIO.Mode = GPIO_Mode_AIN;
  ADC_GPIO.Init();

  ADC_DeInit(this->ADCx);

  ADC_InitTypeDef ADC_InitStruct;
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStruct.ADC_NbrOfChannel = 1;
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;
  ADC_Init(this->ADCx, &ADC_InitStruct);
}

void ADC::Enable(void)
{
  ADC_Cmd(this->ADCx, ENABLE);

  /* ADC Calibration */
  // Reset calibration
  ADC_ResetCalibration(this->ADCx);

  // Wait until reset calibration complete
  while (ADC_GetResetCalibrationStatus(this->ADCx) == 1)
  {
  }

  // Start calibration
  ADC_StartCalibration(this->ADCx);

  // Wait until calibration complete
  while (ADC_GetCalibrationStatus(this->ADCx) == 1)
  {
  }
}

void ADC::Disable(void)
{
  ADC_Cmd(ADCx, DISABLE);
}

uint16_t ADC::getValue(void)
{
  ADC_RegularChannelConfig(this->ADCx, this->ADC_Channel, this->ADC_Rank, this->ADC_SampleTime);
  ADC_SoftwareStartConvCmd(this->ADCx, ENABLE);

  // Wait for convert complete
  while (ADC_GetFlagStatus(this->ADCx, ADC_FLAG_EOC) == 0)
  {
  }

  return (uint16_t)ADC_GetConversionValue(this->ADCx);
}

uint16_t ADC::getValue(uint8_t NewRank, uint8_t NewSampleTime)
{
  ADC_RegularChannelConfig(this->ADCx, this->ADC_Channel, NewRank, NewSampleTime);
  ADC_SoftwareStartConvCmd(this->ADCx, ENABLE);

  // Wait for convert complete
  while (ADC_GetFlagStatus(this->ADCx, ADC_FLAG_EOC) == 0)
  {
  }

  return (uint16_t)ADC_GetConversionValue(this->ADCx);
}

/********************************END OF FILE***********************************/
