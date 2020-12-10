//*******************************************************************
// TinyEngine����  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2013-08-02
// ��Ȩ���� 2007-2020 ������
// (C) 2007-2020 WanLizhong All Rights Reserved
//*******************************************************************

#pragma once
#include "T_Config.h"

class T_Util
{
public:
	static wchar_t * int_to_wstring(int i);

	// �������������������ָ������㡢�յ�������ƶ��ٶ�
	// ���Ҫ��������ֱ���ƶ��ҳ����ٶ�Ϊָ���ƶ��ٶ�
	// ������������̱߶�Ӧ�ķ����ٶ�
	// xRatio��yRatioΪ�������, �����ռ�����
	// ���������Զ��жϷ���
	//	xRatio��yRatioΪ��ֵ����ʾ���ҡ����ƶ�
	//	xRatio��yRatioΪ��ֵ����ʾ�������ƶ�
	static void GetBevelSpeed(
		IN POINT startPT, IN POINT destPT, IN int Speed, 
		OUT int& xRatio, OUT int& yRatio
	);
};