/*This is the DMA functions.
File name :DMA.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "DMA.h"

//Init DMA1.
void DMA1_Init( uint32_t             DMA_Peripheral_Addr,
                uint32_t             DMA_Memory_Addr,
                uint32_t             PeripheralDataSize,
                uint32_t             MemoryDataSize,
                uint32_t             Priority_Level,
                DMA_Channel_TypeDef* DMA1_Channelx
              )
{ //Enable DMA Clock.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  //Reset DMA1
  DMA_DeInit(DMA1_Channelx);

  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = DMA_Peripheral_Addr;
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = PeripheralDataSize;
  DMA_InitStruct.DMA_MemoryDataSize     = MemoryDataSize;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = Priority_Level;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channelx, &DMA_InitStruct);

  DMA_Cmd(DMA1_Channelx, ENABLE);

  //Interrupts and flags management functions
  //FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
  //Clear All Flags.
  DMA1->IFCR |= 0xffffffff;

  //ITStatus DMA_GetITStatus(uint32_t DMAy_IT);

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;

  switch((uint32_t)DMA1_Channelx)
  {
    case (uint32_t)DMA1_Channel1: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; break;
    case (uint32_t)DMA1_Channel2: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn; break;
    case (uint32_t)DMA1_Channel3: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn; break;
    case (uint32_t)DMA1_Channel4: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn; break;
    case (uint32_t)DMA1_Channel5: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn; break;
    case (uint32_t)DMA1_Channel6: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn; break;
    case (uint32_t)DMA1_Channel7: NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn; break;
  }

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  DMA_ITConfig(DMA1_Channelx, DMA_IT_TC, DISABLE);
  DMA_ITConfig(DMA1_Channelx, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA1_Channelx, DMA_IT_TE, DISABLE);
}

//Init DMA2.
void DMA2_Init( uint32_t             DMA_Peripheral_Addr,
                uint32_t             DMA_Memory_Addr,
                uint32_t             PeripheralDataSize,
                uint32_t             MemoryDataSize,
                DMA_Channel_TypeDef* DMA2_Channelx
              )
{ //Enable DMA Clock.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

  //Reset DMA2
  DMA_DeInit(DMA2_Channelx);

  // Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = DMA_Peripheral_Addr;
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralDST;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = PeripheralDataSize;
  DMA_InitStruct.DMA_MemoryDataSize     = MemoryDataSize;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Low;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA2_Channelx, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channelx, ENABLE);


  //Interrupts and flags management functions
  //FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
  //Clear All Flags.
  DMA2->IFCR |= 0xffffffff;

  //ITStatus DMA_GetITStatus(uint32_t DMAy_IT);

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;

  switch((uint32_t)DMA2_Channelx)
  {
    case (uint32_t)DMA2_Channel1: NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel1_IRQn; break;
    case (uint32_t)DMA2_Channel2: NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel2_IRQn; break;
    case (uint32_t)DMA2_Channel3: NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel3_IRQn; break;
    case (uint32_t)DMA2_Channel4: NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel4_IRQn; break;
    case (uint32_t)DMA2_Channel5: NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel5_IRQn; break;
  }

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  DMA_ITConfig(DMA2_Channelx, DMA_IT_TC, DISABLE);
  DMA_ITConfig(DMA2_Channelx, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channelx, DMA_IT_TE, DISABLE);
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

