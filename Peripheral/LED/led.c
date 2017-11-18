#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//====================================================================================================
//初始化PA8 PD2 PC11 PC12作为LED IO口

//LED闪烁设置
#define BlinkInterval			500000u						//定时500ms翻转IO口
#define LED2BreathInterval		5000u						//LED2呼吸间隔
#define LED3BreathInterval		7000u						//LED3呼吸间隔

BreathPWMGroup led2, led3;						

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
	
	//呼吸灯参数初始化
	BreathPara_Init(&led2, LED2BreathInterval);
	BreathPara_Init(&led3, LED3BreathInterval);
}

//LED集群动作控制
void LEDGroupCtrl (LEDGroupNbr nbr, LEDMoveList mv)
{
	//用函数的方法封装不可调用的IO状态操作
	switch (nbr)
	{
	case led_0:
		switch (mv)
		{
		case On: 	LED0_On; 	break;
		case Off: 	LED0_Off;	break;
		case Blink: LED0_Blink;	break;
		}
		break;
	case led_1:
		switch (mv)
		{
		case On: 	LED1_On; 	break;
		case Off: 	LED1_Off;	break;
		case Blink: LED1_Blink;	break;
		}
		break;
	case led_2:
		switch (mv)
		{
		case On: 	LED2_On; 	break;
		case Off: 	LED2_Off;	break;
		case Blink: LED2_Blink;	break;
		}
		break;
	case led_3:
		switch (mv)
		{
		case On: 	LED3_On; 	break;
		case Off: 	LED3_Off;	break;
		case Blink: LED3_Blink;	break;
		}
		break;
	}
}

//初始化完成闪烁标志
void Aft_PeriInit_Blink (void)
{
    u8 bb;													//开个小玩笑
    for (bb = 0; bb < 3; bb++)								//闪烁几次，直到有人发现已经完成初始化
    {
		LEDGroupCtrl(led_0, Blink);
        LEDGroupCtrl(led_1, Blink);
        delay_ms(50);
        LEDGroupCtrl(led_0, Blink);
        LEDGroupCtrl(led_1, Blink);
        delay_ms(50);
        LEDGroupCtrl(led_0, Blink);
        LEDGroupCtrl(led_1, Blink);
        delay_ms(50);
        LEDGroupCtrl(led_0, Blink);
        LEDGroupCtrl(led_1, Blink);
    }
}

//RunLED状态控制
void RunLED_StatusCtrl (void)
{
	static u16 runledBlinkSem = 0u;
	//初始化过程常亮
	if (Return_Error_Type == Error_Clear && pwsf == JBoot)
		LEDGroupCtrl(led_1, On);
	//只有警报清除且初始化完成才闪烁，系统正常运行指示
	else if (Return_Error_Type == Error_Clear && pwsf != JBoot) 
	{
		runledBlinkSem++;									//信号量开始计数
		if (runledBlinkSem == TickDivsIntervalus(BlinkInterval) - 1)
		{
			runledBlinkSem = 0u;
			LEDGroupCtrl(led_1, Blink);															
		}
	}
}

//参数初始化
void BreathPara_Init (BreathPWMGroup *led_nbr, u32 iv)
{
	led_nbr -> breathCtrlSem = 0u;
	led_nbr -> changeDirFlag = False;
	led_nbr -> dutyCycle = 0u;
	led_nbr -> breathInterval = iv;							//呼吸间隔单独初始化
}

//呼吸灯效果生成
void BreathPWMProduce (LEDGroupNbr nbr, BreathPWMGroup *led_nbr)
{
	//初始化过程常亮
	if (Return_Error_Type == Error_Clear && pwsf == JBoot)
		LEDGroupCtrl(nbr, On);
	//初始化完成后开始呼吸
	else if (Return_Error_Type == Error_Clear && pwsf != JBoot) 
	{
		led_nbr -> breathCtrlSem++;							//信号量叠加
		
		if (led_nbr -> breathCtrlSem <= led_nbr -> dutyCycle)
			LEDGroupCtrl(nbr, On);
		else
			LEDGroupCtrl(nbr, Off);
		
		if (led_nbr -> breathCtrlSem == TickDivsIntervalus(led_nbr -> breathInterval) - 1)//决定变换周期
		{
			led_nbr -> breathCtrlSem = 0u;					//信号量复位
			if (!led_nbr -> changeDirFlag)
			{
				led_nbr -> dutyCycle++; 					//占空比增加，LED逐渐变亮
				if (led_nbr -> dutyCycle == TickDivsIntervalus(led_nbr -> breathInterval) - 1) 
					led_nbr -> changeDirFlag = True;		//换向
			}
			else
			{
				led_nbr -> dutyCycle--;						//占空比减小，LED逐渐变暗
				if (led_nbr -> dutyCycle == 0u) 				
					led_nbr -> changeDirFlag = False;		//换向
			}
		}
	}
}

//呼吸灯组调用
void BreathLEDGroupCall (void)
{		
	BreathPWMProduce(led_2, &led2);
	BreathPWMProduce(led_3, &led3);
}

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
