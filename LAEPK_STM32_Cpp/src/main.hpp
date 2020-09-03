/**
 ******************************************************************************
 * @file    main.hpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    25-October-2019
 * @brief   Header for main.cpp module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <sstream>
#include <cmath>
#include "GPIO_Functions.hpp"
#include "PWM_Functions.hpp"
#include "USART_Functions.hpp"
#include "ADC_Functions.hpp"
#include "EC90fl_Motor_Functions.hpp"
#include "joint.hpp"
#include "unit_test.hpp"

extern "C"
{
#include <stdio.h>
#include "stm32f10x.h"
}

/* Right leg define */
#define RightJoint_PortPin_SpeedPWM ((GPIO_PortPinTypeDef)PA7)
#define RightJoint_Timer_SpeedPWM (TIM3)
#define RightJoint_Channel_SpeedPWM (CH2)

#define RightJoint_PortPin_FunctionState ((GPIO_PortPinTypeDef)PB6)
#define RightJoint_PortPin_Direction ((GPIO_PortPinTypeDef)PC7)
#define RightJoint_PortPin_ReadyState ((GPIO_PortPinTypeDef)PA9)

#define RightJoint_PortPin_AnglePOT ((GPIO_PortPinTypeDef)PA1)
#define RightJoint_ADCx_AnglePOT (ADC1)
#define RightJoint_ADC_Channel_AnglePOT (ADC_Channel_1)

#define RightJoint_PortPin_FrontFSR ((GPIO_PortPinTypeDef)PA4)
#define RightJoint_ADCx_FrontFSR (ADC1)
#define RightJoint_ADC_Channel_FrontFSR (ADC_Channel_4)

#define RightJoint_PortPin_BackFSR ((GPIO_PortPinTypeDef)PB0)
#define RightJoint_ADCx_BackFSR (ADC1)
#define RightJoint_ADC_Channel_BackFSR (ADC_Channel_8)

#define RightJoint_DefaultValue_POTFullExtension ((uint16_t)1400)
#define RightJoint_DefaultValue_POTFullFlexion ((uint16_t)2450)

#define RightJoint_DefaultValue_FSRStartExtension ((uint16_t)215)
#define RightJoint_DefaultValue_FSRStartFlexion ((uint16_t)180)

#define RightJoint_DefaultValue_FSRStopExtension ((uint16_t)500)
#define RightJoint_DefaultValue_FSRStopFlexion ((uint16_t)500)

/* Left leg define */
#define LeftJoint_PortPin_SpeedPWM ((GPIO_PortPinTypeDef)PA7)
#define LeftJoint_Timer_SpeedPWM (TIM4)
#define LeftJoint_Channel_SpeedPWM (CH1)

#define LeftJoint_PortPin_FunctionState ((GPIO_PortPinTypeDef)PA8)
#define LeftJoint_PortPin_Direction ((GPIO_PortPinTypeDef)PC7)
#define LeftJoint_PortPin_ReadyState ((GPIO_PortPinTypeDef)PA9)

#define LeftJoint_PortPin_AnglePOT ((GPIO_PortPinTypeDef)PC3)
#define LeftJoint_ADCx_AnglePOT (ADC1)
#define LeftJoint_ADC_Channel_AnglePOT (ADC_Channel_13)

#define LeftJoint_PortPin_FrontFSR ((GPIO_PortPinTypeDef)PC1)
#define LeftJoint_ADCx_FrontFSR (ADC1)
#define LeftJoint_ADC_Channel_FrontFSR (ADC_Channel_11)

#define LeftJoint_PortPin_BackFSR ((GPIO_PortPinTypeDef)PC0)
#define LeftJoint_ADCx_BackFSR (ADC1)
#define LeftJoint_ADC_Channel_BackFSR (ADC_Channel_10)

#define LeftJoint_DefaultValue_POTFullExtension ((uint16_t)1400)
#define LeftJoint_DefaultValue_POTFullFlexion ((uint16_t)2450)

#define LeftJoint_DefaultValue_FSRStartExtension ((uint16_t)215)
#define LeftJoint_DefaultValue_FSRStartFlexion ((uint16_t)180)

#define LeftJoint_DefaultValue_FSRStopExtension ((uint16_t)500)
#define LeftJoint_DefaultValue_FSRStopFlexion ((uint16_t)500)

#define LeftJoint_PortPin_VirtualHall1 ((GPIO_PortPinTypeDef)PA6)
#define LeftJoint_PortPin_VirtualHall2 ((GPIO_PortPinTypeDef)PB9)
#define LeftJoint_PortPin_VirtualHall3 ((GPIO_PortPinTypeDef)PB8)

/**
 * @brief Initializing RCC.
 */
