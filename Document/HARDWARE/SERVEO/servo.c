#include "servo.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�servo
*
* �ļ���ʶ��servo.c
* ժ    Ҫ�����ֶ����ʼ��
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/15
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

u16 servo_value1=1250,servo_value2=0;
/*******************************��������****************************************
* ��������: void Servo_Motor_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ���ֶ���ĳ�ʼ����//1520us\333hz   900-2100us
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Servo_Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
  /****ʱ������----------------------------------------------------***/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    /****GPIO����---------------------------------------------------***/
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /******* TIM3 ���� -----------------------------------------------*/  
  
  //50KZ:2499/575  ;300hz:95   ;400hz:71  ;72hz:399;  40hz:719  ;475hz:59
  TIM_TimeBaseStructure.TIM_Period = 2499;    //2499
  TIM_TimeBaseStructure.TIM_Prescaler = 71  ;   //71
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1250;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
    
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  //ʹ�ܶ�ʱ��
  TIM_Cmd(TIM2, ENABLE); 
  
}

/*******************************��������****************************************
* ��������: void Set_Servo_Value(u16 duty) 
* �������: u16 duty 
* ���ز���: void  
* ��    ��: �ı����ֶ���ĽǶ�  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Set_Servo_Value(u16 duty)
{
  TIM_SetCompare3(TIM2,duty);
}


