
#include "CPlayer.h"

CPlayer::CPlayer(PICKTYPE Type, int Duo)
{
	mEffectTimer = 0;
	mType = Type;
	mPlayerType = Duo;			// 0듀오1나 2적
	mDirect = STOP;
	mMeshCount = 0;
	mObjectSize = 25;
	mLevel = 1;
	mLife = 100;
	mMana = 0;
	mSkillTimer = 0;
	mDamage = 1;
	mScore = 0;
	mBulletRate = 3;
	mBulletSpeed = 10;
	mSpeed = 3;

	IsBullet = false;
	IsSkill = false;
	IsSkillRender = false;
	IsRevolution = false;
	mPosition = { 30,200 + 300 * Duo };
	if (Duo == 2)
		mPosition = { 850, 500 };

	if (mType == WATER)
	{
		mSkillMesh[0].Load(TEXT("물필1.png"));
		mSkillMesh[1].Load(TEXT("물필2.png"));
		mSkillMesh[2].Load(TEXT("물필3.png"));
		mSkillMesh[3].Load(TEXT("물필4.png"));
		mSkillMesh[4].Load(TEXT("물필5.png"));
		mSkillMesh[5].Load(TEXT("물필6.png"));
		mSkillMesh[6].Load(TEXT("물필7.png"));
		mSkillMesh[7].Load(TEXT("물필8.png"));
		mSkillMesh[8].Load(TEXT("물필9.png"));
		mSkillMesh[9].Load(TEXT("물필1.png"));
	}
	if (mType == FIRE)
	{
		mSkillMesh[1].Load(TEXT("불필2.png"));
		mSkillMesh[2].Load(TEXT("불필3.png"));
		mSkillMesh[3].Load(TEXT("불필4.png"));
		mSkillMesh[4].Load(TEXT("불필5.png"));
		mSkillMesh[5].Load(TEXT("불필6.png"));
		mSkillMesh[6].Load(TEXT("불필7.png"));
		mSkillMesh[7].Load(TEXT("불필8.png"));
		mSkillMesh[8].Load(TEXT("불필9.png"));
		mSkillMesh[9].Load(TEXT("불필1.png"));
		mSkillMesh[0].Load(TEXT("불필1.png"));
	}
	if (mType == GRASS)
	{
		mSkillMesh[0].Load(TEXT("풀필1.png"));
		mSkillMesh[1].Load(TEXT("풀필2.png"));
		mSkillMesh[2].Load(TEXT("풀필3.png"));
		mSkillMesh[3].Load(TEXT("풀필4.png"));
		mSkillMesh[4].Load(TEXT("풀필5.png"));
		mSkillMesh[5].Load(TEXT("풀필6.png"));
		mSkillMesh[6].Load(TEXT("풀필7.png"));
		mSkillMesh[7].Load(TEXT("풀필8.png"));
		mSkillMesh[8].Load(TEXT("풀필9.png"));
		mSkillMesh[9].Load(TEXT("풀필1.png"));
	}
	if (mType == ELEC)
	{
		mSkillMesh[0].Load(TEXT("전필1.png"));
		mSkillMesh[1].Load(TEXT("전필2.png"));
		mSkillMesh[2].Load(TEXT("전필3.png"));
		mSkillMesh[3].Load(TEXT("전필4.png"));
		mSkillMesh[4].Load(TEXT("전필5.png"));
		mSkillMesh[5].Load(TEXT("전필6.png"));
		mSkillMesh[6].Load(TEXT("전필7.png"));
		mSkillMesh[7].Load(TEXT("전필8.png"));
		mSkillMesh[8].Load(TEXT("전필9.png"));
		mSkillMesh[9].Load(TEXT("전필1.png"));
	}
	mEffectMesh[ELEC].Load(TEXT("피스킬.png"));
	mEffectMesh[FIRE].Load(TEXT("파스킬.png"));
	mEffectMesh[WATER].Load(TEXT("꼬스킬.png"));
	mEffectMesh[GRASS].Load(TEXT("이스킬.png"));
	mEffectMesh[NONE].Load(TEXT("피스킬2.png"));

	mMesh[9].Load(TEXT("Life.png"));
	mMesh[8].Load(TEXT("Mana.png"));

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
	if (mPlayerType == 1)
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
			break;
		case 'p':
			if (mMana > 99)
				IsSkill = true;
			break;
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
		case 'z':
			if (mMana > 99)
				IsSkill = true;
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

	if (IsBullet)
		switch (mLevel)
		{
		case 1:
			mBullet.push_back(new CBullet({ mPosition.x, mPosition.y - 5 }, mType, mDamage, mBulletSpeed, Dir));
			break;
		case 2:
			mBullet.push_back(new CBullet({ mPosition.x , mPosition.y }, mType, mDamage, mBulletSpeed, Dir));
			mBullet.push_back(new CBullet({ mPosition.x , mPosition.y - 20 }, mType, mDamage, mBulletSpeed, Dir));
			break;
		case 3:
			mBullet.push_back(new CBullet({ mPosition.x , mPosition.y - 40 }, mType, mDamage, mBulletSpeed, Dir));
			mBullet.push_back(new CBullet({ mPosition.x, mPosition.y - 10 }, mType, mDamage, mBulletSpeed, Dir));
			mBullet.push_back(new CBullet({ mPosition.x, mPosition.y + 20 }, mType, mDamage, mBulletSpeed, Dir));
			break;
		}
}
void CPlayer::ScoreUp(int Type)
{
	switch (Type)
	{
	case 0:
		mScore++;
		break;
	case 1:
		mDamage++;
		break;
	case 2:
		mLife += 10;
		break;
	case 3:
		mSpeed++;
		break;
	case 4:
		mBulletSpeed++;
		break;
	}
}
void CPlayer::Animate()
{
	if (mMana < 999)
		mMana++;
	if (mScore > 0 && mLevel < 3)
	{
		mLevel++;
		if (mType == ELEC)
			mLevel = 2;
		mObjectSize += 5;
		IsRevolution = true;
		mScore = 0;
	}
	if (mBulletCount++ == mBulletRate)
	{
		MakeBullet();
		mBulletCount = 0;
	}
	// 포문 안은 어려우니 이해하려 들지 마라(vector + iterator + delete + auto)
	// mBullet = vector<CBullet*>형식   ->  iter = CBullet* ?
	if (mBullet.size())
		for (auto iter = mBullet.begin(); iter != mBullet.end();)
			if ((*iter)->Animate())
			{
				delete(*iter);
				iter = mBullet.erase(iter);
			}
			else
				++iter;
	// Moving Player by Direct
	if (!IsRevolution)
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
	if (IsSkillRender)
	{
		IsSkillRender = true;
		mSkillMesh[ mEffectTimer / 10].Draw(Buffer, 550 + (mEffectTimer) * 3, 100, 100, 200);
		mSkillMesh[ mEffectTimer / 10].Draw(Buffer, 650 + (mEffectTimer) * 3, 200, 100, 200);
		mSkillMesh[ mEffectTimer / 10].Draw(Buffer, 550 + (mEffectTimer) * 3, 300, 100, 200);
		mSkillMesh[ mEffectTimer / 10].Draw(Buffer, 650 + (mEffectTimer) * 3, 400, 100, 200);
		mSkillMesh[ mEffectTimer / 10].Draw(Buffer, 550 + (mEffectTimer) * 3, 500, 100, 200);
		mSkillMesh[ mEffectTimer++ / 10].Draw(Buffer, 650 + (mEffectTimer) * 3, 600, 100, 200);
		if (mEffectTimer == 90)
		{
			IsSkillRender = false;
			mEffectTimer = 0;
			mMana = 0;
		}
	}
	if (IsSkill && mSkillTimer < 550)
	{
		if (mSkillTimer < 400)
			mSkillTimer += 13;
		else
			mSkillTimer += 3;
		mEffectMesh[mType].Draw(Buffer, WIDTH - (mSkillTimer * 2), 250, 1200, 200);
		mEffectMesh[NONE].Draw(Buffer, -mSkillTimer * 2, 250, 1000, 200);

		if (mSkillTimer > 540)
		{
			mEffectTimer = 0;
			IsSkillRender = true;
			mSkillTimer = 0;
			IsSkill = false;
		}
	}
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
			if (mMeshCount == mObjectSize * 2)
				IsRevolution = false;
		}
	}
	else
	{
		mMesh[mLevel - 1].Draw(Buffer, mPosition.x - mObjectSize, mPosition.y - mObjectSize, mObjectSize * 2, mObjectSize * 2);
		mMeshCount = mObjectSize * 2;
		mAnimationCut = true;
	}
	mMesh[9].Draw(Buffer, mPosition.x - mObjectSize / 2, mPosition.y - mObjectSize - 30, mLife / 2, 5);
	mMesh[8].Draw(Buffer, mPosition.x - mObjectSize / 2, mPosition.y - mObjectSize - 35, mMana / 20 + 1, 5);
}
