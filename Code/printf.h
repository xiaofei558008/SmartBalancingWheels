/*This is the printf functions' head.
File name :printf.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@st.com
2014-5-16 09:37:28
*/

#ifndef __PRINTF_H
#define __PRINTF_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#ifdef          STM32F401xxx
#include "stm32f4xx_usart.h"

#elif defined   STM32F030
#include "stm32f0xx_usart.h"

#elif defined   STM32F303xC
#include "stm32f30x_usart.h"

#endif

//Devices' head include

//functions define.
//#define console_print(ch)          USART_SendData(USART1, ch)
#define console_print(ch)          {                                        \
                                    while((USART1->ISR & 0x40) == 0);       \
                                    USART1->TDR = ch;                       \
                                   }

/*functions declare.
*/
void Print_Init(void);
void print(char* fmt, ...);
void printch(char ch);
void printdec(int dec);
void printflt(double flt);
void printbin(int bin);
void printhex(int hex);
void printstr(char* str);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

