#ifndef __SERVO_H
#define __SERVO_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�servo
*
* �ļ���ʶ��servo.h
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

void Servo_Motor_Init(void);
void Set_Servo_Value(u16 duty);

extern u16 servo_value1,servo_value2;
#endif
