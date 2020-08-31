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
#define Joint_DefaultExtensionFSRStartThreshold ((uint8_t)215)
#define Joint_DefaultFlexionFSRStartThreshold ((uint8_t)180)

/* Default FSR stop threshold */
#define Joint_DefaultExtensionFSRStopThreshold ((uint16_t)500)
#define Joint_DefaultFlexionFSRStopThreshold ((uint16_t)500)


bool StartExtensionIsTriggered(void);
bool StartFlexionIsTriggered(void);
bool StopExtensionIsTriggered(void);
bool StopFlexionIsTriggered(void);

float Convert_ADCValueToAngle(uint16_t ADCValue);
uint8_t Convert_DegPerSecToPWMDutyCycle(float DegPerSec);

void CommunicationDecoder(uint8_t Command);

void GPIO_Initialization(void);
void NVIC_Initialization(void);
void USART_Initialization(void);
void ADC_Initialization(void);
void PWM_Initialization(void);
void EXIT_Initialization(void);
void Timer_Initialization(void);

char *convertIntToString(int Number);
//std::string convertFloatToString(float FloatNumber); /* ERROE: region `flash' overflowed */
void Delay_NonTimer(__IO uint32_t nTime);

extern "C"
{
  void Delay_ms(__IO uint32_t nTime);
  void TimingDelay_Decrement(void);
}

//void Joint_setAngularSpeed(uint8_t NewAngularSpeed);
//void Joint_setAngularAcceleration(uint8_t NewAngularAcceleration);
//
//void Joint_setAbsoluteAngle(float TargetAngle);
//void Joint_setAbsoluteAngle(Joint_LimitStateTypeDef TargetPosition);
//void Joint_setRelativelyAngle(Joint_DirectionTypeDef Direction,
//    float IncreaseAngle);
//
//float Joint_getAbsoluteAngle(void);
//
//float Joint_convertADCValueToAngle(uint16_t ADCValue);
//Joint_LimitStateTypeDef Joint_getLimitState(void);

#endif /* __MAIN_H */

/*********************************END OF FILE**********************************/
