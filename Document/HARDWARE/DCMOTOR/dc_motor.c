#include "dc_motor.h"
#include "sys.h" 
//#include "control.h"
#include "delay.h"
#include "led.h"
extern u16 led_count;
 
u8 warning_type=0;
s16 target_value1=0;
s16 target_value2=0;
float P_coeff = 0.15;
float control_value1 = 0;
float control_value2 = 0;
float control_u=0;
float control_motor1 = 0;
float control_motor2 = 0;
float control_different = 0.0;
s16 motor_duty1 = 0;
s16 motor_duty2 = 0;
s16 Duty1=25;
s16 Duty2=25;

extern uint16_t Timecount1;
extern uint16_t Timecount2;

void DC_Motor_Init(void)
{
  DC_MOTOR_System_Init(); 
	ResetAB=0;
	ResetCD=0;
	delay_ms(10);
	DC_MOTOR_PWM_Init();
	ResetAB=1;
	ResetCD=1;
	delay_ms(10);
}

void DC_MOTOR_PWM_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 // TIM_Cmd(TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能TIMx外设
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB外设时钟使能
	
 
   //设置该引脚为复用输出功能,输出TIM4 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
 
	TIM_TimeBaseStructure.TIM_Period = 2399; //设置自动重装载周期值 30khz
	TIM_TimeBaseStructure.TIM_Prescaler =0; //设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2模式	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 24; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 低电平有效 
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIMx
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1 预装载使能
	
	
	
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 24;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 24;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 24;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIMx
  
	//DC_MOTOR_IO_Init();
}

void DC_MOTOR_IO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //??AFIO??
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //??JTAG??  	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PB.5 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
    //GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.5 输出高
    //GPIO_ResetBits(GPIOB,GPIO_Pin_14); 						 //PE.5 输出高 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7;				 //LED0-->PB.5 端口配置
    //
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //推挽输出

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
}


void Reset_Motor(void)
{
    delay_ms(100);
    ResetAB=1;
    ResetCD=1;	
    delay_ms(100);
    ResetAB=0;
    ResetCD=0;	
    delay_ms(100);
    ResetAB=1;
    ResetCD=1;	
}



void DC_MOTOR_IS_Alarm(void)
{
    if(OTW_State==0)
    {
        warning_type |= 0x01;
    }
    else
    {
        warning_type &= 0xfE;
    }

    if(Flaut_State==0)
    {
        warning_type |= 0x02;
    }
    else
    {
        warning_type &= 0xfD;
    }

}
void DC_MOTOR_System_Init(void)
{
  //reset 引脚初始化
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 |GPIO_Pin_15;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

//otw falut 引脚初始化
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
		
}


void DC_MOTOR_Clockwise(void)
{
	
    DC_MOTOR_IS_Alarm();
    //if(warning_type!=0)
    if(0)
    {
        TIM_SetCompare1(TIM3,0);
        TIM_SetCompare2(TIM3,0);
        Reset_Motor();
        delay_ms(1000);
    }
    else
    {
        if(Timecount1>=3)
        {
            Duty1=0;
            TIM_SetCompare1(TIM3,Duty1);
            TIM_SetCompare2(TIM3,Duty1);
        }
        else
        { 
            TIM_SetCompare1(TIM3,Duty1);
            TIM_SetCompare2(TIM3,24);
        }

    }
}

void DC_MOTOR_Anticlockwise(void)
{
    //GPIO_SetBits(GPIOB,GPIO_Pin_14);						 //PB.5 输出高
    //GPIO_ResetBits(GPIOB,GPIO_Pin_13); 						 //PE.5 输出高 
    TIM_SetCompare1(TIM3,24);
    TIM_SetCompare2(TIM3,Duty1);

}



void get_target_value(void)
{
	if(Timecount1==16000)
	{
		target_value1 = 0;
		//target_value2 = 0;
	}
	else
	{
		target_value1 =(s16)(Duty1);
	}
	if(Timecount2==16000)
	{
		//target_value1 = 0;
		target_value2 = 0;
	}
	else
	{
		target_value2 =(s16)(Duty2);
	}		

}

void MotorSaturation(float *Data,float max,float min)
{
	*Data = *Data > max ? max : *Data;
	*Data = *Data < min ? min : *Data;
}


void Motor_control(void)
{
  switch(warning_type)
	{
		case 0x00 :
								stop_motor_pwm();
								motor_led_alarm();
								Reset_Motor();
								break;
		case 0x01 :
								stop_motor_pwm();
								motor_led_alarm();
								Reset_Motor();
								break;
		case 0x02 :
								stop_motor_pwm();
								motor_led_alarm();
								Reset_Motor();
								break;
		case 0x03 :
								P_motor_control();            
								break;
		default:     ;
	}
	
}



void P_motor_control(void)
{
	get_target_value();
	
	control_different = target_value1         -    control_motor1;
	control_u         = control_different     *    P_coeff;
	control_motor1    = control_motor1        +    control_u;
	
	control_different = 0;
	control_u = 0;
	
	control_different = target_value2         -    control_motor2;
	control_u         = control_different     *    P_coeff;
	control_motor2    = control_motor2        +    control_u;
	
	control_different = 0;
	control_u = 0;
	
	MotorSaturation(&control_motor1,2450.0,-2450.0);
	MotorSaturation(&control_motor2,2450.0,-2450.0);
	
	send_motor_pwm();
}


void send_motor_pwm(void)
{	
	motor_duty1 = (s16)control_motor1;
	motor_duty2 = (s16)control_motor2;
	
  if(motor_duty1 >= 0) 
	{	
		TIM_SetCompare3(TIM4,24);
		TIM_SetCompare4(TIM4,motor_duty1);
  }
  else
	{
		TIM_SetCompare3(TIM4,0-motor_duty1);
		TIM_SetCompare4(TIM4,24);
  }		
	
	if(motor_duty2 >= 0) 
	{	
		TIM_SetCompare1(TIM4,24);
		TIM_SetCompare2(TIM4,motor_duty2);
  }
  else
	{
		TIM_SetCompare1(TIM4,0-motor_duty2);
		TIM_SetCompare2(TIM4,24);
  }

}


 void Motor_state(void)
{
  if(OTW_State==1)
	{
    warning_type |= 0x01;
  }
	else
	{
   warning_type &= 0xfE;
  }
		
	if(Flaut_State==1)
	{
    warning_type |= 0x02;
  }
	else
	{
   warning_type &= 0xfD;
  }

}


void stop_motor_pwm(void)
{	
   
   TIM_SetCompare3(TIM4,0);
	 TIM_SetCompare4(TIM4,0);
}


void motor_led_alarm(void)
{
   if(led_count==200)
	 {
      led_count=0;
	    LED = !LED;
   }

}
