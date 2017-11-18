#ifndef __LED_H__
#define __LED_H__
#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//初始化PA8 PD2 PC11 PC12作为LED IO口

#define LED0 		PAout(8)			//PA8 	红灯 报警指示灯
#define LED1 		PDout(2)			//PD2 	绿灯 系统运行指示灯
#define LED2 		PCout(11)			//PC11 	蓝灯 呼吸灯
#define LED3		PCout(12)			//PC12 	蓝灯 

typedef enum {LED_On = 0, LED_Off = !LED_On} LED_Status;//定义LED状态

//封装
#define LED0_On 	(LED0 = LED_On)
#define LED0_Off	(LED0 = LED_Off)
#define LED0_Blink	(LED0 = !LED0)		
#define LED1_On 	(LED1 = LED_On)
#define LED1_Off	(LED1 = LED_Off)
#define LED1_Blink	(LED1 = !LED1)		

#define LED2_On		(LED2 = LED_On)
#define LED2_Off 	(LED2 = LED_Off)
#define LED2_Blink	(LED2 = !LED2)
#define LED3_On		(LED3 = LED_On)
#define LED3_Off	(LED3 = LED_Off)
#define LED3_Blink	(LED3 = !LED3)

void LED_Init (void);					//初始化
extern void Aft_PeriInit_Blink (void);	//系统外设初始化完成标志
void RunLED_StatusCtrl (void);			
void BreathLED_StatusCtrl (void);

#endif

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
