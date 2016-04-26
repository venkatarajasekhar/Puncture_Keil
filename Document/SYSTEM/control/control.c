#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "control.h"
#include "lcd.h"
#include "timer.h"
#include "led.h"
 u8 Set_Par=1;
 u16 Fre=30;
 s16 Duty=25;

 float Time_Run=0.5;
 float temp_c=0.0;
 u16 adcx_c=0;
 u8 Run_State =0;
 
 void key_handle( u8 key)
 {
//  KEY0----PE4   ---1; 
//	KEY1----PE3   ---2; 
//	KEY2----PE2   ---3;
//	Wake Up----PA0  ---4;
	 
	 //key0用于切换控制参数选项
   if(key==1)
	 {
		 /*
		 Set_Par:
		   1    :设置占空比
		   2    ：设置频率
		   3    ：设置往返时间		 
		 */
      Set_Par = Set_Par + 1;
		  if(Set_Par==4)
				 Set_Par = 1 ;
   }
	//根据不同的控制参数在lcd上面显示出来*
 switch(Set_Par)
			{
	      case 1:   LCD_ShowString(60,150,200,16,16,"*");	 
                  LCD_ShowString(60,170,200,16,16," ");	 
				          LCD_ShowString(60,190,200,16,16," ");	 
				    break;
				
				case 2:  LCD_ShowString(60,150,200,16,16," ");	 
                  LCD_ShowString(60,170,200,16,16,"*");	 
				          LCD_ShowString(60,190,200,16,16," ");	   
				    break;
				
				case 3:  	LCD_ShowString(60,150,200,16,16," ");	 
                  LCD_ShowString(60,170,200,16,16," ");	 
				          LCD_ShowString(60,190,200,16,16,"*");	  				
				    break;
				
				default:  
					  break;
			}

	//控制参数 + 或者 — 
	 if(key==4)
		{		 
		  switch(Set_Par)
			{
	      case 1:   Duty = Duty + 100; 
                  if(Duty >= 2300)
										Duty =2300;
				    break;
				
				case 2:   Fre = Fre +10 ; 
									if(Fre >= 130)
										Fre =130;
				    break;
				
				case 3:   Time_Run = Time_Run + 0.1;
									if(Time_Run >= 5.0)
									  Time_Run =5.0;									
				    break;
				
				default:  
					  break;
      }
		
		}else if(key==2)	
		{
			switch(Set_Par)
			{
	      case 1:   Duty = Duty - 100; 
                  if(Duty <= 50)
										Duty =50;				
				    break;
				
				case 2:   Fre = Fre - 10 ; 
									if(Fre <= 30)
										Fre =30;
				    break;
				
				case 3:   Time_Run = Time_Run - 0.1;
									if(Time_Run <= 0.1)
									  Time_Run = 0.1;		
				    break;
				
				default:  
					  break;
      }
		}	 
	//系统系统或者停止判断
		if(key==3)
		{
        Run_State += 1;
			  if(Run_State ==2)
					Run_State = 0;
    }
	//更新显示	
      LCD_ShowxNum(124,150,Duty,4,16,0);     	
	  	LCD_ShowxNum(124,170,Fre,4,16,0); 	  	
	  	temp_c = Time_Run;
	  	adcx_c = temp_c;
			LCD_ShowxNum(124,190,temp_c,1,16,0);     	
 			temp_c-=adcx_c;
			temp_c*=1000;
			LCD_ShowxNum(140,190,temp_c,3,16,0x80); 
		
		 switch(Run_State)
			{
	      case 0:   
				          LCD_ShowString(60,220,200,16,16,"    STOP");	 
				    break;
				
				case 1:   LCD_ShowString(60,220,200,16,16,"    RUN ");	 
				    break;			
				
				default:  
					  break;
			}
		
 }
 
 
 
 void key_handle_2( u8 key)
 {
//  KEY0----PE4   ---1; 
//	KEY1----PE3   ---2; 
//	KEY2----PE2   ---3;
//	Wake Up----PA0  ---4;
	 
   if(key==1)
	 {
		Duty = 25;
   }
	
	 if(key==2)
		{		 
		 	Duty = 1200;
		}	 
	//系统系统或者停止判断
		if(key==3)
		{
      Duty = 2200;
    }
	//更新显示	
      LCD_ShowxNum(124,150,Duty,4,16,0);     	
	  	LCD_ShowxNum(124,170,Fre,4,16,0); 	  	
	  	temp_c = Time_Run;
	  	adcx_c = temp_c;
			LCD_ShowxNum(124,190,temp_c,1,16,0);     	
 			temp_c-=adcx_c;
			temp_c*=1000;
			LCD_ShowxNum(140,190,temp_c,3,16,0x80); 
			
 }
 
 
 /*
 u8 Set_Par=1;
 u16 Fre=30;
 u16 Duty=10;
 float Time_Run=0.5;
 float temp_c=0.0;
 u16 adcx_c=0;
 u8 Run_State =0;
 
 void TIM4_PWM_Init(u16 arr,u16 psc,u16 pulse)
 */
 float arr_new=0;
 
 float pulse_new=0;
 u16  TIME3_COUNT= 50;
  u16 arr_int=0;
 u16 pulse_int=0;
void Para_Set(u8 key)
 {

	 if(Run_State==0)
	 {
		 arr_new = 72000.0/Fre ;
     pulse_int = (u16)(arr_new*0.5);
		 TIM_SetCompare1(TIM4,pulse_int); //停止，输出50%占空比
   }
	 if(key==2||key==3||key==4) 		//WKUP/KEY1/KEY2按下了
   {
    //计算新的PWM波形频率和占空比
     arr_new = 72000.0/Fre ;
		 pulse_new = arr_new*(Duty/100.0);
		 arr_int = (u16)(arr_new+0.5);
		 arr_int = arr_int-1;
		 pulse_int = (u16)(pulse_new);
		 TIME3_COUNT = Time_Run/0.01;
		 TIM4_PWM_Init(arr_int,0,pulse_int);
   }

 }
 
 
void Run_direction_control(void)
 {

	 
 }
//it is over
