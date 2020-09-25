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

#include "main.hpp"

/* Uncomment/Comment the line below to enable/disable speciflc features */
#define ENABLE_RIGHT_LEG
#define ENABLE_LEFT_LEG
// #define ENABLE_UNIT_TEST // Uncomment it to run unit test program, comment it to run main program.
#define ENABLE_AUTO_SEND_INFO

static __IO uint32_t TimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

Joint *NowJoint = NULL;
Joint RightJoint;
JointWithoutHallSensor LeftJoint;

int main(void)
{
#ifndef ENABLE_UNIT_TEST
  /* Region of Main Code */

  /* Configures the NVIC priority grouping */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Initialization */
  RCC_Initialization();
#ifdef ENABLE_RIGHT_LEG
  Joint_Initialization(&RightJoint, Right);
#endif
#ifdef ENABLE_LEFT_LEG
  Joint_Initialization(&LeftJoint, Left);
#endif
  USART_Initialization();
  Board_Initialization();
  LimitSwitch_Initialization();
  Timer_Initialization();

  GPIO limitSwitch(LimitSwitch_PortPin);
  if (limitSwitch.getInputValue() == HIGH)
  {
    TIM_Cmd(TIM2, ENABLE); // Enable timer2(main program).
    USART_Send(USART2, "[L.A.E.P.K. READY]\r\n");
  }
  else
  {
    TIM_Cmd(TIM2, DISABLE); // Disable timer2(main program).
    MotionEmergencyStop();
    USART_Send(USART2, "[Check Limit-Switch]\r\n");
  }

  /* SysTick end of count event each 1ms */
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  USART_Send(USART2, "SysFre: ");
  USART_Send(USART2, Convert::ToString(RCC_Clocks.SYSCLK_Frequency));
  USART_Send(USART2, "\r\n");

  while (1)
  {
#ifdef ENABLE_AUTO_SEND_INFO
    // FIXME Can't send data.
    // StateTransporter();
    // Delay_ms(10);
#endif
  }
#else  /* ENABLE_UNIT_TEST */
  /* Region of Unit Test Code */
  UnitTest::Timer_1sec();
#endif /* ENABLE_UNIT_TEST */
}

void MotionHandler(void)
{
#ifdef ENABLE_RIGHT_LEG
  NowJoint = &RightJoint;
  NowJoint->MotionHandler();
#endif

#ifdef ENABLE_LEFT_LEG
  NowJoint = &LeftJoint;
  NowJoint->MotionHandler();
#endif
}

void MotionEmergencyStop(void)
{
#ifdef ENABLE_RIGHT_LEG
  NowJoint = &RightJoint;
  NowJoint->MotionStop();
#endif

#ifdef ENABLE_LEFT_LEG
  NowJoint = &LeftJoint;
  NowJoint->MotionStop();
#endif

  USART_Send(USART2, "[EMER STOP]\n");
}

void UpdateInfo(void)
{
#ifdef ENABLE_RIGHT_LEG
  USART_Send(USART2, "[Right INFO]\n");
  NowJoint = &RightJoint;
  NowJoint->SendInfo();
#endif

#ifdef ENABLE_LEFT_LEG
  USART_Send(USART2, "[Left INFO]\n");
  NowJoint = &LeftJoint;
  NowJoint->SendInfo();
#endif
}

// FIXME Manual RCC init.
void RCC_Initialization(void)
{
  // RCC_DeInit();

  // RCC_HSICmd(ENABLE);
  // while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
  // {
  // }

  // RCC_HCLKConfig(RCC_SYSCLK_Div1);
  // RCC_PCLK1Config(RCC_HCLK_Div2);
  // RCC_PCLK2Config(RCC_HCLK_Div1);

  // FLASH_SetLatency(FLASH_Latency_2);
  // FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  // RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_16);
  // RCC_PLLCmd(ENABLE);
  // while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  // {
  // }

  // RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  // while (RCC_GetSYSCLKSource() != 0x08)
  // {
  // }

  RCC_GetClocksFreq(&RCC_Clocks);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 |
      RCC_APB1Periph_USART3 |
                             RCC_APB1Periph_TIM2 |
                             RCC_APB1Periph_TIM3 |
                             RCC_APB1Periph_TIM4,
                         ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                             RCC_APB2Periph_GPIOB |
                             RCC_APB2Periph_GPIOC |
                             RCC_APB2Periph_AFIO |
                             RCC_APB2Periph_ADC1,
                         ENABLE);
}

