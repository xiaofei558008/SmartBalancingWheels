/*This is the main functions.
File name :main.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-16 16:03:28
*/

#include "main.h"

#include "IIC_Software.h"
#include "lsm6ds3.h"
#include "FlyControl.h"
#include "Matrix_Keyboard.h"
#include "Matrix_Keyboard_CallBack.h"
#include "Balancing.h"
#include "Bat_Manage.h"

/* main body
*/
int main(void)
{
#ifdef USE_BOOTLOADER
  //Vector Table  : 0x08005000
  //Memory Regions: 0x08005000

  //Set The New Vector T    able.
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 20480);
#endif

  //Set Interrupt Group.
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  //disable all IRQ.
  __disable_irq();

  //HardWare Init.
  Bsp_Init();

  //Power ON.
  Power_ON();

  //Sensor Power On.
  Sen_Power_OFF();
  Delay(1000000);

  Sen_Power_ON();
  Delay(1000000);

  //Matrix Keyboard Initlication.
  Matrix_Keyport_Init(&Matrix_Key_Data);

  //Battery Management Init.
  BAT_Manage_Init(&Li_Ion_Bat);

  //init Angle.
  Angle_Init(&AHallAngle,
             A_HALL_U_GPIO,
             A_HALL_V_GPIO,
             A_HALL_W_GPIO,
             A_HALL_U_PIN_NUM,
             A_HALL_V_PIN_NUM,
             A_HALL_W_PIN_NUM,
             TIM4
            );

  Angle_Init(&BHallAngle,
             B_HALL_U_GPIO,
             B_HALL_V_GPIO,
             B_HALL_W_GPIO,
             B_HALL_U_PIN_NUM,
             B_HALL_V_PIN_NUM,
             B_HALL_W_PIN_NUM,
             TIM3
            );

  //init flags in system.
  Flag_Init(&Systick_Flag);

  //init Clarke Park SVPWM.
  ClarkePark_PID_SVPWM_Init(&AClarkePark,   //ClarkePark_TypeDef* Temp,
                            &AHallAngle,       //Angle_TypeDef*      Angle,
                            TIM1,           //TIM_TypeDef*        TIM_PWM,
                            TIM4            //TIM_TypeDef*        TIM_ANG,
                           );

  ClarkePark_PID_SVPWM_Init(&BClarkePark,   //ClarkePark_TypeDef* Temp,
                            &BHallAngle,       //Angle_TypeDef*      Angle,
                            TIM8,           //TIM_TypeDef*        TIM_PWM,
                            TIM3            //TIM_TypeDef*        TIM_ANG,
                           );
  //IIC GPIO Init.
  IIC_Init();

  //Init Balancing Module.
  Blanecing_Init(&Balancing);

  //enable all IRQ.
  __enable_irq();

  //Main loop.
  for(;;)
  {
    //Balancing Keeping.
    Balancing_Keeping_Loop(&Balancing);
  }
}

//Delay Function.
void Delay(uint32_t delaytime)
{
  while(delaytime --);
}

/********** End of file *********** Copy B Reserved by STMicroelectronics ***********/

