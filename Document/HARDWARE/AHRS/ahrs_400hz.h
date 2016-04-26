#ifndef __STM32F10x_AHRS_400HZ_H
#define __STM32F10x_AHRS_400HZ_H
#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32f10x.h"
#include "stdio.h"
#include "config_init.h"  
#include "math.h"
#include <stdbool.h>   
#include "structural.h"
#include "stm32f10x_it.h"  

   
void AHRSdataDecode(void);
u8 AHRS_CheckSum(u8 *pData,u8 nLength);
   
   
   
   
   
   
   
   
#ifdef __cplusplus
}
#endif

#endif
