/*This is the OPAMP functions.
File name :OPAMP.c
All rights reserved,if the code is not authorized by STMicroelectronics.
----by tom.xiao
E-mail:tom.xiao@ST.com
2015-12-17 10:50:28
*/

#include "OPAMP.h"

static void OPAMPx_Cali_NMOS(OPAMP_TypeDef* OPAMPx);
static void OPAMPx_Cali_PMOS(OPAMP_TypeDef* OPAMPx);

/* Init OPAMP1,2,3,4
*/
void OPAMPx_PGA_Init(void)
{
  //OPAMP Peripheral clock enable.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

  //GPIO Init.
  //GPIOA.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_1 |    /* OPAMP1 +     */
                                    GPIO_Pin_2 |    /* OPAMP1 OUT   */
                                    GPIO_Pin_3 |    /* OPAMP1 -     */
                                    GPIO_Pin_4 |    /* DAC0         */
                                    GPIO_Pin_5 |    /* DAC1         */
                                    GPIO_Pin_6 |    /* OPAMP2 OUT   */
                                    GPIO_Pin_7;     /* OPAMP2 + 1   */
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);

  //GPIOB.
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 |    /* OPAMP3 +     */
                                    GPIO_Pin_1 |    /* OPAMP3 OUT   */
                                    GPIO_Pin_2 |    /* OPAMP3 -     */
                                    GPIO_Pin_10|    /* OPAMP4 -     */
                                    GPIO_Pin_11|    /* OPAMP4 +2    */
                                    GPIO_Pin_12|    /* OPAMP4 OUT   */
                                    GPIO_Pin_13|    /* OPAMP4 + 1   */
                                    GPIO_Pin_14;    /* OPAMP2 + 2   */
  GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

  //GPIOC.
  GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_5;     /* OPAMP2 -     */
  GPIO_Init(GPIOC, &GPIO_InitStruct_Temp);

  //Reset OPAMPx.
  OPAMP1->CSR = 0;
  OPAMP2->CSR = 0;
  OPAMP3->CSR = 0;
  OPAMP4->CSR = 0;

  //Reg Enable Operation.
  OPAMP1->CSR |= OPAMP_CSR_OPAMPxEN;
  OPAMP2->CSR |= OPAMP_CSR_OPAMPxEN;
  OPAMP3->CSR |= OPAMP_CSR_OPAMPxEN;
  OPAMP4->CSR |= OPAMP_CSR_OPAMPxEN;

  //Calibration.
  //NMOS.
  OPAMPx_Cali_NMOS(OPAMP1);
  OPAMPx_Cali_NMOS(OPAMP2);
  OPAMPx_Cali_NMOS(OPAMP3);
  OPAMPx_Cali_NMOS(OPAMP4);

  //PMOS.
  OPAMPx_Cali_PMOS(OPAMP1);
  OPAMPx_Cali_PMOS(OPAMP2);
  OPAMPx_Cali_PMOS(OPAMP3);
  OPAMPx_Cali_PMOS(OPAMP4);

  //PGA_Set.
  OPAMP1->CSR |= OPAMP_CSR_PGGAIN_1;
  OPAMP2->CSR |= OPAMP_CSR_PGGAIN_1;
  OPAMP3->CSR |= OPAMP_CSR_PGGAIN_1;
  OPAMP4->CSR |= OPAMP_CSR_PGGAIN_1;    //PGA = 8 Times.

#if 0
  //Set VM & VP + VM2 & VP2 Pins & Enable Timer Mux.
  OPAMP1->CSR |= 0x000001cc;
  OPAMP2->CSR |= 0x000002cc;
  OPAMP3->CSR |= 0x000000cc;
  OPAMP4->CSR |= 0x000006c4;

  //Disable Timer MUX.
  OPAMP1->CSR &= (~0x00000080);
  OPAMP2->CSR &= (~0x00000080);
  OPAMP3->CSR &= (~0x00000080);
  OPAMP4->CSR &= (~0x00000080);
#else

  //Set VM & VP + VM2 & VP2 Pins & Disable Timer Mux.
  OPAMP1->CSR |= 0x0000014c;
  OPAMP2->CSR |= 0x0000024c;
  OPAMP3->CSR |= 0x0000004c;
  OPAMP4->CSR |= 0x00000644;
#endif

  //Lock.
  //OPAMP1->CSR |= OPAMP_CSR_LOCK;
  //OPAMP2->CSR |= OPAMP_CSR_LOCK;
  //OPAMP3->CSR |= OPAMP_CSR_LOCK;
  //OPAMP4->CSR |= OPAMP_CSR_LOCK;
}

