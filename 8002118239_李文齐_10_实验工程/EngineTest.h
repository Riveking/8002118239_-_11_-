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
	


private:
	//记录游戏窗口宽高
	int wnd_width, wnd_height;
	T_Menu t_menu,t_menuHelp,t_menuAbout;//游戏菜单类的对象

	MyGameMenu my_menu,my_menu2;//游戏运行时菜单类的对象
	HBITMAP hBitmap;//保存已加载的位图的句柄
	int bmpWidth, bmpHeight;//已加载位图的宽高
	HBITMAP hbitmap;//当前位图句柄

	bool display_menu = false;//是否显示游戏运行时的菜单

	//实验十
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
	void UpdateFrames();//更新动画序列帧
	void UpdatePos();//更新位置

	//static int MYCHOOSEMENU;//记录我菜单的选择

	HBITMAP GetBmpHandle()
	{
		return hbitmap;
	};

};
