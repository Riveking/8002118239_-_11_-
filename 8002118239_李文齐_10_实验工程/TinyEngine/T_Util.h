//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 版权所有 2007-2020 万立中
// (C) 2007-2020 WanLizhong All Rights Reserved
//*******************************************************************

#pragma once
#include "T_Config.h"

class T_Util
{
public:
	static wchar_t * int_to_wstring(int i);

	// 根据输入的三个参数所指定的起点、终点坐标和移动速度
	// 如果要保持两点直线移动且长边速度为指定移动速度
	// 本函数计算出短边对应的分量速度
	// xRatio与yRatio为输出参数, 即最终计算结果
	// 本函数会自动判断方向：
	//	xRatio、yRatio为正值，表示朝右、下移动
	//	xRatio、yRatio为负值，表示朝左、上移动
	static void GetBevelSpeed(
		IN POINT startPT, IN POINT destPT, IN int Speed, 
		OUT int& xRatio, OUT int& yRatio
	);
};