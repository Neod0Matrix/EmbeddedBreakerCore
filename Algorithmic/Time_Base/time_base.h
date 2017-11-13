#ifndef __TIME_BASE_H__
#define __TIME_BASE_H__
#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//算法使用的时基，公交车定时器(ಡωಡ)

//使用50ms时基源
#define FDTimer_TogglePeriod	499u						//定时器自动重装翻转周期
#define FDTimer_Prescaler		7199u						//定时器分频器	

//计算出目标定时需要的间隔，输入单位ms
#ifndef TickDivsInterval
#define TickDivsInterval(t)		(float)(t / (TimeCalcusofucTimer(FDTimer_TogglePeriod, FDTimer_Prescaler) * 1000))
#endif

void TIM2_RunLEDTick_Init (FunctionalState control);

#endif

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
