/**
  ******************************************************************************
  * @file    ADC/ADC_AnalogWatchdog/stm32f30x_it.c
  * @author  MCD Application Team
  * @version V1.1.1
  * @date    31-October-2014
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
#include "stm32f30x_it.h"
#include "main.h"
#include "flag.h"
#include "clarke_park.h"
#include "Matrix_Keyboard.h"
#include "Matrix_Keyboard_CallBack.h"
#include "Bat_Manage.h"

/** @addtogroup STM32F30x_StdPeriph_Examples
  * @{
  */

/** @addtogroup AWDG_Mode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
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
  * @brief  This function handles Usage Fault exception.
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
  Systick_Counter ++;

  //Debug_GPIO_Toggle(1);

  Flag_PID  = 1;
  Flag_PID1 = 1;
  Flag_PID2 = 1;
  Flag_PID3 = 1;

  //Debug_GPIO_Toggle(1);
}

/******************************************************************************/
/*                 STM32F30x Peripherals Interrupt Handlers                   */
/******************************************************************************/

/******************************************************************************/
/*                 STM32F30x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f30x.s).                                               */
/******************************************************************************/

void WWDG_IRQHandler(void)
{

}

void PVD_IRQHandler(void)
{

}

void TAMPER_STAMP_IRQHandler(void)
{

}

void RTC_WKUP_IRQHandler(void)
{

}

void FLASH_IRQHandler(void)
{

}

void RCC_IRQHandler(void)
{

}

void EXTI0_IRQHandler(void)
{

}

void EXTI1_IRQHandler(void)
{

}

void EXTI2_TS_IRQHandler(void)
{

}

void EXTI3_IRQHandler(void)
{

}

void EXTI4_IRQHandler(void)
{

}

void DMA1_Channel1_IRQHandler(void)
{
  //DMA Complete Int.
  if(DMA_GetITStatus(DMA1_IT_TC1) == SET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TC1);
    //Debug_GPIO_Toggle(0);

  }

  //DMA Error Int.
  if(DMA_GetITStatus(DMA1_IT_TE1) == SET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TE1);
    //Errors.

  }
}

void DMA1_Channel2_IRQHandler(void)
{

}

void DMA1_Channel3_IRQHandler(void)
{

}
/*
void DMA1_Channel4_IRQHandler(void)
{

}

void DMA1_Channel5_IRQHandler(void)
{

}

void DMA1_Channel6_IRQHandler(void)
{

}

void DMA1_Channel7_IRQHandler(void)
{

}
*/
void ADC1_2_IRQHandler(void)
{
  //ADC1 End of Conversion IRQ.
  if((ADC1->ISR & ADC_IT_JEOC) && (ADC1->IER & ADC_IT_JEOC))
  {
    //Clear Flag.
    ADC1->ISR |= ADC_IT_JEOC;

    //Debug_GPIO_Toggle(0);
#if 1
    //Read Current.
    switch(AClarkePark.OPAMP_SW)
    {
      case OPAMP_UV: AClarkePark.ADCPhaseU = ADC1->JDR1;
                     AClarkePark.ADCPhaseV = ADC2->JDR1;
      break;
      case OPAMP_UW: AClarkePark.ADCPhaseU = ADC1->JDR1;
                     AClarkePark.ADCPhaseW = ADC2->JDR1;
      break;
      case OPAMP_VW: AClarkePark.ADCPhaseV = ADC1->JDR1;
                     AClarkePark.ADCPhaseW = ADC2->JDR1;
      break;
    }

    //Read Angle.
    Hall_Read_Angle(&AHallAngle);

    //FOC Calculation.
#if 0
    AClarkePark.UpdateFlag = 1;
#endif

    ClarkePark_Loop(&AClarkePark);

    //Switch OPAMP1&2.
    OPAMP12_Switch(AClarkePark.OPAMP_SW);
#endif
  }
}

