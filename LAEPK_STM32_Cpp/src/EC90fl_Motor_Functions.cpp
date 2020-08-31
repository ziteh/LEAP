/**
 ******************************************************************************
 * @file    EC90fl_Motor_Functions.cpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Program body of MAXON EC90fl. BL-Motor.
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "EC90fl_Motor_Functions.hpp"

void EC90Motor::setPWMTimerChannelPortPin(TIM_TypeDef *NewTimer,
                                          PWM_TimerChannelTypeDef NewChannel,
                                          GPIO_PortPinTypeDef NewPWMPortPin)
{
  PWM_Speed.setTimer(NewTimer);
  PWM_Speed.setChannel(NewChannel);
  PWM_Speed.setPortPin(NewPWMPortPin);

  PWM_Speed.setFrequency(50);
  PWM_Speed.setDutyCycle(0);
  PWM_Speed.setEnable();
}

void EC90Motor::setOutputPinFunctionState(GPIO_PortPinTypeDef NewFSPortPin)
{
  GPIO_FunctionState.PortPin = NewFSPortPin;
  GPIO_FunctionState.Mode = GPIO_Mode_Out_PP;
  GPIO_FunctionState.Speed = GPIO_Speed_2MHz;
  GPIO_FunctionState.Init();

  GPIO_FunctionState.setValue(LOW); // Disable.
}

void EC90Motor::setOutputPinDirection(GPIO_PortPinTypeDef NewDirPortPin)
{
  GPIO_Direction.PortPin = NewDirPortPin;
  GPIO_Direction.Mode = GPIO_Mode_Out_PP;
  GPIO_Direction.Speed = GPIO_Speed_2MHz;
  GPIO_Direction.Init();

  GPIO_Direction.setValue(LOW);
}

void EC90Motor::setInputPinReadyState(GPIO_PortPinTypeDef NewRSPortPin)
{
  GPIO_ReadyState.PortPin = NewRSPortPin;
  GPIO_ReadyState.Mode = GPIO_Mode_IPD;
  GPIO_ReadyState.Init();
}

void EC90Motor::setInputPinRPM(GPIO_PortPinTypeDef NewRPMPortPin)
{
  GPIO_RPM.PortPin = NewRPMPortPin;
  GPIO_RPM.Mode = GPIO_Mode_AIN;
  GPIO_RPM.Init();
}

void EC90Motor::setFunctionState(Motor_FunctionStateTypeDef NewState)
{
  if (NewState == Enable)
    GPIO_FunctionState.setValue(HIGH); // HIGH: Enable
  else if (NewState == Disable)
    GPIO_FunctionState.setValue(LOW); // LOW: Disable
  else if (NewState == ToggleState)
    GPIO_FunctionState.toggleValue();
}

void EC90Motor::setDirection(Motor_DirectionTypeDef NewDirection)
{
  if (NewDirection == CCW)
    GPIO_Direction.setValue(HIGH); // HIGH: CCW
  else if (NewDirection == CW)
    GPIO_Direction.setValue(LOW); // LOW: CW
  else if (NewDirection == ToggleDirection)
    GPIO_Direction.toggleValue();
}

void EC90Motor::setDutyCycle(uint16_t NewDutyCycle)
{
  PWM_Speed.setDutyCycle(NewDutyCycle);
}

Motor_ReadyStateTypeDef EC90Motor::getReadyState(void)
{
  Motor_ReadyStateTypeDef ReadyState;

  if (GPIO_ReadyState.getValue() == HIGH) // HIGH: Ready
    ReadyState = Ready;
  else // LOW: Fault
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

/*********************************END OF FILE**********************************/