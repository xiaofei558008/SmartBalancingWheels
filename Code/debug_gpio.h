/*This is the debug set document.
File name :debug_gpio.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2013-7-04 15:13:28
*/
#ifndef __DEBUG_GPIO_H
#define __DEBUG_GPIO_H

#include "stdbool.h"
#include "stdint.h"

#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

/* debug flag define.
*/
#define debug_port_0                  GPIOC
#define debug_pin_0                   GPIO_Pin_3

#define debug_port_1                  GPIOC
#define debug_pin_1                   GPIO_Pin_4

#define debug_port_2                  GPIOF
#define debug_pin_2                   GPIO_Pin_4
////////////////////////////////////////////////

#define debug_port_3                  GPIOE
#define debug_pin_3                   GPIO_Pin_11

#define debug_port_4                  GPIOE
#define debug_pin_4                   GPIO_Pin_12

#define debug_port_5                  GPIOE
#define debug_pin_5                   GPIO_Pin_13

#define debug_port_6                  GPIOE
#define debug_pin_6                   GPIO_Pin_14

#define debug_port_7                  GPIOE
#define debug_pin_7                   GPIO_Pin_15

//functions declare
void Debug_GPIO_Pins_Init(bool debug_gpio_0,
                          bool debug_gpio_1,
                          bool debug_gpio_2,
                          bool debug_gpio_3,
                          bool debug_gpio_4,
                          bool debug_gpio_5,
                          bool debug_gpio_6,
                          bool debug_gpio_7
                         );
void Debug_GPIO_Toggle(uint8_t debug_gpio_pin_num);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/


