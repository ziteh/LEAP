
/**
 ******************************************************************************
 * @file   		RCC_Functions.c
 *	@author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	08-October-2019
 * @brief   	RCC functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "RCC_Functions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize the different system clocks.
  * @param  None
  * @retval None
  * @attention Please run this function before any other initialization.
  */
void RCC_Initialization(void)
{
	/* Resets the RCC clock configuration to the default reset state */
	RCC_DeInit();

	/* RCC APB1 */
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_USART2	|
							RCC_APB1Periph_TIM2		|	// PWM:Motor0-Speed
							RCC_APB1Periph_TIM3		,	// PWM:Motor1-Speed
							ENABLE);

	/* RCC APB2 */
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA |
							RCC_APB2Periph_GPIOB |
							RCC_APB2Periph_GPIOC |
							RCC_APB2Periph_GPIOD |
							RCC_APB2Periph_GPIOE ,
							ENABLE);
}

/********************************END OF FILE***********************************/
