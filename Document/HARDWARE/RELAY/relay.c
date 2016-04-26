#include "relay.h"
u8 relay1_status=0,relay2_status=0;
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：relay
*
* 文件标识：relay.c
* 摘    要：继电器驱动初始化
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/7/15
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

/*******************************函数声明****************************************
* 函数名称: void Relay_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 5V继电器输出端口初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Relay_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ê1?üPB,PE???úê±?ó
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;				 //LED0-->PB.5 ???ú????
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //í?íìê?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO?ú?ù?è?a50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);					 //?ù?Yéè?¨2?êy3?ê??ˉGPIOB.5

  Relay1 = 1;
  Relay2 = 1;
}

/*******************************函数声明****************************************
* 函数名称: void Update_Relay_Status(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 更新继电器的开关状态  
* 作    者: by Xu jinqi
* 日    期: 2015/8/12
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


