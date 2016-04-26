/**
  ******************************************************************************
  * @file    UFO/config_init.c 
  * @author  xujinqi
  * @version V3.5.0
  * @date    08-03-2013
  * @brief   config_init.c
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "config_init.h"

/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((uint32_t)0x4001244C)  //ADC数据保存
#define UART4_DR_Address   ((uint32_t)0x40004C04) 
#define USART2_DR_Address   ((uint32_t)0x40004404) 
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define XbeeSize  (countof(Xbee))

/* Private variables ---------------------------------------------------------*/
uint8_t Xbee[13]={0xff,0xff,0x02,0x00,0x01,0x00,0x03,0x00,0x05,0x00,
                  0x07,0x00,0x00};

uint16_t  SPI_SLAVE_Rx_Cali[2]={0};


GyroRaw  Gyrosampe;
GyroRaw  *Gyro_raw=&Gyrosampe;

Accraw   Accsample;
Accraw   *Acc_raw=&Accsample;

//GyroRaw  Gyrosampe_old={2052,2030,2550};
//GyroRaw  *Gyro_raw_old=&Gyrosampe_old;

//Accraw   Accsample_old={2020,2085,1950};
//Accraw   *Acc_raw_old=&Accsample_old;

//__IO uint16_t ADCConvertedValue[6];
//__IO uint16_t ADCConvertedValue_old[6]={2052,2030,2550,2020,2085,1950};
//double ADCConvertedValue_old[6]={0.0};
double ADCConvertedValue_gyro[3][3]={0.0};
double ADCValue_gyro[3][3]={0.0};
//__IO uint16_t After_filter[6];





/*
  * @brief  Configures the system clock.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{  
   /* PCLK2 = HCLK/2 */
   RCC_PCLK2Config(RCC_HCLK_Div2); 
   
   /* TIM2, SPI1,GPIOA, GPIOB,GPIOC,GPIOD, GPIOE and AFIO clocks enable */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|
                          RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 |RCC_APB1Periph_TIM4 |RCC_APB1Periph_TIM5,ENABLE);
}



/*
  * @brief  delay
  * @param  None
  * @retval None
  */
void delay(u16 t)
{
   u16 i,j;
   for(i = 0;i < 7200;i ++)
      for(j = t;j > 0;j --);
}


/*
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 100 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 10))
  { 
    /* Capture error */ 
    while (1);
  }

   NVIC_SetPriority(SysTick_IRQn, 0x0);
}


void AHRS_USART2_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	/* USART configuration */
	
	USART_InitStructure.USART_BaudRate =115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_Init(USART2, &USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);  //使能串口2接收中断 
	/* Enable USART */
	USART_Cmd(USART2, ENABLE);//使能串口

	

}                   





/**
  * @简要   获取AD值，并且每组取平均值.
  * @参数   无
  * @返回值 无
  */
/*
void Get_ADC_Value(void)
{
   uint32_t sum=0;
   uint16_t aver=0;
   u8 count;
   for(u8 i=0;i<6;i++)
   {
      for(count=0;count<10;count++)
      {
         sum+=ADCConvertedValue[count][i];
      }
      aver = sum/10;
      switch(i)
      {
         case 0:
         Acc_raw->XAcc = aver;    //XACC
         break;
         case 1:
         Acc_raw->YAcc = aver ;//YAcc
         break;
         case 2:
         Acc_raw->ZAcc = aver ;//ZAcc
         break;
         case 3:
         Gyro_raw->Roll =  aver ;   //GYRO1  Roll
         break;
         case 4:
         Gyro_raw->Pitch = aver ;   //GYRO2  Pitch
         break;
         case 5:
         Gyro_raw->Yaw = aver ; //GYRO3 Yaw
         break;
         default:
         break;
      }
      sum=0;
      aver=0;
   }
   
   
}

*/

/**
  * @简要   配置LED灯，用于指示遥控器状态.
  * @参数   无
  * @返回值 无
  */
void Light_Init(void)
{
   /****GPIO_Configuration-------------------------------------------------------***/
   GPIO_InitTypeDef GPIO_InitStructure;  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
   GPIO_Init(GPIOA, &GPIO_InitStructure);    
}


void Led1_On_Yellow(void)
{
  GPIO_ResetBits(GPIOA,GPIO_Pin_0);//turn on the "TEST1" light
}

void Led1_Off_Yellow(void)
{
  GPIO_SetBits(GPIOA,GPIO_Pin_0);//turn off the "TEST1" light
}


void Led2_On_Green(void)
{
  GPIO_ResetBits(GPIOA,GPIO_Pin_1);//turn on the "TEST2" light
}

void Led2_Off_Green(void)
{
  GPIO_SetBits(GPIOA,GPIO_Pin_1);//turn off the "TEST2" light
}



