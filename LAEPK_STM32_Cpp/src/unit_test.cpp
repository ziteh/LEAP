/**
 ******************************************************************************
 * @file    unit_test.cpp
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
 * @brief   Main program body of unit-test.
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "unit_test.hpp"

using namespace UnitTest;

/**
 * @brief GPIO-PA3(D0) will output HIGH.
 */
void GPIO_PA3_Output_HIGH(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO pin;
  pin.PortPin = PA3;
  pin.Mode = GPIO_Mode_Out_PP;
  pin.Speed = GPIO_Speed_2MHz;
  pin.Init();

  pin.setValue(HIGH);
}

/********************************END OF FILE***********************************/