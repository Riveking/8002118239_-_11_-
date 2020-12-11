#include "EngineTest.h"
#include <stdio.h>


//int EngineTest::MYCHOOSEMENU = 1;
int EngineTest::FRAME_LEFT[20] = { 0,0,1,1,1,1,2,2,2,2,0,0,1,1,1,1,2,2,2,2 };
int EngineTest::FRAME_RIGHT[20] = { 3,3,4,4,4,4,5,5,5,5,3,3,4,4,4,4,5,5,5,5 };
int EngineTest::FRAME_UP[20] = { 6,6,7,7,7,7,8,8,8,8,6,6,7,7,7,7,8,8,8,8 };
int EngineTest::FRAME_DOWN[20] = { 9,9,10,10,10,10,11,11,11,11,9,9,10,10,10,10,11,11,11,11 };

const int EngineTest::BARRIER[MAP_ROWS*MAP_COLS] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,2,3,4,5,6,0,0,0,0,1,2,3,4,5,6,0,0,0,0,0,1,2,3,4,5,6,0,0,0,
	0,0,27,28,29,30,31,32,0,0,0,0,27,28,29,30,31,32,0,0,0,0,0,27,28,29,30,31,32,0,0,0,
	0,0,53,54,55,56,57,58,0,0,0,0,53,54,55,56,57,58,0,0,0,0,0,53,54,55,56,57,58,0,0,0,
	0,0,79,80,81,82,83,84,0,0,0,0,79,80,81,82,83,84,0,0,0,0,0,79,80,81,82,83,84,0,0,0,
	0,0,105,106,107,108,109,110,0,0,0,0,105,106,107,108,109,110,0,0,0,0,0,105,106,107,108,109,110,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,2,3,4,5,6,0,0,0,0,0,1,2,3,4,5,6,0,0,0,0,0,0,1,2,3,4,5,6,0,0,
	0,27,28,29,30,31,32,0,0,0,0,0,27,28,29,30,31,32,0,0,0,0,0,0,27,28,29,30,31,32,0,0,
	0,53,54,55,56,57,58,0,0,0,0,0,53,54,55,56,57,58,0,0,0,0,0,0,53,54,55,56,57,58,0,0,
	0,79,80,81,82,83,84,0,0,0,0,0,79,80,81,82,83,84,0,0,0,0,0,0,79,80,81,82,83,84,0,0,
	0,105,106,107,108,109,110,0,0,0,0,0,105,106,107,108,109,110,0,0,0,0,0,0,105,106,107,108,109,110,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,323,323,323,0,0,0,0,0,0,0,0,296,294,296,0,0,0,0,0,0,0,323,323,323,0,0,0,
	0,0,0,0,0,349,349,349,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,349,349,349,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

//WinMain函数
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"李文齐的实验十";//游戏窗口标题//
	EngineTest* test = new EngineTest(h_instance, WIN_CLASS, WinTitle, IDI_SHARK, IDI_SHARK, 800, 600);
	T_Engine::pEngine = test;//将父类的静态指针指向构造好的子类
	test->SetFrame(60);//设置画面刷新频率

					   //myApp->SetFullScreen(TRUE);//全屏启动

	test->StartEngine();
	return TRUE;

}

EngineTest::EngineTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title, WORD icon, WORD sm_icon, int winwidth, int winheight, COLORREF bkColor)
	:T_Engine(h_instance, sz_winclass, sz_title, icon, sm_icon, winwidth, winheight, bkColor)
{
	srand((unsigned)time(NULL));
	wnd_width = winwidth;
	wnd_height = winheight;//获取窗口宽高
}

EngineTest::~EngineTest(void) {}

void EngineTest::GameInit() {
	//GameState = GAME_START;
	GameState = GAME_RUN;
	IntMyMenu();
	op = 0;
	LoadMap();
	LoadPlayer();
	LoadNpc(NPC_NUM);

}				//游戏初始化接口函数

void EngineTest::GameLogic()
{
	MyGameLogic();
}//游戏逻辑处理  处理GameState

