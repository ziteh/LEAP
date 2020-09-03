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

  /* Initialization */
  NowJoint = &RightJoint;
  Joint_Initialization(NowJoint, Right);
  NowJoint = &LeftJoint;
  Joint_Initialization(NowJoint, Left);

  RCC_Initialization;
  LimitSwitch_Initialization;
  USART_Initialization;
  Timer_Initialization;
  Board_Initialization;

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

void Joint_Initialization(Joint *joint, JointTypeDef jointType)
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

  //  joint->PortPin_FunctionState = Joint_PortPin_FunctionState(jointType);
  joint->PortPin_FunctionState = (jointType == Right) ? RightJoint_PortPin_FunctionState : LeftJoint_PortPin_FunctionState;
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
