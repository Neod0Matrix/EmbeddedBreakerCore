#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
/*
	模块对框架EmbeddBreakerCore的链接
	该文件写入对框架的函数调用支持
*/

//选项设置，链接到Universal_Resource_Config函数的模块库
void Modules_UniResConfig (void)
{
	//该函数设置内容可以更新Universal_Resource_Config函数原设置
}

//模块选项映射表，链接到urcMapTable_Print函数
void Modules_URCMap (void)
{
	
}

//选项处理，链接到pclURC_DebugHandler函数
void Modules_urcDebugHandler (u8 ed_status, Modules_SwitchNbr sw_type)
{
   //使用前请先更新Modules_SwitchNbr内容
}

//协议调用指令响应，链接到OrderResponse_Handler函数
void Modules_ProtocolTask (void)
{
	
}

//OLED常量显示屏，链接到OLED_DisplayInitConst和UIScreen_DisplayHandler函数
void OLED_ScreenModules_Const (void)
{
   
}

//OLED模块调用数据显示，链接到UIScreen_DisplayHandler函数
void OLED_DisplayModules (u8 page)
{
	if (UIRef_ModeFlag == Stable_Ref)
	{
		switch (page)
		{
		//此处添加case 5,6...(从限定值第一个开始)
		}
	}
}

//硬件底层初始化任务，链接到bspPeriSysCalls函数
void Modules_HardwareInit (void)
{
	
}

//硬件底层外部中断初始化，链接到EXTI_Config_Init函数
void Modules_ExternInterruptInit (void)
{
	
}

//外部中断任务，无需声明，使用时修改函数名
void EXTIx_IRQHandler (void)
{
#if SYSTEM_SUPPORT_OS 												
	OSIntEnter();    
#endif
	
	
	
#if SYSTEM_SUPPORT_OS 												
	OSIntExit();  											 
#endif
}

//模块非中断任务，链接到local_taskmgr.c，默认添加到第二任务
void Modules_NonInterruptTask (void)
{
	
}

//模块中断任务，链接到time_base.c TIM2_IRQHandler函数中
void Modules_InterruptTask (void)
{
	
}

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
