#include "MPU6050.h"
#include <stdio.h>
 
float acc[3] = {0};

uint8_t percussion_flag = 0;
uint8_t percussion_arry[5] = {0};
SENSOR_DATA_TypeDef axis_data[5] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

//
SENSOR_DATA_TypeDef THRESH					= {35,225,225};						//均值
SENSOR_DATA_TypeDef MAX_DATA 				= {-5000,-5000,-5000};		//
SENSOR_DATA_TypeDef MIN_DATA 				= {5000,5000,5000};
SENSOR_DATA_TypeDef DELTA 					= {5000,5000,5000};
SENSOR_DATA_TypeDef RES             = {5000,5000,5000};
SENSOR_DATA_TypeDef LAST_SAMPLE 		= {0,0,0};
SENSOR_DATA_TypeDef CURR_SAMPLE 		= {0,0,0};	
SENSOR_DATA_TypeDef AVERAGE_DATA[4] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

SENSOR_DATA_TypeDef data_tmp				= {0,0,0};

SENSOR_DATA_TypeDef QUICKSORT_DATA[5]  = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

#define max(a,b) ((a)>(b)?(a):(b))


//static SENSOR_DATA_TypeDef MPU6050_Read_Acc(SENSOR_DATA_TypeDef data)
//{
//	SENSOR_DATA_TypeDef data2;	
//	Get_AHRS_Value();
//	
//	data.X = Ax_A;
//	data.Y = Ay_A;
//	data.Z = Az_A;
//	

//	data2.X = Ax_A;
//	data2.Y = Ay_A;
//	data2.Z = Az_A;	
//	printf("data.X=%d,data.Y=%d,data.Z=%d\r\n",data2.X,data2.Y,data2.Z);
//	return data;
//}
void MPU6050_Read_Acc(void)
{
	Get_AHRS_Value();
	data_tmp.X = Ax_A;
	data_tmp.Y = Ay_A;
	data_tmp.Z = Az_A;
	//printf("data_tmp.X=%d,data_tmp.Y=%d,data_tmp.Z=%d\r\n",data_tmp.X,data_tmp.Y,data_tmp.Z);
}

/**************************************************************************//**
 * @brief
 * Calibrate MPU6050 sensor
 *****************************************************************************/
SENSOR_DATA_TypeDef MPU6050_ADD(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1)
{
	SENSOR_DATA_TypeDef result;
	result.X = data0.X + data1.X;
	result.Y = data0.Y + data1.Y;
	result.Z = data0.Z + data1.Z;
	return result;
}

/**************************************************************************//**
 * @brief
 * Calibrate MPU6050 sensor
 *****************************************************************************/
SENSOR_DATA_TypeDef MPU6050_MINUS(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1)
{
	SENSOR_DATA_TypeDef result;
	result.X = data0.X - data1.X;
	result.Y = data0.Y - data1.Y;
	result.Z = data0.Z - data1.Z;
	return result;
}

/**************************************************************************//**
 * @brief
 * Calibrate MPU6050 sensor
 *****************************************************************************/
SENSOR_DATA_TypeDef MPU6050_TIMES(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1)
{
	SENSOR_DATA_TypeDef result;
	result.X = data0.X * data1.X;
	result.Y = data0.Y * data1.Y;
	result.Z = data0.Z * data1.Z;
	return result;
}

/**************************************************************************//**
 * @brief
 * Calibrate MPU6050 sensor
 *****************************************************************************/
SENSOR_DATA_TypeDef MPU6050_DEVIDE(SENSOR_DATA_TypeDef data0, SENSOR_DATA_TypeDef data1)
{
	SENSOR_DATA_TypeDef result;
	result.X = data0.X/data1.X;
	result.Y = data0.Y/data1.Y;
	result.Z = data0.Z/data1.Z;
	return result;
}

/**************************************************************************//**
 * @brief
 * Calibrate MPU6050 sensor
 *****************************************************************************/
SENSOR_DATA_TypeDef MPU6050_AVERAGE(SENSOR_DATA_TypeDef *data, uint32_t len)
{
	SENSOR_DATA_TypeDef result;
	uint32_t i;
	for(i=0;i<len;i++)
	{
		result.X += data[i].X;
		result.Y += data[i].Y;
		result.Z += data[i].Z;
	}
	result.X /= len;
	result.Y /= len;
	result.Z /= len;
	return result;
}

/**************************************************************************//**
 * @brief
 * Calibrate MPU6050 sensor
 *****************************************************************************/
