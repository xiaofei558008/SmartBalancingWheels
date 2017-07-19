/*This is the Smart Balancing functions.
File name :Balancing.c
All rights reserved,if the code is not authorized by STMicroelectronics.
2017-06-19 15:51:16 Tom.xiao@st.com
*/

#include "Balancing.h"
#include "FlyControl.h"
#include "clarke_park.h"
#include "lsm6ds3.h"

//Sensors' Address Define.
#define AAxisAddr               LSM6DS3_ADDRESS_LOW
#define BAxisAddr               LSM6DS3_ADDRESS_HIGH

#define Axis_Direction_Up       0   //For Debug Test.
#define Axis_Direction_Down     1   //For Real Running.
#define Axis_Direction          Axis_Direction_Down

Banalcing_Keeping_TypeDef Balancing;
AccGyro_TypeDef AAxis6, BAxis6;

/* Balancing Keeping Init.
*
*/
void Blanecing_Init(Banalcing_Keeping_TypeDef* Temp)
{
  /* Clear RAM.
  */
  memset(Temp,
         0,
         sizeof(Banalcing_Keeping_TypeDef)
        );

  /* A Side PID Setup.
  *
  */
  /* Angle PI Set Parameters.
  */
  PID_Init(&Temp->AAnglePI,
           Angle_Kp,
           Angle_Ki,
           Angle_Kd,
           Angle_ErrorMax,
           Angle_ErrorMin,
           Angle_OutputMax,
           Angle_OutputMin
          );

  /* Angle Speed PI Set Parameters.
  */
  PID_Init(&Temp->AAngleSpeedPI,
           AngleSpeed_Kp,
           AngleSpeed_Ki,
           AngleSpeed_Kd,
           AngleSpeed_ErrorMax,
           AngleSpeed_ErrorMin,
           AngleSpeed_OutputMax,
           AngleSpeed_OutputMin
          );

  /* B Side PID Setup.
  *
  */
  /* Angle PI Set Parameters.
  */
  PID_Init(&Temp->BAnglePI,
           Angle_Kp,
           Angle_Ki,
           Angle_Kd,
           Angle_ErrorMax,
           Angle_ErrorMin,
           Angle_OutputMax,
           Angle_OutputMin
          );

  /* Angle Speed PI Set Parameters.
  */
  PID_Init(&Temp->BAngleSpeedPI,
           AngleSpeed_Kp,
           AngleSpeed_Ki,
           AngleSpeed_Kd,
           AngleSpeed_ErrorMax,
           AngleSpeed_ErrorMin,
           AngleSpeed_OutputMax,
           AngleSpeed_OutputMin
          );

  //Init Sensors.
  IMU_6AXES_InitTypeDef AG_Init;

  AG_Init.G_FullScale      = LSM6DS3_G_FS_245;  //LSM6DS3_G_FS_2000;
  AG_Init.G_OutputDataRate = LSM6DS3_G_ODR_1K66HZ;
  AG_Init.G_X_Axis         = LSM6DS3_G_XEN_ENABLE;
  AG_Init.G_Y_Axis         = LSM6DS3_G_YEN_ENABLE;
  AG_Init.G_Z_Axis         = LSM6DS3_G_ZEN_ENABLE;

  AG_Init.X_FullScale      = LSM6DS3_XL_FS_4G;  //LSM6DS3_XL_FS_8G;
  AG_Init.X_OutputDataRate = LSM6DS3_XL_ODR_3K33HZ;
  AG_Init.X_X_Axis         = LSM6DS3_XL_XEN_ENABLE;
  AG_Init.X_Y_Axis         = LSM6DS3_XL_YEN_ENABLE;
  AG_Init.X_Z_Axis         = LSM6DS3_XL_ZEN_ENABLE;

  LSM6DS3Drv.Init(AAxisAddr, &AG_Init);
  LSM6DS3Drv.Init(BAxisAddr, &AG_Init);

  LSM6DS3Drv.Read_XG_ID(AAxisAddr, &AAxis6.Device_ID);
  LSM6DS3Drv.Read_XG_ID(BAxisAddr, &BAxis6.Device_ID);

  //A.
  //Init FC and AHRS.
  FlyControl_Init(&AFlyCtrl,         //FlyControl_TypeDef* Temp,
                  &AAxis6,      //AccGyro_TypeDef*    RawData,
                  AHRS_KP_A,     //float               Kp,
                  AHRS_KI_A,     //float               Ki,
                  TIM2           //TIM_TypeDef*        TIMx,
                 );
  //B.
  //Init FC and AHRS.
  FlyControl_Init(&BFlyCtrl,        //FlyControl_TypeDef* Temp,
                  &BAxis6,     //AccGyro_TypeDef*    RawData,
                  AHRS_KP_B,    //float               Kp,
                  AHRS_KI_B,    //float               Ki,
                  TIM2          //TIM_TypeDef*        TIMx,
                 );
}

