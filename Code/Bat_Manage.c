/*This is the Bat_Manage functions.
File name :Bat_Manage.c
All rights reserved,if the code is not authorized by STMicroelectronics.
E-mail:tom.xiao@ST.com
2016-04-26 14:44:28
*/

#include "Bat_Manage.h"

BAT_Manage_TypeDef Li_Ion_Bat;

//Battery Management Init.
void BAT_Manage_Init(BAT_Manage_TypeDef* Temp)
{
  //Clean Memory.
  memset(Temp,
         0,
         sizeof(BAT_Manage_TypeDef)
        );

  //Setup Parameters.
}

/* Battery Manage Loop. Every (50ms) Looping.
*/
void BAT_Manage_Loop(BAT_Manage_TypeDef* Temp)
{
  uint8_t i;

  //Calaulate Voltage in Float.
  Temp->VBat = BAT_Serial * BAT_ADC_Ref_Voltage * (Temp->ADC_BAT) * (BAT_Resister_Up_KOhm + BAT_Resister_Down_KOhm) / BAT_ADC_Level / BAT_Resister_Down_KOhm;

  //Insert into Buffer.
  Temp->VBat_Buffer[Temp->Count] = Temp->VBat;

  //Add Count.
  Temp->Count ++;

  if(Temp->Count >= BAT_ADC_Buffer_Depth)
  {
    //Clean Count.
    Temp->Count = 0;

    //Set Buffer Saturation.
    Temp->Saturation = true;
  }

  //Calculate Voltage Average.
  //Buffer is fulled.
  if(Temp->Saturation)
  {
    for(i = 0; i < BAT_ADC_Buffer_Depth; i++)
    {
      Temp->VBat_Ave_Add += Temp->VBat_Buffer[i];
    }

    //Calculate Average Voltage.
    Temp->VBat_Ave = Temp->VBat_Ave_Add / BAT_ADC_Buffer_Depth;
    Temp->VBat_Ave_Add = 0;
  }

  //Buffer is not fulled.
  else
  {
    for(i = 0; i < Temp->Count; i++)
    {
      Temp->VBat_Ave_Add += Temp->VBat_Buffer[i];
    }

    //Calculate Average Voltage.
    Temp->VBat_Ave = Temp->VBat_Ave_Add / Temp->Count;
    Temp->VBat_Ave_Add = 0;
  }

  //Damage Voltage.
  if(Temp->VBat_Ave > (BAT_Serial * BAT_Level_DamageVoltage))
  {
    Temp->Bat_Level = BAT_Damage;
    BAT_Damage_CallBack();
  }

  //High Voltage.
  else if(Temp->VBat_Ave > (BAT_Serial * BAT_Level_HighVoltage))
  {
    Temp->Bat_Level = BAT_High;
    BAT_High_CallBack();
  }

  //Low Voltage.
  else if(Temp->VBat_Ave < (BAT_Serial * BAT_Level_LowVoltage))
  {
    Temp->Bat_Level = BAT_Low;
    BAT_Low_CallBack();
  }

  //Normal Zone.
  else
  {
    //Low to Normal.
    if(Temp->Bat_Level == BAT_Low)
    {
      if(Temp->VBat_Ave > BAT_Serial * (BAT_Level_LowVoltage + BAT_HystersisVoltage_L * BAT_Serial))
      {
        Temp->Bat_Level = BAT_Normal;
        BAT_Low_To_Normal_CallBack();
      }
    }

    //High to normal.
    else if(Temp->Bat_Level == BAT_High)
    {
      if(Temp->VBat_Ave < BAT_Serial * (BAT_Level_HighVoltage - BAT_HystersisVoltage_H * BAT_Serial))
      {
        Temp->Bat_Level = BAT_Normal;
        BAT_High_To_Normal_CallBack();
      }
    }

    //Normal to normal
    else
    {
      BAT_Normal_To_Normal_CallBack();
    }

    BAT_Voltage_Normal_CallBack();
  }

  BAT_Manage_Loop_CallBack();
}

/* Bat power Loop callback functions.
*/
__weak void BAT_Manage_Loop_CallBack(void)
{
  //printf("##VBAT:%dmV\r\n\r\n",(uint16_t)(Li_Ion_Bat.VBat*1000));
}

//Bat Low power callback function.
__weak void BAT_Low_CallBack(void)
{
  //printf("##Battery Low! r\n");
}

//Bat Voltage Normal power callback function.
__weak void BAT_Voltage_Normal_CallBack(void)
{
  //printf("##Battery Normal!\r\n");
}

//Bat high power callback function.
__weak void BAT_High_CallBack(void)
{
  //printf("##Battery High.\r\n");
}

//Bat high power callback function.
__weak void BAT_Damage_CallBack(void)
{
  //printf("##Battery High.\r\n");
}

//Bat Low to Normal callback function.
__weak void BAT_Low_To_Normal_CallBack(void)
{
  //printf("##Battery Low To Normal!\r\n");
}

//Bat High to Normal callback function.
__weak void BAT_High_To_Normal_CallBack(void)
{
  //printf("##Battery High To Normal!\r\n");
}

//Bat Normal to Normal callback function.
__weak void BAT_Normal_To_Normal_CallBack(void)
{
  //printf("##Battery Normal To Normal!\r\n");
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

