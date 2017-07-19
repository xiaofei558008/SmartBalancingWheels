/*This is the DAC functions' head.
File name :DAC.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __DAC_H
#define __DAC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "stm32f30x_dac.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_syscfg.h"

//Devices' head include


//functions define.


/*functions declare.
*/
void DAC1_Init(void);
void DAC1_DMA_Init(uint32_t RAM_Addr_DAC1,
                   uint32_t RAM_Addr_DAC2
                  );
#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

