#include "ahrs_ringbuffer.h"
#include "ahrs_400hz.h"
#include "ringbuffer.h"
#include "string.h"


#define PACKETSIZE               11
#define START_BYTE_A            0xa5
#define START_BYTE_B            0x5a
#define START_BYTE_C             22
#define START_BYTE_D            0xa2
#define END_BYTE                0xaa
#define LEN_HEADER                1

/* 时间帧头 */
#define START_BYTE_TIME_A		0x55
#define START_BYTE_TIME_B		0x50
/* 加速度帧头 */
#define START_BYTE_AC_A			0x55
#define START_BYTE_AC_B			0x51
/* 角速度帧头 */
#define START_BYTE_AV_A			0x55
#define START_BYTE_AV_B			0x52
/* 角度帧头 */
#define START_BYTE_AG_A			0x55
#define START_BYTE_AG_B			0x53
/* 磁场帧头 */
#define START_BYTE_MF_A			0x55
#define START_BYTE_MF_B			0x54
/* 端口状态数据帧头 */
#define START_BYTE_PS_A			0x55
#define START_BYTE_PS_B			0x55
/* 气压高度帧头 */
#define START_BYTE_PA_A			0x55
#define START_BYTE_PA_B			0x56
/* 经纬度帧头 */
#define START_BYTE_LL_A			0x55
#define START_BYTE_LL_B			0x57
/* 地速帧头 */
#define START_BYTE_GS_A			0x55
#define START_BYTE_GS_B			0x58

uint8_t			Rxbuff_A[40];
uint8_t			Rxbuff_B[40];
uint8_t			Rxbuff_C[40];
uint8_t     m_ahrs_RX_Buff[50];
RingBuffer  m_ahrs_RX_RingBuff_A;
RingBuffer  m_ahrs_RX_RingBuff_B;
RingBuffer  m_ahrs_RX_RingBuff_C;
//extern u8 SBUS_test_count;
//working buffer for packet decoding
uint8_t     m_ahrs_RX_WorkingBuff_A[PACKETSIZE];
uint8_t     m_ahrs_RX_WorkingBuff_B[PACKETSIZE];
uint8_t     m_ahrs_RX_WorkingBuff_C[PACKETSIZE];
uint8_t     m_ahrs_RX_WorkingBuff_A_DataCount = 0;
uint8_t     m_ahrs_RX_WorkingBuff_B_DataCount = 0;
uint8_t     m_ahrs_RX_WorkingBuff_C_DataCount = 0;
uint8_t     m_ahrs_RX_PreviousValue_A = END_BYTE;
uint8_t     m_ahrs_RX_PreviousValue_B = END_BYTE;
uint8_t     m_ahrs_RX_PreviousValue_C = END_BYTE;


struct SAngle stcAngle_A;
struct SAngle stcAngle_B;
struct SAngle stcAngle_C;

u8 AHRSdataOver=0;
s16 Ac_x,Ac_y,Ac_z;
s16 G_x,G_y,G_z;
s16 Mg_x,Mg_y,Mg_z;

float Roll_A,Pitch_A,Yaw_A,Temperature_A;
float Roll_B,Pitch_B,Yaw_B,Temperature_B;
float Roll_C,Pitch_C,Yaw_C,Temperature_C;

float Ax_A, Ay_A, Az_A, Ax_B, Ay_B, Az_B, Ax_C, Ay_C, Az_C;

void AHRSdataDecode_A(void)
{
    if (AHRS_CheckSum(Rxbuff_A,10)==Rxbuff_A[10])
    {
			Ax_A = stcAngle_A.Angle[0];
			Ay_A = stcAngle_A.Angle[1];
			Az_A = stcAngle_A.Angle[2];
			//printf("Ax_A=%f, Ay_A=%f, Az_A=%f\r\n",Ax_A,Ay_A,Az_A);
			
//			Roll_A = (float)stcAngle_A.Angle[0]/32768*180;
//			Pitch_A = (float)stcAngle_A.Angle[1]/32768*180;
//			Yaw_A = (float)stcAngle_A.Angle[2]/32768*180;
//			Temperature_A = (float)stcAngle_A.T/100;
//			printf("Yaw=%.3f, Pitch=%.3f, Roll=%.3f, Temperature=%.1f\r\n",(float)stcAngle_A.Angle[2]/32768*180,(float)stcAngle_A.Angle[1]/32768*180,(float)stcAngle_A.Angle[0]/32768*180,(float)stcAngle_A.T/100);	 
	 }
}

