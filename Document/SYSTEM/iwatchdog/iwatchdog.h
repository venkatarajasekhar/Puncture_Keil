#ifndef __IWATCHDOG_H
#define __IWATCHDOG_H	 
#include "sys.h"

/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：IWatchDog
*
* 文件标识：iwatchdog.h
* 摘    要：独立看门狗程序
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/8/24
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

void IWatchDog_Init(void);
void Fedd_Watchdog(void);

#endif
