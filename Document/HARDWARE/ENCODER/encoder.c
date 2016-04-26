#include "encoder.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：encoder
*
* 文件标识：encoder.c
* 摘    要：各种编码的驱动代码
*
*
* 当前版本：
* 作    者：Xu jinqi
* 日    期：2015/7/13
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/
uint16_t ENC_NU[6]={0};
uint16_t ENC_ABS  =0;
/*******************************函数声明****************************************
* 函数名称: void ABS_Encoder_Init(void) 
* 输入参数: void 
* 返回参数: viod  
* 功    能: SSI信号的绝对编码器初始化配置  
* 作    者: by Xu jinqi
* 日    期: 2015/7/13
*******************************************************************************/ 
void ABS_Encoder_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG, ENABLE );
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
 //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//CS
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //CLK
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//DO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
  
  GPIO_SetBits(GPIOG,GPIO_Pin_1);
}

/*******************************函数声明****************************************
* 函数名称: int ABS_Encoder_Read(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 读取绝对编码器的信号值  
* 作    者: by Xu jinqi
* 日    期: 2015/7/13
*******************************************************************************/ 
int ABS_Encoder_Read(void)
{  
  int i=0;
  int	wdata=0;
  Encoder_CS = 1;
  ABS_Encoder_Delay(0xF);
  
  Encoder_CS = 0;
  ABS_Encoder_Delay(0xF);
  for(i=0; i<16; i++)          //??16?
  {
    Encoder_SCLK = 1;
    ABS_Encoder_Delay(0xF);
    if(Encode_Read_DO)wdata|=1;
    wdata<<=1;
    Encoder_SCLK = 0;
    ABS_Encoder_Delay(0xF);
  }
  wdata = wdata>>7;
  return(wdata);  
}

/*******************************函数声明****************************************
* 函数名称: void Get_ABSEncoder_Number(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 读取绝对编码器的信号值  
* 作    者: by Xu jinqi
* 日    期: 2015/7/13
*******************************************************************************/ 
void Get_ABSEncoder_Number(void)
{  
  ENC_ABS = ABS_Encoder_Read();
}


/*******************************函数声明****************************************
* 函数名称: void ABS_Encoder_Delay(__IO uint32_t nCount) 
* 输入参数: __IO uint32_t nCount 
* 返回参数: void  
* 功    能: 绝对编码器的延时函数  
* 作    者: by Xu jinqi
* 日    期: 2015/7/13
*******************************************************************************/ 
void ABS_Encoder_Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/*******************************函数声明****************************************
* 函数名称: void Incre_Encoder_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 增量光电编码器的初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Incre_Encoder_Init(void)
{ 
  //ENC1 inital
  TIM1_Mode_Config();  
  //ENC2 inital_moni
	TIM3_Mode_Config();
  //ENC3 inital
	TIM4_Mode_Config();  
  //ENC4 inital
  TIM8_Mode_Config();
	//ENC5 inital
	ENC5_Mode_config();
	//ENC6 inital
	TIM5_Mode_config();
}

/*******************************函数声明****************************************
* 函数名称: void TIM1_Mode_Config(void)
* 输入参数: void 
* 返回参数: void  
* 功    能: ENC1的定时器1 初始化 
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void TIM1_Mode_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  //GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
  /* Configure PA.8,9 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  TIM_DeInit(TIM1);
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler =0;	     //设置预分频
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;      //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration  编码配置 编码模式
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM1->CNT =10000;
  TIM_Cmd(TIM1, ENABLE); 
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?à??ó??è??0￡? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//×óó??è??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ê1?üía2??D??í¨μà
  NVIC_Init(&NVIC_InitStructure); 
}

/*******************************函数声明****************************************
* 函数名称: uint16_t Get_ENC1_Number(void) 
* 输入参数: void 
* 返回参数: void
* 功    能: 获取编码器1的数值  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Get_ENC1_Number(void)
{
  ENC_NU[0] = TIM_GetCounter(TIM1);
}

/*******************************函数声明****************************************
* 函数名称: void TIM3_Mode_Config(void)
* 输入参数: void 
* 返回参数: void  
* 功    能: ENC2的定时器2初始化 
* 作    者: by Cao Jue
* 日    期: 2015/12/18
*******************************************************************************/ 
void TIM3_Mode_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
  /* Configure PB.4,5 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
  TIM_DeInit(TIM3);
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler =0;	     //设置预分频
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;      //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration  编码配置 编码模式
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM3->CNT =10000;
  TIM_Cmd(TIM3, ENABLE); 
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?à??ó??è??0￡? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//×óó??è??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ê1?üía2??D??í¨μà
  NVIC_Init(&NVIC_InitStructure); 

}

/*******************************函数声明****************************************
* 函数名称: void Get_ENC2_Number(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 获取编码器2的数值  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Get_ENC2_Number(void)
{
  ENC_NU[1] = TIM_GetCounter(TIM3);
}



/*******************************函数声明****************************************
* 函数名称: void TIM4_Mode_Config(void)
* 输入参数: void 
* 返回参数: void  
* 功    能: ENC3的重映射定时器4 初始化 
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void TIM4_Mode_Config(void)
{
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
  /* Configure PD.12,13 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  TIM_DeInit(TIM4);
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Risingé?éy??2???
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM4->CNT =10000;																						//release  20151028
  TIM_Cmd(TIM4, ENABLE); 
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?à??ó??è??0￡? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//×óó??è??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ê1?üía2??D??í¨μà
  NVIC_Init(&NVIC_InitStructure); 
}

/*******************************函数声明****************************************
* 函数名称: void Get_ENC4_Number(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 获取编码器4的数值  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Get_ENC3_Number(void)
{
  ENC_NU[2] = TIM_GetCounter(TIM4);
}



/*******************************函数声明****************************************
* 函数名称: void TIM8_Mode_Config(void)
* 输入参数: void 
* 返回参数: void  
* 功    能: ENC4的定时器8 初始化 （亦可转移到TIME3）
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void TIM8_Mode_Config(void)
{
  //u16 CCR1_Val = 2500;
  //u16 CCR2_Val = 1000;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PC.6,7 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 
  TIM_DeInit(TIM8);
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //设置复位周期
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //不分频
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration
  TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Risingé?éy??2???
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM8, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM4, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM8, TIM_FLAG_Update);
	//开启编码器溢出中断
  TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM8->CNT =10000;																			//release  20151028
  TIM_Cmd(TIM8, ENABLE); 
  //配置编码器溢出中断
   NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?à??ó??è??0￡? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//×óó??è??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ê1?üía2??D??í¨μà
  NVIC_Init(&NVIC_InitStructure); 
}

/*******************************函数声明****************************************
* 函数名称: void Get_ENC3_Number(void) 
* 输入参数: void 
* 返回参数: void 
* 功    能: 获取编码器4的数值  
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Get_ENC4_Number(void)
{
  ENC_NU[3] =TIM_GetCounter(TIM8);
}

/*******************************函数声明****************************************
* 函数名称: void ENC5_Mode_config(void)
* 输入参数: void 
* 返回参数: void  
* 功    能: ENC5初始化端口，采用模拟IO口进行数据读取  
* 作    者: by Cao Jue
* 日    期: 2015/12/18
*******************************************************************************/
void ENC5_Mode_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_10;          //PD.10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //上拉输入
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_11;						//PD.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //上拉输入
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//GPIOD.10 中断线以及中断初始化配置   下降沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource10);
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;	//KEY2
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	//GPIOD.11	  中断线以及中断初始化配置 下降沿触发 //KEY1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 					//使能PD.15所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 
	
}


