#ifndef __STM32F10x_AHRS_H
#define __STM32F10x_AHRS_H
#ifdef __cplusplus
extern "C" {
#endif
  
#include "stm32f10x.h"
#include "stdio.h"
#include "structural.h"
#include "config_init.h"
//#include "attitude_control.h"
//#include "stabilize_control.h"    
#include "stm32f10x_it.h"
#include "math.h"
#include "stdlib.h"
  
void AHRS_Update(void);
void AHRS_Init(void);
void MatrixOpp(float A[][3],float B[][3]);

float wraparound(float dta);
#ifdef __cplusplus
}
#endif

#endif
