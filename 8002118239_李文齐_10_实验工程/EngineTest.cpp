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

//WinMain����
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"�������ʵ��ʮ";//��Ϸ���ڱ���//
	EngineTest* test = new EngineTest(h_instance, WIN_CLASS, WinTitle, IDI_SHARK, IDI_SHARK, 800, 600);
	T_Engine::pEngine = test;//������ľ�ָ̬��ָ����õ�����
	test->SetFrame(60);//���û���ˢ��Ƶ��

					   //myApp->SetFullScreen(TRUE);//ȫ������

	test->StartEngine();
	return TRUE;

}

EngineTest::EngineTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title, WORD icon, WORD sm_icon, int winwidth, int winheight, COLORREF bkColor)
	:T_Engine(h_instance, sz_winclass, sz_title, icon, sm_icon, winwidth, winheight, bkColor)
{
	srand((unsigned)time(NULL));
	wnd_width = winwidth;
	wnd_height = winheight;//��ȡ���ڿ��
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

}				//��Ϸ��ʼ���ӿں���

void EngineTest::GameLogic()
{
	MyGameLogic();
}//��Ϸ�߼�����  ����GameState

void EngineTest::MyGameLogic()//���Է�װʵ��˵���Ϸ�߼�����
{
	if (GameState == GAME_START)
	{
		//UpdateFrames();
		//UpdatePos();

		GameKeyAction();//���������Ϸ����
		UpdateNpcPos();//�ƶ�NPC
		if (player->IsActive())
		{
			if (op == 1)
			{
				//�����ɫͼ�ξ��ε����ĵ�
				long centerX = player->GetX() + (player->GetRatioSize().cx / 2);
				long centerY = player->GetY() + (player->GetRatioSize().cy / 2);

				POINT centerPT = { centerX,centerY };
				//POINT centerPT2 = { centerX,centerY };
				//centerPT.x = centerX;
				//centerPT.y = centerY;
				//ֱ�ӵ��ù��캯����ֵ���У�ԭ��������Բ����
				//ԭ��POINT centerPT = (centerX,centerY);
				//��ɫ�����λ���ƶ������ĵ㵽�����λ�ñ�ʾ����Ŀ�ĵ�
				player->MoveTo(mouse_pt, centerPT, barrier);
			}
			if (op == 0)
			{
				UpdatePlayerPos(player->GetDir());
				//�ƶ���ҽ�ɫ
			}
			UpdateAnimation();//���¶���
		}
	}

}

void EngineTest::GamePaint(HDC hdc)	//��Ϸ��ʾ	����ֵΪGameState
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
		T_Graph::PaintText(hdc, textRec, L"���˵�", 36, L"����", Color::White, FontStyleBold, StringAlignmentCenter);
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
		T_Graph::PaintText(hdc, textRec, L"����", 36, L"����",
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
		T_Graph::PaintText(hdc, textRec, L"����", 36, L"����",
			Color::White, FontStyleBold, StringAlignmentCenter);
	}

	if (GameState == GAME_START)
	{
		//my_menu.DestroyAll();
		MyGamePaint(hdc);

		if (display_menu == true)
		{
			my_menu.DrawMenu(hdc);//��ʾ�˵�

		}
		else if (display_menu == false)
		{
			my_menu2.DrawMenu(hdc);//���ز˵�
		}

		RectF captionRec;
		captionRec.X = 0.00;
		captionRec.Y = 0.00;
		captionRec.Width = (float)wnd_width;
		captionRec.Height = 60.0f;
		LPCTSTR caption = L"ʵ��ʮ";
		T_Graph::PaintText(hdc, captionRec, caption, 22, L"΢���ź�", Color::White, FontStyleBold, StringAlignmentNear);

	}
}

void EngineTest::GameEnd() {
	GameState = GAME_OVER;
}				//��Ϸ��������

				//��Ϸ��������
