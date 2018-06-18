#include "CPlayer.h"

CPlayer::CPlayer(TYPE Type, int Duo)
{
	mType = Type;
	mPlayerType = Duo;			// 0듀오1나 2적
	mDirect = STOP;
	mMeshCount = 0;
	mObjectSize = 25;
	mLevel = 1;
	mDamage = 1;
	mScore = 0;
	mBulletRate = 8;
	mBulletSpeed = 10;
	mSpeed = 3;
	IsRevolution = false;
	mPosition = { 30,200 + 300*Duo};
	if (Duo == 2)
		mPosition = { 850, 500 };
	mMesh[9].Load(TEXT("Hp.png"));
	//if(Duo < 2)
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
		mMesh[0].Load(TEXT("이상해씨1.png"));
		mMesh[1].Load(TEXT("이상해씨2.png"));
		mMesh[2].Load(TEXT("이상해씨3.png"));
		break;
	case ELEC:
		mMesh[0].Load(TEXT("피카츄1.png"));
		mMesh[1].Load(TEXT("피카츄2.png"));
		mMesh[2].Load(TEXT("피카츄3.png"));
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
	if(mPlayerType == 1)
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
	bool Dir;
	if (mPlayerType < 2)
		Dir = true;
	else
		Dir = false;

	if(IsBullet)
		switch (mLevel)
		{
		case 1:
			mBullet.push_back(new CBullet({ mPosition.x, mPosition.y- 5 }, mType, mDamage,mSpeed,Dir));
			break;
		case 2:
			mBullet.push_back(new CBullet({ mPosition.x , mPosition.y }, mType, mDamage, mSpeed, Dir));
			mBullet.push_back(new CBullet({ mPosition.x , mPosition.y - 20}, mType, mDamage, mSpeed, Dir));
			break;
		case 3:
			mBullet.push_back(new CBullet({ mPosition.x , mPosition.y - 40 }, mType, mDamage, mSpeed, Dir));
			mBullet.push_back(new CBullet({ mPosition.x, mPosition.y - 10 }, mType, mDamage, mSpeed, Dir));
			mBullet.push_back(new CBullet({ mPosition.x, mPosition.y + 20}, mType, mDamage, mSpeed, Dir));
			break;
		}
}
void CPlayer::Animate()
{
	if (mScore >= (3*mLevel))
	{
		if (mLevel < 3)
		{
			mLevel++;
			mObjectSize += 5;
			IsRevolution = true;
		}
		else
			mDamage++;
		mScore = 0;
	}
	if (mBulletCount++ == mBulletRate)
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
	if(!IsRevolution)
		switch (mDirect)
		{
		case DOWN:
			mPosition.y += mSpeed;
			break;
		case UP:
			mPosition.y -= mSpeed;
			break;
		case LEFT:
			mPosition.x -= mSpeed;
			break;
		case RIGHT:
			mPosition.x += mSpeed;
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
	if (IsRevolution)
	{
		if (mAnimationCut)
		{
			if ((mMeshCount % 10) < 5)
				mMesh[mLevel - 2].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mMeshCount, mMeshCount);
			else
				mMesh[mLevel - 2].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mMeshCount / 2, mMeshCount / 2);
			if (mMeshCount-- < 10)
				mAnimationCut = false;
		}
		else
		{
			if ((mMeshCount % 10) < 5)
				mMesh[mLevel - 2].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mMeshCount, mMeshCount);
			else
				mMesh[mLevel - 2].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mMeshCount / 2, mMeshCount / 2);
			mMeshCount++;
			if (mMeshCount == mObjectSize*2)
				IsRevolution = false;
		}
	}
	else
	{
		mMesh[mLevel - 1].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mObjectSize * 2, mObjectSize * 2);
		mMeshCount = mObjectSize*2;
		mAnimationCut = true;
	}
	mMesh[9].Draw(Buffer, mPosition.x - mObjectSize/2, mPosition.y - mObjectSize - 30, 50, 10);
}
