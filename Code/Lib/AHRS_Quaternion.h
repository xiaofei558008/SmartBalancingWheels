/*This is the AHRS & Quaternion functions' head.
File name :AHRS_Quaternion.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2016-05-05 11:03:28
*/

#ifndef __AHRS_Quaternion_H
#define __AHRS_Quaternion_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define COE_MDPS_TO_RADPS       0.00001745329f

//Data Formate Define.

typedef struct
{
  int16_t AXIS_X;
  int16_t AXIS_Y;
  int16_t AXIS_Z;
}AxesRegRaw_TypeDef;

typedef struct
{
  int32_t AXIS_X;
  int32_t AXIS_Y;
  int32_t AXIS_Z;
}AxesRaw_TypeDef;

typedef struct
{
  float AXIS_X;
  float AXIS_Y;
  float AXIS_Z;
}AxesRaw_TypeDef_Float;

//Type define for quaternion
typedef struct
{
  float q0,
        q1,
        q2,
        q3,

        Kp,
        Ki,

        exInt,
        eyInt,
        ezInt;
}Quaternion_TypeDef;

//Type define for Euler angle
typedef struct
{
  float thx;
  float thy;
  float thz;

  float sinx;
  float cosx;
  float siny;
  float cosy;
  float sinz;
  float cosz;

  float Rot_Matrix[9];
}EulerAngle_TypeDef;

//Type define for AHRS
typedef struct
{
  AxesRaw_TypeDef_Float  AccRawData;
  AxesRaw_TypeDef_Float  GyroRawData;

  Quaternion_TypeDef     QuatAngle;
  EulerAngle_TypeDef     EulerAngle;
  AxesRaw_TypeDef_Float  DegreeAngle;
  AxesRaw_TypeDef        hDegreeAngle;
}AHRS_TypeDef;

/*Global declare.
*/
float Sqrt(float x);
float invSqrt(float x);
void QuaternionNorm(Quaternion_TypeDef *q);
void QuaternionMult(Quaternion_TypeDef *qa, Quaternion_TypeDef *qb, Quaternion_TypeDef *qo);
void QuaternionRotation(Quaternion_TypeDef *qr, Quaternion_TypeDef *qv, Quaternion_TypeDef *qo);
void QuaternionConj(Quaternion_TypeDef *qa, Quaternion_TypeDef *qo);
void QuaternionToEuler(Quaternion_TypeDef *qr, EulerAngle_TypeDef *ea);
void AHRS_AG_Init(AHRS_TypeDef*          Temp,
                  float                  Kp,
                  float                  Ki
                 );
void AHRS_Fusion_AG(AHRS_TypeDef* Temp,
                    float         Delta_Time
                   );
#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

