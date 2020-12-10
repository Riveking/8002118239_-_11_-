//*******************************************************************
// TinyEngine����  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2013-08-02
// ��Ȩ���� 2007-2020 ������
// (C) 2007-2020 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Util.h"

wchar_t * T_Util::int_to_wstring(int i)
{
	wchar_t *w_str;
	w_str = new wchar_t[20];
	if(!w_str)
	{
		delete []w_str;
		return NULL;
	}
	swprintf(w_str, 20, L"%d ", i);
	return w_str;
}

//�������������������ָ������㡢�յ�������ƶ��ٶ�
//���Ҫ��������ֱ���ƶ��ҳ����ٶ�Ϊָ���ƶ��ٶ�
//������������̱߶�Ӧ�ķ����ٶ�
//xRatio��yRatioΪ�������, �����ռ�����
//���������Զ��жϷ���
//	xRatio��yRatioΪ��ֵ����ʾ���ҡ����ƶ�
//	xRatio��yRatioΪ��ֵ����ʾ�������ƶ�
void T_Util::GetBevelSpeed(IN POINT startPT, IN POINT destPT, IN int Speed, 
									 OUT int& xRatio, OUT int& yRatio)
{
	float aX,bY;
	if(destPT.x > startPT.x)
	{
		aX = (float)(destPT.x - startPT.x);
	}
	else
	{
		aX = (float)(startPT.x - destPT.x);
	}

	if(destPT.y > startPT.y)
	{
		bY = (float)(destPT.y - startPT.y);	
	}
	else
	{
		bY = (float)(startPT.y - destPT.y);	
	}

	if(aX==0 || bY==0)
	{
		xRatio = 0;
		yRatio = 0;
		return;
	}

	if(bY>aX)
	{
		yRatio = Speed;
		xRatio = (int)((Speed*aX)/bY);
	}
	else
	{
		xRatio = Speed;
		yRatio = (int)((Speed*bY)/aX);
	}
	if(startPT.x-destPT.x == 0) xRatio = 0;
	if(startPT.y-destPT.y == 0) yRatio = 0;
	if(startPT.x-destPT.x > 0) xRatio = -xRatio;
	if(startPT.y-destPT.y > 0) yRatio = -yRatio;
}