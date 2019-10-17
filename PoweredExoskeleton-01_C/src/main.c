
/**
 ******************************************************************************
 * @file		main.c
 * @author		Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V0.1.0
 * @date		08-October-2019
 * @brief   	Powered exoskeleton main program body
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Enable 	(1)
#define Disable (0)
#define CW		(0)
#define CCW		(1)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;
uint8_t USART_ReceivData[];

// Motor control
uint8_t MotorSpeed = 0;			// 0:0%; 100:100%
uint8_t MotorEnable = Disable;	// 0:Disable; 1:Enable
uint8_t MotorDirection = CW; 	// 0:CW; 1:CCW

/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief	Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_md.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */  
  
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  /* Initialize LED2 */
//  STM_EVAL_LEDInit(LED2);
  
  /* Initialize User_Button on STM32NUCLEO */
//  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
  
  /* Initiate Blink Speed variable */ 
//  BlinkSpeed = 0;
  
  /* Infinite loop */
  while(1)
  {

  }
}

/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length, in 1 ms.
* @retval None
*/
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  
  while(TimingDelay != 0);
}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}


#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
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

/**
* @}
*/


/********************************END OF FILE***********************************/
