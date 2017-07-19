/*This is the RCC functions' head.
File name :RCC.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __RCC_H
#define __RCC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef          STM32F401xxx
#include "stm32f4xx_rcc.h"

#elif defined   STM32F030
#include "stm32f0xx_rcc.h"

#elif defined   STM32F303xC
#include "stm32f30x_rcc.h"
#include "stm32f30x_flash.h"

#endif

/* Global Variables Decalre.
*/
extern RCC_ClocksTypeDef RCC_Clocks;

/* Functions Declare.
*/
void RCC_Init(void);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

