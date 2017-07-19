/*This is the speed functions' head.
File name :speed.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-11 10:49:28
*/

#ifndef __SPEED_H
#define __SPEED_H

#include <stdint.h>
#include <stddef.h>
#include "stm32f30x_tim.h"
#include "PID.h"

//Devices' head include.

//speed define.
#define SPEED_CAP_MAX           65535
#define SPEED_CAP_MIN           10
#define SPEED_AVE_TIME          8

#define SPEED_KALMAN_FILTER     0
#define SPEED_COUNT_TOP         65536
#define SPEED_CONSTANT_Q4       29297   //468750    //29297  //937500

//typedef speed info
typedef struct
{
  uint16_t            flag_stop;
  uint32_t            cap;
  uint32_t            cap_old;
  int32_t             cap_delta;
  int32_t             ave;
  int32_t             ave_old;
  int32_t             ave_buf[SPEED_AVE_TIME];
  uint8_t             point;
  PID_TypeDef*        PID_Speed;
}Speed_Struct_TypeDef;

//speed global variables declare.
extern Speed_Struct_TypeDef Motor_Speed;

//functions declare.
void Speed_Init(Speed_Struct_TypeDef* Temp);
void Speed_Calculate(Speed_Struct_TypeDef* Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

