#include "crc16.h"
/*******************************************************************************
* Copyright 2015 SuZhou 苏州敏行医学
* All right reserved
*
* 文件名称：crc16.h
*
* 文件标识：crc16
* 摘    要：CRC16数据包校验
*
*
* 当前版本：v1.0
* 作    者：Xu jinqi
* 日    期：2015/7/22
* 编译环境：IAR 7.0
*
* 历史信息：
*******************************************************************************/

/*******************************函数声明****************************************
* 函数名称: u16 crc16_ccitt(u8  *q,s16 len) 
* 输入参数: u8  *q,s16 len 
* 返回参数: u16  
* 功    能: CRC16_CCITT查表校验  
* 作    者: by Xu jinqi
* 日    期: 2015/7/22
*******************************************************************************/ 
u16 crc16_ccitt(u8  *q,s16 len)
{
  u16 crc = 0;
  while (len-- > 0)
    crc = ccitt_table[(crc >> 8 ^ *q++) & 0xff] ^ (crc << 8);
  return crc;
}


/*******************************函数声明****************************************
* 函数名称: u16 crc16(u8  *q,s16 len) 
* 输入参数: u8  *q,s16 len 
* 返回参数: u16  
* 功    能: CRC16 查表校验  
* 作    者: by Xu jinqi
* 日    期: 2015/7/22
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
