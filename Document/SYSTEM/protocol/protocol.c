#include "protocol.h"
#include "crc16.h"
#include "relay.h"
#include "dac.h"
//#include "servo.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�protocol
*
* �ļ���ʶ��protocol.c
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

u8 test_send[10]={0};

/*******************************��������****************************************
* ��������: void Parsed_Data_FromPC(u8 *receivedata ,u16 DataCheckLen) 
* �������: u8 *receivedata ,u16 DataCheckLen
* ���ز���: void  
* ��    ��: ������PC�����յ�����ָ��  .
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/22
*******************************************************************************/ 
u8 Parsed_Data_FromPC(u8 *receivedata ,u16 DataCheckLen)
{
 u16 crc_result=0,crc_package=0;
 u8 contrast_result=0;
 //check the data packge by crc16 mothod
 crc_result = CRC16(receivedata,DataCheckLen,0xffff);
 //get the CRC16 data from the data package
 crc_package = (receivedata[DataCheckLen]<<8) | (receivedata[DataCheckLen+1]);
 //contrast the two CRC data
   contrast_result = (crc_package ==crc_result ? 1 : 0);
 //CRC check is correct
	return contrast_result;
 
}

/*******************************��������****************************************
* ��������:  SendDataToPC(u8 *usbSendBuf) 
* �������: u8 *usbSendBuf 
* ���ز���: void  
* ��    ��: ׼�����͸����Ե����ݰ�  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/22
*******************************************************************************/ 
void SendDataToPC(u8 *usbSendBufdata )
{
  u16 crc_result=0,stemp=0;
  //usbReceiveBuf[2]=0;
  usbSendBufdata[0]=0;  //high byte
  usbSendBufdata[1]=0;  //low byte
  usbSendBufdata[3]=RESEARCH_BOARD;  //type of control board
  //UpdateADNS9800(usbSendBuf);
  //UpdateMPU9250(usbSendBuf);
  usbSendBufdata[4]=0x00;
  usbSendBufdata[5]=0x01;
  crc_result = CRC16(usbSendBufdata,5,0xffff);
  stemp = crc_result;
  usbSendBufdata[6]=(u8)((stemp&0xFF00)>>8);  
  usbSendBufdata[5]=(u8)(stemp&0x00FF);  
  //USB_SendData(usbSendBuf,sizeof(usbSendBuf));
}

/*******************************��������****************************************
* ��������:  SendCRCDataToPC(u8 *usbSendBuf) 
* �������: u8 *usbSendBuf 
* ���ز���: void  
* ��    ��: ׼�����͸����Ե����ݰ�  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/22
*******************************************************************************/ 
void SendCRCDataToPC(u8 *usbSendBufdata, uint8_t* pDesLength)
{
  u16 crc_result=0,stemp=0;
  
  crc_result = CRC16(usbSendBufdata,(*pDesLength)+5,0xffff);
  stemp = crc_result;
	
	usbSendBufdata[(*pDesLength)+5] = (u8)((stemp&0xFF00)>>8);  
	usbSendBufdata[(*pDesLength)+6]  = (u8)(stemp&0x00FF);	

	
  //USB_SendData(usbSendBuf,sizeof(usbSendBuf));
}


/*******************************��������****************************************
* ��������: void Parse_Pack_Data(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ����������ݰ���������Ӧ�ı���  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_MotorA(u8 *usbReceiveBufdata)
{
	Timecount1 = 0;
	Duty1 = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	Duty1 = Duty1 > 2350 ? 2350 : Duty1;
	Duty1 = Duty1 < -2350 ? -2350 : Duty1;
	
}

/*******************************��������****************************************
* ��������: void Parse_Pack_Data(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ����������ݰ���������Ӧ�ı���  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_MotorB(u8 *usbReceiveBufdata)
{
	Timecount2 = 0;
	Duty2 = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	Duty2 = Duty2 > 2350 ? 2350 : Duty2;
	Duty2 = Duty2 < -2350 ? -2350 : Duty2;

}

/*******************************��������****************************************
* ��������: void Parse_Pack_Data(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ����������ݰ���������Ӧ�ı���  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_LED(u8 *usbReceiveBufdata)
{
	Timecount_RED = 0;
	LED_RED = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	LED_RED = LED_RED > 2399 ? 2399 : LED_RED;
	LED_RED = LED_RED < 0 ? 0 : LED_RED;
	
}

/*******************************��������****************************************
* ��������: void Parse_Pack_Data(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ����������ݰ���������Ӧ�ı���  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_RGB(u8 *usbReceiveBufdata)
{
	Timecount_RGB = 0;
	LED_R = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	LED_R = LED_R > 2399 ? 2399 : LED_R;
	LED_R = LED_R < 0 ? 0 : LED_R;
	
	LED_G = (s16)(usbReceiveBufdata[9]<<8|usbReceiveBufdata[10]);
	LED_G = LED_G > 2399 ? 2399 : LED_G;
	LED_G = LED_G < 0 ? 0 : LED_G;
	
	LED_B = (s16)(usbReceiveBufdata[11]<<8|usbReceiveBufdata[12]);
	LED_B = LED_B > 2399 ? 2399 : LED_B;
	LED_B = LED_B < 0 ? 0 : LED_B;
	
}
