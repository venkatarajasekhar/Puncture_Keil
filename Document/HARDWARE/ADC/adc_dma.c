#include "adc_dma.h"
#include <stdio.h>
#include "delay.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�adc_dma
*
* �ļ���ʶ��adc_dma.c
* ժ    Ҫ���ɼ�STM32��6·ADC�źţ�����DMA��ʽ
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/13
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

__IO uint16_t ADCConvertedValue[6];
__IO uint16_t ADC_Value[6];
ADC_Channel_Value adc_sampe;
ADC_Channel_Value *p_ADC_SampeValue = &adc_sampe;
uint16_t ADCConvertedValue_Arr[6][50]={0};
double ADCConvertedValue_old[6]={0.0};

double ADC_origin[4][6]={0.0};
double ADC_filter[4][6]={0.0};
__IO uint16_t ADC_filter_final[6]={0.0};

//float Adc_a2=-0.9844142,  Adc_b1=0.0077929, Adc_b2=0.0077929;

double Adc_a2=-1.9645,  Adc_a3=0.9651;
//double Adc_b1=0.00015515, Adc_b2=0.0003103, Adc_b3=0.00015515;
double Adc_b1=0.00015, Adc_b2=0.0003, Adc_b3=0.00015; 
/*******************************��������****************************************
* ��������: void ADC_DMA_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ����ADC ������DMA��ʽ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void ADC_DMA_Init(void)
{ 
   GPIO_InitTypeDef GPIO_InitStructure;
   ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
	/****RCC_Configuration--------------------------***/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO |RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
  /****GPIO_Configuration------------------------***/
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /******* DMA1 channel1 configuration ----------***/

  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 6;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /**** ADC1 configuration ------------------------***/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 6;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 5, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 6, ADC_SampleTime_239Cycles5);
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  
  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
  
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  
}

/*******************************��������****************************************
* ��������: void ADC_data_filter(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ʱ��ȡADC����ֵ�����Ҽ����˲��㷨����  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void ADC_data_filter(void)
{
//  float temp[6]={0.0};
//  u8 i=0;
//  for(i=0;i<6;i++)
//  {
//    temp[i]=ADCConvertedValue[i];
//  }
//  
//  p_ADC_SampeValue->ADC_ValueChannel_1    =  (Adc_b1*temp[0] + Adc_b2*ADCConvertedValue_old[0] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_1); 
//  p_ADC_SampeValue->ADC_ValueChannel_2    =  (Adc_b1*temp[1] + Adc_b2*ADCConvertedValue_old[1] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_2); 
//  p_ADC_SampeValue->ADC_ValueChannel_3    =  (Adc_b1*temp[2] + Adc_b2*ADCConvertedValue_old[2] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_3); 
//  p_ADC_SampeValue->ADC_ValueChannel_4    =  (Adc_b1*temp[3] + Adc_b2*ADCConvertedValue_old[3] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_4); 
//  p_ADC_SampeValue->ADC_ValueChannel_5    =  (Adc_b1*temp[4] + Adc_b2*ADCConvertedValue_old[4] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_5); 
//  p_ADC_SampeValue->ADC_ValueChannel_6    =  (Adc_b1*temp[5] + Adc_b2*ADCConvertedValue_old[5] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_6); 
//  
//  for(i=0;i<6;i++)
//  {
//    ADCConvertedValue_old[i]=temp[i];
//  }
 // printf("channel1:%f \r\n",p_ADC_SampeValue->ADC_ValueChannel_1);
 // printf("channel2:%f \n",p_ADC_SampeValue->ADC_ValueChannel_2);
 // printf("channel3:%f \n",p_ADC_SampeValue->ADC_ValueChannel_3);
 // printf("channel4:%f \n",p_ADC_SampeValue->ADC_ValueChannel_4);
  //printf("channel5:%f \n",p_ADC_SampeValue->ADC_ValueChannel_5);
 // printf("channel6:%f \n",p_ADC_SampeValue->ADC_ValueChannel_6);
 
  u8 i=0;
  for(i=0;i<6;i++)
  {
    ADC_origin[3][i] = ADCConvertedValue[i];
  }

	for(i=0;i<6;i++)
	{
		ADC_filter[3][i] = Adc_b1*ADC_origin[3][i] + Adc_b2*ADC_origin[2][i] + Adc_b3*ADC_origin[1][i] - Adc_a2*ADC_filter[2][i] - Adc_a3*ADC_filter[1][i];
	}
	//δ�˲���ֵ
	for(i=0;i<6;i++)
	{
		ADC_origin[1][i] = ADC_origin[2][i]; 
		ADC_origin[2][i] = ADC_origin[3][i];
	}

	//���˲���ֵ
	for(i=0;i<6;i++)
	{
		ADC_filter[1][i] = ADC_filter[2][i]; 
		ADC_filter[2][i] = ADC_filter[3][i]; 
		ADC_filter_final[i] = (u16)ADC_filter[3][i]; 
	}
	//printf("%d %d\r\n",ADC_filter_final[0],ADCConvertedValue[0]);
 
  
}


/*******************************��������****************************************
* ��������: void ADC_data_filter_ave(void) 
* �������: void 
* ���ز���: void  
* ��    ��: 2000hz��ʱ��ȡADC����ֵ
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void ADC_data_filter_ave(void)
{
  static u8 u_y=0;
  u8 u_x=0;
  for(u_x=0;u_x<=5;u_x++)
  {
    ADCConvertedValue_Arr[u_x][u_y] = ADCConvertedValue[u_x]; 
  }
  
  u_y++;
    if(u_y>=50)
    {
      u_y=0;
    }
}


/*******************************��������****************************************
* ��������: void Get_ADC_data_filter_ave(u16 *aver)
* �������: void 
* ���ز���: void  
* ��    ��: 50hz��ʱ��ȡADC����ֵ������ƽ���˲��㷨����  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
/*
void Get_ADC_data_filter_ave(u16 *aver)
{
  u8 x=0,y=0;
  u32 sum=0;
  for(x=0;x<=5;x++)
  {
    for(y=0;y<=49;y++)
    {
     sum =sum + ADCConvertedValue_Arr[x][y];
    }
   aver[x] = sum / 50;
   sum = 0;
  }
}
*/
void Get_ADC_data_filter_ave(void)
{
  u8 x=0,y=0;
  u32 sum=0;
  for(x=0;x<=5;x++)
  {
    for(y=0;y<=49;y++)
    {
     sum =sum + ADCConvertedValue_Arr[x][y];
    }
   //ADC_Value[x] = sum / 50;
		ADC_filter_final[x] = sum / 50;
   sum = 0;
  }
}

