/**
 ******************************************************************************
 * @file    unit_test.cpp
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Main program body of unit-test.
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "unit_test.hpp"

namespace UnitTest
{
  /**
 * @brief GPIO-PA10(D2) will output HIGH.
 */
  void GPIO_PA10_Output_HIGH(void)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO pin;
    pin.PortPin = PA10;
    pin.Mode = GPIO_Mode_Out_PP;
    pin.Speed = GPIO_Speed_2MHz;
    pin.Init();

    pin.setValue(HIGH);
  }

  /**
 * @brief When user-button(B1) push user-LED(LD2) will off, else user-LED will on.
 */
  void GPIO_UserButton_Input_UserLED_Output(void)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                               RCC_APB2Periph_GPIOC,
                           ENABLE);

    GPIO button;
    button.PortPin = User_Button;
    button.Mode = GPIO_Mode_IN_FLOATING;
    button.Init();

    GPIO LED;
    LED.PortPin = User_LED;
    LED.Mode = GPIO_Mode_Out_PP;
    LED.Speed = GPIO_Speed_2MHz;
    LED.Init();

    while (1)
    {
      if (button.getValue() == HIGH)
        LED.setValue(HIGH);
      else
        LED.setValue(LOW);
    }
  }

  /**
 * @brief Send "Hello World!".
 */
  void USART_Send_Data(void)
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

    /* Configures the priority grouping */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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

    /* Clear "Transmission Complete" flag, ���洵1雿����仃 */
    USART_ClearFlag(USART2, USART_FLAG_TC);

    while (1)
    {
      USART_Send(USART2, "Hello World!\r\n");
    }
  }

  void ADC_Read_Analog_value(void)
  {
    /* -- USART2 -- */
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

    /* Configures the priority grouping */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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

    /* Clear "Transmission Complete" flag, ���洵1雿����仃 */
    USART_ClearFlag(USART2, USART_FLAG_TC);
    /* -- End of USART2 -- */

    /* -- ADC -- */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC adc;
    adc.PortPin = PA1;
    adc.ADCx = ADC1;
    adc.ADC_Channel = ADC_Channel_1;
    adc.Init();
    adc.Enable();

    USART_Send(USART2, "READY\r\n");
    USART_Send(USART2, Convert::ToString(1));
    while (1)
    {
      USART_Send(USART2, Convert::ToString(adc.getValue()));
      USART_Send(USART2, "\r\n");
    }
    /* -- End of ADC -- */
  }

  void PWM_Output_1kHz_50DutyCycle(void)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    PWM pwm;
    pwm.PortPin = PA7;
    pwm.Timer = TIM3;
    pwm.Channel = CH2;
    pwm.Init();

    pwm.setFrequency(1000);
    pwm.setDutyCycle(50);

    pwm.Enable();
  }

  void EC90_CW(void)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                               RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOC,
                           ENABLE);

    EC90Motor motor;
    motor.PortPin_SpeedPWM = PA7;
    motor.Timer_SpeedPWM = TIM3;
    motor.Channel_SpeedPWM = CH2;
    motor.PortPin_FunctionState = D10;
    motor.PortPin_Direction = D9;
    motor.PortPin_ReadyState = D8;

    motor.Init();

    motor.setDirection(EC90Motor::CW);
    motor.setSpeed(20);

    motor.Enable();
  }

  void Joint_Extenstion(void)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                               RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOC |
                               RCC_APB2Periph_ADC1,
                           ENABLE);

    GPIO USART2_TX;
    USART2_TX.PortPin = PA2;
    USART2_TX.Mode = GPIO_Mode_AF_PP;
    USART2_TX.Speed = GPIO_Speed_50MHz;
    USART2_TX.Init();

    GPIO USART2_RX;
    USART2_RX.PortPin = PA3;
    USART2_RX.Mode = GPIO_Mode_IN_FLOATING;
    USART2_RX.Init();

    /* Configures the priority grouping */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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

    /* Clear "Transmission Complete" flag, ���洵1雿����仃 */
    USART_ClearFlag(USART2, USART_FLAG_TC);

    Joint joint;

    // Motor
    joint.PortPin_SpeedPWM = PA7; // D11
    joint.Timer_SpeedPWM = TIM3;
    joint.Channel_SpeedPWM = CH2;

    joint.PortPin_FunctionState = D10;
    joint.PortPin_Direction = D9;
    joint.PortPin_ReadyState = D8;

    // ADC
    joint.PortPin_AnglePOT = PA1; // A1
    joint.ADCx_AnglePOT = ADC1;
    joint.ADC_Channel_AnglePOT = ADC_Channel_1;

    joint.PortPin_FrontFSR = PA4; // A2
    joint.ADCx_FrontFSR = ADC1;
    joint.ADC_Channel_FrontFSR = ADC_Channel_4;

    joint.PortPin_BackFSR = PB0; // A3
    joint.ADCx_BackFSR = ADC1;
    joint.ADC_Channel_BackFSR = ADC_Channel_8;

    // Value & Threshold
    joint.FullExtensionPOTValue = 1400;
    joint.FullFlexionPOTValue = 2450;

    joint.ExtensionFSRStartThreshold = 215;
    joint.FlexionFSRStartThreshold = 180;

    joint.ExtensionFSRStopThreshold = 500;
    joint.FlexionFSRStopThreshold = 500;

    joint.Init();
    joint.MotionStop();

    USART_Send(USART2, "READY\r\n");

    while (1)
    {
      joint.MotionHandler();
    }
  }

  void Timer_1sec(void)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseS

  }

} // namespace UnitTest
/********************************END OF FILE***********************************/
