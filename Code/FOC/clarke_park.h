/*This is the Clarke & Park functions' head.
File name :Clarke_park.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-11 10:49:28
*/

#ifndef __CLARKE_PARK_H
#define __CLARKE_PARK_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "math.h"
#include "stm32f30x_tim.h"
#include "PID.h"
#include "tab.h"
#include "flag.h"
#include "OPAMP.h"
#include "angle.h"
#include "Error.h"

/* All Motor PID Set Up.
*/

//  ID
#define     ID_Kp                   8000    /*8000*/
#define     ID_Ki                   100      /*100*/
#define     ID_Kd                   0
#define     ID_ErrorMax             2000    /*1000*/
#define     ID_OutputMax            4000    /*4500*/

#define     ID_ErrorMin             (-ID_ErrorMax)
#define     ID_OutputMin            (-ID_OutputMax)

//  IQ
#define     IQ_Kp                   ID_Kp
#define     IQ_Ki                   ID_Ki
#define     IQ_Kd                   ID_Kd
#define     IQ_ErrorMax             ID_ErrorMax
#define     IQ_OutputMax            ID_OutputMax

#define     IQ_ErrorMin             (-IQ_ErrorMax)
#define     IQ_OutputMin            (-IQ_OutputMax)

//Motor Setup.
#define DACIdIqOutput               0

#define PolePair                    15  //11
#define Elect360                    (32768 / PolePair)

#define ShuntCalibTime              16384
#define ShuntCalibMiddle            2086
#define ShuntCalibErrorMax          100

#define AngCalibTime                16384
#define AngCalibRotorLockTime       (20000 * 2)
#define AngCalibRotorLockVector     500
#define AngCalibErrorMax            20

//Angle Offset Stored in Flash memory.
#define MCUFlashStartAddr           0x08000000
#define MCUFlashPageSize            2048
#define AngFlashPageNo              127
#define AngFlashStartAddr           (MCUFlashStartAddr + AngFlashPageNo * MCUFlashPageSize)
//----|----|----|----|----|----|----|----|----|----|----|----|----|----|
// 0    30   60   90   120  150  180  210  240  270  300  330 ......

//Function define.
#define Max_AB(a,b)                 ((a)>(b) ? (a):(b))
#define Max_ABC(a,b,c)              ((Max_AB((a),(b)) < (c)) ? c : Max_AB((a),(b)))

//Typedefine Motor State.
typedef enum
{
  CPSTA_ShuntResCalib = 0,
  CPSTA_Ready,
  CPSTA_Runing,
  CPSTA_Error,
} ClarkeParkState_TypeDef;

//Clarke and Park Typedefine.
typedef struct
{
  ClarkeParkState_TypeDef State;
  uint16_t     UpdateFlag;
  uint32_t     Counter;

  Angle_TypeDef* Angle;
  uint32_t     AbsAngle;
  uint32_t     EAngleQ13;
  uint32_t     AngleOffset;

  uint16_t     ADC_Raw_A;
  uint16_t     ADC_Raw_B;

  uint32_t     ADCStaticU;
  uint32_t     ADCStaticV;
  uint32_t     ADCStaticW;

  uint16_t     ADCStaticU_Stable;
  uint16_t     ADCStaticV_Stable;
  uint16_t     ADCStaticW_Stable;

  uint16_t     ADCPhaseU;
  uint16_t     ADCPhaseV;
  uint16_t     ADCPhaseW;

  int32_t      IU;
  int32_t      IV;
  int32_t      IW;
  int32_t      IAlpha;
  int32_t      IBeta;
  int32_t      ID;
  int32_t      IQ;

  PID_TypeDef  PID_ID;
  PID_TypeDef  PID_IQ;

  int16_t      VD;
  int16_t      VQ;
  int16_t      VAlpha;
  int16_t      VBeta;

  int16_t      U1;
  int16_t      U2;
  int16_t      U3;

  uint8_t      Sector;

  int16_t      t1;
  int16_t      t2;
  int16_t      t0;

  TIM_TypeDef* TIMPWM;
  TIM_TypeDef* TIMAngle;

  OPAMP_SWITCH_TypeDef OPAMP_SW;
  Motor_Error_TypeDef Error_Flag;
} ClarkePark_TypeDef;

//Global Variable Declare.
extern ClarkePark_TypeDef AClarkePark, BClarkePark;

//Functions Declare.
void ClarkePark_PID_SVPWM_Init(ClarkePark_TypeDef* Temp,
                               Angle_TypeDef*      Angle,
                               TIM_TypeDef*        TIM_PWM,
                               TIM_TypeDef*        TIM_ANG
                              );

void ClarkePark_Loop(ClarkePark_TypeDef* Temp);
void ClarkePark_CurrentStaticCalibration(ClarkePark_TypeDef* Temp);
void ClarkePark_AngleStaticCalibration(ClarkePark_TypeDef* Temp);
void ClarkePark_Ready(ClarkePark_TypeDef* Temp);
__RAM_RUN void ClarkePark_SVPWM(ClarkePark_TypeDef* Temp);
void ClarkePark_Errors(ClarkePark_TypeDef* Temp);
void ClarkePark_AngleCalibError(ClarkePark_TypeDef* Temp);
void ClarkePark_Current_Switch(ClarkePark_TypeDef* Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

