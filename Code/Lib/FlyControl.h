/*This is the Fly Control functions' head.
File name :FlyControl.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2016-05-03 12:34:28
*/

#ifndef __FLY_CONTROL_H
#define __FLY_CONTROL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "stm32f30x.h"

#include "IIR_filter.h"
#include "AHRS_Quaternion.h"

//Devices' head include
#define Fly_Sensor_Cali_Time    64

#define AHRS_KP_A               5               //4
#define AHRS_KI_A               1.25            //1

#define AHRS_KP_B               AHRS_KP_A
#define AHRS_KI_B               AHRS_KI_A

typedef struct
{
  uint8_t               Device_ID;

  AxesRegRaw_TypeDef    Gyro_Reg_Raw;
  AxesRegRaw_TypeDef    Acc_Reg_Raw;

  AxesRegRaw_TypeDef    Gyro_Rel_Raw;
  AxesRegRaw_TypeDef    Acc_Rel_Raw;

  AxesRaw_TypeDef_Float Gyro_Float;
  AxesRaw_TypeDef_Float Acc_Float;
} AccGyro_TypeDef;

typedef enum
{
  STA_PowerON = 0,
  STA_Flying,
} Fly_State_TypeDef;

//typedef fly control.
typedef struct
{
  Fly_State_TypeDef       Fly_State;
  uint16_t                Counter;

  AccGyro_TypeDef*        RawData;

  AxesRaw_TypeDef         Gyro_Reg_Raw_Offset;
  AxesRaw_TypeDef_Float   Gyro_Offset;

  AHRS_TypeDef            AHRS;

  void (*AHRS_AG_Init)    (AHRS_TypeDef*          Temp,
                           float                  Kp,
                           float                  Ki
                          );

  void (*AHRS_Fusion)     (AHRS_TypeDef* Temp,
                           float         Delta_Time
                          );

  uint32_t                Tick_Count;
  TIM_TypeDef*            Tim_Tick;
  float                   Time_Delta_Second;
} FlyControl_TypeDef;

/*Global declare.
*/
extern FlyControl_TypeDef AFlyCtrl, BFlyCtrl;

void FlyControl_Init(FlyControl_TypeDef* Temp,
                     AccGyro_TypeDef*    RawData,
                     float               Kp,
                     float               Ki,
                     TIM_TypeDef*        TIMx
                    );

void FlyControl_Loop(FlyControl_TypeDef* Temp);
void FlyControl_Sensor_Calibration(FlyControl_TypeDef* Temp);
void FlyControl_Sensor_Calibration_Error_Callback(FlyControl_TypeDef* Temp);
void FlyControl_Sensor_Calibration_OK_Callback(FlyControl_TypeDef* Temp);
void FlyControl_Flying(FlyControl_TypeDef* Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

