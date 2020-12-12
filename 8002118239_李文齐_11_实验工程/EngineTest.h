#pragma once

#include ".\\TinyEngine\\T_Engine.h"
#include ".\\TinyEngine\\T_Graph.h"
#include ".\\TinyEngine\\T_Menu.h"
#include "resource.h"
#include ".\\TinyEngine\\T_Sprite.h"
#include ".\\TinyEngine\\T_AI.h"
#include ".\\TinyEngine\\T_Map.h"
#include ".\\TinyEngine\\T_Layer.h"

typedef vector<T_Sprite*>vSpriteSet;

class EngineTest :public T_Engine
{
public:
	virtual ~EngineTest(void);
	EngineTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
		WORD icon = IDI_SHARK, WORD sm_icon = IDI_SHARK,
		int winwidth = WIN_WIDTH, int winheight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
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

	void MyGameMouseAction(int x, int y, int Action);


private:
	//��¼��Ϸ���ڿ��
	int wnd_width, wnd_height;
	T_Menu t_menu, t_menuHelp, t_menuAbout;//��Ϸ�˵���Ķ���

	MyGameMenu my_menu, my_menu2;//��Ϸ����ʱ�˵���Ķ���
	HBITMAP hBitmap;//�����Ѽ��ص�λͼ�ľ��
	int bmpWidth, bmpHeight;//�Ѽ���λͼ�Ŀ��
	HBITMAP hbitmap;//��ǰλͼ���

	bool display_menu = false;//�Ƿ���ʾ��Ϸ����ʱ�Ĳ˵�

							  //ʵ��ʮ

	POINT mouse_pt;
	//T_Sprite* npc[NUM];
	T_AI* sp_ai;

	//void UpdateFrames();//���¶�������֡
	//void UpdatePos();//����λ��

	//ʵ��11
	//���¶��嶯��֡����
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];

	static const int NPC_NUM = 10;
	static const int MAP_ROWS = 24;//��ͼͼ��������
	static const int MAP_COLS = 32;//��ͼͼ��������
	static const int MAP_BKG = 30;//����ͼ����
	static const int TILE_WIDTH = 32;//ͼ���
	static const int TILE_HEIGHT = 32;//ͼ���
	static const int BARRIER[MAP_ROWS*MAP_COLS];//��ͼ�ϰ�ͼ������
												//����Ҫʹ�õ������
	T_Map *barrier;//�ϰ����ͼ����
	T_Map *back;
	T_Sprite* player;
	vSpriteSet npc_set;//NPC��ɫ����
					   //����ȫ���Եı���
	int op;//�������ͣ�op=0 ���̣�op=1 ��꣩

		   //���庯������
	void LoadMap();//������Ϸ��ͼ����
	void LoadPlayer();//������Ϸ���
	void LoadNpc(int total);
	void UpdatePlayerPos(int dir);//�������λ��
	void UpdateNpcPos();//����NPCλ��
	void UpdateAnimation();//������Ϸ����

	HBITMAP GetBmpHandle()
	{
		return hbitmap;
	};

};
