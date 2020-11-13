/**
 ******************************************************************************
 * @file    PWM_Functions.hpp
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    15-October-2019
 * @brief   Header for PWM_Functions.c module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWM_FUNCTIONS_H
#define __PWM_FUNCTIONS_H

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Functions.hpp"

extern "C"
{
#include "stm32f10x.h"
} /* extern "C" { */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  CH1 = 1,
  CH2,
  CH3,
  CH4
} PWM_TimerChannelTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PWM_SetFrequency(TIM_TypeDef *TIMx, uint16_t NewFrequency);
void PWM_SetDutyCycle(TIM_TypeDef *TIMx, PWM_TimerChannelTypeDef Channel,
                      uint8_t DutyCycle);

uint16_t PWM_GetFrequency(TIM_TypeDef *TIMx, PWM_TimerChannelTypeDef Channel);
uint16_t PWM_GetDutyCycle(TIM_TypeDef *TIMx, PWM_TimerChannelTypeDef Channel);

class PWM
{
public:
  GPIO_PortPinTypeDef PortPin;
  TIM_TypeDef *Timer;
  PWM_TimerChannelTypeDef Channel;

  PWM(void);

  void Init(void);
  void Enable(void);
  void Disable(void);

  void setFrequency(uint16_t NewFrequency);
  void setDutyCycle(uint16_t NewDutyCycle);

  uint16_t getFrequency(void);
  uint16_t getDutyCycle(void);

private:
  GPIO GPIO_PWM;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  void setup(void);
  uint16_t convertDutyCycleToPulse(uint16_t DutyCycle);
};

#endif /* __PWM_FUNCTIONS_H */

/********************************END OF FILE***********************************/