void AHRSdataDecode_B(void)
{
    if (AHRS_CheckSum(Rxbuff_B,10)==Rxbuff_B[10])
    {
			Roll_B = (float)stcAngle_B.Angle[0]/32768*180;
			Pitch_B = (float)stcAngle_B.Angle[1]/32768*180;
			Yaw_B = (float)stcAngle_B.Angle[2]/32768*180;
			Temperature_B = (float)stcAngle_B.T/100;
			//printf("Yaw=%.3f, Pitch=%.3f, Roll=%.3f, Temperature=%.1f\r\n",(float)stcAngle_B.Angle[2]/32768*180,(float)stcAngle_B.Angle[1]/32768*180,(float)stcAngle_B.Angle[0]/32768*180,(float)stcAngle_B.T/100);	 
	 }
}


void AHRSdataDecode_C(void)
{
    if (AHRS_CheckSum(Rxbuff_C,10)==Rxbuff_C[10])
    {
			Roll_C = (float)stcAngle_C.Angle[0]/32768*180;
			Pitch_C = (float)stcAngle_C.Angle[1]/32768*180;
			Yaw_C = (float)stcAngle_C.Angle[2]/32768*180;
			Temperature_C = (float)stcAngle_C.T/100;
			//printf("Yaw=%.3f, Pitch=%.3f, Roll=%.3f, Temperature=%.1f\r\n",(float)stcAngle_C.Angle[2]/32768*180,(float)stcAngle_C.Angle[1]/32768*180,(float)stcAngle_C.Angle[0]/32768*180,(float)stcAngle_C.T/100);	 
	 }
}


uint8_t AHRS_CheckSum(u8 *pData,u8 nLength)
{
  uint8_t checksun=0;
  uint8_t i=0;
  for(i=0;i<nLength;i++) checksun += ((u16)pData[i] & 0xFF);  
  return checksun;
}

void ahrs_Configure(void)
{
	//AHRS_USART2_Init();
	rbInitialize(&m_ahrs_RX_RingBuff_A, m_ahrs_RX_Buff, sizeof(m_ahrs_RX_Buff));
	rbInitialize(&m_ahrs_RX_RingBuff_B, m_ahrs_RX_Buff, sizeof(m_ahrs_RX_Buff));
	rbInitialize(&m_ahrs_RX_RingBuff_C, m_ahrs_RX_Buff, sizeof(m_ahrs_RX_Buff));
}

uint8_t ahrs_IsReadyToRead(void)
{
	u8 temp = 0;
	temp = (!rbIsEmpty(&m_ahrs_RX_RingBuff_A))|(!rbIsEmpty(&m_ahrs_RX_RingBuff_B))|(!rbIsEmpty(&m_ahrs_RX_RingBuff_C));
  return temp;
}

void ahrs_Decode_A(void)
{ 
	u8 i;
	for(i=0;i<11;i++)
	{
		Rxbuff_A[i]=m_ahrs_RX_WorkingBuff_A[i];
	}

	memcpy(&stcAngle_A,&m_ahrs_RX_WorkingBuff_A[2],8);
	
	AHRSdataDecode_A();
}

void ahrs_Decode_B(void)
{ 
	u8 i;
	for(i=0;i<11;i++)
	{
		Rxbuff_B[i]=m_ahrs_RX_WorkingBuff_B[i];
	}

	memcpy(&stcAngle_B,&m_ahrs_RX_WorkingBuff_B[2],8);
	
	AHRSdataDecode_B();
}

void ahrs_Decode_C(void)
{ 
	u8 i;
	for(i=0;i<11;i++)
	{
		Rxbuff_C[i]=m_ahrs_RX_WorkingBuff_C[i];
	}

	memcpy(&stcAngle_C,&m_ahrs_RX_WorkingBuff_C[2],8);
	
	AHRSdataDecode_C();
}
  


