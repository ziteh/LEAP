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

#include "EC90fl_Motor_Functions.hpp"

/* The dircetion type of joint. */
typedef enum
{
  Extension = 1,
  Flexion = 2
} Joint_DirectionTypeDef;

/* The limit state type of joint. */
typedef enum
{
  Unlimited = 0,
  FullExtension = 1,
  FullFlexion = 2
} Joint_LimitStateTypeDef;

/* The state struct of joint. */
typedef struct
{
  Joint_LimitStateTypeDef Joint_LimitState;
  uint16_t Joint_Angle;
  Joint_DirectionTypeDef Joint_Direction;
} Joint_StateTypeDef;

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
Joint_LimitStateTypeDef Joint_GetLimitState(void);

/*********************************END OF FILE**********************************/