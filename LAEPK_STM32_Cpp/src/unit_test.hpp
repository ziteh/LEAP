/**
 ******************************************************************************
 * @file    unit_test.hpp
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Header for unit_test.cpp module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __UNIT_TEST_HPP
#define __UNIT_TEST_HPP

#include "main.hpp"
#include "convert.hpp"

namespace UnitTest
{
  void GPIO_PA10_Output_HIGH(void);
  void GPIO_UserButton_Input_UserLED_Output(void);
  void USART_Send_Data(void);
  void ADC_Read_Analog_value(void);
  void PWM_Output_1kHz_50DutyCycle(void);
} // namespace UnitTest

#endif /* __UNIT_TEST_HPP */

/********************************END OF FILE***********************************/
