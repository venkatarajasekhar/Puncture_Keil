#include "crc16.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�crc16.h
*
* �ļ���ʶ��crc16
* ժ    Ҫ��CRC16���ݰ�У��
*
*
* ��ǰ�汾��v1.0
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/22
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/

/*******************************��������****************************************
* ��������: u16 crc16_ccitt(u8  *q,s16 len) 
* �������: u8  *q,s16 len 
* ���ز���: u16  
* ��    ��: CRC16_CCITT���У��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/22
*******************************************************************************/ 
u16 crc16_ccitt(u8  *q,s16 len)
{
  u16 crc = 0;
  while (len-- > 0)
    crc = ccitt_table[(crc >> 8 ^ *q++) & 0xff] ^ (crc << 8);
  return crc;
}


/*******************************��������****************************************
* ��������: u16 crc16(u8  *q,s16 len) 
* �������: u8  *q,s16 len 
* ���ز���: u16  
* ��    ��: CRC16 ���У��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/22
*******************************************************************************/
u16 CRC16(u8 *puchMsgg,u8 usDataLen,u16 crcInput)
{
  u8 uchCRCHi;  
  u8 uchCRCLo;  
  u8 uIndex ; 
  uchCRCHi = (u8)(crcInput>>8);
  uchCRCLo = (u8)crcInput;
  
  while (usDataLen--) 
  { 
    uIndex = uchCRCHi ^ *puchMsgg++ ; 
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ; 
    uchCRCLo = auchCRCLo[uIndex] ; 
  } 
  return (uchCRCHi << 8 | uchCRCLo) ; 
}
