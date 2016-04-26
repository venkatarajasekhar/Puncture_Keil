#ifndef __STM32F10x_CINFIG_INIT_H
#define __STM32F10x_CINFIG_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32f10x.h"
#include "stdio.h"
#include "structural.h"
#include "math.h"
//#include "control.h"
   
   
void delay(u16 t);  
void RCC_Configuration(void);
void SysTick_Configuration(void);
void NVIC_Configuration(void);
void UART_Init(void);
void Time_Init(void);
void RCC_Configuration(void);
void SPI1_Init (void);
void PWM_Init(void);
void PWM_Init_Time1(void);
void ADC_DMA_Init(void);
void Light_Init(void);
void Led1_On_Yellow(void);
void Led1_Off_Yellow(void);
void Led2_On_Green(void);
void Led2_Off_Green(void);
void Xbee_USART_Init(void);
void Xbee_Send(void);
void Xbee_USART2_Init(void);
void AHRS_USART2_Init(void);
void DMA_TX2(void);
void CalcBcc(unsigned char* TxData, int nByte);
void CalcBcc_SPI(uint16_t* TxData, int nByte);
void CalcBcc_SPI_TX(uint16_t* TxData, int nByte);


extern GyroRaw  *Gyro_raw;
extern Accraw   *Acc_raw;
extern GyroRaw  *Gyro_raw_old;
extern Accraw   *Acc_raw_old;
extern __IO uint16_t ADCConvertedValue[6];
extern double ADCConvertedValue_old[6];
extern double ADCConvertedValue_gyro[3][3];
extern double ADCValue_gyro[3][3];
extern __IO uint16_t After_filter[6];
extern uint8_t Xbee[13];
extern uint16_t  SPI_SLAVE_Rx_Cali[2];
#ifdef __cplusplus
}
#endif
#endif


