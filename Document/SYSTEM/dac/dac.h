#ifndef __DACOUTPUT_H
#define __DACOUTPUT_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：dac.h
*
* 文件标识：dac
* 摘    要：2路模拟电压量输出
*
*
* 当前版本：v1.0
* 作    者：Xu jinqi
* 日    期：2015/7/10
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/
void DAC2_Init(void);
void DAC1_Init(void);
void Set_DAC2_Value(u16 vol);
void Set_DAC1_Value(u16 vol);

extern u16 dac1_value,dac2_value;
#endif

