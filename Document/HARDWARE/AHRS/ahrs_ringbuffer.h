#ifndef __AHRS_RINGBUFFER_H
#define __AHRS_RINGBUFFER_H
#include "stm32f10x.h"

void ahrs_Configure(void);
uint8_t ahrs_IsReadyToRead(void);
void ahrs_Update(void);
void AHRSdataDecode_A(void);
void AHRSdataDecode_B(void);
void AHRSdataDecode_C(void);
void ahrs_Decode_A(void);
void ahrs_Decode_B(void);
void ahrs_Decode_C(void);
uint8_t AHRS_CheckSum(u8 *pData,u8 nLength);
void Get_AHRS_Value(void);
void Update_AHRS_A_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_AHRS_B_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_AHRS_C_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void float2byte_trans(float data,unsigned char *pAdder);
void int2byte_trans(float data, unsigned char *pAdder);

struct SAngle
{
	short Angle[3];
	short T;
};

typedef union {
	struct 
	      {
           unsigned char low_byte;
           unsigned char mlow_byte;
           unsigned char mhigh_byte;
           unsigned char high_byte;
          }float_byte;
    struct 
	      { unsigned short int low_word;
          unsigned short int high_word;
          }float_word;
    float  value;
      }float2byte;

typedef union   {
        struct {
        unsigned char low_byte;
        unsigned char high_byte;
        } int_byte;
    unsigned int value;
    } INT;


#endif
