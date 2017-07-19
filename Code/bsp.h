/*This is the bsp functions' head.
File name :bsp.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-11 10:49:28
*/

#ifndef __BSP_H
#define __BSP_H

#include <stdint.h>
#include <stddef.h>
#include "debug_gpio.h"
#include "RCC.h"
#include "ADC.h"
#include "ACMP.h"
#include "OPAMP.h"
#include "PWM.h"
#include "timer.h"
#include "DAC.h"
#include "DMA.h"
#include "USART.h"
#include "SPI.h"
#include "clarke_park.h"
#include "speed.h"
#include "main.h"

//BSP GPIO Defines.
//Power Out.
#define PWR_PORT            GPIOC
#define PWR_PIN_NUM         0

//OFF Define.
#define Power_OFF()         {RCC->AHBENR |= (uint32_t)1 << 19;                                      \
                             PWR_PORT->MODER &= (uint32_t)(~((uint32_t) 3 << (PWR_PIN_NUM << 1)));  \
                             PWR_PORT->MODER |= ((uint32_t) 1 << (PWR_PIN_NUM << 1));               \
                             PWR_PORT->BSRR  |= ((uint32_t) 1 << (PWR_PIN_NUM + 16));               \
                            }
//ON Define.
#define Power_ON()          {RCC->AHBENR |= (uint32_t)1 << 19;                                      \
                             PWR_PORT->MODER &= (uint32_t)(~((uint32_t) 3 << (PWR_PIN_NUM << 1)));  \
                             PWR_PORT->MODER |= ((uint32_t) 1 << (PWR_PIN_NUM << 1));               \
                             PWR_PORT->BSRR  |= ((uint32_t) 1 << PWR_PIN_NUM);                      \
                            }

//Sensor Power Out.
#define Sen_PWR_PORT        GPIOC
#define Sen_PWR_PIN_NUM     15

//OFF Define.
#define Sen_Power_OFF()     {RCC->AHBENR |= (uint32_t)1 << 19;                                              \
                             Sen_PWR_PORT->MODER &= (uint32_t)(~((uint32_t) 3 << (Sen_PWR_PIN_NUM << 1)));  \
                             Sen_PWR_PORT->MODER |= ((uint32_t) 1 << (Sen_PWR_PIN_NUM << 1));               \
                             Sen_PWR_PORT->BSRR  |= ((uint32_t) 1 << Sen_PWR_PIN_NUM);                      \
                            }
//ON Define.
#define Sen_Power_ON()      {RCC->AHBENR |= (uint32_t)1 << 19;                                              \
                             Sen_PWR_PORT->MODER &= (uint32_t)(~((uint32_t) 3 << (Sen_PWR_PIN_NUM << 1)));  \
                             Sen_PWR_PORT->MODER |= ((uint32_t) 1 << (Sen_PWR_PIN_NUM << 1));               \
                             Sen_PWR_PORT->BSRR  |= ((uint32_t) 1 << (Sen_PWR_PIN_NUM + 16));               \
                            }

//Pedal GPIO Defines.
#define Pedal_L_PORT        GPIOD
#define Pedal_L_PIN         GPIO_Pin_2

#define Pedal_R_PORT        GPIOC
#define Pedal_R_PIN         GPIO_Pin_9

//Sensor Power GPIO Define.
#define Sen_PWR_PORT        GPIOC
#define Sen_PWR_PIN         GPIO_Pin_15

#define Sen_PWR_OFF()       {Sen_PWR_PORT->BSRR |= (1 << (Sen_PWR_PIN + 16));}
#define Sen_PWR_ON()        {Sen_PWR_PORT->BSRR |= (1 << Sen_PWR_PIN);}

//Functions Declare.
void Bsp_Init(void);
extern uint16_t ADC_DMA_Buffer[10];
#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

