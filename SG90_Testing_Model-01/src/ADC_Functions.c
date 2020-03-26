/*
 * ADC_Functions.c
 *
 *  Created on: Mar 26, 2020
 *      Author: wk415
 */


void ADC_Initialization(void)
{
	ADC_InitTypeDef ADC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//IO时钟打开，ADC1时钟打开
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//这个是对ADC时钟分频的，ADC时钟不能超过14m，

	ADC_DeInit(ADC1);

	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//不需要连续转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据向右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不需要事件触发，软件触发就好
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//只转换一个通道
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//只有一个通道，所以不需要浏览转换
	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_Cmd(ADC1, ENABLE);//这是个坑，一定要使能ADC后才能校准，
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)==1);//等待复位校准完成
	ADC_StartCalibration(ADC1);//校准
	while(ADC_GetCalibrationStatus(ADC1)==1);//等待校准完成
}

//获取ADC的电压值
float ADC_GetValue(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
	float Value;

	ADC_RegularChannelConfig(ADCx, ADC_Channel, Rank, ADC_SampleTime);//这里选择要转换的通道和转换时间
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);//软件触发转换
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC)==0);//等待转换完成
	Value = ADC_GetConversionValue(ADCx);//获取ADC的值

	return Value;
}