void ADC3_IRQHandler(void)
{
  //ADC3 End of Conversion IRQ.
  if((ADC3->ISR & ADC_IT_JEOC) && (ADC3->IER & ADC_IT_JEOC))
  {
    //Clear Flag.
    ADC3->ISR |= ADC_IT_JEOC;

    //Debug_GPIO_Toggle(1);
#if 1
    //Read Current.
    switch(BClarkePark.OPAMP_SW)
    {
      case OPAMP_UV: BClarkePark.ADCPhaseU = ADC3->JDR1;
                     BClarkePark.ADCPhaseV = ADC4->JDR1;
      break;
      case OPAMP_UW: BClarkePark.ADCPhaseU = ADC3->JDR1;
                     BClarkePark.ADCPhaseW = ADC4->JDR1;
      break;
      case OPAMP_VW: BClarkePark.ADCPhaseV = ADC4->JDR1;
                     BClarkePark.ADCPhaseW = ADC3->JDR1;
      break;
    }

    //Read Angle.
    Hall_Read_Angle(&BHallAngle);

    //FOC Calculation.
#if 0
    BClarkePark.UpdateFlag = 1;
#endif
    ClarkePark_Loop(&BClarkePark);

    //Switch OPAMP3&4.
    OPAMP34_Switch(BClarkePark.OPAMP_SW);
#endif
  }
}

void ADC4_IRQHandler(void)
{
  //ADC4 End of Conversion IRQ.
  if((ADC4->ISR & ADC_IT_JEOC) && (ADC4->IER & ADC_IT_JEOC))
  {
    //Clear Flag.
    ADC4->ISR |= ADC_IT_JEOC;

    ////ClarkePark_Loop(&BClarkePark);
  }
}

void USB_HP_CAN1_TX_IRQHandler(void)
{

}

void USB_LP_CAN1_RX0_IRQHandler(void)
{

}

void CAN1_RX1_IRQHandler(void)
{

}

void CAN1_SCE_IRQHandler(void)
{

}

void EXTI9_5_IRQHandler(void)
{

}

void TIM1_BRK_TIM15_IRQHandler(void)
{
#if 0
  //Break1.
  if((TIM1->DIER & TIM_IT_Break) && (TIM1->SR & TIM_IT_Break))
  {
    TIM1->SR &= (uint16_t)~TIM_IT_Break;
  }
#endif

  //Break2.
  if((TIM1->DIER & TIM_IT_Break) && (TIM1->SR & TIM_IT_Break2))
  {
    TIM1->SR &= (uint16_t)~TIM_IT_Break2;

    //Set Error Flag.
    Motor_Error_Set(&AClarkePark.Error_Flag,
                    ME_HardWareOverCurrentA
                   );
  }
}

void TIM8_BRK_IRQHandler(void)
{
#if 0
  //Break1.
  if((TIM8->DIER & TIM_IT_Break) && (TIM8->SR & TIM_IT_Break))
  {
    TIM8->SR &= (uint16_t)~TIM_IT_Break;
  }
#endif

  //Break2.
  if((TIM8->DIER & TIM_IT_Break) && (TIM8->SR & TIM_IT_Break2))
  {
    TIM8->SR &= (uint16_t)~TIM_IT_Break2;

    //Set Error Flag.
    Motor_Error_Set(&BClarkePark.Error_Flag,
                    ME_HardWareOverCurrentB
                   );
  }
}

void TIM1_UP_TIM16_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    ////Debug_GPIO_Toggle(0);
  }

  if(TIM_GetITStatus(TIM16, TIM_IT_Update) == SET)
  {
    TIM_ClearITPendingBit(TIM16, TIM_IT_Update);

  }
}

void TIM1_TRG_COM_TIM17_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM1, TIM_IT_Trigger) == SET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Trigger);
    //Debug_GPIO_Toggle(0);
  }

  if(TIM_GetITStatus(TIM17, TIM_IT_Update) == SET)
  {
    TIM_ClearITPendingBit(TIM17, TIM_IT_Update);

  }
}

