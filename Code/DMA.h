/*This is the DMA functions' head.
File name :DMA.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __DMA_H
#define __DMA_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "stm32f30x_dma.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

//Devices' head include


/*functions declare.
*/
void DMA1_Init( uint32_t             DMA_Peripheral_Addr,
                uint32_t             DMA_Memory_Addr,
                uint32_t             PeripheralDataSize,
                uint32_t             MemoryDataSize,
                uint32_t             Priority_Level,
                DMA_Channel_TypeDef* DMA1_Channelx
              );

void DMA2_Init( uint32_t             DMA_Peripheral_Addr,
                uint32_t             DMA_Memory_Addr,
                uint32_t             PeripheralDataSize,
                uint32_t             MemoryDataSize,
                DMA_Channel_TypeDef* DMA2_Channelx
              );

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

