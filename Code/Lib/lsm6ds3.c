/**
******************************************************************************
* @file    lsm6ds3.c
* @author  MEMS Application Team
* @version V1.2.0
* @date    28-January-2015
* @brief   This file provides a set of functions needed to manage the LSM6DS3 sensor
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "lsm6ds3.h"
#include <math.h>
#include "stm32f30x.h"
#include "IIC_Software.h"
//#include "stm32f3xx_hal.h"

/** @addtogroup BSP
* @{
*/

/** @addtogroup Components
* @{
*/

/** @addtogroup LSM6DS3
* @{
*/

IMU_6AXES_StatusTypeDef LSM6DS3_Init(uint8_t DeviceAddr, IMU_6AXES_InitTypeDef *LSM6DS3_Init);
IMU_6AXES_StatusTypeDef LSM6DS3_Read_XG_ID(uint8_t DeviceAddr, uint8_t *xg_id);

IMU_6AXES_StatusTypeDef LSM6DS3_X_GetAxesRaw(uint8_t DeviceAddr, int16_t *pData);
IMU_6AXES_StatusTypeDef LSM6DS3_G_GetAxesRaw(uint8_t DeviceAddr, int16_t *pData);

IMU_6AXES_StatusTypeDef LSM6DS3_GetAxesRaw(uint8_t DeviceAddr, int16_t *pData);

IMU_6AXES_StatusTypeDef LSM6DS3_X_GetAxes(uint8_t DeviceAddr, int32_t *pData);
IMU_6AXES_StatusTypeDef LSM6DS3_G_GetAxes(uint8_t DeviceAddr, int32_t *pData);
IMU_6AXES_StatusTypeDef LSM6DS3_GetAxes(uint8_t DeviceAddr, int32_t *pData);
IMU_6AXES_StatusTypeDef LSM6DS3_GetAxes_Fast(uint8_t DeviceAddr, int16_t *pData);

IMU_6AXES_StatusTypeDef LSM6DS3_X_GetSensitivity(uint8_t DeviceAddr, float *pfData);
IMU_6AXES_StatusTypeDef LSM6DS3_G_GetSensitivity(uint8_t DeviceAddr, float *pfData);
IMU_6AXES_StatusTypeDef LSM6DS3_Enable_Free_Fall_Detection(uint8_t DeviceAddr);
IMU_6AXES_StatusTypeDef LSM6DS3_Disable_Free_Fall_Detection(uint8_t DeviceAddr);
IMU_6AXES_StatusTypeDef LSM6DS3_Get_Status_Free_Fall_Detection(uint8_t DeviceAddr, uint8_t *status);

/** @addtogroup LSM6DS3_Private_Variables LSM6DS3_Private_Variables
* @{
*/
IMU_6AXES_DrvTypeDef LSM6DS3Drv =
{
  LSM6DS3_Init,
  LSM6DS3_Read_XG_ID,
  LSM6DS3_X_GetAxes,
  LSM6DS3_G_GetAxes,
  LSM6DS3_GetAxes,
  LSM6DS3_GetAxesRaw,  //LSM6DS3_GetAxes_Fast,
  LSM6DS3_X_GetSensitivity,
  LSM6DS3_G_GetSensitivity,
  NULL
};

/**
* @}
*/


/** @addtogroup LSM6DS3_Private_Functions LSM6DS3_Private_Functions
* @{
*/

