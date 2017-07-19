/*This is the timer functions.
File name :timer.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "timer.h"
/* Timer2 Counter Init.
*/
void Timer2_Base_Counter_Init(void)
{
  //Enable Timer2 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  //Disable Timer.
  TIM_Cmd(TIM2, DISABLE);

  //Reset Timer2 Setup.
  TIM_DeInit(TIM2);

  //Clear Counter.
  TIM_SetCounter(TIM2, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffffffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

  TIM_UpdateDisableConfig(TIM2, DISABLE);
  TIM_ARRPreloadConfig(TIM2, ENABLE);

  //Interrupt Setup.
  //NVIC_InitTypeDef NVIC_InitStructure;
  //NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  //NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM2, TIM_FLAG_CC1);
  //TIM_ITConfig(TIM2, TIM_IT_CC1, Compare_Int_En);

  //Enable Timer2.
  TIM_Cmd(TIM2, ENABLE);
}

/* Timer2 Init As a Counter.
*/
/*
void Timer2_Counter_Init(uint32_t           Timer_Compare,
                         FunctionalState    Compare_Int_En
                        )
{ //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer2 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  //Reset Timer2 Setup.
  TIM_DeInit(TIM2);

  //Disable Timer.
  TIM_Cmd(TIM2, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM2, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period = 0xffffffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

  //Set Auto Reload Data.
  //TIM_SetAutoreload(TIM2, 0xffffff);

  //TIM_UpdateDisableConfig(TIM2, DISABLE);
  //TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Regular);

  //TIM_ARRPreloadConfig(TIM2, ENABLE);
  //TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);
  //TIM_SetClockDivision(TIM2, TIM_CKD_DIV1);

  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = Timer_Compare;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM2, &TIM_OCInitStruct);
  //TIM_OC2Init(TIM2, &TIM_OCInitStruct);
  //TIM_OC3Init(TIM2, &TIM_OCInitStruct);
  //TIM_OC4Init(TIM2, &TIM_OCInitStruct);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel         = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM2, TIM_FLAG_CC1);
  TIM_ITConfig(TIM2, TIM_IT_CC1, Compare_Int_En);

  //Disable Timer2.
  TIM_Cmd(TIM2, ENABLE);
}
*/

/* Timer2 Init As a Capture.
*/
void Timer2_Capture_Init(uint32_t DMA_Memory_Addr)
{
  //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer2 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,  ENABLE);

  //Set as Capture.
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_1);

  //GPIO Setup.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_3;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Reset Timer2 Setup.
  TIM_DeInit(TIM2);

  //Disable Timer.
  TIM_Cmd(TIM2, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM2, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period             = 0xffffffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler          = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision      = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode        = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0x0000;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

  //Init Capture Channel.
  TIM_ICInitTypeDef TIM_ICInitStruct;
  TIM_ICInitStruct.TIM_Channel      = TIM_Channel_2;
  TIM_ICInitStruct.TIM_ICPolarity   = TIM_ICPolarity_Rising;//TIM_ICPolarity_BothEdge;
  TIM_ICInitStruct.TIM_ICSelection  = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler  = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter     = 0x00;
  TIM_ICInit(TIM2, &TIM_ICInitStruct);

  //Set DMA.
  //Regular Channels DMA Configuration functions.
  //Reset DMA1
  DMA_DeInit(DMA1_Channel7);
  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(TIM2->CCR2);
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Low;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel7, &DMA_InitStruct);

  DMA_Cmd(DMA1_Channel7, ENABLE);

  TIM_DMAConfig(TIM2, TIM_DMABase_CCR2, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM2, TIM_DMA_CC2, ENABLE);
  TIM_SelectCCDMA(TIM2, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM2, TIM_FLAG_CC1);
  TIM_ClearFlag(TIM2, TIM_FLAG_CC2);
  TIM_ClearFlag(TIM2, TIM_FLAG_CC3);
  TIM_ClearFlag(TIM2, TIM_FLAG_CC4);

  TIM_ITConfig(TIM2, TIM_IT_CC1, DISABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC3, DISABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC4, DISABLE);

  //Disable Timer2.
  TIM_Cmd(TIM2, ENABLE);
}

