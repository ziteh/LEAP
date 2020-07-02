/**
 ******************************************************************************
 * @file    main.h
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    11-February-2014
 * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_nucleo.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t   Motor_Name;
  bool      Motor_ReadyState;
  bool      Motor_FunctionState;
  bool      Motor_Direction;
  uint16_t  Motor_PMW_CCP;
  uint16_t  Motor_RPM;
  uint16_t  Joint_Angle;
  int8_t    Joint_LimitState;
} Motor_State_TypeDef;

typedef enum {CW = 0, CCW = !CW} Direction;
typedef enum {Fault = 0, Ready = !Fault} ReadyState;

/* Exported constants --------------------------------------------------------*/
// Motor_State_TypeDef
#define Motor_ReadyState_Ready  ((bool)1)
#define Motor_ReadyState_Fault  ((bool)0)

#define Motor_Direction_CCW     ((bool)1)
#define Motor_Direction_CW      ((bool)0)

#define Joint_LimitState_FullExtension  ((int8_t)1)
#define Joint_LimitState_FullFlexion    ((int8_t)-1)
#define Joint_LimitState_Unlimited      ((int8_t)0)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);
void Delay_NonTimer(__IO u32 nTime);
char* Number_TO_String(uint16_t Number);
void MotorCtrl(u16 TargetCCR);

#ifdef __cplusplus
}
#endif

class Motor {
public:
    void Control(FunctionalState NewState, bool Direction, uint16_t PWM_CCP);
    Motor_State_TypeDef* State(void);

private:
    uint8_t StatePin, DirectionPin, SpeedPin;   //GPIO pin

};

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
