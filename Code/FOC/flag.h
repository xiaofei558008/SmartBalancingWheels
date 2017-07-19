/*This is the flag functions' head.
File name :flag.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-11 10:49:28
*/

#ifndef __FLAG_H
#define __FLAG_H

#include <stdint.h>
#include <stddef.h>
#include "def32.h"

/* Define RAM Runing Function
*/
#define __RAM_RUN            //__ramfunc

/*flag define.
*/
#define Systick_Counter      Systick_Flag.systick_counter

//1ms flag define.
#define Flag_PID1            Systick_Flag.flag_1ms.flag.bit0
#define Flag_PID2            Systick_Flag.flag_1ms.flag.bit1
#define Flag_PID3            Systick_Flag.flag_1ms.flag.bit2
#define Flag_PID             Systick_Flag.flag_1ms.flag.bit3

//2ms flag define.
//4ms flag define.
//8ms flag define.
//16ms flag define.
#define flag_TST             Systick_Flag.flag_16ms.flag.bit0
//#define flag_LED            Systick_Flag.flag_16ms.flag.bit1
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit2
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit3
//
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit4
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit5
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit6
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit7
//
/*
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit8
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit9
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit10
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit11
//
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit12
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit13
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit14
//#define Flag_PID            Systick_Flag.flag_16ms.flag.bit15
*/
//32ms flag define.
//64ms flag define.
//128ms flag define.
//256ms flag define.
//512ms flag define.
//1024ms flag define.
//#define flag_LED            Systick_Flag.flag_1024ms.flag.bit0

//2048ms flag define.
//4096ms flag define.
//8192ms flag define.
//16384ms flag define.
//32768ms flag define.
//65536ms flag define.

//typedef  Flags.
typedef struct
{
  uint32_t      systick_counter;

  u8_bit        flag_1ms;
  u8_bit        flag_2ms;
  u8_bit        flag_4ms;
  u8_bit        flag_8ms;
  u8_bit        flag_16ms;
  u8_bit        flag_32ms;
  u8_bit        flag_64ms;
  u8_bit        flag_128ms;
  u8_bit        flag_256ms;
  u8_bit        flag_512ms;
  u8_bit        flag_1024ms;
  u8_bit        flag_2048ms;
  u8_bit        flag_4096ms;
  u8_bit        flag_8192ms;
  u8_bit        flag_16384ms;
  u8_bit        flag_32768ms;
  u8_bit        flag_65536ms;
}Flag_TypeDef;

//Global variables declare.
extern Flag_TypeDef Systick_Flag;

/*functions declare.
*/
void Flag_Init(Flag_TypeDef* Temp);


#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

