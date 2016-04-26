#include "encoder.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�encoder
*
* �ļ���ʶ��encoder.c
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
uint16_t ENC_NU[6]={0};
uint16_t ENC_ABS  =0;
/*******************************��������****************************************
* ��������: void ABS_Encoder_Init(void) 
* �������: void 
* ���ز���: viod  
* ��    ��: SSI�źŵľ��Ա�������ʼ������  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void ABS_Encoder_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG, ENABLE );
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
 //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//CS
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //CLK
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//DO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
  
  GPIO_SetBits(GPIOG,GPIO_Pin_1);
}

/*******************************��������****************************************
* ��������: int ABS_Encoder_Read(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ȡ���Ա��������ź�ֵ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
int ABS_Encoder_Read(void)
{  
  int i=0;
  int	wdata=0;
  Encoder_CS = 1;
  ABS_Encoder_Delay(0xF);
  
  Encoder_CS = 0;
  ABS_Encoder_Delay(0xF);
  for(i=0; i<16; i++)          //??16?
  {
    Encoder_SCLK = 1;
    ABS_Encoder_Delay(0xF);
    if(Encode_Read_DO)wdata|=1;
    wdata<<=1;
    Encoder_SCLK = 0;
    ABS_Encoder_Delay(0xF);
  }
  wdata = wdata>>7;
  return(wdata);  
}

/*******************************��������****************************************
* ��������: void Get_ABSEncoder_Number(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ȡ���Ա��������ź�ֵ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void Get_ABSEncoder_Number(void)
{  
  ENC_ABS = ABS_Encoder_Read();
}


/*******************************��������****************************************
* ��������: void ABS_Encoder_Delay(__IO uint32_t nCount) 
* �������: __IO uint32_t nCount 
* ���ز���: void  
* ��    ��: ���Ա���������ʱ����  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/13
*******************************************************************************/ 
void ABS_Encoder_Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/*******************************��������****************************************
* ��������: void Incre_Encoder_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �������������ĳ�ʼ��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Incre_Encoder_Init(void)
{ 
  //ENC1 inital
  TIM1_Mode_Config();  
  //ENC2 inital_moni
	TIM3_Mode_Config();
  //ENC3 inital
	TIM4_Mode_Config();  
  //ENC4 inital
  TIM8_Mode_Config();
	//ENC5 inital
	ENC5_Mode_config();
	//ENC6 inital
	TIM5_Mode_config();
}

/*******************************��������****************************************
* ��������: void TIM1_Mode_Config(void)
* �������: void 
* ���ز���: void  
* ��    ��: ENC1�Ķ�ʱ��1 ��ʼ�� 
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void TIM1_Mode_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  //GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
  /* Configure PA.8,9 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  TIM_DeInit(TIM1);
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler =0;	     //����Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;      //����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration  �������� ����ģʽ
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM1->CNT =10000;
  TIM_Cmd(TIM1, ENABLE); 
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?��??��??��??0��? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//������??��??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//��1?����a2??D??�����̨�
  NVIC_Init(&NVIC_InitStructure); 
}

/*******************************��������****************************************
* ��������: uint16_t Get_ENC1_Number(void) 
* �������: void 
* ���ز���: void
* ��    ��: ��ȡ������1����ֵ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Get_ENC1_Number(void)
{
  ENC_NU[0] = TIM_GetCounter(TIM1);
}

/*******************************��������****************************************
* ��������: void TIM3_Mode_Config(void)
* �������: void 
* ���ز���: void  
* ��    ��: ENC2�Ķ�ʱ��2��ʼ�� 
* ��    ��: by Cao Jue
* ��    ��: 2015/12/18
*******************************************************************************/ 
void TIM3_Mode_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
  /* Configure PB.4,5 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
  TIM_DeInit(TIM3);
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler =0;	     //����Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;      //����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration  �������� ����ģʽ
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM3->CNT =10000;
  TIM_Cmd(TIM3, ENABLE); 
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?��??��??��??0��? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//������??��??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//��1?����a2??D??�����̨�
  NVIC_Init(&NVIC_InitStructure); 

}

/*******************************��������****************************************
* ��������: void Get_ENC2_Number(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ȡ������2����ֵ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Get_ENC2_Number(void)
{
  ENC_NU[1] = TIM_GetCounter(TIM3);
}



/*******************************��������****************************************
* ��������: void TIM4_Mode_Config(void)
* �������: void 
* ���ز���: void  
* ��    ��: ENC3����ӳ�䶨ʱ��4 ��ʼ�� 
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void TIM4_Mode_Config(void)
{
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
  /* Configure PD.12,13 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  TIM_DeInit(TIM4);
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising��?��y??2???
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM4->CNT =10000;																						//release  20151028
  TIM_Cmd(TIM4, ENABLE); 
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?��??��??��??0��? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//������??��??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//��1?����a2??D??�����̨�
  NVIC_Init(&NVIC_InitStructure); 
}

/*******************************��������****************************************
* ��������: void Get_ENC4_Number(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ȡ������4����ֵ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Get_ENC3_Number(void)
{
  ENC_NU[2] = TIM_GetCounter(TIM4);
}



/*******************************��������****************************************
* ��������: void TIM8_Mode_Config(void)
* �������: void 
* ���ز���: void  
* ��    ��: ENC4�Ķ�ʱ��8 ��ʼ�� �����ת�Ƶ�TIME3��
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void TIM8_Mode_Config(void)
{
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PC.6,7 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 
  TIM_DeInit(TIM8);
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //���ø�λ����
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration
  TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising��?��y??2???
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM8, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM8, TIM_FLAG_Update);
	//��������������ж�
  TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM8->CNT =10000;																			//release  20151028
  TIM_Cmd(TIM8, ENABLE); 
  //���ñ���������ж�
   NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?��??��??��??0��? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//������??��??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//��1?����a2??D??�����̨�
  NVIC_Init(&NVIC_InitStructure); 
}

/*******************************��������****************************************
* ��������: void Get_ENC3_Number(void) 
* �������: void 
* ���ز���: void 
* ��    ��: ��ȡ������4����ֵ  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Get_ENC4_Number(void)
{
  ENC_NU[3] =TIM_GetCounter(TIM8);
}

/*******************************��������****************************************
* ��������: void ENC5_Mode_config(void)
* �������: void 
* ���ز���: void  
* ��    ��: ENC5��ʼ���˿ڣ�����ģ��IO�ڽ������ݶ�ȡ  
* ��    ��: by Cao Jue
* ��    ��: 2015/12/18
*******************************************************************************/
void ENC5_Mode_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_10;          //PD.10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_11;						//PD.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//GPIOD.10 �ж����Լ��жϳ�ʼ������   �½��ش���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource10);
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;	//KEY2
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	//GPIOD.11	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 					//ʹ��PD.15���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure); 
	
}