void EngineTest::MyGameLogic()//用以封装实验八的游戏逻辑函数
{
	if (GameState == GAME_START)
	{
		//UpdateFrames();
		//UpdatePos();

		GameKeyAction();//处理快速游戏按键
		UpdateNpcPos();//移动NPC
		if (player->IsActive())
		{
			if (op == 1)
			{
				//计算角色图形矩形的中心点
				long centerX = player->GetX() + (player->GetRatioSize().cx / 2);
				long centerY = player->GetY() + (player->GetRatioSize().cy / 2);

				POINT centerPT = { centerX,centerY };
				//POINT centerPT2 = { centerX,centerY };
				//centerPT.x = centerX;
				//centerPT.y = centerY;
				//直接调用构造函数赋值不行，原因是用了圆括号
				//原：POINT centerPT = (centerX,centerY);
				//角色朝鼠标位置移动，中心点到达鼠标位置表示到达目的地
				player->MoveTo(mouse_pt, centerPT, barrier);
			}
			if (op == 0)
			{
				UpdatePlayerPos(player->GetDir());
				//移动玩家角色
			}
			UpdateAnimation();//更新动画
		}
	}

}

void EngineTest::GamePaint(HDC hdc)	//游戏显示	参数值为GameState
{
	if (GameState == GAME_RUN)
	{
		t_menu.DrawMenu(hdc);
		PaintMyText(hdc);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = 0.00;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 4;
		T_Graph::PaintText(hdc, textRec, L"主菜单", 36, L"黑体", Color::White, FontStyleBold, StringAlignmentCenter);
	}

	if (GameState == GAME_ABOUT)
	{

		t_menuAbout.DrawMenu(hdc);
		PaintMyAbout(hdc);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = 0.00;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 4;
		T_Graph::PaintText(hdc, textRec, L"关于", 36, L"黑体",
			Color::White, FontStyleBold, StringAlignmentCenter);
	}

	if (GameState == GAME_HELP)
	{
		t_menuHelp.DrawMenu(hdc);
		PaintMyHelp(hdc);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = 0.00;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 4;
		T_Graph::PaintText(hdc, textRec, L"帮助", 36, L"黑体",
			Color::White, FontStyleBold, StringAlignmentCenter);
	}

	if (GameState == GAME_START)
	{
		//my_menu.DestroyAll();
		MyGamePaint(hdc);

		if (display_menu == true)
		{
			my_menu.DrawMenu(hdc);//显示菜单

		}
		else if (display_menu == false)
		{
			my_menu2.DrawMenu(hdc);//隐藏菜单
		}

		RectF captionRec;
		captionRec.X = 0.00;
		captionRec.Y = 0.00;
		captionRec.Width = (float)wnd_width;
		captionRec.Height = 60.0f;
		LPCTSTR caption = L"实验十";
		T_Graph::PaintText(hdc, captionRec, caption, 22, L"微软雅黑", Color::White, FontStyleBold, StringAlignmentNear);

	}
}

void EngineTest::GameEnd() {
	GameState = GAME_OVER;
}				//游戏结束处理

				//游戏按键处理
void EngineTest::GameKeyAction(int Action)
{
	//如果游戏运行时，执行游戏按键处理动作
	//如果不是GAME_START状态，则执行菜单按键操作

	if (GameState == GAME_START)
	{
		MyGameKeyAction(Action);
	}
	else
	{
		MyMenuKeyAction(Action);
	}


}
//游戏鼠标行为处理	参数值为KEY_MOUSE_ACTION
void EngineTest::GameMouseAction(int x, int y, int Action)
{

	if (Action == MOUSE_MOVE)
	{
		if (GameState == GAME_RUN)
		{
			t_menu.MenuMouseMove(x, y);
		}
		if (GameState == GAME_ABOUT)
		{
			t_menuAbout.MenuMouseMove(x, y);
		}
		if (GameState == GAME_HELP)
		{
			t_menuHelp.MenuMouseMove(x, y);
		}
		if (GameState == GAME_START)
		{
			MyGameMouseAction(x, y, Action);
		}
	}

	if (Action == MOUSE_LCLICK)
	{
		if (GameState == GAME_RUN)
		{
			int index = t_menu.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (t_menu.GetMenuIndex())
				{
				case 0://添加新游戏代码
					GameState = GAME_START;
					break;
				case 1://添加关于代码
					GameState = GAME_ABOUT;
					break;
				case 2://添加帮助代码
					GameState = GAME_HELP;
					break;
				case 3:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					//exit(0);
					break;
				}
			}
		}
		if (GameState == GAME_ABOUT)
		{
			int index = t_menuAbout.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (t_menuAbout.GetMenuIndex())
				{
				case 0://添加新游戏代码
					GameState = GAME_START;
					break;
				case 1://添加返回代码
					GameState = GAME_RUN;
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
		if (GameState == GAME_HELP)
		{
			int index = t_menuHelp.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (t_menuHelp.GetMenuIndex())
				{
				case 0://添加新游戏代码
					GameState = GAME_START;
					break;
				case 1://添加关于代码
					GameState = GAME_ABOUT;
					break;
				case 2://添加返回代码
					GameState = GAME_RUN;
					break;
				case 3:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					//exit(0);
					break;
				}
			}
		}

		if (GameState == GAME_START)
		{
			if (GameState == GAME_START && display_menu == true)
			{
				int index = my_menu.MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (my_menu.GetMenuIndex())
					{
					case 0://返回
						GameState = GAME_RUN;
						break;
					case 1://退出
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						//EngineTest::GameEnd();
						break;
					case 2://隐藏
						   //my_menu.DestroyAll();
						display_menu = false;
						break;
						//exit(0);
					default:
						display_menu = false;
						break;

					}
				}
			}
			else if (GameState == GAME_START && display_menu == false)
			{
				int index = my_menu2.MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (my_menu2.GetMenuIndex())
					{
					case 0://显示菜单
						display_menu = true;

						//exit(0);
						break;
					default:
						display_menu = false;
						break;

					}
				}
			}


		}




	}
}