void ahrs_Update(void)
{

	/*从RingBuff_A提取数据*/
	{
		if(m_ahrs_RX_RingBuff_A.flagOverflow==1)
		{
			rbClear(&m_ahrs_RX_RingBuff_A);
		}
		while( !rbIsEmpty(&m_ahrs_RX_RingBuff_A) )  
		{
			uint8_t flagClear = ERROR;
			uint8_t cur = rbPop(&m_ahrs_RX_RingBuff_A);
			
			if( m_ahrs_RX_WorkingBuff_A_DataCount == 0 )    
			{
				
				m_ahrs_RX_WorkingBuff_A[0] = m_ahrs_RX_WorkingBuff_A[1];
				m_ahrs_RX_WorkingBuff_A[1] = cur;

				if((m_ahrs_RX_WorkingBuff_A[0]==START_BYTE_AC_A) && (m_ahrs_RX_WorkingBuff_A[1]==START_BYTE_AC_B)) 
					m_ahrs_RX_WorkingBuff_A_DataCount = 2;
			}
			else { 
				m_ahrs_RX_WorkingBuff_A[m_ahrs_RX_WorkingBuff_A_DataCount++] = cur;
			}
			
			if( m_ahrs_RX_WorkingBuff_A_DataCount == PACKETSIZE ) 
			{  
				//if( m_ahrs_RX_WorkingBuff[PACKETSIZE-1] == END_BYTE ) 
				//{
					ahrs_Decode_A();
					flagClear = SUCCESS;
				//} 
				//else {      
				//  flagClear = SUCCESS;
				//}
			}
			
			m_ahrs_RX_PreviousValue_A = cur;
			
			// buffer clear & buffer over-run prevention
			if( flagClear || (m_ahrs_RX_WorkingBuff_A_DataCount >= sizeof(m_ahrs_RX_WorkingBuff_A)) ) 
			{
				m_ahrs_RX_WorkingBuff_A_DataCount = 0;
				memset(m_ahrs_RX_WorkingBuff_A,0,PACKETSIZE*sizeof(uint8_t));			//WorkingBuff清零
			}
		}
  }
	
	/*从RingBuff_B提取数据*/
	{
		if(m_ahrs_RX_RingBuff_B.flagOverflow==1)
		{
			rbClear(&m_ahrs_RX_RingBuff_B);
		}
		while( !rbIsEmpty(&m_ahrs_RX_RingBuff_B) )  
		{
			uint8_t flagClear = ERROR;
			uint8_t cur = rbPop(&m_ahrs_RX_RingBuff_B);
			
			if( m_ahrs_RX_WorkingBuff_B_DataCount == 0 )    
			{
				
				m_ahrs_RX_WorkingBuff_B[0] = m_ahrs_RX_WorkingBuff_B[1];
				m_ahrs_RX_WorkingBuff_B[1] = cur;

				if((m_ahrs_RX_WorkingBuff_B[0]==START_BYTE_AG_A) && (m_ahrs_RX_WorkingBuff_B[1]==START_BYTE_AG_B)) 
					m_ahrs_RX_WorkingBuff_B_DataCount = 2;
			}
			else { 
				m_ahrs_RX_WorkingBuff_B[m_ahrs_RX_WorkingBuff_B_DataCount++] = cur;
			}
			
			if( m_ahrs_RX_WorkingBuff_B_DataCount == PACKETSIZE ) 
			{  
				//if( m_ahrs_RX_WorkingBuff[PACKETSIZE-1] == END_BYTE ) 
				//{
					ahrs_Decode_B();
					flagClear = SUCCESS;
				//} 
				//else {      
				//  flagClear = SUCCESS;
				//}
			}
			
			m_ahrs_RX_PreviousValue_B = cur;
			
			// buffer clear & buffer over-run prevention
			if( flagClear || (m_ahrs_RX_WorkingBuff_B_DataCount >= sizeof(m_ahrs_RX_WorkingBuff_B)) ) 
			{
				m_ahrs_RX_WorkingBuff_B_DataCount = 0;
				memset(m_ahrs_RX_WorkingBuff_B,0,PACKETSIZE*sizeof(uint8_t));  //WorkingBuff清零
			}
		}
  }	
	
	/*从RingBuff_C提取数据*/
	{
		if(m_ahrs_RX_RingBuff_C.flagOverflow==1)
		{
			rbClear(&m_ahrs_RX_RingBuff_C);
		}
		while( !rbIsEmpty(&m_ahrs_RX_RingBuff_C) )  
		{
			uint8_t flagClear = ERROR;
			uint8_t cur = rbPop(&m_ahrs_RX_RingBuff_C);
			
			if( m_ahrs_RX_WorkingBuff_C_DataCount == 0 )    
			{
				
				m_ahrs_RX_WorkingBuff_C[0] = m_ahrs_RX_WorkingBuff_C[1];
				m_ahrs_RX_WorkingBuff_C[1] = cur;

				if((m_ahrs_RX_WorkingBuff_C[0]==START_BYTE_AG_A) && (m_ahrs_RX_WorkingBuff_C[1]==START_BYTE_AG_B)) 
					m_ahrs_RX_WorkingBuff_C_DataCount = 2;
			}
			else { 
				m_ahrs_RX_WorkingBuff_C[m_ahrs_RX_WorkingBuff_C_DataCount++] = cur;
			}
			
			if( m_ahrs_RX_WorkingBuff_C_DataCount == PACKETSIZE ) 
			{  
				//if( m_ahrs_RX_WorkingBuff[PACKETSIZE-1] == END_BYTE ) 
				//{
					ahrs_Decode_C();
					flagClear = SUCCESS;
				//} 
				//else {      
				//  flagClear = SUCCESS;
				//}
			}
			
			m_ahrs_RX_PreviousValue_C = cur;
			
			// buffer clear & buffer over-run prevention
			if( flagClear || (m_ahrs_RX_WorkingBuff_C_DataCount >= sizeof(m_ahrs_RX_WorkingBuff_C)) ) 
			{
				m_ahrs_RX_WorkingBuff_C_DataCount = 0;
				memset(m_ahrs_RX_WorkingBuff_C,0,PACKETSIZE*sizeof(uint8_t));    //WorkingBuff清零
			}
		}
  }	
	
}

