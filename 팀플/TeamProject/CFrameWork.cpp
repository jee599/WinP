#include "CFrameWork.h"

CFrameWork::CFrameWork()
{
	InitialObject();
}


CFrameWork::~CFrameWork()
{
	DestroyObject();
}

void CFrameWork::InitialObject()
{
	if (!mEnemy)
		mEnemy = new CEnemy;
	if(!mScene)
		mScene = new CScene;
	if (!mPlayer)
		mPlayer = new CPlayer(1);
	if (!mDuo)
		mDuo = new CPlayer(2);
	GameState = TITLE;
}

void CFrameWork::MouseDown(LPARAM lParam)
{
	POINT Point;
	Point.x = LOWORD((int)lParam);
	Point.y = HIWORD((int)lParam);

	if (GameState == TITLE)
		GameState = mScene->MouseDown(Point);
}

void CFrameWork::Render(HDC MainBuffer)
{
	BackBuffer = CreateCompatibleDC(MainBuffer);
	hBitmap = CreateCompatibleBitmap(MainBuffer, WIDTH, HEIGHT);
	SelectObject(BackBuffer, (HBITMAP)hBitmap);
	PatBlt(BackBuffer, 0, 0, WIDTH, HEIGHT, WHITENESS);

	mScene->Render(BackBuffer,GameState);
	
	if (GameState == GAMEPLAY)
	{
		mDuo->Render(BackBuffer);
		mEnemy->Render(BackBuffer);
		mPlayer->Render(BackBuffer);
	}
	
	BitBlt(MainBuffer, 0, 0, WIDTH, HEIGHT, BackBuffer, 0, 0, SRCCOPY);
}

void CFrameWork::KeyDown(WPARAM wParam)
{
	if (GameState == GAMEPLAY)
	{
		dynamic_cast<CPlayer*>(mPlayer)->Move(wParam);
		dynamic_cast<CPlayer*>(mDuo)->Move(wParam);
	}
}

void CFrameWork::Animate()
{
	if (GameState == GAMEPLAY)
	{
		dynamic_cast<CPlayer*>(mPlayer)->Animate();
		dynamic_cast<CPlayer*>(mDuo)->Animate();
	}
}

void CFrameWork::CollCheck()
{
	auto iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.begin();
	for (; iter != dynamic_cast<CPlayer*>(mPlayer)->mBullet.end();)
	{
		if ((*iter)->CollCheck(mEnemy->GetRect()))
		{
			delete(*iter);
			iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.erase(iter);
		}
		else
			++iter;
	}
}

void CFrameWork::KeyUp(WPARAM wParam)
{
	if (GameState == GAMEPLAY)
	{
		if (wParam == VK_RETURN)
			dynamic_cast<CPlayer*>(mPlayer)->StopBullet();
		if (wParam == VK_SPACE)
			dynamic_cast<CPlayer*>(mDuo)->StopBullet();
	}
}

void CFrameWork::DestroyObject()
{
	if (mDuo)
		delete mDuo;
	if (mPlayer)
		delete mPlayer;
	if (mScene)
		delete mScene;
}
