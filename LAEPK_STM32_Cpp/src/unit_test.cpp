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

// using namespace UnitTest;

/**
 * @brief GPIO-PA10(D2) will output HIGH.
 */
void GPIO_PA10_Output_HIGH(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO pin;
  pin.PortPin = PA10;
  pin.Mode = GPIO_Mode_Out_PP;
  pin.Speed = GPIO_Speed_2MHz;
  pin.Init();

  pin.setValue(HIGH);
}

/**
 * @brief When user-button(B1) push user-LED(LD2) will off, else user-LED will on.
 */
void GPIO_UserButton_Input_UserLED_Output(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                             RCC_APB2Periph_GPIOC,
                         ENABLE);

  GPIO button;
  button.PortPin = User_Button;
  button.Mode = GPIO_Mode_IN_FLOATING;
  button.Init();

  GPIO LED;
  LED.PortPin = User_LED;
  LED.Mode = GPIO_Mode_Out_PP;
  LED.Speed = GPIO_Speed_2MHz;
  LED.Init();

  while (1)
  {
    if (button.getValue() == HIGH)
      LED.setValue(HIGH);
    else
      LED.setValue(LOW);
  }
}

/********************************END OF FILE***********************************/
