#include"ahrs_400hz.h"
# define HIC_X  -0.0531
# define HIC_Y  -0.03825
# define HIC_Z  0.1
/*
# define K_Xacc  0.00076226
# define K_Yacc  0.00076347
# define K_Zacc  0.00076078
*/
# define K_Xacc  0.00076374
# define K_Yacc  0.00077126
# define K_Zacc  0.00076078

# define K_Rollrate  0.00022405
# define K_Pitchrate 0.00021442
# define K_Yawrate   0.00021772
extern u8 AHRSdataOver;
extern u8 Rxbuff[40];//定义接收缓存区，用于存放接收到的字节
IMU_Data  AHRS_Data;
IMU_Data  *pAHRS_Data = &AHRS_Data;
IMU_Data  AHRS_Data_Temp;
IMU_Data  *pAHRS_Data_Temp=&AHRS_Data_Temp;
u8 AHRS_count=0;
void AHRSdataDecode(void)
{
  /*
  if(AHRSdataOver==1)
  {
    AHRSdataOver=0;*/
    if (AHRS_CheckSum(Rxbuff+2,20)==Rxbuff[22])
    {
      if(AHRS_count==0)
      {
        AHRS_count=1;
        pAHRS_Data_Temp->magX = (u16)(Rxbuff[16]<<8|Rxbuff[17]);
        if(pAHRS_Data_Temp->magX>32768)
          pAHRS_Data_Temp->magX = -(pAHRS_Data_Temp->magX-32768);    
        pAHRS_Data->magX = (pAHRS_Data_Temp->magX)*(-0.00075)-(HIC_X);
        
        pAHRS_Data_Temp->magY = (u16)(Rxbuff[18]<<8|Rxbuff[19]);
        if(pAHRS_Data_Temp->magY>32768)
          pAHRS_Data_Temp->magY = -(pAHRS_Data_Temp->magY-32768);
        pAHRS_Data->magY = (pAHRS_Data_Temp->magY)*(-0.00075)-(HIC_Y);
        
        pAHRS_Data_Temp->magZ = (u16)(Rxbuff[20]<<8|Rxbuff[21]);
        if(pAHRS_Data_Temp->magZ>32768)
          pAHRS_Data_Temp->magZ = (-(pAHRS_Data_Temp->magZ-32768));
        pAHRS_Data->magZ = (pAHRS_Data_Temp->magZ)*(-0.00075);
      }
   
      pAHRS_Data_Temp->Xacc = (u16)(Rxbuff[4]<<8|Rxbuff[5]);
      if(pAHRS_Data_Temp->Xacc>32768)
        pAHRS_Data_Temp->Xacc = -(pAHRS_Data_Temp->Xacc-32768);
      pAHRS_Data->Xacc = -(pAHRS_Data_Temp->Xacc-125)*K_Xacc;
      
      pAHRS_Data_Temp->Yacc = (u16)(Rxbuff[6]<<8|Rxbuff[7]);
      if(pAHRS_Data_Temp->Yacc>32768)
        pAHRS_Data_Temp->Yacc = -(pAHRS_Data_Temp->Yacc-32768);
      pAHRS_Data->Yacc = -(pAHRS_Data_Temp->Yacc+450)*K_Yacc;
      
      pAHRS_Data_Temp->Zacc = (u16)(Rxbuff[8]<<8|Rxbuff[9]);
      if(pAHRS_Data_Temp->Zacc>32768)
        pAHRS_Data_Temp->Zacc = -(pAHRS_Data_Temp->Zacc-32768);
      pAHRS_Data->Zacc = -(pAHRS_Data_Temp->Zacc+25)*K_Zacc;     

      pAHRS_Data_Temp->RollRate = (u16)(Rxbuff[10]<<8|Rxbuff[11]);
      if(pAHRS_Data_Temp->RollRate>32768)
        pAHRS_Data_Temp->RollRate = -(pAHRS_Data_Temp->RollRate-32768);
      pAHRS_Data->RollRate = pAHRS_Data_Temp->RollRate*K_Rollrate;
      
      pAHRS_Data_Temp->PitchRate= (u16)(Rxbuff[12]<<8|Rxbuff[13]);
      if(pAHRS_Data_Temp->PitchRate>32768)
        pAHRS_Data_Temp->PitchRate = -(pAHRS_Data_Temp->PitchRate-32768);
      pAHRS_Data->PitchRate = pAHRS_Data_Temp->PitchRate*K_Pitchrate;
      
      pAHRS_Data_Temp->YawRate  = (u16)(Rxbuff[14]<<8|Rxbuff[15]);
      if(pAHRS_Data_Temp->YawRate>32768)
        pAHRS_Data_Temp->YawRate = -(pAHRS_Data_Temp->YawRate-32768);
      pAHRS_Data->YawRate = pAHRS_Data_Temp->YawRate*K_Yawrate;
      
      pAHRS_Data_Temp->magX = (u16)(Rxbuff[16]<<8|Rxbuff[17]);
      if(pAHRS_Data_Temp->magX>32768)
        pAHRS_Data_Temp->magX = -(pAHRS_Data_Temp->magX-32768);
      //if(pAHRS_Data->magX-((pAHRS_Data_Temp->magX)*(-0.00075)-(HIC_X))<=0.1 && pAHRS_Data->magX-((pAHRS_Data_Temp->magX)*(-0.00075)-(HIC_X))>=-0.1)    
        pAHRS_Data->magX = (pAHRS_Data_Temp->magX)*(-0.00075)-(HIC_X);
      
      pAHRS_Data_Temp->magY = (u16)(Rxbuff[18]<<8|Rxbuff[19]);
      if(pAHRS_Data_Temp->magY>32768)
        pAHRS_Data_Temp->magY = -(pAHRS_Data_Temp->magY-32768);
      //if(pAHRS_Data->magY-((pAHRS_Data_Temp->magY)*(-0.00075)-(HIC_Y))<=0.1 && pAHRS_Data->magY-((pAHRS_Data_Temp->magY)*(-0.00075)-(HIC_Y))>=-0.1)    
        pAHRS_Data->magY = (pAHRS_Data_Temp->magY)*(-0.00075)-(HIC_Y);
      
      pAHRS_Data_Temp->magZ = (u16)(Rxbuff[20]<<8|Rxbuff[21]);
      if(pAHRS_Data_Temp->magZ>32768)
        pAHRS_Data_Temp->magZ = (-(pAHRS_Data_Temp->magZ-32768));    
      //if(pAHRS_Data->magZ-((pAHRS_Data_Temp->magZ)*(-0.00075))<=0.1 && pAHRS_Data->magZ-((pAHRS_Data_Temp->magZ)*(-0.00075))>=-0.1)    
        pAHRS_Data->magZ = (pAHRS_Data_Temp->magZ)*(-0.00075) - (HIC_Z);
      }
    }
 
u8 AHRS_CheckSum(u8 *pData,u8 nLength)
{
	u8 i;
  u8 checksun=0;
  for(i=0;i<nLength;i++) checksun += ((u16)pData[i] & 0xFF);  
  return checksun;
}