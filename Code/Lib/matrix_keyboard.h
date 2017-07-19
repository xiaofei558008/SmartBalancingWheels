/*This is type define which is used in matrix keyboard.c.
File name : Matrix_Keyboard_CallBack.h
All rights reserved,if the code is not authorized by STMicroelectronic.
2016-09-01 15:22:38 Tom.xiao@st.com
*/

#ifndef __MATRIX_KEY_BOARD
#define __MATRIX_KEY_BOARD

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

/* keyboard and key scan parameters define;
*/
//the scale of keyboard is row_num * column_num;
//define row(Out) lines number;
#define row_num                 1
//define column(In) lines number;
#define column_num              3

#define key_control_time        5
#define key_pressdown_time      15  //if the key pressdown longer then 15*key_pressdown_time ms
//then it regard as keeping pressdown mode;

//after key_check_time,then the software get the key num(time >= (key_ckeck_time+1)*10)ms);
#define key_check_time          5

//GPIO Input Pins Define.
#define L0_In_Port              GPIOC
#define L0_In_Pin               GPIO_Pin_1
#define L0_In_Pin_Num           1

#define L1_In_Port              GPIOD
#define L1_In_Pin               GPIO_Pin_2
#define L1_In_Pin_Num           2

#define L2_In_Port              GPIOC
#define L2_In_Pin               GPIO_Pin_9
#define L2_In_Pin_Num           9

//GPIO Output Pins Define.
#define L0_Out_Port             GPIOD
#define L0_Out_Pin              GPIO_Pin_5
#define L0_Out_Pin_Num          5

#define L1_Out_Port             GPIOD
#define L1_Out_Pin              GPIO_Pin_6
#define L1_Out_Pin_Num          6

#define L2_Out_Port             GPIOD
#define L2_Out_Pin              GPIO_Pin_7
#define L2_Out_Pin_Num          7

/*Below is the key in and out pins definition;
*/
//input define(if the input pins is not used,please define it as "1");
#define L0_In                   ((L0_In_Port->IDR >> L0_In_Pin_Num) & 0x01)
#define L1_In                   ((L1_In_Port->IDR >> L1_In_Pin_Num) & 0x01)
#define L2_In                   ((L2_In_Port->IDR >> L2_In_Pin_Num) & 0x01)
#define L3_In                   1
#define L4_In                   1
#define L5_In                   1
#define L6_In                   1
#define L7_In                   1
#define L8_In                   1
#define L9_In                   1
#define L10_In                  1
#define L11_In                  1
#define L12_In                  1
#define L13_In                  1
#define L14_In                  1
#define L15_In                  1

//output define(if the output pins is not used,please define it as "__asm("NOP")")
#define L0_Out0                 __asm("NOP")
#define L1_Out0                 __asm("NOP")
#define L2_Out0                 __asm("NOP")
#define L3_Out0                 __asm("NOP")
#define L4_Out0                 __asm("NOP")
#define L5_Out0                 __asm("NOP")
#define L6_Out0                 __asm("NOP")
#define L7_Out0                 __asm("NOP")
#define L8_Out0                 __asm("NOP")
#define L9_Out0                 __asm("NOP")
#define L10_Out0                __asm("NOP")
#define L11_Out0                __asm("NOP")
#define L12_Out0                __asm("NOP")
#define L13_Out0                __asm("NOP")
#define L14_Out0                __asm("NOP")
#define L15_Out0                __asm("NOP")

#define L0_Out1                 __asm("NOP")
#define L1_Out1                 __asm("NOP")
#define L2_Out1                 __asm("NOP")
#define L3_Out1                 __asm("NOP")
#define L4_Out1                 __asm("NOP")
#define L5_Out1                 __asm("NOP")
#define L6_Out1                 __asm("NOP")
#define L7_Out1                 __asm("NOP")
#define L8_Out1                 __asm("NOP")
#define L9_Out1                 __asm("NOP")
#define L10_Out1                __asm("NOP")
#define L11_Out1                __asm("NOP")
#define L12_Out1                __asm("NOP")
#define L13_Out1                __asm("NOP")
#define L14_Out1                __asm("NOP")
#define L15_Out1                __asm("NOP")

/* keyboard struct
*/
typedef struct
{
  uint8_t bit0:1;
  uint8_t bit1:1;
  uint8_t bit2:1;
  uint8_t bit3:1;
  uint8_t bit4:1;
  uint8_t bit5:1;
  uint8_t bit6:1;
  uint8_t bit7:1;
  uint8_t bit8:1;
  uint8_t bit9:1;
  uint8_t bit10:1;
  uint8_t bit11:1;
  uint8_t bit12:1;
  uint8_t bit13:1;
  uint8_t bit14:1;
  uint8_t bit15:1;
} matrix_struct_bits16;

typedef union
{
  uint16_t             all;
  matrix_struct_bits16 flag;
} matrix_u16_Bit;

typedef struct
{
  bool           flag_scan;

  uint8_t        count;
  uint8_t        scan_count;
  uint8_t        same_count;
  uint8_t        down_count;      //key press down count;

  matrix_u16_Bit group[2][16];    //for shake cleaning,7--based on read in lines(column)A group.
  matrix_u16_Bit flag[16];        //final key flags,after shake time;

  uint16_t       num[2];          //use for shake cleaning,the absolute key num
  uint16_t       now;             //final key num,after shake time;
  uint16_t       down;            //key press down data;

  uint16_t       trigger;         //first time press down flag(=1);
} Matrix_Keyboard_TypeDef;

/* Variables of key structure definition;
*/
extern Matrix_Keyboard_TypeDef Matrix_Key_Data;

/*functions declare;
*/
void Matrix_Keyport_Init(Matrix_Keyboard_TypeDef* temp);
void Matrix_Key_Scan(Matrix_Keyboard_TypeDef* key);
static void Matrix_Key_Num_Control_CallBack(Matrix_Keyboard_TypeDef* key);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

