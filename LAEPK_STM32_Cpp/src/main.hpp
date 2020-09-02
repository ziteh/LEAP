/**
 ******************************************************************************
 * @file    main.hpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
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

/* GPIO mapping */
#define RightMotor_DirectionPin ((GPIO_PortPinTypeDef)D10)
#define RightMotor_FunctionStatePin ((GPIO_PortPinTypeDef)D9)

/* Default PWM value */
#define PWM_DefaultFrequncy ((uint16_t)5000)
#define PWM_DefaultDutyCycle ((uint8_t)15)

/* Default Joint ADC value */
#define Joint_DefaultFullExtensionADCValue ((uint16_t)1400)
#define Joint_DefaultFullFlexionADCValue ((uint16_t)2450)

/* Default FSR start threshold */
#define Joint_DefaultExtensionFSRStartThreshold ((uint16_t)215)
#define Joint_DefaultFlexionFSRStartThreshold ((uint16_t)180)

/* Default FSR stop threshold */
#define Joint_DefaultExtensionFSRStopThreshold ((uint16_t)500)
#define Joint_DefaultFlexionFSRStopThreshold ((uint16_t)500)

void MotionHandler(void);
void CommunicationDecoder(uint8_t Command);
void Delay_NonTimer(__IO uint32_t nTime);

void Joint_Initialization(Joint *joint);
void LimitSwitch_Initialization(void);
void USART_Initialization(void);
void Timer_Initialization(void);
void Board_Initialization(void);

extern "C"
{
  void Delay_ms(__IO uint32_t nTime);
  void TimingDelay_Decrement(void);
}

#endif /* __MAIN_H */

/*********************************END OF FILE**********************************/
