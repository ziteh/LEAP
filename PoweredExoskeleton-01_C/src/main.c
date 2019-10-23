
/**
 ******************************************************************************
 * @file		main.c
 * @author		Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V0.1.0
 * @date		17-October-2019
 * @brief   	Powered exoskeleton main program body
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
//#include <string.h>
//#include <stdint.h>
#include "stm32f10x.h"
#include "main.h"
#include "GPIO_Functions.h"
#include "RCC_Functions.h"
#include "NVIC_Functions.h"
#include "USART_Functions.h"
#include "PWM_Functions.h"

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;

/* Private define ------------------------------------------------------------*/
#define Enable 	(1)
#define Disable (0)
#define CW		(0)
#define CCW		(1)

/* Pin define */
// Nucleo-64 board
#define PinButton_User	(PC13)	// B1. When push the button, the I/O is LOW value.
#define PinLED_User		(PA5)	// LD2. When the I/O is HIGH value, the LED is on.

// Motor-0
#define PinMotor0_Enbale	(PB5)	// Arduino:D4
#define PinMotor0_Direction	(PB4)	// Arduino:D5
#define PinMotor0_Speed		(PB10)	// Arduino:D6(PWM); TIM2_CH3

// Motor-1
#define PinMotor1_Enbale	(PA8)	// Arduino:D7
#define PinMotor1_Direction	(PA9)	// Arduino:D8
#define PinMotor1_Speed		(PC7)	// Arduino:D9(PWM); TIM3_CH2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;
//uint8_t USART_ReceivData[];

// Motor control
uint8_t MotorSpeed = 0;			// 0:0%; 100:100%
uint8_t MotorEnable = Disable;	// 0:Disable; 1:Enable
uint8_t MotorDirection = CW; 	// 0:CW; 1:CCW

/* Private function prototypes -----------------------------------------------*/
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
  
  /* Initialize */
  RCC_Initialization();
  GPIO_Initialization();
  PWM_Initialization();
  USART_Initialization();
  NVIC_Initialization();

  /* Initialize LED2 */
//  STM_EVAL_LEDInit(LED2);
  
  /* Initialize User_Button on STM32NUCLEO */
//  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
  
  /* Initiate Blink Speed variable */ 
//  BlinkSpeed = 0;
  
  /* Infinite loop */
  while(1)
  {
	  //USART_Send(USART2, "Hi");
	  uint8_t Data[] = "Hi\n";
	  for (int i = 0; Data[i] != '\0'; i++)
	  	{
	  		/* Transmits single data through the USARTx peripheral */
	  		USART_SendData(USART2, (uint16_t)Data[i]);

	  		/* Wait until transmission complete, use TC or TXE flag */
	  		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	  		{/* Null */}
	  	}
	  Delay(1000);
  }
}

/**
* @brief  	Control the motor.
* @param	Motor: the number of motor. This parameter should be: 0~1.
* @param	Status: the status of motor.
* 			This parameter should be 0~2. 0: Disable; 1: Enable; 2: maintain.
* @param	Direction: the direction of motor.
* 			This parameter should be 0~2. 0: CW; 1: CCW; 2: maintain.
* @param	Speed: the speed of motor in %. This parameter should be: 0~100.
* @retval 	None
*/
void MotorCtrl(uint8_t Motor, uint8_t Status, uint8_t Direction, uint8_t Speed)
{

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
