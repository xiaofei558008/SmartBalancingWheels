/*This is matrix keyboard function;
File name : Matrix_Keyboard_CallBack.c
All rights reserved,if the code is not authorized by STMicroelectronic.
2017-04-19 16:10:50 Tom.xiao@st.com
*/

/*
max matrix keyboard net -- 32*32 1024 keys;

(Output)      |     |     |     |     |     |     |     |     |
row0   PB10---1-----2-----3-----4-----5-----6-----7-----|-----|-----
              |     |     |     |     |     |     |     |     |
row1   PB9----8-----9-----10----11----12----13----14----|-----|-----
              |     |     |     |     |     |     |     |     |
row2   PB11---15----16----17----18----19----20----21----|-----|-----
              |     |     |     |     |     |     |     |     |
row3   PB12---22----23----24----25----26----27----28----|-----|-----
              |     |     |     |     |     |     |     |     |
row4   PD12---29----30----31----32----33----34----35----|-----|-----
              |     |     |     |     |     |     |     |     |
row5   PD0----36----37----38----39----40----41----42----|-----|-----
              |     |     |     |     |     |     |     |     |
row6   PD1----43----44----45----46----47----48----49----|-----|-----
.             |     |     |     |     |     |     |     |     |
.         ----|-----|-----|-----|-----|-----|-----|-----|-----|-----
.             |     |     |     |     |     |     |     |     |
row31     ----|-----|-----|-----|-----|-----|-----|-----|-----1024--
             PA12  PA13  PA14  PE0   PE1   PE2   PE3    |     |
              |     |     |     |     |     |     |     |     |
            colu0 colu1 colu2 colu3 colu4 colu5 colu6  ...  colu31 (input/Pull up)
*/

#include "Matrix_Keyboard.h"
#include "Matrix_Keyboard_CallBack.h"
#include "bsp.h"
#include "clarke_park.h"
#include "Balancing.h"
#include "Error.h"

/* Key-Board CallBack Functions.
*/
#define APWM_Start()        TIM_CtrlPWMOutputs(TIM1, ENABLE)
#define APWM_Stop()         TIM_CtrlPWMOutputs(TIM1, DISABLE)

#define BPWM_Start()        TIM_CtrlPWMOutputs(TIM8, ENABLE)
#define BPWM_Stop()         TIM_CtrlPWMOutputs(TIM8, DISABLE)


#define Pedal_Keep_Time     5

static uint8_t AKeep_Time, BKeep_Time;


/* Key Union CallBacks.
*/
void Key_Union_CallBack(Matrix_Keyboard_TypeDef* key)
{
  /*  R1C1+R1C2 key
  */
  /*
  if(key->flag[0].flag.bit0 &&    //key in row 1 column 1;
     key->flag[0].flag.bit1       //key in row 1 column 2;
    )
  {
    if(key->trigger)              //press the key down first time;
    {
      key->trigger = 0;
      key->down_count = 0;

      // user add the one time mode code below;

    }
    else
    {
      key->down_count ++;
      if(key->down_count >= key_pressdown_time)
      {
        key->down_count = key_pressdown_time;

        // user add the keeping pressdown mode code below;

      }
    }
  }
  */

  //#####key-1 (Power Switch)#####
  if(key->flag[0].flag.bit0)
  {
    if(key->trigger)              //press the key down first time;
    {
      key->trigger = 0;
      key->down_count = 0;

      // user add the one time mode code below;

    }
    else
    {
      key->down_count ++;
      if(key->down_count >= 3 * key_pressdown_time)
      {
        key->down_count = 3 * key_pressdown_time;

        // user add the keeping pressdown mode code below;
        Power_OFF();              //System Power OFF.
      }
    }
  }

  //#####Key-2 (Pedal - Right(B Side))#####
  if(key->flag[0].flag.bit1)
  {
    if(key->trigger)              //press the key down first time;
    {
      key->trigger = 0;
      key->down_count = 0;

      // user add the one time mode code below;
      //BClarkePark.UpdateFlag = 1;
    }
    else
    {
      key->down_count ++;
      if(key->down_count >= key_pressdown_time)
      {
        key->down_count = key_pressdown_time;

        // user add the keeping pressdown mode code below;
        //No errors.
        if(Motor_Error_Get(&Motor_Error_Flag, ME_HardWareOverCurrentB) == 0)
        {
          BPWM_Start();
          BClarkePark.UpdateFlag = 1;
          BKeep_Time = Pedal_Keep_Time;
        }
      }
    }
  }

  //Key-2 (Pedal - Right(B side)) Release.
  else
  {
    //Release Pedal A.
    if(BKeep_Time == 0)
    {
      //Disable PWM.
      BPWM_Stop();

      //Disable FOC.
      BClarkePark.UpdateFlag = 0;

      //Reset PIDs.
      PID_Clear(&(BClarkePark.PID_ID));
      PID_Clear(&(BClarkePark.PID_IQ));

      PID_Clear(&(Balancing.BAnglePI));
      PID_Clear(&(Balancing.BAngleSpeedPI));
    }
    else
    {
      BKeep_Time --;
    }
  }

  //#####Key-3 (Pedal - Left(A side)) Press down.#####
  if(key->flag[0].flag.bit2)
  {
    if(key->trigger)              //press the key down first time;
    {
      key->trigger = 0;
      key->down_count = 0;

      // user add the one time mode code below;

    }
    else
    {
      key->down_count ++;
      if(key->down_count >= key_pressdown_time)
      {
        key->down_count = key_pressdown_time;

        // user add the keeping pressdown mode code below;
        //No errors.
        if(Motor_Error_Get(&Motor_Error_Flag, ME_HardWareOverCurrentA) == 0)
        {
          APWM_Start();
          AClarkePark.UpdateFlag = 1;
          AKeep_Time = Pedal_Keep_Time;
        }
      }
    }
  }

  //Key-3 (Pedal - Left(A side)) Release.
  else
  {
    //Release Pedal B.
    if(AKeep_Time == 0)
    {
      //Disable PWM.
      APWM_Stop();

      //Disable FOC.
      AClarkePark.UpdateFlag = 0;

      //Reset PIDs.
      PID_Clear(&(AClarkePark.PID_ID));
      PID_Clear(&(AClarkePark.PID_IQ));

      PID_Clear(&(Balancing.AAnglePI));
      PID_Clear(&(Balancing.AAngleSpeedPI));
    }
    else
    {
      AKeep_Time --;
    }
  }
}

/* Key Trigger CallBacks;
*/
void Key_Trigger_CallBack(Matrix_Keyboard_TypeDef* key)
{
  switch(key->now)
  {
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;

  }
}

/* Key Press Down CallBacks.
*/
void Key_PressDown_CallBack(Matrix_Keyboard_TypeDef* key)
{
  switch(key->now)
  {
  case 1:
    break;
  case 2: //BClarkePark.UpdateFlag = 1;
    break;
  case 3: //AClarkePark.UpdateFlag = 1;
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  }
}

/* All Keys Release CallBack.
*/
void Key_Release_CallBack(Matrix_Keyboard_TypeDef* key)
{

}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/


