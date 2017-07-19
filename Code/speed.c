/*This is the speed functions.
File name :speed.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-11 10:50:28
*/

#include "speed.h"

//speed define.
Speed_Struct_TypeDef Motor_Speed;

//init speed datas.
void Speed_Init(Speed_Struct_TypeDef* Temp)
{
  uint8_t temp;

  Temp->flag_stop = 0x00;
  Temp->cap       = 0x00;
  Temp->cap_old   = 0x00;
  Temp->cap_delta = 0x00;
  Temp->ave       = 0x00;
  Temp->ave_old   = 0x00;

  for(temp = 0; temp < SPEED_AVE_TIME; temp ++)
  {
    Temp->ave_buf[temp] = 0x00;
  }

  Temp->point = 0x00;


  //Select Speed PID.
  //Temp->PID_Speed = &PID_X_V;
}

/* Calculate Speed.
*/
void Speed_Calculate(Speed_Struct_TypeDef* Temp)
{
  uint8_t  temp;
  int32_t  temp_add = 0;

  if(TIM16->SR & 0x01) //Timer Cap Overflow -- Motor stops now.
  {
    //Clear Flag.
    TIM16->SR = 0xfffe;

    //Upadte Old Data.
    Temp->cap       = 0x00;
    Temp->cap_old   = 0x00;
    Temp->cap_delta = 0x00;
    Temp->ave       = 0x00;
    Temp->ave_old   = 0x00;

    for(temp = 0; temp < SPEED_AVE_TIME; temp ++)
    {
      Temp->ave_buf[temp] = 0x00;
    }

    Temp->point = 0x00;
  }//end of if(Temp->flag_overflow)
  else                //Cap normally.
  {
    //Judge a new speed calculate.
    if(Temp->cap_old != Temp->cap)
    {
      //Speed Data Cal.
      if(Temp->cap < Temp->cap_old)
      {
        Temp->cap_delta = Temp->cap + SPEED_COUNT_TOP - Temp->cap_old;
      }
      else
      {
        if(Temp->cap_old)   //not first time cap.
        {
          Temp->cap_delta = Temp->cap - Temp->cap_old;
        }
        else                //First Cap.
        {
          Temp->cap_delta = Temp->cap;
        }
      }

      //Update Old Data.
      Temp->cap_old = Temp->cap;
      Temp->ave_old = Temp->ave;

      //Set Calculate Limit.
      if(Temp->cap_delta > SPEED_CAP_MAX)
      {
        Temp->cap_delta = SPEED_CAP_MAX;
      }
      else if(Temp->cap_delta < SPEED_CAP_MIN)
      {
        Temp->cap_delta = SPEED_CAP_MIN;
      }

      //Speed Dir Cal.
      if((TIM3->CR1 & 0x0010) != 0)
      {
        Temp->cap_delta = -Temp->cap_delta;
      }

      //Calculate Speed.
      Temp->ave_buf[Temp->point] = SPEED_CONSTANT_Q4 / Temp->cap_delta;

      for(temp = 0; temp < SPEED_AVE_TIME; temp ++)
      {
        temp_add += Temp->ave_buf[temp];
      }

      temp_add /= SPEED_AVE_TIME;

  #if SPEED_KALMAN_FILTER
      Temp->ave = (int32_t)kalman1_filter(&(Temp->state1_speed), temp_add);
  #else
      Temp->ave = temp_add;
  #endif

      //Set Limit.
      if(Temp->point < SPEED_AVE_TIME)
      {
        Temp->point ++;
      }
      else
      {
        Temp->point = 0;
      }
    } //end of if(Temp->cap_old != Temp->cap)
  }
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

