/**
  ******************************************************************************
  * @file    system_stm32f10x.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  * 
  *          This file contains the system clock configuration for STM32F103 devices
  *          and is customized for use with stm32f103_nucleo Kit. 
  *          The STM32F103 is configured to run at 72 MHz, following the three  
  *          configuration below:
  *            - PLL_SOURCE_HSI   (default)     : HSI (~8MHz) used to clock the PLL, and
  *                                               the PLL is used as system clock source,
  *                                               64 MHz is maximum frequency on PLL HSI mode.
  *            - PLL_SOURCE_HSE                 : HSE (8MHz) used to clock the PLL, and 
  *                                               the PLL is used as system clock source.
  *            - PLL_SOURCE_HSE_BYPASS          : HSE bypassed with an external clock 
  *                                              (8MHz, coming from ST-Link) used to clock
  *                                              the PLL, and the PLL is used as system
  *                                              clock source.  
  *              
  * 1.  This file provides two functions and one global variable to be called from 
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
  *                      factors, AHB/APBx prescalers and Flash settings). 
  *                      This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f10x_xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HSI (8 MHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32f10x_xx.s" file, to
  *    configure the system clock before to branch to main program.
  *
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and HSI still used as system clock source. User can 
  *    add some code to deal with this issue inside the SetSysClock() function.
  *
  * 4. The default value of HSE crystal is set to 8 MHz. 
  *    When HSE is used as system clock source, directly or through PLL, and you
  *    are using different crystal you have to adapt the HSE value to your own
  *    configuration.
  *        
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
#include "stm32f10x.h"

/** @addtogroup Projects
  * @{
  */ 

/** @addtogroup stm32f10x_system
  * @{
  */  

/* Private typedef -----------------------------------------------------------*/

/** @addtogroup STM32F10x_System_Private_Defines
  * @{
  */

/*!< Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source)
   
   IMPORTANT NOTE:
   ============== 
   1. After each device reset the HSI is used as System clock source.
      
   2. If none of the define below is enabled, the HSI is used as System clock
    source.

   3. The System clock configuration functions provided within this file assume
      that an external 8MHz crystal is used to drive the System clock.

     If you are using different crystal you have to adapt those functions accordingly.
    */
    
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */ 
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. 
                                  This value must be a multiple of 0x200. */


#define PLL_SOURCE_HSI          // HSI (~8 MHz) used to clock the PLL, and the PLL is used as system clock source
                                  //When the HSI is used as a PLL clock input, the maximum system clock
                                  //frequency that can be achieved is 64 MHz.

//#define PLL_SOURCE_HSE            // HSE (8MHz) used to clock the PLL, and the PLL is used as system clock source

//#define PLL_SOURCE_HSE_BYPASS   // HSE bypassed with an external clock (8MHz, coming from ST-Link) used to clock

  uint32_t SystemCoreClock = 72000000;

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};


/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @addtogroup STM32F10x_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW,SWS, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */

  RCC->CFGR &= (uint32_t)0xF8FF0000;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetSysClock();

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *           
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.         
  *     
  * @note   - The system frequency computed by this function is not the real 
  *           frequency in the chip. It is calculated based on the predefined 
  *           constant and the selected clock source:
  *             
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *                                              
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *                          
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**) 
  *             or HSI_VALUE(*) multiplied by the PLL factors.
  *         
  *         (*) HSI_VALUE is a constant defined in stm32f1xx.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.   
  *    
  *         (**) HSE_VALUE is a constant defined in stm32f1xx.h file (default value
  *              8 MHz or 25 MHz, depending on the product used), user has to ensure
  *              that HSE_VALUE is same as the real frequency of the crystal used.
  *              Otherwise, this function may have wrong result.
  *                
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0;
  
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
  case 0x00:  /* HSI used as system clock */
    SystemCoreClock = HSI_VALUE;
    break;
  case 0x04:  /* HSE used as system clock */
    SystemCoreClock = HSE_VALUE;
    break;
  case 0x08:  /* PLL used as system clock */
    
    /* Get PLL clock source and multiplication factor ----------------------*/
    pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
    pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
    
    pllmull = ( pllmull >> 18) + 2;
    
    if (pllsource == 0x00)
    {
      /* HSI oscillator clock divided by 2 selected as PLL clock entry */
      SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
    }
    else
    {        
      /* HSE selected as PLL clock entry */
      if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t)RESET)
      {/* HSE oscillator clock divided by 2 */
        SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
      }
      else
      {
        SystemCoreClock = HSE_VALUE * pllmull;
      }        
    }
    break;
  default:
    SystemCoreClock = HSI_VALUE;
    break;
  }
  
  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;  
}

/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
 #ifdef PLL_SOURCE_HSI  
  /* At this stage the HSI is already enabled */
  
  /*  PLL configuration: PLLCLK = HSI/2 * 16 = 64 MHz */
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL));
  RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL16);
    
 #else /* PLL_SOURCE_HSE_BYPASS or PLL_SOURCE_HSE */  
      
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
#ifdef PLL_SOURCE_HSE_BYPASS
  RCC->CR |= ((uint32_t)RCC_CR_HSEBYP);
#endif   /* PLL_SOURCE_HSE_BYPASS */
   
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  
  
  if (HSEStatus == (uint32_t)0x01)
  {    
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
  }  
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
    configuration. User can add here some code to deal with this error */
  }
  
#endif /*PLL_SOURCE_HSI*/
  
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
