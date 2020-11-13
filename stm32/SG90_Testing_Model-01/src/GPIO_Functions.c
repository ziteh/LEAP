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
//#include "stm32f10x.h"
#include "GPIO_Functions.h"
//#include "GPIO_mapping.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* -----Pin Mode and Speed----- */
//#define OUT		(0)
//#define IN		(1)
//
//#define GPPP	(0)
//#define GPOD	(1)
//#define AFPP	(2)
//#define AFOD	(3)
//
//#define FL		(0)
//#define AN		(1)
//#define PD		(2)
//#define PU		(3)
//
//#define S2M		(2)
//#define S10M	(10)
//#define S50M	(50)
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
void GPIO_Initialization(void) {
    /* Structure Declarations */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Fills each GPIO_InitStruct member with its default value */
    GPIO_StructInit(&GPIO_InitStructure);

    /* Configure the GPIO pin */
    /* STM32 Nucleo-64 board */
    Pin_Mod(LD2, OUT, GPPP, S2M);	// PA5: LED-user
    Pin_Mod(B1, IN, FL, S2M);	// PC13: Button-user

    /* USART */
    Pin_Mod(PA2, OUT, AFPP, S50M);	// USART2_TX
    Pin_Mod(PA3, IN, FL, S50M);	// USART2_RX//

//	/* Motor */
    //紅色：5V 電源正極
    //棕色：共地線
    //橙色：控制訊號線

    Pin_Mod(PA7, OUT, AFPP, S50M);	// SG90-PWM
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

//	Pin_Mod(PA1, IN, AN, S50M); // ADC

    // EXT
    Pin_Mod(PA0, IN, PD, S50M); // EXT

    EXTI_InitTypeDef EXTI_InitStructure;

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief  Config a pin mode and speed.
 * @param	PortPin: select a pin to set.
 * 		    This parameter should be: 0 ~ 79
 * 		     0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 * 		    48~63:PD0~PD15; 64~79:PE0~PE15
 * @param	INout: Input or Output.
 * 		This parameter should be: 0(Output) or 1(Input).
 * @param	Mode: Pin mode.
 *			This parameter should be: 0~3.
 *			0: GPPP or FL.
 *			1: GPOD or AN.
 *			2: AFPP or PD.
 *			3: AFOD or PU.
 * @param	Speed: Pin speed.
 * 		    This parameter should be: 0~2.
 * 		     2:  2MHz.
 * 		    10: 10MHz.
 * 		    50: 50MHz.
 * @retval None
 */
void Pin_Mod(u8 PortPin, u8 INout, u8 Mode, u8 Speed) {
    /* Structure Declarations */
    GPIO_InitTypeDef GPIO_InitStructure;

    // GPIO_Speed
    switch (Speed) {
    case S2M:	// S2M:2
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        break;
    case S10M:	// S10M:10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        break;
    case S50M:	// S50M:50
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        break;
    default:
        break;
    }

    // GPIO_Mode
    if (INout == OUT) { // OUT:0
        switch (Mode) {
        case GPPP:	// GPPP:0
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            break;
        case GPOD:	// GPOD:1
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
            break;
        case AFPP:	// AFPP:2
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            break;
        case AFOD:	// AFOD:3
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
            break;
        default:
            break;
        }
    } else if (INout == IN) {   // IN:1
        switch (Mode) {
        case FL:	// FL:0
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            break;
        case AN:	// AN:1
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
            break;
        case PD:	// PD:2
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
            break;
        case PU:	// PU:3
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            break;
        default:
            break;
        }
    }

    // GPIO_Pin & GPIO_Init() function.
    if (PortPin <= 15) {	    // Port-A:  0~15
        GPIO_InitStructure.GPIO_Pin = ((uint16_t) (0x0001 << PortPin));
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    } else if (PortPin <= 31) {	// Port-B: 16~31
        GPIO_InitStructure.GPIO_Pin = ((uint16_t) (0x0001 << (PortPin - 16)));
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    } else if (PortPin <= 47) {	// Port-C: 32~47
        GPIO_InitStructure.GPIO_Pin = ((uint16_t) (0x0001 << (PortPin - 32)));
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    } else if (PortPin <= 63) {	// Port-D: 48~63
        GPIO_InitStructure.GPIO_Pin = ((uint16_t) (0x0001 << (PortPin - 48)));
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    } else if (PortPin <= 79) {	// Port-E: 64~79
        GPIO_InitStructure.GPIO_Pin = ((uint16_t) (0x0001 << (PortPin - 64)));
        GPIO_Init(GPIOE, &GPIO_InitStructure);
    } else {
        /* Null */;             // Out of range(0~79)
    }

}

//#undef OUT
//#undef IN
//
//#undef GPPP
//#undef GPOD
//#undef AFPP
//#undef AFOD
//
//#undef FL
//#undef AN
//#undef PD
//#undef PU
//
//#undef S2M
//#undef S10M
//#undef S50M

/**
 * @brief  Set a pin to High(1).
 * @param	PortPin: select a pin to set.
 * 		This parameter should be: 0 ~ 79
 * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 * 		48~63:PD0~PD15; 64~79:PE0~PE15
 * @retval None
 */
void Pin_Set(u8 PortPin) {
    if (PortPin <= 15)								// Port-A:  0~15
        GPIOA->BSRR |= (0x0001 << PortPin);
    else if (PortPin <= 31)							// Port-B: 16~31
        GPIOB->BSRR |= (0x0001 << (PortPin - 16));
    else if (PortPin <= 47)							// Port-C: 32~47
        GPIOC->BSRR |= (0x0001 << (PortPin - 32));
    else if (PortPin <= 63)							// Port-D: 48~63
        GPIOD->BSRR |= (0x0001 << (PortPin - 48));
    else if (PortPin <= 79)							// Port-E: 64~79
        GPIOE->BSRR |= (0x0001 << (PortPin - 64));
    else
        // Out of range(0~79)
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
void Pin_Clr(u8 PortPin) {
    if (PortPin <= 15)								// Port-A:  0~15
        GPIOA->BRR |= (0x0001 << PortPin);
    else if (PortPin <= 31)							// Port-B: 16~31
        GPIOB->BRR |= (0x0001 << (PortPin - 16));
    else if (PortPin <= 47)							// Port-C: 32~47
        GPIOC->BRR |= (0x0001 << (PortPin - 32));
    else if (PortPin <= 63)							// Port-D: 48~63
        GPIOD->BRR |= (0x0001 << (PortPin - 48));
    else if (PortPin <= 79)							// Port-E: 64~79
        GPIOE->BRR |= (0x0001 << (PortPin - 64));
    else
        // Out of range(0~79)
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
void Pin_Toggle(u8 PortPin) {
    if (PortPin <= 15)								// Port-A:  0~15
        GPIOA->ODR ^= (0x0001 << PortPin);
    else if (PortPin <= 31)							// Port-B: 16~31
        GPIOB->ODR ^= (0x0001 << (PortPin - 16));
    else if (PortPin <= 47)							// Port-C: 32~47
        GPIOC->ODR ^= (0x0001 << (PortPin - 32));
    else if (PortPin <= 63)							// Port-D: 48~63
        GPIOD->ODR ^= (0x0001 << (PortPin - 48));
    else if (PortPin <= 79)							// Port-E: 64~79
        GPIOE->ODR ^= (0x0001 << (PortPin - 64));
    else
        // Out of range(0~79)
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
void Pin_Write(u8 PortPin, u8 Value) {
    if (Value == 1)
        Pin_Set(PortPin);
    else if (Value == 0)
        Pin_Clr(PortPin);
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
u8 Pin_ReadInput(u8 PortPin) {
    u8 PinInputValue = 0x00;

    // !! ERROR: u8 Pin_Read(u8 PortPin)

//	if(PortPin <= 15)									// Port-A:  0~15
//		PinInputValue = (GPIOA->IDR & (0x0001 << PortPin));
//	else if(PortPin <= 31)								// Port-B: 16~31
//		PinInputValue = (GPIOB->IDR & (0x0001 << (PortPin - 16)));
//	else if(PortPin <= 47)								// Port-C: 32~47
//		PinInputValue = (GPIOC->IDR & (0x0001 << (PortPin - 32)));
//	else if(PortPin <= 63)								// Port-D: 48~63
//		PinInputValue = (GPIOD->IDR & (0x0001 << (PortPin - 48)));
//	else if(PortPin <= 79)								// Port-E: 64~79
//		PinInputValue = (GPIOE->IDR & (0x0001 << (PortPin - 64)));
//	else												// Out of range(0~79)
//		/* Null */;

    if (PortPin <= 15)									// Port-A:  0~15
        PinInputValue = GPIO_ReadInputDataBit(GPIOA, (0x0001 << PortPin));
    else if (PortPin <= 31)								// Port-B: 16~31
        PinInputValue = GPIO_ReadInputDataBit(GPIOB, (0x0001 << (PortPin - 16)));
    else if (PortPin <= 47)								// Port-C: 32~47
        PinInputValue = GPIO_ReadInputDataBit(GPIOB, (0x0001 << (PortPin - 32)));
    else if (PortPin <= 63)								// Port-D: 48~63
        PinInputValue = GPIO_ReadInputDataBit(GPIOB, (0x0001 << (PortPin - 48)));
    else if (PortPin <= 79)								// Port-E: 64~79
        PinInputValue = GPIO_ReadInputDataBit(GPIOB, (0x0001 << (PortPin - 64)));
    else
        // Out of range(0~79)
        /* Null */;

    return PinInputValue;
}

/**
 * @brief  Read a output-pin value.
 * @param	PortPin: select a pin to read.
 * 		This parameter should be: 0 ~ 79
 * 		 0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 * 		48~63:PD0~PD15; 64~79:PE0~PE15
 * @retval The output-pin value
 */
u8 Pin_ReadOutput(u8 PortPin) {
    u8 PinInputValue = 0x00;

    if (PortPin <= 15)									// Port-A:  0~15
        PinInputValue = GPIO_ReadOutputDataBit(GPIOA, (0x0001 << PortPin));
    else if (PortPin <= 31)								// Port-B: 16~31
        PinInputValue = GPIO_ReadOutputDataBit(GPIOB, (0x0001 << (PortPin - 16)));
    else if (PortPin <= 47)								// Port-C: 32~47
        PinInputValue = GPIO_ReadOutputDataBit(GPIOB, (0x0001 << (PortPin - 32)));
    else if (PortPin <= 63)								// Port-D: 48~63
        PinInputValue = GPIO_ReadOutputDataBit(GPIOB, (0x0001 << (PortPin - 48)));
    else if (PortPin <= 79)								// Port-E: 64~79
        PinInputValue = GPIO_ReadOutputDataBit(GPIOB, (0x0001 << (PortPin - 64)));
    else
        // Out of range(0~79)
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
char Port_Determine(u8 PortPin) {
    char Port;

    if (PortPin <= 15)		// Port-A:  0~15
        Port = 'A';
    else if (PortPin <= 31)	// Port-B: 16~31
        Port = 'B';
    else if (PortPin <= 47)	// Port-C: 32~47
        Port = 'C';
    else if (PortPin <= 63)	// Port-D: 48~63
        Port = 'D';
    else if (PortPin <= 79)	// Port-E: 64~79
        Port = 'E';
    else
        // Out of range(0~79)
        /* Null */;

    return Port;
}

/********************************END OF FILE***********************************/
