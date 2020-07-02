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

static __IO uint32_t TimingDelay;

uint16_t Joint_FullExtensionADCValue = Joint_DefaultFullExtensionADCValue;
uint16_t Joint_FullFlexionADCValue = Joint_DefaultFullFlexionADCValue;

uint8_t Joint_ExtensionFSRStartThreshold = Joint_DefaultExtensionFSRStartThreshold;
uint8_t Joint_FlexionFSRStartThreshold = Joint_DefaultFlexionFSRStartThreshold;

uint16_t Joint_ExtensionFSRStopThreshold = Joint_DefaultExtensionFSRStopThreshold;
uint16_t Joint_FlexionFSRStopThreshold = Joint_DefaultFlexionFSRStopThreshold;

RCC_ClocksTypeDef RCC_Clocks;

int main(void)
{
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  uint16_t ADC_JointAnglePOTValue;
  uint16_t ADC_FrontFSRValue;
  uint16_t ADC_BackFSRValue;

  float Joint_Angle;

  /* Initialization Functions */
  RCC_Initialization();
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
    /*
     * If FSR-Start-Extension is triggered,
     * and knee joint didn't exceed the Full-Extension angle limit,
     * then start extension.
     */
    if (StartExtensionIsTriggered() && (Joint_GetLimitState() != FullExtension))
    {
      USART_Send(USART2, "Start Ext\r\n");

      GPIO_SetValue(RightMotor_DirectionPin, HIGH); // CW(0) = Flexion; CCW(1) = Extension
      GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
      PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

      /*
       * Wait until FSR-Stop-Extension is triggered
       * or knee joint exceed the Full-Extension angle limit
       */
      while (!(StopExtensionIsTriggered() || (Joint_GetLimitState() == FullExtension)))
      {
      }

      USART_Send(USART2, "Stop Ext\r\n");
      GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
      PWM_SetDutyCycle(TIM3, CH2, 0);
    }

    /*
     * If FSR-Start-Flexion is triggered,
     * and knee joint didn't exceed the Full-Flexion angle limit,
     * then start flexion.
     */
    else if (StartFlexionIsTriggered() && (Joint_GetLimitState() != FullFlexion))
    {
      USART_Send(USART2, "Start Fle\r\n");

      GPIO_SetValue(RightMotor_DirectionPin, LOW); // CW(0) = Flexion; CCW(1) = Extension
      GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
      PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

      /*
       * Wait until FSR-Stop-Flexion is triggered
       * or knee joint exceed the Full-Flexion angle limit
       */
      while (!(StopFlexionIsTriggered() || (Joint_GetLimitState() == FullFlexion)))
      {
      }

      USART_Send(USART2, "Stop Fle\r\n");
      GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
      PWM_SetDutyCycle(TIM3, CH2, 0);
    }

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
}

void Joint_SetAbsoluteAngle(float TargetAngle)
{
  float NowAngle = Joint_GetAbsoluteAngle();

  GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
  PWM_SetDutyCycle(TIM3, CH2, 0);

  /* Extension */
  if ((NowAngle > TargetAngle)
      && (NowAngle > Convert_ADCValueToAngle(Joint_FullExtensionADCValue)))
  {
    GPIO_SetValue(RightMotor_DirectionPin, HIGH); // CW(0) = Flexion; CCW(1) = Extension
    GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
    PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

    while ((NowAngle > TargetAngle)
        && (NowAngle > Convert_ADCValueToAngle(Joint_FullExtensionADCValue)))
    {
      NowAngle = Joint_GetAbsoluteAngle(); // Update angle.
      USART_Send(USART2,
          convertIntToString(
              round(Convert_ADCValueToAngle(ADC_GetValue(ADC1, ADC_Channel_1, 1,
              ADC_SampleTime_55Cycles5)))));
      USART_Send(USART2, "\r\n");
    }

    GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
    PWM_SetDutyCycle(TIM3, CH2, 0);
  }
  /* Flexion */
  else if ((NowAngle < TargetAngle)
      && (NowAngle < Convert_ADCValueToAngle(Joint_FullFlexionADCValue)))
  {
    GPIO_SetValue(RightMotor_DirectionPin, LOW); // CW(0) = Flexion; CCW(1) = Extension
    GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
    PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

    while ((NowAngle < TargetAngle)
        && (NowAngle < Convert_ADCValueToAngle(Joint_FullFlexionADCValue)))
    {
      NowAngle = Joint_GetAbsoluteAngle(); // Update angle.
      USART_Send(USART2,
          convertIntToString(
              round(Convert_ADCValueToAngle(ADC_GetValue(ADC1, ADC_Channel_1, 1,
              ADC_SampleTime_55Cycles5)))));
      USART_Send(USART2, "\r\n");
    }

    GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
    PWM_SetDutyCycle(TIM3, CH2, 0);
  }
}