/*******************************��������****************************************
* ��������: void Update_ADC_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������: uint8_t* pDesArr,uint8_t* pDesLength 
* ���ز���: void  
* ��    ��: ��ADC��6ͨ��ֵ���뵽usb send���ݰ��С�
            ע��˺�����ͬ�ĵ��ô���Ӱ��������������������ݰ��е�λ��
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void Update_ADC_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  s16 t=0;
  // t = DS18B20_Get_Temp();
  // t = 0x1234;
  //ADC1 value
  //t=ADC_Value[0];
  t = ADC_filter_final[0];
	*pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);
  
  //ADC2 value
  //t=ADC_Value[1];
	t = ADC_filter_final[1];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);	
  
  //ADC3 value
  //t=ADC_Value[2];
	t = ADC_filter_final[2];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);	
  
  //ADC4 value
  //t=ADC_Value[3];
	t = ADC_filter_final[3];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);	
  
  //ADC5 value
  //t=ADC_Value[4];
	t = ADC_filter_final[4];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);	
  
  //ADC6 value
  //t=ADC_Value[5];
	t = ADC_filter_final[5];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);		
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}


//3?��??��ADC
//?a��??��????��?1??�������̨�?a��y
//?��????��????a??�����̨�0~3																	   
void  Adc_Init(void)
{ 	
  ADC_InitTypeDef ADC_InitStructure; 
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1, ENABLE );	  //��1?��ADC1�����̨�����?��
  
  
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����??ADC��??�̨�������6 72M/6=12,ADC��?�䨮����??2??��3?1y14M
  
  //PA1 ����?a?��?a�����̨���?��?��y??                         
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//?��?a��?��?��y??
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
  
  ADC_DeInit(ADC1);  //?��??ADC1,??��a���� ADC1 ��?��?2???��??��??����?a������??��
  
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC1�����?�꨺?:ADC1o��ADC21�����?��?������?�꨺?
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//?�꨺y��a??1�����?���̣������̨�?�꨺?
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//?�꨺y��a??1�����?���̣���?��a???�꨺?
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��a??��������?t??2?��?��a2?�䣤����???��
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC��y?Y����????
  ADC_InitStructure.ADC_NbrOfChannel = 1;	//?3D��??DD1??����a??��?ADC�����̨���?��y??
  ADC_Init(ADC1, &ADC_InitStructure);	//?��?YADC_InitStruct?D???����?2?��y3?��??����a����ADCx��???��??��   
  
  
  ADC_Cmd(ADC1, ENABLE);	//��1?��???����?ADC1
  
  ADC_ResetCalibration(ADC1);	//��1?��?��??D���?  
  
  while(ADC_GetResetCalibrationStatus(ADC1));	//�̨���y?��??D���??����?
  
  ADC_StartCalibration(ADC1);	 //?a??ADD���?
  
  while(ADC_GetCalibrationStatus(ADC1));	 //�̨���yD���??����?
  
  //	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//��1?��???����?ADC1��?����?t��a?????��1|?��
  
}		

u16 Get_Adc(u8 ch)   
{
  //����?????��ADC��?1??�����������̨���?��???D����D��?2��?������??
  ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC�����̨�,2��?������???a239.5?��?��	  			    
  
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//��1?��???����?ADC1��?����?t��a?????��1|?��	
  
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�̨���y��a???����?
  
  return ADC_GetConversionValue(ADC1);	//����??��??����?��?ADC11??��������?��a???��1?
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
  u32 temp_val=0;
  u8 t;
  for(t=0;t<times;t++)
  {
    temp_val+=Get_Adc(ch);
    delay_ms(5);
  }
  return temp_val/times;
} 	