void LimitSwitch_Initialization(void)
{
  GPIO limitSwitch;
  limitSwitch.PortPin = LimitSwitch_PortPin;
  limitSwitch.Mode = GPIO_Mode_IPD;
  limitSwitch.Init();

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority_EXTI0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority_EXTI0;
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

void USART_Initialization(void)
{
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
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority_USART2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority_USART2;
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

  /* Clear "Transmission Complete" flag, else the first bit of data will lose. */
  USART_ClearFlag(USART2, USART_FLAG_TC);

  GPIO USART3_TX;
  USART2_TX.PortPin = PC10;
  USART2_TX.Mode = GPIO_Mode_AF_PP;
  USART2_TX.Speed = GPIO_Speed_50MHz;
  USART2_TX.Init();

  GPIO USART3_RX;
  USART2_RX.PortPin = PC11;
  USART2_RX.Mode = GPIO_Mode_IN_FLOATING;
  USART2_RX.Init();

  GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority_USART3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority_USART3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);

  /* Enable "Receive data register not empty" interrupt */
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

  /* Enable USART */
  USART_Cmd(USART3, ENABLE);

  /* Clear "Transmission Complete" flag, else the first bit of data will lose. */
  USART_ClearFlag(USART3, USART_FLAG_TC);
}

