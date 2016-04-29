#ifndef __MPU6050_H
#define __MPU6050_H

#include "ahrs_ringbuffer.h"
#include <stdlib.h>
#include <stdio.h>

extern float Ax_A, Ay_A, Az_A, Ax_B, Ay_B, Az_B, Ax_C, Ay_C, Az_C;


typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
	
}SENSOR_DATA_TypeDef;

int DetectAcc(void);
void Update_Percussion_Value(uint8_t* pDesArr,uint8_t* pDesLength);
//static SENSOR_DATA_TypeDef MPU6050_Read_Acc(SENSOR_DATA_TypeDef data);
void MPU6050_Read_Acc(void);

SENSOR_DATA_TypeDef MPU6050_ADD(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1);
SENSOR_DATA_TypeDef MPU6050_MINUS(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1);
SENSOR_DATA_TypeDef MPU6050_TIMES(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1);
SENSOR_DATA_TypeDef MPU6050_DEVIDE(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1);
int MPU6050_IS_NULL(SENSOR_DATA_TypeDef data);
void MPU6050_READ_FIFO(SENSOR_DATA_TypeDef *axis_converted_avg);
int MPU6050_Acc_Detect(SENSOR_DATA_TypeDef NEW_SAMPLE);
void Get_Percussion_Flag(void);
int Partition(short *a,int low,int high);
short Quick_Sort(short *a,int low,int high);
	


#endif
