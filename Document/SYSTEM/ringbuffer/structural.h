#ifndef _STRUCTUAL_H
#define _STRUCTUAL_H
#ifdef __cplusplus
extern "C" {
#endif
  
  /* Private define ---------------------------------------------------------*/ 
  //#define BufferSize       6
#define BufferSize_RX       11  
#define BufferSize_Tx     10   
  /* Private structure ---------------------------------------------------------*/
  
  /**************接收遥控器数据****************/    
  typedef struct {
    float Roll;	        //调控范围：860---2180   中间值：1520
    float Pitch;	        //调控范围：860---2180   中间值：1525
    float Throttle;	//调控范围：860---2180  
    float Yaw;		//调控范围：860---2180   中间值：1523 
    float Switch_A;      // "A" :push:640---pull:2400
    float Switch_G;    //"B" :push:640---pull:2400
    float Switch_E;  // "C" :push:635---Mid:1520---pull:2405
    float Switch_F;   //"F" :push:635---pull:2405
    float Knob;
  }d_ReceiverData_Raw;
  
  /**************增稳积分****************/
  typedef struct {
    float Roll;
    float Pitch;
    float Yaw;
  }d_Theta;
  
  /**************电机输出****************/
  typedef struct{
    s16 F;
    s16 B;
    s16 L;
    s16 R;
    s16 FL_Ail;
    s16 FR_Ail;
    s16 BL_Ail;
    s16 BR_Ail;
  }d_Motor;
  
  /**************Gyro数组****************/
  typedef struct{
    uint16_t Roll[20];
    uint16_t Pitch[20];
    uint16_t Yaw[20];
  }d_temp_gyro;
  
  /****************AHRS GYRO数组**********/
  
  typedef struct{
    s16 Roll[20];
    s16 Pitch[20];
    s16 Yaw[20];
  }d_temp_gyro_AHRS;
  
  /**************Acc数组****************/
  typedef struct{
    uint16_t XAcc[20];
    uint16_t YAcc[20];
    uint16_t ZAcc[20];
  }d_temp_acc;
  /**************Mag数组****************/
  typedef struct{
    s16 Mag_X[20];
    s16 Mag_Y[20];
    s16 Mag_Z[20];
  }d_temp_mag;
  
  /**************滤波后的Gyro的原始数据****************/
  typedef struct Gyro{
    float Roll;
    float Pitch;
    float Yaw;
  }GyroRaw;
  /**************滤波后的Acc的原始数据****************/
  typedef struct Accel {
    float XAcc;
    float YAcc;
    float ZAcc;
  }Accraw;
  /**************Mag原始数据****************/
  typedef struct {
    s16 Mag_X;
    s16 Mag_Y;
    s16 Mag_Z;
  }d_Mag;
  
  /**************Gyro的零点****************/
  typedef struct{
    uint16_t Roll;
    uint16_t Pitch;
    uint16_t Yaw;
  }d_GyoZero;
  /***************AHRS GYRO零点************/
  typedef struct{
    s16 Roll;
    s16 Pitch;
    s16 Yaw;
  }d_GyoZero_AHRS;
  /**************Acc的零点****************/
  typedef struct{
    uint16_t XAcc;
    uint16_t YAcc;
    uint16_t ZAcc;
  }d_AccZero;
  
  /**************去除零点的Gyro****************/
  typedef struct{
    short Roll;
    short Pitch;
    short Yaw;
  }d_GyoZeroed;
  /**************去除零点的Acc****************/
  typedef struct{
    short XAcc;
    short YAcc;
    short ZAcc;
  }d_AccZeroed;
  /**************转化为标准单位的Gyro****************/
  typedef struct{
    float Roll;
    float Pitch;
    float Yaw;
  }d_StandardizedGyroFeedback;
  /**************转化为标准单位的Acc****************/
  typedef struct{
    float XAcc;
    float YAcc;
    float ZAcc;
  }d_StandardizedAccFeedback;
  /**************姿态控制的目标值****************/
  typedef struct{
    float Roll;
    float Pitch;
    float Yaw;
  }d_Attitude_Reference;
  
  /**************增稳控制的目标值****************/
  typedef struct{
    float Roll;
    float Pitch;
    float Yaw;
    float Throttle;
  }d_Stabilize_Reference;
  
  /**************去除零点后的遥控器值****************/
  typedef struct{
    short Roll;	
    short Throttle;
    short Pitch;	
    short Yaw;		
    unsigned char Ch5;		
    unsigned char Ch6;		
  }d_Propodata_Zeroed;
  
  typedef struct{
    s16 BMP_Altitude;
    s16 Zacc;
    s16 Altitude_Ref;
    s16 Altitude_ControlU;
    s16 Sim_Al;
    s16 Sim_Acc;
  }d_Altitudedata_From_Master;
  typedef struct{
    float Rollrate;
    float Roll;
    float XAcc;
    float Pitchrate;
    float Pitch;
    float YAcc;
    float Yaw;
  }d_Kalman_Simulation;
  
  typedef struct{
    float Xacc;
    float Yacc;
    float Zacc;
    float RollRate;
    float PitchRate;
    float YawRate;
    float magX;
    float magY;
    float magZ;
    float Roll;
    float Pitch;
    float Yaw;
    float Latitude;
    float Longitude;
    float Altitude;
    float Velocity_X;
    float Velocity_Y;
    float Velocity_Z;
  }IMU_Data;

#ifdef __cplusplus
}
#endif

#endif
