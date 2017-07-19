/*This is the USART functions' head.
File name :USART.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __USART_H
#define __USART_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef          STM32F401xxx
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#elif defined   STM32F030
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

#elif defined   STM32F303xC
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

#elif defined   STM32L1XX_MD
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"

#endif


//Devices' head include



/*functions declare.
*/
void USART1_Init(uint32_t Baud_Rate);
void USART2_Init(uint32_t Baud_Rate);
void USART3_Init(uint32_t Baud_Rate);
uint8_t USART_Byte_In(USART_TypeDef* USARTx);
void USART_Byte_Out(USART_TypeDef* USARTx,
                    uint8_t        Data_Temp
                   );

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

