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
  } DirectionTypeDef;

  /* The limit state type of joint. */
  typedef enum
  {
    Unlimited,
    FullExtension,
    FullFlexion
  } LimitStateTypeDef;

  /* The state struct of joint. */
  typedef struct
  {
    DirectionTypeDef Direction;
    LimitStateTypeDef LimitState;
    uint16_t Angle;
  } State;

  LimitStateTypeDef Extension(void);
  LimitStateTypeDef Flexion(void);
  LimitStateTypeDef Stop(void);

private:
  EC90Motor Motor;
}

/**
 * @brief Set absolute angle of joint.
 * @param TargetAngle Target angle(degree).
 */
void
Joint_SetAbsoluteAngle(float TargetAngle);

/**
 * @brief Get absolute angle of joint.
 * @return Angle of joint(degree). 
 */
float Joint_GetAbsoluteAngle(void);

/**
 * @brief Get limit state of joint.
 * @return Limit state of joint. 
 */
LimitStateTypeDef Joint_GetLimitState(void);

#endif /* __JOINT_HPP */

/*********************************END OF FILE**********************************/