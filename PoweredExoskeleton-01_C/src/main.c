
/**
 ******************************************************************************
 * @file   		main.c
 *	@author  	Huang, Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.0
 * @date    	25-October-2019
 * @brief   	Main program body of Powered Exoskeleton
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f10x.h"
#include "GPIO_Functions.h"
#include "RCC_Functions.h"
#include "NVIC_Functions.h"
#include "USART_Functions.h"
#include "PWM_Functions.h"

/** @addtogroup Powered Exoskeleton
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;

/* Private define ------------------------------------------------------------*/
#define Enable 	(1)
#define Disable (0)
#define CW		(0)
#define CCW		(1)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;

/* Motor */
// Row: Motor number; Column: The pin of Enable,Direction,Ready
uint8_t MotorPin[2][3] =
{	// | Enable | Direction | Ready |
	{PinMotor0_Enbale, PinMotor0_Direction, PinMotor0_Ready},	// Motor0
	{PinMotor1_Enbale, PinMotor1_Direction, PinMotor1_Ready}	// Motor1
};

// The PWM timer of Motor0, Motor1
uint32_t MotorTimer[2] = {TIM3, TIM3};

/* Private function prototypes -----------------------------------------------*/
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
	// Functions & Setups
	RCC_Initialization();
	GPIO_Initialization();
	USART_Initialization();
	PWM_Initialization();
	NVIC_Initialization();

	// Reset all motor
	MotorCtrl(0, Disable, CCW, 0);	// Motor0: Disable, CCW, Speed:0
	MotorCtrl(1, Disable, CW, 0);	// Motor1: Disable, CW, Speed:0

	Pin_Clr(LD2);					// Turn off LD2(User-LED)

	/* Infinite loop */
	while(1)
	{
		SendStatus();
		Delay(250);
	}
}

/**
* @brief  	Send status.
* @retval 	None
*/
void SendStatus(void)
{
//	uint8_t TxData;

	// Binary:010nnrXX
//	TxData = ((0x40 | (Motor << 3)) | (Pin_Read(MotorPin[Motor][2]) << 2));
//	USART_Send(USART2, TxData);

	// Motor0
	USART_Send(USART2, "[Status]Motor0 ");
	if(Pin_ReadInput(PB4) == 1)				// Motor_Ready pin=High
		USART_Send(USART2, "Ready ; ");
	else									// Motor_Ready pin=Low
		USART_Send(USART2, "FAULT! ; ");

	if(Pin_ReadOutput(PinMotor0_Enbale) == 1)
		USART_Send(USART2, " Enable ; ");
	else
		USART_Send(USART2, "Disable ; ");

	if(Pin_ReadOutput(PinMotor0_Direction) == 1)
		USART_Send(USART2, "CCW\n");
	else
		USART_Send(USART2, " CW\n");

	// Motor1
	USART_Send(USART2, "[Status]Motor1 ");
	if(Pin_ReadInput(PA7) == 1)				// Motor_Ready pin=High
		USART_Send(USART2, "Ready ; ");
	else									// Motor_Ready pin=Low
		USART_Send(USART2, "FAULT! ; ");

	if(Pin_ReadOutput(PinMotor1_Enbale) == 1)
		USART_Send(USART2, " Enable ; ");
	else
		USART_Send(USART2, "Disable ; ");

	if(Pin_ReadOutput(PinMotor1_Direction) == 1)
		USART_Send(USART2, "CCW\n");
	else
		USART_Send(USART2, " CW\n");

	USART_Send(USART2, "----------\n");



}

/**
* @brief  	Control the motor.
* @param	Motor: the number of motor. This parameter should be: 0~1.
* @param	Status: the status of motor.
* 			This parameter should be 0~3.
* 			0: Disable; 1: Enable; 2: Toggle; 3: Keep.
* @param	Direction: the direction of motor.
* 			This parameter should be 0~3.
* 			0: CW; 1: CCW; 2: Toggle; 3: Keep.
* @param	Speed: the speed of motor in %.
* 			This parameter should be: 0~100, 127.
* 			0~100: 0%~100%; 127: Keep.
* @retval 	None
*/
void MotorCtrl(uint8_t Motor, uint8_t Status, uint8_t Direction, uint8_t Speed)
{
//	u16 DutyCycleValue;

	// Status
	if(Status <= 1)								// Disable(0) & Enable(1)
		Pin_Write((MotorPin[Motor][0]), Status);
	else if(Status == 2)						// Toggle(2)
		Pin_Toggle((MotorPin[Motor][0]));
	else /* Null */;							// Keep(3)

	// Direction
	if(Direction <= 1)							// CW(0) & CCW(1)
		Pin_Write((MotorPin[Motor][1]), Direction);
	else if(Direction == 2)						// Toggle(2)
		Pin_Toggle((MotorPin[Motor][1]));
	else /* Null */;							// Keep(3)

	// Speed
	if(Speed == 0)	// Turn OFF the motor
	{
		Pin_Write((MotorPin[Motor][0]), Disable);
		TIM_SetCompare1((MotorTimer[Motor]), 0);
	}
	else if(Speed == 100)
	{
		TIM_SetCompare1((MotorTimer[Motor]), 999);	// Set PWM duty cycle=100%
	}
	else if((Speed > 0) && (Speed < 100))
	{
		TIM_SetCompare1((MotorTimer[Motor]), ((Speed-1)*10)); // Set duty cycle
	}
	else if(Speed == 127)	// Keep speed of motor
	{
		/* Null */;
	}
	else /* Null */;
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
