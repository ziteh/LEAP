/**
 ******************************************************************************
 * @file    STM32F103RB_GPIO_Mapping.h
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    22-May-2020
 * @brief   Header for GPIO_Function.c module for STM32F103RB
 ******************************************************************************
 * @attention
 *
 * This file is used ONLY for STM32F103RB(STM32 Nucleo-64 board).
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F103RB_GPIO_MAPPING_H
#define __STM32F103RB_GPIO_MAPPING_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
    /* STM32 Pin(Morpho) */
  PA0 = 0 ,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
  PB0     ,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
  PC0     ,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
  PD0     ,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
  PE0     ,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,

  /* Arduino Pin */
  // Analog(CN8)
  A0 = PA0,
  A1 = PA1,
  A2 = PA4,
  A3 = PB0,
  A4 = PC1,   // PC1 or PB9, change by solder bridges.
  A5 = PC0,   // PC0 or PB8, change by solder bridges.

  // Digital(CN9)
  D0 = PA3,   // USART2_RX
  D1 = PA2,   // USART2_TX
  D2 = PA10,
  D3 = PB3,   // PWM
  D4 = PB5,
  D5 = PB4,   // PWM
  D6 = PB10,  // PWM
  D7 = PA8,

  // Digital(CN5)
  D8 = PA9,
  D9 = PC7,   // PWM
  D10 = PB6,  // PWM/CS
  D11 = PA7,  // PWM/MOSI
  D12 = PA6,  // MISO
  D13 = PA5,  // SCK
  D14 = PB9,  // SDA
  D15 = PB8,  // SCL

  /* STM32 Nucleo-64 board */
  B1 = PC13, // When push the button, the I/O is LOW value.
  LD2 = PA5, // the I/O is HIGH value, the LED is on; the I/O is LOW, the LED is off.
  User_Button = B1,
  User_LED = LD2
} GPIO_PortPinTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __STM32F103RB_GPIO_MAPPING_H */

/********************************END OF FILE***********************************/
