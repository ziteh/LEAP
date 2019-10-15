
/**
 ******************************************************************************
 * @file   		PWM_Functions.c
 *	@author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	15-October-2019
 * @brief   	PWM functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "PWM_Functions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize PWM.
  * @param  None
  * @retval None
  */
void PWM_Initialization(void)
{
	// PWM duty cycle % = (TIM_Pulse/TIM_Period)*100%

	/* Structure Declarations */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 		TIM_OCInitStructure;
	GPIO_InitTypeDef 		GPIO_InitStructure;

	/* Enable RCC_APB */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Configure the GPIO pin for PWM */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	// TIM3_CH1 = PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999; // Set the Auto-Reload value
	TIM_TimeBaseStructure.TIM_Prescaler = 0; // Set the Prescaler value
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// Select the Counter Mode
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 333;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	/* Enable */
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	// TIMx peripheral Preload register on CCR1
	TIM_ARRPreloadConfig(TIM3, ENABLE);					// TIMx peripheral Preload register on ARR
	TIM_Cmd(TIM3, ENABLE);								// The specified TIM peripheral
}

void PWMSet(uint8_t DutyCycle)
{
	TIM_SetCompare1(TIM3,pwmdc);	// Set TIM_Pulse(CCR1)
}

/********************************END OF FILE***********************************/


