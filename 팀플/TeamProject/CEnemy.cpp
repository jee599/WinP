#include "CEnemy.h"

CEnemy::CEnemy()
{
	mPosition = { WIDTH, (rand () % 300) *2 + 100 };
	mType = rand() % 5;
	mLife = 15 - mType*2;
	mObjectSize = 30 + 10*mType;
	mState = SPAWN;
	mMoving = 0;
	mDir = rand() % 4;
	switch (mType)
	{
	case 1:
		mMesh[0].Load(TEXT("enemy4.png"));
		break;
	case 2:
		mMesh[0].Load(TEXT("enemy1.png"));
		break;
	case 3:
		mMesh[0].Load(TEXT("enemy3.png"));
		break;
	case 4:
		mMesh[0].Load(TEXT("enemy2.png"));
		break;
	case 0:
		mMesh[0].Load(TEXT("enemy5.png"));
		break;
	}
	mEffect = new CEffect;
}

CEnemy::~CEnemy()
{
	mMesh->Destroy();
	if (mEffect)
		delete mEffect;
}
void CEnemy::Collision()
{
	if (mState == PLAY)
	{
		if (mLife > 0)
			mLife--;
		else
			mState = DEAD;
	}
}
int CEnemy::Animate()
{
	if (mState == PLAY)
	{
		if(mMoving++ % (mType+1) == 0)
			switch (mDir)
			{
			case 0:
				mPosition.x++;
				mPosition.y++;
				if (mMoving % (10*(mType+1)) == 0)
					mDir = rand() % 4;
				if (mPosition.x > 900 || mPosition.y > 750)
					mDir = 3;
				break;
			case 1:
				mPosition.x++;
				mPosition.y--;
				if (mMoving % (10 * (mType + 1)) == 0)
					mDir = rand() % 4;
				if (mPosition.x > 900 || mPosition.y < 100)
					mDir = 2;
				break;
			case 2:
				mPosition.x--;
				mPosition.y++;
				if (mMoving % (10 * (mType + 1)) == 0)
					mDir = rand() % 4;
				if (mPosition.x < 400 || mPosition.y > 750)
					mDir = 0;
				break;
			case 3:
				mPosition.x--;
				mPosition.y--;
				if (mMoving % (10 * (mType + 1)) == 0)
					mDir = rand() % 4;
				if (mPosition.x < 400 || mPosition.y < 100)
					mDir = 1;
				break;
			}
	}
	return IsEnd;
}
void CEnemy::Render(HDC Buffer)
{
	switch (mState)
	{
	case SPAWN:
		if (mMoving++ < (100 + mType*30))
			mMesh[0].Draw(Buffer, mPosition.x - mMoving, mPosition.y, mObjectSize, mObjectSize);
		else
		{
			mPosition.x -= mMoving;
			mState = PLAY;
			mMoving = 0;
		}
		break;
	case PLAY:
		mMesh[0].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize, mObjectSize);
		break;
	case DEAD:
		if (mEffect->Render(Buffer, mPosition))
			mState = DEL;
		break;
	case DEL:
		if (mType)
			IsEnd = 1;
		else
			IsEnd = 2;
		break;
	}
}
