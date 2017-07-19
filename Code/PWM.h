/*This is the PWM functions' head.
File name :PWM.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:49:28
*/

#ifndef __PWM_H
#define __PWM_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "RCC.h"

#include "stm32f30x_tim.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "tab.h"
#include "clarke_park.h"
#include "speed.h"

//Phase Define.
#define Phase_UH_VL()                  {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0060;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x4000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0040;    /*  W+  */  \
                                        GPIOA->BSRR |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BRR  |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_1;                        /*  W-  */  \
                                       }
#define Phase_WH_VL()                  {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0040;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x4000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0060;    /*  W+  */  \
                                        GPIOA->BSRR |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BRR  |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_1;                        /*  W-  */  \
                                       }
#define Phase_WH_UL()                  {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0040;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x4000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0060;    /*  W+  */  \
                                        GPIOA->BRR  |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_1;                        /*  W-  */  \
                                       }
#define Phase_VH_UL()                  {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0040;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x6000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0040;    /*  W+  */  \
                                        GPIOA->BRR  |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_1;                        /*  W-  */  \
                                       }
#define Phase_VH_WL()                  {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0040;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x6000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0040;    /*  W+  */  \
                                        GPIOA->BSRR |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BRR  |= GPIO_Pin_1;                        /*  W-  */  \
                                       }
#define Phase_UH_WL()                  {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0060;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x4000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0040;    /*  W+  */  \
                                        GPIOA->BSRR |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BRR  |= GPIO_Pin_1;                        /*  W-  */  \
                                       }
#define Phase_All_Close()              {TIM1->CCMR1 &= 0xff8f;  TIM1->CCMR1 |= 0x0040;    /*  U+  */  \
                                        TIM1->CCMR1 &= 0x8fff;  TIM1->CCMR1 |= 0x4000;    /*  V+  */  \
                                        TIM1->CCMR2 &= 0xff8f;  TIM1->CCMR2 |= 0x0040;    /*  W+  */  \
                                        GPIOA->BSRR |= GPIO_Pin_7;                        /*  U-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_0;                        /*  V-  */  \
                                        GPIOB->BSRR |= GPIO_Pin_1;                        /*  W-  */  \
                                       }

/*Functions Declare.
*/
void PWM_Init_180(uint32_t Freq_Hz);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