/* Timer3 Init As a Counter.
*/
/*
void Timer3_Counter_Init(uint16_t           Timer_Compare,
                         FunctionalState    Compare_Int_En
                        )
{ //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer3 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  //Reset Timer3 Setup.
  TIM_DeInit(TIM3);

  //Disable Timer.
  TIM_Cmd(TIM3, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM3, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler = 209;
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV2;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

  //Set Auto Reload Data.
  //TIM_SetAutoreload(TIM3, 0xffff);

  //TIM_UpdateDisableConfig(TIM3, DISABLE);
  //TIM_UpdateRequestConfig(TIM3, TIM_UpdateSource_Regular);

  //TIM_ARRPreloadConfig(TIM3, ENABLE);

  //Timer3 Set as One Time Pulse Mode.
  //TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Single);
  //TIM_SetClockDivision(TIM3, TIM_CKD_DIV1);

  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = Timer_Compare;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM3, &TIM_OCInitStruct);
  //TIM_OC2Init(TIM3, &TIM_OCInitStruct);
  //TIM_OC3Init(TIM3, &TIM_OCInitStruct);
  //TIM_OC4Init(TIM3, &TIM_OCInitStruct);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel         = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM3, TIM_FLAG_CC1);
  TIM_ITConfig(TIM3, TIM_IT_CC1, Compare_Int_En);

  //Disable Timer3.
  TIM_Cmd(TIM3, DISABLE);
}
*/

