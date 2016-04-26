 #include "dac.h"
u16 dac1_value=0,dac2_value=0;
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：dac.c
*
* 文件标识：dac
* 摘    要：2路模拟电压量输出
*
*
* 当前版本：v1.0
* 作    者：Xu jinqi
* 日    期：2015/7/10
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/
/*******************************函数声明****************************************
* 函数名称: void DAC2_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: DAC1路模拟量输出初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/14
*******************************************************************************/ 
void DAC2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  DAC_InitTypeDef DAC_InitType;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_4);
  
  DAC_InitType.DAC_Trigger=DAC_Trigger_None;	
  DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;
  DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
  DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;
  DAC_Init(DAC_Channel_1,&DAC_InitType);
  
  DAC_Cmd(DAC_Channel_1, ENABLE);
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);
}

/*******************************函数声明****************************************
* 函数名称: void DAC1_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: DAC1路模拟量输出初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/14
*******************************************************************************/ 
void DAC1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  DAC_InitTypeDef DAC_InitType;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_5);
  
  DAC_InitType.DAC_Trigger=DAC_Trigger_None;	
  DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;
  DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
  DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;
  DAC_Init(DAC_Channel_2,&DAC_InitType);
  
  DAC_Cmd(DAC_Channel_2, ENABLE);

  DAC_SetChannel2Data(DAC_Align_12b_R, 0);
}

/*******************************函数声明****************************************
* 函数名称: void Set_DAC2_Value(u16 vol) 
* 输入参数: u16 vol 
* 返回参数: void  
* 功    能: 设置DAC的模拟值   //vol:0~3300,  0~3.3v
* 作    者: by Xu jinqi
* 日    期: 2015/7/14
*******************************************************************************/ 
void Set_DAC2_Value(u16 vol)
{
  float temp=vol;
  temp/=1000;
  temp=temp*4095/3.3;
	if(temp>=0&&temp<=4095)
		DAC_SetChannel1Data(DAC_Align_12b_R,temp);
}

/*******************************函数声明****************************************
* 函数名称: void Set_DAC1_Value(u16 vol) 
* 输入参数: u16 vol 
* 返回参数: void  
* 功    能: 设置DAC的模拟值  //vol:0~3300,  0~3.3v
* 作    者: by Xu jinqi
* 日    期: 2015/7/14
*******************************************************************************/ 
void Set_DAC1_Value(u16 vol)
{
  float temp=vol;
  temp/=1000;
  temp=temp*4095/3.3;
	if(temp>=0&&temp<=4095)
		DAC_SetChannel2Data(DAC_Align_12b_R,temp);
}


