/*This is the SPI functions' head.
File name :SPI.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-11-11 10:49:28
*/

#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_spi.h"

#define SPI1_TX_RX_OneLine_Mode         1

/*functions declare.
*/
void SPI1_Init(void);
void SPI2_Init(void);

uint8_t SPI_Send_Receive_One_Byte(SPI_TypeDef*     SPIx,
                                  uint16_t            Byte_Temp
                                 );

void SPI_Send_Several_Byte(SPI_TypeDef*     SPIx,
                           uint8_t*            Byte_Temp,
                           uint16_t            Byte_Num
                          );

void SPI_Receive_Several_Byte(SPI_TypeDef*     SPIx,
                              uint8_t*            Byte_Temp,
                              uint16_t            Byte_Num
                             );

void SPI_Send_16Bits(SPI_TypeDef*     SPIx,
                     uint16_t            Data_Temp
                    );

uint16_t SPI_Receive_16Bits(SPI_TypeDef*     SPIx);

void SPI_Send_Several_16Bits(SPI_TypeDef*     SPIx,
                             uint16_t*           Byte_Temp,
                             uint16_t            Byte_Num
                            );
void SPI_Receive_Several_16Bits(SPI_TypeDef*     SPIx,
                                uint16_t*        Byte_Temp,
                                uint16_t         Byte_Num
                               );

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