//在此处初始化主菜单、关于菜单、帮助菜单、游戏运行时菜单
void EngineTest::IntMyMenu()
{

	/*将x、y坐标修改如下，可以实现水平居中布局
	x =i*(btn_ width+MENU_SPACE)+(wndWidth - 4*btn_width - 3*MENU_SPACE)/2;
	y = wnd_height-2 *btn_height;
	*/

	/*将x、y坐标修改如下，可以实现双行双列布局
	int col=i%2;
	int row=i/2;
	x =col*(btn_ width+MENU_SPACE)+(wndWidth - 2*btn_width - *MENU_SPACE)/2;
	y = row*(btn_height+MENU_SPACE)+(wnd_height-2*btn_height-MENU_SPACE)/2;
	*/

	/*将按钮修改如下，可以改成圆形布局效果
	btn_ width= 120;
	btn_ height= 120;
	normalClr = Color::White;
	focusClr = Color:: Yellow;
	t_menu.SetBtnBmp(L".\\res\\redroundbtn.png", btn_width, btn_height);// 菜单项图片
	*/

	/*初始菜单*/
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;
	Color normalClr, focusClr;
	wstring menuItems[] = { L"新游戏",L"关于",L"帮助",L"退出" };
	t_menu.SetMenuBkg(L".\\res\\seabed.jpg");
	//长条形的按钮菜单项
	btn_width = 150;
	btn_height = 60;
	normalClr = Color::Red;
	focusClr = Color::White;
	t_menu.SetBtnBmp(L".\\res\\button150x120.png", btn_width, btn_height);
	//设置菜单信息
	MENU_INFO menuInfo;
	menuInfo.align = 1;//居中对齐
	menuInfo.space = MENU_SPACE;//菜单项之间的间隔距离
	menuInfo.width = btn_width;//菜单项宽高
	menuInfo.height = btn_height;
	menuInfo.fontName = L"黑体";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = normalClr;
	menuInfo.focusTextColor = focusClr;
	t_menu.SetMenuInfo(menuInfo);

	for (int i = 0; i < 4; i++)
	{
		//垂直居中布局的坐标
		x = (wndWidth - btn_width) / 8;
		y = i*(btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

		MENUITEM mItem;
		mItem.pos.x = x;//当前菜单项xy坐标
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];
		t_menu.AddMenuItem(mItem);
	}


	/*关于菜单*/
	int xAbout = 0, yAbout = 0;
	int btn_widthAbout = 0, btn_heightAbout = 0;
	Color normalClrAbout, focusClrAbout;
	wstring menuItemsAbout[] = { L"新游戏",L"返回",L"退出" };
	t_menuAbout.SetMenuBkg(L".\\res\\beach.jpg");

	btn_widthAbout = 120;
	btn_heightAbout = 120;
	normalClrAbout = Color::White;
	focusClrAbout = Color::Yellow;
	t_menuAbout.SetBtnBmp(L".\\res\\redroundbtn.png", btn_widthAbout, btn_heightAbout);// 菜单项图片
																					   //设置菜单信息
	MENU_INFO menuInfoAbout;
	menuInfoAbout.align = 1;//居中对齐
	menuInfoAbout.space = MENU_SPACE;//菜单项之间的间隔距离
	menuInfoAbout.width = btn_widthAbout;//菜单项宽高
	menuInfoAbout.height = btn_heightAbout;
	menuInfoAbout.fontName = L"黑体";
	menuInfoAbout.isBold = true;
	menuInfoAbout.normalTextColor = normalClrAbout;
	menuInfoAbout.focusTextColor = focusClrAbout;
	t_menuAbout.SetMenuInfo(menuInfoAbout);

	for (int i = 0; i < 3; i++)
	{
		int col = i % 3;
		xAbout = col*(btn_widthAbout + MENU_SPACE) + (wndWidth - 3 * btn_widthAbout) / 2;
		yAbout = wnd_height - 2 * btn_heightAbout;

		MENUITEM mItemAbout;
		mItemAbout.pos.x = xAbout;//当前菜单项xy坐标
		mItemAbout.pos.y = yAbout;
		mItemAbout.ItemName = menuItemsAbout[i];
		t_menuAbout.AddMenuItem(mItemAbout);
	}//wnd_height - 2 * btn_height

	 /*帮助菜单*/
	int xHelp = 0, yHelp = 0;
	int btn_widthHelp = 0, btn_heightHelp = 0;
	Color normalClrHelp, focusClrHelp;
	wstring menuItemsHelp[] = { L"新游戏",L"关于",L"返回",L"退出" };
	t_menuHelp.SetMenuBkg(L".\\res\\seafloor.jpg");
	btn_widthHelp = 120;
	btn_heightHelp = 120;
	normalClrHelp = Color::White;
	focusClrHelp = Color::Yellow;
	t_menuHelp.SetBtnBmp(L".\\res\\redroundbtn.png", btn_widthHelp, btn_heightHelp);// 菜单项图片
																					//设置菜单信息
	MENU_INFO menuInfoHelp;
	menuInfoHelp.align = 1;//居中对齐
	menuInfoHelp.space = MENU_SPACE;//菜单项之间的间隔距离
	menuInfoHelp.width = btn_widthHelp;//菜单项宽高
	menuInfoHelp.height = btn_heightHelp;
	menuInfoHelp.fontName = L"黑体";
	menuInfoHelp.isBold = true;
	menuInfoHelp.normalTextColor = normalClrHelp;
	menuInfoHelp.focusTextColor = focusClrHelp;
	t_menuHelp.SetMenuInfo(menuInfoHelp);

	for (int i = 0; i < 4; i++)
	{
		int col = i % 2;
		int row = i / 2;
		xHelp = col*(btn_widthHelp + MENU_SPACE) + (wndWidth - 2 * btn_widthHelp - MENU_SPACE) / 2;
		yHelp = row*(btn_heightHelp + MENU_SPACE) + (wnd_height - 2 * btn_heightHelp - MENU_SPACE);

		MENUITEM mItemHelp;
		mItemHelp.pos.x = xHelp;//当前菜单项xy坐标
		mItemHelp.pos.y = yHelp;
		mItemHelp.ItemName = menuItemsHelp[i];
		t_menuHelp.AddMenuItem(mItemHelp);
	}

	//运行时显示菜单
	int xGame = 0, yGame = 0;
	int btn_widthGame = 0, btn_heightGame = 0;
	Color normalClrGame, focusClrGame;
	wstring menuItemsGame[] = { L"返回",L"退出",L"隐藏" };
	//my_menu.SetMenuBkg(L".\\res\\menubkg.jpg");
	//长条形的按钮菜单项
	btn_widthGame = 250;
	btn_heightGame = 70;
	normalClrGame = Color::Red;
	focusClrGame = Color::White;
	my_menu.SetBtnBmp(L".\\res\\button.png", btn_widthGame, btn_heightGame);
	//设置菜单信息
	MENU_INFO menuInfoGame;
	menuInfoGame.align = 1;//居中对齐
	menuInfoGame.space = MENU_SPACE;//菜单项之间的间隔距离
	menuInfoGame.width = btn_widthGame;//菜单项宽高
	menuInfoGame.height = btn_heightGame;
	menuInfoGame.fontName = L"黑体";
	menuInfoGame.isBold = true;
	menuInfoGame.normalTextColor = normalClrGame;
	menuInfoGame.focusTextColor = focusClrGame;
	my_menu.SetMenuInfo(menuInfoGame);

	for (int i = 0; i < 3; i++)
	{
		//右上角的坐标
		x = (wndWidth - btn_widthGame);
		y = i*(btn_heightGame + MENU_SPACE);

		MENUITEM mItem;
		mItem.pos.x = x;//当前菜单项xy坐标
		mItem.pos.y = y;
		mItem.ItemName = menuItemsGame[i];
		my_menu.AddMenuItem(mItem);
	}

	//运行时隐藏菜单
	int xGame2 = 0, yGame2 = 0;
	int btn_widthGame2 = 0, btn_heightGame2 = 0;
	Color normalClrGame2, focusClrGame2;
	wstring menuItemsGame2[] = { L"菜单" };
	//my_menu.SetMenuBkg(L".\\res\\menubkg.jpg");
	//长条形的按钮菜单项
	btn_widthGame2 = 250;
	btn_heightGame2 = 70;
	normalClrGame2 = Color::Red;
	focusClrGame2 = Color::White;
	my_menu2.SetBtnBmp(L".\\res\\button.png", btn_widthGame2, btn_heightGame2);
	//设置菜单信息
	MENU_INFO menuInfoGame2;
	menuInfoGame2.align = 1;//居中对齐
	menuInfoGame2.space = MENU_SPACE;//菜单项之间的间隔距离
	menuInfoGame2.width = btn_widthGame2;//菜单项宽高
	menuInfoGame2.height = btn_heightGame2;
	menuInfoGame2.fontName = L"黑体";
	menuInfoGame2.isBold = true;
	menuInfoGame2.normalTextColor = normalClrGame2;
	menuInfoGame2.focusTextColor = focusClrGame2;
	my_menu2.SetMenuInfo(menuInfoGame2);

	for (int i = 0; i < 1; i++)
	{
		//右上角的坐标
		x = (wndWidth - btn_widthGame2);
		y = i*(btn_heightGame2 + MENU_SPACE);

		MENUITEM mItem;
		mItem.pos.x = x;//当前菜单项xy坐标
		mItem.pos.y = y;
		mItem.ItemName = menuItemsGame2[i];
		my_menu2.AddMenuItem(mItem);
	}
}

