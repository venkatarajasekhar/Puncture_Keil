#include "relay.h"
u8 relay1_status=0,relay2_status=0;
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�relay
*
* �ļ���ʶ��relay.c
* ժ    Ҫ���̵���������ʼ��
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/15
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

/*******************************��������****************************************
* ��������: void Relay_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: 5V�̵�������˿ڳ�ʼ��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Relay_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //��1?��PB,PE???������?��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;				 //LED0-->PB.5 ???��????
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //��?������?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO?��?��?��?a50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);					 //?��?Y����?��2?��y3?��??��GPIOB.5

  Relay1 = 1;
  Relay2 = 1;
}

/*******************************��������****************************************
* ��������: void Update_Relay_Status(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ���¼̵����Ŀ���״̬  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/12
*******************************************************************************/ 
void Update_Relay_Status(void)
{
  if(relay1_status==1)
  {Relay1 =0;}
  else
  {Relay1 =1;}
  
  if(relay2_status==1)
  {Relay2 =0;}
  else
  {Relay2 =1;}
}