/**
* @brief  Set LSM6DS3 Initialization
* @param  LSM6DS3_Init the configuration setting for the LSM6DS3
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_Init(uint8_t DeviceAddr, IMU_6AXES_InitTypeDef *LSM6DS3_Init)
{
  /*Here we have to add the check if the parameters are valid*/
  uint8_t tmp1 = 0x00;

  /* Configure the low level interface -------------------------------------*/
  if(LSM6DS3_IO_Init() != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }


  /******** Common init *********/

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL3_C, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Enable register address automatically incremented during a multiple byte
  access with a serial interface (I2C or SPI) */
  tmp1 &= ~(LSM6DS3_XG_IF_INC_MASK);
  tmp1 |= LSM6DS3_XG_IF_INC;

  tmp1 &= ~(LSM6DS3_XG_BDU_MASK);
  tmp1 |= LSM6DS3_XG_BDU_ENABLE;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL3_C, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }


  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_FIFO_CTRL5, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* FIFO ODR selection */
  tmp1 &= ~(LSM6DS3_XG_FIFO_ODR_MASK);
  tmp1 |= LSM6DS3_XG_FIFO_ODR_NA;

  /* FIFO mode selection */
  tmp1 &= ~(LSM6DS3_XG_FIFO_MODE_MASK);
  tmp1 |= LSM6DS3_XG_FIFO_MODE_BYPASS;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_FIFO_CTRL5, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }


  /******* Gyroscope init *******/

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL2_G, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Output Data Rate selection */
  tmp1 &= ~(LSM6DS3_G_ODR_MASK);
  tmp1 |= LSM6DS3_Init->G_OutputDataRate; //833

  /* Full scale selection */
  tmp1 &= ~(LSM6DS3_G_FS_MASK);
  tmp1 |= LSM6DS3_Init->G_FullScale;      //2000

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL2_G, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }


  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL10_C, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Enable X axis selection */
  tmp1 &= ~(LSM6DS3_G_XEN_MASK);
  tmp1 |= LSM6DS3_Init->G_X_Axis;

  /* Enable Y axis selection */
  tmp1 &= ~(LSM6DS3_G_YEN_MASK);
  tmp1 |= LSM6DS3_Init->G_Y_Axis;

  /* Enable Z axis selection */
  tmp1 &= ~(LSM6DS3_G_ZEN_MASK);
  tmp1 |= LSM6DS3_Init->G_Z_Axis;

  // User added config
  // Enable embeded function
  tmp1 &= ~(LSM6DS3_XL_FUNC_EN_MASK);
  tmp1 |= LSM6DS3_XL_FUNC_EN_MASK;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL10_C, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }


  /***** Accelerometer init *****/

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Output Data Rate selection */
  tmp1 &= ~(LSM6DS3_XL_ODR_MASK);
  tmp1 |= LSM6DS3_Init->X_OutputDataRate;

  /* Full scale selection */
  tmp1 &= ~(LSM6DS3_XL_FS_MASK);
  tmp1 |= LSM6DS3_Init->X_FullScale;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }


  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL9_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Enable X axis selection */
  tmp1 &= ~(LSM6DS3_XL_XEN_MASK);
  tmp1 |= LSM6DS3_Init->X_X_Axis;

  /* Enable Y axis selection */
  tmp1 &= ~(LSM6DS3_XL_YEN_MASK);
  tmp1 |= LSM6DS3_Init->X_Y_Axis;

  /* Enable Z axis selection */
  tmp1 &= ~(LSM6DS3_XL_ZEN_MASK);
  tmp1 |= LSM6DS3_Init->X_Z_Axis;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL9_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Configure interrupt lines */
  LSM6DS3_IO_ITConfig();

  /*****************************
  *  User Configuration.
  */

  // User defined initialization
  // 1. Enable Gyro high pass filter
  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL7_G, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  // enable hpf for gyro
  tmp1 &= ~(LSM6DS3_XG_HP_G_EN_MASK);
  tmp1 |= LSM6DS3_XG_HP_G_EN_DISABLE;

  tmp1 &= ~(LSM6DS3_XG_HPCF_MASK);
  tmp1 |= LSM6DS3_XG_HPCF_0_DOT_0324;

  tmp1 &= ~(LSM6DS3_XG_HP_G_RST_MASK);
  tmp1 |= LSM6DS3_XG_HP_G_RST_ENABLE;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL7_G, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  // 2. Enable Accelerometer LPF
  //    if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_TAP_CFG, 1) != IMU_6AXES_OK)
  //    {
  //      return IMU_6AXES_ERROR;
  //    }
  //
  //    tmp1 &= ~(LSM6DS3_XG_SLOPE_FDS_MASK);
  //    tmp1 |= LSM6DS3_XG_SLOPE_FDS_ENABLE;
  //
  //    if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_TAP_CFG, 1) != IMU_6AXES_OK)
  //    {
  //      return IMU_6AXES_ERROR;
  //    }

  // enable lpf for acc
  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL8_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  tmp1 &= ~(LSM6DS3_XG_LPF2_XL_EN_MASK);
  tmp1 |= LSM6DS3_XG_LPF2_XL_EN_ENABLE;

  tmp1 &= ~(LSM6DS3_XG_HP_SLOPE_XL_EN_MASK);
  tmp1 |= LSM6DS3_XG_HP_SLOPE_XL_ENABLE;

  // Set LPF frequency to ODR/400
  tmp1 &= ~(LSM6DS3_XG_LPF2_FC_MASK);
  tmp1 |= LSM6DS3_XG_LPF2_ODR_DIV_100;   // /9

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL8_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL4_C, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  // enable anti-alias bandwidth determined by setting BW_XL[1:0]
  tmp1 &= ~(LSM6DS3_XL_BW_SCAL_ODR_MASK);
  tmp1 |= LSM6DS3_XL_BW_SCAL_ODR;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL4_C, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  // BW_XL[1:0] : Set Acc anti-alias filter to 50Hz
  tmp1 &= ~(LSM6DS3_BW_XL1_ANTIALIAS_MASK);
  tmp1 |= LSM6DS3_BW_XL1_ANTIALIAS_100HZ;
  //tmp1 |= LSM6DS3_BW_XL1_ANTIALIAS_400HZ;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  return IMU_6AXES_OK;
}

