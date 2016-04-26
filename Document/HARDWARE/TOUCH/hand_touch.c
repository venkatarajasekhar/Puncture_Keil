#include "hand_touch.h"
#include "stdio.h"
#include "switch.h"
/*******************************************************************************
* Copyright 2015 SuZhou ��������ҽѧ
* All right reserved
*
* �ļ����ƣ�hand_touch
*
* �ļ���ʶ��hand_touch.h
* ժ    Ҫ���ִ�����ĳ�ʼ��
*
*
* ��ǰ�汾��
* ��    �ߣ�Xu jinqi
* ��    �ڣ�2015/7/15
* ���뻷����IAR 7.0
*
* ��ʷ��Ϣ��
*******************************************************************************/
SwitchStruct switchvalue_touch;
SwitchStruct *pSwitchValue_touch = &switchvalue_touch;
/*******************************��������****************************************
* ��������: void Hand_Touch_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �ִ�����Ķ˿ڳ�ʼ��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Hand_Touch_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  GPIO_SetBits(GPIOF,GPIO_Pin_15);
  GPIO_SetBits(GPIOG,GPIO_Pin_0);
}

 /*******************************��������****************************************
 * ��������: void Hand_Touch_Detection(void) 
 * �������: void 
 * ���ز���: void  
 * ��    ��: �ִ������źŶ�ȡ  
 * ��    ��: by Xu jinqi
 * ��    ��: 2015/7/15
 *******************************************************************************/ 
 void Hand_Touch_Detection(void)
 {
   pSwitchValue_touch->bit.switch1 = TOUCH1_State;
   pSwitchValue_touch->bit.switch2 = TOUCH2_State;
  // printf("3:%d--4:%d\n",a,b); 
 }
 
/*******************************��������****************************************
* ��������:  Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������:  uint8_t* pDesArr,uint8_t* pDesLength
* ���ز���:   void
* ��    ��:   ���¹�����������usbsendbuffer
* ��    ��: by Xu jinqi
* ��    ��: 2015/7/15
*******************************************************************************/ 
void Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  u8 t=0;
  //t = 0x1234;	
  t=pSwitchValue_touch->total_value;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = t;  
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}

