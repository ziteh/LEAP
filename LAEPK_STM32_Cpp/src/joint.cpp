/**
 ******************************************************************************
 * @file    joint.cpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Program body of L.A.E.P.K. of joint.
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "joint.hpp"

// Joint::LimitStateTypeDef Joint::MotionExtension(void)
// {
//   /*
//    * If FSR-Start-Extension is triggered,
//    * and knee joint didn't exceed the Full-Extension angle limit,
//    * then start extension.
//    */
//   if (StartExtensionIsTriggered() && (Joint_GetLimitState() != FullExtension))
//   {
//     USART_Send(USART2, "Start Ext\r\n");

//     GPIO_SetValue(RightMotor_DirectionPin, HIGH);     // CW(0) = Flexion; CCW(1) = Extension
//     GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
//     PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

//     /*
//      * Wait until FSR-Stop-Extension is triggered
//      * or knee joint exceed the Full-Extension angle limit
//      */
//     while (!(StopExtensionIsTriggered() || (Joint_GetLimitState() == FullExtension)))
//     {
//     }

//     USART_Send(USART2, "Stop Ext\r\n");
//     GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
//     PWM_SetDutyCycle(TIM3, CH2, 0);
//   }
// }

// Joint::LimitStateTypeDef Joint::MotionFlexion(void)
// {

// }

// void Joint_SetAbsoluteAngle(float TargetAngle)
// {
//   float NowAngle = Joint_GetAbsoluteAngle();

//   GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
//   PWM_SetDutyCycle(TIM3, CH2, 0);

//   /* Extension */
//   if ((NowAngle > TargetAngle) && (NowAngle > Convert_ADCValueToAngle(Joint_FullExtensionADCValue)))
//   {
//     GPIO_SetValue(RightMotor_DirectionPin, HIGH);     // CW(0) = Flexion; CCW(1) = Extension
//     GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
//     PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

//     while ((NowAngle > TargetAngle) && (NowAngle > Convert_ADCValueToAngle(Joint_FullExtensionADCValue)))
//     {
//       NowAngle = Joint_GetAbsoluteAngle(); // Update angle.
//       USART_Send(USART2,
//                  convertIntToString(
//                      round(Convert_ADCValueToAngle(ADC_GetValue(ADC1, ADC_Channel_1, 1,
//                                                                 ADC_SampleTime_55Cycles5)))));
//       USART_Send(USART2, "\r\n");
//     }

//     GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
//     PWM_SetDutyCycle(TIM3, CH2, 0);
//   }
//   /* Flexion */
//   else if ((NowAngle < TargetAngle) && (NowAngle < Convert_ADCValueToAngle(Joint_FullFlexionADCValue)))
//   {
//     GPIO_SetValue(RightMotor_DirectionPin, LOW);      // CW(0) = Flexion; CCW(1) = Extension
//     GPIO_SetValue(RightMotor_FunctionStatePin, HIGH); // LOW(0) = Disable; HIGH(1) = Enbale
//     PWM_SetDutyCycle(TIM3, CH2, PWM_DefaultDutyCycle);

//     while ((NowAngle < TargetAngle) && (NowAngle < Convert_ADCValueToAngle(Joint_FullFlexionADCValue)))
//     {
//       NowAngle = Joint_GetAbsoluteAngle(); // Update angle.
//       USART_Send(USART2,
//                  convertIntToString(
//                      round(Convert_ADCValueToAngle(ADC_GetValue(ADC1, ADC_Channel_1, 1,
//                                                                 ADC_SampleTime_55Cycles5)))));
//       USART_Send(USART2, "\r\n");
//     }

//     GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // LOW(0) = Disable; HIGH(1) = Enbale
//     PWM_SetDutyCycle(TIM3, CH2, 0);
//   }
// }

// inline float Joint_GetAbsoluteAngle(void)
// {
//   uint16_t ADC_Value = ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
//   return Convert_ADCValueToAngle(ADC_Value);
// }

// inline Joint_LimitStateTypeDef Joint_GetLimitState(void)
// {
//   if (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5) <= Joint_FullExtensionADCValue)
//     return ((Joint_LimitStateTypeDef)FullExtension);
//   else if (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5) >= Joint_FullFlexionADCValue)
//     return ((Joint_LimitStateTypeDef)FullFlexion);
//   else
//     return ((Joint_LimitStateTypeDef)Unlimited);
// }

/*********************************END OF FILE**********************************/
