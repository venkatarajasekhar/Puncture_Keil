#ifndef __PROTOCOL_H
#define __PROTOCOL_H	 
#include "sys.h"
#include "stm32f10x_it.h"
#include "dc_motor.h"
#include "led.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�protocol
*
* �ļ���ʶ��protocol.h
* ժ    Ҫ������Э������塢�����ļ�
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/22
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/


#define RESEARCH_BOARD 0x30
#define GreenBoard     0x10
#define BlackBoard     0x00

#define ReadDateToPC   0x01

extern uint16_t Timecount1;
extern uint16_t Timecount2;
extern s16 LED_RED;
extern s16 LED_R;
extern s16 LED_G;
extern s16 LED_B;
extern s16 Duty1;
extern s16 Duty2;

u8 Parsed_Data_FromPC(u8 *receivedata ,u16 DataCheckLen);
void SendDataToPC(u8 *usbSendBuf );
void SendCRCDataToPC(u8 *usbSendBufdata, uint8_t* pDesLength);
void Parse_Pack_Data_MotorA(u8 *usbReceiveBufdata);
void Parse_Pack_Data_MotorB(u8 *usbReceiveBufdata);
void Parse_Pack_Data_LED(u8 *usbReceiveBufdata);
void Parse_Pack_Data_RGB(u8 *usbReceiveBufdata);

#endif
