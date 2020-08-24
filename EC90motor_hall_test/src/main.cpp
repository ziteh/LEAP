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

/* Modified by Atollic to build with c++ */
extern "C"
{
/* Includes ------------------------------------------------------------------*/
#include "main.h"
}

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;
/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_md.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */  
  
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  /* Initialize LED2 */
  STM_EVAL_LEDInit(LED2);
  
  /* Initialize User_Button on STM32NUCLEO */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);   
  
  /* Initiate Blink Speed variable */ 
  BlinkSpeed = 0;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                         RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC,
                         ENABLE);

  GPIO_InitTypeDef GPIO_IS;
  GPIO_IS.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_IS.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_IS.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_IS);

  GPIO_IS.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_IS.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_IS.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIO_IS);

  GPIO_IS.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_IS.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_IS.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_IS);

  int mod = 0;
  /* Infinite loop */
  while (1)
  {
    switch (mod) {
      case 0:
         GPIO_SetBits(GPIOA, GPIO_Pin_10);
         GPIO_ResetBits(GPIOC, GPIO_Pin_7);
         GPIO_ResetBits(GPIOB, GPIO_Pin_5);
         mod = 1;
        break;
      case 1:
         GPIO_SetBits(GPIOA, GPIO_Pin_10);
         GPIO_SetBits(GPIOC, GPIO_Pin_7);
         GPIO_ResetBits(GPIOB, GPIO_Pin_5);
         mod = 2;
        break;
      case 2:
         GPIO_ResetBits(GPIOA, GPIO_Pin_10);
         GPIO_SetBits(GPIOC, GPIO_Pin_7);
         GPIO_ResetBits(GPIOB, GPIO_Pin_5);
         mod = 3;
        break;
      case 3:
         GPIO_ResetBits(GPIOA, GPIO_Pin_10);
         GPIO_SetBits(GPIOC, GPIO_Pin_7);
         GPIO_SetBits(GPIOB, GPIO_Pin_5);
         mod = 4;
        break;
      case 4:
         GPIO_ResetBits(GPIOA, GPIO_Pin_10);
         GPIO_ResetBits(GPIOC, GPIO_Pin_7);
         GPIO_SetBits(GPIOB, GPIO_Pin_5);
         mod = 5;
        break;
      case 5:
      default:
         GPIO_SetBits(GPIOA, GPIO_Pin_10);
         GPIO_ResetBits(GPIOC, GPIO_Pin_7);
         GPIO_SetBits(GPIOB, GPIO_Pin_5);
         mod = 0;
        break;
    }

    Delay(500);
  }
}

/* Modified by Atollic to build with c++ */
extern "C"
{
/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length, in 1 ms.
* @retval None
*/
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  
  while(TimingDelay != 0);
}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
* @}
*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
