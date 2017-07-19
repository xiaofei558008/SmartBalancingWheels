/*This is type define which is used in PID.c.
File name : PID.h
All rights reserved,if the code is not authorized by STMicroelectronics.
2016-10-15 12:52:8 Tom.xiao@st.com
*/

#ifndef __PID
#define __PID

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* PID structure define.
*/
typedef struct
{
  bool               FlagSaturated;
  int32_t            Kp;
  int32_t            Ki;
  int32_t            Kd;

  int32_t            Reference;
  int32_t            Feedback;

  int32_t            ErrorNow;
  int32_t            ErrorOld;

  int32_t            ErrorMax;
  int32_t            ErrorMin;
  int32_t            ErrorAdd;

  int32_t            OutputMax;
  int32_t            OutputMin;
  int16_t            Output;
} PID_TypeDef;

/*functions declare;
*/
void PID_Init(PID_TypeDef* Loop,
              int32_t     Kp,
              int32_t     Ki,
              int32_t     Kd,
              int32_t     ErrorMax,
              int32_t     ErrorMin,
              int32_t     OutputMax,
              int32_t     OutputMin
             );
void PID_Reset(PID_TypeDef* Loop);
void PID_ParamSet(PID_TypeDef* Loop,
                  int32_t      Kp,
                  int32_t      Ki,
                  int32_t      Kd,
                  int32_t      ErrorMax,
                  int32_t      ErrorMin,
                  int32_t      OutputMax,
                  int32_t      OutputMin
                 );
void PID_Clear(PID_TypeDef* Loop);
/* __ramfunc*/ int16_t PID_ModuleQ12(PID_TypeDef* Loop);

#endif

/******************************* End of file **********************************/

