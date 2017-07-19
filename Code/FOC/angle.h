/*This is the angle functions' head.
File name :angle.h
All rights reserved,if the code is not authorized by STMicroelectronics.
2017-04-18 15:21:10 Tom.xiao@st.com
*/

#ifndef __MOTOR_ANGLE_H
#define __MOTOR_ANGLE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "stm32f30x_tim.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "Error.h"
#include "tab.h"

//Define Motor-A HALL Pins.
#define A_HALL_U_GPIO           GPIOB
#define A_HALL_U_PIN_NUM        6
#define A_HALL_V_GPIO           GPIOB
#define A_HALL_V_PIN_NUM        7
#define A_HALL_W_GPIO           GPIOB
#define A_HALL_W_PIN_NUM        8

//Define Motor-B HALL Pins.
#define B_HALL_U_GPIO           GPIOB
#define B_HALL_U_PIN_NUM        4
#define B_HALL_V_GPIO           GPIOB
#define B_HALL_V_PIN_NUM        5
#define B_HALL_W_GPIO           GPIOC
#define B_HALL_W_PIN_NUM        8

//Define motor pole Pairs.
#define Motor_Pole_Pairs        15                  //Motor Pairs.
#define Motor_Speed_RPM_Min     120                 //Motor Mechnical Speed Min.
#define Motor_Speed_RPM_Max     7300                //Motor Mechnical Speed Max.

#define Hall_Sector_Num_Min     10                  //Every Hall Sector Need 10 Times Read.
#define Hall_Sector_Num_Max     1365                //Every Hall Sector Max Time of Hall Read.
#define Hall_Carry_Wave_Freq    (Motor_Speed_RPM_Max * Motor_Pole_Pairs * Hall_Sector_Num_Min / 10)

#define Hall_Error_Tolerance    4                   //Error Continue Times.
#define Hall_Confirm            2                   //Every Time Read Hall Data Confirm Times.

//Hall Sector Define.
/*
#define Hall_Sector_1           3
#define Hall_Sector_2           1
#define Hall_Sector_3           5
#define Hall_Sector_4           4
#define Hall_Sector_5           6
#define Hall_Sector_6           2
*/
//Sector Angle Define.
#define Hall_Sector_1_Ang_L     Degree_30
#define Hall_Sector_1_Ang_M     Degree_0
#define Hall_Sector_1_Ang_R     Degree_330

#define Hall_Sector_2_Ang_L     Degree_90
#define Hall_Sector_2_Ang_M     Degree_60
#define Hall_Sector_2_Ang_R     Degree_30

#define Hall_Sector_3_Ang_L     Degree_150
#define Hall_Sector_3_Ang_M     Degree_120
#define Hall_Sector_3_Ang_R     Degree_90

#define Hall_Sector_4_Ang_L     Degree_210
#define Hall_Sector_4_Ang_M     Degree_180
#define Hall_Sector_4_Ang_R     Degree_150

#define Hall_Sector_5_Ang_L     Degree_270
#define Hall_Sector_5_Ang_M     Degree_240
#define Hall_Sector_5_Ang_R     Degree_210

#define Hall_Sector_6_Ang_L     Degree_330
#define Hall_Sector_6_Ang_M     Degree_300
#define Hall_Sector_6_Ang_R     Degree_270

/* Typedefine CW/CCW.
*/
typedef enum
{
  CCW_Dir = 1,             //Set Hall Ahead Direction(CW).
  CW_Dir  = (!CCW_Dir),    //Set Reverse Direction(CCW).
}Angle_Dir_TypeDef;

/* motor angle struct.
*/
typedef struct
{
  Angle_Dir_TypeDef Hall_Dir;
  Angle_Dir_TypeDef Driver_Dir;

  bool              Flag_Close_Loop;

  GPIO_TypeDef*     Hall_Port_U;
  GPIO_TypeDef*     Hall_Port_V;
  GPIO_TypeDef*     Hall_Port_W;

  uint16_t          Hall_Pin_U;
  uint16_t          Hall_Pin_V;
  uint16_t          Hall_Pin_W;

  uint8_t           Hall_Num;
  uint8_t           Hall_Data;
  uint8_t           Hall_Data_Old;
  uint8_t           Hall_Data_Old_Old;
  uint8_t           Hall_Error_Count;
  uint8_t           Hall_Count[2];

  uint16_t          Ele_Ang;
  uint16_t          Ele_Ang_360;
  uint16_t          Step_Degree;

  uint16_t          Carry_Wave_Count;
  uint16_t          Carry_Wave_Hz;

  uint32_t          Speed_Cap_Old;
  uint32_t          Speed_Cap;
  int32_t           ESpeed_RPM;
  int32_t           MSpeed_RPM;
  TIM_TypeDef*      TIMxSpeed;
}Angle_TypeDef;

/*variables declare.
*/
extern Angle_TypeDef AHallAngle, BHallAngle;

/*functions declare.
*/
void Angle_Init(Angle_TypeDef* Temp,
                GPIO_TypeDef*  Temp_Port_U,
                GPIO_TypeDef*  Temp_Port_V,
                GPIO_TypeDef*  Temp_Port_W,
                uint8_t        Temp_Pin_Num_U,
                uint8_t        Temp_Pin_Num_V,
                uint8_t        Temp_Pin_Num_W,
                TIM_TypeDef*   TIM_ANG
               );
__RAM_RUN void Hall_Read(Angle_TypeDef* Temp);
__RAM_RUN void Hall_Read_Angle(Angle_TypeDef* Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