//角色与NPC初始化
void EngineTest::LoadPlayer()
{
	SPRITEINFO spInfo;
	player = new T_Sprite(L".\\res\\blockorange.png,80,80");
	spInfo.Active = false;
	spInfo.Dead = false;
	spInfo.Dir = DIR_UP;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.5f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 3;
	spInfo.Alpha = 255;
	spInfo.X = wnd_width / 5;
	spInfo.Y = (wnd_height - player->GetHeight()) / 2;
	spInfo.Visible = true;
	player->Initiate(spInfo);
	player->SetSequence(FRAME_UP, 20);
	player->SetLayerTypeID(LAYER_PLY);
}

void EngineTest::LoadNpc(int total)
{
	SPRITEINFO spInfo;
	for (int i = 0; i < total; i++)
	{
		spInfo.Active = true;
		spInfo.Dead = false;
		spInfo.Rotation = TRANS_NONE;
		spInfo.Ratio = 0.5f;
		spInfo.Speed = 2;
		spInfo.Alpha = 255;
		spInfo.Visible = true;
		spInfo.Level = 0;
		spInfo.Score = 0;
		int sp_width = 40;
		int sp_height = 40;
		//抽取随机方向
		int sdr = rand() % 4;
		int d = rand() % 2;
		switch (sdr)
		{
		case 0://左上角
			if (d == 0) spInfo.Dir = DIR_RIGHT;
			if (d == 1) spInfo.Dir = DIR_DOWN;
			spInfo.X = 0;
			spInfo.Y = 0;
			break;
		case 1://右上角
			if (d == 0) spInfo.Dir = DIR_LEFT;
			if (d == 1) spInfo.Dir = DIR_DOWN;
			spInfo.X = wnd_width - sp_width;
			spInfo.Y = 0;
			break;
		case 2://左下角
			if (d == 0) spInfo.Dir = DIR_RIGHT;
			if (d == 1) spInfo.Dir = DIR_UP;
			spInfo.X = 0;
			spInfo.Y = wnd_height - sp_height;
		case 3://右下角
			if (d == 0) spInfo.Dir = DIR_LEFT;
			if (d == 1) spInfo.Dir = DIR_UP;
			spInfo.X = wnd_width - sp_width;
			spInfo.Y = wnd_height - sp_height;
			break;
		}
		//在NPC列表中添加新的项目
		npc_set.push_back(new T_Sprite(L".\\res\\blockgreen.png", 80, 80));
		//初始化刚增加的项目
		T_Sprite *sp = npc_set.back();
		sp->Initiate(spInfo);
		switch (spInfo.Dir)
		{
		case DIR_LEFT:
			sp->SetSequence(FRAME_LEFT, 20);
			break;
		case DIR_RIGHT:
			sp->SetSequence(FRAME_RIGHT, 20);
			break;
		case DIR_UP:
			sp->SetSequence(FRAME_UP, 20);
			break;
		case DIR_DOWN:
			sp->SetSequence(FRAME_DOWN, 20);
			break;
		}
		sp->SetLayerTypeID(LAYER_NPC);
		sp = NULL;
	}
}