/* Timer3 Init As a Capture.
*/
void Timer3_Capture_Init(uint32_t DMA_Memory_Addr1,    //For CAP
                         uint32_t DMA_Memory_Addr2     //For Overflow.
                        )
{
  //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer3 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //Set as Capture.
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_1);

  //GPIO Setup.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_12;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Reset Timer3 Setup.
  TIM_DeInit(TIM3);

  //Disable Timer.
  TIM_Cmd(TIM3, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM3, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 31;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

  //Init Capture Channel.
  TIM_ICInitTypeDef TIM_ICInitStruct;
  TIM_ICInitStruct.TIM_Channel      = TIM_Channel_1;
  TIM_ICInitStruct.TIM_ICPolarity   = TIM_ICPolarity_Rising;//TIM_ICPolarity_BothEdge;
  TIM_ICInitStruct.TIM_ICSelection  = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler  = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter     = 0x00;
  TIM_ICInit(TIM3, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_2;
  //TIM_ICInit(TIM3, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_3;
  //TIM_ICInit(TIM3, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_4;
  //TIM_ICInit(TIM3, &TIM_ICInitStruct);

  //Set DMA.
  //DMA Remap Set.
  ////SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM3, ENABLE);

  //Regular Channels DMA Configuration functions.
  //Reset DMA1 -- Channel6 for Cap.
  DMA_DeInit(DMA1_Channel6);
  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(TIM3->CCR1);
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr1;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Low;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel6, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel6, ENABLE);

  TIM_DMAConfig(TIM3, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM3, TIM_DMA_CC1, ENABLE);
  TIM_DMACmd(TIM3, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIM3, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  //NVIC_InitStructure.NVIC_IRQChannel                    = TIM1_UP_TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Flags.
  TIM3->SR |= 0xffffffff;

  TIM_ITConfig(TIM3, TIM_IT_CC1, DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC2, DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC3, DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC4, DISABLE);

  //Disable Timer3.
  TIM_Cmd(TIM3, ENABLE);
}

/* Timer4 Init As a Capture.
*/
void Timer4_Capture_Init(uint32_t DMA_Memory_Addr1,    //For CAP
                          uint32_t DMA_Memory_Addr2     //For Overflow.
                         )
{
  //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer3 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //Set as Capture.
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_1);

  //GPIO Setup.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_12;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Reset Timer3 Setup.
  TIM_DeInit(TIM4);

  //Disable Timer.
  TIM_Cmd(TIM4, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM4, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 31;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

  //Init Capture Channel.
  TIM_ICInitTypeDef TIM_ICInitStruct;
  TIM_ICInitStruct.TIM_Channel      = TIM_Channel_1;
  TIM_ICInitStruct.TIM_ICPolarity   = TIM_ICPolarity_Rising;//TIM_ICPolarity_BothEdge;
  TIM_ICInitStruct.TIM_ICSelection  = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler  = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter     = 0x00;
  TIM_ICInit(TIM4, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_2;
  //TIM_ICInit(TIM4, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_3;
  //TIM_ICInit(TIM4, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_4;
  //TIM_ICInit(TIM4, &TIM_ICInitStruct);

  //Set DMA.
  //DMA Remap Set.
  ///SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM4, ENABLE);

  //Regular Channels DMA Configuration functions.
  //Reset DMA1 -- Channel6 for Cap.
  DMA_DeInit(DMA1_Channel6);
  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(TIM4->CCR1);
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr1;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Low;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel6, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel6, ENABLE);

  TIM_DMAConfig(TIM4, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM4, TIM_DMA_CC1, ENABLE);
  TIM_DMACmd(TIM4, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIM4, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  ////NVIC_InitStructure.NVIC_IRQChannel                    = TIM1_UP_TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Flags.
  TIM4->SR |= 0xffffffff;

  TIM_ITConfig(TIM4, TIM_IT_CC1, DISABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC2, DISABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC3, DISABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC4, DISABLE);

  //Disable Timer3.
  TIM_Cmd(TIM4, ENABLE);
}

/* Time3 Encoder Init.
*/
void Timer3_Encoder_Init(void)
{
  //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer4 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  //Set as Capture.
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_2);

  //GPIO Setup.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_4;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Reset Timer4 Setup.
  TIM_DeInit(TIM3);

  //Disable Timer.
  TIM_Cmd(TIM3, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM3, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 16383;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Down;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

  //Set Encoder Interface.
  TIM_EncoderInterfaceConfig(TIM3,
                             TIM_EncoderMode_TI12,
                             TIM_ICPolarity_Falling,    //TIM_ICPolarity_Rising,
                             TIM_ICPolarity_Rising      //TIM_ICPolarity_Falling
                            );
  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Flags.
  //TIM_ClearFlag(TIM3, TIM_FLAG_CC1);
  TIM3->SR = 0xffff;

  //Enable Timer4 Int.
  TIM_ITConfig(TIM3, TIM_IT_CC1, DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC2, DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC3, DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC4, DISABLE);

  //Enable Timer2.
  TIM_Cmd(TIM3, ENABLE);
}

/* Timer6 Counter Init.
*/
void Timer6_Base_Counter_Init(void)
{
  //Enable Timer6 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  //Disable Timer.
  TIM_Cmd(TIM6, DISABLE);

  //Reset Timer6 Setup.
  TIM_DeInit(TIM6);

  //Clear Counter.
  TIM_SetCounter(TIM6, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 9999;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 71;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);

  TIM_UpdateDisableConfig(TIM6, DISABLE);
  TIM_ARRPreloadConfig(TIM6, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_DAC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM6->SR = 0x00;
  TIM6->DIER |= 0x01;

  //Enable Timer6.
  TIM_Cmd(TIM6, ENABLE);
}

/* Timer15 Counter Init.
*/
void Timer15_Counter_Init(uint32_t           Timer_Compare,
                          FunctionalState    Compare_Int_En
                         )
{ //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer15 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

  //Reset Timer15 Setup.
  TIM_DeInit(TIM15);

  //Disable Timer.
  TIM_Cmd(TIM15, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM15, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV4;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM15, &TIM_TimeBaseInitStruct);

  TIM_UpdateDisableConfig(TIM15, DISABLE);
  //TIM_UpdateRequestConfig(TIM15, TIM_UpdateSource_Regular);

  TIM_ARRPreloadConfig(TIM15, ENABLE);
  //TIM_SelectOnePulseMode(TIM15, TIM_OPMode_Repetitive);
  //TIM_SetClockDivision(TIM15, TIM_CKD_DIV1);

  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = Timer_Compare;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM15, &TIM_OCInitStruct);
  //TIM_OC2Init(TIM15, &TIM_OCInitStruct);
  //TIM_OC3Init(TIM15, &TIM_OCInitStruct);
  //TIM_OC4Init(TIM15, &TIM_OCInitStruct);

  //Timer DMA Setup.
  TIM_DMAConfig(TIM15, TIM_DMABase_ARR, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM15, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIM15, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = TIM1_BRK_TIM15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM15, TIM_FLAG_CC1);
  TIM_ITConfig(TIM15, TIM_IT_CC1, Compare_Int_En);

  //Enable Timer15.
  TIM_Cmd(TIM15, ENABLE);
}

/* Timer16 Counter Init.
*/
void Timer16_Counter_Init(uint32_t           Timer_Compare,
                          FunctionalState    Compare_Int_En
                         )
{ //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer16 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);

  //Reset Timer16 Setup.
  TIM_DeInit(TIM16);

  //Disable Timer.
  TIM_Cmd(TIM16, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM16, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV4;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM16, &TIM_TimeBaseInitStruct);

  //Set Auto Reload Data.
  //TIM_SetAutoreload(TIM16, 0xffffff);

  //TIM_UpdateDisableConfig(TIM16, DISABLE);
  //TIM_UpdateRequestConfig(TIM16, TIM_UpdateSource_Regular);

  TIM_ARRPreloadConfig(TIM16, ENABLE);
  //TIM_SelectOnePulseMode(TIM16, TIM_OPMode_Repetitive);
  //TIM_SetClockDivision(TIM16, TIM_CKD_DIV1);

  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = Timer_Compare;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM16, &TIM_OCInitStruct);
  //TIM_OC2Init(TIM16, &TIM_OCInitStruct);
  //TIM_OC3Init(TIM16, &TIM_OCInitStruct);
  //TIM_OC4Init(TIM16, &TIM_OCInitStruct);

  //Timer DMA Setup.
  TIM_DMAConfig(TIM16, TIM_DMABase_ARR, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM16, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIM16, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = TIM1_UP_TIM16_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM16, TIM_FLAG_CC1);
  TIM_ITConfig(TIM16, TIM_IT_Update, Compare_Int_En);

  //Enable Timer16.
  TIM_Cmd(TIM16, ENABLE);
}

/* Timer16 Init As a Capture.
*/
void Timer16_Capture_Init(uint32_t DMA_Memory_Addr1,    //For CAP
                          uint32_t DMA_Memory_Addr2     //For Overflow.
                         )
{
  //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer16 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //Set as Capture.
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_1);

  //GPIO Setup.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_12;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Reset Timer16 Setup.
  TIM_DeInit(TIM16);

  //Disable Timer.
  TIM_Cmd(TIM16, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM16, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 31;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM16, &TIM_TimeBaseInitStruct);

  //Init Capture Channel.
  TIM_ICInitTypeDef TIM_ICInitStruct;
  TIM_ICInitStruct.TIM_Channel      = TIM_Channel_1;
  TIM_ICInitStruct.TIM_ICPolarity   = TIM_ICPolarity_Rising;//TIM_ICPolarity_BothEdge;
  TIM_ICInitStruct.TIM_ICSelection  = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler  = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter     = 0x00;
  TIM_ICInit(TIM16, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_2;
  //TIM_ICInit(TIM16, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_3;
  //TIM_ICInit(TIM16, &TIM_ICInitStruct);

  //TIM_ICInitStruct.TIM_Channel      = TIM_Channel_4;
  //TIM_ICInit(TIM16, &TIM_ICInitStruct);

  //Set DMA.
  //DMA Remap Set.
  SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM16, ENABLE);

  //Regular Channels DMA Configuration functions.
  //Reset DMA1 -- Channel6 for Cap.
  DMA_DeInit(DMA1_Channel6);
  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(TIM16->CCR1);
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr1;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Low;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel6, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel6, ENABLE);

  TIM_DMAConfig(TIM16, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM16, TIM_DMA_CC1, ENABLE);
  TIM_DMACmd(TIM16, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIM16, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM1_UP_TIM16_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Flags.
  TIM16->SR |= 0xffffffff;

  TIM_ITConfig(TIM16, TIM_IT_CC1, DISABLE);
  TIM_ITConfig(TIM16, TIM_IT_CC2, DISABLE);
  TIM_ITConfig(TIM16, TIM_IT_CC3, DISABLE);
  TIM_ITConfig(TIM16, TIM_IT_CC4, DISABLE);

  //Disable Timer16.
  TIM_Cmd(TIM16, ENABLE);
}

