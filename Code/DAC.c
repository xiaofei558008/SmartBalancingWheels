/*This is the DAC functions.
File name :DAC.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "DAC.h"

//Init DAC1.
void DAC1_Init(void)
{ //Enable DAC1 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //DAC GPIO Pins Set.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Reset DAC1.
  DAC_DeInit(DAC1);

  //DAC1 Init.
  DAC_InitTypeDef DAC_InitStruct;
  DAC_InitStruct.DAC_Trigger                      = DAC_Trigger_None;
  DAC_InitStruct.DAC_WaveGeneration               = DAC_WaveGeneration_None;
  DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  DAC_InitStruct.DAC_Buffer_Switch                = DAC_BufferSwitch_Enable;
  DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStruct);
  DAC_Init(DAC1, DAC_Channel_2, &DAC_InitStruct);

  //Enable DAC1.
  DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
  DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);

  //Software Trigger Set.
  DAC_SoftwareTriggerCmd(DAC1, DAC_Channel_1, DISABLE);
  DAC_DualSoftwareTriggerCmd(DAC1, DISABLE);

  //Wave Generate Set.
  DAC_WaveGenerationCmd(DAC1, DAC_Channel_1, DAC_Wave_Noise, DISABLE);

  //Set Channels Data.
  //DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 2047);
  //DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, 2047);
  //DAC_SetDualChannelData(DAC1, DAC_Align_12b_R, 2047, 2047);
  //uint16_t DAC_GetDataOutputValue(DAC1, DAC_Channel_1);

  // Interrupts and flags management functions.
  //DAC Flags Clear.
  //FlagStatus DAC_GetFlagStatus(DAC1, DAC_Channel_1, uint32_t DAC_FLAG);
  DAC_ClearFlag(DAC1, DAC_Channel_1, DAC_FLAG_DMAUDR);
  DAC_ClearFlag(DAC1, DAC_Channel_2, DAC_FLAG_DMAUDR);

  //ITStatus DAC_GetITStatus(DAC1, DAC_Channel_1, uint32_t DAC_IT);
  DAC_ClearITPendingBit(DAC1, DAC_Channel_1, DAC_IT_DMAUDR);
  DAC_ClearITPendingBit(DAC1, DAC_Channel_2, DAC_IT_DMAUDR);

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM6_DAC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  DAC_ITConfig(DAC1, DAC_Channel_1, DAC_IT_DMAUDR, DISABLE);
  DAC_ITConfig(DAC1, DAC_Channel_2, DAC_IT_DMAUDR, DISABLE);
}

//Init DAC1.
void DAC1_DMA_Init(uint32_t RAM_Addr_DAC1_CH1,
                   uint32_t RAM_Addr_DAC1_CH2
                  )
{ //Enable DAC1 Clock.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //DAC GPIO Pins Set.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Reset DAC1.
  DAC_DeInit(DAC1);

  //DAC1 Init.
  DAC_InitTypeDef DAC_InitStruct;
  DAC_InitStruct.DAC_Trigger                      = DAC_Trigger_None;
  DAC_InitStruct.DAC_WaveGeneration               = DAC_WaveGeneration_None;
  DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  DAC_InitStruct.DAC_Buffer_Switch                = DAC_BufferSwitch_Enable;
  DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStruct);
  DAC_Init(DAC1, DAC_Channel_2, &DAC_InitStruct);

  //Enable DAC1.
  DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
  DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);

  //Software Trigger Set.
  DAC_SoftwareTriggerCmd(DAC1, DAC_Channel_1, DISABLE);
  DAC_DualSoftwareTriggerCmd(DAC1, DISABLE);

  //Wave Generate Set.
  DAC_WaveGenerationCmd(DAC1, DAC_Channel_1, DAC_Wave_Noise, DISABLE);

  //Set Channels Data.
  //DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 2047);
  //DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, 2047);
  //DAC_SetDualChannelData(DAC1, DAC_Align_12b_R, 2047, 2047);
  //uint16_t DAC_GetDataOutputValue(DAC1, DAC_Channel_1);

  // DMA management functions.
/*
  //Regular Channels DMA Configuration functions.
  //Reset DMA1
  DMA_DeInit(DMA1_Channel3);
  DMA_DeInit(DMA1_Channel4);

  //DMA Remap Set.
  SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM6DAC1Ch1, ENABLE);
  SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM7DAC1Ch2, ENABLE);

  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(DAC1->DHR12R1);
  DMA_InitStruct.DMA_MemoryBaseAddr     = RAM_Addr_DAC1_CH1;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralDST;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Low;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;

  //Set DMA Channel3 DAC1 CH1.
  DMA_Init(DMA1_Channel3, &DMA_InitStruct);

  //Set DMA Channel4 DAC1 CH2.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(DAC1->DHR12R2);
  DMA_InitStruct.DMA_MemoryBaseAddr     = RAM_Addr_DAC1_CH2;
  DMA_Init(DMA1_Channel4, &DMA_InitStruct);

  DMA_Cmd(DMA1_Channel3, ENABLE);
  DMA_Cmd(DMA1_Channel4, ENABLE);
*/

/*
  //Init DMA2 Channel3 & 4.
  DMA_InitTypeDef DMA_InitStructure;

  DMA_DeInit(DMA2_Channel3);
  DMA_DeInit(DMA2_Channel4);

  //Channel 3 Init.
  DMA_InitStructure.DMA_PeripheralBaseAddr  = 0x40007420;//(uint32_t)&(DAC1->DHR12R1);
  DMA_InitStructure.DMA_MemoryBaseAddr      = RAM_Addr_DAC1_CH1;
  DMA_InitStructure.DMA_DIR                 = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize          = 1;
  DMA_InitStructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc           = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode                = DMA_Mode_Normal;  //DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority            = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M                 = DMA_M2M_Disable;
  DMA_Init(DMA2_Channel3, &DMA_InitStructure);

  //Channel 4 Init.
  DMA_InitStructure.DMA_PeripheralBaseAddr  = (uint32_t)&(DAC1->DHR12R2);
  DMA_InitStructure.DMA_MemoryBaseAddr      = RAM_Addr_DAC1_CH2;
  DMA_Init(DMA2_Channel4, &DMA_InitStructure);

  DMA_Cmd(DMA2_Channel3, ENABLE);
  DMA_Cmd(DMA2_Channel4, ENABLE);

  DAC_DMACmd(DAC1, DAC_Channel_1, ENABLE);
  DAC_DMACmd(DAC1, DAC_Channel_2, ENABLE);
*/

  // Interrupts and flags management functions.
  //DAC Flags Clear.
  //FlagStatus DAC_GetFlagStatus(DAC1, DAC_Channel_1, uint32_t DAC_FLAG);
  DAC_ClearFlag(DAC1, DAC_Channel_1, DAC_FLAG_DMAUDR);
  DAC_ClearFlag(DAC1, DAC_Channel_2, DAC_FLAG_DMAUDR);

  //ITStatus DAC_GetITStatus(DAC1, DAC_Channel_1, uint32_t DAC_IT);
  DAC_ClearITPendingBit(DAC1, DAC_Channel_1, DAC_IT_DMAUDR);
  DAC_ClearITPendingBit(DAC1, DAC_Channel_2, DAC_IT_DMAUDR);

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = TIM6_DAC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  DAC_ITConfig(DAC1, DAC_Channel_1, DAC_IT_DMAUDR, DISABLE);
  DAC_ITConfig(DAC1, DAC_Channel_2, DAC_IT_DMAUDR, DISABLE);
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

