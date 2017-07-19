/*This is type define which is used in matrix keyboard.c.
File name: Matrix_Keyboard_CallBack.h
All rights reserved,if the code is not authorized by STMicroelectronic.
2017-04-19 16:13:12 Tom.xiao@st.com
*/

#ifndef __MATRIX_KEY_BOARD_CALLBACK
#define __MATRIX_KEY_BOARD_CALLBACK

#include "Matrix_Keyboard.h"

//Global Declare.
void Key_Union_CallBack(Matrix_Keyboard_TypeDef* key);
void Key_Trigger_CallBack(Matrix_Keyboard_TypeDef* key);
void Key_PressDown_CallBack(Matrix_Keyboard_TypeDef* key);
void Key_Release_CallBack(Matrix_Keyboard_TypeDef* key);

#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

