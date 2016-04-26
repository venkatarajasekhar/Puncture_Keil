#ifndef __HANDTOUCH_H
#define __HANDTOUCH_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�hand_touch
*
* �ļ���ʶ��hand_touch.h
* ժ    Ҫ���ִ�����ĳ�ʼ��
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/15
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

#define TOUCH1_State  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15)
#define TOUCH2_State  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_0)

void Hand_Touch_Init(void);
 void Hand_Touch_Detection(void);
 void Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength);
#endif
