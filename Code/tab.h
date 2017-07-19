/*This is the tab functions' head.
File name :tab.h
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 11:13:28
*/

#ifndef __TAB_H
#define __TAB_H

#include <stdint.h>
#include <stddef.h>

//defines
#define Quarter_Sin_Point_Num           2048

#define Degree_0                        0
#define Degree_30                       683
#define Degree_60                       1366
#define Degree_90                       2048
#define Degree_120                      2731
#define Degree_150                      3414
#define Degree_180                      4096
#define Degree_210                      4779
#define Degree_240                      5462
#define Degree_270                      6144
#define Degree_300                      6827
#define Degree_330                      7510
#define Degree_360                      8192

//Sin Const Data Q15 Define.
#define Const1_Q15                      32768       //const 1

#define Sqrt3_Q15                       56756       //sqrt(3)
#define Sin30_Q15                       16384       //sin30бу
#define Sin60_Q15                       28378       //sin60бу
#define Sin90_Q15                       Const1_Q15  //sin90бу
#define Sin120_Q15                      Sin60_Q15   //sin120бу

//Sin Const Data Q16 Define.
#define Sin30_Q16                       32768       //sin30бу
#define Sin60_Q16                       56755       //sin60бу
#define Sqrt3_Q16                       113512      //sqrt(3)
#define Const1_Q16                      65536       //const 1

//glable variables declare.
extern uint16_t Sin_90_Q15_Tab[Quarter_Sin_Point_Num];

//functions declare.
/*__ramfunc*/ int32_t Sin_Cal_Q15(int32_t angle_Q13);
/*__ramfunc*/ int32_t Cos_Cal_Q15(int32_t angle_Q13);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

