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
  
  /**************����ң��������****************/    
  typedef struct {
    float Roll;	        //���ط�Χ��860---2180   �м�ֵ��1520
    float Pitch;	        //���ط�Χ��860---2180   �м�ֵ��1525
    float Throttle;	//���ط�Χ��860---2180  
    float Yaw;		//���ط�Χ��860---2180   �м�ֵ��1523 
    float Switch_A;      // "A" :push:640---pull:2400
    float Switch_G;    //"B" :push:640---pull:2400
    float Switch_E;  // "C" :push:635---Mid:1520---pull:2405
    float Switch_F;   //"F" :push:635---pull:2405
    float Knob;
  }d_ReceiverData_Raw;
  
  /**************���Ȼ���****************/
  typedef struct {
    float Roll;
    float Pitch;
    float Yaw;
  }d_Theta;
  
  /**************������****************/
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
  
  /**************Gyro����****************/
  typedef struct{
    uint16_t Roll[20];
    uint16_t Pitch[20];
    uint16_t Yaw[20];
  }d_temp_gyro;
  
  /****************AHRS GYRO����**********/
  
  typedef struct{
    s16 Roll[20];
    s16 Pitch[20];
    s16 Yaw[20];
  }d_temp_gyro_AHRS;
  
  /**************Acc����****************/
  typedef struct{
    uint16_t XAcc[20];
    uint16_t YAcc[20];
    uint16_t ZAcc[20];
  }d_temp_acc;
  /**************Mag����****************/
  typedef struct{
    s16 Mag_X[20];
    s16 Mag_Y[20];
    s16 Mag_Z[20];
  }d_temp_mag;
  
  /**************�˲����Gyro��ԭʼ����****************/
  typedef struct Gyro{
    float Roll;
    float Pitch;
    float Yaw;
  }GyroRaw;
  /**************�˲����Acc��ԭʼ����****************/
  typedef struct Accel {
    float XAcc;
    float YAcc;
    float ZAcc;
  }Accraw;
  /**************Magԭʼ����****************/
  typedef struct {
    s16 Mag_X;
    s16 Mag_Y;
    s16 Mag_Z;
  }d_Mag;
  
  /**************Gyro�����****************/
  typedef struct{
    uint16_t Roll;
    uint16_t Pitch;
    uint16_t Yaw;
  }d_GyoZero;
  /***************AHRS GYRO���************/
  typedef struct{
    s16 Roll;
    s16 Pitch;
    s16 Yaw;
  }d_GyoZero_AHRS;
  /**************Acc�����****************/
  typedef struct{
    uint16_t XAcc;
    uint16_t YAcc;
    uint16_t ZAcc;
  }d_AccZero;
  
  /**************ȥ������Gyro****************/
  typedef struct{
    short Roll;
    short Pitch;
    short Yaw;
  }d_GyoZeroed;
  /**************ȥ������Acc****************/
  typedef struct{
    short XAcc;
    short YAcc;
    short ZAcc;
  }d_AccZeroed;
  /**************ת��Ϊ��׼��λ��Gyro****************/
  typedef struct{
    float Roll;
    float Pitch;
    float Yaw;
  }d_StandardizedGyroFeedback;
  /**************ת��Ϊ��׼��λ��Acc****************/
  typedef struct{
    float XAcc;
    float YAcc;
    float ZAcc;
  }d_StandardizedAccFeedback;
  /**************��̬���Ƶ�Ŀ��ֵ****************/
  typedef struct{
    float Roll;
    float Pitch;
    float Yaw;
  }d_Attitude_Reference;
  
  /**************���ȿ��Ƶ�Ŀ��ֵ****************/
  typedef struct{
    float Roll;
    float Pitch;
    float Yaw;
    float Throttle;
  }d_Stabilize_Reference;
  
  /**************ȥ�������ң����ֵ****************/
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