void Get_AHRS_Value(void)
{
	
	if( ahrs_IsReadyToRead() )
	{
		ahrs_Update();		
	} 
}

/*
void Update_AHRS_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
	uint16_t t=0;
	t = (uint16_t)(Yaw*1000);
	*pDesLength = *pDesLength+1;
	pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);
	
	t = (uint16_t)(Pitch*1000);
	*pDesLength = *pDesLength+1;
	pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);
	
	t = (uint16_t)(Roll*1000);
	*pDesLength = *pDesLength+1;
	pDesArr[*pDesLength+4] = (u8)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (u8)(t&0x00FF);

}
*/



void float2byte_trans(float data,unsigned char *pAdder)
{
  float2byte temp;
  temp.value =data;
  *pAdder++ = temp.float_byte.low_byte;
  *pAdder++ = temp.float_byte.mlow_byte;
  *pAdder++ = temp.float_byte.mhigh_byte;
  *pAdder   = temp.float_byte.high_byte;
}

void int2byte_trans(float data, unsigned char *pAdder)
{
	INT temp;
	temp.value = (short int)(data*100);
	*pAdder++ = temp.int_byte.low_byte;
	*pAdder   = temp.int_byte.high_byte;
}

void Update_AHRS_A_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
	Roll_A=0.0;Pitch_A=0.0;Yaw_A=0.0;Temperature_A=0.0;
    *pDesLength = *pDesLength+1;
    //"ROLL"is Pitch truely
    int2byte_trans(Roll_A, &pDesArr[*pDesLength+4]);
    //float2byte_trans(-11.1 ,&pDesArr[*pDesLength+4]);
    *pDesLength = *pDesLength+2;
    //"Pitch"is ROLL truely
    int2byte_trans(Pitch_A, &pDesArr[*pDesLength+4]);
    // float2byte_trans(11.0 ,&pDesArr[*pDesLength+4]);
    *pDesLength = *pDesLength+2;
    int2byte_trans(Yaw_A, &pDesArr[*pDesLength+4]);  
    //  float2byte_trans(11.0 ,&pDesArr[*pDesLength+4]);  
    *pDesLength = *pDesLength+1;
    pDesArr[4]=*pDesLength;  
		//发送数据清零
		//Roll_A=0.0;Pitch_A=0.0;Yaw_A=0.0;Temperature_A=0.0;
}

void Update_AHRS_B_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
    *pDesLength = *pDesLength+1;
    //"ROLL"is Pitch truely
    int2byte_trans(Roll_B, &pDesArr[*pDesLength+4]);
    //float2byte_trans(-11.1 ,&pDesArr[*pDesLength+4]);
    *pDesLength = *pDesLength+2;
    //"Pitch"is ROLL truely
    int2byte_trans(Pitch_B, &pDesArr[*pDesLength+4]);
    // float2byte_trans(11.0 ,&pDesArr[*pDesLength+4]);
    *pDesLength = *pDesLength+2;
    int2byte_trans(Yaw_B, &pDesArr[*pDesLength+4]);  
    //  float2byte_trans(11.0 ,&pDesArr[*pDesLength+4]);  
    *pDesLength = *pDesLength+1;
    pDesArr[4]=*pDesLength;
		//发送数据清零  
		//Roll_B=0.0;Pitch_B=0.0;Yaw_B=0.0;Temperature_B=0.0;
}

void Update_AHRS_C_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
    *pDesLength = *pDesLength+1;
    //"ROLL"is Pitch truely
    int2byte_trans(Roll_C, &pDesArr[*pDesLength+4]);
    //float2byte_trans(-11.1 ,&pDesArr[*pDesLength+4]);
    *pDesLength = *pDesLength+2;
    //"Pitch"is ROLL truely
    int2byte_trans(Pitch_C, &pDesArr[*pDesLength+4]);
    // float2byte_trans(11.0 ,&pDesArr[*pDesLength+4]);
    *pDesLength = *pDesLength+2;
    int2byte_trans(Yaw_C, &pDesArr[*pDesLength+4]);  
    //  float2byte_trans(11.0 ,&pDesArr[*pDesLength+4]);  
    *pDesLength = *pDesLength+1;
    pDesArr[4]=*pDesLength;
		//发送数据清零
		//Roll_C=0.0;Pitch_C=0.0;Yaw_C=0.0;Temperature_C=0.0;	
}


