#ifndef __RELAY_H
#define __RELAY_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�relay
*
* �ļ���ʶ��relay.h
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

#define Relay2 PEout(15)
#define Relay1 PEout(14)

extern u8 relay1_status,relay2_status;

void Relay_Init(void);
void Update_Relay_Status(void);
#endif