void EngineTest::LoadMap()
{
	//2020.12.10先写到这里吧
	LAYERINFO mapInfo;//定义地图信息结构体
					  //为结构体中的元素赋值
	mapInfo.first_gid = 1;//图块编号从1开始
	mapInfo.map_cols = MAP_COLS;//地图图块总列数
	mapInfo.map_rows = MAP_ROWS;//地图图块总行数
	mapInfo.tile_width = TILE_WIDTH;//图块宽
	mapInfo.tile_height = TILE_HEIGHT;//图块高
	mapInfo.tile_path = L".\\map\\desert.png";//图块文件路径名称
	vector<vector<int>>barrier_data;//保存障碍图层的vector容器
	vector<vector<int>>back_data;//保存背景图层的vector容器
	vector<int>row_data(MAP_COLS);//按照地图图块总列数构造的临时vector容器
	for (int r = 0; r < MAP_ROWS; r++)
	{
		//分别为障碍图层和背景图层的vector容器分配空间
		barrier_data.push_back(row_data);
		back_data.push_back(row_data);
	}
	for (int r = 0; r < MAP_ROWS; r++)
	{
		for (int c = 0; c < MAP_COLS; c++)
		{
			//由于背景只是用了图块文件中的一个图块，所以全部元素赋相同值；
			back_data[r][c] = MAP_BKG;
		}
	}
	mapInfo.type_id = LAYER_MAP_BACK;//设置图层类型
	mapInfo.data = back_data;//将以上的vector容器转存到地图信息结构体中
	back = new T_Map(mapInfo);//用完整的地图信息构造T_Map对象
	back->SetPosition(0, 0);//设置图层在窗口的初始位置
	back->setUpdate(true);//设置图层更新状态


						  //将BARRIER数组中的图块数据转存到vector容器中 
	for (int i = 0; i < MAP_ROWS*MAP_COLS; i++)
	{
		int col = i%MAP_COLS;
		int row = i / MAP_COLS;
		barrier_data[row][col] = BARRIER[i];
	}
	mapInfo.type_id = LAYER_MAP_BARR;//设置图层类型
	mapInfo.data = barrier_data;//将以上vector容器转存到地图信息结构体中
	barrier = new T_Map(mapInfo);
	barrier->SetPosition(0, 0);
	barrier->setUpdate(true);//设置图层更新状态

}

