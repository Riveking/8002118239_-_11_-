//*******************************************************************
// TinyEngine����  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2013-08-02
// ��Ȩ���� 2007-2020 ������
// (C) 2007-2020 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Sprite.h"

T_Sprite::T_Sprite(LPCTSTR imgPath, int frameWidth, int frameHeight)
{
	if(wcslen(imgPath)>0)
	{
		spImg.LoadImageFile(imgPath);
		spOldImg = spImg;
	}
	else
	{
		throw L"ͼ��·��Ϊ��!";
	}
	
	// �޶����Ľ�ɫͼƬ
	if(frameWidth==0 && frameHeight==0)
	{
		SetWidth(spImg.GetImageWidth());
		SetHeight(spImg.GetImageHeight());

		totalFrames = rawFrames = 0; // ������֡��
	}
	else// ���ж����Ľ�ɫͼƬ
	{
		SetWidth(frameWidth);
		SetHeight(frameHeight);

		frameCols = spImg.GetImageWidth()/frameWidth;		// ����֡ͼƬ������
		frameRows = spImg.GetImageHeight()/frameHeight;	// ����֡ͼƬ������
		totalFrames = frameCols*frameRows;					// ������֡��
		rawFrames = frameCols*frameRows;					// ��¼ԭʼ������֡��
		forward = 0;									// ��ǰ֡������ʼ��
		backward = totalFrames-1;
	}
	

	frameSequence = NULL;
	loopForward = true;

	mapBlockPT.x = -1;
	mapBlockPT.y = -1;
}

T_Sprite::~T_Sprite(void)
{
}

void T_Sprite::Initiate(SPRITEINFO spInfo)
{								
	SetPosition(spInfo.X, spInfo.Y);	// ��ɫ����
	Visible = spInfo.Visible;			// ��ɫ�Ƿ�ɼ�
	dir = spInfo.Dir;					// ��ɫ����
	active = spInfo.Active;				// ��ɫ״̬���Ƿ��ƶ���
	speed = spInfo.Speed;				// ��ɫ�ƶ��ٶ�
	dead = spInfo.Dead;					// ��ɫ����״̬
	level = spInfo.Level;				// ��ɫ�ȼ�
	score = spInfo.Score;				// ��ɫ��ɫ��ֵ 
	frameRatio = spInfo.Ratio;			// ֡ͼƬ���ű�(����1ԭʼ������1�Ŵ�С��1��С)
	frameRotate = spInfo.Rotation;		// ֡ͼƬ�Ƿ���ת�任(TRANSFERֵ֮һ)
	frameAlpha = spInfo.Alpha;			// ֡ͼƬ͸����
	if(frameRatio>0) 
	{
		colideWidth = GetRatioSize().cx;
		colideHeight = GetRatioSize().cy;
	}
	else
	{
		colideWidth = (int)GetWidth();
		colideHeight =  (int)GetHeight();
	}
}

//��ǰ������ѭ����������֡
void T_Sprite::LoopFrame(bool ahead)
{	
	loopForward = ahead;
	if(totalFrames>0)
	{
		if(ahead == true)
		{
			forward = forward + 1;
			if(forward > totalFrames-1) 
			{
				forward = 0; 
			}
		}
		else
		{
			backward = backward - 1;
			if(backward < 0) 
			{
				backward = totalFrames-1;
			}
		}
	}
}

