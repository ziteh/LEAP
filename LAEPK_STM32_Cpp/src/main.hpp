/**
 ******************************************************************************
 * @file    main.hpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V0.1
 * @date    25-October-2019
 * @brief   Header for main.cpp module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <sstream>
#include <cmath>
#include "GPIO_Functions.hpp"
#include "PWM_Functions.hpp"
#include "USART_Functions.hpp"
#include "ADC_Functions.hpp"
#include "EC90fl_Motor_Functions.hpp"
#include "joint.hpp"
#include "unit_test.hpp"

extern "C"
{
#include <stdio.h>
#include "stm32f10x.h"
}

#define LimitSwitch_PortPin ((GPIO_PortPinTypeDef)PA0)

/* Right leg define */
#define RightJoint_PortPin_SpeedPWM ((GPIO_PortPinTypeDef)PA7)
#define RightJoint_Timer_SpeedPWM (TIM3)
#define RightJoint_Channel_SpeedPWM (CH2)

#define RightJoint_PortPin_FunctionState ((GPIO_PortPinTypeDef)PC7)
#define RightJoint_PortPin_Direction ((GPIO_PortPinTypeDef)PB6)
#define RightJoint_PortPin_ReadyState ((GPIO_PortPinTypeDef)PA9)

#define RightJoint_PortPin_AnglePOT ((GPIO_PortPinTypeDef)PA1)
#define RightJoint_ADCx_AnglePOT (ADC1)
#define RightJoint_ADC_Channel_AnglePOT (ADC_Channel_1)

#define RightJoint_PortPin_FrontFSR ((GPIO_PortPinTypeDef)PA4)
#define RightJoint_ADCx_FrontFSR (ADC1)
#define RightJoint_ADC_Channel_FrontFSR (ADC_Channel_4)

#define RightJoint_PortPin_BackFSR ((GPIO_PortPinTypeDef)PB0)
#define RightJoint_ADCx_BackFSR (ADC1)
#define RightJoint_ADC_Channel_BackFSR (ADC_Channel_8)

#define RightJoint_DefaultValue_POTFullExtension ((uint16_t)1400)
#define RightJoint_DefaultValue_POTFullFlexion ((uint16_t)2450)

#define RightJoint_DefaultValue_FSRStartExtension ((uint16_t)2000)
#define RightJoint_DefaultValue_FSRStartFlexion ((uint16_t)2500)

#define RightJoint_DefaultValue_FSRStopExtension ((uint16_t)RightJoint_DefaultValue_FSRStartFlexion - 200)
#define RightJoint_DefaultValue_FSRStopFlexion ((uint16_t)RightJoint_DefaultValue_FSRStartExtension - 200)

#define RightJoint_Reverse ((bool) false)

/* Left leg define */
#define LeftJoint_PortPin_SpeedPWM ((GPIO_PortPinTypeDef)PB8)
#define LeftJoint_Timer_SpeedPWM (TIM4)
#define LeftJoint_Channel_SpeedPWM (CH3)

#define LeftJoint_PortPin_FunctionState ((GPIO_PortPinTypeDef)PA8)
#define LeftJoint_PortPin_Direction ((GPIO_PortPinTypeDef)PC9)
#define LeftJoint_PortPin_ReadyState ((GPIO_PortPinTypeDef)PA9)

#define LeftJoint_PortPin_AnglePOT ((GPIO_PortPinTypeDef)PC3)
#define LeftJoint_ADCx_AnglePOT (ADC1)
#define LeftJoint_ADC_Channel_AnglePOT (ADC_Channel_13)

#define LeftJoint_PortPin_FrontFSR ((GPIO_PortPinTypeDef)PC1)
#define LeftJoint_ADCx_FrontFSR (ADC1)
#define LeftJoint_ADC_Channel_FrontFSR (ADC_Channel_11)

#define LeftJoint_PortPin_BackFSR ((GPIO_PortPinTypeDef)PC0)
#define LeftJoint_ADCx_BackFSR (ADC1)
#define LeftJoint_ADC_Channel_BackFSR (ADC_Channel_10)

#define LeftJoint_DefaultValue_POTFullExtension ((uint16_t)1400)
#define LeftJoint_DefaultValue_POTFullFlexion ((uint16_t)2450)

#define LeftJoint_DefaultValue_FSRStartExtension ((uint16_t)1400)
#define LeftJoint_DefaultValue_FSRStartFlexion ((uint16_t)1600)

#define LeftJoint_DefaultValue_FSRStopExtension ((uint16_t)LeftJoint_DefaultValue_FSRStartFlexion - 250)
#define LeftJoint_DefaultValue_FSRStopFlexion ((uint16_t)LeftJoint_DefaultValue_FSRStartExtension - 250)

#define LeftJoint_Reverse ((bool) true)

#define LeftJoint_PortPin_VirtualHall1 ((GPIO_PortPinTypeDef)PB8)
#define LeftJoint_PortPin_VirtualHall2 ((GPIO_PortPinTypeDef)PB9)
#define LeftJoint_PortPin_VirtualHall3 ((GPIO_PortPinTypeDef)PA6)

/* Limit switch */
#define NVIC_PreemptionPriority_EXTI0 (0)
#define NVIC_SubPriority_EXTI0 (0)

/* User button */
#define NVIC_PreemptionPriority_EXTI15_10 (3)
#define NVIC_SubPriority_EXTI15_10 (3)

/* Main timer */
#define NVIC_PreemptionPriority_TIM2 (2)
#define NVIC_SubPriority_TIM2 (0)

/* Virtual hall sensor timer */
#define NVIC_PreemptionPriority_TIM4 (2)
#define NVIC_SubPriority_TIM4 (1)

/* USB */
#define NVIC_PreemptionPriority_USART2 (1)
#define NVIC_SubPriority_USART2 (0)

/* Bluetooth */
#define NVIC_PreemptionPriority_USART3 (1)
#define NVIC_SubPriority_USART3 (1)

typedef enum
{
  Right,
  Left
} JointTypeDef;

void MotionHandler(void);
void MotionEmergencyStop(void);
void UpdateInfo(void);

/**
 * @brief Initializing RCC.
 */
void RCC_Initialization(void);

/**
 * @brief Initializing limit switch.
 * @remark RCC_APB2: GPIOA
 */
void LimitSwitch_Initialization(void);

/**
 * @brief Initializing USART.
 * @remark RCC_APB1: USART2
 *         RCC_APB2: GPIOA
 */
void USART_Initialization(void);

/**
 * @brief Initializing timer.
 * @remark RCC_APB1: TIM2
 */
void Timer_Initialization(void);

/**
 * @brief Initializing board.
 * @remark RCC_APB2: GPIOA, GPIOC, AFIO
 */
void Board_Initialization(void);

/**
 * @brief Initializing joint.
 * @remark RCC_APB1: TIM3
 *         RCC_APB2: GPIOA, GPIOB, GPIOC, ADC1
 */
void Joint_Initialization(Joint *joint, JointTypeDef jointType);
void Joint_Initialization(JointWithoutHallSensor *joint, JointTypeDef jointType);

void StateTransporter(void);
void CommunicationDecoder(uint8_t command);

void Delay_NonTimer(__IO uint32_t nTime);

extern "C"
{
  void Delay_ms(__IO uint32_t nTime);
  void TimingDelay_Decrement(void);
}

#endif /* __MAIN_H */

/*********************************END OF FILE**********************************/
