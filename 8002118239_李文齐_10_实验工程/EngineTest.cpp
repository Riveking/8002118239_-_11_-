#include "EngineTest.h"
#include <stdio.h>


//int EngineTest::MYCHOOSEMENU = 1;
//ʵ��ʮ
FISHINFO EngineTest::fish[7] = {
	{L"blue.png",143,84},{ L"green.png",143,84 },{ L"orange.png",143,84 },{ L"pink.png",143,84 },{ L"red.png",143,84 },{ L"yellow.png",143,84 },{ L"clown.png",78,40 }
};

int EngineTest::sequence[20] = { 0,0,1,1,1,1,3,3,3,3,5,5,5,5,7,7,7,7,0,0 };

//WinMain����
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"�������ʵ��ʮ";//��Ϸ���ڱ���//
	EngineTest* test = new EngineTest(h_instance, WIN_CLASS, WinTitle,IDI_SHARK, IDI_SHARK, 800, 600);
	T_Engine::pEngine = test;//������ľ�ָ̬��ָ����õ�����
	test->SetFrame(60);//���û���ˢ��Ƶ��

	//myApp->SetFullScreen(TRUE);//ȫ������

	test->StartEngine();
	return TRUE;

}

EngineTest::EngineTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title, WORD icon, WORD sm_icon, int winwidth, int winheight)
	:T_Engine(h_instance,sz_winclass,sz_title,icon,sm_icon,winwidth,winheight)
{
	srand((unsigned)time(NULL));
	wnd_width = winwidth;
	wnd_height = winheight;//��ȡ���ڿ��
}

EngineTest::~EngineTest(void){}

static float myratio[7] = { 0.5,0.75,1,1.25,1.5,1.75,2.0 };

void EngineTest::GameInit(){
	//GameState = GAME_START;
	GameState = GAME_RUN;
	IntMyMenu();

	//ʵ��ʮ
	srand(GetTickCount());
	back = new T_Graph(L".\\res\\seafloor.jpg");
	sp_ai = new T_AI(8);
	LoadPlayer();
	LoadNpc(NUM);

}				//��Ϸ��ʼ���ӿں���
void EngineTest::GameLogic()
{
	MyGameLogic();
}//��Ϸ�߼�����  ����GameState


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
		T_Graph::PaintText(hdc, textRec, L"���˵�", 36, L"����",
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

void EngineTest::GameEnd(){
	delete player;
	player = NULL;
	delete back;
	back = NULL;
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
	mouse_pt.x = x;
	mouse_pt.y = y;

	//�������ʱ����Ϣ
	wstring str = L"X";
	str.append(T_Util::int_to_wstring(x));
	str.append(L"Y");
	str.append(T_Util::int_to_wstring(y));

	RectF rect;
	rect.X = 0;
	rect.Y = 0;
	rect.Width = wnd_width;
	rect.Height = wnd_height;
	T_Graph::PaintText(GetDC(m_hWnd), rect, str.c_str(), 32, L"����");

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



void EngineTest::PaintMyText(HDC hdc)
{
	if(GameState==GAME_RUN){
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

	
}


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

//�ڴ˴���ʼ�����˵������ڲ˵��������˵�����Ϸ����ʱ�˵�
void EngineTest::IntMyMenu()
{


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
		yAbout =wnd_height - 2 * btn_heightAbout;

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
	//�ƶ���ҽ�ɫ
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


void EngineTest::MyGameLogic()//���Է�װʵ��˵���Ϸ�߼�����
{
	if (GameState == GAME_START)
	{
		UpdateFrames();
		UpdatePos();
	}

}

//�����NPC����
void EngineTest::MyGamePaint(HDC hdc)
{
	back->PaintImage(hdc, 0, 0, wnd_width, wnd_height);
	for (int i = 0; i < NUM; i++)
	{
		npc[i]->Draw(hdc);
	}
	player->Draw(hdc);
}

//��Ϸ���水������
void EngineTest::MyGameKeyAction(int Action)
{

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

void EngineTest::PaintMyAbout(HDC hdc)
{
	if (GameState==GAME_ABOUT)
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

