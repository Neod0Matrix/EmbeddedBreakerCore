#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//====================================================================================================
//初始化PA8 PD2 PC11 PC12作为LED IO口

//LED闪烁设置
#define BlinkInterval			500u						//定时500ms翻转IO口

//LED IO初始化
void LED_Init (void)
{
	//PA8 LED0 RLED
	ucGPIO_Config_Init (RCC_APB2Periph_GPIOA,			
						GPIO_Mode_Out_PP,					
						GPIO_Speed_50MHz,						
						GPIORemapSettingNULL,			
						GPIO_Pin_8,					
						GPIOA,					
						IHL,				
						EBO_Disable);
	//PD2 LED1 GLED
	ucGPIO_Config_Init (RCC_APB2Periph_GPIOD,			
						GPIO_Mode_Out_PP,					
						GPIO_Speed_50MHz,						
						GPIORemapSettingNULL,			
						GPIO_Pin_2,					
						GPIOD,					
						IHL,				
						EBO_Disable);
	//PC11 PC12 
	ucGPIO_Config_Init (RCC_APB2Periph_GPIOC,			
						GPIO_Mode_Out_PP,					
						GPIO_Speed_50MHz,						
						GPIORemapSettingNULL,			
						GPIO_Pin_11 | GPIO_Pin_12,					
						GPIOC,					
						IHL,				
						EBO_Disable);
}

//初始化完成闪烁标志
void Aft_PeriInit_Blink (void)
{
    u8 bb;													//开个小玩笑
    for (bb = 0; bb < 3; bb++)								//闪烁几次，直到有人发现已经完成初始化
    {
        LED0_Blink;
        LED1_Blink;
        delay_ms(50);
        LED0_Blink;
        LED1_Blink;
        delay_ms(50);
        LED0_Blink;
        LED1_Blink;
        delay_ms(50);
        LED0_Blink;
        LED1_Blink;
    }
}

//RunLED状态控制
void RunLED_StatusCtrl (void)
{
	static u16 runledBlinkSem = 0u;
	//初始化过程常亮
	if (Return_Error_Type == Error_Clear && pwsf == JBoot)
		LED1_On;
	//只有警报清除且初始化完成才闪烁，系统正常运行指示
	else if (Return_Error_Type == Error_Clear && pwsf != JBoot) 
	{
		runledBlinkSem++;									//信号量开始计数
		if (runledBlinkSem == TickDivsIntervalms(BlinkInterval) - 1)
		{
			runledBlinkSem = 0u;
			LED1_Blink;										//翻转IO口闪烁										
		}
	}
}

//呼吸灯控制
void BreathLED_StatusCtrl (void)
{
	static u16 breledCtrlSem = 0u;							//计数信号量
	static u16 pwmDutyCycle = 0u;							//PWM占空比
	static Bool_ClassType cdir = False;						//PWM增减换向标识
	
	//初始化过程常亮
	if (Return_Error_Type == Error_Clear && pwsf == JBoot)
	{
		LED2_On;
		LED3_On;
	}
	else if (Return_Error_Type == Error_Clear && pwsf != JBoot) 
	{
		breledCtrlSem++;
		if (breledCtrlSem <= pwmDutyCycle)
		{
			LED2_On;
			LED3_Off;
		}
		else
		{
			LED2_Off;
			LED3_On;
		}
		//5ms分频
		if (breledCtrlSem == TickDivsIntervalus(5000) - 1)
		{
			breledCtrlSem = 0u;
			if (!cdir)
			{
				pwmDutyCycle++; 
				if (pwmDutyCycle == TickDivsIntervalus(5000) - 1) 
					cdir = True;
			}
			else
			{
				pwmDutyCycle--;
				if (pwmDutyCycle == 0u) 
					cdir = False;
			}
		}
	}
}

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
