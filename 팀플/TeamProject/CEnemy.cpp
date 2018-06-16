#include "CEnemy.h"

CEnemy::CEnemy()
{
	mMesh[0].Load(TEXT("pika.png"));
	mPosition = { WIDTH - 100, HEIGHT / 2 };
	mLife = 50;
	mObjectSize = 50;
}

CEnemy::~CEnemy()
{
	mMesh->Destroy();
}
void CEnemy::Render(HDC Buffer)
{
	mMesh[0].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize, mObjectSize);
}
