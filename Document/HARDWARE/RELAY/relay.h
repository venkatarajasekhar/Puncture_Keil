#ifndef __RELAY_H
#define __RELAY_H	 
#include "sys.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：relay
*
* 文件标识：relay.h
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

#define Relay2 PEout(15)
#define Relay1 PEout(14)

extern u8 relay1_status,relay2_status;

void Relay_Init(void);
void Update_Relay_Status(void);
#endif
