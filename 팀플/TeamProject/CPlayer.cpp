#include "CPlayer.h"

CPlayer::CPlayer()
{
	mDirect = STOP;
	mMeshCount = 0;
	mPosition = { 30, HEIGHT / 2 };
	mMesh[0].Load((TEXT("종이1.png")));
	mMesh[1].Load((TEXT("종이2.png")));
	mMesh[2].Load((TEXT("종이3.png")));
}

CPlayer::CPlayer(int Type)
{
	switch (Type)
	{
	case PAPER:
		mMesh[0].Load((TEXT("종이1.png")));
		mMesh[1].Load((TEXT("종이2.png")));
		mMesh[2].Load((TEXT("종이3.png")));
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
	case VK_SPACE:
		IsBullet = true;
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
		mBullet.push_back(new CBullet(mPosition));
}

void CPlayer::Animate()
{
	if (mBulletCount++ % BULLETRATE == 0)
		MakeBullet();
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
	mMesh[mMeshCount++ / 10].Draw(Buffer, mPosition.x, mPosition.y, PLAYERSIZE, PLAYERSIZE);
}
