#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//算法使用的时基，公交车定时器(ಡωಡ)

//注意高级定时器18挂载在APB2总线上，通用定时器2345挂载在APB1总线上
#define TimeBaseFreqDivTimer	TIM2
#define RCC_APB1Periph_TIMERx 	RCC_APB1Periph_TIM2			//设置定时器挂载总线
#define Timerx_IRQn				TIM2_IRQn					//定时器中断	

//初始化定时器2作为分频时序基础
void TIM2_RunLEDTick_Init (FunctionalState control)  
{  
	ucTimerx_InitSetting(	TimeBaseFreqDivTimer, 
							Timerx_IRQn, 
							RCC_APB1Periph_TIMERx,
							TIMx_GPIO_Remap_NULL,
							FDTimer_TogglePeriod, 
							FDTimer_Prescaler, 
							TIM_CKD_DIV1, 
							TIM_CounterMode_Up, 
							irq_Use, 						
							0x02, 
							0x05, 
							control);
}  

//定时器2中断服务：定时器分割混合使用
void TIM2_IRQHandler (void)  								
{
#if SYSTEM_SUPPORT_OS										//OS支持
	OSIntEnter();
#endif
	
	if (TIM_GetITStatus(TimeBaseFreqDivTimer, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否
	{
		TIM_ClearITPendingBit(TimeBaseFreqDivTimer, TIM_IT_Update);//清除TIMx的中断待处理位
		
		RunLED_StatusCtrl();								//RunLED动作处理
		OLED_PageAlterCtrl();								//OLED切屏控制
	}
	
#if SYSTEM_SUPPORT_OS										//OS支持
	OSIntExit();    
#endif
}

//====================================================================================================
//code by </MATRIX>@Neod Anderjon