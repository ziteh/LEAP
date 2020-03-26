
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


/* Private typedef */
/* Private define  */
#define MESSAGE5   " program built with "
#define MESSAGE6   " Atollic TrueSTUDIO "

/* Private macro */
/* Private variables */
 USART_InitTypeDef USART_InitStructure;
 static __IO uint32_t TimingDelay;

/* Private function prototypes */
/* Private functions */
 void Delay_normal(__IO u32 nTime);
 void Delay(__IO uint32_t nTime);

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
	USART_Initialization();
	PWM_Initialization();
	NVIC_Initialization();

	TIM_SetCompare2(TIM3, 1720);

	int vPWM = 525; // 525～1720
	int dPWM = 0;

	/* Infinite loop */
	while (1)
	{
//		Delay_normal(0xFFF); // 0xFCF
////		TIM_SetCompare2(TIM3, 840);
////		Delay_normal(0xFFFEF); // 0xFCF
////		TIM_SetCompare2(TIM3, 1140);
//
//		if(dPWM)
//			vPWM++;
//		else
//			vPWM--;
//
//		if(vPWM >= 1220)
//			dPWM = 0;
//		if(vPWM <= 700)
//			dPWM = 1;
//		TIM_SetCompare2(TIM3, vPWM);
	}
}

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

