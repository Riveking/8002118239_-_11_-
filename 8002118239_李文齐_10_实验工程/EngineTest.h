#pragma once

#include ".\\TinyEngine\T_Engine.h"
#include ".\\TinyEngine\T_Graph.h"
#include ".\\TinyEngine\T_Menu.h"
#include "resource.h"
#include ".\\TinyEngine\T_Sprite.h"
#include ".\\TinyEngine\T_AI.h"


typedef struct
{
	wstring filename;
	int wframe;
	int hframe;
}FISHINFO;

class EngineTest :public T_Engine
{
public:
	virtual ~EngineTest(void);
	EngineTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
		WORD icon = IDI_SHARK, WORD sm_icon = IDI_SHARK,
		int winwidth = WIN_WIDTH, int winheight = WIN_HEIGHT);
	//����T_Engine���е��麯��
	void GameInit();			//��Ϸ��ʼ��
	void GameLogic();			//��Ϸ�߼�����
	void GameEnd();				//��Ϸ��������
	void GamePaint(HDC hdc);	//��Ϸ��ʾ
	void GameKeyAction(int Action = KEY_SYS_NONE);//������Ϊ����
	void GameMouseAction(int x, int y, int Action);//�����Ϊ����

	/*ʵ����*/
	void PaintMyText(HDC hdc);//���ҵ���
	void IntMyMenu();//��ʼ���ҵĲ˵�

	//void DrawMyMenu(HDC hdc);//���ҵĲ˵�
	void MyMenuKeyAction(int Action);//�˵���Ϸ��������
	void PaintMyAbout(HDC hdc);//��ʾ���ڲ˵�����
	void PaintMyHelp(HDC hdc);//��ʾ�����˵�����
	//void MyGameMenuAction(int Action);

	/*ʵ���*/
	//void LoadPlayer();//��ʼ���ҵ���ҽ�ɫ��NPC��ɫ
	void MyGameLogic();
	void MyGamePaint(HDC hdc);//��Ϸ����ʱ�������
	void MyGameKeyAction(int Action);

	//ʵ��ʮ
	


private:
	//��¼��Ϸ���ڿ��
	int wnd_width, wnd_height;
	T_Menu t_menu,t_menuHelp,t_menuAbout;//��Ϸ�˵���Ķ���

	MyGameMenu my_menu,my_menu2;//��Ϸ����ʱ�˵���Ķ���
	HBITMAP hBitmap;//�����Ѽ��ص�λͼ�ľ��
	int bmpWidth, bmpHeight;//�Ѽ���λͼ�Ŀ��
	HBITMAP hbitmap;//��ǰλͼ���

	bool display_menu = false;//�Ƿ���ʾ��Ϸ����ʱ�Ĳ˵�

	//ʵ��ʮ
	static FISHINFO fish[7];
	static const int NUM = 10;
	static int sequence[20];
	POINT mouse_pt;
	T_Graph* back;
	T_Sprite* player;
	T_Sprite* npc[NUM];
	T_AI* sp_ai;
	void LoadPlayer();
	void LoadNpc(int num);
	void UpdateFrames();//���¶�������֡
	void UpdatePos();//����λ��

	//static int MYCHOOSEMENU;//��¼�Ҳ˵���ѡ��

	HBITMAP GetBmpHandle()
	{
		return hbitmap;
	};

};
