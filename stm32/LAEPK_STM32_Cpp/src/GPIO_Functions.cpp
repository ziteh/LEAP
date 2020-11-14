/**
 ******************************************************************************
 * @file    GPIO_Functions.cpp
 * @author  ZiTe (honmonoh@gmail.com)
 * @version V1.0
 * @date    14-November-2020
 * @brief   GPIO functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Functions.hpp"

/**
 * @brief Config a pin mode and speed.
 * @param PortPin:  select a pin to set.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @param Mode: Pin mode.
 * @param Speed: Pin speed.
 */
void GPIO_SetMode(GPIO_PortPinTypeDef PortPin,
                  GPIOMode_TypeDef Mode,
                  GPIOSpeed_TypeDef Speed)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Mode = Mode;
  GPIO_InitStructure.GPIO_Speed = Speed;
  GPIO_InitStructure.GPIO_Pin = GPIO_GetPin(PortPin);
  GPIO_Init(GPIO_GetPort(PortPin), &GPIO_InitStructure);
}
void GPIO_SetMode(GPIO_PortPinTypeDef PortPin,
                  GPIOMode_TypeDef Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // Input pin no need to set Speed.
  GPIO_InitStructure.GPIO_Mode = Mode;
  GPIO_InitStructure.GPIO_Pin = GPIO_GetPin(PortPin);
  GPIO_Init(GPIO_GetPort(PortPin), &GPIO_InitStructure);
}

/**
 * @brief Set a pin to High(1).
 * @param PortPin:  select a pin to set.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  None
 */
void GPIO_SetHigh(GPIO_PortPinTypeDef PortPin)
{
  GPIO_GetPort(PortPin)->BSRR |= GPIO_GetPin(PortPin);
}

/**
 * @brief Set a pin to Low(0).
 * @param PortPin:  select a pin to set.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  None
 */
void GPIO_SetLow(GPIO_PortPinTypeDef PortPin)
{
  GPIO_GetPort(PortPin)->BRR |= GPIO_GetPin(PortPin);
}

/**
 * @brief Toggle a pin from High(1) to Low(0) or from Low(0) to High(1).
 * @param PortPin:  select a pin to set.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  None
 */
void GPIO_SetToggle(GPIO_PortPinTypeDef PortPin)
{
  GPIO_GetPort(PortPin)->ODR ^= GPIO_GetPin(PortPin);
}

/**
 * @brief Set a pin to High(1) or Low(0).
 * @param PortPin:  select a pin to set.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @param Value:  select High(1) or Low(0) to set.
 *                This parameter should be HIGH or LOW
 * @return  None
 */
void GPIO_SetValue(GPIO_PortPinTypeDef PortPin, GPIO_ValueTypeDef Value)
{
  if (Value == HIGH)
    GPIO_SetHigh(PortPin);
  else if (Value == LOW)
    GPIO_SetLow(PortPin);
}

GPIO_ValueTypeDef GPIO_GetValue(GPIO_PortPinTypeDef PortPin)
{
  GPIO_ValueTypeDef PinInputValue;

  if ((GPIO_GetPort(PortPin)->IDR & GPIO_GetPin(PortPin)) != (uint32_t)Bit_RESET)
  {
    PinInputValue = HIGH;
  }
  else
  {
    PinInputValue = LOW;
  }
  return PinInputValue;
}

/**
 * @brief Read a input-pin value.
 * @param PortPin:  select a pin.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  The input-pin value
 */
GPIO_ValueTypeDef GPIO_GetInputValue(GPIO_PortPinTypeDef PortPin)
{
  GPIO_ValueTypeDef PinInputValue;

  if ((GPIO_GetPort(PortPin)->IDR & GPIO_GetPin(PortPin)) != (uint32_t)Bit_RESET)
  {
    PinInputValue = HIGH;
  }
  else
  {
    PinInputValue = LOW;
  }
  return PinInputValue;
}

/**
 * @brief Read a output-pin value.
 * @param PortPin:  select a pin
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  The output-pin value.
 */
GPIO_ValueTypeDef GPIO_GetOutputValue(GPIO_PortPinTypeDef PortPin)
{
  GPIO_ValueTypeDef PinOutputValue;

  if ((GPIO_GetPort(PortPin)->ODR & GPIO_GetPin(PortPin)) != (uint32_t)Bit_RESET)
  {
    PinOutputValue = HIGH;
  }
  else
  {
    PinOutputValue = LOW;
  }
  return PinOutputValue;
}

/**
 * @brief Get the port.
 * @param PortPin:  select a pin.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  The port.
 */
GPIO_TypeDef *GPIO_GetPort(GPIO_PortPinTypeDef PortPin)
{
  if ((PortPin >= PA0) && (PortPin <= PA15)) // Port-A:  0~15
    return GPIOA;
  else if ((PortPin >= PB0) && (PortPin <= PB15)) // Port-B: 16~31
    return GPIOB;
  else if ((PortPin >= PC0) && (PortPin <= PC15)) // Port-C: 32~47
    return GPIOC;
  else if ((PortPin >= PD0) && (PortPin <= PD15)) // Port-D: 48~63
    return GPIOD;
  else if ((PortPin >= PE0) && (PortPin <= PE15)) // Port-E: 64~79
    return GPIOE;
}

/**
 * @brief Get the pin.
 * @param PortPin:  select a pin.
 *                  This parameter should be: 0 ~ 79.
 *                   0~15:PA0~PA15; 16~31:PB0~PB15; 32~47:PC0~PC15;
 *                  48~63:PD0~PD15; 64~79:PE0~PE15
 * @return  The pin.
 */
