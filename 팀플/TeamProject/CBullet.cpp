#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	if(mMesh[4])
	mMesh[4].Destroy();
}

CBullet::CBullet(POINT p)
{
	mMesh[0].Load(TEXT("lite1.png"));
	mMesh[1].Load(TEXT("lite2.png"));
	mMesh[2].Load(TEXT("lite3.png"));
	mMesh[3].Load(TEXT("lite4.png"));
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