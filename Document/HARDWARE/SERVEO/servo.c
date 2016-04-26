#include "servo.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：servo
*
* 文件标识：servo.c
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

u16 servo_value1=1250,servo_value2=0;
/*******************************函数声明****************************************
* 函数名称: void Servo_Motor_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 数字舵机的初始化，//1520us\333hz   900-2100us
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Servo_Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
  /****时钟配置----------------------------------------------------***/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    /****GPIO配置---------------------------------------------------***/
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /******* TIM3 配置 -----------------------------------------------*/  
  
  //50KZ:2499/575  ;300hz:95   ;400hz:71  ;72hz:399;  40hz:719  ;475hz:59
  TIM_TimeBaseStructure.TIM_Period = 2499;    //2499
  TIM_TimeBaseStructure.TIM_Prescaler = 71  ;   //71
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1250;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能的预装载寄存器
    
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  //使能定时器
  TIM_Cmd(TIM2, ENABLE); 
  
}

/*******************************函数声明****************************************
* 函数名称: void Set_Servo_Value(u16 duty) 
* 输入参数: u16 duty 
* 返回参数: void  
* 功    能: 改变数字舵机的角度  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Set_Servo_Value(u16 duty)
{
  TIM_SetCompare3(TIM2,duty);
}


