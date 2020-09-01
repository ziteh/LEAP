/**
 ******************************************************************************
 * @file    main.cpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    25-October-2019
 * @brief   Main program body of L.A.E.P.K.
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Uncomment it to run unit test program, comment it to run main program. */
// #define ENABLE_UNIT_TEST

#include "main.hpp"

static __IO uint32_t TimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

int main(void)
{
#ifndef ENABLE_UNIT_TEST
  /* Region of Main Code */

  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  uint16_t ADC_JointAnglePOTValue;
  uint16_t ADC_FrontFSRValue;
  uint16_t ADC_BackFSRValue;

  float Joint_Angle;

  /* Initialization Functions */
  GPIO_Initialization();
  //  Timer_Initialization();
  EXIT_Initialization();
  NVIC_Initialization();
  USART_Initialization();
  ADC_Initialization();
  PWM_Initialization();

  PWM_SetFrequency(TIM3, PWM_DefaultFrequncy);
  PWM_SetDutyCycle(TIM3, CH2, 0);
  GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // Disable motor

  GPIO_SetLow(User_LED);

  USART_Send(USART2, "[READY]\r\n");

  while (1)
  {
    /* Get value */
    ADC_FrontFSRValue = ADC_GetValue(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
    ADC_BackFSRValue = ADC_GetValue(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
    ADC_JointAnglePOTValue = ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
    Joint_Angle = Convert_ADCValueToAngle(ADC_JointAnglePOTValue);

    USART_Send(USART2, "ANG:");
    USART_Send(USART2, convertIntToString(round(Joint_Angle)));
    USART_Send(USART2, "\r\n");

    USART_Send(USART2, "POT:");
    USART_Send(USART2, convertIntToString(ADC_JointAnglePOTValue));
    USART_Send(USART2, "\r\n");

    USART_Send(USART2, "EXT:");
    USART_Send(USART2, convertIntToString(ADC_FrontFSRValue));
    USART_Send(USART2, "\r\n");

    USART_Send(USART2, "FLE:");
    USART_Send(USART2, convertIntToString(ADC_BackFSRValue));
    USART_Send(USART2, "\r\n----------\r\n");

    Delay_ms(200);
  }
#else  /* ENABLE_UNIT_TEST */
  /* Region of Unit Test Code */
  UnitTest::Joint_Extenstion();
#endif /* ENABLE_UNIT_TEST */
}

/**
 * @brief  Initialization GPIO.
 */
void GPIO_Initialization(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                             RCC_APB2Periph_GPIOB |
                             RCC_APB2Periph_GPIOC |
                             RCC_APB2Periph_GPIOD |
                             RCC_APB2Periph_GPIOE,
                         ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  // STM32 Nucleo-64 board
  GPIO_SetMode(User_LED, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);
  GPIO_SetMode(User_Button, GPIO_Mode_IN_FLOATING);

  // USART
  GPIO_SetMode(PA2, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); // USART2_TX
  GPIO_SetMode(PA3, GPIO_Mode_IN_FLOATING);             // USART2_RX

  /* Right leg */
  // Motor
  GPIO_SetMode(PA7, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); // PWM
  GPIO_SetMode(D10, GPIO_Mode_Out_PP, GPIO_Speed_2MHz); // Direction
  GPIO_SetMode(D9, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);  // Enable/Disable

  // ADC
  GPIO_SetMode(PA1, GPIO_Mode_AIN);
  GPIO_SetMode(PA4, GPIO_Mode_AIN);
  GPIO_SetMode(PB0, GPIO_Mode_AIN);

  // EXT
  GPIO_SetMode(PA0, GPIO_Mode_IPD); // Limit switch

  /* Left leg */
  // Motor
  // ADC
  // EXT
}

/**
 * @brief  Initialize NVIC.
 */
void NVIC_Initialization(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configures the priority grouping */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Configure the NVIC */
  // USART2
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // EXTI: Limit Switch
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Timer
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief       Initialize USART.
 */
void USART_Initialization(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  USART_InitTypeDef USART_InitStructure;
  USART_StructInit(&USART_InitStructure);

  //    USART_DeInit(USART2);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);

  /* Enable "Receive data register not empty" interrupt */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  /* Enable USART */
  USART_Cmd(USART2, ENABLE);

  /* Clear "Transmission Complete" flag, 否則第1位數據會丟失 */
  USART_ClearFlag(USART2, USART_FLAG_TC);
}

/**
 * @brief  Initialize ADC.
 */
void ADC_Initialization(void)
{
  /* ADC's clock con't over than 14MHz */
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_DeInit(ADC1);

  ADC_InitTypeDef ADC_InitStruct;

  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStruct.ADC_NbrOfChannel = 1;
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;
  ADC_Init(ADC1, &ADC_InitStruct);

  ADC_Cmd(ADC1, ENABLE);

  /* ADC Calibration */
  // Reset calibration
  ADC_ResetCalibration(ADC1);

  // Wait until reset calibration complete
  while (ADC_GetResetCalibrationStatus(ADC1) == 1)
  {
  }

  // Start calibration
  ADC_StartCalibration(ADC1);

  // Wait until calibration complete
  while (ADC_GetCalibrationStatus(ADC1) == 1)
  {
  }
}

/**
 * @brief  Initialize PWM.
 */
void PWM_Initialization(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 14399; // Set the Auto-Reload value
  TIM_TimeBaseStructure.TIM_Prescaler = 10; // Set the Prescaler value
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // Select the Counter Mode
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 530; // TIM_Pulse=CCRx
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  /* Enable */
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
}

void EXIT_Initialization(void)
{
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  EXTI_InitTypeDef EXTI_InitStructure;

  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void Timer_Initialization(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Period = 72 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = 1000;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

void CommunicationDecoder(uint8_t Command)
{
  //  Joint_SetAbsoluteAngle(Command - 5);
}

void Delay_NonTimer(__IO uint32_t nTime)
{
  for (; nTime != 0; nTime--)
  {
  }
}

extern "C"
{

  void Delay_ms(__IO uint32_t nTime)
  {
    TimingDelay = (nTime * 0.125);

    while (TimingDelay != 0)
    {
    }
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

} /* extern "C" { */

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************END OF FILE**********************************/