/* Timer17 Counter Init.
*/
void Timer17_Counter_Init(uint32_t           Timer_Compare,
                          FunctionalState    Compare_Int_En
                         )
{ //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer17 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);

  //Reset Timer17 Setup.
  TIM_DeInit(TIM17);

  //Disable Timer.
  TIM_Cmd(TIM17, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM17, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV4;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM17, &TIM_TimeBaseInitStruct);

  //Set Top Data.
  //TIM_SetAutoreload(TIM17, 0xffffff);

  //TIM_UpdateDisableConfig(TIM17, DISABLE);
  //TIM_UpdateRequestConfig(TIM17, TIM_UpdateSource_Regular);

  TIM_ARRPreloadConfig(TIM17, ENABLE);
  //TIM_SelectOnePulseMode(TIM17, TIM_OPMode_Repetitive);
  //TIM_SetClockDivision(TIM17, TIM_CKD_DIV1);

  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = Timer_Compare;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM17, &TIM_OCInitStruct);
  //TIM_OC2Init(TIM17, &TIM_OCInitStruct);
  //TIM_OC3Init(TIM17, &TIM_OCInitStruct);
  //TIM_OC4Init(TIM17, &TIM_OCInitStruct);

  //Timer DMA Setup.
  TIM_DMAConfig(TIM17, TIM_DMABase_ARR, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIM17, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIM17, ENABLE);

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = TIM1_TRG_COM_TIM17_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM17, TIM_FLAG_CC1);
  TIM_ITConfig(TIM17, TIM_IT_Update, Compare_Int_En);

  //Enable Timer17.
  TIM_Cmd(TIM17, ENABLE);
}

