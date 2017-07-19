/*This is the timer functions' head.
File name :timer.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef          STM32F401xxx
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#elif defined   STM32F030
#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

#elif defined   STM32F303xC
#include "stm32f30x_tim.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_syscfg.h"
#include "clarke_park.h"
#endif

/*functions declare.
*/
void Timer2_Base_Counter_Init(void);
void Timer2_Counter_Init(uint32_t           Timer_Compare,
                         FunctionalState    Compare_Int_En
                        );

void Timer2_Capture_Init(uint32_t DMA_Memory_Addr);
void Timer2_Encoder_Init(void);

void Timer3_Counter_Init(uint16_t           Timer_Compare,
                         FunctionalState    Compare_Int_En
                        );
void Timer4_Counter_Init(uint32_t           Timer_Compare,
                         FunctionalState    Compare_Int_En
                        );
void Timer3_Encoder_Init(void);
void TIM_Config(void);
void Timer3_Counter_Trigger_Init(void);
void Timer4_Counter_Trigger_Init(void);

void Timer5_Counter_Init(uint32_t           Timer_Compare,
                         FunctionalState    Compare_Int_En
                        );
void Timer6_Base_Counter_Init(void);
void Timer15_Counter_Init(uint32_t           Timer_Compare,
                          FunctionalState    Compare_Int_En
                         );
void Timer16_Counter_Init(uint32_t           Timer_Compare,
                          FunctionalState    Compare_Int_En
                         );
void Timer16_Capture_Init(uint32_t DMA_Memory_Addr1,    //For CAP
                          uint32_t DMA_Memory_Addr2     //For Overflow.
                         );
void Timer17_Counter_Init(uint32_t           Timer_Compare,
                          FunctionalState    Compare_Int_En
                         );
void Timerx_Counter_Init(TIM_TypeDef *      TIMx,
                         uint32_t           Timer_Compare,
                         FunctionalState    Compare_Int_En,
                         FunctionalState    Update_Int_En
                        );

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

