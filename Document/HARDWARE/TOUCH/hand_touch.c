#include "hand_touch.h"
#include "stdio.h"
#include "switch.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：hand_touch
*
* 文件标识：hand_touch.h
* 摘    要：手触摸板的初始化
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/7/15
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/
SwitchStruct switchvalue_touch;
SwitchStruct *pSwitchValue_touch = &switchvalue_touch;
/*******************************函数声明****************************************
* 函数名称: void Hand_Touch_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 手触摸板的端口初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Hand_Touch_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  GPIO_SetBits(GPIOF,GPIO_Pin_15);
  GPIO_SetBits(GPIOG,GPIO_Pin_0);
}

 /*******************************函数声明****************************************
 * 函数名称: void Hand_Touch_Detection(void) 
 * 输入参数: void 
 * 返回参数: void  
 * 功    能: 手触摸板信号读取  
 * 作    者: by Xu jinqi
 * 日    期: 2015/7/15
 *******************************************************************************/ 
 void Hand_Touch_Detection(void)
 {
   pSwitchValue_touch->bit.switch1 = TOUCH1_State;
   pSwitchValue_touch->bit.switch2 = TOUCH2_State;
  // printf("3:%d--4:%d\n",a,b); 
 }
 
/*******************************函数声明****************************************
* 函数名称:  Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新光电编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  u8 t=0;
  //t = 0x1234;	
  t=pSwitchValue_touch->total_value;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = t;  
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}

