/*This is the IIC Software functions' head.
File name :IIC_Software.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2016-06-02 10:58:28
*/

#ifndef __IIC_SOFTWARE_H
#define __IIC_SOFTWARE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "stm32f30x.h"

//IIC Software PORTs & PINs Define.
//SDA.
#define SDA_PORT            GPIOC
#define SDA_PIN_Num         13

//SCL.
#define SCL_PORT            GPIOC
#define SCL_PIN_Num         14

#define SDA_PIN_Mode_IN     0
#define SDA_PIN_Mode_OUT    1

//Delay Define
//IIC Clock Delay Define.
#define Sen_IIC_Low         0
#define Sen_IIC_Middle      1
#define Sen_IIC_High        2
#define Sen_IIC_Clk         Sen_IIC_High    //Sen_IIC_Middle

#if(Sen_IIC_Clk == Sen_IIC_Low)
#define STR_Del             100
#define STP_Del             100

#define SDA_L_Del           100
#define SDA_H_Del           100

#define SCL_L_Del           100
#define SCL_H_Del           100

#define ACK_Del             100

#elif(Sen_IIC_Clk == Sen_IIC_Middle)
#define STR_Del             20
#define STP_Del             20

#define SDA_L_Del           10
#define SDA_H_Del           20

#define SCL_L_Del           10
#define SCL_H_Del           20

#define ACK_Del             20

#elif(Sen_IIC_Clk == Sen_IIC_High)
#define STR_Del             20
#define STP_Del             20

#define SDA_L_Del           4
#define SDA_H_Del           6

#define SCL_L_Del           4
#define SCL_H_Del           6

#define ACK_Del             10
#endif

//Functions define.
#define IIC_SDA0()          {SDA_PORT->BSRR |= (1 << (SDA_PIN_Num + 16));}
#define IIC_SDA1()          {SDA_PORT->BSRR |= (1 << SDA_PIN_Num);}

#define IIC_SCL0()          {SCL_PORT->BSRR |= (1 << (SCL_PIN_Num + 16));}
#define IIC_SCL1()          {SCL_PORT->BSRR |= (1 << SCL_PIN_Num);}

#define SDA_IN_Mode()       {SDA_PORT->MODER &= (uint32_t)( ~(3  << (SDA_PIN_Num << 1)));}
#define SDA_OUT_Mode()      {SDA_PORT->MODER |= (uint32_t)(SDA_PIN_Mode_OUT << (SDA_PIN_Num << 1));}

//Function Define.
#define IIC_SDA_Set(x,y)    {if(x){IIC_SDA1(); SoftDelay(y);} else{IIC_SDA0(); SoftDelay(y);}}
#define IIC_SCL_Set(x,y)    {if(x){IIC_SCL1(); SoftDelay(y);} else{IIC_SCL0(); SoftDelay(y);}}

#define IIC_SDA_Dir_Set(x)  {if(x){SDA_OUT_Mode();} else{SDA_IN_Mode();}}

//#define Read_IIC_SDA()      ((SDA_PORT->IDR & (1 << SDA_PIN_Num)) >> SDA_PIN_Num)
#define Read_IIC_SDA()      ((SDA_PORT->IDR >> SDA_PIN_Num) & 1)

//Delay.
#define SoftDelay(x)        Delay_ns(x)

//ACK typedef.
typedef enum
{
  ACK  = 0,
  NACK = 1,
}IIC_ACK_TypeDef;

/*Global declare.
*/
void IIC_Init(void);
void IICStart(void);
void IICStop(void);

IIC_ACK_TypeDef IICWriteByte(uint8_t dat);
uint8_t IICReadByte(IIC_ACK_TypeDef ack);
uint8_t IICWriteDevice(uint8_t device,
                       uint8_t reg_addr,
                       uint8_t *buf,
                       uint8_t cnt
                      );
uint8_t IICReadDevice(uint8_t device,
                      uint8_t reg_addr,
                      uint8_t *buf,
                      uint8_t cnt
                     );

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

