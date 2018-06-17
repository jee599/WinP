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
	srand(time(NULL));
	mEnemy[mEnemyCount++] = new CEnemy;
	if(!mScene)
		mScene = new CScene;
	if (!mPlayer)
		mPlayer = new CPlayer(FIRE,1);
	if (!mDuo)
		mDuo = new CPlayer(WATER,0);
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
		for (int i = 0; i < mItemCount; ++i)
			mItem[i]->Render(BackBuffer);
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

void CFrameWork::MakeFood(POINT Position)
{
	mItem[mItemCount++] = new CItem(Position);
}

void CFrameWork::Animate()
{
	if (GameState == GAMEPLAY)
	{
		if (++Timer % 100 == 0)
		{
			mBossCount++;
			mEnemy[mEnemyCount++] = new CEnemy;
		}
		dynamic_cast<CPlayer*>(mPlayer)->Animate();
		dynamic_cast<CPlayer*>(mDuo)->Animate();
		for (int i = 0; i < mItemCount; ++i)
			dynamic_cast<CItem*>(mItem[i])->Animate();
		for (int i = 0; i < mEnemyCount; ++i)
		{
			int Result = dynamic_cast<CEnemy*>(mEnemy[i])->Animate();
			if (Result == 2)
				MakeFood(dynamic_cast<CEnemy*>(mEnemy[i])->GetPosition());
			if (Result)
			{
				dynamic_cast<CPlayer*>(mPlayer)->ScoreUp();
				delete mEnemy[i];
				for (int j = i; j < mEnemyCount; ++j)
					mEnemy[j] = mEnemy[j + 1];
				mEnemyCount--;
			}
		}
		CollCheck();
	}
}

void CFrameWork::CollCheck()
{
	RECT Temp;
	for (int i = 0; i < mItemCount; ++i)
	{
		if (IntersectRect(&Temp, &(mItem[i]->GetRect()), &(mPlayer->GetRect())))
		{
			dynamic_cast<CPlayer*>(mPlayer)->DamageUp();
			for (int j = 0; j < mItemCount; ++j)
			{
				delete mItem[i];
				mItem[j] = mItem[j + 1];
				mItemCount--;
			}
		}
		if (IntersectRect(&Temp, &(mItem[i]->GetRect()), &(mDuo->GetRect())))
		{
			dynamic_cast<CPlayer*>(mDuo)->DamageUp();
			for (int j = 0; j < mItemCount; ++j)
			{
				delete mItem[i];
				mItem[j] = mItem[j + 1];
				mItemCount--;
			}
		}
	}
	for (int i = 0; i < mEnemyCount; ++i)
	{
		auto iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.begin();
		for (; iter != dynamic_cast<CPlayer*>(mPlayer)->mBullet.end();)
		{
			if ((*iter)->CollCheck(mEnemy[i]->GetRect()))
			{
				if (dynamic_cast<CEnemy*>(mEnemy[i])->Collision((*iter)->GetDamage()))
					break;
				delete(*iter);
				iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.erase(iter);
			}
			else
				++iter;
		}
		auto iter1 = dynamic_cast<CPlayer*>(mDuo)->mBullet.begin();
		for (; iter1 != dynamic_cast<CPlayer*>(mDuo)->mBullet.end();)
		{

			if ((*iter1)->CollCheck(mEnemy[i]->GetRect()))
			{
				if (dynamic_cast<CEnemy*>(mEnemy[i])->Collision((*iter1)->GetDamage()))
					break; 
				delete(*iter1);
				iter1 = dynamic_cast<CPlayer*>(mDuo)->mBullet.erase(iter1);
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
	for (int i = 0; i < mItemCount; ++i)
		delete mItem[i];
	for(int i = 0; i < mEnemyCount;++i)
		delete mEnemy[i];
	if (mDuo)
		delete mDuo;
	if (mPlayer)
		delete mPlayer;
	if (mScene)
		delete mScene;
}
