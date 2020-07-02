/**
 ******************************************************************************
 * @file    main.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    11-February-2014
 * @brief   Main program body
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
using namespace std;
/* Modified by Atollic to build with c++ */
extern "C" {
/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "main.h"
#include "GPIO_Functions.h"
#include "RCC_Functions.h"
#include "PWM_Functions.h"
#include "USART_Functions.h"
#include "NVIC_Functions.h"
#include "ADC_Functions.h"
}

/** @addtogroup L.A.E.P.K. Testing Model
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LimPos_Straight (76)    // The ADC value of full knee extension
#define LimPos_Bent     (3724)  // The ADC value of full knee flexion

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;
int POTdir = 0; //0:Unlimited; 1:Limited-Straight; -1:Limited-Bent

/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Main program
 * @param  None
 * @retval None
 */
int main(void) {
    /* Initialization */
    // Functions & Setups
    RCC_Initialization();
    GPIO_Initialization();
    ADC_Initialization();
    USART_Initialization();
    PWM_Initialization();
    NVIC_Initialization();

    // User-LED
    Pin_Clr(LD2);

    // Motor
//    MotorCtrl(530);
    TIM_SetCompare2(TIM3, 530);

    /* Infinite loop */
    while (1) {
        USART_Send(USART2, (uint8_t*)Number_TO_String(TIM3->CCR2));
        USART_Send(USART2, (uint8_t*)"  ");
        USART_Send(USART2, (uint8_t*)Number_TO_String(POTdir));
        USART_Send(USART2, (uint8_t*)"  ");
        USART_Send(USART2, (uint8_t*)Number_TO_String(ADC_GetValue(ADC1,
                                                         ADC_Channel_1,
                                                         1,
                                                         ADC_SampleTime_55Cycles5)));
        USART_Send(USART2, (uint8_t*)"\n");

        Delay_NonTimer(0x8FFFF);
    }
}

void MotorCtrl(u16 TargetCCR) {
    if ((POTdir == 1)
     || (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
         <= LimPos_Straight)) { //Str-Max
        while ((TargetCCR > (TIM3->CCR2))
            && (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
                < LimPos_Bent)) {
            u16 NowCCR = (TIM3->CCR2);
            TIM_SetCompare2(TIM3, NowCCR + 1);
            Delay_NonTimer(0xf0f);
        }
    } else if ((POTdir == -1)
            || (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
                >= LimPos_Bent)) { //Bent-Max
        while ((TargetCCR < (TIM3->CCR2))
            && (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
                > LimPos_Straight)) {
            u16 NowCCR = (TIM3->CCR2);
            TIM_SetCompare2(TIM3, NowCCR - 1);
            Delay_NonTimer(0xf0f);
        }
    } else {
        while ((TargetCCR != (TIM3->CCR2))
            && (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
                > LimPos_Straight)
            && (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
                < LimPos_Bent)) {
            u16 NowCCR = (TIM3->CCR2);
            if (TargetCCR > NowCCR) {
                TIM_SetCompare2(TIM3, NowCCR + 1);
            } else {
                TIM_SetCompare2(TIM3, NowCCR - 1);
            }

            Delay_NonTimer(0xf0f);
        }
    }

    if (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
        <= LimPos_Straight) {
        POTdir = 1;
        USART_Send(USART2, (uint8_t*)"POS_Str-Max\n");
    } else if (ADC_GetValue(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5)
               >= LimPos_Bent) {
        POTdir = -1;
        USART_Send(USART2, (uint8_t*)"POS_Bet-Max\n");
        USART_Send(USART2, (uint8_t*)"POS_Bet-Max\n");
    } else {
        POTdir = 0;
        USART_Send(USART2, (uint8_t*)"POS_Nor\n");
    }
}

/**
 * @brief
 * @param
 * @return
 */
Motor_State_TypeDef* GetMotorState(void) {

    Motor_State_TypeDef Motor_State;

    for(i=0; i<3; i++){
        if (Pin_ReadInput(Motor[i][0]) == 1)
            Motor_State.Motor_ReadyState = Motor_ReadyState_Ready;
        else
            Motor_State.Motor_ReadyState = Motor_ReadyState_Fault;

        if (Pin_ReadOutput(Motor[i][1]) == 1)
            Motor_State.Motor_FunctionState = ENABLE;
        else
            Motor_State.Motor_FunctionState = DIASBLE;

        if (Pin_ReadOutput(Motor[i][3]) == 1)
            Motor_State.Motor_Direction = Motor_Direction_CCW;
        else
            Motor_State.Motor_Direction = Motor_Direction_CW;


    }

}

/**
 * @brief    Convert number into string
 * @param     Number: The number want to convert.
 * @return    The converted string.
 */
char* Number_TO_String(uint16_t Number) {
    static char string[3];
    sprintf(string, "%d", Number);
    return string;
}

void Delay_NonTimer(__IO u32 nTime) {
    for (; nTime != 0; nTime--) {
    }
}

/* Modified by Atollic to build with c++ */
extern "C" {
    /**
     * @brief  Inserts a delay time.
     * @param  nTime: specifies the delay time length, in 1 ms.
     * @retval None
     */
    void Delay(__IO uint32_t nTime) {
        TimingDelay = nTime;

        while (TimingDelay != 0){
        }
    }

    /**
     * @brief  Decrements the TimingDelay variable.
     * @param  None
     * @retval None
     */
    void TimingDelay_Decrement(void) {
        if (TimingDelay != 0x00) {
            TimingDelay--;
        }
    }

}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1) {
    }
}
#endif

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
