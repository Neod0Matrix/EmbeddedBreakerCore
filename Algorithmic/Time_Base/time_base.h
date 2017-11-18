#ifndef __TIME_BASE_H__
#define __TIME_BASE_H__
#include "stdafx.h"
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//算法使用的时基，公交车定时器(ಡωಡ)

//50ms时基源
#define ms_TogglePeriod		499u						//定时器自动重装翻转周期
#define ms_Prescaler		7199u						//定时器分频器	
//50us时基源
#define us_TogglePeriod		49u							//定时器自动重装翻转周期
#define us_Prescaler		71u							//定时器分频器	

//计算出目标定时需要的间隔，输入单位ms，单个时间间隔必须大于定时时基，且为时基的整数倍
#ifndef TickDivsIntervalms
#define TickDivsIntervalms(t)		(float)(t / (TimeCalcusofucTimer(ms_TogglePeriod, ms_Prescaler) * 1000))
#endif
//计算出目标定时需要的间隔，输入单位us，单个时间间隔必须大于定时时基，且为时基的整数倍
#ifndef TickDivsIntervalus
#define TickDivsIntervalus(t)		(float)(t / (TimeCalcusofucTimer(us_TogglePeriod, us_Prescaler) * 1000000))
#endif

void TIM2_msTimeBase_Init (FunctionalState control);
void TIM3_usTimeBase_Init (FunctionalState control);

#endif

//====================================================================================================
//code by </MATRIX>@Neod Anderjon
