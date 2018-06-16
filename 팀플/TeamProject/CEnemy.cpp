#include "CEnemy.h"

CEnemy::CEnemy()
{
	mMesh[0].Load(TEXT("pika.png"));
	mPosition = { WIDTH, (rand () % 300) *2 + 100 };
	mLife = 5;
	mObjectSize = 50;
	mState = SPAWN;
	mMoving = 0;
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