/**
* @brief  Read ID of LSM6DS3 Accelerometer and Gyroscope
* @param  xg_id the pointer where the ID of the device is stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_Read_XG_ID(uint8_t DeviceAddr, uint8_t *xg_id)
{
  if(!xg_id)
  {
    return IMU_6AXES_ERROR;
  }

  return LSM6DS3_IO_Read(xg_id, DeviceAddr, LSM6DS3_XG_WHO_AM_I_ADDR, 1);
}



/**
* @brief  Read raw data from LSM6DS3 Accelerometer output register
* @param  pData the pointer where the accelerometer raw data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_X_GetAxesRaw(uint8_t DeviceAddr, int16_t *pData)
{
  /*Here we have to add the check if the parameters are valid*/

  uint8_t tempReg[6];

  if(LSM6DS3_IO_Read(&tempReg[0], DeviceAddr, LSM6DS3_XG_OUT_X_L_XL, 6) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  pData[0] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);
  pData[1] = ((((int16_t)tempReg[3]) << 8)+(int16_t)tempReg[2]);
  pData[2] = ((((int16_t)tempReg[5]) << 8)+(int16_t)tempReg[4]);

  return IMU_6AXES_OK;
}

/**
* @brief  Read data from LSM6DS3 Accelerometer and calculate linear acceleration in mg
* @param  pData the pointer where the accelerometer data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_X_GetAxes(uint8_t DeviceAddr, int32_t *pData)
{
  /*Here we have to add the check if the parameters are valid*/

  uint8_t tempReg = 0x00;
  int16_t pDataRaw[3];
  float sensitivity = 0;

  if(LSM6DS3_X_GetAxesRaw(DeviceAddr, pDataRaw) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tempReg, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  tempReg &= LSM6DS3_XL_FS_MASK;

  switch(tempReg)
  {
    case LSM6DS3_XL_FS_2G:
    sensitivity = 0.06103515625;
    break;
    case LSM6DS3_XL_FS_4G:
    sensitivity = 0.1220703125;
    break;
    case LSM6DS3_XL_FS_8G:
    sensitivity = 0.244140625;
    break;
    case LSM6DS3_XL_FS_16G:
    sensitivity = 0.48828125;
    break;
  }
  pData[0] = (int32_t)(pDataRaw[0] * sensitivity);
  pData[1] = (int32_t)(pDataRaw[1] * sensitivity);
  pData[2] = (int32_t)(pDataRaw[2] * sensitivity);

  return IMU_6AXES_OK;
}



