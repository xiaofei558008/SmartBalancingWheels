/*This is the Smart Balancing functions' head.
File name :Balancing.h
All rights reserved,if the code is not authorized by STMicroelectronics.
2017-06-19 15:51:38 Tom.xiao@st.com
*/

#ifndef __BALANCING_H
#define __BALANCING_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "PID.h"

/* Error Angle Define
*  +- 30 Degree max.
*/
#define     SBW_Error_Angle_Max            6000
#define     SBW_Error_Angle_Min            (-SBW_Error_Angle_Max)

/* A side Angle PI Parameters
*/
#define     Angle_Kp                       10000
#define     Angle_Ki                       0
#define     Angle_Kd                       0
#define     Angle_ErrorMax                 3600     //1800      //18000 Max
#define     Angle_OutputMax                30000    //32768 Max

#define     Angle_ErrorMin                 (-Angle_ErrorMax)
#define     Angle_OutputMin                (-Angle_OutputMax)

/* A side Angle Speed PI Parameters
*/
#define     AngleSpeed_Kp                  200     //2000
#define     AngleSpeed_Ki                  60      //60
#define     AngleSpeed_Kd                  0
#define     AngleSpeed_ErrorMax            30000    //32768 Max
#define     AngleSpeed_OutputMax           2000     //600      //3000  Max

#define     AngleSpeed_ErrorMin            (-AngleSpeed_ErrorMax)
#define     AngleSpeed_OutputMin           (-AngleSpeed_OutputMax)

#define     AngleABFilterConst             4
/* Balancing Keep TypeDef.
*
*/
typedef struct
{
  uint32_t Counter;

  PID_TypeDef AAnglePI;
  PID_TypeDef AAngleSpeedPI;

  PID_TypeDef BAnglePI;
  PID_TypeDef BAngleSpeedPI;
} Banalcing_Keeping_TypeDef;


/* Global Declare.
*
*/
extern Banalcing_Keeping_TypeDef Balancing;

void Blanecing_Init(Banalcing_Keeping_TypeDef* Temp);
void Balancing_Keeping_Loop(Banalcing_Keeping_TypeDef* Temp);
void ABalancing_Angle_Overflow_CallBack(Banalcing_Keeping_TypeDef* Temp);
void BBalancing_Angle_Overflow_CallBack(Banalcing_Keeping_TypeDef* Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

