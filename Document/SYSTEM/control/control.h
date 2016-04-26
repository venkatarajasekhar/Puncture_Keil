#ifndef __CONTROL_H
#define __CONTROL_H	 
#include "sys.h"


 void key_handle( u8 key);
 void Para_Set(u8 key);
 void Run_direction_control(void);
  void key_handle_2( u8 key);
 extern u8 Set_Par;
 extern u16 Fre;
 extern s16 Duty;
 extern float Time_Run;
 extern u16  TIME3_COUNT;
 extern u8 Run_State;
#endif
