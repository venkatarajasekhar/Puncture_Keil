 #include "dac.h"
u16 dac1_value=0,dac2_value=0;
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�dac.c
*
* �ļ���ʶ��dac
* ժ    Ҫ��2·ģ���ѹ�����
*
*
* ��ǰ�汾��v1.0
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/10
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/
/*******************************��������****************************************
* ��������: void DAC2_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: DAC1·ģ���������ʼ��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/14
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

/*******************************��������****************************************
* ��������: void DAC1_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: DAC1·ģ���������ʼ��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/14
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

/*******************************��������****************************************
* ��������: void Set_DAC2_Value(u16 vol) 
* �������: u16 vol 
* ���ز���: void  
* ��    ��: ����DAC��ģ��ֵ   //vol:0~3300,  0~3.3v
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/14
*******************************************************************************/ 
void Set_DAC2_Value(u16 vol)
{
  float temp=vol;
  temp/=1000;
  temp=temp*4095/3.3;
	if(temp>=0&&temp<=4095)
		DAC_SetChannel1Data(DAC_Align_12b_R,temp);
}

/*******************************��������****************************************
* ��������: void Set_DAC1_Value(u16 vol) 
* �������: u16 vol 
* ���ز���: void  
* ��    ��: ����DAC��ģ��ֵ  //vol:0~3300,  0~3.3v
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/14
*******************************************************************************/ 
void Set_DAC1_Value(u16 vol)
{
  float temp=vol;
  temp/=1000;
  temp=temp*4095/3.3;
	if(temp>=0&&temp<=4095)
		DAC_SetChannel2Data(DAC_Align_12b_R,temp);
}


