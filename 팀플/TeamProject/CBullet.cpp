#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	for (int i = 0; i < 10; ++i)
		mMesh[i].Destroy();
}
int CBullet::GetDamage()
{
	return mDamage;
}
CBullet::CBullet(POINT p, TYPE Type)
{
	mDamage = 1;

	switch (Type)
	{
	case FIRE:
		mMesh[0].Load(TEXT("fire1.png"));
		mMesh[1].Load(TEXT("fire2.png"));
		mMesh[2].Load(TEXT("fire3.png"));
		mMesh[3].Load(TEXT("fire4.png"));
		break;
	case WATER:
		mMesh[0].Load(TEXT("water1.png"));
		mMesh[1].Load(TEXT("water2.png"));
		mMesh[2].Load(TEXT("water3.png"));
		mMesh[3].Load(TEXT("water4.png"));
		break;
	case GRASS:
		mMesh[0].Load(TEXT("grass1.png"));
		mMesh[1].Load(TEXT("grass2.png"));
		mMesh[2].Load(TEXT("grass3.png"));
		mMesh[3].Load(TEXT("grass4.png"));
		break;
	case ELEC:
		mMesh[0].Load(TEXT("grass1.png"));
		mMesh[1].Load(TEXT("grass2.png"));
		mMesh[2].Load(TEXT("grass3.png"));
		mMesh[3].Load(TEXT("grass4.png"));
		break;
	}
	mPosition = p;
	mObjectSize = 30;
	mMeshCount = 0;
}

bool CBullet::CollCheck(RECT Rect)
{
	RECT Temp;
	if (IntersectRect(&Temp, &Rect, &GetRect()))
		return true;
	return false;
}
bool CBullet::Animate()
{
	mPosition.x += BULLETSPEED;
	if (mPosition.x >= WIDTH)
		return true;
	return false;
}

void CBullet::Render(HDC Buffer)
{
	if (mMeshCount >= 40)
		mMeshCount = 0;
	mMesh[mMeshCount++ / 10].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize, mObjectSize);
}