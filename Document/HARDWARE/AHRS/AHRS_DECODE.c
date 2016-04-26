//#include""

u8 AHRSdataOver=0;
s16 Ac_x,Ac_y,Ac_z;
s16 G_x,G_y,G_z;
s16 Mg_x,Mg_y,Mg_z;

void AHRSdataDecode(void)
{
  if(AHRSdataOver==1)
  {
    AHRSdataOver=0;
    if (AHRS_CheckSum(Rxbuff+2,20)==Rxbuff[22])
    {
     Ac_x = Rxbuff[4]<<8|Rxbuff[5];
     Ac_y = Rxbuff[6]<<8|Rxbuff[7];
     Ac_z = Rxbuff[8]<<8|Rxbuff[9];
     
     G_x = Rxbuff[10]<<8|Rxbuff[11];
     G_y = Rxbuff[12]<<8|Rxbuff[13];
     G_z = Rxbuff[14]<<8|Rxbuff[15];
     
     Mg_x = Rxbuff[16]<<8|Rxbuff[17];
     Mg_y = Rxbuff[18]<<8|Rxbuff[19];
     Mg_z = Rxbuff[20]<<8|Rxbuff[21];
    

      }
    }
  }
u8 AHRS_CheckSum(u8 *pData,u8 nLength)
{
  uint_8 checksun=0;
  for(u8 i=0;i<nLength;i++) checksun += ((u16)pData[i] & 0xFF);  
  return checksun;
}