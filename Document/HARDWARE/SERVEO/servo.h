#ifndef __SERVO_H
#define __SERVO_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：servo
*
* 文件标识：servo.h
* 摘    要：数字舵机初始化
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/7/15
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

void Servo_Motor_Init(void);
void Set_Servo_Value(u16 duty);

extern u16 servo_value1,servo_value2;
#endif
