#include "time_user.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：Time_user
*
* 文件标识：
* 摘    要：设置定时器参数，用于定时等功能
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/7/13
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

/*******************************函数声明****************************************
* 函数名称: void Time_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 设置定时器参数  
* 作    者: by Xu jinqi
* 日    期: 2015/7/13
*******************************************************************************/ 
void Time_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
  NVIC_InitTypeDef NVIC_InitStructure; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  /****设置time5.AD数据获取时间  2000HZ **************************************/
  TIM_TimeBaseStructure.TIM_Period = 90;  //90
  TIM_TimeBaseStructure.TIM_Prescaler = 399;  //399
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化定时器2
  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //开定时器中断
  TIM_Cmd(TIM2, ENABLE); //使能定时器5
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
  
 
  
}

