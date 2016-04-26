#ifndef __HANDTOUCH_H
#define __HANDTOUCH_H	 
#include "sys.h"
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

#define TOUCH1_State  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15)
#define TOUCH2_State  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_0)

void Hand_Touch_Init(void);
 void Hand_Touch_Detection(void);
 void Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength);
#endif
