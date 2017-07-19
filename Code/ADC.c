/*This is the ADC functions.
File name :ADC.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "ADC.h"

/* Init ADC.
*/
void ADC1_Init(uint32_t DMA_Memory_Addr)
{
  //Enable ADC Clock.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  //ADC GPIO Pins Set.
  //PA0 A1 A2 A3 A6.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //PC0 C1.
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOC, &GPIO_InitStruct_Temp);

  //Reset ADC1.
  ADC_DeInit(ADC1);

  //Enable ADC Voltage Regulator.
  ADC_VoltageRegulatorCmd(ADC1, ENABLE);

  //Start ADC1 Calibration.
  ADC_StartCalibration(ADC1);

  //Waiting Calibration Finished.
  while(ADC1->CR & ADC_CR_ADCAL);

  //ADC Regular Init Struct.
  ADC_InitTypeDef ADC_InitStruct;
  ADC_InitStruct.ADC_ContinuousConvMode    = DISABLE;
  ADC_InitStruct.ADC_Resolution            = ADC_Resolution_12b;
  ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_9; //Update Trigger.
  ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_FallingEdge;
  ADC_InitStruct.ADC_DataAlign             = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_OverrunMode           = DISABLE;
  ADC_InitStruct.ADC_AutoInjMode           = DISABLE;
  ADC_InitStruct.ADC_NbrOfRegChannel       = 2;
  ADC_Init(ADC1, &ADC_InitStruct);

  //ADC1 Common Init Struct.
  ADC_CommonInitTypeDef ADC_CommonInitStruct;
  ADC_CommonInitStruct.ADC_Mode             = ADC_Mode_Independent;
  ADC_CommonInitStruct.ADC_Clock            = ADC_Clock_AsynClkMode;
  ADC_CommonInitStruct.ADC_DMAAccessMode    = ADC_DMAAccessMode_1;
  ADC_CommonInitStruct.ADC_DMAMode          = ADC_DMAMode_Circular;
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = 0;
  ADC_CommonInit(ADC1, &ADC_CommonInitStruct);

  //Auto Dealy Set.
  ADC_AutoDelayCmd(ADC1, ENABLE);

  // Temperature Sensor, Vrefint and Vbat management function
  ADC_TempSensorCmd(ADC1, DISABLE);
  ADC_VrefintCmd(ADC1, DISABLE);
  ADC_VbatCmd(ADC1, DISABLE);

  // Channels Configuration functions.
  //(12.5 + x) Clocks.
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_1Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_1Cycles5);
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_601Cycles5);
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_61Cycles5);
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_61Cycles5);
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_61Cycles5);
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 7, ADC_SampleTime_61Cycles5);

  //ADC Offset Set.
  ADC_SetChannelOffset1(ADC1, ADC_Channel_1,0);
  ADC_SetChannelOffset2(ADC1, ADC_Channel_1,0);
  ADC_SetChannelOffset3(ADC1, ADC_Channel_1,0);
  ADC_SetChannelOffset4(ADC1, ADC_Channel_1,0);
  ADC_ChannelOffset1Cmd(ADC1, DISABLE);
  ADC_ChannelOffset2Cmd(ADC1, DISABLE);
  ADC_ChannelOffset3Cmd(ADC1, DISABLE);
  ADC_ChannelOffset4Cmd(ADC1, DISABLE);

  //Regular Channels DMA Configuration functions.
  //Reset DMA1
  DMA_DeInit(DMA1_Channel1);

  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = DMA_Memory_Addr;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 2;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;//DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);

  DMA_Cmd(DMA1_Channel1, ENABLE);

  //Interrupts and flags management functions
  //Clear All Flags.
  DMA1->IFCR |= 0xffffffff;

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA1_Channel1, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TE, DISABLE);

  ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC1, ENABLE);

  //Clear All The Dual ADC Common Flags.
  ADC1_2->CSR = 0xffffffff;

  // Interrupts and flags management functions.
  //Clear All Flags.
  ADC1->ISR |= 0xffffffff;

  //Set NVIC.
  NVIC_InitStructure.NVIC_IRQChannel                    = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  ADC_ITConfig(ADC1, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD1,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JQOVF, DISABLE);

  //Enable ADC1.
  ADC_Cmd(ADC1, ENABLE);

  //wait for ADRDY
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY));

  //Start ADC Convert.
  ADC_StartConversion(ADC1);
}

