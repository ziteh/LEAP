
/**
  ******************************************************************************
  * @file   	NVIC_Functions.c
  * @author  	ZiTe-H
  * @version 	V1.0.0
  * @date    	7-September-2019
  * @brief   	NVIC Functions
  ******************************************************************************
  * @attention
  *
  * None
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "NVIC_Functions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize NVIC.
  * @param  None
  * @retval None
  */
void NVIC_Initialization(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	// Structure Declarations

	/* Configures the priority grouping */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Configure the NVIC */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/********************************END OF FILE***********************************/