float Joint_GetAbsoluteAngle(void)
{
  uint16_t ADC_Value = ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
  return Convert_ADCValueToAngle(ADC_Value);
}

inline Joint_LimitStateTypeDef Joint_GetLimitState(void)
{
  if (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
      <= Joint_FullExtensionADCValue)
    return ((Joint_LimitStateTypeDef) FullExtension);
  else if (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
      >= Joint_FullFlexionADCValue)
    return ((Joint_LimitStateTypeDef) FullFlexion);
  else
    return ((Joint_LimitStateTypeDef) Unlimited);
}

inline bool StartExtensionIsTriggered(void)
{
  /*
   * If Start-Extension is triggered,
   * that is if Front FSR ADC Value > Extension Start Threshold,
   * then return TRUE, else return FALSE.
   */
  return (ADC_GetValue(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5)
      > Joint_ExtensionFSRStartThreshold);
}

inline bool StartFlexionIsTriggered(void)
{
  /*
   * If Start-Flexion is triggered,
   * that is if Back FSR ADC Value > Flexion Start Threshold,
   * then return TRUE, else return FALSE.
   */
  return (ADC_GetValue(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5)
      > Joint_FlexionFSRStartThreshold);
}

inline bool StopExtensionIsTriggered(void)
{
  /*
   * If Stop-Extension is triggered,
   * that is if Back FSR ADC Value > Extension Stop Threshold,
   * then return TRUE, else return FALSE.
   */
  return (ADC_GetValue(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5)
      > Joint_ExtensionFSRStopThreshold);
}

inline bool StopFlexionIsTriggered(void)
{
  /*
   * If Stop-Flexion is triggered,
   * that is if Front FSR ADC Value > Flexion Stop Threshold,
   * then return TRUE, else return FALSE.
   */
  return (ADC_GetValue(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5)
      > Joint_FlexionFSRStopThreshold);
}

float Convert_ADCValueToAngle(uint16_t ADCValue)
{
  /**
   * The POT_Gear is 20 teeth, Joint_Gear is 250 teeth.
   * The Gear Ratio = 250/20 = 12.5:1
   *
   * ADC resolution is 12bits = 4096 quantization levels (0 ~ 4095).
   * POT Maximum degree = 3600 degrees = 10 turn.
   *
   * The POT_Angle per ADC_Quantization levels = 3600/4096
   *                                           = 225/256
   *                                           = 0.878 906 25
   *                                           (unit in deg/ADC_Lv)
   *
   * That,
   * The Joint_Angle per ADC_Quantization levels = POT_deg per ADC_lv / 12.5
   *                                             = (3600/4096)/12.5
   *                                             = 9/128
   *                                             = 0.070 312 5
   *                                             (unit in deg/ADC_Lv)
   *
   * And,
   * Knee joint full extension is defined as -5 deg.
   * So,
   * Joint_Angle = [(ADC_Value - Full_Extension_ADC_Value)*(9/128)]-5
   */

  return ((float) ((ADCValue - Joint_FullExtensionADCValue)*(0.0703125) -5));
}

