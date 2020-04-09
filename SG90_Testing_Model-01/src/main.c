
/**
 ******************************************************************************
 * @file   		main.c
 *	@author  	Huang, Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	25-March-2020
 * @brief   	Main program body of Powered Exoskeleton-SG90 Testing model
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes */
#include <stddef.h>
#include "stm32f10x.h"
#include "GPIO_Functions.h"
#include "RCC_Functions.h"
#include "PWM_Functions.h"
#include "USART_Functions.h"
#include "NVIC_Functions.h"
#include "ADC_Functions.h"

/* Private typedef */
/* Private define  */
#define MESSAGE5   " program built with "
#define MESSAGE6   " Atollic TrueSTUDIO "

#define LimPos_Straight	(76)	// Leg straight
#define LimPos_Bent		(3724)	// Knee bent
//#define PosOffset	(0)

/* Private macro */
/* Private variables */
 USART_InitTypeDef USART_InitStructure;
 static __IO uint32_t TimingDelay;
 int POTdir=0; //0:Non-Limit; 1:Lim-Straight_Max; -1:Lim-Bent_Max

/* Private function prototypes */
/* Private functions */
 void Delay_normal(__IO u32 nTime);
 void Delay(__IO uint32_t nTime);
// float ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
 char* Number_TO_String(uint16_t Number);
// float ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
 void MotorCtrl(u16 TargetCCR);

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	/* Initialization */
	// Functions & Setups
	RCC_Initialization();
	GPIO_Initialization();
	ADC_Initialization();
	USART_Initialization();
	PWM_Initialization();
	NVIC_Initialization();

	// User-LED
	Pin_Clr(LD2);

	// Motor
//	MotorCtrl(530);
	TIM_SetCompare2(TIM3, 530);

	while(1)
	{
		USART_Send(USART2, Number_TO_String(TIM3->CCR2));
		USART_Send(USART2, "  ");
		USART_Send(USART2, Number_TO_String(POTdir));
		USART_Send(USART2, "  ");
		USART_Send(USART2, Number_TO_String(ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5)));
		USART_Send(USART2, "\n");

		Delay_normal(0xFFFF);
	}
}

void MotorCtrl(u16 TargetCCR)
{
	if((POTdir == 1)|(ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) <= LimPos_Straight)) //Str-Max
	{
		while((TargetCCR > (TIM3->CCR2)) & (ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) < LimPos_Bent))
		{
			u16 NowCCR = (TIM3->CCR2);
			TIM_SetCompare2(TIM3, NowCCR+1);
			Delay_normal(0xf0f);
		}
	}
	else if((POTdir == -1)|(ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) >= LimPos_Bent)) //Bent-Max
	{
		while((TargetCCR < (TIM3->CCR2)) & (ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) > LimPos_Straight))
		{
			u16 NowCCR = (TIM3->CCR2);
			TIM_SetCompare2(TIM3, NowCCR-1);
			Delay_normal(0xf0f);
		}
	}
	else
	{
		while((TargetCCR != (TIM3->CCR2)) & (ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) > LimPos_Straight) & (ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) < LimPos_Bent))
		{
			u16 NowCCR = (TIM3->CCR2);
			if(TargetCCR > NowCCR)
			{
				TIM_SetCompare2(TIM3, NowCCR+1);
			}
			else
			{
				TIM_SetCompare2(TIM3, NowCCR-1);
			}

			Delay_normal(0xf0f);
		}
	}

	if(ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) <= LimPos_Straight)
	{
		POTdir = 1;
		USART_Send(USART2, "POS_Str-Max\n");
	}
	else if(ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5) >= LimPos_Bent)
	{
		POTdir = -1;
		USART_Send(USART2, "POS_Bet-Max\n");
	}
	else
	{
		POTdir = 0;
		USART_Send(USART2, "POS_Nor\n");
	}
}

/**
 * @brief	Convert number into string
 * @param 	Number: The number want to convert.
 * @return	The converted string.
 */
char* Number_TO_String(uint16_t Number)
{
	static char string[3];
	sprintf(string, "%d", Number);
	return string;
}

////获取ADC的电压值
//float ADC_GetValue(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5)
//{
//	float temp;
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);//这里选择要转换的通道和转换时间
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
//	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);//等待转换完成
//	temp=ADC_GetConversionValue(ADC1);//获取ADC的值
//	temp=(3.3/4096)*temp;//转换为相应的电压，默认是12位转换的吧
//	return temp;
//}

/**
 * @brief  Inserts a delay time(no-interrupt).
 * @param  nTime: specifies the delay time length.
 * @retval None
 */
void Delay_normal(__IO u32 nTime)
{
	for(; nTime != 0; nTime--);
}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in 1 ms.
 * @retval None
 */
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;

	while (TimingDelay != 0)
		/* Null */;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}

#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */

