#ifndef __SWITCH_SIGNAL_H
#define __SWITCH_SIGNAL_H	 
#include "sys.h"
#include <stdio.h>
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：switch.h
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

#define  SWITCH1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)
#define  SWITCH2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)
#define  SWITCH3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)
#define  SWITCH4  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)
#define  SWITCH5  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)
#define  SWITCH6  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)
#define  SWITCH7  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)
#define  SWITCH8  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)


#define SWITCH_OPTO1  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8)
#define SWITCH_OPTO2  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7)
#define SWITCH_OPTO3  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6)
#define SWITCH_OPTO4  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5)

/*
typedef struct bitStruct{
unsigned char switch1:1;
unsigned char switch2:1;
unsigned char switch3:1;
unsigned char switch4:1;
unsigned char switch5:1;
unsigned char switch6:1;
unsigned char switch7:1;
unsigned char switch8:1;
unsigned char total_value;
}SwitchStruct;
*/
typedef union bitStruct{
  struct 
  {
    unsigned char switch1:1;
    unsigned char switch2:1;
    unsigned char switch3:1;
    unsigned char switch4:1;
    unsigned char switch5:1;
    unsigned char switch6:1;
    unsigned char switch7:1;
    unsigned char switch8:1;
  }bit;
  unsigned char total_value;
}SwitchStruct;

extern SwitchStruct *pSwitchValue;

void SWITCH_IO_Init(void);
void SWITCH_IO_Detection(void);
void SWITCH_OPTP_Init(void);
void SWITCH_OPTO_Detection(void);

void Update_IO_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_OPTP_Value(uint8_t* pDesArr,uint8_t* pDesLength);
#endif

