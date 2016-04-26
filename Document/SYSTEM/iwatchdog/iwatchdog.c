#include "iwatchdog.h"
/*******************************��������****************************************
* ��������: void IWatchDog_Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �������Ź���ʼ��  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/24
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

/*******************************��������****************************************
* ��������: void Fedd_Watchdog(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ι��������λ���Ź��ź�  
* ��    ��: by Xu jinqi
* ��    ��: 2015/8/24
*******************************************************************************/ 
void Fedd_Watchdog(void)
{
  /* Reload IWDG counter */
  IWDG_ReloadCounter();  
}