uint8_t Convert_DegPerSecToPWMDutyCycle(float DegPerSec)
{
  /**
   * The nominal speed of Maxon EC90 flat brushless motor(515458) is 2720rpm.
   * The gear ratio of Harmoinc Drive SHD-25-100-2SH is 100:1.
   *
   * So, the max speed of joint is 2720/100 = 27.2rpm(ideal).
   *
   * Mode of motor controller is open loop speed control,
   * 0...95 % PWM depending on the «Set value speed» input voltage.
   *
   * Minimum speed: Nmin (rpm)
   * Maximum speed: Nmax (rpm)
   * Set respectively speed: N (rpm)
   * Set value voltage: Vset (V)
   * Vset = {[(N-Nmin)/(Nmax-Nmin)]*4.9}+0.1
   *
   * 1 Degree Per Second = 1/6 rpm
   */

  /* gear ration * RespectivelySpeed in rpm */
  float RespectivelySpeed = 100*(DegPerSec/6.0);

  /* Vset = {[(N-Nmin)/(Nmax-Nmin)]*4.9}+0.1 */
  float Vset = ((RespectivelySpeed/2720.0)*4.9)+0.1;

  /* PWM Dutu Cucly = (Vset/Vp)*100% */
  float PWMDutyCycle = (Vset/3.3)*100;

  if (PWMDutyCycle >= 100)
    return ((uint8_t) 100);
  else
    return ((uint8_t) PWMDutyCycle);
}

void CommunicationDecoder(uint8_t Command)
{
  Joint_SetAbsoluteAngle(Command-5);
}

void Full_Initialization(void)
{
}

/**
 * @brief       Initialize the different system clocks.
 * @param       None
 * @retval      None
 * @attention   Please run this function BEFORE any other initialization.
 */
void RCC_Initialization(void)
{
  /* Resets the RCC clock configuration to the default reset state */
  RCC_DeInit();

  /* RCC APB1 */
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2 |
                          RCC_APB1Periph_TIM3,
                          ENABLE);

  /* RCC APB2 */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA |
                          RCC_APB2Periph_GPIOB |
                          RCC_APB2Periph_GPIOC |
                          RCC_APB2Periph_GPIOD |
                          RCC_APB2Periph_GPIOE,
//                          RCC_APB2Periph_ADC1,
//                          RCC_APB2Periph_AFIO,
                          ENABLE);
}