/* Init OPAMP1,2,3,4
*/
void OPAMPx_Init(uint32_t OPAMPx)   //OPAMP_Selection_OPAMP1
{
  //Clock Enable.
  //OPAMP Peripheral clock enable.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

  //Set GPIO.
  GPIO_InitTypeDef GPIO_InitStruct_Temp;
  GPIO_InitStruct_Temp.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct_Temp.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct_Temp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct_Temp.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  //OPAMP1--P:PA7 N:PA3 Vout:PA2
  if(OPAMPx == OPAMP_Selection_OPAMP1)
  {
    GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);
  }

  //OPAMP2--P:PB14 N:PC5 Vout:PA6
  if(OPAMPx == OPAMP_Selection_OPAMP2)
  {
    GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);

    GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStruct_Temp);

    GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct_Temp);
  }

  //OPAMP3--P:PB0 N:PB2 Vout:PB1
  if(OPAMPx == OPAMP_Selection_OPAMP3)
  {
    GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);
  }

  //OPAMP4--P:PB11 N:PB10 Vout:PB12
  if(OPAMPx == OPAMP_Selection_OPAMP4)
  {
    GPIO_InitStruct_Temp.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStruct_Temp);
  }

  //Reset OPAMPx.
  OPAMP_DeInit(OPAMPx);

  //OPAMP Calibration.
  //OPAMP_StartCalibration(OPAMPx, ENABLE);

  //Init Struct.
  OPAMP_InitTypeDef OPAMP_InitStruct;

  //OP1
  OPAMP_InitStruct.OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO1;   //PA7  V+
  OPAMP_InitStruct.OPAMP_InvertingInput    = OPAMP_InvertingInput_IO2;      //PA3  V-
  OPAMP_Init(OPAMP_Selection_OPAMP1, &OPAMP_InitStruct);

  //OP2
  OPAMP_InitStruct.OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO2;   //PB14 V+
  OPAMP_InitStruct.OPAMP_InvertingInput    = OPAMP_InvertingInput_IO1;      //PC5  V-
  OPAMP_Init(OPAMP_Selection_OPAMP2, &OPAMP_InitStruct);

  //OP3
  OPAMP_InitStruct.OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO4;   //PB0  V+
  OPAMP_InitStruct.OPAMP_InvertingInput    = OPAMP_InvertingInput_IO2;      //PB2  V-
  OPAMP_Init(OPAMP_Selection_OPAMP3, &OPAMP_InitStruct);

  //OP4
  OPAMP_InitStruct.OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO2;   //PB11 V+
  OPAMP_InitStruct.OPAMP_InvertingInput    = OPAMP_InvertingInput_IO1;      //PB10 V-
  OPAMP_Init(OPAMP_Selection_OPAMP4, &OPAMP_InitStruct);

  //Set PGA.
  //OPAMP_PGAConfig(OPAMP_Selection_OPAMP1, OPAMP_OPAMP_PGAGain_2, OPAMP_PGAConnect_No);
  //OPAMP_PGAConfig(OPAMP_Selection_OPAMP2, OPAMP_OPAMP_PGAGain_2, OPAMP_PGAConnect_No);
  //OPAMP_PGAConfig(OPAMP_Selection_OPAMP3, OPAMP_OPAMP_PGAGain_2, OPAMP_PGAConnect_No);
  //OPAMP_PGAConfig(OPAMP_Selection_OPAMP4, OPAMP_OPAMP_PGAGain_2, OPAMP_PGAConnect_No);

  //Set Vref.
  //OPAMP_VrefConfig(OPAMP_Selection_OPAMP1, OPAMP_Vref_3VDDA);
  //OPAMP_VrefConnectADCCmd(OPAMP_Selection_OPAMP1, ENABLE);
  //OPAMP_VrefConnectNonInvertingInput(OPAMP_Selection_OPAMP1, ENABLE);

  //OPAMP_VrefConfig(OPAMP_Selection_OPAMP2, OPAMP_Vref_3VDDA);
  //OPAMP_VrefConnectADCCmd(OPAMP_Selection_OPAMP2, ENABLE);
  //OPAMP_VrefConnectNonInvertingInput(OPAMP_Selection_OPAMP2, ENABLE);

  //OPAMP_VrefConfig(OPAMP_Selection_OPAMP3, OPAMP_Vref_3VDDA);
  //OPAMP_VrefConnectADCCmd(OPAMP_Selection_OPAMP3, ENABLE);
  //OPAMP_VrefConnectNonInvertingInput(OPAMP_Selection_OPAMP3, ENABLE);

  //OPAMP_VrefConfig(OPAMP_Selection_OPAMP4, OPAMP_Vref_3VDDA);
  //OPAMP_VrefConnectADCCmd(OPAMP_Selection_OPAMP4, ENABLE);
  //OPAMP_VrefConnectNonInvertingInput(OPAMP_Selection_OPAMP4, ENABLE);

  //Set Timer Connect.
  //OPAMP_TimerControlledMuxConfig(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct);
  //OPAMP_TimerControlledMuxCmd(uint32_t OPAMP_Selection, FunctionalState NewState);

  //Set Offset.
  //OPAMP_OffsetTrimModeSelect(uint32_t OPAMP_Selection, uint32_t OPAMP_Trimming);
  //OPAMP_OffsetTrimConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);

  //Enable OPAMPx.
  OPAMP_Cmd(OPAMPx, ENABLE);

  //Lock Config.
  OPAMP_LockConfig(OPAMPx);
}

