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
  RCC_Initialization;
  USART_Initialization;
  Timer_Initialization;
  Board_Initialization;
  //  LimitSwitch_Initialization;
  Joint_Initialization(&RightJoint, Right);
  Joint_Initialization(&LeftJoint, Left);

  USART_Send(USART2, "[L.A.E.P.K. READY]\r\n");

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
