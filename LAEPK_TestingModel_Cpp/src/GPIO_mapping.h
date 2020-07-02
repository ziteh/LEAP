/**
 ******************************************************************************
 * @file    GPIO_mapping.h
 * @author  Huang Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    08-October-2019
 * @brief   Header for GPIO_Function.c module for STM32F103RB
 ******************************************************************************
 * @attention
 *
 * This file is used ONLY for STM32F103RB(STM32 Nucleo-64 board).
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_MAPPING_H
#define __GPIO_MAPPING_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* STM32 Pin(Morpho) */
/*
 * Default=Alternate functions Default
 * MA=Main function(after reset)
 * Remap=Alternate functions Remap
 */

typedef enum {
    PA0 = 0 ,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
    PB0     ,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
    PC0     ,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
    PD0     ,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
    PE0     ,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,

} GPIO_PortPin;

// Port-A
#define PA0   (0)   // WKUP/USART2_CTS/ADC12_IN0/TIM2_CH1_ETR
#define PA1   (1)   // USART2_RTS/ADC12_IN1/TIM2_CH2
#define PA2   (2)   // USART2_TX/ADC12_IN2/TIM2_CH3
#define PA3   (3)   // USART2_RX/ADC12_IN3/TIM2_CH4
#define PA4   (4)   // SPI1_NSS/USART2_CK/ADC12_IN4
#define PA5   (5)   // SPI1_SCK/ADC12_IN5
#define PA6   (6)   // SPI1_MISO/ADC12_IN6/TIM3_CH1;Remap:TIM1_BKIN
#define PA7   (7)   // SPI1_MOSI/ADC12_IN7/TIM3_CH2;Remap:TIM1_CH1N
#define PA8   (8)   // USART1_CK/TIM1_CH1/MCO
#define PA9   (9)   // USART1_TX/TIM1_CH2
#define PA10  (10)  // USART1_RX/TIM1_CH3
#define PA11  (11)  // USART1_CTS/CANRX/USBDM/TIM1_CH4
#define PA12  (12)  // USART1_RTS/CANTX/USBDP/TIM1_ETR
#define PA13  (13)  // MA:JTMS/SWDIO;Remap:PA13
#define PA14  (14)  // MA:JTCK/SWCLK;Remap:PA14
#define PA15  (15)  // MA:JTDI;Remap:TIM2_CH1_ETR/ PA15/SPI1_NSS

// Port-B
#define PB0   (16)  // ADC12_IN8/TIM3_CH3;Remap:TIM1_CH2N
#define PB1   (17)  // ADC12_IN9/TIM3_CH4;Remap:TIM1_CH3N
#define PB2   (18)  // MA:PB2/BOOT1
#define PB3   (19)  // MA:JTDO;Remap:TIM2_CH2/PB3/TRACESWO/SPI1_SCK
#define PB4   (20)  // MA:JNTRST;Remap:TIM3_CH1/PB4/SPI1_MISO
#define PB5   (21)  // I2C1_SMBAl;Remap:TIM3_CH2/SPI1_MOSI
#define PB6   (22)  // I2C1_SCL/TIM4_CH1;Remap:USART1_TX
#define PB7   (23)  // I2C1_SDA/TIM4_CH2;Remap:USART1_RX
#define PB8   (24)  // TIM4_CH3;Remap:I2C1_SCL/CANRX
#define PB9   (25)  // TIM4_CH4;Remap:I2C1_SDA/CANTX
#define PB10  (26)  // I2C2_SCL/USART3_TX;Remap:TIM2_CH3
#define PB11  (27)  // I2C2_SDA/USART3_RX;Remap:TIM2_CH4
#define PB12  (28)  // SPI2_NSS/I2C2_SMBAl/USART3_CK/TIM1_BKIN
#define PB13  (29)  // SPI2_SCK/USART3_CTS/TIM1_CH1N
#define PB14  (30)  // SPI2_MISO/USART3_RTS/TIM1_CH2N
#define PB15  (31)  // SPI2_MOSI/TIM1_CH3N

// Port-C
#define PC0   (32)  //
#define PC1   (33)  //
#define PC2   (34)  //
#define PC3   (35)  //
#define PC4   (36)  //
#define PC5   (37)  //
#define PC6   (38)  //
#define PC7   (39)  //
#define PC8   (40)  //
#define PC9   (41)  //
#define PC10  (42)  //
#define PC11  (43)  //
#define PC12  (44)  //
#define PC13  (45)  //
#define PC14  (46)  //
#define PC15  (47)  //

// Port-D
#define PD0   (48)  //
#define PD1   (49)  //
#define PD2   (50)  //
#define PD3   (51)  //
#define PD4   (52)  //
#define PD5   (53)  //
#define PD6   (54)  //
#define PD7   (55)  //
#define PD8   (56)  //
#define PD9   (57)  //
#define PD10  (58)  //
#define PD11  (59)  //
#define PD12  (60)  //
#define PD13  (61)  //
#define PD14  (62)  //
#define PD15  (63)  //

// Port-E
#define PE0   (64)  //
#define PE1   (65)  //
#define PE2   (66)  //
#define PE3   (67)  //
#define PE4   (68)  //
#define PE5   (69)  //
#define PE6   (70)  //
#define PE7   (71)  //
#define PE8   (72)  //
#define PE9   (73)  //
#define PE10  (74)  //
#define PE11  (75)  //
#define PE12  (76)  //
#define PE13  (77)  //
#define PE14  (78)  //
#define PE15  (79)  //

/* Arduino Pin */
// Analog(CN8)
#define A0    (0)   // PA0
#define A1    (1)   // PA1
#define A2    (4)   // PA4
#define A3    (16)  // PB0
#define A4    (33)  // PC1(or PB9,change by solder bridges)
#define A5    (32)  // PC0(or PB8,change by solder bridges)

// Digital(CN9)
#define D0    (3)   // PA3(USART2_RX)
#define D1    (2)   // PA2(USART2_TX)
#define D2    (10)  // PA10
#define D3    (19)  // PB3(PWM)
#define D4    (21)  // PB5
#define D5    (20)  // PB4(PWM)
#define D6    (26)  // PB10(PWM)
#define D7    (8)   // PA8

// Digital(CN5)
#define D8    (9)   // PA9
#define D9    (39)  // PC7(PWM)
#define D10   (22)  // PB6(PWM/CS)
#define D11   (7)   // PA7(PWM/MOSI)
#define D12   (6)   // PA6(MISO)
#define D13   (5)   // PA5(SCK)
#define D14   (25)  // PB9(SDA)
#define D15   (24)  // PB8(SCL)

/* STM32 Nucleo-64 board */
#define Button_User (45)  // PC13. B1. When push the button, the I/O is LOW value.
#define B1          (45)
#define LED_User    (5)   // PA5. LD2. When the I/O is HIGH value, the LED is on.
#define LD2         (5)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __GPIO_MAPPING_H */

/********************************END OF FILE***********************************/