uint16_t GPIO_GetPin(GPIO_PortPinTypeDef PortPin)
{
  uint8_t Offset = 0;

  if ((PortPin >= PA0) && (PortPin <= PA15)) // Port-A:  0~15
    Offset = PA0;
  else if ((PortPin >= PB0) && (PortPin <= PB15)) // Port-B: 16~31
    Offset = PB0;
  else if ((PortPin >= PC0) && (PortPin <= PC15)) // Port-C: 32~47
    Offset = PC0;
  else if ((PortPin >= PD0) && (PortPin <= PD15)) // Port-D: 48~63
    Offset = PD0;
  else if ((PortPin >= PE0) && (PortPin <= PE15)) // Port-E: 64~79
    Offset = PE0;

  return ((uint16_t)(0x0001 << (PortPin - Offset)));
}

/**
 * @brief   Convert uint8_t to GPIO_Value_TypeDef.
 * @param   value: The value in uint8_t. This parameter should be 0 or 1.
 * @return  The converted GPIO_Value_TypeDef value.
 */
GPIO_ValueTypeDef uint8_t_to_GPIO_Value_TypeDef(uint8_t Value)
{
  if (Value == 0)
    return ((GPIO_ValueTypeDef)LOW);
  else
    return ((GPIO_ValueTypeDef)HIGH);
}

/* class GPIO */
GPIO::GPIO(void)
{
  this->Mode = GPIO_Mode_IN_FLOATING;
  this->Speed = GPIO_Speed_2MHz;
}

GPIO::GPIO(GPIO_PortPinTypeDef NewPortPin)
{
  this->PortPin = NewPortPin;
  this->Mode = GPIO_Mode_IN_FLOATING;
  this->Speed = GPIO_Speed_2MHz;
}

void GPIO::Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = this->Mode;
  GPIO_InitStructure.GPIO_Speed = this->Speed;
  GPIO_InitStructure.GPIO_Pin = this->getPin();
  GPIO_Init(this->getPort(), &GPIO_InitStructure);
}

void GPIO::setValue(GPIO_ValueTypeDef NewValue)
{
  switch (NewValue)
  {
  case LOW:
    (this->getPort())->BRR |= (this->getPin()); // Set value LOW
    break;

  case HIGH:
  default:
    (this->getPort())->BSRR |= (this->getPin()); // Set value HIGH
    break;
  }
}

void GPIO::setValue(uint8_t NewValue)
{
  switch (NewValue)
  {
  case 0:
    (this->getPort())->BRR |= (this->getPin()); // Set value LOW
    break;

  case 1:
  default:
    (this->getPort())->BSRR |= (this->getPin()); // Set value HIGH
    break;
  }
}

void GPIO::toggleValue(void)
{
  (this->getPort())->ODR ^= (this->getPin());
}

// TODO Use register to replace function.
GPIO_ValueTypeDef GPIO::getValue(void)
{
  uint8_t value;

  switch (this->Mode)
  {
  case GPIO_Mode_AIN:
  case GPIO_Mode_IN_FLOATING:
  case GPIO_Mode_IPD:
  case GPIO_Mode_IPU:
    // This GPIO is input.
    value = GPIO_ReadInputDataBit(this->getPort(), this->getPin());
    break;

  case GPIO_Mode_Out_OD:
  case GPIO_Mode_Out_PP:
  case GPIO_Mode_AF_OD:
  case GPIO_Mode_AF_PP:
    // This GPIO is output.
    value = GPIO_ReadOutputDataBit(this->getPort(), this->getPin());
    break;
  }

  // Convert data type from uint8_t to GPIO_ValueTypeDef.
  if (value == 0)
    return ((GPIO_ValueTypeDef)LOW);
  else
    return ((GPIO_ValueTypeDef)HIGH);
}

GPIO_ValueTypeDef GPIO::getInputValue(void)
{
  GPIO_ValueTypeDef value;

  if (((this->getPort())->IDR & (this->getPin())) != (uint32_t)Bit_RESET)
  {
    value = HIGH;
  }
  else
  {
    value = LOW;
  }

  return value;
}

GPIO_ValueTypeDef GPIO::getOutputValue(void)
{
  GPIO_ValueTypeDef value;

  if (((this->getPort())->ODR & (this->getPin())) != (uint32_t)Bit_RESET)
  {
    value = HIGH;
  }
  else
  {
    value = LOW;
  }

  return value;
}

GPIO_TypeDef *GPIO::getPort(void)
{
  if (((uint8_t)this->PortPin) <= ((uint8_t)PA15)) // Port-A:  0~15
    return GPIOA;
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PB15)) // Port-B: 16~31
    return GPIOB;
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PC15)) // Port-C: 32~47
    return GPIOC;
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PD15)) // Port-D: 48~63
    return GPIOD;
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PE15)) // Port-E: 64~79
    return GPIOE;
}

uint16_t GPIO::getPin(void)
{
  uint8_t offset = 0;

  if (((uint8_t)this->PortPin) <= ((uint8_t)PA15)) // Port-A:  0~15
    offset = ((uint8_t)PA0);
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PB15)) // Port-B: 16~31
    offset = ((uint8_t)PB0);
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PC15)) // Port-C: 32~47
    offset = ((uint8_t)PC0);
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PD15)) // Port-D: 48~63
    offset = ((uint8_t)PD0);
  else if (((uint8_t)this->PortPin) <= ((uint8_t)PE15)) // Port-E: 64~79
    offset = ((uint8_t)PE0);

  return ((uint16_t)(0x0001 << (((uint8_t)this->PortPin) - offset)));
}

/********************************END OF FILE***********************************/
