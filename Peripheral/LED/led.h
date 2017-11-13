#ifndef __LED_H__
#define __LED_H__
#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//初始化PA8，PD2用于LED，源于正点原子AlienTek MiniSTM32开发板设置
//初始化PC11，PC12用于LED，指示电机运行状态

#define LED0 		PAout(8)			//PA8 	红灯 报警指示灯
#define LED1 		PDout(2)			//PD2 	绿灯 系统运行指示灯
#define Mecanum_LED PCout(11)			//PC11 	蓝灯 移动平台运行指示灯
#define ARM_LED		PCout(12)			//PC12 	蓝灯 机械臂运行指示灯

typedef enum {LED_On = 0, LED_Off = !LED_On} LED_Status;//定义LED状态

//封装
#define LED0_On 	(LED0 = LED_On)
#define LED0_Off	(LED0 = LED_Off)
#define LED0_Blink	(LED0 = !LED0)		//快速闪烁不延时
#define LED1_On 	(LED1 = LED_On)
#define LED1_Off	(LED1 = LED_Off)
#define LED1_Blink	(LED1 = !LED1)		//快速闪烁不延时

#define MLED_On		(Mecanum_LED = LED_On)
#define MLED_Off 	(Mecanum_LED = LED_Off)
#define ALED_On		(ARM_LED = LED_On)
#define ALED_Off	(ARM_LED = LED_Off)

extern float runledBlinkSem;

void LED_Init (void);					//初始化
extern void Aft_PeriInit_Blink (void);	//系统外设初始化完成标志
void RunLED_StatusCtrl (void);			

#endif

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
