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
//  #define ENABLE_UNIT_TEST

#include "main.hpp"

static __IO uint32_t TimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

// Joint NowJoint;
Joint *NowJoint;
Joint RightJoint;
JointWithoutHallSensor LeftJoint;

int main(void)
{
#ifndef ENABLE_UNIT_TEST
  /* Region of Main Code */

  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  /* Configures the priority grouping */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Initialization Functions */
  NowJoint = &RightJoint;
  Joint_Initialization(NowJoint);
  NowJoint = &LeftJoint;
  Joint_Initialization(NowJoint);
  LimitSwitch_Initialization();
  USART_Initialization();
  Timer_Initialization();
  Board_Initialization();

  USART_Send(USART2, "[READY]\r\n");

  while (1)
  {
  }
#else  /* ENABLE_UNIT_TEST */
  /* Region of Unit Test Code */
  UnitTest::Timer_1sec();
#endif /* ENABLE_UNIT_TEST */
}

void MotionHandler(void)
{
  NowJoint = &RightJoint;
  if (NowJoint->MotionState == Joint::NoInMotion)
  {
    if (NowJoint->ExtensionStartTriggered())
    {
      NowJoint->MotionExtensionStart();
    }
    else if (NowJoint->FlexionStartTriggered())
    {
      NowJoint->MotionFlexionStart();
    }
  }
  else
  {
    if ((NowJoint->MotionState == Joint::Extensioning) && NowJoint->ExtensionStopTriggered())
    {
      NowJoint->MotionExtensionStop();
    }
    else if ((NowJoint->MotionState == Joint::Flexioning) && NowJoint->FlexionStopTriggered())
    {
      NowJoint->MotionFlexionStop();
    }
  }

  NowJoint = &LeftJoint;
  if (NowJoint->MotionState == Joint::NoInMotion)
  {
    if (NowJoint->ExtensionStartTriggered())
    {
      NowJoint->MotionExtensionStart();
    }
    else if (NowJoint->FlexionStartTriggered())
    {
      NowJoint->MotionFlexionStart();
    }
  }
  else
  {
    if ((NowJoint->MotionState == Joint::Extensioning) && NowJoint->ExtensionStopTriggered())
    {
      NowJoint->MotionExtensionStop();
    }
    else if ((NowJoint->MotionState == Joint::Flexioning) && NowJoint->FlexionStopTriggered())
    {
      NowJoint->MotionFlexionStop();
    }
  }
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

void Joint_Initialization(Joint *joint)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                             RCC_APB2Periph_GPIOB |
                             RCC_APB2Periph_GPIOC |
                             RCC_APB2Periph_ADC1,
                         ENABLE);

  // Motor
  joint->PortPin_SpeedPWM = PA7; // D11
  joint->Timer_SpeedPWM = TIM3;
  joint->Channel_SpeedPWM = CH2;

  joint->PortPin_FunctionState = D10;
  joint->PortPin_Direction = D9;
  joint->PortPin_ReadyState = D8;

  // ADC
  joint->PortPin_AnglePOT = PA1; // A1
  joint->ADCx_AnglePOT = ADC1;
  joint->ADC_Channel_AnglePOT = ADC_Channel_1;

  joint->PortPin_FrontFSR = PA4; // A2
  joint->ADCx_FrontFSR = ADC1;
  joint->ADC_Channel_FrontFSR = ADC_Channel_4;

  joint->PortPin_BackFSR = PB0; // A3
  joint->ADCx_BackFSR = ADC1;
  joint->ADC_Channel_BackFSR = ADC_Channel_8;

  // Value & Threshold
  joint->FullExtensionPOTValue = 1400;
  joint->FullFlexionPOTValue = 2450;

  joint->ExtensionFSRStartThreshold = 215;
  joint->FlexionFSRStartThreshold = 180;

  joint->ExtensionFSRStopThreshold = 500;
  joint->FlexionFSRStopThreshold = 500;

  joint->Init();
  joint->MotionStop();
}

void LimitSwitch_Initialization(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO limitSwitch;
  limitSwitch.PortPin = PA0;
  limitSwitch.Mode = GPIO_Mode_IPD;
  limitSwitch.Init();

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief Initialize USART.
 */
void USART_Initialization(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO USART2_TX;
  USART2_TX.PortPin = PA2;
  USART2_TX.Mode = GPIO_Mode_AF_PP;
  USART2_TX.Speed = GPIO_Speed_50MHz;
  USART2_TX.Init();

  GPIO USART2_RX;
  USART2_RX.PortPin = PA3;
  USART2_RX.Mode = GPIO_Mode_IN_FLOATING;
  USART2_RX.Init();

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_InitTypeDef USART_InitStructure;
  USART_StructInit(&USART_InitStructure);
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

void Timer_Initialization(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Period = 2000;
  TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Board_Initialization(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                             RCC_APB2Periph_GPIOC,
                         ENABLE);

  GPIO Button;
  Button.PortPin = User_Button;
  Button.Mode = GPIO_Mode_IN_FLOATING;
  Button.Init();

  GPIO LED;
  LED.PortPin = User_LED;
  LED.Mode = GPIO_Mode_Out_PP;
  LED.Speed = GPIO_Speed_2MHz;
  LED.Init();
  LED.setValue(LOW);
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
