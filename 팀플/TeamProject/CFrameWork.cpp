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
	mEnemy[mEnemyCount++] = new CEnemy;
	if(!mScene)
		mScene = new CScene;
	if (!mPlayer)
		mPlayer = new CPlayer(WATER,1);
	if (!mDuo)
		mDuo = new CPlayer(GRASS,0);
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
		for (int i = 0; i < mEnemyCount;++i)
			mEnemy[i]->Render(BackBuffer);
		mDuo->Render(BackBuffer);
		mPlayer->Render(BackBuffer);
	}
	
	BitBlt(MainBuffer, 0, 0, WIDTH, HEIGHT, BackBuffer, 0, 0, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteDC(BackBuffer);
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
		if (++Timer % 100 == 0)
		{
			mEnemy[mEnemyCount++] = new CEnemy;
		}
		dynamic_cast<CPlayer*>(mPlayer)->Animate();
		dynamic_cast<CPlayer*>(mDuo)->Animate();

		for (int i = 0; i < mEnemyCount;++i)
			if (dynamic_cast<CEnemy*>(mEnemy[i])->Animate())
			{
				delete mEnemy[i];
				for (int j = i; j < mEnemyCount; ++j)
					mEnemy[j] = mEnemy[j + 1];
				mEnemyCount--;
			}

		CollCheck();
	}
}

void CFrameWork::CollCheck()
{
	for (int i = 0; i < mEnemyCount; ++i)
	{
		auto iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.begin();
		for (; iter != dynamic_cast<CPlayer*>(mPlayer)->mBullet.end();)
		{
			if ((*iter)->CollCheck(mEnemy[i]->GetRect()))
			{
				delete(*iter);
				iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.erase(iter);
				mEnemy[i]->Collision();
			}
			else
				++iter;
		}

		auto iter1 = dynamic_cast<CPlayer*>(mDuo)->mBullet.begin();
		for (; iter1 != dynamic_cast<CPlayer*>(mDuo)->mBullet.end();)
		{

			if ((*iter1)->CollCheck(mEnemy[i]->GetRect()))
			{
				delete(*iter1);
				iter1 = dynamic_cast<CPlayer*>(mDuo)->mBullet.erase(iter1);
				mEnemy[i]->Collision();
			}
			else
				++iter1;
		}
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
	for(int i = 0; i < mEnemyCount;++i)
		delete mEnemy[i];
	if (mDuo)
		delete mDuo;
	if (mPlayer)
		delete mPlayer;
	if (mScene)
		delete mScene;
}
