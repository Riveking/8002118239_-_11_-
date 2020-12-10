#include "EngineTest.h"
#include <stdio.h>


//int EngineTest::MYCHOOSEMENU = 1;
//实验十
FISHINFO EngineTest::fish[7] = {
	{L"blue.png",143,84},{ L"green.png",143,84 },{ L"orange.png",143,84 },{ L"pink.png",143,84 },{ L"red.png",143,84 },{ L"yellow.png",143,84 },{ L"clown.png",78,40 }
};

int EngineTest::sequence[20] = { 0,0,1,1,1,1,3,3,3,3,5,5,5,5,7,7,7,7,0,0 };

//WinMain函数
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"李文齐的实验十";//游戏窗口标题//
	EngineTest* test = new EngineTest(h_instance, WIN_CLASS, WinTitle,IDI_SHARK, IDI_SHARK, 800, 600);
	T_Engine::pEngine = test;//将父类的静态指针指向构造好的子类
	test->SetFrame(60);//设置画面刷新频率

	//myApp->SetFullScreen(TRUE);//全屏启动

	test->StartEngine();
	return TRUE;

}

EngineTest::EngineTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title, WORD icon, WORD sm_icon, int winwidth, int winheight)
	:T_Engine(h_instance,sz_winclass,sz_title,icon,sm_icon,winwidth,winheight)
{
	srand((unsigned)time(NULL));
	wnd_width = winwidth;
	wnd_height = winheight;//获取窗口宽高
}

EngineTest::~EngineTest(void){}

static float myratio[7] = { 0.5,0.75,1,1.25,1.5,1.75,2.0 };

void EngineTest::GameInit(){
	//GameState = GAME_START;
	GameState = GAME_RUN;
	IntMyMenu();

	//实验十
	srand(GetTickCount());
	back = new T_Graph(L".\\res\\seafloor.jpg");
	sp_ai = new T_AI(8);
	LoadPlayer();
	LoadNpc(NUM);

}				//游戏初始化接口函数
void EngineTest::GameLogic()
{
	MyGameLogic();
}//游戏逻辑处理  处理GameState


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
		T_Graph::PaintText(hdc, textRec, L"主菜单", 36, L"黑体",
			Color::White, FontStyleBold, StringAlignmentCenter);
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

void EngineTest::GameEnd(){
	delete player;
	player = NULL;
	delete back;
	back = NULL;
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
	mouse_pt.x = x;
	mouse_pt.y = y;

	//输出测试时的信息
	wstring str = L"X";
	str.append(T_Util::int_to_wstring(x));
	str.append(L"Y");
	str.append(T_Util::int_to_wstring(y));

	RectF rect;
	rect.X = 0;
	rect.Y = 0;
	rect.Width = wnd_width;
	rect.Height = wnd_height;
	T_Graph::PaintText(GetDC(m_hWnd), rect, str.c_str(), 32, L"黑体");

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
			my_menu.MenuMouseMove(x, y);
			int p_dir = player->GetDir(mouse_pt);
			player->SetDir(p_dir);
			switch (p_dir)
			{
			case DIR_LEFT:
			case DIR_LEFT_UP:
			case DIR_LEFT_DOWN:
				player->SetRotation(TRANS_NONE);
				break;
			case DIR_RIGHT:
			case DIR_RIGHT_DOWN:
			case DIR_RIGHT_UP:
				player->SetRotation(TRANS_HFLIP_NOROT);
				break;
			case DIR_UP:
			case DIR_DOWN:
				break;


			}
			player->SetActive(true);
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



void EngineTest::PaintMyText(HDC hdc)
{
	if(GameState==GAME_RUN){
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

	
}


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

//在此处初始化主菜单、关于菜单、帮助菜单、游戏运行时菜单
void EngineTest::IntMyMenu()
{


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
		yAbout =wnd_height - 2 * btn_heightAbout;

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
	int x = 0;
	int y = 0;
	player = new T_Sprite(L".\\res\\fish\\purplefish.png", 176, 111);
	SPRITEINFO spInfo;
	spInfo.Active = true;
	spInfo.Alpha = 255;
	spInfo.Dead = false;
	spInfo.Dir = DIR_LEFT;
	spInfo.Level = 0;
	spInfo.Ratio = 0.8f;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Score = 0;
	spInfo.Speed = 10;
	spInfo.Visible = true;
	player->Initiate(spInfo);
	x = (wnd_width - player->GetRatioSize().cx) / 2;
	y = (wnd_height - player->GetRatioSize().cy) / 2;
	player->SetPosition(x, y);
	player->SetSequence(sequence, 20);
}

void EngineTest::LoadNpc(int num)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < num; i++)
	{
		int r = rand() % 7;
		wstring path = L".\\res\\fish\\";
		path.append(fish[r].filename);
		npc[i] = new T_Sprite(path.c_str(), fish[r].wframe, fish[r].hframe);
		SPRITEINFO spInfo;
		spInfo.Active = true;
		spInfo.Alpha = 255;
		spInfo.Dead = false;
		spInfo.Dir = DIR_LEFT;
		spInfo.Level = 0;
		spInfo.Ratio = 1.0f;
		spInfo.Rotation = TRANS_NONE;
		spInfo.Score = 0;
		spInfo.Speed = 3;
		spInfo.Visible = true;
		npc[i]->Initiate(spInfo);
		x = rand()%(wnd_width - npc[i]->GetRatioSize().cx);
		y = rand()%(wnd_height - npc[i]->GetRatioSize().cy);
		npc[i]->SetPosition(x, y);
	}
}