void TIM1_CC_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM1, TIM_IT_CC1) == SET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);

  }
}

void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);


  }

  if(TIM_GetITStatus(TIM2, TIM_IT_CC4) == SET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);

  }
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  }

}

void TIM4_IRQHandler(void)
{

}
/*
void I2C1_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}
*/
void SPI1_IRQHandler(void)
{

}

void SPI2_IRQHandler(void)
{

}

void USART1_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{

}

void USART3_IRQHandler(void)
{

}

void EXTI15_10_IRQHandler(void)
{

}

void RTC_Alarm_IRQHandler(void)
{

}

void USBWakeUp_IRQHandler(void)
{

}

void TIM8_UP_IRQHandler(void)
{

}

void TIM8_TRG_COM_IRQHandler(void)
{

}

void TIM8_CC_IRQHandler(void)
{

}

void SPI3_IRQHandler(void)
{

}

void UART4_IRQHandler(void)
{

}

void UART5_IRQHandler(void)
{

}

void TIM6_DAC_IRQHandler(void)
{
  static uint8_t TIM6_Counter;

  //Update Flag & Keyboard.
  if((TIM6->DIER & 0x01) && (TIM6->SR & 0x01))
  {
    TIM6->SR = 0x00;

    //Matrix Keyboard Scanning.
    Matrix_Key_Data.flag_scan = true;

#if 1
    Matrix_Key_Scan(&Matrix_Key_Data);
#endif

    //Debug_GPIO_Toggle(0);

    //Add Counter.
    TIM6_Counter ++;
  }

  //Battery Management(Every 160ms).
  if((TIM6_Counter % 16) == 0)
  {
    //Read ADC Data.
    Li_Ion_Bat.ADC_BAT = ADC1->DR;

    //Battery Management Loop.
    BAT_Manage_Loop(&Li_Ion_Bat);
  }
}

void TIM7_IRQHandler(void)
{

}

void DMA2_Channel1_IRQHandler(void)
{
  //DMA Complete Int.
  if(DMA_GetITStatus(DMA2_IT_TC1) == SET)
  {
    DMA_ClearITPendingBit(DMA2_IT_TC1);
    ////Debug_GPIO_Toggle(0);
  }

  //DMA Error Int.
  if(DMA_GetITStatus(DMA2_IT_TE1) == SET)
  {
    DMA_ClearITPendingBit(DMA2_IT_TE1);
    //Errors.

  }
}

void DMA2_Channel2_IRQHandler(void)
{
  //DMA Complete Int.
  if(DMA_GetITStatus(DMA2_IT_TC2) == SET)
  {
    DMA_ClearITPendingBit(DMA2_IT_TC2);
    Debug_GPIO_Toggle(2);
  }

  //DMA Error Int.
  if(DMA_GetITStatus(DMA2_IT_TE2) == SET)
  {
    DMA_ClearITPendingBit(DMA2_IT_TE2);
    //Errors.

  }
}

void DMA2_Channel3_IRQHandler(void)
{

}

void DMA2_Channel4_IRQHandler(void)
{

}

void DMA2_Channel5_IRQHandler(void)
{
  //DMA Complete Int.
  if(DMA_GetITStatus(DMA2_IT_TC5) == SET)
  {
    DMA_ClearITPendingBit(DMA2_IT_TC5);
    Debug_GPIO_Toggle(1);
  }

  //DMA Error Int.
  if(DMA_GetITStatus(DMA2_IT_TE5) == SET)
  {
    DMA_ClearITPendingBit(DMA2_IT_TE5);
    //Errors.

  }
}

void COMP1_2_3_IRQHandler(void)
{

}

void COMP4_5_6_IRQHandler(void)
{

}

void COMP7_IRQHandler(void)
{

}

void USB_HP_IRQHandler(void)
{

}

void USB_LP_IRQHandler(void)
{

}

void USBWakeUp_RMP_IRQHandler(void)
{

}

void FPU_IRQHandler(void)
{

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