void EngineTest::UpdateAnimation()
{
	vSpriteSet::iterator p;
	if (npc_set.size() > 0)
	{
		for (p = npc_set.begin(); p != npc_set.end(); p++)
		{
			(*p)->LoopFrame();
		}
	}
	if (player != NULL)
	{
		if (player->IsVisible() == true && player->IsActive() == true)
		{
			player->LoopFrame();
		}
	}
}

void EngineTest::UpdateNpcPos()
{
	if (npc_set.size() == 0) return;
	//构造T_AI对象
	T_AI* spAi = new T_AI(4);
	//遍历全部NPC
	vSpriteSet::iterator p;
	for (p = npc_set.begin(); p != npc_set.end(); p++)
	{
		if ((*p)->IsActive() == true && (*p)->IsVisible() == true)
		{
			spAi->Evade((*p), player);//躲避玩家角色
			spAi->CheckOverlay((*p), npc_set);//防止相互重叠
			int npc_dir = (*p)->GetDir();//获取当前方向
										 //根据当前方向及时更新帧动画序列
			switch (npc_dir)
			{
			case DIR_LEFT:
				(*p)->SetSequence(FRAME_LEFT, 20);
				break;
			case DIR_RIGHT:
				(*p)->SetSequence(FRAME_RIGHT, 20);
				break;
			case DIR_UP:
				(*p)->SetSequence(FRAME_UP, 20);
				break;
			case DIR_DOWN:
				(*p)->SetSequence(FRAME_DOWN, 20);
				break;
			}
			//NPC在地图上漫游并自动检测地图障碍
			spAi->Wander((*p), npc_dir, (*p)->GetSpeed(), barrier);
		}
	}
	delete spAi;
}

