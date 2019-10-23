/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    7-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f10x.h"
#include "GPIO_Functions.h"
#include "GPIO_mapping.h"
#include "RCC_Functions.h"
#include "NVIC_Functions.h"
#include "USART_Functions.h"

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
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

uint8_t TxBuf1[] = "Hello, World!\n";
uint8_t RxBuf1[] = "";

// Motor control
uint8_t MotorSpeed = 0;			// 0:0%; 100:100%
uint8_t MotorEnable = Disable;	// 0:Disable; 1:Enable
uint8_t MotorDirection = CW; 	// 0:CW; 1:CCW


/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
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

  /* Initialization */
  RCC_Initialization();
  USART_Initialization();
  GPIO_Initialization();
  NVIC_Initialization();

  GPIO_ResetBits(GPIOA,GPIO_Pin_5);

  /* Infinite loop */
  while (1)
  {
//	for (int i = 0; TxBuf1[i] != '\0'; i++)
//	{
//		USART_SendData(USART2, (uint16_t)TxBuf1[i]);
//
//		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
//		{}	// Wait until transmission Complete
//	}
//	Delay(100);
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