/* Balancing Keeping Loop.
*  P  - Angle(160Hz)
*  PI - AngleSpeed(1.6KHz)
*  PI - Current(16KHz).
*/
void Balancing_Keeping_Loop(Banalcing_Keeping_TypeDef* Temp)
{
  //1.6KHz.
  if((AClarkePark.Counter % 10) == 0)
  {
    AClarkePark.Counter ++;

    /* Sensor Read & AHRS Calculation.
    */
    //Read Sensors.
    LSM6DS3Drv.Get_Axes_Fast(AAxisAddr, &AAxis6.Gyro_Reg_Raw.AXIS_X);
    LSM6DS3Drv.Get_Axes_Fast(BAxisAddr, &BAxis6.Gyro_Reg_Raw.AXIS_X);

    /* Axis A.
    */
    // Axis Align.
#if Axis_Direction == Axis_Direction_Down
    AAxis6.Gyro_Rel_Raw.AXIS_X =  AAxis6.Gyro_Reg_Raw.AXIS_X;
    AAxis6.Gyro_Rel_Raw.AXIS_Y = -AAxis6.Gyro_Reg_Raw.AXIS_Y;
    AAxis6.Gyro_Rel_Raw.AXIS_Z = -AAxis6.Gyro_Reg_Raw.AXIS_Z;

    AAxis6.Acc_Rel_Raw.AXIS_X =  AAxis6.Acc_Reg_Raw.AXIS_X;
    AAxis6.Acc_Rel_Raw.AXIS_Y = -AAxis6.Acc_Reg_Raw.AXIS_Y;
    AAxis6.Acc_Rel_Raw.AXIS_Z = -AAxis6.Acc_Reg_Raw.AXIS_Z;

#elif Axis_Direction == Axis_Direction_Up
    AAxis6.Gyro_Rel_Raw.AXIS_X = AAxis6.Gyro_Reg_Raw.AXIS_X;
    AAxis6.Gyro_Rel_Raw.AXIS_Y = AAxis6.Gyro_Reg_Raw.AXIS_Y;
    AAxis6.Gyro_Rel_Raw.AXIS_Z = AAxis6.Gyro_Reg_Raw.AXIS_Z;

    AAxis6.Acc_Rel_Raw.AXIS_X = AAxis6.Acc_Reg_Raw.AXIS_X;
    AAxis6.Acc_Rel_Raw.AXIS_Y = AAxis6.Acc_Reg_Raw.AXIS_Y;
    AAxis6.Acc_Rel_Raw.AXIS_Z = AAxis6.Acc_Reg_Raw.AXIS_Z;
#endif

#if 0
    //Calculate Gyro(2000Degree/s).
    AAxis6.Gyro_Float.AXIS_X = AAxis6.Gyro_Rel_Raw.AXIS_X * 70;
    AAxis6.Gyro_Float.AXIS_Y = AAxis6.Gyro_Rel_Raw.AXIS_Y * 70;
    AAxis6.Gyro_Float.AXIS_Z = AAxis6.Gyro_Rel_Raw.AXIS_Z * 70;

    //Calculate Acc(8g).
    AAxis6.Acc_Float.AXIS_X = AAxis6.Acc_Rel_Raw.AXIS_X * 0.244140625;
    AAxis6.Acc_Float.AXIS_Y = AAxis6.Acc_Rel_Raw.AXIS_Y * 0.244140625;
    AAxis6.Acc_Float.AXIS_Z = AAxis6.Acc_Rel_Raw.AXIS_Z * 0.244140625;

#else
    //Calculate Gyro(245Degree/s).
    AAxis6.Gyro_Float.AXIS_X = AAxis6.Gyro_Rel_Raw.AXIS_X * 8.75;
    AAxis6.Gyro_Float.AXIS_Y = AAxis6.Gyro_Rel_Raw.AXIS_Y * 8.75;
    AAxis6.Gyro_Float.AXIS_Z = AAxis6.Gyro_Rel_Raw.AXIS_Z * 8.75;

    //Calculate Acc(4g).
    AAxis6.Acc_Float.AXIS_X = AAxis6.Acc_Rel_Raw.AXIS_X * 0.1220703125;
    AAxis6.Acc_Float.AXIS_Y = AAxis6.Acc_Rel_Raw.AXIS_Y * 0.1220703125;
    AAxis6.Acc_Float.AXIS_Z = AAxis6.Acc_Rel_Raw.AXIS_Z * 0.1220703125;

#endif
    /* Axis B.
    */
    // Axis Align.
#if Axis_Direction == Axis_Direction_Down
    BAxis6.Gyro_Rel_Raw.AXIS_X = -BAxis6.Gyro_Reg_Raw.AXIS_X;
    BAxis6.Gyro_Rel_Raw.AXIS_Y =  BAxis6.Gyro_Reg_Raw.AXIS_Y;
    BAxis6.Gyro_Rel_Raw.AXIS_Z = -BAxis6.Gyro_Reg_Raw.AXIS_Z;

    BAxis6.Acc_Rel_Raw.AXIS_X = -BAxis6.Acc_Reg_Raw.AXIS_X;
    BAxis6.Acc_Rel_Raw.AXIS_Y =  BAxis6.Acc_Reg_Raw.AXIS_Y;
    BAxis6.Acc_Rel_Raw.AXIS_Z = -BAxis6.Acc_Reg_Raw.AXIS_Z;

#elif Axis_Direction == Axis_Direction_Up
    BAxis6.Gyro_Rel_Raw.AXIS_X = BAxis6.Gyro_Reg_Raw.AXIS_X;
    BAxis6.Gyro_Rel_Raw.AXIS_Y = BAxis6.Gyro_Reg_Raw.AXIS_Y;
    BAxis6.Gyro_Rel_Raw.AXIS_Z = BAxis6.Gyro_Reg_Raw.AXIS_Z;

    BAxis6.Acc_Rel_Raw.AXIS_X = BAxis6.Acc_Reg_Raw.AXIS_X;
    BAxis6.Acc_Rel_Raw.AXIS_Y = BAxis6.Acc_Reg_Raw.AXIS_Y;
    BAxis6.Acc_Rel_Raw.AXIS_Z = BAxis6.Acc_Reg_Raw.AXIS_Z;
#endif

#if 0
    //Calculate Gyro(2000Degree/s).
    BAxis6.Gyro_Float.AXIS_X = BAxis6.Gyro_Rel_Raw.AXIS_X * 70;
    BAxis6.Gyro_Float.AXIS_Y = BAxis6.Gyro_Rel_Raw.AXIS_Y * 70;
    BAxis6.Gyro_Float.AXIS_Z = BAxis6.Gyro_Rel_Raw.AXIS_Z * 70;

    //Calculate Acc(8g).
    BAxis6.Acc_Float.AXIS_X = BAxis6.Acc_Rel_Raw.AXIS_X * 0.244140625;
    BAxis6.Acc_Float.AXIS_Y = BAxis6.Acc_Rel_Raw.AXIS_Y * 0.244140625;
    BAxis6.Acc_Float.AXIS_Z = BAxis6.Acc_Rel_Raw.AXIS_Z * 0.244140625;

#else
    //Calculate Gyro(245Degree/s).
    BAxis6.Gyro_Float.AXIS_X = BAxis6.Gyro_Rel_Raw.AXIS_X * 8.75;
    BAxis6.Gyro_Float.AXIS_Y = BAxis6.Gyro_Rel_Raw.AXIS_Y * 8.75;
    BAxis6.Gyro_Float.AXIS_Z = BAxis6.Gyro_Rel_Raw.AXIS_Z * 8.75;

    //Calculate Acc(4g).
    BAxis6.Acc_Float.AXIS_X = BAxis6.Acc_Rel_Raw.AXIS_X * 0.1220703125;
    BAxis6.Acc_Float.AXIS_Y = BAxis6.Acc_Rel_Raw.AXIS_Y * 0.1220703125;
    BAxis6.Acc_Float.AXIS_Z = BAxis6.Acc_Rel_Raw.AXIS_Z * 0.1220703125;

#endif
    /* Angle Speed PID.
    */
    //Read Feedback Angle Speed.
    Temp->AAngleSpeedPI.Feedback =  AAxis6.Gyro_Rel_Raw.AXIS_X;
    Temp->BAngleSpeedPI.Feedback =  BAxis6.Gyro_Rel_Raw.AXIS_X;

#if 1
    AClarkePark.PID_IQ.Reference =  PID_ModuleQ12(&Temp->AAngleSpeedPI);
    BClarkePark.PID_IQ.Reference = -PID_ModuleQ12(&Temp->BAngleSpeedPI);
#endif

    /*160Hz.*/
    if((Temp->Counter % 10) == 0)
    {
      //AHRS Calculate.
      FlyControl_Loop(&AFlyCtrl);
      FlyControl_Loop(&BFlyCtrl);

      /* A & B Angle Filter.
      */
#if 0
      AFlyCtrl.AHRS.hDegreeAngle.AXIS_X /= AngleABFilterConst;
      BFlyCtrl.AHRS.hDegreeAngle.AXIS_X /= AngleABFilterConst;

      AFlyCtrl.AHRS.hDegreeAngle.AXIS_X *= AngleABFilterConst;
      BFlyCtrl.AHRS.hDegreeAngle.AXIS_X *= AngleABFilterConst;
#endif
      /* A side Angle PID.
      *
      */
      // SBW Angle Overflow.
      if(AFlyCtrl.AHRS.hDegreeAngle.AXIS_X < SBW_Error_Angle_Min)
      {
        ABalancing_Angle_Overflow_CallBack(Temp);
      }

      //SBW in normal angle.
      else if(AFlyCtrl.AHRS.hDegreeAngle.AXIS_X < SBW_Error_Angle_Max)
      {
        //Get A side Feedback.
        Temp->AAnglePI.Feedback = AFlyCtrl.AHRS.hDegreeAngle.AXIS_X;

        //Output to A side Angle Speed PI.
        Temp->AAngleSpeedPI.Reference = PID_ModuleQ12(&Temp->AAnglePI);
      }

      // SBW Angle Overflow.
      else
      {
        ABalancing_Angle_Overflow_CallBack(Temp);
      }

      /* B side Angle PID.
      *
      */
      // SBW Angle Overflow.
      if(BFlyCtrl.AHRS.hDegreeAngle.AXIS_X < SBW_Error_Angle_Min)
      {
        BBalancing_Angle_Overflow_CallBack(Temp);
      }

      //SBW in normal angle.
      else if(BFlyCtrl.AHRS.hDegreeAngle.AXIS_X < SBW_Error_Angle_Max)
      {
        //Get B side Feedback.
        Temp->BAnglePI.Feedback = BFlyCtrl.AHRS.hDegreeAngle.AXIS_X;

        //Output to B side Angle Speed PI.
        Temp->BAngleSpeedPI.Reference = PID_ModuleQ12(&Temp->BAnglePI);
      }

      // SBW Angle Overflow.
      else
      {
        BBalancing_Angle_Overflow_CallBack(Temp);
      }
    } //end of 160Hz Loop.

    /* Add Counter.
    *
    */
    Temp->Counter ++;
  }
}

/* Smart Balancing Wheels Angle Overflow.
*
*/
__weak void ABalancing_Angle_Overflow_CallBack(Banalcing_Keeping_TypeDef* Temp)
{

}

__weak void BBalancing_Angle_Overflow_CallBack(Banalcing_Keeping_TypeDef* Temp)
{

}


/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

