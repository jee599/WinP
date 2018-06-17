#include "CPlayer.h"

CPlayer::CPlayer(TYPE Type, int Duo)
{
	mType = Type;
	mDuoMode = Duo;
	mDirect = STOP;
	mMeshCount = 0;
	mBulletNumber = 2;
	mObjectSize = 50;
	mPosition = { 30,200 + 300*Duo};
	switch (Type)
	{
	case FIRE:
		mMesh[0].Load(TEXT("파이리1.png"));
		mMesh[1].Load(TEXT("파이리2.png"));
		mMesh[2].Load(TEXT("파이리3.png"));
		break;
	case WATER:
		mMesh[0].Load(TEXT("꼬부기1.png"));
		mMesh[1].Load(TEXT("꼬부기2.png"));
		mMesh[2].Load(TEXT("꼬부기3.png"));
		break;
	case GRASS:
		mMesh[0].Load(TEXT("grass.png"));
		break;
	case ELEC:
		mMesh[0].Load(TEXT("elec.png"));
		break;
	}
}

CPlayer::~CPlayer()
{
	mMesh->Destroy();
	for (auto p : mBullet)
		delete p;
}

void CPlayer::Move(WPARAM wParam)
{
	if(mDuoMode)
	// Set Player Direction by wParam
	switch (wParam)
	{
	case VK_UP:
		mDirect = UP;
		break;
	case VK_DOWN:
		mDirect = DOWN;
		break;
	case VK_LEFT:
		mDirect = LEFT;
		break;
	case VK_RIGHT:
		mDirect = RIGHT;
		break;
	case VK_RETURN:
		IsBullet = true;
	}
	else
	{
		switch (wParam)
		{
		case 'w':
			mDirect = UP;
			break;
		case 's':
			mDirect = DOWN;
			break;
		case 'a':
			mDirect = LEFT;
			break;
		case 'd':
			mDirect = RIGHT;
			break;
		case VK_SPACE:
			IsBullet = true;
		}
	}
}
void CPlayer::StopBullet()
{
	IsBullet = false;
}

void CPlayer::MakeBullet()
{
	// Make Bullet with Player Position
	if(IsBullet)
		switch (mBulletNumber)
		{
		case 1:
			mBullet.push_back(new CBullet({ mPosition.x + 40, mPosition.y + 10 }, mType));
			break;
		case 2:
			mBullet.push_back(new CBullet({ mPosition.x + 40, mPosition.y + 20 }, mType));
			mBullet.push_back(new CBullet({ mPosition.x + 40, mPosition.y}, mType));
			break;
		case 3:
			mBullet.push_back(new CBullet({ mPosition.x + 40, mPosition.y + 25 }, mType));
			mBullet.push_back(new CBullet({ mPosition.x + 40, mPosition.y - 5 }, mType));
			mBullet.push_back(new CBullet({ mPosition.x + 40, mPosition.y + 10}, mType));
			break;
		}
}
void CPlayer::Animate()
{
	if (mBulletCount++ == BULLETRATE)
	{
		MakeBullet();
		mBulletCount = 0;
	}
	// 포문 안은 어려우니 이해하려 들지 마라(vector + iterator + delete + auto)
	// mBullet = vector<CBullet*>형식   ->  iter = CBullet* ?
	for (auto iter = mBullet.begin(); iter != mBullet.end();)
		if ((*iter)->Animate())
		{
			delete(*iter);
			iter = mBullet.erase(iter);
		}
		else
			++ iter;
			
	// Moving Player by Direct
	switch (mDirect)
	{
	case DOWN:
		mPosition.y += PLAYERSPEED;
		break;
	case UP:
		mPosition.y -= PLAYERSPEED;
		break;
	case LEFT:
		mPosition.x -= PLAYERSPEED;
		break;
	case RIGHT:
		mPosition.x += PLAYERSPEED;
		break;
	}
	if (mPosition.x >= WIDTH || mPosition.x <= 0 || mPosition.y >= HEIGHT || mPosition.y <= 0)
		mDirect += 2;
	if (mDirect > 4)
		mDirect -= 4;
}
void CPlayer::Render(HDC Buffer)
{
	for (auto p : mBullet)
		p->Render(Buffer);
	if (mMeshCount == 30)
		mMeshCount = 0;
	mMesh[0].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize, mObjectSize);
}