/* TIMx Set As A Counter.
*/
void Timerx_Counter_Init(TIM_TypeDef *      TIMx,
                         uint32_t           Timer_Compare,
                         FunctionalState    Compare_Int_En,
                         FunctionalState    Update_Int_En
                        )
{ //Get System Clocks.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timerx Clock.
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx, ENABLE);

  //Reset Timerx Setup.
  TIM_DeInit(TIMx);

  //Disable Timer.
  TIM_Cmd(TIMx, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIMx, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0; //64M Clock.
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);

  TIM_UpdateDisableConfig(TIMx, DISABLE);
  //TIM_UpdateRequestConfig(TIMx, TIM_UpdateSource_Regular);

  TIM_ARRPreloadConfig(TIMx, ENABLE);
  //TIM_SelectOnePulseMode(TIMx, TIM_OPMode_Repetitive);
  //TIM_SetClockDivision(TIMx, TIM_CKD_DIV1);

  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = Timer_Compare;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIMx, &TIM_OCInitStruct);
  //TIM_OC2Init(TIMx, &TIM_OCInitStruct);
  //TIM_OC3Init(TIMx, &TIM_OCInitStruct);
  //TIM_OCxInit(TIMx, &TIM_OCInitStruct);

  //Timer DMA Setup.
  TIM_DMAConfig(TIMx, TIM_DMABase_ARR, TIM_DMABurstLength_1Transfer);
  TIM_DMACmd(TIMx, TIM_DMA_Update, ENABLE);
  TIM_SelectCCDMA(TIMx, ENABLE);

  //Interrupt Setup.
  TIM_ClearFlag(TIMx, TIM_FLAG_CC1);
  TIM_ITConfig(TIMx, TIM_IT_CC1, Compare_Int_En);
  TIM_ITConfig(TIMx, TIM_IT_Update, Update_Int_En);

  //Enable Timerx.
  TIM_Cmd(TIMx, ENABLE);
}

/* Timer17 init for Capture function.
*/
#if 0
void Timer17_Capture_Init(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  //Enable Timer17 Clock.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);

  //Reset Timer17 Setup.
  TIM_DeInit(TIM17);

  //Disable Timer.
  TIM_Cmd(TIM17, DISABLE);

  //Clear Counter.
  TIM_SetCounter(TIM17, 0);

  //Timer Base Init.
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Period            = 0xffff;
  TIM_TimeBaseInitStruct.TIM_Prescaler         = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM17, &TIM_TimeBaseInitStruct);

  //Set Auto Reload Data.
  //TIM_SetAutoreload(TIM17, 0xffffff);

  //TIM_UpdateDisableConfig(TIM17, DISABLE);
  //TIM_UpdateRequestConfig(TIM17, TIM_UpdateSource_Regular);

  //TIM_ARRPreloadConfig(TIM17, ENABLE);
  //TIM_SelectOnePulseMode(TIM17, TIM_OPMode_Single);
  //TIM_SetClockDivision(TIM17, TIM_CKD_DIV1);

  //Set Timer Capture Struct.
  TIM_ICInitTypeDef TIM_ICInitStruct;
  TIM_ICInitStruct.TIM_Channel     = TIM_Channel_1;
  TIM_ICInitStruct.TIM_ICPolarity  = TIM_ICPolarity_BothEdge;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter    = 0x00;
  TIM_ICInit(TIM17, &TIM_ICInitStruct)

  //Pins Configuration.

  //Interrupt Setup.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel         = TIM17_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM17, TIM_FLAG_CC1);
  TIM_ITConfig(TIM17, TIM_IT_Update, ENABLE);

  //Enable Timer17.
  TIM_Cmd(TIM17, DISABLE);
}
#endif
/* Timer Init as a Capture.
*/
void Timer_x_Capture_Init()
{


}

/* Timer Init as PWM Output.
*/
void Timer_x_PWM_Init()
{


}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