void EngineTest::GameKeyAction(int Action)
{
	//�����Ϸ����ʱ��ִ����Ϸ����������
	//�������GAME_START״̬����ִ�в˵���������

	if (GameState == GAME_START)
	{
		MyGameKeyAction(Action);
	}
	else
	{
		MyMenuKeyAction(Action);
	}


}
//��Ϸ�����Ϊ����	����ֵΪKEY_MOUSE_ACTION
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
				case 0://�������Ϸ����
					GameState = GAME_START;
					break;
				case 1://��ӹ��ڴ���
					GameState = GAME_ABOUT;
					break;
				case 2://��Ӱ�������
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
				case 0://�������Ϸ����
					GameState = GAME_START;
					break;
				case 1://��ӷ��ش���
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
				case 0://�������Ϸ����
					GameState = GAME_START;
					break;
				case 1://��ӹ��ڴ���
					GameState = GAME_ABOUT;
					break;
				case 2://��ӷ��ش���
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
					case 0://����
						GameState = GAME_RUN;
						break;
					case 1://�˳�
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						//EngineTest::GameEnd();
						break;
					case 2://����
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
					case 0://��ʾ�˵�
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





//�ڴ˴���ʼ�����˵������ڲ˵��������˵�����Ϸ����ʱ�˵�
void EngineTest::IntMyMenu()
{

	/*��x��y�����޸����£�����ʵ��ˮƽ���в���
	x =i*(btn_ width+MENU_SPACE)+(wndWidth - 4*btn_width - 3*MENU_SPACE)/2;
	y = wnd_height-2 *btn_height;
	*/

	/*��x��y�����޸����£�����ʵ��˫��˫�в���
	int col=i%2;
	int row=i/2;
	x =col*(btn_ width+MENU_SPACE)+(wndWidth - 2*btn_width - *MENU_SPACE)/2;
	y = row*(btn_height+MENU_SPACE)+(wnd_height-2*btn_height-MENU_SPACE)/2;
	*/

	/*����ť�޸����£����Ըĳ�Բ�β���Ч��
	btn_ width= 120;
	btn_ height= 120;
	normalClr = Color::White;
	focusClr = Color:: Yellow;
	t_menu.SetBtnBmp(L".\\res\\redroundbtn.png", btn_width, btn_height);// �˵���ͼƬ
	*/

	/*��ʼ�˵�*/
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;
	Color normalClr, focusClr;
	wstring menuItems[] = { L"����Ϸ",L"����",L"����",L"�˳�" };
	t_menu.SetMenuBkg(L".\\res\\seabed.jpg");
	//�����εİ�ť�˵���
	btn_width = 150;
	btn_height = 60;
	normalClr = Color::Red;
	focusClr = Color::White;
	t_menu.SetBtnBmp(L".\\res\\button150x120.png", btn_width, btn_height);
	//���ò˵���Ϣ
	MENU_INFO menuInfo;
	menuInfo.align = 1;//���ж���
	menuInfo.space = MENU_SPACE;//�˵���֮��ļ������
	menuInfo.width = btn_width;//�˵�����
	menuInfo.height = btn_height;
	menuInfo.fontName = L"����";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = normalClr;
	menuInfo.focusTextColor = focusClr;
	t_menu.SetMenuInfo(menuInfo);

	for (int i = 0; i < 4; i++)
	{
		//��ֱ���в��ֵ�����
		x = (wndWidth - btn_width) / 8;
		y = i*(btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

		MENUITEM mItem;
		mItem.pos.x = x;//��ǰ�˵���xy����
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];
		t_menu.AddMenuItem(mItem);
	}


	/*���ڲ˵�*/
	int xAbout = 0, yAbout = 0;
	int btn_widthAbout = 0, btn_heightAbout = 0;
	Color normalClrAbout, focusClrAbout;
	wstring menuItemsAbout[] = { L"����Ϸ",L"����",L"�˳�" };
	t_menuAbout.SetMenuBkg(L".\\res\\beach.jpg");

	btn_widthAbout = 120;
	btn_heightAbout = 120;
	normalClrAbout = Color::White;
	focusClrAbout = Color::Yellow;
	t_menuAbout.SetBtnBmp(L".\\res\\redroundbtn.png", btn_widthAbout, btn_heightAbout);// �˵���ͼƬ
																					   //���ò˵���Ϣ
	MENU_INFO menuInfoAbout;
	menuInfoAbout.align = 1;//���ж���
	menuInfoAbout.space = MENU_SPACE;//�˵���֮��ļ������
	menuInfoAbout.width = btn_widthAbout;//�˵�����
	menuInfoAbout.height = btn_heightAbout;
	menuInfoAbout.fontName = L"����";
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
		mItemAbout.pos.x = xAbout;//��ǰ�˵���xy����
		mItemAbout.pos.y = yAbout;
		mItemAbout.ItemName = menuItemsAbout[i];
		t_menuAbout.AddMenuItem(mItemAbout);
	}//wnd_height - 2 * btn_height

	 /*�����˵�*/
	int xHelp = 0, yHelp = 0;
	int btn_widthHelp = 0, btn_heightHelp = 0;
	Color normalClrHelp, focusClrHelp;
	wstring menuItemsHelp[] = { L"����Ϸ",L"����",L"����",L"�˳�" };
	t_menuHelp.SetMenuBkg(L".\\res\\seafloor.jpg");
	btn_widthHelp = 120;
	btn_heightHelp = 120;
	normalClrHelp = Color::White;
	focusClrHelp = Color::Yellow;
	t_menuHelp.SetBtnBmp(L".\\res\\redroundbtn.png", btn_widthHelp, btn_heightHelp);// �˵���ͼƬ
																					//���ò˵���Ϣ
	MENU_INFO menuInfoHelp;
	menuInfoHelp.align = 1;//���ж���
	menuInfoHelp.space = MENU_SPACE;//�˵���֮��ļ������
	menuInfoHelp.width = btn_widthHelp;//�˵�����
	menuInfoHelp.height = btn_heightHelp;
	menuInfoHelp.fontName = L"����";
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
		mItemHelp.pos.x = xHelp;//��ǰ�˵���xy����
		mItemHelp.pos.y = yHelp;
		mItemHelp.ItemName = menuItemsHelp[i];
		t_menuHelp.AddMenuItem(mItemHelp);
	}

	//����ʱ��ʾ�˵�
	int xGame = 0, yGame = 0;
	int btn_widthGame = 0, btn_heightGame = 0;
	Color normalClrGame, focusClrGame;
	wstring menuItemsGame[] = { L"����",L"�˳�",L"����" };
	//my_menu.SetMenuBkg(L".\\res\\menubkg.jpg");
	//�����εİ�ť�˵���
	btn_widthGame = 250;
	btn_heightGame = 70;
	normalClrGame = Color::Red;
	focusClrGame = Color::White;
	my_menu.SetBtnBmp(L".\\res\\button.png", btn_widthGame, btn_heightGame);
	//���ò˵���Ϣ
	MENU_INFO menuInfoGame;
	menuInfoGame.align = 1;//���ж���
	menuInfoGame.space = MENU_SPACE;//�˵���֮��ļ������
	menuInfoGame.width = btn_widthGame;//�˵�����
	menuInfoGame.height = btn_heightGame;
	menuInfoGame.fontName = L"����";
	menuInfoGame.isBold = true;
	menuInfoGame.normalTextColor = normalClrGame;
	menuInfoGame.focusTextColor = focusClrGame;
	my_menu.SetMenuInfo(menuInfoGame);

	for (int i = 0; i < 3; i++)
	{
		//���Ͻǵ�����
		x = (wndWidth - btn_widthGame);
		y = i*(btn_heightGame + MENU_SPACE);

		MENUITEM mItem;
		mItem.pos.x = x;//��ǰ�˵���xy����
		mItem.pos.y = y;
		mItem.ItemName = menuItemsGame[i];
		my_menu.AddMenuItem(mItem);
	}

	//����ʱ���ز˵�
	int xGame2 = 0, yGame2 = 0;
	int btn_widthGame2 = 0, btn_heightGame2 = 0;
	Color normalClrGame2, focusClrGame2;
	wstring menuItemsGame2[] = { L"�˵�" };
	//my_menu.SetMenuBkg(L".\\res\\menubkg.jpg");
	//�����εİ�ť�˵���
	btn_widthGame2 = 250;
	btn_heightGame2 = 70;
	normalClrGame2 = Color::Red;
	focusClrGame2 = Color::White;
	my_menu2.SetBtnBmp(L".\\res\\button.png", btn_widthGame2, btn_heightGame2);
	//���ò˵���Ϣ
	MENU_INFO menuInfoGame2;
	menuInfoGame2.align = 1;//���ж���
	menuInfoGame2.space = MENU_SPACE;//�˵���֮��ļ������
	menuInfoGame2.width = btn_widthGame2;//�˵�����
	menuInfoGame2.height = btn_heightGame2;
	menuInfoGame2.fontName = L"����";
	menuInfoGame2.isBold = true;
	menuInfoGame2.normalTextColor = normalClrGame2;
	menuInfoGame2.focusTextColor = focusClrGame2;
	my_menu2.SetMenuInfo(menuInfoGame2);

	for (int i = 0; i < 1; i++)
	{
		//���Ͻǵ�����
		x = (wndWidth - btn_widthGame2);
		y = i*(btn_heightGame2 + MENU_SPACE);

		MENUITEM mItem;
		mItem.pos.x = x;//��ǰ�˵���xy����
		mItem.pos.y = y;
		mItem.ItemName = menuItemsGame2[i];
		my_menu2.AddMenuItem(mItem);
	}
}