/* OPAMP1 -- ADC1-CH3
   OPAMP2 -- ADC2-CH3
   OPAMP3 -- ADC3-CH1
   OPAMP4 -- ADC4-CH3
*/
void ADC_OPAMP_DMA_Init(uint32_t ADC1_DMA_Addr,
                        uint32_t ADC2_DMA_Addr,
                        uint32_t ADC3_DMA_Addr,
                        uint32_t ADC4_DMA_Addr
                       )
{ //Enable Clock.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,  ENABLE);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  //GPIO Init.
  //Port A0/A1/A7.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Port B0/B11/B13/B14.
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Reset ADC.
  ADC_DeInit(ADC1);
  ADC_DeInit(ADC2);
  ADC_DeInit(ADC3);
  ADC_DeInit(ADC4);

  //Enable ADC Voltage Regulator.
  ADC_VoltageRegulatorCmd(ADC1, ENABLE);
  ADC_VoltageRegulatorCmd(ADC2, ENABLE);
  ADC_VoltageRegulatorCmd(ADC3, ENABLE);
  ADC_VoltageRegulatorCmd(ADC4, ENABLE);

  //Start ADC Calibration.
  ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
  ADC_SelectCalibrationMode(ADC2, ADC_CalibrationMode_Single);
  ADC_SelectCalibrationMode(ADC3, ADC_CalibrationMode_Single);
  ADC_SelectCalibrationMode(ADC4, ADC_CalibrationMode_Single);

  ADC_StartCalibration(ADC1);
  ADC_StartCalibration(ADC2);
  ADC_StartCalibration(ADC3);
  ADC_StartCalibration(ADC4);

  //Waiting Calibration Finished.
  while(ADC1->CR & ADC_CR_ADCAL);
  while(ADC2->CR & ADC_CR_ADCAL);
  while(ADC3->CR & ADC_CR_ADCAL);
  while(ADC4->CR & ADC_CR_ADCAL);

  //ADC Regular Init Struct.
  ADC_InitTypeDef ADC_InitStruct;
  ADC_InitStruct.ADC_ContinuousConvMode    = DISABLE;
  ADC_InitStruct.ADC_Resolution            = ADC_Resolution_12b;
  ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_10;          //TIM1 TRGO2.
  ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;  //ADC_ExternalTrigEventEdge_BothEdge;
  ADC_InitStruct.ADC_DataAlign             = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_OverrunMode           = DISABLE;
  ADC_InitStruct.ADC_AutoInjMode           = DISABLE;
  ADC_InitStruct.ADC_NbrOfRegChannel       = 1;
  ADC_Init(ADC1, &ADC_InitStruct);
  ADC_Init(ADC2, &ADC_InitStruct);

  ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_8;           //TIM8 TRGO2.
  ADC_Init(ADC3, &ADC_InitStruct);
  ADC_Init(ADC4, &ADC_InitStruct);

  //ADC1 Common Init Struct.
  ADC_CommonInitTypeDef ADC_CommonInitStruct;
  ADC_CommonInitStruct.ADC_Mode             = ADC_Mode_Independent;
  ADC_CommonInitStruct.ADC_Clock            = ADC_Clock_SynClkModeDiv1;
  ADC_CommonInitStruct.ADC_DMAAccessMode    = ADC_DMAAccessMode_1;
  ADC_CommonInitStruct.ADC_DMAMode          = ADC_DMAMode_Circular;
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = 0;
  ADC_CommonInit(ADC1, &ADC_CommonInitStruct);
  ADC_CommonInit(ADC2, &ADC_CommonInitStruct);
  ADC_CommonInit(ADC3, &ADC_CommonInitStruct);
  ADC_CommonInit(ADC4, &ADC_CommonInitStruct);

  //Auto Dealy Set.
  //ADC_AutoDelayCmd(ADC1, ENABLE);
  //ADC_AutoDelayCmd(ADC2, ENABLE);
  //ADC_AutoDelayCmd(ADC3, ENABLE);
  //ADC_AutoDelayCmd(ADC4, ENABLE);

  // Channels Configuration functions.
  //(12.5 + x) Clocks.

  ////ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_7Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_7Cycles5);
  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime_7Cycles5);
  ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 1, ADC_SampleTime_7Cycles5);
  ADC_RegularChannelConfig(ADC4, ADC_Channel_3, 1, ADC_SampleTime_7Cycles5);

  //ADC Offset Set.
  //ADC_SetChannelOffset1(ADC1, ADC_Channel_1,0);
  //ADC_ChannelOffset1Cmd(ADC1, DISABLE);

  //Set DMA Remap.
  //SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM6DAC1Ch1, ENABLE);
  //SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM7DAC1Ch2, ENABLE);

  //Regular Channels DMA Configuration functions.
  //Reset DMA1
  DMA_DeInit(DMA1_Channel1);
  DMA_DeInit(DMA2_Channel1);

  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC1_DMA_Addr;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;

  //DMA ADC1 DMA1 - Channel1.
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel1, ENABLE);

  //DMA ADC2 DMA2 - Channel1.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC2->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC2_DMA_Addr;
  DMA_Init(DMA2_Channel1, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channel1, ENABLE);

  //DMA ADC3 DMA2 - Channel5.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC3->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC3_DMA_Addr;
  DMA_Init(DMA2_Channel5, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channel5, ENABLE);

  //DMA ADC4 DMA2 - Channel2.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC4->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC4_DMA_Addr;
  DMA_Init(DMA2_Channel2, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channel2, ENABLE);

  //Interrupts and flags management functions
  //Clear All Flags.
  DMA1->IFCR |= 0xffffffff;
  DMA2->IFCR |= 0xffffffff;

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;

  //DMA1-Ch1
  NVIC_Init(&NVIC_InitStructure);

  //DMA2-Ch1
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA2_Channel1_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //DMA2-Ch5
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA2_Channel5_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //DMA2-Ch2
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA2_Channel2_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  //DMA1 Channel1
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA1_Channel1, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TE, ENABLE);

  //DMA2 Channel1
  DMA_ITConfig(DMA2_Channel1, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA2_Channel1, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channel1, DMA_IT_TE, ENABLE);

  //DMA2 Channel5
  DMA_ITConfig(DMA2_Channel5, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA2_Channel5, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channel5, DMA_IT_TE, ENABLE);

  //DMA2 Channel2
  DMA_ITConfig(DMA2_Channel2, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA2_Channel2, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channel2, DMA_IT_TE, ENABLE);

  //ADC DMA Modes Set.
  ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC1, ENABLE);

  ADC_DMAConfig(ADC2, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC2, ENABLE);

  ADC_DMAConfig(ADC3, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC3, ENABLE);

  ADC_DMAConfig(ADC4, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC4, ENABLE);

  // Interrupts and flags management functions.
  //Clear All Flags.
  ADC1->ISR = 0xffffffff;
  ADC2->ISR = 0xffffffff;
  ADC3->ISR = 0xffffffff;
  ADC4->ISR = 0xffffffff;

  //Set NVIC.
  NVIC_InitStructure.NVIC_IRQChannel                    = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                    = ADC3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                    = ADC4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  ADC_ITConfig(ADC1, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD1,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JQOVF, DISABLE);

  ADC_ITConfig(ADC2, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_JQOVF, DISABLE);

  ADC_ITConfig(ADC3, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_AWD1,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_JQOVF, DISABLE);

  ADC_ITConfig(ADC4, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_JQOVF, DISABLE);

  //Enable ADC.
  ADC_Cmd(ADC1, ENABLE);
  ADC_Cmd(ADC2, ENABLE);
  ADC_Cmd(ADC3, ENABLE);
  ADC_Cmd(ADC4, ENABLE);

  //waiting for ADRDY
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY) == RESET);
  while(ADC_GetFlagStatus(ADC2, ADC_FLAG_RDY) == RESET);
  while(ADC_GetFlagStatus(ADC3, ADC_FLAG_RDY) == RESET);
  while(ADC_GetFlagStatus(ADC4, ADC_FLAG_RDY) == RESET);

  //Start ADC Convert.
  ADC_StartConversion(ADC1);
  ADC_StartConversion(ADC2);
  ADC_StartConversion(ADC3);
  ADC_StartConversion(ADC4);
}