bool T_Sprite::LoopFrameOnce(bool ahead)
{
	loopForward = ahead;
	if(totalFrames<=0) return true;
	if(totalFrames>0)
	{
		if(ahead == true)
		{
			forward = forward + 1;
			if(forward > totalFrames-1) 
			{
				forward = 0; 
				return true;//������һ������֡
			}
			else
			{
				return false;
			}
		}
		if(ahead == false)
		{
			backward = backward - 1;
			if(backward < 0) 
			{
				backward = totalFrames-1;
				return true;//������һ������֡
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void T_Sprite::Draw(HDC hdc)
{
	int frmIndex = 0;
	if(frameSequence != NULL && backward>=0 && forward>=0)
	{
		if(loopForward == false)
			frmIndex = frameSequence[backward];
		else
			frmIndex = frameSequence[forward];
	}
	else
	{
		if(loopForward == false)
			frmIndex = backward;
		else
			frmIndex = forward;
	}

	if(&spImg != NULL)
	{
		if(Visible == true)
		{
			if(totalFrames==0)
			{
				spImg.PaintRegion(
					spImg.GetBmpHandle(), hdc, (int)X, (int)Y, 
					0, 0, Width, Height, frameRatio, frameRotate, frameAlpha
				);
			}
			else
			{
				spImg.PaintFrame(
					spImg.GetBmpHandle(), hdc, (int)X, (int)Y, frmIndex,  
					frameCols, Width, Height, frameRatio, frameRotate, frameAlpha
				);
			}
		}
	}
}

bool T_Sprite::MoveTo(IN POINT mousePT, IN POINT desPT, IN RECT Boundary)
{
	//ʹ�������½�ɫλ��
	//
	//����Ƿ񵽴�Ŀ�ĵأ�ʹ�õĹؼ�������PtInRect
	//���ݽ�ɫ��ǰλ�ý���һ���������򣬼��û�����Ƿ��������
	//ע�⣬��������̫С���������ɲ���
	//��ָ����(desPT)����5������Ϊ������ȽϺ���
	//����û������������λ�ã����ʾ��ɫ�Ѿ��Ƶ���Ŀ�ĵ�
	//�������Ŀ�ĵأ����ɫͣ�ڼ������
	//
	int  xRatio, yRatio; 
	if(active == true)
	{
		SIZE ratioFrameSize = GetRatioSize();	//�������ź��֡ͼ�ߴ�
		RECT HotRect;//����õľ�������(ָ��������5������Ϊ�����)
		HotRect.left = (long)(desPT.x-5);
		HotRect.top = (long)(desPT.y-5);
		HotRect.right = (long)(desPT.x+5);
		HotRect.bottom = (long)(desPT.y+5);

		//���ݵ�ǰ������ϴ���������x, y���λ�ƾ���
		T_Util::GetBevelSpeed(desPT, mousePT, speed, xRatio, yRatio);

		BOOL ToDesPos = PtInRect(&HotRect, mousePT);

		if(ToDesPos == TRUE)
		{
			return true;
		}
		if(ToDesPos == FALSE)
		{		
			//������һ��Ҫ�ƶ��������ﵽ�򳬹��߽�ʱ�ƶ��Ĳ���
			//int nextStepX = (int)(Speed*xRatio);
			//int nextStepY = (int)(Speed*yRatio);

			int nextStepX = (int)xRatio;
			int nextStepY = (int)yRatio;

			POINT nextPT = {(long)(GetX()+nextStepX), (long)(GetY()+nextStepY)};
			if(nextPT.x <=Boundary.left) 
				nextStepX = Boundary.left - (int)GetX();
			if((nextPT.x+ratioFrameSize.cx) >=Boundary.right) 
				nextStepX = Boundary.right - ratioFrameSize.cx - (int)GetX();
			if(nextPT.y <=Boundary.top) 
				nextStepY = Boundary.top - (int)GetY();
			if((nextPT.y+ratioFrameSize.cy) >=Boundary.bottom) 
				nextStepY = Boundary.bottom - ratioFrameSize.cy - (int)GetY();

			Move(nextStepX, nextStepY);	

			return false;
		}
	}
	return true;
}

//��������жϷ���
int T_Sprite::GetDir(POINT mousePT)
{
	int dir = -1;
	POINT spNowXY = {(long)GetX(),(long)GetY()};

	//�������ź��֡ͼ�ߴ�
	SIZE ratioFrameSize = GetRatioSize();
	
	//���ս�ɫ�����������ο���������
	//��Ϊ���յľ������򣨸��ݽ�ɫ��ǰ��������ã�
	RECT SpriteRect;
	SpriteRect.left = (long)GetX();
	SpriteRect.top = (long)GetY();
	SpriteRect.right = (long)(GetX() + ratioFrameSize.cx);
	SpriteRect.bottom = (long)(GetY() + ratioFrameSize.cy);

	//�жϳ�������
	if( mousePT.x <= SpriteRect.left && 
		mousePT.y >= SpriteRect.top && 
		mousePT.y <= SpriteRect.bottom)
	{
		dir = DIR_LEFT;
	}
	else if(mousePT.x >= SpriteRect.right && 
		mousePT.y >= SpriteRect.top && mousePT.y <= SpriteRect.bottom)
	{
		dir = DIR_RIGHT;
	}
	else if(mousePT.y <= (SpriteRect.bottom-ratioFrameSize.cy/2) &&
		mousePT.x > SpriteRect.left && mousePT.x < SpriteRect.right)
	{
		dir = DIR_UP;
	}
	else if(mousePT.y > (SpriteRect.bottom-ratioFrameSize.cy/2) &&
		mousePT.x > SpriteRect.left && mousePT.x < SpriteRect.right)
	{
		dir = DIR_DOWN;
	}
	else if(mousePT.x < SpriteRect.left && mousePT.y < SpriteRect.top)
	{
		dir = DIR_LEFT_UP;
	}
	else if(mousePT.x < SpriteRect.left && mousePT.y > SpriteRect.bottom)
	{
		dir = DIR_LEFT_DOWN;
	}
	else if(mousePT.x > SpriteRect.right && mousePT.y < SpriteRect.top)
	{
		dir = DIR_RIGHT_UP;
	}
	else if(mousePT.x > SpriteRect.right && mousePT.y > SpriteRect.bottom)
	{
		dir = DIR_RIGHT_DOWN;
	}
	else
	{
		dir = -1;			
	}
	return dir;
}