//��ɫ��NPC��ʼ��
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
		//��ȡ�������
		int sdr = rand() % 4;
		int d = rand() % 2;
		switch (sdr)
		{
		case 0://���Ͻ�
			if (d == 0) spInfo.Dir = DIR_RIGHT;
			if (d == 1) spInfo.Dir = DIR_DOWN;
			spInfo.X = 0;
			spInfo.Y = 0;
			break;
		case 1://���Ͻ�
			if (d == 0) spInfo.Dir = DIR_LEFT;
			if (d == 1) spInfo.Dir = DIR_DOWN;
			spInfo.X = wnd_width - sp_width;
			spInfo.Y = 0;
			break;
		case 2://���½�
			if (d == 0) spInfo.Dir = DIR_RIGHT;
			if (d == 1) spInfo.Dir = DIR_UP;
			spInfo.X = 0;
			spInfo.Y = wnd_height - sp_height;
		case 3://���½�
			if (d == 0) spInfo.Dir = DIR_LEFT;
			if (d == 1) spInfo.Dir = DIR_UP;
			spInfo.X = wnd_width - sp_width;
			spInfo.Y = wnd_height - sp_height;
			break;
		}
		//��NPC�б�������µ���Ŀ
		npc_set.push_back(new T_Sprite(L".\\res\\blockgreen.png", 80, 80));
		//��ʼ�������ӵ���Ŀ
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
	//2020.12.10��д�������
	LAYERINFO mapInfo;//�����ͼ��Ϣ�ṹ��
					  //Ϊ�ṹ���е�Ԫ�ظ�ֵ
	mapInfo.first_gid = 1;//ͼ���Ŵ�1��ʼ
	mapInfo.map_cols = MAP_COLS;//��ͼͼ��������
	mapInfo.map_rows = MAP_ROWS;//��ͼͼ��������
	mapInfo.tile_width = TILE_WIDTH;//ͼ���
	mapInfo.tile_height = TILE_HEIGHT;//ͼ���
	mapInfo.tile_path = L".\\map\\desert.png";//ͼ���ļ�·������
	vector<vector<int>>barrier_data;//�����ϰ�ͼ���vector����
	vector<vector<int>>back_data;//���汳��ͼ���vector����
	vector<int>row_data(MAP_COLS);//���յ�ͼͼ���������������ʱvector����
	for (int r = 0; r < MAP_ROWS; r++)
	{
		//�ֱ�Ϊ�ϰ�ͼ��ͱ���ͼ���vector��������ռ�
		barrier_data.push_back(row_data);
		back_data.push_back(row_data);
	}
	for (int r = 0; r < MAP_ROWS; r++)
	{
		for (int c = 0; c < MAP_COLS; c++)
		{
			//���ڱ���ֻ������ͼ���ļ��е�һ��ͼ�飬����ȫ��Ԫ�ظ���ֵͬ��
			back_data[r][c] = MAP_BKG;
		}
	}
	mapInfo.type_id = LAYER_MAP_BACK;//����ͼ������
	mapInfo.data = back_data;//�����ϵ�vector����ת�浽��ͼ��Ϣ�ṹ����
	back = new T_Map(mapInfo);//�������ĵ�ͼ��Ϣ����T_Map����
	back->SetPosition(0, 0);//����ͼ���ڴ��ڵĳ�ʼλ��
	back->setUpdate(true);//����ͼ�����״̬


						  //��BARRIER�����е�ͼ������ת�浽vector������ 
	for (int i = 0; i < MAP_ROWS*MAP_COLS; i++)
	{
		int col = i%MAP_COLS;
		int row = i / MAP_COLS;
		barrier_data[row][col] = BARRIER[i];
	}
	mapInfo.type_id = LAYER_MAP_BARR;//����ͼ������
	mapInfo.data = barrier_data;//������vector����ת�浽��ͼ��Ϣ�ṹ����
	barrier = new T_Map(mapInfo);
	barrier->SetPosition(0, 0);
	barrier->setUpdate(true);//����ͼ�����״̬

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
	//����T_AI����
	T_AI* spAi = new T_AI(4);
	//����ȫ��NPC
	vSpriteSet::iterator p;
	for (p = npc_set.begin(); p != npc_set.end(); p++)
	{
		if ((*p)->IsActive() == true && (*p)->IsVisible() == true)
		{
			spAi->Evade((*p), player);//�����ҽ�ɫ
			spAi->CheckOverlay((*p), npc_set);//��ֹ�໥�ص�
			int npc_dir = (*p)->GetDir();//��ȡ��ǰ����
										 //���ݵ�ǰ����ʱ����֡��������
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
			//NPC�ڵ�ͼ�����β��Զ�����ͼ�ϰ�
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
			//������һ���ƶ��Ƿ񳬹��߽�
			nextStepX = player->GetX() - player->GetSpeed();
			if (nextStepX <= 0)
				SpeedX = 0 - player->GetX();
			break;
		case DIR_RIGHT:
			SpeedX = player->GetSpeed();
			SpeedY = 0;
			//������һ���ƶ��Ƿ񳬹��߽�
			nextStepX = player->GetX() + player->GetRatioSize().cx + player->GetSpeed();
			if (nextStepX >= wnd_width)
				SpeedX = wnd_width - player->GetRatioSize().cx - player->GetX();
			break;
		case DIR_UP:
			SpeedX = 0;
			SpeedY = -player->GetSpeed();
			//������һ���ƶ��Ƿ񳬹��߽�߽�߽�߽�
			nextStepY = player->GetY() - player->GetSpeed();
			if (nextStepY < 0)
				SpeedY = 0 - player->GetY();
			break;
		case DIR_DOWN:
			SpeedX = 0;
			SpeedY = player->GetSpeed();
			//����Խ��
			nextStepY = player->GetY() + player->GetRatioSize().cy + player->GetSpeed();
			if (nextStepY >= wnd_height)
				SpeedY = wnd_height - player->GetRatioSize().cy - player->GetY();
			break;
		}
		int x = player->GetX();
		int y = player->GetY();
		if (!player->CollideWith(barrier))
		{
			//���û���ϰ���
			player->Move(SpeedX, SpeedY);
		}
		if (player->CollideWith(barrier))
		{
			//�����ϰ�����ԭ�ƶ�ǰ��λ��
			player->SetPosition(x, y);
		}

	}
}



