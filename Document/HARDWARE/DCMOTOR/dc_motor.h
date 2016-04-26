#ifndef __DC_MOTOR_H
#define __DC_MOTOR_H	 
#include "sys.h"

#define Flaut_State  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//读取按键7
#define OTW_State  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//读取按键7

#define ResetAB PBout(14)// PB5
#define ResetCD PBout(15)// PB5



void DC_Motor_Init(void);
void DC_MOTOR_System_Init(void);
void DC_MOTOR_PWM_Init(void);
void DC_MOTOR_Clockwise(void);
void DC_MOTOR_Anticlockwise(void);
void DC_MOTOR_IO_Init(void);
void DC_MOTOR_IS_Alarm(void);
void Reset_Motor(void);
void get_target_value(void);
void MotorSaturation(float *Data,float max,float min);
void P_motor_control(void);
void send_motor_pwm(void);
void Motor_control(void);
void Motor_state(void);
void stop_motor_pwm(void);
void motor_led_alarm(void);

#endif
