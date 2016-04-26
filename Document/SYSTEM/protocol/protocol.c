#include "protocol.h"
#include "crc16.h"
#include "relay.h"
#include "dac.h"
//#include "servo.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：protocol
*
* 文件标识：protocol.c
* 摘    要：数据协议包定义、解析文件
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/7/22
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

u8 test_send[10]={0};

/*******************************函数声明****************************************
* 函数名称: void Parsed_Data_FromPC(u8 *receivedata ,u16 DataCheckLen) 
* 输入参数: u8 *receivedata ,u16 DataCheckLen
* 返回参数: void  
* 功    能: 解析从PC机接收的数据指令  .
* 作    者: by Xu jinqi
* 日    期: 2015/7/22
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

/*******************************函数声明****************************************
* 函数名称:  SendDataToPC(u8 *usbSendBuf) 
* 输入参数: u8 *usbSendBuf 
* 返回参数: void  
* 功    能: 准备发送给电脑的数据包  
* 作    者: by Xu jinqi
* 日    期: 2015/7/22
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

/*******************************函数声明****************************************
* 函数名称:  SendCRCDataToPC(u8 *usbSendBuf) 
* 输入参数: u8 *usbSendBuf 
* 返回参数: void  
* 功    能: 准备发送给电脑的数据包  
* 作    者: by Xu jinqi
* 日    期: 2015/7/22
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


/*******************************函数声明****************************************
* 函数名称: void Parse_Pack_Data(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 将具体的数据包解析到相应的变量  
* 作    者: by Xu jinqi
* 日    期: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_MotorA(u8 *usbReceiveBufdata)
{
	Timecount1 = 0;
	Duty1 = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	Duty1 = Duty1 > 2350 ? 2350 : Duty1;
	Duty1 = Duty1 < -2350 ? -2350 : Duty1;
	
}

/*******************************函数声明****************************************
* 函数名称: void Parse_Pack_Data(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 将具体的数据包解析到相应的变量  
* 作    者: by Xu jinqi
* 日    期: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_MotorB(u8 *usbReceiveBufdata)
{
	Timecount2 = 0;
	Duty2 = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	Duty2 = Duty2 > 2350 ? 2350 : Duty2;
	Duty2 = Duty2 < -2350 ? -2350 : Duty2;

}

/*******************************函数声明****************************************
* 函数名称: void Parse_Pack_Data(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 将具体的数据包解析到相应的变量  
* 作    者: by Xu jinqi
* 日    期: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data_LED(u8 *usbReceiveBufdata)
{
	Timecount_RED = 0;
	LED_RED = (u16)(usbReceiveBufdata[7]<<8|usbReceiveBufdata[8]);
	LED_RED = LED_RED > 2399 ? 2399 : LED_RED;
	LED_RED = LED_RED < 0 ? 0 : LED_RED;
	
}

/*******************************函数声明****************************************
* 函数名称: void Parse_Pack_Data(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 将具体的数据包解析到相应的变量  
* 作    者: by Xu jinqi
* 日    期: 2015/8/12
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