void EngineTest::UpdateFrames()
{
	player->LoopFrame();
	for(int i = 0; i < NUM; i++)
	{
		npc[i]->LoopFrame();
	}
}

void EngineTest::UpdatePos()
{
	//移动玩家角色
	if (player->IsActive() == true)
	{
		long centerX = player->GetX() + (player->GetRatioSize().cx / 2);
		long centerY = player->GetY() + (player->GetRatioSize().cy / 2);
		POINT centerPT = { centerX,centerY};
		RECT WinRECT = { 0,0,wnd_width,wnd_height };
		player->MoveTo(mouse_pt, centerPT, WinRECT);
	}
	int npc_dir = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (npc[i]->IsActive() == true && npc[i]->IsVisible() == true)
		{
			npc_dir = npc[i]->GetDir();
			switch (npc_dir)
			{
			case DIR_LEFT:
			case DIR_LEFT_UP:
			case DIR_LEFT_DOWN:
						npc[i]->SetRotation(TRANS_NONE);
						break;
			case DIR_RIGHT:
			case DIR_RIGHT_UP:
			case DIR_RIGHT_DOWN:
				npc[i]->SetRotation(TRANS_HFLIP_NOROT);
			case DIR_UP:
			case DIR_DOWN:
				break;
			default:
				break;
			}
		}
		RECT npc_move_bound;
		npc_move_bound.left = -200;
		npc_move_bound.top = 0;
		npc_move_bound.right = wnd_width + 200;
		npc_move_bound.bottom = wnd_height - npc[i]->GetHeight();
		sp_ai->Wander(npc[i], npc_dir, npc[i]->GetSpeed(), npc_move_bound);
		sp_ai->Evade(npc[i], player);

	}
}


void EngineTest::MyGameLogic()//用以封装实验八的游戏逻辑函数
{
	if (GameState == GAME_START)
	{
		UpdateFrames();
		UpdatePos();
	}

}

//玩家与NPC绘制
void EngineTest::MyGamePaint(HDC hdc)
{
	back->PaintImage(hdc, 0, 0, wnd_width, wnd_height);
	for (int i = 0; i < NUM; i++)
	{
		npc[i]->Draw(hdc);
	}
	player->Draw(hdc);
}

//游戏游玩按键处理
void EngineTest::MyGameKeyAction(int Action)
{

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

void EngineTest::PaintMyAbout(HDC hdc)
{
	if (GameState==GAME_ABOUT)
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

