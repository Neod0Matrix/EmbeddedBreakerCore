#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//算法使用的时基，公交车定时器(ಡωಡ)

//注意高级定时器18挂载在APB2总线上，通用定时器2345挂载在APB1总线上
//TIM2 ms级定时时基源
#define TimeBasemsFreqDivTimer	TIM2
#define RCC_APB1Periph_TIMERxms RCC_APB1Periph_TIM2			//设置定时器挂载总线
#define Timerx_msIRQn			TIM2_IRQn					//定时器中断	
//TIM3 us级定时时基源
#define TimeBaseusFreqDivTimer	TIM3
#define RCC_APB1Periph_TIMERxus RCC_APB1Periph_TIM3			//设置定时器挂载总线
#define Timerx_usIRQn			TIM3_IRQn					//定时器中断	

//初始化定时器2作为ms级分频时序基础
void TIM2_msTimeBase_Init (FunctionalState control)  
{  
	ucTimerx_InitSetting(	TimeBasemsFreqDivTimer, 
							Timerx_msIRQn, 
							RCC_APB1Periph_TIMERxms,
							TIMx_GPIO_Remap_NULL,
							ms_TogglePeriod, 
							ms_Prescaler, 
							TIM_CKD_DIV1, 
							TIM_CounterMode_Up, 
							irq_Use, 						
							0x02, 
							0x05, 
							control);
}  

//初始化定时器3作为us级分频时序基础
void TIM3_usTimeBase_Init (FunctionalState control)  
{  
	ucTimerx_InitSetting(	TimeBaseusFreqDivTimer, 
							Timerx_usIRQn, 
							RCC_APB1Periph_TIMERxus,
							TIMx_GPIO_Remap_NULL,
							us_TogglePeriod, 
							us_Prescaler, 
							TIM_CKD_DIV1, 
							TIM_CounterMode_Up, 
							irq_Use, 						
							0x02, 
							0x06, 
							control);
}  

//定时器2中断服务：定时器分割混合使用
void TIM2_IRQHandler (void)  								
{
#if SYSTEM_SUPPORT_OS										//OS支持
	OSIntEnter();
#endif
	
	if (TIM_GetITStatus(TimeBasemsFreqDivTimer, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否
	{
		TIM_ClearITPendingBit(TimeBasemsFreqDivTimer, TIM_IT_Update);//清除TIMx的中断待处理位
		
		RunLED_StatusCtrl();								//RunLED动作处理
		OLED_PageAlterCtrl();								//OLED切屏控制
	}
	
#if SYSTEM_SUPPORT_OS										//OS支持
	OSIntExit();    
#endif
}

//定时器3中断服务：定时器分割混合使用
void TIM3_IRQHandler (void)  								
{
#if SYSTEM_SUPPORT_OS										//OS支持
	OSIntEnter();
#endif
	
	if (TIM_GetITStatus(TimeBaseusFreqDivTimer, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否
	{
		TIM_ClearITPendingBit(TimeBaseusFreqDivTimer, TIM_IT_Update);//清除TIMx的中断待处理位
		
		BreathLED_StatusCtrl();								//呼吸灯动作处理
	}
	
#if SYSTEM_SUPPORT_OS										//OS支持
	OSIntExit();    
#endif
}

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
