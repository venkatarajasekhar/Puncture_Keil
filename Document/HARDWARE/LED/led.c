#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
s16 LED_RED = 0;
s16 LED_R = 0;
s16 LED_G = 0;
s16 LED_B = 0;


void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}
 
/*******************************��������****************************************
* ��������:  	void LED_1W_Init(void)
* �������:  	void
* ���ز���:   void
* ��    ��:   ��ʼ��LED����
* ��    ��: 	by Cao Jue
* ��    ��: 	2016/03/18
*******************************************************************************/ 
void LED_RED_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 // TIM_Cmd(TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ��TIMx����
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOB����ʱ��ʹ��
	
 
   //���ø�����Ϊ�����������,���TIM4 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH4 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
 
	TIM_TimeBaseStructure.TIM_Period = 2399; //�����Զ���װ������ֵ 30khz
	TIM_TimeBaseStructure.TIM_Prescaler =0; //����Ԥ��Ƶֵ ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2ģʽ	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//TIM_OCInitStructure.TIM_Pulse = 1250; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �͵�ƽ��Ч 
	//TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIMx
	//TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1 Ԥװ��ʹ��
	
	
	
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  // TIM_OCInitStructure.TIM_Pulse = 24;
  // TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
  // TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = 0;
   TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
  
	//DC_MOTOR_IO_Init();	
	
}


//RGB TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void LED_RGB_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    

  //���ø�����Ϊ�����������,���TIM3 CH4 ��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH4 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
	
   //���ø�����Ϊ�����������,���TIM3 CH1 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}

void SetLED_RED_Value(void)
{	
	if(Timecount_RED==16000)
	{  
    TIM_SetCompare3(TIM3,0);
  }
  else
	{
    TIM_SetCompare3(TIM3,LED_RED);
  }		 
}

void SetLED_RGB_Value(void)
{	
	if(Timecount_RGB==16000)
	{  
    TIM_SetCompare4(TIM3,0);
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM3,0);
  }
  else
	{
    TIM_SetCompare4(TIM3,LED_R);
		TIM_SetCompare1(TIM3,LED_G);
		TIM_SetCompare2(TIM3,LED_B);
		
  }		 
}