int MPU6050_IS_NULL(SENSOR_DATA_TypeDef data)
{
	if(data.X==0 && data.Y==0 && data.Z==0)
	{
		return 1;
	}
	else return 0;
}


/*****Quick Sort************/
int Partition(SENSOR_DATA_TypeDef *a,int low,int high)
{
	int pivotkey = a[low].Z;
	while(low<high)
	{
		if(low<high && a[high].Z>=pivotkey) --high;
		a[low].Z = a[high].Z;
		if(low<high && a[low].Z<=pivotkey) ++low;
		a[high].Z = a[low].Z;
	}
	a[low].Z = pivotkey;
	return low;
}

SENSOR_DATA_TypeDef Quick_Sort(SENSOR_DATA_TypeDef *a,int low,int high)
{
	uint8_t i = 0;
	SENSOR_DATA_TypeDef result;
	if(low<high)
	{
		int position = Partition(a,low,high);
		Quick_Sort(a,low,position-1);
		Quick_Sort(a,position+1,high);
	}
	result = a[low];
	for(i=0;i<5;i++)
		QUICKSORT_DATA[i] = a[i];
	
	return result;
}




/**************************************************************************//**
 * @brief
 * Read full FIFO of ADXL345 sensor, average over 4 consecutive data points
 *****************************************************************************/
void MPU6050_READ_FIFO(SENSOR_DATA_TypeDef *axis_converted_avg)
{
   uint8_t init_flag=0;
	 uint8_t i = 0;
//	 SENSOR_DATA_TypeDef axis_data_tmp;
//   SENSOR_DATA_TypeDef axis_data[5] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
   uint8_t res_div = 5;
   
   //reinit MAX and MIN value for each FIFO read
   MAX_DATA.X = -5000;
   MAX_DATA.Y = -5000;
   MAX_DATA.Z = -5000;
   MIN_DATA.X = 5000;
   MIN_DATA.Y = 5000;
   MIN_DATA.Z = 5000;
   //check if this is the very first data collection
   if(MPU6050_IS_NULL(AVERAGE_DATA[0]) && MPU6050_IS_NULL(AVERAGE_DATA[1]) && MPU6050_IS_NULL(AVERAGE_DATA[2]))
   {
	   init_flag = 1;
   }
   for(i=0; i<5; i++)
	{
		//ADXL345_Read_Reg(ADXL345Handle.port, DATA_START_REG_ADDR,(uint8_t*)axis_data[i],6);
		//axis_converted[i] = ADXL345_DATA_CONVERT(axis_data[i]);	
		MPU6050_Read_Acc();
		//Take care of first data collection issue
		if(i==0 && init_flag)
		{
			AVERAGE_DATA[0] = data_tmp;
			AVERAGE_DATA[1] = data_tmp;
			AVERAGE_DATA[2] = data_tmp;
			AVERAGE_DATA[3] = data_tmp;
		}
		//average process
		AVERAGE_DATA[3] = AVERAGE_DATA[2];
		AVERAGE_DATA[2] = AVERAGE_DATA[1];
		AVERAGE_DATA[1] = AVERAGE_DATA[0];
		AVERAGE_DATA[0] = data_tmp;
	  axis_converted_avg[i] = MPU6050_AVERAGE(AVERAGE_DATA,4);
		//find maximum and minimum value of 3 axis
		if(MAX_DATA.X<axis_converted_avg[i].X)  MAX_DATA.X=axis_converted_avg[i].X;
		if(MAX_DATA.Y<axis_converted_avg[i].Y)  MAX_DATA.Y=axis_converted_avg[i].Y;
		if(MAX_DATA.Z<axis_converted_avg[i].Z)  MAX_DATA.Z=axis_converted_avg[i].Z;
		if(MIN_DATA.X>axis_converted_avg[i].X)  MIN_DATA.X=axis_converted_avg[i].X;
		if(MIN_DATA.Y>axis_converted_avg[i].Y)  MIN_DATA.Y=axis_converted_avg[i].Y;
		if(MIN_DATA.Z>axis_converted_avg[i].Z)  MIN_DATA.Z=axis_converted_avg[i].Z;		
	}	
	//printf("axis_converted_avg : %d , %d , %d , %d , %d \r\n",axis_converted_avg[0].Z,axis_converted_avg[1].Z,axis_converted_avg[2].Z,axis_converted_avg[3].Z,axis_converted_avg[4].Z);
	//Calculate resolution for step counting 
	//THRESH = MPU6050_AVERAGE(axis_converted_avg,5);
	THRESH = Quick_Sort(axis_converted_avg,0,4);
	//printf("QuickSort : %d , %d , %d , %d , %d \r\n",axis_converted_avg[0].Z,axis_converted_avg[1].Z,axis_converted_avg[2].Z,axis_converted_avg[3].Z,axis_converted_avg[4].Z);
	DELTA =  MPU6050_MINUS(MAX_DATA,MIN_DATA);
	RES.X = max(MAX_DATA.X-THRESH.X, THRESH.X-MIN_DATA.X)/res_div;
	RES.Y = max(MAX_DATA.Y-THRESH.Y, THRESH.Y-MIN_DATA.Y)/res_div;
	//RES.Z = max(MAX_DATA.Z-THRESH.Z, THRESH.Z-MIN_DATA.Z)/res_div;
	RES.Z = 1000;
}


