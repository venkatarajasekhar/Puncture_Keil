#ifndef __ADC_DMA_H
#define __ADC_DMA_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�adc_dma
*
* �ļ���ʶ��adc_dma.h
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

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

extern __IO uint16_t ADCConvertedValue[6];
extern __IO uint16_t ADC_Value[6];

typedef struct ADC_Value {
  float ADC_ValueChannel_1;
  float ADC_ValueChannel_2;
  float ADC_ValueChannel_3;
  float ADC_ValueChannel_4;
  float ADC_ValueChannel_5;
  float ADC_ValueChannel_6;
}ADC_Channel_Value;

void ADC_DMA_Init(void);
void ADC_data_filter(void);
void ADC_data_filter_ave(void);
void Get_ADC_data_filter_ave(void);
void Update_ADC_Value(uint8_t* pDesArr,uint8_t* pDesLength);

void  Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);
#endif
