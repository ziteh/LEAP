
/**
 ******************************************************************************
 * @file		GPIO_Functions.c
 * @author  	Huang Tzu-Fu
 * 				National Formosa University
 * 				Department of Electronic Engineering
 * 				Intelligent Robot System Laboratory
 * @version 	V1.0.1
 * @date    	08-October-2019
 * @brief   	GPIO functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO_Functions.h"
#include "GPIO_mapping.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialization GPIO.
  * @param  None
  * @retval None
  * @attention Please run "RCC_Initialization()" before this function.
  */
void GPIO_Initialization(void)
{
	/* Structure Declarations */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_StructInit(&GPIO_InitStructure);	// Fills each GPIO_InitStruct member with its default value

	/* Configure the GPIO pin */
	/* user */
	// PA5: LED-user
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// PC13: Button-user
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	/* USART */
	// PA2: USART2_TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// PA3: USART2_RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Motor0 */
	// PB5: Motor0_Enbale
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PB4: Motor0-Direction
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PB10: Motor0-Speed(PWM, TIM2_CH3)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PB3: Motor0-Ready
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Motor1 */
	// PA8: Motor1_Enbale
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// PA9: Motor1-Direction
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// PC7: Motor1-Speed(PWM, TIM3_CH2)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// PB6: Motor1-Ready
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//**
//  * @brief  Config a pin Mode and Speed.
//  * @param	PortPin: select a pin to set.
//  * 		This parameter should be: 0 ~ 79
//  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
//  * 		48~63:PD0~PD15; 64~79:PE0~PE15
//  * @retval None
//  */
//void PinMod(u8 PortPin, u8 INout, u8 Mode, u8 Speed)
//{
//	u8 PinConfig = 0;
//	u8 PxODR = 0;
//
//	if(INout == 1)
//	{
//		switch(Speed)
//		{
//			case 1:
//				PinConfig = 0x0001;
//				break;
//			case 0:
//				PinConfig = 0x0010;
//				break;
//			case 2:
//				PinConfig = 0x0011;
//				break;
//			default:
//				break;
//		}
//
//		switch(Mode)
//		{
//			case 0:
//				PinConfig |= 0x0000;
//				break;
//			case 1:
//				PinConfig |= 0x0100;
//				break;
//			case 2:
//				PinConfig |= 0x1000;
//				break;
//			case 3:
//				PinConfig |= 0x1100;
//				break;
//		}
//	}
//	else if(INout == 0)
//	{
//		PinConfig = 0x0000;
//		switch(Mode)
//		{
//			case 0:
//				PinConfig |= 0x0000;
//				break;
//			case 1:
//				PinConfig |= 0x0100;
//				break;
//			case 2:
//				PinConfig |= 0x1000;
//				PxODR = 0;
//				break;
//			case 3:
//				PinConfig |= 0x1000;
//				PxODR = 1;
//				break;
//		}
//	}
//}

/**
  * @brief  Set a pin to High(1).
  * @param	PortPin: select a pin to set.
  * 		This parameter should be: 0 ~ 79
  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
  * 		48~63:PD0~PD15; 64~79:PE0~PE15
  * @retval None
  */
void PinSet(u8 PortPin)
{
	if(PortPin <= 15)								// Port-A:  0~15
		GPIOA->BSRR |= (0x0001 << PortPin);
	else if(PortPin <= 31)							// Port-B: 16~31
		GPIOB->BSRR |= (0x0001 << (PortPin - 16));
	else if(PortPin <= 47)							// Port-C: 32~47
		GPIOC->BSRR |= (0x0001 << (PortPin - 32));
	else if(PortPin <= 63)							// Port-D: 48~63
		GPIOD->BSRR |= (0x0001 << (PortPin - 48));
	else if(PortPin <= 79)							// Port-E: 64~79
		GPIOE->BSRR |= (0x0001 << (PortPin - 64));
	else											// Out of range(0~79)
		/* Null */;
}

/**
  * @brief  Clear a pin to Low(0).
  * @param	PortPin: select a pin to clear.
  * 		This parameter should be: 0 ~ 79
  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
  * 		48~63:PD0~PD15; 64~79:PE0~PE15
  * @retval None
  */
void PinClr(u8 PortPin)
{
	if(PortPin <= 15)								// Port-A:  0~15
		GPIOA->BRR |= (0x0001 << PortPin);
	else if(PortPin <= 31)							// Port-B: 16~31
		GPIOB->BRR |= (0x0001 << (PortPin - 16));
	else if(PortPin <= 47)							// Port-C: 32~47
		GPIOC->BRR |= (0x0001 << (PortPin - 32));
	else if(PortPin <= 63)							// Port-D: 48~63
		GPIOD->BRR |= (0x0001 << (PortPin - 48));
	else if(PortPin <= 79)							// Port-E: 64~79
		GPIOE->BRR |= (0x0001 << (PortPin - 64));
	else											// Out of range(0~79)
		/* Null */;
}

/**
  * @brief  Toggle a pin.
  * @param	PortPin: select a pin to toggle.
  * 		This parameter should be: 0 ~ 79
  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
  * 		48~63:PD0~PD15; 64~79:PE0~PE15
  * @retval None
  */
void PinToggle(u8 PortPin)
{
	if(PortPin <= 15)								// Port-A:  0~15
		GPIOA->ODR ^= (0x0001 << PortPin);
	else if(PortPin <= 31)							// Port-B: 16~31
		GPIOB->ODR ^= (0x0001 << (PortPin - 16));
	else if(PortPin <= 47)							// Port-C: 32~47
		GPIOC->ODR ^= (0x0001 << (PortPin - 32));
	else if(PortPin <= 63)							// Port-D: 48~63
		GPIOD->ODR ^= (0x0001 << (PortPin - 48));
	else if(PortPin <= 79)							// Port-E: 64~79
		GPIOE->ODR ^= (0x0001 << (PortPin - 64));
	else											// Out of range(0~79)
		/* Null */;
}

/**
  * @brief  Write a pin to High(1) or Low(0).
  * @param	PortPin: select a pin to write.
  * 		This parameter should be: 0 ~ 79
  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
  * 		48~63:PD0~PD15; 64~79:PE0~PE15
  * @param	Value: select High or Low to write.
  * 		This parameter should be: 1 or 0
  * @retval None
  */
void PinWrite(u8 PortPin, u8 Value)
{
	if(Value == 1)
		PinSet(PortPin);
	else if(Value == 0)
		PinClr(PortPin);
	else
		/* Null */;
}

/**
  * @brief  Read a input-pin value.
  * @param	PortPin: select a pin to read.
  * 		This parameter should be: 0 ~ 79
  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
  * 		48~63:PD0~PD15; 64~79:PE0~PE15
  * @retval The input-pin value
  */
u8 PinRead(u8 PortPin)
{
	u8 PinInputValue;

	if(PortPin <= 15)									// Port-A:  0~15
		PinInputValue = (GPIOA->IDR & (0x0001 << PortPin));
	else if(PortPin <= 31)								// Port-B: 16~31
		PinInputValue = (GPIOB->IDR & (0x0001 << (PortPin - 16)));
	else if(PortPin <= 47)								// Port-C: 32~47
		PinInputValue = (GPIOC->IDR & (0x0001 << (PortPin - 32)));
	else if(PortPin <= 63)								// Port-D: 48~63
		PinInputValue = (GPIOD->IDR & (0x0001 << (PortPin - 48)));
	else if(PortPin <= 79)								// Port-E: 64~79
		PinInputValue = (GPIOE->IDR & (0x0001 << (PortPin - 64)));
	else												// Out of range(0~79)
		/* Null */;

	return PinInputValue;
}

/**
  * @brief  Determine the port.
  * @param	PortPin: select a pin to determine.
  * 		This parameter should be: 0 ~ 79
  * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
  * 		48~63:PD0~PD15; 64~79:PE0~PE15
  * @retval The port
  */
char PortDetermine(u8 PortPin)
{
	char Port;

	if(PortPin <= 15)		// Port-A:  0~15
		Port = 'A';
	else if(PortPin <= 31)	// Port-B: 16~31
		Port = 'B';
	else if(PortPin <= 47)	// Port-C: 32~47
		Port = 'C';
	else if(PortPin <= 63)	// Port-D: 48~63
		Port = 'D';
	else if(PortPin <= 79)	// Port-E: 64~79
		Port = 'E';
	else					// Out of range(0~79)
		/* Null */;

	return Port;
}

/********************************END OF FILE***********************************/
