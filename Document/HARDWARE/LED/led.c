#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
s16 LED_RED = 0;
s16 LED_R = 0;
s16 LED_G = 0;
s16 LED_B = 0;


void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz

 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
}
 
/*******************************函数声明****************************************
* 函数名称:  	void LED_1W_Init(void)
* 输入参数:  	void
* 返回参数:   void
* 功    能:   初始化LED引脚
* 作    者: 	by Cao Jue
* 日    期: 	2016/03/18
*******************************************************************************/ 
void LED_RED_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 // TIM_Cmd(TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能TIMx外设
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB外设时钟使能
	
 
   //设置该引脚为复用输出功能,输出TIM4 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH4 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
 
	TIM_TimeBaseStructure.TIM_Period = 2399; //设置自动重装载周期值 30khz
	TIM_TimeBaseStructure.TIM_Prescaler =0; //设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2模式	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	//TIM_OCInitStructure.TIM_Pulse = 1250; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 低电平有效 
	//TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIMx
	//TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1 预装载使能
	
	
	
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  // TIM_OCInitStructure.TIM_Pulse = 24;
  // TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
  // TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = 0;
   TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx
  
	//DC_MOTOR_IO_Init();	
	
}


//RGB TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void LED_RGB_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    

  //设置该引脚为复用输出功能,输出TIM3 CH4 的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH4 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
	
   //设置该引脚为复用输出功能,输出TIM3 CH1 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
	//初始化TIM3 Channel2 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器

	//初始化TIM3 Channel4 PWM模式	 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

void SetLED_RED_Value(void)
{	
	if(Timecount_RED==16000)
	{  
    TIM_SetCompare3(TIM3,0);
  }
  else
	{
    TIM_SetCompare3(TIM3,LED_RED);
  }		 
}

void SetLED_RGB_Value(void)
{	
	if(Timecount_RGB==16000)
	{  
    TIM_SetCompare4(TIM3,0);
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM3,0);
  }
  else
	{
    TIM_SetCompare4(TIM3,LED_R);
		TIM_SetCompare1(TIM3,LED_G);
		TIM_SetCompare2(TIM3,LED_B);
		
  }		 
}