#define RCC_Initialization                            \
  {                                                   \
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 |    \
                               RCC_APB1Periph_TIM2 |  \
                               RCC_APB1Periph_TIM3,   \
                           ENABLE);                   \
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |     \
                               RCC_APB2Periph_GPIOB | \
                               RCC_APB2Periph_GPIOC | \
                               RCC_APB2Periph_ADC1,   \
                           ENABLE);                   \
  }

/**
 * @brief Initializing limit switch.
 * @remark RCC_APB2: GPIOA
 */
#define LimitSwitch_Initialization                              \
  {                                                             \
    GPIO limitSwitch;                                           \
    limitSwitch.PortPin = PA0;                                  \
    limitSwitch.Mode = GPIO_Mode_IPD;                           \
    limitSwitch.Init();                                         \
                                                                \
    NVIC_InitTypeDef NVIC_InitStructure;                        \
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;            \
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   \
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          \
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             \
    NVIC_Init(&NVIC_InitStructure);                             \
                                                                \
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); \
                                                                \
    EXTI_InitTypeDef EXTI_InitStructure;                        \
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;                  \
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         \
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     \
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   \
    EXTI_Init(&EXTI_InitStructure);                             \
  }

/**
 * @brief Initializing USART.
 * @remark RCC_APB1: USART2
 *         RCC_APB2: GPIOA
 */
#define USART_Initialization                                                        \
  {                                                                                 \
    GPIO USART2_TX;                                                                 \
    USART2_TX.PortPin = PA2;                                                        \
    USART2_TX.Mode = GPIO_Mode_AF_PP;                                               \
    USART2_TX.Speed = GPIO_Speed_50MHz;                                             \
    USART2_TX.Init();                                                               \
                                                                                    \
    GPIO USART2_RX;                                                                 \
    USART2_RX.PortPin = PA3;                                                        \
    USART2_RX.Mode = GPIO_Mode_IN_FLOATING;                                         \
    USART2_RX.Init();                                                               \
                                                                                    \
    NVIC_InitTypeDef NVIC_InitStructure;                                            \
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                               \
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                       \
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                              \
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                 \
    NVIC_Init(&NVIC_InitStructure);                                                 \
                                                                                    \
    USART_InitTypeDef USART_InitStructure;                                          \
    USART_StructInit(&USART_InitStructure);                                         \
    USART_InitStructure.USART_BaudRate = 9600;                                      \
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     \
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          \
    USART_InitStructure.USART_Parity = USART_Parity_No;                             \
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; \
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 \
    USART_Init(USART2, &USART_InitStructure);                                       \
                                                                                    \
    /* Enable "Receive data register not empty" interrupt */                        \
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                                  \
                                                                                    \
    /* Enable USART */                                                              \
    USART_Cmd(USART2, ENABLE);                                                      \
                                                                                    \
    /* Clear "Transmission Complete" flag, else the first bit of data will lose. */ \
    USART_ClearFlag(USART2, USART_FLAG_TC);                                         \
  }

/**
 * @brief Initializing timer.
 * @remark RCC_APB1: TIM2
 */
#define Timer_Initialization                                    \
  {                                                             \
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;              \
    TIM_TimeBaseStructure.TIM_Period = 2000;                    \
    TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1;             \
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     \
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; \
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             \
                                                                \
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);                       \
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                  \
    TIM_Cmd(TIM2, ENABLE);                                      \
                                                                \
    NVIC_InitTypeDef NVIC_InitStructure;                        \
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             \
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   \
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          \
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             \
    NVIC_Init(&NVIC_InitStructure);                             \
  }

/**
 * @brief Initializing board.
 * @remark RCC_APB2: GPIOA, GPIOC
 */
#define Board_Initialization             \
  {                                      \
    GPIO Button;                         \
    Button.PortPin = User_Button;        \
    Button.Mode = GPIO_Mode_IN_FLOATING; \
    Button.Init();                       \
                                         \
    GPIO LED;                            \
    LED.PortPin = User_LED;              \
    LED.Mode = GPIO_Mode_Out_PP;         \
    LED.Speed = GPIO_Speed_2MHz;         \
    LED.Init();                          \
    LED.setValue(LOW);                   \
  }

typedef enum
{
  Right,
  Left
} JointTypeDef;

void MotionHandler(void);
void CommunicationDecoder(uint8_t Command);
void Delay_NonTimer(__IO uint32_t nTime);

/**
 * @brief Initializing joint.
 * @remark RCC_APB1: TIM3
 *         RCC_APB2: GPIOA, GPIOB, GPIOC, ADC1
 */
void Joint_Initialization(Joint *joint, JointTypeDef jointType);
void Joint_Initialization(JointWithoutHallSensor *joint, JointTypeDef jointType);

extern "C"
{
  void Delay_ms(__IO uint32_t nTime);
  void TimingDelay_Decrement(void);
}

#endif /* __MAIN_H */

/*********************************END OF FILE**********************************/