/* OPAMP1 -- ADC1-CH3
   OPAMP2 -- ADC2-CH3
   OPAMP3 -- ADC3-CH1
   OPAMP4 -- ADC4-CH3
*/
void ADC_Inject_OPAMP_Init(void)
{
  //Enable Clock.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,  ENABLE);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  //GPIO Init.
  //Port A0/A1/A7.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Port B0/B11/B13/B14.
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Reset ADC.
  ADC_DeInit(ADC1);
  ADC_DeInit(ADC2);
  ADC_DeInit(ADC3);
  ADC_DeInit(ADC4);

  //Enable ADC Voltage Regulator.
  ADC_VoltageRegulatorCmd(ADC1, ENABLE);
  ADC_VoltageRegulatorCmd(ADC2, ENABLE);
  ADC_VoltageRegulatorCmd(ADC3, ENABLE);
  ADC_VoltageRegulatorCmd(ADC4, ENABLE);

  //Start ADC Calibration.
  ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
  ADC_SelectCalibrationMode(ADC2, ADC_CalibrationMode_Single);
  ADC_SelectCalibrationMode(ADC3, ADC_CalibrationMode_Single);
  ADC_SelectCalibrationMode(ADC4, ADC_CalibrationMode_Single);

  ADC_StartCalibration(ADC1);
  ADC_StartCalibration(ADC2);
  ADC_StartCalibration(ADC3);
  ADC_StartCalibration(ADC4);

  //Waiting Calibration Finished.
  while(ADC1->CR & ADC_CR_ADCAL);
  while(ADC2->CR & ADC_CR_ADCAL);
  while(ADC3->CR & ADC_CR_ADCAL);
  while(ADC4->CR & ADC_CR_ADCAL);

  //ADC Regular & Inject Mode Init Struct.
  //ADC1 & ADC2, ADC3 & ADC4 Works on Dual ADC Mode.
  //Vbus  --ADC1-CH1.
  //ADC Regular Init Struct.
  ADC_InitTypeDef ADC_InitStruct;
  ADC_InitStruct.ADC_ContinuousConvMode    = DISABLE;
  ADC_InitStruct.ADC_Resolution            = ADC_Resolution_12b;
  ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_10;                              //TIM1 TRGO2.
  ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;                      //ADC_ExternalTrigEventEdge_BothEdge;
  ADC_InitStruct.ADC_DataAlign             = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_OverrunMode           = ENABLE;
  ADC_InitStruct.ADC_AutoInjMode           = DISABLE;
  ADC_InitStruct.ADC_NbrOfRegChannel       = 1;
  ADC_Init(ADC1, &ADC_InitStruct);

  //Vbus ADC1-CH1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_61Cycles5);

  //OPAMP1--ADC1-CH3.
  //OPAMP2--ADC2-CH3.
  //OPAMP3--ADC3-CH1.
  //OPAMP4--ADC4-CH3.
  ADC_InjectedInitTypeDef Temp_ADC_InjectedInitStruct;
  Temp_ADC_InjectedInitStruct.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_8; //TIM1-CH4  //ADC_ExternalTrigInjecConvEvent_1;
  Temp_ADC_InjectedInitStruct.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_RisingEdge;
  Temp_ADC_InjectedInitStruct.ADC_NbrOfInjecChannel          = 1;
  Temp_ADC_InjectedInitStruct.ADC_InjecSequence1             = ADC_InjectedChannel_3;                   //OPAMP Channel
  Temp_ADC_InjectedInitStruct.ADC_InjecSequence2             = ADC_InjectedChannel_1;
  Temp_ADC_InjectedInitStruct.ADC_InjecSequence3             = ADC_InjectedChannel_1;
  Temp_ADC_InjectedInitStruct.ADC_InjecSequence4             = ADC_InjectedChannel_1;

  ADC_InjectedInit(ADC1, &Temp_ADC_InjectedInitStruct);                                                 //OPAMP1 Channel-3
  ADC_InjectedInit(ADC2, &Temp_ADC_InjectedInitStruct);                                                 //OPAMP2 Channel-3

  Temp_ADC_InjectedInitStruct.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_10; //TIM8-CH4  //ADC_ExternalTrigInjecConvEvent_4;
  Temp_ADC_InjectedInitStruct.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_RisingEdge;
  Temp_ADC_InjectedInitStruct.ADC_InjecSequence1             = ADC_InjectedChannel_1;                   //OPAMP3 Channel-1
  ADC_InjectedInit(ADC3, &Temp_ADC_InjectedInitStruct);                                                 //TIM8_TRGO2

  Temp_ADC_InjectedInitStruct.ADC_InjecSequence1             = ADC_InjectedChannel_3;                   //OPAMP4 Channel-3
  ADC_InjectedInit(ADC4, &Temp_ADC_InjectedInitStruct);                                                 //TIM8_TRGO2

  //ADC1 Common Init Struct.
  ADC_CommonInitTypeDef ADC_CommonInitStruct;
  ADC_CommonInitStruct.ADC_Mode             = ADC_Mode_InjSimul;            //ADC_Mode_Independent;
  ADC_CommonInitStruct.ADC_Clock            = ADC_Clock_SynClkModeDiv1;
  ADC_CommonInitStruct.ADC_DMAAccessMode    = ADC_DMAAccessMode_1;
  ADC_CommonInitStruct.ADC_DMAMode          = ADC_DMAMode_Circular;
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = 0;
  ADC_CommonInit(ADC1, &ADC_CommonInitStruct);
  ADC_CommonInit(ADC2, &ADC_CommonInitStruct);
  ADC_CommonInit(ADC3, &ADC_CommonInitStruct);
  ADC_CommonInit(ADC4, &ADC_CommonInitStruct);

  //Auto Dealy Set.
  //ADC_AutoDelayCmd(ADC1, ENABLE);
  //ADC_AutoDelayCmd(ADC2, ENABLE);
  //ADC_AutoDelayCmd(ADC3, ENABLE);
  //ADC_AutoDelayCmd(ADC4, ENABLE);

  // Channels Configuration functions.
  //(12.5 + x) Clocks.
  ADC_InjectedChannelSampleTimeConfig(ADC1, ADC_InjectedChannel_3, ADC_SampleTime_7Cycles5);
  ADC_InjectedChannelSampleTimeConfig(ADC2, ADC_InjectedChannel_3, ADC_SampleTime_7Cycles5);
  ADC_InjectedChannelSampleTimeConfig(ADC3, ADC_InjectedChannel_1, ADC_SampleTime_7Cycles5);
  ADC_InjectedChannelSampleTimeConfig(ADC4, ADC_InjectedChannel_3, ADC_SampleTime_7Cycles5);

  //ADC Offset Set.
  //ADC_SetChannelOffset1(ADC1, ADC_Channel_1,0);
  //ADC_ChannelOffset1Cmd(ADC1, DISABLE);

  //Set DMA Remap.
  //SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM6DAC1Ch1, ENABLE);
  //SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM7DAC1Ch2, ENABLE);
#if 0
  //Regular Channels DMA Configuration functions.
  //Reset DMA1
  DMA_DeInit(DMA1_Channel1);
  DMA_DeInit(DMA2_Channel1);

  //Initialization and Configuration functions.
  DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC1_DMA_Addr;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;

  //DMA ADC1 DMA1 - Channel1.
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel1, ENABLE);

  //DMA ADC2 DMA2 - Channel1.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC2->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC2_DMA_Addr;
  DMA_Init(DMA2_Channel1, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channel1, ENABLE);

  //DMA ADC3 DMA2 - Channel5.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC3->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC3_DMA_Addr;
  DMA_Init(DMA2_Channel5, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channel5, ENABLE);

  //DMA ADC4 DMA2 - Channel2.
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC4->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr     = ADC4_DMA_Addr;
  DMA_Init(DMA2_Channel2, &DMA_InitStruct);
  DMA_Cmd(DMA2_Channel2, ENABLE);

  //Interrupts and flags management functions
  //Clear All Flags.
  DMA1->IFCR |= 0xffffffff;
  DMA2->IFCR |= 0xffffffff;

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;

  //DMA1-Ch1
  NVIC_Init(&NVIC_InitStructure);

  //DMA2-Ch1
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA2_Channel1_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //DMA2-Ch5
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA2_Channel5_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //DMA2-Ch2
  NVIC_InitStructure.NVIC_IRQChannel                    = DMA2_Channel2_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  //DMA1 Channel1
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA1_Channel1, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TE, ENABLE);

  //DMA2 Channel1
  DMA_ITConfig(DMA2_Channel1, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA2_Channel1, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channel1, DMA_IT_TE, ENABLE);

  //DMA2 Channel5
  DMA_ITConfig(DMA2_Channel5, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA2_Channel5, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channel5, DMA_IT_TE, ENABLE);

  //DMA2 Channel2
  DMA_ITConfig(DMA2_Channel2, DMA_IT_TC, DISABLE);  //ENABLE
  DMA_ITConfig(DMA2_Channel2, DMA_IT_HT, DISABLE);
  DMA_ITConfig(DMA2_Channel2, DMA_IT_TE, ENABLE);

  //ADC DMA Modes Set.
  ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC1, ENABLE);

  ADC_DMAConfig(ADC2, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC2, ENABLE);

  ADC_DMAConfig(ADC3, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC3, ENABLE);

  ADC_DMAConfig(ADC4, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC4, ENABLE);
