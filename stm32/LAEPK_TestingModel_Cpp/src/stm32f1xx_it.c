/**
 ******************************************************************************
 * @file    stm32f1xx_it.c
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
#include "stm32f1xx_it.h"
#include "stm32f10x.h"
#include "GPIO_Functions.h"

/** @addtogroup IO_Toggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t nInst = 0;            // The number of instruction
uint8_t selMotor = 0xFF;    // The motor which be selected

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
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles USART2_IRQHandler Handler.
 * @param  None
 * @retval None
 */
void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) { // NOT USART_FLAG_RXNE
        uint16_t USART_ReceivData = 0xF0;
        USART_ReceivData = USART_ReceiveData(USART2);

        if (USART_ReceivData == 0xE0) {    // System stop
            USART_Send(USART2, "[System]Stop.\n");
            while (1) {
            }
        } else if (USART_ReceivData == 0xE1) {    // System reset
            /* Initialization */
            // Functions & Setups
            RCC_Initialization();
            GPIO_Initialization();
            USART_Initialization();
            PWM_Initialization();
            NVIC_Initialization();

            USART_Send(USART2, "[System]Reset.\n");
        } else if ((USART_ReceivData >= 0x25) & (USART_ReceivData <= 0xB3)) {
            /*
             50Hz ; 20ms

             0度: 0.5ms = 2.50% : CCR:360  -> 0x24 //Str
             45度: 1.0ms = 5.00% : CCR:720  -> 0x48
             90度: 1.5ms = 7.50% : CCR:1080 -> 0x6C
             135度: 2.0ms = 10.0% : CCR:1440 -> 0x90
             180度: 2.5ms = 12.5% : CCR:1800 -> 0xB4    //Ben

             270度: 3.5ms = 17.5% : CCR:2520 -> 0xFC
             */
//                    TIM_SetCompare2(TIM3, (((USART_ReceivData)*10)+5));
            USART_Send(USART2, "OK\n");
            MotorCtrl((USART_ReceivData) * 10);
        } else if (USART_ReceivData == 0xF0) {
            /* Null instruction */;
        } else {    // Unknown instruction
            USART_Send(USART2, "[Error]Unknown instruction.\n");
        }

        /* NO need to clears the USARTx's interrupt pending bits */
        /* USART_ClearITPendingBit(USART2,USART_IT_RXNE); */
    }
}

void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        TIM_Cmd(TIM3, DISABLE);    // Disable PWM
        USART_Send(USART2, "[STOP]\n");
        while (1) {
        }
//        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
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