void EXIT_Initialization(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void Timer_Initialization(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 72-1;
  TIM_TimeBaseStructure.TIM_Prescaler = 1000;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

/* class Motor */
void EC90Motor::setPWMTimerChannelPortPin(TIM_TypeDef* NewTimer,
    PWM_TimerChannelTypeDef NewChannel, GPIO_PortPinTypeDef NewPWMPortPin)
{
  PWM_Speed.setTimer(NewTimer);
  PWM_Speed.setChannel(NewChannel);
  PWM_Speed.setPortPin(NewPWMPortPin);

  PWM_Speed.setFrequency(50);
  PWM_Speed.setDutyCycle(0);
//  PWM_Speed.setDisable();
  PWM_Speed.setEnable();
}

void EC90Motor::setOutputPinFunctionState(GPIO_PortPinTypeDef NewFSPortPin)
{
  GPIO_FunctionState.setPortPin(NewFSPortPin);
  GPIO_FunctionState.setMode(GPIO_Mode_Out_PP);
  GPIO_FunctionState.setSpeed(GPIO_Speed_2MHz);
  GPIO_FunctionState.setValue(LOW); // Disable
}

void EC90Motor::setOutputPinDirection(GPIO_PortPinTypeDef NewDirPortPin)
{
  GPIO_Direction.setPortPin(NewDirPortPin);
  GPIO_Direction.setMode(GPIO_Mode_Out_PP);
  GPIO_Direction.setSpeed(GPIO_Speed_2MHz);
  GPIO_Direction.setValue(LOW);
}

void EC90Motor::setInputPinReadyState(GPIO_PortPinTypeDef NewRSPortPin)
{
  GPIO_ReadyState.setPortPin(NewRSPortPin);
  GPIO_ReadyState.setMode(GPIO_Mode_IPD);
}

void EC90Motor::setInputPinRPM(GPIO_PortPinTypeDef NewRPMPortPin)
{
  GPIO_RPM.setPortPin(NewRPMPortPin);
  GPIO_RPM.setMode(GPIO_Mode_AIN);
}

void EC90Motor::setFunctionState(Motor_FunctionStateTypeDef NewState)
{
  if (NewState == Enable)
    GPIO_FunctionState.setValue(HIGH);  // HIGH: Enable
  else if (NewState == Disable)
    GPIO_FunctionState.setValue(LOW);  // HIGH: Enable
  else if (NewState == ToggleState)
    GPIO_FunctionState.setValueToggle();
}

void EC90Motor::setDirection(Motor_DirectionTypeDef NewDirection)
{
  if (NewDirection == CCW)
    GPIO_Direction.setValue(HIGH);  // HIGH: CCW
  else if (NewDirection == CW)
    GPIO_Direction.setValue(LOW);  // HIGH: CW
  else if (NewDirection == ToggleDirection)
    GPIO_Direction.setValueToggle();
}

void EC90Motor::setDutyCycle(uint16_t NewDutyCycle)
{
  PWM_Speed.setDutyCycle(NewDutyCycle);
}

Motor_ReadyStateTypeDef EC90Motor::getReadyState(void)
{
  Motor_ReadyStateTypeDef ReadyState = Fault;

  if (GPIO_ReadyState.getValue() == HIGH) // HIGH: Ready
    ReadyState = Ready;
  else  // LOW: Fault
    ReadyState = Fault;

  return ReadyState;
}

Motor_FunctionStateTypeDef EC90Motor::getFunctionState(void)
{
  Motor_FunctionStateTypeDef FunctionState;

  if (GPIO_FunctionState.getValue() == HIGH) // HIGH: Enable
    FunctionState = Enable;
  else if (GPIO_FunctionState.getValue() == LOW) // LOW: Disable
    FunctionState = Disable;

  return FunctionState;
}

Motor_DirectionTypeDef EC90Motor::getDirection(void)
{
  Motor_DirectionTypeDef Direction;

  if (GPIO_Direction.getValue() == HIGH) // HIGH: CCW
    Direction = CCW;
  else if (GPIO_Direction.getValue() == LOW) // LOW: CW
    Direction = CW;

  return Direction;
}

uint16_t EC90Motor::getDutyCycle(void)
{
 return PWM_Speed.getDutyCycle();
}

//Joint_Joint(void)
//{
//  Full_Extension_ADC_Value = Default_Full_Extension_ADC_Value;
//  Full_Flexion_ADC_Value = Default_Full_Flexion_ADC_Value;
//
//  Motor_1.setPWMTimerChannelPortPin(TIM3, CH2, PA7);
//  Motor_1.setDutyCycle(0);
//
//  ADC_POT.setADCChannel(ADC1, ADC_Channel_1);
//  ADC_POT.setPortPin(A1);
//  ADC_POT.setEnable();
//}

//void Joint_setAngularSpeed(uint8_t NewAngularSpeed)
//{
//}
//
//void Joint_Joint_setAngularAcceleration(uint8_t NewAngularAcceleration)
//{
//}
//
//void Joint_setAbsoluteAngle(float TargetAngle)
//{
//  float NowAngle = Joint_getAbsoluteAngle();
////  EC90Motor Motor_R;
////  Motor_R.setPWMTimerChannelPortPin(TIM3, CH2, PA7);
////  Motor_R.setDutyCycle(0);
//
//  /* Extension */
//  if (NowAngle > TargetAngle)
//  {
////    Motor_R.setDirection(CW);
////    Motor_R.setDutyCycle(10);
////    Motor_R.setFunctionState(Enable);
//
////    setPWMDutyCycle(TIM3, CH2, 10);
//
//    while (NowAngle > TargetAngle)
//    {
//      NowAngle = Joint_getAbsoluteAngle(); // Update angle.
//    }
////    Motor_R.setFunctionState(Disable);
////    Motor_R.setDutyCycle(0);
//
////    setPWMDutyCycle(TIM3, CH2, 0);
//  }
//  /* Flexion */
//  else if (NowAngle < TargetAngle)
//  {
////    Motor_R.setDirection(CCW);
////    Motor_R.setDutyCycle(10);
////    Motor_R.setFunctionState(Enable);
//
////    setPWMDutyCycle(TIM3, CH2, 10);
//
//    while (NowAngle < TargetAngle)
//    {
//      NowAngle = Joint_getAbsoluteAngle(); // Update angle.
//    }
////    Motor_R.setFunctionState(Disable);
////    Motor_R.setDutyCycle(0);
//
////    setPWMDutyCycle(TIM3, CH2, 0);
//  }
//}
//
//void Joint_setAbsoluteAngle(Joint_LimitStateTypeDef TargetPosition)
//{
//}
//
//void Joint_setRelativelyAngle(Joint_DirectionTypeDef Direction, float IncreaseAngle)
//{
// if (Direction == Extension)
// {
//
// }
//
//
//}
//
//float Joint_getAbsoluteAngle(void)
//{
//  /* POT */
////  ADC ADC_POT_R(ADC1, ADC_Channel_1, A1);
////  ADC_POT_R.setEnable();
//
//  uint16_t ADC_Value = ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
//  return Joint_convertADCValueToAngle(ADC_Value);
//}
//
//float Joint_convertADCValueToAngle(uint16_t ADCValue)
//{
//  /**
//   * The POT_Gear is 20 teeth, Joint_Gear is 250 teeth.
//   * The Gear Ratio = 250/20 = 12.5:1
//   *
//   * ADC resolution is 12bits = 4096 quantization levels (0 ~ 4095).
//   * POT Maximum degree = 3600 degrees = 10 turn.
//   *
//   * The POT_Angle per ADC_Quantization levels = 3600/4096
//   *                                           = 225/256
//   *                                           = 0.878 906 25
//   *                                           (unit in deg/ADC_Lv)
//   *
//   * That,
//   * The Joint_Angle per ADC_Quantization levels = POT_deg per ADC_lv / 12.5
//   *                                             = (3600/4096)/12.5
//   *                                             = 9/128
//   *                                             = 0.070 312 5
//   *                                             (unit in deg/ADC_Lv)
//   *
//   * And,
//   * Knee joint full extension is defined as -5 deg.
//   * So,
//   * Joint_Angle = [(ADC_Value - Full_Extension_ADC_Value)*(9/128)]-5
//   */
//
//  return ((float) ((ADCValue - Full_Extension_ADC_Value)*(0.0703125) -5));
//}
//
//Joint_LimitStateTypeDef Joint_getLimitState(void)
//{
//  /* POT */
////  ADC ADC_POT_R(ADC1, ADC_Channel_1, A1);
////  ADC_POT_R.setEnable();
//
//  uint16_t ADC_Value = ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
//
//  /* Full_Extension_ADC_Value is the minimum ADC value */
//  if (ADC_Value <= Full_Extension_ADC_Value)
//    return FullExtension;
//  /* Full_Flexion_ADC_Value is the maximum ADC value */
//  else if (ADC_Value >= Full_Flexion_ADC_Value)
//    return FullFlexion;
//  else
//    return Unlimited;
//}

char* convertIntToString(int IntNumber)
{
  static char string[3];
  sprintf(string, "%d", IntNumber);
  return string;
}

/* ERROE: region `flash' overflowed */
//std::string convertFloatToString(float FloatNumber)
//{
//  std::ostringstream ss;
//  ss << FloatNumber;
//  std::string s(ss.str());
//  return ((std::string) s);
//}

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
  TimingDelay = (nTime*0.125);

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

/*********************************END OF FILE**********************************/
