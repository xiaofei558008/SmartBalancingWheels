/*This is the Bat_Manage functions' head.
File name :Bat_Manage.h
All rights reserved,if the code is not authorized by STMicroelectronics.
E-mail:tom.xiao@ST.com
2016-04-26 14:44:28
*/

#ifndef __BAT_MANAGE_H
#define __BAT_MANAGE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

/* Define ADC Update Loop Period.
   Li-Ion Battery is 3.0V Empty, 4.2V Full, 4.35V Damage.
*/
#define BAT_ADC_Buffer_Depth      32
#define BAT_ADC_Level             4096
/* Voltage Level & Parameters Define.
*/
#define BAT_Resister_Up_KOhm      100.0
#define BAT_Resister_Down_KOhm    10.0
#define BAT_ADC_Ref_Voltage       3.3

#define BAT_Serial                10
#define BAT_Level_LowVoltage      3.30
#define BAT_Level_HighVoltage     4.18
#define BAT_Level_DamageVoltage   4.25
#define BAT_HystersisVoltage_L    0.5       //3.3 -> 3.8 Recovery Normal.
#define BAT_HystersisVoltage_H    0.2       //4.18->3.98 High Area.

/* Battery State Define.
*/
typedef enum
{
  BAT_Normal = 0,
  BAT_Low    = 1,
  BAT_High   = 2,
  BAT_Damage = 3,
}BAT_Level_TypeDef;

/* typedef Battery Management Structure.
*/
typedef struct
{
  bool              Saturation;
  uint8_t           Count;
  uint16_t          ADC_BAT;
  float             VBat;
  float             VBat_Ave;
  float             VBat_Ave_Add;
  float             VBat_Buffer[BAT_ADC_Buffer_Depth];
  BAT_Level_TypeDef Bat_Level;
}BAT_Manage_TypeDef;

/* Global declare.
*/
extern BAT_Manage_TypeDef Li_Ion_Bat;

void BAT_Manage_Init(BAT_Manage_TypeDef* Temp);
void BAT_Manage_Loop(BAT_Manage_TypeDef* Temp);

void BAT_Manage_Loop_CallBack(void);
void BAT_Low_CallBack(void);
void BAT_High_CallBack(void);
void BAT_Damage_CallBack(void);
void BAT_Voltage_Normal_CallBack(void);

/* Bat Low to Normal callback function.
*/
void BAT_Low_To_Normal_CallBack(void);
void BAT_High_To_Normal_CallBack(void);
void BAT_Normal_To_Normal_CallBack(void);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

