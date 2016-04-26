#ifndef __ENCODER_H
#define __ENCODER_H	 
#include "sys.h"
#include "stm32f10x_it.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�encoder
*
* �ļ���ʶ��encoder.h
* ժ    Ҫ�����ֱ������������
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/13
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

#define Encoder_CS         PEout(8)
#define Encoder_SCLK	   PGout(1)
#define Encode_Read_DO    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)

void ABS_Encoder_Init(void);
int ABS_Encoder_Read(void);
void ABS_Encoder_Delay(__IO uint32_t nCount);
void Incre_Encoder_Init(void);
void Get_ABSEncoder_Number(void);
void TIM1_Mode_Config(void);
void Get_ENC1_Number(void);
void TIM3_Mode_Config(void);
void Get_ENC2_Number(void);
void TIM8_Mode_Config(void);
void Get_ENC3_Number(void);
void TIM4_Mode_Config(void);
void Get_ENC4_Number(void);
void ENC5_Mode_config(void);
void TIM5_Mode_config(void);
void Get_ENC6_Number(void);

void Update_ENC1_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ENC2_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ENC3_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ENC4_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ENC5_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ENC6_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ABSEnc_Value(uint8_t* pDesArr,uint8_t* pDesLength);

extern int16_t ENC2_COUNT;
extern int16_t ENC5_COUNT;
extern int16_t ENC6_COUNT;


void ENC2_Mode_config(void);

#endif
