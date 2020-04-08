
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

#define PosStr		(2.8)	// Leg straight
#define PosBen		(0.05)	// Knee bent
#define PosOffset	(0)

/* Private macro */
/* Private variables */
 USART_InitTypeDef USART_InitStructure;
 static __IO uint32_t TimingDelay;
 int POTdir=0; //0:Def; 1:Straight-MAX; -1:Bent-MAX

/* Private function prototypes */
/* Private functions */
 void Delay_normal(__IO u32 nTime);
 void Delay(__IO uint32_t nTime);
 float get_adc1();
 char* Number_TO_String(uint16_t Number);
 float get_adc1();
 void MotorCtrl(u16 TargetCCR);
// int fputc(int ch, FILE *f);

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

	TIM_SetCompare2(TIM3, 1080);

	//int vPWM = 525; // 525～1720
	//int dPWM = 0;

	ADC_InitTypeDef ADC_InitStruct;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//IO时钟打开，ADC1时钟打开
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//这个是对ADC时钟分频的，ADC时钟不能超过14m，

	ADC_DeInit(ADC1);
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//不需要连续转换
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//数据向右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//不需要事件触发，软件触发就好
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel=1;//只转换一个通道
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//只有一个通道，所以不需要浏览转换
	ADC_Init(ADC1,&ADC_InitStruct);

	ADC_Cmd(ADC1,ENABLE);//这是个坑，一定要使能ADC后才能校准，
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)==1);//等待复位校准完成
	ADC_StartCalibration(ADC1);//校准
	while(ADC_GetCalibrationStatus(ADC1)==1);//等待校准完成


	float Voltage=0;//电压值
//	delay_init();	//延时函数初始化
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	init__uart1();//串口1初始化
//	init_adc3();

	Pin_Clr(LD2);

	while(1)
	{
		Voltage=get_adc1();//获取ADC的电压值
//		printf("Voltage=%f\r\n",Voltage);//发送到电脑
		USART_Send(USART2, Number_TO_String(TIM3->CCR2));
		USART_Send(USART2, "   ");
		USART_Send(USART2, Number_TO_String(POTdir));
		USART_Send(USART2, "   ");
		USART_Send(USART2, Number_TO_String(Voltage*10000));


		USART_Send(USART2, "\n");//发送到电脑
		Delay_normal(0xFFFA);	//这个延时只是为了让数据输出慢点，方便观察
	}
}

void MotorCtrl(u16 TargetCCR)
{
	/*
	while((TargetCCR != (TIM3->CCR2)&(get_adc1() < PosStr)&(get_adc1() > PosBen)))
	{
		u16 NowCCR = (TIM3->CCR2);
		Pin_Set(LD2);
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
	*/

	if(POTdir == 0)	// Def
	{
		while((TargetCCR != (TIM3->CCR2)&(get_adc1() < PosStr)&(get_adc1() > PosBen)))
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
	else if(POTdir == 1) //
	{
		while((TargetCCR != (TIM3->CCR2)&(get_adc1() > PosBen)))
		{
			u16 NowCCR = (TIM3->CCR2);
			TIM_SetCompare2(TIM3, NowCCR-1);
			Delay_normal(0xf0f);
		}
	}
	else if(POTdir == -1) //
	{
		while((TargetCCR != (TIM3->CCR2)&(get_adc1() < PosStr)))
		{
			u16 NowCCR = (TIM3->CCR2);
			TIM_SetCompare2(TIM3, NowCCR+1);
			Delay_normal(0xf0f);
		}
	}

	if(!(get_adc1() < PosStr))
	{
		POTdir = 1;
//		TIM_SetCompare2(TIM3, (TIM3->CCR2)-1);
		USART_Send(USART2, "POS_Str\n");
	}
	else if(!(get_adc1() > PosBen))
	{
		POTdir = -1;
//		TIM_SetCompare2(TIM3, (TIM3->CCR2)+1);
		USART_Send(USART2, "POS_Bet\n");
	}
//	Pin_Clr(LD2);
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

//获取ADC的电压值
float get_adc1()
{
	float temp;
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);//这里选择要转换的通道和转换时间
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);//等待转换完成
	temp=ADC_GetConversionValue(ADC1);//获取ADC的值
	temp=(3.3/4096)*temp;//转换为相应的电压，默认是12位转换的吧
	return temp;
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

