/**
 ******************************************************************************
 * @file    GPIO_Functions.hpp
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    08-October-2019
 * @brief   Header for GPIO_Function.c module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __GPIO_FUNCTIONS_H
#define __GPIO_FUNCTIONS_H

extern "C"
{
#include "stm32f10x.h"
#include "STM32F103RB_GPIO_Mapping.h"
}

typedef enum
{
  LOW = 0,
  HIGH = !LOW
} GPIO_ValueTypeDef;

void GPIO_SetMode(GPIO_PortPinTypeDef PortPin,
                  GPIOMode_TypeDef Mode,
                  GPIOSpeed_TypeDef Speed);
void GPIO_SetMode(GPIO_PortPinTypeDef PortPin,
                  GPIOMode_TypeDef Mode);

void GPIO_SetHigh(GPIO_PortPinTypeDef PortPin);
void GPIO_SetLow(GPIO_PortPinTypeDef PortPin);
void GPIO_SetToggle(GPIO_PortPinTypeDef PortPin);
void GPIO_SetValue(GPIO_PortPinTypeDef PortPin, GPIO_ValueTypeDef Value);

GPIO_ValueTypeDef GPIO_GetValue(GPIO_PortPinTypeDef PortPin);
GPIO_ValueTypeDef GPIO_GetInputValue(GPIO_PortPinTypeDef PortPin);
GPIO_ValueTypeDef GPIO_GetOutputValue(GPIO_PortPinTypeDef PortPin);

GPIO_TypeDef *GPIO_GetPort(GPIO_PortPinTypeDef PortPin);
uint16_t GPIO_GetPin(GPIO_PortPinTypeDef PortPin);

GPIO_ValueTypeDef uint8_t_to_GPIO_Value_TypeDef(uint8_t Value);

class GPIO
{
public:
  GPIO_PortPinTypeDef PortPin;
  GPIOMode_TypeDef Mode;
  GPIOSpeed_TypeDef Speed;

  GPIO(void);
  GPIO(GPIO_PortPinTypeDef NewPortPin);
  void Init(void);

  void setValue(GPIO_ValueTypeDef NewValue);
  void setValue(uint8_t NewValue);
  void toggleValue(void);

  GPIO_ValueTypeDef getValue(void);
  GPIO_ValueTypeDef getInputValue(void);
  GPIO_ValueTypeDef getOutputValue(void);

private:
  GPIO_TypeDef *getPort(void);
  uint16_t getPin(void);
};

#endif /* __GPIO_FUNCTIONS_H */

/********************************END OF FILE***********************************/