void EngineTest::UpdatePlayerPos(int dir)
{
	if (player == NULL)return;
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;
	if (player->IsVisible() == true && player->IsActive() == true)
	{
		switch (dir)
		{
		case DIR_LEFT:
			SpeedX = -player->GetSpeed();
			SpeedY = 0;
			//计算下一步移动是否超过边界
			nextStepX = player->GetX() - player->GetSpeed();
			if (nextStepX <= 0)
				SpeedX = 0 - player->GetX();
			break;
		case DIR_RIGHT:
			SpeedX = player->GetSpeed();
			SpeedY = 0;
			//计算下一步移动是否超过边界
			nextStepX = player->GetX() + player->GetRatioSize().cx + player->GetSpeed();
			if (nextStepX >= wnd_width)
				SpeedX = wnd_width - player->GetRatioSize().cx - player->GetX();
			break;
		case DIR_UP:
			SpeedX = 0;
			SpeedY = -player->GetSpeed();
			//计算下一步移动是否超过边界边界边界边界
			nextStepY = player->GetY() - player->GetSpeed();
			if (nextStepY < 0)
				SpeedY = 0 - player->GetY();
			break;
		case DIR_DOWN:
			SpeedX = 0;
			SpeedY = player->GetSpeed();
			//计算越界
			nextStepY = player->GetY() + player->GetRatioSize().cy + player->GetSpeed();
			if (nextStepY >= wnd_height)
				SpeedY = wnd_height - player->GetRatioSize().cy - player->GetY();
			break;
		}
		int x = player->GetX();
		int y = player->GetY();
		if (!player->CollideWith(barrier))
		{
			//如果没碰障碍上
			player->Move(SpeedX, SpeedY);
		}
		if (player->CollideWith(barrier))
		{
			//碰上障碍，还原移动前的位置
			player->SetPosition(x, y);
		}

	}
}



//游戏游玩按键处理
void EngineTest::MyGameKeyAction(int Action)
{
	if (Action == KEY_DOWN)
	{
		if (CheckKey(VK_LEFT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_LEFT, 20);
			player->SetDir(DIR_LEFT);
			op = 0;
		}
		if (CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_RIGHT, 20);
			player->SetDir(DIR_RIGHT);
			op = 0;
		}
		if (CheckKey(VK_UP) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_UP, 20);
			player->SetDir(DIR_UP);
			op = 0;
		}
		if (CheckKey(VK_DOWN) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_DOWN, 20);
			player->SetDir(DIR_DOWN);
			op = 0;
		}
		if (CheckKey(VK_LEFT) == false && CheckKey(VK_RIGHT) == false && CheckKey(VK_UP) == false && CheckKey(VK_DOWN) == false && op == 0)
		{
			player->SetActive(false);
		}

	}
}//游戏按键响应

 //菜单按键处理
void EngineTest::MyMenuKeyAction(int Action)
{
	if (GameState == GAME_RUN)//游戏开始运行，显示初始菜单
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			t_menu.MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			t_menu.MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			t_menu.MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			t_menu.MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (t_menu.GetMenuIndex() >= 0) {
				//当菜单为默认菜单时相应操作

				switch (t_menu.GetMenuIndex())
				{
				case 0://添加新游戏代码
					GameState = GAME_START;
					//t_menu.DestroyAll();

					//EngineTest::IsPaintText = 1;
					break;
				case 1://添加关于代码
					GameState = GAME_ABOUT;
					//t_menu.DestroyAll();
					break;
				case 2://添加帮助代码
					GameState = GAME_HELP;
					//t_menu.DestroyAll();
					break;
				case 3:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					//exit(0);
					break;
				}
				t_menu.SetMenuIndex(-1);
			}

		}
	}
	if (GameState == GAME_ABOUT)//显示关于菜单
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			t_menuAbout.MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			t_menuAbout.MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			t_menuAbout.MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			t_menuAbout.MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (t_menuAbout.GetMenuIndex() >= 0) {
				//当菜单为默认菜单时相应操作

				switch (t_menuAbout.GetMenuIndex())
				{
				case 0://添加新游戏代码
					GameState = GAME_START;
					break;
				case 1://添加返回代码
					GameState = GAME_RUN;
					break;

				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					//exit(0);
					break;
				}
				t_menuAbout.SetMenuIndex(-1);

			}
		}


	}
	if (GameState == GAME_HELP)//显示帮助
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			t_menuHelp.MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			t_menuHelp.MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			t_menuHelp.MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			t_menuHelp.MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (t_menuHelp.GetMenuIndex() >= 0) {
				//当菜单为默认菜单时相应操作

				switch (t_menuHelp.GetMenuIndex())
				{
				case 0://添加新游戏代码
					GameState = GAME_START;
					break;
				case 1://添加关于代码
					GameState = GAME_ABOUT;
					break;
				case 2://添加返回代码
					GameState = GAME_RUN;
					break;
				case 3:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					//exit(0);
					break;
				}
				t_menuHelp.SetMenuIndex(-1);

			}
		}
	}
}

