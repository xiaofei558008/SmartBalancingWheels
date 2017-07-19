/*This is the IIR Filter functions' head.
File name :IIR_filter.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2016-04-06 16:03:28
*/

#ifndef __IIR_FILTER_H
#define __IIR_FILTER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Filter Parameters Define.
*/
#define Gyro_IIR_2nd_a1         1.2741149f
#define Gyro_IIR_2nd_a2         -0.4748008f

#define Gyro_IIR_2nd_b0         0.0501715f
#define Gyro_IIR_2nd_b1         0.1003429f
#define Gyro_IIR_2nd_b2         0.0501715f

#define Gyro_X_IIR_2nd_a1       Gyro_IIR_2nd_a1
#define Gyro_X_IIR_2nd_a2       Gyro_IIR_2nd_a2

#define Gyro_X_IIR_2nd_b0       Gyro_IIR_2nd_b0
#define Gyro_X_IIR_2nd_b1       Gyro_IIR_2nd_b1
#define Gyro_X_IIR_2nd_b2       Gyro_IIR_2nd_b2

#define Gyro_Y_IIR_2nd_a1       Gyro_X_IIR_2nd_a1
#define Gyro_Y_IIR_2nd_a2       Gyro_X_IIR_2nd_a2

#define Gyro_Y_IIR_2nd_b0       Gyro_X_IIR_2nd_b0
#define Gyro_Y_IIR_2nd_b1       Gyro_X_IIR_2nd_b1
#define Gyro_Y_IIR_2nd_b2       Gyro_X_IIR_2nd_b2

#define Gyro_Z_IIR_2nd_a1       Gyro_X_IIR_2nd_a1
#define Gyro_Z_IIR_2nd_a2       Gyro_X_IIR_2nd_a2

#define Gyro_Z_IIR_2nd_b0       Gyro_X_IIR_2nd_b0
#define Gyro_Z_IIR_2nd_b1       Gyro_X_IIR_2nd_b1
#define Gyro_Z_IIR_2nd_b2       Gyro_X_IIR_2nd_b2

/* Parameters TypeDef.
*/
typedef struct
{
  float a1,
        a2,
        b0,
        b1,
        b2;
}IIR_Coeff_TypeDef;

typedef struct
{
  float*                Data_In;
  float*                Data_Out;
  IIR_Coeff_TypeDef Coeff;
  float                 Data_In_Ex[2];
  float                 Data_Out_Ex[2];
}IIR_2nd_Order_TypeDef;

/* Global Declare.
*/
extern IIR_2nd_Order_TypeDef Gyro_X_IIR_2nd_Filter_Left, Gyro_X_IIR_2nd_Filter_Right,
                             Gyro_Y_IIR_2nd_Filter_Left, Gyro_Y_IIR_2nd_Filter_Right,
                             Gyro_Z_IIR_2nd_Filter_Left, Gyro_Z_IIR_2nd_Filter_Right;

void IIR_Filter_2_Order_Init(float* Data_In,
                             float* Data_Out,
                             IIR_2nd_Order_TypeDef* Temp
                            );

void IIR_Filter_2_Order(IIR_2nd_Order_TypeDef* Temp);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/
