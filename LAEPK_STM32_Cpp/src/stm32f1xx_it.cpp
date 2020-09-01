/**
 ******************************************************************************
 * @file    stm32f1xx_it.cpp
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    11-February-2014
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stm32f1xx_it.hpp>

/** @addtogroup L.A.E.P.K.
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t nInst = 0;      // The number of instruction
uint8_t selMotor = 0xFF; // The motor which be selected

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                          */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Usage Fault  .
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/**
 * @brief  This function handles USART2_IRQHandler Handler.
 * @param  None
 * @retval None
 */
void USART2_IRQHandler(void)
{
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    uint16_t USART_ReceivData = 0xF0; // 0xF0 : Null instruction
    USART_ReceivData = USART_ReceiveData(USART2);

    /* System stop */
    if (USART_ReceivData == 0xE0)
    {
      USART_Send(USART2, "[System]Stop.\n");
      while (1)
      {
      }
    }
    /* System reset */
    else if (USART_ReceivData == 0xE1)
    {
      USART_Send(USART2, "[System]Reset.\n");
      NVIC_SystemReset();
    }
    else if ((USART_ReceivData >= 0x00) && (USART_ReceivData <= 0x87))
    {
      CommunicationDecoder(USART_ReceivData);
    }
    /* Null instruction */
    else if (USART_ReceivData == 0xF0)
    {
    }
    /* Unknown instruction */
    else
    {
      USART_Send(USART2, "[Error]Unknown instruction.\n");
    }

    /* NO need to clears the USARTx's interrupt pending bits */
    /* USART_ClearITPendingBit(USART2,USART_IT_RXNE); */
  }
}

/**
 * @brief  This function handles limit switch STOP
 * @param  None
 * @retval None
 */
void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    // GPIO_SetValue(RightMotor_FunctionStatePin, LOW); // Disable motor
    // TIM_Cmd(TIM3, DISABLE);    // Disable PWM
    USART_Send(USART2, "[EXTI STOP]\n");
    while (1)
    {
    }

    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_md.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
