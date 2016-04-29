#include "main.h"
#include "sys.h"
#include "delay.h"
#include <stdio.h>
#include "usart.h"
#include "switch.h"
#include "adc_dma.h"
#include "time_user.h"
#include "encoder.h"
#include "led.h"
#include "dac.h"
#include "relay.h"
#include "ds18b20.h"
#include "MPU6050.h"
#include "dc_motor.h"

/**USB HID head file**************************/
#include "usb_lib.h"
#include "usbio.h"
#include "hw_config.h"
#include "crc16.h"
#include "protocol.h"

extern u8 USB_ReceiveFlg ;
extern u8 Receive_Buffer[ReceiveLength];
extern u8 Transi_Buffer[SendLength];
extern int16_t ENC5_COUNT;
extern uint8_t control_flag;


void USB_SendString(u8 *str);
void USB_PORT_SET(FunctionalState NewState);
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f) 
#endif /* __GNUC__ */

uint8_t crc16test[6]={0,1,2,3,0,0};
uint16_t crcreturn1 =0;
uint16_t crcreturn2 =0;
uint8_t rotation_flag=0;
uint8_t filter_flag = 0;

int main(void)
{
	
  uint8_t usbReceiveBuf[64]={0x00}; 
  uint8_t usbSendBuf[64]={0x00};
  uint8_t cmdIndex=0;
  uint8_t crcresult=0;
  uint8_t usbSendVaildLength=0;
  NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Time_Init();
  delay_init();	    	 //延时函数初始化	    
  ahrs_Configure();//初始化AHRS buffer   需要先初始化buffer再初始化串口，否则程序会卡死
	uart_init(115200);	 //串口初始化为9600 
  LED_Init();
	LED_RED_Init();
	LED_RGB_Init(2399,0);
	DC_Motor_Init(); 
  SWITCH_IO_Init();
  ADC_DMA_Init();  //TEST IS OK  
  Relay_Init();
  
  //USB HID initialize:
  USB_GPIO_Configuration();
  USB_Interrupts_Config();
  Set_USBClock();    
  USB_Init();
  USB_ReceiveFlg = FALSE;
  USB_Cable_Config(DISABLE);
  USB_PORT_SET(DISABLE);   
	
  delay_ms(1000);
  USB_PORT_SET(ENABLE);	

/**************************************************************/	
	//printf(" Skywalker is started..\r\n");
	while(1)
  {   
		printf(" Skywalker is started..\r\n");
		//Get_AHRS_Value();
		Get_Percussion_Flag();
		
		if(filter_flag)
		{
			filter_flag = 0;
			ADC_data_filter();
		}
		
		if(rotation_flag)
    {
      rotation_flag =0;
			//LED = !LED;
			//更新继电器状态
//      Update_Relay_Status();
		}

//		SetRGB_Value();
		
    if(USB_ReceiveFlg == TRUE ) 
    {
			timeout = 0;
			LED = !LED;
      usbSendVaildLength=2;
      USB_GetData(usbReceiveBuf,sizeof(usbReceiveBuf));
      USB_ReceiveFlg = FALSE;
      crcresult=Parsed_Data_FromPC(usbReceiveBuf,usbReceiveBuf[4]+5);
      cmdIndex=usbReceiveBuf[1];
      //  cmdIndex=usbReceiveBuf[0];
      if(crcresult)
      {
        if(usbReceiveBuf[6]==0xB5)
        {
          usbReceiveBuf[6]=0;
          //??
          usbSendBuf[0]=0x00;
          usbSendBuf[1]=cmdIndex; //包号
          //????
          usbSendBuf[2]=0x02;			//控制板编号
          //??????,????????????
          // usbSendBuf[3]=?;
          //usbSendBuf[4]=?;			//数据长度
          //???
          usbSendBuf[5]=0x00;
          usbSendBuf[6]=0xB5;			//命令字
          //更新数据
//					Update_AHRS_A_Value(usbSendBuf,&usbSendVaildLength);    //AHRS数据段，占12个字节
//          Update_AHRS_B_Value(usbSendBuf,&usbSendVaildLength);    //AHRS数据段，占12个字节
//					Update_AHRS_C_Value(usbSendBuf,&usbSendVaildLength);    //AHRS数据段，占12个字节
          Update_ADC_Value(usbSendBuf,&usbSendVaildLength);			//AD数据段，占12个字节
					SWITCH_IO_Detection();																	//8路开关量数据段，占2个字节
					Update_IO_Value(usbSendBuf,&usbSendVaildLength);	
					Update_Percussion_Value(usbSendBuf,&usbSendVaildLength);

					SendCRCDataToPC(usbSendBuf,&usbSendVaildLength);
          USB_SendData(usbSendBuf,sizeof(usbSendBuf));				
        }     
//        
        else if(usbReceiveBuf[6]==0xAA)
        {
          usbReceiveBuf[6]=0;       
          // 接受到上位机的控制指令 
          Parse_Pack_Data_MotorA(usbReceiveBuf);         
        }
				
				else if(usbReceiveBuf[6]==0xAB)
				{
					usbReceiveBuf[6]=0;       
          // 接受到上位机的控制指令
					Parse_Pack_Data_MotorB(usbReceiveBuf); 
					
				}
				else if(usbReceiveBuf[6]==0xAC)
				{
					usbReceiveBuf[6]=0;       
          // 接受到上位机的控制指令 
					Parse_Pack_Data_LED(usbReceiveBuf);
				}
				else if(usbReceiveBuf[6]==0xAD)
				{
					usbReceiveBuf[6]=0;       
          // 接受到上位机的控制指令 
					Parse_Pack_Data_RGB(usbReceiveBuf);
				}
      }
			
			// Judge state of motor
			Motor_state();

			// change the LED value	 
			SetLED_RED_Value();
			SetLED_RGB_Value();

			//control the motor;	 
			if(control_flag==1)
			{
				control_flag=0;
				Motor_control();      
			}				
    }
		if(timeout >= 1000)
		{
			Duty1 = 0;
			Duty1 = 0;
			//reset motor
			Motor_state();
			Motor_control(); 
			//reset LED
			TIM_SetCompare4(TIM3,0);
			TIM_SetCompare1(TIM3,0);
			TIM_SetCompare2(TIM3,0);
			TIM_SetCompare3(TIM3,0);

		}			
  } 
	
}





void USB_SendString(u8 *str)
{
  u8 ii=0;   
  while(*str)
  {
    Transi_Buffer[ii++]=*(str++);
    if (ii == SendLength) break;
  }
  UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, SendLength);
  SetEPTxValid(ENDP2);
}


void USB_PORT_SET(FunctionalState NewState)
{  	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
  if(NewState)_SetCNTR(_GetCNTR()&(~(1<<1)));//í?3???μ??￡ê?
  else
  {	  
    _SetCNTR(_GetCNTR()|(1<<1));  // ??μ??￡ê?
    GPIOA->CRH&=0XFFF00FFF;
    GPIOA->CRH|=0X00033000;
    GPIO_ResetBits(GPIOA,GPIO_Pin_12);    		  
  }
}  



PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);
  
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  
  return ch;
}