//��Ϸ���水������
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
}//��Ϸ������Ӧ

 //�˵���������
void EngineTest::MyMenuKeyAction(int Action)
{
	if (GameState == GAME_RUN)//��Ϸ��ʼ���У���ʾ��ʼ�˵�
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
				//���˵�ΪĬ�ϲ˵�ʱ��Ӧ����

				switch (t_menu.GetMenuIndex())
				{
				case 0://�������Ϸ����
					GameState = GAME_START;
					//t_menu.DestroyAll();

					//EngineTest::IsPaintText = 1;
					break;
				case 1://��ӹ��ڴ���
					GameState = GAME_ABOUT;
					//t_menu.DestroyAll();
					break;
				case 2://��Ӱ�������
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
	if (GameState == GAME_ABOUT)//��ʾ���ڲ˵�
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
				//���˵�ΪĬ�ϲ˵�ʱ��Ӧ����

				switch (t_menuAbout.GetMenuIndex())
				{
				case 0://�������Ϸ����
					GameState = GAME_START;
					break;
				case 1://��ӷ��ش���
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
	if (GameState == GAME_HELP)//��ʾ����
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
				//���˵�ΪĬ�ϲ˵�ʱ��Ӧ����

				switch (t_menuHelp.GetMenuIndex())
				{
				case 0://�������Ϸ����
					GameState = GAME_START;
					break;
				case 1://��ӹ��ڴ���
					GameState = GAME_ABOUT;
					break;
				case 2://��ӷ��ش���
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

//�����NPC����
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
	//���������⣬����Draw����ʱ��ָ�����NULL
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
		LPCTSTR caption = L"����";
		T_Graph::PaintText(hdc, captionRec, caption, 22, L"΢���ź�", Color::White, FontStyleBold, StringAlignmentCenter);
		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height / 2 - 80);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 60;
		LPCTSTR info = L"������������ ʱ�䣺2020��11��12��\n �༶����1809�� ѧ��8002118239";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"����", Color::White, FontStyleBold, StringAlignmentCenter);
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
		LPCTSTR caption = L"����";
		T_Graph::PaintText(hdc, captionRec, caption, 22, L"΢���ź�", Color::White, FontStyleBold, StringAlignmentCenter);
		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height / 2 - 80);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 60;
		LPCTSTR info = L"ͨ���������ҷ��������С�㣬\n��ܴ�֣��Ե�С��";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"����", Color::White, FontStyleBold, StringAlignmentCenter);
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
		LPCTSTR caption = L"ʵ��ʮ�ۺ�ʵ��";
		T_Graph::PaintText(hdc, captionRec, caption, 32, L"΢���ź�", Color::White, FontStyleBold, StringAlignmentNear);
		RectF infoRec;
		infoRec.X = 250;
		infoRec.Y = (REAL)(wnd_height / 2 - 200);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 400;
		LPCTSTR info = L" ������������\nѧ��8002118239\nѡ�ΰࣺѡ��2��\nԭ�༶����1809��\n  ʱ�䣺2020��12��3��";
		T_Graph::PaintText(hdc, infoRec, info, 20, L"����", Color::White, FontStyleBold, StringAlignmentCenter);
	}
	/*
	static void PaintText(HDC hdc, RectF fontRect, wstring text,
	REAL fontSize, wstring fontName,
	Color fontColor = Color::White,
	FontStyle style = FontStyleBold,
	StringAlignment align = StringAlignmentCenter);
	*/

}
