/*This is the PWM functions.
File name :PWM.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "PWM.h"

/* Init PWM As Sine Wave Mode -- Timerx.
*/
void PWM_Init_180(uint32_t Freq_Hz)
{
  //Enable Timerx Clock.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);

  //Set Timer Clock From PLL.
  RCC_TIMCLKConfig(RCC_TIM1CLK_PLLCLK);
  RCC_TIMCLKConfig(RCC_TIM8CLK_PLLCLK);

  // Setup PWM GPIOs.
  //Motor-A PWM
  //PA8 PA9 PA10. U+/V+/W+
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_6);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_6);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_6);

  //PA11 PA12 PB15. U-/V-/W-
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_4);

  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_8 | /*U+*/
                                    GPIO_Pin_9 | /*V+*/
                                    GPIO_Pin_10| /*W+*/
                                    GPIO_Pin_11| /*U-*/
                                    GPIO_Pin_12; /*V-*/
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_15; /*W-*/
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Motor-B PWM.
  //PC6 PC7 PB9.   U+/V+/W+
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,  GPIO_AF_4);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7,  GPIO_AF_4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9,  GPIO_AF_10);

  //PC10 PC11 PC12. U-/V-/W-
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_4);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_4);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_4);

  GPIO_InitStruct_Temp.GPIO_Pin = GPIO_Pin_6 | /*U+*/
                                  GPIO_Pin_7 | /*V+*/
                                  GPIO_Pin_10| /*U-*/
                                  GPIO_Pin_11| /*V-*/
                                  GPIO_Pin_12; /*W-*/
  GPIO_Init(GPIOC, &GPIO_InitStruct_Temp);

  GPIO_InitStruct_Temp.GPIO_Pin = GPIO_Pin_9;  /*W+*/
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Reset Timerx Setup.
  TIM_DeInit(TIM1);
  TIM_DeInit(TIM8);

  //Disable Timer.
  TIM_Cmd(TIM1, DISABLE);
  TIM_Cmd(TIM8, DISABLE);

  //PWM Init Struct.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = ((RCC_Clocks.SYSCLK_Frequency / Freq_Hz));
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0x0000;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_CenterAligned1;  //Counting Down CMP Will Int.
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0001;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

  //Clear Timerx Counter;
  TIM_SetCounter(TIM1, TIM1->ARR);
  TIM_SetCounter(TIM8, 0);

  //Output Compare management.
  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStruct.TIM_Pulse        = TIM_TimeBaseInitStruct.TIM_Period >> 1;//3;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCNPolarity_Low;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCIdleState_Set;

  TIM_OC1Init(TIM1, &TIM_OCInitStruct);
  TIM_OC2Init(TIM1, &TIM_OCInitStruct);
  TIM_OC3Init(TIM1, &TIM_OCInitStruct);
  TIM_OC4Init(TIM1, &TIM_OCInitStruct);

  TIM_OC1Init(TIM8, &TIM_OCInitStruct);
  TIM_OC2Init(TIM8, &TIM_OCInitStruct);
  TIM_OC3Init(TIM8, &TIM_OCInitStruct);
  TIM_OC4Init(TIM8, &TIM_OCInitStruct);

  //Set TIM1 Trigger Signal.
  //Trigger 1.
  TIM_SelectOutputTrigger(TIM1,  TIM_TRGOSource_Enable);        //ITR  - > Timer8 / En

  //Trigger2.
  TIM1->CCR4 = TIM1->ARR - 1;
  TIM_SelectOutputTrigger2(TIM1, TIM_TRGO2Source_OC4Ref);       //ITR2 - > ADC1&2 ---- TIM_TRGO2Source_Update
  TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);  //Enable Master & Slave

  //Set TIM8 Trigger Signal.
  TIM_SelectInputTrigger(TIM8, TIM_TS_ITR0);

  //Trigger2.
  TIM8->CCR4 = TIM8->ARR - 1;
  TIM_SelectOutputTrigger2(TIM8, TIM_TRGO2Source_OC4Ref);       // ---- TIM_TRGO2Source_Update
  TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Trigger);             //Enable Tim8

  //ARR & CCx Buffered.
  TIM_ARRPreloadConfig(TIM1, ENABLE);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM8, ENABLE);
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);

  //TIM_SelectCOM(TIM1, DISABLE);
  //TIM_CCPreloadControl(TIM1, DISABLE);
  //TIM_CCPreloadControl(TIM8, DISABLE);

  //Break ACTH Set.
  SYSCFG_BreakConfig(SYSCFG_Break_PVD);
  SYSCFG_BreakConfig(SYSCFG_Break_SRAMParity);
  SYSCFG_BreakConfig(SYSCFG_Break_Lockup);

  //Break1 Advanced-control timers (TIM1 and TIM8) specific features.
  //TIM_Break1Config(TIM1, TIM_Break1Polarity_High, 2);
  //TIM_Break1Cmd(TIM1, ENABLE);
  //TIM_Break1Config(TIM8, TIM_Break1Polarity_High, 2);
  //TIM_Break1Cmd(TIM8, ENABLE);

  //Break2 Advanced-control timers (TIM1 and TIM8) specific features.
  TIM_Break2Config(TIM1, TIM_Break2Polarity_High, 2);
  TIM_Break2Cmd(TIM1, ENABLE);
  TIM_Break2Config(TIM8, TIM_Break2Polarity_High, 2);
  TIM_Break2Cmd(TIM8, ENABLE);

  //BDTR Set up (TIM1 and TIM8) specific features.
  TIM_BDTRInitTypeDef TIM_BDTRInitStruct;
  TIM_BDTRInitStruct.TIM_OSSRState       = TIM_OSSRState_Enable;
  TIM_BDTRInitStruct.TIM_OSSIState       = TIM_OSSIState_Enable;
  TIM_BDTRInitStruct.TIM_LOCKLevel       = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct.TIM_DeadTime        = 179; //20; //179;
  TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM1->BDTR |= (uint32_t)TIM_BDTRInitStruct.TIM_OSSRState |
                TIM_BDTRInitStruct.TIM_OSSIState |
                TIM_BDTRInitStruct.TIM_LOCKLevel |
                TIM_BDTRInitStruct.TIM_DeadTime  |
                TIM_BDTRInitStruct.TIM_AutomaticOutput;

  TIM8->BDTR = TIM1->BDTR;

  //Enable PWM Output.
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM8, ENABLE);

  //Interrupts management.
  //Clear Flags.
  TIM1->SR = 0x0000;
  TIM8->SR = 0x0000;

  NVIC_InitTypeDef NVIC_InitStructure;

  //Timer1 Brake Interrupt.
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM1_BRK_TIM15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                    = TIM8_BRK_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //Timer1 Update Interrupt.
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM1_UP_TIM16_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                    = TIM8_UP_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //TIM_ITConfig(TIM1, TIM_IT_Update,  DISABLE);
  TIM_ITConfig(TIM1, TIM_IT_Break,  ENABLE);

  //TIM_ITConfig(TIM8, TIM_IT_Update,  DISABLE);
  TIM_ITConfig(TIM8, TIM_IT_Break,  ENABLE);

  //Start TIM1 & TIM8.
  TIM_Cmd(TIM1, ENABLE);
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

