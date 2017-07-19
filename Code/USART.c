/*This is the USART functions.
File name :USART.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "USART.h"

/* USART1 Init.
*/
void USART1_Init(uint32_t Baud_Rate)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  //Setup USART GPIOs.
  //Tx Pin PB6.
  //Rx Pin PB7.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Set as USART output.
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_7);

  //Reset USART1.
  USART_DeInit(USART1);

  //Disable USART1.
  USART_Cmd(USART1, DISABLE);

  //Set USART1 Prescaler.
  USART_SetPrescaler(USART1, 0x00);

  //Set OverSampling.
  USART_OverSampling8Cmd(USART1, ENABLE);

  //Set One bit Method.
  USART_OneBitMethodCmd(USART1, ENABLE);

  //Init USART1.
  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_BaudRate   = Baud_Rate;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits   = USART_StopBits_1;
  USART_InitStruct.USART_Parity     = USART_Parity_No ;
  USART_InitStruct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStruct);

  //Init USART1 Clock.
  USART_ClockInitTypeDef USART_ClockInitStruct;
  USART_ClockInitStruct.USART_Clock   = USART_Clock_Disable;
  USART_ClockInitStruct.USART_CPOL    = USART_CPOL_Low;
  USART_ClockInitStruct.USART_CPHA    = USART_CPHA_1Edge;
  USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;
  USART_ClockInit(USART1, &USART_ClockInitStruct);

  // Interrupts and flags management functions.
  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Int Flags.
  USART1->ISR |= 0xffffffff;

  //Set USART1 Int.
  USART_ITConfig(USART1, USART_IT_CTS,  DISABLE);
  USART_ITConfig(USART1, USART_IT_LBD,  DISABLE);
  USART_ITConfig(USART1, USART_IT_TXE,  DISABLE);
  USART_ITConfig(USART1, USART_IT_TC,   DISABLE);
  USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
  USART_ITConfig(USART1, USART_IT_PE,   DISABLE);
  USART_ITConfig(USART1, USART_IT_ERR,  DISABLE);

  //Enable USART1.
  USART_Cmd(USART1, ENABLE);
}

/* USART2 Init.
*/
void USART2_Init(uint32_t Baud_Rate)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  // Setup USART GPIOs.
  //Tx Pin PA2.
  //Rx Pin PA3.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Set as USART output.
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);

  //Reset USART2.
  USART_DeInit(USART2);

  //Disable USART2.
  USART_Cmd(USART2, DISABLE);

  //Set USART2 Prescaler.
  USART_SetPrescaler(USART2, 0x00);

  //Set OverSampling.
  USART_OverSampling8Cmd(USART2, ENABLE);

  //Set One bit Method.
  USART_OneBitMethodCmd(USART2, ENABLE);

  //Init USART2.
  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_BaudRate   = Baud_Rate;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits   = USART_StopBits_1;
  USART_InitStruct.USART_Parity     = USART_Parity_No;
  USART_InitStruct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART2, &USART_InitStruct);

  //Init USART2 Clock.
  USART_ClockInitTypeDef USART_ClockInitStruct;
  USART_ClockInitStruct.USART_Clock   = USART_Clock_Disable;
  USART_ClockInitStruct.USART_CPOL    = USART_CPOL_Low;
  USART_ClockInitStruct.USART_CPHA    = USART_CPHA_1Edge;
  USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;
  USART_ClockInit(USART2, &USART_ClockInitStruct);

  // Interrupts and flags management functions.
  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Int Flags.
  USART2->ISR |= 0xffffffff;

  //Set USART2 Int.
  USART_ITConfig(USART2, USART_IT_CTS,  DISABLE);
  USART_ITConfig(USART2, USART_IT_LBD,  DISABLE);
  USART_ITConfig(USART2, USART_IT_TXE,  DISABLE);
  USART_ITConfig(USART2, USART_IT_TC,   DISABLE);
  USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);
  USART_ITConfig(USART2, USART_IT_PE,   DISABLE);
  USART_ITConfig(USART2, USART_IT_ERR,  DISABLE);

  //Enable USART2.
  USART_Cmd(USART2, ENABLE);
}

/* USART3 Init.
*/
void USART3_Init(uint32_t Baud_Rate)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  //Setup USART GPIOs.
  //Tx Pin PB10.
  //Rx Pin PB11.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //Set as USART output.
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_7);

  //Reset USART3.
  USART_DeInit(USART3);

  //Disable USART3.
  USART_Cmd(USART3, DISABLE);

  //Set USART3 Prescaler.
  USART_SetPrescaler(USART3, 0x00);

  //Set OverSampling.
  USART_OverSampling8Cmd(USART3, ENABLE);

  //Set One bit Method.
  USART_OneBitMethodCmd(USART3, ENABLE);

  //Init USART3.
  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_BaudRate   = Baud_Rate;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits   = USART_StopBits_1;
  USART_InitStruct.USART_Parity     = USART_Parity_No;
  USART_InitStruct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART3, &USART_InitStruct);

  //Init USART3 Clock.
  USART_ClockInitTypeDef USART_ClockInitStruct;
  USART_ClockInitStruct.USART_Clock   = USART_Clock_Disable;
  USART_ClockInitStruct.USART_CPOL    = USART_CPOL_Low;
  USART_ClockInitStruct.USART_CPHA    = USART_CPHA_1Edge;
  USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;
  USART_ClockInit(USART3, &USART_ClockInitStruct);

  // Interrupts and flags management functions.
  //Set NVIC.
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                    = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Clear All Int Flags.
  USART3->ISR |= 0xffffffff;

  //Set USART3 Int.
  USART_ITConfig(USART3, USART_IT_CTS,  DISABLE);
  USART_ITConfig(USART3, USART_IT_LBD,  DISABLE);
  USART_ITConfig(USART3, USART_IT_TXE,  DISABLE);
  USART_ITConfig(USART3, USART_IT_TC,   DISABLE);
  USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART3, USART_IT_IDLE, DISABLE);
  USART_ITConfig(USART3, USART_IT_PE,   DISABLE);
  USART_ITConfig(USART3, USART_IT_ERR,  DISABLE);

  //Enable USART3.
  USART_Cmd(USART3, ENABLE);
}

/* Send A Byte.
*/
uint8_t USART_Byte_In(USART_TypeDef* USARTx)
{
  //Waiting For The Data In.
  while((USARTx->ISR & 0x20) == 0);
  //Get Data.
  return USARTx->TDR;
}

/* Receive A Byte.
*/
void USART_Byte_Out(USART_TypeDef* USARTx,
                    uint8_t        Data_Temp
                   )
{ while((USARTx->ISR & 0x40) == 0);
  USARTx->RDR = Data_Temp;
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