/*******************************��������****************************************
* ��������: void TIM5_Mode_config(void)
* �������: void 
* ���ز���: void  
* ��    ��: ENC6�� ��ʱ��5 ��ʼ��
* ��    ��: by Cao Jue
* ��    ��: 2015/12/18
*******************************************************************************/
void TIM5_Mode_config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.0,1 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
  TIM_DeInit(TIM5);
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //���ø�λ����
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising��?��y??2???
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	//��������������ж�
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM5->CNT =10000;																			//release  20151028
  TIM_Cmd(TIM5, ENABLE); 
  //���ñ���������ж�
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?��??��??��??0��? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;			//������??��??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//��1?����a2??D??�����̨�
  NVIC_Init(&NVIC_InitStructure); 	
}

/*******************************��������****************************************
* ��������: void Get_ENC6_Number(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ȡ������6����ֵ  
* ��    ��: by Cao Jue
* ��    ��: 2015/12/18
*******************************************************************************/ 
void Get_ENC6_Number(void)
{
  ENC_NU[5] = TIM_GetCounter(TIM5);
}


/*******************************��������****************************************
* ��������:  Update_ENC1_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:   void
* ��    ��:   ���»�е����������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Update_ENC1_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[0];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************��������****************************************
* ��������:  Update_ENC2_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:   void
* ��    ��:   ���»�е����������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Update_ENC2_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[1];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************��������****************************************
* ��������:  Update_ENC3_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:   void
* ��    ��:   ���¹�����������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Update_ENC3_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[2];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************��������****************************************
* ��������:  Update_ENC4_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:   void
* ��    ��:   ���¹�����������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Update_ENC4_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[3];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************��������****************************************
* ��������:  Update_ENC5_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:  void
* ��    ��:  ���±���������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/10/29
*******************************************************************************/ 
void Update_ENC5_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
	uint16_t t=0;
  //t = 0x1234;	
  t=ENC5_COUNT;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}


/*******************************��������****************************************
* ��������:  Update_ENC6_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:  void
* ��    ��:  ���±���������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/10/29
*******************************************************************************/ 
void Update_ENC6_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
	uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[5];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************��������****************************************
* ��������:  Update_ABSEnc_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:   void
* ��    ��:   ���¾���ֵ����������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Update_ABSEnc_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_ABS;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}
