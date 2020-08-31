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

#include "PWM_Functions.hpp"
#include "GPIO_Functions.hpp"

/* The functino state type of motor */
typedef enum
{
  Disable = 0,
  Enable = 1,
  ToggleState = 2
} Motor_FunctionStateTypeDef;

/* The direction type of motor */
typedef enum
{
  CW = 0,
  CCW = 1,
  ToggleDirection = 2
} Motor_DirectionTypeDef;

/* The ready state type of motor */
typedef enum
{
  Fault = 0,
  Ready = !Fault
} Motor_ReadyStateTypeDef;

/* The state type of motor */
typedef struct
{
  Motor_ReadyStateTypeDef Motor_ReadyState;
  Motor_FunctionStateTypeDef Motor_FunctionState;
  Motor_DirectionTypeDef Motor_Direction;
  uint16_t Motor_PMW_DutyCycle;
  uint16_t Motor_RPM;
} Motor_StateTypeDef;

/* The class of EC90fl. BL-Motor */
class EC90Motor
{
public:
  void setPWMTimerChannelPortPin(TIM_TypeDef *NewTimer,
                                 PWM_TimerChannelTypeDef NewChannel,
                                 GPIO_PortPinTypeDef NewPWMPortPin);

  void setOutputPinFunctionState(GPIO_PortPinTypeDef NewFSPortPin);
  void setOutputPinDirection(GPIO_PortPinTypeDef NewDirPortPin);
  void setInputPinReadyState(GPIO_PortPinTypeDef NewRSPortPin);
  void setInputPinRPM(GPIO_PortPinTypeDef NewRPMPortPin);

  void setFunctionState(Motor_FunctionStateTypeDef NewState);
  void setDirection(Motor_DirectionTypeDef NewDirection);
  void setDutyCycle(uint16_t NewDutyCycle);

  Motor_ReadyStateTypeDef getReadyState(void);
  Motor_FunctionStateTypeDef getFunctionState(void);
  Motor_DirectionTypeDef getDirection(void);
  uint16_t getDutyCycle(void);

private:
  /* PWM Output used for motor speed control. */
  PWM PWM_Speed;

  /* Output pin used for motor functino state control. */
  GPIO GPIO_FunctionState;

  /* Output pin used for motor direction control. */
  GPIO GPIO_Direction;

  /* Input pin used for read motor ready state. */
  GPIO GPIO_ReadyState;

  /* Analog input pin used for read motor RPM. */
  GPIO GPIO_RPM;
};

/*********************************END OF FILE**********************************/