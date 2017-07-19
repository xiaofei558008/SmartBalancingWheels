/*This is the OPAMP functions' head.
File name :OPAMP.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __OPAMP_H
#define __OPAMP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_opamp.h"

//TypeDefine.
typedef enum
{
  OPAMP_UV = 0,
  OPAMP_UW = 1,
  OPAMP_VW = 2,
} OPAMP_SWITCH_TypeDef;

/*functions declare.
*/
void OPAMPx_PGA_Init(void);
void OPAMPx_Init(uint32_t OPAMPx);

void OPAMP12_Switch(OPAMP_SWITCH_TypeDef Temp);
void OPAMP34_Switch(OPAMP_SWITCH_TypeDef Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

