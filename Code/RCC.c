/*This is the RCC functions.
File name :RCC.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-01-15 10:50:28
*/

#include "RCC.h"

//Global Variable.
RCC_ClocksTypeDef RCC_Clocks;

/* RCC Init Function.
*/
void RCC_Init(void)
{
  //Reset All Clock Set.
  RCC_DeInit();

  //HSE Enabled.
  RCC_HSEConfig(RCC_HSE_ON);

  //Waiting for HSE Ready.
  while(RCC_WaitForHSEStartUp() == ERROR);

  //Enable Clock Security.
  RCC_ClockSecuritySystemCmd(ENABLE);

  //Set HSE PreDiv.
  RCC_PREDIV1Config(RCC_PREDIV1_Div1);

  //Enable HSI.
  RCC_HSICmd(ENABLE);

  //Set Cal-HSI.
  //RCC_AdjustHSICalibrationValue(0x00);

  //Set SysClock Source From HSI.
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

  //Get All Sys Clocks.
  RCC_GetClocksFreq(&RCC_Clocks);

  //Set AHB / HCLK Prescaler.    -- Max 72M
  RCC_HCLKConfig(RCC_SYSCLK_Div1);

  //Set APB1 / PCLK1 Prescaler.  -- Max 36M
  RCC_PCLK1Config(RCC_HCLK_Div2);

  //Set APB2 / PCLK2 Prescaler.  -- Max 72M
  RCC_PCLK2Config(RCC_HCLK_Div1);

  //Set ADC12 Div.
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);

  //Set ADC34 Div.
  RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div1);

  //Waiting For HSE Stable.
  while(RCC_WaitForHSEStartUp() == ERROR);

  //LSE Set.
  RCC_LSEConfig(RCC_LSE_OFF);

  //Set LSE Drive.
  //RCC_LSEDriveConfig(RCC_LSEDrive_MediumLow);

  //Set LSI.
  RCC_LSICmd(DISABLE);

  //PLL Disable.
  RCC_PLLCmd(DISABLE);

  //Set PLL 8M / 1 * 9 = 72MHz.
  RCC_PREDIV1Config(RCC_PREDIV1_Div1);
  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);

  //PLL Enable.
  RCC_PLLCmd(ENABLE);

  //Set Flash Latency.
  FLASH_SetLatency(FLASH_Latency_2);

  //Waiting PLL Ready(Locked).
  while((RCC->CR & (1 << 25)) == 0);

  //Set SysClock Source.
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  //Set MCO ClockSource.
  //RCC_MCOConfig(RCC_MCOSource_NoClock);

  //Set IIC123 Clock Source.
  //RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);
  //RCC_I2CCLKConfig(RCC_I2C2CLK_SYSCLK);
  //RCC_I2CCLKConfig(RCC_I2C3CLK_SYSCLK);

  //Set Timers Clock Source.
  RCC_TIMCLKConfig(RCC_TIM1CLK_PLLCLK); //Timer1.
  RCC_TIMCLKConfig(RCC_TIM8CLK_PLLCLK); //Timer8.

  //Set HRTIM1 Clock Source.
  RCC_HRTIM1CLKConfig(RCC_HRTIM1CLK_PLLCLK);

  //Set IIS Clock.
  RCC_I2SCLKConfig(RCC_I2S2CLKSource_SYSCLK);

  //Set USARTs Clock.
  RCC_USARTCLKConfig(RCC_USART1CLK_PCLK);

  //Set USB Clock.
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);

  //Set RTC Clock.
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  //Enable / Disable RTC Clock.
  RCC_RTCCLKCmd(DISABLE);

  //Backup & Reset Enable / Disable.
  RCC_BackupResetCmd(DISABLE);

  //Set AHB Enable.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_TS,    ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,   ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FMC,   ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FLITF, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);

  //Set APB2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,   ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4,   ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15,  ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16,  ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17,  ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,   ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,   ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_HRTIM1, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM20,  ENABLE);

  //Set APB1
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,  ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,  ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,  ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,  ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,  ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB,   ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,   ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC2,  ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3,  ENABLE);

  //Clear IRQ Flags.
  RCC_ClearITPendingBit(  RCC_IT_LSIRDY
                          | RCC_IT_LSERDY
                          | RCC_IT_HSIRDY
                          | RCC_IT_HSERDY
                          | RCC_IT_PLLRDY
                          | RCC_IT_CSS
                       );

  //Clear RCC Reset Flags.
  RCC_ClearFlag();

  //Set NVIC
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = RCC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //Set IRQs.
  RCC_ITConfig(RCC_IT_LSIRDY,DISABLE);
  RCC_ITConfig(RCC_IT_LSERDY,DISABLE);
  RCC_ITConfig(RCC_IT_HSIRDY,DISABLE);
  RCC_ITConfig(RCC_IT_HSERDY,DISABLE);
  RCC_ITConfig(RCC_IT_PLLRDY,DISABLE);

  //Get Status Flags.
  //FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);

  //Get IRQ Flags.
  //ITStatus RCC_GetITStatus(uint8_t RCC_IT);

  //Get All Sys Clocks.
  RCC_GetClocksFreq(&RCC_Clocks);
}


/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

