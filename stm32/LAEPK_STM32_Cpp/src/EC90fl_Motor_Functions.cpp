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

EC90Motor::EC90Motor(void)
{
  FunctionState.Mode = GPIO_Mode_Out_PP;
  FunctionState.Speed = GPIO_Speed_2MHz;

  Direction.Mode = GPIO_Mode_Out_PP;
  Direction.Speed = GPIO_Speed_2MHz;

  ReadyState.Mode = GPIO_Mode_IPD;

  RPM.Mode = GPIO_Mode_AIN;
}

void EC90Motor::Init(void)
{
  Speed.PortPin = PortPin_SpeedPWM;
  Speed.Timer = Timer_SpeedPWM;
  Speed.Channel = Channel_SpeedPWM;
  Speed.setFrequency(2000); // 2kHz.
  Speed.setDutyCycle(0);    // 0%.
  Speed.Init();
  Speed.Disable();

  FunctionState.PortPin = PortPin_FunctionState;
  FunctionState.Init();
  FunctionState.setValue(LOW); // Disable.

  Direction.PortPin = PortPin_Direction;
  Direction.Init();

  ReadyState.PortPin = PortPin_ReadyState;
  ReadyState.Init();

  RPM.PortPin = PortPin_RPM;
  RPM.Init();
}

void EC90Motor::Enable(void)
{
  Speed.Enable();
  FunctionState.setValue(HIGH);
}

void EC90Motor::Disable(void)
{
  FunctionState.setValue(LOW);
  Speed.Disable();
}

void EC90Motor::setDirection(EC90Motor::RotationDirectionTypeDef NewDirection)
{
  switch (NewDirection)
  {
  case CCW:
    Direction.setValue(HIGH); // HIGH: CCW
    break;
  case CW:
    Direction.setValue(LOW); // LOW: CW
    break;
  case ToggleDirection:
    Direction.toggleValue();
    break;
  }
}

void EC90Motor::setSpeed(uint16_t NewSpeed)
{
  Speed.setDutyCycle(NewSpeed);
}

EC90Motor::ReadyStateTypeDef EC90Motor::getReadyState(void)
{
  if (ReadyState.getValue() == HIGH)
    return Ready; // HIGH: Ready
  else
    return Fault; // LOW: Fault
}

EC90Motor::RotationDirectionTypeDef EC90Motor::getDirection(void)
{
  if (Direction.getValue() == HIGH)
    return CCW; // HIGH: CCW
  else
    return CW; // LOW: CW
}

uint16_t EC90Motor::getSpeed(void)
{
  return Speed.getDutyCycle();
}

/*********************************END OF FILE**********************************/