/**
* @brief  Read raw data from LSM6DS3 Gyroscope output register
* @param  pData the pointer where the gyroscope raw data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_G_GetAxesRaw(uint8_t DeviceAddr, int16_t *pData)
{
  /*Here we have to add the check if the parameters are valid*/

  uint8_t tempReg[6];

  if(LSM6DS3_IO_Read(&tempReg[0], DeviceAddr, LSM6DS3_XG_OUT_X_L_G, 6) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  pData[0] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);
  pData[1] = ((((int16_t)tempReg[3]) << 8)+(int16_t)tempReg[2]);
  pData[2] = ((((int16_t)tempReg[5]) << 8)+(int16_t)tempReg[4]);

  return IMU_6AXES_OK;
}

/**
* @brief  Read data from LSM6DS3 Gyroscope and calculate angular rate in mdps
* @param  pData the pointer where the gyroscope data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_G_GetAxes(uint8_t DeviceAddr, int32_t *pData)
{
  /*Here we have to add the check if the parameters are valid*/

  uint8_t tempReg = 0x00;
  int16_t pDataRaw[3];
  float sensitivity = 0;

  if(LSM6DS3_G_GetAxesRaw(DeviceAddr, pDataRaw) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tempReg, DeviceAddr, LSM6DS3_XG_CTRL2_G, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  tempReg &= LSM6DS3_G_FS_MASK;

  switch(tempReg)
  {
    case LSM6DS3_G_FS_125:
    sensitivity = 4.375;
    break;
    case LSM6DS3_G_FS_245:
    sensitivity = 8.75;
    break;
    case LSM6DS3_G_FS_500:
    sensitivity = 17.50;
    break;
    case LSM6DS3_G_FS_1000:
    sensitivity = 35;
    break;
    case LSM6DS3_G_FS_2000:
    sensitivity = 70;
    break;
  }

  pData[0] = (int32_t)(pDataRaw[0] * sensitivity);
  pData[1] = (int32_t)(pDataRaw[1] * sensitivity);
  pData[2] = (int32_t)(pDataRaw[2] * sensitivity);

  return IMU_6AXES_OK;
}

/**
* @brief  Read raw data from LSM6DS3 Gyroscope & Accelerometer output register
* @param  pData the pointer where the raw data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_GetAxesRaw(uint8_t DeviceAddr, int16_t *pData)
{
  /*Here we have to add the check if the parameters are valid*/
  uint8_t tempReg[12];

  if(LSM6DS3_IO_Read(&tempReg[0], DeviceAddr, LSM6DS3_XG_OUT_X_L_G, 12) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  pData[0] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);
  pData[1] = ((((int16_t)tempReg[3]) << 8)+(int16_t)tempReg[2]);
  pData[2] = ((((int16_t)tempReg[5]) << 8)+(int16_t)tempReg[4]);

  pData[3] = ((((int16_t)tempReg[7]) << 8)+(int16_t)tempReg[6]);
  pData[4] = ((((int16_t)tempReg[9]) << 8)+(int16_t)tempReg[8]);
  pData[5] = ((((int16_t)tempReg[11])<< 8)+(int16_t)tempReg[10]);

  return IMU_6AXES_OK;
}

