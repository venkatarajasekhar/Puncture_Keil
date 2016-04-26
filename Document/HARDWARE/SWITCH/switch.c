#include "switch.h"
#include "stdio.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：switch.c
*
* 文件标识：switch
* 摘    要：开关量信号采集
*
*
* 当前版本：v1.0
* 作    者：Xu jinqi
* 日    期：2015/7/10
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

SwitchStruct switchvalue;
SwitchStruct *pSwitchValue = &switchvalue;

SwitchStruct switchvalue_optp;
SwitchStruct *pSwitchValue_optp = &switchvalue_optp;
/*******************************函数声明****************************************
* 函数名称: void SWITCH_IO_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 开关量引脚初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/10
*******************************************************************************/ 
void SWITCH_IO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF , ENABLE);	 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_Init(GPIOF, &GPIO_InitStructure);	 
}

/*******************************函数声明****************************************
* 函数名称: void SWITCH_IO_Detection(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 8路开关量信号采集  
* 作    者: by Xu jinqi
* 日    期: 2015/7/10
*******************************************************************************/ 
void SWITCH_IO_Detection(void)
{
  pSwitchValue->bit.switch1 = SWITCH1;
  pSwitchValue->bit.switch2 = SWITCH2;
  pSwitchValue->bit.switch3 = SWITCH3;
  pSwitchValue->bit.switch4 = SWITCH4;
  pSwitchValue->bit.switch5 = SWITCH5;
  pSwitchValue->bit.switch6 = SWITCH6;
  pSwitchValue->bit.switch7 = SWITCH7;
  pSwitchValue->bit.switch8 = SWITCH8;
}

/*******************************函数声明****************************************
* 函数名称: void SWITCH_OPTP_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 光电开光初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void SWITCH_OPTP_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  GPIO_SetBits(GPIOG,GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5);
	
}

/*******************************函数声明****************************************
* 函数名称:  SWITCH_OPTO_Detection() 
* 输入参数:  void
* 返回参数:   void
* 功    能:   读取光电开关的信号值
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void SWITCH_OPTO_Detection(void)
{
  pSwitchValue_optp->bit.switch1 = SWITCH_OPTO1;
  pSwitchValue_optp->bit.switch2 = SWITCH_OPTO2;
	pSwitchValue_optp->bit.switch3 = SWITCH_OPTO3;
	pSwitchValue_optp->bit.switch4 = SWITCH_OPTO4;
 // switch_state1 = SWITCH_OPTO1;
 // switch_state2 = SWITCH_OPTO2;
  // printf("1:%d--2:%d\n",switch_state1,switch_state2);
}


/*******************************函数声明****************************************
* 函数名称:  Update_IO_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新IO开关量数据进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_IO_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  u8 t=0;
  //t = 0x1234;	
  t=pSwitchValue->total_value;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = t;  
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}

/*******************************函数声明****************************************
* 函数名称:  Update_OPTP_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新光电编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_OPTP_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  u8 t=0;
  //t = 0x1234;	
  t=pSwitchValue_optp->total_value;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = t;  
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}



