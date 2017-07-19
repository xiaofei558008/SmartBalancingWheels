/*This is the SPI functions.
File name :SPI.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-11-11 10:50:28
*/

#include "SPI.h"

/* SPI1 Init.
*/
void SPI1_Init(void)
{
  //Clock Enable.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  //GPIO Init.
  //PA15 -- NSS
  //PB3  -- SCK
  //PB5  -- MOSI
  //GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3,  GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5,  GPIO_AF_5);

  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_3;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_5;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_15;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Set CS High.
  GPIO_SetBits(GPIOA, GPIO_Pin_15);

  //Reset SPI1.
  SPI_I2S_DeInit(SPI1);

  //Disable SPI1.
  SPI_Cmd(SPI1, DISABLE);

  //SPI Init.
  SPI_InitTypeDef SPI_InitStruct;
  SPI_InitStruct.SPI_Direction         = SPI_Direction_1Line_Tx;
  SPI_InitStruct.SPI_Mode              = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize          = SPI_DataSize_16b;
  SPI_InitStruct.SPI_CPOL              = SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA              = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS               = SPI_NSS_Soft;//SPI_NSS_Hard;//
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  SPI_InitStruct.SPI_FirstBit          = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial     = 7;
  SPI_Init(SPI1, &SPI_InitStruct);

  //SPI_TIModeCmd(SPI1, ENABLE);

  //SPI_NSSPulseModeCmd(SPI1, ENABLE);
  //SPI_SSOutputCmd(SPI1, ENABLE);
  SPI_Cmd(SPI1, ENABLE);

  //SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_HF);

  //SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_Tx);

  //SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Reset);

  //SPI_SendData8(SPI1, uint8_t Data);
  //uint8_t SPI_ReceiveData8(SPI1);

  //CRC Config.
  //SPI_CRCLengthConfig(SPI1, SPI_CRCLength_16b);
  //SPI_CalculateCRC(SPI1, ENABLE);
  //SPI_TransmitCRC(SPI1);
  //uint16_t SPI_GetCRC(SPI1, uint8_t SPI_CRC);
  //uint16_t SPI_GetCRCPolynomial(SPI1);

  //DMA Config.
  //SPI_LastDMATransferCmd(SPI1, uint16_t SPI_LastDMATransfer);

  //IRQ Set.
  //Interrupt Setup.
/*
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  SPI_I2S_ITConfig(SPI1, uint8_t SPI_I2S_IT, ENABLE);
   SPI_GetTransmissionFIFOStatus(SPI1);
   SPI_GetReceptionFIFOStatus(SPI1);
  FlagStatus SPI_I2S_GetFlagStatus(SPI1, uint16_t SPI_I2S_FLAG);
  SPI_I2S_ClearFlag(SPI1, uint16_t SPI_I2S_FLAG);
  ITStatus SPI_I2S_GetITStatus(SPI1, uint8_t SPI_I2S_IT);
*/
}

/* SPI2 Init.
*/
void SPI2_Init(void)
{
  //Clock Enable.
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,  ENABLE);

  //GPIO Init.
  //PC4  -- NSS
  //PB13 -- SCK
  //PB15 -- MOSI
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13,  GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15,  GPIO_AF_5);

  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_13;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_15;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_4;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_Init(GPIOC, &GPIO_InitStruct_Temp);

  //Set CS High.
  GPIO_SetBits(GPIOC, GPIO_Pin_4);

  //Reset SPI1.
  SPI_I2S_DeInit(SPI2);

  //Disable SPI1.
  SPI_Cmd(SPI2, DISABLE);

  //SPI Init.
  SPI_InitTypeDef SPI_InitStruct;
  SPI_InitStruct.SPI_Direction         = SPI_Direction_1Line_Tx;
  SPI_InitStruct.SPI_Mode              = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize          = SPI_DataSize_16b;
  SPI_InitStruct.SPI_CPOL              = SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA              = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS               = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
  SPI_InitStruct.SPI_FirstBit          = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial     = 7;
  SPI_Init(SPI2, &SPI_InitStruct);

  //SPI_TIModeCmd(SPI1, ENABLE);

  //SPI_NSSPulseModeCmd(SPI1, ENABLE);
  //SPI_SSOutputCmd(SPI1, ENABLE);
  SPI_Cmd(SPI2, ENABLE);

  //SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_HF);

  //SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_Tx);

  //SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Reset);

  //SPI_SendData8(SPI1, uint8_t Data);
  //uint8_t SPI_ReceiveData8(SPI1);

  //CRC Config.
  //SPI_CRCLengthConfig(SPI1, SPI_CRCLength_16b);
  //SPI_CalculateCRC(SPI1, ENABLE);
  //SPI_TransmitCRC(SPI1);
  //uint16_t SPI_GetCRC(SPI1, uint8_t SPI_CRC);
  //uint16_t SPI_GetCRCPolynomial(SPI1);

  //DMA Config.
  //SPI_LastDMATransferCmd(SPI1, uint16_t SPI_LastDMATransfer);

  //IRQ Set.
  //Interrupt Setup.
/*
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  SPI_I2S_ITConfig(SPI1, uint8_t SPI_I2S_IT, ENABLE);
   SPI_GetTransmissionFIFOStatus(SPI1);
   SPI_GetReceptionFIFOStatus(SPI1);
  FlagStatus SPI_I2S_GetFlagStatus(SPI1, uint16_t SPI_I2S_FLAG);
  SPI_I2S_ClearFlag(SPI1, uint16_t SPI_I2S_FLAG);
  ITStatus SPI_I2S_GetITStatus(SPI1, uint8_t SPI_I2S_IT);
*/
}


