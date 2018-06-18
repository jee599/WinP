#include "CEnemy.h"

CEnemy::CEnemy(GAMESTATE p)
{
	mPosition = { WIDTH, 400 };
	mLife = 1000;
	mType = 25;		//BOSS
	mObjectSize = 75;
	mState = SPAWN;
	mMoving = 0;
	mDir = 3;
	mMesh[11].Load(TEXT("Life.png"));
	mMesh[0].Load(TEXT("비주기1.png"));
	mMesh[1].Load(TEXT("비주기2.png"));
	mMesh[2].Load(TEXT("비주기3.png"));
	mMesh[3].Load(TEXT("비주기4.png"));
	mMesh[4].Load(TEXT("비주기5.png"));
	mMesh[5].Load(TEXT("비주기6.png"));
	mMesh[6].Load(TEXT("비주기7.png"));
	mMesh[7].Load(TEXT("비주기8.png"));
	mMesh[8].Load(TEXT("비주기9.png"));
	mMesh[9].Load(TEXT("비주기10.png"));
	mMesh[10].Load(TEXT("비주기11.png"));
}

CEnemy::CEnemy()
{
	mPosition = { WIDTH, (rand () % 300) *2 + 100 };
	mType = rand() % 25;
	mLife = 200 - (mType * 5);
	mObjectSize = 50;
	mState = SPAWN;
	mMoving = 0;
	mDir = rand() % 4;
	mMesh[11].Load(TEXT("Life.png"));
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
			if (mType == 25 && Damage > 1)
				Damage--;
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
	if(mType == 25 && mState == PLAY)
		switch (mDir)
		{
		case 0:
			mPosition.x++;
			mPosition.y++;
			if (mMoving % 50 == 0)
				mDir = rand() % 4;
			if (mPosition.x > 900 || mPosition.y > 750)
				mDir = 3;
			break;
		case 1:
			mPosition.x++;
			mPosition.y--;
			if (mMoving % 50 == 0)
				mDir = rand() % 4;
			if (mPosition.x > 900 || mPosition.y < 100)
				mDir = 2;
			break;
		case 2:
			mPosition.x--;
			mPosition.y++;
			if (mMoving % 50 == 0)
				mDir = rand() % 4;
			if (mPosition.x < 400 || mPosition.y > 750)
				mDir = 0;
			break;
		case 3:
			mPosition.x--;
			mPosition.y--;
			if (mMoving % 50 == 0)
				mDir = rand() % 4;
			if (mPosition.x < 400 || mPosition.y < 100)
				mDir = 1;
			break;
		}
	else if (mState == PLAY)
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
	case WAIT:
		mBossState = 2;
		mMesh[mMoving++ / 20].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mObjectSize * 2, mObjectSize * 2);
		if ((mMoving / 20) == 11)
			mState = PLAY;
		break;
	case SPAWN:
		mBossState = 1;
		if (mMoving++ < (100 + mType * 10))
			mMesh[0].Draw(Buffer, mPosition.x - mMoving - mObjectSize - 10, mPosition.y - mObjectSize, (mObjectSize + ((float)mObjectSize / 120 * mMoving)) / 2, (mObjectSize + ((float)mObjectSize / 120 * mMoving)) / 2);
		else
		{
			mPosition.x -= mMoving;
			if (mType == 25)
				mState = WAIT;
			else
				mState = PLAY;
			mMoving = 0;
		}
		break;
	case PLAY:
		if (mType == 25)
		{
			mBossState = 3;
			mMesh[10].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mObjectSize * 2, mObjectSize * 2);
		}
		else
			mMesh[0].Draw(Buffer, mPosition.x-mObjectSize, mPosition.y - mObjectSize, mObjectSize*2, mObjectSize*2);
		mMesh[11].Draw(Buffer, mPosition.x - mObjectSize/2, mPosition.y - mObjectSize - 10, (mLife+2)/2, 7);
		break;
	case DEAD:
		if (mType == 25)
			mState = DEL;
		else if (mEffect->Render(Buffer, mPosition))
			mState = DEL;
		break;
	case DEL:
		if (mType == 25)
			IsEnd = 4;			//Boss End
		else if (rand()% 10 > 3)
			IsEnd = 1;			// Normal End
		else
			IsEnd = 2;			//ITem End
		break;
	}
}
