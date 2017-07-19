/*This is the Motor Error functions' head.
File name :Error.h
All rights reserved,if the code is not authorized by STMicroelectronics.
2017-04-18 15:20:39 Tom.xiao@st.com
*/



#ifndef __MOTOR_ERROR_H
#define __MOTOR_ERROR_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "flag.h"

//typedef Error
typedef uint32_t Motor_Error_TypeDef;

//typedef Error Enum.
typedef enum
{
  ME_HardWareOverCurrentA = 0,
  ME_HardWareOverCurrentB,
  ME_UnderVoltage,
  ME_OverVoltage,
  ME_HallLost,
  ME_OverLoad,
  ME_OverTemperature,
  ME_ComLost,
  ME_OverSpeed,
}Motor_Error_Flag_TypeDef;

/*Global Declare.
*/
extern Motor_Error_TypeDef Motor_Error_Flag;

__RAM_RUN void Motor_Error_Set(Motor_Error_TypeDef* TempState,
                               Motor_Error_Flag_TypeDef TempFlag
                              );
__RAM_RUN void Motor_Error_Clear(Motor_Error_TypeDef* TempState,
                                 Motor_Error_Flag_TypeDef TempFlag
                                );
__RAM_RUN bool Motor_Error_Get(Motor_Error_TypeDef* TempState,
                               Motor_Error_Flag_TypeDef TempFlag
                              );

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

