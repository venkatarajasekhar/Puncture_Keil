#ifndef __DACOUTPUT_H
#define __DACOUTPUT_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�dac.h
*
* �ļ���ʶ��dac
* ժ    Ҫ��2·ģ���ѹ�����
*
*
* ��ǰ�汾��v1.0
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/10
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/
void DAC2_Init(void);
void DAC1_Init(void);
void Set_DAC2_Value(u16 vol);
void Set_DAC1_Value(u16 vol);

extern u16 dac1_value,dac2_value;
#endif

