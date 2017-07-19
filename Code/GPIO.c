/*This is the GPIO functions.
File name :GPIO.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "GPIO.h"

void GPIO_Ports_Init(void)
{
  //Enable GPIO Clocks.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_IN;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //GPIO Interrupt Set.
  //Int Set.
  //NVIC_InitTypeDef NVIC_InitStructure;
  //NVIC_InitStructure.NVIC_IRQChannel                    = EXTI9_5_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  //NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);

  //NVIC_InitStructure.NVIC_IRQChannel                    = EXTI15_10_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
  //NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);

/*
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);

  //Set External Int.
  EXTI_InitTypeDef EXTI_InitStruct;
  EXTI_InitStruct.EXTI_Line    = EXTI_Line11;
  EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStruct);
*/
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

