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
#include "servo.h"
#include "hand_touch.h"
#include "ds18b20.h"
#include "adns9200.h"
/**USB HID head file**************************/
#include "usb_lib.h"
#include "usbio.h"
#include "hw_config.h"
#include "crc16.h"
#include "protocol.h"
#include "servo.h"
extern u8 USB_ReceiveFlg ;
extern u8 Receive_Buffer[ReceiveLength];
extern u8 Transi_Buffer[SendLength];

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

int main(void)
{
  uint8_t usbReceiveBuf[64]={0x00}; 
  uint8_t usbSendBuf[64]={0x00};
  uint8_t cmdIndex=0;
  uint8_t crcresult=0;
  uint8_t usbSendVaildLength=0;
  NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
  delay_init();	    	 //延时函数初始化	    
  ahrs_Configure();//初始化AHRS buffer   需要先初始化buffer再初始化串口，否则程序会卡死
	uart_init(115200);	 //串口初始化为9600
  
  LED_Init();
  SWITCH_IO_Init();
  ABS_Encoder_Init();   //此函数未经过验证（以前代码测试通过，直接移植），手头没有编码器。
  SWITCH_OPTP_Init(); 
  Hand_Touch_Init();  
  ADC_DMA_Init();  //TEST IS OK
  
  Time_Init(); 
  Servo_Motor_Init();  //900-2100
  
  DAC1_Init();
  DAC2_Init();
  Incre_Encoder_Init();	
  Relay_Init();
  
  DS18B20_Init();        
  ADNS9200_Init();  

	
  
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

		
	while(1)
	{
		//Get_ENC3_Number();

		//IfReadSignal=1;
		//Read_MPU9250();
		Get_AHRS_Value();
		Get_ADC_data_filter_ave();

		if(rotation_flag)
		{
			rotation_flag =0;
			LED = !LED;
		}

		if(SWITCH1==0)
		{
			TIM_Cmd(TIM4, DISABLE); 
			TIM4->CNT =200;      
			TIM_Cmd(TIM4, ENABLE); 

			TIM_Cmd(TIM8, DISABLE); 
			TIM8->CNT =200;      
			TIM_Cmd(TIM8, ENABLE); 
		}

		if (USB_ReceiveFlg == TRUE ) //�?�?o箝?????陏?Yo�??
		{
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
					//??ADNS9800???(ADNS)        
					//??CRC???
					//Update_MPU9250_Value(usbSendBuf,&usbSendVaildLength);
					Update_AHRS_Value(usbSendBuf,&usbSendVaildLength);    //AHRS数据段，占6个字节
					Update_ADC_Value(usbSendBuf,&usbSendVaildLength);			//AD数据段，占12个字节
					Get_ENC4_Number();
					Update_ENC4_Value(usbSendBuf,&usbSendVaildLength);		//光电编码器数据段，占2个字节
					SWITCH_IO_Detection();
					Update_IO_Value(usbSendBuf,&usbSendVaildLength);			//8路开关量数据段，占2个字节
					Get_ENC3_Number();
					Update_ENC3_Value(usbSendBuf,&usbSendVaildLength);		//机械编码器数据段，占2个字节
					SendCRCDataToPC(usbSendBuf,&usbSendVaildLength);
					USB_SendData(usbSendBuf,sizeof(usbSendBuf));				
				}     

				else if(usbReceiveBuf[6]==0xAA)
				{
					usbReceiveBuf[6]=0;       
					// ??????????? 
					Parse_Pack_Data(usbReceiveBuf);         
				}        
			}
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
  USART_SendData(UART4, (uint8_t) ch);
  
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
  {}
  
  return ch;
}