/*******************************函数声明****************************************
* 函数名称: void TIM5_Mode_config(void)
* 输入参数: void 
* 返回参数: void  
* 功    能: ENC6的 定时器5 初始化
* 作    者: by Cao Jue
* 日    期: 2015/12/18
*******************************************************************************/
void TIM5_Mode_config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  /*----------------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.0,1 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*----------------------------------------------------------------*/	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
  TIM_DeInit(TIM5);
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //设置复位周期
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //不分频
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  /*-----------------------------------------------------------------*/
  //encode configuration
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Risingé?éy??2???
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;       
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	//开启编码器溢出中断
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 
  //Reset counter
  TIM5->CNT =10000;																			//release  20151028
  TIM_Cmd(TIM5, ENABLE); 
  //配置编码器溢出中断
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//?à??ó??è??0￡? 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;			//×óó??è??1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ê1?üía2??D??í¨μà
  NVIC_Init(&NVIC_InitStructure); 	
}

/*******************************函数声明****************************************
* 函数名称: void Get_ENC6_Number(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 获取编码器6的数值  
* 作    者: by Cao Jue
* 日    期: 2015/12/18
*******************************************************************************/ 
void Get_ENC6_Number(void)
{
  ENC_NU[5] = TIM_GetCounter(TIM5);
}


/*******************************函数声明****************************************
* 函数名称:  Update_ENC1_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新机械编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_ENC1_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[0];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************函数声明****************************************
* 函数名称:  Update_ENC2_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新机械编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_ENC2_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[1];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************函数声明****************************************
* 函数名称:  Update_ENC3_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新光电编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_ENC3_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[2];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************函数声明****************************************
* 函数名称:  Update_ENC4_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新光电编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_ENC4_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[3];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************函数声明****************************************
* 函数名称:  Update_ENC5_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:  void
* 功    能:  更新编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/10/29
*******************************************************************************/ 
void Update_ENC5_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
	uint16_t t=0;
  //t = 0x1234;	
  t=ENC5_COUNT;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}


/*******************************函数声明****************************************
* 函数名称:  Update_ENC6_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:  void
* 功    能:  更新编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/10/29
*******************************************************************************/ 
void Update_ENC6_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
	uint16_t t=0;
  //t = 0x1234;	
  t=ENC_NU[5];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}

/*******************************函数声明****************************************
* 函数名称:  Update_ABSEnc_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* 输入参数:  uint8_t* pDesArr,uint8_t* pDesLength
* 返回参数:   void
* 功    能:   更新绝对值编码器进入usbsendbuffer
* 作    者: by Xu jinqi
* 日    期: 2015/7/15
*******************************************************************************/ 
void Update_ABSEnc_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  uint16_t t=0;
  //t = 0x1234;	
  t=ENC_ABS;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

  pDesArr[4]=*pDesLength;
}