/* SPI Send One Byte.
*/
uint8_t SPI_Send_Receive_One_Byte(SPI_TypeDef*     SPIx,
                                  uint16_t            Byte_Temp
                                 )
{ uint8_t Temp;
  //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);

  //Waiting for Transmit Complete.
  while((SPIx->SR & SPI_SR_TXE) == 0);
  SPI_SendData8(SPIx,Byte_Temp);

  //Waiting for the data available.
  while((SPIx->SR & SPI_SR_RXNE) == 0);
  Temp = SPI_ReceiveData8(SPIx);

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);

  return Temp;
}

/* SPI Send Several Byte.
*/
void SPI_Send_Several_Byte(SPI_TypeDef*     SPIx,
                           uint8_t*            Byte_Temp,
                           uint16_t            Byte_Num
                          )
{ uint16_t Temp = 0;

  //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);

  //Set Tx.
  SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);

  do
  {
    //Waiting for Transmit Complete.
    while((SPIx->SR & SPI_SR_TXE) == 0);

    //Send data.
    SPI_SendData8(SPIx,*(Byte_Temp + Temp));
  }while((++Temp) < Byte_Num);

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);
}

/* SPI Receive Several Byte.
*/
void SPI_Receive_Several_Byte(SPI_TypeDef*     SPIx,
                              uint8_t*            Byte_Temp,
                              uint16_t            Byte_Num
                             )
{ uint16_t Temp = 0;

  //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);

  //Set Rx.
  SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);

  do
  {
    //Waiting for Transmit Complete.
    while((SPIx->SR & SPI_SR_TXE) == 0);
    //Send data.
    SPI_SendData8(SPIx,*(Byte_Temp + Temp));

    //Waiting for the data available.
    while((SPIx->SR & SPI_SR_RXNE) == 0);

    //Receive Data.
    Temp = SPI_ReceiveData8(SPIx);

  }while((++Temp) < Byte_Num);

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);
}

//////////////////////////////////////////////////////////////////////////////////////////

/* SPI Send & Receive 16Bits.
*/
void SPI_Send_16Bits(SPI_TypeDef*     SPIx,
                     uint16_t         Data_Temp
                    )
{ //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);
  //Enable SPIx.
  SPIx->CR1 |= SPI_CR1_SPE;

  //Waiting for Not Busy.
  while(SPIx->SR & SPI_SR_BSY);

  //Set Tx.
  if(SPIx->CR1 & SPI_CR1_BIDIMODE)
  {
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
  }

  //Waiting for Transmit Complete.
  while((SPIx->SR & SPI_SR_TXE) == 0);
  SPIx->DR = Data_Temp;

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);
}

/* SPI Receive 16Bits.
*/
uint16_t SPI_Receive_16Bits(SPI_TypeDef* SPIx)
{
  uint16_t Temp;
  //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);
  //Enable SPIx.
  SPIx->CR1 |= SPI_CR1_SPE;

  //Waiting for Not Busy.
  while(SPIx->SR & SPI_SR_BSY);

  //Set Rx
  if(SPIx->CR1 & SPI_CR1_BIDIMODE)
  {
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);
  }

  //Waiting for the data available.
  while((SPIx->SR & SPI_SR_RXNE) == 0);
  Temp = SPIx->DR;

  //Disable SPIx.
  SPIx->CR1 &= (uint16_t)(~SPI_CR1_SPE);

  //Set Tx Dir.
  if(SPIx->CR1 & SPI_CR1_BIDIMODE)
  {
    //Set Tx.
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
  }

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);

  return Temp;
}

/* SPI Send Several 16Bits.
*/
void SPI_Send_Several_16Bits(SPI_TypeDef*     SPIx,
                             uint16_t*        Byte_Temp,
                             uint16_t         Byte_Num
                            )
{ uint16_t Temp = 0;

  //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);
  //Enable SPIx.
  SPIx->CR1 |= SPI_CR1_SPE;

  //Waiting for Not Busy.
  while(SPIx->SR & SPI_SR_BSY);

  //Set Tx
  if(SPIx->CR1 & SPI_CR1_BIDIMODE)
  {
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
  }

  do
  {
    //Waiting for Transmit Complete.
    while((SPIx->SR & SPI_SR_TXE) == 0);
    //Send data.
    SPIx->DR = *(Byte_Temp + Temp);
  }while((++Temp) < Byte_Num);

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);
}

/* SPI Receive Several 16Bits.
*/
void SPI_Receive_Several_16Bits(SPI_TypeDef*     SPIx,
                                uint16_t*        Byte_Temp,
                                uint16_t         Byte_Num
                               )
{ uint16_t Temp = 0;

  //CS Low.
  //GPIO_ResetBits(GPIOA, //GPIO_Pin_15);

  //Enable SPIx.
  SPIx->CR1 |= SPI_CR1_SPE;

  //Waiting for Not Busy.
  while(SPIx->SR & SPI_SR_BSY);

  //Set Rx.
  if(SPIx->CR1 & SPI_CR1_BIDIMODE)
  {
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);
  }

  do
  {
    //Waiting for the data available.
    while((SPIx->SR & SPI_SR_RXNE) == 0);

    //Receive Data.
    *(Byte_Temp + Temp) = SPIx->DR;
  }while((++Temp) < Byte_Num);

  //Disable SPIx.
  SPIx->CR1 &= (uint16_t)(~SPI_CR1_SPE);

  //Set Tx Dir.
  if(SPIx->CR1 & SPI_CR1_BIDIMODE)
  {
    //Set Tx.
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
  }

  //CS High.
  //GPIO_SetBits(GPIOA, //GPIO_Pin_15);
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

