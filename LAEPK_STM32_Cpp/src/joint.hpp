/**
 ******************************************************************************
 * @file    joint.hpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Header for joint.cpp module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __JOINT_HPP
#define __JOINT_HPP

#include "EC90fl_Motor_Functions.hpp"
#include "ADC_Functions.hpp"
#include "USART_Functions.hpp"
#include "convert.hpp"

/**
 * @brief The class of joint.
 */
class Joint
{
public:
  /* The dircetion type of joint. */
  typedef enum
  {
    Extension,
    Flexion
  } MotionDirectionTypeDef;

  /* The software limit state type of joint. */
  typedef enum
  {
    Unlimited,
    FullExtension,
    FullFlexion
  } SoftwareLimitStateTypeDef;

  typedef enum
  {
    WaitStop,
    NoInMotion,
    Extensioning,
    Flexioning
  } MotionStateTypeDef;

  MotionStateTypeDef MotionState;

  /* The state struct of joint. */
  typedef struct
  {
    MotionDirectionTypeDef Direction;
    SoftwareLimitStateTypeDef LimitState;
    uint16_t Angle;
  } State;

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

  GPIO_PortPinTypeDef PortPin_AnglePOT;
  ADC_TypeDef *ADCx_AnglePOT;
  uint8_t ADC_Channel_AnglePOT;

  GPIO_PortPinTypeDef PortPin_FrontFSR;
  ADC_TypeDef *ADCx_FrontFSR;
  uint8_t ADC_Channel_FrontFSR;

  GPIO_PortPinTypeDef PortPin_BackFSR;
  ADC_TypeDef *ADCx_BackFSR;
  uint8_t ADC_Channel_BackFSR;

  uint16_t FullExtensionPOTValue;
  uint16_t FullFlexionPOTValue;

  uint16_t ExtensionFSRStartThreshold;
  uint16_t FlexionFSRStartThreshold;

  uint16_t ExtensionFSRStopThreshold;
  uint16_t FlexionFSRStopThreshold;

  Joint(void);
  virtual void Init(void);

  bool ExtensionStartTriggered(void);
  bool FlexionStartTriggered(void);
  bool ExtensionStopTriggered(void);
  bool FlexionStopTriggered(void);

  virtual void MotionExtensionStart(void);
  virtual void MotionFlexionStart(void);

  virtual SoftwareLimitStateTypeDef MotionExtensionStop(void);
  virtual SoftwareLimitStateTypeDef MotionFlexionStop(void);

  uint16_t getAnglePOTValue(void);
  uint16_t getFrontFSRValue(void);
  uint16_t getBackFSRValue(void);
  SoftwareLimitStateTypeDef getLimitState(void);

  void MotionWaitStop(void);

  void MotionHandler(void);
  virtual SoftwareLimitStateTypeDef MotionStop(void);

  void SendInfo(void);

protected:
  EC90Motor Motor;
  ADC AnglePOT;
  ADC FrontFSR;
  ADC BackFSR;

  bool StartExtensionIsTriggered(void);
  bool StartFlexionIsTriggered(void);
  bool StopExtensionIsTriggered(void);
  bool StopFlexionIsTriggered(void);

  float Convert_ADCValueToAngle(uint16_t ADCValue);
  uint8_t Convert_DegPerSecToPWMDutyCycle(float DegPerSec);
};

class JointWithoutHallSensor : public Joint
{
public:
  GPIO_PortPinTypeDef PortPin_VirtualHall1;
  GPIO_PortPinTypeDef PortPin_VirtualHall2;
  GPIO_PortPinTypeDef PortPin_VirtualHall3;

  JointWithoutHallSensor(void);
  void Init(void);

  void MotionExtensionStart(void);
  void MotionFlexionStart(void);

  SoftwareLimitStateTypeDef MotionExtensionStop(void);
  SoftwareLimitStateTypeDef MotionFlexionStop(void);

  SoftwareLimitStateTypeDef MotionStop(void);

private:
  uint8_t VirtualHallStep;

  GPIO VirtualHall1;
  GPIO VirtualHall2;
  GPIO VirtualHall3;

  void VirtualHallHandler(EC90Motor::RotationDirectionTypeDef Direction);
};

/**
 * @brief Set absolute angle of joint.
 * @param TargetAngle Target angle(degree).
 */
void Joint_SetAbsoluteAngle(float TargetAngle);

/**
 * @brief Get absolute angle of joint.
 * @return Angle of joint(degree). 
 */
float Joint_GetAbsoluteAngle(void);

/**
 * @brief Get limit state of joint.
 * @return Limit state of joint. 
 */
// LimitStateTypeDef Joint_GetLimitState(void);

#endif /* __JOINT_HPP */

/*********************************END OF FILE**********************************/
