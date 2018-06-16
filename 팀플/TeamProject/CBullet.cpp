#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	mMesh->Destroy();
}

CBullet::CBullet(POINT p)
{
	mMesh[0].Load(TEXT("grass.png"));
	mPosition = p;
	mObjectSize = 30;
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
	mMesh[0].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize, mObjectSize);
}