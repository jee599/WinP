#include "CFrameWork.h"

CFrameWork::CFrameWork()
{
	InitialObject();
	if (!mScene)
		mScene = new CScene;

}


CFrameWork::~CFrameWork()
{
	DestroyObject();
	if (mScene)
		delete mScene;

}

void CFrameWork::InitialObject()
{
	mBossState = 0;
	Timer = 0;
	mBossCount = 0;
	mEnemyCount = 0;
	mItemCount = 0;

	IsBoss = false;
	IsInit = true;
	srand((unsigned int)time(NULL));
	mEnemyCount = 0;
	mEnemy[mEnemyCount++] = new CEnemy;
	mPlayer = new CPlayer(FIRE, 1);
	mDuo = new CPlayer(WATER, 0);
	GameState = TITLE;
	mBoss = new CEnemy(BOSS);
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
	if (GameState == BOSS)
	{
		if (!IsBoss)
		{
			auto iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.begin();
			for (; iter != dynamic_cast<CPlayer*>(mPlayer)->mBullet.end();)
			{
				delete(*iter);
				iter = dynamic_cast<CPlayer*>(mPlayer)->mBullet.erase(iter);
			}

			if (mItemCount)
				for (int i = 0; i < mItemCount; ++i)
					delete mItem[i];
			if (mEnemyCount)
				for (int i = 0; i < mEnemyCount; ++i)
					delete mEnemy[i];
			mItemCount = 0;
			mEnemyCount = 0;

			mEnemy[0] = new CEnemy(BOSS);

			for (int i = 1; i < 30; ++i)
				mEnemy[i] = new CEnemy;
			mEnemyCount = 30;
			IsBoss = true;
		}
		if (mBossState == 3)
		{
			mDuo->Render(BackBuffer);
			mPlayer->Render(BackBuffer);
			for (int i = 1; i < mEnemyCount; ++i)
				mEnemy[i]->Render(BackBuffer);
		}
		mEnemy[0]->Render(BackBuffer);
	}
	BitBlt(MainBuffer, 0, 0, WIDTH, HEIGHT, BackBuffer, 0, 0, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteDC(BackBuffer);
}

void CFrameWork::KeyDown(WPARAM wParam)
{
	if (GameState == GAMEPLAY || GameState == BOSS)
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
	if (GameState == TITLE && IsInit)
	{
		DestroyObject();
		InitialObject();
		IsInit = false;
	}
	if (IsBoss)
		mBossState = dynamic_cast<CEnemy*>(mEnemy[0])->mBossState;
	if (GameState == BOSS && mBossState == 3)
	{
		dynamic_cast<CPlayer*>(mPlayer)->Animate();
		dynamic_cast<CPlayer*>(mDuo)->Animate();
		int Result = dynamic_cast<CEnemy*>(mEnemy[0])->Animate();
		if (Result == 4)
		{
			IsInit = true;
			GameState = TITLE;
		}

		for (int i = 1; i < mEnemyCount; ++i)
		{
			Result = dynamic_cast<CEnemy*>(mEnemy[i])->Animate();
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
	if (GameState == GAMEPLAY)
	{
		dynamic_cast<CPlayer*>(mPlayer)->Animate();
		dynamic_cast<CPlayer*>(mDuo)->Animate();
		for (int i = 0; i < mItemCount; ++i)
			dynamic_cast<CItem*>(mItem[i])->Animate();
		if (mBossCount > 15)
		{
			GameState = BOSS;
		}
		if (++Timer % 100 == 0)
			mEnemy[mEnemyCount++] = new CEnemy;
		for (int i = 0; i < mEnemyCount; ++i)
		{
			int Result = dynamic_cast<CEnemy*>(mEnemy[i])->Animate();
			if (Result == 2)
				MakeFood(dynamic_cast<CEnemy*>(mEnemy[i])->GetPosition());
			if (Result)
			{
				dynamic_cast<CPlayer*>(mPlayer)->ScoreUp();
				delete mEnemy[i];
				mBossCount++;
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
			delete mItem[i];
			for (int j = i; j < mItemCount; ++j)
			{
				mItem[j] = mItem[j + 1];
				mItemCount--;
			}
		}
		else if (IntersectRect(&Temp, &(mItem[i]->GetRect()), &(mDuo->GetRect())))
		{
			dynamic_cast<CPlayer*>(mDuo)->DamageUp();
			delete mItem[i];
			for (int j = i; j < mItemCount; ++j)
			{
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
	if (GameState == GAMEPLAY || GameState == BOSS)
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
	delete mDuo;
	delete mPlayer;
}
