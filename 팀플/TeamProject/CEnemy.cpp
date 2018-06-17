#include "CEnemy.h"

CEnemy::CEnemy()
{
	mPosition = { WIDTH, (rand () % 300) *2 + 100 };
	mType = rand() % 25;
	mLife = 100 - ((mType /10)+6)*10;
	mObjectSize = 50;
	mState = SPAWN;
	mMoving = 0;
	mDir = rand() % 4;
	mMesh[9].Load(TEXT("Hp.png"));
	switch (mType)
	{
	case 1:
		mMesh[0].Load(TEXT("1.png"));
		break;
	case 2:
		mMesh[0].Load(TEXT("2.png"));
		break;
	case 3:
		mMesh[0].Load(TEXT("3.png"));
		break;
	case 4:
		mMesh[0].Load(TEXT("4.png"));
		break;
	case 5:
		mMesh[0].Load(TEXT("5.png"));
		break;
	case 6:
		mMesh[0].Load(TEXT("6.png"));
		break;
	case 7:
		mMesh[0].Load(TEXT("7.png"));
		break;
	case 8:
		mMesh[0].Load(TEXT("8.png"));
		break;
	case 9:
		mMesh[0].Load(TEXT("9.png"));
		break;
	case 10:
		mMesh[0].Load(TEXT("10.png"));
		break;
	case 11:
		mMesh[0].Load(TEXT("11.png"));
		break;
	case 12:
		mMesh[0].Load(TEXT("12.png"));
		break;
	case 13:
		mMesh[0].Load(TEXT("13.png"));
		break;
	case 14:
		mMesh[0].Load(TEXT("14.png"));
		break;
	case 15:
		mMesh[0].Load(TEXT("15.png"));
		break;
	case 16:
		mMesh[0].Load(TEXT("16.png"));
		break;
	case 17:
		mMesh[0].Load(TEXT("17.png"));
		break;
	case 18:
		mMesh[0].Load(TEXT("18.png"));
		break;
	case 19:
		mMesh[0].Load(TEXT("19.png"));
		break;
	case 20:
		mMesh[0].Load(TEXT("20.png"));
		break;
	case 21:
		mMesh[0].Load(TEXT("21.png"));
		break;
	case 22:
		mMesh[0].Load(TEXT("22.png"));
		break;
	case 23:
		mMesh[0].Load(TEXT("23.png"));
		break;
	case 24:
		mMesh[0].Load(TEXT("24.png"));
		break;
	case 0:
		mMesh[0].Load(TEXT("0.png"));
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
bool CEnemy::Collision(int Damage)
{
	if (mState == PLAY)
	{
		if (mLife > Damage)
		{
			mLife -= Damage;
			return false;
		}
		else
		{
			mState = DEAD;
			return true;
		}
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
	char Temp[20];
	sprintf_s(Temp,"%d", mLife);
	switch (mState)
	{
	case SPAWN:
		if (mMoving++ < (100 + mType*10))
			mMesh[0].Draw(Buffer, mPosition.x - mMoving - mObjectSize - 10, mPosition.y - mObjectSize, (mObjectSize + ((float)mObjectSize/120 *mMoving))/2 , (mObjectSize + ((float)mObjectSize / 120 * mMoving))/2);
		else
		{
			mPosition.x -= mMoving;
			mState = PLAY;
			mMoving = 0;
		}
		break;
	case PLAY:
		mMesh[0].Draw(Buffer, mPosition.x-mObjectSize, mPosition.y - mObjectSize, mObjectSize*2, mObjectSize*2);
		TextOut(Buffer, mPosition.x, mPosition.y - 70, Temp, strlen(Temp));
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