#endif

  // Interrupts and flags management functions.
  //Clear All Flags.
  ADC1->ISR = 0xffffffff;
  ADC2->ISR = 0xffffffff;
  ADC3->ISR = 0xffffffff;
  ADC4->ISR = 0xffffffff;

  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                    = ADC3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                    = ADC4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  ADC_ITConfig(ADC1, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JEOC,  ENABLE );     //ADC-1.2
  ADC_ITConfig(ADC1, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD1,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC1, ADC_IT_JQOVF, DISABLE);

  ADC_ITConfig(ADC2, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC2, ADC_IT_JQOVF, DISABLE);

  ADC_ITConfig(ADC3, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_JEOC,  ENABLE );     //ADC-3.4
  ADC_ITConfig(ADC3, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_AWD1,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC3, ADC_IT_JQOVF, DISABLE);

  ADC_ITConfig(ADC4, ADC_IT_RDY,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_EOSMP, DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_EOC,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_EOS,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_OVR,   DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_JEOC,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_JEOS,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_AWD2,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_AWD3,  DISABLE);
  ADC_ITConfig(ADC4, ADC_IT_JQOVF, DISABLE);

  //Enable ADC.
  ADC_Cmd(ADC1, ENABLE);
  ADC_Cmd(ADC2, ENABLE);
  ADC_Cmd(ADC3, ENABLE);
  ADC_Cmd(ADC4, ENABLE);

  //waiting for ADRDY
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY) == RESET);
  while(ADC_GetFlagStatus(ADC2, ADC_FLAG_RDY) == RESET);
  while(ADC_GetFlagStatus(ADC3, ADC_FLAG_RDY) == RESET);
  while(ADC_GetFlagStatus(ADC4, ADC_FLAG_RDY) == RESET);

  //Start ADC Convert.
  ADC_StartConversion(ADC1);            //Vbus.
  //ADC_StartConversion(ADC2);
  //ADC_StartConversion(ADC3);
  //ADC_StartConversion(ADC4);

  ADC_StartInjectedConversion(ADC1);    //Motor A. ADC1 & ADC2
  ADC_StartInjectedConversion(ADC3);    //Motor B. ADC3 & ADC4.
}

/* ADC Convert.
*/
uint16_t ADC_Convert_One_Channel(uint32_t ADC_Channel_Sel)
{
/*
  //Set Channel.
  ADC1->CHSELR &= 0x00000000;
  ADC1->CHSELR |= ADC_Channel_Sel;

  //Start to Convert.
  ADC1->CR |= ADC_CR_ADSTART;

  //Waiting for Convert Finished.
  while((ADC1->ISR & ADC_FLAG_EOC) == 0);
*/
  return(ADC1->DR);
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