void Timer_Initialization(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Period = 50; /* Unit: ms */
  TIM_TimeBaseStructure.TIM_Prescaler = (RCC_Clocks.SYSCLK_Frequency / 1000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, DISABLE);

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority_TIM2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority_TIM2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Board_Initialization(void)
{
  GPIO LED;
  LED.PortPin = User_LED;
  LED.Mode = GPIO_Mode_Out_PP;
  LED.Speed = GPIO_Speed_2MHz;
  LED.Init();
  LED.setValue(LOW);

  GPIO Button;
  Button.PortPin = User_Button;
  Button.Mode = GPIO_Mode_IPU;
  Button.Init();

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority_EXTI15_10;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority_EXTI15_10;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);

  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

// TODO Clean it.
void Joint_Initialization(Joint *joint, JointTypeDef jointType)
{
  // Motor
  joint->PortPin_SpeedPWM = ((jointType == Right) ? RightJoint_PortPin_SpeedPWM : LeftJoint_PortPin_SpeedPWM);
  joint->Timer_SpeedPWM = ((jointType == Right) ? RightJoint_Timer_SpeedPWM : LeftJoint_Timer_SpeedPWM);
  joint->Channel_SpeedPWM = ((jointType == Right) ? RightJoint_Channel_SpeedPWM : LeftJoint_Channel_SpeedPWM);

  joint->PortPin_FunctionState = ((jointType == Right) ? RightJoint_PortPin_FunctionState : LeftJoint_PortPin_FunctionState);
  joint->PortPin_Direction = ((jointType == Right) ? RightJoint_PortPin_Direction : LeftJoint_PortPin_Direction);
  joint->PortPin_ReadyState = ((jointType == Right) ? RightJoint_PortPin_ReadyState : LeftJoint_PortPin_ReadyState);

  // ADC
  joint->PortPin_AnglePOT = ((jointType == Right) ? RightJoint_PortPin_AnglePOT : LeftJoint_PortPin_AnglePOT);
  joint->ADCx_AnglePOT = ((jointType == Right) ? RightJoint_ADCx_AnglePOT : LeftJoint_ADCx_AnglePOT);
  joint->ADC_Channel_AnglePOT = ((jointType == Right) ? RightJoint_ADC_Channel_AnglePOT : LeftJoint_ADC_Channel_AnglePOT);

  joint->PortPin_FrontFSR = ((jointType == Right) ? RightJoint_PortPin_FrontFSR : LeftJoint_PortPin_FrontFSR);
  joint->ADCx_FrontFSR = ((jointType == Right) ? RightJoint_ADCx_FrontFSR : LeftJoint_ADCx_FrontFSR);
  joint->ADC_Channel_FrontFSR = ((jointType == Right) ? RightJoint_ADC_Channel_FrontFSR : LeftJoint_ADC_Channel_FrontFSR);

  joint->PortPin_BackFSR = ((jointType == Right) ? RightJoint_PortPin_BackFSR : LeftJoint_PortPin_BackFSR);
  joint->ADCx_BackFSR = ((jointType == Right) ? RightJoint_ADCx_BackFSR : LeftJoint_ADCx_BackFSR);
  joint->ADC_Channel_BackFSR = ((jointType == Right) ? RightJoint_ADC_Channel_BackFSR : LeftJoint_ADC_Channel_BackFSR);

  // Value
  joint->FullExtensionPOTValue = ((jointType == Right) ? RightJoint_DefaultValue_POTFullExtension : LeftJoint_DefaultValue_POTFullExtension);
  joint->FullFlexionPOTValue = ((jointType == Right) ? RightJoint_DefaultValue_POTFullFlexion : LeftJoint_DefaultValue_POTFullFlexion);

  joint->ExtensionFSRStartThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStartExtension : LeftJoint_DefaultValue_FSRStartExtension);
  joint->FlexionFSRStartThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStartFlexion : LeftJoint_DefaultValue_FSRStartFlexion);

  joint->ExtensionFSRStopThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStopExtension : LeftJoint_DefaultValue_FSRStopExtension);
  joint->FlexionFSRStopThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStopFlexion : LeftJoint_DefaultValue_FSRStopFlexion);

  joint->Init();
  joint->MotionStop();
}

