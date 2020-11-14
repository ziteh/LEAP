/**
 ******************************************************************************
 * @file    stm32f1xx_it.hpp
 * @author  ZiTe (honmonoh@gmail.com)
 * @version V1.0
 * @date    14-November-2020
 * @brief   This file contains the headers of the interrupt handlers.
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1XX_IT_H
#define __STM32F1XX_IT_H

/* Includes ------------------------------------------------------------------*/
#include <string>
#include "main.hpp"

#ifdef __cplusplus
extern "C"
{

#include "stm32f10x.h"
#endif

  void NMI_Handler(void);
  void HardFault_Handler(void);
  void MemManage_Handler(void);
  void BusFault_Handler(void);
  void UsageFault_Handler(void);
  void SVC_Handler(void);
  void DebugMon_Handler(void);
  void PendSV_Handler(void);
  void SysTick_Handler(void);

  void TIM2_IRQHandler(void);
  void TIM4_IRQHandler(void);
  void USART2_IRQHandler(void);
  void USART3_IRQHandler(void);
  void EXTI0_IRQHandler(void);
  void EXTI15_10_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1XX_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