//OPAMP NMOS Calibration.
static void OPAMPx_Cali_NMOS(OPAMP_TypeDef* OPAMPx)
{
  //Reg Enable Operation.
  OPAMPx->CSR |= OPAMP_CSR_OPAMPxEN;

  //Calibration.
  //NMOS.
  OPAMPx->CSR |= OPAMP_CSR_USERTRIM;    //Enable UserTrim.
  OPAMPx->CSR |= OPAMP_CSR_CALON;       //CAL ON.
  OPAMPx->CSR |= OPAMP_CSR_CALSEL;      //90% VDDA.

  //OPAMPx Cal.
  uint8_t i = 0;
  while(i < 32)
  {
    OPAMPx->CSR |= (i << 24);
    i++;

    if((OPAMPx->CSR & OPAMP_CSR_OUTCAL) == 0)
    {
      break;
    }
  }

  //Disable
  OPAMPx->CSR &= (uint32_t)(~OPAMP_CSR_USERTRIM);    //Disable UserTrim.
  OPAMPx->CSR &= (uint32_t)(~OPAMP_CSR_CALON);       //CAL OFF.
}

//OPAMP PMOS Calibration.
static void OPAMPx_Cali_PMOS(OPAMP_TypeDef* OPAMPx)
{
  //Reg Enable Operation.
  OPAMPx->CSR |= OPAMP_CSR_OPAMPxEN;

  //Calibration.
  //NMOS.
  OPAMPx->CSR |= OPAMP_CSR_USERTRIM;    //Enable UserTrim.
  OPAMPx->CSR |= OPAMP_CSR_CALON;       //CAL ON.
  OPAMPx->CSR |= OPAMP_CSR_CALSEL_0;    //10% VDDA.

  //OPAMPx Cal.
  uint8_t i = 0;
  while(i < 32)
  {
    OPAMPx->CSR |= (i << 19);
    i++;

    if((OPAMPx->CSR & OPAMP_CSR_OUTCAL) == 0)
    {
      break;
    }
  }

  //Disable
  OPAMPx->CSR &= (uint32_t)(~OPAMP_CSR_USERTRIM);    //Disable UserTrim.
  OPAMPx->CSR &= (uint32_t)(~OPAMP_CSR_CALON);       //CAL OFF.
}

//OPAMP12 Switch Function.
void OPAMP12_Switch(OPAMP_SWITCH_TypeDef Temp)
{
  //Clean.
  OPAMP1->CSR &= 0xfffffff3;                // ----- PA1 ---|---- U
  OPAMP2->CSR &= 0xfffffff3;                // ----- PA7 ---|---- V Public
  // ----- PB14---|---- W
  switch(Temp)
  {
  case OPAMP_UV:
    OPAMP1->CSR |= 0x0c;    //PA1
    OPAMP2->CSR |= 0x0c;    //PA7
    break;

  case OPAMP_UW:
    OPAMP1->CSR |= 0x0c;    //PA1
    OPAMP2->CSR |= 0x04;    //PB14
    break;

  case OPAMP_VW:
    OPAMP1->CSR |= 0x00;    //PA7
    OPAMP2->CSR |= 0x04;    //PB14
    break;
  }
}

#if 0
//OPAMP34 Switch Function.
void OPAMP34_Switch(OPAMP_SWITCH_TypeDef Temp)
{
  //Clean.
  OPAMP3->CSR &= 0xfffffff3;                // ----- PB0 ---|---- U
  OPAMP4->CSR &= 0xfffffff3;                // ----- PB13---|---- V Public
  // ----- PB11---|---- W
  switch(Temp)
  {
  case OPAMP_UV:
    OPAMP3->CSR |= 0x0c;    //PB0
    OPAMP4->CSR |= 0x0c;    //PB13
    break;

  case OPAMP_UW:
    OPAMP3->CSR |= 0x0c;    //PB0
    OPAMP4->CSR |= 0x04;    //PB11
    break;

  case OPAMP_VW:
    OPAMP3->CSR |= 0x00;    //PB13
    OPAMP4->CSR |= 0x04;    //PB11
    break;
  }
}

#else
//OPAMP34 Switch Function.
void OPAMP34_Switch(OPAMP_SWITCH_TypeDef Temp)
{
  //Clean.
  OPAMP3->CSR &= 0xfffffff3;                // ----- PB0 ---|---- U
  OPAMP4->CSR &= 0xfffffff3;                // ----- PB13---|---- W Public
  // ----- PB11---|---- W
  switch(Temp)
  {
  case OPAMP_UW:
    OPAMP3->CSR |= 0x0c;    //PB0
    OPAMP4->CSR |= 0x0c;    //PB13
    break;

  case OPAMP_UV:
    OPAMP3->CSR |= 0x0c;    //PB0
    OPAMP4->CSR |= 0x04;    //PB11
    break;

  case OPAMP_VW:
    OPAMP3->CSR |= 0x00;    //PB13
    OPAMP4->CSR |= 0x04;    //PB11
    break;
  }
}
#endif

/********** End of file *********** Copy Right Reserved by STMicroelectronics ***********/

