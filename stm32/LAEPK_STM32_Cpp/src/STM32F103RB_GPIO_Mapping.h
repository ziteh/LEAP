/**
 ******************************************************************************
 * @file    STM32F103RB_GPIO_Mapping.h
 * @author  ZiTe (honmonoh@gmail.com)
 * @version V1.0
 * @date    14-November-2020
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

    /**
     * Arduino Pin: A3
     * Main function: PB0
     * Alternate functions (Default): ADC12_IN8/TIM3_CH3(9)
     * Alternate functions (Remap): TIM1_CH2N
     * I/O Level : 3.3v
     */
    PB0,

    /**
     * Arduino Pin: --
     * Main function: PB1
     * Alternate functions (Default): ADC12_IN9/TIM3_CH4(9)
     * Alternate functions (Remap): TIM1_CH4N
     * I/O Level : 3.3v
     */
    PB1,

    /**
     * Arduino Pin: --
     * Main function: PB1/BOOT1
     * Alternate functions (Default): --
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PB2,

    /**
     * Arduino Pin: D3
     * Main function: JTDO
     * Alternate functions (Default): --
     * Alternate functions (Remap): TIM2_CH2/PB3/TRACESWO/SPI1_SCK
     * I/O Level : 5v tolerant
     */
    PB3,

    /**
     * Arduino Pin: D5
     * Main function: JNTRST
     * Alternate functions (Default): --
     * Alternate functions (Remap): TIM3_CH1/PB4/SPI1_MISO
     * I/O Level : 5v tolerant
     */
    PB4,

    /**
     * Arduino Pin: D4
     * Main function: PB5
     * Alternate functions (Default): I2C1_SMBAl
     * Alternate functions (Remap): TIM3_CH2/SPI1_MOSI
     * I/O Level : 3.3v(?)
     */
    PB5,

    /**
     * Arduino Pin: D10
     * Main function: PB6
     * Alternate functions (Default): I2C1_SCL(9)/TIM4_CH1(9)
     * Alternate functions (Remap): USART1_TX
     * I/O Level : 5v tolerant
     */
    PB6,

    /**
     * Arduino Pin: --
     * Main function: PB7
     * Alternate functions (Default): I2C1_SDA(9)/TIM4_CH2(9)
     * Alternate functions (Remap): USART1_RX
     * I/O Level : 5v tolerant
     */
    PB7,

    /**
     * Arduino Pin: D15
     * Main function: PB8
     * Alternate functions (Default): TIM4_CH3(9)
     * Alternate functions (Remap): I2C1_SCL/CANRX
     * I/O Level : 5v tolerant
     */
    PB8,

    /**
     * Arduino Pin: D14
     * Main function: PB9
     * Alternate functions (Default): TIM4_CH4(9)
     * Alternate functions (Remap): I2C1_SDA/CANTX
     * I/O Level : 5v tolerant
     */
    PB9,

    /**
     * Arduino Pin: D6
     * Main function: PB10
     * Alternate functions (Default): I2C2_SCL/USART3_TX(9)
     * Alternate functions (Remap): TIM2_CH3
     * I/O Level : 5v tolerant
     */
    PB10,

    /**
     * Arduino Pin: --
     * Main function: PB11
     * Alternate functions (Default): I2C2_SDA/USART3_RX(9)
     * Alternate functions (Remap): TIM2_CH4
     * I/O Level : 5v tolerant
     */
    PB11,

    /**
     * Arduino Pin: --
     * Main function: PB12
     * Alternate functions (Default): SPI2_NSS/I2C2_SMBAl/USART3_CK(9)/TIM1_BKIN(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PB12,

    /**
     * Arduino Pin: --
     * Main function: PB13
     * Alternate functions (Default): SPI2_SCK/USART3_CTS(9)/TIM1_CH1N(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PB13,

    /**
     * Arduino Pin: --
     * Main function: PB14
     * Alternate functions (Default): SPI2_MISO/USART3_RTS(9)/TIM1_CH2N(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
    PB14,

    /**
     * Arduino Pin: --
     * Main function: PB15
     * Alternate functions (Default): SPI2_MOSI/TIM1_CH3N(9)
     * Alternate functions (Remap): --
     * I/O Level : 5v tolerant
     */
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
