/**
******************************************************************************
* @file    GPIO/IOToggle/stm32f10x_it.c 
* @author  MCD Application Team
* @version V3.5.0
* @date    08-April-2011
* @brief   Main Interrupt Service Routines.
*          This file provides template for all exceptions handler and peripherals
*          interrupt service routine.
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "adc_dma.h"
#include "usb_istr.h"
#include "ringbuffer.h"
#include "delay.h"

//#define ENC2_ROTATE_A PDin(10)
//#define ENC2_ROTATE_B PDin(11)
#define ENC5_ROTATE_A PDin(11)
#define ENC5_ROTATE_B PDin(10)
//#define ENC6_ROTATE_A PGin(3)
//#define ENC6_ROTATE_B PGin(4)

//int16_t ENC2_COUNT=10000;
int16_t ENC5_COUNT=10000;
//int16_t ENC6_COUNT=10000;

uint16_t Timecount1=0;
uint16_t Timecount2=0;
uint16_t Timecount_RED=0;
uint16_t Timecount_RGB=0;
uint8_t control_flag=0;
uint16_t led_count=0;
uint16_t timeout = 0;

extern uint8_t rotation_flag; 
extern uint8_t filter_flag;
uint8_t time5_count=0;
char  ahrs_data_A;
char  ahrs_data_B;
char  ahrs_data_C;
extern RingBuffer  m_ahrs_RX_RingBuff_A;
extern RingBuffer  m_ahrs_RX_RingBuff_B;
extern RingBuffer  m_ahrs_RX_RingBuff_C;



void UART4_IRQHandler(void)			 //UART4中断服务程序
{ 
	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(UART4);
	}

	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)    //进中断的标志
	{                                                                                                    
		USART_ClearITPendingBit(UART4,USART_IT_RXNE); 		
		ahrs_data_A=USART_ReceiveData(UART4);
		//USART_SendData(UART4, ahrs_data);        //接收到的数据重新发送到串口  
		rbPush(&m_ahrs_RX_RingBuff_A, ahrs_data_A);                           
	}  
}




void UART5_IRQHandler(void)                	//串口5中断服务程序
{
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(UART5);
	}

	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)    //进中断的标志
	{                                                                                                    
		USART_ClearITPendingBit(UART5,USART_IT_RXNE); 		
		ahrs_data_B=USART_ReceiveData(UART5);
		//USART_SendData(UART5, ahrs_data);        //接收到的数据重新发送到串口  
		rbPush(&m_ahrs_RX_RingBuff_B, ahrs_data_B);                           
	} 
} 



void USART1_IRQHandler(void)			 //USART1中断服务程序
{ 
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(USART1);
	}

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    //进中断的标志
	{                                                                                                    
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); 		
		ahrs_data_C=USART_ReceiveData(USART1);
		//USART_SendData(USART1, ahrs_data);        //接收到的数据重新发送到串口  
		rbPush(&m_ahrs_RX_RingBuff_C, ahrs_data_C);                           
	}  
}

void USART2_IRQHandler(void)			 //USART2中断服务程序
{ 
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(USART2);
	}

	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)    //进中断的标志
	{                                                                                                    
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); 		
		ahrs_data_C=USART_ReceiveData(USART2);
		//USART_SendData(USART1, ahrs_data);        //接收到的数据重新发送到串口  
		rbPush(&m_ahrs_RX_RingBuff_C, ahrs_data_C);                           
	}  
}


void TIM2_IRQHandler(void) 
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);    
    time5_count++; 
    filter_flag = 1;
    if(time5_count>=40)  //rotation_flag:50hz
    {
      time5_count=0;
      rotation_flag=1;
    }
		Timecount1++;
		Timecount2++;
		Timecount_RED++;
		Timecount_RGB++;
		control_flag=1;
		led_count++;
		timeout++;
		if(led_count >=200)
		{
			led_count=200;
    }
		
		if(Timecount1>=16000)
		{
			Timecount1=16000;
    }
		if(Timecount2>=16000)
		{
			Timecount2=16000;
    }
		if(Timecount_RED>=16000)
		{
			Timecount_RED=16000;
    }
		if(Timecount_RGB>=16000)
		{
			Timecount_RGB=16000;
    }
  }  
}

void TIM1_UP_IRQHandler(void) 
{
  
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //?ì2é???¨μ?TIM?D??·￠éúó?·?:TIM ?D???′ 
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //??3yTIMxμ??D??′y′|àí??:TIM ?D???′ 
  }
  
}


void TIM3_IRQHandler(void) 
{
  
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //?ì2é???¨μ?TIM?D??·￠éúó?·?:TIM ?D???′ 
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //??3yTIMxμ??D??′y′|àí??:TIM ?D???′ 
  }
  
}

void TIM5_IRQHandler(void) 
{
  
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //?ì2é???¨μ?TIM?D??·￠éúó?·?:TIM ?D???′ 
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //??3yTIMxμ??D??′y′|àí??:TIM ?D???′ 
  }
  
}

void TIM8_UP_IRQHandler(void) 
{
  
  if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //?ì2é???¨μ?TIM?D??·￠éúó?·?:TIM ?D???′ 
  {
    TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //??3yTIMxμ??D??′y′|àí??:TIM ?D???′ 
  }
  
}

void TIM4_IRQHandler(void) 
{
  
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //?ì2é???¨μ?TIM?D??·￠éúó?·?:TIM ?D???′ 
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //??3yTIMxμ??D??′y′|àí??:TIM ?D???′ 
  }
  
}

void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Toggle LED1 */
    // gyro_data_ready_cb();
    
    /* Clear the  EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{			
		
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{			
		
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{			
		
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{			
		if(ENC5_ROTATE_B)
		{
			if(ENC5_ROTATE_A)
			{ENC5_COUNT--;ENC5_COUNT--;}
			else
			{ENC5_COUNT++;ENC5_COUNT++;}			
		}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{		
		if(ENC5_ROTATE_A)
		{
			if(ENC5_ROTATE_B)
			{ENC5_COUNT++;ENC5_COUNT++;}
			else
			{ENC5_COUNT--;ENC5_COUNT--;}
		}
		EXTI_ClearITPendingBit(EXTI_Line11);		
	}
	
}


void USBWakeUp_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}



void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}



void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}


void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