/**
* @brief  Read data from LSM6DS3 Accelerometer and calculate linear acceleration in mg
*         & Gyroscope and calculate angular rate in mdps
*
* @param  pData the pointer where the accelerometer & gyroscope data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_GetAxes(uint8_t DeviceAddr, int32_t *pData)
{
  int16_t pDataRaw[6];
  float sensitivity;

  //Read 6 Axis Raw Data.
  LSM6DS3_GetAxesRaw(DeviceAddr, pDataRaw);

  //Get Acc Sensitive.
  LSM6DS3_X_GetSensitivity(DeviceAddr, &sensitivity);

  //Calculate Acc.
  pData[0] = (int32_t)(pDataRaw[3] * sensitivity);
  pData[1] = (int32_t)(pDataRaw[4] * sensitivity);
  pData[2] = (int32_t)(pDataRaw[5] * sensitivity);

  //Get Gyro Sensitive.
  LSM6DS3_G_GetSensitivity(DeviceAddr, &sensitivity);

  //Calculate Angle Speed.
  pData[3] = (int32_t)(pDataRaw[0] * sensitivity);
  pData[4] = (int32_t)(pDataRaw[1] * sensitivity);
  pData[5] = (int32_t)(pDataRaw[2] * sensitivity);

  return IMU_6AXES_OK;
}


/**
* @brief  Fast Read data from LSM6DS3 Accelerometer and calculate linear acceleration in mg
*         & Gyroscope and calculate angular rate in mdps
*
* @param  pData the pointer where the accelerometer & gyroscope data are stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_GetAxes_Fast(uint8_t DeviceAddr, int16_t *pData)
{
  int16_t pDataRaw[6];  //Gyro 0-1-2  Acc 3-4-5
  //     X-Y-Z      X-Y-Z
  //Read 6 Axis Raw Data.
  LSM6DS3_GetAxesRaw(DeviceAddr, pDataRaw);

  //Axis-X
#if   (Real_Axis_PX == Sens_Axis_PX)
  pData[0] =  pDataRaw[0];    //Gyro
  pData[3] =  pDataRaw[3];    //Acc.
#elif (Real_Axis_PX == Sens_Axis_PY)
  pData[0] =  pDataRaw[1];    //Gyro
  pData[3] =  pDataRaw[4];    //Acc.
#elif (Real_Axis_PX == Sens_Axis_PZ)
  pData[0] =  pDataRaw[2];    //Gyro
  pData[3] =  pDataRaw[5];    //Acc.
#elif (Real_Axis_PX == Sens_Axis_NX)
  pData[0] = -pDataRaw[0];    //Gyro
  pData[3] = -pDataRaw[3];    //Acc.
#elif (Real_Axis_PX == Sens_Axis_NY)
  pData[0] = -pDataRaw[1];    //Gyro
  pData[3] = -pDataRaw[4];    //Acc.
#elif (Real_Axis_PX == Sens_Axis_NZ)
  pData[0] = -pDataRaw[2];    //Gyro
  pData[3] = -pDataRaw[5];    //Acc.
#endif

  //Axis-Y
#if   (Real_Axis_PY == Sens_Axis_PX)
  pData[1] =  pDataRaw[0];    //Gyro
  pData[4] =  pDataRaw[3];    //Acc.
#elif (Real_Axis_PY == Sens_Axis_PY)
  pData[1] =  pDataRaw[1];    //Gyro
  pData[4] =  pDataRaw[4];    //Acc.
#elif (Real_Axis_PY == Sens_Axis_PZ)
  pData[1] =  pDataRaw[2];    //Gyro
  pData[4] =  pDataRaw[5];    //Acc.
#elif (Real_Axis_PY == Sens_Axis_NX)
  pData[1] = -pDataRaw[0];    //Gyro
  pData[4] = -pDataRaw[3];    //Acc.
#elif (Real_Axis_PY == Sens_Axis_NY)
  pData[1] = -pDataRaw[1];    //Gyro
  pData[4] = -pDataRaw[4];    //Acc.
#elif (Real_Axis_PY == Sens_Axis_NZ)
  pData[1] = -pDataRaw[2];    //Gyro
  pData[4] = -pDataRaw[5];    //Acc.
#endif

  //Axis-Z
#if   (Real_Axis_PZ == Sens_Axis_PX)
  pData[2] =  pDataRaw[0];    //Gyro
  pData[5] =  pDataRaw[3];    //Acc.
#elif (Real_Axis_PZ == Sens_Axis_PY)
  pData[2] =  pDataRaw[1];    //Gyro
  pData[5] =  pDataRaw[4];    //Acc.
#elif (Real_Axis_PZ == Sens_Axis_PZ)
  pData[2] =  pDataRaw[2];    //Gyro
  pData[5] =  pDataRaw[5];    //Acc.
#elif (Real_Axis_PZ == Sens_Axis_NX)
  pData[2] = -pDataRaw[0];    //Gyro
  pData[5] = -pDataRaw[3];    //Acc.
#elif (Real_Axis_PZ == Sens_Axis_NY)
  pData[2] = -pDataRaw[1];    //Gyro
  pData[5] = -pDataRaw[4];    //Acc.
#elif (Real_Axis_PZ == Sens_Axis_NZ)
  pData[2] = -pDataRaw[2];    //Gyro
  pData[5] = -pDataRaw[5];    //Acc.
#endif

  return IMU_6AXES_OK;
}


/**
* @brief  Read Accelero Sensitivity
* @param  pfData the pointer where the accelerometer sensitivity is stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_X_GetSensitivity(uint8_t DeviceAddr, float *pfData)
{
  /*Here we have to add the check if the parameters are valid*/

  uint8_t tempReg = 0x00;


  if(LSM6DS3_IO_Read(&tempReg, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  tempReg &= LSM6DS3_XL_FS_MASK;

  switch(tempReg)
  {
    case LSM6DS3_XL_FS_2G:
    *pfData = 0.06103515625;
    break;
    case LSM6DS3_XL_FS_4G:
    *pfData = 0.1220703125;
    break;
    case LSM6DS3_XL_FS_8G:
    *pfData = 0.244140625;
    break;
    case LSM6DS3_XL_FS_16G:
    *pfData = 0.48828125;
    break;
    default:
    break;
  }

  return IMU_6AXES_OK;
}



/**
* @brief  Read Gyro Sensitivity
* @param  pfData the pointer where the gyroscope sensitivity is stored
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_G_GetSensitivity(uint8_t DeviceAddr, float *pfData)
{
  /*Here we have to add the check if the parameters are valid*/

  uint8_t tempReg = 0x00;


  if(LSM6DS3_IO_Read(&tempReg, DeviceAddr, LSM6DS3_XG_CTRL2_G, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  tempReg &= LSM6DS3_G_FS_MASK;

  switch(tempReg)
  {
    case LSM6DS3_G_FS_125:
    *pfData = 4.375;
    break;
    case LSM6DS3_G_FS_245:
    *pfData = 8.75;
    break;
    case LSM6DS3_G_FS_500:
    *pfData = 17.50;
    break;
    case LSM6DS3_G_FS_1000:
    *pfData = 35;
    break;
    case LSM6DS3_G_FS_2000:
    *pfData = 70;
    break;
    default:
    break;
  }

  return IMU_6AXES_OK;
}

/**
* @brief  Enable free fall detection
* @param  None
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_Enable_Free_Fall_Detection(uint8_t DeviceAddr)
{
  uint8_t tmp1 = 0x00;

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* Output Data Rate selection */
  tmp1 &= ~(LSM6DS3_XL_ODR_MASK);
  tmp1 |= LSM6DS3_XL_ODR_416HZ;

  /* Full scale selection */
  tmp1 &= ~(LSM6DS3_XL_FS_MASK);
  tmp1 |= LSM6DS3_XL_FS_2G;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_CTRL1_XL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_UP_DUR, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* FF_DUR5 setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_FF_DUR5_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_FF_DUR5_DEFAULT;

  /* WAKE_DUR setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_WAKE_DUR_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_WAKE_DUR_DEFAULT;

  /* TIMER_HR setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_TIMER_HR_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_TIMER_HR_DEFAULT;

  /* SLEEP_DUR setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_SLEEP_DUR_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_SLEEP_DUR_DEFAULT;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_UP_DUR, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_FREE_FALL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* FF_DUR setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_TYPICAL;

  /* FF_THS setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_312MG;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_FREE_FALL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_MD1_CFG, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* INT1_FF setting */
  tmp1 &= ~(LSM6DS3_XG_MD1_CFG_INT1_FF_MASK);
  tmp1 |= LSM6DS3_XG_MD1_CFG_INT1_FF_ENABLE;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_MD1_CFG, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  return IMU_6AXES_OK;
}

/**
* @brief  Disable free fall detection
* @param  None
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_Disable_Free_Fall_Detection(uint8_t DeviceAddr)
{
  uint8_t tmp1 = 0x00;

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_MD1_CFG, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* INT1_FF setting */
  tmp1 &= ~(LSM6DS3_XG_MD1_CFG_INT1_FF_MASK);
  tmp1 |= LSM6DS3_XG_MD1_CFG_INT1_FF_DISABLE;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_MD1_CFG, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_FREE_FALL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  /* FF_DUR setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_DEFAULT;

  /* FF_THS setting */
  tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_MASK);
  tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_156MG;

  if(LSM6DS3_IO_Write(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_FREE_FALL, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  return IMU_6AXES_OK;
}

/**
* @brief  Get status of free fall detection
* @param  status the pointer where the status of free fall detection is stored; 0 means no detection, 1 means detection happened
* @retval IMU_6AXES_OK in case of success, an error code otherwise
*/
IMU_6AXES_StatusTypeDef LSM6DS3_Get_Status_Free_Fall_Detection(uint8_t DeviceAddr, uint8_t *status)
{
  uint8_t tmp1 = 0x00;

  if(LSM6DS3_IO_Read(&tmp1, DeviceAddr, LSM6DS3_XG_WAKE_UP_SRC, 1) != IMU_6AXES_OK)
  {
    return IMU_6AXES_ERROR;
  }

  tmp1 &= LSM6DS3_XG_WAKE_UP_SRC_FF_IA_MASK;

  switch(tmp1)
  {
    case LSM6DS3_XG_WAKE_UP_SRC_FF_IA_ENABLE:
    *status = 1;
    break;
    case LSM6DS3_XG_WAKE_UP_SRC_FF_IA_DISABLE:
    default:
    *status = 0;
    break;
  }

  return IMU_6AXES_OK;
}


/*************************************************************
***************     User Code Below.   ***********************
**************************************************************
*/
//extern I2C_HandleTypeDef    hi2c1;

#define LSM6DS3_IIC_TIMOUT  100
#define LSM6DS3_IICx        hi2c1

void I2C_Write(I2C_TypeDef* I2Cx,
               uint8_t      Dev_Addr,
               uint8_t      Reg_Addr,
               uint8_t*     Buffer,
               uint8_t      Len
                 );

void I2C_Read(I2C_TypeDef* I2Cx,
              uint8_t      Dev_Addr,
              uint8_t      Reg_Addr,
              uint8_t*     Buffer,
              uint8_t      Len
                );

void I2C_Reg_Addr_Set(I2C_TypeDef* I2Cx,
                      uint8_t      Dev_Addr,
                      uint8_t      Reg_Addr
                        );

/* Parameters Define.
*/
#define LSM6DS3_IIC_TIMOUT  100
//#define LSM6DS3_IICx        I2C1
#define I2C_Timing          0x20303e5d

//0x50330309

/* MCU GPIO Init
*/
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Init(void)
{
  return IMU_6AXES_OK;
}

/* IIC / SPI Write
*/
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Write(uint8_t*   pBuffer,
                                         uint8_t    DeviceAddr,
                                         uint8_t    RegisterAddr,
                                         uint16_t   NumByteToWrite
                                           )
{
  IICWriteDevice(DeviceAddr,    //uint8_t device,
                 RegisterAddr,  //uint8_t reg_addr,
                 pBuffer,       //uint8_t *buf,
                 NumByteToWrite //uint8_t cnt
                   );
  return IMU_6AXES_OK;
}

/* IIC / SPI Read
*/
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Read(uint8_t*    pBuffer,
                                        uint8_t     DeviceAddr,
                                        uint8_t     RegisterAddr,
                                        uint16_t    NumByteToRead
                                          )
{
  IICReadDevice(DeviceAddr,     //uint8_t device,
                RegisterAddr,   //uint8_t reg_addr,
                pBuffer,        //uint8_t *buf,
                NumByteToRead   //uint8_t cnt
                  );
  return IMU_6AXES_OK;
}

void LSM6DS3_IO_ITConfig(void)
{

}

/* Read All Registers.
*/
void LSM6DS3_Read_Reg_All(uint8_t* Buffer)
{
  IICReadDevice(0xd4,   //uint8_t device,
                0x01,   //uint8_t reg_addr,
                Buffer, //uint8_t *buf,
                96      //uint8_t cnt
                  );
}


/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
