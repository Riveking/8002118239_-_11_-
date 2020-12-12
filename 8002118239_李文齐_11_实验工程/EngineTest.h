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
	//重载T_Engine类中的虚函数
	void GameInit();			//游戏初始化
	void GameLogic();			//游戏逻辑处理
	void GameEnd();				//游戏结束处理
	void GamePaint(HDC hdc);	//游戏显示
	void GameKeyAction(int Action = KEY_SYS_NONE);//按键行为处理
	void GameMouseAction(int x, int y, int Action);//鼠标行为处理

												   /*实验七*/
	void PaintMyText(HDC hdc);//画我的字
	void IntMyMenu();//初始化我的菜单

					 //void DrawMyMenu(HDC hdc);//画我的菜单
	void MyMenuKeyAction(int Action);//菜单游戏按键处理
	void PaintMyAbout(HDC hdc);//显示关于菜单内容
	void PaintMyHelp(HDC hdc);//显示帮助菜单内容
							  //void MyGameMenuAction(int Action);

							  /*实验八*/
							  //void LoadPlayer();//初始化我的玩家角色和NPC角色
	void MyGameLogic();
	void MyGamePaint(HDC hdc);//游戏运行时画面绘制
	void MyGameKeyAction(int Action);

	//实验十

	void MyGameMouseAction(int x, int y, int Action);


private:
	//记录游戏窗口宽高
	int wnd_width, wnd_height;
	T_Menu t_menu, t_menuHelp, t_menuAbout;//游戏菜单类的对象

	MyGameMenu my_menu, my_menu2;//游戏运行时菜单类的对象
	HBITMAP hBitmap;//保存已加载的位图的句柄
	int bmpWidth, bmpHeight;//已加载位图的宽高
	HBITMAP hbitmap;//当前位图句柄

	bool display_menu = false;//是否显示游戏运行时的菜单

							  //实验十

	POINT mouse_pt;
	//T_Sprite* npc[NUM];
	T_AI* sp_ai;

	//void UpdateFrames();//更新动画序列帧
	//void UpdatePos();//更新位置

	//实验11
	//重新定义动画帧序列
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];

	static const int NPC_NUM = 10;
	static const int MAP_ROWS = 24;//地图图块总行数
	static const int MAP_COLS = 32;//地图图块总列数
	static const int MAP_BKG = 30;//背景图块编号
	static const int TILE_WIDTH = 32;//图块宽
	static const int TILE_HEIGHT = 32;//图块高
	static const int BARRIER[MAP_ROWS*MAP_COLS];//地图障碍图层数据
												//定义要使用的类对象
	T_Map *barrier;//障碍层地图对象
	T_Map *back;
	T_Sprite* player;
	vSpriteSet npc_set;//NPC角色集合
					   //定义全局性的变量
	int op;//操作类型（op=0 键盘；op=1 鼠标）

		   //定义函数功能
	void LoadMap();//加载游戏地图场景
	void LoadPlayer();//加载游戏玩家
	void LoadNpc(int total);
	void UpdatePlayerPos(int dir);//更新玩家位置
	void UpdateNpcPos();//更新NPC位置
	void UpdateAnimation();//更新游戏动画

	HBITMAP GetBmpHandle()
	{
		return hbitmap;
	};

};
