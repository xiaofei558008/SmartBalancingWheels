/*This is the debug set document.
File name :debug_gpio.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@STMicroelectronics.com
2013-7-04 15:13:28
*/
#include "debug_gpio.h"

/* init the debug pin
*/
void Debug_GPIO_Pins_Init(bool debug_gpio_0,
                          bool debug_gpio_1,
                          bool debug_gpio_2,
                          bool debug_gpio_3,
                          bool debug_gpio_4,
                          bool debug_gpio_5,
                          bool debug_gpio_6,
                          bool debug_gpio_7
                         )
{
#if defined(DEBUG_MCU)

// Setup GPIO.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin      = debug_pin_0;
  GPIO_InitStruct_Temp.GPIO_Mode     = GPIO_Mode_OUT;
  GPIO_InitStruct_Temp.GPIO_Speed    = GPIO_Speed_2MHz;
  GPIO_InitStruct_Temp.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd     = GPIO_PuPd_NOPULL;

// Debug pins config.
  if(debug_gpio_0)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    GPIO_SetBits(debug_port_0, debug_pin_0);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_0;
    GPIO_Init(debug_port_0, &GPIO_InitStruct_Temp);
  }

  if(debug_gpio_1)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);

    GPIO_SetBits(debug_port_1, debug_pin_1);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_1;
    GPIO_Init(debug_port_1, &GPIO_InitStruct_Temp);
  }

  if(debug_gpio_2)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF,ENABLE);

    GPIO_SetBits(debug_port_2, debug_pin_2);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_2;
    GPIO_Init(debug_port_2, &GPIO_InitStruct_Temp);
  }

  if(debug_gpio_3)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

    GPIO_SetBits(debug_port_3, debug_pin_3);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_3;
    GPIO_Init(debug_port_3, &GPIO_InitStruct_Temp);
  }

  if(debug_gpio_4)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

    GPIO_SetBits(debug_port_4, debug_pin_4);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_4;
    GPIO_Init(debug_port_4, &GPIO_InitStruct_Temp);
  }


  if(debug_gpio_5)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

    GPIO_SetBits(debug_port_5, debug_pin_5);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_5;
    GPIO_Init(debug_port_5, &GPIO_InitStruct_Temp);
  }

  if(debug_gpio_6)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

    GPIO_SetBits(debug_port_6, debug_pin_6);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_6;
    GPIO_Init(debug_port_6, &GPIO_InitStruct_Temp);
  }

  if(debug_gpio_7)
  {
    // Enable GPIO Clock.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

    GPIO_SetBits(debug_port_7, debug_pin_7);
    GPIO_InitStruct_Temp.GPIO_Pin = debug_pin_7;
    GPIO_Init(debug_port_7, &GPIO_InitStruct_Temp);
  }

#else
  (void) debug_gpio_0;
  (void) debug_gpio_1;
  (void) debug_gpio_2;
  (void) debug_gpio_3;
  (void) debug_gpio_4;
  (void) debug_gpio_5;
  (void) debug_gpio_6;
  (void) debug_gpio_7;
#endif
}

/* IO toggle function.
*/
void Debug_GPIO_Toggle(uint8_t debug_gpio_pin_num)
{
#if defined (DEBUG_MCU)
  switch(debug_gpio_pin_num)
  {
  case 0:
    GPIO_ToggleBits(debug_port_0, debug_pin_0);
    break;
  case 1:
    GPIO_ToggleBits(debug_port_1, debug_pin_1);
    break;
  case 2:
    GPIO_ToggleBits(debug_port_2, debug_pin_2);
    break;
  case 3:
    GPIO_ToggleBits(debug_port_3, debug_pin_3);
    break;
  case 4:
    GPIO_ToggleBits(debug_port_4, debug_pin_4);
    break;
  case 5:
    GPIO_ToggleBits(debug_port_5, debug_pin_5);
    break;
  case 6:
    GPIO_ToggleBits(debug_port_6, debug_pin_6);
    break;
  case 7:
    GPIO_ToggleBits(debug_port_7, debug_pin_7);
    break;
  }
#else
  (void) debug_gpio_pin_num;
#endif
}

//Toggle a GPIO.
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x)
{
  GPIOx->ODR ^= GPIO_Pin_x;
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/
