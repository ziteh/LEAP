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
 * Reference from: 
 * [STM32F103x8, STM32F103xB] Datasheet-production data(DocID13587 Rev 17)
 * Table 5. Medium-density STM32F103xx pin definitions (page 28)
 * 
 * (9) This alternate function can be remapped by software to some other port
 * pins (if available on the used package). For more details, refer to the 
 * Alternate function I/O and debug configuration section in the STM32F10xxx
 * reference manual, available from the STMicroelectronics website: www.st.com.
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

  typedef enum
  {
    /* STM32 Pin(Morpho) */

    /**
     * Arduino Pin: A0  
     * Main function: PA0  
     * Alternate functions (Default): WKUP/USART2_CTS①/ADC12_IN0/TIM2_CH1_ETR(9)
     * Alternate functions (Remap): --
     * I/O Level : 3.3v
     */
    PA0 = 0,

    /**
     * Arduino Pin: A1
     * Main function: PA1  
     * Alternate functions (Default): USART2_RTS(9)/ADC12_IN1/TIM2_CH2(9)
     * Alternate functions (Remap): --
     * I/O Level : 3.3v
     */
    PA1,

    /**
     * Arduino Pin: D1 
     * Main function: PA2
     * Alternate functions (Default): USART2_TX(9)/ADC12_IN2/TIM2_CH3(9)
     * Alternate functions (Remap): --
     * I/O Level : 3.3v
     */
    PA2,

    /**
     * Arduino Pin: D0
     * Main function: PA3
     * Alternate functions (Default): USART2_RX(9)/ADC12_IN3/TIM2_CH4(9)
     * Alternate functions (Remap): --
     * I/O Level : 3.3v
     */
    PA3,

    /**
     * Arduino Pin: A2
     * Main function: PA4
     * Alternate functions (Default): SPI1_NSS(9)/USART2_CK(9)/ADC12_IN4
     * Alternate functions (Remap): --
     * I/O Level : 3.3v
     */
    PA4,

    /**
     * Arduino Pin: D13 (LD2, User-LED. When the I/O is HIGH/LOW, the LED is ON/OFF.)
     * Main function: PA5
     * Alternate functions (Default): SPI1_SCK(9)/ADC12_IN5
     * Alternate functions (Remap): --
     * I/O Level : 3.3v
     */
    PA5,

    /**
     * Arduino Pin: D12
     * Main function: PA6
     * Alternate functions (Default): SPI1_MISO(9)/ADC12_IN6/TIM3_CH1(9)
     * Alternate functions (Remap): TIM1_BKIN
     * I/O Level : 3.3v
     */
    PA6,

    /**
     * Arduino Pin: D11
     * Main function: PA7
     * Alternate functions (Default): SPI1_MOSI(9)/ADC12_IN7/TIM3_CH2(9)
     * Alternate functions (Remap): TIM1_CH1N
     * I/O Level : 3.3v
     */
    PA7,

    /**
     * Arduino Pin: D7
     * Main function: PA8
     * Alternate functions (Default): USART1_CK/TIM1_CH1(9)/MCO 
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PA8,

    /**
     * Arduino Pin: D8
     * Main function: PA9
     * Alternate functions (Default): USART1_TX(9)/TIM1_CH2(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PA9,

    /**
     * Arduino Pin: D2
     * Main function: PA10
     * Alternate functions (Default): USART1_RX(9)/TIM1_CH3(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PA10,

    /**
     * Arduino Pin: --
     * Main function: PA11
     * Alternate functions (Default): USART1_CTS/CANRX(9)/USBDM/TIM1_CH4(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PA11,

    /**
     * Arduino Pin: --
     * Main function: PA12
     * Alternate functions (Default): USART1_RTS/CANTX(9)/USBDPTIM1_ETR(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PA12,

    /**
     * Arduino Pin: --
     * Main function: JTMS/SWDIO
     * Alternate functions (Default): --
     * Alternate functions (Remap): PA13
     * I/O Level : 5v tolerant
     */
    PA13,

    /**
     * Arduino Pin: --
     * Main function: JTCK/SWCLK
     * Alternate functions (Default): --
     * Alternate functions (Remap): PA14
     * I/O Level : 5v tolerant
     */
    PA14,

    /**
     * Arduino Pin: --
     * Main function: JTDI
     * Alternate functions (Default): --
     * Alternate functions (Remap): TIM2_CH1_ETR/PA15/SPI1_NSS4
     * I/O Level : 5v tolerant
     */
    PA15,
    PB0,
    PB1,
    PB2,
    PB3,
    PB4,
    PB5,
    PB6,
    PB7,
    PB8,
    PB9,
    PB10,
    PB11,
    PB12,
    PB13,
    PB14,
    PB15,
    PC0,
    PC1,
    PC2,
    PC3,
    PC4,
    PC5,
    PC6,
    PC7,
    PC8,
    PC9,
    PC10,
    PC11,
    PC12,
    PC13,
    PC14,
    PC15,
    PD0,
    PD1,
    PD2,
    PD3,
    PD4,
    PD5,
    PD6,
    PD7,
    PD8,
    PD9,
    PD10,
    PD11,
    PD12,
    PD13,
    PD14,
    PD15,
    PE0,
    PE1,
    PE2,
    PE3,
    PE4,
    PE5,
    PE6,
    PE7,
    PE8,
    PE9,
    PE10,
    PE11,
    PE12,
    PE13,
    PE14,
    PE15,

    /* Arduino Pin */


    // Analog(CN8)
    A0 = PA0,
    A1 = PA1,
    A2 = PA4,
    A3 = PB0,
    A4 = PC1, // PC1 or PB9, change by solder bridges.
    A5 = PC0, // PC0 or PB8, change by solder bridges.

    // Digital(CN9)
    D0 = PA3, // USART2_RX
    D1 = PA2, // USART2_TX
    D2 = PA10,
    D3 = PB3, // PWM
    D4 = PB5,
    D5 = PB4,  // PWM
    D6 = PB10, // PWM
    D7 = PA8,

    // Digital(CN5)
    D8 = PA9,
    D9 = PC7,  // PWM
    D10 = PB6, // PWM/CS
    D11 = PA7, // PWM/MOSI
    D12 = PA6, // MISO
    D13 = PA5, // SCK
    D14 = PB9, // SDA
    D15 = PB8, // SCL

    /* STM32 Nucleo-64 board */
    B1 = PC13, // When push the button, the I/O is LOW value.
    LD2 = PA5, // the I/O is HIGH value, the LED is on; the I/O is LOW, the LED is off.
    User_Button = B1,
    User_LED = LD2
  } GPIO_PortPinTypeDef;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __STM32F103RB_GPIO_MAPPING_H */

/********************************END OF FILE***********************************/
