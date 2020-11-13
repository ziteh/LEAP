/**
 ******************************************************************************
 * @file   		ADC_Functions.c
 *	@author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	26-March-2020
 * @brief   	ADC functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "ADC_Functions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initialize ADC.
 * @param  None
 * @retval None
 */
void ADC_Initialization(void) {
    /* Structure Declarations */
    ADC_InitTypeDef ADC_InitStruct;

    /* RCC config */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);	// ADC's clock con't over 14MHz

    /* GPIO config */
    Pin_Mod(PA1, IN, AN, S50M);

    /* Deinitializes the ADCx peripheral registers to their default reset values */
    ADC_DeInit(ADC1);

    /* ADC configuration */
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1, &ADC_InitStruct);

    /* Enable */
    ADC_Cmd(ADC1, ENABLE);

    /* ADC Calibration */
    ADC_ResetCalibration(ADC1);	// Reset calibration
    while (ADC_GetResetCalibrationStatus(ADC1) == 1) {
    }   // Wait until reset calibration complete
    ADC_StartCalibration(ADC1);	// Start calibration
    while (ADC_GetCalibrationStatus(ADC1) == 1) {
    }	// Wait until calibration complete
}

/**
 * @brief  Get ADC converted value.
 * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
 * @param  ADC_Channel: the ADC channel to configure.
 *   This parameter can be one of the following values:
 *     @arg ADC_Channel_0: ADC Channel0 selected
 *     @arg ADC_Channel_1: ADC Channel1 selected
 *     @arg ADC_Channel_2: ADC Channel2 selected
 *     @arg ADC_Channel_3: ADC Channel3 selected
 *     @arg ADC_Channel_4: ADC Channel4 selected
 *     @arg ADC_Channel_5: ADC Channel5 selected
 *     @arg ADC_Channel_6: ADC Channel6 selected
 *     @arg ADC_Channel_7: ADC Channel7 selected
 *     @arg ADC_Channel_8: ADC Channel8 selected
 *     @arg ADC_Channel_9: ADC Channel9 selected
 *     @arg ADC_Channel_10: ADC Channel10 selected
 *     @arg ADC_Channel_11: ADC Channel11 selected
 *     @arg ADC_Channel_12: ADC Channel12 selected
 *     @arg ADC_Channel_13: ADC Channel13 selected
 *     @arg ADC_Channel_14: ADC Channel14 selected
 *     @arg ADC_Channel_15: ADC Channel15 selected
 *     @arg ADC_Channel_16: ADC Channel16 selected
 *     @arg ADC_Channel_17: ADC Channel17 selected
 * @param  Rank: The rank in the regular group sequencer. This parameter must be between 1 to 16.
 * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
 *   This parameter can be one of the following values:
 *     @arg ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles
 *     @arg ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles
 *     @arg ADC_SampleTime_13Cycles5: Sample time equal to 13.5 cycles
 *     @arg ADC_SampleTime_28Cycles5: Sample time equal to 28.5 cycles
 *     @arg ADC_SampleTime_41Cycles5: Sample time equal to 41.5 cycles
 *     @arg ADC_SampleTime_55Cycles5: Sample time equal to 55.5 cycles
 *     @arg ADC_SampleTime_71Cycles5: Sample time equal to 71.5 cycles
 *     @arg ADC_SampleTime_239Cycles5: Sample time equal to 239.5 cycles
 * @retval Converted value
 */
uint16_t ADC_GetValue(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank,
        uint8_t ADC_SampleTime) {
    ADC_RegularChannelConfig(ADCx, ADC_Channel, Rank, ADC_SampleTime); // ADC Config
    ADC_SoftwareStartConvCmd(ADCx, ENABLE);			// Software start convert
    while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == 0) {
    }   // Wait until convert complete
    return (uint16_t) ADC_GetConversionValue(ADCx);	// Get conversion value
}

/********************************END OF FILE***********************************/