/**************************************************************************//**
 * @brief
 * Calibrate ADXL345 sensor
 *****************************************************************************/
int MPU6050_Acc_Detect(SENSOR_DATA_TypeDef NEW_SAMPLE)
{
	int flag = 0;
	//@TODO add time window and step model rule 
	if(abs(DELTA.X)>=abs(DELTA.Y) && abs(DELTA.X)>=abs(DELTA.Z) )
	{
		if((LAST_SAMPLE.X-THRESH.X>RES.X) && (CURR_SAMPLE.X-THRESH.X<-RES.X))
		{
			flag = 0;
			LAST_SAMPLE = CURR_SAMPLE;
		}	
		else
		{
			flag = 0;
			LAST_SAMPLE = CURR_SAMPLE;
			CURR_SAMPLE = NEW_SAMPLE;
		}
	}
	
	else if(abs(DELTA.Y)>=abs(DELTA.X) && abs(DELTA.Y)>=abs(DELTA.Z) )
	{
		if((LAST_SAMPLE.Y-THRESH.Y>RES.Y) && (CURR_SAMPLE.Y-THRESH.Y<-RES.Y))
		{
			flag = 0;
			LAST_SAMPLE = CURR_SAMPLE;
		}	
		else
		{
			flag = 0;
			LAST_SAMPLE = CURR_SAMPLE;
			CURR_SAMPLE = NEW_SAMPLE;
		}
	}
	
	else if(abs(DELTA.Z)>=abs(DELTA.X) && abs(DELTA.Z)>=abs(DELTA.Y) )
	{
		//flag = 1;
		if((abs(LAST_SAMPLE.Z-THRESH.Z)>RES.Z) && (abs(CURR_SAMPLE.Z-THRESH.Z)>RES.Z))
		{
			flag = 1;
			LAST_SAMPLE = CURR_SAMPLE;
			//CURR_SAMPLE = NEW_SAMPLE;
		}	
		else
		{
			flag = 0;
			LAST_SAMPLE = CURR_SAMPLE;
			CURR_SAMPLE = NEW_SAMPLE;
		}
	}

	return flag;
	
}

/*
int DetectAcc(void)
{
	int a;
	acc[2] = Az_A;
	if((int)(acc[2]-acc[1])>100)
		a = 1;
	else
		a = 0;
	
	acc[0] = acc[1];
	acc[1] = acc[2];
	
	return a;
}
*/

/*******************************函数声明****************************************
* 函数名称:  Get_Percussion_Flag(void)
* 输入参数:  void
* 返回参数:   void
* 功    能:   判定叩诊信号量
* 作    者: 	by Cao Jue
* 日    期: 	2016/03/17
*******************************************************************************/ 
void Get_Percussion_Flag(void)
{
	uint8_t i = 0;
	MPU6050_READ_FIFO(axis_data);
	for(i=0;i<5;i++)
	{
		percussion_arry[i] = MPU6050_Acc_Detect(axis_data[i]);
	
	}
	if(percussion_arry[0]|percussion_arry[1]|percussion_arry[2]|percussion_arry[3]|percussion_arry[4])
		percussion_flag = 1;
	else
		percussion_flag = 0;
//	MPU6050_Read_Acc();
//	percussion_flag = MPU6050_Acc_Detect(data_tmp);
}

/*******************************函数声明****************************************
* 函数名称:  Update_Percussion_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新叩诊信号量进入usbsendbuffer
* 作    者: 	by Cao Jue
* 日    期: 	2016/01/28
*******************************************************************************/ 
void Update_Percussion_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  u8 t=0;
  //t = 0x1234;	
  t=percussion_flag;
	percussion_flag = 0;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = t;  
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}

