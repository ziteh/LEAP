/**
 ******************************************************************************
 * @file    EC90fl_Motor_Functions.hpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Header for EC90fl_Motor_Functions.cpp module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __EC90FL_MOTOR_FUNCTIONS_HPP
#define __EC90FL_MOTOR_FUNCTIONS_HPP

#include "PWM_Functions.hpp"
#include "GPIO_Functions.hpp"

// /* The functino state type of motor */
// typedef enum
// {
//   Disable = 0,
//   Enable = 1,
//   ToggleState = 2
// } Motor_FunctionStateTypeDef;

// /* The state type of motor */
// typedef struct
// {
//   Motor_ReadyStateTypeDef Motor_ReadyState;
//   Motor_FunctionStateTypeDef Motor_FunctionState;
//   Motor_DirectionTypeDef Motor_Direction;
//   uint16_t Motor_PMW_DutyCycle;
//   uint16_t Motor_RPM;
// } Motor_StateTypeDef;

/* The class of EC90fl. BL-Motor */
class EC90Motor
{
public:
  /* The direction type of motor */
  typedef enum
  {
    CW = 0,
    CCW = 1,
    ToggleDirection = 2
  } RotationDirectionTypeDef;

  /* The ready state type of motor */
  typedef enum
  {
    Fault = 0,
    Ready = !Fault
  } ReadyStateTypeDef;

  /* PWM timer used for motor speed control. */
  TIM_TypeDef *Timer_SpeedPWM;

  /* PWM timer-chammel used for motor speed control. */
  PWM_TimerChannelTypeDef Channel_SpeedPWM;

  /* PWM output pin used for motor speed control. */
  GPIO_PortPinTypeDef PortPin_SpeedPWM;

  /* Output pin used for motor functino state control. */
  GPIO_PortPinTypeDef PortPin_FunctionState;

  /* Output pin used for motor direction control. */
  GPIO_PortPinTypeDef PortPin_Direction;

  /* Input pin used for read motor ready state. */
  GPIO_PortPinTypeDef PortPin_ReadyState;

  /* Analog input pin used for read motor RPM. */
  GPIO_PortPinTypeDef PortPin_RPM;

  EC90Motor(void);
  void Init(void);
  void Enable(void);
  void Disable(void);
  void setDirection(EC90Motor::RotationDirectionTypeDef NewDirection);
  void setSpeed(uint16_t NewSpeed);

  ReadyStateTypeDef getReadyState(void);
  RotationDirectionTypeDef getDirection(void);
  uint16_t getSpeed(void);

private:
  PWM Speed;
  GPIO FunctionState;
  GPIO Direction;
  GPIO ReadyState;
  GPIO RPM;
};

#endif /* __EC90FL_MOTOR_FUNCTIONS_HPP */

/*********************************END OF FILE**********************************/
