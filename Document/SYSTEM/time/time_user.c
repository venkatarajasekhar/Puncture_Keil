#include "time_user.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�Time_user
*
* �ļ���ʶ��
* ժ    Ҫ�����ö�ʱ�����������ڶ�ʱ�ȹ���
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/13
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

/*******************************��������****************************************
* ��������: void Time_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ���ö�ʱ������  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void Time_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
  NVIC_InitTypeDef NVIC_InitStructure; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  /****����time5.AD���ݻ�ȡʱ��  2000HZ **************************************/
  TIM_TimeBaseStructure.TIM_Period = 90;  //90
  TIM_TimeBaseStructure.TIM_Prescaler = 399;  //399
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʼ����ʱ��2
  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //����ʱ���ж�
  TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��5
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
  
 
  
}

