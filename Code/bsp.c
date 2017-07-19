/*This is the bsp functions.
File name :bsp.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2014-12-11 10:50:28
*/

#include "bsp.h"

//init bsp in mcu.
void Bsp_Init(void)
{
  //Setup System Clock -- 72MHz.
  RCC_Init();

  //Init Debug GPIO.
  Debug_GPIO_Pins_Init(true,     //bool debug_gpio_0,
                       true,     //bool debug_gpio_1,
                       true,     //bool debug_gpio_2,
                       false,    //bool debug_gpio_3,
                       false,    //bool debug_gpio_4,
                       false,    //bool debug_gpio_5,
                       false,    //bool debug_gpio_6,
                       false     //bool debug_gpio_7
                      );

  //Set systick as 1ms period.
  //while(SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000));

  //Setup ADC Module.
  ADC_Inject_OPAMP_Init();

  //Set OPAMP.
  OPAMPx_PGA_Init();

  //ACMP Init.
#if 1
  ACMPs_Init();
#endif

  //Setup PWM Module -- TIM1 & TIM8.
  PWM_Init_180(16000);

  //Setup DAC1.
  DAC1_Init();

  //init timer2 as free run counter for AHRS.
  Timer2_Base_Counter_Init();

  //innit timer6 as 10ms(100Hz) tick for keys & Battery management.
  Timer6_Base_Counter_Init();

  //init SPI.
  ////////////////////////////////////////
  //SPI2_Init();

  //init UART.
  ////////////////////////////////////////
  ////USART3_Init(115200);

  //init IIC.

  //init window watchdog.
  ////////////////////////////////////////

  //init watchdog.
  ////////////////////////////////////////
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