// TODO Clean it.
void Joint_Initialization(JointWithoutHallSensor *joint, JointTypeDef jointType)
{
  if (jointType == Left)
  {
    joint->PortPin_VirtualHall1 = LeftJoint_PortPin_VirtualHall1;
    joint->PortPin_VirtualHall2 = LeftJoint_PortPin_VirtualHall2;
    joint->PortPin_VirtualHall3 = LeftJoint_PortPin_VirtualHall3;
  }

  // Motor
  joint->PortPin_SpeedPWM = ((jointType == Right) ? RightJoint_PortPin_SpeedPWM : LeftJoint_PortPin_SpeedPWM);
  joint->Timer_SpeedPWM = ((jointType == Right) ? RightJoint_Timer_SpeedPWM : LeftJoint_Timer_SpeedPWM);
  joint->Channel_SpeedPWM = ((jointType == Right) ? RightJoint_Channel_SpeedPWM : LeftJoint_Channel_SpeedPWM);

  joint->PortPin_FunctionState = ((jointType == Right) ? RightJoint_PortPin_FunctionState : LeftJoint_PortPin_FunctionState);
  joint->PortPin_Direction = ((jointType == Right) ? RightJoint_PortPin_Direction : LeftJoint_PortPin_Direction);
  joint->PortPin_ReadyState = ((jointType == Right) ? RightJoint_PortPin_ReadyState : LeftJoint_PortPin_ReadyState);

  // ADC
  joint->PortPin_AnglePOT = ((jointType == Right) ? RightJoint_PortPin_AnglePOT : LeftJoint_PortPin_AnglePOT);
  joint->ADCx_AnglePOT = ((jointType == Right) ? RightJoint_ADCx_AnglePOT : LeftJoint_ADCx_AnglePOT);
  joint->ADC_Channel_AnglePOT = ((jointType == Right) ? RightJoint_ADC_Channel_AnglePOT : LeftJoint_ADC_Channel_AnglePOT);

  joint->PortPin_FrontFSR = ((jointType == Right) ? RightJoint_PortPin_FrontFSR : LeftJoint_PortPin_FrontFSR);
  joint->ADCx_FrontFSR = ((jointType == Right) ? RightJoint_ADCx_FrontFSR : LeftJoint_ADCx_FrontFSR);
  joint->ADC_Channel_FrontFSR = ((jointType == Right) ? RightJoint_ADC_Channel_FrontFSR : LeftJoint_ADC_Channel_FrontFSR);

  joint->PortPin_BackFSR = ((jointType == Right) ? RightJoint_PortPin_BackFSR : LeftJoint_PortPin_BackFSR);
  joint->ADCx_BackFSR = ((jointType == Right) ? RightJoint_ADCx_BackFSR : LeftJoint_ADCx_BackFSR);
  joint->ADC_Channel_BackFSR = ((jointType == Right) ? RightJoint_ADC_Channel_BackFSR : LeftJoint_ADC_Channel_BackFSR);

  // Value
  joint->FullExtensionPOTValue = ((jointType == Right) ? RightJoint_DefaultValue_POTFullExtension : LeftJoint_DefaultValue_POTFullExtension);
  joint->FullFlexionPOTValue = ((jointType == Right) ? RightJoint_DefaultValue_POTFullFlexion : LeftJoint_DefaultValue_POTFullFlexion);

  joint->ExtensionFSRStartThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStartExtension : LeftJoint_DefaultValue_FSRStartExtension);
  joint->FlexionFSRStartThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStartFlexion : LeftJoint_DefaultValue_FSRStartFlexion);

  joint->ExtensionFSRStopThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStopExtension : LeftJoint_DefaultValue_FSRStopExtension);
  joint->FlexionFSRStopThreshold = ((jointType == Right) ? RightJoint_DefaultValue_FSRStopFlexion : LeftJoint_DefaultValue_FSRStopFlexion);

  joint->Init();
  joint->MotionStop();
}

void StateTransporter(void)
{
  Joint::StateTypeDef state;
  std::string stateText;

  stateText += "R,";
#ifdef ENABLE_RIGHT_LEG
  NowJoint = &RightJoint;
  NowJoint->getState(&state);

  stateText += Convert::ToString((int)state.Ready);
  stateText += ",";

  stateText += Convert::ToString((int)state.SoftwareLimit);
  stateText += ",";

  stateText += Convert::ToString((int)state.Motion);
  stateText += ",";

  stateText += Convert::ToString((int)state.AnglePOTValue);
  stateText += ",";

  stateText += Convert::ToString((int)state.FrontFSRValue);
  stateText += ",";

  stateText += Convert::ToString((int)state.BackFSRValue);
  stateText += ",";
#else
  stateText += "X,";
#endif

  stateText += "L,";
#ifdef ENABLE_LEFT_LEG
  NowJoint = &LeftJoint;
  NowJoint->getState(&state);

  stateText += Convert::ToString((int)state.Ready);
  stateText += ",";

  stateText += Convert::ToString((int)state.SoftwareLimit);
  stateText += ",";

  stateText += Convert::ToString((int)state.Motion);
  stateText += ",";

  stateText += Convert::ToString((int)state.AnglePOTValue);
  stateText += ",";

  stateText += Convert::ToString((int)state.FrontFSRValue);
  stateText += ",";

  stateText += Convert::ToString((int)state.BackFSRValue);
  stateText += ",";
#else
  stateText += "X,";
#endif
  stateText += "#\r\n";

  USART_Send(USART2, stateText);
  USART_Send(USART3, stateText);
}

void CommunicationDecoder(uint8_t command)
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
