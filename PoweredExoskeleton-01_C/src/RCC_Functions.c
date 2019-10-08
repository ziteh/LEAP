
/**
  ******************************************************************************
  * @file   	RCC_Functions.c
  * @author  	ZiTe-H
  * @version 	V1.0.0
  * @date    	7-September-2019
  * @brief   	RCC_Configuration program
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
	RCC_DeInit();	// Resets the RCC clock configuration to the default reset state

	/* RCC APB1 */
//	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_USART2, ENABLE);

	/* RCC APB2 */
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA |
							RCC_APB2Periph_GPIOB |
							RCC_APB2Periph_GPIOC |
							RCC_APB2Periph_GPIOD |
							RCC_APB2Periph_GPIOE |
							RCC_APB2Periph_USART1,
							ENABLE);
}

/********************************END OF FILE***********************************/
