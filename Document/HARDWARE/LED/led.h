#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
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

#define LED PEout(5)// PE5	


extern uint16_t Timecount_RED;
extern uint16_t Timecount_RGB;

void LED_Init(void);//��ʼ��
void LED_RED_Init(void);
void LED_RGB_Init(u16 arr,u16 psc);
void SetLED_RED_Value(void);
void SetLED_RGB_Value(void); 				    
#endif
