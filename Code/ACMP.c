/*This is the ACMP functions.
File name :ACMP.c
All rights reserved,if the code is not authorized by STMicroelectronics.
2017-04-28 9:51:29 Tom.xiao@st.com
*/

#include "ACMP.h"

void ACMPs_Init(void)
{
  //Enable Clocks.
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  //Reset ACMPs.
  COMP1->CSR = 0x00000000;
  COMP2->CSR = 0x00000000;
  COMP3->CSR = 0x00000000;
  COMP4->CSR = 0x00000000;

  COMP5->CSR = 0x00000000;
  COMP6->CSR = 0x00000000;
  COMP7->CSR = 0x00000000;

  //Init ACMP.
  /*
  IO1              IO2
  PA1  for COMP1,
  PA7  for COMP2,  PA3  for COMP2,
  PB14 for COMP3,  PD14 for COMP3,
  PB0  for COMP4,  PE7  for COMP4,
  PD12 for COMP5,  PB13 for COMP5,
  PD11 for COMP6,  PB11 for COMP6,
  PA0  for COMP7   PC1  for COMP7
  */

  //PA1       ACMP1
  //PA7       ACMP2
  //PB14      ACMP3
  //PB0       ACMP4
  //PA0       ACMP7

  //PB13      ACMP5
  //PB11      ACMP6

  //GPIO Init.
  //Port A0/A1/A7.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //Port B0/B11/B13/B14.
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //ACMP Init.
  COMP_InitTypeDef Temp;
  Temp.COMP_InvertingInput    = COMP_InvertingInput_3_4VREFINT; ////COMP_InvertingInput_1_2VREFINT;               //+ VREFINT = 1.16-1.25V.
  Temp.COMP_NonInvertingInput = COMP_NonInvertingInput_IO1;                   //-
  Temp.COMP_Output            = COMP_Output_TIM1BKIN2;              //TIM1 & TIM8 Break2.
  Temp.COMP_BlankingSrce      = COMP_BlankingSrce_TIM1OC5;                    //Set Blanking Source.
  Temp.COMP_OutputPol         = COMP_OutputPol_NonInverted;
  Temp.COMP_Hysteresis        = COMP_Hysteresis_Low;
  Temp.COMP_Mode              = COMP_Mode_HighSpeed;

  //Init ACMPs.
  //Motor A TIM1
  COMP_Init(COMP_Selection_COMP1, &Temp);   //PA1       ACMP1
  COMP_Init(COMP_Selection_COMP2, &Temp);   //PA7       ACMP2
  COMP_Init(COMP_Selection_COMP3, &Temp);   //PB14      ACMP3

  //Motor B TIM8
  Temp.COMP_Output            = COMP_Output_TIM8BKIN2;              //TIM1 & TIM8 Break2.
  COMP_Init(COMP_Selection_COMP4, &Temp);   //PB0       ACMP4
  Temp.COMP_NonInvertingInput = COMP_NonInvertingInput_IO2;
  COMP_Init(COMP_Selection_COMP5, &Temp);   //PB13      ACMP5
  COMP_Init(COMP_Selection_COMP6, &Temp);   //PB11      ACMP6

  ////COMP_Init(COMP_Selection_COMP7, &Temp);   //PA0       ACMP7

  //Disconnect from DAC to ACMP1.
  COMP1->CSR &= (~COMP_CSR_COMP1SW1);

  //Enable ACMPs.
  COMP1->CSR |= COMP_CSR_COMPxEN;
  COMP2->CSR |= COMP_CSR_COMPxEN;
  COMP3->CSR |= COMP_CSR_COMPxEN;
  COMP4->CSR |= COMP_CSR_COMPxEN;
  COMP5->CSR |= COMP_CSR_COMPxEN;
  COMP6->CSR |= COMP_CSR_COMPxEN;
  COMP7->CSR |= COMP_CSR_COMPxEN;

  //Lock ACMPs.
  COMP1->CSR |= COMP_CSR_COMPxLOCK;
  COMP2->CSR |= COMP_CSR_COMPxLOCK;
  COMP3->CSR |= COMP_CSR_COMPxLOCK;
  COMP4->CSR |= COMP_CSR_COMPxLOCK;
  COMP5->CSR |= COMP_CSR_COMPxLOCK;
  COMP6->CSR |= COMP_CSR_COMPxLOCK;
  COMP7->CSR |= COMP_CSR_COMPxLOCK;
}

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

