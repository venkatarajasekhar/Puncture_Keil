#include "iwatchdog.h"
/*******************************函数声明****************************************
* 函数名称: void IWatchDog_Init(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 独立看门狗初始化  
* 作    者: by Xu jinqi
* 日    期: 2015/8/24
*******************************************************************************/ 
void IWatchDog_Init(void)
{
  /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
  dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  
  /* IWDG counter clock: LSI/32 */
  IWDG_SetPrescaler(IWDG_Prescaler_32);
  
  /* Set counter reload value to obtain 250ms IWDG TimeOut.
  Counter Reload Value = 250ms/IWDG counter clock period
  = 250ms / (LSI/32)
  = 0.25s / (LsiFreq/32)
  = LsiFreq/(32 * 4)
  = LsiFreq/128
  */
 // IWDG_SetReload(LsiFreq/128);
  
  /* Reload IWDG counter */
  IWDG_ReloadCounter();
  
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
}

/*******************************函数声明****************************************
* 函数名称: void Fedd_Watchdog(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 喂狗——复位看门狗信号  
* 作    者: by Xu jinqi
* 日    期: 2015/8/24
*******************************************************************************/ 
void Fedd_Watchdog(void)
{
  /* Reload IWDG counter */
  IWDG_ReloadCounter();  
}



