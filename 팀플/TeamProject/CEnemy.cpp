#include "CEnemy.h"

CEnemy::CEnemy()
{
	mPosition = { WIDTH, (rand () % 300) *2 + 100 };
	mType = rand() % 5;
	mLife = 5 + mType;
	mObjectSize = 50;
	mState = SPAWN;
	mMoving = 0;
	switch (mType)
	{
	case 1:
		mMesh[0].Load(TEXT("enemy1.png"));
		break;
	case 2:
		mMesh[0].Load(TEXT("enemy3.png"));
		break;
	case 3:
		mMesh[0].Load(TEXT("enemy4.png"));
		break;
	case 4:
		mMesh[0].Load(TEXT("enemy5.png"));
		break;
	case 0:
		mMesh[0].Load(TEXT("enemy2.png"));
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
bool CEnemy::Animate()
{
	return IsDead;
}
void CEnemy::Render(HDC Buffer)
{
	switch (mState)
	{
	case SPAWN:
		if (mMoving++ < 200)
			mMesh[0].Draw(Buffer, mPosition.x - mMoving, mPosition.y, mObjectSize, mObjectSize);
		else
		{
			mPosition.x -= mMoving;
			mState = PLAY;
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
		IsDead = true;
		break;
	}
}
