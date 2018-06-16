#include "CBullet.h"

CBullet::CBullet()
{
	mMesh[0].Load(TEXT("ball.png"));
}

CBullet::~CBullet()
{
}

CBullet::CBullet(POINT p)
{
	mMesh[0].Load(TEXT("ball.png"));
	mPosition = p;
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
	mMesh[0].Draw(Buffer, mPosition.x, mPosition.y, BULLETSIZE, BULLETSIZE);
}