void EngineTest::MyGameMouseAction(int x, int y, int Action)
{
	mouse_pt.x = x;
	mouse_pt.y = y;
	op = 1;
	if (Action == MOUSE_MOVE)
	{
		player->SetActive(true);
		int sp_dir = player->GetDir(mouse_pt);
		player->SetDir(sp_dir);
		switch (sp_dir)
		{
		case DIR_LEFT:
			player->SetSequence(FRAME_LEFT, 20);
			break;
		case DIR_RIGHT:
			player->SetSequence(FRAME_RIGHT, 20);
			break;
		case DIR_UP:
			player->SetSequence(FRAME_UP, 20);
			break;
		case DIR_DOWN:
			player->SetSequence(FRAME_DOWN, 20);

		}
	}
}

//玩家与NPC绘制
void EngineTest::MyGamePaint(HDC hdc)
{
	back->Draw(hdc);
	barrier->Draw(hdc);
	vSpriteSet::iterator p;
	for (p = npc_set.begin(); p != npc_set.end(); p++)
	{
		if ((*p)->IsActive() == true && (*p)->IsVisible() == true)
		{
			(*p)->Draw(hdc);
		}

	}
	//player->Draw(hdc);
	//这里有问题，调用Draw返回时，指针会变成NULL
}


void EngineTest::PaintMyAbout(HDC hdc)
{
	if (GameState == GAME_ABOUT)
	{
		RectF captionRec;
		captionRec.X = 0.00;
		captionRec.Y = 0.00;
		captionRec.Width = (float)wnd_width;
		captionRec.Height = 60.0f;
		LPCTSTR caption = L"关于";
		T_Graph::PaintText(hdc, captionRec, caption, 22, L"微软雅黑", Color::White, FontStyleBold, StringAlignmentCenter);
		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height / 2 - 80);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 60;
		LPCTSTR info = L"姓名：李文齐 时间：2020年11月12日\n 班级：软工1809班 学号8002118239";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"宋体", Color::White, FontStyleBold, StringAlignmentCenter);
	}
}

void EngineTest::PaintMyHelp(HDC hdc)
{
	if (GameState == GAME_HELP)
	{
		RectF captionRec;
		captionRec.X = 0.00;
		captionRec.Y = 0.00;
		captionRec.Width = (float)wnd_width;
		captionRec.Height = 60.0f;
		LPCTSTR caption = L"帮助";
		T_Graph::PaintText(hdc, captionRec, caption, 22, L"微软雅黑", Color::White, FontStyleBold, StringAlignmentCenter);
		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height / 2 - 80);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 60;
		LPCTSTR info = L"通过上下左右方向键控制小鱼，\n躲避大怪，吃掉小怪";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"宋体", Color::White, FontStyleBold, StringAlignmentCenter);
	}
}

void EngineTest::PaintMyText(HDC hdc)
{
	if (GameState == GAME_RUN) {
		RectF captionRec;
		captionRec.X = 0.00;
		captionRec.Y = 0.00;
		captionRec.Width = (float)wnd_width;
		captionRec.Height = 60.0f;
		LPCTSTR caption = L"实验十综合实验";
		T_Graph::PaintText(hdc, captionRec, caption, 32, L"微软雅黑", Color::White, FontStyleBold, StringAlignmentNear);
		RectF infoRec;
		infoRec.X = 250;
		infoRec.Y = (REAL)(wnd_height / 2 - 200);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 400;
		LPCTSTR info = L" 姓名：李文齐\n学号8002118239\n选课班：选课2班\n原班级：软工1809班\n  时间：2020年12月3日";
		T_Graph::PaintText(hdc, infoRec, info, 20, L"宋体", Color::White, FontStyleBold, StringAlignmentCenter);
	}
	/*
	static void PaintText(HDC hdc, RectF fontRect, wstring text,
	REAL fontSize, wstring fontName,
	Color fontColor = Color::White,
	FontStyle style = FontStyleBold,
	StringAlignment align = StringAlignmentCenter);
	*/

}
