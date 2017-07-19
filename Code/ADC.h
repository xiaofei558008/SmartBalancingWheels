/*This is the ADC functions' head.
File name :ADC.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef          STM32F401xxx
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#elif defined   STM32F030
#include "stm32f0xx_adc.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

#elif defined   STM32F303xC
#include "stm32f30x_adc.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

#endif

/*functions declare.
*/
void ADC1_Init(uint32_t DMA_Memory_Addr);
void ADC_OPAMP_DMA_Init(uint32_t ADC1_DMA_Addr,
                        uint32_t ADC2_DMA_Addr,
                        uint32_t ADC3_DMA_Addr,
                        uint32_t ADC4_DMA_Addr
                       );
void ADC_Inject_OPAMP_Init(void);
uint16_t ADC_Convert_One_Channel(uint32_t ADC_Channel_Sel);


#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

